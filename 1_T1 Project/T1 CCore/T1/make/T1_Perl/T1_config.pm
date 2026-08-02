######################################################################################
#
#   File:           T1_config.pm
#
#   Description:    Generate T1 config datastructures
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

package T1_config;
require Exporter;
our @ISA = ("Exporter");
our @EXPORT = qw(
    GenT1ConfigC
    GenT1ConfigBuffC
    GenT1ConfigH
    GenT1ConfigHUserSw
    GenT1ConfigHAF
    GenT1ConfigHDL
    GenT1ConfigHUE
    FormatConfigMacro
    FormatDocu
    EqualF
    isT1HostSwVersionAllowed
);

use strict;
use warnings;
use POSIX qw(ceil);

use constant DEBUG => 0;    # Change to 1 to enable debug logging information

######################################################################################
# global variables used for documentation in generated files.
######################################################################################

my %macroDocuTextList = (
    T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER =>   undef,
    T1_ANY_TRACE_TIMER_IS_SYNC_TIMER =>     undef,
    T1_BACKGROUND_TASK_ID_COREXX =>         'Specifies the name of the background task for system XX so that it can be excluded from the T1.cont and T1.scope CPU load calculation.',
    T1_BSF_EVENT_ID_COREXX =>               "Specifies the event ID which starts the Basic Scheduling Frame (BSF) for system XX.\nAllowed values are T1_ACTIVATION and T1_START or the ID of an user event (0x20-0x3F)",
    T1_BSF_EVENT_INFO_COREXX =>             "ID of the task for the Basic Scheduling Frame (BSF) event for system XX.\nThe selected task or user event must be traced on this core.\nHas to be set to '0' if a user event is used to define the BSF.",
    T1_CAN_ECU_TO_PC_ID =>                  'Defines the CAN ID for messages from the target to the host.',
    T1_CAN_PC_TO_ECU_ID =>                  'Defines the CAN ID for messages from the host to the target.',
    T1_CHECK_INTEGRATION =>                 'Indicates that the integration checking mechanism is enabled using the invocation file parameter [-checkIntegration](\ref checkIntegration), see T1_CheckIntegrationPC()',
    T1_COMMS_CORE_OFFSET =>                 'Specifies the index of the system that is used as T1 communication core.',
    T1_CONT_ANALYSIS_CAPACITY_COREXX =>     "Limits the amount of processing which is done in each call to the T1.cont background handle for system XX.\nHas to be set to a value equal or less than T1_TRACEBUFFER_ENTRIES_COREXX.",
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT =>    undef,
    T1_CONT_NOF_FOCUS_MEASUREMENTS =>       "Defines the number of focus measurements configured in the T1-TARGET-SW.\nAllowed values are 1 and 2.",
    T1_CONT_NOF_VRTL_STPWS =>               undef,
    T1_CONT_RC_UNMAP =>                     undef,
    T1_CORE_ID_TO_SCOPE_FG_GLOBALS =>       undef,
    T1_CORE_ID_TO_SCOPE_GLOBALS =>          'Do not change, macro is used by T1 internaly.',
    T1_CPULOAD_CALLBACK_COREXX =>           'Defines the name of the CPU load callback function for system XX.',
    T1_CPULOAD_SAMPLES_COREXX =>            "Defines if the CPU load is calculated only\nfor one single Basic Scheduling Frame (BSF) for system XX or if it is calculated as\nan average over all values that were collected during the time\nframe defined by T1_CPULOAD_TX_PERIOD_COREXX.",
    T1_CPULOAD_THRESHOLD_256THS_COREXX =>   'Initial CPU load threshold in per two hundred fifty-sixth for system XX',
    T1_CPULOAD_TX_PERIOD_COREXX =>          'Defines how often the CPU load is sent to the T1-HOST-SW for system XX in multiple of Basic Scheduling Frame (BSF).',
    T1_COUNT_PREEMPTION =>                  undef,
    T1_CROSS_CORE_ACT =>                    undef,
    T1_DETECT_TIMER_OVERFLOW =>             undef,
    T1_DISABLE_T1_CONT =>                   undef,
    T1_DISABLE_T1_DELAY =>                  undef,
    T1_DISABLE_T1_FLEX =>                   undef,
    T1_DISABLE_T1_MOD =>                    undef,
    T1_ETH_ECU_DNS_HOST_NAME =>             "Specifies the hostname of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_DNS_HOST_NAME_COREXX =>      "Specifies the hostname of the ECU used for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP0 =>                       "Specifies the first octet of the ECUs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP0_COREXX =>                "Specifies the first octet of the ECUs IP address used for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP1 =>                       "Specifies the second octet of the ECUs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP1_COREXX =>                "Specifies the second octet of the ECUs IP address used for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP2 =>                       "Specifies the third octet of the ECUs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP2_COREXX =>                "Specifies the third octet of the ECUs IP address used for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP3 =>                       "Specifies the fourth octet of the ECUs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IP3_COREXX =>                "Specifies the fourth octet of the ECUs IP address used for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV4 =>                      "Specifies the IPv4 address of the ECU as provided in the invocation file.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV4_COREXX =>               "Specifies the IPv4 address of the ECU as provided in the invocation file for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6 =>                      "Specifies the IPv6 address of the ECU as provided in the invocation file.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_COREXX =>               "Specifies the IPv6 address of the ECU as provided in the invocation file for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW0 =>                  "Specifies the first 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW0_COREXX =>           "Specifies the first 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW1 =>                  "Specifies the second 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW1_COREXX =>           "Specifies the second 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW2 =>                  "Specifies the third 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW2_COREXX =>           "Specifies the third 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW3 =>                  "Specifies the fourth 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW3_COREXX =>           "Specifies the fourth 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW4 =>                  "Specifies the fifth 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW4_COREXX =>           "Specifies the fifth 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW5 =>                  "Specifies the sixth 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW5_COREXX =>           "Specifies the sixth 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW6 =>                  "Specifies the seventh 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW6_COREXX =>           "Specifies the seventh 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW7 =>                  "Specifies the eighth 16-bits (half word) of the IPv6 address of the ECU.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_IPV6_HW7_COREXX =>           "Specifies the eighth 16-bits (half word) of the IPv6 address of the ECU for System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_PORT =>                      "Specifies the Port number of the ECU used for communicating with the T1-TARGET-SW.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_ECU_PORT_COREXX =>               "Specifies the Port number of the ECU used for communicating with the T1-TARGET-SW System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IP0 =>                        "Specifies the first octet of the host PCs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IP1 =>                        "Specifies the second octet of the host PCs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IP2 =>                        "Specifies the third octet of the host PCs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IP3 =>                        "Specifies the fourth octet of the host PCs IP address.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV4 =>                       "Specifies the IPv4 address of the host PC as provided in the invocation file.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6 =>                       "Specifies the IPv6 address of the host PC as provided in the invocation file.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW0 =>                   "Specifies the first 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW1 =>                   "Specifies the second 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW2 =>                   "Specifies the third 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW3 =>                   "Specifies the fourth 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW4 =>                   "Specifies the fifth 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW5 =>                   "Specifies the sixth 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW6 =>                   "Specifies the seventh 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_IPV6_HW7 =>                   "Specifies the eighth 16-bits (half word) of the IPv6 address of the host PC.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_PORT =>                       "Specifies the Port number of the host PCs used for communicating with the T1-TARGET-SW.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_PC_PORT_COREXX =>                "Specifies the Port number of the host PCs used for communicating with the T1-TARGET-SW System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_USE_IPV6 =>                      "Specifies if IPv6 (1) or IPv4 (0) should be used for communicating with the T1-TARGET-SW.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_USE_IPV6_COREXX =>               "Specifies if IPv6 (1) or IPv4 (0) should be used for communicating with the T1-TARGET-SW System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_USE_UDP =>                       "Specifies if UDP (1) or TCP (0) should be used for communicating with the T1-TARGET-SW.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_ETH_USE_UDP_COREXX =>                "Specifies if UDP (1) or TCP (0) should be used for communicating with the T1-TARGET-SW System XX.\nThis parameter is not used by the T1-TARGET-SW.",
    T1_EXTERNAL_TRACEBUFFER =>              'Allow external configuration of the T1 trace buffers, see \ref externalTraceBuffer.',
    T1_EXT_TRACEBUFFER_ENTRIES_COREXX =>    "Allow to configure the size of the T1 trace buffer for the system XX when #T1_EXTERNAL_TRACEBUFFER is defined.\nThis macro can be globally defined or defined in T1_AppInterface.h, otherwise #T1_TRACEBUFFER_ENTRIES_COREXX is used.",
    T1_EXT_ISR_ID_OFFSET_COREXX =>          'Offset at which starts the CAT1 ISR IDs on the system XX, see \ref additionalCat1IsrIdOffset.',
    T1_FEATURE_MASK_CALLBACK_COREXX =>      "Specifies if the T1 feature mask callback is called for system XX or not if the feature mask changes.\nThe value is a 16-bit mask where every system is represented by the bit position that corresponds to the systems index. See \\ref featureMaskCallback",
    T1_FG_CONT =>                           undef,
    T1_FLEX_OVERHEAD_COREXX_NS =>           'Specifies the additional overhead incurred at a T1.flex trace event in nanoseconds.',
    T1_GCP_MAX_RX_FRAME_SIZE =>             'Specifies the maximum messages size sent by the T1-HOST-SW (Host to Target).',
    T1_GCP_MAX_TX_FRAME_SIZE =>             'Specifies the maximum messages size sent by the T1-TARGET-SW (Target to Host).',
    T1_GET_RAW_TIME_COREXX =>               'Returns the RAW timer value for system XX.',
    T1_GET_SYNC_TIME =>                     'Returns the current sync timer value, see \ref pSyncTimer.',
    T1_GET_TRACE_TIME_PC =>                 "\\def T1_GET_TRACE_TIME_PC\nThis macro is generated depending on the timers configuration.\n\\returns the trace timer count register scaled to trace timer ticks.",
    T1_INIT_FEATURE_MASK =>                 'Initial value of application feature mask.',
    T1_MAX_NOF_TASKS =>                     'The maximum value of all cores T1_NOF_TASKS_COREXX macros.',
    T1_MIN_CAT1_ISR_ID_OFFSET =>            'The minimum value of all cores T1_CAT1_ISR_ID_OFFSET_COREXX macros.',
    T1_MIN_CAT2_ISR_ID_OFFSET =>            'The minimum value of all cores T1_CAT2_ISR_ID_OFFSET_COREXX macros.',
    T1_MIN_EXT_ISR_ID_OFFSET =>             'The minimum value of all cores T1_EXT_ISR_ID_OFFSET_COREXX macros.',
    T1_NOF_CORES =>                         'The number of cores that are instrumented with T1.',
    T1_NOF_CSRNS_COREXX =>                  'Specifies the number of constraints for system XX.',
    T1_NOF_DELAYS_COREXX =>                 'Specifies the number of delays for system XX.',
    T1_NOF_FLEX_ADDRS_COREXX =>             'Defines the number of T1.flex address buffer for system XX.',
    T1_NOF_FLEX_STPWS_COREXX =>             'Defines the number of used T1.flex stopwatches for system XX.',
    T1_NOF_STPWS_COREXX =>                  'Defines the number of used user and T1.flex stopwatches for system XX.',
    T1_NOF_TASKS_COREXX =>                  'Defines the number of tasks and ISRs for system XX.',
    T1_NOF_USER_STPWS_COREXX =>             'Defines the number of user stopwatches for system XX.',
    T1_OVERHEAD_COREXX_NS =>                'Specifies the minimum duration of one call to T1_TraceEvent() in nanoseconds on system XX.',
    T1_PC =>                                undef,
    T1_PC_ARRAY =>                          undef,
    T1_RAW_TO_SYNC_TIME =>                  undef,
    T1_RAW_TO_SYNC_TIME_COREXX =>           'Macro to convert the RAW timer value to the sync timer value for system XX.',
    T1_RAW_TO_TRACE_TIME =>                 undef,
    T1_RAW_TO_TRACE_TIME_COREXX =>          'Macro to convert the RAW timer value to the trace timer value for system XX.',
    T1_RAW_TO_TRACE_TIME_UNMASKED =>        undef,
    T1_RAW_TO_TRACE_TIME_UNMASKED_COREXX => undef,
    T1_SID =>                               'T1 system ID for system 0',
    T1_SUPPORT_TIMER_OVERFLOW =>            undef,
    T1_SYNC_PERIOD_COREXX =>                'Automatically generated sync events during streaming for every Nth call of T1_HandlerPC for system XX.',
    T1_SYNC_TIMER_DURATION_NS =>            'Duration of one tick of the synchronization timer in nanoseconds.',
    T1_SYNC_TIMER_WIDTH_BITS =>             'Synchronization time bit length (up to 32 bits).',
    T1_SYNC_TO_TRACE_TIME =>                undef,
    T1_SYNC_TO_TRACE_TIME_COREXX =>         undef,
    T1_TICK_DURATION_COREXX_NS =>           'Duration of one tick of the trace timer in nanoseconds for system XX.',
    T1_TIMEOUT_RESPONSE =>                  'Timeout on the target side for receiving an acknowledgment of a message from the host in multiples of the period of T1_HandlerPC.',
    T1_TIMEOUT_RX =>                        'Defines the target receive timeout in multiples of the period of T1_HandlerPC.',
    T1_TIMEOUT_TX =>                        'Minimum time allowed for (retrying) the sending of a frame by the target in multiples of the period of T1_HandlerPC.',
    T1_TRACEBUFFER_ENTRIES_COREXX =>        'Defines the number of trace buffer entries for system XX',
    T1_TRACE_TASK =>                        'Used to exclude from tracing some tasks with the lowest used priority level, see \ref targetExcludeFromTraceByName and \ref targetExcludeFromTraceById.',
    T1_TRACE_TIMER_BIT_LENGTH_COREXX =>     'Defines the number of counting bits in the raw (unscaled) physical trace timer register for system XX.',
    T1_TRACE_TIMER_COUNTS_DOWN_COREXX =>    'This parameter is used to specify that the trace timer is counting down for system XX.',
    T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX =>  'Indicates whether the trace timer on system XX is the same as the shared, trace-synchronization timer.',
    T1_TRACE_TO_SYNC_TIME =>                undef,
    T1_TRACE_TO_SYNC_TIME_COREXX =>         undef,
    T1_WAIT_RESUME =>                       undef,
);

# Core specific variables should be documented without the coreId, the comment
# will have the coreId added in FormatConfigVariable
my %variableDocuTextList = (
    T1_checkIntegration =>      'Variable read/written by the system XX and read by the next ( modulo the number of systems ) in T1_CheckIntegrationHandlerPC() for checking T1.flex data measurement during integration.',
    T1_checkIntegrationPC =>    'For each core, a variable for checking integration used by T1_CheckIntegrationHandlerPC().',
    T1_commsCoreOffset =>       'Index of the system that is used as T1 communication core.',
    T1_csrnConfig =>            'The T1.cont constraint configuration of system XX.',
    T1_csrnConfigPC =>          'For each core, a pointer to the T1.cont constraint configuration.',
    T1_delayConfigPC =>         'For each system, a pointer to the T1.delay configuration (array with initial values).',
    T1_nOfCores =>              'Number of cores with T1 enabled.',
    T1_nOfCsrnsPC =>            'For each core, the number of constraints.',
    T1_nOfDelaysPC =>           'For each system, the number of delays.',
    T1_nOfStpwsPC =>            "For each core, the number of stopwatches used by T1.\nCounting the users, T1.flex and virtual stopwatches.",
    T1_nOfTasksPC =>            'For each core, the number of tasks and ISRs instrumented by T1.',
    T1_nOfUserStpwsPC =>        'For each core, the number of user stopwatches used by T1.',
    T1_resultBuffer =>          'The T1.cont result buffer of system XX.',
    T1_traceBuffer =>           'Array holding the number of events + 1 for system XX, set using -traceBufferEntries or using \ref externalTraceBuffer.',
    T1_traceEntries =>          'Array holding the number of events for system XX, set using -traceBufferEntries or using \ref externalTraceBuffer.',
);

######################################################################################
# sub isT1HostSwVersionAllowed Checks if it is allowed to generate code that requires
#                              a range of T1-HOST-SW versions. The supplied range of
#                              version is compared to what has been set using
#                              $minT1HostSwVersion.
# param set min version should be set to the value of $minT1HostSwVersion
# param min version
# param max version (optional)
#
# returns 0 if min version <  $minT1HostSwVersion
# returns 0 if max version >= $minT1HostSwVersion
# returns 1 otherwise
######################################################################################
sub isT1HostSwVersionAllowed
{
    my ( $setMinMajor, $setMinMinor, $setMinPatch ) = split /\./, shift;
    my ( $minMajor, $minMinor, $minPatch ) = split /\./, shift;
    my ( $maxMajor, $maxMinor, $maxPatch ) = split /\./, shift if scalar @_;

    if( defined $minMajor )
    {
        print qq(Debug: v$minMajor.$minMinor.$minPatch >= v$setMinMajor.$setMinMinor.$setMinPatch\n) if DEBUG;

        if( $setMinMajor < $minMajor )
        {
            return 0;
        }
        elsif( $setMinMinor < $minMinor )
        {
            return 0;
        }
        elsif( $setMinPatch < $minPatch )
        {
            return 0;
        }
    }

    if( defined $maxMajor )
    {
        print qq(Debug: v$minMajor.$minMinor.$minPatch >= v$setMinMajor.$setMinMinor.$setMinPatch < v$maxMajor.$maxMinor.$maxPatch\n) if DEBUG;

        if( $maxMajor <= $setMinMajor )
        {
            if( $maxMinor <= $setMinMinor )
            {
                if( $maxPatch <= $setMinPatch )
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

    return 1;
}

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
# sub stripU for literals that can be evaluated by the preprocessor
######################################################################################

sub stripU($)
{
    my $intgr = shift;
    $intgr =~ s/^(0x[0-9A-Fa-f]+|\d+)$/$1/;
    return $intgr;
}

######################################################################################
# sub SecString returns the #include MemMap to start/stop a given section
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Core ID
#   START or STOP
#   VAR_POWER_ON_CLEARED_x or CONST_x or CODE
#   Alignment in bits
sub SecString($$$$)
{
    my $coreId = shift;
    my $ppIndent = shift;
    my $startStop = shift;
    my $kind = shift;
    my $modifier = '';
    if( $kind =~ s/(\d+)(_\S+)$/$1/ )
    {
        $modifier = $2;
        $kind =~ s/_\d+$// if '_DCX' eq $modifier;
    }
    my $coreSuffix = '';
    $coreSuffix = "_CORE$coreId" if 0 <= $coreId;
    return  "#   ${ppIndent}define T1$modifier${coreSuffix}_${startStop}_SEC_$kind\n#   ${ppIndent}include \"T1_MemMap.h\"";
}

######################################################################################
# sub Sec prints the #include MemMap to start/stop a given section
######################################################################################

# Input:
#   File handle for output
#   Additional indentation whitespace
#   Core ID
#   START or STOP
#   VAR_POWER_ON_CLEARED_x or CONST_x or CODE
#   Alignment in bits
sub Sec($$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $coreId = shift;
    my $startStop = shift;
    my $kind = shift;
    print $fh (SecString( $coreId, $ppIndent, $startStop, $kind ) . "\n");

    return;
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
#   Doxygen comment generation, used by FormatConfigVariable
sub GenMultiCoreDataStructure($$$$$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $nOfCores = shift;
    my $arrayName = shift;
    my $elementType = shift;
    my $alignmentBits = shift;
    my $elementName = shift;
    my $doxygenComment = shift;
    my $modifier = '';
    if( $alignmentBits =~ s/(\d+)(_\S+)$/$1/ )
    {
        $modifier = $2;
    }
    my @elementNames;
    foreach my $coreId ( 0 .. ($nOfCores-1) )
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

    Sec( $fh, $ppIndent, -1, 'START', "CONST_$alignmentBits$modifier" );
    print $fh FormatConfigVariable( $doxygenComment, $arrayName, undef );
    printf $fh "%-23s T1%s_SEC_CONST_%s %s[%d] =\n{\n    ", "$elementType const", $modifier, $alignmentBits, $arrayName, $nOfCores;
    print $fh ((join ",\n    ", @elementNames) . "\n");
    print $fh "};\n";
    Sec( $fh, $ppIndent, -1, 'STOP', "CONST_$alignmentBits$modifier" );

    return;
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
#   Whether or not to make the elements static ('static'/'')
#   Doxygen comment generation, used by FormatConfigVariable
sub GenMultiCoreDataStructurePlusElements($$$$$$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $nOfCores = shift;
    my $elementType = shift;
    my $alignmentBits = shift;
    my $elementName = shift;
    my $static = shift;
    $static .= ' ' unless '' eq $static;
    my $initializer = shift;
    my $doxygenComment = shift;
    my $modifier = '';
    if( $alignmentBits =~ s/(\d+)(_\S+)$/$1/ )
    {
        $modifier = $2;
    }
    my $initStringXX = '';
    my $kind = 'VAR_POWER_ON_CLEARED';
    if( '' ne $initializer )
    {
        # Initialize only consts
        $initStringXX = ' = ' . $initializer;
        $kind = 'CONST';
    }

    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        Sec( $fh, $ppIndent, $coreId, 'START', "${kind}_$alignmentBits$modifier" );
        my $initString = $initStringXX;
        $initString =~ s/XX/$coreId/g;
        print $fh FormatConfigVariable( $doxygenComment, $elementName, $coreId );
        printf $fh "%-23s T1%s_CORE%d_SEC_%s_%s %s%d%s;\n", "$static$elementType", $modifier, $coreId, $kind, $alignmentBits, $elementName, $coreId, $initString;
        Sec( $fh, $ppIndent, $coreId, 'STOP', "${kind}_$alignmentBits$modifier" );
    }

    GenMultiCoreDataStructure( $fh, $ppIndent, $nOfCores, $elementName . 'PC', $elementType . ' *', '32', '&' . $elementName . 'XX', $doxygenComment );

    return;
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
#   Doxygen comment generation, used by FormatConfigVariable
sub Gen2DimensionalMultiCoreDataStructure($$$$$$$$)
{
    my $fh = shift;
    my $ppIndent = shift;
    my $nOfCores = shift;
    my $elementType = shift;
    my $alignmentBits = shift;
    my $elementName = shift;
    my $secondDimension = shift;
    my $doxygenComment = shift;
    my $modifier = '';
    if( $alignmentBits =~ s/(\d+)(_\S+)$/$1/ )
    {
        $modifier = $2;
    }

    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        my $arraySize = $secondDimension;
        $arraySize =~ s/XX/$coreId/g;
        my $static = 'static ';
        $static = '' if $elementName =~ /^T1_traceBuffer/
                        or $elementName =~ /^T1_resultBuffer/
                        or $elementType eq 'T1_focusData_t'
                        or $elementType eq 'T1_stpwFgData_t'
                        or $elementType eq 'T1_vStpwMapping_t'
                        or $elementType eq 'T1_csVStpwCache_t';

        Sec( $fh, $ppIndent, $coreId, 'START', "VAR_POWER_ON_CLEARED_$alignmentBits$modifier" );
        print $fh FormatConfigVariable( $doxygenComment, $elementName, $coreId );
        # $alignmentBits is formatted as a string so that we can append DCX, etc.
        printf $fh "%-23s T1%s_CORE%d_SEC_VAR_POWER_ON_CLEARED%s %s%d[%s];\n", "$static$elementType", $modifier, $coreId, '_DCX' eq $modifier ? '' : "_$alignmentBits", $elementName, $coreId, $arraySize;
        Sec( $fh, $ppIndent, $coreId, 'STOP', "VAR_POWER_ON_CLEARED_$alignmentBits$modifier" );
    }

    $alignmentBits =~ s/_.*$//;
    GenMultiCoreDataStructure( $fh, $ppIndent, $nOfCores, $elementName . 'PC', $elementType . ' *', $alignmentBits, $elementName . 'XX', $doxygenComment );

    return;
}

my $formatConfigMacroWarningShown = 0;

######################################################################################
# sub FormatDocu returns a formatted string containing the Doxygen documentation if
# enabled and documented in the hash %macroDocuTextList
######################################################################################

# Input:
#   Doxygen comment generation
#   Name of the macro
#   Core Id, can be undefined
sub FormatDocu
{
    my $DoxyGen = shift;
    my $name = shift;
    my $coreId = shift;

    my $macroName = $name;
    if( defined $coreId )
    {
        unless( $macroName =~ s/COREXX/CORE${coreId}/ )
        {
            die "Error: Core ID (${coreId}) provided, but did not found 'COREXX' in '${name}', please contact GLIWA support (support\@gliwa.com).\n";
        }
    }
    elsif( $macroName =~ /COREXX/ )
    {
        die "Error: No core ID provided, but found 'COREXX' in '${macroName}', please contact GLIWA support (support\@gliwa.com).\n";
    }
    else
    {
        # No processing of macro name required
    }

    my $returnString = '';
    if( $DoxyGen ne 'false' )
    {
        my ( $helpName ) = $name =~ /^(\w+)/;
        if( my $helpText = $macroDocuTextList{$helpName} )
        {
            $helpText =~ s/((?:CORE|system)\s*)XX/$1${coreId}/ig if defined $coreId;
            my @helpTextLines = split $/, $helpText;

            if( $DoxyGen eq 'before' )
            {
                $returnString = "/*!\n * ";
                $returnString .= join "\n * ", @helpTextLines;
                $returnString .= "\n */\n";
            }
            elsif( $DoxyGen eq 'after' )
            {
                $returnString = ' /*!< ' . ( join ' ', @helpTextLines ) . ' */';
            }
            elsif( not $formatConfigMacroWarningShown )
            {
                $formatConfigMacroWarningShown = 1;
                warn "Warning: Parameter '-enableDoxygenComments' with unknown argument '${DoxyGen}'.\n";
            }
            else
            {
                # Just continue
            }
        }
        elsif( DEBUG and not exists $macroDocuTextList{$helpName} )
        {
            print "Missing Doxygen Comment: ${helpName}\n";
        }
    }

    return $returnString;
}
######################################################################################
# sub FormatConfigMacro returns a formatted string containing the macro definition
# with optional Doxygen documentation if enabled and documented in the hash
# %macroDocuTextList
######################################################################################

# Input:
#   Doxygen comment generation
#   Additional indentation whitespace
#   Name of the macro
#   Value of the macro
#   Core Id, can be undefined
#   Suppression of brackets around the value
sub FormatConfigMacro
{
    my $DoxyGen = shift;
    my $indent1 = int shift;
    my $name = shift;
    my $value = shift;
    my $coreId = shift;
    my $suppressBracket = shift;

    $indent1 = $indent1 > 0 ? $indent1 * 4 : 1;
    my $indent2 = 46 - $indent1;

    my $macroName = $name;
    if( defined $coreId )
    {
        unless( $macroName =~ s/COREXX/CORE${coreId}/ )
        {
            die "Error: Core ID (${coreId}) provided, but did not found 'COREXX' in '${name}', please contact GLIWA support (support\@gliwa.com).\n";
        }

        # Try to replace COREXX in the value, this is needed for some of the values
        # e.g. #define T1_NOF_STPWS_COREXX (T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX)
        $value =~ s/COREXX/CORE${coreId}/g;
    }
    elsif( $macroName =~ /COREXX/ )
    {
        die "Error: No core ID provided, but found 'COREXX' in '${macroName}', please contact GLIWA support (support\@gliwa.com).\n";
    }
    elsif( $value =~ /COREXX/ )
    {
        die "Error: No core ID provided, but found 'COREXX' in '${value}', please contact GLIWA support (support\@gliwa.com).\n";
    }
    else
    {
        # No processing of macro name required
    }

    unless( $suppressBracket )
    {
        $value = "(${value})";
    }

    my $helpTextBefore = '';
    my $helpTextAfter = '';

    if( $DoxyGen ne 'false' )
    {
        my ( $helpName ) = $name =~ /^(\w+)/;
        if( my $helpText = $macroDocuTextList{$helpName} )
        {
            $helpText =~ s/((?:CORE|system)\s*)XX/$1${coreId}/ig if defined $coreId;
            my @helpTextLines = split $/, $helpText;

            if( $DoxyGen eq 'before' )
            {
                $helpTextBefore = "/*!\n * ";
                $helpTextBefore .= join "\n * ", @helpTextLines;
                $helpTextBefore .= "\n */\n";
            }
            elsif( $DoxyGen eq 'after' )
            {
                $helpTextAfter = ' /*!< ' . ( join ' ', @helpTextLines ) . ' */';
            }
            elsif( not $formatConfigMacroWarningShown )
            {
                $formatConfigMacroWarningShown = 1;
                warn "Warning: Parameter '-enableDoxygenComments' with unknown argument '${DoxyGen}'.\n";
            }
            else
            {
                # Just continue
            }
        }
        elsif( DEBUG and not exists $macroDocuTextList{$helpName} )
        {
            print "Missing Doxygen Comment: ${helpName}\n";
        }
    }

    my $returnString = $helpTextBefore;
    $returnString   .= sprintf "%-*sdefine %-*s %s", $indent1, '#', $indent2, $macroName, $value;
    $returnString   .= $helpTextAfter;
    $returnString   .= "\n";

    return $returnString;
}

######################################################################################
# sub FormatConfigVariable returns a string with the Doxygen documentation if enabled
# and if the variable is documented in the hash %variableDocuTextList. If both
# conditions are false, returns an empty string.
######################################################################################

# Input:
#   Doxygen comment generation
#   Name of the variable
#   Core Id, can be undefined
sub FormatConfigVariable
{
    my $DoxyGen = shift;
    my $name = shift;
    my $coreId = shift;

    if( $DoxyGen eq 'false' )
    {
        return '';
    }
    else
    {
        my $returnString = '';
        if( my $helpText = $variableDocuTextList{$name} )
        {
            $helpText =~ s/((?:CORE|system)\s*)XX/$1${coreId}/ig if defined $coreId;
            my @helpTextLines = split $/, $helpText;

            if( ( $DoxyGen eq 'before' ) or ( $DoxyGen eq 'after' ) )
            {
                # Only comment variables before
                $returnString = "/*!\n * ";
                $returnString .= join "\n * ", @helpTextLines;
                $returnString .= "\n */\n";
            }
            elsif( not $formatConfigMacroWarningShown )
            {
                $formatConfigMacroWarningShown = 1;
                warn "Warning: Parameter '-enableDoxygenComments' with unknown argument '${DoxyGen}'.\n";
            }
            else
            {
                # Just continue
            }
        }
        elsif( DEBUG and not exists $variableDocuTextList{$name} )
        {
            print "Missing Doxygen Comment: ${name}\n";
        }
        return $returnString;
    }
}

my %secStrings;

######################################################################################
# sub GenT1ConfigBuffC prints the generated tracebuffer segment of T1_configBuff.c
######################################################################################

# Input:
#   File handle for output
#   Configuration database as a Perl hash
sub GenT1ConfigBuffC($$)
{
    my $fh = shift;
    my $configRef = shift;
    my %config = %$configRef;
    my $nOfCores = $config{'nOfCores'};
    my $DG = $config{'enableDoxygenComments'};

    print $fh <<EOT;
#if defined T1_ENABLE && ! defined T1_DISABLE_T1_SCOPE && defined T1_EXTERNAL_TRACEBUFFER
EOT

    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        print $fh <<EOT;

#   if 8 == T1_CONT_NOF_VRTL_STPWS
#       define T1_FG_DO_V_STPW T1_FgDoVStpw8
#   else /* 64 event chains */
#       define T1_FG_DO_V_STPW T1_FgDoVStpw64
#   endif /* 8 == T1_CONT_NOF_VRTL_STPWS */

#   ifdef T1_EXT_TRACEBUFFER_ENTRIES_CORE$coreId
#       if T1_EXT_TRACEBUFFER_ENTRIES_CORE$coreId < 1 || 65535 < T1_EXT_TRACEBUFFER_ENTRIES_CORE$coreId
#           error T1_EXT_TRACEBUFFER_ENTRIES_CORE$coreId must be in the range [1..65535]
#       endif
#   else
EOT
        print $fh FormatConfigMacro( $DG, 2, 'T1_EXT_TRACEBUFFER_ENTRIES_COREXX', "T1_TRACEBUFFER_ENTRIES_COREXX", $coreId, 1 );
        print $fh <<EOT;
#   endif

#   if ! defined T1_PTIMER_CORE$coreId
#define T1_PTIMER_CORE$coreId (0u)
#   endif /* defined T1_PTIMER_CORE$coreId */
EOT
    }

    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_traceEntry_t T1_FAR', '32_TRACEBUFFER', 'T1_traceBuffer', 'T1_EXT_TRACEBUFFER_ENTRIES_COREXX + 1', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_traceEntriesPC', 'T1_nOfEntries_t', '16', 'T1_EXT_TRACEBUFFER_ENTRIES_COREXX', $DG );

    print $fh <<EOT;
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
EOT
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_scopeFgConsts_t', '32', 'T1_scopeFgConsts', '', '{ { { (T1_scopeGlobals_t *)&T1_scopeFgGlobalsXX }, T1_traceBufferXX + 1, T1_EXT_TRACEBUFFER_ENTRIES_COREXX - 1, T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX, T1_SYNC_TIMER_WIDTH_BITS, T1_TRACE_TIMER_BIT_LENGTH_COREXX, XXu, T1_EXT_TRACEBUFFER_ENTRIES_COREXX, (T1_tickUint_t volatile const *)T1_PTIMER_COREXX, (T1_bool_t)T1_TRACE_56BIT_SYNC_TIMER, T1_CONT_NOF_VRTL_STPWS, T1_FG_CONT_ACT_EXTRA_ENTRIES, T1_FAR_TRACE_EVENT_NOSUSP_TIME, T1_FAR_TRACE_UINT32_REST_NOSUSP, T1_FAR_TRACE_UINT56_REST_NOSUSP }, T1_DISPATCH_COREXX, T1_MAX_NOF_TASKS, T1_NOF_USER_STPWS_COREXX, T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX, T1_CONT_NOF_FOCUS_MEASUREMENTS, T1_NOF_CSRNS_COREXX, 0u, (T1_uint32_t)(0uL - T1_NOF_FLEX_STPWS_COREXX), T1_taskFgData, T1_focusXX, T1_stpwFgDataXX, T1_contHandlerStatusPC + XX, T1_FG_DO_V_STPW, T1_resultBufferXX + T1_NOF_TASKS_COREXX, T1_vStpwXX, T1_vStpwXX + T1_CONT_NOF_VRTL_STPWS, T1_contCsVStpwCacheXX, T1_HANDLERS }', $DG );
    print $fh <<EOT;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
EOT
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_scopeConsts_t', '32', 'T1_scopeConsts', '', '{ { &T1_scopeGlobalsXX }, T1_traceBufferXX + 1, T1_EXT_TRACEBUFFER_ENTRIES_COREXX - 1, T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX, T1_SYNC_TIMER_WIDTH_BITS, T1_TRACE_TIMER_BIT_LENGTH_COREXX, XXu, T1_EXT_TRACEBUFFER_ENTRIES_COREXX, (T1_tickUint_t volatile const *)T1_PTIMER_COREXX, (T1_bool_t)T1_TRACE_56BIT_SYNC_TIMER, 0u, 0u, T1_FAR_TRACE_EVENT_NOSUSP_TIME, T1_FAR_TRACE_UINT32_REST_NOSUSP, T1_FAR_TRACE_UINT56_REST_NOSUSP }', $DG );
    print $fh <<EOT;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_SCOPE && defined T1_EXTERNAL_TRACEBUFFER */
EOT

    return;
}

######################################################################################
# sub ipv6StringToHalfWords
#     converts a IPv6 string into 8 half words represented by hex strings
######################################################################################
sub ipv6StringToHalfWords
{
    my ( $string ) = @_;

    my $countDoubleColons = () = $string =~ /::/g;
    if( 1 != $countDoubleColons )
    {
        warn qq(Warning: Invalid IPv6 address "${string}".\n);
        return;
    }
    else
    {
        my $countColons = () = $string =~ /:/g;

        if( $countColons < 7 )
        {
            # If there are less than 7 colons there must be a double colon
            my $missingColons = 8 - $countColons;
            my $replacementString = ( (':0') x $missingColons ) . ':';
            $string =~ s/::/${replacementString}/;
        }

        # Ensure that the IP address starts and ends with a valid char
        $string =~ s/^:/0:/;
        $string =~ s/:$/:0/;

        my @halfWords =  split /:/, $string;

        # Check format of each half word
        foreach my $halfWord ( @halfWords )
        {
            unless( $halfWord =~ /^[0-9a-fA-F]{1,4}$/ )
            {
                warn qq(Warning: Invalid IPv6 address "${string}".\n);
                return;
            }
        }

        @halfWords = map { sprintf "%04x", hex $_ } @halfWords;
        return @halfWords;
    }
}

######################################################################################
# sub printIpv6StringAsHalfWords
#     converts a IPv6 string into 8 half and prints it to the provided file handle
######################################################################################
sub printIpv6StringAsHalfWords
{
    my ( $fh, $DG, $template, $string, $coreId ) = @_;

    my @array = ipv6StringToHalfWords( $string );

    my $counter = 0;
    foreach my $halfWord ( @array )
    {
        my $macro = $template;
        $macro =~ s/NN/$counter/;

        print $fh FormatConfigMacro( $DG, 0, $macro, $halfWord, $coreId, 1 );
        ++$counter;
    }

    return;
}

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
    my $nOfCores = $config{'nOfCores'};
    my @nOfTasks = @{$config{'numberOfTasks'}};
    # absolute value used for T1_configGen.c data structure
    # if the @config value is negative, the macro is not generated in T1_config.h
    my @nOfUserStopwatches = map { abs } @{$config{'numberOfUserStpws'}};
    # absolute value used for T1_configGen.c data structure
    # if the @config value is negative, the macro is not generated in T1_config.h
    my @nOfConstraints = map { abs } @{$config{'numberOfConstraints'}};
    my $checkIntegration = $config{'checkIntegration'};
    my $DG = $config{'enableDoxygenComments'};

    # Initialize %secStrings
    foreach my $startStop ('START', 'STOP')
    {
        foreach my $kind ('VAR_POWER_ON_CLEARED_8', 'VAR_POWER_ON_CLEARED_16', 'VAR_POWER_ON_CLEARED_32', 'VAR_POWER_ON_CLEARED_32_TRACEBUFFER', 'CONST_8', 'CONST_16', 'CONST_32', 'CODE', 'CODE_FAST')
        {
            foreach my $coreId ( -1 .. ($nOfCores-1) )
            {
                foreach my $indentTab ( 0 .. 2 )
                {
                    $secStrings{$startStop}{$kind}{$coreId}{$indentTab} = SecString( $coreId, '    ' x $indentTab, $startStop, $kind );
                }
            }
        }
    }

######################################################################################
### Verify $nOfCores                                                               ###
######################################################################################

        print $fh <<EOT;
/*----------------------------------------------------------------------------------*/
/*--- Optimization pragmas for uniform code generation with widely-used compilers --*/
/*----------------------------------------------------------------------------------*/

#if defined __ghs__
#   pragma ghs O
#elif defined __TASKING__
#   pragma optimize 2
#elif defined __GNUC__ && ! defined __TMS470__ && ! defined __clang__ && ! defined __ARMCC_VERSION
#   pragma GCC optimize "O2"
#endif /* defined __ghs__ */

EOT

    {
        print $fh <<EOT;
#if defined T1_ENABLE
#   if $nOfCores != T1_NOF_CORES
#       error T1_NOF_CORES does not match generated configuration
#   endif /* $nOfCores != T1_NOF_CORES */
#   if 15 < T1_NOF_CORES
#       error Only up to 15 cores
#   endif /* 15 < T1_NOF_CORES */
#endif /* defined T1_ENABLE */
EOT
    }

######################################################################################
### T1.base                                                                        ###
######################################################################################

    my $featureMaskCallbackMaskString = 'T1_FEATURE_MASK_CALLBACK_CORE0'; # Special case for single core, because it looks nicer
    if( 1 < $nOfCores )
    {
        $featureMaskCallbackMaskString = "(\n      ";
        $featureMaskCallbackMaskString .= join '    | ', map { "T1_FEATURE_MASK_CALLBACK_CORE${_}\n" } ( 0 .. $nOfCores-1 );
        $featureMaskCallbackMaskString .= ')';
    }

    print $fh <<EOT;

#if defined T1_ENABLE && ! defined T1_DISABLE_T1_BASE
#   if ! defined T1_SID
#       error T1_SID must be defined
#   else
#       if T1_SID < 1 || 255 < T1_SID
#           error T1_SID must be > 0 and < 256
#       endif /* T1_SID < 1 || 255 < T1_SID */
/* Also check GCP Target ID which is derived from SID */
#       define T1_TID_CORE0 (T1_SID % 32u) /*! GCP Target ID for Core 0 */
#       if defined T1_NOF_CORES
#           if T1_TID_CORE0 < 1 || (32 - T1_NOF_CORES) < T1_TID_CORE0
#               error (T1_SID % 32) must be > 0 and <= (32 - T1_NOF_CORES)
#           endif /* T1_TID_CORE0 < 1 || (32 - T1_NOF_CORES) < T1_TID_CORE0 */
#       else /* ! defined T1_NOF_CORES */
#           if T1_TID_CORE0 < 1 || 31 < T1_TID_CORE0
#               error (T1_SID % 32) must be > 0 and < 32
#           endif /* T1_TID_CORE0 < 1 || 31 < T1_TID_CORE0 */
#       endif /* defined T1_NOF_CORES */
#       undef T1_TID_CORE0
#   endif /* ! defined T1_SID */

#if 8 == T1_CONT_NOF_VRTL_STPWS
#   define T1_FG_DO_V_STPW T1_FgDoVStpw8
#else /* 64 event chains */
#   define T1_FG_DO_V_STPW T1_FgDoVStpw64
#endif /* 8 == T1_CONT_NOF_VRTL_STPWS */

$secStrings{START}{CONST_8}{-1}{0}
EOT
    if( 0 < $nOfCores )
    {
        print $fh FormatConfigVariable( $DG, 'T1_commsCoreOffset', undef );
        print $fh "T1_uint8_t const        T1_SEC_CONST_8 T1_commsCoreOffset = T1_COMMS_CORE_OFFSET;\n";
    }
    print $fh <<"EOT";
#   if ! defined T1_EXTERNAL_BID
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_CAT( T1_bid_, T1_BUILD_ID );
T1_uint8_t const        T1_SEC_CONST_8 T1_CAT( T1_bid_, T1_BUILD_ID ) = 0u;
#   endif /* ! defined T1_EXTERNAL_BID */
#   if ! defined T1_NO_INIT_SID
T1_uint8_t const        T1_SEC_CONST_8 T1_sid = T1_SID;
#   endif /* ! defined T1_NO_INIT_SID */
$secStrings{STOP}{CONST_8}{-1}{0}
#   if defined T1_NO_INIT_SID
$secStrings{START}{VAR_POWER_ON_CLEARED_8}{-1}{1}
T1_uint8_t              T1_SEC_VAR_POWER_ON_CLEARED_8 T1_sid;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_8}{-1}{1}
#   endif /* defined T1_NO_INIT_SID */
$secStrings{START}{CONST_16}{-1}{0}
T1_timeouts_t const     T1_SEC_CONST_16 T1_timeouts = { T1_TIMEOUT_RX, T1_TIMEOUT_TX, T1_TIMEOUT_RESPONSE };
T1_uint16_t const       T1_SEC_CONST_16 T1_featureMaskCallbackMask = ${featureMaskCallbackMaskString};
$secStrings{STOP}{CONST_16}{-1}{0}
$secStrings{START}{CONST_32}{-1}{0}
#   if ! defined T1_EXTERNAL_BID
T1_uint8_t const * const T1_SEC_CONST_32 T1_pBid = &T1_CAT( T1_bid_, T1_BUILD_ID );
T1_uint32_t const       T1_SEC_CONST_32 T1_bid = T1_CAT( T1_BUILD_ID, uL );
#   endif /* ! defined T1_EXTERNAL_BID */
T1_featureMask_t const  T1_SEC_CONST_32 T1_initFeatureMask = T1_INIT_FEATURE_MASK;
$secStrings{STOP}{CONST_32}{-1}{0}
$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{0}
T1_featureMask_t        T1_SEC_VAR_POWER_ON_CLEARED_32 T1_featureMask;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{0}
EOT

    print $fh "#   if defined T1_CPU32BIT || defined T1_CPU64BIT\n";
    if( $nOfCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{1}
T1_uint8_t const        T1_SEC_CONST_8 T1_traceTimerBitLength = T1_TRACE_TIMER_BIT_LENGTH_CORE0;
$secStrings{STOP}{CONST_8}{-1}{1}
EOT
    }
    else
    {
        GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_traceTimerBitLengthPC', 'T1_uint8_t', '8', 'T1_TRACE_TIMER_BIT_LENGTH_COREXX', $DG );
    }
    print $fh "#   endif /* defined T1_CPU32BIT || defined T1_CPU64BIT */\n";

    if( $nOfCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{0}
T1_baseGlobals_t        T1_SEC_VAR_POWER_ON_CLEARED_32 T1_baseGlobals;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{0}
EOT
    }
    else
    {
        print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_nOfCores = T1_NOF_CORES;
$secStrings{STOP}{CONST_8}{-1}{0}
EOT
        GenMultiCoreDataStructurePlusElements( $fh, '', $nOfCores, 'T1_baseGlobals_t', '32', 'T1_baseGlobals', 'static', '', $DG );
    }

    print $fh <<EOT;

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_BASE */
EOT

######################################################################################
### T1.cont                                                                        ###
######################################################################################
    print $fh <<EOT;

#if defined T1_ENABLE && ! defined T1_DISABLE_T1_CONT
EOT

#------ Callouts to check if T1_FG_CONT is enabled and refresh/reset results --------#
    print $fh <<EOT;

$secStrings{START}{CONST_8}{-1}{0}
T1_bool_t const T1_SEC_CONST_8 T1_fgContEnabled =
#   if defined T1_FG_CONT
    T1_TRUE;
#   else
    T1_FALSE;
#   endif /* defined T1_FG_CONT */
$secStrings{STOP}{CONST_8}{-1}{0}

EOT

#------------------------------------------------------------------------------------#

    print $fh <<EOT;

#   if ! defined T1_CONT_NOF_VRTL_STPWS
#       error T1_CONT_NOF_VRTL_STPWS not defined
#   else /* defined T1_CONT_NOF_VRTL_STPWS */
#       if 8 != T1_CONT_NOF_VRTL_STPWS && 64 != T1_CONT_NOF_VRTL_STPWS
#           error T1_CONT_NOF_VRTL_STPWS must be either 8 or 64
#       endif /* 8 != T1_CONT_NOF_VRTL_STPWS && 64 != T1_CONT_NOF_VRTL_STPWS */
#   endif /* ! defined T1_CONT_NOF_VRTL_STPWS */
#   if !(1 <= T1_CONT_NOF_FOCUS_MEASUREMENTS && T1_CONT_NOF_FOCUS_MEASUREMENTS <= 3)
#       error T1_CONT_NOF_FOCUS_MEASUREMENTS must be between one and three
#   endif /* !(1 <= T1_CONT_NOF_FOCUS_MEASUREMENTS && T1_CONT_NOF_FOCUS_MEASUREMENTS <= 3) */
EOT

    printf $fh <<EOT if $config{'taskIdClash'};
#   if (defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES) || defined T1_FG_CONT
#       error T1 configuration does not support different tasks with the same ID (on different cores)
#   endif /* (defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES) || defined T1_FG_CONT */
EOT

    my $contNofCores = $nOfCores;
    $contNofCores = 1 if $contNofCores <= 0;

    foreach my $coreId ( 0 .. ($contNofCores-1) )
    {
        print $fh <<EOT;

/* Check that static T1 configuration parameters for core $coreId are present */
#   if ! defined T1_TRACEBUFFER_ENTRIES_CORE$coreId
#       error T1_TRACEBUFFER_ENTRIES_CORE$coreId must be defined
#   endif /* ! defined T1_TRACEBUFFER_ENTRIES_CORE$coreId */
#   if ! defined T1_NOF_USER_STPWS_CORE$coreId
#       error T1_NOF_USER_STPWS_CORE$coreId must be defined
#   endif /* ! defined T1_NOF_USER_STPWS_CORE$coreId */
#   if ! defined T1_NOF_FLEX_STPWS_CORE$coreId
#       error T1_NOF_FLEX_STPWS_CORE$coreId must be defined
#   endif /* ! defined T1_NOF_FLEX_STPWS_CORE$coreId */
#   if ! defined T1_NOF_FLEX_ADDRS_CORE$coreId
#       error T1_NOF_FLEX_ADDRS_CORE$coreId must be defined
#   endif /* ! defined T1_NOF_FLEX_ADDRS_CORE$coreId */
#   if ! defined T1_NOF_TASKS_CORE$coreId
#       error T1_NOF_TASKS_CORE$coreId must be defined
#   endif /* ! defined T1_NOF_TASKS_CORE$coreId */
#   if ! defined T1_NOF_CSRNS_CORE$coreId
#       error T1_NOF_CSRNS_CORE$coreId must be defined
#   endif /* ! defined T1_NOF_CSRNS_CORE$coreId */
#   if ! defined T1_MAX_TASK_PREEMPTIONS_CORE$coreId
#       error T1_MAX_TASK_PREEMPTIONS_CORE$coreId must be defined
#   endif /* ! defined T1_MAX_TASK_PREEMPTIONS_CORE$coreId */
#   if ! defined T1_OVERHEAD_CORE${coreId}_NS
#       error T1_OVERHEAD_CORE${coreId}_NS must be defined
#   endif /* T1_OVERHEAD_CORE${coreId}_NS */
#   if ! defined T1_FLEX_OVERHEAD_CORE${coreId}_NS
#       error T1_FLEX_OVERHEAD_CORE${coreId}_NS must be defined
#   endif /* T1_FLEX_OVERHEAD_CORE${coreId}_NS */
#   if ! defined T1_CPULOAD_TX_PERIOD_CORE$coreId
#       error T1_CPULOAD_TX_PERIOD_CORE$coreId must be defined
#   endif /* T1_CPULOAD_TX_PERIOD_CORE$coreId */
#   if ! defined T1_CPULOAD_SAMPLES_CORE$coreId
#       error T1_CPULOAD_SAMPLES_CORE$coreId must be defined
#   endif /* T1_CPULOAD_SAMPLES_CORE$coreId */

/* Check limits of T1 configuration parameters for core $coreId */
#   if 65535 < T1_TRACEBUFFER_ENTRIES_CORE$coreId
#       error Only up to 65535 trace buffer entries are allowed per core
#   endif /* 65535 < T1_TRACEBUFFER_ENTRIES_CORE$coreId */
#   if 255 < T1_NOF_USER_STPWS_CORE$coreId + T1_NOF_FLEX_STPWS_CORE$coreId + T1_CONT_NOF_VRTL_STPWS
#       error Only up to 255 stopwatches are allowed per core
#   endif /* 255 < T1_NOF_USER_STPWS_CORE$coreId + T1_NOF_FLEX_STPWS_CORE$coreId + T1_CONT_NOF_VRTL_STPWS */
#   if 255 < T1_NOF_FLEX_ADDRS_CORE$coreId
#       error Only up to 255 T1.flex address buffer entries are allowed per core
#   endif /* 255 < T1_NOF_FLEX_ADDRS_CORE$coreId */
#   if 1024 < T1_NOF_TASKS_CORE$coreId
#       error Only up to 1024 tasks and ISRs are allowed per core
#   endif /* 1024 < T1_NOF_TASKS_CORE$coreId */
#   if 64 < T1_NOF_CSRNS_CORE$coreId
#       error Only up to 64 constraints are allowed per core
#   endif /* 64 < T1_NOF_CSRNS_CORE$coreId */
#   if 255 < T1_MAX_TASK_PREEMPTIONS_CORE$coreId
#       error Only up to 255 tasks and ISRs pre-emptions are allowed per core
#   endif /* 255 < T1_MAX_TASK_PREEMPTIONS_CORE$coreId */
#   if T1_NOF_FLEX_ADDRS_CORE$coreId < T1_NOF_FLEX_STPWS_CORE$coreId
#       error Number of T1.flex address buffer entries must be at least the number of T1.flex stopwatches
#   endif /* T1_NOF_FLEX_ADDRS_CORE$coreId < T1_NOF_FLEX_STPWS_CORE$coreId */
#   if ( T1_TRACEBUFFER_ENTRIES_CORE${coreId}_ % ( T1_MAX_TRACE_BUFFER_MSG_BYTES_ / T1_TRACE_ENTRY_BYTES ) == T1_NAMEBUFFER_ENTRIES )
#       error The trace buffer size must be changed for core $coreId by at least 1 with the invocation parameter -traceBufferEntries
#   endif /* ( T1_TRACEBUFFER_ENTRIES_CORE${coreId}_ % ( T1_MAX_TRACE_BUFFER_MSG_BYTES_ / T1_TRACE_ENTRY_BYTES ) == T1_NAMEBUFFER_ENTRIES ) */
#   if 255 < T1_NOF_FLEXBUFFER_ENTRIES_CORE$coreId
#       error Only up to 255 T1.flex buffer entries are allowed per core
#   endif /* 255 < T1_NOF_FLEXBUFFER_ENTRIES_CORE$coreId */
EOT
    }

    print $fh <<EOT;

$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_nOfVrtlStpws = T1_CONT_NOF_VRTL_STPWS;
T1_uint8_t const        T1_SEC_CONST_8 T1_nOfFocusMeasurements = T1_CONT_NOF_FOCUS_MEASUREMENTS;
$secStrings{STOP}{CONST_8}{-1}{0}

$secStrings{START}{CONST_16}{-1}{0}
T1_uint16_t const       T1_SEC_CONST_16 T1_maxNofTasks = T1_MAX_NOF_TASKS;
$secStrings{STOP}{CONST_16}{-1}{0}
EOT

    foreach my $coreId ( 0 .. ($contNofCores-1) )
    {
        print $fh <<EOT;
#   define T1_NOF_RESULTS_CORE$coreId \\
    (T1_NOF_TASKS_CORE$coreId + 2*(T1_NOF_USER_STPWS_CORE$coreId + T1_NOF_FLEX_STPWS_CORE$coreId + T1_CONT_NOF_VRTL_STPWS) + 3u)

#   if ! defined T1_DISABLE_T1_FLEX && T1_NOF_FLEX_STPWS_CORE$coreId < 1
#       error At least one core $coreId T1.flex stopwatch is required
#   endif /* T1_NOF_FLEX_STPWS_CORE$coreId */
EOT
    }

    Sec( $fh, '', -1, 'START', 'VAR_POWER_ON_CLEARED_8' );
    if( $nOfCores <= 0 )
    {
        print $fh <<EOT;
T1_contStatus_t         T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contBgStatus;
T1_contStatus_t         T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contHandlerStatus;
EOT
    }
    else
    {
        print $fh <<EOT;
T1_contStatus_t         T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contBgStatusPC[$nOfCores];
T1_contStatus_t         T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contHandlerStatusPC[$nOfCores];
EOT
    }
    Sec( $fh, '', -1, 'STOP', 'VAR_POWER_ON_CLEARED_8' );

    print $fh <<EOT;
#   if defined T1_FG_CONT
#       define T1_CHECKED_START_SEC_VAR_POWER_ON_CLEARED_32
#       include "T1_MemMap.h"
T1_taskFgData_t         T1_CHECKED_SEC_VAR_POWER_ON_CLEARED_32 T1_taskFgData[T1_MAX_NOF_TASKS];
#       define T1_CHECKED_STOP_SEC_VAR_POWER_ON_CLEARED_32
#       include "T1_MemMap.h"
#   endif /* defined T1_FG_CONT */
EOT

    GenMultiCoreDataStructurePlusElements( $fh, '', $nOfCores, 'T1_contGlobals_t', '32', 'T1_contGlobals', '', '', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_stpwData_t', '32', 'T1_stpwData', 'T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX + T1_CONT_NOF_VRTL_STPWS', $DG );
    print $fh "#   if defined T1_FG_CONT\n";
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_stpwFgData_t', '32_CHECKED', 'T1_stpwFgData', 'T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX + T1_CONT_NOF_VRTL_STPWS', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_csVStpwCache_t', '32_CHECKED', 'T1_contCsVStpwCache', 'T1_NOF_CS_VS', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_vStpwMapping_t', '32_CHECKED', 'T1_vStpw', '2*T1_CONT_NOF_VRTL_STPWS', $DG );
    print $fh "#   else /* !defined T1_FG_CONT */\n";
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_csVStpwCache_t', '32', 'T1_contCsVStpwCache', 'T1_NOF_CS_VS', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_vStpwMapping_t', '32', 'T1_vStpw', '2*T1_CONT_NOF_VRTL_STPWS', $DG );
    print $fh "#   endif /* defined T1_FG_CONT */\n";
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_csrnData_t', '32', 'T1_csrnData', 'T1_NOF_CSRNS_COREXX', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_resultTime_t', '32_CHECKED', 'T1_resultBuffer', '((T1_NOF_RESULTS_COREXX + 0xFu) & ~0xFu) + 1u', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_taskStackElem_t', '32', 'T1_taskStack', 'T1_MAX_TASK_PREEMPTIONS_COREXX+T1_TASK_STACK_OVERRUNS', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_focusData_t', '32', 'T1_focus', 'T1_CONT_NOF_FOCUS_MEASUREMENTS', $DG );
    print $fh "#   if defined T1_WAIT_RESUME\n";
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_taskData_t', '32', 'T1_taskData', 'T1_NOF_TASKS_COREXX', $DG );
    print $fh <<EOT;
#   else /* ! defined T1_WAIT_RESUME */
$secStrings{START}{CONST_32}{-1}{1}
T1_taskData_t     * const T1_SEC_CONST_32 T1_taskDataPC[1] = { T1_NULL };
$secStrings{STOP}{CONST_32}{-1}{1}
#   endif /* defined T1_WAIT_RESUME */
EOT

    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfResultsPC',              'T1_resultsIdx_t', '16', 'T1_NOF_RESULTS_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_overheadPC',                'T1_tick_t',       '16', '(T1_tick_t)T1_NS_TO_TICKS( T1_OVERHEAD_COREXX_NS )', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_flexOverheadPC',            'T1_tick_t',       '16', '(T1_tick_t)T1_NS_TO_TICKS( T1_FLEX_OVERHEAD_COREXX_NS )', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_cpuLoadTxPeriodPC',         'T1_uint16_t',     '16', 'T1_CPULOAD_TX_PERIOD_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_startOfFrameEventPC',       'T1_uint16_t',     '16', '((T1_uint16_t)T1_BSF_EVENT_ID_COREXX << 10) | (T1_uint16_t)(T1_BSF_EVENT_INFO_COREXX & 0x3FFu)', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_defaultAnalysisCapacityPC', 'T1_anaCapa_t',    '16', 'T1_CONT_ANALYSIS_CAPACITY_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfTasksPC',                'T1_taskIdx_t',    '16', 'T1_NOF_TASKS_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_bgTaskIdxPC',               'T1_taskIdx_t',    '16', 'T1_BACKGROUND_TASK_IDX_COREXX', $DG );

    print $fh "#   if ! defined T1_70618\n";
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_38948', 'T1_longTime_t', '32', '0xFFFFFFFFuL', $DG );
    print $fh "#   endif /* ! defined T1_70618 */\n";

    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_avgCPULoadSamplesPC', 'T1_uint8_t',   '8', 'T1_CPULOAD_SAMPLES_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfStpwsPC',          'T1_stpwIdx_t', '8', 'T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX + T1_CONT_NOF_VRTL_STPWS', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfUserStpwsPC',      'T1_stpwIdx_t', '8', 'T1_NOF_USER_STPWS_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfCsrnsPC',          'T1_csrnIdx_t', '8', 'T1_NOF_CSRNS_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfPreemptionsPC',    'T1_uint8_t',   '8', 'T1_MAX_TASK_PREEMPTIONS_COREXX', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_cpuLoadThresholdPC',  'T1_uint8_t',   '8', 'T1_CPULOAD_THRESHOLD_256THS_COREXX', $DG );
    print $fh <<EOT;
#   if defined T1_CONT_DEFAULT_CONFIG_STOPWATCH
$secStrings{START}{CONST_8}{-1}{1}
EOT
    if( @{$config{'userStopWatches'}} )
    {
        my @userStopWatches = @{$config{'userStopWatches'}};

        foreach my $coreId ( 0 .. ($nOfCores-1) )
        {
            my $userStopWatchesPCRef = $userStopWatches[$coreId];
            print $fh <<EOT;
#       if $nOfUserStopwatches[$coreId] != T1_NOF_USER_STPWS_CORE$coreId
#           error T1_NOF_USER_STPWS_CORE$coreId does not match generated configuration
#       endif /* $nOfUserStopwatches[$coreId] != T1_NOF_USER_STPWS_CORE$coreId */
static T1_stpwConfig_t  T1_SEC_CONST_8 T1_stpwConfig${coreId}[$nOfUserStopwatches[$coreId]] =
{
EOT
                foreach my $swIdx ( 0..$nOfUserStopwatches[$coreId]-1 )
                {
                    my $userSWRef = @{$userStopWatchesPCRef}[$swIdx];

                    my $macro = @{$userSWRef->{'perCoreMacro'}}[$coreId];
                    my $type  = $userSWRef->{'type'};
                    my $id    = $userSWRef->{'id'};

                    unless( $id == $swIdx )
                    {
                        die "Error: Something went wrong during generating user stopwatch ID for $macro.\n";
                    }

                    my %userStopWatchTypeLookUp = (
                        CET     => 'T1_CONT_CET_STOPWATCH(           ',
                        DA      => 'T1_CONT_DATA_AGE_STOPWATCH(      ',
                        DEFAULT => 'T1_CONT_DEFAULT_CONFIG_STOPWATCH(',
                        GET     => 'T1_CONT_GET_STOPWATCH(           ',
                    );

                    my $typeMacro = $userStopWatchTypeLookUp{$type};

                    unless( $typeMacro )
                    {
                        die qq(Error: Unexpected user stopwatch type "${type}"\n);
                    }

                    print $fh "    ${typeMacro} ${macro} )," . ( ( defined $userSWRef->{'name'} ) ? ' /* ' . $userSWRef->{'name'} . ' */' : '' ) . "\n";
                }
            print $fh "};\n";
        }

        Sec( $fh, '    ', -1, 'STOP', "CONST_8" );
        GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_stpwConfigPC', 'T1_stpwConfig_t *', '32', 'T1_stpwConfigXX', $DG );
    }
    else
    {
        foreach my $coreId ( 0 .. ($nOfCores-1) )
        {
            print $fh <<EOT;
#       if $nOfUserStopwatches[$coreId] != T1_NOF_USER_STPWS_CORE$coreId
#           error T1_NOF_USER_STPWS_CORE$coreId does not match generated configuration
#       endif /* $nOfUserStopwatches[$coreId] != T1_NOF_USER_STPWS_CORE$coreId */
static T1_stpwConfig_t  T1_SEC_CONST_8 T1_stpwConfig${coreId}[$nOfUserStopwatches[$coreId]] =
{
EOT
            printf $fh ("    " . (join ",\n    ", (map { "T1_CONT_DEFAULT_CONFIG_STOPWATCH( ${_}u )" } ( 0 .. ($nOfUserStopwatches[$coreId]-1) ))) . "\n");
            print $fh "};\n";
        }
        Sec( $fh, '    ', -1, 'STOP', "CONST_8" );
        GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_stpwConfigPC', 'T1_stpwConfig_t *', '32', 'T1_stpwConfigXX', $DG );
    }
    print $fh <<EOT;
#   endif /* defined T1_CONT_DEFAULT_CONFIG_STOPWATCH */
EOT

    print $fh <<EOT;

#   if defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT
$secStrings{START}{CONST_32}{-1}{1}
EOT
    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        print $fh <<EOT;
#       if $nOfConstraints[$coreId] != T1_NOF_CSRNS_CORE$coreId
#           error T1_NOF_CSRNS_CORE$coreId does not match generated configuration
#       endif /* $nOfConstraints[$coreId] != T1_NOF_CSRNS_CORE$coreId */
static T1_csrnData_t const T1_SEC_CONST_32 T1_csrnConfig${coreId}[$nOfConstraints[$coreId]] =
{
EOT
        my @constraintInitializers;

        if( @{$config{'constraints'}} )
        {
            my @constraints = @{$config{'constraints'}};

            foreach my $constraint ( @{$constraints[$coreId]} )
            {
                if( scalar @constraintInitializers >= $nOfConstraints[$coreId] )
                {
                    # This should never happen as it is checked in checkUserSWCsrns too
                    die qq(Error: Still more constraints are defined for system ${coreId} than number of constraints is set to);
                }
                else
                {
                    my $swMacro  = $constraint->{'swMacro'};
                    my $value    = $constraint->{'value'};
                    my $subType  = $constraint->{'subType'};
                    my $siPrefix = uc $constraint->{'siPrefix'};

                    unless( $siPrefix )
                    {
                        # Is in seconds, convert to milliseconds
                        $siPrefix = 'M';
                        $value *= 1000.0;
                    }

                    push @constraintInitializers, "T1_STPW_IDX_CONSTRAINT( ${swMacro}, T1_${siPrefix}S_TO_TICKS_CORE${coreId}( ${value} ), T1_CSRN_${subType} )";
                }
            }
        }

        # Set remaining number of constraints to default value
        push @constraintInitializers, ( 'T1_CONT_DEFAULT_CONFIG_CONSTRAINT' ) x ( $nOfConstraints[$coreId] - scalar @constraintInitializers );

        printf $fh '    ' . ( join ",\n    ", @constraintInitializers ) . "\n";

        print $fh "};\n";
    }
    Sec( $fh, '    ', -1, 'STOP', "CONST_32" );
    GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_csrnConfigPC', 'T1_csrnData_t const *', '32', 'T1_csrnConfigXX', $DG );
    print $fh <<EOT;
#   endif /* defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT */
EOT
    print $fh <<EOT;

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_CONT */
EOT

######################################################################################
### T1.delay                                                                       ###
######################################################################################
    my @nOfDelays = @{$config{'nOfDelays'}};

    print $fh <<EOT;

#if defined T1_ENABLE && ! defined T1_DISABLE_T1_DELAY
EOT

    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfDelaysPC', 'T1_uint8_t', '8', 'T1_NOF_DELAYS_COREXX', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_delay_t', '32', 'T1_delays', 'T1_NOF_DELAYS_COREXX', $DG );
    GenMultiCoreDataStructurePlusElements( $fh, '', $nOfCores, 'T1_delayGlobals_t', '32', 'T1_delayGlobals', 'static', '', $DG );

    print $fh <<EOT;
#   if ! defined T1_DELAY_OVERWRITE_CONFIG
EOT
    Sec( $fh, '    ', -1, 'START', "CONST_32" );

    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        my $nOfDelaysCurrentCore = $nOfDelays[$coreId];
        print $fh <<EOT;
/*!
 * \\brief Array with T1.delay configuration values use by T1_InitDelays() and
 *        T1_InitDelaysPC(), for system ${coreId}.
 */
EOT
        if( $nOfDelaysCurrentCore < 0 )
        {
            # enum can not be used in C preprocessor directives
            print $fh <<EOT;
static T1_delay_t const T1_SEC_CONST_32 T1_delayConfig${coreId}[T1_NOF_DELAYS_CORE$coreId] =
{
EOT
        }
        else
        {
            print $fh <<EOT;
#   if $nOfDelaysCurrentCore != T1_NOF_DELAYS_CORE$coreId
#       error T1_NOF_DELAYS_CORE$coreId does not match generated configuration
#   endif /* $nOfDelaysCurrentCore != T1_NOF_DELAYS_CORE$coreId */
static T1_delay_t const T1_SEC_CONST_32 T1_delayConfig${coreId}[$nOfDelaysCurrentCore] =
{
EOT
        }
        if( @{$config{'delays'}} )
        {
            my $delayRef = $config{'delays'};
            my $delayPCRef = $delayRef->[$coreId];

            foreach my $dlIdx ( 0..$nOfDelaysCurrentCore-1 )
            {
                my $dlRef = @{$delayPCRef}[$dlIdx];

                my $macro = @{$dlRef->{'perCoreMacro'}}[$coreId];
                my $init  = $dlRef->{'init'};
                my $id    = $dlRef->{'id'};

                my ( $value, $siPrefix ) = $init =~ /(\d+)([mun]?)/;

                my $conversionMacro;
                if( $siPrefix )
                {
                    my %siPrefixToMacroLookup = (
                        m => 'T1_MS_TO_TICKS_COREXX',
                        u => 'T1_US_TO_TICKS_COREXX',
                        );
                    $conversionMacro = $siPrefixToMacroLookup{$siPrefix};
                }
                else
                {
                    # Convert s to ms
                    $value = $value * 1000;
                    $conversionMacro = 'T1_MS_TO_TICKS_COREXX';
                }

                my $valueString;
                if( 0 == $value )
                {
                    # Do not use conversion macro for 0 values to avoid compiler warnings:
                    # ctc W587: ["T1_configGen.c"] underflow on constant of type "float"
                    $valueString = '0u';
                }
                else
                {
                    $value = addU( $value );
                    $conversionMacro =~ s/XX/${coreId}/;
                    $valueString = "${conversionMacro}( ${value} )";
                }

                unless( $id == $dlIdx )
                {
                    die "Error: Something went wrong during generating T1.delay IDs (${id} != ${dlIdx}) delay name '$dlRef->{'name'}'.\n";
                }

                $dlIdx = sprintf "%3d", $dlIdx;

                print $fh "    /* ${dlIdx} */ (T1_delay_t)${valueString} /* ${init}s */, /* " . ( ( defined $dlRef->{'name'} ) ? $dlRef->{'name'} : $macro ) . " */\n";
            }
        }
        else
        {
            # Init to 0 for now, if -allocateDL is not used
            my $localNofDelays = abs $nOfDelays[$coreId];
            foreach my $dlIdx ( 0..$localNofDelays-1 )
            {
                $dlIdx = sprintf "%3d", $dlIdx;

                print $fh "    /* ${dlIdx} */ (T1_delay_t)0u /* 0s */,\n";
            }
        }

        print $fh "};\n";
    }

    Sec( $fh, '    ', -1, 'STOP', "CONST_32" );
    print $fh <<EOT;
#   endif /* ! defined T1_DELAY_OVERWRITE_CONFIG */
EOT

    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_delayConfigPC', 'T1_delay_t const *', '32', 'T1_delayConfigXX', $DG );


    print $fh <<EOT;

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_DELAY */
EOT

######################################################################################
### T1.mod                                                                         ###
######################################################################################
    print $fh <<EOT;

#if defined T1_ENABLE && ! defined T1_DISABLE_T1_MOD
EOT

    if( $nOfCores <= 0 )
    {
        print $fh <<EOT;
$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{0}
T1_modGlobals_t         T1_SEC_VAR_POWER_ON_CLEARED_32 T1_modGlobals;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{0}
EOT
    }
    else
    {
        GenMultiCoreDataStructurePlusElements( $fh, '', $nOfCores, 'T1_modGlobals_t', '32', 'T1_modGlobals', 'static', '', $DG );
    }

    print $fh <<EOT;

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_MOD */
EOT

######################################################################################
### T1.flex                                                                        ###
######################################################################################

    print $fh <<EOT;

#if defined T1_ENABLE && ! defined T1_DISABLE_T1_FLEX

$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{0}
T1_uint32_t             T1_SEC_VAR_POWER_ON_CLEARED_32 T1_swdStart;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{0}

EOT

    print $fh <<EOT;
#   if defined T1_TRICORE

EOT
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_flexAddr_t', '32_DCX', 'T1_dcx', 4, $DG );
    GenMultiCoreDataStructure( $fh, '        ', $nOfCores, 'T1_outerHandlerPC', 'T1_pVoidVoid_t', '32', 'T1_OUTER_HANDLER_COREXX', $DG );
    print $fh <<EOT;

#   elif /* ! defined T1_TRICORE && */ defined T1_ARM7R || defined T1_ARM8R
EOT
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_uint32_t', '32', 'T1_abortSP', '', '', $DG );
    my $fpCtrlRev = $config{'cortexMFPBversion'} - 1;
    print $fh <<EOT;

#   elif /* ! defined T1_TRICORE && ! (defined T1_ARM7R || defined T1_ARM8R) && */ defined T1_ARM7M

#       if 0 <= $fpCtrlRev && $fpCtrlRev <= 1
$secStrings{START}{CONST_8}{-1}{0}
/* Flash Patch breakpoint architecture revision: version $config{'cortexMFPBversion'} */
T1_uint8_t const T1_SEC_CONST_8 T1_fpCtrlRev = ${fpCtrlRev}u;
$secStrings{STOP}{CONST_8}{-1}{0}
#       else
#           error Invalid configuration, please check -cortexMFPBversion is 1 or 2
#       endif /* 0 <= $fpCtrlRev && $fpCtrlRev <= 1 */

#   endif /* defined T1_TRICORE / T1_ARM7R / T1_ARM8R / T1_ARM7M */

EOT

    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfAddrsPC', 'T1_uint8_t', '8', 'T1_NOF_FLEX_ADDRS_COREXX', $DG );
    print $fh "#    if defined T1_DISABLE_T1_CONT\n";
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfFlexStpwsPC', 'T1_stpwIdx_t', '8', '255', $DG );
    print $fh "#    else /* ! defined T1_DISABLE_T1_CONT */\n";
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfFlexStpwsPC', 'T1_stpwIdx_t', '8', 'T1_NOF_FLEX_STPWS_COREXX', $DG );
    print $fh "#    endif /* defined T1_DISABLE_T1_CONT */\n";
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_flexAddr_t', '32', 'T1_addrs', 'T1_FLEX_NOF_PRE_ADDRS + T1_NOF_FLEX_ADDRS_COREXX', $DG );
    GenMultiCoreDataStructurePlusElements( $fh, '', $nOfCores, 'T1_flexGlobals_t', '32', 'T1_flexGlobals', '', '', $DG );
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_nOfFlexBufferEntriesPC', 'T1_uint8_t', '8', 'T1_NOF_FLEXBUFFER_ENTRIES_COREXX', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_uint32_t', '32', 'T1_flexBuffer', 'T1_NOF_FLEXBUFFER_ENTRIES_COREXX', $DG );

    print $fh <<EOT;

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_FLEX */
EOT

######################################################################################
### T1.scope                                                                       ###
######################################################################################

    print $fh <<EOT;

#if defined T1_ENABLE && ! defined T1_DISABLE_T1_SCOPE

$secStrings{START}{CONST_32}{-1}{0}
T1_fgContHelpers_t const * const T1_SEC_CONST_32 T1_pFgContHelpers =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    &T1_46828;
#   else
    &T1_91054;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
$secStrings{STOP}{CONST_32}{-1}{0}

#   if defined T1_64BIT_TRACE_ENTRY
#       if 24 != $config{'traceTimeStampBitLength'}
#           error traceTimeStampBitLength should be 24
#       endif /* 24 != $config{'traceTimeStampBitLength'} */
#   else /* ! defined T1_64BIT_TRACE_ENTRY */
#       if 16 != $config{'traceTimeStampBitLength'}
#           error traceTimeStampBitLength should be 16
#       endif /* 16 != $config{'traceTimeStampBitLength'} */
#   endif /* defined T1_64BIT_TRACE_ENTRY */

#   if ! defined T1_SYNC_TIMER_WIDTH_BITS
EOT
    print $fh "#       error T1_SYNC_TIMER_WIDTH_BITS must be defined\n" if 1 < $nOfCores;

    print $fh <<EOT;
#   endif /* ! defined T1_SYNC_TIMER_WIDTH_BITS */
EOT

        print $fh <<EOT if 'true' ne $config{'externalTraceBuffer'};
#   if defined T1_EXTERNAL_TRACEBUFFER
#       error T1_EXTERNAL_TRACEBUFFER defined but -externalTraceBuffer not set to true
#   endif /* defined T1_EXTERNAL_TRACEBUFFER */
EOT

        print $fh <<EOT if 'true' eq $config{'externalTraceBuffer'};
#   if ! defined T1_EXTERNAL_TRACEBUFFER
#       error T1_EXTERNAL_TRACEBUFFER not defined but -externalTraceBuffer set to true
#   endif /* ! defined T1_EXTERNAL_TRACEBUFFER */
EOT

    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        print $fh <<EOT;
#   if ! defined T1_EXTERNAL_TRACEBUFFER && ! defined T1_TRACEBUFFER_ENTRIES_CORE$coreId
#       error T1_TRACEBUFFER_ENTRIES_CORE$coreId not defined
#   endif /* ! defined T1_EXTERNAL_TRACEBUFFER && ! defined T1_TRACEBUFFER_ENTRIES_CORE$coreId */

#   if ! defined T1_PTIMER_CORE$coreId
#define T1_PTIMER_CORE$coreId (0u)
#   endif /* defined T1_PTIMER_CORE$coreId */
EOT
    }
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_syncPeriodPC', 'T1_uint8_t', '8', 'T1_SYNC_PERIOD_COREXX', $DG );
    Gen2DimensionalMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_traceEntry_t T1_FAR', '32_TRACEBUFFER', 'T1_traceBuffer', 'T1_TRACEBUFFER_ENTRIES_COREXX + 1', $DG ) if 'true' ne $config{'externalTraceBuffer'};
    GenMultiCoreDataStructure( $fh, '', $nOfCores, 'T1_traceEntriesPC', 'T1_nOfEntries_t', '16', 'T1_TRACEBUFFER_ENTRIES_COREXX', $DG ) if 'true' ne $config{'externalTraceBuffer'};
    print $fh "#   if defined T1_NAMEBUFFER_ENABLE\n";
    Gen2DimensionalMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_traceEntry_t T1_FAR', '32_TRACEBUFFER', 'T1_nameBuffer', 'T1_NAMEBUFFER_ENTRIES + 1', $DG );
    print $fh <<EOT;
$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{1}
void * T1_SEC_VAR_POWER_ON_CLEARED_32 T1_nameListHandlePC[T1_NOF_CORES];
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{1}
#   endif /* defined T1_NAMEBUFFER_ENABLE */
EOT

    print $fh <<EOT;
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
EOT
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_scopeFgGlobals_t', '32_CHECKED', 'T1_scopeFgGlobals', '', '', $DG );
    GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_scopeGlobalsPC', 'T1_scopeGlobals_t *', '32', '&(T1_scopeFgGlobalsXX._)', $DG );
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_scopeFgConsts_t', '32', 'T1_scopeFgConsts', '', '{ { { (T1_scopeGlobals_t *)&T1_scopeFgGlobalsXX }, T1_traceBufferXX + 1, T1_TRACEBUFFER_ENTRIES_COREXX - 1, T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX, T1_SYNC_TIMER_WIDTH_BITS, T1_TRACE_TIMER_BIT_LENGTH_COREXX, XXu, T1_TRACEBUFFER_ENTRIES_COREXX, (T1_tickUint_t volatile const *)T1_PTIMER_COREXX, (T1_bool_t)T1_TRACE_56BIT_SYNC_TIMER, T1_CONT_NOF_VRTL_STPWS, T1_FG_CONT_ACT_EXTRA_ENTRIES, T1_FAR_TRACE_EVENT_NOSUSP_TIME, T1_FAR_TRACE_UINT32_REST_NOSUSP, T1_FAR_TRACE_UINT56_REST_NOSUSP }, T1_DISPATCH_COREXX, T1_MAX_NOF_TASKS, T1_NOF_USER_STPWS_COREXX, T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX, T1_CONT_NOF_FOCUS_MEASUREMENTS, T1_NOF_CSRNS_COREXX, 0u, (T1_uint32_t)(0uL - T1_NOF_FLEX_STPWS_COREXX), T1_taskFgData, T1_focusXX, T1_stpwFgDataXX, T1_contHandlerStatusPC + XX, T1_FG_DO_V_STPW, T1_resultBufferXX + T1_NOF_TASKS_COREXX, T1_vStpwXX, T1_vStpwXX + T1_CONT_NOF_VRTL_STPWS, T1_contCsVStpwCacheXX, T1_HANDLERS }', $DG ) if 'true' ne $config{'externalTraceBuffer'};
    GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_scopeConstsPC', 'T1_scopeConsts_t *', '32', '&(T1_scopeFgConstsXX._)', $DG );
    print $fh <<EOT;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
EOT
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_scopeGlobals_t', '32_CHECKED', 'T1_scopeGlobals', '', '', $DG );
    GenMultiCoreDataStructurePlusElements( $fh, '    ', $nOfCores, 'T1_scopeConsts_t', '32', 'T1_scopeConsts', '', '{ { &T1_scopeGlobalsXX }, T1_traceBufferXX + 1, T1_TRACEBUFFER_ENTRIES_COREXX - 1, T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX, T1_SYNC_TIMER_WIDTH_BITS, T1_TRACE_TIMER_BIT_LENGTH_COREXX, XXu, T1_TRACEBUFFER_ENTRIES_COREXX, (T1_tickUint_t volatile const *)T1_PTIMER_COREXX, (T1_bool_t)T1_TRACE_56BIT_SYNC_TIMER, 0u, 0u, T1_FAR_TRACE_EVENT_NOSUSP_TIME, T1_FAR_TRACE_UINT32_REST_NOSUSP, T1_FAR_TRACE_UINT56_REST_NOSUSP }', $DG ) if 'true' ne $config{'externalTraceBuffer'};
    print $fh <<EOT;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
#   if defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES
$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{1}
/* Add one extra element as destination for writes with invalid task ID. */
T1_uint32_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_taskAct[T1_MAX_NOF_TASKS+1];
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{1}
#   endif /* defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES */
EOT

    print $fh <<EOT;
$secStrings{START}{CONST_8}{-1}{0}
T1_uint8_t const        T1_SEC_CONST_8 T1_syncTimerWidthBits = T1_SYNC_TIMER_WIDTH_BITS;
$secStrings{STOP}{CONST_8}{-1}{0}
#   if defined T1_DEFN_GET_TASK_NAME
$secStrings{START}{CONST_8}{-1}{1}
T1_char_t const * const T1_SEC_CONST_8 T1_taskNames[T1_MAX_NOF_TASKS] =
{
EOT
    my $maxNofTasks = 0;
    my $lastCoreIndex = $config{'nOfCores'} - 1;
    $lastCoreIndex = 0 if $lastCoreIndex < 0;
    foreach my $coreId ( 0 .. $lastCoreIndex )
    {
        $maxNofTasks = $config{'numberOfTasks'}[$coreId] if $maxNofTasks < $config{'numberOfTasks'}[$coreId];
    }

    foreach my $taskId (0 .. $maxNofTasks-1)
    {
        my $taskName = '';
        $taskName = $config{'taskNames'}->{$taskId} if exists $config{'taskNames'}->{$taskId};
        my $comma = '';
        $comma = ',' unless $taskId == $maxNofTasks-1;
        print $fh "    \"$taskName\"$comma\n";
    }
    print $fh <<EOT;
};
$secStrings{STOP}{CONST_8}{-1}{1}

$secStrings{START}{VAR_POWER_ON_CLEARED_16}{-1}{1}
typedef T1_uint16_t T1_TaskIdListDescriptor_t;
EOT

    my $nOfTaskIdListDescriptors = $lastCoreIndex + 1;
    print $fh "T1_TaskIdListDescriptor_t T1_SEC_VAR_POWER_ON_CLEARED_16 T1_TaskIdListDescriptorPC[$nOfTaskIdListDescriptors];\n";

    print $fh <<EOT;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_16}{-1}{1}

$secStrings{START}{CODE}{-1}{1}
T1_char_t const T1_FARPTR T1_CODE T1_GetTaskName( T1_taskId_t taskId )
{
    if( (T1_taskId_t)T1_MAX_NOF_TASKS <= taskId )
    {
        return T1_NULL;
    }
    return T1_taskNames[taskId];
}

void * T1_CODE T1_InitTaskIdListPC( T1_uint8Least_t coreId )
{
    T1_TaskIdListDescriptor_t * const pTaskIdListDescriptor = T1_TaskIdListDescriptorPC + coreId;
    *pTaskIdListDescriptor = 0u;
    return (void *)pTaskIdListDescriptor;
}

T1_taskId_t T1_CODE T1_GetNextTaskId( void *pHandle )
{
    T1_TaskIdListDescriptor_t * const pTaskIdListDescriptor = (T1_TaskIdListDescriptor_t *)pHandle;
    T1_taskId_t taskId = (T1_taskId_t)*pTaskIdListDescriptor;

    while( taskId < (T1_taskId_t)T1_MAX_NOF_TASKS )
    {
        T1_taskId_t const validTaskId = taskId;
        T1_char_t const T1_FARPTR const pName = T1_GetTaskName( validTaskId );
        ++taskId;
        if( T1_NULL != pName && 0 != pName[0] )
        {
            *pTaskIdListDescriptor = taskId;
            return validTaskId;
        }
    }

    /* All task IDs have been returned. */
    return T1_INVALID_TASK_ID;
}

T1_status_t T1_CODE T1_RewindTaskId( void *pHandle )
{
    T1_TaskIdListDescriptor_t * const pTaskIdListDescriptor = (T1_TaskIdListDescriptor_t *)pHandle;
    T1_taskId_t taskId = (T1_taskId_t)*pTaskIdListDescriptor;

    while( 0 <= --taskId )
    {
        T1_char_t const T1_FARPTR const pName = T1_GetTaskName( taskId );
        if( T1_NULL != pName && 0 != pName[0] )
        {
            *pTaskIdListDescriptor = taskId;
            return T1_OK;
        }
    }
    *pTaskIdListDescriptor = 0u;
    return T1_FAILED;
}

T1_uint32_t T1_CODE T1_GetTaskOsIds( T1_taskId_t taskId, T1_uint32_t const **ppOsIds )
{
    (void)taskId;
    (void)ppOsIds;

    return 0uL;
}

$secStrings{STOP}{CODE}{-1}{1}
#   endif /* defined T1_DEFN_GET_TASK_NAME */

$secStrings{START}{CODE}{-1}{0}
void T1_CODE T1_InitNameBufferNoSuspPC(
#   if defined T1_NAMEBUFFER_ENABLE
    T1_uint8Least_t coreId
#   else /* ! defined T1_NAMEBUFFER_ENABLE */
/* polyspace<MISRA-C3:20.7:Justified:Low> obeying this rule here results in compiler errors */
    T1_UNUSED( T1_uint8Least_t coreId )
#   endif /* defined T1_NAMEBUFFER_ENABLE */
)
{
#   if defined T1_NAMEBUFFER_ENABLE
    T1_nameListHandlePC[coreId] = T1_InitTaskIdListPC( coreId );
#   endif /* defined T1_NAMEBUFFER_ENABLE */
}

T1_uint8_t T1_FARPTR T1_CODE T1_GetNameBufferPC(
#   if defined T1_NAMEBUFFER_ENABLE
    T1_uint8Least_t coreId
#   else /* ! defined T1_NAMEBUFFER_ENABLE */
/* polyspace<MISRA-C3:20.7:Justified:Low> obeying this rule here results in compiler errors */
    T1_UNUSED( T1_uint8Least_t coreId )
#   endif /* defined T1_NAMEBUFFER_ENABLE */
)
{
#   if defined T1_NAMEBUFFER_ENABLE
    T1_uint8Least_t counter;
    T1_uint8Least_t nOfEntriesPerLoop;
    T1_traceEntry_t * const pNameBuffer = T1_nameBufferPC[coreId] + 1;
    void * const pHandle = T1_nameListHandlePC[coreId];
    T1_scopeGlobals_t tmpScopeGlobals;
    T1_scopeConsts_t tmpScopeConsts =
    {
        { &tmpScopeGlobals },
        pNameBuffer,
        T1_NAMEBUFFER_ENTRIES - 1,
        T1_TRUE,
        32u,
        32u,
        coreId,
        T1_NAMEBUFFER_ENTRIES
    };
    T1_taskId_t taskId = T1_GetNextTaskId( pHandle );
    if( T1_INVALID_TASK_ID == taskId )
    {
        return T1_NULL;
    }

    counter = T1_NAMEBUFFER_ENTRIES;
    do
    {
        pNameBuffer[--counter] = 0uL;
    }
    while( 0u != counter );
#       if ! defined T1_CERT_RELEASE
    tmpScopeGlobals.pTraceBuffer = pNameBuffer;
    tmpScopeGlobals.bufferEntriesMinusOne = T1_NAMEBUFFER_ENTRIES - 1;
#       endif /* ! defined T1_CERT_RELEASE */
    tmpScopeGlobals.tB._.wrIdx = T1_NAMEBUFFER_ENTRIES - 1;
    tmpScopeGlobals.compareIdx = T1_NAMEBUFFER_ENTRIES - 1;
    tmpScopeGlobals.compareState = 0u; /* T1_COMPARE_WRAP */

    /* We assume that the data length of one task never overflows the buffer */
    /*
     * Safe with interrupts enabled because T1_TraceNameNoSuspTime_ and
     * T1_TraceOsIdsNoSuspTime_ cannot be pre-empted by code using tmpScopeGlobals
     */
    nOfEntriesPerLoop  = T1_TraceNameNoSuspTime_(  &tmpScopeConsts, taskId, 0uL );
    nOfEntriesPerLoop += T1_TraceOsIdsNoSuspTime_( &tmpScopeConsts, taskId, 0uL );
    counter = T1_NAMEBUFFER_ENTRIES - nOfEntriesPerLoop;
    tmpScopeGlobals.compareState = 2u; /* T1_COMPARE_TRACING_DISABLED */

    while( 0u != counter && T1_INVALID_TASK_ID != (taskId = T1_GetNextTaskId( pHandle )) )
    {
        /*
         * Safe with interrupts enabled because T1_TraceNameNoSuspTime_ and
         * T1_TraceOsIdsNoSuspTime_ cannot be pre-empted by code using tmpScopeGlobals
         */
        nOfEntriesPerLoop  = T1_TraceNameNoSuspTime_(  &tmpScopeConsts, taskId, 0uL );
        nOfEntriesPerLoop += T1_TraceOsIdsNoSuspTime_( &tmpScopeConsts, taskId, 0uL );
        if( nOfEntriesPerLoop <= counter )
        {
            counter -= nOfEntriesPerLoop;
        }
        else
        {
            /*
             * This else-part is executed when T1_nameBufferPC[coreId] overflows.
             * Writing to the buffer did not wrap-around because pCompare is set to
             * the last entry and compareState is set to T1_COMPARE_TRACING_DISABLED.
             * But the last, incomplete entries need to be overwritten with T1_EMPTY.
             */
            if( T1_OK == T1_RewindTaskId( pHandle ) )
            {
                do
                {
                    pNameBuffer[tmpScopeGlobals.tB._.wrIdx--] = 0u;
                }
                while( 0u != --counter );
            }
        }
    }

    return (T1_uint8_t T1_FARPTR)pNameBuffer;

#   else /* ! defined T1_NAMEBUFFER_ENABLE */
    return T1_NULL;
#   endif /* defined T1_NAMEBUFFER_ENABLE */
}

EOT

#---------------------------- T1 Sync To Trace Time ---------------------------------#
    print $fh <<EOT;
/*!
 * \\brief Callout function to translate a duration in synchronization timer ticks to
 *        trace timer ticks.
 * \\param[in] coreId    use the trace timer tick duration for this core
 * \\param[in] getSwTime the GET stopwatch duration to convert
 * \\returns             converted result
 *
 * Translate a duration in synchronization timer ticks to trace timer ticks. This is
 * used as a callout from library code and should not normally be called directly
 * from user code.
 *
 */
T1_longTime_t T1_CODE T1_SyncToTraceTimerPC( T1_uint8Least_t coreId, T1_longTime_t getSwTime )
{
#   if defined T1_SYNC_TO_TRACE_TIME
    (void)coreId;    /* Suppress warnings since coreId is not actually used */
    return T1_SYNC_TO_TRACE_TIME( getSwTime );
#   else /* Different trace timer frequencies on different cores */
    switch( coreId )
    {
    default:    return T1_SYNC_TO_TRACE_TIME_CORE0( getSwTime );
EOT
    foreach my $coreId ( 1 .. ($nOfCores-1) )
    {
        printf $fh "    case %-6s return T1_SYNC_TO_TRACE_TIME_CORE%s( getSwTime );\n", "${coreId}u:", "$coreId";
    }

    print $fh <<EOT;
    }
#   endif /* defined T1_SYNC_TO_TRACE_TIME */
}
$secStrings{STOP}{CODE}{-1}{0}

EOT

#------------------------------------------------------------------------------------#

#---------------------------- T1 Trace To Sync Time ---------------------------------#
    print $fh <<EOT;

$secStrings{START}{CODE_FAST}{-1}{0}
/*!
 * \\brief Callout to translate a duration in trace timer ticks to synchronization timer ticks.
 * \\param[in] coreId    use the trace timer tick duration for this core
 * \\param[in] traceTime the trace timer value to convert
 * \\returns             converted result
 *
 * Translate a value in trace timer ticks to synchronization timer ticks. This is
 * used as a callout from library code and should not normally be called directly
 * from user code.
 *
 */
#if defined T1_GCC_ADAPT
#   undef T1_TraceToSyncTimerPC
T1_CODE_FAST( T1_tickUint_t ) T1_NOINLINE T1_CODE_OPT T1_TraceToSyncTimerPC
                            ( T1_uint8Least_t coreId, T1_tickUint_t traceTime )
{
    return T1_NearTraceToSyncTimerPC( coreId, traceTime );
}
T1_CODE_FAST( T1_uint32_t ) T1_CODE_OPT T1_NearTraceToSyncTimerPC
#else /* ! defined T1_GCC_ADAPT */
T1_CODE_FAST( T1_uint32_t ) T1_CODE_OPT T1_TraceToSyncTimerPC
#endif /* defined T1_GCC_ADAPT */
                            ( T1_uint8Least_t coreId, T1_tickUint_t traceTime )
{
EOT

    if( $config{'allCoresTraceTickDurationNs'} )
    {
        print $fh <<EOT;
    (void)coreId;    /* Suppress warnings since coreId is not actually used */
    return T1_TRACE_TO_SYNC_TIME( traceTime );
EOT
    }
    else # Different ratios on different cores
    {
        print $fh <<EOT;
    switch( coreId )
    {
    default:    return T1_TRACE_TO_SYNC_TIME_CORE0( traceTime );
EOT
        foreach my $coreId ( 1 .. ($nOfCores-1) )
        {
            printf $fh "    case %-6s return T1_TRACE_TO_SYNC_TIME_CORE%s( traceTime );\n", "${coreId}u:", "$coreId";
        }

        print $fh <<EOT;
    }
EOT
    }

    print $fh <<EOT;
}
#   if defined T1_NEAR_CODE_FAST
T1_uint32_t T1_NOINLINE T1_NEAR_CODE_FAST __attribute__((alias("T1_TraceToSyncTimerPC")))
T1_NearTraceToSyncTimerPC( T1_uint8Least_t coreId, T1_tickUint_t traceTime );
#   endif /* defined T1_NEAR_CODE_FAST */
EOT

#------------------------------------------------------------------------------------#

#------------T1_SWStopNoSusp__ and T1_TraceToSyncNoSusp__ ---------------------------#

    print $fh <<EOT;

#   if defined __ghs__
/* Green Hills __noinline keyword can be disabled, so use the pragma instead. */
#       pragma ghs startnoinline
#   endif /* defined __ghs__ */

T1_CODE_FAST( void ) T1_NOINLINE T1_CODE_OPT
T1_SWStopNoSusp__( T1_scopeConsts_t    *pScopeConsts,
                   T1_eventInfo_t       eventInfo,
                   T1_uint32_t          syncData )
{
    T1_SWStopNoSuspTime__(  pScopeConsts,
                            syncData,
                            T1_NearTraceEventNoSusp__( pScopeConsts, eventInfo ) );
}

#if defined T1_NEAR_CODE_FAST
void T1_NOINLINE T1_NEAR_CODE_FAST T1_CODE_OPT __attribute__((alias("T1_SWStopNoSusp__")))
T1_NearSWStopNoSusp__( T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_uint32_t syncData );
#endif /* defined T1_NEAR_CODE_FAST */

T1_CODE_FAST( void ) T1_NOINLINE T1_CODE_OPT
T1_SWStopNoSuspTime__(  T1_scopeConsts_t   *pScopeConsts,
                        T1_uint32_t         syncData,
                        T1_tickUint_t       traceTime   )
{
    T1_uint32_t syncTime;
#   if T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER && 28 <= T1_SYNC_TIMER_WIDTH_BITS
    syncTime = traceTime;
#   else /* ! T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER || T1_SYNC_TIMER_WIDTH_BITS < 28 */
#       if T1_ANY_TRACE_TIMER_IS_SYNC_TIMER && 28 <= T1_SYNC_TIMER_WIDTH_BITS
    if( pScopeConsts->syncTimerIsTraceTimer )
    {
        syncTime = traceTime;
    }
    else
#       endif /* T1_ANY_TRACE_TIMER_IS_SYNC_TIMER && 28 <= T1_SYNC_TIMER_WIDTH_BITS */
    {
        T1_tickUint_t const traceTimerBase = pScopeConsts->_.pScopeGlobals->_.traceTime;
        T1_uint32_t const syncTimerBase = pScopeConsts->_.pScopeGlobals->_.syncTime;
        T1_tickUint_t const traceTimerDelta = traceTime - traceTimerBase;
        syncTime = syncTimerBase +
#       if defined T1_TRACE_TO_SYNC_TIME
                            T1_TRACE_TO_SYNC_TIME( traceTimerDelta );
#       elif 28 <= T1_SYNC_TIMER_WIDTH_BITS /* Cannot be a sync timer */
                            T1_TRACE_TO_NOT_SYNC_TIME_PC( pScopeConsts->coreId, traceTimerDelta );
#       else /* Can be a sync timer */
                            T1_TRACE_TO_SYNC_TIME_PC( pScopeConsts->coreId, traceTimerDelta );
#       endif /* defined T1_TRACE_TO_SYNC_TIME */
    }
#   endif /* T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER && 28 <= T1_SYNC_TIMER_WIDTH_BITS */

#   if defined T1_CONT_REMOTE
    (void)T1_NearTraceUint32RestNoSuspRC
#   elif defined T1_FG_CONT
    (void)T1_NearTraceUint32RestNoSuspFg
#   else
    (void)T1_NearTraceUint32RestNoSusp
#   endif /* defined T1_CONT_REMOTE */
                (   pScopeConsts,
                    T1_TRUNC_SYNC_DATA( (syncTime << 4) - syncData ) );
}

#if defined T1_NEAR_CODE_FAST
void T1_NOINLINE T1_NEAR_CODE_FAST T1_CODE_OPT __attribute__((alias("T1_SWStopNoSuspTime__")))
T1_NearSWStopNoSuspTime__( T1_scopeConsts_t *pScopeConsts, T1_uint32_t syncData, T1_tickUint_t traceTime );
#endif /* defined T1_NEAR_CODE_FAST */

#   if defined __ghs__
#       pragma ghs endnoinline
#   endif /* defined __ghs__ */

#   if ! T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER || T1_SYNC_TIMER_WIDTH_BITS < 32
T1_CODE_FAST( T1_uint32_t ) T1_CODE_OPT
T1_TraceToSyncNoSusp__( T1_scopeConsts_t *pScopeConsts, T1_tickUint_t traceTime )
{
#       if T1_ANY_TRACE_TIMER_IS_SYNC_TIMER && 32 <= T1_SYNC_TIMER_WIDTH_BITS
    if( pScopeConsts->syncTimerIsTraceTimer )
    {
        return (T1_uint32_t)traceTime;
    }
#       endif /* T1_ANY_TRACE_TIMER_IS_SYNC_TIMER && 32 <= T1_SYNC_TIMER_WIDTH_BITS */
    {
        T1_tickUint_t const traceTimerDelta = traceTime
                                        - pScopeConsts->_.pScopeGlobals->_.traceTime;
        T1_uint32_t const syncTimerBase = pScopeConsts->_.pScopeGlobals->_.syncTime;
        return syncTimerBase +
#       if defined T1_TRACE_TO_SYNC_TIME
                            T1_TRACE_TO_SYNC_TIME( traceTimerDelta );
#       elif 28 <= T1_SYNC_TIMER_WIDTH_BITS /* Cannot be a sync timer */
                            T1_TRACE_TO_NOT_SYNC_TIME_PC( pScopeConsts->coreId, traceTimerDelta );
#       else /* Can be a sync timer */
                            T1_TRACE_TO_SYNC_TIME_PC( pScopeConsts->coreId, traceTimerDelta );
#       endif /* defined T1_TRACE_TO_SYNC_TIME */
    }
}
#   endif /* ! T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER || T1_SYNC_TIMER_WIDTH_BITS < 32 */

#   if T1_TRACE_56BIT_SYNC_TIMER
T1_CODE_FAST( void ) T1_TraceSync56RestNoSusp( T1_scopeConsts_t *pScopeConsts,
                                               T1_tickUint_t traceTime )
{
    T1_tickUint_t const traceTimerDelta = traceTime
                                    - pScopeConsts->_.pScopeGlobals->_.traceTime;
    T1_uint64_t const syncTimerBase =
        pScopeConsts->_.pScopeGlobals->_.syncTime
        | ( (T1_uint64_t)( pScopeConsts->_.pScopeGlobals->syncTimeHigh ) << 32 );
    T1_uint64_t const syncTimer = syncTimerBase +
#   if defined T1_TRACE_TO_SYNC_TIME
                        T1_TRACE_TO_SYNC_TIME( traceTimerDelta );
#   elif 28 <= T1_SYNC_TIMER_WIDTH_BITS /* Cannot be a sync timer */
                        T1_TRACE_TO_NOT_SYNC_TIME_PC( pScopeConsts->coreId, traceTimerDelta );
#   else /* Can be a sync timer */
                        T1_TRACE_TO_SYNC_TIME_PC( pScopeConsts->coreId, traceTimerDelta );
#   endif /* defined T1_TRACE_TO_SYNC_TIME */
    (void)T1_NEAR_TRACE_UINT56_REST_NOSUSP( pScopeConsts,
                                            (T1_uint32_t)syncTimer,
                                            (T1_uint32_t)( syncTimer >> 32 ) );
}
#   endif /* T1_TRACE_56BIT_SYNC_TIMER */

$secStrings{STOP}{CODE_FAST}{-1}{0}
EOT

#------------------------------------------------------------------------------------#

#---------------------------- T1_FG_CONT Dispatchers --------------------------------#
    print $fh <<EOT;

#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
#       if 1 == T1_NOF_CORES || (defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME)
$secStrings{START}{CODE_FAST}{-1}{2}
T1_CODE_FAST( T1_tickUint_t ) T1_CODE_OPT T1_Dispatch0( T1_scopeFgConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_uint8Least_t handlerIdx )
{
    T1_tickUint_t const traceTime = T1_RAW_TO_TRACE_TIME_UNMASKED_CORE0( T1_GET_RAW_TIME_CORE0( ) );
    T1_DISPATCH_PC( 0, pScopeConsts, eventInfo, traceTime, handlerIdx, pScopeGlobals->cpuLoadMultiplier_, 16 < T1_TRACE_TIMER_BIT_LENGTH_CORE0, Near );
}
$secStrings{STOP}{CODE_FAST}{-1}{2}
EOT
    print $fh "#       else /* 1 != T1_NOF_CORES && (! defined T1_GET_RAW_TIME || ! defined T1_RAW_TO_TRACE_TIME) */\n";
    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        print $fh <<EOT;
$secStrings{START}{CODE}{$coreId}{2}
T1_CODE_FAST( T1_tickUint_t ) T1_CODE_OPT T1_Dispatch$coreId( T1_scopeFgConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_uint8Least_t handlerIdx )
{
    T1_tickUint_t const traceTime = T1_RAW_TO_TRACE_TIME_UNMASKED_CORE$coreId( T1_GET_RAW_TIME_CORE$coreId( ) );
    T1_DISPATCH_PC( $coreId, pScopeConsts, eventInfo, traceTime, handlerIdx, pScopeGlobals->cpuLoadMultiplier_, 16 < T1_TRACE_TIMER_BIT_LENGTH_CORE$coreId, Near );
}
$secStrings{STOP}{CODE}{$coreId}{2}

EOT
    }

    print $fh <<EOT;
#       endif /* 1 == T1_NOF_CORES || (defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME) */

$secStrings{START}{CODE}{-1}{1}
EOT
    if( 1 == $nOfCores )
    {
        print $fh <<EOT;
/* polyspace<MISRA-C3:20.7:Justified:Low> obeying this rule here results in compiler errors */
T1_tickUint_t T1_CODE T1_DispatchTimePC( T1_UNUSED( T1_uint8Least_t coreId ), T1_eventInfo_t eventInfo, T1_uint8Least_t handlerIdx, T1_tickUint_t now )
{
    T1_scopeFgConsts_t * const pScopeConsts = T1_CORE_ID_TO_SCOPE_FG_CONSTS( 0 );
    T1_DISPATCH_PC( 0, pScopeConsts, eventInfo, now, handlerIdx, pScopeGlobals->cpuLoadMultiplier_, 16 < T1_TRACE_TIMER_BIT_LENGTH_CORE0, );
}
EOT
    }
    else
    {
        print $fh <<EOT;
T1_tickUint_t T1_CODE T1_DispatchTimePC( T1_uint8Least_t coreId, T1_eventInfo_t eventInfo, T1_uint8Least_t handlerIdx, T1_tickUint_t now )
{
    T1_scopeFgConsts_t *pScopeConsts;
    switch( coreId )
    {
    default:    /* Do nothing in the event of an invalid coreId parameter. */ return 0uL;
EOT
        foreach my $coreId ( 0 .. ($nOfCores-1) )
        {
            print $fh <<EOT
    case ${coreId}u:
        pScopeConsts = T1_CORE_ID_TO_SCOPE_FG_CONSTS( $coreId );
        T1_DISPATCH_PC( $coreId, pScopeConsts, eventInfo, now, handlerIdx, pScopeGlobals->cpuLoadMultiplier_, 16 < T1_TRACE_TIMER_BIT_LENGTH_CORE$coreId, );
EOT
        }
        print $fh "    }\n}\n";
    }
    print $fh <<EOT;
$secStrings{STOP}{CODE}{-1}{1}

EOT
    print $fh <<EOT;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

EOT
#------------------------------------------------------------------------------------#

#------------------------- T1_FG_CONT test support code -----------------------------#

    print $fh <<EOT;

#   if ! defined T1_DISABLE_T1_SCOPE
$secStrings{START}{CODE}{-1}{1}
void T1_CODE
T1_TraceScopeUploadNoSuspTime__( T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_tickUint_t now )
{
#       if defined T1_FG_CONT && defined T1_TEST_ONLY
    T1_TraceScopeUploadNoSuspTimeIntern( (T1_scopeFgConsts_t *)pScopeConsts, eventInfo, now );
#       else /* ! defined T1_FG_CONT || ! defined T1_TEST_ONLY */
    (void)T1_FAR_TRACE_EVENT_NOSUSP_TIME( pScopeConsts, eventInfo, now );
#       endif /* defined T1_FG_CONT && defined T1_TEST_ONLY */
}
$secStrings{STOP}{CODE}{-1}{1}
#   endif /* defined T1_DISABLE_T1_SCOPE */

EOT

#------------------------------------------------------------------------------------#

#-------------------------- T1_FG_CONT Init and Calibration -------------------------#
    my $inlineActivationCount = 2; # Only supported value
    my $taskActExtraTotal = 0;

    print $fh <<EOT;
#   if defined T1_64BIT_TRACE_ENTRY && defined T1_CPU64BIT
#       define ALIGN    0uL,
#   elif ! defined T1_64BIT_TRACE_ENTRY && (defined T1_CPU32BIT || defined T1_CPU64BIT)
#       define ALIGN    0u,
#   else
#       define ALIGN
#   endif

EOT

    foreach my $coreId ( 0 .. ($nOfCores-1) )
    {
        print $fh <<EOT
#   define T1_INIT_FG_CONT_SCOPE_CORE$coreId                                        \\
{                                                                                   \\
    (T1_uint16_t)T1_NS_TO_TICKS_CORE${coreId}( T1_OVERHEAD_CORE${coreId}_NS ),      \\
    (T1_uint16_t)(T1_NS_TO_TICKS_CORE${coreId}( T1_FLEX_OVERHEAD_CORE${coreId}_NS ) + T1_NS_TO_TICKS_CORE${coreId}( T1_OVERHEAD_CORE${coreId}_NS )), \\
    (T1_uint16_t)(T1_NS_TO_TICKS_CORE${coreId}( T1_FLEX_OVERHEAD_CORE${coreId}_NS ) >> 1), \\
    (T1_uint16_t)0u,                                                                \\
    T1_BSF_EVENT_TO_MASK( T1_BSF_EVENT_ID_CORE$coreId ),                            \\
    ALIGN                                                                           \\
    T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE$coreId, T1_BSF_EVENT_INFO_CORE$coreId ) \\
}
EOT
    }

    print $fh "#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT\n";
    GenMultiCoreDataStructure( $fh, '    ', $nOfCores, 'T1_initFgContScopePC', 'T1_scopeFgGlobalsInit_t', '32', 'T1_INIT_FG_CONT_SCOPE_COREXX', $DG );
    print $fh <<EOT;
$secStrings{START}{CONST_32}{-1}{0}
T1_taskFgInitData_t const T1_SEC_CONST_32 T1_initFgContTasks[T1_MAX_NOF_TASKS] =
{
EOT
    foreach my $taskId ( 0 .. ($maxNofTasks-1) )
    {
        my $comma = ',';
        $comma = '' if $taskId == $maxNofTasks-1; # Not for last array element
        my $taskType = 'T1_TT_ALL_CORE_ID << 1';
        my $taskActExtra = 0;
        if( exists $config{'taskData'}{$taskId} )
        {
            my %taskData = %{$config{'taskData'}{$taskId}};
            $taskType = $taskData{'coreId'};
            $taskType = 15 if $taskType eq 'all';
            $taskType <<= 1; # Shift to make space for T1_TT_FG_TASK
            $taskType = sprintf "0x%02Xu", $taskType;
            $taskType = "T1_TT_FG_TASK | " . $taskType unless $taskData{'isBg'};
            my $actDataExtra = '';
            if( defined $taskData{'maxAct'} and 1 < $taskData{'maxAct'} )
            {
                my $actCountLog2 = ceil( ( log $taskData{'maxAct'} ) / ( log 2 ) );
                # Task with 2 activations actually gets 4 slots
                --$actCountLog2 if 1 < $actCountLog2;
                $taskType = "(${actCountLog2}u << T1_TT_MULTI_ACT_SHIFT) | " . $taskType;
                if( $inlineActivationCount < $taskData{'maxAct'} )
                {
                    $taskActExtra = 2 << $actCountLog2;
                }
            }
        }
        print $fh <<EOT;
    {
        $taskType,
        0u,
        ${taskActExtraTotal}u
    }$comma
EOT
        $taskActExtraTotal += $taskActExtra;
    }
    $taskActExtraTotal = 1 if 0 == $taskActExtraTotal; # C does not support an array of size zero

    print $fh <<EOT;
};
$secStrings{STOP}{CONST_32}{-1}{0}

#       define T1_CHECKED_START_SEC_VAR_POWER_ON_CLEARED_32
#       include "T1_MemMap.h"
T1_uint32_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_actExtra[T1_FG_CONT_ACT_EXTRA_ENTRIES];
#       define T1_CHECKED_STOP_SEC_VAR_POWER_ON_CLEARED_32
#       include "T1_MemMap.h"

#   endif /* if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_SCOPE */
EOT

######################################################################################
### T1.flex handler tables with and without foreground T1.cont                     ###
######################################################################################

my $codeBpHandlersFg    = 1 == $config{'cortexMFPBversion'} ? 'T1_00885' : 'T1_02986';
my $codeBpHandlers      = 1 == $config{'cortexMFPBversion'} ? 'T1_23656' : 'T1_00483';
my $dataBpHandlersFg    = 1 == $config{'cortexMFPBversion'} ? 'T1_95477' : 'T1_96945';
my $dataBpHandlers      = 1 == $config{'cortexMFPBversion'} ? 'T1_23656' : 'T1_36799';
my $dataBpHandlers1     = 1 == $config{'cortexMFPBversion'} ? 'T1_42046' : 'T1_20315';
my $swHandlersFg        = 1 == $config{'cortexMFPBversion'} ? 'T1_55015' : 'T1_51501';
my $swHandlers          = 1 == $config{'cortexMFPBversion'} ? 'T1_73409' : 'T1_61319';
my $teHandlerFg         = 1 == $config{'cortexMFPBversion'} ? 'T1_15112' : 'T1_11056';
my $teHandler           = 1 == $config{'cortexMFPBversion'} ? 'T1_30318' : 'T1_11338';
my $ncaMaybeStoreAddrFg = 1 == $config{'cortexMFPBversion'} ? 'T1_40585' : 'T1_15052';
my $ncaMaybeStoreAddr   = 1 == $config{'cortexMFPBversion'} ? 'T1_57687' : 'T1_93425';
my $cftMaybeStoreAddrFg = 1 == $config{'cortexMFPBversion'} ? 'T1_35804' : 'T1_84306';
my $cftMaybeStoreAddr   = 1 == $config{'cortexMFPBversion'} ? 'T1_20590' : 'T1_35035';

    print $fh <<EOT;
#if defined T1_ENABLE && ! defined T1_DISABLE_T1_FLEX
$secStrings{START}{CONST_32}{-1}{0}
void (* const (* const T1_pCodeBpHandlers)[T1_NOF_CODE_BP_HANDLERS])( T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32 =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    &$codeBpHandlersFg;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    &$codeBpHandlers;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

void (* const (* const T1_pDataBpHandlers)[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS])( T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32 =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    &$dataBpHandlersFg;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
#       if 1 == T1_NOF_CORES
    &$dataBpHandlers1;
#       else /* 1 < T1_NOF_CORES */
    &$dataBpHandlers;
#       endif /* 1 == T1_NOF_CORES */
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

void (* const (* const T1_pSwHandlers)[T1_NOF_SW_HANDLERS])( T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32 =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    &$swHandlersFg;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    &$swHandlers;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

void (* const T1_pHandlerTraceEvent)( T1_uint8Least_t coreId, T1_uint32_t val ) T1_SEC_CONST_32 =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    $teHandlerFg;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    $teHandler;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

void (* const T1_pNcaMaybeStoreCodeAddress)( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr ) T1_SEC_CONST_32 =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    $ncaMaybeStoreAddrFg;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    $ncaMaybeStoreAddr;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */

void (* const T1_pCftMaybeStoreCodeAddress)( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr ) T1_SEC_CONST_32 =
#   if defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT
    $cftMaybeStoreAddrFg;
#   else /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    $cftMaybeStoreAddr;
#   endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
$secStrings{STOP}{CONST_32}{-1}{0}

$secStrings{START}{VAR_POWER_ON_CLEARED_32}{-1}{0}
void (*T1_pMaybeStoreCodeAddress)( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr ) T1_SEC_VAR_POWER_ON_CLEARED_32;
$secStrings{STOP}{VAR_POWER_ON_CLEARED_32}{-1}{0}

EOT

######################################################################################
### T1.flex Tricore-specific trap class3 user handler table                        ###
######################################################################################

    print $fh "#   if defined T1_TRICORE\n";

    my %trapCls3UserHandlerSet = (); # temporary hash used to prevent duplicated extern declaration
    foreach my $trapCls3UserHandler ( @{$config{'trapCls3UserHandler'}} )
    {
        if( $trapCls3UserHandler and not exists $trapCls3UserHandlerSet{$trapCls3UserHandler} )
        {
            $trapCls3UserHandlerSet{$trapCls3UserHandler} = 1;
            print $fh "void $trapCls3UserHandler( void );\n";
        }
    }

    print $fh <<EOT;
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
void (* const T1_pAppContextManagementHandlerPC[T1_NOF_CORES])( void ) T1_SEC_CONST_32 =
{
EOT
    foreach my $coreId ( 0..$nOfCores-1 )
    {
        my $comma = ( $coreId == $nOfCores-1 ) ? '' : ',';
        my $userHandler = $config{'trapCls3UserHandler'}[$coreId] ? $config{'trapCls3UserHandler'}[$coreId] : 'T1_NULL';
        print $fh "    $userHandler$comma\n";
    }
    print $fh <<EOT;
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   endif /* defined T1_TRICORE */
EOT
    print $fh <<EOT;
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_FLEX */
EOT

######################################################################################
### Integration check                                                              ###
######################################################################################

    if( $checkIntegration eq 'true' )
    {
        print $fh <<EOT;

#if defined T1_ENABLE
#   if ! defined T1_CHECK_INTEGRATION
#       error Expected T1_CHECK_INTEGRATION to be defined with the invocation file parameter -checkIntegration enabled
#   endif /* ! defined T1_CHECK_INTEGRATION */
EOT

        GenMultiCoreDataStructurePlusElements( $fh, '', $nOfCores, 'T1_uint8_t', '8', 'T1_checkIntegration', 'static', '', $DG );

        print $fh <<EOT;
#endif /* defined T1_ENABLE */
EOT
    }
    return $taskActExtraTotal;
}

######################################################################################
# sub EqualF compare two floating point numbers for approximate equality
######################################################################################

# Input:
#   x
#   y
sub EqualF($$)
{
    my $x = shift;
    my $y = shift;
    return abs($x - $y) < 0.000000001;
}

######################################################################################
# sub GCD find the approximate greatest common divisor of two floating point values
######################################################################################

# Input:
#   x
#   y
sub GCD($$);
sub GCD($$)
{
    my $x = shift;
    my $y = shift;
    return GCD( $y, $x )    if $y < $x;
    return $y               if EqualF( 0, $x );
    return GCD( $y - int($y / $x) * $x, $x );
}

######################################################################################
# sub GetConverter returns a C expression to convert between two clock speeds
######################################################################################

# Input:
#   tick duration of input
#   tick duration of output
#   32-bit symbol with which to reference the input
#   number of counting bits in symbol - higher bits must be masked off
sub GetConverter($$$$)
{
    my $fromNsText = shift;
    my $toNsText = shift;
    my $sym = shift;
    $sym = "($sym)";
    my $countingBits = shift;
    my $nonCountingBits = 32 - $countingBits;
    my $nonCountingBitsPlus32 = 32 + $nonCountingBits;
    my $nonCountingBitsPlus33 = 33 + $nonCountingBits;
    my $nonCountingBitsPlus34 = 34 + $nonCountingBits;
    my $nonCountingBitsPlus35 = 35 + $nonCountingBits;
    my $nonCountingBitsPlus36 = 36 + $nonCountingBits;
    my $nonCountingBitsAbove1 = 0; $nonCountingBitsAbove1 = $nonCountingBits - 1 if 1 < $nonCountingBits;
    my $nonCountingBitsAbove2 = 0; $nonCountingBitsAbove2 = $nonCountingBits - 2 if 2 < $nonCountingBits;
    my $nonCountingBitsAbove3 = 0; $nonCountingBitsAbove3 = $nonCountingBits - 3 if 3 < $nonCountingBits;
    my $nonCountingBitsAbove4 = 0; $nonCountingBitsAbove4 = $nonCountingBits - 4 if 4 < $nonCountingBits;
    my $nonCountingBitsAbove5 = 0; $nonCountingBitsAbove5 = $nonCountingBits - 5 if 5 < $nonCountingBits;

    my $fromNs = eval "$fromNsText";
    my $toNs = eval "$toNsText";

    # Conversion ratio is $fromNs / $toNs
    my $ratioNumerator = $fromNs;
    my $ratioDenominator = $toNs;

    # Normalize fraction so that any run-time division is by a small integer
    my $gcd = GCD( $ratioNumerator, $ratioDenominator);
    $ratioNumerator /= $gcd;
    $ratioDenominator /= $gcd;

    # Correct for (hopefully tiny) rounding errors
    $ratioNumerator = int( $ratioNumerator + 0.5 );
    $ratioDenominator = int( $ratioDenominator + 0.5 );

    my $ratio = $ratioNumerator / $ratioDenominator;

    # A selection of optimized special cases, subject to periodic review
    # For division by a constant, see Hacker's Delight.
    # There used to be an on-line calculator for all these magic numbers but it has
    # been taken down.
    # Arguments to T1_MULT_U32_U32_U32 are $sym, magic number, bit 33 of magic number, shift+32
    return "($sym << $nonCountingBits) >> (5 + $nonCountingBits)"                                                                                                                                        if EqualF(  1 / 32, $ratio );
    return "($sym << $nonCountingBits) >> (4 + $nonCountingBits)"                                                                                                                                        if EqualF(  1 / 16, $ratio );
    return "T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus35 )"                                                                                                    if EqualF(  1 / 12, $ratio );
    return "($sym << $nonCountingBits) >> (3 + $nonCountingBits)"                                                                                                                                        if EqualF(  1 /  8, $ratio );
    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) + (($sym & (0xFFFFFFFFuL >> $nonCountingBits)) >> 1)) >> 3"                                                                                     if EqualF(  3 / 16, $ratio );
    return "T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0x24924925uL, 1, $nonCountingBitsPlus35 )"                                                                                                    if EqualF(  1 /  7, $ratio );
    return "T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus34 )"                                                                                                    if EqualF(  1 /  6, $ratio );
    return "T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xCCCCCCCDuL, 0, $nonCountingBitsPlus34 )"                                                                                                    if EqualF(  1 /  5, $ratio );
    return "($sym << $nonCountingBits) >> (2 + $nonCountingBits)"                                                                                                                                        if EqualF(  1 /  4, $ratio );
    return "T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus33 )"                                                                                                    if EqualF(  1 /  3, $ratio );
    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) + (($sym & (0xFFFFFFFFuL >> $nonCountingBits)) >> 1)) >> 2"                                                                                     if EqualF(  3 /  8, $ratio );
    return "($sym << $nonCountingBits) >> (1 + $nonCountingBits)"                                                                                                                                        if EqualF(  1 /  2, $ratio );
    return "T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus32 )"                                                                                                    if EqualF(  2 /  3, $ratio );
    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) + (($sym & (0xFFFFFFFFuL >> $nonCountingBits)) >> 1)) >> 1"                                                                                     if EqualF(  3 /  4, $ratio );
    return "($sym << $nonCountingBits) >> $nonCountingBits"                                                                                                                                              if EqualF(  1 /  1, $ratio );
    return "(($sym << $nonCountingBits) >> $nonCountingBits) + T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus33 )"                                                 if EqualF(  4 /  3, $ratio );
    return "($sym & (0xFFFFFFFFuL >> $nonCountingBits)) + (($sym & (0xFFFFFFFFuL >> $nonCountingBits)) >> 1)"                                                                                            if EqualF(  3 /  2, $ratio );
    return "($sym << (1 + $nonCountingBitsAbove1)) >> $nonCountingBitsAbove1"                                                                                                                            if EqualF(  2     , $ratio );
    return "(($sym << (1 + $nonCountingBitsAbove1)) >> $nonCountingBitsAbove1) + T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus32 )"                               if EqualF(  8 /  3, $ratio );
    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) << 1) + ($sym & (0xFFFFFFFFuL >> $nonCountingBits))"                                                                                            if EqualF(  3     , $ratio );
    return "($sym << (2 + $nonCountingBitsAbove2)) >> $nonCountingBitsAbove2"                                                                                                                            if EqualF(  4     , $ratio );
    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) << 2) + ($sym & (0xFFFFFFFFuL >> $nonCountingBits))"                                                                                            if EqualF(  5     , $ratio );
    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) << 2) + ($sym & (0xFFFFFFFFuL >> $nonCountingBits)) + T1_MULT_U32_U32_U32( $sym << $nonCountingBits, 0xAAAAAAABuL, 0, $nonCountingBitsPlus33 )" if EqualF( 16 /  3, $ratio );
    return "($sym << (3 + $nonCountingBitsAbove3)) >> $nonCountingBitsAbove3"                                                                                                                            if EqualF(  8     , $ratio );
    return "($sym << (4 + $nonCountingBitsAbove4)) >> $nonCountingBitsAbove4"                                                                                                                            if EqualF( 16     , $ratio );
    return "($sym << (5 + $nonCountingBitsAbove5)) >> $nonCountingBitsAbove5"                                                                                                                            if EqualF( 32     , $ratio );

    return "(($sym & (0xFFFFFFFFuL >> $nonCountingBits)) * (T1_uint32Least_t)($ratioNumerator)) / (T1_uint32_t)($ratioDenominator)";
}

######################################################################################
# sub GetMaxFrameBytes returns maxRxFrameBytes and maxTxFrameBytes for given invocation files
######################################################################################

# Input:
#   System number for which the configurations are checked
#   Configuration database as a Perl hash
sub GetMaxFrameBytes
{
    # Get subroutine parameters
    my $sysNo = shift;
    my $configRef = shift;

    # Convert hash ref to hash
    my %config = %$configRef;

    # Default Values
    my $maxRxFrameBytes = 8;
    my $maxTxFrameBytes = 8;

    if ($config{'connectionType'}[$sysNo] eq 'Diagnosis' )
    {
        die "-diagMaxTxDataSize must be bigger than 0 when connectionType is set to Diagnosis"            if $config{'diagMaxTxDataSize'}[$sysNo] == 0;
        warn "Warning: -canFDMaxTxDataSize is not used when -connectionType is set to Diagnosis\n"        if $config{'canFDMaxTxDataSize'}[$sysNo] != 0;
        warn "Warning: -ethMaxTxDataSize is not used when -connectionType is set to Diagnosis\n"          if $config{'ethMaxTxDataSize'}[$sysNo] != 0;
        warn "Warning: -t32HostToTargetBufferSize is not used when -connectionType is set to Diagnosis\n" if $config{'t32HostToTargetBufferSize'}[$sysNo] != 0;
        $maxRxFrameBytes = $config{'diagMaxTxDataSize'}[$sysNo];

        die "-diagMaxRxDataSize must be bigger than 0 when connectionType is set to Diagnosis"            if $config{'diagMaxRxDataSize'}[$sysNo] == 0;
        warn "Warning: -canFDMaxRxDataSize is not used when -connectionType is set to Diagnosis\n"        if $config{'canFDMaxRxDataSize'}[$sysNo] != 0;
        warn "Warning: -ethMaxRxDataSize is not used when -connectionType is set to Diagnosis\n"          if $config{'ethMaxRxDataSize'}[$sysNo] != 0;
        warn "Warning: -t32TargetToHostBufferSize is not used when -connectionType is set to Diagnosis\n" if $config{'t32TargetToHostBufferSize'}[$sysNo] != 0;
        $maxTxFrameBytes = $config{'diagMaxRxDataSize'}[$sysNo];
    }
    else # pure T1 connection
    {
        warn "Warning: -diagMaxTxDataSize is not used when -connectionType is set to pure T1\n" if $config{'diagMaxTxDataSize'}[$sysNo] != 8;
        if( $config{'txChannel'}[$sysNo] eq 'CAN_FD' )
        {
            die "-canFDMaxTxDataSize must be bigger than 0 when -txChannel is set to CAN_FD"          if $config{'canFDMaxTxDataSize'}[$sysNo] == 0;
            warn "Warning: -ethMaxTxDataSize is not used when -txChannel is set to CAN_FD\n"          if $config{'ethMaxTxDataSize'}[$sysNo] != 0;
            warn "Warning: -t32HostToTargetBufferSize is not used when -txChannel is set to CAN_FD\n" if $config{'t32HostToTargetBufferSize'}[$sysNo] != 0;
            $maxRxFrameBytes = $config{'canFDMaxTxDataSize'}[$sysNo];
        }
        elsif( $config{'txChannel'}[$sysNo] eq 'ETHERNET' )
        {
            die "-ethMaxTxDataSize must be bigger than 0 when -txChannel is set to ETHERNET"          if $config{'ethMaxTxDataSize'}[$sysNo] == 0;
            warn "Warning: -canFDMaxTxDataSize is not used when -txChannel is set to CAN_FD\n"        if $config{'canFDMaxTxDataSize'}[$sysNo] != 0;
            warn "Warning: -t32HostToTargetBufferSize is not used when -txChannel is set to CAN_FD\n" if $config{'t32HostToTargetBufferSize'}[$sysNo] != 0;
            $maxRxFrameBytes = $config{'ethMaxTxDataSize'}[$sysNo];
        }
        elsif( $config{'txChannel'}[$sysNo] eq 'TRACE32' )
        {
            die "-t32HostToTargetBufferSize must be bigger than 0 when -txChannel is set to TRACE32 " if $config{'t32HostToTargetBufferSize'}[$sysNo] == 0;
            warn "Warning: -canFDMaxTxDataSize is not used when -txChannel is set to CAN_FD\n "       if $config{'canFDMaxTxDataSize'}[$sysNo] != 0;
            warn "Warning: -ethMaxTxDataSize is not used when -txChannel is set to CAN_FD\n"          if $config{'ethMaxTxDataSize'}[$sysNo] != 0;
            $maxRxFrameBytes = $config{'t32HostToTargetBufferSize'}[$sysNo];
        }

        warn "Warning: -diagMaxRxDataSize is not used when -connectionType is set to pure T1\n" if $config{'diagMaxRxDataSize'}[$sysNo] != 8;
        if( $config{'rxChannel'}[$sysNo] eq 'CAN_FD' )
        {
            die "-canFDMaxRxDataSize must be bigger than 0 when -rxChannel is set to CAN_FD"          if $config{'canFDMaxRxDataSize'}[$sysNo] == 0;
            warn "Warning: -ethMaxRxDataSize is not used when -rxChannel is set to CAN_FD\n"          if $config{'ethMaxRxDataSize'}[$sysNo] != 0;
            warn "Warning: -t32TargetToHostBufferSize is not used when -rxChannel is set to CAN_FD\n" if $config{'t32TargetToHostBufferSize'}[$sysNo] != 0;
            $maxTxFrameBytes = $config{'canFDMaxRxDataSize'}[$sysNo];
        }
        elsif( $config{'rxChannel'}[$sysNo] eq 'ETHERNET' )
        {
            die "-ethMaxRxDataSize must be bigger than 0 when -rxChannel is set to ETHERNET"          if $config{'ethMaxRxDataSize'}[$sysNo] == 0;
            warn "Warning: -canFDMaxRxDataSize is not used when -rxChannel is set to CAN_FD\n"        if $config{'canFDMaxRxDataSize'}[$sysNo] != 0;
            warn "Warning: -t32TargetToHostBufferSize is not used when -rxChannel is set to CAN_FD\n" if $config{'t32TargetToHostBufferSize'}[$sysNo] != 0;
            $maxTxFrameBytes = $config{'ethMaxRxDataSize'}[$sysNo];
        }
        elsif( $config{'rxChannel'}[$sysNo] eq 'TRACE32' )
        {
            die "-t32TargetToHostBufferSize must be bigger than 0 when -rxChannel is set to TRACE32 " if $config{'t32TargetToHostBufferSize'}[$sysNo] == 0;
            warn "Warning: -canFDMaxRxDataSize is not used when -rxChannel is set to CAN_FD\n "       if $config{'canFDMaxRxDataSize'}[$sysNo] != 0;
            warn "Warning: -ethMaxRxDataSize is not used when -rxChannel is set to CAN_FD\n"          if $config{'ethMaxRxDataSize'}[$sysNo] != 0;
            $maxTxFrameBytes = $config{'t32TargetToHostBufferSize'}[$sysNo];
        }
    }

    return ( $maxRxFrameBytes, $maxTxFrameBytes );
}

######################################################################################
# sub GenT1ConfigH prints the generated segment of T1_config.h (virtually all of it)
######################################################################################

# Input:
#   File handle for output
#   Configuration database as a Perl hash
sub GenT1ConfigH($$$)
{
    my $fh = shift;
    my $configRef = shift;
    my $taskActExtraTotal = shift;
    my %config = %$configRef;
    my $DG = $config{'enableDoxygenComments'};

    my @CPULoadThresholdsRaw;
    foreach my $CPULoadThreshold (@{$config{'cpuLoadThreshold'}})
    {
        if( $CPULoadThreshold =~ /^(\d{0,3}(?:\.\d+)?)%?$/ )
        {
            $CPULoadThreshold = $1;
        }
        elsif( $CPULoadThreshold =~ /^([\ \.\d\/\*\+\-\(\)]+)$/ ) # Limit the set of characters as the following use of the eval expression would otherwise be potentially unsafe
        {
            $CPULoadThreshold = eval $1;
        }
        else
        {
            warn sprintf "Warning: Invalid format for cpuLoadThreshold '%s', will be set to 100%%\n", $CPULoadThreshold;
            $CPULoadThreshold = 100;
        }

        if( $CPULoadThreshold < 0 )
        {
            warn sprintf "Warning: cpuLoadThreshold of %03.1f%% detected, will be set to 0%%\n", $CPULoadThreshold;
            $CPULoadThreshold = 0;
        }
        elsif( $CPULoadThreshold > 100 )
        {
            warn sprintf "Warning: cpuLoadThreshold of %03.1f%% detected, will be set to 100%%\n", $CPULoadThreshold;
            $CPULoadThreshold = 100;
        }

        # Convert from percentage to per 256ths and round to the nearest integer value
        my $CPULoadThresholdRaw = int( $CPULoadThreshold * 256 / 100 + 0.5 );
        $CPULoadThresholdRaw = 255 if 255 < $CPULoadThresholdRaw;

        push @CPULoadThresholdsRaw, $CPULoadThresholdRaw;
    }

    die 'Undefined number of cores' unless 0 < $config{'nOfCores'};

    print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_CORES', addU( $config{'nOfCores'} ) );
    if( 1 == $config{'nOfCores'} )
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_PC_ARRAY( coreId_, var_ )',  'var_ ## 0' );
        print $fh FormatConfigMacro( $DG, 0, 'T1_PC( coreId_, var_ )',        '&T1_PC_ARRAY( coreId_, var_ )' );

        printf $fh <<EOT;
#if defined T1_GET_RAW_TIME_CORE0 && ! defined T1_GET_RAW_TIME
#   define T1_GET_RAW_TIME( ) T1_GET_RAW_TIME_CORE0( )
#endif /* defined T1_GET_RAW_TIME_CORE0 && ! defined T1_GET_RAW_TIME */
EOT
    }
    else
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_PC_ARRAY( coreId_, var_ )',  '((var_ ## PC)[coreId_])',      , undef, 1 );
        print $fh FormatConfigMacro( $DG, 0, 'T1_PC( coreId_, var_ )',        'T1_PC_ARRAY( coreId_, var_ )', , undef, 1 );
    }

    print $fh FormatConfigMacro( $DG, 0, 'T1_COMMS_CORE_OFFSET', addU( $config{'commsCoreOffset'} ) );
    print $fh FormatConfigMacro( $DG, 0, 'T1_SID', addU( $config{'sid'} ) );
    print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_56BIT_SYNC_TIMER', ($config{'traceWideSyncTimer'} eq 'true') ? '1' : '0' );
    print $fh FormatConfigMacro( $DG, 0, 'T1_FG_CONT_ACT_EXTRA_ENTRIES', $taskActExtraTotal );
    if( '' eq $config{'bidHeader'} ) # no BID-header specified. write BID into Config_H
    {
        printf $fh $config{'t1BidHDefs'};
    }

    if( $config{'useSameConnectionForAllSystems'} eq 'true' )
    {
        if( defined $config{'ethHwName'} )
        {
            print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_USE_IPV6', ( ('true' eq $config{'ethUseIpv6'}[0]) ? 1 : 0 ), undef );

            if( 'true' eq $config{'ethUseIpv6'}[0] )
            {
                printf $fh "\/* PC IP address [%s]:%d *\/\n", $config{'ethPcIP'}, $config{'ethPcPort'}[0];
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IPV6', $config{'ethPcIP'}, undef, 1 );

                printIpv6StringAsHalfWords( $fh, $DG, 'T1_ETH_PC_IPV6_HWNN', $config{'ethPcIP'}, undef );
            }
            else # assume false, IPv4
            {
                printf $fh "\/* PC IP address %s:%d *\/\n", $config{'ethPcIP'}, $config{'ethPcPort'}[0];
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IPV4', $config{'ethPcIP'}, undef, 1 );

                my ( $Ip0, $Ip1, $Ip2, $Ip3 ) = split /\./, $config{'ethPcIP'};
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP0', $Ip0, undef, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP1', $Ip1, undef, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP2', $Ip2, undef, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP3', $Ip3, undef, 1 );
            }
            print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_PORT', $config{'ethPcPort'}[0], undef, 1 );

            if( 'true' eq $config{'ethUseIpv6'}[0] )
            {
                printf $fh "\/* ECU IP address [%s]:%d *\/\n", $config{'ethEcuIP'}[0], $config{'ethEcuPort'}[0];
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IPV6', $config{'ethEcuIP'}[0], undef, 1 );

                printIpv6StringAsHalfWords( $fh, $DG, 'T1_ETH_ECU_IPV6_HWNN', $config{'ethEcuIP'}[0], undef );
            }
            else # assume false, IPv4
            {
                printf $fh "\/* ECU IP address %s:%d *\/\n", $config{'ethEcuIP'}[0], $config{'ethEcuPort'}[0];
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IPV4', $config{'ethEcuIP'}[0], undef, 1 );

                my ( $Ip0, $Ip1, $Ip2, $Ip3 ) = split /\./, $config{'ethEcuIP'}[0];
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP0', $Ip0, undef, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP1', $Ip1, undef, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP2', $Ip2, undef, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP3', $Ip3, undef, 1 );
            }
            # only specify the macro if the value is really set to a sensible value
            if( defined $config{'ethEcuDNSHostName'}[0] )
            {
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_DNS_HOST_NAME', $config{'ethEcuDNSHostName'}[0], undef, 1 );
            }
            print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_PORT', $config{'ethEcuPort'}[0], undef, 1 );
            print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_USE_UDP', ( $config{'ethUseUdp'}[0] eq 'true' ) ? '1' : '0' );
        }

        if( $config{'canHardware'} or $config{'canFDHardware'} ) # A scalar value is interpreted as FALSE in the Boolean sense if it is undefined, the null string or the number 0 (or its string equivalent, "0"), and TRUE if it is anything else.
        {
            print $fh FormatConfigMacro( $DG, 0, 'T1_CAN_PC_TO_ECU_ID', addU( $config{'canTxID'}[0] ) );
            print $fh FormatConfigMacro( $DG, 0, 'T1_CAN_ECU_TO_PC_ID', addU( $config{'canRxID'}[0] ) );
        }

        my ( $maxRxFrameBytes, $maxTxFrameBytes ) = GetMaxFrameBytes( 0, $configRef );
        print $fh FormatConfigMacro( $DG, 0, 'T1_GCP_MAX_RX_FRAME_SIZE', addU( $maxRxFrameBytes ) );
        print $fh FormatConfigMacro( $DG, 0, 'T1_GCP_MAX_TX_FRAME_SIZE', addU( $maxTxFrameBytes ) );
    }

    print $fh FormatConfigMacro( $DG, 0, 'T1_STATIC_RUNNABLE_ID', addU(  $config{'staticRunnableID'} ) ) if '' ne $config{'staticRunnableID'};
    print $fh FormatConfigMacro( $DG, 0, 'T1_TIMEOUT_RX',         addU(  $config{'timeoutRx'} )        ) if '' ne $config{'timeoutRx'};
    print $fh FormatConfigMacro( $DG, 0, 'T1_TIMEOUT_TX',         addU(  $config{'timeoutTx'} )        ) if '' ne $config{'timeoutTx'};
    print $fh FormatConfigMacro( $DG, 0, 'T1_TIMEOUT_RESPONSE',   addU(  $config{'timeoutResponse'} )  ) if '' ne $config{'timeoutResponse'};
    print $fh FormatConfigMacro( $DG, 0, 'T1_INIT_FEATURE_MASK',  addUL( $config{'initFeatureMask'} ) )  if '' ne $config{'initFeatureMask'};

    my $lastCoreIndex = $config{'nOfCores'} - 1;
    my $syncTimerCountsDown = 0;
    $syncTimerCountsDown = 1 if $config{'syncTimerDownCounting'} eq 'true';

    unless( $config{'pSyncTimer'} )
    {
        foreach my $sysNo ( 0 .. $lastCoreIndex )
        {
            if( $config{'traceTimerIsSyncTimer'}[$sysNo] eq 'true' )
            {
                # Since the sync timer is equal to the trace timer for this core,
                # use the trace time macro for the sync time macro.
                my $getSyncTime = "(T1_uint32_t)T1_GET_TRACE_TIME_PC( ${sysNo}u )";

                # Stop here because it seems more natural to use the first of them
                # when several cores use the sync timer as their trace timer.
                print $fh FormatConfigMacro( $DG, 0, 'T1_GET_SYNC_TIME( )', $getSyncTime );
                last;
            }
        }
    }
    else
    {
        my $getSyncTime = sprintf "%s*(T1_uint32_t volatile const *)%s", '(T1_uint32_t)-' x $syncTimerCountsDown, addUL( $config{'pSyncTimer'} );
        print $fh FormatConfigMacro( $DG, 0, 'T1_GET_SYNC_TIME( )', $getSyncTime );
    }
    print $fh FormatConfigMacro( $DG, 0, 'T1_SYNC_TIMER_WIDTH_BITS', addU( $config{'syncTimeBitLength'} ) );
    # Add 'f' suffix to float literals for MISRA conformance and to match T1 headers
    my $syncTimerTickDurationMisraNs = $config{'syncTimerTickDurationNs'};
    $syncTimerTickDurationMisraNs =~ s/(\d*\.\d*)/$1f/g;
    print $fh FormatConfigMacro( $DG, 0, 'T1_SYNC_TIMER_DURATION_NS',          $syncTimerTickDurationMisraNs ) if '' ne $syncTimerTickDurationMisraNs;
    print $fh FormatConfigMacro( $DG, 0, 'T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER', $config{'allTraceTimersAreSyncTimer'} );
    print $fh FormatConfigMacro( $DG, 0, 'T1_ANY_TRACE_TIMER_IS_SYNC_TIMER', $config{'anyTraceTimerIsSyncTimer'} );
    print $fh FormatConfigMacro( $DG, 0, 'T1_CONT_REMOTE',                   '1' ) if 0 < scalar keys %{$config{'contRunsOnCore'}} and 1 < $config{'nOfCores'};
    print $fh FormatConfigMacro( $DG, 0, 'T1_CONT_NOF_FOCUS_MEASUREMENTS',   addU( $config{'numberOfFocusMeasurements'} ) );

    my $maxNofTasks = 0;

    my $minCat1IsrOffset       = 1024; # A value larger than the maximum task id
    my $minCat2IsrOffset       = 1024; # A value larger than the maximum task id
    my $minExternalIsrIdOffset = 1024; # A value larger than the maximum task id

    foreach my $coreId ( 0 .. $lastCoreIndex )
    {
        $maxNofTasks = $config{'numberOfTasks'}[$coreId] if $maxNofTasks < $config{'numberOfTasks'}[$coreId];

        $minCat1IsrOffset       = $config{'cat1IsrIdOffset'}[$coreId]     if $minCat1IsrOffset       > $config{'cat1IsrIdOffset'}[$coreId];
        $minCat2IsrOffset       = $config{'cat2IsrIdOffset'}[$coreId]     if $minCat2IsrOffset       > $config{'cat2IsrIdOffset'}[$coreId];
        $minExternalIsrIdOffset = $config{'externalIsrIdOffset'}[$coreId] if $minExternalIsrIdOffset > $config{'externalIsrIdOffset'}[$coreId];
    }

    if( 255 < $maxNofTasks and not isT1HostSwVersionAllowed( $config{'minT1HostSwVersion'}, '3.4.0') )
    {
        die << "EOT";
Error: Detected more than 255 tasks (${maxNofTasks}) per core,
       this feature requires T1-HOST-SW v3.4.0 or later,
       please use the -minT1HostSwVersion to increase the minimum version.
EOT
    }

    print $fh FormatConfigMacro( $DG, 0, 'T1_MAX_NOF_TASKS', ( sprintf "%4s", addU( $maxNofTasks ) ) );

    print $fh FormatConfigMacro( $DG, 0, 'T1_MIN_CAT1_ISR_ID_OFFSET', ( sprintf "%4s", addU( $minCat1IsrOffset )       ) );
    print $fh FormatConfigMacro( $DG, 0, 'T1_MIN_CAT2_ISR_ID_OFFSET', ( sprintf "%4s", addU( $minCat2IsrOffset )       ) );
    print $fh FormatConfigMacro( $DG, 0, 'T1_MIN_EXT_ISR_ID_OFFSET',  ( sprintf "%4s", addU( $minExternalIsrIdOffset ) ) );


    # If all cores use the same, memory-mapped timer, generate the obvious
    # T1_GET_TRACE_TIME definition.
    my $allCoresTraceTimerAddr;
    $allCoresTraceTimerAddr = $config{'pTimer'}[0] unless not defined $config{'pTimer'}[0] or $config{'pTimer'}[0] eq '0' or $config{'pTimer'}[0] eq '1';
    my $allCoresTraceTimerCountsDown;
    $allCoresTraceTimerCountsDown = $config{'traceTimerDownCounting'}[0] eq 'true';
    my $allCoresMemoryMappedTimer = $allCoresTraceTimerAddr;
    foreach my $sysNo ( 1 .. $lastCoreIndex )
    {
        last unless $allCoresTraceTimerAddr;
        last unless defined $allCoresTraceTimerCountsDown;
        undef $allCoresTraceTimerAddr unless $config{'pTimer'}[$sysNo] and $allCoresTraceTimerAddr eq $config{'pTimer'}[$sysNo];
        $allCoresTraceTimerAddr = 0 unless $config{'pTimer'}[$sysNo] and $config{'pTimer'}[$sysNo] ne '0' and $config{'pTimer'}[$sysNo] ne '1';
        undef $allCoresTraceTimerCountsDown unless $allCoresTraceTimerCountsDown == ($config{'traceTimerDownCounting'}[$sysNo] eq 'true');
    }
    print $fh FormatConfigMacro( $DG, 0, 'T1_GET_RAW_TIME( )', (
        sprintf '%s%s', '(T1_tickUint_t)-' x $allCoresTraceTimerCountsDown, '*(T1_tickUint_t volatile const *)T1_PTIMER_CORE0' )
    ) if $allCoresTraceTimerAddr and defined $allCoresTraceTimerCountsDown;
    print $fh FormatConfigMacro( $DG, 0, 'T1_ALL_TIMERS_ARE_MEMORY_MAPPED', '1' ) if $allCoresMemoryMappedTimer;

    if( $config{'allCoresTraceTickDurationNs'} )
    {
        # Sync to trace time conversion is done in contexts where no further truncation is required
        print $fh FormatConfigMacro( $DG, 0, 'T1_SYNC_TO_TRACE_TIME( syncTime__ )',  '(T1_tickUint_t)(' . GetConverter( $config{'syncTimerTickDurationNs'}, $config{'allCoresTraceTickDurationNs'}, 'syncTime__', , 32 ) . ')' );
        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_TO_SYNC_TIME( traceTime__ )', '(T1_uint32_t)(' . GetConverter( $config{'allCoresTraceTickDurationNs'}, $config{'syncTimerTickDurationNs'}, 'traceTime__', $config{'traceTimerBitLength'}[0] ) . ')' );
    }
    if( $config{'allCoresRawTickDurationNs'} )
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_RAW_TO_SYNC_TIME( rawTime_ )', '(T1_uint32_t)(' . GetConverter( $config{'allCoresRawTickDurationNs'}, $config{'syncTimerTickDurationNs'}, 'rawTime_', $config{'rawTimerBitLength'}[0] ) . ')' );
    }
    if( $config{'allCoresRawToTickRatio'} )
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_RAW_TO_TRACE_TIME( rawTime_ )', '(T1_tickUint_t)(' . GetConverter( 1, $config{'allCoresRawToTickRatio'}, 'rawTime_', $config{'rawTimerBitLength'}[0] ) . ')' );
        print $fh FormatConfigMacro( $DG, 0, 'T1_RAW_TO_TRACE_TIME_UNMASKED( rawTime_ )', '(T1_tickUint_t)(' . GetConverter( 1, $config{'allCoresRawToTickRatio'}, 'rawTime_', 32 ) . ')' );
    }

    printf $fh FormatDocu( $DG, 'T1_GET_TRACE_TIME_PC', undef );
    printf $fh <<EOT;
#if ! defined T1_GET_TRACE_TIME_PC
#   if defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME
#       define T1_GET_TRACE_TIME_PC( coreId_ )                                  \\
            T1_RAW_TO_TRACE_TIME( T1_GET_RAW_TIME( ) )
EOT
    $lastCoreIndex = 0 if $lastCoreIndex < 0;
    printf $fh <<EOT;
#   else /* Different timers/speeds for different cores */
#       define T1_GET_TRACE_TIME_PC( coreId_ )                                  \\
(                                                                               \\
EOT
    foreach my $coreId ( 0 .. $lastCoreIndex-1 )
    {
        printf $fh "    ${coreId}u == (coreId_) ? T1_RAW_TO_TRACE_TIME_CORE$coreId( T1_GET_RAW_TIME_CORE$coreId( ) ) :  \\\n";
    }
    printf $fh <<EOT;
                      T1_RAW_TO_TRACE_TIME_CORE$lastCoreIndex( T1_GET_RAW_TIME_CORE$lastCoreIndex( ) )    \\
)
EOT
    my @syncCoreIds = 0 .. $lastCoreIndex;
    my $lastSyncCoreId = pop @syncCoreIds;
    printf $fh <<EOT;
#       define T1_TRACE_TO_SYNC_TIME_PC( coreId_, traceTime_ )                  \\
(                                                                               \\
EOT
    foreach my $coreId ( @syncCoreIds )
    {
        printf $fh "    ${coreId}u == (coreId_) ? T1_TRACE_TO_SYNC_TIME_CORE$coreId( traceTime_ ) :               \\\n";
    }
    printf $fh <<EOT;
                      T1_TRACE_TO_SYNC_TIME_CORE$lastSyncCoreId( traceTime_ )                 \\
)
EOT
    my @traceNotSyncCoreIds; # The list of cores for which sync != trace time
    foreach my $coreId ( 0 .. $lastCoreIndex )
    {
        push @traceNotSyncCoreIds, ($coreId) unless $config{'traceTimerIsSyncTimer'}[$coreId] eq 'true';
    }
    if( 0 != scalar @traceNotSyncCoreIds )
    {
        my $lastTraceNotSyncCoreId = pop @traceNotSyncCoreIds;
        print $fh FormatConfigMacro( $DG, 2, 'T1_MORE_THAN_ONE_NOT_SYNC_TRACE_TIMER', '1' ) unless 0 == scalar @traceNotSyncCoreIds;
        printf $fh <<EOT;
#       define T1_TRACE_TO_NOT_SYNC_TIME_PC( coreId_, traceTime_ )              \\
(                                                                               \\
EOT
        foreach my $coreId ( @traceNotSyncCoreIds )
        {
            printf $fh "    ${coreId}u == (coreId_) ? T1_TRACE_TO_SYNC_TIME_CORE$coreId( traceTime_ ) :               \\\n";
        }
        printf $fh <<EOT;
                      T1_TRACE_TO_SYNC_TIME_CORE$lastTraceNotSyncCoreId( traceTime_ )                 \\
)
EOT
    }
    printf $fh <<EOT;
#   endif /* defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME */
#endif /* ! defined T1_GET_TRACE_TIME_PC */
EOT

    if( $config{'checkIntegration'} eq 'true' )
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_CHECK_INTEGRATION', '1' );
        print $fh FormatConfigMacro( $DG, 0, 'T1_CHECK_INTEGRATION_INV_PARAM', '1' );
    }

    foreach my $sysNo ( 0 .. $lastCoreIndex )
    {
        my $BgTask = '';

        # perform some value checks:
        if( $config{'cpuLoadAvgSamples'}[$sysNo] && $config{'cpuLoadTxPeriod'}[$sysNo] )
        {
            die "error: cpuLoadAvgSamples must either be 1 or equal to cpuLoadTxPeriod!"
                unless $config{'cpuLoadAvgSamples'}[$sysNo] == 1 || $config{'cpuLoadAvgSamples'}[$sysNo] == $config{'cpuLoadTxPeriod'}[$sysNo];
        }
        if( $config{'nOfFlexAddrs'}[$sysNo] < $config{'nOfFlexStopwatches'}[$sysNo] )
        {
            die "error: nOfFlexStopwatches must be at most nOfFlexAddrs";
        }

        print $fh "\n/* Core-specific configuration for core $sysNo */\n";
        if( $config{'osBasicSchedFrameEventId'}[$sysNo] eq "T1_USEREVENT" )
        {
            print $fh FormatConfigMacro( $DG, 0, 'T1_BSF_EVENT_ID_COREXX', addU( $config{'osBasicSchedFrameId'}[$sysNo] ), $sysNo );
            print $fh FormatConfigMacro( $DG, 0, 'T1_BSF_EVENT_INFO_COREXX', '0u', $sysNo ); # event info must be statically 0
        }
        else # T1_ACTIVATION, T1_START, T1_STOP
        {
            print $fh FormatConfigMacro( $DG, 0, 'T1_BSF_EVENT_ID_COREXX', addU( $config{'osBasicSchedFrameEventId'}[$sysNo] ), $sysNo );
            if( $config{'osBasicSchedFrameName'}[$sysNo])
            {
                my $taskIdMacro = "T1_$config{'osBasicSchedFrameName'}[$sysNo]_ID";
                print $fh FormatConfigMacro( $DG, 0, 'T1_BSF_EVENT_INFO_COREXX', $taskIdMacro, $sysNo );
            }
            else # only ID is specified
            {
                if( $config{'osBasicSchedFrameId'}[$sysNo] ) # leave out if not specified
                {
                    print $fh FormatConfigMacro( $DG, 0, 'T1_BSF_EVENT_INFO_COREXX', addU( $config{'osBasicSchedFrameId'}[$sysNo] ), $sysNo );
                }
            }
        }
        if( $config{'useSameConnectionForAllSystems'} eq 'false' )
        {
            if( $config{'canHardware'} or $config{'canFDHardware'} ) # A scalar value is interpreted as FALSE in the Boolean sense if it is undefined, the null string or the number 0 (or its string equivalent, "0"), and TRUE if it is anything else.
            {
                print $fh FormatConfigMacro( $DG, 0, 'T1_CAN_PC_TO_ECU_ID_COREXX', addU( $config{'canTxID'}[$sysNo] ) );
                print $fh FormatConfigMacro( $DG, 0, 'T1_CAN_ECU_TO_PC_ID_COREXX', addU( $config{'canRxID'}[$sysNo] ) );
            }

            if( defined $config{'ethHwName'} )
            {
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_USE_IPV6_COREXX', ( ('true' eq $config{'ethUseIpv6'}[$sysNo]) ? 1 : 0 ), $sysNo );

                # Do not repeat the same configuration macros for every core
                if( 0 == $sysNo )
                {
                    if( 'true' eq $config{'ethUseIpv6'}[$sysNo] )
                    {
                        printf $fh "\/* PC IP address [%s]:%d *\/\n", $config{'ethPcIP'}, $config{'ethPcPort'}[$sysNo];
                        print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IPV6', $config{'ethPcIP'}, undef, 1 );

                        printIpv6StringAsHalfWords( $fh, $DG, 'T1_ETH_PC_IPV6_HWNN', $config{'ethPcIP'}, undef );
                    }
                    else # assume false, IPv4
                    {
                        printf $fh "\/* PC IP address %s:%d *\/\n", $config{'ethPcIP'}, $config{'ethPcPort'}[$sysNo];
                        print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IPV4', $config{'ethPcIP'}, undef, 1 );

                        my ( $Ip0, $Ip1, $Ip2, $Ip3 ) = split /\./, $config{'ethPcIP'};
                        print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP0', $Ip0, undef, 1 );
                        print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP1', $Ip1, undef, 1 );
                        print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP2', $Ip2, undef, 1 );
                        print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_IP3', $Ip3, undef, 1 );
                    }
                }
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_PC_PORT_COREXX', $config{'ethPcPort'}[$sysNo], $sysNo, 1 );

                if( 'true' eq $config{'ethUseIpv6'}[$sysNo] )
                {
                    printf $fh "\/* ECU IP address [%s]:%d *\/\n", $config{'ethEcuIP'}[$sysNo], $config{'ethEcuPort'}[$sysNo];
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IPV6_COREXX', $config{'ethEcuIP'}[$sysNo], $sysNo, 1 );

                    printIpv6StringAsHalfWords( $fh, $DG, 'T1_ETH_ECU_IPV6_HWNN_COREXX', $config{'ethEcuIP'}[$sysNo], $sysNo );
                }
                else # assume false, IPv4
                {
                    printf $fh "\/* ECU IP address %s:%d *\/\n", $config{'ethEcuIP'}[$sysNo], $config{'ethEcuPort'}[$sysNo];
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IPV4_COREXX', $config{'ethEcuIP'}[$sysNo], $sysNo, 1 );

                    my ( $Ip0, $Ip1, $Ip2, $Ip3 ) = split /\./, $config{'ethEcuIP'}[$sysNo];
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP0_COREXX', $Ip0, $sysNo, 1 );
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP1_COREXX', $Ip1, $sysNo, 1 );
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP2_COREXX', $Ip2, $sysNo, 1 );
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_IP3_COREXX', $Ip3, $sysNo, 1 );
                }
                # only specify the macro if the value is really set to a sensible value
                if( defined $config{'ethEcuDNSHostName'}[$sysNo] )
                {
                    print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_DNS_HOST_NAME_COREXX', $config{'ethEcuDNSHostName'}[$sysNo], $sysNo, 1 );
                }
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_ECU_PORT_COREXX', $config{'ethEcuPort'}[$sysNo], $sysNo, 1 );
                print $fh FormatConfigMacro( $DG, 0, 'T1_ETH_USE_UDP_COREXX', ( $config{'ethUseUdp'}[$sysNo] eq 'true' ) ? '1' : '0', $sysNo );
            }

            my ( $maxRxFrameBytes, $maxTxFrameBytes ) = GetMaxFrameBytes( $sysNo, $configRef );
            print $fh FormatConfigMacro( $DG, 0, 'T1_GCP_MAX_RX_FRAME_SIZE_COREXX', addU( $maxRxFrameBytes ), $sysNo );
            print $fh FormatConfigMacro( $DG, 0, 'T1_GCP_MAX_TX_FRAME_SIZE_COREXX', addU( $maxTxFrameBytes ), $sysNo );
        }

        if( $config{'osBackgroundTaskName'}[$sysNo] )
        {
            $BgTask = "T1_$config{'osBackgroundTaskName'}[$sysNo]_ID";
        }
        elsif( defined $config{'osBackgroundTaskId'}[$sysNo] )
        {
             $BgTask = $config{'osBackgroundTaskId'}[$sysNo];
        }
        else
        {
            $BgTask = "T1_INVALID_TASK_ID";
        }
        print $fh FormatConfigMacro( $DG, 0, 'T1_BACKGROUND_TASK_ID_COREXX', $BgTask, $sysNo );

        # Add 'f' suffix to float literals for MISRA conformance and to match T1 headers
        my $tickDurationMisraNs = $config{'tickDurationNs'}[$sysNo];
        $tickDurationMisraNs =~ s/(\d*\.\d*)/$1f/g;
        print $fh FormatConfigMacro( $DG, 0, 'T1_TICK_DURATION_COREXX_NS', $tickDurationMisraNs, $sysNo );
        if( 0 < $config{'nOfCores'} )
        {
            # Sync to trace time conversion is done in contexts where no further truncation is required
            print $fh FormatConfigMacro( $DG, 0, 'T1_SYNC_TO_TRACE_TIME_COREXX( syncTime__ )', '(T1_tickUint_t)(' . GetConverter( $config{'syncTimerTickDurationNs'}, $config{'tickDurationNs'}[$sysNo], 'syncTime__', 32 ) . ')', $sysNo );
            print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_TO_SYNC_TIME_COREXX( traceTime__ )', '(T1_uint32_t)(' . GetConverter( $config{'tickDurationNs'}[$sysNo], $config{'syncTimerTickDurationNs'}, 'traceTime__', $config{'traceTimerBitLength'}[$sysNo] ) . ')', $sysNo );
            # Foreground T1.cont 'now' is a synthetic value with 32 counting bits
            # regardless of physical timer and scaling
            print $fh FormatConfigMacro( $DG, 0, 'T1_RAW_TO_TRACE_TIME_COREXX( rawTime_ )', '(T1_tickUint_t)(' . GetConverter( $config{'rawTickDurationNs'}[$sysNo], $config{'tickDurationNs'}[$sysNo], 'rawTime_', $config{'rawTimerBitLength'}[$sysNo] ) . ')', $sysNo );
            print $fh FormatConfigMacro( $DG, 0, 'T1_RAW_TO_TRACE_TIME_UNMASKED_COREXX( rawTime_ )', '(T1_tickUint_t)(' . GetConverter( $config{'rawTickDurationNs'}[$sysNo], $config{'tickDurationNs'}[$sysNo], 'rawTime_', 32 ) . ')', $sysNo );
            print $fh FormatConfigMacro( $DG, 0, 'T1_RAW_TO_SYNC_TIME_COREXX( rawTime_ )', '(T1_uint32_t)(' . GetConverter( $config{'rawTickDurationNs'}[$sysNo], $config{'syncTimerTickDurationNs'}, 'rawTime_', $config{'rawTimerBitLength'}[$sysNo] ) . ')', $sysNo );
        }
        print $fh FormatConfigMacro( $DG, 0, 'T1_OVERHEAD_COREXX_NS', $config{'t1ScopeOverheadNs'}[$sysNo], $sysNo );
        print $fh FormatConfigMacro( $DG, 0, 'T1_FLEX_OVERHEAD_COREXX_NS', $config{'t1FlexOverheadNs'}[$sysNo], $sysNo );

        print $fh FormatConfigMacro( $DG, 0, 'T1_CPULOAD_THRESHOLD_256THS_COREXX', ( sprintf "(%s) /* %03.1f%% */", addU( $CPULoadThresholdsRaw[$sysNo] ), $CPULoadThresholdsRaw[$sysNo] / 256 * 100 ), $sysNo, 1 );

        print $fh FormatConfigMacro( $DG, 0, 'T1_FEATURE_MASK_CALLBACK_COREXX', $config{'featureMaskCallback'}[$sysNo] ? "1u << ${sysNo}" : '0u', $sysNo );

        # Remove any u or ul suffix in order that trace buffer size can be evaluated by the C preprocessor
        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACEBUFFER_ENTRIES_COREXX_', stripU( $config{'traceBufferEntries'}[$sysNo] ), $sysNo ) if $config{'traceBufferEntries'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACEBUFFER_ENTRIES_COREXX', addU( $config{'traceBufferEntries'}[$sysNo] ), $sysNo ) if $config{'traceBufferEntries'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_CSRNS_COREXX', addU( $config{'numberOfConstraints'}[$sysNo] ), $sysNo )          if 0 < $config{'numberOfConstraints'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_USER_STPWS_COREXX', addU( $config{'numberOfUserStpws'}[$sysNo] ), $sysNo )       if 0 < $config{'numberOfUserStpws'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_FLEX_STPWS_COREXX', addU( $config{'nOfFlexStopwatches'}[$sysNo] ), $sysNo )      if $config{'nOfFlexStopwatches'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_STPWS_COREXX', 'T1_NOF_USER_STPWS_COREXX + T1_NOF_FLEX_STPWS_COREXX', $sysNo );
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_FLEX_ADDRS_COREXX', addU( $config{'nOfFlexAddrs'}[$sysNo] ), $sysNo )            if $config{'nOfFlexAddrs'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_FLEXBUFFER_ENTRIES_COREXX', addU( $config{'numberOfFlexBufferEntries'}[$sysNo] ), $sysNo )   if $config{'numberOfFlexBufferEntries'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_OUTER_HANDLER_COREXX', 'T1_OuterHandlerCore' . $sysNo . ( 'true' eq $config{'useDMStrampoline'}[$sysNo] ? '' : '_' ), $sysNo );
        print $fh FormatConfigMacro( $DG, 0, 'T1_PTIMER_COREXX', addUL( $config{'pTimer'}[$sysNo] ), $sysNo )                         if $config{'pTimer'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_SYNC_PERIOD_COREXX', addU( $config{'syncPeriod'}[$sysNo] ), $sysNo );
        print $fh FormatConfigMacro( $DG, 0, 'T1_GET_RAW_TIME_COREXX( )', "*(T1_tickUint_t volatile const *)T1_PTIMER_COREXX", $sysNo )    if $config{'pTimer'}[$sysNo];

        my $traceTimerIsSyncTimer = 0;
        $traceTimerIsSyncTimer = 1 if $config{'traceTimerIsSyncTimer'}[$sysNo] eq 'true';
        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX', $traceTimerIsSyncTimer, $sysNo );

        my $traceTimerDownCounting = 'T1_FALSE';
        $traceTimerDownCounting = 'T1_TRUE' if $config{'traceTimerDownCounting'}[$sysNo] eq 'true';
        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_TIMER_COUNTS_DOWN_COREXX', $traceTimerDownCounting, $sysNo );

        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_TIMER_BIT_LENGTH_COREXX', addU( $config{'traceTimerBitLength'}[$sysNo] ), $sysNo );

        my $cpuLoadTxPeriod = $config{'cpuLoadTxPeriod'}[$sysNo];
        my $cpuLoadAvgSamples = $config{'cpuLoadAvgSamples'}[$sysNo];
        $cpuLoadAvgSamples = $cpuLoadTxPeriod unless 1 <= $cpuLoadAvgSamples and $cpuLoadAvgSamples <= $cpuLoadTxPeriod;
        my $codedCpuLoadAvgSamples = $cpuLoadAvgSamples;
        my $encodingString = '';
        if( 255 < $cpuLoadAvgSamples )
        {
            die "Unsupported cpuLoadAvgSamples ($cpuLoadAvgSamples) in the range [256 .. cpuLoadTxPeriod-1 ($cpuLoadTxPeriod-1)]" unless $cpuLoadAvgSamples == $cpuLoadTxPeriod;
            # Sentinel value, meaning $cpuLoadAvgSamples == $cpuLoadTxPeriod
            $codedCpuLoadAvgSamples = 0;
            $encodingString = " /* denotes $cpuLoadAvgSamples */";
        }
        print $fh FormatConfigMacro( $DG, 0, 'T1_CPULOAD_TX_PERIOD_COREXX', addU( $cpuLoadTxPeriod ), $sysNo );
        print $fh FormatConfigMacro( $DG, 0, 'T1_CPULOAD_SAMPLES_COREXX', addU( $codedCpuLoadAvgSamples ) . $encodingString, $sysNo );
        print $fh FormatConfigMacro( $DG, 0, 'T1_CONT_ANALYSIS_CAPACITY_COREXX', addU( $config{'analysisCapacity'}[$sysNo] ), $sysNo ) if $config{'analysisCapacity'}[$sysNo];
        print $fh FormatConfigMacro( $DG, 0, 'T1_NOF_DELAYS_COREXX', addU( $config{'nOfDelays'}[$sysNo] ), $sysNo )                    if 0 < $config{'nOfDelays'}[$sysNo];
    }

    print $fh "\n/* Unused cores. */\n";
    foreach my $sysNo ( $lastCoreIndex+1 .. 5 )
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_TRACE_TIMER_IS_SYNC_TIMER_COREXX', '1', $sysNo );
    }

    print $fh <<EOT;


#if ! defined T1_CORE_ID_TO_SCOPE_CONSTS
#   if ! defined T1_CLONE
EOT
    if( $config{'nOfCores'} <= 1 )
    {
        print $fh FormatConfigMacro( $DG, 0, 'T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ )', 'T1_P_SCOPE_CONSTS0' );
        print $fh FormatConfigMacro( $DG, 0, 'T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ )', 'T1_P_SCOPE_FG_CONSTS0' );
    }
    else
    {
        print $fh "/* This default version can be evaluated at compile time when passed a literal input */\n";
        print $fh "#       if 2 < T1_NOF_CORES && defined __GNUC__ /* use switch statement */\n";
        #T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ )
        my $tempString = <<'EOT';
{                 \
    T1_scopeConsts_t * pScopeConsts_;                                       \
    switch( coreId_ )                                                       \
    {                                                                       \
EOT
        foreach my $sysNo ( 0 .. ($lastCoreIndex-1) )
        {
            $tempString .= sprintf "    case %-7spScopeConsts_  = T1_P_SCOPE_CONSTS%-5s break;              \\\n", "$sysNo:", "$sysNo;";
        }
        $tempString .= sprintf "    default:    pScopeConsts_  = T1_P_SCOPE_CONSTS%-5s break;              \\\n", "$lastCoreIndex;";
        $tempString .= <<'EOT';
    }                                                                       \
    pScopeConsts_;                                                          \
}
EOT
        chomp $tempString; # Remove last newline char
        print $fh FormatConfigMacro( $DG, 3, 'T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ )', $tempString );

        #T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ )
        $tempString = <<'EOT';
{              \
    T1_scopeFgConsts_t * pScopeFgConsts_;                                   \
    switch( coreId_ )                                                       \
    {                                                                       \
EOT
        foreach my $sysNo ( 0 .. ($lastCoreIndex-1) )
        {
            $tempString .= sprintf "    case %-7spScopeFgConsts_  = T1_P_SCOPE_FG_CONSTS%-5s break;         \\\n", "$sysNo:", "$sysNo;";
        }
        $tempString .= sprintf "    default:    pScopeFgConsts_  = T1_P_SCOPE_FG_CONSTS%-5s break;         \\\n", "$lastCoreIndex;";
        $tempString .= <<'EOT';
    }                                                                       \
    pScopeFgConsts_;                                                        \
}
EOT
        chomp $tempString; # Remove last newline char
        print $fh FormatConfigMacro( $DG, 3, 'T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ )', $tempString );
        print $fh "#       else /* NOTE 'coreId_' can be evaluated more than once with >2 cores */\n";
        #define T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ )
        $tempString = "                  \\\n";

        foreach my $sysNo ( 0 .. ($lastCoreIndex-1) )
        {
            $tempString .= sprintf "    (%2u == (coreId_) ) ? T1_P_SCOPE_CONSTS%-3u :                             \\\n", $sysNo, $sysNo;
        }
        $tempString .= sprintf "                         T1_P_SCOPE_CONSTS%-3u                               \\\n", $lastCoreIndex;
        print $fh FormatConfigMacro( $DG, 3, 'T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ )', $tempString );

        #define T1_CORE_ID_TO_SCOPE_FG_GLOBALS( coreId_ )
        $tempString = "               \\\n";

        foreach my $sysNo ( 0 .. ($lastCoreIndex-1) )
        {
            $tempString .= sprintf "    (%2u == (coreId_) ) ? T1_P_SCOPE_FG_CONSTS%-2u :                           \\\n", $sysNo, $sysNo;
        }
        $tempString .= sprintf "                         T1_P_SCOPE_FG_CONSTS%-2u                             \\\n", $lastCoreIndex;
        print $fh FormatConfigMacro( $DG, 3, 'T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ )', $tempString );
        print $fh <<EOT;
#       endif /* switch or ?: */
EOT
    }
    print $fh <<EOT;
#   endif /* ! defined T1_CLONE */
#endif /* ! defined T1_CORE_ID_TO_SCOPE_CONSTS */

#if ! defined T1_CONT_RC_UNMAP
EOT
    if( 1 == $config{'nOfCores'} )
    {
        print $fh FormatConfigMacro( $DG, 1, 'T1_CONT_RC_UNMAP( coreId_ )', '0' );
    }
    elsif( 0 == keys %{$config{'contRunsOnCore'}} )
    {
        print $fh FormatConfigMacro( $DG, 1, 'T1_CONT_RC_UNMAP( coreId_ )', 'coreId_' );
    }
    else
    {
        my $oneCoreId = 0;
        $oneCoreId = $config{'contRunsOnCore'}{0} if exists $config{'contRunsOnCore'}{0};
        # Fill in the "blanks" in %{$config{'contRunsOnCore'}} to simplify the following code
        foreach my $sysNo ( 0 .. ($config{'nOfCores'}-1) )
        {
            $config{'contRunsOnCore'}{$sysNo} = $sysNo unless exists $config{'contRunsOnCore'}{$sysNo};
            $oneCoreId = -1 if $config{'contRunsOnCore'}{$sysNo} != $oneCoreId;
        }
        if( -1 != $oneCoreId )
        {
            # All T1.cont background handlers run on the same core
            print $fh FormatConfigMacro( $DG, 1, 'T1_CONT_RC_UNMAP( coreId_ )', addU( $oneCoreId ) );
        }
        else
        {
            my $tempString;
            if( 2 < $config{'nOfCores'} )
            {
                $tempString = <<'EOT';
                              \
T1_INLINE T1_uint8Least_t T1_CODE T1_ContRcUnmapCoreId( T1_uint8Least_t coreId )    \
{                                                                                   \
    switch( coreId )                                                                \
    {                                                                               \
EOT
                $tempString .= sprintf "    default : return %-63s\\\n", addU( $config{'contRunsOnCore'}{0} . ';' );
                foreach my $sysNo ( 1 .. $lastCoreIndex )
                {
                    $tempString .= sprintf "    case %3s: return %-63s\\\n", addU( $sysNo ), addU( $config{'contRunsOnCore'}{$sysNo} . ';' );
                }
                $tempString .= <<'EOT';
    }                                                                               \
}
EOT
            print $fh FormatConfigMacro( $DG, 1, 'T1_DEFN_CONT_UNMAP_CORE_ID', $tempString, undef, 1 );
            }

            if( 2 == $config{'nOfCores'} )
            {
                $tempString = " (0 == (coreId_)) ? $config{'contRunsOnCore'}{0}u : $config{'contRunsOnCore'}{1}u ";
            }
            else
            {
                $tempString = " T1_ContRcUnmapCoreId( coreId_ ) ";
            }
            print $fh FormatConfigMacro( $DG, 1, 'T1_CONT_RC_UNMAP( coreId_ )', $tempString );
        }
    }
    print $fh <<EOT;
#endif /* ! defined T1_CONT_RC_UNMAP */
EOT

    print $fh FormatConfigMacro( $DG, 0, 'T1_EXTERNAL_TRACEBUFFER', '1', undef, 0 ) if 'true' eq $config{'externalTraceBuffer'};
    print $fh FormatConfigMacro( $DG, 0, 'T1_COMMS_SHARED_MEM_RX',  '1', undef, 0 ) if 'TRACE32' eq $config{'txChannel'}[0];
    print $fh FormatConfigMacro( $DG, 0, 'T1_COMMS_SHARED_MEM_TX',  '1', undef, 0 ) if 'TRACE32' eq $config{'rxChannel'}[0];
    print $fh FormatConfigMacro( $DG, 0, 'T1_POLLING_TRANSMIT',     '1', undef, 0 ) if 'true' eq $config{'useSameConnectionForAllSystems'} and 'Diagnosis' eq $config{'connectionType'}[0];

    return;
}

######################################################################################
# Sub routine to generate User Stopwatch configuration for adding it to T1_config.h
######################################################################################

sub GenT1ConfigHUserSw
{
    my $fh = shift;
    my $nOfCores = int shift;
    my $configRef = shift;
    my %config = %$configRef;
    my @userStopWatches = @{$config{'userStopWatches'}};

    if( @userStopWatches )
    {
        print $fh <<'EOT';
/*----------------------------------------------------------------------------------*/
/*--- User stopwatch IDs -----------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
        my $allCoreMacrosString;
        foreach my $swRef ( @{$userStopWatches[ 0 ]} )
        {
            my $lastT1cont = '';

            if( '_ALL' eq $swRef->{'coreId'} )
            {
                my $macroName = $swRef->{'macroAll'};
                my $id = sprintf "%5s", addU( $swRef->{'id'} );

                if( $lastT1cont ne $swRef->{'t1cont'} )
                {
                    if( 'true' eq $swRef->{'t1cont'} )
                    {
                        $allCoreMacrosString .=  "/* The following user stopwatches are supervised by T1.cont */\n";
                    }
                    else
                    {
                        $allCoreMacrosString .=  "/* The following user stopwatches are not supervised by T1.cont */\n";
                    }
                    $lastT1cont = $swRef->{'t1cont'};
                }

                my $string = FormatConfigMacro( 'false', 0, $macroName, $id );
                chomp $string;
                $allCoreMacrosString .=  $string . ( defined $swRef->{'name'} ? ' /* ' . $swRef->{'name'} . ' */' : '' ) . "\n";
            }
        }

        if( $allCoreMacrosString )
        {
            print $fh "/* User stopwatches for all cores */\n";
            print $fh $allCoreMacrosString;
            print $fh "\n";
        }

        foreach my $coreId ( 0..$nOfCores-1 )
        {
            my $lastT1cont = '';

            print $fh "/* User stopwatches for core ${coreId} */\n";

            foreach my $swRef ( @{$userStopWatches[$coreId]} )
            {
                my $coreMacro = @{$swRef->{'perCoreMacro'}}[$coreId];
                my $id;

                if( '_ALL' eq $swRef->{'coreId'} )
                {
                    $id = $swRef->{'macroAll'};
                }
                else
                {
                    $id = sprintf "%5s", addU( $swRef->{'id'} );
                }

                if( $lastT1cont ne $swRef->{'t1cont'} )
                {
                    if( 'true' eq $swRef->{'t1cont'} )
                    {
                        print $fh "/* The following user stopwatches are supervised by T1.cont */\n";
                    }
                    else
                    {
                        print $fh "/* The following user stopwatches are not supervised by T1.cont */\n";
                    }
                    $lastT1cont = $swRef->{'t1cont'};
                }

                my $string = FormatConfigMacro( 'false', 0, $coreMacro, $id );
                chomp $string;

                print $fh $string . ( ( defined $swRef->{'name'} ) ? ' /* ' . $swRef->{'name'} . ' */' : '' ) . "\n";
            }

            print $fh "\n";
        }
    }

    return;
}

######################################################################################
# Sub routine to generate Application Feature masks for adding it to T1_config.h
######################################################################################

sub GenT1ConfigHAF
{
    my $fh = shift;
    my $configRef = shift;
    my %config = %$configRef;
    my @applicationFeatures = @{$config{'applicationFeatures'}};

    if( @applicationFeatures )
    {
        print $fh <<'EOT';
/*----------------------------------------------------------------------------------*/
/*--- Application Features ---------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
        foreach my $afRef ( sort { $a->{'mask'} <=> $b->{'mask'} } @applicationFeatures )
        {
            my $macroName = $afRef->{'macroName'};
            my $name      = $afRef->{'name'};
            my $mask      = $afRef->{'mask'};
            my $maskAsHex = sprintf "0x%08XuL", $mask;

            my $string = FormatConfigMacro( 'false', 0, $macroName, $maskAsHex );
            chomp $string;
            $string .= " /* ${name} */\n";

            print $fh $string;
        }

        print $fh "\n";
    }

    return;
}

######################################################################################
# Sub routine to generate T1.delay configuration for adding it to T1_config.h
######################################################################################
sub GenT1ConfigHDL
{
    my $fh = shift;
    my $nOfCores = int shift;
    my $configRef = shift;
    my %config = %$configRef;
    my $delays = $config{'delays'};

    if( @{$delays} )
    {
        print $fh <<'EOT';
/*----------------------------------------------------------------------------------*/
/*--- T1.delay IDs -----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
        my $allCoreMacrosString;
        foreach my $dlRef ( @{$delays->[ 0 ]} )
        {
            if( '_ALL' eq $dlRef->{'coreId'} )
            {
                my $macroName = $dlRef->{'macroAll'};
                my $id = addU( $dlRef->{'id'} );

                my $string = FormatConfigMacro( 'false', 0, $macroName, $id );
                chomp $string;
                $allCoreMacrosString .=  $string . ( defined $dlRef->{'name'} ? ' /* ' . $dlRef->{'name'} . ' */' : '' ) . "\n";
            }
        }

        if( $allCoreMacrosString )
        {
            print $fh "/* Delays for all cores */\n";
            print $fh $allCoreMacrosString;
            print $fh "\n";
        }

        foreach my $coreId ( 0..$nOfCores-1 )
        {
            my $coreXString;

            foreach my $dlRef ( @{@$delays[$coreId]} )
            {
                my $coreMacro = @{$dlRef->{'perCoreMacro'}}[$coreId];
                if( defined $coreMacro )
                {
                    my $id;

                    if( '_ALL' eq $dlRef->{'coreId'} )
                    {
                        $id = $dlRef->{'macroAll'};
                    }
                    else
                    {
                        $id = addU( $dlRef->{'id'} );
                    }

                    my $string = FormatConfigMacro( 'false', 0, $coreMacro, $id );
                    chomp $string;

                    $coreXString .= $string . ( ( defined $dlRef->{'name'} ) ? ' /* ' . $dlRef->{'name'} . ' */' : '' ) . "\n";
                }
            }

            if( $coreXString )
            {
                print $fh "/* Delays for core ${coreId} */\n";
                print $fh $coreXString;
            }

            print $fh "\n";
        }
    }

    return;
}

sub GenT1ConfigHUE
{
    my $fh = shift;
    my $nOfCores = int shift;
    my $configRef = shift;
    my %config = %$configRef;
    my $userEvents = $config{'userEvents'};

    if( @{$userEvents} )
    {
        print $fh <<'EOT';
/*----------------------------------------------------------------------------------*/
/*--- User Data Event and User Event IDs -------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
        my $allCoreMacrosString;
        foreach my $ueRef ( @{$userEvents->[ 0 ]} )
        {
            if( '_ALL' eq $ueRef->{'coreId'} )
            {
                my $macroName = $ueRef->{'macroAll'};
                my $id = addU( $ueRef->{'id'} );

                my $string = FormatConfigMacro( 'false', 0, $macroName, $id );
                chomp $string;
                $allCoreMacrosString .=  $string . ( defined $ueRef->{'name'} ? ' /* ' . $ueRef->{'name'} . ' */' : '' ) . "\n";
            }
        }

        if( $allCoreMacrosString )
        {
            print $fh "/* User Events for all cores */\n";
            print $fh $allCoreMacrosString;
            print $fh "\n";
        }

        foreach my $coreId ( 0..$nOfCores-1 )
        {
            my $coreXString;

            foreach my $ueRef ( @{@$userEvents[$coreId]} )
            {
                my $coreMacro = @{$ueRef->{'perCoreMacro'}}[$coreId];
                if( defined $coreMacro )
                {
                    my $id;

                    if( '_ALL' eq $ueRef->{'coreId'} )
                    {
                        $id = $ueRef->{'macroAll'};
                    }
                    else
                    {
                        $id = addU( $ueRef->{'id'} );
                    }

                    my $string = FormatConfigMacro( 'false', 0, $coreMacro, $id );
                    chomp $string;

                    $coreXString .= $string . ( ( defined $ueRef->{'name'} ) ? ' /* ' . $ueRef->{'name'} . ' */' : '' ) . "\n";
                }
            }

            if( $coreXString )
            {
                print $fh "/* User Events for core ${coreId} */\n";
                print $fh $coreXString;
            }

            print $fh "\n";
        }
    }

    return;
}

1;
