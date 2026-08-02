######################################################################################
#
#   File:           T1_config.pm
#
#   Description:    Generate T1 config datastructures
#
#   $Author: nick $
#
#   $Revision: 39039 $
#
#   Copyright:      GLIWA GmbH embedded systems
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

package T1_config;
require Exporter;
our @ISA = ("Exporter");
our @EXPORT = qw(GenT1ConfigC GenT1ConfigH);

use strict;
use warnings;

use constant DEBUG => 0;    # Change to 1 to enable debug logging information

######################################################################################
# sub addU for MISRA compliance with unsigned integer C literals
######################################################################################

sub addU($)
{
    my $unsignedInt = shift;
    $unsignedInt =~ s/^(0x[0-9A-Fa-f]+|\d+)$/$1u/;
    return $unsignedInt;
}

######################################################################################
# sub addUL for MISRA compliance with unsigned long C literals
######################################################################################

sub addUL($)
{
    my $unsignedInt = shift;
    $unsignedInt =~ s/^(0x[0-9A-Fa-f]+|\d+)$/$1uL/;
    return $unsignedInt;
}

######################################################################################
# sub SecString returns the #include MemMap to start/stop a given section
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Core ID
#   START or STOP
#   NO_INIT_x or CONST_x or CODE
#   Alignment in bits
sub SecString($$$$)
{
    my $coreId = shift;
    my $ppIndent = shift;
    my $startStop = shift;
    my $kind = shift;
    my $coreSuffix = "";
    $coreSuffix = "_CORE$coreId" if 0 <= $coreId;
    return  "#   ${ppIndent}define T1_${startStop}_SEC_$kind$coreSuffix\n#   ${ppIndent}include \"T1_MemMap.h\"";
}

######################################################################################
# sub Sec prints the #include MemMap to start/stop a given section
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Core ID
#   START or STOP
#   NO_INIT_x or CONST_x or CODE
#   Alignment in bits
sub Sec($$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $coreId = shift;
    my $startStop = shift;
    my $kind = shift;
    print $fh (SecString( $coreId, $ppIndent, $startStop, $kind ) . "\n");
}

######################################################################################
# sub GenMultiCoreDataStructure prints a multi-core array
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Non-zero number of cores
#   Name of array
#   Name of array element type
#   Alignment in bits
#   Name of each element with XX for core ID - OR - reference to array of names
sub GenMultiCoreDataStructure($$$$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $nofCores = shift;
    my $arrayName = shift;
    my $elementType = shift;
    my $alignmentBits = shift;
    my $elementName = shift;
    my @elementNames;
    foreach my $coreId ( 0 .. ($nofCores-1) )
    {
        my $nextElementName;
        if( 'ARRAY' eq ref $elementName )
        {
            $nextElementName = $elementName->[$coreId] . 'u';
        }
        else
        {
            $nextElementName = $elementName;
            $nextElementName =~ s/XX/$coreId/g;
        }
        push @elementNames, ($nextElementName);
    }

    Sec( $fh, $ppIndent, -1, 'START', "CONST_$alignmentBits" );
    printf $fh "%-23s T1_SEC_CONST_%d %s[%d] =\n{\n    ", "$elementType const", $alignmentBits, $arrayName, $nofCores;
    print $fh ((join ",\n    ", @elementNames) . "\n");
    print $fh "};\n";
    Sec( $fh, $ppIndent, -1, 'STOP', "CONST_$alignmentBits" );
}

######################################################################################
# sub GenMultiCoreDataStructurePlusElements prints a multi-core array and generates
#     the datastructures referenced in that array
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Non-zero number of cores
#   Name of array element type
#   Alignment in bits
#   Name of each element (without the core ID suffix)
sub GenMultiCoreDataStructurePlusElements($$$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $nofCores = shift;
    my $elementType = shift;
    my $alignmentBits = shift;
    my $elementName = shift;

    foreach my $coreId ( 0 .. ($nofCores-1) )
    {
        Sec( $fh, $ppIndent, $coreId, 'START', "NO_INIT_$alignmentBits" );
        printf $fh "%-23s T1_SEC_NO_INIT_%d_CORE%d %s%d;\n", $elementType, $alignmentBits, $coreId, $elementName, $coreId;
        Sec( $fh, $ppIndent, $coreId, 'STOP', "NO_INIT_$alignmentBits" );
    }

    GenMultiCoreDataStructure( $fh, $ppIndent, $nofCores, $elementName . 'PC', $elementType . ' *', $alignmentBits, '&' . $elementName . 'XX' );
}

######################################################################################
# sub Gen2DimensionalMultiCoreDataStructure prints a multi-core array and generates
#     the array datastructures referenced in that array
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Non-zero number of cores
#   Name of array element type
#   Section name
#   Name of each element (without the core ID suffix)
sub Gen2DimensionalMultiCoreDataStructure($$$$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $nofCores = shift;
    my $elementType = shift;
    my $alignmentBits = shift;
    my $elementName = shift;
    my $secondDimension = shift;

    foreach my $coreId ( 0 .. ($nofCores-1) )
    {
        my $arraySize = $secondDimension;
        $arraySize =~ s/XX/$coreId/g;
        Sec( $fh, $ppIndent, $coreId, 'START', "NO_INIT_$alignmentBits" );
        if( $alignmentBits =~ /TRACEBUFFER/ )
        {
            print $fh <<EOT;
#   ${ppIndent}if defined T1_EXTERNAL_TRACEBUFFER
T1_EXTERN
#   ${ppIndent}endif /* !defined T1_EXTERNAL_TRACEBUFFER */
EOT
        }
        # $alignmentBits is formatted as a string so that we can append DCX
        printf $fh "%-23s T1_SEC_NO_INIT_%s_CORE%d %s%d[%s];\n", $elementType, $alignmentBits, $coreId, $elementName, $coreId, $arraySize;
        Sec( $fh, $ppIndent, $coreId, 'STOP', "NO_INIT_$alignmentBits" );
    }

    $alignmentBits =~ s/_.*$//;
    GenMultiCoreDataStructure( $fh, $ppIndent, $nofCores, $elementName . 'PC', $elementType . ' *', $alignmentBits, $elementName . 'XX' );
}

my %secStrings;

######################################################################################
# sub GenT1ConfigC prints the generated segment of T1_config.c
######################################################################################

# Input:
#   File handle for output
#   Configuration database as a Perl hash
sub GenT1ConfigC($$)
{
    my $fh = shift;
    my $configRef = shift;
    my %config = %$configRef;
    my $nofCores = $config{'nofCores'};
    my @nofTasks = @{$config{'numberOfTasks'}};
    my @nofUserStopwatches = map { abs } @{$config{'numberOfUserStpws'}};
    my @nofConstraints = @{$config{'numberOfConstraints'}};
    my @CPULoadThresholds = @{$config{'cpuLoadThreshold'}};
    foreach my $CPULoadThreshold (@CPULoadThresholds)
    {
        # Convert from percentage to 256ths
        $CPULoadThreshold = int( $CPULoadThreshold * 2.56 );
        $CPULoadThreshold = 0 if $CPULoadThreshold < 0;
        $CPULoadThreshold = 255 if 255 < $CPULoadThreshold;
    }

    # Initialize %secStrings
    foreach my $startStop ('START', 'STOP')
    {
        foreach my $kind ('NO_INIT_8', 'NO_INIT_16', 'NO_INIT_32', 'NO_INIT_32_TRACEBUFFER', 'CONST_8', 'CONST_16', 'CONST_32', 'CODE', 'CODE_FAST')
        {
            foreach my $coreId ( -1 .. ($nofCores-1) )
            {
                foreach my $indentTab ( 0 .. 2 )
                {
                    $secStrings{$startStop}{$kind}{$coreId}{$indentTab} = SecString( $coreId, '    ' x $indentTab, $startStop, $kind );
                }
            }
        }
    }

######################################################################################
### Verify $nofCores                                                               ###
######################################################################################

    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
#if defined T1_NOF_CORES
#   error T1_NOF_CORES is defined and generated configuration is for single core T1
#endif /* defined T1_NOF_CORES */
EOT
    }
    else
    {
        print $fh <<EOT;
#if defined T1_NOF_CORES
#   if $nofCores != T1_NOF_CORES
#       error T1_NOF_CORES does not match generated configuration
#   endif /* $nofCores != T1_NOF_CORES */
#else /* ! defined T1_NOF_CORES */
#   error T1_NOF_CORES is not defined and generated configuration is for multi-core T1
#endif /* defined T1_NOF_CORES */
EOT
    }


######################################################################################
### T1.base                                                                        ###
######################################################################################
    print $fh <<EOT;

#if defined T1_ENABLE && !defined T1_DISABLE_T1_BASE

$secStrings{START}{CONST_8}{-1}{0}
EOT
    print $fh "T1_uint8_t const        T1_SEC_CONST_8 T1_commsCoreOffset = $config{'commsCoreOffset'}u;\n" if 0 < $nofCores;
    print $fh <<EOT;
#   if !defined T1_EXTERNAL_BID
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_CAT( T1_bid_, T1_BUILD_ID );
T1_uint8_t const        T1_SEC_CONST_8 T1_CAT( T1_bid_, T1_BUILD_ID ) = 0u;
#   endif /* !defined T1_EXTERNAL_BID */
#   if !defined T1_NO_INIT_SID
T1_uint8_t const        T1_SEC_CONST_8 T1_sid = T1_SID;
#   endif /* !defined T1_NO_INIT_SID */
$secStrings{STOP}{CONST_8}{-1}{0}
#   if defined T1_NO_INIT_SID
$secStrings{START}{NO_INIT_8}{-1}{1}
T1_uint8_t              T1_SEC_NO_INIT_8 T1_sid;
$secStrings{STOP}{NO_INIT_8}{-1}{1}
#   endif /* defined T1_NO_INIT_SID */
$secStrings{START}{CONST_16}{-1}{0}
T1_timeouts_t const     T1_SEC_CONST_16 T1_timeouts = { T1_TIMEOUT_RX, T1_TIMEOUT_TX, T1_TIMEOUT_RESPONSE };
$secStrings{STOP}{CONST_16}{-1}{0}
$secStrings{START}{CONST_32}{-1}{0}
#   if !defined T1_EXTERNAL_BID
T1_uint8_t const * const T1_SEC_CONST_32 T1_pBid = &T1_CAT( T1_bid_, T1_BUILD_ID );
T1_uint32_t const       T1_SEC_CONST_32 T1_bid = T1_CAT( T1_BUILD_ID, uL );
#   endif /* !defined T1_EXTERNAL_BID */
T1_featureMask_t const  T1_SEC_CONST_32 T1_initFeatureMask = T1_INIT_FEATURE_MASK;
$secStrings{STOP}{CONST_32}{-1}{0}
EOT

    print $fh "#   if defined T1_CPU32BIT\n";
    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{1}
T1_bool_t const         T1_SEC_CONST_8 T1_traceTimerBitLength = T1_TRACE_TIMER_BIT_LENGTH_CORE0;
$secStrings{STOP}{CONST_8}{-1}{1}
EOT
    }
    else
    {
        GenMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_traceTimerBitLengthPC', 'T1_bool_t', 8, 'T1_TRACE_TIMER_BIT_LENGTH_COREXX' );
    }
    print $fh "#   endif /* defined T1_CPU32BIT */\n";

    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{NO_INIT_32}{-1}{0}
T1_baseGlobals_t        T1_SEC_NO_INIT_32 T1_baseGlobals;
$secStrings{STOP}{NO_INIT_32}{-1}{0}
EOT
    }
    else
    {
        print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_nofCores = T1_NOF_CORES;
$secStrings{STOP}{CONST_8}{-1}{0}
EOT
        GenMultiCoreDataStructurePlusElements( $fh, '', $nofCores, 'T1_baseGlobals_t', 32, 'T1_baseGlobals' );
    }

    print $fh <<EOT;

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_BASE */
EOT

######################################################################################
### T1.cont                                                                        ###
######################################################################################
    print $fh <<EOT;

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#   if 8 != T1_CONT_NOF_VRTL_STPWS && 64 != T1_CONT_NOF_VRTL_STPWS
#       error Unsupported number of event chains configured (must be 8 or 64)
#   endif /* 8 != T1_CONT_NOF_VRTL_STPWS && 64 != T1_CONT_NOF_VRTL_STPWS */

$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_nOfVrtlStpws = T1_CONT_NOF_VRTL_STPWS;
T1_uint8_t const        T1_SEC_CONST_8 T1_nofFocusMeasurements = T1_CONT_NOF_FOCUS_MEASUREMENTS;
$secStrings{STOP}{CONST_8}{-1}{0}
EOT

    my $contNofCores = $nofCores;
    $contNofCores = 1 if $contNofCores <= 0;

    foreach my $coreId ( 0 .. ($contNofCores-1) )
    {
        print $fh <<EOT;
#   define T1_NOF_RESULTS_CORE$coreId \\
    (T1_NOF_TASKS_CORE$coreId + 2*(T1_NOF_USER_STPWS_CORE$coreId + T1_NOF_FLEX_STPWS_CORE$coreId + T1_CONT_NOF_VRTL_STPWS) + 3u)
#   if !defined T1_OVERHEAD_CORE${coreId}_NS
#       error T1_OVERHEAD_CORE${coreId}_NS not defined
#   endif /* T1_OVERHEAD_CORE${coreId}_NS */
#   if !defined T1_FLEX_OVERHEAD_CORE${coreId}_NS
#       error T1_FLEX_OVERHEAD_CORE${coreId}_NS not defined
#   endif /* T1_FLEX_OVERHEAD_CORE${coreId}_NS */
#   if !defined T1_CPULOAD_TX_PERIOD_CORE$coreId
#       error T1_CPULOAD_TX_PERIOD_CORE$coreId not defined
#   endif /* T1_CPULOAD_TX_PERIOD_CORE$coreId */
#   if !defined T1_CPULOAD_SAMPLES_CORE$coreId
#       error T1_CPULOAD_SAMPLES_CORE$coreId not defined
#   endif /* T1_CPULOAD_SAMPLES_CORE$coreId */
#   if !defined T1_NOF_TASKS_CORE$coreId
#       error T1_NOF_TASKS_CORE$coreId not defined
#   endif /* T1_NOF_TASKS_CORE$coreId */
#   if !defined T1_NOF_USER_STPWS_CORE$coreId
#       error T1_NOF_USER_STPWS_CORE$coreId not defined
#       if $nofUserStopwatches[$coreId] != T1_NOF_USER_STPWS_CORE$coreId
#           error T1_NOF_USER_STPWS_CORE$coreId does not match generated configuration
#       endif /* $nofUserStopwatches[$coreId] != T1_NOF_USER_STPWS_CORE$coreId */
#   endif /* T1_NOF_USER_STPWS_CORE$coreId */
#   if !defined T1_NOF_CSRNS_CORE$coreId
#       error T1_NOF_CSRNS_CORE$coreId not defined
#       if $nofConstraints[$coreId] != T1_NOF_CSRNS_CORE$coreId
#           error T1_NOF_CSRNS_CORE$coreId does not match generated configuration
#       endif /* $nofConstraints[$coreId] != T1_NOF_CSRNS_CORE$coreId */
#   endif /* T1_NOF_CSRNS_CORE$coreId */
#   if !defined T1_NOF_FLEX_STPWS_CORE$coreId
#       error T1_NOF_FLEX_STPWS_CORE$coreId not defined
#   endif /* T1_NOF_FLEX_STPWS_CORE$coreId */
#   if !defined T1_DISABLE_T1_FLEX && T1_NOF_FLEX_STPWS_CORE$coreId < 1
#       error At least one core $coreId T1.flex stopwatch is required
#   endif /* T1_NOF_FLEX_STPWS_CORE$coreId */
EOT
    }

    Sec( $fh, '', -1, 'START', 'NO_INIT_8' );
    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
T1_contStatus_t         T1_SEC_NO_INIT_8 T1_contBgStatus;
T1_contStatus_t         T1_SEC_NO_INIT_8 T1_contHandlerStatus;
EOT
    }
    else
    {
        print $fh <<EOT;
T1_contStatus_t         T1_SEC_NO_INIT_8 T1_contBgStatusPC[$nofCores];
T1_contStatus_t         T1_SEC_NO_INIT_8 T1_contHandlerStatusPC[$nofCores];
EOT
    }
    Sec( $fh, '', -1, 'STOP', 'NO_INIT_8' );

    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{NO_INIT_32}{-1}{0}
T1_contScopeGlobals_t   T1_SEC_NO_INIT_32 T1_contGlobals;
T1_stpwData_t           T1_SEC_NO_INIT_32 T1_stpwData[T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS];
T1_csrnData_t           T1_SEC_NO_INIT_32 T1_csrnData[$nofConstraints[0]u];
T1_resultTime_t         T1_SEC_NO_INIT_32 T1_resultBuffer[((T1_NOF_RESULTS_CORE0 + 0xFu) & ~0xFu) + 1u];
T1_taskStackElem_t      T1_SEC_NO_INIT_32 T1_taskStack[T1_MAX_TASK_PREEMPTIONS_CORE0+T1_TASK_STACK_OVERRUNS];
T1_vStpwMapping_t       T1_SEC_NO_INIT_32 T1_vStpw[2*T1_CONT_NOF_VRTL_STPWS];
T1_focusData_t          T1_SEC_NO_INIT_32 T1_focus[T1_CONT_NOF_FOCUS_MEASUREMENTS];
#   if defined T1_WAIT_RESUME
T1_taskData_t           T1_SEC_NO_INIT_32 T1_taskData[T1_NOF_TASKS_CORE0];
#   else /* ! defined T1_WAIT_RESUME */
T1_taskData_t           T1_SEC_NO_INIT_32 T1_taskData[1];
#   endif /* defined T1_WAIT_RESUME */
$secStrings{STOP}{NO_INIT_32}{-1}{0}
$secStrings{START}{CONST_16}{-1}{0}
T1_resultsIdx_t const   T1_SEC_CONST_16 T1_nofResults = T1_NOF_RESULTS_CORE0;
T1_tick_t       const   T1_SEC_CONST_16 T1_overhead     = (T1_tick_t)T1_NS_TO_TICKS( T1_OVERHEAD_CORE0_NS );
T1_tick_t       const   T1_SEC_CONST_16 T1_flexOverhead = (T1_tick_t)T1_NS_TO_TICKS( T1_FLEX_OVERHEAD_CORE0_NS );
T1_uint16_t     const   T1_SEC_CONST_16 T1_cpuLoadTxPeriod = T1_CPULOAD_TX_PERIOD_CORE0;
T1_uint16_t     const   T1_SEC_CONST_16 T1_startOfFrameEvent = T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE0, T1_BSF_EVENT_INFO_CORE0);
T1_anaCapa_t    const   T1_SEC_CONST_16 T1_defaultAnalysisCapacity = T1_CONT_ANALYSIS_CAPACITY_CORE0;
$secStrings{STOP}{CONST_16}{-1}{0}
#   if !defined T1_70618
$secStrings{START}{CONST_32}{-1}{1}
T1_longTime_t const     T1_SEC_CONST_32 T1_06960 = 0xFFFFFFFFuL;
$secStrings{STOP}{CONST_32}{-1}{1}
#   endif /* !defined T1_70618 */
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t   const      T1_SEC_CONST_8 T1_avgCPULoadSamples = T1_CPULOAD_SAMPLES_CORE0;
T1_taskIdx_t const      T1_SEC_CONST_8 T1_nofTasks      = $nofTasks[0]u;
T1_stpwIdx_t const      T1_SEC_CONST_8 T1_nofStpws      = $nofUserStopwatches[0]u + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS;
T1_stpwIdx_t const      T1_SEC_CONST_8 T1_nofUserStpws  = $nofUserStopwatches[0]u;
T1_csrnIdx_t const      T1_SEC_CONST_8 T1_nofCsrns      = $nofConstraints[0]u;
T1_uint8_t   const      T1_SEC_CONST_8 T1_nofPreemptions = T1_MAX_TASK_PREEMPTIONS_CORE0;
T1_uint8_t   const      T1_SEC_CONST_8 T1_cpuLoadThreshold = $CPULoadThresholds[0]u;
T1_taskIdx_t const      T1_SEC_CONST_8 T1_bgTaskIdx    = T1_BACKGROUND_TASK_IDX_CORE0;
#   if defined T1_CONT_DEFAULT_CONFIG_STOPWATCH
T1_stpwConfig_t         T1_SEC_CONST_8 T1_stpwConfig[$nofUserStopwatches[0]] =
{
EOT
        printf $fh ("    " . (join ",\n    ", (map { "T1_CONT_DEFAULT_CONFIG_STOPWATCH( ${_}u )" } ( 0 .. ($nofUserStopwatches[0]-1) ))) . "\n");
        print $fh <<EOT;
};
#   endif /* defined T1_CONT_DEFAULT_CONFIG_STOPWATCH */
$secStrings{STOP}{CONST_8}{-1}{0}
#   if defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT
$secStrings{START}{CONST_32}{-1}{1}
T1_csrnData_t const     T1_SEC_CONST_32 T1_csrnConfig[$nofConstraints[0]] =
{
EOT
        printf $fh ("    " . (join ",\n    ", (('T1_CONT_DEFAULT_CONFIG_CONSTRAINT') x $nofConstraints[0])) . "\n");
        print $fh <<EOT;
};
$secStrings{STOP}{CONST_32}{-1}{1}
#   endif /* defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT */
EOT
    }
    else
    {
        GenMultiCoreDataStructurePlusElements( $fh, '', $nofCores, 'T1_contScopeGlobals_t', 32, 'T1_contGlobals' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_stpwData_t', 32, 'T1_stpwData', 'T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX + T1_CONT_NOF_VRTL_STPWS' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_csrnData_t', 32, 'T1_csrnData', 'T1_NOF_CSRNS_COREXX' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_resultTime_t', 32, 'T1_resultBuffer', '((T1_NOF_RESULTS_COREXX + 0xFu) & ~0xFu) + 1u' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_taskStackElem_t', 32, 'T1_taskStack', 'T1_MAX_TASK_PREEMPTIONS_COREXX+T1_TASK_STACK_OVERRUNS' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_vStpwMapping_t', 32, 'T1_vStpw', '2*T1_CONT_NOF_VRTL_STPWS' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_focusData_t', 32, 'T1_focus', 'T1_CONT_NOF_FOCUS_MEASUREMENTS' );
        print $fh "#   if defined T1_WAIT_RESUME\n";
        Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_taskData_t', 32, 'T1_taskData', 'T1_NOF_TASKS_COREXX' );
        print $fh <<EOT;
#   else /* ! defined T1_WAIT_RESUME */
$secStrings{START}{CONST_32}{-1}{1}
T1_taskData_t     * const T1_SEC_CONST_32 T1_taskDataPC[1] = { T1_NULL };
$secStrings{STOP}{CONST_32}{-1}{1}
#   endif /* defined T1_WAIT_RESUME */
EOT

        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofResultsPC', 'T1_resultsIdx_t', 16, 'T1_NOF_RESULTS_COREXX' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_overheadPC', 'T1_tick_t', 16, '(T1_tick_t)T1_NS_TO_TICKS( T1_OVERHEAD_COREXX_NS )' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_flexOverheadPC', 'T1_tick_t', 16, '(T1_tick_t)T1_NS_TO_TICKS( T1_FLEX_OVERHEAD_COREXX_NS )' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_cpuLoadTxPeriodPC', 'T1_uint16_t', 16, 'T1_CPULOAD_TX_PERIOD_COREXX' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_startOfFrameEventPC', 'T1_uint16_t', 16, 'T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_COREXX, T1_BSF_EVENT_INFO_COREXX )' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_defaultAnalysisCapacityPC', 'T1_anaCapa_t', 16, 'T1_CONT_ANALYSIS_CAPACITY_COREXX' );

        print $fh "#   if !defined T1_70618\n";
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_38948', 'T1_longTime_t', 32, '0xFFFFFFFFuL' );
        print $fh "#   endif /* !defined T1_70618 */\n";

        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_avgCPULoadSamplesPC', 'T1_uint8_t', 8, 'T1_CPULOAD_SAMPLES_COREXX' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofTasksPC', 'T1_taskIdx_t', 8, 'T1_NOF_TASKS_COREXX' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofStpwsPC', 'T1_stpwIdx_t', 8, 'T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX + T1_CONT_NOF_VRTL_STPWS' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofUserStpwsPC', 'T1_stpwIdx_t', 8, \@nofUserStopwatches );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofCsrnsPC', 'T1_csrnIdx_t', 8, \@nofConstraints );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofPreemptionsPC', 'T1_uint8_t', 8, 'T1_MAX_TASK_PREEMPTIONS_COREXX' );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_cpuLoadThresholdPC', 'T1_uint8_t', 8, \@CPULoadThresholds );
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_bgTaskIdxPC', 'T1_taskIdx_t', 8, 'T1_BACKGROUND_TASK_IDX_COREXX' );
        print $fh <<EOT;
#   if defined T1_CONT_DEFAULT_CONFIG_STOPWATCH
$secStrings{START}{CONST_8}{-1}{1}
EOT
        foreach my $coreId ( 0 .. ($nofCores-1) )
        {
            print $fh <<EOT;
T1_stpwConfig_t         T1_SEC_CONST_8 T1_stpwConfig${coreId}[$nofUserStopwatches[$coreId]] =
{
EOT
            printf $fh ("    " . (join ",\n    ", (map { "T1_CONT_DEFAULT_CONFIG_STOPWATCH( ${_}u )" } ( 0 .. ($nofUserStopwatches[$coreId]-1) ))) . "\n");
            print $fh "};\n";
        }
        Sec( $fh, '    ', -1, 'STOP', "CONST_8" );
        GenMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_stpwConfigPC', 'T1_stpwConfig_t *', 32, 'T1_stpwConfigXX' );
        print $fh <<EOT;
#   endif /* defined T1_CONT_DEFAULT_CONFIG_STOPWATCH */
#   if defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT
$secStrings{START}{CONST_32}{-1}{1}
EOT
        foreach my $coreId ( 0 .. ($nofCores-1) )
        {
            print $fh <<EOT;
T1_csrnData_t const     T1_SEC_CONST_32 T1_csrnConfig${coreId}[$nofConstraints[$coreId]] =
{
EOT
            printf $fh ("    " . (join ",\n    ", (('T1_CONT_DEFAULT_CONFIG_CONSTRAINT') x $nofConstraints[$coreId])) . "\n");
            print $fh "};\n";
        }
        Sec( $fh, '    ', -1, 'STOP', "CONST_32" );
        GenMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_csrnConfigPC', 'T1_csrnData_t const *', 32, 'T1_csrnConfigXX' );
        print $fh <<EOT;
#   endif /* defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT */
EOT
    }

    print $fh <<EOT;

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_CONT */
EOT

######################################################################################
### T1.delay                                                                       ###
######################################################################################
    print $fh <<EOT;

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY
EOT

    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_nofDelays = T1_NOF_DELAYS_CORE0;
$secStrings{STOP}{CONST_8}{-1}{0}
$secStrings{START}{NO_INIT_32}{-1}{0}
T1_delay_t              T1_SEC_NO_INIT_32 T1_delays[T1_NOF_DELAYS_CORE0];
T1_delayGlobals_t       T1_SEC_NO_INIT_32 T1_delayGlobals;
$secStrings{STOP}{NO_INIT_32}{-1}{0}
EOT
    }
    else
    {
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofDelaysPC', 'T1_uint8_t', 8, 'T1_NOF_DELAYS_COREXX' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_delay_t', 32, 'T1_delays', 'T1_NOF_DELAYS_COREXX' );
        GenMultiCoreDataStructurePlusElements( $fh, '', $nofCores, 'T1_delayGlobals_t', 32, 'T1_delayGlobals' );
    }

    print $fh <<EOT;

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */
EOT

######################################################################################
### T1.flex                                                                        ###
######################################################################################

    print $fh <<EOT;

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX

$secStrings{START}{NO_INIT_32}{-1}{0}
T1_uint32_t             T1_SEC_NO_INIT_32 T1_swdStart;
$secStrings{STOP}{NO_INIT_32}{-1}{0}

EOT

    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_nofAddrs = T1_NOF_FLEX_ADDRS_CORE0;
$secStrings{STOP}{CONST_8}{-1}{0}
$secStrings{START}{NO_INIT_32}{-1}{0}
T1_flexAddr_t           T1_SEC_NO_INIT_32 T1_addrs[T1_NOF_FLEX_ADDRS_CORE0];
T1_flexGlobals_t        T1_SEC_NO_INIT_32 T1_flexGlobals;
$secStrings{STOP}{NO_INIT_32}{-1}{0}
EOT
    }
    else
    {
        print $fh <<EOT;
EOT

        print $fh <<EOT;
#   if defined T1_TRICORE
EOT
        Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_flexAddr_t', '32_DCX', 'T1_dcx', 4 );
        GenMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_OuterExceptionHandlerPC', 'T1_pVoidVoid_t', 32, 'T1_OuterExceptionHandlerCoreXX' );
        print $fh <<EOT;
#   endif /* defined T1_TRICORE */
EOT

        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_nofAddrsPC', 'T1_uint8_t', 8, 'T1_NOF_FLEX_ADDRS_COREXX' );
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_flexAddr_t', 32, 'T1_addrs', 'T1_NOF_FLEX_ADDRS_COREXX' );
        GenMultiCoreDataStructurePlusElements( $fh, '', $nofCores, 'T1_flexGlobals_t', 32, 'T1_flexGlobals' );
    }

    print $fh <<EOT;

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX */
EOT

######################################################################################
### T1.scope                                                                       ###
######################################################################################

    print $fh <<EOT;

#if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE

#   if !defined T1_SYNC_TIMER_WIDTH_BITS
EOT
    if( 1 < $nofCores )
    {
        print $fh "#       error T1_SYNC_TIMER_WIDTH_BITS must be defined\n";
    }
    print $fh <<EOT;
#   endif /* !defined T1_SYNC_TIMER_WIDTH_BITS */
EOT

    if( $nofCores <= 0 )
    {
        print $fh <<EOT;
#   if !defined T1_TRACEBUFFER_ENTRIES_CORE0
#       if defined T1_EXTERNAL_TRACEBUFFER
#           define T1_TRACEBUFFER_ENTRIES_CORE0
#       else /* !defined T1_EXTERNAL_TRACEBUFFER */
#           error T1_TRACEBUFFER_ENTRIES_CORE0 not defined
#       endif /* defined T1_EXTERNAL_TRACEBUFFER */
#   endif /* T1_TRACEBUFFER_ENTRIES_CORE0 */
#   if !defined T1_TRACE_TIMER_COUNTS_DOWN_CORE0
#       error T1_TRACE_TIMER_COUNTS_DOWN_CORE0 not defined
#   endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE0 */
$secStrings{START}{NO_INIT_32_TRACEBUFFER}{-1}{0}
#   if defined T1_EXTERNAL_TRACEBUFFER
T1_EXTERN
#   endif /* !defined T1_EXTERNAL_TRACEBUFFER */
T1_traceEntry_t T1_FAR  T1_SEC_NO_INIT_32_TRACEBUFFER T1_traceBuffer[T1_TRACEBUFFER_ENTRIES_CORE0];
$secStrings{STOP}{NO_INIT_32_TRACEBUFFER}{-1}{0}
#   if !defined T1_EXTERNAL_TRACEBUFFER
$secStrings{START}{CONST_16}{-1}{1}
T1_uint16_t const       T1_SEC_CONST_16 T1_bufferSize = T1_TRACEBUFFER_ENTRIES_CORE0;
$secStrings{STOP}{CONST_16}{-1}{1}
#   endif /* !defined T1_EXTERNAL_TRACEBUFFER */
$secStrings{START}{NO_INIT_32}{-1}{0}
T1_scopeGlobals_t       T1_SEC_NO_INIT_32 T1_scopeGlobals;
$secStrings{STOP}{NO_INIT_32}{-1}{0}
EOT
    }
    else
    {
        foreach my $coreId ( 0 .. ($nofCores-1) )
        {
            print $fh <<EOT;
#   if !defined T1_TRACEBUFFER_ENTRIES_CORE$coreId
#       if defined T1_EXTERNAL_TRACEBUFFER
#           define T1_TRACEBUFFER_ENTRIES_CORE$coreId
#       else /* !defined T1_EXTERNAL_TRACEBUFFER */
#           error T1_TRACEBUFFER_ENTRIES_CORE$coreId not defined
#       endif /* defined T1_EXTERNAL_TRACEBUFFER */
#   endif /* T1_TRACEBUFFER_ENTRIES_CORE$coreId */
#   if !defined T1_TRACE_TIMER_COUNTS_DOWN_CORE$coreId
#       error T1_TRACE_TIMER_COUNTS_DOWN_CORE$coreId not defined
#   endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE$coreId */
EOT
        }
        Gen2DimensionalMultiCoreDataStructure( $fh, '', $nofCores, 'T1_traceEntry_t T1_FAR', '32_TRACEBUFFER', 'T1_traceBuffer', 'T1_TRACEBUFFER_ENTRIES_COREXX' );
        print $fh <<EOT;
$secStrings{START}{CONST_32}{-1}{0}
T1_traceIndirect_t const T1_SEC_CONST_32 T1_traceIndirect =
{
#if defined T1_CONT_REMOTE
    T1_TraceEventNoSuspTimeRC__,
    T1_TraceSyncNoSuspRC__
#else /* !defined T1_CONT_REMOTE */
    T1_TraceEventNoSuspTime__,
    T1_TraceSyncNoSusp__
#endif /* defined T1_CONT_REMOTE */
};
$secStrings{STOP}{CONST_32}{-1}{0}
#   if !defined T1_EXTERNAL_TRACEBUFFER
EOT
        GenMultiCoreDataStructure( $fh, '    ', $nofCores, 'T1_bufferSizePC', 'T1_uint16_t', 16, 'T1_TRACEBUFFER_ENTRIES_COREXX' );
        print $fh <<EOT;
#   endif /* !defined T1_EXTERNAL_TRACEBUFFER */
EOT
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_syncTimerIsTraceTimerPC', 'T1_bool_t', 8, 'T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX' );
        print $fh <<EOT;
#   if defined T1_DISABLE_T1_CONT
EOT
        GenMultiCoreDataStructurePlusElements( $fh, '', $nofCores, 'T1_scopeGlobals_t', 32, 'T1_scopeGlobals' );
        print $fh <<EOT;
#   else /* ! defined T1_DISABLE_T1_CONT */
EOT
        GenMultiCoreDataStructure( $fh, '', $nofCores, 'T1_scopeGlobalsPC', 'T1_scopeGlobals_t *', 32, '&(T1_contGlobalsXX.scopeGlobals)' );
        print $fh <<EOT;
#   endif /* defined T1_DISABLE_T1_CONT */
#   if defined T1_CROSS_CORE_ACT
$secStrings{START}{NO_INIT_32}{-1}{1}
T1_uint32_t T1_SEC_NO_INIT_32 T1_taskAct[T1_MAX_NOF_TASKS];
$secStrings{STOP}{NO_INIT_32}{-1}{1}
#   endif /* defined T1_CROSS_CORE_ACT */
EOT
    }

    print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_syncTimerWidthBits = T1_SYNC_TIMER_WIDTH_BITS;
$secStrings{STOP}{CONST_8}{-1}{0}
EOT

    print $fh <<EOT;

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE */
EOT

}

######################################################################################
# sub GenT1ConfigH prints the generated segment of T1_config.h (virtually all of it)
######################################################################################

# Input:
#   File handle for output
#   Configuration database as a Perl hash
sub GenT1ConfigH($$)
{
    my $fh = shift;
    my $configRef = shift;
    my %config = %$configRef;

    if( 0 < $config{'nofCores'} )
    {
        printf $fh "#define %-45s (%s)\n", "T1_NOF_CORES", addU( $config{'nofCores'} );
    }

    printf $fh "#define %-45s (%s)\n", "T1_SID", addU( $config{'sid'} );
    if( '' eq $config{'bidHeader'} ) # no BID-header specified. write BID into Config_H
    {
        printf $fh $config{'t1BidHDefs'};
    }

    if( $config{'useSameConnectionForAllSystems'} eq 'true' )
    {
        my $maxRxFrameBytes = 8;
        my $maxTxFrameBytes = 8;

        if( $config{'canHardware'} eq 'U2C' or $config{'canHardware'} eq 'VECTOR' or $config{'canFDHardware'} eq 'VECTOR' )
        {
            printf $fh "#define %-45s (%s)\n", "T1_CAN_PC_TO_ECU_ID", addU( $config{'canTxID'}[0] );
            printf $fh "#define %-45s (%s)\n", "T1_CAN_ECU_TO_PC_ID", addU( $config{'canRxID'}[0] );
        }

        if ($config{'connectionType'}[0] eq 'Diagnosis' )
        {
            if( $config{'ethMaxTxDataSize'}[0] != 0 )
            {
                die "Ethernet and Diagnosis usage not supported. Remove parameter -ethMaxTxDataSize or -connectionType=Diagnosis from T1_Cfg.inv";
            }
            $maxRxFrameBytes = $config{'diagMaxTxDataSize'}[0];
        }
        else# pure T1 connection
        {
            if( $config{'canFDMaxTxDataSize'}[0] != 0 )
            {
                if( $config{'ethMaxTxDataSize'}[0] != 0 )
                {
                    die "Parameters -ethMaxTxDataSize and -canFDMaxTxDataSize set, remove the unused one from T1_Cfg.inv";
                }
                $maxRxFrameBytes = $config{'canFDMaxTxDataSize'}[0];
            }
            elsif( $config{'ethMaxTxDataSize'}[0] != 0 )
            {
                $maxRxFrameBytes = $config{'ethMaxTxDataSize'}[0];
            }
        }

        if ($config{'connectionType'}[0] eq 'Diagnosis' )
        {
            if( $config{'ethMaxRxDataSize'}[0] != 0 )
            {
                die "Ethernet and Diagnosis usage not supported. Remove parameter -ethMaxRxDataSize or -connectionType=Diagnosis from T1_Cfg.inv";
            }
            $maxTxFrameBytes = $config{'diagMaxRxDataSize'}[0];
        }
        else# pure T1 connection
        {
            if( $config{'canFDMaxRxDataSize'}[0] != 0 )
            {
                if( $config{'ethMaxRxDataSize'}[0] != 0 )
                {
                    die "Parameters -ethMaxRxDataSize and -canFDMaxRxDataSize set, remove the unused one from T1_Cfg.inv";
                }
                $maxTxFrameBytes = $config{'canFDMaxRxDataSize'}[0];
            }
            elsif( $config{'ethMaxRxDataSize'}[0] != 0 )
            {
                $maxTxFrameBytes = $config{'ethMaxRxDataSize'}[0];
            }
        }
        printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE", addU( $maxRxFrameBytes );
        printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE", addU( $maxTxFrameBytes );
    }

    printf $fh "#define %-45s (%s)\n", "T1_STATIC_RUNNABLE_ID", addU( $config{'staticRunnableID'} )     if '' ne $config{'staticRunnableID'};
    printf $fh "#define %-45s (%s)\n", "T1_TIMEOUT_RX", addU( $config{'timeoutRx'} )                    if '' ne $config{'timeoutRx'};
    printf $fh "#define %-45s (%s)\n", "T1_TIMEOUT_TX", addU( $config{'timeoutTx'} )                    if '' ne $config{'timeoutTx'};
    printf $fh "#define %-45s (%s)\n", "T1_TIMEOUT_RESPONSE", addU( $config{'timeoutResponse'} )        if '' ne $config{'timeoutResponse'};
    printf $fh "#define %-45s (%s)\n", "T1_INIT_FEATURE_MASK", addUL( $config{'initFeatureMask'} )      if '' ne $config{'initFeatureMask'};
    printf $fh "#define %-45s (*(T1_uint32_t volatile *)%s)\n", "T1_GET_SYNC_TIME( )", addUL( $config{'pSyncTimer'} ) unless '0' eq $config{'pSyncTimer'};
    printf $fh "#define %-45s (%s)\n", "T1_SYNC_TIMER_WIDTH_BITS", addU( $config{'syncTimeBitLength'} );
    # Add 'f' suffix to float literals for MISRA conformance and to match T1 headers
    my $syncTimerTickDurationMisraNs = $config{'syncTimerTickDurationNs'};
    $syncTimerTickDurationMisraNs =~ s/(\d*\.\d*)/$1f/g;
    printf $fh "#define %-45s (%s)\n", "T1_SYNC_TIMER_DURATION_NS", $syncTimerTickDurationMisraNs       if '' ne $syncTimerTickDurationMisraNs;
    printf $fh "#define %-45s (1)\n", "T1_CONT_REMOTE"                                                  if 0 < scalar keys %{$config{'contRunsOnCore'}} and 1 < $config{'nofCores'};
    printf $fh "#define %-45s (%s)\n", "T1_CONT_NOF_FOCUS_MEASUREMENTS", addU( $config{'numberOfFocusMeasurements'} );

    my $maxNofTasks = 0;
    my $lastCoreIndex = $config{'nofCores'} - 1;
    $lastCoreIndex = 0 if $lastCoreIndex < 0;
    foreach my $coreId ( 0 .. $lastCoreIndex )
    {
        $maxNofTasks = $config{'numberOfTasks'}[$coreId] if $maxNofTasks < $config{'numberOfTasks'}[$coreId];
    }
    printf $fh "#define %-45s (%s)\n", "T1_MAX_NOF_TASKS", addU( $maxNofTasks );

    # If all cores use the same, memory-mapped timer, generate the obvious
    # T1_GET_TRACE_TIME definition.
    my $allCoresTraceTimerAddr;
    $allCoresTraceTimerAddr = $config{'pTimer'}[0] unless not defined $config{'pTimer'}[0] or $config{'pTimer'}[0] eq '0' or $config{'pTimer'}[0] eq '1';
    my $allCoresTraceTimerCountsDown;
    $allCoresTraceTimerCountsDown = $config{'traceTimerDownCounting'}[0] eq 'true';
    foreach my $sysNo ( 1 .. $lastCoreIndex )
    {
        last unless $allCoresTraceTimerAddr;
        last unless defined $allCoresTraceTimerCountsDown;
        undef $allCoresTraceTimerAddr unless $allCoresTraceTimerAddr eq $config{'pTimer'}[$sysNo];
        undef $allCoresTraceTimerCountsDown unless $allCoresTraceTimerCountsDown == ($config{'traceTimerDownCounting'}[$sysNo] eq 'true');
    }
    printf $fh "#define %-45s (%s%s)\n", 'T1_GET_TRACE_TIME( )', '(T1_tickUint_t)-' x $allCoresTraceTimerCountsDown, '*(T1_tickUint_t volatile *)T1_PTIMER_CORE0' if $allCoresTraceTimerAddr and defined $allCoresTraceTimerCountsDown;

    foreach my $sysNo ( 0 .. $lastCoreIndex )
    {
        my $BgTask = '';
        my $coreSuffix = '';

        $coreSuffix = "_CORE$sysNo";

        # perform some value checks:
        if( $config{'cpuLoadAvgSamples'}[$sysNo] && $config{'cpuLoadTxPeriod'}[$sysNo] )
        {
            die "error: cpuLoadAvgSamples must either be 1 or equal to cpuLoadTxPeriod!"
                unless $config{'cpuLoadAvgSamples'}[$sysNo] == 1 || $config{'cpuLoadAvgSamples'}[$sysNo] == $config{'cpuLoadTxPeriod'}[$sysNo];
        }
        if( $config{'nofFlexAddrs'}[$sysNo] < $config{'nofFlexStopwatches'}[$sysNo] )
        {
            die "error: nofFlexStopwatches must be at most nofFlexAddrs";
        }

        print $fh "\n/* Core-specific configuration for core $sysNo */\n";

        if( $config{'osBasicSchedFrameEventId'}[$sysNo] eq "T1_USEREVENT" )
        {
            printf $fh "#define %-45s (%s)\n", "T1_BSF_EVENT_ID$coreSuffix", addU( $config{'osBasicSchedFrameId'}[$sysNo] );
            printf $fh "#define %-45s (%s)\n", "T1_BSF_EVENT_INFO$coreSuffix", "0u"; # event info must be statically 0
        }
        else # T1_ACTIVATION, T1_START, T1_STOP
        {
            printf $fh "#define %-45s (%s)\n", "T1_BSF_EVENT_ID$coreSuffix", addU( $config{'osBasicSchedFrameEventId'}[$sysNo] );
            if( $config{'osBasicSchedFrameName'}[$sysNo ])
            {
                my $taskIdMacro = "T1_$config{'osBasicSchedFrameName'}[$sysNo]_ID";
                printf $fh "#define %-45s (%s)\n", "T1_BSF_EVENT_INFO$coreSuffix", $taskIdMacro;
            }
            else # only ID is specified
            {
                if( $config{'osBasicSchedFrameId'}[$sysNo] ) # leave out if not specified
                {
                    printf $fh "#define %-45s (%s)\n", "T1_BSF_EVENT_INFO$coreSuffix", addU( $config{'osBasicSchedFrameId'}[$sysNo] );
                }
            }
        }

        if( $config{'osBackgroundTaskName'}[$sysNo] )
        {
            $BgTask = "T1_$config{'osBackgroundTaskName'}[$sysNo]_ID";
        }
        elsif( defined( $config{'osBackgroundTaskId'}[$sysNo] ) )
        {
             $BgTask = $config{'osBackgroundTaskId'}[$sysNo];
        }
        else
        {
            $BgTask = "T1_INVALID_TASK_ID";
        }
        if( $config{'useSameConnectionForAllSystems'} eq 'false' )
        {
            my $maxRxFrameBytes = 8;
            my $maxTxFrameBytes = 8;

            printf $fh "#define %-45s (%s)\n", "T1_CAN_PC_TO_ECU_ID$coreSuffix", addU( $config{'canTxID'}[$sysNo] );
            printf $fh "#define %-45s (%s)\n", "T1_CAN_ECU_TO_PC_ID$coreSuffix", addU( $config{'canRxID'}[$sysNo] );

            if ($config{'connectionType'}[$sysNo] eq 'Diagnosis' )
            {
                if( $config{'ethMaxTxDataSize'}[$sysNo] != 0 )
                {
                    die "Ethernet and Diagnosis usage not supported. Remove parameter -ethMaxTxDataSize or -connectionType=Diagnosis from T1_Cfg.inv";
                }
                $maxRxFrameBytes = $config{'diagMaxTxDataSize'}[$sysNo];
                printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE$coreSuffix", addU( $config{'diagMaxTxDataSize'}[$sysNo] );
            }
            else# pure T1 connection
            {
                if( $config{'canFDMaxTxDataSize'}[$sysNo] != 0 )
                {
                    if( $config{'ethMaxTxDataSize'}[$sysNo] != 0 )
                    {
                        die "Parameters -ethMaxTxDataSize and -canFDMaxTxDataSize set, remove the unused one from T1_Cfg.inv";
                    }
                    $maxRxFrameBytes = $config{'canFDMaxTxDataSize'}[$sysNo];
                    printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE$coreSuffix", addU( $config{'canFDMaxTxDataSize'}[$sysNo] );
                }
                elsif( $config{'ethMaxTxDataSize'}[$sysNo] != 0 )
                {
                    $maxRxFrameBytes = $config{'ethMaxTxDataSize'}[$sysNo];
                    printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE$coreSuffix", addU( $config{'ethMaxTxDataSize'}[$sysNo] );
                }
            }

            if ($config{'connectionType'}[$sysNo] eq 'Diagnosis' )
            {
                if( $config{'ethMaxRxDataSize'}[$sysNo] != 0 )
                {
                    die "Ethernet and Diagnosis usage not supported. Remove parameter -ethMaxRxDataSize or -connectionType=Diagnosis from T1_Cfg.inv";
                }
                $maxTxFrameBytes = $config{'diagMaxRxDataSize'}[$sysNo];
                printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE$coreSuffix", addU( $config{'diagMaxRxDataSize'}[$sysNo] );
            }
            else# pure T1 connection
            {
                if( $config{'canFDMaxRxDataSize'}[$sysNo] != 0 )
                {
                    if( $config{'ethMaxRxDataSize'}[$sysNo] != 0 )
                    {
                        die "Parameters -ethMaxRxDataSize and -canFDMaxRxDataSize set, remove the unused one from T1_Cfg.inv";
                    }
                    $maxTxFrameBytes = $config{'canFDMaxRxDataSize'}[$sysNo];
                    printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE$coreSuffix", addU( $config{'canFDMaxRxDataSize'}[$sysNo] );
                }
                elsif( $config{'ethMaxRxDataSize'}[$sysNo] != 0 )
                {
                    $maxTxFrameBytes = $config{'ethMaxRxDataSize'}[$sysNo];
                    printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE$coreSuffix", addU( $config{'ethMaxRxDataSize'}[$sysNo] );
                }
            }
            printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE$coreSuffix", addU( $maxRxFrameBytes );
            printf $fh "#define %-45s (%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE$coreSuffix", addU( $maxTxFrameBytes );
        }
        printf $fh "#define %-45s (%s)\n", "T1_BACKGROUND_TASK_ID$coreSuffix", $BgTask;
        # Add 'f' suffix to float literals for MISRA conformance and to match T1 headers
        my $tickDurationMisraNs = $config{'tickDurationNs'}[$sysNo];
        $tickDurationMisraNs =~ s/(\d*\.\d*)/$1f/g;
        printf $fh "#define %-45s (%s)\n", "T1_TICK_DURATION${coreSuffix}_NS", $tickDurationMisraNs;
        printf $fh "#define %-45s (%s)\n", "T1_OVERHEAD${coreSuffix}_NS", $config{'t1ScopeOverheadNs'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_FLEX_OVERHEAD${coreSuffix}_NS", $config{'t1FlexOverheadNs'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_CPULOAD_CALLBACK$coreSuffix", $config{'cpuLoadCallback'}[$sysNo];

        printf $fh "#define %-45s (%s)\n", "T1_CPULOAD_THRESHOLD_PERCENT$coreSuffix", $config{'cpuLoadThreshold'}[$sysNo]       if $config{'cpuLoadThreshold'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_TRACEBUFFER_ENTRIES$coreSuffix", addU( $config{'traceBufferEntries'}[$sysNo] )   if $config{'traceBufferEntries'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_NOF_CSRNS$coreSuffix", addU( $config{'numberOfConstraints'}[$sysNo] )            if $config{'numberOfConstraints'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_NOF_USER_STPWS$coreSuffix", addU( $config{'numberOfUserStpws'}[$sysNo] )         if 0 < $config{'numberOfUserStpws'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_NOF_FLEX_STPWS$coreSuffix", addU( $config{'nofFlexStopwatches'}[$sysNo] )        if $config{'nofFlexStopwatches'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_NOF_STPWS$coreSuffix", "T1_NOF_USER_STPWS${coreSuffix} + T1_NOF_FLEX_STPWS$coreSuffix";
        printf $fh "#define %-45s (%s)\n", "T1_NOF_FLEX_ADDRS$coreSuffix", addU( $config{'nofFlexAddrs'}[$sysNo] )              if $config{'nofFlexAddrs'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_PTIMER$coreSuffix", addUL( $config{'pTimer'}[$sysNo] )                           if $config{'pTimer'}[$sysNo];

        my $traceTimerIsSyncTimer = 0;
        $traceTimerIsSyncTimer = 1 if $config{'traceTimerIsSyncTimer'}[$sysNo] eq 'true';
        printf $fh "#define %-45s (%s)\n", "T1_TRACE_TIMER_IS_SYNC_TIMER$coreSuffix", $traceTimerIsSyncTimer;

        my $traceTimerDownCounting = 'T1_FALSE';
        $traceTimerDownCounting = 'T1_TRUE' if $config{'traceTimerDownCounting'}[$sysNo] eq 'true';
        printf $fh "#define %-45s (%s)\n", "T1_TRACE_TIMER_COUNTS_DOWN$coreSuffix", $traceTimerDownCounting;

        printf $fh "#define %-45s (%s)\n", "T1_TRACE_TIMER_BIT_LENGTH$coreSuffix", addU( $config{'traceTimerBitLength'}[$sysNo] );

        printf $fh "#define %-45s (%s)\n", "T1_CPULOAD_TX_PERIOD$coreSuffix", addU( $config{'cpuLoadTxPeriod'}[$sysNo] )        if $config{'cpuLoadTxPeriod'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_CPULOAD_SAMPLES$coreSuffix", addU( $config{'cpuLoadAvgSamples'}[$sysNo] )        if $config{'cpuLoadAvgSamples'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_CONT_ANALYSIS_CAPACITY$coreSuffix", addU( $config{'analysisCapacity'}[$sysNo] )  if $config{'analysisCapacity'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_NOF_DELAYS$coreSuffix", addU( $config{'nofDelays'}[$sysNo] )                     if $config{'nofDelays'}[$sysNo];
        printf $fh "#define %-45s (%s)\n", "T1_CET_EVT_CHAIN_TO_IDX$coreSuffix( id_ )", " T1_NOF_STPWS$coreSuffix + ( ( 3u < (id_) ) ? T1_invalidCETeventChainIdx : ( 2u*(id_) ) ) ";
        printf $fh "#define %-45s (%s)\n", "T1_GET_EVT_CHAIN_TO_IDX$coreSuffix( id_ )", " T1_NOF_STPWS$coreSuffix + ( ( 3u < (id_) ) ? ( (id_) + 4u ) : ( 2u*(id_) + 1u ) ) ";
    }

    print $fh <<EOT;


#if ! defined T1_CORE_ID_TO_SCOPE_GLOBALS
#   if defined T1_DISABLE_T1_CONT
#       if ! defined T1_NOF_CORES || defined T1_CLONE
#           define T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ) (&T1_scopeGlobals)
#       else /* defined T1_NOF_CORES && ! defined T1_CLONE */
EOT
    if( 1 == $config{'nofCores'} )
    {
        printf $fh "#       define %-38s (%s)\n", 'T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ )', '&T1_scopeGlobals0';
    }
    else
    {
        printf $fh "/* This default version can be evaluated at compile time when passed a literal input */\n";
        print $fh <<EOT;
#           if 2 < T1_NOF_CORES && defined __GNUC__ /* use switch statement */
#               define T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ) ({            \\
    T1_scopeGlobals_t * pScopeGlobals_;                                     \\
    switch( coreId_ )                                                       \\
    {                                                                       \\
EOT
        foreach my $sysNo (0 .. ($lastCoreIndex-1) )
        {
            printf $fh "    case %-7spScopeGlobals_ = &T1_scopeGlobals%-3s break;                 \\\n", "$sysNo:", "$sysNo;";
        }
        printf $fh "    default:    pScopeGlobals_ = &T1_scopeGlobals%-3s break;                 \\\n", "$lastCoreIndex;";
        print $fh <<EOT;
    }                                                                       \\
    pScopeGlobals_;                                                         \\
})
#           else /* NOTE 'coreId_' can be evaluated more than once with >2 cores */
#               define T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ) (             \\
EOT
        foreach my $sysNo (0 .. ($lastCoreIndex-1) )
        {
            printf $fh "    (%2u == (coreId_) ) ? &T1_scopeGlobals%-2u :                               \\\n", $sysNo, $sysNo;
        }
        printf $fh "                         &T1_scopeGlobals%-2u                                 \\\n", $lastCoreIndex;
        print $fh <<EOT;
)
#           endif /* switch or ?: */
EOT
    }
    print $fh <<EOT;
#       endif /* ! defined T1_NOF_CORES || defined T1_CLONE */
#   else /* ! defined T1_DISABLE_T1_CONT */
#       if ! defined T1_NOF_CORES || defined T1_CLONE
#           define T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ) (&(T1_contScopeGlobals.scopeGlobals))
#       else /* defined T1_NOF_CORES && ! defined T1_CLONE */
EOT
    if( 1 == $config{'nofCores'} )
    {
        printf $fh "#       define %-38s (%s)\n", 'T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ )', '&(T1_contGlobals0.scopeGlobals)';
    }
    else
    {
        printf $fh "/* This default version can be evaluated at compile time when passed a literal input */\n";
        print $fh <<EOT;
#           if 2 < T1_NOF_CORES && defined __GNUC__ /* use switch statement */
#               define T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ) ({            \\
    T1_scopeGlobals_t * pScopeGlobals_;                                     \\
    switch( coreId_ )                                                       \\
    {                                                                       \\
EOT
        foreach my $sysNo (0 .. ($lastCoreIndex-1) )
        {
            printf $fh "    case %-7spScopeGlobals_ = &(T1_contGlobals%-2u.scopeGlobals); break;   \\\n", "$sysNo:", $sysNo;
        }
        printf $fh "    default:    pScopeGlobals_ = &(T1_contGlobals%-2u.scopeGlobals); break;   \\\n", $lastCoreIndex;
        print $fh <<EOT;
    }                                                                       \\
    pScopeGlobals_;                                                         \\
})
#           else /* NOTE 'coreId_' can be evaluated more than once with >2 cores */
#               define T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ) (             \\
EOT
        foreach my $sysNo (0 .. ($lastCoreIndex-1) )
        {
            printf $fh "    (%2u == (coreId_) ) ? &(T1_contGlobals%-2u.scopeGlobals) :                 \\\n", $sysNo, $sysNo;
        }
        printf $fh "                         &(T1_contGlobals%-2u.scopeGlobals)                   \\\n", $lastCoreIndex;
        print $fh <<EOT;
)
#           endif /* switch or ?: */
EOT
    }
    print $fh <<EOT;
#       endif /* ! defined T1_NOF_CORES || defined T1_CLONE */
#   endif /* defined T1_DISABLE_T1_CONT */
#endif /* ! defined T1_CORE_ID_TO_SCOPE_GLOBALS */

#if ! defined T1_CONT_RC_UNMAP
EOT
    if( 1 == $config{'nofCores'} || 0 == keys %{$config{'contRunsOnCore'}} )
    {
        printf $fh "#   define %-42s (%s)\n", 'T1_CONT_RC_UNMAP( coreId_ )', 'coreId_';
    }
    else
    {
        my $oneCoreId = 0;
        $oneCoreId = $config{'contRunsOnCore'}{0} if exists $config{'contRunsOnCore'}{0};
        # Fill in the "blanks" in %{$config{'contRunsOnCore'}} to simplify the following code
        foreach my $sysNo ( 0 .. ($config{'nofCores'}-1) )
        {
            $config{'contRunsOnCore'}{$sysNo} = $sysNo unless exists $config{'contRunsOnCore'}{$sysNo};
            $oneCoreId = -1 if $config{'contRunsOnCore'}{$sysNo} != $oneCoreId;
        }
        if( -1 != $oneCoreId )
        {
            # All T1.cont background handlers run on the same core
            printf $fh "#   define %-42s (%uu)\n", 'T1_CONT_RC_UNMAP( coreId_ )', $oneCoreId;
        }
        else
        {
            if( 2 < $config{'nofCores'} )
            {
                print $fh <<EOT;
#       define T1_DEFN_CONT_UNMAP_CORE_ID                                           \\
T1_INLINE T1_uint8Least_t T1_CODE T1_ContRcUnmapCoreId( T1_uint8Least_t coreId )    \\
{                                                                                   \\
    switch( coreId )                                                                \\
    {                                                                               \\
EOT
                printf $fh "    default : return %-63s\\\n", addU( $config{'contRunsOnCore'}{0} . ';' );
                foreach my $sysNo ( 1 .. $lastCoreIndex )
                {
                    printf $fh "    case %3s: return %-63s\\\n", addU( $sysNo ), addU( $config{'contRunsOnCore'}{$sysNo} . ';' );
                }
                print $fh <<EOT;
    }                                                                               \\
}
EOT
            }
            printf $fh "#   define %-42s ", 'T1_CONT_RC_UNMAP( coreId_ )';
            if( 2 == $config{'nofCores'} )
            {
                print $fh "( (0 == (coreId_)) ? $config{'contRunsOnCore'}{0}u : $config{'contRunsOnCore'}{1}u )\n";
            }
            else
            {
                print $fh "( T1_ContRcUnmapCoreId( coreId_ ) )\n";
            }
        }
    }
    print $fh <<EOT;
#endif /* ! defined T1_CONT_RC_UNMAP */
EOT

}

1;
