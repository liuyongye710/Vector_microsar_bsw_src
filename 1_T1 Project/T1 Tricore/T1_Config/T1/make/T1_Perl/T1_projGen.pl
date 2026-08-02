######################################################################################
#
#   File:           T1_projGen.pl
#
#   Description:    Reading OS-configuration using OS-specific Perl-module
#                   Read parameters from T1 invocation files
#                   Generate T1_config.h and .t1p file
#
#   $Author: jialinli $
#
#   $Revision: 120 $
#
#   Copyright:      GLIWA GmbH | know- how in embedded software
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

use strict;
use warnings;
use File::Spec::Functions ':ALL';
use File::Copy;
use File::Basename;
use File::Path;
use File::stat;
use T1_config;
use constant MAX_NOF_CORES => 15;

File::Basename::fileparse_set_fstype("MSWin32");

######################################################################################
# global variables. Values are to be assigned by reading invocation files
######################################################################################

#paths of required files:
my @inlineHeaders = ();                             # the content of those files is copied to the T1 project file (external data). Specify path and file name. Use next parameter optionally
my @includeHeaders = ();                            # these files are referenced in the T1 project file. The T1-HOST-SW parses the contents and searches for systemElements. Specify path and file name. Use previous parameter optionally
my $configGenC = "";                                # name and path of T1_config.c
my $configHeader = "";                              # name and path of header file being generated containing T1 configuration parameter macros (and task/ISR-ID macros if $idHeader is not specified)
my @symbolFiles = ();                               # name and path of symbol files being referenced by the T1 project file -> wild-card allowed: e.g. ".\myFolder\proj*.elf"
my $projectFile = "";                               # name and path of T1 project file being generated

#paths of optional files:
my $runnableHeader = "";                            # name and path of header file being generated containing T1 definitions for runnable start/stop macros (only if supported by OS-specific Perl-module)
my $idHeader = "";                                  # name and path of header file being generated containing T1 task and ISR-ID macros. If specified no ID macros are generated to $configHeader
my $bidHeader = "";                                 # name and path of header file being generated containing T1 Build ID. If not specified the BID will be generated into idHeader
my @t1pSymbolIncludeFiles = ();                     # name and path of auxiliary t1p-files containing T1SymbolsPart (such as symbol groups)
my %t1pAnnotationsFiles = ();                       # name and path of auxiliary t1a-files containing indirect calls for T1.stack

#parameters that use default value if omitted:
my $copySymbolFile = "false";                       # copy symbol-file to T1 project path [true/false]
my $copyIncludeHeader = "false";                    # copy include headers to T1 project path [true/false]
my $generateBuildId = "true";                       # generate Build ID (BID) every time the Perl script is executed. The BID is propagated to the t1p-file and T1_config.h and by that to the executable. The T1-HOST-SW checks if symbol-file and target-code are consistent
my $projectName = "T1 project";                     # any project name
my $licInfo1 = "unknown POT";                       # POT number to identify the project to GLIWA
my $licInfo2 = "unknown LAP";                       # LAP number to identify the project to GLIWA
my $readPreviousT1p = "true";                       # read user-configured parts from previous t1p (if exists) and copy to new t1p
my $syncTimeBitLength = 32;                         # Synchronisation of Multicore systems requires a timer resolution of at least 24 bits

my $useSameConnectionForAllSystems = 'true';        # are all systems using the same connection? [true/false]
my $txCycle = 10;                                   # TX cycle of T1-HOST-SW
my $canBitrate = 500000;                            # CAN bitrate
my $canFDBitrate = 500000;                          # CAN FD bitrate
my $canHardware = '';                               # CAN hardware [U2C/VECTOR], initialized empty to check which is necessary
my $canFDHardware = '';                             # CAN FD hardware [VECTOR], initialized empty to check which is necessary
my $ethHardware = '';                               # Ethernet hardware [LAN_ADAPTER], initialized empty to check which is necessary
my $ethTxCycle= 20;                                 # Ethernet TX cycle of T1-HOST-SW
my $ethPcIP = '0.0.0.0';                            # Ethernet IP address of PC
my $mustUseFixedBlockSize = 'true';                 # T1-HOST-SW CAN TX-messages always use DLC=8
my $ethMustUseFixedBlockSize = 'false';             # T1-HOST-SW Ethernet TX-messages length is variable by default
my $usingMulticoreLibs = 'false';                   # using Multicore-Libs [true/false]
my $bigEndian = "false";                            # target is big-endian [true/false]
my $cortex = "false";                               # is target ARM cortex M or R [true/false]
my $initFeatureMask = "";                           # string of initial application feature mask [e.g. (T1_AF_TRACE_STARUP | T1_AF_MEASURE_T1_HANDLER)]
my $symbolPrefix = '';                              # Green Hills compiler prefixes symbols with underscore
my $numberOfFocusMeasurements = 2;                  # Number of focus measurements that can run simultaneously

#parameters that are omitted if omitted:
my $canFDMustUseFixedBlockSize = '';                # T1-HOST-SW CAN FD TX-messages length can be variable or not
my $canHwName;                                      # Name of CAN HW
my $canFDHwName;                                    # Name of CAN FD HW
my $ethHwName;                                      # Name of Ethernet connection
my $canUsage = '';                                  # Preferred device for the T1-HOST-SW
my $ethUsage = '';                                  # Preferred device for the T1-HOST-SW
my $canFDUsage = '';                                # Preferred device for the T1-HOST-SW
my $timeoutRx = "";                                 # The receive time-out is the maximum time allowed between reception of two frames of the same message.This needs to be large enough to allow for network traffic and routing delays between the host and the target [multiple of t1HandlerPeriodMs of communication core]
my $timeoutRxMs = "";                               # Version in milliseconds
my $timeoutTx = "";                                 # The transmit time-out is the maximum time allowed for (retrying) the sending of a frame. This needs to be large enough to allow for queuing in the CAN layer(s), typically a smaller number than the receive timeout [multiple of t1HandlerPeriodMs of communication core]
my $timeoutTxMs = "";                               # Version in milliseconds
my $timeoutResponse = "";                           # It is the maximum time permitted between transmitting the last frame of a message that requires acknowledgement and receiving the last frame of that acknowledgement. It is typically very much larger than the GCP timeout limits, since it needs to allow for the T1-HOST-SW to respond in addition to transmission and reception delays [multiple of t1HandlerPeriodMs of communication core]
my $timeoutResponseMs = "";                         # Version in milliseconds
my $syncTimerTickDurationNs = "";                   # This represents the tick duration for the main/synchronization clock. The T1-HOST-SW needs this to merge multicore traces. Strictly required for Multicore systems!
my @configHeaderIncludes = ();                      # header files to be included in T1_config.h ["myFileToBeIncluded.h"]
my @idHeaderIncludes = ();                          # header files to be included in idHeader ["myFileToBeIncluded.h"]
my @runnableHeaderIncludes = ();                    # header files to be included in runnableHeader ["myFileToBeIncluded.h"]
my $storeTimingInformation = "";                    # store timing information in t1p [true/false]
my $endiannessAgnosticComSetup = "";                # used for compatibility with T1-TARGET-SW starting with V2.2.0.0 and prior to V2.2.4.0 on big endian targets
my $canFDSamplePoint = 0;                           # CAN FD SamplePoint value, default is 70%
my $canFDDataBitrate = 0;                           # CAN FD DataBitrate value, default is Bitrate value. If SamplePoint is also defined, this value is ommited
my $canFDDataSamplePoint = 0;                       # CAN FD DataSamplePoint value, default is 70%
my $canFDOscillatorFrequencyMhz = 0;                # CAN FD OscillatorFrequencyMhz value, default is 80 MHz
my @canFDBitTiming = ();                            # CAN FD BitTiming values separated with "," in the specific order "[Brp], [Prop], [Phase1], [Phase2], [Sjw], [Sam]". SamplePoint is used by default
my @canFDDataBitTiming = ();                        # CAN FD DataBitTiming values separated with "," in the specific order "[Brp], [Prop], [Phase1], [Phase2], [Sjw], [Sam]". DataSamplePoint is used by default

#these connection parameters are project-specific (and thus global) if useSameConnectionForAllSystems == true
#if system-specific connections-settings are required state -useSameConnectionForAllSystems=false and add these parameters to each system
my @connectionType = ('pure T1') x MAX_NOF_CORES;   # connection-type: [pure T1/Diagnosis]
my @txChannel = ('CAN') x MAX_NOF_CORES;            # hardware used for TxChannel: [CAN/CAN_FD/ETHERNET]
my @rxChannel = ('CAN') x MAX_NOF_CORES;            # hardware used for RxChannel: [CAN/CAN_FD/ETHERNET]
my @canRxID = ('0x6FA') x MAX_NOF_CORES;            # CAN / CAN FD ID ECU to T1-HOST-SW [0x6FA]
my @canTxID = ('0x6CB') x MAX_NOF_CORES;            # CAN / CAN FD ID T1-HOST-SW to ECU [0x6CB]
my @canExtendedIds = ('false') x MAX_NOF_CORES;     # use extended CAN IDs [true/false]
my @canFDMaxRxDataSize = (0) x MAX_NOF_CORES;       # CAN FD: max. data size of one frame from ECU to T1-HOST-SW
my @canFDMaxTxDataSize = (0) x MAX_NOF_CORES;       # CAN FD: max. data size of one frame from T1-HOST-SW to ECU, minimum is used to set the bus parameter MaxTxBlocksize
my @diagAddressingMode = ('normal') x MAX_NOF_CORES;# Diagnosis: addressing mode: [normal/extended]
my @diagSourceAddr = ('0xFA') x MAX_NOF_CORES;      # Diagnosis: source address: Typically the lowest 8 byte of canRxID [0xFA]
my @diagTargetAddr = ('0xCB') x MAX_NOF_CORES;      # Diagnosis: target address: Typically the lowest 8 byte of canTxID [0xCB]
my @diagUseServiceByLocalId = ('false') x MAX_NOF_CORES;# Diagnosis: use service by local ID (deprecated: only supported by KWP2000)
my @diagT1Identifier = (0) x MAX_NOF_CORES;         # Diagnosis: T1 identifier
my @diagLocalIdentifier = (0) x MAX_NOF_CORES;      # Diagnosis: local identifier (deprecated: only supported by KWP2000)
my @diagMaxRxDataSize = (8) x MAX_NOF_CORES;        # Diagnosis: max. RX data size of one Frame (using ReadByIdentifier service)
my @diagMinTxDataSize = (8) x MAX_NOF_CORES;        # Diagnosis: min. TX data size of one Frame (using WriteByIdentifier service)
my @diagMaxTxDataSize = (8) x MAX_NOF_CORES;        # Diagnosis: max. TX data size of one Frame (using WriteByIdentifier service)
my @diagOpenSessionType = ('None') x MAX_NOF_CORES; # Diagnosis: Specifies the session type to be opened when the target link is enabled.
my @diagCustomSessionId = (0) x MAX_NOF_CORES;      # Diagnosis: Specifies the concrete session type to be opened, if the diagOpenSessionType Custom is selected.
my @diagTesterPresentPeriod = (0) x MAX_NOF_CORES;  # Diagnosis: Period the 'TesterPresent' message is sent.
my @ethEcuIP = ('0.0.0.0') x MAX_NOF_CORES;         # Ethernet: IP address of ECU
my @ethEcuPort = (0) x MAX_NOF_CORES;               # Ethernet: ECU Port
my @ethPcPort = (0) x MAX_NOF_CORES;                # Ethernet: PC Port
my @ethUseUdp = ('false') x MAX_NOF_CORES;          # Ethernet: if false, TCP is used
my @ethMaxTxDataSize = (0) x MAX_NOF_CORES;         # Ethernet: Ethernet message max. datasize, initialized to 0, if given it will set T1_GCP_MAX_RX_FRAME_SIZE from T1-HOST-SW to ECU
my @ethMaxRxDataSize = (0) x MAX_NOF_CORES;         # Ethernet: Initialized to 0, if given it will set T1_GCP_MAX_TX_FRAME_SIZE from ECU to T1-HOST-SW
my @useSameRxTxChannel = ('true') x MAX_NOF_CORES;  # system uses the same channel for RX and TX [true/false]

#system-related configuration parameters:
#strictly required:
my $core0sid = 0;                                   # The SID of core 0
my $commsCoreOffset = 0;                            # Offset of the communications core
my @systemType = ();                                # additional info [OSEK/ErcosEK/gliwOS/PC Software/RTA OSEK/AUTOSAR OS/Unknown]
my @systemName = ();                                # unique System Name. This name is displayed in the T1.base context menu of the T1-HOST-SW [any string]
my @systemComment = ();                             # any comment. Just additional info [any string]
my @tickDurationNs = ();                            # tick duration in ns of system-specific timer
my @osBasicSchedFrameName = ();                     # OS-name of task used as Basic Scheduling Frame event. The BSF event determines the boundaries for CPU-load calculation. Alternatively use osBasicSchedFrameId if only the ID is known
my @osBasicSchedFrameId = ();                       # T1 task ID of Basic Scheduling Frame Event
my @t1HandlerPeriodMs = ();                         # System-specific period of T1_Handler [ms]. It is recommended to call T1_Handler every 5 to 10ms
my @t1ScopeOverheadNs = ();                         # Duration of one call to T1_TraceEvent [ns]
my @t1FlexOverheadNs = ();                          # T1.flex overhead [ns]
my @analysisCapacity = ();                          # defines macro T1_CONT_ANALYSIS_CAPACITY_COREx

#parameters that use default value if omitted:
my @traceTimerIsSyncTimer = ('true') x MAX_NOF_CORES;   # when using different timers in Multicore systems one timer needs to be declared the synchronization timer. If the current systems used this timer assign true [true/false]
my @cpuLoadCallback = map { 'T1_CPULoadCallbackCore' . $_ } (0 .. (MAX_NOF_CORES-1));  # system-specific callback being executed if system-specific CPU-load threshold is exceeded
my @osBasicSchedFrameEventId = ('T1_ACTIVATION') x MAX_NOF_CORES;   # system-specific Event ID used for BSF [T1_START/T1_ACTIVATION/T1_USEREVENT]. Use -osBasicSchedFrameId for specifying ID of UserEvent. Caution: The event field must be 0 on the target!
my @osBackgroundTaskName = ('') x MAX_NOF_CORES;    # system-specific OS-name of Background task. If any name is stated this task is excluded from T1.cont and T1.scope calculations. If nothing is stated T1_INVALID_TASK_ID is used instead and thus considering the BG-task
my @osBackgroundTaskId;                             # alternatively if only task-ID is known
my @nofAdditionalCat1Isrs = (0) x MAX_NOF_CORES;    # number of additional ISRs that are not covered by OS-specific module
my @additionalCat1IsrIdOffset = (0) x MAX_NOF_CORES;# if the external cat1 ISRs are starting at a fixed offset configure offset for each system
my @allocateCat1IsrIdPrio = map { {} } ((0) x MAX_NOF_CORES); # specific symbols for which to reserve cat1 ISR IDs. Do not use ({}) x MAX_NOF_CORES because it gives MAX_NOF_CORES references to a single hash!
my @targetExcludeFromTraceByName = ();              # defines macro $configHeader
my @targetExcludeFromTraceById = ();                # defines macro $configHeader
my @flexAnalysisCapacity = (0) x MAX_NOF_CORES;     # T1.flex analysis capacity: Max. number of exception handler calls within T1_Handler period before measurement will be disabled
my @targetType = ('') x MAX_NOF_CORES;              # Used to indicate to the T1-HOST-SW target specifics information, this parameter is system specific [PPC5xxx_nonVLE]

#optional config parameters used for macros in T1_config.h:
my @cpuLoadThreshold = (100) x MAX_NOF_CORES;       # defines macro T1_CPULOAD_THRESHOLD_PERCENT_COREx: CPU-load threshold [0..99]
my @traceBufferEntries = (0) x MAX_NOF_CORES;       # defines macro T1_TRACEBUFFER_ENTRIES_COREx: Number of trace buffer entries
my @numberOfUserStpws = (1) x MAX_NOF_CORES;        # defines macro T1_NOF_USER_STPWS_COREx: Number of user stopwatches
my @numberOfConstraints = (1) x MAX_NOF_CORES;      # defines macro T1_NOF_CSRNS_COREx: Number of constraints
my @nofDelays = ();                                 # defines macro T1_NOF_DELAYS_COREx: Number of delays
my @nofFlexStopwatches = (0) x MAX_NOF_CORES;       # defines macro T1_NOF_FLEX_STPWS_COREx: Number of T1.flex stopwatches (e.g. used for feature "linked Stopwatches") [0..255]
my @nofFlexAddrs = (0) x MAX_NOF_CORES;             # defines macro T1_NOF_FLEX_ADDRS_COREx: Number of T1.flex addresses. Needs to be greater or equal $nofFlexStopwatches [0..255]
my @pTimer = ();                                    # defines macro T1_PTIMER_COREx: If using memory mapped timer: address of timer. Otherwise omit
my $pSyncTimer = 0;                                 # defines macro T1_GET_SYNC_TIMER if using multicore
my @traceTimerDownCounting = ();                    # defines macro T1_TRACE_TIMER_COUNTS_DOWN_COREx: Trace timer is counting down [true/false]
my @traceTimerBitLength = (32) x MAX_NOF_CORES;     # defines macro T1_TRACE_TIMER_BIT_LENGTH_COREx: [16..32]
my @cpuLoadTxPeriod = ();                           # defines macro T1_CPU_LOAD_TX_PERIOD_COREx: Transmit CPU load every x CPU load frames (BSF-frame). E.g. BasicSchedFrame-Event has a period of 100ms. If $cpuLoadTxPeriod is 10 the CPU-load is transmitted every second
my @cpuLoadAvgSamples = ();                         # defines macro T1_CPU_LOAD_SAMPLES_COREx: Number of samples taken within period [1 or $cpuLoadTxPeriod]
my $staticRunnableID = '';                          # defines macro T1_STATIC_RUNNABLE_ID: Id used for tracing runnables with a unique ID [0..1023]

#optional system-specific parameters:
my %t1pSymbolIncludeFilesCoreX = ();
my @symbolFilesCoreX = ();

######################################################################################
# global variables
######################################################################################

my @sysElems = ();
my @extraSysElems = ();
my $t1ConfigHDefs = "";
my $t1idHDefs  = "";
my $t1runnableIds = "";
my $t1ConfigHIds = "";
my $t1IsrWrapper = "";
my $t1p = "";
my $includeHeader = "";

my $buildId = "123456";

my @includeDirs = ();

my @numberOfTasks = (0) x MAX_NOF_CORES;
my %maxPreemptionDepth = ();
my @cat1IsrIdOffset = (1000) x MAX_NOF_CORES;       # just any high initial value
my @cat2IsrIdOffset = (1000) x MAX_NOF_CORES;       # just any high initial value
my @externalIsrIdOffset = (1000) x MAX_NOF_CORES;   # just any high initial value
my @highestIsrIdCat1 = (0) x MAX_NOF_CORES;
my @highestIsrIdCat2 = (0) x MAX_NOF_CORES;

my $externDataAvailable = 0;
my $externData = "";

my $systemNo = undef;

my $debug = 0;

my $userCfgFile = "";
my $cfgFile= "";
my $osCfgFile = "";
# By default, T1.cont runs on it's own core
my %contRunsOnCore = ();

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
# sub ParseParam
######################################################################################
sub ParseParam($)
{

    my $curLine = $_[0];
    $curLine =~ s/^\s//;


    if( (my $no) = $curLine =~ /#system\s+(\d)/ )
    {
        $systemNo = $no;
    }
    if( $curLine =~ /^-/ )
    {
        my $validParamFound = 0;
        my @substr = split(/;/, $curLine); # ';' functions as a comment operator
        my $curAssignm = $substr[0];
        @substr = split(/=/, $curAssignm);
        my $curParam = $substr[0];
        $curParam =~ s/^-|^\s+|\s+$//g;
        my $curVal = $substr[1];
        $curVal =~ s/\s+$|^\s+//g;

        if( $debug )
        {
            print $curParam.'='.$curVal."\n";
        }

        if( $curParam =~ /projectFile/ )              { $projectFile                  = rel2abs($curVal);   $validParamFound = 1; }
        if( $curParam =~ /configGenC$/ )              { $configGenC                   = rel2abs($curVal);   $validParamFound = 1; }
        if( $curParam =~ /configHeader$/ )            { $configHeader                 = rel2abs($curVal);   $validParamFound = 1; }
        if( $curParam =~ /runnableHeader$/ )          { $runnableHeader               = rel2abs($curVal);   $validParamFound = 1; }
        if( $curParam =~ /^idHeader/ )                { $idHeader                     = rel2abs($curVal);   $validParamFound = 1; }
        if( $curParam =~ /bidHeader/ )                { $bidHeader                    = rel2abs($curVal);   $validParamFound = 1; }
        if( $curParam =~ /inlineHeader/ )             { push @inlineHeaders,                   ($curVal);   $validParamFound = 1; }
        if( $curParam =~ /includeHeader/ )            { push @includeHeaders,                  ($curVal);   $validParamFound = 1; }
        if( $curParam =~ /symbolFile/ )
        {
            if( defined( $systemNo ) ) # check if this is a system-specific symbol file
            {
                                                        push ( @{$symbolFilesCoreX[$systemNo]}, $curVal );  $validParamFound = 1;
            }
            else # otherwise it is a global symbol file
            {
                                                        push ( @symbolFiles,                    $curVal );  $validParamFound = 1;
            }
        }
        if( $curParam =~ /t1pAnnotationsFile/ )
        {
            if( not defined( $systemNo ) ) # global annotation include file
            {
                                                        $t1pAnnotationsFiles{$curVal}{"global"} =  1;       $validParamFound = 1;
            }
            else
            {
                if( !exists $t1pAnnotationsFiles{$curVal}{"global"} ) # check redundancy of annotation file
                {
                                                        $t1pAnnotationsFiles{$curVal}{$systemNo} =  1;      $validParamFound = 1;
                }
                else
                {
                    print "Warning: Annotation file present in global section and system $systemNo section in $_[1]\n";# issue a warning if redundancy
                    $validParamFound = 1;
                }
            }
        }
        if( $curParam =~ /t1pSymbolIncludeFile/ )
        {
            if( not defined( $systemNo ) ) # check if this is a global symbol include file
            {
                                                        push @t1pSymbolIncludeFiles,           ($curVal);   $validParamFound = 1;
            }
            else # otherwise it is a core-specific symbol include file
            {
                                                       $t1pSymbolIncludeFilesCoreX{$curVal} =  $systemNo;   $validParamFound = 1;
            }
        }

        if( $curParam =~ /configHeaderInclude/ )      { push @configHeaderIncludes,            ($curVal);   $validParamFound = 1; }
        if( $curParam =~ /idHeaderInclude/ )          { push @idHeaderIncludes,                ($curVal);   $validParamFound = 1; }
        if( $curParam =~ /runnableHeaderInclude/ )    { push @runnableHeaderIncludes,          ($curVal);   $validParamFound = 1; }
        if( $curParam =~ /copyIncludeHeader/ )        { $copyIncludeHeader                    = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /copySymbolFile/ )           { $copySymbolFile                       = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /generateBuildId/ )          { $generateBuildId                      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /projectName/ )              { $projectName                          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /licInfo1/ )                 { $licInfo1                             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /licInfo2/ )                 { $licInfo2                             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /readPreviousT1p/ )          { $readPreviousT1p                      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /storeTimingInformation/ )   { $storeTimingInformation               = $curVal;    $validParamFound = 1; }

        if( $curParam =~ /usingMulticoreLibs/ )       { $usingMulticoreLibs                   = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /initFeatureMask/ )          { $initFeatureMask                      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /symbolPrefix/ )             { $symbolPrefix                         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /numberOfFocusMeasurements/ ){ $numberOfFocusMeasurements            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /mainTickDuration/ )         { $syncTimerTickDurationNs              = $curVal;    $validParamFound = 1; } # For synchronization timer
        if( $curParam =~ /syncTimerTickDurationNs/ )  { $syncTimerTickDurationNs              = $curVal;    $validParamFound = 1; } # For synchronization timer
        if( $curParam =~ /syncTimeBitLength/ )        { $syncTimeBitLength                    = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /bigEndian/ )                { $bigEndian                            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /cortex/ )                   { $cortex                               = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /timeoutRx/ )                { $timeoutRx                            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /timeoutTx/ )                { $timeoutTx                            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /timeoutResponse/ )          { $timeoutResponse                      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /timeoutRxMs/ )              { $timeoutRxMs                          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /timeoutTxMs/ )              { $timeoutTxMs                          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /timeoutResponseMs/ )        { $timeoutResponseMs                    = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /endiannessAgnosticComSetup/ ) { $endiannessAgnosticComSetup         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDSamplePoint/ )         { $canFDSamplePoint                     = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDBitTiming/ )           { @canFDBitTiming           = split( ',', $curVal );  $validParamFound = 1; }
        if( $curParam =~ /canFDDataBitrate/ )         { $canFDDataBitrate                     = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDDataSamplePoint/ )     { $canFDDataSamplePoint                 = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDDataBitTiming/ )       { @canFDDataBitTiming       = split( ',', $curVal );  $validParamFound = 1; }
        if( $curParam =~ /canFDOscillatorFrequencyMhz/ ){ $canFDOscillatorFrequencyMhz        = $curVal;    $validParamFound = 1; }

        if( $curParam =~ /canHardware/ )              { $canHardware                          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDHardware/ )            { $canFDHardware                        = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canHwName/ )                { $canHwName                            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDHwName/ )              { $canFDHwName                          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethHardware/ )              { $ethHardware                          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethHwName/ )                { $ethHwName                            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethPcIP/ )                  { $ethPcIP                              = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /txCycle/ )                  { $txCycle                              = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethTxCycle/ )               { $ethTxCycle                           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canBitrate/ )               { $canBitrate                           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDBitrate/ )             { $canFDBitrate                         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /mustUseFixedBlockSize/ )    { $mustUseFixedBlockSize                = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethMustUseFixedBlockSize/ ) { $ethMustUseFixedBlockSize             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDMustUseFixedBlockSize/ ) { $canFDMustUseFixedBlockSize         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /useSameConnectionForAllSystems/ ) { $useSameConnectionForAllSystems = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /targetExcludeFromTraceByName/ ) { push @targetExcludeFromTraceByName,($curVal);   $validParamFound = 1; }
        if( $curParam =~ /targetExcludeFromTraceById/ )   { push @targetExcludeFromTraceById,  ($curVal);   $validParamFound = 1; }

        if( $curParam =~ /connectionType/ )           { $connectionType[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /txChannel/ )                { $txChannel[$systemNo]                 = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /rxChannel/ )                { $rxChannel[$systemNo]                 = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canRxID/ )                  { $canRxID[$systemNo]                   = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canTxID/ )                  { $canTxID[$systemNo]                   = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canExtendedIds/ )           { $canExtendedIds[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDRxDataSize/ )          { $canFDMaxRxDataSize[$systemNo]           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDMaxRxDataSize/ )       { $canFDMaxRxDataSize[$systemNo]           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDTxDataSize/ )          { $canFDMaxTxDataSize[$systemNo]           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDMaxTxDataSize/ )       { $canFDMaxTxDataSize[$systemNo]           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagAddressingMode/ )       { $diagAddressingMode[$systemNo]        = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagSourceAddr/ )           { $diagSourceAddr[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagTargetAddr/ )           { $diagTargetAddr[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagUseServiceByLocalId/ )  { $diagUseServiceByLocalId[$systemNo]   = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagT1Identifier/ )         { $diagT1Identifier[$systemNo]          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagLocalIdentifier/ )      { $diagLocalIdentifier[$systemNo]       = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagRxDataSize/ )           { $diagMaxRxDataSize[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagMaxRxDataSize/ )        { $diagMaxRxDataSize[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagTxDataSize/ )           { $diagMaxTxDataSize[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagMaxTxDataSize/ )        { $diagMaxTxDataSize[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagMinTxDataSize/ )        { $diagMinTxDataSize[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagOpenSessionType/ )      { $diagOpenSessionType[$systemNo]          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagCustomSessionId/ )      { $diagCustomSessionId[$systemNo]          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /diagTesterPresentPeriod/ )  { $diagTesterPresentPeriod[$systemNo]      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethEcuIP/ )                 { $ethEcuIP[$systemNo]                  = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethEcuPort/ )               { $ethEcuPort[$systemNo]                = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethPcPort/ )                { $ethPcPort[$systemNo]                 = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethUseUdp/ )                { $ethUseUdp[$systemNo]                 = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethRxDataSize/ )            { $ethMaxRxDataSize[$systemNo]             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethMaxRxDataSize/ )         { $ethMaxRxDataSize[$systemNo]             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethTxDataSize/ )            { $ethMaxTxDataSize[$systemNo]             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethMaxTxDataSize/ )         { $ethMaxTxDataSize[$systemNo]             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /useSameRxTxChannel/ )       { $useSameRxTxChannel[$systemNo]        = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canUsage/ )                 { $canUsage                             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /ethUsage/ )                 { $ethUsage                             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /canFDUsage/ )               { $canFDUsage                           = $curVal;    $validParamFound = 1; }

        if( $curParam =~ /sid/ )
        {
            my $newCore0sid = $curVal - $systemNo;
            die "SID cannot be zero" unless 0 < $newCore0sid;
            die "Incompatible SID $curParam at system $systemNo" unless 0 == $core0sid or $core0sid = $newCore0sid;
                                                        $core0sid                             = $newCore0sid;    $validParamFound = 1;
        }
        if( $curParam =~ /commsCoreOffset/ )          { $commsCoreOffset                      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /systemName/ )               { $systemName[$systemNo]                = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /systemComment/ )            { $systemComment[$systemNo]             = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /osBackgroundTaskName/ )     { $osBackgroundTaskName[$systemNo]      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /osBackgroundTaskId/ )       { $osBackgroundTaskId[$systemNo]        = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /osBasicSchedFrameName/ )    { $osBasicSchedFrameName[$systemNo]     = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /osBasicSchedFrameId/ )      { $osBasicSchedFrameId[$systemNo]       = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /osBasicSchedFrameEventId/ ) { $osBasicSchedFrameEventId[$systemNo]  = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /nofAdditionalCat1Isrs/ )    { $nofAdditionalCat1Isrs[$systemNo]     = $curVal;    $validParamFound = 1; }    # For backwards compatibility
        if( $curParam =~ /numberOfAdditionalCat1Isrs/ ) { $nofAdditionalCat1Isrs[$systemNo]   = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /allocateCat1IsrIdPrio/ )    { $allocateCat1IsrIdPrio[$systemNo]{$curVal} = 1;     $validParamFound = 1; }
        if( $curParam =~ /additionalCat1IsrIdOffset/ ){ $additionalCat1IsrIdOffset[$systemNo] = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /t1HandlerPeriodMs/ )        { $t1HandlerPeriodMs[$systemNo]         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /traceBufferEntries/ )       { $traceBufferEntries[$systemNo]        = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /cpuLoadThreshold/ )         { $cpuLoadThreshold[$systemNo]          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /cpuLoadCallback/ )          { $cpuLoadCallback[$systemNo]           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /numberOfUserStpws/ )        { $numberOfUserStpws[$systemNo]         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /numberOfConstraints/ )      { $numberOfConstraints[$systemNo]       = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /analysisCapacity/ )         { $analysisCapacity[$systemNo]          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /flexAnalysisCapacity/ )     { $flexAnalysisCapacity[$systemNo]      = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /targetType/ )               { $targetType[$systemNo]                = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /nofDelays/ )                { $nofDelays[$systemNo]                 = $curVal;    $validParamFound = 1; }    # For backwards compatibility
        if( $curParam =~ /numberOfDelays/ )           { $nofDelays[$systemNo]                 = $curVal;    $validParamFound = 1; }

        if( $curParam =~ /systemType/ )               { $systemType[$systemNo]                = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /tickDurationNs/ )           { $tickDurationNs[$systemNo]            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /traceTimerIsMainTimer/ )    { $traceTimerIsSyncTimer[$systemNo]     = $curVal;    $validParamFound = 1; }    # For backwards compatibility
        if( $curParam =~ /traceTimerIsSyncTimer/ )    { $traceTimerIsSyncTimer[$systemNo]     = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /t1ScopeOverheadNs/ )        { $t1ScopeOverheadNs[$systemNo]         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /t1FlexOverheadNs/ )         { $t1FlexOverheadNs[$systemNo]          = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /nofFlexAddrs/ )             { $nofFlexAddrs[$systemNo]              = $curVal;    $validParamFound = 1; }    # For backwards compatibility
        if( $curParam =~ /numberOfFlexAddrs/ )        { $nofFlexAddrs[$systemNo]              = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /nofFlexStopwatches/ )       { $nofFlexStopwatches[$systemNo]        = $curVal;    $validParamFound = 1; }    # For backwards compatibility
        if( $curParam =~ /numberOfFlexStopwatches/ )  { $nofFlexStopwatches[$systemNo]        = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /pTimer/ )                   { $pTimer[$systemNo]                    = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /pSyncTimer/ )               { $pSyncTimer                           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /traceTimerDownCounting/ )   { $traceTimerDownCounting[$systemNo]    = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /32BitCpuWithSmallerTimer/ ) { if( $curVal eq 'true' and $traceTimerBitLength[$systemNo] == 32 ) { $traceTimerBitLength[$systemNo] = 16; } $validParamFound = 1; }
        if( $curParam =~ /traceTimerBitLength/ )      { $traceTimerBitLength[$systemNo]       = $curVal < 16 ? 16 : 32 < $curVal ? 32 : $curVal; $validParamFound = 1; }
        if( $curParam =~ /cpuLoadTxPeriod/ )          { $cpuLoadTxPeriod[$systemNo]           = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /cpuLoadAvgSamples/ )        { $cpuLoadAvgSamples[$systemNo]         = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /contRunsOnCore/ )           { $contRunsOnCore{$systemNo}            = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /staticRunnableID/ )         { $staticRunnableID                     = $curVal;    $validParamFound = 1; }
        if( $curParam =~ /maxPreemptionDepth/ )       { $maxPreemptionDepth{$systemNo}        = $curVal;    $validParamFound = 1; }

        if( not $validParamFound )
        {
            die "Error: invalid parameter $curParam found in invocation file $_[1]";
        }
    }
}

######################################################################################
# sub resolvePathRelToProjectFile
######################################################################################

sub resolvePathRelToProjectFile($$$)
{
    my $filePath = shift;
    my $prjFilePath = shift;
    my $copyFile = shift;
    my $relativeFilePath = "";
    my $fileBaseName = "";

    $fileBaseName = File::Basename::basename($filePath);

    if( $copyFile eq 'true' )
    {
        # remove the path of the file to be copied

        # Build up the path for the copied include file
        my $copiedFilePathName = File::Spec::Functions::catfile( $prjFilePath, $fileBaseName );
        # Copy the filePath to the same location as the projectFile
        copy( $filePath, $copiedFilePathName ) or die "Failed: copy( $filePath, $copiedFilePathName )";

        $relativeFilePath = $fileBaseName;

        return $relativeFilePath;
    }

    $relativeFilePath = abs2rel( $filePath, $prjFilePath );
    $relativeFilePath =~ s/^.://; #workaround for abs2rel bug: Remove drive

    return $relativeFilePath;
}

######################################################################################
# sub createPath
######################################################################################

sub createPath($)
{
    my $path = shift;
    my $fileName = File::Basename::basename($path);

    my $dirname;
    if( $fileName =~ /\./ )
    {
        $dirname = File::Basename::dirname($path);
    }
    else
    {
        $dirname = $path;
    }
    $dirname =~ s|\\|/|g; # replace '\' by '/'

    if( ($dirname =~ m/\w/) and (! -d $dirname) )
    {
        return 1 == mkdir( $dirname ); # return 1 if mkdir returned 1, otherwise return 0
    }
    else
    {
        return 1; # directory already exists or is empty -> nothing to be created
    }
}

######################################################################################
# sub writeUnlessEqual returns 1 if and only if the file was written
######################################################################################

sub writeUnlessEqual($$)
{
    my $fileName = shift;
    my $newContent = shift;

    createPath( $fileName ) or die "Unable to create directory for $fileName";

    if( -r $fileName )
    {
        open OLD, "$fileName" or die "Unable to read $fileName";
        my $oldContentWithoutComments = join '', <OLD>;
        close OLD;
        # Remove single-line comments because one will contain the generation time,
        # which is always different but does not mean that there are any interesting
        # changes.
        my $newContentWithoutComments = $newContent;
        $oldContentWithoutComments =~ s/<Comment>.*<\/Comment>//g;
        $newContentWithoutComments =~ s/<Comment>.*<\/Comment>//g;
        return 0 if $oldContentWithoutComments eq $newContentWithoutComments;
    }

    open NEW, ">:utf8", $fileName or die "Unable to write $fileName";
    print NEW $newContent;
    close NEW;

    return 1;
}

######################################################################################
# sub getNewestFileMatchingWildcard
######################################################################################
sub getNewestFileMatchingWildcard($)
{
    my $pathAndFileName = $_[0];
    my $fileName = File::Basename::basename($pathAndFileName);
    my $dir = "";
    my $fileSuffix = "";
    my $returnPath = "";
    my $highestModTime = 0;
    my $selectedFile = "";

    if( $fileName =~ /\*/ ) # fileName contains wild-card
    {
         my $fileNameWithStarChar = $fileName;
         $fileNameWithStarChar =~ s/\*/\\\*/;
         $pathAndFileName =~ s/$fileNameWithStarChar//;
         $dir = $pathAndFileName;
         $fileNameWithStarChar =~ /.*\.(.*)$/;
         $fileSuffix = $1;

         opendir(FILE_DIR, $dir) or die "Directory '$dir' for $pathAndFileName not found";
         my @files = grep { /\.$fileSuffix$/ } readdir(FILE_DIR);
         closedir(FILE_DIR);

         my $regExFileName = $fileName;
         $regExFileName =~ s/\*/\(\.\*\)/;
         foreach my $file (@files)
         {
            if( $file =~ /^$regExFileName$/ )
            {
                $returnPath = $dir.$file;
                my $mTime = stat($returnPath)->mtime;
                if( $mTime > $highestModTime)
                {
                    $highestModTime = $mTime;
                    $selectedFile = $file;
                }
            }
         }
         if( $returnPath ne "" )
         {
            print "Wildcard for file $fileName : Selected newest file: $selectedFile\n";
            return $returnPath;
         }
         else
         {
            die "No file matched wildcard $dir$fileName";
         }
    }
    else # fileName contains no wildcard. Simply return the passed string
    {
        return $pathAndFileName;
    }
}

######################################################################################
# Routine for resolving Tasks names to Task IDs
######################################################################################
sub resolveTaskOrIsrName($$)
{
    my $nameToFind          = shift;
    my $coreId              = shift;
    my $taskRef             = OsGetSysElementReference( 'Task' );

    if( ref $taskRef )
    {
        foreach my $task (keys %{$taskRef})
        {
            my $taskId      = OsGetValue( $taskRef, $task, 'ID' );
            my $taskName    = OsGetValue( $taskRef, $task, 'Name' );
            my $taskCore    = OsGetValue( $taskRef, $task, 'Core' );

            return $taskId if $taskName eq $nameToFind and ( $taskCore eq 'all' or $taskCore == $coreId );
        }
    }

    my $isrRef              = OsGetSysElementReference( 'Interrupt' );
    if( ref $isrRef )
    {
        foreach my $isr (keys %{$isrRef})
        {
            my $isrId       = OsGetValue( $isrRef, $isr, 'ID' );
            my $isrName     = OsGetValue( $isrRef, $isr, 'Name' );
            my $isrCore     = OsGetValue( $isrRef, $isr, 'Core' );

            return $isrId if $isrName eq $nameToFind and ( $isrCore eq 'all' or $isrCore == $coreId );
        }
    }

    return undef; # resolving failed - return undef
}

######################################################################################
# Routine for resolving Task IDs to Task Names
######################################################################################
sub resolveTaskOrIsrId($$)
{
    my $idToFind            = shift;
    my $coreId              = shift;
    my $taskRef             = OsGetSysElementReference( 'Task' );

    if( ref $taskRef )
    {
        foreach my $task (keys %{$taskRef})
        {
            my $taskId      = OsGetValue( $taskRef, $task, 'ID' );
            my $taskName    = OsGetValue( $taskRef, $task, 'Name' );
            my $taskCore    = OsGetValue( $taskRef, $task, 'Core' );

            return $taskName if $taskId eq $idToFind and ( $taskCore eq 'all' or $taskCore == $coreId );
        }
    }

    my $isrRef              = OsGetSysElementReference( 'Interrupt' );
    if( ref $isrRef )
    {
        foreach my $isr (keys %{$isrRef})
        {
            my $isrId       = OsGetValue( $isrRef, $isr, 'ID' );
            my $isrName     = OsGetValue( $isrRef, $isr, 'Name' );
            my $isrCore     = OsGetValue( $isrRef, $isr, 'Core' );

            return $isrName if $isrId eq $idToFind and ( $isrCore eq 'all' or $isrCore == $coreId );
        }
    }

    return 0;
}

######################################################################################
# Parse command line and get invocation file paths
######################################################################################

while( my $arg = shift )
{
    my $val = "";

    if( ($val) = $arg =~ /-UserCfg=(.*)/ )
    {
        open (INVOCATION_FILE, "$val") or die "Error: could not locate user invocation file '$val.'";
        my $currentLine;
        while ($currentLine = <INVOCATION_FILE>)
        {
            &ParseParam($currentLine, $val);
        }
        $systemNo = 0;
        close (INVOCATION_FILE);
    }
    elsif( ($val) = $arg =~ /-OsCfg=(.*)/ )
    {
        $osCfgFile = $val;
    }
    elsif( ($val) = $arg =~ /-Cfg=(.*)/ )
    {
        open (INVOCATION_FILE, "$val") or die "Error: could not locate config invocation file '$val.'";
        my $currentLine;
        while ($currentLine = <INVOCATION_FILE>)
        {
            &ParseParam($currentLine, $val);
        }
        $systemNo = 0;
        close (INVOCATION_FILE);
    }
    elsif( $arg eq "-I" )
    {
        if( $arg = shift and -d $arg )
        {
            push @includeDirs, (rel2abs($arg));
        }
    }
    elsif( $arg =~ /^-I(.*)$/ )
    {
        if( -d $1 )
        {
            push @includeDirs, (rel2abs($1));
        }
    }
    elsif( ($val) = $arg =~ /-OsPm=(.*)/ )  # use appropriate OS-module
    {
        if( $val  =~ /T1_Microsar/ )
        {
            require T1_Microsar;
            import T1_Microsar;
        }
        elsif( $val =~ /T1_ProOsek/ )
        {
            require T1_ProOsek;
            import T1_ProOsek;
        }
        elsif( $val =~ /T1_Tresos/ )
        {
            require T1_Tresos;
            import T1_Tresos;
        }
        elsif( $val =~ /T1_SafeOs/ )
        {
            require T1_SafeOs;
            import T1_SafeOs;
        }
        elsif( $val =~ /T1_RtaOs/ )
        {
            require T1_RtaOs;
            import T1_RtaOs;
        }
        elsif( $val =~ /T1_gliwOS/ )
        {
            require T1_gliwOS;
            import T1_gliwOS;
        }
        elsif( $val =~ /T1_Odin/ )
        {
            require T1_Odin;
            import T1_Odin;
        }
        elsif( $val =~ /T1_dummyOS/ )
        {
            require T1_dummyOS;
            import T1_dummyOS;
        }
        elsif( $val =~ /T1_FreescaleOS/ )
        {
            require T1_FreescaleOS;
            import T1_FreescaleOS;
        }
        elsif( $val =~ /T1_PXROSHR/)
        {
            require T1_PXROSHR;
            import T1_PXROSHR;
        }
        else
        {
            if( $val eq "")
            {
                die "no OS-specific Perl-module on command line specified! Eg: -OsPm=T1_Microsar\n"
            }
            else
            {
                die "incorrect OS-specific Perl-module via -OsPm specified on command line!\n"
            }
        }
    }
    elsif( $arg =~ /-([^=]+)=(.*)/ ) # any non-OS parameter
    {
        undef $systemNo; # ensure that this is handled as a non system-specific parameter
        &ParseParam( "-$1=$2" );
    }
}

######################################################################################
# Process header files to be included / inlined
######################################################################################

my $includeAllHeaders = '';

foreach my $inlineHeader (@inlineHeaders)
{
    my $absPath = rel2abs($inlineHeader);

    open (INLINE_HEADER, "$absPath") or die "Error: could not open file '$absPath' for input";

    $includeAllHeaders .= "#include \"" . File::Basename::basename($absPath) . "\"\n";

    $externDataAvailable = 1;

    while (my $currentLine = <INLINE_HEADER>)
    {
        chomp $currentLine;
        $currentLine=~ s/ö/oe/g;
        $currentLine=~ s/ü/ue/g;
        $currentLine=~ s/ä/ae/g;
        $currentLine=~ s/Ö/Oe/g;
        $currentLine=~ s/Ü/Ue/g;
        $currentLine=~ s/Ä/Ae/g;

        $externData .= $currentLine."\n";

        if( $currentLine =~ /^\s*#\s*define\s*T1_NOF_USER_STPWS_CORE(\d+)\s+\(*\s*(\d+)/ )
        {
            my $coreId = $1;
            my $nofUserStopwatches = $2;
            if( $numberOfUserStpws[$coreId] != 1 and $numberOfUserStpws[$coreId] != $nofUserStopwatches )
            {
                die "Inconsistent number of stopwatches on core $coreId";
            }
            $numberOfUserStpws[$coreId] = -$nofUserStopwatches;
        }
    }
    close (INLINE_HEADER);
}

my $prjFilePath = File::Basename::dirname($projectFile);
$prjFilePath =~ s/\s//g;

foreach my $incFile (@includeHeaders)
{
    my $absPath = rel2abs($incFile);
    my $relPath = resolvePathRelToProjectFile($absPath, $prjFilePath, $copyIncludeHeader);

    open INCLUDE_HEADER, "$absPath" or die "Error: could not open file '$absPath' for input";

    $includeAllHeaders .= "#include \"" . File::Basename::basename($absPath) . "\"\n";

    while (my $currentLine = <INCLUDE_HEADER>)
    {
        if( $currentLine =~ /^\s*#\s*define\s*T1_NOF_USER_STPWS_CORE(\d+)\s+\(*\s*(\d+)/ )
        {
            my $coreId = $1;
            my $nofUserStopwatches = $2;
            if( $numberOfUserStpws[$coreId] != 1 and $numberOfUserStpws[$coreId] != $nofUserStopwatches )
            {
                die "Inconsistent number of stopwatches on core $coreId";
            }
            $numberOfUserStpws[$coreId] = -$nofUserStopwatches;
        }
    }
    close INCLUDE_HEADER;

    $includeHeader  .= "      <HeaderInclude>$relPath</HeaderInclude>\n";
}

######################################################################################
# Read OS configuration, process Tasks, ISRs and Runnables
######################################################################################

OsReadOsConfiguration($osCfgFile, @includeDirs);

my $taskRef     = OsGetSysElementReference('Task');
my $isrRef      = OsGetSysElementReference('Interrupt');
my $runnableRef = OsGetSysElementReference('Runnable');
my $symGroupRef = OsGetSysElementReference('SymbolGroup');
my $osRef       = OsGetSysElementReference('OS');

# get general OS configurations
my $genSource = OsGetValue( $osRef, 'Info',  'GenSource' );
my $genDate = OsGetValue( $osRef, 'Info',  'GenDate' );
my $nofCores = OsGetValue( $osRef, 'Info',  'NofCores' );
my @isCoreUnused = (0) x MAX_NOF_CORES;
if( OsGetValue( $osRef, 'Info',  'UnusedCoreLookupTable' ) )    # get OS-coreID to physical CoreID mapping. -1 indicated that a core is unused.
{
    my $ref = OsGetValue( $osRef, 'Info',  'UnusedCoreLookupTable' );
    @isCoreUnused = @$ref;
}

sub tasksByIdThenName($$)
{
    my $a = shift;
    my $b = shift;
    my $idA = OsGetValue( $taskRef, $a, 'ID' );
    my $idB = OsGetValue( $taskRef, $b, 'ID' );
    return $idA <=> $idB unless $idA == $idB;
    return OsGetValue( $taskRef, $a, 'Name' ) cmp OsGetValue( $taskRef, $b, 'Name' );
}

if( ref $taskRef )
{
    my $runnableIndex = 65536;
    # Sort by task ID
    foreach my $task (sort tasksByIdThenName keys %{$taskRef})
    {
        my $taskPrio    = OsGetValue( $taskRef, $task,  'Priority' );
        my $taskName    = OsGetValue( $taskRef, $task,  'Name' );
        my $taskSymName = OsGetValue( $taskRef, $task,  'SymbolName' );
        my $taskId      = OsGetValue( $taskRef, $task,  'ID' );
        my $taskPeriod  = OsGetValue( $taskRef, $task,  'Period' );
        my $taskOffset  = OsGetValue( $taskRef, $task,  'Offset' );
        my $taskCore    = OsGetValue( $taskRef, $task,  'Core' );
        my $taskMaxAct  = OsGetValue( $taskRef, $task,  'MaxActivations' );
        my $taskComment = OsGetValue( $taskRef, $task,  'Comment' );
        my $taskType    = OsGetValue( $taskRef, $task,  'Type' );
        my $taskRunnablesRef = OsGetValue( $taskRef, $task, 'Runnables' );
        my @taskRunnables = ();
        @taskRunnables = @$taskRunnablesRef if ref $taskRunnablesRef;

        my $taskDesc = $taskName;
        my $exclFromCpuLoadStr = "";
        if( $taskComment ne "" )
        {
            $taskDesc .= ": $taskComment";
            $taskComment = "/* $taskComment */";
        }
        if( $taskCore eq "all" )
        {
            for my $system (0 .. ($nofCores-1))
            {
                $exclFromCpuLoadStr = ""; # Ensure that ExcludeFromCpuLoad is present only on the cores where this parameter is defined
                if( $osBackgroundTaskName[$system] eq $taskName )
                {
                    $exclFromCpuLoadStr= " ExcludeFromCpuLoad=\"true\"";
                }
                elsif( defined($osBackgroundTaskId[$system]) and ( resolveTaskOrIsrId( $osBackgroundTaskId[$system], $system ) eq $taskName ) )
                {
                    $exclFromCpuLoadStr= " ExcludeFromCpuLoad=\"true\"";
                }
                if( $taskId >= $numberOfTasks[$system] ) # find highest scope ID of all tasks from OS-specific Perl-module
                {
                   $numberOfTasks[$system] = $taskId + 1;
                }
                if( 0 != scalar @taskRunnables )
                {
                    $sysElems[$system] .= "      <SystemElement Name=\"$taskDesc\" Priority=\"$taskPrio\" ID=\"$taskId\" Type=\"$taskType\" MaxActivations=\"$taskMaxAct\"$exclFromCpuLoadStr SymbolRef=\"${symbolPrefix}$taskSymName\">\n";
                    foreach my $runnableName (@taskRunnables)
                    {
                        my $symbolRefString = "SymbolRef=\"${symbolPrefix}$runnableName\" ";
                        ### !! For internal testing only !! ###
                        $symbolRefString = '' if $runnableName eq 'SyT_RunnableWithoutSymbolRef';
                        $sysElems[$system] .= "        <SystemElement Name=\"$runnableName\" ID=\"$runnableIndex\" Type=\"Runnable\" $symbolRefString/>\n";
                        ++$runnableIndex;
                    }
                    $sysElems[$system] .= "      </SystemElement>\n";
                }
                else
                {
                    $sysElems[$system] .= "      <SystemElement Name=\"$taskDesc\" Priority=\"$taskPrio\" ID=\"$taskId\" Type=\"$taskType\" MaxActivations=\"$taskMaxAct\"$exclFromCpuLoadStr SymbolRef=\"${symbolPrefix}$taskSymName\"/>\n";
                }
            }
        }
        else
        {
            if( $osBackgroundTaskName[$taskCore] eq $taskName )
            {
                $exclFromCpuLoadStr= " ExcludeFromCpuLoad=\"true\"";
            }
            elsif( defined($osBackgroundTaskId[$taskCore]) and ( resolveTaskOrIsrId( $osBackgroundTaskId[$taskCore], $taskCore ) eq $taskName ) )
            {
                $exclFromCpuLoadStr= " ExcludeFromCpuLoad=\"true\"";
            }
            if( $taskId >= $numberOfTasks[$taskCore] ) # find highest scope ID of all tasks from OS-specific Perl-module
            {
               $numberOfTasks[$taskCore] = $taskId + 1;
            }
            if( 0 != scalar @taskRunnables )
            {
                $sysElems[$taskCore] .= "      <SystemElement Name=\"$taskDesc\" Priority=\"$taskPrio\" ID=\"$taskId\" Type=\"$taskType\" MaxActivations=\"$taskMaxAct\"$exclFromCpuLoadStr SymbolRef=\"${symbolPrefix}$taskSymName\">\n";
                foreach my $runnableName (@taskRunnables)
                {
                    ### !! For internal testing only !! ###
                    my $symbolRefString = "SymbolRef=\"${symbolPrefix}$runnableName\" ";
                    $symbolRefString = '' if $runnableName eq 'SyT_RunnableWithoutSymbolRef';
                    $sysElems[$taskCore] .= "        <SystemElement Name=\"$runnableName\" ID=\"$runnableIndex\" Type=\"Runnable\" $symbolRefString/>\n";
                    ++$runnableIndex;
                }
                $sysElems[$taskCore] .= "      </SystemElement>\n";
            }
            else
            {
                $sysElems[$taskCore] .= "      <SystemElement Name=\"$taskDesc\" Priority=\"$taskPrio\" ID=\"$taskId\" Type=\"$taskType\" MaxActivations=\"$taskMaxAct\"$exclFromCpuLoadStr SymbolRef=\"${symbolPrefix}$taskSymName\"/>\n";
            }
        }
        $t1ConfigHIds .= sprintf "#define %-45s (%3uu)%s\n", "T1_${taskName}_ID", $taskId, $taskComment;
    }
}

# Get application ISRs

sub isrsByIdThenName($$)
{
    my $a = shift;
    my $b = shift;
    my $idA = OsGetValue( $isrRef, $a, 'ID' );
    my $idB = OsGetValue( $isrRef, $b, 'ID' );
    return $idA <=> $idB unless $idA == $idB;
    return OsGetValue( $isrRef, $a, 'Name' ) cmp OsGetValue( $isrRef, $b, 'Name' );
}

if( ref $isrRef )
{
    foreach my $isr (sort isrsByIdThenName keys %{$isrRef})
    {
        my $start;
        my $stop;
        my $isrPrio    = OsGetValue( $isrRef, $isr,  'Priority' );
        my $isrName    = OsGetValue( $isrRef, $isr,  'Name' );
        my $isrSymName = OsGetValue( $isrRef, $isr,  'SymbolName' );
        my $isrId      = OsGetValue( $isrRef, $isr,  'ID' );
        my $isrCore    = OsGetValue( $isrRef, $isr,  'Core' );
        my $isrComment = OsGetValue( $isrRef, $isr,  'Comment' );
        my $isrCategory= OsGetValue( $isrRef, $isr,  'Category' );
        my $isrType    = OsGetValue( $isrRef, $isr,  'Type' );
        my $irsContext = OsGetValue( $isrRef, $isr,  'Context' );
        my $isrDesc    = $isrName;

        if( $isrComment ne "" )
        {
            $isrDesc .= ": $isrComment";
            $isrComment = "/* $isrComment */";
        }

        if( $isrCore eq "all")  # ISR is to be assigned to all systems
        {
            $start = 0;
            $stop = $nofCores-1;
        }
        else    # ISR is to be assigned to a specific system
        {
            $start = $isrCore;
            $stop = $isrCore;
        }

        # now get the task ID offsets (required for some OS trace interfaces
        # the script requires to have the scope IDs arranged in following order (starting from 0):
        #   - tasks from OS-specific Perl-module
        #   - CAT2 ISRs from OS-specific Perl-module
        #   - CAT1 ISRs from OS-specific Perl-module
        #   - external CAT1 ISRs (not from OS-specific Perl-module)

        for my $system ($start .. $stop)
        {
            if( $isrId >= $numberOfTasks[$system] ) # find highest scope ID of all tasks from OS-specific Perl-module
            {
               $numberOfTasks[$system] = $isrId + 1;
            }
            if($isrId < $cat1IsrIdOffset[$system] && $isrCategory == 1) # find lowest cat1 ISR ID from OS-specific Perl-module
            {
               $cat1IsrIdOffset[$system] = $isrId;
            }
            if($isrId < $cat2IsrIdOffset[$system] && $isrCategory == 2) # find lowest cat2 ISR ID from OS-specific Perl-module
            {
               $cat2IsrIdOffset[$system] = $isrId;
            }
            if($isrId < $externalIsrIdOffset[$system] && $irsContext eq "External") # find lowest external ISR ID from OS-specific Perl-module
            {
                $externalIsrIdOffset[$system] = $isrId;
            }
            if($isrId > $highestIsrIdCat2[$system] && $isrCategory == 2) # find highest cat2 ISR ID from OS-specific Perl-module
            {
               $highestIsrIdCat2[$system] = $isrId;
            }
            if($isrId > $highestIsrIdCat1[$system] && $isrCategory == 1) # find highest cat1 ISR ID from OS-specific Perl-module
            {
                $highestIsrIdCat1[$system] = $isrId;
            }
            $sysElems[$system] .= "      <SystemElement Name=\"$isrDesc\" Priority=\"$isrPrio\" ID=\"$isrId\" Type=\"$isrType\" SymbolRef=\"${symbolPrefix}$isrSymName\" />\n";
        }

        $t1ConfigHIds .= sprintf "#define %-45s (%3uu)%s\n", "T1_${isrName}_ID", $isrId, $isrComment;
    }
}

# verify and modify task and ISR IDs and get the overall number of tasks (required by T1.cont)
for my $system (0 .. ($nofCores-1))
{
    my $coreSuffix ="";
    my $cat1IsrsAvailable = 1;

    my $nofTasksFromOsModule = $numberOfTasks[$system];
    my $lowestCat1ISRID;
    if( $additionalCat1IsrIdOffset[$system]) # external ISRs do have a fixed offset. Just add the number of external ISRs in order to get the overall number of tasks
    {
        $lowestCat1ISRID = $additionalCat1IsrIdOffset[$system];
    }
    else # IDs are assigned in order with scope IDs from OS-specific module
    {
        $lowestCat1ISRID = $nofTasksFromOsModule;
    }

    my $nOfAllocatedCat1IsrIDs = 0;
    foreach my $allocateCat1IsrIdPrio ( sort keys %{$allocateCat1IsrIdPrio[$system]} )
    {
        $allocateCat1IsrIdPrio[$system]{$allocateCat1IsrIdPrio} = $lowestCat1ISRID + $nOfAllocatedCat1IsrIDs++;
    }
    $nofAdditionalCat1Isrs[$system] += $nOfAllocatedCat1IsrIDs;

    my $nofTasksWithExternalTasks = $lowestCat1ISRID + $nofAdditionalCat1Isrs[$system];

    $coreSuffix ="_CORE".$system;

    if( $highestIsrIdCat2[$system] == 0 )  # no cat2 ISR received from OS specific module
    {
        $highestIsrIdCat2[$system] = $nofTasksFromOsModule - 1;  # set number of tasks -1 instead
    }
    if( $cat2IsrIdOffset[$system] == 1000) # if initial value -> no cat2 ISRs received from OS-specific module
    {
        $cat2IsrIdOffset[$system] = $nofTasksFromOsModule;  # set number of tasks instead
    }
    if( $cat1IsrIdOffset[$system] == 1000) # if initial value -> no cat1 ISRs received from OS-specific module
    {
        $cat1IsrIdOffset[$system] = $highestIsrIdCat2[$system] + 1;  # set highest cat2 level instead
    }
    if( $highestIsrIdCat1[$system] == 0) # if initial value -> no cat1 ISRs received from OS-specific module
    {
        $cat1IsrsAvailable = 0;
        $highestIsrIdCat1[$system] = $cat1IsrIdOffset[$system];  # set highestIsrIdCat2 instead
    }
    if( $additionalCat1IsrIdOffset[$system]) # external CAT1 ISRs are at fixed offset in this system
    {
        $externalIsrIdOffset[$system] = $additionalCat1IsrIdOffset[$system];  # set fixed offset
    }
    elsif( $externalIsrIdOffset[$system] == 1000) # if initial value -> no additional ISRs configured via -externalIsrIdOffset
    {
        $externalIsrIdOffset[$system] = $highestIsrIdCat1[$system] + $cat1IsrsAvailable;
    }

    if( $isCoreUnused[$system] ne "1" )
    {
        $numberOfTasks[$system] = $nofTasksWithExternalTasks;
    }
    else # this core is unused. Reduce T1.cont result buffer allocation to minimum
    {
        $numberOfTasks[$system] = 1;
        $cat1IsrIdOffset[$system] = 0;
        $cat2IsrIdOffset[$system] = 0;
        $externalIsrIdOffset[$system] = 0;
    }

    $t1ConfigHIds  .= "/* Core $system: */\n";
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_NOF_TASKS$coreSuffix", addU( $numberOfTasks[$system] );
    my $maxTaskPreemptions = int( 4 + $numberOfTasks[$system] / 5 );
    $maxTaskPreemptions = 20 if $maxTaskPreemptions < 20;
    $maxTaskPreemptions = $maxPreemptionDepth{$system} if exists $maxPreemptionDepth{$system}; # Allow override
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_MAX_TASK_PREEMPTIONS$coreSuffix", addU( $maxTaskPreemptions );
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_CAT1_ISR_ID_OFFSET$coreSuffix", addU( $cat1IsrIdOffset[$system] );
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_CAT2_ISR_ID_OFFSET$coreSuffix", addU( $cat2IsrIdOffset[$system] );
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_EXT_ISR_ID_OFFSET$coreSuffix", addU( $externalIsrIdOffset[$system] );
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_CAT1_TO_TRACE_ID$coreSuffix( id_ )", "T1_CAT1_ISR_ID_OFFSET$coreSuffix + (id_)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_CAT2_TO_TRACE_ID$coreSuffix( id_ )", "T1_CAT2_ISR_ID_OFFSET$coreSuffix + (id_)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_EXT_ISR_TO_TRACE_ID$coreSuffix( id_ )", "T1_EXT_ISR_ID_OFFSET$coreSuffix + (id_)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_NS_TO_TICKS$coreSuffix( ns_ )", "(T1_tickUint_t)(((ns_) * 1.0f) / T1_TICK_DURATION${coreSuffix}_NS)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_US_TO_TICKS$coreSuffix( us_ )", "(T1_tickUint_t)(((us_) * 1000.0f) / T1_TICK_DURATION${coreSuffix}_NS)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_MS_TO_TICKS$coreSuffix( ms_ )", "(T1_tickUint_t)(((ms_) * 1000000.0f) / T1_TICK_DURATION${coreSuffix}_NS)";


    foreach my $cat1IsrIdPrio ( sort keys %{$allocateCat1IsrIdPrio[$system]} )
    {
        ( my $cat1IsrName, my $cat1IsrPrio ) = split /,/, $cat1IsrIdPrio;
        $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_CAT1_${cat1IsrName}_ID", addU( $allocateCat1IsrIdPrio[$system]{$cat1IsrIdPrio} );

        $cat1IsrPrio += 2000;
        $extraSysElems[$system] .= "      <SystemElement Name=\"$cat1IsrName\" Priority=\"$cat1IsrPrio\" ID=\"$allocateCat1IsrIdPrio[$system]{$cat1IsrIdPrio}\" Type=\"Interrupt\" />\n";
    }
}

# Get application runnables

sub runnablesByIdThenName($$)
{
    my $a = shift;
    my $b = shift;
    my $idA = OsGetValue( $runnableRef, $a, 'ID' );
    my $idB = OsGetValue( $runnableRef, $b, 'ID' );
    return $idA <=> $idB unless $idA == $idB;
    return OsGetValue( $runnableRef, $a, 'Name' ) cmp OsGetValue( $runnableRef, $b, 'Name' );
}

if( ref $runnableRef)
{
    foreach my $runnable (sort runnablesByIdThenName keys %{$runnableRef})
    {
        my $runnablePosInTask = OsGetValue( $runnableRef, $runnable,  'PosInTask' );
        my $runnableName      = OsGetValue( $runnableRef, $runnable,  'Name' );
        my $runnableSymName   = OsGetValue( $runnableRef, $runnable,  'SymbolName' );
        my $runnableId        = OsGetValue( $runnableRef, $runnable,  'ID' );
        my $runnableCore      = OsGetValue( $runnableRef, $runnable,  'Core' );
        my $runnableComment   = OsGetValue( $runnableRef, $runnable,  'Comment' );
        my $runnableType      = OsGetValue( $runnableRef, $runnable,  'Type' );
        my $runnableTaskRef   = OsGetValue( $runnableRef, $runnable,  'TaskRef' );

        my $runnableDesc = $runnableName;
        if( $runnableComment ne "" )
        {
            $runnableDesc .= ": $runnableComment";
            $runnableComment = " /* $runnableComment */";
        }
        if( $runnableHeader ne "" ) # optionally create header for redefinition of start/stop macros and add corresponding system elemts to t1p:
        {
            if( $runnableCore eq "all" ) # if core is not identified add runnable to all cores in t1p
            {
                for my $counter (0 .. ($nofCores-1))
                {
                    $sysElems[$counter] .= "      <SystemElement Name=\"$runnableDesc\" ID=\"$runnableId\" Type=\"$runnableType\" />\n";
                }
            }
            else
            {
                $sysElems[$runnableCore] .= "      <SystemElement Name=\"$runnableDesc\" ID=\"$runnableId\" Type=\"$runnableType\" />\n";
            }
            $t1runnableIds .= sprintf "#define %-45s (%3uu)%s\n", "T1_${runnableName}_ID", $runnableId, $runnableComment;
        }
    }
}

# append ISR wrapper macros from OS-Module
$t1IsrWrapper .= OsGetIsrWrapper();


#  Perform OS instrumentation
OsPerformInstrumentation();

######################################################################################
# Create T1 project file
######################################################################################

my $t1pDoesNotExist = 0;
my @reportConfigFromPrevT1p = ('') x MAX_NOF_CORES;
my %symGroupsFromPrevT1p = ();
my %tasksIsrsNameByIdFromPrevT1p = ();
my %symGroupsFromOsModule = ();
my %evtChainsFromPrevT1p = ();
my %annotationFilesFromPrevT1p = ();

if( $generateBuildId eq "true" )
{
    $buildId = int(rand(4294967295));
    die "Build ID out of uint32_t range" unless $buildId <= 4294967295;
}

my $t1BidHDefs = sprintf "#define %-45s %s\n", "T1_BUILD_ID", $buildId;


if( -e $projectFile && $readPreviousT1p eq "true" ) # check if project file exists and if user-configured parts shall be copied to new t1p
{
    # extract user-configurable information from previous t1p:
    my $sysIdx = -1;
    my $extractReportCfg = 0;
    my $extractSymGroup = 0;
    my $extractEvtChain = 0;
    my $curLine = "";
    my $curSymGroupName = "";
    my $curEvtChainName = "";

    open PREV_T1P, $projectFile or die "Unable to read \"$projectFile\"";
    while( $curLine = <PREV_T1P> )
    {
        if( $curLine =~ /\<System Name/ )
        {
            $sysIdx ++;
        }

        # extract report configuration:
        if( $curLine =~ /\<ReportConfiguration\>/ )
        {
            $extractReportCfg = 1;
        }
        if( $extractReportCfg )
        {
            $reportConfigFromPrevT1p[$sysIdx] .= $curLine;
        }
        if( $curLine =~ /\<\/ReportConfiguration\>/ )
        {
            $extractReportCfg = 0;
        }

        # extract Symbol Groups:
        if( $curLine =~ /\<SymbolGroup Name=\"(.*)\" IsCode/ )
        {
            $extractSymGroup = 1;
            $curSymGroupName = $1."_$sysIdx";
        }
        if( $extractSymGroup )
        {
            $symGroupsFromPrevT1p{$curSymGroupName} .= $curLine;
        }
        if( $curLine =~ /\<\/SymbolGroup\>/ )
        {
            $extractSymGroup = 0;
        }

        #extract Tasks and Interrupts and their IDs in order to check EventChains for consistency before adding EventChains to newly generated t1p:
        if( $curLine =~ /\<SystemElement Name=\"(.*)\" Priority=\"(.*)\" ID=\"(.*)\" Type/ )
        {
            $tasksIsrsNameByIdFromPrevT1p{$3} = $1;
        }

        # preserve Event Chains:
        if( $curLine =~ /\<EventChainSystemElement Name=\"(.*)\" ID=\"([0-9]+)\"/ )
        {
            $extractEvtChain = 1;
            $curEvtChainName = $1."_$sysIdx"; # append system ID in order to re-assign EventChains to systems
        }
        if( $extractEvtChain )
        {
            if( $curLine =~ /SystemElementID=\"([0-9]+)\" SystemElementType=\"(.*)\" ID=\"([0-9]+)\"/ )
            {
                if( $2 eq "Task" || $2 eq "Interrupt")  # only Interrupts and Tasks can be verified
                {
                    #replace Task and Interrupt IDs by their names and add pattern for identification in t1p generation process:
                    my $replacedId = "\$\$\$".$tasksIsrsNameByIdFromPrevT1p{$1};
                    $curLine =~ s/ SystemElementID=\"([0-9]+)\"/ SystemElementID=\"$replacedId\"/;
                }
            }
            $evtChainsFromPrevT1p{$curEvtChainName} .= $curLine;
        }
        if( $curLine =~ /\<\/EventChainSystemElement\>/ )
        {
            $extractEvtChain = 0;
        }

        # extract Annotation Files:
        if( $curLine =~ /\<AnnotationInclude\>(.*)\<\/AnnotationInclude\>/ )
        {
            $annotationFilesFromPrevT1p{$sysIdx}{$1} = 1;
        }
    }
    close PREV_T1P;
}
else # project file does not exist
{
    $t1pDoesNotExist = 1;
}

#project specific part:
$t1p .="<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
$t1p .="<T1 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" Version=\"2.0\">\n";

# Check for implicit sync timer tick duration
for my $sysNo (0 .. ($nofCores-1))
{
    if( $traceTimerIsSyncTimer[$sysNo] eq 'true' )
    {
        $pSyncTimer = $pTimer[$sysNo] if $pTimer[$sysNo];
        $syncTimerTickDurationNs = $tickDurationNs[$sysNo];
    }
}

$t1p .= "  <Project Name=\"$projectName\" ";
if( $syncTimerTickDurationNs )
{
    my $syncTimerTickDurationNsDecimal;
    eval "\$syncTimerTickDurationNsDecimal = $syncTimerTickDurationNs;";
    $t1p .= "MainTickDuration=\"$syncTimerTickDurationNsDecimal\" ";
}
$t1p .= "SyncTimeBitLength=\"$syncTimeBitLength\" " if $syncTimeBitLength;
$t1p .= "T1targetVersion=\"2\">\n";
$t1p .= "    <Comment>Project file \"$projectFile\" auto-generated from $genSource on $genDate</Comment>\n";

#system specific part:

if( %t1pAnnotationsFiles )# take care of the possible default t1a added in the invocation files for each cores
{
    my $annotationBaseName = File::Basename::basename( $projectFile, ".t1p" );
    my @matchedT1A = ();

    for my $elem (keys %t1pAnnotationsFiles)
    {
        if( $elem =~ /.*$annotationBaseName\_Core[\d+].t1a/ )
        {
            push( @matchedT1A, $elem );
            print "Warning: default annotation file $elem in invocation file\n";
        }
    }
    delete @t1pAnnotationsFiles{@matchedT1A};
}


#process each system and create corresponding systems elements
for my $sysNo (0 .. ($nofCores-1))
{
    if( not $isCoreUnused[$sysNo] )
    {
        my $measOvhdHalf = $t1ScopeOverheadNs[$sysNo] /2;
        my $storeTimInfoStr = "";
        my $flexAnaCapStr = "";
        my $traceTimerDownCountingStr = "";
        my $bsfSysElemType = 'SystemElementType="Task"';
        my $endiannessAgnosticComSetupStr = "";
        if( $storeTimingInformation eq "true" )     { $storeTimInfoStr = ' StoreTimingInformation="true"'; }
        if( $flexAnalysisCapacity[$sysNo] != 0 )    { $flexAnaCapStr = "T1flexAnalysisCapacity=\"$flexAnalysisCapacity[$sysNo]\""; }
        if( $traceTimerDownCounting[$sysNo] eq "true" ) { $traceTimerDownCountingStr = ' TimerCountsDown="true"'; }
        if( $endiannessAgnosticComSetup eq "true" ) { $endiannessAgnosticComSetupStr = ' EndiannessAgnosticComSetup="true"'; }

        my $tickDurationNsDecimal;
        eval "\$tickDurationNsDecimal = $tickDurationNs[$sysNo];";
        my $staticRunnableConfig = '';
        $staticRunnableConfig = " StaticRunnableID=\"$staticRunnableID\"" if '' ne $staticRunnableID;
        my $sid = $core0sid + $sysNo;
        $t1p  .= "    <System Name=\"$systemName[$sysNo]\" TickDuration=\"$tickDurationNsDecimal\"$traceTimerDownCountingStr MaxAbsTime=\"65535\" KernelPriority=\"255\" MinPreempPrio=\"1\" SystemType=\"$systemType[$sysNo]\" T1HandlerPeriod=\"$t1HandlerPeriodMs[$sysNo]\"$storeTimInfoStr$endiannessAgnosticComSetupStr SID=\"$sid\" BID=\"$buildId\" LicInfo1=\"$licInfo1\" LicInfo2=\"$licInfo2\"$staticRunnableConfig> <!-- TraceBufferSize=\"$traceBufferEntries[$sysNo]\" -->\n";
        $t1p  .= "      <Comment>$systemComment[$sysNo]</Comment>\n";
        if( $cortex eq 'true' or $bigEndian eq 'true' or $targetType[$sysNo] ne '' )
        {
            $t1p .= "      <TargetSpecifics";
            $t1p .= " Target=\"$targetType[$sysNo]\"" if $targetType[$sysNo] ne '';
            $t1p .= " BigEndian=\"true\"" if $bigEndian eq 'true';
            $t1p .= " NeedsUniqueSuccessorAddress=\"true\"" if $cortex eq 'true';
            $t1p .= " />\n";
        }
        $t1p .= "      <TargetAnalysis $flexAnaCapStr />\n" if $flexAnalysisCapacity[$sysNo];
        if( $traceTimerIsSyncTimer[$sysNo] eq 'true' )
        {
            $t1p .= "      <TraceMergeAttributes TraceTimerIsMainTimer=\"$traceTimerIsSyncTimer[$sysNo]\" />\n";
        }
        if( $osBasicSchedFrameName[$sysNo] ) # only for tasks and ISRs
        {
            my $taskID = resolveTaskOrIsrName( $osBasicSchedFrameName[$sysNo], $sysNo );
            die "Could not resolve task/ISR name $osBasicSchedFrameName[$sysNo] !" unless defined $taskID;
            
            if( ref $isrRef )
            {
                if( defined OsGetValue( $isrRef, $osBasicSchedFrameName[$sysNo], 'Name' ) )
                {
                    $bsfSysElemType = "SystemElementType=\"Interrupt\"";
                }
            }
            
            $osBasicSchedFrameId[$sysNo] = $taskID;
            $t1p .= "      <BasicSchedulingFrameEvent Type=\"$osBasicSchedFrameEventId[$sysNo]\" SystemElementID=\"$osBasicSchedFrameId[$sysNo]\" $bsfSysElemType ID=\"4294967295\" />\n";
        }
        elsif( $osBasicSchedFrameId[$sysNo] )
        {
            if( $osBasicSchedFrameEventId[$sysNo] eq "T1_USEREVENT" )
            {
                $bsfSysElemType = "SystemElementType=\"UserEvent\""; # not required for UserEvents
            }
            $t1p .= "      <BasicSchedulingFrameEvent Type=\"$osBasicSchedFrameEventId[$sysNo]\" SystemElementID=\"$osBasicSchedFrameId[$sysNo]\" $bsfSysElemType ID=\"4294967295\" />\n";
        }
        else
        {
            print "Warning: No Basic Scheduling Frame Name configured for System $sysNo !\n";
        }
        $t1p .= $includeHeader if $includeHeader;
        if( $sysElems[$sysNo] )
        {
            $t1p .= $sysElems[$sysNo];
            if( $extraSysElems[$sysNo] )
            {
                $t1p .= $extraSysElems[$sysNo];
            }
        }

        # check and append all valid Event Chains from previous t1p. Hint: Only Tasks and Interrupt IDs can be verified!
        foreach my $evtChainName (keys %evtChainsFromPrevT1p) # get Event Chains extracted from previous t1p one by one
        {
            my $evtChainSysNo    = substr( $evtChainName, length($evtChainName)-1, 1 ); # get system number of current Event Chain
            my $evtChainOrigName = substr( $evtChainName, 0, length($evtChainName)-2 );

            if( $evtChainSysNo == $sysNo ) # is system number of Event Chain equal to current sysNo?
            {
                if( $evtChainsFromPrevT1p{$evtChainName} =~ /SystemElementID=\"(.*)\" SystemElementType=\"(.*)\" ID=\"([0-9]+)\"/ )
                {
                    my $discardEvtChain = 0;
                    my $newEvtChain = "";
                    my @evtChainEntry = split /\n+/, $evtChainsFromPrevT1p{$evtChainName}; # buffer current Event Chain in array
                    my $idx = 0;

                    foreach my $line (@evtChainEntry)
                    {
                        if( $line =~ /\"\$\$\$(.*)\" S(.*)/ ) # check for pattern indicating Task/Interrupt name from previous t1p
                        {
                            my $newTaskId = resolveTaskOrIsrName( $1, $sysNo ); # try to resolve ID of Task/Interrupt by name
                            if( $newTaskId ) # check if Task/Interrupt name still exists
                            {
                                $line =~ s/\"\$\$\$(.*)\" S(.*)/\"$newTaskId\" S$2/; # replace pattern and Task/Interrupt name by actual ID
                            }
                            else # Task/Interrupt name could not be resolved and thus does not exist any longer in the new configuration
                            {
                                $discardEvtChain = 1;
                                print "could not resolve Task name $1 from previous configuration. Event Chain $evtChainOrigName will be discarded!\n";
                            }
                        }
                        $newEvtChain .= $line."\n";
                        $idx ++;
                    }
                    if( $discardEvtChain == 0)
                    {
                        $t1p  .= $newEvtChain;
                    }
                }
            }
        }

        # global symbol files:
        $t1p .= "      <Symbols>\n";
        foreach my $symbolFile (@symbolFiles)
        {
            my $symFile = getNewestFileMatchingWildcard($symbolFile);
            $symFile = resolvePathRelToProjectFile( rel2abs($symbolFile), $prjFilePath, 'false' );
            $t1p .= "          <SymbolFilePath>$symFile</SymbolFilePath>\n";
        }

        # core-specific symbol files:
        foreach my $symbolFileOnCoreX (@{$symbolFilesCoreX[$sysNo]})
        {
            if( defined($symbolFileOnCoreX) )
            {
                my $symFile = resolvePathRelToProjectFile( rel2abs($symbolFileOnCoreX), $prjFilePath, 'false' );
                $t1p .= "          <SymbolFilePath>$symFile</SymbolFilePath>\n";
            }
        }

        if( %t1pAnnotationsFiles or $annotationFilesFromPrevT1p{$sysNo} )# take care of the default t1a if some t1a are given or if it was in the previous t1p
        {
            my $annotationBaseName = File::Basename::basename( $projectFile, ".t1p" );
            $t1p  .= "         <AnnotationInclude>$annotationBaseName\_Core$sysNo.t1a</AnnotationInclude>\n";
            if( exists $annotationFilesFromPrevT1p{$sysNo}{$annotationBaseName."_Core".$sysNo.".t1a"})# remove from saved file
            {
                delete $annotationFilesFromPrevT1p{$sysNo}{$annotationBaseName."_Core".$sysNo.".t1a"};
            }
            print "default annotation file added $annotationBaseName\_Core$sysNo.t1a\n" if $debug;
        }

        if( %t1pAnnotationsFiles )# if annotations files given
        {
            foreach my $t1pAnnotationsFile ( keys %t1pAnnotationsFiles )
            {
                # include only global and for this system
                if( exists $t1pAnnotationsFiles{$t1pAnnotationsFile}{"global"} or exists $t1pAnnotationsFiles{$t1pAnnotationsFile}{$sysNo} )
                {
                    my $t1pAnnotationsFileResolved = resolvePathRelToProjectFile( rel2abs($t1pAnnotationsFile), $prjFilePath, 'false');
                    my $t1aName = ( split(/\\/, $t1pAnnotationsFileResolved) )[-1];
                    # check on name. If t1a present in last t1p, use the path from invocation files
                    foreach my $savedT1a ( keys %{ $annotationFilesFromPrevT1p{$sysNo} } ) {
                        # if t1a present, put the value at 0 to not use it again
                        if( $t1aName eq ( split( /\\/, $savedT1a ) )[-1] ){
                            $annotationFilesFromPrevT1p{$sysNo}{$savedT1a} = 0;
                            last;
                        }
                    }
                    $t1p  .= "         <AnnotationInclude>$t1pAnnotationsFileResolved</AnnotationInclude>\n";
                    print "annotation file added $t1pAnnotationsFileResolved\n" if $debug;
                }
            }
        }
        if( $annotationFilesFromPrevT1p{$sysNo} )# if saved t1a from previous t1p
        {
            foreach my $savedT1a ( keys %{ $annotationFilesFromPrevT1p{$sysNo} } )
            {
                # add annotation files which were not given in the invocation files
                if( $annotationFilesFromPrevT1p{$sysNo}{$savedT1a} != 0 )
                {
                    $t1p  .= "         <AnnotationInclude>$savedT1a</AnnotationInclude>\n";
                    print "saved annotation file added $savedT1a\n" if $debug;
                }
            }
        }

        if( @t1pSymbolIncludeFiles  )
        {
            foreach my $t1pSymbolIncludeFile (@t1pSymbolIncludeFiles)
            {
                my $t1pSymbolInclude = resolvePathRelToProjectFile( rel2abs($t1pSymbolIncludeFile), $prjFilePath, 'false');
                $t1p  .= "         <Include>$t1pSymbolInclude</Include>\n";
            }
        }

        # symbol part - core-specific includes:
        if( %t1pSymbolIncludeFilesCoreX )
        {
            foreach my $t1pSymbolInclude (keys %t1pSymbolIncludeFilesCoreX)
            {
                # does this include apply to the current system?
                if( $t1pSymbolIncludeFilesCoreX{$t1pSymbolInclude} == $sysNo )
                {
                    my $t1pSymbolInclude = resolvePathRelToProjectFile( rel2abs($t1pSymbolInclude), $prjFilePath, 'false');
                    $t1p  .= "         <Include>$t1pSymbolInclude</Include>\n";
                }
            }
        }

        # symbol groups from OS-module
        if( ref $symGroupRef )
        {
            foreach my $symGroup (sort { OsGetValue( $symGroupRef, $a, 'Name' ) cmp OsGetValue( $symGroupRef, $b, 'Name' ) } keys %{$symGroupRef})
            {
                my $symGroupName        = OsGetValue( $symGroupRef, $symGroup,  'Name' );
                my $symGroupIsCode      = OsGetValue( $symGroupRef, $symGroup,  'IsCode' );
                my $symGroupDuration    = OsGetValue( $symGroupRef, $symGroup,  'MeasureDuration' );
                my $symGroupIntervalCnt = OsGetValue( $symGroupRef, $symGroup,  'FocusIntervalCount' );
                my $symGroupTraceCount  = OsGetValue( $symGroupRef, $symGroup,  'TraceCount' );
                my $symGroupCore        = OsGetValue( $symGroupRef, $symGroup,  'Core' );
                my $symGroupElementRef  = OsGetValue( $symGroupRef, $symGroup,  'SymbolGroupElemRef');

                if( $symGroupCore eq "all" || $symGroupCore == $sysNo )
                {
                    my $catName = $symGroupName."_".$sysNo;
                    $symGroupsFromOsModule{ $catName } = $symGroupName;

                    $t1p .= "         <SymbolGroups Name=\"$symGroupName\" IsCode=\"$symGroupIsCode\" MeasureDuration=\"$symGroupDuration\" FocusIntervalCount=\"$symGroupIntervalCnt\" TraceCount=\"$symGroupTraceCount\">\n";
                    foreach my $symbol (@$symGroupElementRef)
                    {
                        $t1p .= "            <Symbol>${symbolPrefix}$symbol</Symbol>\n";
                    }
                    $t1p .= "         </SymbolGroups>\n";

                }
            }
        }
        # then append all user-configured Symbol Groups:
        foreach my $userSymbGroupName (keys %symGroupsFromPrevT1p) # get all Symbol Groups from previous t1p
        {
            my $symGroupSysNo = substr( $userSymbGroupName, (length $userSymbGroupName)-1, 1 ); # get system number of current Symbol Group

            if( $symGroupSysNo == $sysNo ) # is system number of user-defined Symbol Group equal current sysNo?
            {
                if( not exists $symGroupsFromOsModule{$userSymbGroupName} ) # check if Symbol Group has already been added by OS-module
                {
                    $t1p .= $symGroupsFromPrevT1p{$userSymbGroupName}; # add Symbol Group if not yet present
                }
            }
        }
        $t1p  .= "      </Symbols>\n";

        # measure overhead part
        $t1p  .= "      <MeasureOverheads Extended=\"true\">\n";
        $t1p  .= "         <MainMeasureOverhead>\n";
        $t1p  .= "            <T1>$measOvhdHalf</T1>\n";
        $t1p  .= "            <T2>$measOvhdHalf</T2>\n";
        $t1p  .= "         </MainMeasureOverhead>\n";
        $t1p  .= "         <T1flexMeasureOverhead>\n";
        $t1p  .= "            <T1>$t1FlexOverheadNs[$sysNo]</T1>\n";
        $t1p  .= "         </T1flexMeasureOverhead>\n";
        $t1p  .= "      </MeasureOverheads>\n";
        # Report configuration part:

        if( $t1pDoesNotExist ) # Check if t1p does already exist: Only add the report configuration the first time the t1p is generated! Otherwise retain the user-configured settings!
        {
            $t1p  .= "      <ReportConfiguration>\n";
            $t1p  .= "          <CsvConfig TimeBase=\"formatted\">\n";
            $t1p  .= "            <SelectedTimingInformation>\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"DeltaTime\" SubType=\"Min\" />\n";
            $t1p  .= "            </SelectedTimingInformation>\n";
            $t1p  .= "          </CsvConfig>\n";
            $t1p  .= "          <HtmlConfig>\n";
            $t1p  .= "            <SelectedTimingInformation>\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"DeltaTime\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"DeltaTime\" SubType=\"Average\" />\n";
            $t1p  .= "            </SelectedTimingInformation>\n";
            $t1p  .= "          </HtmlConfig>\n";
            $t1p  .= "        </ReportConfiguration>\n";
        }
        else
        {
            $t1p  .= $reportConfigFromPrevT1p[$sysNo];
        }

        if($externDataAvailable)
        {
            $t1p  .= "    <ExternalData>\n";
            $t1p  .= "       <HeaderContent><![CDATA[\n";
            $t1p  .= $externData."\n";
            $t1p  .= "       ]]></HeaderContent>\n";
            $t1p  .= "     </ExternalData>\n";
        }

        my $conSysNo                    = 0; # if useSameConnectionForAllSystems is declared false in *.inv the settings at index 0 are used for all systems
        if( $useSameConnectionForAllSystems eq 'false' )
        {
            $conSysNo = $sysNo;
        }
        my $targetId                    = ($core0sid + $sysNo) % 32;
        my $intCanRxId                  = hex($canRxID[$conSysNo]);
        my $intCanTxId                  = hex($canTxID[$conSysNo]);
        my $intDiagSourceAddr           = hex($diagSourceAddr[$conSysNo]);
        my $intDiagTargetAddr           = hex($diagTargetAddr[$conSysNo]);
        my $intDiagT1Identifier         = hex($diagT1Identifier[$conSysNo]);
        my $intDiagLocalIdentifier      = hex($diagLocalIdentifier[$conSysNo]);
        my $intDiagCustomSessionId      = hex($diagCustomSessionId[$conSysNo]);

        $t1p  .= "      <CommunicationConfig UseSameRxTxChannel=\"$useSameRxTxChannel[$conSysNo]\">\n";
        $t1p  .= "        <RxChannel>\n";
        $t1p  .= "          <LayerConfig>\n";
        $t1p  .= "            <Name>$connectionType[$conSysNo]</Name>\n";
        $t1p  .= "            <RoutingParameters xmlns:q1=\"Gliwa-CommunicationConfig\" xsi:type=\"q1:GcpRoutingParameterType\">\n";
        $t1p  .= "              <AppId>0</AppId>\n";
        $t1p  .= "              <TargetId>$targetId</TargetId>\n";
        $t1p  .= "            </RoutingParameters>\n";
        if( $rxChannel[$conSysNo] eq 'ETHERNET' ) # if it is an Ethernet RxChannel
        {
            $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:TcpIpRoutingParameterType\">\n";
            $t1p  .= "              <IpAddress>$ethEcuIP[$conSysNo]</IpAddress>\n";
            $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
            $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
            if( $ethUseUdp[$conSysNo] eq 'true' )
            {
                ($t1p  .= "              <UseUdp>$ethUseUdp[$conSysNo]</UseUdp>\n");
            }
            $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>Ethernet</Name>\n";
            $t1p  .= "            <BusType>$rxChannel[$conSysNo]</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>RX</Direction>\n";
            $t1p  .= "        </RxChannel>\n";
        }
        else
        {
            if( $connectionType[$conSysNo] eq 'Diagnosis' )
            {
                $t1p  .= "            <RoutingParameters xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:DgnRoutingParameterType\">\n";
                $t1p  .= "              <AddressingMode>$diagAddressingMode[$conSysNo]</AddressingMode>\n";
                $t1p  .= "              <SouceAddress>$intDiagSourceAddr</SouceAddress>\n";
                $t1p  .= "              <TargetAddress>$intDiagTargetAddr</TargetAddress>\n";
                $t1p  .= "              <UseServicesByLocId>$diagUseServiceByLocalId[$conSysNo]</UseServicesByLocId>\n";
                $t1p  .= "              <T1Identifier>$intDiagT1Identifier</T1Identifier>\n";
                $t1p  .= "              <T1LocalIdentifier>$intDiagLocalIdentifier</T1LocalIdentifier>\n";
                $t1p  .= "              <RxDataSize>$diagMaxRxDataSize[$conSysNo]</RxDataSize>\n";
                $t1p  .= "              <TxDataSize>$diagMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                $t1p  .= "              <minTxDataSize>$diagMinTxDataSize[$conSysNo]</minTxDataSize>\n";
                $t1p  .= "              <OpenSession>$diagOpenSessionType[$conSysNo]</OpenSession>\n";
                if( $diagOpenSessionType[$conSysNo] eq 'Custom' )
                {
                    $t1p  .= "              <CustomSessionId>$intDiagCustomSessionId</CustomSessionId>\n";
                    if( $intDiagCustomSessionId == 0 )
                    {
                        die "Error: Parameter -diagCustomSessionId is not specified for 'Custom' session!";
                    }
                }
                if( $diagTesterPresentPeriod[$conSysNo] == 0 )
                {
                    if( ( $diagOpenSessionType[$conSysNo] ne 'None' ) and ( $diagOpenSessionType[$conSysNo] ne 'Default' ) )
                    {
                        print "Warning: Parameter -diagTesterPresentPeriod is not specified!\n";
                    }
                }
                else
                {
                    $t1p  .= "              <TesterPresentPeriod>$diagTesterPresentPeriod[$conSysNo]</TesterPresentPeriod>\n";
                }
                $t1p  .= "            </RoutingParameters>\n";
            }
            $t1p  .= "            <BusRoutingParameter xmlns:q3=\"Gliwa-CommunicationConfig\" xsi:type=\"q3:CanRoutingParameterType\">\n";
            $t1p  .= "              <CanId>\n";
            $t1p  .= "                <Id>$intCanRxId</Id>\n";
            $t1p  .= "                <isExtended>$canExtendedIds[$conSysNo]</isExtended>\n";
            $t1p  .= "              </CanId>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>$rxChannel[$conSysNo]1</Name>\n";
            $t1p  .= "            <BusType>$rxChannel[$conSysNo]</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>RX</Direction>\n";
            $t1p  .= "        </RxChannel>\n";
        }

        $t1p  .= "        <TxChannel>\n";
        $t1p  .= "          <LayerConfig>\n";
        $t1p  .= "            <Name>$connectionType[$conSysNo]</Name>\n";
        $t1p  .= "            <RoutingParameters xmlns:q1=\"Gliwa-CommunicationConfig\" xsi:type=\"q1:GcpRoutingParameterType\">\n";
        $t1p  .= "              <AppId>0</AppId>\n";
        $t1p  .= "              <TargetId>$targetId</TargetId>\n";
        $t1p  .= "            </RoutingParameters>\n";
        if( $txChannel[$conSysNo] eq 'ETHERNET' ) # if it is an Ethernet TxChannel
        {
            $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:TcpIpRoutingParameterType\">\n";
            $t1p  .= "              <IpAddress>$ethEcuIP[$conSysNo]</IpAddress>\n";
            $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
            $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
            if( $ethUseUdp[$conSysNo] eq 'true' )
            {
                ($t1p  .= "              <UseUdp>$ethUseUdp[$conSysNo]</UseUdp>\n");
            }
            $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>Ethernet</Name>\n";
            $t1p  .= "            <BusType>$txChannel[$conSysNo]</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>TX</Direction>\n";
            $t1p  .= "        </TxChannel>\n";
        }
        else
        {
            if( $connectionType[$conSysNo] eq 'Diagnosis' )
            {
                $t1p  .= "            <RoutingParameters xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:DgnRoutingParameterType\">\n";
                $t1p  .= "              <AddressingMode>$diagAddressingMode[$conSysNo]</AddressingMode>\n";
                $t1p  .= "              <SouceAddress>$intDiagSourceAddr</SouceAddress>\n";
                $t1p  .= "              <TargetAddress>$intDiagTargetAddr</TargetAddress>\n";
                $t1p  .= "              <UseServicesByLocId>$diagUseServiceByLocalId[$conSysNo]</UseServicesByLocId>\n";
                $t1p  .= "              <T1Identifier>$intDiagT1Identifier</T1Identifier>\n";
                $t1p  .= "              <T1LocalIdentifier>$intDiagLocalIdentifier</T1LocalIdentifier>\n";
                $t1p  .= "              <RxDataSize>$diagMaxRxDataSize[$conSysNo]</RxDataSize>\n";
                $t1p  .= "              <TxDataSize>$diagMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                $t1p  .= "              <minTxDataSize>$diagMinTxDataSize[$conSysNo]</minTxDataSize>\n";
                $t1p  .= "              <OpenSession>$diagOpenSessionType[$conSysNo]</OpenSession>\n";
                if( $diagOpenSessionType[$conSysNo] eq 'Custom' )
                {
                    $t1p  .= "              <CustomSessionId>$intDiagCustomSessionId</CustomSessionId>\n";
                }
                if( $diagTesterPresentPeriod[$conSysNo] != 0 )
                {
                    $t1p  .= "              <TesterPresentPeriod>$diagTesterPresentPeriod[$conSysNo]</TesterPresentPeriod>\n";
                }
                $t1p  .= "            </RoutingParameters>\n";
            }
            $t1p  .= "            <BusRoutingParameter xmlns:q3=\"Gliwa-CommunicationConfig\" xsi:type=\"q3:CanRoutingParameterType\">\n";
            $t1p  .= "              <CanId>\n";
            $t1p  .= "                <Id>$intCanTxId</Id>\n";
            $t1p  .= "                <isExtended>$canExtendedIds[$conSysNo]</isExtended>\n";
            $t1p  .= "              </CanId>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>$txChannel[$conSysNo]1</Name>\n";
            $t1p  .= "            <BusType>$txChannel[$conSysNo]</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>TX</Direction>\n";
            $t1p  .= "        </TxChannel>\n";
        }
        $t1p  .= "      </CommunicationConfig>\n";

        $t1p  .= "    </System>\n";
    }
}

if( '' ne $ethHardware )
{
    if( not defined($ethHwName) )
    {
        $ethHwName='Ethernet';
    }
    $t1p  .= "    <Buses FixedBlocksize=\"$ethMustUseFixedBlockSize\">\n";
    $t1p  .= "      <Name>Ethernet</Name>\n";
    $t1p  .= "      <Type>ETHERNET</Type>\n";
    if( $ethUsage eq 'Preferred' )
    {
        $t1p  .= "      <HwIdentifier Usage=\"Preferred\">\n";
    }else
    {
        $t1p  .= "      <HwIdentifier>\n";
    }
    $t1p  .= "        <Name>$ethHwName</Name>\n";
    $t1p  .= "        <PcIpAddress>$ethPcIP</PcIpAddress>\n";
    $t1p  .= "        <HwType>$ethHardware</HwType>\n";
    $t1p  .= "      </HwIdentifier>\n";
    $t1p  .= "      <TxCycleMs>$ethTxCycle</TxCycleMs>\n";
    $t1p  .= "    </Buses>\n";
}


if( $canFDHardware eq 'VECTOR' )
{
    if( not defined($canFDHwName) )
    {
        $canFDHwName='CANcaseXL Channel 1';
    }
    $t1p .= "    <Buses";

    # Retrieve the minimum canFDMaxTxDataSize to set the MaxTxBlocksize corresponding to the size of the CAN FD message from the T1-HOST-SW to the target
    my $minTxDataSize = 64;
    foreach my $maxTxDataSize (@canFDMaxTxDataSize)
    {
        if( 0 < $maxTxDataSize and $maxTxDataSize < $minTxDataSize )
        {
            $minTxDataSize = $maxTxDataSize;
        }
    }
    $t1p .= " MaxTxBlocksize=\"$minTxDataSize\"";

    if( $canFDMustUseFixedBlockSize ne '' )
    {
        $t1p .= " FixedBlocksize=\"$canFDMustUseFixedBlockSize\"";
    }
    $t1p .= ">\n";
    $t1p  .= "      <Name>CAN_FD1</Name>\n";
    $t1p  .= "      <Type>CAN_FD</Type>\n";
    if( $canFDUsage eq '' )
    {
        $t1p  .= "      <HwIdentifier>\n";
    }
    else
    {
        $t1p  .= "      <HwIdentifier Usage=\"$canFDUsage\">\n";
    }
    $t1p  .= "        <Name>$canFDHwName</Name>\n";
    $t1p  .= "        <HwType>VECTOR</HwType>\n";
    $t1p  .= "      </HwIdentifier>\n";
    $t1p  .= "      <TxCycleMs>$txCycle</TxCycleMs>\n";
    $t1p  .= "      <BusConfig xmlns:q13=\"Gliwa-CommunicationConfig\" xsi:type=\"q13:CanBusConfigType\">\n";
    $t1p  .= "        <Bitrate>$canFDBitrate</Bitrate>\n";

    if( $canFDSamplePoint != 0 )
    {
        $t1p  .= "        <SamplePoint>$canFDSamplePoint</SamplePoint>\n";
        if( @canFDBitTiming )
        {
            print "Warning: CAN FD SamplePoint AND BitTiming specified, BitTiming ignored\n";
        }
    }
    elsif( @canFDBitTiming )
    {
        if( scalar @canFDBitTiming != 6 )
        {
            print "Warning: canFDBitTiming does not contain 6 elements, values ignored\n";
        }
        else
        {
            $t1p  .= "        <BitTiming>\n";
            $t1p  .= "          <Brp>".$canFDBitTiming[0]."</Brp>\n";
            $t1p  .= "          <Prop>".$canFDBitTiming[1]."</Prop>\n";
            $t1p  .= "          <Phase1>".$canFDBitTiming[2]."</Phase1>\n";
            $t1p  .= "          <Phase2>".$canFDBitTiming[3]."</Phase2>\n";
            $t1p  .= "          <Sjw>".$canFDBitTiming[4]."</Sjw>\n";
            $t1p  .= "          <Sam>".$canFDBitTiming[5]."</Sam>\n";
            $t1p  .= "        </BitTiming>\n";
        }
    }

    if( $canFDDataBitrate != 0 )
    {
        $t1p  .= "        <DataBitrate>$canFDDataBitrate</DataBitrate>\n";
        if( $canFDDataSamplePoint != 0 )
        {
            $t1p  .= "        <DataSamplePoint>$canFDDataSamplePoint</DataSamplePoint>\n";
            if( @canFDDataBitTiming )
            {
                print "Warning: CAN FD DataSamplePoint AND DataBitTiming specified, DataBitTiming ignored\n";
            }
        }
        elsif( @canFDDataBitTiming )
        {
            if( scalar @canFDDataBitTiming != 6 )
            {
                print "Warning: canFDDataBitTiming does not contain 6 elements, values ignored\n";
            }
            else
            {
                $t1p  .= "        <DataBitTiming>\n";
                $t1p  .= "          <Brp>".$canFDDataBitTiming[0]."</Brp>\n";
                $t1p  .= "          <Prop>".$canFDDataBitTiming[1]."</Prop>\n";
                $t1p  .= "          <Phase1>".$canFDDataBitTiming[2]."</Phase1>\n";
                $t1p  .= "          <Phase2>".$canFDDataBitTiming[3]."</Phase2>\n";
                $t1p  .= "          <Sjw>".$canFDDataBitTiming[4]."</Sjw>\n";
                $t1p  .= "          <Sam>".$canFDDataBitTiming[5]."</Sam>\n";
                $t1p  .= "        </DataBitTiming>\n";
            }
        }
    }

    if( $canFDOscillatorFrequencyMhz != 0 )
    {
        $t1p  .= "        <OscillatorFrequencyMhz>$canFDOscillatorFrequencyMhz</OscillatorFrequencyMhz>\n";
    }
    $t1p  .= "      </BusConfig>\n";
    $t1p  .= "    </Buses>\n";
}

if( $canHardware eq 'VECTOR' )
{
    if( not defined($canHwName) )
    {
        $canHwName='CANcaseXL Channel 1';
    }
    $t1p  .= "    <Buses FixedBlocksize=\"$mustUseFixedBlockSize\">\n";
    $t1p  .= "      <Name>CAN1</Name>\n";
    $t1p  .= "      <Type>CAN</Type>\n";
    $t1p  .= "      <HwIdentifier>\n";
    $t1p  .= "        <Name>$canHwName</Name>\n";
    $t1p  .= "        <HwType>VECTOR</HwType>\n";
    $t1p  .= "      </HwIdentifier>\n";
    $t1p  .= "      <TxCycleMs>$txCycle</TxCycleMs>\n";
    $t1p  .= "      <BusConfig xmlns:q7=\"Gliwa-CommunicationConfig\" xsi:type=\"q7:CanBusConfigType\">\n";
    if( $canBitrate == 500000 )
    {
        $t1p  .= "        <Bitrate>500000</Bitrate>\n";
        $t1p  .= "        <BitTiming>\n";
        $t1p  .= "          <Brp>1</Brp>\n";
        $t1p  .= "          <Prop>0</Prop>\n";
        $t1p  .= "          <Phase1>10</Phase1>\n";
        $t1p  .= "          <Phase2>5</Phase2>\n";
        $t1p  .= "          <Sjw>4</Sjw>\n";
        $t1p  .= "          <Sam>1</Sam>\n";
        $t1p  .= "        </BitTiming>\n";
        $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 250000 )
    {
        $t1p  .= "        <Bitrate>250000</Bitrate>\n";
        $t1p  .= "        <BitTiming>\n";
        $t1p  .= "          <Brp>2</Brp>\n";
        $t1p  .= "          <Prop>0</Prop>\n";
        $t1p  .= "          <Phase1>10</Phase1>\n";
        $t1p  .= "          <Phase2>5</Phase2>\n";
        $t1p  .= "          <Sjw>4</Sjw>\n";
        $t1p  .= "          <Sam>1</Sam>\n";
        $t1p  .= "        </BitTiming>\n";
        $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 800000)
    {
    $t1p  .= "        <Bitrate>800000</Bitrate>\n";
    $t1p  .= "        <BitTiming>\n";
    $t1p  .= "          <Brp>1</Brp>\n";
    $t1p  .= "          <Prop>0</Prop>\n";
    $t1p  .= "          <Phase1>7</Phase1>\n";
    $t1p  .= "          <Phase2>2</Phase2>\n";
    $t1p  .= "          <Sjw>2</Sjw>\n";
    $t1p  .= "          <Sam>1</Sam>\n";
    $t1p  .= "        </BitTiming>\n";
    $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 1000000)
    {
        $t1p  .= "        <Bitrate>1000000</Bitrate>\n";
        $t1p  .= "        <BitTiming>\n";
        $t1p  .= "          <Brp>1</Brp>\n";
        $t1p  .= "          <Prop>0</Prop>\n";
        $t1p  .= "          <Phase1>4</Phase1>\n";
        $t1p  .= "          <Phase2>3</Phase2>\n";
        $t1p  .= "          <Sjw>4</Sjw>\n";
        $t1p  .= "          <Sam>1</Sam>\n";
        $t1p  .= "        </BitTiming>\n";
        $t1p  .= "      </BusConfig>\n";
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in T1-HOST-SW!\n";
    }
    $t1p  .= "    </Buses>\n";
}
elsif( $canHardware eq 'U2C' or ($ethHardware eq '' and $canHardware eq '' and $canFDHardware eq '') )  # if U2C specified or both default for retrocompatibility
{
    if( not defined($canHwName) )
    {
        $canHwName='U2C_';
    }
    $t1p  .= "    <Buses FixedBlocksize=\"$mustUseFixedBlockSize\">\n";
    $t1p  .= "      <Name>CAN1</Name>\n";
    $t1p  .= "      <Type>CAN</Type>\n";
    if( $canUsage eq 'Preferred' )
    {
        $t1p  .= "      <HwIdentifier Usage=\"Preferred\">\n";
    }else
    {
        $t1p  .= "      <HwIdentifier>\n";
    }
    $t1p  .= "        <Name>$canHwName</Name>\n";
    $t1p  .= "        <HwType>U2C</HwType>\n";
    $t1p  .= "      </HwIdentifier>\n";
    $t1p  .= "      <TxCycleMs>$txCycle</TxCycleMs>\n";
    $t1p  .= "      <BusConfig xmlns:q7=\"Gliwa-CommunicationConfig\" xsi:type=\"q7:CanBusConfigType\">\n";
    if( $canBitrate == 500000 )
    {
        $t1p  .= "        <Bitrate>500000</Bitrate>\n";
        $t1p  .= "        <BitTiming>\n";
        $t1p  .= "          <Brp>1</Brp>\n";
        $t1p  .= "          <Prop>1</Prop>\n";
        $t1p  .= "          <Phase1>6</Phase1>\n";
        $t1p  .= "          <Phase2>4</Phase2>\n";
        $t1p  .= "          <Sjw>1</Sjw>\n";
        $t1p  .= "          <Sam>3</Sam>\n";
        $t1p  .= "        </BitTiming>\n";
        $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 250000 )
    {
        $t1p  .= "        <Bitrate>250000</Bitrate>\n";
        $t1p  .= "        <BitTiming>\n";
        $t1p  .= "          <Brp>1</Brp>\n";
        $t1p  .= "          <Prop>7</Prop>\n";
        $t1p  .= "          <Phase1>8</Phase1>\n";
        $t1p  .= "          <Phase2>8</Phase2>\n";
        $t1p  .= "          <Sjw>1</Sjw>\n";
        $t1p  .= "          <Sam>3</Sam>\n";
        $t1p  .= "        </BitTiming>\n";
        $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 100000 )
    {
        $t1p  .= "        <Bitrate>100000</Bitrate>\n";
        $t1p  .= "        <BitTiming>\n";
        $t1p  .= "          <Brp>3</Brp>\n";
        $t1p  .= "          <Prop>3</Prop>\n";
        $t1p  .= "          <Phase1>8</Phase1>\n";
        $t1p  .= "          <Phase2>8</Phase2>\n";
        $t1p  .= "          <Sjw>1</Sjw>\n";
        $t1p  .= "          <Sam>3</Sam>\n";
        $t1p  .= "        </BitTiming>\n";
        $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 1000000 )
    {
        print "Bitrate not supported by U2C. Please contact Gliwa!\n";
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in T1-HOST-SW!\n";
    }
    $t1p  .= "    </Buses>\n";
}

$t1p  .= "  </Project>\n";
$t1p  .= "</T1>\n";

if( $projectFile =~ /\.t1p$/ and $generateBuildId ne 'true' )
{
    # If we generate the .t1p file directly then changes made by the T1-HOST-SW
    # will lead to incorrect re-generation of the .t1p file and a spurious BID
    # mismatch. Therefore we create a "reference" .t0p file and test to see if an old
    # .t0p file is different from the new content.
    my $projectRefFile = $projectFile;
    $projectRefFile =~ s/\.t1p$/.t0p/;
    if( writeUnlessEqual( $projectRefFile, $t1p ) or ! -f $projectFile )
    {
        copy( $projectRefFile, $projectFile );
    }
}
else
{
    writeUnlessEqual( $projectFile, $t1p );
}

######################################################################################
# Create T1_config.h
######################################################################################

#----------------------------------------------------------------------------------
my $traceTaskMacro = "#define T1_TRACE_TASK( taskId_ ) \\\n(  1 \\\n";

foreach my $exclName (@targetExcludeFromTraceByName)
{
    $traceTaskMacro .= " && ((taskId_) != T1_".$exclName."_ID) \\\n";
}
foreach my $exclId (@targetExcludeFromTraceById)
{
   $traceTaskMacro .= " && ((taskId_) != $exclId) \\\n";
}
$traceTaskMacro .= ")\n";

#----------------------------------------------------------------------------------

if( $idHeader ne "" )
{
    my $idHeaderBaseName = "";

    $idHeaderBaseName = File::Basename::basename($idHeader);
    $idHeaderBaseName =~ s/\s//g;

    my $idHeaderMacro = uc($idHeaderBaseName);
    $idHeaderMacro =~ s/\./_/g;
    $idHeaderMacro .= "_";

    my $idHeaderIncl = "";

    foreach my $inc (@idHeaderIncludes)
    {
        $idHeaderIncl .= "#include $inc\n" unless $inc eq "";
    }

    my $t1idHIds = $t1ConfigHIds;  # copy all task ID macros to ID-header
    $t1ConfigHIds = "";            # delete all task ID macros from config header

    my $idHeaderContent = <<EOT;
/*************************************************************************************
 *  FILE:           $idHeaderBaseName
 *
 *  DESCRIPTION:    this header was generated by perl script T1_projGen.pl
 *
 *  AUTHOR:         GLIWA GmbH
 *
 *  COPYRIGHT:      GLIWA GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 ************************************************************************************/

#ifndef $idHeaderMacro
#define $idHeaderMacro (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$idHeaderIncl

/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$t1idHIds

/*----------------------------------------------------------------------------------*/
/*--- Macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$traceTaskMacro

/*----------------------------------------------------------------------------------*/
/*--- Function wrapper -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef T1_ENABLE
$t1IsrWrapper
#endif /* T1_ENABLE */

/*----------------------------------------------------------------------------------*/

#endif /* $idHeaderMacro */
EOT

    writeUnlessEqual( $idHeader, $idHeaderContent );
}

#----------------------------------------------------------------------------------

# Convert values in milliseconds to multiples of communications core T1_Handler period
if( '' eq $timeoutResponse )
{
    warn '-timeoutResponse is deprecated, please use -timeoutResponseMs';
}
if( '' eq $timeoutTx )
{
    warn '-timeoutTx is deprecated, please use -timeoutTxMs';
}
if( '' eq $timeoutRx )
{
    warn '-timeoutRx is deprecated, please use -timeoutRxMs';
}
if( '' ne $timeoutResponseMs )
{
    $timeoutResponse = int( $timeoutResponseMs / $t1HandlerPeriodMs[$commsCoreOffset] );
}
if( '' ne $timeoutTxMs )
{
    $timeoutTx = int( $timeoutTxMs / $t1HandlerPeriodMs[$commsCoreOffset] );
}
if( '' ne $timeoutRxMs )
{
    $timeoutRx = int( $timeoutRxMs / $t1HandlerPeriodMs[$commsCoreOffset] );
}

# Create configuration hash for sharing with T1_config.pm
my %config;
$config{'traceTimerBitLength'} = \@traceTimerBitLength;
$config{'analysisCapacity'} = \@analysisCapacity;
$config{'bidHeader'} = $bidHeader;
$config{'canHardware'} = $canHardware;
$config{'canRxID'} = \@canRxID;
$config{'canTxID'} = \@canTxID;
$config{'canFDHardware'} = $canFDHardware;
$config{'canFDMaxRxDataSize'} = \@canFDMaxRxDataSize;
$config{'canFDMaxTxDataSize'} = \@canFDMaxTxDataSize;
$config{'connectionType'} = \@connectionType;
$config{'contRunsOnCore'} = \%contRunsOnCore;
$config{'cpuLoadAvgSamples'} = \@cpuLoadAvgSamples;
$config{'cpuLoadCallback'} = \@cpuLoadCallback;
$config{'cpuLoadThreshold'} = \@cpuLoadThreshold;
$config{'cpuLoadTxPeriod'} = \@cpuLoadTxPeriod;
$config{'diagMinTxDataSize'} = \@diagMinTxDataSize;
$config{'diagMaxRxDataSize'} = \@diagMaxRxDataSize;
$config{'diagMaxTxDataSize'} = \@diagMaxTxDataSize;
$config{'ethMaxRxDataSize'} = \@ethMaxRxDataSize;
$config{'ethMaxTxDataSize'} = \@ethMaxTxDataSize;
$config{'initFeatureMask'} = $initFeatureMask;
$config{'nofCores'} = 0;
$config{'nofCores'} = $nofCores if 'true' eq $usingMulticoreLibs;
$config{'commsCoreOffset'} = $commsCoreOffset;
$config{'nofDelays'} = \@nofDelays;
$config{'nofFlexAddrs'} = \@nofFlexAddrs;
$config{'nofFlexStopwatches'} = \@nofFlexStopwatches;
$config{'numberOfConstraints'} = \@numberOfConstraints;
$config{'numberOfTasks'} = \@numberOfTasks;
$config{'numberOfUserStpws'} = \@numberOfUserStpws;
$config{'osBackgroundTaskId'} = \@osBackgroundTaskId;
$config{'osBackgroundTaskName'} = \@osBackgroundTaskName;
$config{'osBasicSchedFrameEventId'} = \@osBasicSchedFrameEventId;
$config{'osBasicSchedFrameId'} = \@osBasicSchedFrameId;
$config{'osBasicSchedFrameName'} = \@osBasicSchedFrameName;
$config{'pSyncTimer'} = $pSyncTimer;
$config{'pTimer'} = \@pTimer;
$config{'sid'} = $core0sid;
$config{'staticRunnableID'} = $staticRunnableID;
$config{'syncTimeBitLength'} = $syncTimeBitLength;
$config{'syncTimerTickDurationNs'} = $syncTimerTickDurationNs;
$config{'t1BidHDefs'} = $t1BidHDefs;
$config{'t1FlexOverheadNs'} = \@t1FlexOverheadNs;
$config{'t1ScopeOverheadNs'} = \@t1ScopeOverheadNs;
$config{'tickDurationNs'} = \@tickDurationNs;
$config{'timeoutResponse'} = $timeoutResponse;
$config{'timeoutRx'} = $timeoutRx;
$config{'timeoutTx'} = $timeoutTx;
$config{'traceBufferEntries'} = \@traceBufferEntries;
$config{'traceTimerDownCounting'} = \@traceTimerDownCounting;
$config{'traceTimerIsSyncTimer'} = \@traceTimerIsSyncTimer;
$config{'useSameConnectionForAllSystems'} = $useSameConnectionForAllSystems;
$config{'numberOfFocusMeasurements'} = $numberOfFocusMeasurements;

if( '' ne $configHeader )
{
    my $tempConfigHeader = $configHeader."_";
    my $configHeaderBaseName = "";
    my $t1config_IsrWrapper = "";
    createPath($tempConfigHeader) or die "Unable to create path for file $tempConfigHeader";

    open my $fh, ">$tempConfigHeader" or die "Unable to write file $tempConfigHeader";

    $configHeaderBaseName = File::Basename::basename($configHeader);
    $configHeaderBaseName =~ s/\s//g;

    my $configHeaderMacro = uc($configHeaderBaseName);
    $configHeaderMacro =~ s/\./_/g;
    $configHeaderMacro .= "_";

    my $configHeaderIncl = "";

    foreach my $inc (@configHeaderIncludes)
    {
        $configHeaderIncl .= "#include $inc\n" unless $inc eq "";
    }

    my $localTraceTaskMacro = "";
    if( '' eq $idHeader ) # only copy traceTaskMacro to config header if no ID header is generated
    {
        $localTraceTaskMacro = $traceTaskMacro;
        $t1config_IsrWrapper = $t1IsrWrapper;
    }

    print $fh <<EOT;
/*************************************************************************************
 *  FILE:           $configHeaderBaseName
 *
 *  DESCRIPTION:    this header was generated by perl script T1_projGen.pl
 *
 *  AUTHOR:         GLIWA GmbH
 *
 *  COPYRIGHT:      GLIWA GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 ************************************************************************************/

#ifndef $configHeaderMacro
#define $configHeaderMacro (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$configHeaderIncl

/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$t1ConfigHIds

/*----------------------------------------------------------------------------------*/
/*--- Config macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
    GenT1ConfigH( $fh, \%config );
    print $fh <<EOT;

$localTraceTaskMacro

/*----------------------------------------------------------------------------------*/
/*--- Function wrapper -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE
$t1config_IsrWrapper
#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/

#endif /* $configHeaderMacro */
EOT

    # Re-read temporary file into a string for writeUnlessEqual
    open $fh, $tempConfigHeader or die "Unable to re-read $tempConfigHeader";
    my $configContent = join '', <$fh>;
    close $fh;
    unlink $tempConfigHeader;

    writeUnlessEqual( $configHeader, $configContent );
}

######################################################################################
# Create T1_configGen.c
######################################################################################

$includeAllHeaders .= "#include \"" . File::Basename::basename($bidHeader) . "\"\n" if '' ne $bidHeader;

if( '' ne $configGenC )
{
    my $tempConfigGenC = $configGenC."_";

    open my $fhtempConfigGenC, ">$tempConfigGenC" or die "Unable to write file $tempConfigGenC";
    print $fhtempConfigGenC <<EOT;
/*************************************************************************************
 *  FILE:           $configGenC
 *
 *  DESCRIPTION:    this file was generated by perl script T1_projGen.pl
 *
 *  AUTHOR:         GLIWA GmbH
 *
 *  COPYRIGHT:      GLIWA GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 ************************************************************************************/

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$includeAllHeaders

/*----------------------------------------------------------------------------------*/
/*--- Config variables -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
    GenT1ConfigC( $fhtempConfigGenC, \%config );
    close $fhtempConfigGenC;

    # Re-read temporary file into a string for writeUnlessEqual
    open $fhtempConfigGenC, $tempConfigGenC or die "Unable to re-read $tempConfigGenC";
    my $configGenContent = join '', <$fhtempConfigGenC>;
    close $fhtempConfigGenC;
    unlink $tempConfigGenC;

    writeUnlessEqual( $configGenC, $configGenContent );
}

#----------------------------------------------------------------------------------

if( "" ne $bidHeader )
{
    createPath( $bidHeader ) or die "Unable to create path for file $bidHeader";
    open (BID_HEADER, ">$bidHeader") or die "Error: could not open file '$bidHeader' for output";

    $bidHeader = File::Basename::basename($bidHeader);
    $bidHeader =~ s/\s//g;

    my $bidHeaderMacro = uc($bidHeader);
    $bidHeaderMacro =~ s/\./_/g;
    $bidHeaderMacro .= "_";

    print BID_HEADER <<EOT;
/*************************************************************************************
 *  FILE:           $bidHeader
 *
 *  DESCRIPTION:    this header was generated by perl script T1_projGen.pl
 *
 *  AUTHOR:         GLIWA GmbH
 *
 *  COPYRIGHT:      GLIWA GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 ************************************************************************************/

#ifndef $bidHeaderMacro
#define $bidHeaderMacro (1)

/*----------------------------------------------------------------------------------*/
/*--- Config macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1BidHDefs

/*----------------------------------------------------------------------------------*/

#endif /* $bidHeaderMacro */
EOT

    close (BID_HEADER);
}

######################################################################################
# Create runnable header if required
######################################################################################


if( '' ne $runnableHeader )
{
    my $runnableHeaderBaseName = "";
    my $runnableDefnitions = "";

    eval { $runnableDefnitions = OsGetRunnableDefinitions( ) };

    $runnableHeaderBaseName = File::Basename::basename($runnableHeader);
    $runnableHeaderBaseName =~ s/\s//g;

    my $runnableHeaderMacro = uc($runnableHeaderBaseName);
    $runnableHeaderMacro =~ s/\./_/g;
    $runnableHeaderMacro .= "_";

    my $runnableHeaderIncl = "";

    foreach my $inc (@runnableHeaderIncludes)
    {
        $runnableHeaderIncl .= "#include $inc\n" unless $inc eq "";
    }

    my $runnableHeaderContent = <<EOT;
/**************************************************************************************************
 *  FILE:           $runnableHeaderBaseName
 *
 *  DESCRIPTION:    this header was generated by perl script T1_projGen.pl
 *
 *  AUTHOR:         GLIWA GmbH
 *
 *  COPYRIGHT:      GLIWA GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 *************************************************************************************************
*/

#ifndef $runnableHeaderMacro
#define $runnableHeaderMacro (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$runnableHeaderIncl
/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1runnableIds
/*----------------------------------------------------------------------------------*/
/*--- Macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
#ifdef T1_TRACE_RUNNABLES

$runnableDefnitions

#endif /* T1_TRACE_RUNNABLES    */
/*----------------------------------------------------------------------------------*/

#endif /* $runnableHeaderMacro */
EOT

    writeUnlessEqual( $runnableHeader, $runnableHeaderContent );
}
