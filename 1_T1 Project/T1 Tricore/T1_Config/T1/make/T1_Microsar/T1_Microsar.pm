######################################################################################
#
#   File:           T1_Microsar.pm
#
#   Description:    Parse OS config files and extract task and interrupt configuration
#
#   $Author: alexandrebau $
#
#   $Revision: 49951 $
#
#   Copyright:      GLIWA GmbH embedded systems
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

use 5.006_000;

package T1_Microsar;
require Exporter;

use strict;
use warnings;

use base qw(Exporter);
our @EXPORT = qw(OsReadOsConfiguration OsGetValue OsGetSysElementReference OsGetIsrWrapper OsPerformInstrumentation OsGetRunnableDefinitions);

use File::Spec::Functions 'rel2abs';
use File::stat;

use constant MAX_NOF_CORES => 15;

######################################################################################
# Values to be assigned by reading OS-invocation file
######################################################################################
my $mcuCore;                                              # Used MCU [V850/TC2xx/TC3xx/MPC5xxx]
my $osCfgPath;                                            # Path to OS config files. The file names are hard-coded below as they should not change.
my $overrideNofCores;                                     # Optional: In case OS has more cores configured than shall be equipped with T1. This value overrides the number of cores [1..15]
my @osToPhysicalCoreIdMapping = ( 0..MAX_NOF_CORES - 1 ); # Optional: Only to be specified if OS-configuration uses different core IDs than the physical ones. Specify only cores that are used by the OS.
my $appendElementType = 'false';                          # Optional: Append type of Task (BCC, ECC or ECC Endless) and ISR (CAT2 or CAT1) to the elements name [true/false(default)]
my @runnableParseModules;                                 # Optional: modules such RTE.c can be parsed for runnable names. Macros are created accordingly in T1_config.h (or T1_ids.h respectively).
my $symbolGroupsPerEvent = 'false';                       # Optional: Create symbol groups per event instead of per task for tasks calling WaitEvent() [true/false(default)]
my $symbolGroupsMaxEntries;                               # Optional: Limit the number of entries per symbol group, a new symbol group will be created if the number has been exceeded [1..N]

######################################################################################
# Other global variables
######################################################################################
my $debug = 0;
my %taskIds; # Used for tasks and ISRs.
my %coreIds;
my $taskSymbolSuffix = '';
my $runnableShims = '';
my @includeDirs;
my @cpuFreq = (0);
my $maxTaskId = 0;
my $maxCat2Id = 0;
my $maxIsrPrio = 2000;
my $nofCores = 0;
my $osName = 'Vector Microsar OS';
my %systemElements;
my $compilerSpecificSymbolPrefix = '';

#----------------------------------------------------------------------------------
sub OsParseParam
{
    my $currentParam = shift;

    if( not $currentParam =~ /^;/ ) # a ';' Functions as a comment operator
    {
        my $val = '';
        my $validParamFound = 0;
        my @substr = split /;/, $currentParam;
        $currentParam = $substr[0];
        $currentParam =~ s/\s+$//;
        if( $debug )
        {
            print "$currentParam \n";
        }

        if( ($val) = $currentParam =~ /-mcuCore=(.*)/ )                      { $mcuCore          = $val;                    $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-osCfgPath=(.*)/ )                    { $osCfgPath        = $val;                    $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-overrideNofCores=(.*)/ )             { $overrideNofCores = $val;                    $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-osToPhysicalCoreIdMapping=(.*)/ )    { assignCoreIdMapping( $val );                 $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-appendElementType=(true|false)/ )    { $appendElementType = $val;                   $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-runnableParseModule=(.*)/ )          { push @runnableParseModules, rel2abs( $val ); $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-symbolGroupsPerEvent=(true|false)/ ) { $symbolGroupsPerEvent = $val;                $validParamFound = 1; }
        if( ($val) = $currentParam =~ /-symbolGroupsMaxEntries=(\d+)/ )      { $symbolGroupsMaxEntries = $val;              $validParamFound = 1; }

        if( (not $validParamFound) and ($currentParam =~ /^\s*-.*/) )
        {
            die "Error: invalid parameter $currentParam found in command line\n";
        }
    }

    return;
}

######################################################################################
# assign coreID mapping
######################################################################################
sub assignCoreIdMapping
{
    my $coreIdMappingStr = shift;
    # Remove whitespaces
    $coreIdMappingStr =~ s/\s//g;

    if( $coreIdMappingStr =~ /^(?:-?\d+)(?:,-?\d+)+$/ )
    {
        my @newMapping = map { int } split /,/, $coreIdMappingStr;
        splice @osToPhysicalCoreIdMapping, 0, scalar @newMapping, @newMapping;
    }
    else
    {
        die "Error: Incorrect format of parameter -osToPhysicalCoreIdMapping!\n       Format: -osToPhysicalCoreIdMapping=0,1,2\n";
    }

    return;
}

######################################################################################
# Parse command line
######################################################################################
sub OsReadOsConfiguration
{
    my( $invocationFile, @incDirs ) = @_;

    @includeDirs = @incDirs;

    if( $invocationFile )
    {
        open my $INVOCATION_FILE, '<', $invocationFile or die "Error: could not locate invocation file '$invocationFile.'\n";
        while( my $currentLine = <$INVOCATION_FILE> )
        {
            OsParseParam( $currentLine );
        }
        close $INVOCATION_FILE;
    }

    ######################################################################################
    # Define architecture (and compiler) specific symbol prefixes
    ######################################################################################

    if( ( $mcuCore ne 'V850' ) and ( $mcuCore ne 'TC2xx' ) and ( $mcuCore ne 'TC3xx' ) and ( $mcuCore ne 'MPC5xxx' ) )
    {
       die "Selected MCU $mcuCore not yet supported by this script!\n";
    }
    elsif( $mcuCore eq 'V850' )
    {
        # Assume that Green Hills Compiler is used which prefixes function symbols with an underscore
        $compilerSpecificSymbolPrefix = '_';
    }

    if( $debug )
    {
        foreach my $dir ( @includeDirs )
        {
            print "Include: '$dir'\n";
        }
    }

    ######################################################################################
    # Read core ID mapping from Os_Core_Lcfg.c
    ######################################################################################

    my $fileName = rel2abs( $osCfgPath.'Os_Core_Lcfg.c' );
    if( -e $fileName )
    {
        my $foundCore = 0;
        my $currentCore;
        my $currentCoreId;


        open my $CORE_FILE, '<', $fileName or die "Unable to read '$fileName'\n";
        print "\nStart parsing '$fileName'\n" if $debug;

        while( my $currentLine = <$CORE_FILE> )
        {
            if( $currentLine =~ /\/\*! Core configuration data:/ )
            {
                $foundCore = 1;
                print 'Found core ' if $debug;
            }
            elsif( $foundCore == 1 )
            {
                if( $currentLine =~ /\};/ )
                {
                    $foundCore = 0;
                }
                elsif( $currentLine =~ /CONST\(Os_CoreAsrConfigType,\s* OS_CONST\)\s*(\w+)\s*=/ )
                {
                    $currentCore = $1;
                    print "with name $currentCore " if $debug;
                }
                elsif( $currentLine =~ /\/\*\s*\.(?:CoreId|Id)\s*=\s*\*\/\s*OS_CORE_ID_(\d+),/ )
                {
                    $currentCoreId = $1;
                    $coreIds{$currentCore} = $currentCoreId;
                    print "and core ID $currentCoreId\n" if $debug;
                    if( $nofCores <= $currentCoreId )
                    {
                        $nofCores = $currentCoreId + 1;
                    }
                }
            }
        }
        print "Number of cores is set to $nofCores\n" if $debug;

        close $CORE_FILE;
        print "Stop parsing '$fileName'\n" if $debug;
    }
    else
    {
        die "File '$fileName' not found\n";
    }

    ######################################################################################
    # Read task and ISR trace IDs from Os_Types_Lcfg.h - OS Timing Hooks must be enabled!
    ######################################################################################

    $fileName = rel2abs( $osCfgPath.'Os_Types_Lcfg.h' );
    if( -e $fileName )
    {
        my $idCntr = 0;
        my $foundIds = 0;
        my $idCntrChck = 0;

        open my $TYPES_FILE, '<', $fileName or die "Unable to read '$fileName'\n";
        print "\nStart parsing '$fileName'\n" if $debug;

        while( my $currentLine = <$TYPES_FILE> )
        {
            if( $currentLine =~ /\/\*! Trace thread identifier/ )
            {
                $foundIds = 1;
                print "Found IDs\n" if $debug;
            }
            elsif( $foundIds == 1 )
            {
                if( $currentLine =~ /Os_TraceThreadIdType;/ )
                {
                    $foundIds = 0;
                    print "End of IDs\n" if $debug;
                    last; # Stop processing the file
                }
                elsif( $currentLine =~ /OS_TRACE_THREADID_COUNT\s*=\s*\(?(\d+)/ )
                {
                    $idCntrChck = int $1;
                }
                elsif( $currentLine =~ /Os_TraceId_(\w+)\s*=\s*\(?(\d+)/ )
                {
                    $taskIds{$1} = int $2;
                    $idCntr ++;
                    if( $maxTaskId < $taskIds{$1} )
                    {
                        $maxTaskId = $taskIds{$1};
                    }
                    print "ID $2 for task/ISR $1\n" if $debug;
                }
            }
        }

        if( ( 0 == $idCntrChck ) || ( 0 == $idCntr ) )
        {
            die "No trace IDs found! OS Timing Hooks are probably disabled!\n";
        }
        elsif( $idCntrChck != $idCntr )
        {
            die "Number of trace IDs found ($idCntr) doesn't match OS trace ID count (OS_TRACE_THREADID_COUNT = $idCntrChck)!\n";
        }

        close $TYPES_FILE;
        print "Stop parsing '$fileName'\n" if $debug;
    }
    else
    {
        die "File '$fileName' not found\n";
    }

    ######################################################################################
    # Read task priorities and core assignment from Os_Task_Lcfg.c
    ######################################################################################

    $fileName = rel2abs( $osCfgPath . 'Os_Task_Lcfg.c' );
    if( -e $fileName )
    {
        my $foundTask;
        my $currentTask;
        my $currentTaskPrio;
        my $currentTaskIsECC;
        my $currentTaskMaxAct;
        my $currentCore;
        my $currentCoreId;

        open my $TASK_FILE, '<', $fileName or die "Unable to read '$fileName'\n";
        print "\nStart parsing '$fileName'\n" if $debug;

        while( my $currentLine = <$TASK_FILE> )
        {
            if( $currentLine =~ /! Task configuration data:\s*(\w+)\s*/ )
            {
                $foundTask = 1;
                $currentTask = $1;
                $currentCore = undef; # Overwrite current core id, to be able to detect that it wasn't found for a task
                undef $currentTaskIsECC;
                $currentTaskMaxAct = 1; # Set to one to ensure compatibility
            }
            elsif( $currentLine =~ /\};/ )
            {
                if( not defined $currentCore )
                {
                    die "Could not find Core ID for Task $currentTask, the OS specific Perl module might need to be adapted, please contact support\@gliwa.com\n";
                }
                else
                {
                    $systemElements{'Task'}{$currentTask} = {
                                                                'Name'                => $currentTask,
                                                                'Comment'             => ( $appendElementType eq 'true' ) ? ( ( $currentTaskIsECC eq 'TRUE' ) ? 'ECC' : 'BCC' ) : '',
                                                                'SymbolName'          => $compilerSpecificSymbolPrefix . 'Os_Task_' . $currentTask . $taskSymbolSuffix,
                                                                'Offset'              => 0,
                                                                'Period'              => 0,
                                                                'ID'                  => $taskIds{$currentTask},
                                                                'Priority'            => $currentTaskPrio,
                                                                'Core'                => $currentCoreId,
                                                                'MaxActivations'      => $currentTaskMaxAct,
                                                                'Type'                => 'Task',
                                                                'scriptInternalIsECC' => ( $currentTaskIsECC eq 'TRUE' ) ? 1 : 0
                                                            };
                }
                undef $foundTask;
            }
            elsif( $foundTask )
            {
                if( $currentLine =~ /^.*\.Core\s*=\s*\*\/\s*&(\w+)/ )
                {
                    $currentCore = $1;
                    $currentCoreId = $coreIds{$currentCore};
                    print "Found core $currentCoreId for task $currentTask\n" if $debug;
                }
                elsif( $currentLine =~ /^.*\.HomePriority\s*=\s*\*\/\s*(?:\([\w\s]+\))?\s*(\d+)/ )
                {
                    if( ( $mcuCore eq 'V850' ) or ( $mcuCore eq 'TC2xx' ) or ( $mcuCore eq 'TC3xx' ) or ( $mcuCore eq 'MPC5xxx' ) )
                    {
                        $currentTaskPrio = 1000 - $1; # Lowest value means highest priority
                    }
                    else
                    {
                        $currentTaskPrio = $1; # Highest value means highest priority
                    }
                    print "Found prio $currentTaskPrio for task $currentTask\n" if $debug;
                }
                elsif( $currentLine =~ /^.*\.IsExtended\s*=\s*\*\/\s*(?:\([\w\s]+\))?\s*(\w+)/ )
                {
                    $currentTaskIsECC = $1;
                }
                elsif( $currentLine =~ /^.*\.MaxActivations\s*=\s*\*\/\s*(?:\([\w\s]+\))?\s*(\d+)/ )
                {
                    $currentTaskMaxAct = int $1;
                }
            }
        }
        close $TASK_FILE;
        print "Stop parsing '$fileName'\n" if $debug;
    }
    else
    {
        die "File '$fileName' not found\n";
    }

    ######################################################################################
    # Read ISR priorities and core assignment from Os_Hal_Interrupt_Lcfg.c
    ######################################################################################

    $fileName = rel2abs( $osCfgPath . 'Os_Hal_Interrupt_Lcfg.c' );
    my $cat1ISRID = $maxTaskId + 1;
    if( -e $fileName )
    {
        my $foundIsr = 0;
        my $currentCore;
        my $currentIsr;
        my $currentIsrPrio;

        open my $IRQ_FILE, '<', $fileName or die "Unable to read '$fileName'\n";
        print "\nStart parsing '$fileName'\n" if $debug;

        while( my $currentLine = <$IRQ_FILE> )
        {
            if( $currentLine =~ /! HAL ISR configuration data:\s*(\w+)\s*/ )
            {
                # Start of the ISR definition
                $foundIsr = 1;
                $currentIsr = $1;
                print "Found ISR $currentIsr\n" if $debug;
            }
            elsif( $foundIsr and $currentLine =~ /\};/ )
            {
                # End of the ISR definition
                if( not defined $currentCore )
                {
                    die "Could not find Core ID for ISR $currentIsr, the OS specific Perl module might need to be adapted, please contact support\@gliwa.com\n";
                }
                elsif( defined $taskIds{$currentIsr} ) # Store ISR only if trace ID is defined by OS (exclude cat1 ISRs and exceptions).
                {
                    $systemElements{'Interrupt'}{$currentIsr} = {  'Name'           => $currentIsr,
                                                                   'Comment'        => ( $appendElementType eq 'true' ) ? 'CAT2' : '',
                                                                   'SymbolName'     => $compilerSpecificSymbolPrefix . 'Os_Isr_' . $currentIsr,
                                                                   'Offset'         => 0,
                                                                   'Period'         => 0,
                                                                   'Priority'       => $currentIsrPrio,
                                                                   'ID'             => $taskIds{$currentIsr},
                                                                   'Core'           => $currentCore,
                                                                   'Type'           => 'Interrupt',
                                                                   'Category'       => 2 };
                }
                else #Cat1 ISRs
                {
                    $systemElements{'Interrupt'}{$currentIsr} = {  'Name'           => $currentIsr,
                                                                   'Comment'        => ( $appendElementType eq 'true' ) ? 'CAT1' : '',
                                                                   'SymbolName'     => '',
                                                                   'Offset'         => 0,
                                                                   'Period'         => 0,
                                                                   'Priority'       => $currentIsrPrio,
                                                                   'ID'             => $cat1ISRID,
                                                                   'Core'           => $currentCore,
                                                                   'Type'           => 'Interrupt',
                                                                   'Category'       => 1 };
                    $cat1ISRID++;
                }

                $foundIsr = 0;
                undef $currentIsr;
                undef $currentCore;
                undef $currentIsrPrio;
            }
            elsif( $foundIsr )
            {
                # There are different flavours of how the core id is defined in Microsar
                if( ( $currentLine =~ /\s*\.CoreID\s*=\s*\*\/\s*\(uint32\)\w*CORE_ID_(\d+)/ ) or # Older RH850
                    ( $currentLine =~ /\s*\.CoreAssignment\s*=\s*\*\/\s*\w*CORE\((\d+)\)/ ) or # MPC5xxx
                    ( $currentLine =~ /\s*\.CoreAssignment\s*=\s*\*\/\s*\w*?(\d+)/ ) or # TC2xx / TC3xx
                    ( $currentLine =~ /\s*\.CoreID\s*=\s*\*\/\s*\(uint32\)(\d+)/ ) # MICROSAR 4 Release 18 (RH850), just a plain number
                  )
                {
                    $currentCore = int $1; # Make sure that we get an integer value
                    if( ( $mcuCore eq 'TC3xx' ) and ( $currentCore > 0 ) ) # OS file Os_Hal_Interrupt_Lcfg.c is using .CoreAssignment 0, 2 and 3 for the ISRs for core 0, 1, and 2.
                    {
                        --$currentCore;
                    }
                    print "Found core $currentCore for ISR $currentIsr\n" if $debug;
                }
                elsif( ( $currentLine =~ /\s*\.IntLevel\s*=\s*\*\/\s*\(uint32\)(\d+)/ ) or
                       ( $currentLine =~ /\s*\.Level\s*=\s*\*\/\s*(\d+)/ ) or
                       ( not defined $currentIsrPrio and $currentLine =~ /\s*\.Source\s*=\s*\*\/\s*(\d+),/ )
                     )
                {
                    if( $mcuCore eq "V850" )
                    {
                        $currentIsrPrio = 2000 - $1; # Lowest value means highest priority
                    }
                    else
                    {
                        $currentIsrPrio = 2000 + $1; # Highest value means highest priority
                    }
                    print "Found prio $currentIsrPrio for ISR $currentIsr\n" if $debug;
                }
            }
        }

        close $IRQ_FILE;
        print "Stop parsing '$fileName'\n" if $debug;
    }
    else
    {
        die "File '$fileName' not found\n";
    }

    ######################################################################################
    # Set general parameters
    ######################################################################################

    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime time;
    my $dateAndTime = sprintf "%02d.%02d.%04d at %02d:%02d:%02d", $mday, ( $mon + 1 ), ( $year + 1900 ), $hour, $min, $sec;
    my @isCoreUnused = 1 x MAX_NOF_CORES;

    for my $core ( 0..$nofCores-1 )
    {
        unless( $osToPhysicalCoreIdMapping[$core] == -1 )
        {
            $isCoreUnused[$osToPhysicalCoreIdMapping[$core]] = 0;
        }
    }

    if( $overrideNofCores ) # This value overrides the number of cores
    {
        $nofCores = $overrideNofCores;
    }

    $systemElements{'OS'}{'Info'} = {
                                        'GenDate'               => $dateAndTime,
                                        'GenSource'             => qq("$osCfgPath"),
                                        'NofCores'              => $nofCores,
                                        'UnusedCoreLookupTable' => \@isCoreUnused
                                    };

    ######################################################################################
    # Read runnables from RTE.c and others if desired:
    ######################################################################################

    foreach my $runnableParseModule ( @runnableParseModules )
    {
        if( -e $runnableParseModule )
        {
            my $currentTask;
            my $isTask = 0;
            my @symbolsPerTask;
            my $currentTaskRef;
            my $foundVfbEEStartMacro;
            my $foundEEComment;

            open my $RUN_MOD_FILE, '<', $runnableParseModule or die "Unable to read '$runnableParseModule'\n";

            print "Reading '$runnableParseModule'\n" if $debug;
            my @waitForEvents;
            my $runnablesPerEvent;
            my $blockLevel;
            my $currentEvent;
            while( my $currentLine = <$RUN_MOD_FILE> )
            {
                if( $currentLine =~ /^TASK\(\s*(\w+)\s*\)/ )
                {
                    $isTask = 1;
                    $currentTask = $1;
                    print "Found task '$currentTask'\n" if $debug;
                    $currentTaskRef = $systemElements{'Task'}{$currentTask};

                    unless( defined $currentTaskRef )
                    {
                        warn sprintf "Warning: Found TASK(%s) in '%s' which has not been found while reading the OS configuration!\n", $currentTask, $runnableParseModule;
                        $isTask = 0;
                        undef $currentTask;
                    }

                    undef $currentEvent;
                    undef $runnablesPerEvent;
                    undef @waitForEvents;
                    undef @symbolsPerTask; # Clear on new task definition
                }
                elsif( $isTask )
                {
                    if( ( $symbolGroupsPerEvent eq 'true' ) and $systemElements{'Task'}{$currentTask}{'scriptInternalIsECC'} )
                    {
                        # Detect endless ECC Tasks and events
                        if( $currentLine =~ /for\s*\(\s*[;]\s*[;]\s*\)/ )
                        {
                            $isTask = 2;
                            printf "  Detected endless ECC task '%s'\n", $currentTask if $debug;

                            if( $appendElementType eq 'true' )
                            {
                                $systemElements{'Task'}{$currentTask}{'Comment'} = 'ECC Endless';
                            }
                        }
                        elsif( ( $isTask == 2 ) and ( $currentLine =~ /^\s*\(void\)WaitEvent\s*\((.+)\)\s*;/ ) )
                        {
                            @waitForEvents = split /\s*[|]\s*/, $1;

                            printf "  Wait for events:\n    %s\n", join "\n    ", @waitForEvents if $debug;
                        }
                        elsif( ( $isTask == 2 ) and ( $currentLine =~ /^\s*if\s*[(\s]+ev\s*\&\s*(\w+)\s*\)/ ) )
                        {
                            # Check if the extracted event is in the WaitEvent list
                            if( grep { $_ eq $1 } @waitForEvents )
                            {
                                $currentEvent = $1;
                            }
                            else
                            {
                                undef $currentEvent;
                            }

                            $blockLevel = 0;
                        }
                        elsif( defined $currentEvent )
                        {
                            if( $currentLine =~ /\{/ )
                            {
                                ++$blockLevel;
                            }
                            elsif( $currentLine =~ /\}/ )
                            {
                                --$blockLevel;

                                if( $blockLevel == 0 )
                                {
                                    if( defined $runnablesPerEvent->{$currentEvent} )
                                    {
                                        my @array_ref = @{$runnablesPerEvent->{$currentEvent}};
                                        $systemElements{'SymbolGroup'}{$currentEvent} = {
                                                                                            'Name'               => $currentEvent . '_Runnables',
                                                                                            'IsCode'             => 'true',
                                                                                            'MeasureDuration'    => 1000,
                                                                                            'FocusIntervalCount' => 16777216,
                                                                                            'Core'               => $systemElements{'Task'}{$currentTask}{'Core'},
                                                                                            'SymbolGroupElemRef' => \@array_ref
                                                                                        };
                                        printf "  Runnables for event '%s':\n    %s\n", $currentEvent, ( join "\n    ", @array_ref ) if $debug;
                                    }
                                }
                            }
                        }
                    }

                    # Extract Executable Entities (RunnableEntity or BswSchedulableEntity)
                    # Executable Entities are identified by either of the following two conditions
                    # 1. Comment "call runnable" or "call schedulable entity"
                    # 2. The VFB Tracing Hooks for Runnable Entity and BSW Schedulable Entities Trace Events
                    if( $currentLine =~ /\/\* call (?:runnable|schedulable entity) \*\// )
                    {
                        $foundEEComment = 1;
                        undef $foundVfbEEStartMacro;
                    }
                    elsif( ( $currentLine =~ /(Rte_(\w*)Runnable_\w+_Start)/ ) or ( $currentLine =~ /(SchM_(\w*)Schedulable_\w+_Start)/ ) ) # Use two RegEx's to ensure that signatures match
                    {
                        my $startMacro = $1;
                        my $client = $2; # Trace Client Name, currently unused but might become handy in the future

                        undef $foundEEComment;
                        $foundVfbEEStartMacro = 1;
                    }
                    elsif( $foundEEComment or $foundVfbEEStartMacro )
                    {
                        chomp $currentLine;
                        $currentLine =~ s/\s+//s; # Remove whitespace, including end-of-line
                        if( $currentLine =~ /^.*?(\w+)\s*\(.*?\).*$/ )
                        {
                            my $runnableName = $1;

                            # Avoid creating a per Task symbol group in case a per Event symbol group is going to be created
                            if( $currentEvent )
                            {
                                if( not grep { /^$compilerSpecificSymbolPrefix$runnableName$/ } @{$runnablesPerEvent->{$currentEvent}} )
                                {
                                    push @{$runnablesPerEvent->{$currentEvent}}, $compilerSpecificSymbolPrefix.$runnableName;
                                }
                            }
                            else
                            {
                                if( not grep { /^$compilerSpecificSymbolPrefix$runnableName$/ } @symbolsPerTask )
                                {
                                    push @symbolsPerTask, $compilerSpecificSymbolPrefix.$runnableName;
                                }
                            }

                            # Only push to task if task exists and if the Runnable is not already present
                            if( $currentTaskRef and not grep { /^$runnableName$/ } @{$currentTaskRef->{'Runnables'}} )
                            {
                                # Create Runnable SystemElement under Task SystemElement
                                push @{$currentTaskRef->{'Runnables'}}, $runnableName;
                            }
                        }

                        undef $foundEEComment;
                        undef $foundVfbEEStartMacro;
                    }
                    elsif( $currentLine =~ /^\}/ )
                    {
                        if( 0 < scalar @symbolsPerTask )
                        {
                            my @array_ref = @symbolsPerTask;
                            $systemElements{'SymbolGroup'}{$currentTask} = {
                                                                                'Name'               => $currentTask . '_Runnables',
                                                                                'IsCode'             => 'true',
                                                                                'MeasureDuration'    => 1000,
                                                                                'FocusIntervalCount' => 16777216,
                                                                                'Core'               => $systemElements{'Task'}{$currentTask}{'Core'},
                                                                                'SymbolGroupElemRef' => \@array_ref
                                                                            };
                        }

                        undef $isTask;
                        undef $currentTaskRef;
                    }
                }
            }
            close $RUN_MOD_FILE;
        }
        else
        {
            die "File '$runnableParseModule' not found\n";
        }
    }

    if( $symbolGroupsMaxEntries and defined $systemElements{'SymbolGroup'} )
    {
        my @symbolGroupRefNames = keys %{$systemElements{'SymbolGroup'}};

        while( my $key = shift @symbolGroupRefNames )
        {
            my $value = \%{$systemElements{'SymbolGroup'}{$key}};
            my @symbols = @{$value->{'SymbolGroupElemRef'}};

            if( scalar @symbols > $symbolGroupsMaxEntries )
            {
                my $SymbolGroupElemRef;
                my $countSymbols = 0;
                while( my $symbol = shift @symbols )
                {
                    if( ( $countSymbols % $symbolGroupsMaxEntries ) == 0 )
                    {
                        my @symbolsPerGroup;
                        my $name = $value->{'Name'} . sprintf "_%d", $countSymbols / $symbolGroupsMaxEntries;

                        $systemElements{'SymbolGroup'}{$name} = {
                                                                    'Name'               => $name,
                                                                    'IsCode'             => $systemElements{'SymbolGroup'}{$key}{'IsCode'},
                                                                    'MeasureDuration'    => $systemElements{'SymbolGroup'}{$key}{'MeasureDuration'},
                                                                    'FocusIntervalCount' => $systemElements{'SymbolGroup'}{$key}{'FocusIntervalCount'},
                                                                    'Core'               => $systemElements{'SymbolGroup'}{$key}{'Core'},
                                                                    'SymbolGroupElemRef' => \@symbolsPerGroup
                                                                };

                        $SymbolGroupElemRef = \@{$systemElements{'SymbolGroup'}{$name}{'SymbolGroupElemRef'}};
                    }

                    push @$SymbolGroupElemRef, $symbol;
                    ++$countSymbols;
                }

                delete $systemElements{'SymbolGroup'}{$key};
            }
        }
    }

    return;
}

sub OsGetValue
{
    my $ref = shift;
    my $key = shift;
    my $name = shift;
    return $ref->{$key}{$name} if exists $ref->{$key}{$name};

    return 0;
}

sub OsGetSysElementReference
{
    my $name = shift;
    return $systemElements{$name} if exists $systemElements{$name};

    return 0;
}

sub OsGetIsrWrapper
{
    return '';
}

sub OsGetRunnableDefinitions
{
    return $runnableShims;
}

sub OsPerformInstrumentation
{
}

1;
