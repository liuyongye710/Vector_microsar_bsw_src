######################################################################################
#
#   File:           T1_neusarOS.pm
#
#   Description:    Satisfy callouts from T1_projGen.pl and return empty list of SystemElements
#
#   $Author: jialinli $
#
#   $Revision: 370 $
#
#   Copyright:      GLIWA embedded systems GmbH & Co. KG
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

use 5.006_000;

package T1_neusarOS;
require Exporter;
our @ISA = ("Exporter");
our @EXPORT = qw(OsReadOsConfiguration OsGetValue OsGetSysElementReference OsGetIsrWrapper OsPerformInstrumentation);

use strict;
use warnings;
use File::Spec::Functions 'rel2abs';

############### Parameters to be assigned via invocation file #########################

my $overrideNofCores = 0;       # Set number of cores



# global vars
my $debug = 0;
my $isrShims = "";
my $nOfCores = 1;
my $cpuFreq = 0;
my %systemElements = ();
my $symbolPrefix;
my @osDefineStacks;
my $osCfgPath="";
my %macroDef = ();
my $maxTaskID = 0;

#----------------------------------------------------------------------------------
sub OsParseParam($)
{

    my $currentParam = $_[0];
    if (not $currentParam =~ /^;/) # a ';' functions as a comment operator
    {
        my $val = "";
        my $validParamFound = 0;
        my @substr = split(/;/, $currentParam);
        $currentParam = $substr[0];
        $currentParam =~ s/\s+$//;
        if( $debug )
        {
            print "$currentParam \n";
        }

        if (($val) = $currentParam =~ /-overrideNofCores=(.*)/)    { $overrideNofCores          = $val;             $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-osCfgPath=(.*)/ )                    { $osCfgPath        = $val;                    $validParamFound = 1; }

        if ( (not $validParamFound) and ($currentParam =~ /\s*-.*/) )
        {
            #die "error: invalid parameter $currentParam found in command line";
        }
    }
}

######################################################################################
# Read OS configuration
######################################################################################
sub OsReadOsConfiguration($$@)
{
    ( my $invocationFile, $symbolPrefix, my @incDirs ) = @_;

    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    my $dateAndTime = sprintf "on %02d.%02d.%04d at %02d:%02d:%02d", $mday, ($mon + 1), ($year + 1900), $hour, $min, $sec;

    if( $invocationFile )
    {
        open INVOCATION_FILE, "$invocationFile" or die "error: could not locate invocation file '$invocationFile.'";
        my $currentLine;
        while( $currentLine = <INVOCATION_FILE> )
        {
            &OsParseParam( $currentLine );
        }
        close( INVOCATION_FILE );
    }
    ######################################################################################
    # Read Os_Types_Cfg.h for Number of core and id macros
    ######################################################################################
    my $fileName = rel2abs( $osCfgPath.'Os_Types_Cfg.h' );
    if( -e $fileName )
    {

        open my $CORE_FILE, '<', $fileName or die "Unable to read '$fileName'\n";
        print "\nStart parsing '$fileName'\n" if $debug;

        while( my $currentLine = <$CORE_FILE> )
        {
            if ( $currentLine =~ /OS_COREID_COUNT\s*=\s*(\d)/ )
            {
                $nOfCores = $1;
                print "Number of core is $nOfCores \n" if $debug;
            }
            elsif (  $currentLine =~ / (\w+)\s*=\s*(\d+)/  )
            {
                $macroDef{$1} = $2;
                print "The value of macro $1 is $2 .\n" if $debug;
            }
        }
        close $CORE_FILE;
    }

    ######################################################################################
    # Read Os_Platform_Lcfg.c for tasks and ISRs
    ######################################################################################
    $fileName = rel2abs( $osCfgPath.'Os_Platform_Lcfg.c' );
    if( -e $fileName )
    {
        my $foundTask = 0;
        my $foundISR = 0;
        my $currentTaskISR;
        my $currentTaskISRPrio;
        my $currentTaskISRId;
        my $currentTaskISRCore;
        my $currentTaskISRSymbol;
        my $currentTaskMaxAct;

        open my $TASK_FILE, '<', $fileName or die "Unable to read '$fileName'\n";
        print "\nStart parsing '$fileName'\n" if $debug;

        while( my $currentLine = <$TASK_FILE> )
        {
            if ( $currentLine =~ /const\s+Os_TaskCfgType\s+OsCfg_Task_(\w+)\s*=/ )
            {
                $currentTaskISR = $1;
                $foundTask = 1;
                print "Start task: $currentTaskISR  \n" if $debug;
            }
            if ( $currentLine =~ /const\s+Os_IsrCfgType\s+OsCfg_Isr_(\w+)\s*=/ )
            {
                $currentTaskISR = $1;
                $foundISR = 1;
                print "Start ISR: $currentTaskISR  \n" if $debug;
            }
            if ( $foundTask )
            {
                if ( $currentLine =~ /^\};/ )
                {
                    $foundTask = 0;
                    $systemElements{'Task'}{$currentTaskISR} = {
                                                                'Name'                => $currentTaskISR,
                                                                'Comment'             => "",
                                                                'SymbolName'          => $currentTaskISR,
                                                                'Offset'              => 0,
                                                                'Period'              => 0,
                                                                'ID'                  => $currentTaskISRId,
                                                                'Priority'            => $currentTaskISRPrio,
                                                                'Core'                => $currentTaskISRCore,
                                                                'MaxActivations'      => $currentTaskMaxAct,
                                                                'Type'                => 'Task'
                                                            };
                    print "Finish task: $currentTaskISR  \n\n" if $debug;
                    $currentTaskISR=undef;
                    $currentTaskISRPrio=undef;
                    $currentTaskISRId=undef;
                    $currentTaskISRCore=undef;
                    $currentTaskISRSymbol=undef;
                    $currentTaskMaxAct=undef;
                }
                if ( $currentLine =~ /\/\*\s*taskId\s*=\s*\*\/\s*(\w+),/ )
                {
                    my $currentTaskISRIdMacro = $1;
                    if ( exists ( $macroDef{$currentTaskISRIdMacro} ))
                    {
                        $currentTaskISRId = $macroDef{$currentTaskISRIdMacro};
                        if ( $currentTaskISRId > $maxTaskID )
                        {
                            $maxTaskID = $currentTaskISRId;
                        }
                    }
                    else
                    {
                        die "Can not find the ID of task $currentTaskISR \n";
                    }
                    print "Id of task $currentTaskISR : $currentTaskISRId \n" if $debug;
                }
                if ( $currentLine =~ /\/\*\s*coreId\s*=\s*\*\/\s*(\w+),/ )
                {
                    my $currentTaskISRCoreMacro = $1;
                    if ( exists ( $macroDef{$currentTaskISRCoreMacro} ))
                    {
                        $currentTaskISRCore = $macroDef{$currentTaskISRCoreMacro};
                    }
                    else
                    {
                        die "Can not find the Core ID of task $currentTaskISR \n";
                    }
                    print "Core Id of task $currentTaskISR : $currentTaskISRCore \n" if $debug;
                }
                if ( $currentLine =~ /\/\*\s*cfgPrio\s*=\s*\*\/\s*(\d+)/ )
                {
                    $currentTaskISRPrio = 1000 - $1;
                    print "Prio of task $currentTaskISR : $currentTaskISRPrio \n" if $debug;
                }
                if ( $currentLine =~ /\/\*\s*maxActivations\s*=\s*\*\/\s*(\d+)/ )
                {
                    $currentTaskMaxAct = $1;
                    print "Max Activations of task $currentTaskISR : $currentTaskMaxAct \n" if $debug;
                }
            }
            if ( $foundISR )
            {
                if ( $currentLine =~ /^\};/ )
                {
                    $foundISR = 0;
                    $systemElements{'Interrupt'}{$currentTaskISR} = {
                                                                'Name'                => $currentTaskISR,
                                                                'Comment'             => "",
                                                                'SymbolName'          => $currentTaskISR,
                                                                'Offset'              => 0,
                                                                'Period'              => 0,
                                                                'ID'                  => $currentTaskISRId,
                                                                'Priority'            => 1000, #$currentTaskISRPrio,
                                                                'Core'                => $currentTaskISRCore,
                                                                'Type'                => 'Interrupt',
                                                                'Category'            => 2
                                                            };
                    print "Finish ISR: $currentTaskISR  \n\n" if $debug;
                    $currentTaskISR=undef;
                    $currentTaskISRPrio=undef;
                    $currentTaskISRId=undef;
                    $currentTaskISRCore=undef;
                    $currentTaskISRSymbol=undef;

                }
                if ( $currentLine =~ /\/\*\s*isrId\s*=\s*\*\/\s*(\w+),/ )
                {
                    my $currentTaskISRIdMacro = $1;
                    if ( exists ( $macroDef{$currentTaskISRIdMacro} ))
                    {
                        $currentTaskISRId = $macroDef{$currentTaskISRIdMacro} + $maxTaskID + 1;
                    }
                    else
                    {
                        die "Can not find the ID of ISR $currentTaskISR \n";
                    }
                    print "Id of ISR $currentTaskISR : $currentTaskISRId \n" if $debug;
                }
                if ( $currentLine =~ /\/\*\s*coreId\s*=\s*\*\/\s*(\w+),/ )
                {
                    my $currentTaskISRCoreMacro = $1;
                    if ( exists ( $macroDef{$currentTaskISRCoreMacro} ))
                    {
                        $currentTaskISRCore = $macroDef{$currentTaskISRCoreMacro};
                    }
                    else
                    {
                        die "Can not find the Core ID of ISR $currentTaskISR \n";
                    }
                    print "Core Id of ISR $currentTaskISR : $currentTaskISRCore \n" if $debug;
                }
            }

        }
        close $TASK_FILE;
    }
    


    if( $overrideNofCores > 0 ) # by default nOfCores is 1
    {
        $nOfCores = $overrideNofCores;
    }

    $systemElements{"OS"}{'Info'} = {   "GenDate"        => $dateAndTime,
                                        "GenSource"      => "NeusarOS OS-module",
                                        "NofCores"       => $nOfCores,
                                        "CpuFreq"        => $cpuFreq,
                                        "ISRIDOffset"    => $maxTaskID,
                                        "defineStackRef" => \@osDefineStacks, };

}

######################################################################################
# OsGetValue
######################################################################################

sub OsGetValue($$$)
{
    my $ref = shift;
    my $key = shift;
    my $name = shift;
    return $ref->{$key}{$name} if exists $ref->{$key}{$name};

    return 0;
}

######################################################################################
# OsGetSysElementReference
######################################################################################

sub OsGetSysElementReference($)
{
    my $name = shift;
    return $systemElements{$name} if exists $systemElements{$name};

    return 0;
}

######################################################################################
# OsGetIsrWrapper
######################################################################################

sub OsGetIsrWrapper()
{
    # not required in conjunction with RTA Trace
    return $isrShims;
}

######################################################################################
# OsPerformInstrumentation
######################################################################################

sub OsPerformInstrumentation()
{

}

1;
