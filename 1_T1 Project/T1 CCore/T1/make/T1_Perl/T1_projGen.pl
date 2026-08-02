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
#   $Revision: 370 $
#
#   Copyright:      GLIWA embedded systems GmbH & Co. KG
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

# Perl pragmas
use 5.8.8;
use strict;
use warnings;
use constant MAX_NOF_CORES => 15;

# Core Perl modules
use Encode;                         # Core module since v5.7.3
use File::Spec::Functions ':ALL';   # Core module since v5.6.0
use File::Copy;                     # Core module since v5.2.0
use File::Basename;                 # Core module since v5
File::Basename::fileparse_set_fstype('MSWin32'); # This might prevent the script working under other OSs, e.g. Linux
use File::Path;                     # Core module since v5.1.0
use File::stat;                     # Core module since v5.4.0
use POSIX qw(ceil);                 # Core module since v5
# use Text::ParseWords; Note: Do not use "parse_line" because it is slow, see #2426

# Implicitly loaded modules are listed here for completeness and documentation
use PerlIO;             # Core module since v5.7.3
use PerlIO::encoding;   # Core module since v5.8.0
use PerlIO::scalar;     # Core module since v5.8.0

# Non-core Perl modules
use T1_config;

######################################################################################
# global variables. Values are to be assigned by reading invocation files
######################################################################################

#paths of required files:
my @inlineHeaders = ();                             # the content of those files is copied to the T1 project file (external data). Specify path and file name. Use next parameter optionally
my @includeHeaders = ();                            # these files are referenced in the T1 project file. The T1-HOST-SW parses the contents and searches for systemElements. Specify path and file name. Use previous parameter optionally
my $configGenC = '';                                # name and path of T1_config.c
my $configHeader = '';                              # name and path of header file being generated containing T1 configuration parameter macros (and task/ISR-ID macros if $idHeader is not specified)
my @symbolFiles = ();                               # name and path of symbol files being referenced by the T1 project file -> wild-card allowed: e.g. ".\myFolder\proj*.elf"
my $projectFile = '';                               # name and path of T1 project file being generated

#paths of optional files:
my $runnableHeader = '';                            # name and path of header file being generated containing T1 definitions for runnable start/stop macros (only if supported by OS-specific Perl-module)
my $idHeader = '';                                  # name and path of header file being generated containing T1 task and ISR-ID macros. If specified no ID macros are generated to $configHeader
my $bidHeader = '';                                 # name and path of header file being generated containing T1 Build ID. If not specified the BID will be generated into idHeader
my $t1LibAnnotationsFile = '';                      # name and path of t1a-file being generated containing indirect calls and known memory annotations for T1.stack
my @t1pSymbolIncludeFiles = ();                     # name and path of auxiliary t1p-files containing T1SymbolsPart (such as symbol groups)
my %t1pAnnotationsFiles = ();                       # name and path of auxiliary t1a-files containing indirect calls for T1.stack
my @dpcSymbols = map { {} } ((0) x MAX_NOF_CORES);  # code symbols that must or must not use DPC. Do not use ({}) x MAX_NOF_CORES because it gives MAX_NOF_CORES references to a single hash!
my @retainSymbols = map { {} } ((0) x MAX_NOF_CORES); # symbols to import despite filtering. Do not use ({}) x MAX_NOF_CORES because it gives MAX_NOF_CORES references to a single hash!
my @retainMax = (0) x MAX_NOF_CORES;                # maximum number symbols to import despite filtering (zero means no limit)
my @retainIgnoreCase = ('false') x MAX_NOF_CORES;   # whether retention regexp ignores case

#parameters that use default value if omitted:
my $copySymbolFile = "false";                       # copy symbol-file to T1 project path [true/false]
my $copyIncludeHeader = "false";                    # copy include headers to T1 project path [true/false]
my $generateBuildId = "true";                       # generate Build ID (BID) every time the Perl script is executed. The BID is propagated to the t1p-file and T1_config.h and by that to the executable. The T1-HOST-SW checks if symbol-file and target-code are consistent
my $projectName = "T1 project";                     # any project name
my $licInfo1 = "unknown POT";                       # POT number to identify the project to GLIWA
my $licInfo2 = "unknown LAP";                       # LAP number to identify the project to GLIWA
my $readPreviousT1p = "true";                       # read user-configured parts from previous t1p (if exists) and copy to new t1p
my $syncTimeBitLength = undef;                      # Synchronization of multi-core systems requires a timer resolution of at least 24 bits, default value of 32 is set later
my $traceTimeStampBitLength = 16;                   # 16/32
my $useSameConnectionForAllSystems = 'true';        # are all systems using the same connection? [true/false]
my $txCycleMs = 10;                                 # TX cycle of T1-HOST-SW
my $canBitrate = 500000;                            # CAN bit rate
my $canFDBitrate = 500000;                          # CAN FD bit rate
my $canHardware = '';                               # CAN hardware [U2C/VECTOR/PEAK], initialized empty to check which is necessary
my $canFDHardware = '';                             # CAN FD hardware [VECTOR/PEAK], initialized empty to check which is necessary
my $ethHardware = '';                               # Ethernet: Hardware [LAN_ADAPTER], initialized empty to check which is necessary
my $ethTxCycleMs = 20;                              # Ethernet: TX cycle of T1-HOST-SW
my $ethPcIP = undef;                                # Ethernet: IP address of PC
my $mustUseFixedBlockSize = 'true';                 # T1-HOST-SW CAN TX-messages always use DLC=8
my $ethMustUseFixedBlockSize = 'false';             # T1-HOST-SW Ethernet TX-messages length is variable by default
my $bigEndian = 'false';                            # target is big-endian [true/false]
my $cortexMFPBversion = 2;                          # Only for ARM Cortex-M, specify Flash Patch breakpoint version (defaults to 2)
my $initFeatureMask = '';                           # string of initial application feature mask [e.g. (T1_AF_TRACE_STARUP | T1_AF_MEASURE_T1_HANDLER)]
my $symbolPrefix = '';                              # Green Hills compiler prefixes symbols with underscore
my $numberOfFocusMeasurements = 2;                  # Number of focus measurements that can run simultaneously
my $syncPeriodMs = 100;                             # Period of sync events for multi-core streaming
my $externalTraceBuffer = 'false';                  # true => external trace buffer macro generated in T1_config.h, for use in the file T1_configBuff.c
                                                    # false => trace buffer configuration generated in T1_configGen.c
my $configBuffC = 'T1_configBuff.c';                # name and path of file containing external trace buffer configuration, by default T1_configBuff.c
my $targetConnectionName = 'Default Connection';    # Name of the TargetConnectionConfig
my $minT1HostSwVersion = '3.4.0';                   # Version number of the T1-HOST-SW that shall be considered while generating code and the project file
my $traceWideSyncTimer = 'false';                   # Set to true to trace 56 rather than 32 bits of the sync timer. This has nothing to do with the hardware register width, as the additional bits are synthesised in software.

#parameters that are omitted if omitted:
my $canFDMustUseFixedBlockSize = '';                # T1-HOST-SW CAN FD TX-messages length can be variable or not
my $canHwName;                                      # Name of CAN HW
my $canFDHwName;                                    # Name of CAN FD HW
my $ethHwName;                                      # Name of Ethernet connection
my $canUsage = '';                                  # Preferred device for the T1-HOST-SW
my $ethUsage = '';                                  # Preferred device for the T1-HOST-SW
my $canFDUsage = '';                                # Preferred device for the T1-HOST-SW
my $timeoutRx = '';                                 # The receive time-out is the maximum time allowed between reception of two frames of the same message.This needs to be large enough to allow for network traffic and routing delays between the host and the target [multiple of t1HandlerPeriodMs of communication core]
my $timeoutRxMs = '';                               # Version in milliseconds
my $timeoutTx = '';                                 # The transmit time-out is the maximum time allowed for (retrying) the sending of a frame. This needs to be large enough to allow for queuing in the CAN layer(s), typically a smaller number than the receive timeout [multiple of t1HandlerPeriodMs of communication core]
my $timeoutTxMs = '';                               # Version in milliseconds
my $timeoutResponse = '';                           # It is the maximum time permitted between transmitting the last frame of a message that requires acknowledgment and receiving the last frame of that acknowledgment. It is typically very much larger than the GCP timeout limits, since it needs to allow for the T1-HOST-SW to respond in addition to transmission and reception delays [multiple of t1HandlerPeriodMs of communication core]
my $timeoutResponseMs = '';                         # Version in milliseconds
my $syncTimerTickDurationNs = '';                   # This represents the tick duration for the main/synchronization clock. The T1-HOST-SW needs this to merge multi-core traces. Strictly required for multi-core systems!
my @configHeaderIncludes = ();                      # header files to be included in T1_config.h ["myFileToBeIncluded.h"]
my @idHeaderIncludes = ();                          # header files to be included in idHeader ["myFileToBeIncluded.h"]
my @runnableHeaderIncludes = ();                    # header files to be included in runnableHeader ["myFileToBeIncluded.h"]
my $storeTimingInformation = '';                    # store timing information in t1p [true/false]
my $endiannessAgnosticComSetup = '';                # used for compatibility with T1-TARGET-SW starting with V2.2.0.0 and prior to V2.2.4.0 on big-endian targets
my $canFDSamplePoint = 0;                           # CAN FD SamplePoint value, default is 70%
my $canFDDataBitrate = 0;                           # CAN FD Data bit rate value, default is bit rate value. If SamplePoint is also defined, this value is omitted
my $canFDDataSamplePoint = 0;                       # CAN FD DataSamplePoint value, default is 70%
my $canFDOscillatorFrequencyMhz = 0;                # CAN FD OscillatorFrequencyMhz value, default is 80 MHz
my @canFDBitTiming = ();                            # CAN FD BitTiming values separated with "," in the specific order "[Brp], [Prop], [Phase1], [Phase2], [Sjw], [Sam]". SamplePoint is used by default
my @canFDDataBitTiming = ();                        # CAN FD DataBitTiming values separated with "," in the specific order "[Brp], [Prop], [Phase1], [Phase2], [Sjw], [Sam]". DataSamplePoint is used by default
my $enableStreaming = '';                           # true -> EnableStreamingUI="true", false -> EnableStreamingUI="false", omitted -> no entry in .t1p file
my $enableDoxygenComments = 'false';
my @defineStack = (undef) x MAX_NOF_CORES;
my @assignTaskStack = (undef) x MAX_NOF_CORES;
my @trapCls3UserHandler = (undef) x MAX_NOF_CORES;  # Tricore only. If T1_OuterTrapCls3Hndlr[CoreX] is installed into trap vector table, the evicted user trap class3 handler should be registered to -trapCls3UserHandler
my $cfgEncoding;                                    # Encoding used for reading in the invocation files
my $sourceFileEncoding;                             # Encoding used for reading and writing C source and header files and the T1 project file
my $systemFileNameEncoding;                         # Encoding used by the (Windows) system for paths / filenames

#these connection parameters are project-specific (and thus global) if useSameConnectionForAllSystems == true
#if system-specific connections-settings are required state -useSameConnectionForAllSystems=false and add these parameters to each system
my @connectionType = ('pure T1') x MAX_NOF_CORES;   # connection-type: [pure T1/Diagnosis]
my @rxChannel = ('CAN') x MAX_NOF_CORES;            # hardware used for RxChannel: [CAN/CAN_FD/ETHERNET/TRACE32]
my @txChannel = ('CAN') x MAX_NOF_CORES;            # hardware used for TxChannel: [CAN/CAN_FD/ETHERNET/TRACE32]
my @useSameRxTxChannel = ('true') x MAX_NOF_CORES;  # system uses the same channel for RX and TX [true/false]

# CAN
my @canExtendedIds = ('false') x MAX_NOF_CORES;     # use extended CAN IDs [true/false]
my @canFDMaxRxDataSize = (0) x MAX_NOF_CORES;       # CAN FD: max. data size of one frame from ECU to T1-HOST-SW
my @canFDMaxTxDataSize = (0) x MAX_NOF_CORES;       # CAN FD: max. data size of one frame from T1-HOST-SW to ECU, minimum is used to set the bus parameter MaxTxBlocksize
my @canRxID = ('0x6FA') x MAX_NOF_CORES;            # CAN / CAN FD ID ECU to T1-HOST-SW [0x6FA]
my @canTxID = ('0x6CB') x MAX_NOF_CORES;            # CAN / CAN FD ID T1-HOST-SW to ECU [0x6CB]

# UDS
my @diagAddressingMode = ('normal') x MAX_NOF_CORES;# Diagnosis: addressing mode: [normal/extended]
my @diagCustomSessionId = (0) x MAX_NOF_CORES;      # Diagnosis: Specifies the concrete session type to be opened, if the diagOpenSessionType Custom is selected.
my @diagLocalIdentifier = (0) x MAX_NOF_CORES;      # Diagnosis: local identifier (deprecated: only supported by KWP2000)
my @diagMaxRxDataSize = (8) x MAX_NOF_CORES;        # Diagnosis: max. RX data size of one Frame (using ReadByIdentifier service)
my @diagMaxTxDataSize = (8) x MAX_NOF_CORES;        # Diagnosis: max. TX data size of one Frame (using WriteByIdentifier service)
my @diagMinTxDataSize = (8) x MAX_NOF_CORES;        # Diagnosis: min. TX data size of one Frame (using WriteByIdentifier service)
my @diagOpenSessionType = ('None') x MAX_NOF_CORES; # Diagnosis: Specifies the session type to be opened when the target link is enabled.
my @diagSourceAddr = ('0xFA') x MAX_NOF_CORES;      # Diagnosis: source address: Typically the lowest 8 byte of canRxID [0xFA]
my @diagT1Identifier = (0) x MAX_NOF_CORES;         # Diagnosis: T1 identifier
my @diagTargetAddr = ('0xCB') x MAX_NOF_CORES;      # Diagnosis: target address: Typically the lowest 8 byte of canTxID [0xCB]
my @diagTesterPresentPeriod = (0) x MAX_NOF_CORES;  # Diagnosis: Period the 'TesterPresent' message is sent.
my @diagUseServiceByLocalId = ('false') x MAX_NOF_CORES;# Diagnosis: use service by local ID (deprecated: only supported by KWP2000)

# UDP/IP
my @ethEcuDNSHostName = (undef) x MAX_NOF_CORES;    # Ethernet: Hostname of ECU
my @ethEcuIP = (undef) x MAX_NOF_CORES;             # Ethernet: IP address of ECU, can be used for IPv4 and IPv6
my @ethEcuPort = (0) x MAX_NOF_CORES;               # Ethernet: ECU Port
my @ethMac = (undef) x MAX_NOF_CORES;               # Ethernet: ECU MAC only needed by Vector Ethernet
my @ethNetworkName = (undef) x MAX_NOF_CORES;       # Ethernet: Network name only needed by Vector Ethernet
my @ethVirtualPortName = (undef) x MAX_NOF_CORES;   # Ethernet: VirtualPortName only needed by Vector Ethernet
my @vlanIDs = (undef) x MAX_NOF_CORES;              # Ethernet: VLAN ID only needed by Vector Ethernet
my @ethMaxRxDataSize = (0) x MAX_NOF_CORES;         # Ethernet: Initialized to 0, if given it will set T1_GCP_MAX_TX_FRAME_SIZE from ECU to T1-HOST-SW
my @ethMaxTxDataSize = (0) x MAX_NOF_CORES;         # Ethernet: Ethernet message max. data size in bytes, initialized to 0, if given it will set T1_GCP_MAX_RX_FRAME_SIZE from T1-HOST-SW to ECU
my @ethPcPort = (0) x MAX_NOF_CORES;                # Ethernet: PC Port
my @ethUseIpv6 = ('false') x MAX_NOF_CORES;         # Ethernet: If false, IPv4 is used
my @ethUseUdp = ('false') x MAX_NOF_CORES;          # Ethernet: If false, TCP is used

# Lauterbach TRACE32 related parameters
my @t32Host                       = ('localhost') x MAX_NOF_CORES;                            # TRACE32: TRACE32 Host address
my @t32HostToTargetBufferSize     = (0) x MAX_NOF_CORES;                                      # TRACE32: Size of "T1_hostToTargetArray"
my @t32PacketLength               = (1024) x MAX_NOF_CORES;                                   # TRACE32: Packet length (TRACE32 <=> T1-HOST-SW)
my @t32Port                       = (20000) x MAX_NOF_CORES;                                  # TRACE32: TRACE32 Port
my @t32TargetToHostBufferSize     = (0) x MAX_NOF_CORES;                                      # TRACE32: Size of "T1_targetToHostArray"
# The following variables are not mapped to parameters yet, but the code is prepared to do this if required
my @t32SymHostToTargetAcknowledge = ('T1_hostToTargetHandshakeAcknowledge') x MAX_NOF_CORES;  # TRACE32: Interface symbol
my @t32SymHostToTargetAnnounce    = ('T1_hostToTargetHandshakeAnnounce') x MAX_NOF_CORES;     # TRACE32: Interface symbol
my @t32SymHostToTargetBuffer      = ('T1_hostToTargetArray') x MAX_NOF_CORES;                 # TRACE32: Interface symbol
my @t32SymHostToTargetFrameLength = ('T1_hostToTargetFrameLength') x MAX_NOF_CORES;           # TRACE32: Interface symbol
my @t32SymTargetToHostAcknowledge = ('T1_targetToHostHandshakeAcknowledge') x MAX_NOF_CORES;  # TRACE32: Interface symbol
my @t32SymTargetToHostAnnounce    = ('T1_targetToHostHandshakeAnnounce') x MAX_NOF_CORES;     # TRACE32: Interface symbol
my @t32SymTargetToHostBuffer      = ('T1_targetToHostArray') x MAX_NOF_CORES;                 # TRACE32: Interface symbol
my @t32SymTargetToHostFrameLength = ('T1_targetToHostFrameLength') x MAX_NOF_CORES;           # TRACE32: Interface symbol

# Communication timeouts
my @hostTimeoutMs = (2000) x MAX_NOF_CORES;         # Maximum time allowed between a message from the T1-HOST-SW and the response from the T1-TARGET-SW
my @gcpTimeoutMs = (400) x MAX_NOF_CORES;           # Maximum time allowed between consecutive frames of the same extended message
my @diagTimeoutMs = (300) x MAX_NOF_CORES;          # Maximum time allowed between consecutive UDS frames of the same message

#system-related configuration parameters:
#strictly required:
my $core0sid = 0;                                   # The SID of core 0
my $commsCoreOffset = 0;                            # Offset of the communications core
my @systemType = ();                                # additional info [OSEK/ErcosEK/gliwOS/PC Software/RTA OSEK/AUTOSAR OS/Unknown]
my @systemName = ();                                # unique System Name. This name is displayed in the T1.base context menu of the T1-HOST-SW [any string]
my @systemComment = ();                             # any comment. Just additional info [any string]
my @tickDurationNs = ();                            # tick duration in ns of system-specific trace timer - can be scaled (down) from the raw timer
my @rawTickDurationNs = ();                         # tick duration in ns of system-specific physical timer
my @osBasicSchedFrameName = ();                     # OS-name of task used as Basic Scheduling Frame event. The BSF event determines the boundaries for CPU-load calculation. Alternatively use osBasicSchedFrameId if only the ID is known
my @osBasicSchedFrameId = ();                       # T1 task ID of Basic Scheduling Frame Event
my @t1HandlerPeriodMs = ();                         # System-specific period of T1_Handler [ms]. It is recommended to call T1_Handler every 5 to 10ms
my @t1ScopeOverheadNs = ();                         # Duration of one call to T1_TraceEvent [ns]
my @t1FlexOverheadNs = ();                          # T1.flex overhead [ns]

#parameters that use default value if omitted:
my @traceTimerIsSyncTimer = ('true') x MAX_NOF_CORES; # when using different timers in multi-core systems one timer needs to be declared the synchronization timer. If the current systems used this timer assign true [true/false]
my @osBasicSchedFrameEventId = ('T1_ACTIVATION') x MAX_NOF_CORES;   # system-specific Event ID used for BSF [T1_START/T1_ACTIVATION/T1_USEREVENT]. Use -osBasicSchedFrameId for specifying ID of UserEvent. Caution: The event field must be 0 on the target!
my @osBackgroundTaskName = ('') x MAX_NOF_CORES;    # system-specific OS-name of Background task. If any name is stated this task is excluded from T1.cont and T1.scope calculations. If nothing is stated T1_INVALID_TASK_ID is used instead and thus considering the BG-task
my @osBackgroundTaskId;                             # alternatively if only task-ID is known
my @nOfAdditionalCat1Isrs = (0) x MAX_NOF_CORES;    # number of additional ISRs that are not covered by OS-specific module
my @additionalCat1IsrIdOffset = (0) x MAX_NOF_CORES;# if the external cat1 ISRs are starting at a fixed offset configure offset for each system
my %allocateCat1IsrIdPrio;                          # specific symbols for which to reserve cat1 ISR IDs
my @targetExcludeFromTraceByName = ();              # defines macro $configHeader
my @targetExcludeFromTraceById = ();                # defines macro $configHeader
my @flexAnalysisCapacity = (0) x MAX_NOF_CORES;     # T1.flex analysis capacity: Max. number of exception handler calls within T1_Handler period before measurement will be disabled
my @targetType = ('') x MAX_NOF_CORES;              # Used to indicate to the T1-HOST-SW target specifics information, this parameter is system specific [PPC5xxx_nonVLE/ARM7M/ARM7R/ARM8R]
my @featureMaskCallback = (0) x MAX_NOF_CORES;      # Non-zero indicates a core requires a callback when the feature mask is changed
my $checkIntegration = 'false';                     # Used to check T1 integration
my @useDMStrampoline = ('true') x MAX_NOF_CORES;    # TriCore only setting, system should use DMS trampoline or not [true/false]

#optional config parameters used for macros in T1_config.h:
my @cpuLoadThreshold = (100) x MAX_NOF_CORES;       # defines macro T1_CPULOAD_THRESHOLD_PERCENT_COREx: CPU-load threshold [0..99]
my @traceBufferEntries = (1) x MAX_NOF_CORES;       # defines macro T1_TRACEBUFFER_ENTRIES_COREx: Number of trace buffer entries
my @analysisCapacity = (0) x MAX_NOF_CORES;         # defines macro T1_CONT_ANALYSIS_CAPACITY_COREx
my @numberOfUserStpws = (1) x MAX_NOF_CORES;        # defines macro T1_NOF_USER_STPWS_COREx: Number of user stopwatches
my @numberOfConstraints = (undef) x MAX_NOF_CORES;  # defines macro T1_NOF_CSRNS_COREx: Number of constraints
my @nOfDelays = (0) x MAX_NOF_CORES;                # defines macro T1_NOF_DELAYS_COREx: Number of delays
my @nOfFlexStopwatches = (0) x MAX_NOF_CORES;       # defines macro T1_NOF_FLEX_STPWS_COREx: Number of T1.flex stopwatches (e.g. used for feature "linked Stopwatches") [0..255]
my @nOfFlexAddrs = (0) x MAX_NOF_CORES;             # defines macro T1_NOF_FLEX_ADDRS_COREx: Number of T1.flex addresses. Needs to be greater or equal $nOfFlexStopwatches [0..255]
my @numberOfFlexBufferEntries = (1) x MAX_NOF_CORES;# defines macro T1_NOF_FLEXBUFFER_ENTRIES_COREx: Number of T1.flex buffer entries.
my @pTimer = ();                                    # defines macro T1_PTIMER_COREx: If using memory mapped timer: address of timer. Otherwise omit
my $pSyncTimer;                                     # defines macro T1_GET_SYNC_TIME if using multi-core
my @traceTimerDownCounting = ();                    # Trace timer is counting down [true/false] the default is false, although not explicitly set here
my $syncTimerDownCounting;                          # Sync timer is counting down [true/false] the default is false, although not explicitly set here
my @rawTimerBitLength = (32) x MAX_NOF_CORES;       # defines macro T1_RAW_TIMER_BIT_LENGTH_COREx: [16..32]
my @cpuLoadTxPeriod = ();                           # defines macro T1_CPU_LOAD_TX_PERIOD_COREx: Transmit CPU load every x CPU load frames (BSF-frame). E.g. BasicSchedFrame-Event has a period of 100ms. If $cpuLoadTxPeriod is 10 the CPU-load is transmitted every second
my @cpuLoadAvgSamples = ();                         # defines macro T1_CPU_LOAD_SAMPLES_COREx: Number of samples taken within period [1 or $cpuLoadTxPeriod]
my $staticRunnableID = '';                          # defines macro T1_STATIC_RUNNABLE_ID: Id used for tracing runnables with a unique ID [0..1023]
my $countPreemption = 'false';                      # defines the macro T1_COUNT_PREEMPTION [true/false]
my $foregroundCont = 'false';                       # defines the macro T1_FG_CONT [true/false]
my $waitResume = 'false';                           # defines the macro T1_WAIT_RESUME [true/false]
my $crossCoreAct = 'false';                         # defines the macro T1_CROSS_CORE_ACT [true/false]
my $disableT1Cont = 'false';                        # defines the macro T1_DISABLE_T1_CONT [true/false]
my $disableT1Flex = 'false';                        # defines the macro T1_DISABLE_T1_FLEX [true/false]
my $disableT1Mod = 'false';                         # defines the macro T1_DISABLE_T1_MOD [true/false]
my $disableT1Delay = 'false';                       # defines the macro T1_DISABLE_T1_DELAY [true/false]
my $supportTimerOverflow = 'false';                 # defines the macro T1_SUPPORT_TIMER_OVERFLOW [true/false]
my $detectTimerOverflow = 'false';                  # defines the macro T1_DETECT_TIMER_OVERFLOW [true/false]
my $numberOfVirtualStopwatches = undef;             # defines the macro T1_CONT_NOF_VRTL_STPWS [8/64]

#optional system-specific parameters:
my %t1pSymbolIncludeFilesCoreX = ();
my @symbolFilesCoreX = ();

my @allocateAF;
my %allocateDL;
my %allocateUDE;
my %allocateUE;
my %keyValueMapUE;
my %allocateUserSW;
my %addConstraintToUserSW;

######################################################################################
# global variables
######################################################################################

# Enforce T1-HOST-SW V2 compatibility by not generating the CommunicationConfigList (introduced with T1-HOST-SW V3 which generates a warning for T1-HOST-SW V2).
my $enforceHostV2Compatibility = 0;
my $cortex = ''; # true if target is ARM Cortex-M or R

my @sysElems = ();
my @extraSysElems = ();
my @appFeatureElems = ();
my @delayElems = ();
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

my @invocationFiles = ();               # name and path to the invocation files provided via the parameters -UserCfg and -Cfg
my @additionalCmdLineParameters = ();   # parameters provided via the command line
my $osCfgFile = "";
# By default, T1.cont runs on it's own core
my %contRunsOnCore = ();

my @traceTimerBitLength = (0) x MAX_NOF_CORES; # Will be set in InitRatios() based on systems rawTickDurationNs and traceTickDurationNs
my $allCoresRawToTickRatio;         # Will be set to 0 if not equal for all systems or actual value in InitRatios()
my $allCoresTraceTickDurationNs;    # Will be set to 0 if not equal for all systems or actual value in InitRatios()
my $allCoresRawTickDurationNs;      # Will be set to 0 if not equal for all systems or actual value in InitRatios()
my $allTraceTimersAreSyncTimer = 1; # Will be set to 0 in InitRatios() if necessary
my $anyTraceTimerIsSyncTimer = 0;   # Will be set to 1 in InitRatios() if necessary

# Application Feature masks configured via invocation file parameter
my @applicationFeatures;
my @delays;
my @userEvents;
my @constraints;
# User stopwatches configured via invocation file parameter
my @userStopWatches;

# The following list is from https://www.w3schools.com/colors/colors_names.asp
use constant HTML_COLOR_LOOKUP => (
    black                   => '#000000',
    navy                    => '#000080',
    darkblue                => '#00008B',
    mediumblue              => '#0000CD',
    blue                    => '#0000FF',
    darkgreen               => '#006400',
    green                   => '#008000',
    teal                    => '#008080',
    darkcyan                => '#008B8B',
    deepskyblue             => '#00BFFF',
    darkturquoise           => '#00CED1',
    mediumspringgreen       => '#00FA9A',
    lime                    => '#00FF00',
    springgreen             => '#00FF7F',
    aqua                    => '#00FFFF',
    cyan                    => '#00FFFF',
    midnightblue            => '#191970',
    dodgerblue              => '#1E90FF',
    lightseagreen           => '#20B2AA',
    forestgreen             => '#228B22',
    seagreen                => '#2E8B57',
    darkslategray           => '#2F4F4F',
    darkslategrey           => '#2F4F4F',
    limegreen               => '#32CD32',
    mediumseagreen          => '#3CB371',
    turquoise               => '#40E0D0',
    royalblue               => '#4169E1',
    steelblue               => '#4682B4',
    darkslateblue           => '#483D8B',
    mediumturquoise         => '#48D1CC',
    indigo                  => '#4B0082',
    darkolivegreen          => '#556B2F',
    cadetblue               => '#5F9EA0',
    cornflowerblue          => '#6495ED',
    rebeccapurple           => '#663399',
    mediumaquamarine        => '#66CDAA',
    dimgray                 => '#696969',
    dimgrey                 => '#696969',
    slateblue               => '#6A5ACD',
    olivedrab               => '#6B8E23',
    slategray               => '#708090',
    slategrey               => '#708090',
    lightslategray          => '#778899',
    lightslategrey          => '#778899',
    mediumslateblue         => '#7B68EE',
    lawngreen               => '#7CFC00',
    chartreuse              => '#7FFF00',
    aquamarine              => '#7FFFD4',
    maroon                  => '#800000',
    purple                  => '#800080',
    olive                   => '#808000',
    gray                    => '#808080',
    grey                    => '#808080',
    skyblue                 => '#87CEEB',
    lightskyblue            => '#87CEFA',
    blueviolet              => '#8A2BE2',
    darkred                 => '#8B0000',
    darkmagenta             => '#8B008B',
    saddlebrown             => '#8B4513',
    darkseagreen            => '#8FBC8F',
    lightgreen              => '#90EE90',
    mediumpurple            => '#9370DB',
    darkviolet              => '#9400D3',
    palegreen               => '#98FB98',
    darkorchid              => '#9932CC',
    yellowgreen             => '#9ACD32',
    sienna                  => '#A0522D',
    brown                   => '#A52A2A',
    darkgray                => '#A9A9A9',
    darkgrey                => '#A9A9A9',
    lightblue               => '#ADD8E6',
    greenyellow             => '#ADFF2F',
    paleturquoise           => '#AFEEEE',
    lightsteelblue          => '#B0C4DE',
    powderblue              => '#B0E0E6',
    firebrick               => '#B22222',
    darkgoldenrod           => '#B8860B',
    mediumorchid            => '#BA55D3',
    rosybrown               => '#BC8F8F',
    darkkhaki               => '#BDB76B',
    silver                  => '#C0C0C0',
    mediumvioletred         => '#C71585',
    indianred               => '#CD5C5C',
    peru                    => '#CD853F',
    chocolate               => '#D2691E',
    tan                     => '#D2B48C',
    lightgray               => '#D3D3D3',
    lightgrey               => '#D3D3D3',
    thistle                 => '#D8BFD8',
    orchid                  => '#DA70D6',
    goldenrod               => '#DAA520',
    palevioletred           => '#DB7093',
    crimson                 => '#DC143C',
    gainsboro               => '#DCDCDC',
    plum                    => '#DDA0DD',
    burlywood               => '#DEB887',
    lightcyan               => '#E0FFFF',
    lavender                => '#E6E6FA',
    darksalmon              => '#E9967A',
    violet                  => '#EE82EE',
    palegoldenrod           => '#EEE8AA',
    lightcoral              => '#F08080',
    khaki                   => '#F0E68C',
    aliceblue               => '#F0F8FF',
    honeydew                => '#F0FFF0',
    azure                   => '#F0FFFF',
    sandybrown              => '#F4A460',
    wheat                   => '#F5DEB3',
    beige                   => '#F5F5DC',
    whitesmoke              => '#F5F5F5',
    mintcream               => '#F5FFFA',
    ghostwhite              => '#F8F8FF',
    salmon                  => '#FA8072',
    antiquewhite            => '#FAEBD7',
    linen                   => '#FAF0E6',
    lightgoldenrodyellow    => '#FAFAD2',
    oldlace                 => '#FDF5E6',
    red                     => '#FF0000',
    fuchsia                 => '#FF00FF',
    magenta                 => '#FF00FF',
    deeppink                => '#FF1493',
    orangered               => '#FF4500',
    tomato                  => '#FF6347',
    hotpink                 => '#FF69B4',
    coral                   => '#FF7F50',
    darkorange              => '#FF8C00',
    lightsalmon             => '#FFA07A',
    orange                  => '#FFA500',
    lightpink               => '#FFB6C1',
    pink                    => '#FFC0CB',
    gold                    => '#FFD700',
    peachpuff               => '#FFDAB9',
    navajowhite             => '#FFDEAD',
    moccasin                => '#FFE4B5',
    bisque                  => '#FFE4C4',
    mistyrose               => '#FFE4E1',
    blanchedalmond          => '#FFEBCD',
    papayawhip              => '#FFEFD5',
    lavenderblush           => '#FFF0F5',
    seashell                => '#FFF5EE',
    cornsilk                => '#FFF8DC',
    lemonchiffon            => '#FFFACD',
    floralwhite             => '#FFFAF0',
    snow                    => '#FFFAFA',
    yellow                  => '#FFFF00',
    lightyellow             => '#FFFFE0',
    ivory                   => '#FFFFF0',
    white                   => '#FFFFFF',
);

######################################################################################
# sub InitTimerSettings Initialize timer ratios and default values
######################################################################################

sub InitTimerSettings
{
    my $nOfCores = int shift;

    foreach my $sysNo ( 0 .. $nOfCores-1 )
    {
        if( 'true' eq $traceTimerIsSyncTimer[$sysNo] )
        {
            $anyTraceTimerIsSyncTimer = 1;

            # Check timer tick duration
            if( $tickDurationNs[$sysNo] and $syncTimerTickDurationNs )
            {
                unless( EqualF( eval "${tickDurationNs[$sysNo]}", eval "${syncTimerTickDurationNs}" ) )
                {
                    die qq(Error: -traceTimerIsSyncTimer=true for system ${sysNo}, but -tickDurationNs=${tickDurationNs[$sysNo]}\n       is not equal to -syncTimerTickDurationNs=${syncTimerTickDurationNs}\n);
                }
            }
            elsif( not $tickDurationNs[$sysNo] and $syncTimerTickDurationNs )
            {
                # Implicit trace timer duration
                $tickDurationNs[$sysNo] = $syncTimerTickDurationNs;
            }
            elsif( $tickDurationNs[$sysNo] and not $syncTimerTickDurationNs )
            {
                # Implicit synchronization timer duration
                $syncTimerTickDurationNs = $tickDurationNs[$sysNo];
            }
            else
            {
                die qq(Error: -traceTimerIsSyncTimer=true for system ${sysNo}, but neither\n       -tickDurationNs nor -syncTimerTickDurationNs is set.\n);
            }

            # Check timer address
            if( $pTimer[$sysNo] and $pSyncTimer )
            {
                unless( $pTimer[$sysNo] eq $pSyncTimer )
                {
                    die qq(Error: -traceTimerIsSyncTimer=true for system ${sysNo}, but -pTimer=${pTimer[$sysNo]}\n       is not equal to -pSyncTimer=${pSyncTimer}\n);
                }
            }
            elsif( not $pTimer[$sysNo] and $pSyncTimer )
            {
                # Implicit trace timer address
                $pTimer[$sysNo] = $pSyncTimer;
            }
            elsif( $pTimer[$sysNo] and not $pSyncTimer )
            {
                # Implicit synchronization timer address
                # Do nothing so that T1_GET_SYNC_TIME( ) can be defined to be
                # T1_GET_TRACE_TIME_PC( $sysNo ) in T1_config.pm
                # see https://sutra1.gliwa.com/trac/t1target/ticket/2219 (r55600)
            }

            # Check timer counting up/down
            if( $traceTimerDownCounting[$sysNo] and $syncTimerDownCounting )
            {
                unless( $traceTimerDownCounting[$sysNo] eq $syncTimerDownCounting )
                {
                    die qq(Error: -traceTimerIsSyncTimer=true for system ${sysNo}, but -traceTimerDownCounting=${traceTimerDownCounting[$sysNo]}\n       is not equal to -syncTimerDownCounting=${syncTimerDownCounting}\n);
                }
            }
            elsif( not $traceTimerDownCounting[$sysNo] and $syncTimerDownCounting )
            {
                # Implicit trace timer counting up/down
                $traceTimerDownCounting[$sysNo] = $syncTimerDownCounting;
            }
            elsif( $traceTimerDownCounting[$sysNo] and not $syncTimerDownCounting )
            {
                # Implicit synchronization timer counting up/down
                $syncTimerDownCounting = $traceTimerDownCounting[$sysNo];
            }
        }
        else
        {
            $allTraceTimersAreSyncTimer = 0;
        }
    }

    # Start with core 0
    my $localTickDurationNs    = $tickDurationNs[0];
    my $localRawTickDurationNs = $rawTickDurationNs[0];
    my $localRawTimerBitLength = $rawTimerBitLength[0];
    $localRawTimerBitLength = eval "${localRawTimerBitLength}";

    # Scaled trace timer tick duration
    $allCoresTraceTickDurationNs = eval "${localTickDurationNs}";

    # Physical trace timer tick duration
    $allCoresRawTickDurationNs = eval "${localRawTickDurationNs}";

    # Physical to scaled trace timer ratio and scaled trace timer bit length
    $allCoresRawToTickRatio = eval "(${localTickDurationNs}) / (${localRawTickDurationNs})";
    my $shift = ceil( ( log $allCoresRawToTickRatio ) / ( log 2 ) - 0.00001 );
    die "Error: Core 0 ratio of rawTickDuractionNs to tickDuractionNs must be a power of two\n" unless EqualF( 2**$shift, $allCoresRawToTickRatio );
    $traceTimerBitLength[0] = $localRawTimerBitLength - $shift;
    $traceTimerBitLength[0] = 32 if 32 < $traceTimerBitLength[0];

    # Compare values of remaining systems with system 0
    foreach my $sysNo ( 1 .. $nOfCores-1 )
    {
        $localTickDurationNs    = $tickDurationNs[$sysNo];
        $localRawTickDurationNs = $rawTickDurationNs[$sysNo];
        $localRawTimerBitLength = $rawTimerBitLength[$sysNo];
        $localRawTimerBitLength = eval "${localRawTimerBitLength}";

        # Scaled trace timer tick duration
        my $thisCoreTraceTickDurationNsDiff = ( eval "${localTickDurationNs}" ) - $allCoresTraceTickDurationNs;
        $allCoresTraceTickDurationNs = 0 unless EqualF( 0, $thisCoreTraceTickDurationNsDiff );

        # Physical trace timer tick duration
        my $thisCoreRawTickDurationNsDiff = ( eval "${localRawTickDurationNs}" ) - $allCoresRawTickDurationNs;
        $allCoresRawTickDurationNs = 0 unless EqualF( 0, $thisCoreRawTickDurationNsDiff );

        # Physical to scaled trace timer ratio and scaled trace timer bit length
        my $thisCoreRawToTickRatio = eval "(${localTickDurationNs}) / (${localRawTickDurationNs})";
        my $shift = ceil( ( log $thisCoreRawToTickRatio ) / ( log 2 ) - 0.00001 );
        die "Error: Core ${sysNo} ratio of rawTickDuractionNs to tickDuractionNs must be a power of two\n" unless EqualF( 2**$shift, $thisCoreRawToTickRatio );
        $traceTimerBitLength[$sysNo] = $localRawTimerBitLength - $shift;
        $traceTimerBitLength[$sysNo] = 32 if 32 < $traceTimerBitLength[$sysNo];
        $allCoresRawToTickRatio = 0 unless EqualF( $thisCoreRawToTickRatio, $allCoresRawToTickRatio ) and $traceTimerBitLength[$sysNo] == $traceTimerBitLength[0];
    }

    unless( $syncTimerDownCounting )
    {
        # Set to default value if not already set
        $syncTimerDownCounting = 'false';
    }

    foreach my $sysNo ( 0 .. $nOfCores-1 )
    {
        unless( $traceTimerDownCounting[$sysNo] )
        {
            # Set to default value if not already set
            $traceTimerDownCounting[$sysNo] = 'false';
        }

        if( 'true' eq $traceTimerIsSyncTimer[$sysNo] )
        {
            # Check timer bit length
            if( $syncTimeBitLength and $traceTimerBitLength[$sysNo] )
            {
                # Check if sync timer bit length is set to a reasonable value
                if( $traceTimerBitLength[$sysNo] < $syncTimeBitLength )
                {
                    warn qq(Warning: Synchronization timer bit length (-syncTimeBitLength=${syncTimeBitLength}) can not exceed trace timer bit length (${traceTimerBitLength[$sysNo]}) for system ${sysNo}.\n);
                    warn qq(Warning: Synchronization timer bit length set to ${traceTimerBitLength[$sysNo]}.\n);
                    $syncTimeBitLength = $traceTimerBitLength[$sysNo];
                }
            }
            elsif( not $syncTimeBitLength and $traceTimerBitLength[$sysNo] )
            {
                # Implicit synchronization timer bit length
                $syncTimeBitLength = $traceTimerBitLength[$sysNo];
            }
            elsif( $syncTimeBitLength and not $traceTimerBitLength[$sysNo] )
            {
                # The scaled trace timer bit length has already been derived from the
                # physical trace timer bit length and their duration ratio
            }
        }
    }

    if( $syncTimeBitLength )
    {
        if( 24 > $syncTimeBitLength and 1 < $nOfCores )
        {
            warn qq(Warning: Synchronization timer bit length (-syncTimeBitLength=${syncTimeBitLength}) must be at least 24 for multi-core systems.\n);
        }
    }
    else
    {
        # Use default value
        $syncTimeBitLength = 32;
    }

    if( $debug )
    {
        foreach my $index ( 0..$nOfCores-1 )
        {
            print  "Debug: System ${index}\n";
            print  "Debug:   \$traceTimerIsSyncTimer[${index}] =  ${traceTimerIsSyncTimer[$index]}\n";
            print  "Debug:   \$tickDurationNs[${index}] =         ${tickDurationNs[$index]}\n";
            print  "Debug:   \$rawTickDurationNs[${index}] =      ${rawTickDurationNs[$index]}\n";
            printf "Debug:   Ratio =                      %-0.6f\n", eval "(${rawTickDurationNs[$index]}) / (${tickDurationNs[$index]})";
            print  "Debug:   \$traceTimerBitLength[${index}] =    ${traceTimerBitLength[$index]}\n";
            print  "Debug:   \$rawTimerBitLength[${index}] =      ${rawTimerBitLength[$index]}\n";
            print  "Debug:   \$traceTimerDownCounting[${index}] = ${traceTimerDownCounting[$index]}\n";
            printf "Debug:   \$pTimer[${index}] =                 %s\n", $pTimer[$index] ? $pTimer[$index] : 'undef';
        }
        print  "Debug: All Systems:\n";
        print  "Debug:   \$allCoresRawToTickRatio =      ${allCoresRawToTickRatio}\n";
        print  "Debug:   \$allCoresTraceTickDurationNs = ${allCoresTraceTickDurationNs}\n";
        print  "Debug:   \$allCoresRawTickDurationNs =   ${allCoresRawTickDurationNs}\n";
        print  "Debug:   \$syncTimerTickDurationNs =     ${syncTimerTickDurationNs}\n";
        print  "Debug:   \$syncTimeBitLength =           ${syncTimeBitLength}\n";
        print  "Debug:   \$syncTimerDownCounting =       ${syncTimerDownCounting}\n";
        printf "Debug:   \$pSyncTimer =                  %s\n", $pSyncTimer ? $pSyncTimer : 'undef';
        print  "Debug:   \$allTraceTimersAreSyncTimer =  ${allTraceTimersAreSyncTimer}\n";
        print  "Debug:   \$anyTraceTimerIsSyncTimer =    ${anyTraceTimerIsSyncTimer}\n";
    }

    return;
}

######################################################################################
# sub addU for MISRA compliance with unsigned integer C literals
######################################################################################

sub addU($)
{
    my $unsignedInt = shift;
    $unsignedInt =~ s/^(0[xX][0-9A-Fa-f]+|\d+)$/$1u/;
    return $unsignedInt;
}

######################################################################################
# sub addUL for MISRA compliance with unsigned long C literals
######################################################################################
sub addUL($)
{
    my $unsignedInt = shift;
    $unsignedInt =~ s/^(0[xX][0-9A-Fa-f]+|\d+)$/$1uL/;
    return $unsignedInt;
}

######################################################################################
# sub assignValueToPerSystemArray to allow assigning a value to one or all systems
######################################################################################
sub assignValueToPerSystemArray
{
    my ( $arrayRef, $value, $systemNo ) = @_;

    unless( defined $systemNo )
    {
        # Assign value to all systems
        @$arrayRef = ( $value ) x MAX_NOF_CORES;
    }
    else
    {
        # Assign value only to the given system index
        if( ( 0 <= $systemNo ) and ( $systemNo <= 15 )  )
        {
            $arrayRef->[$systemNo] = $value;
        }
        else
        {
            die qq(Error: Invalid system index "${systemNo}".\n);
        }
    }

    return;
}

######################################################################################
# sub ParseParam
######################################################################################
my $systemNoIncAll = 'all';
sub ParseParam($)
{
    my $curLine = shift;
    $curLine =~ s/^\s//;

    if( 0 == rindex $curLine, '#', 0 )
    {
        # Line starts with #
        if( (my $no) = $curLine =~ /^#system\s+(\d+)/ )
        {
            $systemNo = $no;
            $systemNoIncAll = $no;
        }
        elsif( $curLine =~ /^#system\s+all/ )
        {
            # Reset the system to undef
            undef $systemNo;
            $systemNoIncAll = 'all';
        }
    }
    elsif( 0 == rindex $curLine, '-', 0 )
    {
        # Line starts with -
        # We already know that - is the first char and can strip it
        $curLine = substr $curLine, 1;

        if( -1 != index $curLine, ';' )
        {
            ($curLine, ) = purposeBuiltParseLine( $curLine, ';' ); # ';' functions as a comment operator
        }

        my ($curParam, $curVal) = split /=/, $curLine, 2;

        # Trim leading  whitespace and trailing whitespace
        trimStringRef( \$curParam );

        # Trim leading and trailing whitespace
        trimStringRef( \$curVal );

        if( $debug )
        {
            print "$curParam=$curVal\n";
        }

        # Check for most common (at least in GTF) parameter first
           if( $curParam eq 'keyValueMapUE' )            { push @{$keyValueMapUE{$systemNoIncAll}}, $curVal; }
        # Avoid backtracking for second most common (at least in GTF) parameters
        elsif( $curParam =~ /^allocate(AF|Cat1IsrIdPrio|DL|U(DE|E|serSW))$/ )
        {
            my $rest = $1; # The part that is not 'allocate'
               if( $rest eq 'AF' )                       { push @allocateAF,                       $curVal; }
            elsif( $rest eq 'Cat1IsrIdPrio' )            { allocateCat1IsrIdPrio($systemNo, \%allocateCat1IsrIdPrio, $curVal); }
            elsif( $rest eq 'DL' )                       { push @{$allocateDL{$systemNoIncAll}},   $curVal; }
            elsif( $rest eq 'UDE' )                      { push @{$allocateUDE{$systemNoIncAll}},  $curVal; }
            elsif( $rest eq 'UE' )                       { push @{$allocateUE{$systemNoIncAll}},   $curVal; }
            else                                         { push @{$allocateUserSW{$systemNoIncAll}}, $curVal; }
        }
        elsif( $curParam eq 'projectFile' )              { $projectFile                  = rel2abs($curVal); }
        elsif( $curParam eq 'configGenC' )               { $configGenC                   = rel2abs($curVal); }
        elsif( $curParam eq 'configBuffC' )              { $configBuffC                  = rel2abs($curVal); $externalTraceBuffer = 'true'; }
        elsif( $curParam eq 'configHeader' )             { $configHeader                 = rel2abs($curVal); }
        elsif( $curParam eq 'runnableHeader' )           { $runnableHeader               = rel2abs($curVal); }
        elsif( $curParam eq 'idHeader' )                 { $idHeader                     = rel2abs($curVal); }
        elsif( $curParam eq 'bidHeader' )                { $bidHeader                    = rel2abs($curVal); }
        elsif( $curParam eq 't1LibAnnotationsFile' )     { $t1LibAnnotationsFile         = rel2abs($curVal); $t1pAnnotationsFiles{$t1LibAnnotationsFile}{'global'} =  1;}
        elsif( $curParam eq 'inlineHeader' )             { push @inlineHeaders,                   ($curVal); }
        elsif( $curParam eq 'includeHeader' )            { push @includeHeaders,                  ($curVal); }
        elsif( $curParam eq 'symbolFile' )
        {
            if( defined $systemNo ) # check if this is a system-specific symbol file
            {
                                                           push   @{$symbolFilesCoreX[$systemNo]}, $curVal;
            }
            else # otherwise it is a global symbol file
            {
                                                           push   @symbolFiles,                    $curVal;
            }
        }
        elsif( $curParam eq 't1pAnnotationsFile' )
        {
            if( not defined $systemNo ) # global annotation include file
            {
                                                           $t1pAnnotationsFiles{$curVal}{'global'} =  1;
            }
            else
            {
                if( !exists $t1pAnnotationsFiles{$curVal}{'global'} ) # check redundancy of annotation file
                {
                                                           $t1pAnnotationsFiles{$curVal}{$systemNo} =  1;
                }
                else
                {
                    print "Warning: Annotation file present in global section and system $systemNo section in $_[1]\n";# issue a warning if redundancy
                }
            }
        }
        elsif( $curParam eq 't1pSymbolIncludeFile' )
        {
            if( not defined $systemNo ) # check if this is a global symbol include file
            {
                                                           push @t1pSymbolIncludeFiles,            $curVal;
            }
            else # otherwise it is a core-specific symbol include file
            {
                                                           $t1pSymbolIncludeFilesCoreX{$curVal} =  $systemNo;
            }
        }

        elsif( $curParam eq 'configHeaderInclude' )      { push @configHeaderIncludes,             $curVal; }
        elsif( $curParam eq 'idHeaderInclude' )          { push @idHeaderIncludes,                 $curVal; }
        elsif( $curParam eq 'runnableHeaderInclude' )    { push @runnableHeaderIncludes,           $curVal; }
        elsif( $curParam eq 'copyIncludeHeader' )        { $copyIncludeHeader                    = $curVal; }
        elsif( $curParam eq 'copySymbolFile' )           { $copySymbolFile                       = $curVal; }
        elsif( $curParam eq 'generateBuildId' )          { $generateBuildId                      = $curVal; }
        elsif( $curParam eq 'noRefT0p' )                 {                                                  }
        elsif( $curParam eq 'projectName' )              { $projectName                          = $curVal; }
        elsif( $curParam eq 'licInfo1' )                 { $licInfo1                             = $curVal; }
        elsif( $curParam eq 'licInfo2' )                 { $licInfo2                             = $curVal; }
        elsif( $curParam eq 'readPreviousT1p' )          { $readPreviousT1p                      = $curVal; }
        elsif( $curParam eq 'storeTimingInformation' )   { $storeTimingInformation               = $curVal; }

        elsif( $curParam eq 'usingMulticoreLibs' )       { warn "Warning: -usingMulticoreLibs ignored ('true' is the only supported value)" unless 'true' eq $curVal; }
        elsif( $curParam eq 'initFeatureMask' )          { $initFeatureMask                      = $curVal; }
        elsif( $curParam eq 'symbolPrefix' )             { $symbolPrefix                         = $curVal; }
        elsif( $curParam eq 'numberOfFocusMeasurements' ){ $numberOfFocusMeasurements            = $curVal; }
        elsif( $curParam eq 'mainTickDuration' )         { $syncTimerTickDurationNs              = $curVal; } # For synchronization timer
        elsif( $curParam eq 'syncTimerTickDurationNs' )  { $syncTimerTickDurationNs              = $curVal; } # For synchronization timer
        elsif( $curParam eq 'syncTimeBitLength' )        { $syncTimeBitLength                    = $curVal; }
        elsif( $curParam eq 'traceWideSyncTimer' )       { $traceWideSyncTimer                   = $curVal; }
        elsif( $curParam eq 'bigEndian' )                { $bigEndian                            = $curVal; }
        elsif( $curParam eq 'cortex' )                   { warn "-cortex is deprecated, please use -targetType instead!\n"; }
        elsif( $curParam eq 'cortexMFPBversion' )        { $cortex = 'true'; $cortexMFPBversion  = $curVal; }
        elsif( $curParam eq 'externalTraceBuffer' )      { $externalTraceBuffer                  = $curVal; $configBuffC = rel2abs($configBuffC); }
        elsif( $curParam eq 'timeoutRx' )                { $timeoutRx                            = $curVal; } # retro-compatibility, add end word boundary for single assignment
        elsif( $curParam eq 'timeoutTx' )                { $timeoutTx                            = $curVal; } # retro-compatibility, add end word boundary for single assignment
        elsif( $curParam eq 'timeoutResponse' )          { $timeoutResponse                      = $curVal; } # retro-compatibility, add end word boundary for single assignment
        elsif( $curParam eq 'timeoutRxMs' )              { $timeoutRxMs                          = $curVal; }
        elsif( $curParam eq 'timeoutTxMs' )              { $timeoutTxMs                          = $curVal; }
        elsif( $curParam eq 'timeoutResponseMs' )        { $timeoutResponseMs                    = $curVal; }
        elsif( $curParam eq 'endiannessAgnosticComSetup' ) { $endiannessAgnosticComSetup         = $curVal; }
        elsif( $curParam eq 'canFDSamplePoint' )         { $canFDSamplePoint                     = $curVal; }
        elsif( $curParam eq 'canFDBitTiming' )           { @canFDBitTiming           = split /,/,  $curVal; }
        elsif( $curParam eq 'canFDDataBitrate' )         { $canFDDataBitrate                     = $curVal; }
        elsif( $curParam eq 'canFDDataSamplePoint' )     { $canFDDataSamplePoint                 = $curVal; }
        elsif( $curParam eq 'canFDDataBitTiming' )       { @canFDDataBitTiming       = split /,/,  $curVal; }
        elsif( $curParam eq 'canFDOscillatorFrequencyMhz' ){ $canFDOscillatorFrequencyMhz        = $curVal; }

        elsif( $curParam eq 'canHardware' )              { $canHardware                          = $curVal; }
        elsif( $curParam eq 'canFDHardware' )            { $canFDHardware                        = $curVal; }
        elsif( $curParam eq 'canHwName' )                { $canHwName                            = $curVal; }
        elsif( $curParam eq 'canFDHwName' )              { $canFDHwName                          = $curVal; }
        elsif( $curParam eq 'ethHardware' )              { $ethHardware                          = $curVal; }
        elsif( $curParam eq 'ethHwName' )                { $ethHwName                            = $curVal; }
        elsif( $curParam eq 'ethPcIP' )                  { $ethPcIP                              = $curVal; }
        elsif( $curParam eq 'txCycle' )                  { $txCycleMs                            = $curVal; } # retro-compatibility, add end word boundary for single assignment
        elsif( $curParam eq 'ethTxCycle' )               { $ethTxCycleMs                         = $curVal; } # retro-compatibility, add end word boundary for single assignment
        elsif( $curParam eq 'txCycleMs' )                { $txCycleMs                            = $curVal; }
        elsif( $curParam eq 'ethTxCycleMs' )             { $ethTxCycleMs                         = $curVal; }
        elsif( $curParam eq 'canBitrate' )               { $canBitrate                           = $curVal; }
        elsif( $curParam eq 'canFDBitrate' )             { $canFDBitrate                         = $curVal; }
        elsif( $curParam eq 'mustUseFixedBlockSize' )    { $mustUseFixedBlockSize                = $curVal; }
        elsif( $curParam eq 'ethMustUseFixedBlockSize' ) { $ethMustUseFixedBlockSize             = $curVal; }
        elsif( $curParam eq 'canFDMustUseFixedBlockSize' ) { $canFDMustUseFixedBlockSize         = $curVal; }
        elsif( $curParam eq 'useSameConnectionForAllSystems' ) { $useSameConnectionForAllSystems = $curVal; }
        elsif( $curParam eq 'targetExcludeFromTraceByName' ) { push @targetExcludeFromTraceByName, $curVal; }
        elsif( $curParam eq 'targetExcludeFromTraceById' )   { push @targetExcludeFromTraceById,   $curVal; }

        elsif( $curParam eq 'connectionType' )           { assignValueToPerSystemArray( \@connectionType, $curVal, $systemNo ); }
        elsif( $curParam eq 'txChannel' )                { assignValueToPerSystemArray( \@txChannel, $curVal, $systemNo ); }
        elsif( $curParam eq 'rxChannel' )                { assignValueToPerSystemArray( \@rxChannel, $curVal, $systemNo ); }
        elsif( $curParam eq 'canRxID' )                  { assignValueToPerSystemArray( \@canRxID, $curVal, $systemNo ); }
        elsif( $curParam eq 'canTxID' )                  { assignValueToPerSystemArray( \@canTxID, $curVal, $systemNo ); }
        elsif( $curParam eq 'canExtendedIds' )           { assignValueToPerSystemArray( \@canExtendedIds, $curVal, $systemNo ); }
        elsif( $curParam eq 'canFDRxDataSize' )          { assignValueToPerSystemArray( \@canFDMaxRxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'canFDMaxRxDataSize' )       { assignValueToPerSystemArray( \@canFDMaxRxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'canFDTxDataSize' )          { assignValueToPerSystemArray( \@canFDMaxTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'canFDMaxTxDataSize' )       { assignValueToPerSystemArray( \@canFDMaxTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagAddressingMode' )       { assignValueToPerSystemArray( \@diagAddressingMode, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagSourceAddr' )           { assignValueToPerSystemArray( \@diagSourceAddr, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagTargetAddr' )           { assignValueToPerSystemArray( \@diagTargetAddr, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagUseServiceByLocalId' )  { assignValueToPerSystemArray( \@diagUseServiceByLocalId, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagT1Identifier' )         { assignValueToPerSystemArray( \@diagT1Identifier, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagLocalIdentifier' )      { assignValueToPerSystemArray( \@diagLocalIdentifier, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagRxDataSize' )           { assignValueToPerSystemArray( \@diagMaxRxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagMaxRxDataSize' )        { assignValueToPerSystemArray( \@diagMaxRxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagTxDataSize' )           { assignValueToPerSystemArray( \@diagMaxTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagMaxTxDataSize' )        { assignValueToPerSystemArray( \@diagMaxTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagMinTxDataSize' )        { assignValueToPerSystemArray( \@diagMinTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagOpenSessionType' )      { assignValueToPerSystemArray( \@diagOpenSessionType, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagCustomSessionId' )      { assignValueToPerSystemArray( \@diagCustomSessionId, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagTesterPresentPeriod' )  { assignValueToPerSystemArray( \@diagTesterPresentPeriod, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethEcuIP' )                 { assignValueToPerSystemArray( \@ethEcuIP, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethEcuDNSHostName' )        { assignValueToPerSystemArray( \@ethEcuDNSHostName, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethEcuMac' )                { assignValueToPerSystemArray( \@ethMac, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethNetworkName' )           { assignValueToPerSystemArray( \@ethNetworkName, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethVirtualPortName' )       { assignValueToPerSystemArray( \@ethVirtualPortName, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethVLanID' )                { assignValueToPerSystemArray( \@vlanIDs, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethEcuPort' )               { assignValueToPerSystemArray( \@ethEcuPort, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethPcPort' )                { assignValueToPerSystemArray( \@ethPcPort, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethUseIpv6' )               { assignValueToPerSystemArray( \@ethUseIpv6, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethUseUdp' )                { assignValueToPerSystemArray( \@ethUseUdp, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethRxDataSize' )            { assignValueToPerSystemArray( \@ethMaxRxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethMaxRxDataSize' )         { assignValueToPerSystemArray( \@ethMaxRxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethTxDataSize' )            { assignValueToPerSystemArray( \@ethMaxTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 'ethMaxTxDataSize' )         { assignValueToPerSystemArray( \@ethMaxTxDataSize, $curVal, $systemNo ); }
        elsif( $curParam eq 't32Host' )                  { assignValueToPerSystemArray( \@t32Host, $curVal, $systemNo ); }
        elsif( $curParam eq 't32Port' )                  { assignValueToPerSystemArray( \@t32Port, int $curVal, $systemNo ); }
        elsif( $curParam eq 't32PacketLength' )          { assignValueToPerSystemArray( \@t32PacketLength, int $curVal, $systemNo ); }
        elsif( $curParam eq 't32TargetToHostBufferSize' ) { assignValueToPerSystemArray( \@t32TargetToHostBufferSize, int $curVal, $systemNo ); }
        elsif( $curParam eq 't32HostToTargetBufferSize' ) { assignValueToPerSystemArray( \@t32HostToTargetBufferSize, int $curVal, $systemNo ); }
        elsif( $curParam eq 'useSameRxTxChannel' )       { assignValueToPerSystemArray( \@useSameRxTxChannel, $curVal, $systemNo ); }
        elsif( $curParam eq 'canUsage' )                 { $canUsage                                           = $curVal; }
        elsif( $curParam eq 'ethUsage' )                 { $ethUsage                                           = $curVal; }
        elsif( $curParam eq 'canFDUsage' )               { $canFDUsage                                         = $curVal; }
        elsif( $curParam eq 'hostTimeoutMs' )            { assignValueToPerSystemArray( \@hostTimeoutMs, $curVal, $systemNo ); }
        elsif( $curParam eq 'gcpTimeoutMs' )             { assignValueToPerSystemArray( \@gcpTimeoutMs, $curVal, $systemNo ); }
        elsif( $curParam eq 'diagTimeoutMs' )            { assignValueToPerSystemArray( \@diagTimeoutMs, $curVal, $systemNo ); }
        elsif( $curParam eq 'targetConnectionName' )     { $targetConnectionName                               = $curVal; }

        elsif( $curParam eq 'sid' )
        {
            my $newCore0sid = $curVal - $systemNo;
            # Check that the SID is in the valid range
            die "Error: Parameter -sid ($curVal) has to be in the range [1..255] at system $systemNo\n" unless 0 < $curVal and $curVal < 256;
            # Check that SIDs for the different systems are consecutive numbers
            die "Error: Parameter -sid ($curVal) is not a consecutive number at system $systemNo\n" unless 0 == $core0sid or $core0sid == $newCore0sid;
            # Check that TargetID (= SID % 32) is not 0 for current system
            die "Error: Parameter -sid ($curVal) % 32 cannot be zero at system $systemNo\n" unless 0 < ( $curVal % 32 );
            # Check that the TargetID will be greater than 0 for all systems
            foreach my $tempSystemNo (0..$systemNo)
            {
                my $systemNoDiff = $systemNo - $tempSystemNo;
                die "Error: Derived parameter -sid ($curVal - $systemNoDiff) % 32 for system $tempSystemNo cannot be zero at system $systemNo\n" unless 0 < ( ($curVal - $systemNoDiff) % 32 );
            }
                                                           $core0sid                             = $newCore0sid;
        }
        elsif( $curParam eq 'commsCoreOffset' )          { $commsCoreOffset                      = $curVal; }
        elsif( $curParam eq 'systemName' )               { $systemName[$systemNo]                = $curVal; }
        elsif( $curParam eq 'systemComment' )            { $systemComment[$systemNo]             = $curVal; }
        elsif( $curParam eq 'osBackgroundTaskName' )     { $osBackgroundTaskName[$systemNo]      = $curVal; }
        elsif( $curParam eq 'osBackgroundTaskId' )       { $osBackgroundTaskId[$systemNo]        = $curVal; }
        elsif( $curParam eq 'osBasicSchedFrameName' )    { $osBasicSchedFrameName[$systemNo]     = $curVal; }
        elsif( $curParam eq 'osBasicSchedFrameId' )      { $osBasicSchedFrameId[$systemNo]       = $curVal; }
        elsif( $curParam eq 'osBasicSchedFrameEventId' ) { $osBasicSchedFrameEventId[$systemNo]  = $curVal; }
        elsif( $curParam eq 'nofAdditionalCat1Isrs' )    { $nOfAdditionalCat1Isrs[$systemNo]     = $curVal; }    # For backwards compatibility
        elsif( $curParam eq 'numberOfAdditionalCat1Isrs' ) { $nOfAdditionalCat1Isrs[$systemNo]   = $curVal; }
        elsif( $curParam eq 'additionalCat1IsrIdOffset' ){ $additionalCat1IsrIdOffset[$systemNo] = $curVal; }
        elsif( $curParam eq 't1HandlerPeriodMs' )        { $t1HandlerPeriodMs[$systemNo]         = $curVal; }
        elsif( $curParam eq 'traceBufferEntries' )       { $traceBufferEntries[$systemNo]        = $curVal; }
        elsif( $curParam eq 'cpuLoadThreshold' )         { $cpuLoadThreshold[$systemNo]          = $curVal; }
        elsif( $curParam eq 'numberOfUserStpws' )        { $numberOfUserStpws[$systemNo]         = $curVal; }
        elsif( $curParam eq 'numberOfConstraints' )      { $numberOfConstraints[$systemNo]       = $curVal; }
        elsif( $curParam eq 'analysisCapacity' )         { $analysisCapacity[$systemNo]          = $curVal; }
        elsif( $curParam eq 'flexAnalysisCapacity' )     { $flexAnalysisCapacity[$systemNo]      = $curVal; }
        elsif( $curParam eq 'targetType' )               { $targetType[$systemNo]                = $curVal; $cortex = 'true' if $curVal =~ /^ARM/ ; } # All supported ARMs are Cortex
        elsif( $curParam eq 'nofDelays' )                { $nOfDelays[$systemNo]                 = $curVal; }    # For backwards compatibility
        elsif( $curParam eq 'numberOfDelays' )           { $nOfDelays[$systemNo]                 = $curVal; }
        elsif( $curParam eq 'checkIntegration' )         { $checkIntegration                     = $curVal; }

        elsif( $curParam eq 'systemType' )               { $systemType[$systemNo]                = $curVal; }
        elsif( $curParam eq 'tickDurationNs' )           { $tickDurationNs[$systemNo]            = $curVal; }
        elsif( $curParam eq 'rawTickDurationNs' )        { $rawTickDurationNs[$systemNo]         = $curVal; }
        elsif( $curParam eq 'traceTimerIsMainTimer' )    { $traceTimerIsSyncTimer[$systemNo]     = $curVal; }    # For backwards compatibility
        elsif( $curParam eq 'traceTimerIsSyncTimer' )    { $traceTimerIsSyncTimer[$systemNo]     = $curVal; }
        elsif( $curParam eq 't1ScopeOverheadNs' )        { $t1ScopeOverheadNs[$systemNo]         = $curVal; }
        elsif( $curParam eq 't1FlexOverheadNs' )         { $t1FlexOverheadNs[$systemNo]          = $curVal; }
        elsif( $curParam eq 'nofFlexAddrs' )             { $nOfFlexAddrs[$systemNo]              = $curVal; }    # For backwards compatibility
        elsif( $curParam eq 'numberOfFlexAddrs' )        { $nOfFlexAddrs[$systemNo]              = $curVal; }
        elsif( $curParam eq 'nofFlexStopwatches' )       { $nOfFlexStopwatches[$systemNo]        = $curVal; }    # For backwards compatibility
        elsif( $curParam eq 'numberOfFlexStopwatches' )  { $nOfFlexStopwatches[$systemNo]        = $curVal; }
        elsif( $curParam eq 'numberOfFlexBufferEntries' ){ $numberOfFlexBufferEntries[$systemNo] = $curVal; }
        elsif( $curParam eq 'pTimer' )                   { $pTimer[$systemNo]                    = $curVal; }
        elsif( $curParam eq 'pSyncTimer' )               { $pSyncTimer                           = $curVal; }
        elsif( $curParam eq 'traceTimerDownCounting' )   { $traceTimerDownCounting[$systemNo]    = $curVal; }
        elsif( $curParam eq 'syncTimerDownCounting' )    { $syncTimerDownCounting                = $curVal; }
        elsif( $curParam eq '32BitCpuWithSmallerTimer' ) { if( $curVal eq 'true' and $rawTimerBitLength[$systemNo] == 32 ) { $rawTimerBitLength[$systemNo] = 16; } }
        elsif( $curParam eq 'rawTimerBitLength' )        { $rawTimerBitLength[$systemNo]         = $curVal < 16 ? 16 : 32 < $curVal ? 32 : $curVal; }
        elsif( $curParam eq 'cpuLoadTxPeriod' && 0 < $curVal ) { $cpuLoadTxPeriod[$systemNo]     = $curVal; }
        elsif( $curParam eq 'cpuLoadAvgSamples' )        { $cpuLoadAvgSamples[$systemNo]         = $curVal; }
        elsif( $curParam eq 'contRunsOnCore' )           { $contRunsOnCore{$systemNo}            = $curVal; }
        elsif( $curParam eq 'staticRunnableID' )         { $staticRunnableID                     = $curVal; }
        elsif( $curParam eq 'maxPreemptionDepth' )       { $maxPreemptionDepth{$systemNo}        = $curVal; }
        elsif( $curParam eq 'dpcAlways' )                { $dpcSymbols[$systemNo]{$curVal}       = 'Preferred'; }
        elsif( $curParam eq 'dpcNever' )                 { $dpcSymbols[$systemNo]{$curVal}       = 'Never'; }
        elsif( $curParam eq 'retainSymbol' )             { $retainSymbols[$systemNo]{$curVal}    = 1; }
        elsif( $curParam eq 'retainMax' )                { $retainMax[$systemNo]                 = $curVal; }
        elsif( $curParam eq 'retainIgnoreCase' )         { $retainIgnoreCase[$systemNo]          = $curVal; }
        elsif( $curParam eq 'featureMaskCallback' )      { $featureMaskCallback[$systemNo]       = $curVal eq 'true' ? 1 : 0; }
        elsif( $curParam eq 'syncPeriodMs' )             { $syncPeriodMs                         = $curVal; }
        elsif( $curParam eq 'traceTimeStampBitLength' )  { $traceTimeStampBitLength              = $curVal; }
        elsif( $curParam eq 'enableStreaming' )          { $enableStreaming                      = $curVal; }
        elsif( $curParam eq 'enableDoxygenComments' )    { $enableDoxygenComments                = $curVal; }
        elsif( $curParam eq 'addConstraintToUserSW' )    { push @{$addConstraintToUserSW{$systemNoIncAll}}, $curVal; }
        elsif( $curParam eq 'countPreemption' )          { $countPreemption                      = $curVal; }
        elsif( $curParam eq 'foregroundCont' )           { $foregroundCont                       = $curVal; }
        elsif( $curParam eq 'waitResume' )               { $waitResume                           = $curVal; }
        elsif( $curParam eq 'crossCoreAct' )             { $crossCoreAct                         = $curVal; }
        elsif( $curParam eq 'disableT1Cont' )            { $disableT1Cont                        = $curVal; }
        elsif( $curParam eq 'disableT1Flex' )            { $disableT1Flex                        = $curVal; }
        elsif( $curParam eq 'disableT1Mod' )             { $disableT1Mod                         = $curVal; }
        elsif( $curParam eq 'disableT1Delay' )           { $disableT1Delay                       = $curVal; }
        elsif( $curParam eq 'suppotTimerOverflow' )      { $supportTimerOverflow                 = $curVal; }    # For backwards compatibility
        elsif( $curParam eq 'supportTimerOverflow' )     { $supportTimerOverflow                 = $curVal; }
        elsif( $curParam eq 'detectTimerOverflow' )      { $detectTimerOverflow                  = $curVal; }
        elsif( $curParam eq 'numberOfVirtualStopwatches' ){ $numberOfVirtualStopwatches          = $curVal; }
        elsif( $curParam eq 'defineStack' )              { defineStack( $systemNo, \@defineStack, $curVal); }
        elsif( $curParam eq 'assignTaskStack' )          { assignTaskStack( $systemNo, \@assignTaskStack, $curVal); }
        elsif( $curParam eq 'assignIsrStack' )           { assignTaskStack( $systemNo, \@assignTaskStack, $curVal); } # Is a synonym for -assignTaskStack
        elsif( $curParam eq 'minT1HostSwVersion' )       { $minT1HostSwVersion                   = $curVal; }
        elsif( $curParam eq 'useDMStrampoline' )         { assignValueToPerSystemArray( \@useDMStrampoline, $curVal, $systemNo ); }
        elsif( $curParam eq 'trapCls3UserHandler' )      { assignValueToPerSystemArray( \@trapCls3UserHandler, $curVal, $systemNo ); }
        else
        {
            # This has to be consistent with the copy above
            die qq(Error: invalid parameter "${curParam}" found in invocation file "${_[1]}"\n);
        }
    }

    return;
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
# sub trimStringRef Removes leading and trailing whitespace expects a reference to a string
######################################################################################

sub trimStringRef
{
    my $stringRef = shift;

    $$stringRef =~ s/^\s+//;
    $$stringRef =~ s/\s+$//;

    return;
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
        return 1 == mkdir $dirname ; # return 1 if mkdir returned 1, otherwise return 0
    }
    else
    {
        return 1; # directory already exists or is empty -> nothing to be created
    }
}

######################################################################################
# sub writeUnlessEqual returns 1 if and only if the file was written
######################################################################################

sub writeUnlessEqual
{
    my $fileName = shift;
    my $newContent = shift;
    my $encoding = shift;

    if( $encoding )
    {
        # Open using the specified encoding
        $encoding = ":encoding(${encoding})";
    }
    else
    {
        # Open using the systems default encoding
        $encoding = '';
    }

    createPath( $fileName ) or die qq(Error: Unable to create directory for "${fileName}"\n);

    if( -r $fileName )
    {
        open my $fhOld, "<${encoding}", $fileName or die qq(Error: Unable to read "${fileName}"\n);
        # Locally set Perl Input Record Separator ($/) to undef, to be able to read in
        # the whole file with the diamond operator (<>)
        my $oldContentWithoutComments = do { local $/ = undef; <$fhOld> };
        close $fhOld;

        # Remove comments because one will contain the generation time,
        # which is always different but does not mean that there are any interesting
        # changes.
        my $newContentWithoutComments = $newContent;
        $oldContentWithoutComments =~ s/<Comment>.*<\/Comment>//g; # Remove XML Comment elements
        $oldContentWithoutComments =~ s/\/\*.*?\*\///gs; # Remove all C style (multi-line) comments

        $newContentWithoutComments =~ s/<Comment>.*<\/Comment>//g; # Remove XML Comment elements
        $newContentWithoutComments =~ s/\/\*.*?\*\///gs; # Remove all C style (multi-line) comments

        return 0 if $oldContentWithoutComments eq $newContentWithoutComments;
    }

    open my $fhNew, ">${encoding}", $fileName or die qq(Error: Unable to write "${fileName}"\n);
    printf qq(Debug: File "${fileName}" Layers %s\n), ( join ', ', PerlIO::get_layers( $fhNew ) ) if $debug;
    print $fhNew $newContent;
    close $fhNew;

    return 1;
}

######################################################################################
# sub getNewestFileMatchingWildcard
######################################################################################
sub getNewestFileMatchingWildcard($)
{
    my $pathAndFileName = shift;
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

         opendir my $FILE_DIR, $dir or die qq(Error: Directory "${dir}" for "${pathAndFileName}" not found\n);
         my @files = grep { /\.$fileSuffix$/ } readdir $FILE_DIR;
         closedir $FILE_DIR;

         my $regExFileName = $fileName;
         $regExFileName =~ s/\*/\(\.\*\)/;
         foreach my $file ( @files )
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

    return; # resolving failed
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
# Sub routine to process header files to be included / inlined
# This sub will try to extract the number of constraints and delays per core
# It will also check the syntax of the definitions of AF, STPWS, DELAYS, UE and UED
######################################################################################
sub processHeader($$)
{
    my $filePath = shift;
    my $nOfCores = int shift;
    my $fileName = File::Basename::basename($filePath);
    my $externData;

    if( MAX_NOF_CORES < $nOfCores )
    {
        die "Internal Error: \$nOfCores exceeds MAX_NOF_CORES in processHeader.\n";
    }

    local *max = sub
    {
        my $valA = shift;
        my $valB = shift;

        if( defined $valA and not defined $valB )
        {
            return $valA;
        }
        elsif( defined $valB and not defined $valA )
        {
            return $valB;
        }
        else
        {
            if( $valA > $valB )
            {
                return $valA;
            }
            else
            {
                return $valB;
            }
        }
    };

    my @listElementNames = (
        'AppFeature',
        'Delay',
        'SystemElement',
    );

    my @listAttributeNames = (
        'ExcludeFromCpuLoad',
        'FunctionalGroup',
        'Id', # DelayType
        'ID', # SystemElement
        'IsDataflow',
        'MaxActivations',
        'Name',
        'Offset',
        'Period',
        'Priority',
        'SID',
        'SymbolRef',
        'Type',
    );

    my %nOfElementsFound;

    my $currentElementName = undef;
    my $currentElementType = undef;
    my $currentCore = 'all';
    my $posInEnum = undef;

    open my $fhHeader, '<', $filePath or die qq(Error: Could not open file "${filePath}" for input\n);

    while ( my $currentLine = <$fhHeader> )
    {
        my $lineNumber = $.;

        chomp $currentLine;
        $externData .= $currentLine."\n";

        if( $currentLine =~ /^\s*#\s*define\s*T1_NOF_USER_STPWS_CORE(\d+)\s+\(*\s*(\d+)/ )
        {
            my $coreId = $1;
            my $nOfUserStopwatches = $2;
            if( $coreId < $nOfCores )
            {
                if( $numberOfUserStpws[$coreId] != 1 and $numberOfUserStpws[$coreId] != $nOfUserStopwatches )
                {
                    die "Error: Inconsistent number of stopwatches on core $coreId";
                }
            }
            # macro found in this file, value changed to negative for detection in T1_config.pm
            $numberOfUserStpws[$coreId] = -$nOfUserStopwatches;
        }
        elsif( $currentLine =~ /^\s*#\s*define\s*T1_NOF_CSRNS_CORE(\d+)\s+\(*\s*(\d+)/ )
        {
            my $coreId = $1;
            my $nOfConstraints = $2;
            if( $coreId < $nOfCores )
            {
                if( $numberOfConstraints[$coreId] != 1 and $numberOfConstraints[$coreId] != $nOfConstraints )
                {
                    die "Error: Inconsistent number of constraints on core $coreId";
                }
            }
            # macro found in this file, value changed to negative for detection in T1_config.pm
            $numberOfConstraints[$coreId] = -$nOfConstraints;
        }
        elsif( $currentLine =~ /^\s*T1_NOF_DELAYS_CORE(\d+)\s*=\s*\(*\s*(\d+)/ )
        {
            my $coreId = $1;
            my $nOfDelaysInt = $2;
            if( $coreId < $nOfCores )
            {
                if( $nOfDelays[$coreId] != 0 and $nOfDelays[$coreId] != $nOfDelaysInt )
                {
                    die "Error: Inconsistent number of delays on core $coreId";
                }
            }
            # macro found in this file, value changed to negative for detection in T1_config.pm
            $nOfDelays[$coreId] = -$nOfDelaysInt;
        }
        elsif( $currentLine =~ /enum/ )
        {
            $posInEnum = 0;
        }
        elsif( defined $posInEnum and $currentLine =~ /^\s*(\w+)\s*=\s*\(*\s*(\d+)/ )
        {
            # Matching this after "T1_NOF_DELAYS_CORExx" means that we don't check its value here
            if( $posInEnum != int $2 )
            {
                warn "Warning: The constant ${2} assigned to the enumerator '${1}' doesn't match it's position ${posInEnum} in enum, at '${fileName}' line ${lineNumber}\n";
            }
            ++$posInEnum;
        }
        elsif( defined $posInEnum and $currentLine =~ /\}/ )
        {
            undef $posInEnum;
        }
        elsif( $currentLine =~ /\@T1\@\s*<(?![\/])\s*(Info)\w*(.*?)\s*([\/])?>/ ) # XML Element Start Tag is Info
        {
            my $extra = $1;
            my $isSelfClosingTag = defined $2 ? 1 : 0;
            if( not defined $currentElementName or $currentElementName ne 'SystemElement' )
            {
                warn "Warning: XML element 'Info' is not inside XML element 'SystemElement', at '${fileName}' line ${lineNumber}\n";
            }
            elsif( not defined $currentElementType or $currentElementType ne 'UserEvent' )
            {
                warn "Warning: XML element 'Info' is not inside 'SystemElement' of the Type 'UserEvent', at '${fileName}' line ${lineNumber}\n";
            }
        }
        elsif( $currentLine =~ /\@T1\@\s*<(?![\/])([\w]+)\w*(.*?)\s*([\/])?>/ ) # XML Element Start Tag
        {
            my $elementName = $1;
            my $extra = $2;
            my $isSelfClosingTag = defined $3 ? 1 : 0;
            $currentElementType = undef;
            $currentCore = 'all';

            if( defined $currentElementName )
            {
                warn "Warning: Start Tag '${currentElementName}' without End Tag, at '${fileName}' line ${lineNumber}\n";
            }

            unless( grep { /^${elementName}$/ } @listElementNames )
            {
                warn "Warning: Unknown Start Tag '${elementName}', at '${fileName}' line ${lineNumber}\n";
            }

            my @keyValuePairs = $extra =~ /\s(\w+\s*=\s*".*?")/g;
            foreach my $keyValuePair ( @keyValuePairs )
            {
                if( $keyValuePair =~ /(\w+)\s*=\s*"(.*?)"/ )
                {
                    my $attributeName = $1;
                    my $value = $2;

                    unless( grep { /^${attributeName}$/ } @listAttributeNames )
                    {
                         warn "Warning: Unknown Attribute '${attributeName}', at '${fileName}' line ${lineNumber}\n";
                    }

                    if( $attributeName eq 'SID' )
                    {
                        $currentCore = (int $value) - $core0sid;
                    }
                    elsif( $attributeName eq 'Type' )
                    {
                        $currentElementType = $value;
                    }
                }
            }
            unless( $isSelfClosingTag )
            {
                $currentElementName = $elementName;
            }
        }
        elsif( $currentLine =~ /\@T1\@\s*<\/([\w]+)\s*>/ ) # XML Element End Tag
        {
            my $endTagName = $1;

            if( defined $currentElementName )
            {
                if( $currentElementName ne $endTagName )
                {
                    warn "Warning: Start Tag and End Tag names don't match ('${currentElementName}' ne '${endTagName}'), at '${fileName}' line ${lineNumber}\n";
                }
            }
            else
            {
                warn "Warning: End Tag '${endTagName}' without Start Tag, at '${fileName}' line ${lineNumber}\n";
            }

            undef $currentElementName;
            undef $currentElementType;
        }
        elsif( defined $currentElementName # is within XML element
                and (
                    $currentLine =~ /^\s*#\s*define\s+(\w+)\s+\(*\s*(0[xX][0-9a-fA-F]+|[0-9]+)/ # C define
                    or $currentLine =~ /^\s*(\w+)\s*=\s*\(*\s*(0[xX][0-9a-fA-F]+|[0-9]+)/ # C enum
                )
        )
        {
            my $elementName = $currentElementName;
            # Make SystemElement a Stopwatch or UserEvent
            if( defined $currentElementType )
            {
                $elementName = $currentElementType;
            }

            my $name  = $1;
            my $value = $2;

            # Extra Check for spaces between # and define in between XML start and end tag, this is necessary because of T1HOSTSW-290
            if( $elementName eq 'AppFeature' and $currentLine =~ /^\s*#\s+define/ )
            {
                warn "Warning: No spaces between # and define are allowed due to T1HOSTSW-290, at '${fileName}' line ${lineNumber}\n";
            }

            if( $value =~ /0[xX]((?i)[0-9a-f]+)/ )
            {
                $value = hex $1;
            }
            else
            {
                $value = int $value;
            }

            if( $elementName eq 'Delay' or $elementName eq 'Stopwatch' )
            {
                if( $currentCore ne 'all' )
                {
                    $nOfElementsFound{$elementName}{$currentCore} = max($nOfElementsFound{$elementName}{$currentCore}, $value);
                }
                else
                {
                    foreach my $coreId  ( 0..($nOfCores - 1) )
                    {
                        $nOfElementsFound{$elementName}{$coreId} = max($nOfElementsFound{$elementName}{$coreId}, $value);
                    }
                }
            }

            # Id range check
            if( 'all' eq $currentCore or $currentCore < $nOfCores )
            {
                if( $elementName eq 'Delay' )
                {
                    if( $value > 1023 )
                    {
                        warn "Warning: The id ${value} of Delay '${name}' is out of range (0-1023), at '${fileName}' line ${lineNumber}\n";
                    }
                }
                elsif( $elementName eq 'Stopwatch' )
                {
                    # Check that invocation file parameter -allocateUserSW is not present
                    if( @userStopWatches )
                    {
                        warn qq(Warning: Mix inline XML syntax and parameter -allocateUserSW might cause ID conflicts, at "${fileName}" line ${lineNumber}\n);
                    }

                    if( $value > 764 )
                    {
                        warn "Warning: The id ${value} of Stopwatch '${name}' is out of range (0-764), at '${fileName}' line ${lineNumber}\n";
                    }
                }
                elsif( $elementName eq 'UserEvent' )
                {
                    if( @userEvents )
                    {
                        if( $value < 32 )
                        {
                            # Check that invocation file parameter -allocateUDE is not present for User Data Events
                            warn qq(Warning: Mix inline XML syntax and parameter -allocateUDE might cause ID conflicts, at "${fileName}" line ${lineNumber}\n);
                        }
                        elsif( $value < 64 )
                        {
                            # Check that invocation file parameter -allocateUE is not present for User Events
                            warn qq(Warning: Mix inline XML syntax and parameter -allocateUE might cause ID conflicts, at "${fileName}" line ${lineNumber}\n);
                        }
                    }

                    if( $value > 63 )
                    {
                        warn "Warning: The id ${value} of UserEvent '${name}' is out of range (0-31 for UED and 32-63 for UE), at '${fileName}' line ${lineNumber}\n";
                    }
                }
                elsif( $elementName eq 'AppFeature' )
                {
                    # Check that invocation file parameter -allocateAF is not present
                    if( @applicationFeatures )
                    {
                        warn qq(Warning: Mix inline XML syntax and parameter -allocateAF might cause ID conflicts, at "${fileName}" line ${lineNumber}\n);
                    }
                }
            }
        }
    }

    close $fhHeader;

    foreach my $coreId ( 0..($nOfCores - 1) )
    {
        if( defined $numberOfUserStpws[$coreId] and defined $nOfElementsFound{'Stopwatch'}{$coreId} )
        {
            if( (abs $numberOfUserStpws[$coreId]) < ($nOfElementsFound{'Stopwatch'}{$coreId} + 1) )
            {
                printf "Info: At least one stopwatch with an id (%d) higher or equal to the configured number of stopwatches (%d) seen on core %d. These will not be supervised by T1.cont, but can still be analyzed with T1.scope.\n", $nOfElementsFound{'Stopwatch'}{$coreId}, abs $numberOfUserStpws[$coreId], $coreId;
            }
        }

        if( defined $nOfDelays[$coreId] and defined $nOfElementsFound{'Delay'}{$coreId} )
        {
            if( (abs $nOfDelays[$coreId]) < ($nOfElementsFound{'Delay'}{$coreId} + 1) )
            {
                warn sprintf "Warning: At least one delay with an id (%d) higher or equal to the configured number of delays (%d) seen on core %d!\n", $nOfElementsFound{'Delay'}{$coreId}, abs $nOfDelays[$coreId], $coreId;
            }
        }
    }

    return $externData;
}

######################################################################################
# Sub routine to allocate a new application features via the invocation file
######################################################################################
sub allocateAF
{
    my $value = shift;

    my ( $shortName, $name, $init, $mask ) = purposeBuiltParseLine( $value, ',' );

    # Trim leading and trailing white space
    trimStringRef( \$shortName ); # Mandatory
    trimStringRef( \$name ) if $name;
    trimStringRef( \$init ) if $init;
    trimStringRef( \$mask ) if $mask;

    $mask = $mask ? $mask : undef;

    # Ensure that these strings are not empty
    $init = 'false'    unless $init;
    $name = $shortName unless $name;

    # Ensure lower case
    $init = lc $init;
    $mask = lc $mask if $mask;

    # Checks
    unless( $shortName =~ /^\w+$/ )
    {
        my $newShortName = $shortName;
        $newShortName =~ s/\W/_/g;
        warn qq(Warning: "${shortName}" is not a valid C identifier, replacing invalid chars with '_', new identifier "${newShortName}"\n);
        $shortName = $newShortName;
    }

    if( defined $mask )
    {
        if( $mask =~ /^0x([0-9a-f]+)$/ )
        {
            $mask = hex $1;

            unless( $mask )
            {
                die qq(Error: '0' can not be used as mask\n);
            }
        }
        else
        {
            die qq(Error: Expected a hex value (format: 0x[0-9a-fA-F]+) as mask (saw '${mask}') or empty\n);
        }
    }

    my @validInitList = qw(true false);
    unless( grep { /^${init}$/ } @validInitList )
    {
        $init = 'false';
        warn qq(Warning: Expected true or false as init value, using default value "false" instead);
    }

    my %applicationFeature = (
        shortName    => $shortName,
        name         => $name,
        init         => $init,
        mask         => $mask,
    );

    push @applicationFeatures, \%applicationFeature;

    return;
}

######################################################################################
# Sub routine to allocate masks for the application features
######################################################################################
sub allocateAFMasks
{
    my $nextMask = 1;
    my @initFeatureMaskList;

    foreach my $afRef ( @applicationFeatures )
    {
        my $macroName = $afRef->{'shortName'};
        if( $macroName =~ /^T1_/ )
        {
            # Macro name already starts with T1_ assume that the user knows what he does
        }
        else
        {
            $macroName = "T1_AF_${macroName}";
        }
        $afRef->{'macroName'} = $macroName;

        my $mask = $afRef->{'mask'};
        unless( defined $mask )
        {
            $mask = $nextMask;
            $nextMask <<= 1;
        }
        else
        {
            my $maskAsBinaryString = sprintf "%b", $mask;
            $nextMask = 1 << ( length $maskAsBinaryString ); # Breaks VS Code syntax highlighting if written without parentheses
        }

        if( $mask > 0xFFFFFFFF )
        {
            my $name = $afRef->{'name'};
            my $hexMask = sprintf "0x%08X", $mask;
            die qq(Error: Bit mask (${hexMask}) for application feature "${name}" can not be represented as an UINT32.\n);
        }

        $afRef->{'mask'} = $mask;

        my $init = $afRef->{'init'};
        push @initFeatureMaskList, $macroName if 'true' eq $init;
    }

    unless( $initFeatureMask )
    {
        if( @initFeatureMaskList )
        {
            $initFeatureMask = join ' | ', @initFeatureMaskList;
        }
        else
        {
            $initFeatureMask = '0uL';
        }
    }

    return;
}

######################################################################################
# Sub routine to allocate a new delays via the invocation file
######################################################################################
sub allocateDL
{
    my $value    = shift;
    my $systemNo = shift;
    $systemNo = '_ALL' unless( defined $systemNo );

    my ( $shortName, $name, $init, $id ) = purposeBuiltParseLine( $value, ',' );

    # Trim leading and trailing white space
    trimStringRef( \$shortName ); # Mandatory
    trimStringRef( \$name ) if $name;
    trimStringRef( \$init ) if $init;
    trimStringRef( \$id )   if $id;

    # Ensure that name string is not empty
    $name = $shortName unless $name;

    # Ensure that optional parameter is 0 if not provided or lower case if provided
    $init = $init ? lc $init : '0us';

    # Ensure that optional parameter is undef if not provided or lower case if provided
    $id   = $id   ? lc $id   : undef;

    # Checks
    unless( $shortName =~ /^\w+$/ )
    {
        my $newShortName = $shortName;
        $newShortName =~ s/\W/_/g;
        warn qq(Warning: "${shortName}" is not a valid C identifier, replacing invalid chars with '_', new identifier "${newShortName}"\n);
        $shortName = $newShortName;
    }

    if( defined $init )
    {
        if( $init =~ /^(\d+[mu]?)[s]$/ )
        {
            $init = $1;
        }
        else
        {
            die qq(Error: Expected a duration (format: \\d+[mu]?[s]) for T1.delay "${shortName}" was "${init}".\n);
        }
    }

    if( defined $id )
    {
        if( $id =~ /^0x([0-9a-f]{1,8})$/ )
        {
            $id = hex $1;
        }
        elsif( $id =~ /^(\d+)$/ )
        {
            $id = int $1;
        }
        else
        {
            die qq(Error: Expected a hex (format: 0x[0-9a-fA-F]{2,8}), decimal or empty value as id (saw '${id}')\n);
        }
    }

    my %delay = (
        shortName   => $shortName,
        name        => $name,
        init        => $init,
        id          => $id,
        coreId      => $systemNo,
    );

    if( $systemNo eq '_ALL' )
    {
        # Push to all systems.
        # Please note, that references to the same hash will be pushed
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            push @{$delays[$coreId]}, \%delay;
        }
    }
    else
    {
        push @{$delays[$systemNo]}, \%delay;
    }

    return;
}

######################################################################################
# Sub routine to allocate ids for the delays
######################################################################################
sub allocateDLIds
{
    if( @delays )
    {
        # Check that there is at least one delay per system
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            unless( defined $delays[$coreId] )
            {
                # Create a dummy
                my %delay = (
                    shortName   => 'DUMMY_0',
                    name        => 'Dummy Delay 0',
                    init        => '0s',
                    id          => 0,
                    coreId      => $coreId,
                );

                # Ensure that there is at least one delay per system
                push @{$delays[$coreId]}, \%delay;
            }
        }

        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            my $nextDlId = 0;

            # Start with core _ALL
            foreach my $dlRef ( sort { $b->{'coreId'} cmp $a->{'coreId'} } @{$delays[$coreId]} )
            {
                my $id = $dlRef->{'id'};

                if( defined $id )
                {
                    if( $id > $nextDlId )
                    {
                        foreach my $val ( $nextDlId .. $id-1 )
                        {
                            my %delay = (
                                name    => 'dummy',
                                init    => 0,
                                id      => $val,
                                coreId  => $coreId,
                            );
                            splice @{$delays[$coreId]}, $val, 0, \%delay;
                        }
                    }
                }
                else
                {
                    $id = $nextDlId;
                }

                $nextDlId = $id + 1;

                if( $id < 0 or 254 < $id )
                {
                    my $name = $dlRef->{'name'};
                    die qq(Error: Id (${id}) for T1.delay "${name}" is outside the allowed range [0..255].\n);
                }

                $dlRef->{'id'} = $id;
            }

            $nOfDelays[$coreId] = $nextDlId;

            @{$delays[$coreId]} = sort { $a->{'id'} <=> $b->{'id'} } @{$delays[$coreId]};
        }

        # Create proper macro names
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            foreach my $dlRef ( @{$delays[$coreId]} )
            {
                if( exists $dlRef->{'shortName'} )
                {
                    my $shortName = $dlRef->{'shortName'};
                    if( '_ALL' eq $dlRef->{'coreId'} )
                    {
                        if( $shortName =~ /^T1_/ )
                        {
                            # Macro name already starts with T1_ assume that the user knows what he does
                            $dlRef->{'macroAll'} = $shortName;
                        }
                        else
                        {
                            $shortName = "T1_DL_${shortName}";
                            $dlRef->{'macroAll'} = "${shortName}_CORE_ALL";

                            # Create aliases for the individual cores
                            my $coreMacro = "${shortName}_CORE${coreId}";
                            push @{$dlRef->{'perCoreMacro'}}, $coreMacro;
                        }
                    }
                    else
                    {
                        if( $shortName =~ /^T1_/ )
                        {
                            # Macro name already starts with T1 assume that the user knows what he does
                        }
                        else
                        {
                            $shortName = "T1_DL_${shortName}_CORE${coreId}";
                        }

                        # Create an entry for that core
                        @{$dlRef->{'perCoreMacro'}}[$coreId] = $shortName;
                    }

                    # Remove the unprocessed macro name
                    delete $dlRef->{'macro'};
                }
            }
        }
    }

    return;
}

######################################################################################
# Sub routine to allocate a new user and user data events via the invocation file
######################################################################################
sub allocateUE
{
    my $type     = shift;
    my $value    = shift;
    my $systemNo = shift;
    $systemNo = '_ALL' unless( defined $systemNo );

    unless( grep {/^${type}$/} ('UE', 'UDE') )
    {
        die qq(Error: Wrong User Event Type "${type}", please contact GLIWA support (support\@gliwa.com).\n);
    }

    my ( $shortName, $name, $color, $id ) = purposeBuiltParseLine( $value, ',' );

    # Trim leading and trailing white space
    trimStringRef( \$shortName ); # Mandatory
    trimStringRef( \$name )  if $name;
    trimStringRef( \$color ) if $color;
    trimStringRef( \$id )    if $id;

    # Ensure that optional parameter are undef if not provided or lower case if provided
    $color = $color ? lc $color : undef;
    $id    = $id    ? lc $id    : undef;

    # Ensure that name string is not empty
    $name = $shortName unless $name;

    # Checks
    unless( $shortName =~ /^\w+$/ )
    {
        my $newShortName = $shortName;
        $newShortName =~ s/\W/_/g;
        warn qq(Warning: "${shortName}" is not a valid C identifier, replacing invalid chars with '_', new identifier "${newShortName}"\n);
        $shortName = $newShortName;
    }

    if( defined $color )
    {
        if( $color =~ /^(#[0-9a-f]{6})$/ )
        {
            $color = uc $1;
        }
        elsif( $color =~ /^([a-z]+)$/ and exists {HTML_COLOR_LOOKUP()}->{$1} )
        {
            $color = uc {HTML_COLOR_LOOKUP()}->{$1};
        }
        else
        {
            die qq(Error: Value "${color}" is an unknown color or has wrong rgb format (#[0-9a-FA-F]{6}).\n);
        }
    }

    if( defined $id )
    {
        if( $id =~ /^0x([0-9a-f]{1,8})$/ )
        {
            $id = hex $1;
        }
        elsif( $id =~ /^(\d+)$/ )
        {
            $id = int $1;
        }
        else
        {
            die qq(Error: Expected a hex (format: 0x[0-9a-fA-F]{2,8}), decimal or empty value as id (saw '${id}')\n);
        }
    }

    my %userEvent = (
        shortName   => $shortName,
        name        => $name,
        color       => $color,
        id          => $id,
        coreId      => $systemNo,
        type        => $type,
    );

    if( $systemNo eq '_ALL' )
    {
        # Push to all systems.
        # Please note, that references to the same hash will be pushed
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            push @{$userEvents[$coreId]}, \%userEvent;
        }
    }
    else
    {
        push @{$userEvents[$systemNo]}, \%userEvent;
    }

    return;
}

######################################################################################
# Sub routine to allocate a new user events via the invocation file
######################################################################################
sub allocateUEKeyValue
{
    my $value    = shift;
    my $systemNo = shift;

    my ( $shortName, $key, $info ) = purposeBuiltParseLine( $value, ',' );

    # Trim leading and trailing white space
    trimStringRef( \$shortName ); # Mandatory
    trimStringRef( \$key );       # Mandatory
    trimStringRef( \$info );      # Mandatory

    my @coreIds = ( 0..MAX_NOF_CORES-1 );
    @coreIds    = ( $systemNo ) if defined $systemNo;

    UE: foreach my $coreId ( @coreIds )
    {
        foreach my $userEventRef ( @{$userEvents[$coreId]} )
        {
            if( $userEventRef->{'shortName'} eq $shortName )
            {
                my $type = $userEventRef->{'type'};

                if( 'UE' eq $type )
                {
                    $userEventRef->{'key'}->{$key} = $info;
                }
                else
                {
                    # Omit a warning message and continue processing
                    warn qq(Warning: Parameter "-allocateUEKeyValue=${shortName}" is only allowed for User Events and not for User Data Events.\n);
                }

                # A given name may be used for multiple systems but the references
                # all point to the same object so only one update is required.
                last UE;
            }
        }
    }

    return;
}

######################################################################################
# Sub routine to allocate ids for the user events
######################################################################################
sub allocateUEIds
{
    if( @userEvents )
    {
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            if( $userEvents[$coreId] )
            {
                my $nextUdeId = 0;
                my $nextUeId  = 32;

                # Start with core _ALL
                foreach my $ueRef ( sort { $b->{'coreId'} cmp $a->{'coreId'} } @{$userEvents[$coreId]} )
                {
                    my $type = $ueRef->{'type'};
                    my $id = $ueRef->{'id'};
                    my $validMin;
                    my $validMax;

                    if( 'UDE' eq $type )
                    {
                        $validMin = 0;
                        $validMax = 31;

                        unless( defined $id )
                        {
                            $id = $nextUdeId;
                        }

                        $nextUdeId = $id + 1;
                    }
                    elsif( 'UE' eq $type )
                    {
                        $validMin = 32;
                        $validMax = 63;

                        unless( defined $id )
                        {
                            $id = $nextUeId;
                        }

                        $nextUeId = $id + 1;
                    }
                    else
                    {
                        die; # Should not occur as checked before in allocateUE
                    }

                    if( $validMin > $id or $validMax < $id )
                    {
                        my $name = $ueRef->{'name'};
                        my %shortTypeNameToFull = (
                            UE  => 'User Event',
                            UDE => 'User Data Event',
                        );
                        my $typeName = $shortTypeNameToFull{$type};
                        die qq(Error: Id (${id}) for ${typeName} "${name}" is outside the allowed range [${validMin}..${validMax}].\n);
                    }

                    $ueRef->{'id'} = $id;
                }
            }
        }

        # Create proper macro names
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            foreach my $ueRef ( @{$userEvents[$coreId]} )
            {
                my $type = $ueRef->{'type'};
                if( exists $ueRef->{'shortName'} )
                {
                    my $shortName = $ueRef->{'shortName'};
                    if( '_ALL' eq $ueRef->{'coreId'} )
                    {
                        if( $shortName =~ /^T1_/ )
                        {
                            # Macro name already starts with T1_ assume that the user knows what he does
                            $ueRef->{'macroAll'} = $shortName;
                        }
                        else
                        {
                            $shortName = "T1_${type}_${shortName}";
                            $ueRef->{'macroAll'} = "${shortName}_CORE_ALL";

                            # Create aliases for the individual cores
                            my $coreMacro = "${shortName}_CORE${coreId}";
                            push @{$ueRef->{'perCoreMacro'}}, $coreMacro;
                        }
                    }
                    else
                    {
                        if( $shortName =~ /^T1_/ )
                        {
                            # Macro name already starts with T1 assume that the user knows what he does
                        }
                        else
                        {
                            $shortName = "T1_${type}_${shortName}_CORE${coreId}";
                        }

                        # Create an entry for that core
                        @{$ueRef->{'perCoreMacro'}}[$coreId] = $shortName;
                    }
                    # Remove the unprocessed macro name
                    delete $ueRef->{'macro'};
                }
            }
        }
    }

    return;
}

######################################################################################
# purposeBuiltParseLine Splits a string into list of words ignoring delimiters that
#                       appear inside double quotes (")
######################################################################################
sub purposeBuiltParseLine
{
    my $line = shift;
    my $delim = shift;

    my $startPos = 0;
    while( 1 )
    {
        my $firstDelimPos = index $line, $delim, $startPos;
        if( -1 == $firstDelimPos )
        {
            # No delimiter at all
            # Strip quotation marks if necessary
            if( $line =~ /^\s*\"(.*)\"\s*$/ )
            {
                $line = $1;
            }

            return $line;
        }
        else
        {
            my $firstQmPos = index $line, '"', $startPos;
            if( -1 == $firstQmPos )
            {
                # No quotation marks at all
                my $param = substr $line, 0, $firstDelimPos;
                my $rest  = substr $line, $firstDelimPos + 1;

                # Strip quotation marks and whitespace if necessary
                if( $param =~ /^\s*\"(.*)\"\s*$/ )
                {
                    $param = $1;
                }

                return $param, purposeBuiltParseLine( $rest, $delim );
            }
            else
            {
                my $secondQmPos = index $line, '"', $firstQmPos + 1;
                if( $firstQmPos < $firstDelimPos )
                {
                    # Quotation mark before delimiter
                    if( -1 == $secondQmPos )
                    {
                        die qq(Error: Unbalanced quotation marks in parameter "${line}".);
                    }
                    else
                    {
                        # We cannot just split at this point we have to continue to
                        # search for quotation marks
                        $startPos = $secondQmPos + 1;
                    }
                }
                elsif( $secondQmPos < $firstDelimPos )
                {
                    # We cannot just split at this point we have to continue to
                    # search for quotation marks
                    $startPos = $secondQmPos + 1;
                }
                else
                {
                    # First quotation mark is after first delimiter
                    my $param = substr $line, 0, $firstDelimPos;
                    my $rest  = substr $line, $firstDelimPos + 1;

                    # Strip quotation marks and whitespace if necessary
                    if( $param =~ /^\s*\"(.*)\"\s*$/ )
                    {
                        $param = $1;
                    }

                    return $param, purposeBuiltParseLine( $rest, $delim );
                }
            }
        }
    }

    return; # This is unreachable and here just for the linter
}
######################################################################################
# Sub routine to allocate a new user stopwatch via the invocation file
######################################################################################

my %validUserSWTypes = (
    CET         => undef,
    DA          => undef,
    DEFAULT     => undef,
    GET         => undef,
    SCOPE       => undef,
    SCOPE_DA    => undef,
    SCOPE_FIFO  => undef,
    SCOPE_LIFO  => undef,
);

sub allocateUserSW
{
    my $value    = shift;
    my $systemNo = shift;
    $systemNo = '_ALL' unless( defined $systemNo );

    my ( $shortName, $name, $type, $id ) = purposeBuiltParseLine( $value, ',' );
    my $t1cont = 'true';

    # Trim leading and trailing white space
    trimStringRef( \$shortName ); # Mandatory
    trimStringRef( \$name ) if $name;
    trimStringRef( \$type ) if $type;

    # Ensure that strings are not empty
    $name = $shortName unless $name;
    $type = 'DEFAULT'  unless $type;

    # Ensure upper case for type
    $type = uc $type;

    # Checks
    unless( $shortName =~ /^\w+$/ )
    {
        my $newShortName = $shortName;
        $newShortName =~ s/\W/_/g;
        warn qq(Warning: "${shortName}" is not a valid C identifier, replacing invalid chars with '_', new identifier "${newShortName}");
        $shortName = $newShortName;
    }

    unless( exists $validUserSWTypes{$type} )
    {
        $type = 'DEFAULT';
        warn qq(Warning: Expected one of the following types ) . ( join ', ', map { qq("$_") } keys %validUserSWTypes ) . qq(, using default value "DEFAULT" instead);
    }

    if( $type =~ /^SCOPE/ )
    {
        # T1.scope only stopwatch
        $t1cont = 'false';
    }

    my %userStopWatch = (
        shortName   => $shortName,
        name        => $name,
        type        => $type,
        t1cont      => $t1cont,
        coreId      => $systemNo,
        id          => defined $id ? int $id : undef,
    );

    if( $systemNo eq '_ALL' )
    {
        # Push to all systems.
        # Please note, that references to the same hash will be pushed
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            push @{$userStopWatches[$coreId]}, \%userStopWatch;
        }
    }
    else
    {
        push @{$userStopWatches[$systemNo]}, \%userStopWatch;
    }

    return;
}

sub addConstraintToUserSW
{
    my $param    = shift;
    my $systemNo = shift;

    # -addConstraintToUserSW=<shortName>, <subType>, <value>[, <type>]

    my ( $shortName, $subType, $value, $type ) = purposeBuiltParseLine( $param, ',' );

    # Trim leading and trailing white space
    trimStringRef( \$shortName ); # Mandatory
    trimStringRef( \$subType );   # Mandatory
    trimStringRef( \$value );     # Mandatory
    trimStringRef( \$type )       if $type;

    # Ensure upper case for types
    $subType = uc $subType;
    $type    = uc $type if $type;

    # Checks
    unless( $subType =~ /^(?:MAX|MIN)$/ )
    {
        die qq(Error: Wrong subType "${subType}" in parameter -addConstraintToUserSW, allowed subType are min and max\n);
    }

    my $siPrefix;
    if( $value =~ /^(\d+)\s*([mun]?)[s]?$/ )
    {
        $value    = int $1;
        $siPrefix = $2;
    }
    else
    {
        die qq(Error: Value "${value}" does not match its specified format in parameter -addConstraintToUserSW, the format of value should be follow the following regular expression "\\d+\\s*[mun]?[s]?"\n);
    }
    my @validTypesList = qw(CET DA GET SCOPE_CET SCOPE_DA SCOPE_FIFO SCOPE_GET SCOPE_LIFO);

    if( $type )
    {
        unless( grep { /^${type}$/ } @validTypesList )
        {
            die qq(Error: Wrong type "${type}" in parameter -addConstraintToUserSW, expected one of the following types ) . ( join ', ', map { qq("$_") } @validTypesList ) . "\n";
        }
    }

    my @coreIds = ( 0..MAX_NOF_CORES-1 );
    @coreIds    = ( $systemNo ) if defined $systemNo;

    my $foundMatchingUserSW;

    COREID: foreach my $coreId ( @coreIds )
    {
        foreach my $userStopWatchRef ( @{$userStopWatches[$coreId]} )
        {
            if( $userStopWatchRef->{'shortName'} eq $shortName )
            {
                # Found SW with matching shortName

                # Type is one of the following CET DA DEFAULT GET SCOPE SCOPE_DA
                my $swType = $userStopWatchRef->{'type'};

                unless( $type )
                {
                    if( $swType =~ /^(?:DEFAULT|SCOPE)$/ )
                    {
                        warn qq(Warning: Type "${swType}" of User Stopwatch "${shortName}" can not be used as type for constraint, please consider to explicitly set the constraint type\n);
                        last COREID;
                    }
                    else
                    {
                        $type = $swType;
                    }
                }
                else
                {
                    if( $type eq $swType )
                    {
                        # Okay
                    }
                    elsif( $type eq 'SCOPE_DA' and $swType =~ /DA$/ )
                    {
                        # Okay
                    }
                    elsif( $type =~ /^SCOPE_(?:CET|GET)$/ and $swType =~ /(?:CET|GET)$/ )
                    {
                        # Okay
                    }
                    else
                    {
                        warn qq(Warning: Types of User Stopwatch ("${swType}") and Constraint ("${type}") are incompatible\n);
                        last COREID;
                    }
                }

                my %hash = (
                    type        => $type,
                    subType     => $subType,
                    value       => $value,
                    siPrefix    => $siPrefix,
                );

                push @{$userStopWatchRef->{'constraints'}}, \%hash;

                $foundMatchingUserSW = 1;
                # A given name may be used for multiple systems but the references
                # all point to the same object so only one update is required.
                last COREID;
            }
        }
    }

    unless( $foundMatchingUserSW )
    {
        warn qq(Warning: Found no T1 user stopwatch with a matching shortName for constraint "${shortName}".\n);
    }

    return;
}

######################################################################################
# Sub routine to allocate ids for the user stopwatches
######################################################################################
sub allocateUserSWIds
{
    if( @userStopWatches )
    {
        # Check that there is at least one user stopwatch supervised by T1.cont per system
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            my $count = 0;
            foreach my $swRef ( @{$userStopWatches[$coreId]} )
            {
                $count++ if( 'true' eq $swRef->{'t1cont'} );
            }

            unless( $count )
            {
                # Ensure that there is at least one user stopwatch per system
                my %userStopWatch = (
                    shortName   => 'DUMMY_SW',
                    name        => undef,
                    type        => 'DEFAULT',
                    t1cont      => 'true',
                    coreId      => $coreId,
                    id          => undef,
                );
                push @{$userStopWatches[$coreId]}, \%userStopWatch;
            }
        }

        # Sort user stopwatches, stopwatches supervised by T1.cont first
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            @{$userStopWatches[$coreId]} = sort {$b->{'t1cont'} cmp $a->{'t1cont'}} sort {$b->{'coreId'} cmp $a->{'coreId'}} @{$userStopWatches[$coreId]};
        }

        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            my $swIdCounter = 0;

            foreach my $swRef ( @{$userStopWatches[$coreId]} )
            {
                if( not defined $swRef->{'id'} )
                {
                    $swRef->{'id'} = $swIdCounter++;
                }
                else
                {
                    $swIdCounter = 1 + int $swRef->{'id'};
                }
            }
        }

        # Sort user stopwatches by ID
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            @{$userStopWatches[$coreId]} = sort {$a->{'id'} <=> $b->{'id'}} @{$userStopWatches[$coreId]};
        }

        # Check for gaps in the ID space and fill them if necessary
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            my $arrayIdxCounter = 0;
            my $lastSwId = -1;

            foreach my $swRef ( @{$userStopWatches[$coreId]} )
            {
                my $id = $swRef->{'id'};
                if( $lastSwId + 1 < $id and 'true' eq $swRef->{'t1cont'} )
                {
                    my $val = ++$lastSwId;
                    my %userStopWatch = (
                        shortName   => "T1_SW_DUMMY_SW_${val}_CORE${coreId}",
                        name        => undef,
                        type        => 'CET',
                        t1cont      => $swRef->{'t1cont'},
                        coreId      => $coreId,
                        id          => $val,
                    );
                    splice @{$userStopWatches[$coreId]}, $arrayIdxCounter, 0, \%userStopWatch;
                }
                else
                {
                    $lastSwId = $id;
                }

                # Figure out how many SW are supervised by T1.cont on each core
                if( 'true' eq $swRef->{'t1cont'} )
                {
                    $numberOfUserStpws[$coreId] = $id + 1;
                }

                # Check the IDs
                if( 'true' eq $swRef->{'t1cont'} and 255 < $id )
                {
                    my $name = $swRef->{'name'};
                    die qq(Error: The ID (${id}) of the user stopwatch "${name}" exceeds the available ID (255) space for stopwatches which are supervised by T1.cont.\n)
                }
                elsif( 1023 < $id )
                {
                    my $name = $swRef->{'name'};
                    die qq(Error: The ID (${id}) of the user stopwatch "${name}" exceeds the available ID (1023) space for stopwatches.\n)
                }

                $arrayIdxCounter++;
            }
        }

        # Create proper macro names
        foreach my $coreId ( 0..MAX_NOF_CORES-1 )
        {
            foreach my $swRef ( @{$userStopWatches[$coreId]} )
            {
                if( exists $swRef->{'shortName'} )
                {
                    my $macroName = $swRef->{'shortName'};
                    if( '_ALL' eq $swRef->{'coreId'} )
                    {
                        if( $macroName =~ /^T1_/ )
                        {
                            # Macro name already starts with T1_ assume that the user knows what he does
                            $swRef->{'macroAll'} = $macroName;
                        }
                        else
                        {
                            $macroName = "T1_SW_${macroName}";
                            $swRef->{'macroAll'} = "${macroName}_CORE_ALL";
                        }

                        # Create aliases for the individual cores
                        foreach my $localCoreId ( 0..MAX_NOF_CORES-1 )
                        {
                            my $coreMacro = "${macroName}_CORE${localCoreId}";
                            push @{$swRef->{'perCoreMacro'}}, $coreMacro;
                        }
                    }
                    else
                    {
                        if( $macroName =~ /^T1_/ )
                        {
                            # Macro name already starts with T1 assume that the user knows what he does
                        }
                        else
                        {
                            $macroName = "T1_SW_${macroName}_CORE${coreId}";
                        }

                        # Create an entry for that core
                        @{$swRef->{'perCoreMacro'}}[$coreId] = $macroName;
                    }
                }

                if( $swRef->{'constraints'} )
                {
                    # Currently only one T1.cont constraint is allowed per User SW
                    my $foundContConstraint = 0;

                    CSRN: foreach my $csrnRef ( @{$swRef->{'constraints'}} )
                    {
                        unless( $csrnRef->{'type'} =~ /^SCOPE_/ )
                        {
                            # At this point we are only interested in constraints that are going to be supervised by T1.cont
                            unless( $foundContConstraint )
                            {
                                $foundContConstraint = 1;

                                my %hash = (
                                    swMacro     => ( '_ALL' eq $coreId ) ? ($swRef->{'macroAll'}) : ($swRef->{'perCoreMacro'}[$coreId]),
                                    type        => $csrnRef->{'type'},
                                    subType     => $csrnRef->{'subType'},
                                    value       => $csrnRef->{'value'},
                                    siPrefix    => $csrnRef->{'siPrefix'},
                                    coreId      => $coreId,
                                );

                                push @{$constraints[$coreId]}, \%hash;
                            }
                            else
                            {
                                my $shortName = $swRef->{'shortName'};
                                warn qq(Warning: It is only possible to supervise one constraint per User Stopwatch with T1.cont, SW is "${shortName}"\n);
                                last CSRN;
                            }
                        }
                    }
                }
            }
        }
    }

    return;
}

######################################################################################
# Check that User Stopwatch Constraints are correctly configured
# Currently it only checks the number of constraints supervised by T1.cont per core
######################################################################################
sub checkUserSWCsrns
{
    foreach my $systemNo ( 0 .. MAX_NOF_CORES-1 )
    {
        # add constraint for check integration at the end of @constraints in case
        # it overflows, it will be removed first.
        if( $checkIntegration eq 'true' and $t1HandlerPeriodMs[$systemNo] )
        {
            my $maxT1HandlerPeriodMs = int eval "2 ** ($syncTimeBitLength) * ($syncTimerTickDurationNs) / 1000 / 1000";
            my $constraint = $maxT1HandlerPeriodMs <= ( 2 * $t1HandlerPeriodMs[$systemNo] ) ? $maxT1HandlerPeriodMs : ( 2 * $t1HandlerPeriodMs[$systemNo] );

            my %hash = (
                            'swMacro'  => "T1_SW_CHECK_INTEGRATION_CORE_ALL",
                            'subType'  => 'MAX',
                            'value'    => $constraint,
                            'siPrefix' => 'M',
                            'coreId'   => $systemNo,
                        );

            push @{$constraints[$systemNo]}, \%hash;
        }

        if( $constraints[$systemNo] )
        {
            my $countNofT1ContCsrns = scalar @{$constraints[$systemNo]};

            if( defined $numberOfConstraints[$systemNo] )
            {
                # if T1_NOF_CSRNS_COREx is parsed in the headers, $numberOfConstraints is negative
                if( $countNofT1ContCsrns > abs $numberOfConstraints[$systemNo] )
                {
                    warn qq(Warning: There are ${countNofT1ContCsrns} configured constraints for system ${systemNo}, but -numberOfConstraints or T1_NOF_CSRNS_CORE${systemNo} is set to ${numberOfConstraints[$systemNo]}\n);
                    if( $checkIntegration eq 'true' )
                    {
                        warn qq(Warning: No constraint available for -checkIntegration on system ${systemNo}, remove a configured constraint using -addConstraintToUserSW\n);
                    }

                    # Adjust the last array index
                    $#{$constraints[$systemNo]} -= $countNofT1ContCsrns - abs $numberOfConstraints[$systemNo];
                }
            }
            else
            {
                if( $countNofT1ContCsrns > 64 )
                {
                    warn qq(Warning: There are ${countNofT1ContCsrns} configured constraints for system ${systemNo}, but T1.cont only supports up to 64\n);
                    if( $checkIntegration eq 'true' )
                    {
                        warn qq(Warning: No constraint available for -checkIntegration on system ${systemNo}, remove a configured constraint using -addConstraintToUserSW\n);
                    }
                    $countNofT1ContCsrns = 64;
                }

                # numberOfConstraints is undefined yet so set it to the appropriate number
                $numberOfConstraints[$systemNo] = $countNofT1ContCsrns;
            }
        }

        # Check and adjust numberOfConstraints if needed
        if( not defined $numberOfConstraints[$systemNo] )
        {
            # Silently set it to 1 which is the default value
            $numberOfConstraints[$systemNo] = 1;
        }
        elsif( $numberOfConstraints[$systemNo] == 0 )
        {
            warn qq(Warning: Number of constraints (-numberOfConstraints or T1_NOF_CSRNS_CORE${systemNo}) for system ${systemNo} is set to 0, but can not be less than 1\n);
            $numberOfConstraints[$systemNo] = 1;
        }
        elsif( $numberOfConstraints[$systemNo] > 64 )
        {
            warn qq(Warning: Number of constraints (-numberOfConstraints or T1_NOF_CSRNS_CORE${systemNo}) for system ${systemNo} cannot be greater than 64\n);
            $numberOfConstraints[$systemNo] = 64;
        }
    }

    return;
}

######################################################################################
# sub defineStack
#
# Args:
#   - First:  System number or undef for "all"
#   - Second: Reference to the variable that stores the OsStacks
#   - Third:  The argument as seen in the invocation file, supported formats are
#       - Name, StartSymbolRef
#       - Name, StartSymbolRef, EndSymbolRef
#       - Name, StartSymbolRef, Size
#       - Name, StartSymbolRef, Size, Offset
#       - Size and Offset can be decimal or hexadecimal (0x) numbers
######################################################################################
sub defineStack
{
    my $systemNo = shift;
    my $defineStackRef = shift;
    my $curVal = shift;

    my $warnMsg = qq(Warning: Discarded invalid parameter "-defineStack=${curVal}"\n);

    my @splitedArguments = purposeBuiltParseLine( $curVal, ',' );

    my $name = shift @splitedArguments;
    trimStringRef( \$name );

    my $startSymbolRef = shift @splitedArguments;
    trimStringRef( \$startSymbolRef );
    unless( $startSymbolRef =~ /^[a-zA-Z_]\w*$/ ) # Valid C identifier
    {
        warn $warnMsg;
        return;
    }

    my $endSymbolRef;
    my $offset;
    my $size;

    if( 1 == scalar @splitedArguments )
    {
        # Assume (Name, StartSymbolRef), EndymbolRef or Size
        (my $thirdArg) = @splitedArguments;
        trimStringRef( \$thirdArg );

        if( $thirdArg =~ /^\d+/ ) # Decimal or Hex
        {
            $size = $thirdArg;
        }
        elsif( $thirdArg =~ /^[a-zA-Z_]\w*$/ ) # Valid C identifier
        {
            $endSymbolRef = $thirdArg;
        }
        else
        {
            warn $warnMsg;
            return;
        }
    }
    elsif( 2 == scalar @splitedArguments )
    {
        # Assume (Name, StartSymbolRef), Size, Offset
        ($size, $offset) = @splitedArguments;
    }
    elsif( 2 < scalar @splitedArguments )
    {
        # Too many arguments
        warn $warnMsg;
        return;
    }

    my $hashRef = {
        Name           => $name,
        StartSymbolRef => $startSymbolRef,
    };
    $hashRef->{'EndSymbolRef'} = $endSymbolRef if defined $endSymbolRef;

    my $assignAndTestInteger = sub {
        my ($hashRef, $key, $value) = @_;
        trimStringRef( \$value );
        $value = lc $value;
        if( $value =~ /^\d+$/ ) # Decimal
        {
            $value = int $value;
        }
        elsif( $value =~ /^0x[a-f\d]+$/ ) # Hex
        {
            $value = hex $value;
        }
        else
        {
            warn $warnMsg;
            return;
        }
        $hashRef->{$key} = $value;
    };

    $assignAndTestInteger->( $hashRef, 'Size', $size )     if defined $size;
    $assignAndTestInteger->( $hashRef, 'Offset', $offset ) if defined $offset;

    my @systems = (0..MAX_NOF_CORES-1);
    if( defined $systemNo )
    {
        @systems = (int $systemNo);
    }

    foreach my $system ( @systems )
    {
        push @{$$defineStackRef[$system]}, $hashRef;
    }

    return;
}

######################################################################################
#
######################################################################################
sub allocateCat1IsrIdPrio
{
    my $systemNo = shift;
    my $allocateCat1IsrIdPrioRef = shift;
    my $curVal = shift;

    my ($isrName, $prio) = purposeBuiltParseLine( $curVal, ',' );

    trimStringRef( \$isrName );
    $prio = int $prio;

    my @systems = (0..MAX_NOF_CORES-1);
    if( defined $systemNo )
    {
        @systems = int $systemNo;
    }

    # Ensure that the CAT1 isr names are unique per system
    foreach my $sysNo (@systems)
    {
        my $localIsrName = scalar @systems > 1 ? "${isrName}_${sysNo}" : $isrName;
        my %hash = (
            Name           => $localIsrName,
            SymbolName     => $isrName,
            ID             => undef,
            Priority       => $prio + 2000,
            Comment        => '',
            Offset         => 0,
            Period         => 0,
            Core           => $sysNo,
            Type           => 'Interrupt',
            Category       => 1,
            Context        => 'Internal',
            OsStackRef     => '',
        );

        $allocateCat1IsrIdPrioRef->{$localIsrName} = \%hash;
    }

    return;
}

######################################################################################
# Adds arguments of -assignTaskStack (or Isr) to per system array
######################################################################################
sub assignTaskStack
{
    my $systemNo = shift;
    my $assignTaskStackRef = shift;
    my $curVal = shift;

    my ($taskName, $osStackRef) = purposeBuiltParseLine( $curVal, ',' );

    trimStringRef( \$taskName );
    trimStringRef( \$osStackRef );

    my @systems = (0..MAX_NOF_CORES-1); # All systems probably makes no sense
    if( defined $systemNo )
    {
        @systems = (int $systemNo);
    }

    foreach my $system ( @systems )
    {
        push @{$$assignTaskStackRef[$system]}, {
            Pattern =>    $taskName,
            OsStackRef => $osStackRef,
        };
    }

    return;
}

######################################################################################
# Processes list of assignTaskStack parameters and hash references to system elements
# Args:
# - First: Number of cores, used to not process excess cores
# - Second: per system array that holds array of assignTaskStack (the one filled by
#           sub assignTaskStack)
# - Following: Hash references to hash of system element(s) as received from the OS
#              specific Perl module
######################################################################################
sub assignTaskStackSecondStage
{
    my $nOfCores = int shift;
    my $assignTaskStackRef = shift;

    while( my $hashRef = shift )
    {
        my @threadNames = keys %{$hashRef};

        foreach my $systemNo (0..$nOfCores-1)
        {
            my $assignTaskStackCurrentSystem = $$assignTaskStackRef[$systemNo];

            foreach my $assignTaskStackHashRef (@$assignTaskStackCurrentSystem)
            {
                my $pattern = $assignTaskStackHashRef->{'Pattern'};
                my $osStackRef = $assignTaskStackHashRef->{'OsStackRef'};
                # Implicit ^$ to not cause unwanted behaviour if the user does not use RegEx
                my @listOfMatchingThreadNames = grep {/^${pattern}$/} @threadNames;

                foreach my $threadName (@listOfMatchingThreadNames)
                {
                    my $localHashRef = $hashRef->{$threadName};

                    if( 'all' eq $localHashRef->{'Core'} or $systemNo == int $localHashRef->{'Core'} )
                    {
                        my $oldOsStackRef = $localHashRef->{'OsStackRef'};
                        unless( $oldOsStackRef )
                        {
                            # Either undef, '' or 0
                            $localHashRef->{'OsStackRef'} = $osStackRef;
                        }
                        elsif( $oldOsStackRef eq $osStackRef )
                        {
                            # No need to set to the same value again
                        }
                        else
                        {
                            print qq(Info: Already set OsStackRef="${oldOsStackRef}" will be overwritten with "${osStackRef}".\n) if $debug;
                        }
                    }
                    elsif( $nOfCores <= int $localHashRef->{'Core'} )
                    {
                        # Cleanup, remove threads that are assigned to excess cores
                        delete $hashRef->{$threadName};
                    }
                }
            }
        }
    }

    return
}

######################################################################################
# Generates the default GLIWA file header
######################################################################################
sub generateSourceFileHeader
{
    my $fileBaseName = shift;
    my $genDate = shift;

    my $fileEncodingLine = '';

    if( $sourceFileEncoding )
    {
        $fileEncodingLine = <<"EOT";
*
*   \\par Encoding
*                   ${sourceFileEncoding}
EOT
    }

    my $headerContent = <<EOT;
/*********************************************************************************//*!
*   \\file           ${fileBaseName}
*
*   \\brief          generated by T1_projGen.pl for project ${projectName}
*                   using license ${licInfo1} - ${licInfo2}
*
*   \\par Visibility
*                   External
${fileEncodingLine}*
*   \\date           ${genDate}
*
*   \\copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/
EOT
    return $headerContent
}

######################################################################################
# Takes file name and converts it to include guard macros, ensures that the macro only
# contains ASCII chars
######################################################################################
sub generateIncludeGuard
{
    my $fileBaseName = shift;
    my $headerMacro = uc $fileBaseName;

    # Replace no basic ASCII chars with underscores
    $headerMacro =~ s/[^[:ascii:]]|\./_/g;

    # Remove whitespace
    $headerMacro =~ s/\s//g;

    $headerMacro .= '_';

    my $includeGuardStart = <<"EOT";
#ifndef ${headerMacro}
#define ${headerMacro} (1)
EOT

    my $includeGuardEnd = "#endif /* ${headerMacro} */";

    return ($includeGuardStart, $includeGuardEnd);
}

######################################################################################
# Takes a file path and name, strips the path, and converts it to Perls internal
# character encoding (basically utf-8)
######################################################################################
sub getFileBaseName
{
    my $filePath = shift;

    my $fileBaseName = File::Basename::basename( $filePath );

    if( $systemFileNameEncoding )
    {
        $fileBaseName = decode( $systemFileNameEncoding, $fileBaseName );
    }

    return $fileBaseName;
}

######################################################################################
# Global variables which are set in sub createThreadXmlElementsAndDefines
######################################################################################
my @allTaskIds;
my $taskIdClash = 0; # True if tasks on different cores re-use the same ID
my %taskNames;
my %taskData = ();
my $runnableIndex = 65536; # Used for runnables which are supposed to be measured by T1.flex

######################################################################################
# sub createThreadXmlElementsAndDefines creates the XML elements for the T1 project
#                                       file and #defines for T1_config.h
# Args:
# - First: Number of cores
# - Second: Reference to per system array that holds the XML elements
# - Third: Reference to string that holds the #defines
# - Remaining: hash references as received from OS specific Perl module
######################################################################################
sub createThreadXmlElementsAndDefines
{
    my $nOfCores = int shift;
    my $stringPerSystemRef = shift;
    my $headerFileStringRef = shift;

    my $generateRunnablesForSE = sub {
        my ( $seName, $arrayRef ) = @_;
        my $sysElemsString = '';

        RUNNABLES: foreach my $runnableHashOrName ( @$arrayRef )
        {
            my $type = ref $runnableHashOrName;
            my $runnableName;
            my $symbolName;

            if( 'HASH' eq $type )
            {
                $runnableName = $runnableHashOrName->{'Name'};
                $symbolName   = $runnableHashOrName->{'SymbolName'};
            }
            elsif( 'REF' eq $type )
            {
                $runnableName = $$runnableHashOrName->{'Name'};
                $symbolName   = $$runnableHashOrName->{'SymbolName'};
            }
            elsif( '' eq $type )
            {
                $runnableName = $runnableHashOrName;
                # Prepend runnable name with symbolPrefix because the plain array contains just the names and not the symbols
                $symbolName   = $symbolPrefix . $runnableName;
            }
            else
            {
                warn qq(Warning: Invalid type "${type}" for runnable element in <SystemElement Name="${seName}">.\n);
                # Stop processing this list
                last RUNNABLES;
            }

            my $symbolRefString = '';
            $symbolRefString = qq( SymbolRef="${symbolName}") unless $symbolName eq '';
            $runnableName =~ s/\$.*\$//;
            $sysElemsString .= qq(        <SystemElement Name="${runnableName}" ID="${runnableIndex}" Type="Runnable"${symbolRefString} />\n);
            ++$runnableIndex;
        }

        return $sysElemsString;
    };

    my $threadsByIdThenName = sub {
        my $hashRef = shift;
        my @listOfThreadNames = sort keys %{$hashRef};

        @listOfThreadNames = sort {
            my $idA = OsGetValue( $hashRef, $a, 'ID');
            my $idB = OsGetValue( $hashRef, $b, 'ID');
            if( defined $idA and defined $idB )
            {
                return $idA <=> $idB;
            }
            else
            {
                return 0;
            }
        } @listOfThreadNames;

        return @listOfThreadNames;
    };

    while( my $hashRef = shift )
    {
        KEY: foreach my $key ( $threadsByIdThenName->( $hashRef ) )
        {
            my $threadCore = OsGetValue( $hashRef, $key, 'Core' );

            my @systems = (0..$nOfCores-1);
            if( 'all' ne $threadCore )
            {
                @systems = int $threadCore;

                if( $nOfCores <= int $threadCore )
                {
                    # Cleanup, remove threads that are assigned to excess cores
                    delete $hashRef->{$key};
                    next KEY;
                }
            }

            my $threadId = OsGetValue( $hashRef, $key, 'ID' );
            my $threadType    = OsGetValue( $hashRef, $key, 'Type' );
            if( 'Task' eq $threadType )
            {
                # The following code is used to check if there are TASK id clashes
                # which means that we cannot support cross core activations in
                # T1_config.pm
                if( $allTaskIds[$threadId] )
                {
                    $allTaskIds[$threadId]++;
                    $taskIdClash = 1;
                }
                else
                {
                    $allTaskIds[$threadId] = 1;
                }
            }

            my $threadName    = OsGetValue( $hashRef, $key, 'Name' );
            my $threadSymName = OsGetValue( $hashRef, $key, 'SymbolName' );
            my $threadPrio    = OsGetValue( $hashRef, $key, 'Priority' );
            my $threadPeriod  = OsGetValue( $hashRef, $key, 'Period' );
            my $threadOffset  = OsGetValue( $hashRef, $key, 'Offset' );

            my $threadMaxAct  = OsGetValue( $hashRef, $key, 'MaxActivations' );
            $threadMaxAct = 1 unless defined $threadMaxAct;
            # The limit of 256 is a FG T1.cont restriction, see #784 changeset 48166
            # and #2319
            # AUTOSAR allows up to 4294967295
            die qq(Error: Task "${threadName}" has more than 256 activations.\n) unless $threadMaxAct <= 256;

            my $threadComment = OsGetValue( $hashRef, $key, 'Comment' );
            my $threadRunnablesRef = OsGetValue( $hashRef, $key, 'Runnables' );
            my @threadRunnables;
            if( $threadRunnablesRef )
            {
                @threadRunnables = @$threadRunnablesRef;
            }
            else
            {
                $threadRunnablesRef = OsGetValue( $hashRef, $key, 'RunnablesElemRef' );
                @threadRunnables = @$threadRunnablesRef if $threadRunnablesRef;
            }
            my $osStackRef  = OsGetValue( $hashRef, $key, 'OsStackRef' );

            my $isrCategory = OsGetValue( $hashRef, $key, 'Category' );
            my $isrContext = OsGetValue( $hashRef, $key, 'Context' ); # Can be 'External' (OS module but external) or 'Internal' (Defined using -allocateCat1IsrIdPrio)

            my $threadDesc = $threadName;
            if( $threadComment ne '' )
            {
                $threadDesc   .= ": ${threadComment}";
                $threadComment = "/* ${threadComment} */";
            }

            $taskData{$threadId} = {
                coreId      => $threadCore,
                maxAct      => $threadMaxAct,
                isBg        => ('all' eq $threadCore or $osBackgroundTaskName[$threadCore] eq $threadName)
            };

            my $MaxActivationsStr = '';
            if( 'Task' eq $threadType )
            {
                $MaxActivationsStr = qq( MaxActivations="${threadMaxAct}");
            }

            my $stringA = qq(      <SystemElement Name="${threadDesc}" Priority="${threadPrio}" ID="${threadId}" Type="${threadType}"${MaxActivationsStr});
            my $stringB = qq( SymbolRef="${threadSymName}");
            $stringB .= qq( OsStackRef="${osStackRef}") if $osStackRef and isT1HostSwVersionAllowed( $minT1HostSwVersion, '3.4.0' );
            if( scalar @threadRunnables )
            {
                $stringB .= ">\n";
                $stringB .= $generateRunnablesForSE->( $threadDesc, \@threadRunnables );
                $stringB .= "      </SystemElement>\n";
            }
            else
            {
                $stringB .= " />\n";
            }

            foreach my $systemNo ( @systems )
            {
                if( $numberOfTasks[$systemNo] <= $threadId ) # find highest T1.scope ID of all tasks and isrs from OS-specific Perl-module
                {
                   $numberOfTasks[$systemNo] = $threadId + 1;
                }

                if( 'Interrupt' eq $threadType )
                {
                    if( $threadId < $cat1IsrIdOffset[$systemNo] and $isrCategory == 1 and $isrContext ne 'Internal' ) # find lowest cat1 ISR ID from OS-specific Perl-module
                    {
                        $cat1IsrIdOffset[$systemNo] = $threadId;
                    }

                    if( $threadId < $cat2IsrIdOffset[$systemNo] and $isrCategory == 2 ) # find lowest cat2 ISR ID from OS-specific Perl-module
                    {
                        $cat2IsrIdOffset[$systemNo] = $threadId;
                    }

                    if( $threadId < $externalIsrIdOffset[$systemNo] and $isrContext eq 'External' ) # find lowest external ISR ID from OS-specific Perl-module
                    {
                        $externalIsrIdOffset[$systemNo] = $threadId;
                    }

                    if( $threadId > $highestIsrIdCat2[$systemNo] and $isrCategory == 2 ) # find highest cat2 ISR ID from OS-specific Perl-module
                    {
                        $highestIsrIdCat2[$systemNo] = $threadId;
                    }

                    if( $threadId > $highestIsrIdCat1[$systemNo] and $isrCategory == 1 and $isrContext ne 'Internal' ) # find highest cat1 ISR ID from OS-specific Perl-module
                    {
                        $highestIsrIdCat1[$systemNo] = $threadId;
                    }
                }

                my $exclFromCpuLoadStr = ''; # Ensure that ExcludeFromCpuLoad is present only on the cores where this parameter is defined
                if( 'Task' eq $threadType )
                {
                    if( $osBackgroundTaskName[$systemNo] eq $threadName )
                    {
                        $exclFromCpuLoadStr = ' ExcludeFromCpuLoad="true"';
                    }
                    elsif( defined $osBackgroundTaskId[$systemNo] and ( resolveTaskOrIsrId( $osBackgroundTaskId[$systemNo], $systemNo ) eq $threadName ) )
                    {
                        $exclFromCpuLoadStr = ' ExcludeFromCpuLoad="true"';
                    }
                }

                $$stringPerSystemRef[$systemNo] .= $stringA . $exclFromCpuLoadStr . $stringB;

            }

            $taskNames{$threadId} = $threadDesc unless exists $taskNames{$threadId};

            $threadName = 'CAT1_' . $threadName if 'Internal' eq $isrContext;
            $$headerFileStringRef .= sprintf "#define %-45s (%3uu)%s\n", "T1_${threadName}_ID", $threadId, $threadComment;
        }
    }

    return;
}

######################################################################################
# Parse command line and get invocation file paths
######################################################################################

my @clFlags = ();
while( my $arg = shift )
{
    my $val = "";

    if( ($val) = $arg =~ /-(?:User)?Cfg=(.+)/ ) # -UserCfg and -Cfg
    {
        push @invocationFiles, $val;
        push @clFlags, $arg;
    }
    elsif( ($val) = $arg =~ /-OsCfg=(.*)/ )
    {
        $osCfgFile = $val;
        push @clFlags, $arg;
    }
    elsif( $arg eq "-I" )
    {
        if( $arg = shift and -d $arg )
        {
            push @includeDirs, rel2abs($arg);
            push @clFlags, "-I$arg";
        }
    }
    elsif( $arg =~ /^-I(.*)$/ )
    {
        if( -d $1 )
        {
            push @includeDirs, rel2abs($1);
            push @clFlags, $arg;
        }
    }
    elsif( ($val) = $arg =~ /-OsPm=(.*)/ )  # use appropriate OS-module
    {
        push @clFlags, $arg;
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
        elsif( $val =~ /T1_TresosAutoCoreOS/ )
        {
            require T1_TresosAutoCoreOS;
            import T1_TresosAutoCoreOS;
        }
        elsif( $val =~ /T1_TresosSafetyOs/ )
        {
            require T1_TresosSafetyOs;
            import T1_TresosSafetyOs;
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
        elsif( $val =~ /T1_Mobilgene/ )
        {
            require T1_Mobilgene;
            import T1_Mobilgene;
        }
        elsif( $val =~ /T1_dummyOS/ )
        {
            require T1_dummyOS;
            import T1_dummyOS;
        }
        elsif( $val =~ /T1_neusarOS/ )
        {
            require T1_neusarOS;
            import T1_neusarOS;
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
        elsif( $val =~ /T1_VSTAR/ )
        {
            require T1_VSTAR;
            import T1_VSTAR;
        }
        elsif( $val =~ /T1_NonOs/ )
        {
            require T1_NonOs;
            import T1_NonOs;
        }
        elsif( $val =~ /T1_FreeRTOS/ )
        {
            require T1_FreeRTOS;
            import T1_FreeRTOS;
        }
        elsif( $val =~ /T1_RenesasOS/ )
        {
            require T1_RenesasOS;
            import T1_RenesasOS;
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
    elsif( ($val) = $arg =~ /-CfgEncoding=(.*)/ )
    {
        trimStringRef( \$val );
        $cfgEncoding = $val;
    }
    elsif( ($val) = $arg =~ /-SourceFileEncoding=(.*)/ )
    {
        trimStringRef( \$val );
        $sourceFileEncoding = $val;
    }
    elsif( ($val) = $arg =~ /-SystemFileNameEncoding=(.*)/ )
    {
        trimStringRef( \$val );
        $systemFileNameEncoding = $val;
    }
    elsif( $arg =~ /-[^=]+=.*/ ) # any non-OS parameter
    {
        push @additionalCmdLineParameters, $arg;
        push @clFlags, $arg;
    }
}

foreach my $invocationFile ( map {rel2abs( $_ )} @invocationFiles )
{
    # Reset systemNo to undef which means non system-specific parameter
    undef $systemNo;

    open my $fhInvocationFile, $cfgEncoding ? "<:encoding(${cfgEncoding})" : '<', $invocationFile or die qq(Error: Could not open invocation file "${invocationFile}" for reading.\n);

    while( my $currentLine = <$fhInvocationFile> )
    {
        &ParseParam( $currentLine, $invocationFile );
    }

    close $fhInvocationFile;
}

# Process additional command line parameters after invocation files so that these can
# overwrite what has been set in an invocation file
undef $systemNo; # ensure that the command line parameters are handled as a non system-specific parameter
foreach my $additionalCmdLineParameter ( @additionalCmdLineParameters )
{
    &ParseParam( $additionalCmdLineParameter );
}

######################################################################################
# Adjust file names and convert to absolute paths
######################################################################################
foreach my $fileName (
    $projectFile,
    $configGenC,
    $configBuffC,
    $configHeader,
    $runnableHeader,
    $idHeader,
    $bidHeader,
    @inlineHeaders,
    @includeHeaders,
    $t1LibAnnotationsFile,
    @t1pSymbolIncludeFiles,
    # %t1pSymbolIncludeFilesCoreX,
    # %t1pAnnotationsFiles,
    # @@symbolFilesCoreX,
)
{
    # Skip options that are not set
    unless( $fileName )
    {
        next;
    }

    # Convert to system specific encoding if required
    if( $systemFileNameEncoding )
    {
        $fileName = encode( $systemFileNameEncoding, $fileName, sub { warn sprintf "Warning: Substituted character 'U+%04X' which cannot be represented in '${systemFileNameEncoding}' in file name with '_'\n", shift; return '_'} );
    }

    # Make file path absolute
    $fileName = rel2abs( $fileName );
}

######################################################################################
# Add symbolPrefix to dpcSymbols and retainSymbols
######################################################################################

if( '' ne $symbolPrefix )
{
    # Iterate list of array references
    foreach my $arrarRef ( \@dpcSymbols, \@retainSymbols )
    {
        # Iterate individual array elements (systems)
        foreach my $hashRef ( @$arrarRef )
        {
            # Iterate symbols
            foreach my $symbol (keys %{$hashRef})
            {
                # Prepend prefix only if not already prefixed
                unless( $symbol =~ /^\Q$symbolPrefix\E/ )
                {
                    $hashRef->{$symbolPrefix . $symbol} =
                        delete $hashRef->{$symbol};
                }
            }
        }
    }
}

######################################################################################
# Read OS configuration, process Tasks, ISRs and Runnables
######################################################################################

OsReadOsConfiguration( $osCfgFile, $symbolPrefix, @includeDirs );

my $taskRef     = OsGetSysElementReference('Task');
my $isrRef      = OsGetSysElementReference('Interrupt');
my $runnableRef = OsGetSysElementReference('Runnable');
my $symGroupRef = OsGetSysElementReference('SymbolGroup');
my $osRef       = OsGetSysElementReference('OS');


# get general OS configurations
my $genSource = OsGetValue( $osRef, 'Info', 'GenSource' );
my $genDate = OsGetValue( $osRef, 'Info', 'GenDate' );
my $nOfCores = OsGetValue( $osRef, 'Info', 'NofCores' );
my @isCoreUnused = (0) x MAX_NOF_CORES;
if( OsGetValue( $osRef, 'Info', 'UnusedCoreLookupTable' ) )    # get OS-coreID to physical CoreID mapping. -1 indicated that a core is unused.
{
    my $ref = OsGetValue( $osRef, 'Info', 'UnusedCoreLookupTable' );
    @isCoreUnused = @$ref;
}

my $osDefineStackRef = OsGetValue( $osRef, 'Info', 'defineStackRef' );
if( $osDefineStackRef )
{
    foreach my $systemNo (0..$nOfCores-1)
    {
        if( defined @$osDefineStackRef[$systemNo] and scalar @{@$osDefineStackRef[$systemNo]} )
        {
            # Append OsStack info to existing OsStack info
            push @{$defineStack[$systemNo]}, @{@$osDefineStackRef[$systemNo]};
        }
    }
}

######################################################################################
# Fill in OsStackRef with data from invocation files, only if not already set by OS
# specific Perl module
######################################################################################
assignTaskStackSecondStage( $nOfCores, \@assignTaskStack, $taskRef, $isrRef, \%allocateCat1IsrIdPrio );

######################################################################################
# Generate OsStack elements
######################################################################################
my @osStackStringPerSystem = ('') x $nOfCores;
foreach my $systemNo ( 0..$nOfCores-1 )
{
    my $osStackArray = $defineStack[$systemNo];
    if( defined $osStackArray )
    {
        my $osStacksString = '      <OsStacks>';
        foreach my $values ( @$osStackArray )
        {
            my @attributeList;
            while( my ($attrib, $value ) = each %{$values} )
            {
                push @attributeList, qq(${attrib}="${value}");
            }

            # XML order of attributes is not significant, but keep it consitent
            my $attributeString = join ' ', sort {$a cmp $b} @attributeList;

            $osStacksString .= "\n        <OsStack ${attributeString}/>";
        }
        $osStacksString .= "\n      </OsStacks>\n";

        $osStackStringPerSystem[$systemNo] = $osStacksString;
    }
}

######################################################################################
# Initialize timer settings
######################################################################################

InitTimerSettings( $nOfCores );

######################################################################################
# Execute all allocate* subs
######################################################################################

foreach my $param ( @allocateAF )
{
    allocateAF( $param );
}

foreach my $systemNo ( 'all', 0 .. $nOfCores )
{
    my $systemNoForFunctions = $systemNo eq 'all' ? undef : $systemNo;
    foreach my $param ( @{$allocateDL{$systemNo}} )
    {
        allocateDL( $param, $systemNoForFunctions );
    }

    foreach my $param ( @{$allocateUDE{$systemNo}} )
    {
        allocateUE( 'UDE', $param, $systemNoForFunctions );
    }

    foreach my $param ( @{$allocateUE{$systemNo}} )
    {
        allocateUE( 'UE', $param, $systemNoForFunctions );
    }

    foreach my $param ( @{$keyValueMapUE{$systemNo}} )
    {
         allocateUEKeyValue( $param, $systemNoForFunctions );
    }

    foreach my $param ( @{$allocateUserSW{$systemNo}} )
    {
        allocateUserSW( $param, $systemNoForFunctions );
    }

    foreach my $param ( @{$addConstraintToUserSW{$systemNo}} )
    {
        addConstraintToUserSW( $param, $systemNoForFunctions );
    }
}

######################################################################################
# Process header files to be included / inlined
######################################################################################

my $includeAllHeaders = '';

foreach my $inlineHeader ( @inlineHeaders )
{
    my $absPath = rel2abs($inlineHeader);

    # Use getFileBaseName() to optionally convert the filename to UTF-8
    $includeAllHeaders .= '#include "' . getFileBaseName( $absPath ) . "\"\n";

    $externDataAvailable = 1;
    $externData .= processHeader( $absPath, $nOfCores );
}

my $prjFilePath = File::Basename::dirname($projectFile);
$prjFilePath =~ s/\s//g;

foreach my $incFile ( @includeHeaders )
{
    my $absPath = rel2abs($incFile);
    my $relPath = resolvePathRelToProjectFile($absPath, $prjFilePath, $copyIncludeHeader);

    # Use getFileBaseName() to optionally convert the filename to UTF-8
    $includeAllHeaders .= '#include "' . getFileBaseName( $absPath ) . "\"\n";

    processHeader( $absPath, $nOfCores );

    if( $systemFileNameEncoding )
    {
        $relPath = decode( $systemFileNameEncoding, $relPath);
    }
    $includeHeader  .= "      <HeaderInclude>$relPath</HeaderInclude>\n";
}

if( $includeAllHeaders eq '' )
{
    die "Error: At least one header file needs to be inlined or included using -inlineHeader or -includeHeader.";
}

# Allocate masks for the Application Features which have been
# defined via the invocation file.
# NOTE: Currently the two approaches (inline xml and invocation file) are incompatible
#       but there is no check that not both have been used at the same time.
allocateAFMasks( );

# Allocate IDs for the delays which have been defined via the invocation file.
# NOTE: Currently the two approaches (inline xml and invocation file) are incompatible
#       but there is no check that not both have been used at the same time.
allocateDLIds( );

# Allocate masks for the User Events which have been defined via the invocation file.
# NOTE: Currently the two approaches (inline xml and invocation file) are incompatible
#       but there is no check that not both have been used at the same time.
allocateUEIds( );

# Allocate IDs for the user stopwatches which have been defined via the invocation file.
# NOTE: Currently the two approaches (inline xml and invocation file) are incompatible
#       but there is no check that not both have been used at the same time.
allocateUserSWIds( );

checkUserSWCsrns( );

# PID-'000'
# PID-'001'
# Referenced Perl Symbol
# : $osBasicSchedFrameName, $nOfCores, $allocateCat1IsrIdPrio, $taskRef, $isrRef, $runnableRef, $symGroupRef, @invocationFiles, $configHeader

createThreadXmlElementsAndDefines( $nOfCores, \@sysElems, \$t1ConfigHIds, $taskRef, $isrRef );

# Allocate ISR IDs
my @nOfTasksFromOsModule = @numberOfTasks;
for my $systemNo ( 0..$nOfCores-1 )
{
    my $lowestCat1ISRID;
    if( $additionalCat1IsrIdOffset[$systemNo]) # external ISRs do have a fixed offset. Just add the number of external ISRs in order to get the overall number of tasks
    {
        $lowestCat1ISRID = $additionalCat1IsrIdOffset[$systemNo];
    }
    else # IDs are assigned in order with scope IDs from OS-specific module
    {
        $lowestCat1ISRID = $nOfTasksFromOsModule[$systemNo];
    }

    foreach my $threadName ( sort keys %allocateCat1IsrIdPrio )
    {
        my $hashRef = $allocateCat1IsrIdPrio{$threadName};
        if( int $hashRef->{'Core'} == $systemNo )
        {
            $hashRef->{'ID'} = $lowestCat1ISRID + $nOfAdditionalCat1Isrs[$systemNo];
            $nOfAdditionalCat1Isrs[$systemNo]++;
        }
    }

    $numberOfTasks[$systemNo] = $lowestCat1ISRID + $nOfAdditionalCat1Isrs[$systemNo];
}

createThreadXmlElementsAndDefines( $nOfCores, \@extraSysElems, \$t1ConfigHIds, \%allocateCat1IsrIdPrio );

# verify task and ISR IDs and get the overall number of tasks (required by T1.cont)
for my $system ( 0..$nOfCores-1 )
{
    my $coreSuffix = '';
    my $cat1IsrsAvailable = 1;

    $coreSuffix = '_CORE' . $system;

    if( $highestIsrIdCat2[$system] == 0 )  # no cat2 ISR received from OS specific module
    {
        $highestIsrIdCat2[$system] = $nOfTasksFromOsModule[$system] - 1;  # set number of tasks -1 instead
    }
    if( $cat2IsrIdOffset[$system] == 1000) # if initial value -> no cat2 ISRs received from OS-specific module
    {
        $cat2IsrIdOffset[$system] = $nOfTasksFromOsModule[$system];  # set number of tasks instead
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

    if( $isCoreUnused[$system] eq '1' ) # this core is unused. Reduce T1.cont result buffer allocation to minimum
    {
        $numberOfTasks[$system] = 1;
        $cat1IsrIdOffset[$system] = 0;
        $cat2IsrIdOffset[$system] = 0;
        $externalIsrIdOffset[$system] = 0;
    }

    $t1ConfigHIds  .= "/* Core $system: */\n";

    $t1ConfigHIds  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_NOF_TASKS_COREXX', ( sprintf "%4s", addU( $numberOfTasks[$system]) ), $system );
    my $maxTaskPreemptions = int( 4 + $numberOfTasks[$system] / 5 );
    $maxTaskPreemptions = 20 if $maxTaskPreemptions < 20;
    $maxTaskPreemptions = $maxPreemptionDepth{$system} if exists $maxPreemptionDepth{$system}; # Allow override
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_MAX_TASK_PREEMPTIONS$coreSuffix", addU( $maxTaskPreemptions );
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_CAT1_ISR_ID_OFFSET$coreSuffix", addU( $cat1IsrIdOffset[$system] );
    $t1ConfigHIds  .= sprintf "#define %-45s (%4s)\n", "T1_CAT2_ISR_ID_OFFSET$coreSuffix", addU( $cat2IsrIdOffset[$system] );
    $t1ConfigHIds  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_EXT_ISR_ID_OFFSET_COREXX', ( sprintf "%4s", addU( $externalIsrIdOffset[$system]) ), $system );
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_CAT1_TO_TRACE_ID$coreSuffix( id_ )", "T1_CAT1_ISR_ID_OFFSET$coreSuffix + (id_)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_CAT2_TO_TRACE_ID$coreSuffix( id_ )", "T1_CAT2_ISR_ID_OFFSET$coreSuffix + (id_)";
    $t1ConfigHIds  .= sprintf "#define %-45s (%s)\n", "T1_EXT_ISR_TO_TRACE_ID$coreSuffix( id_ )", "T1_EXT_ISR_ID_OFFSET$coreSuffix + (id_)";
}

for my $system ( 0..$nOfCores-1 )
{
    # Create system elements for the user stopwatches which have been defined via the invocation file
    if( @userStopWatches )
    {
        foreach my $swRef ( sort { $a->{'name'} cmp $b->{'name'} } @{$userStopWatches[$system]} )
        {
            my $name = $swRef->{'name'};
            if( defined $name )
            {
                my $id     = $swRef->{'id'};
                my $type   = $swRef->{'type'};
                my $t1cont = $swRef->{'t1cont'};
                $extraSysElems[$system] .= qq(      <SystemElement Name="${name}" ID="${id}" Type="Stopwatch") . ( $type =~ /DA$/ ? qq( IsDataflow="true") : '' );

                my %scopeTypeLookup = (
                    SCOPE_FIFO  =>  'ReentrantFifo',
                    SCOPE_LIFO  =>  'ReentrantLifo',
                );

                if( exists $scopeTypeLookup{$type} )
                {
                    my $scopeTypeForT1p = $scopeTypeLookup{$type};
                    $extraSysElems[$system] .= qq( StopwatchType="${scopeTypeForT1p}");
                }

                if( exists $swRef->{'constraints'} )
                {
                    $extraSysElems[$system] .= ">\n";

                    foreach my $csrnRef ( @{$swRef->{'constraints'}} )
                    {
                        my $csrnType = uc $csrnRef->{'type'};
                        my $subType  = uc $csrnRef->{'subType'};
                        my $value    = $csrnRef->{'value'};
                        my $siPrefix = $csrnRef->{'siPrefix'};

                        ( $csrnType ) = $csrnType =~ /(CET|DA|GET)$/;
                        my %timingResultTypeLookup = (
                            CET => 'CoreExecTime', # T1-HOST-SW will write CoreExecTime instead of StopwatchCoreTime into the T1P
                            DA  => 'StopwatchDataAge',
                            GET => 'StopwatchGrossTime',
                        );
                        my $timingResultType = $timingResultTypeLookup{$csrnType};

                        my %subTypeLookup = (
                            MAX => 'Max',
                            MIN => 'Min',
                        );
                        $subType = $subTypeLookup{$subType};

                        my %multiplier = (
                            ''  => 1000.0 * 1000.0 * 1000.0,
                            m   => 1000.0 * 1000.0,
                            u   => 1000.0,
                            n   => 1.0,
                        );
                        $value *= $multiplier{$siPrefix};

                        $extraSysElems[$system] .= <<"EOT";
        <Constraint Type="${timingResultType}" SubType="${subType}">
          <Value>${value}</Value>
        </Constraint>
EOT
                    }

                    $extraSysElems[$system] .= "      </SystemElement>\n";
                }
                else
                {
                    $extraSysElems[$system] .= " />\n";
                }
            }
        }
    }

    # Create system elements for the User Events which have been defined via the invocation file
    if( @userEvents )
    {
        foreach my $ueRef ( @{$userEvents[$system]} )
        {
            my $name  = $ueRef->{'name'};
            my $color = $ueRef->{'color'};
            my $id    = $ueRef->{'id'};

            my $closeElement1 = ' />';
            my $closeElement2 = '';
            my $infos = '';
            if( exists $ueRef->{'key'} )
            {
                foreach my $key ( sort keys %{$ueRef->{'key'}} )
                {
                    $infos .= "\n        <Info InfoStr=\"$ueRef->{'key'}->{$key}\" Index=\"$key\" />";
                }
                $closeElement1 = '>';
                $closeElement2 = "\n      </SystemElement>";
            }
            if( defined $color )
            {
                $color = "\n        <Visualization Color=\"$color\" />";
                $closeElement1 = '>';
                $closeElement2 = "\n      </SystemElement>";
            }
            else
            {
                $color = '';
            }
            $extraSysElems[$system] .= "      <SystemElement Name=\"$name\" ID=\"$id\" Type=\"UserEvent\"$closeElement1$infos$color$closeElement2\n";
        }
    }

    # Create AppFeature element for the application features which have been defined via the invocation file
    # They must appear after the EventChainSystemElement to respect the fix order required by the T1-HOST-SW
    if( @applicationFeatures )
    {
        foreach my $afRef ( sort { $a->{'mask'} <=> $b->{'mask'} } @applicationFeatures )
        {
            my $name = $afRef->{'name'};
            my $mask = $afRef->{'mask'}; # T1-HOST-SW will write it as a decimal value, not as a hex string
            $appFeatureElems[$system] .= qq(      <AppFeature Name="${name}">\n);
            $appFeatureElems[$system] .= qq(        <Mask>${mask}</Mask>\n);
            $appFeatureElems[$system] .= qq(      </AppFeature>\n);
        }
    }

    # Create system elements for the delays which have been defined via the invocation file
    if( @delays )
    {
        foreach my $dlRef ( @{$delays[$system]} )
        {
            my $name  = $dlRef->{'name'};
            my $id    = $dlRef->{'id'};

            $delayElems[$system] .= qq(      <Delay Name="${name}" Id="${id}" /\>\n);
        }
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

# Optionally create header file for redefinition of start/stop macros and add corresponding system elements to the T1 project file
if( ref $runnableRef and $runnableHeader ne "" )
{
    foreach my $runnable ( sort runnablesByIdThenName keys %{$runnableRef} )
    {
        my $runnableName      = OsGetValue( $runnableRef, $runnable,  'Name' );
        my $runnableId        = OsGetValue( $runnableRef, $runnable,  'ID' );
        my $runnableCore      = OsGetValue( $runnableRef, $runnable,  'Core' );
        my $runnableComment   = OsGetValue( $runnableRef, $runnable,  'Comment' );
        my $runnableType      = OsGetValue( $runnableRef, $runnable,  'Type' );

        my $runnableDesc = $runnableName;
        if( $runnableComment ne "" )
        {
            $runnableDesc .= ": $runnableComment";
            $runnableComment = " /* $runnableComment */";
        }
        if( $runnableCore eq "all" ) # If core is not identified add runnable to all cores in the T1 project file
        {
            for my $counter (0 .. ($nOfCores-1))
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

# append ISR wrapper macros from OS-Module
$t1IsrWrapper .= OsGetIsrWrapper( );

#  Perform OS instrumentation
OsPerformInstrumentation( );

######################################################################################
# Create T1 project file
######################################################################################

my $t1pDoesNotExist = 0;
my @reportConfigFromPrevT1p = ('') x MAX_NOF_CORES;
my $projectLevelStackQueryConfigurationFromPrevT1p;
my @stackQueryConfigurationFromPrevT1p = (undef) x MAX_NOF_CORES;
my %symGroupsFromPrevT1p = ();
my %tasksIsrsNameByIdFromPrevT1p = ();
my %symGroupsFromOsModule = ();
my %evtChainsFromPrevT1p = ();
my %annotationFilesFromPrevT1p = ();

if( $generateBuildId eq "true" )
{
    $buildId = int rand 4294967295;
    die "Build ID out of uint32_t range" unless $buildId <= 4294967295;
}

my $t1BidHDefs = sprintf "#define %-45s %s\n", "T1_BUILD_ID", $buildId;


if( -e $projectFile and $readPreviousT1p eq 'true' ) # check if project file exists and if user-configured parts shall be copied to new t1p
{
    # extract user-configurable information from previous t1p:
    my $sysIdx = -1;
    my $extractReportCfg = 0;
    my $extractSymGroup = 0;
    my $extractEvtChain = 0;
    my $extractDpc = 0;
    my $extractStackQueryConfiguration = 0;
    my $curSymGroupName = "";
    my $curEvtChainName = "";
    my $insideSystem = 0;

    open my $fhPrevT1P, '<:encoding(utf-8)', $projectFile or die qq(Error: Unable to read "${projectFile}"\n);
    while( my $curLine = <$fhPrevT1P> )
    {
        if( $curLine =~ /<System Name/ )
        {
            $insideSystem = 1;
            $sysIdx ++;
        }
        elsif( $insideSystem )
        {
            # Inside <system>...</system>
            # extract Tasks and Interrupts and their IDs in order to check EventChains for consistency before adding EventChains to newly generated t1p:
            if( $curLine =~ /<SystemElement Name=\"(.*)\" Priority=\"(.*)\" ID=\"(.*)\" Type/ )
            {
                $tasksIsrsNameByIdFromPrevT1p{$3} = $1;
            }
            # extract Symbol Groups:
            elsif( $curLine =~ /<SymbolGroup Name=\"(.*)\" IsCode/ )
            {
                $extractSymGroup = 1;
                $curSymGroupName = $1 . '_' . $sysIdx;
            }
            # extract report configuration:
            elsif( $curLine =~ /<ReportConfiguration\>/ )
            {
                $extractReportCfg = 1;
            }
            # preserve Event Chains:
            elsif( $curLine =~ /<EventChainSystemElement Name=\"(.*)\" ID=\"([0-9]+)\"/ )
            {
                $extractEvtChain = 1;
                $curEvtChainName = $1 . '_' . $sysIdx; # append system ID in order to re-assign EventChains to systems
            }
            # extract Annotation Files:
            elsif( $curLine =~ /\<AnnotationInclude\>(.*)\<\/AnnotationInclude\>/ )
            {
                $annotationFilesFromPrevT1p{$sysIdx}{$1} = 1;
            }
            # extract DPC Configuration
            elsif( $curLine =~ /<Extensions\>/ )
            {
                $extractDpc = 1;
                # Continue parsing with next line
                $curLine = <$fhPrevT1P>;
            }
            # Extract system level StackQueryConfiguration
            elsif( $curLine =~ /<StackQueryConfiguration\s*>/ )
            {
                $extractStackQueryConfiguration = 1;
                # Continue parsing with next line
                $curLine = <$fhPrevT1P>;
            }

            if( $extractSymGroup )
            {
                $symGroupsFromPrevT1p{$curSymGroupName} .= $curLine;
                $extractSymGroup = 0 if $curLine =~ /<\/SymbolGroup>/;
            }
            elsif( $extractReportCfg )
            {
                $reportConfigFromPrevT1p[$sysIdx] .= $curLine;
                $extractReportCfg = 0 if $curLine =~ /<\/ReportConfiguration>/;
            }
            elsif( $extractEvtChain )
            {
                if( $curLine =~ /SystemElementID=\"([0-9]+)\" SystemElementType=\"(.*)\" ID=\"([0-9]+)\"/ )
                {
                    if( $2 eq "Task" || $2 eq "Interrupt")  # only Interrupts and Tasks can be verified
                    {
                        #replace Task and Interrupt IDs by their names and add pattern for identification in t1p generation process:
                        my $replacedId = '$$$' . $tasksIsrsNameByIdFromPrevT1p{$1};
                        $curLine =~ s/ SystemElementID=\"([0-9]+)\"/ SystemElementID=\"$replacedId\"/;
                    }
                }
                $evtChainsFromPrevT1p{$curEvtChainName} .= $curLine;
                $extractEvtChain = 0 if $curLine =~ /\<\/EventChainSystemElement\>/;
            }
            elsif ( $extractDpc )
            {
                if( $curLine =~ /<SymbolExtension\s+Name="(.*)"\s+DpcEligible="(.*)"\s*\/>/ )
                {
                    $dpcSymbols[$sysIdx]{$1} = $2;
                }
                else
                {
                    $extractDpc = 0;
                }
            }
            elsif( $extractStackQueryConfiguration )
            {
                if( $curLine =~ /<\/StackQueryConfiguration/ )
                {
                    $extractStackQueryConfiguration = 0;
                }
                else
                {
                    $stackQueryConfigurationFromPrevT1p[$sysIdx] .= $curLine;
                }
            }
            elsif( $curLine =~ /<\/System\s*>/ )
            {
                $insideSystem = 0;
            }
        }
        else
        {
            # Outside <system>...</system>
            # Extract project level StackQueryConfiguration
            if( $curLine =~ /<StackQueryConfiguration\s*>/ )
            {
                $extractStackQueryConfiguration = 1;
            }
            elsif( $extractStackQueryConfiguration )
            {
                if( $curLine =~ /<\/StackQueryConfiguration\s*>/ )
                {
                    $extractStackQueryConfiguration = 0;
                }
                else
                {
                    $projectLevelStackQueryConfigurationFromPrevT1p .= $curLine;
                }
            }
        }
    }
    close $fhPrevT1P;
}
else # project file does not exist
{
    $t1pDoesNotExist = 1;
}

#project specific part:
$t1p .="<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
$t1p .="<T1 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" Version=\"2.0\">\n";

$t1p .= "  <Project Name=\"$projectName\" ";
if( $syncTimerTickDurationNs )
{
    my $syncTimerTickDurationNsDecimal = eval "$syncTimerTickDurationNs;";
    $t1p .= "MainTickDuration=\"$syncTimerTickDurationNsDecimal\" ";
}
$t1p .= "SyncTimeBitLength=\"32\" "; # the T1-HOST-SW sees only the extrapolated 32 bits
$t1p .= 'T1targetVersion="2"';
$t1p .= " EnableStreamingUI=\"$enableStreaming\"" if '' ne $enableStreaming;
my $projectFileNoDotDigit = $projectFile;
$projectFileNoDotDigit =~ s/.[0-9]$//;
$t1p .= ">\n    <Comment>Project file \"$projectFileNoDotDigit\" auto-generated from $genSource on $genDate</Comment>\n";

if( $t1LibAnnotationsFile ne '' )
{
    my $annotationBaseName = File::Basename::basename( $t1LibAnnotationsFile, '.t1a' );
    # Use getFileBaseName() to optionally convert the filename to UTF-8
    $annotationBaseName = getFileBaseName( $annotationBaseName );

    foreach my $sysNo (0 .. ($nOfCores-1))
    {
        $t1pAnnotationsFiles{"$annotationBaseName\_Core$sysNo.t1a"}{$sysNo} =  1;
    }
}

#system specific part:
if( %t1pAnnotationsFiles )# take care of the possible default t1a added in the invocation files for each cores
{
    my $annotationBaseName = File::Basename::basename( $projectFileNoDotDigit, '.t1p' );

    # Use getFileBaseName() to optionally convert the filename to UTF-8
    $annotationBaseName = getFileBaseName( $annotationBaseName );

    my @matchedT1A = ();

    foreach my $elem (keys %t1pAnnotationsFiles)
    {
        if( $elem =~ /.*${annotationBaseName}\_Core[\d+].t1a/ )
        {
            push @matchedT1A, $elem;
            warn "Warning: default annotation file $elem in invocation file\n";
        }
    }
    delete @t1pAnnotationsFiles{@matchedT1A};
}

# With less than 32 bits, "missing" upper bits of sync timer are computed by
# T1_Handler. This defines a maximum T1_Handler period, assuming no jitter. With
# jitter, the real possible period will be smaller but the jitter is unknown so all
# we can do is check without jitter, which is certainly an upper bound.
my $maxT1HandlerPeriodMs = eval "2 ** ($syncTimeBitLength) * ($syncTimerTickDurationNs) / 1000 / 1000;";

#process each system and create corresponding system elements
for my $sysNo (0 .. ($nOfCores-1))
{
    if( not $isCoreUnused[$sysNo] )
    {
        my $measOvhdHalf = $t1ScopeOverheadNs[$sysNo] /2;
        my $storeTimInfoStr = '';
        my $flexAnaCapStr = '';
        my $bsfSysElemType = '';
        my $endiannessAgnosticComSetupStr = '';
        if( $storeTimingInformation eq 'true' )     { $storeTimInfoStr = ' StoreTimingInformation="true"'; }
        if( $flexAnalysisCapacity[$sysNo] != 0 )    { $flexAnaCapStr = "T1flexAnalysisCapacity=\"$flexAnalysisCapacity[$sysNo]\""; }
        if( $endiannessAgnosticComSetup eq 'true' ) { $endiannessAgnosticComSetupStr = ' EndiannessAgnosticComSetup="true"'; }

        my $tickDurationNsDecimal = eval "$tickDurationNs[$sysNo];";
        my $staticRunnableConfig = '';
        $staticRunnableConfig = " StaticRunnableID=\"$staticRunnableID\"" if '' ne $staticRunnableID;
        my $sid = $core0sid + $sysNo;
        my $effectiveRawTimerBitLength = $rawTimerBitLength[$sysNo];
        $effectiveRawTimerBitLength = $traceTimeStampBitLength if $traceTimeStampBitLength < $effectiveRawTimerBitLength;
        my $maxAbsTime = 2 ** $effectiveRawTimerBitLength - 1;
        32 <= $syncTimeBitLength or $t1HandlerPeriodMs[$sysNo] < $maxT1HandlerPeriodMs or die "Error: Core ${sysNo} T1_Handler period is too long for synchronization timer with only ${syncTimeBitLength} bits\n";
        $t1p  .= "    <System Name=\"$systemName[$sysNo]\" TickDuration=\"$tickDurationNsDecimal\" MaxAbsTime=\"$maxAbsTime\" KernelPriority=\"255\" MinPreempPrio=\"1\" SystemType=\"$systemType[$sysNo]\" T1HandlerPeriod=\"$t1HandlerPeriodMs[$sysNo]\"$storeTimInfoStr$endiannessAgnosticComSetupStr SID=\"$sid\" BID=\"$buildId\" LicInfo1=\"$licInfo1\" LicInfo2=\"$licInfo2\"$staticRunnableConfig TraceBufferSize=\"$traceBufferEntries[$sysNo]\" >\n";
        $t1p  .= "      <Comment>$systemComment[$sysNo]</Comment>\n";
        if( $cortex eq 'true' or $bigEndian eq 'true' or $targetType[$sysNo] ne '' )
        {
            $t1p .= '      <TargetSpecifics';
            $t1p .= " Target=\"$targetType[$sysNo]\"" if $targetType[$sysNo] ne '';
            $t1p .= ' BigEndian="true"' if $bigEndian eq 'true';
            $t1p .= ' NeedsUniqueSuccessorAddress="true"' if $cortex eq 'true';
            $t1p .= " />\n";
        }
        $t1p .= "      <TargetAnalysis $flexAnaCapStr />\n" if $flexAnalysisCapacity[$sysNo];
        if( $traceTimerIsSyncTimer[$sysNo] eq 'true' )
        {
            $t1p .= "      <TraceMergeAttributes TraceTimerIsMainTimer=\"$traceTimerIsSyncTimer[$sysNo]\" />\n";
        }

        # Check if osBasicSchedFrameId parameter is set for current system
        if( $osBasicSchedFrameId[$sysNo] )
        {
            # Check if this is a hex number
            if( $osBasicSchedFrameId[$sysNo] =~ /^0[xX]((?i)[0-9a-f]+)$/ )
            {
                $osBasicSchedFrameId[$sysNo] = hex $1;
            }
            # Check if it is a decimal number
            elsif( $osBasicSchedFrameId[$sysNo] =~ /^(\d+)$/ )
            {
                $osBasicSchedFrameId[$sysNo] = int $1;
            }
            else
            {
                die sprintf "osBasicSchedFrameId is set, but neither a hex nor a decimal number (%s) for system %d!\n", $osBasicSchedFrameId[$sysNo], $sysNo;
            }
        }

        if( $osBasicSchedFrameEventId[$sysNo] eq 'T1_USEREVENT' )
        {
            # BSF Type is a T1_USEREVENT

            die "osBasicSchedFrameEventId is T1_USEREVENT but osBasicSchedFrameId is missing for system $sysNo!\n"
                unless defined $osBasicSchedFrameId[$sysNo];

            # Check range of User Event Id
            die sprintf "osBasicSchedFrameId (%d) is out of range (32..63) for system %d!\n", $osBasicSchedFrameId[$sysNo], $sysNo
                unless 32 <= $osBasicSchedFrameId[$sysNo] and $osBasicSchedFrameId[$sysNo] <= 63;

            $bsfSysElemType = 'UserEvent'; # not required for UserEvents
        }
        else
        {
            # BSF Type is not a T1_USEREVENT

            if( $osBasicSchedFrameId[$sysNo] )
            {
                # In case the ID of a Task or Interrupt is given resolve the ID to a Name
                $osBasicSchedFrameName[$sysNo] = resolveTaskOrIsrId($osBasicSchedFrameId[$sysNo], $sysNo);

                if( not $osBasicSchedFrameName[$sysNo] )
                {
                    die "Could not resolve task/ISR ID $osBasicSchedFrameId[$sysNo] !\n";
                }
            }
            elsif( $osBasicSchedFrameName[$sysNo] )
            {
                # In case the Name of a Task or Interrupt is given resolve the Name to an ID
                $osBasicSchedFrameId[$sysNo] = resolveTaskOrIsrName( $osBasicSchedFrameName[$sysNo], $sysNo );

                if( not defined $osBasicSchedFrameId[$sysNo] )
                {
                    die "Could not resolve task/ISR name $osBasicSchedFrameName[$sysNo] !\n";
                }
            }

            # By now the Task/ISR name should be resolved or BSF is not defined at all
            if( defined $osBasicSchedFrameName[$sysNo] )
            {
                if( ref $isrRef and OsGetValue( $isrRef, $osBasicSchedFrameName[$sysNo], 'Name' ) )
                {
                    # If this returns a value != 0 type is Interrupt, however we can't test for != 0 because if type is Interrupt it will return the name which is a string and not a number
                    $bsfSysElemType = 'Interrupt';
                }
                else
                {
                    # Type is Task
                    $bsfSysElemType = 'Task';
                }
            }
        }

        if( $bsfSysElemType ne '' )
        {
            $t1p .= "      <BasicSchedulingFrameEvent Type=\"$osBasicSchedFrameEventId[$sysNo]\" SystemElementID=\"$osBasicSchedFrameId[$sysNo]\" SystemElementType=\"$bsfSysElemType\" ID=\"4294967295\" />\n";
        }
        else
        {
            print "Warning: No Basic Scheduling Frame Name or Id configured for System $sysNo !\n";
        }

        $t1p .= $includeHeader if $includeHeader;
        $t1p .= $osStackStringPerSystem[$sysNo] if $osStackStringPerSystem[$sysNo] and isT1HostSwVersionAllowed( $minT1HostSwVersion, '3.4.0' );
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
            my $evtChainSysNo    = substr $evtChainName, ( length $evtChainName ) - 1, 1; # get system number of current Event Chain
            my $evtChainOrigName = substr $evtChainName, 0, ( length $evtChainName ) - 2;

            if( $evtChainSysNo == $sysNo ) # is system number of Event Chain equal to current sysNo?
            {
                if( $evtChainsFromPrevT1p{$evtChainName} =~ /SystemElementID=\"(.*)\" SystemElementType=\"(.*)\" ID=\"([0-9]+)\"/ )
                {
                    my $discardEvtChain = 0;
                    my $newEvtChain = "";
                    my @evtChainEntry = split /\n+/, $evtChainsFromPrevT1p{$evtChainName}; # buffer current Event Chain in array
                    my $idx = 0;

                    foreach my $line ( @evtChainEntry )
                    {
                        if( $line =~ /\"\$\$\$(.*)\" S(.*)/ ) # check for pattern indicating Task/Interrupt name from previous t1p
                        {
                            my $newTaskId = undef;
                            $newTaskId = resolveTaskOrIsrName( $1, $sysNo ); # try to resolve ID of Task/Interrupt by name
                            if( defined $newTaskId ) # check if Task/Interrupt name still exists
                            {
                                $line =~ s/\"\$\$\$(.*)\" S(.*)/\"$newTaskId\" S$2/; # replace pattern and Task/Interrupt name by actual ID
                            }
                            else # Task/Interrupt name could not be resolved and thus does not exist any longer in the new configuration
                            {
                                $discardEvtChain = 1;
                                print "could not resolve Task name $1 from previous configuration. Event Chain $evtChainOrigName will be discarded!\n";
                            }
                        }
                        $newEvtChain .= $line . "\n";
                        $idx ++;
                    }
                    if( $discardEvtChain == 0)
                    {
                        $t1p  .= $newEvtChain;
                    }
                }
            }
        }

        if( $appFeatureElems[$sysNo] )
        {
            $t1p .= $appFeatureElems[$sysNo];
        }

        if( $delayElems[$sysNo] )
        {
            $t1p .= $delayElems[$sysNo];
        }

        # global symbol files:
        $t1p .= "      <Symbols>\n";
        foreach my $symbolFile ( @symbolFiles )
        {
            my $symFile = getNewestFileMatchingWildcard($symbolFile);
            $symFile = resolvePathRelToProjectFile( rel2abs($symbolFile), $prjFilePath, 'false' );
            $t1p .= "        <SymbolFilePath>$symFile</SymbolFilePath>\n";
        }

        # core-specific symbol files:
        foreach my $symbolFileOnCoreX ( @{$symbolFilesCoreX[$sysNo]} )
        {
            if( defined $symbolFileOnCoreX )
            {
                my $symFile = resolvePathRelToProjectFile( rel2abs($symbolFileOnCoreX), $prjFilePath, 'false' );
                $t1p .= "        <SymbolFilePath>$symFile</SymbolFilePath>\n";
            }
        }

        if( scalar keys %{$retainSymbols[$sysNo]} )
        {
            # symbols to retain (inhibit filter)
            my $maxInclusionCount = '';
            $maxInclusionCount = qq( MaxInclusionCount="${retainMax[$sysNo]}") unless 0 == $retainMax[$sysNo]; # The T1-HOST-SW will use its default value of 4,294,967,295 if attribute is omitted
            $t1p .= qq(        <SpecialSymbolsInclusion$maxInclusionCount RegExIgnoreCase="${retainIgnoreCase[$sysNo]}">\n);
            foreach my $retainSymbol (sort keys %{$retainSymbols[$sysNo]})
            {
                $t1p .= "          <RegExPattern>${retainSymbol}</RegExPattern>\n";
            }
            $t1p .= "        </SpecialSymbolsInclusion>\n";
        }

        if( %t1pAnnotationsFiles or $annotationFilesFromPrevT1p{$sysNo} )# take care of the default t1a if some t1a are given or if it was in the previous t1p
        {
            my $annotationBaseName = File::Basename::basename( $projectFileNoDotDigit, '.t1p' );
            $t1p  .= "        <AnnotationInclude>$annotationBaseName\_Core$sysNo.t1a</AnnotationInclude>\n";
            if( exists $annotationFilesFromPrevT1p{$sysNo}{"${annotationBaseName}_Core$sysNo.t1a"})# remove from saved file
            {
                delete $annotationFilesFromPrevT1p{$sysNo}{"${annotationBaseName}_Core$sysNo.t1a"};
            }
            print "default annotation file added $annotationBaseName\_Core$sysNo.t1a\n" if $debug;
        }

        if( %t1pAnnotationsFiles )# if annotations files given
        {
            foreach my $t1pAnnotationsFile ( sort keys %t1pAnnotationsFiles )
            {
                # include only global and for this system
                if( exists $t1pAnnotationsFiles{$t1pAnnotationsFile}{'global'} or exists $t1pAnnotationsFiles{$t1pAnnotationsFile}{$sysNo} )
                {
                    my $t1pAnnotationsFileResolved = resolvePathRelToProjectFile( rel2abs($t1pAnnotationsFile), $prjFilePath, 'false');
                    my $t1aName = ( split /\\/, $t1pAnnotationsFileResolved )[-1];
                    # check on name. If t1a present in last t1p, use the path from invocation files
                    foreach my $savedT1a ( keys %{ $annotationFilesFromPrevT1p{$sysNo} } ) {
                        # if t1a present, put the value at 0 to not use it again
                        if( $t1aName eq ( split /\\/, $savedT1a )[-1] )
                        {
                            $annotationFilesFromPrevT1p{$sysNo}{$savedT1a} = 0;
                            last;
                        }
                    }
                    $t1p  .= "        <AnnotationInclude>$t1pAnnotationsFileResolved</AnnotationInclude>\n";
                    print "annotation file added $t1pAnnotationsFileResolved\n" if $debug;
                }
            }
        }
        if( $annotationFilesFromPrevT1p{$sysNo} )# if saved t1a from previous t1p
        {
            foreach my $savedT1a ( sort keys %{ $annotationFilesFromPrevT1p{$sysNo} } )
            {
                # add annotation files which were not given in the invocation files
                if( $annotationFilesFromPrevT1p{$sysNo}{$savedT1a} != 0 )
                {
                    $t1p  .= "        <AnnotationInclude>$savedT1a</AnnotationInclude>\n";
                    print "saved annotation file added $savedT1a\n" if $debug;
                }
            }
        }

        if( @t1pSymbolIncludeFiles  )
        {
            foreach my $t1pSymbolIncludeFile ( @t1pSymbolIncludeFiles )
            {
                my $t1pSymbolInclude = resolvePathRelToProjectFile( rel2abs($t1pSymbolIncludeFile), $prjFilePath, 'false');
                $t1p  .= "        <Include>$t1pSymbolInclude</Include>\n";
            }
        }

        # symbol part - core-specific includes:
        if( %t1pSymbolIncludeFilesCoreX )
        {
            foreach my $t1pSymbolInclude ( sort keys %t1pSymbolIncludeFilesCoreX )
            {
                # does this include apply to the current system?
                if( $t1pSymbolIncludeFilesCoreX{$t1pSymbolInclude} == $sysNo )
                {
                    my $t1pSymbolInclude = resolvePathRelToProjectFile( rel2abs($t1pSymbolInclude), $prjFilePath, 'false');
                    $t1p  .= "        <Include>$t1pSymbolInclude</Include>\n";
                }
            }
        }

        # symbol groups from OS-module
        if( ref $symGroupRef )
        {
            foreach my $symGroup ( sort { OsGetValue( $symGroupRef, $a, 'Name' ) cmp OsGetValue( $symGroupRef, $b, 'Name' ) } keys %{$symGroupRef} )
            {
                my $symGroupName        = OsGetValue( $symGroupRef, $symGroup,  'Name' );
                my $symGroupIsCode      = OsGetValue( $symGroupRef, $symGroup,  'IsCode' );
                my $symGroupDuration    = OsGetValue( $symGroupRef, $symGroup,  'MeasureDuration' );
                my $symGroupIntervalCnt = OsGetValue( $symGroupRef, $symGroup,  'FocusIntervalCount' );
                my $symGroupCore        = OsGetValue( $symGroupRef, $symGroup,  'Core' );
                my $symGroupElementRef  = OsGetValue( $symGroupRef, $symGroup,  'SymbolGroupElemRef');

                if( $symGroupCore eq "all" || $symGroupCore == $sysNo )
                {
                    my $catName = $symGroupName . '_' . $sysNo;
                    $symGroupsFromOsModule{ $catName } = $symGroupName;

                    $t1p .= "        <SymbolGroup Name=\"$symGroupName\" IsCode=\"$symGroupIsCode\" MeasureDuration=\"$symGroupDuration\" FocusIntervalCount=\"$symGroupIntervalCnt\">\n";
                    foreach my $symbol ( @$symGroupElementRef )
                    {
                        $t1p .= "          <Symbol>${symbol}</Symbol>\n";
                    }
                    $t1p .= "        </SymbolGroup>\n";

                }
            }
        }

        # then append all user-configured Symbol Groups:
        foreach my $userSymbGroupName ( sort keys %symGroupsFromPrevT1p ) # get all Symbol Groups from previous t1p
        {
            my $symGroupSysNo = substr $userSymbGroupName, ( length $userSymbGroupName ) - 1, 1; # get system number of current Symbol Group

            if( $symGroupSysNo == $sysNo ) # is system number of user-defined Symbol Group equal current sysNo?
            {
                if( not exists $symGroupsFromOsModule{$userSymbGroupName} ) # check if Symbol Group has already been added by OS-module
                {
                    $t1p .= $symGroupsFromPrevT1p{$userSymbGroupName}; # add Symbol Group if not yet present
                }
            }
        }

        # then append DPC symbol information:
        $t1p    .= "        <Extensions>\n";
        foreach my $dpcSymbol (sort keys %{$dpcSymbols[$sysNo]})
        {
            $t1p .= "          <SymbolExtension Name=\"$dpcSymbol\" DpcEligible=\"$dpcSymbols[$sysNo]{$dpcSymbol}\" />\n";
        }
        $t1p    .= "        </Extensions>\n";

        $t1p  .= "      </Symbols>\n";

        # measure overhead part
        $t1p  .= "      <MeasureOverheads Extended=\"true\">\n";
        $t1p  .= "        <MainMeasureOverhead>\n";
        $t1p  .= "          <T1>$measOvhdHalf</T1>\n";
        $t1p  .= "          <T2>$measOvhdHalf</T2>\n";
        $t1p  .= "        </MainMeasureOverhead>\n";
        $t1p  .= "        <T1flexMeasureOverhead>\n";
        $t1p  .= "          <T1>$t1FlexOverheadNs[$sysNo]</T1>\n";
        $t1p  .= "        </T1flexMeasureOverhead>\n";
        $t1p  .= "      </MeasureOverheads>\n";
        # Report configuration part:

        if( $t1pDoesNotExist ) # Check if t1p does already exist: Only add the report configuration the first time the t1p is generated! Otherwise retain the user-configured settings!
        {
            $t1p  .= "      <ReportConfiguration>\n";
            $t1p  .= "        <CsvConfig TimeBase=\"formatted\">\n";
            $t1p  .= "          <SelectedTimingInformation>\n";
            $t1p  .= "            <TimingInformation Type=\"CpuLoad\" SubType=\"Max\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CpuLoad\" SubType=\"Min\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CpuLoad\" SubType=\"Average\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CoreExecTime\" SubType=\"Max\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CoreExecTime\" SubType=\"Min\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CoreExecTime\" SubType=\"Average\" />\n";
            $t1p  .= "            <TimingInformation Type=\"DeltaTime\" SubType=\"Min\" />\n";
            $t1p  .= "          </SelectedTimingInformation>\n";
            $t1p  .= "        </CsvConfig>\n";
            $t1p  .= "        <HtmlConfig>\n";
            $t1p  .= "          <SelectedTimingInformation>\n";
            $t1p  .= "            <TimingInformation Type=\"CpuLoad\" SubType=\"Max\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CpuLoad\" SubType=\"Min\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CpuLoad\" SubType=\"Average\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CoreExecTime\" SubType=\"Max\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CoreExecTime\" SubType=\"Min\" />\n";
            $t1p  .= "            <TimingInformation Type=\"CoreExecTime\" SubType=\"Average\" />\n";
            $t1p  .= "            <TimingInformation Type=\"DeltaTime\" SubType=\"Min\" />\n";
            $t1p  .= "            <TimingInformation Type=\"DeltaTime\" SubType=\"Average\" />\n";
            $t1p  .= "          </SelectedTimingInformation>\n";
            $t1p  .= "        </HtmlConfig>\n";
            $t1p  .= "      </ReportConfiguration>\n";
        }
        else
        {
            $t1p  .= $reportConfigFromPrevT1p[$sysNo];
        }

        if( $stackQueryConfigurationFromPrevT1p[$sysNo] )
        {
            $t1p .= "      <StackQueryConfiguration>\n";
            $t1p .= $stackQueryConfigurationFromPrevT1p[$sysNo];
            $t1p .= "      </StackQueryConfiguration>\n";
        }
        else
        {
            $t1p .= "      <StackQueryConfiguration />\n";
        }

        if( $externDataAvailable )
        {
            $t1p  .= "    <ExternalData>\n";
            $t1p  .= "       <HeaderContent><![CDATA[\n";
            $t1p  .= "$externData\n";
            $t1p  .= "       ]]></HeaderContent>\n";
            $t1p  .= "     </ExternalData>\n";
        }

        # Continue processing CommunicationConfig inside System because CommunicationConfigList is not supported by T1-HOST-SW V2
        my $conSysNo                = 0; # if useSameConnectionForAllSystems is declared false in *.inv the settings at index 0 are used for all systems
        if( $useSameConnectionForAllSystems eq 'false' )
        {
            $conSysNo = $sysNo;
        }
        my $targetId                = int ($core0sid + $sysNo) % 32;
        my $intCanRxId              = hex $canRxID[$conSysNo];
        my $intCanTxId              = hex $canTxID[$conSysNo];
        my $intDiagSourceAddr       = hex $diagSourceAddr[$conSysNo];
        my $intDiagTargetAddr       = hex $diagTargetAddr[$conSysNo];
        my $intDiagT1Identifier     = hex $diagT1Identifier[$conSysNo];
        my $intDiagLocalIdentifier  = hex $diagLocalIdentifier[$conSysNo];
        my $intDiagCustomSessionId  = hex $diagCustomSessionId[$conSysNo];

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
            if( 'true' eq $ethUseIpv6[$conSysNo] )
            {
                if( defined $ethEcuIP[$conSysNo] )
                {
                    # Perform basic check on IPv6 address format
                    # Min length is 2 (::)
                    # Max length is 39 (8*4 + 7, 0000:0000:0000:0000:0000:0000:0000:0000)
                    unless( $ethEcuIP[$conSysNo] =~ /^[0-9a-fA-F:]{2,39}$/ )
                    {
                        warn qq(Warning: Invalid IPv6 address "${ethEcuIP[$conSysNo]}".\n);
                    }
                }
                else
                {
                    # Set to default IPv6 address, see https://en.wikipedia.org/wiki/0.0.0.0
                    $ethEcuIP[$conSysNo] = '::';
                }
            }
            else # assume false (IPv4)
            {
                if( defined $ethEcuIP[$conSysNo] )
                {
                    # Perform basic check on IPv4 address format
                    unless( $ethEcuIP[$conSysNo] =~ /^\d{1,3}[.]\d{1,3}[.]\d{1,3}[.]\d{1,3}$/ )
                    {
                        warn qq(Warning: Invalid IPv4 address "${ethEcuIP[$conSysNo]}".\n);
                    }
                }
                else
                {
                    # Set to default IPv4 address, see https://en.wikipedia.org/wiki/0.0.0.0
                    $ethEcuIP[$conSysNo] = '0.0.0.0';
                }
            }
            $t1p  .= "              <IpAddress>$ethEcuIP[$conSysNo]</IpAddress>\n";
            # only specify the tag if the value is really set to a sensible value
            if( defined $ethEcuDNSHostName[$conSysNo] )
            {
                # Perform very basic check on DNS name (no space and length)
                unless( $ethEcuDNSHostName[$conSysNo] =~ /^\S{1,255}$/ )
                {
                    warn qq(Warning: Invalid DNS name "${ethEcuDNSHostName[$conSysNo]}".\n);
                }
                $t1p  .= "              <EcuDnsHostName>$ethEcuDNSHostName[$conSysNo]</EcuDnsHostName>\n";
            }
            $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
            $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
            if( $ethUseUdp[$conSysNo] eq 'true' )
            {
                ($t1p  .= "              <UseUdp>$ethUseUdp[$conSysNo]</UseUdp>\n");
            }
            # Append _V6 for IPv6
            my $rxChannelString = $rxChannel[$conSysNo] . ( ( 'true' eq $ethUseIpv6[$conSysNo] ) ? '_V6' : '' );
            $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>Ethernet</Name>\n";
            $t1p  .= "            <BusType>$rxChannelString</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>RX</Direction>\n";
            $t1p  .= "        </RxChannel>\n";
        }
        elsif( $rxChannel[$conSysNo] eq 'TRACE32' )
        {
            $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:Trace32RoutingParameterType\">\n";
            $t1p  .= "              <HostName>${t32Host[$conSysNo]}</HostName>\n";
            $t1p  .= "              <Port>${t32Port[$conSysNo]}</Port>\n";
            $t1p  .= "              <PacketLength>${t32PacketLength[$conSysNo]}</PacketLength>\n";
            $t1p  .= "              <TargetToHostBuffer>${symbolPrefix}${t32SymTargetToHostBuffer[$conSysNo]}</TargetToHostBuffer>\n";
            $t1p  .= "              <TargetToHostAnnounce>${symbolPrefix}${t32SymTargetToHostAnnounce[$conSysNo]}</TargetToHostAnnounce>\n";
            $t1p  .= "              <TargetToHostAck>${symbolPrefix}${t32SymTargetToHostAcknowledge[$conSysNo]}</TargetToHostAck>\n";
            $t1p  .= "              <TargetToHostFrameLength>${symbolPrefix}${t32SymTargetToHostFrameLength[$conSysNo]}</TargetToHostFrameLength>\n";
            $t1p  .= "              <HostToTargetBuffer>${symbolPrefix}${t32SymHostToTargetBuffer[$conSysNo]}</HostToTargetBuffer>\n";
            $t1p  .= "              <HostToTargetAnnounce>${symbolPrefix}${t32SymHostToTargetAnnounce[$conSysNo]}</HostToTargetAnnounce>\n";
            $t1p  .= "              <HostToTargetAck>${symbolPrefix}${t32SymHostToTargetAcknowledge[$conSysNo]}</HostToTargetAck>\n";
            $t1p  .= "              <HostToTargetFrameLength>${symbolPrefix}${t32SymHostToTargetFrameLength[$conSysNo]}</HostToTargetFrameLength>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>Lauterbach</Name>\n";
            $t1p  .= "            <BusType>LAUTERBACH</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>RX</Direction>\n";
            $t1p  .= "        </RxChannel>\n";
        }
        elsif ( $rxChannel[$conSysNo] eq 'ETHERNET_VECTOR' )
        {
            $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:VectorEthernetRoutingParameterType\">\n";
            $t1p  .= "              <PcIpAddress>$ethPcIP</PcIpAddress>\n";
            $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
            $t1p  .= "              <EcuIpAddress>$ethEcuIP[$conSysNo]</EcuIpAddress>\n";
            $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
            $t1p  .= "              <EcuMac>$ethMac[$conSysNo]</EcuMac>\n";
            $t1p  .= "              <NetworkName>$ethNetworkName[$conSysNo]</NetworkName>\n";
            $t1p  .= "              <VirtualPortName>$ethVirtualPortName[$conSysNo]</VirtualPortName>\n";
            $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "              <IsBlockSizeFixed>$ethMustUseFixedBlockSize</IsBlockSizeFixed>\n";
            $t1p  .= "              <TxCycleMs>$ethTxCycleMs</TxCycleMs>\n";
            if ( defined $vlanIDs[$conSysNo] )
            {
                $t1p  .= "              <VlanId>$vlanIDs[$conSysNo]</VlanId>\n";
            }
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>$ethHwName</Name>\n";
            $t1p  .= "            <BusType>VECTOR_ETHERNET</BusType>\n";
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
            if( 'true' eq $ethUseIpv6[$conSysNo] )
            {
                if( defined $ethEcuIP[$conSysNo] )
                {
                    # Perform basic check on IPv6 address format
                    # Min length is 2 (::)
                    # Max length is 39 (8*4 + 7, 0000:0000:0000:0000:0000:0000:0000:0000)
                    unless( $ethEcuIP[$conSysNo] =~ /^[0-9a-fA-F:]{2,39}$/ )
                    {
                        warn qq(Warning: Invalid IPv6 address "${ethEcuIP[$conSysNo]}".\n);
                    }
                }
                else
                {
                    # Set to default IPv6 address, see https://en.wikipedia.org/wiki/0.0.0.0
                    $ethEcuIP[$conSysNo] = '::';
                }
            }
            else # assume false (IPv4)
            {
                if( defined $ethEcuIP[$conSysNo] )
                {
                    # Perform basic check on IPv4 address format
                    unless( $ethEcuIP[$conSysNo] =~ /^\d{1,3}[.]\d{1,3}[.]\d{1,3}[.]\d{1,3}$/ )
                    {
                        warn qq(Warning: Invalid IPv4 address "${ethEcuIP[$conSysNo]}".\n);
                    }
                }
                else
                {
                    # Set to default IPv4 address, see https://en.wikipedia.org/wiki/0.0.0.0
                    $ethEcuIP[$conSysNo] = '0.0.0.0';
                }
            }

            $t1p  .= "              <IpAddress>$ethEcuIP[$conSysNo]</IpAddress>\n";
            # only specify the tag if the value is really set to a sensible value
            if( defined $ethEcuDNSHostName[$conSysNo] )
            {
                # Perform very basic check on DNS name (no space and length)
                unless( $ethEcuDNSHostName[$conSysNo] =~ /^\S{1,255}$/ )
                {
                    warn qq(Warning: Invalid DNS name "${ethEcuDNSHostName[$conSysNo]}".\n);
                }
                $t1p  .= "              <EcuDnsHostName>$ethEcuDNSHostName[$conSysNo]</EcuDnsHostName>\n";
            }
            $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
            $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
            if( $ethUseUdp[$conSysNo] eq 'true' )
            {
                ($t1p  .= "              <UseUdp>$ethUseUdp[$conSysNo]</UseUdp>\n");
            }
            # Append _V6 for IPv6
            my $txChannelString = $txChannel[$conSysNo] . ( ( 'true' eq $ethUseIpv6[$conSysNo] ) ? '_V6' : '' );
            $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>Ethernet</Name>\n";
            $t1p  .= "            <BusType>$txChannelString</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>TX</Direction>\n";
            $t1p  .= "        </TxChannel>\n";
        }
        elsif( $txChannel[$conSysNo] eq 'TRACE32' )
        {
            $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:Trace32RoutingParameterType\">\n";
            $t1p  .= "              <HostName>${t32Host[$conSysNo]}</HostName>\n";
            $t1p  .= "              <Port>${t32Port[$conSysNo]}</Port>\n";
            $t1p  .= "              <PacketLength>${t32PacketLength[$conSysNo]}</PacketLength>\n";
            $t1p  .= "              <TargetToHostBuffer>${symbolPrefix}${t32SymTargetToHostBuffer[$conSysNo]}</TargetToHostBuffer>\n";
            $t1p  .= "              <TargetToHostAnnounce>${symbolPrefix}${t32SymTargetToHostAnnounce[$conSysNo]}</TargetToHostAnnounce>\n";
            $t1p  .= "              <TargetToHostAck>${symbolPrefix}${t32SymTargetToHostAcknowledge[$conSysNo]}</TargetToHostAck>\n";
            $t1p  .= "              <TargetToHostFrameLength>${symbolPrefix}${t32SymTargetToHostFrameLength[$conSysNo]}</TargetToHostFrameLength>\n";
            $t1p  .= "              <HostToTargetBuffer>${symbolPrefix}${t32SymHostToTargetBuffer[$conSysNo]}</HostToTargetBuffer>\n";
            $t1p  .= "              <HostToTargetAnnounce>${symbolPrefix}${t32SymHostToTargetAnnounce[$conSysNo]}</HostToTargetAnnounce>\n";
            $t1p  .= "              <HostToTargetAck>${symbolPrefix}${t32SymHostToTargetAcknowledge[$conSysNo]}</HostToTargetAck>\n";
            $t1p  .= "              <HostToTargetFrameLength>${symbolPrefix}${t32SymHostToTargetFrameLength[$conSysNo]}</HostToTargetFrameLength>\n";
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>Lauterbach</Name>\n";
            $t1p  .= "            <BusType>LAUTERBACH</BusType>\n";
            $t1p  .= "          </BusRef>\n";
            $t1p  .= "          <Direction>TX</Direction>\n";
            $t1p  .= "        </TxChannel>\n";
        }
        elsif ( $txChannel[$conSysNo] eq 'ETHERNET_VECTOR' )
        {
            $t1p  .= "            <BusRoutingParameter xmlns:q4=\"Gliwa-CommunicationConfig\" xsi:type=\"q4:VectorEthernetRoutingParameterType\">\n";
            $t1p  .= "              <PcIpAddress>$ethPcIP</PcIpAddress>\n";
            $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
            $t1p  .= "              <EcuIpAddress>$ethEcuIP[$conSysNo]</EcuIpAddress>\n";
            $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
            $t1p  .= "              <EcuMac>$ethMac[$conSysNo]</EcuMac>\n";
            $t1p  .= "              <NetworkName>$ethNetworkName[$conSysNo]</NetworkName>\n";
            $t1p  .= "              <VirtualPortName>$ethVirtualPortName[$conSysNo]</VirtualPortName>\n";
            $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "              <IsBlockSizeFixed>$ethMustUseFixedBlockSize</IsBlockSizeFixed>\n";
            $t1p  .= "              <TxCycleMs>$ethTxCycleMs</TxCycleMs>\n";
            if ( defined $vlanIDs[$conSysNo] )
            {
                $t1p  .= "              <VlanId>$vlanIDs[$conSysNo]</VlanId>\n";
            }
            $t1p  .= "            </BusRoutingParameter>\n";
            $t1p  .= "          </LayerConfig>\n";
            $t1p  .= "          <BusRef>\n";
            $t1p  .= "            <Name>$ethHwName</Name>\n";
            $t1p  .= "            <BusType>VECTOR_ETHERNET</BusType>\n";
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

if( $projectLevelStackQueryConfigurationFromPrevT1p )
{
    # This feature is new in T1-HOST-SW V3.4.0, but no isT1HostSwVersionAllowed()
    # check as it is only generated by T1-HOST-SW V >= 3.4.0 anyways.
    $t1p .= <<"EOT";
    <StackQueryConfiguration>
${projectLevelStackQueryConfigurationFromPrevT1p}    </StackQueryConfiguration>
EOT
}
else
{
    # Do not put <StackQueryConfiguration /> into project file to not cause incompatibilities with T1-HOST-SW V < 3.4.0
}

if( '' ne $ethHardware or defined $ethHwName )
{
    if ( $txChannel[0] eq "ETHERNET_VECTOR" )
    {
        $t1p  .= "      <Buses FixedBlocksize=\"false\">\n";
        $t1p  .= "        <Name>$ethHwName</Name>\n";
        $t1p  .= "        <Type>VECTOR_ETHERNET</Type>\n";
        $t1p  .= "        <HwIdentifier>\n";
        $t1p  .= "          <Name>$ethHwName</Name>\n";
        $t1p  .= "          <PcMacAddress>000000000000</PcMacAddress>\n";
        $t1p  .= "          <HwType>VECTOR</HwType>\n";
        $t1p  .= "        </HwIdentifier>\n";
        $t1p  .= "        <TxCycleMs>$ethTxCycleMs</TxCycleMs>\n";
        $t1p  .= "      </Buses>\n";
    }
    else
    {
        if( 'true' eq $ethUseIpv6[0] )
        {
            if( defined $ethPcIP )
            {
                # Perform basic check on IPv6 address format
                # Min length is 2 (::)
                # Max length is 39 (8*4 + 7, 0000:0000:0000:0000:0000:0000:0000:0000)
                unless( $ethPcIP =~ /^[0-9a-fA-F:]{2,39}$/ )
                {
                    warn qq(Warning: Invalid IPv6 address "${ethPcIP}".\n);
                }
            }
            else
            {
                # Set to default IPv6 address, see https://en.wikipedia.org/wiki/0.0.0.0
                $ethPcIP = '::';
            }
        }
        else # assume false (IPv4)
        {
            if( defined $ethPcIP )
            {
                # Perform basic check on IPv4 address format
                unless( $ethPcIP =~ /^\d{1,3}[.]\d{1,3}[.]\d{1,3}[.]\d{1,3}$/ )
                {
                    warn qq(Warning: Invalid IPv4 address "${ethPcIP}".\n);
                }
            }
            else
            {
                # Set to default IPv4 address, see https://en.wikipedia.org/wiki/0.0.0.0
                $ethPcIP = '0.0.0.0';
            }
        }
        if( not defined $ethHwName )
        {
            $ethHwName='Ethernet';
        }
        $t1p  .= "    <Buses FixedBlocksize=\"$ethMustUseFixedBlockSize\">\n";
        $t1p  .= "      <Name>Ethernet</Name>\n";
        if( 'true' eq $ethUseIpv6[0] )
        {
            $t1p  .= "      <Type>ETHERNET_V6</Type>\n";
        }
        else # assume false, IPv4
        {
            $t1p  .= "      <Type>ETHERNET</Type>\n";
        }
        if( $ethUsage eq 'Preferred' )
        {
            $t1p  .= "      <HwIdentifier Usage=\"Preferred\">\n";
        }
        else
        {
            $t1p  .= "      <HwIdentifier>\n";
        }
        $t1p  .= "        <Name>$ethHwName</Name>\n";
        $t1p  .= "        <PcIpAddress>$ethPcIP</PcIpAddress>\n";
        $t1p  .= "        <HwType>$ethHardware</HwType>\n";
        $t1p  .= "      </HwIdentifier>\n";
        $t1p  .= "      <TxCycleMs>$ethTxCycleMs</TxCycleMs>\n";
        $t1p  .= "    </Buses>\n";
    }
}

if( $canFDHardware eq 'VECTOR' or ( $canFDHardware eq 'PEAK' and isT1HostSwVersionAllowed( $minT1HostSwVersion, '3.2.0' ) ) )
{
    if( not defined $canFDHwName )
    {
        $canFDHwName = '';
        $canFDHwName = 'CANcaseXL Channel 1' if $canFDHardware eq 'VECTOR';
    }
    $t1p .= "    <Buses";

    # Retrieve the minimum canFDMaxTxDataSize to set the MaxTxBlocksize corresponding to the size of the CAN FD message from the T1-HOST-SW to the target
    my $minTxDataSize = 64;
    foreach my $maxTxDataSize ( @canFDMaxTxDataSize )
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
    $t1p  .= "        <HwType>$canFDHardware</HwType>\n";
    $t1p  .= "      </HwIdentifier>\n";
    $t1p  .= "      <TxCycleMs>$txCycleMs</TxCycleMs>\n";
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
            $t1p  .= "          <Brp>$canFDBitTiming[0]</Brp>\n";
            $t1p  .= "          <Prop>$canFDBitTiming[1]</Prop>\n";
            $t1p  .= "          <Phase1>$canFDBitTiming[2]</Phase1>\n";
            $t1p  .= "          <Phase2>$canFDBitTiming[3]</Phase2>\n";
            $t1p  .= "          <Sjw>$canFDBitTiming[4]</Sjw>\n";
            $t1p  .= "          <Sam>$canFDBitTiming[5]</Sam>\n";
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
                $t1p  .= "          <Brp>$canFDDataBitTiming[0]</Brp>\n";
                $t1p  .= "          <Prop>$canFDDataBitTiming[1]</Prop>\n";
                $t1p  .= "          <Phase1>$canFDDataBitTiming[2]</Phase1>\n";
                $t1p  .= "          <Phase2>$canFDDataBitTiming[3]</Phase2>\n";
                $t1p  .= "          <Sjw>$canFDDataBitTiming[4]</Sjw>\n";
                $t1p  .= "          <Sam>$canFDDataBitTiming[5]</Sam>\n";
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

my %canBitTiming = (
    PEAK => {
                250000 => { Brp => '2', Prop => '0', Phase1 => '10', Phase2 => '5', Sjw => '4', Sam => '1' },
                500000 => { Brp => '1', Prop => '0', Phase1 => '10', Phase2 => '5', Sjw => '4', Sam => '1' },
                800000 => { Brp => '1', Prop => '0', Phase1 =>  '6', Phase2 => '3', Sjw => '3', Sam => '1' },
               1000000 => { Brp => '1', Prop => '0', Phase1 =>  '5', Phase2 => '2', Sjw => '2', Sam => '1' },
    },
    U2C => {
                100000 => { Brp => '3', Prop => '3', Phase1 =>  '8', Phase2 => '8', Sjw => '1', Sam => '3' },
                250000 => { Brp => '1', Prop => '7', Phase1 =>  '8', Phase2 => '8', Sjw => '1', Sam => '3' },
                500000 => { Brp => '1', Prop => '1', Phase1 =>  '6', Phase2 => '4', Sjw => '1', Sam => '3' },
    },
    VECTOR => {
                250000 => { Brp => '2', Prop => '0', Phase1 => '10', Phase2 => '5', Sjw => '4', Sam => '1' },
                500000 => { Brp => '1', Prop => '0', Phase1 => '10', Phase2 => '5', Sjw => '4', Sam => '1' },
                800000 => { Brp => '1', Prop => '0', Phase1 =>  '7', Phase2 => '2', Sjw => '2', Sam => '1' },
               1000000 => { Brp => '1', Prop => '0', Phase1 =>  '4', Phase2 => '3', Sjw => '4', Sam => '1' },
    },
);

sub CANConfig($$$$)
{
    my $hw = shift;
    my $canHwName = shift;
    my $baud = shift;
    my $preferred = '';
    $preferred = ' Usage="Preferred"' if 'Preferred' eq shift;

    return <<EOT;
    <Buses FixedBlocksize=\"$mustUseFixedBlockSize\">
      <Name>CAN1</Name>
      <Type>CAN</Type>
      <HwIdentifier$preferred>
        <Name>$canHwName</Name>
        <HwType>$hw</HwType>
      </HwIdentifier>
      <TxCycleMs>$txCycleMs</TxCycleMs>
      <BusConfig xmlns:q7=\"Gliwa-CommunicationConfig\" xsi:type=\"q7:CanBusConfigType\">
        <Bitrate>$baud</Bitrate>
        <BitTiming>
          <Brp>$canBitTiming{$hw}{$baud}{'Brp'}</Brp>
          <Prop>$canBitTiming{$hw}{$baud}{'Prop'}</Prop>
          <Phase1>$canBitTiming{$hw}{$baud}{'Phase1'}</Phase1>
          <Phase2>$canBitTiming{$hw}{$baud}{'Phase2'}</Phase2>
          <Sjw>$canBitTiming{$hw}{$baud}{'Sjw'}</Sjw>
          <Sam>$canBitTiming{$hw}{$baud}{'Sam'}</Sam>
        </BitTiming>
      </BusConfig>
    </Buses>
EOT
}

if( $canHardware eq 'VECTOR' )
{
    if( not defined $canHwName )
    {
        $canHwName='CANcaseXL Channel 1';
    }
    if( exists $canBitTiming{'VECTOR'}{$canBitrate} )
    {
        $t1p .= CANConfig( 'VECTOR', $canHwName, $canBitrate, $canUsage );
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in T1-HOST-SW!\n";
    }
}
elsif( $canHardware eq 'PEAK' and isT1HostSwVersionAllowed( $minT1HostSwVersion, '3.2.0' ) )
{
    if( not defined $canHwName )
    {
        $canHwName = '';
    }
    if( exists $canBitTiming{'PEAK'}{$canBitrate} )
    {
        $t1p .= CANConfig( 'PEAK', $canHwName, $canBitrate, $canUsage );
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in T1-HOST-SW!\n";
    }
}
elsif( $canHardware eq 'U2C' or ( not $ethHardware and not $ethHwName and not $canHardware and not $canFDHardware ) )  # if U2C specified or both default for retro-compatibility
{
    # Ensure that canHardware is set to a valid value
    $canHardware = 'U2C';
    if( not defined $canHwName )
    {
        $canHwName='U2C_';
    }
    if( exists $canBitTiming{'U2C'}{$canBitrate} )
    {
        $t1p .= CANConfig( 'U2C', $canHwName, $canBitrate, $canUsage );
    }
    elsif( $canBitrate == 1000000 )
    {
        print "Bitrate not supported by U2C. Please contact Gliwa!\n";
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in T1-HOST-SW!\n";
    }
}

# generate the CommunicationConfigList if the T1-HOST-SW V2 compatibility is not set
if( not $enforceHostV2Compatibility )
{
    $t1p  .= "    <CommunicationConfigList>\n";
    $t1p  .= "      <TargetConnectionConfig Name=\"$targetConnectionName\">\n";

    for my $sysNo (0 .. ($nOfCores-1))
    {
        if( not $isCoreUnused[$sysNo] )
        {
            my $conSysNo = 0; # if useSameConnectionForAllSystems is declared false in *.inv the settings at index 0 are used for all systems
            if( $useSameConnectionForAllSystems eq 'false' )
            {
                $conSysNo = $sysNo;
            }
            my $targetId                = int ($core0sid + $sysNo) % 32;
            my $intCanRxId              = hex $canRxID[$conSysNo];
            my $intCanTxId              = hex $canTxID[$conSysNo];
            my $intDiagSourceAddr       = hex $diagSourceAddr[$conSysNo];
            my $intDiagTargetAddr       = hex $diagTargetAddr[$conSysNo];
            my $intDiagT1Identifier     = hex $diagT1Identifier[$conSysNo];
            my $intDiagLocalIdentifier  = hex $diagLocalIdentifier[$conSysNo];
            my $intDiagCustomSessionId  = hex $diagCustomSessionId[$conSysNo];

            $t1p  .= "        <SystemConnectionList SID=\"$targetId\">\n";
            $t1p  .= "          <SystemCommunicationConfig UseSameRxTxChannel=\"$useSameRxTxChannel[$conSysNo]\">\n";
            $t1p  .= "            <RxChannel>\n";
            $t1p  .= "              <LayerConfig>\n";
            $t1p  .= "                <Name>$connectionType[$conSysNo]</Name>\n";
            $t1p  .= "                <RoutingParameters xmlns:q1=\"Gliwa-CommunicationConfig\" xsi:type=\"q1:GcpRoutingParameterType\">\n";
            $t1p  .= "                  <AppId>0</AppId>\n";
            $t1p  .= "                  <TargetId>$targetId</TargetId>\n";
            $t1p  .= "                  <Timeout>$gcpTimeoutMs[$conSysNo]</Timeout>\n";
            $t1p  .= "                </RoutingParameters>\n";
            if( $rxChannel[$conSysNo] eq 'ETHERNET' ) # if it is an Ethernet RxChannel
            {
                $t1p  .= "                <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:TcpIpRoutingParameterType\">\n";
                if( 'true' eq $ethUseIpv6[$conSysNo] )
                {
                    if( defined $ethEcuIP[$conSysNo] )
                    {
                        # Perform basic check on IPv6 address format
                        # Min length is 2 (::)
                        # Max length is 39 (8*4 + 7, 0000:0000:0000:0000:0000:0000:0000:0000)
                        unless( $ethEcuIP[$conSysNo] =~ /^[0-9a-fA-F:]{2,39}$/ )
                        {
                            warn qq(Warning: Invalid IPv6 address "${ethEcuIP[$conSysNo]}".\n);
                        }
                    }
                    else
                    {
                        # Set to default IPv6 address, see https://en.wikipedia.org/wiki/0.0.0.0
                        $ethEcuIP[$conSysNo] = '::';
                    }
                }
                else # assume false (IPv4)
                {
                    if( defined $ethEcuIP[$conSysNo] )
                    {
                        # Perform basic check on IPv4 address format
                        unless( $ethEcuIP[$conSysNo] =~ /^\d{1,3}[.]\d{1,3}[.]\d{1,3}[.]\d{1,3}$/ )
                        {
                            warn qq(Warning: Invalid IPv4 address "${ethEcuIP[$conSysNo]}".\n);
                        }
                    }
                    else
                    {
                        # Set to default IPv4 address, see https://en.wikipedia.org/wiki/0.0.0.0
                        $ethEcuIP[$conSysNo] = '0.0.0.0';
                    }
                }
                $t1p  .= "                  <IpAddress>$ethEcuIP[$conSysNo]</IpAddress>\n";
                # only specify the tag if the value is really set to a sensible value
                if( defined $ethEcuDNSHostName[$conSysNo] )
                {
                    # Perform very basic check on DNS name (no space and length)
                    unless( $ethEcuDNSHostName[$conSysNo] =~ /^\S{1,255}$/ )
                    {
                        warn qq(Warning: Invalid DNS name "${ethEcuDNSHostName[$conSysNo]}".\n);
                    }
                    $t1p  .= "              <EcuDnsHostName>$ethEcuDNSHostName[$conSysNo]</EcuDnsHostName>\n";
                }
                $t1p  .= "                  <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
                $t1p  .= "                  <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
                if( $ethUseUdp[$conSysNo] eq 'true' )
                {
                    ($t1p  .= "                  <UseUdp>$ethUseUdp[$conSysNo]</UseUdp>\n");
                }
                # Append _V6 for IPv6
                my $rxChannelString = $rxChannel[$conSysNo] . ( ( 'true' eq $ethUseIpv6[$conSysNo] ) ? '_V6' : '' );
                $t1p  .= "                  <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                $t1p  .= "                </BusRoutingParameter>\n";
                $t1p  .= "              </LayerConfig>\n";
                $t1p  .= "              <BusRef>\n";
                $t1p  .= "                <Name>Ethernet</Name>\n";
                $t1p  .= "                <BusType>$rxChannelString</BusType>\n";
                $t1p  .= "              </BusRef>\n";
                $t1p  .= "              <Direction>RX</Direction>\n";
                $t1p  .= "            </RxChannel>\n";
            }
            elsif( $rxChannel[$conSysNo] eq 'TRACE32' )
            {
                $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:Trace32RoutingParameterType\">\n";
                $t1p  .= "              <HostName>${t32Host[$conSysNo]}</HostName>\n";
                $t1p  .= "              <Port>${t32Port[$conSysNo]}</Port>\n";
                $t1p  .= "              <PacketLength>${t32PacketLength[$conSysNo]}</PacketLength>\n";
                $t1p  .= "              <TargetToHostBuffer>${symbolPrefix}${t32SymTargetToHostBuffer[$conSysNo]}</TargetToHostBuffer>\n";
                $t1p  .= "              <TargetToHostAnnounce>${symbolPrefix}${t32SymTargetToHostAnnounce[$conSysNo]}</TargetToHostAnnounce>\n";
                $t1p  .= "              <TargetToHostAck>${symbolPrefix}${t32SymTargetToHostAcknowledge[$conSysNo]}</TargetToHostAck>\n";
                $t1p  .= "              <TargetToHostFrameLength>${symbolPrefix}${t32SymTargetToHostFrameLength[$conSysNo]}</TargetToHostFrameLength>\n";
                $t1p  .= "              <HostToTargetBuffer>${symbolPrefix}${t32SymHostToTargetBuffer[$conSysNo]}</HostToTargetBuffer>\n";
                $t1p  .= "              <HostToTargetAnnounce>${symbolPrefix}${t32SymHostToTargetAnnounce[$conSysNo]}</HostToTargetAnnounce>\n";
                $t1p  .= "              <HostToTargetAck>${symbolPrefix}${t32SymHostToTargetAcknowledge[$conSysNo]}</HostToTargetAck>\n";
                $t1p  .= "              <HostToTargetFrameLength>${symbolPrefix}${t32SymHostToTargetFrameLength[$conSysNo]}</HostToTargetFrameLength>\n";
                $t1p  .= "            </BusRoutingParameter>\n";
                $t1p  .= "          </LayerConfig>\n";
                $t1p  .= "          <BusRef>\n";
                $t1p  .= "            <Name>Lauterbach</Name>\n";
                $t1p  .= "            <BusType>LAUTERBACH</BusType>\n";
                $t1p  .= "          </BusRef>\n";
                $t1p  .= "          <Direction>RX</Direction>\n";
                $t1p  .= "        </RxChannel>\n";
            }
            elsif ( $rxChannel[$conSysNo] eq 'ETHERNET_VECTOR' )
            {
                $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:VectorEthernetRoutingParameterType\">\n";
                $t1p  .= "              <PcIpAddress>$ethPcIP</PcIpAddress>\n";
                $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
                $t1p  .= "              <EcuIpAddress>$ethEcuIP[$conSysNo]</EcuIpAddress>\n";
                $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
                $t1p  .= "              <EcuMac>$ethMac[$conSysNo]</EcuMac>\n";
                $t1p  .= "              <NetworkName>$ethNetworkName[$conSysNo]</NetworkName>\n";
                $t1p  .= "              <VirtualPortName>$ethVirtualPortName[$conSysNo]</VirtualPortName>\n";
                $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                $t1p  .= "              <IsBlockSizeFixed>$ethMustUseFixedBlockSize</IsBlockSizeFixed>\n";
                $t1p  .= "              <TxCycleMs>$ethTxCycleMs</TxCycleMs>\n";
                if ( defined $vlanIDs[$conSysNo] )
                {
                    $t1p  .= "              <VlanId>$vlanIDs[$conSysNo]</VlanId>\n";
                }
                $t1p  .= "            </BusRoutingParameter>\n";
                $t1p  .= "          </LayerConfig>\n";
                $t1p  .= "          <BusRef>\n";
                $t1p  .= "            <Name>$ethHwName</Name>\n";
                $t1p  .= "            <BusType>VECTOR_ETHERNET</BusType>\n";
                $t1p  .= "          </BusRef>\n";
                $t1p  .= "          <Direction>RX</Direction>\n";
                $t1p  .= "        </RxChannel>\n";
            }
            else
            {
                if( $connectionType[$conSysNo] eq 'Diagnosis' )
                {
                    $t1p  .= "                <RoutingParameters xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:DgnRoutingParameterType\">\n";
                    $t1p  .= "                  <AddressingMode>$diagAddressingMode[$conSysNo]</AddressingMode>\n";
                    $t1p  .= "                  <SouceAddress>$intDiagSourceAddr</SouceAddress>\n";
                    $t1p  .= "                  <TargetAddress>$intDiagTargetAddr</TargetAddress>\n";
                    $t1p  .= "                  <UseServicesByLocId>$diagUseServiceByLocalId[$conSysNo]</UseServicesByLocId>\n";
                    $t1p  .= "                  <T1Identifier>$intDiagT1Identifier</T1Identifier>\n";
                    $t1p  .= "                  <T1LocalIdentifier>$intDiagLocalIdentifier</T1LocalIdentifier>\n";
                    $t1p  .= "                  <RxDataSize>$diagMaxRxDataSize[$conSysNo]</RxDataSize>\n";
                    $t1p  .= "                  <TxDataSize>$diagMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                    $t1p  .= "                  <minTxDataSize>$diagMinTxDataSize[$conSysNo]</minTxDataSize>\n";
                    $t1p  .= "                  <OpenSession>$diagOpenSessionType[$conSysNo]</OpenSession>\n";
                    if( $diagOpenSessionType[$conSysNo] eq 'Custom' )
                    {
                        $t1p  .= "                  <CustomSessionId>$intDiagCustomSessionId</CustomSessionId>\n";
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
                        $t1p  .= "                  <TesterPresentPeriod>$diagTesterPresentPeriod[$conSysNo]</TesterPresentPeriod>\n";
                    }
                    $t1p  .= "                  <Timeout>$diagTimeoutMs[$conSysNo]</Timeout>\n";
                    $t1p  .= "                </RoutingParameters>\n";
                }
                $t1p  .= "                <BusRoutingParameter xmlns:q3=\"Gliwa-CommunicationConfig\" xsi:type=\"q3:CanRoutingParameterType\">\n";
                $t1p  .= "                  <CanId>\n";
                $t1p  .= "                    <Id>$intCanRxId</Id>\n";
                $t1p  .= "                    <isExtended>$canExtendedIds[$conSysNo]</isExtended>\n";
                $t1p  .= "                  </CanId>\n";
                $t1p  .= "                </BusRoutingParameter>\n";
                $t1p  .= "              </LayerConfig>\n";
                $t1p  .= "              <BusRef>\n";
                $t1p  .= "                <Name>$rxChannel[$conSysNo]1</Name>\n";
                $t1p  .= "                <BusType>$rxChannel[$conSysNo]</BusType>\n";
                $t1p  .= "              </BusRef>\n";
                $t1p  .= "              <Direction>RX</Direction>\n";
                $t1p  .= "            </RxChannel>\n";
            }

            $t1p  .= "            <TxChannel>\n";
            $t1p  .= "              <LayerConfig>\n";
            $t1p  .= "                <Name>$connectionType[$conSysNo]</Name>\n";
            $t1p  .= "                <RoutingParameters xmlns:q1=\"Gliwa-CommunicationConfig\" xsi:type=\"q1:GcpRoutingParameterType\">\n";
            $t1p  .= "                  <AppId>0</AppId>\n";
            $t1p  .= "                  <TargetId>$targetId</TargetId>\n";
            $t1p  .= "                </RoutingParameters>\n";
            if( $txChannel[$conSysNo] eq 'ETHERNET' ) # if it is an Ethernet TxChannel
            {
                $t1p  .= "                <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:TcpIpRoutingParameterType\">\n";
                if( 'true' eq $ethUseIpv6[$conSysNo] )
                {
                    if( defined $ethEcuIP[$conSysNo] )
                    {
                        # Perform basic check on IPv6 address format
                        # Min length is 2 (::)
                        # Max length is 39 (8*4 + 7, 0000:0000:0000:0000:0000:0000:0000:0000)
                        unless( $ethEcuIP[$conSysNo] =~ /^[0-9a-fA-F:]{2,39}$/ )
                        {
                            warn qq(Warning: Invalid IPv6 address "${ethEcuIP[$conSysNo]}".\n);
                        }
                    }
                    else
                    {
                        # Set to default IPv6 address, see https://en.wikipedia.org/wiki/0.0.0.0
                        $ethEcuIP[$conSysNo] = '::';
                    }
                }
                else # assume false (IPv4)
                {
                    if( defined $ethEcuIP[$conSysNo] )
                    {
                        # Perform basic check on IPv4 address format
                        unless( $ethEcuIP[$conSysNo] =~ /^\d{1,3}[.]\d{1,3}[.]\d{1,3}[.]\d{1,3}$/ )
                        {
                            warn qq(Warning: Invalid IPv4 address "${ethEcuIP[$conSysNo]}".\n);
                        }
                    }
                    else
                    {
                        # Set to default IPv4 address, see https://en.wikipedia.org/wiki/0.0.0.0
                        $ethEcuIP[$conSysNo] = '0.0.0.0';
                    }
                }

                $t1p  .= "                  <IpAddress>$ethEcuIP[$conSysNo]</IpAddress>\n";
                # only specify the tag if the value is really set to a sensible value
                if( defined $ethEcuDNSHostName[$conSysNo] )
                {
                    # Perform very basic check on DNS name (no space and length)
                    unless( $ethEcuDNSHostName[$conSysNo] =~ /^\S{1,255}$/ )
                    {
                        warn qq(Warning: Invalid DNS name "${ethEcuDNSHostName[$conSysNo]}".\n);
                    }
                    $t1p  .= "                  <EcuDnsHostName>$ethEcuDNSHostName[$conSysNo]</EcuDnsHostName>\n";
                }
                $t1p  .= "                  <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
                $t1p  .= "                  <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
                if( $ethUseUdp[$conSysNo] eq 'true' )
                {
                    ($t1p  .= "                  <UseUdp>$ethUseUdp[$conSysNo]</UseUdp>\n");
                }
                # Append _V6 for IPv6
                my $txChannelString = $txChannel[$conSysNo] . ( ( 'true' eq $ethUseIpv6[$conSysNo] ) ? '_V6' : '' );
                $t1p  .= "                  <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                $t1p  .= "                </BusRoutingParameter>\n";
                $t1p  .= "              </LayerConfig>\n";
                $t1p  .= "              <BusRef>\n";
                $t1p  .= "                <Name>Ethernet</Name>\n";
                $t1p  .= "                <BusType>$txChannelString</BusType>\n";
                $t1p  .= "              </BusRef>\n";
                $t1p  .= "              <Direction>TX</Direction>\n";
                $t1p  .= "            </TxChannel>\n";
            }
            elsif( $txChannel[$conSysNo] eq 'TRACE32' )
            {
                $t1p  .= "            <BusRoutingParameter xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:Trace32RoutingParameterType\">\n";
                $t1p  .= "              <HostName>${t32Host[$conSysNo]}</HostName>\n";
                $t1p  .= "              <Port>${t32Port[$conSysNo]}</Port>\n";
                $t1p  .= "              <PacketLength>${t32PacketLength[$conSysNo]}</PacketLength>\n";
                $t1p  .= "              <TargetToHostBuffer>${symbolPrefix}${t32SymTargetToHostBuffer[$conSysNo]}</TargetToHostBuffer>\n";
                $t1p  .= "              <TargetToHostAnnounce>${symbolPrefix}${t32SymTargetToHostAnnounce[$conSysNo]}</TargetToHostAnnounce>\n";
                $t1p  .= "              <TargetToHostAck>${symbolPrefix}${t32SymTargetToHostAcknowledge[$conSysNo]}</TargetToHostAck>\n";
                $t1p  .= "              <TargetToHostFrameLength>${symbolPrefix}${t32SymTargetToHostFrameLength[$conSysNo]}</TargetToHostFrameLength>\n";
                $t1p  .= "              <HostToTargetBuffer>${symbolPrefix}${t32SymHostToTargetBuffer[$conSysNo]}</HostToTargetBuffer>\n";
                $t1p  .= "              <HostToTargetAnnounce>${symbolPrefix}${t32SymHostToTargetAnnounce[$conSysNo]}</HostToTargetAnnounce>\n";
                $t1p  .= "              <HostToTargetAck>${symbolPrefix}${t32SymHostToTargetAcknowledge[$conSysNo]}</HostToTargetAck>\n";
                $t1p  .= "              <HostToTargetFrameLength>${symbolPrefix}${t32SymHostToTargetFrameLength[$conSysNo]}</HostToTargetFrameLength>\n";
                $t1p  .= "            </BusRoutingParameter>\n";
                $t1p  .= "          </LayerConfig>\n";
                $t1p  .= "          <BusRef>\n";
                $t1p  .= "            <Name>Lauterbach</Name>\n";
                $t1p  .= "            <BusType>LAUTERBACH</BusType>\n";
                $t1p  .= "          </BusRef>\n";
                $t1p  .= "          <Direction>TX</Direction>\n";
                $t1p  .= "        </TxChannel>\n";
            }
            elsif ( $txChannel[$conSysNo] eq 'ETHERNET_VECTOR' )
            {
                $t1p  .= "            <BusRoutingParameter xmlns:q4=\"Gliwa-CommunicationConfig\" xsi:type=\"q4:VectorEthernetRoutingParameterType\">\n";
                $t1p  .= "              <PcIpAddress>$ethPcIP</PcIpAddress>\n";
                $t1p  .= "              <PcPort>$ethPcPort[$conSysNo]</PcPort>\n";
                $t1p  .= "              <EcuIpAddress>$ethEcuIP[$conSysNo]</EcuIpAddress>\n";
                $t1p  .= "              <EcuPort>$ethEcuPort[$conSysNo]</EcuPort>\n";
                $t1p  .= "              <EcuMac>$ethMac[$conSysNo]</EcuMac>\n";
                $t1p  .= "              <NetworkName>$ethNetworkName[$conSysNo]</NetworkName>\n";
                $t1p  .= "              <VirtualPortName>$ethVirtualPortName[$conSysNo]</VirtualPortName>\n";
                $t1p  .= "              <TxDataSize>$ethMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                $t1p  .= "              <IsBlockSizeFixed>$ethMustUseFixedBlockSize</IsBlockSizeFixed>\n";
                $t1p  .= "              <TxCycleMs>$ethTxCycleMs</TxCycleMs>\n";
                if ( defined $vlanIDs[$conSysNo] )
                {
                    $t1p  .= "              <VlanId>$vlanIDs[$conSysNo]</VlanId>\n";
                }
                $t1p  .= "            </BusRoutingParameter>\n";
                $t1p  .= "          </LayerConfig>\n";
                $t1p  .= "          <BusRef>\n";
                $t1p  .= "            <Name>$ethHwName</Name>\n";
                $t1p  .= "            <BusType>VECTOR_ETHERNET</BusType>\n";
                $t1p  .= "          </BusRef>\n";
                $t1p  .= "          <Direction>TX</Direction>\n";
                $t1p  .= "        </TxChannel>\n";
            }
            else
            {
                if( $connectionType[$conSysNo] eq 'Diagnosis' )
                {
                    $t1p  .= "                <RoutingParameters xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:DgnRoutingParameterType\">\n";
                    $t1p  .= "                  <AddressingMode>$diagAddressingMode[$conSysNo]</AddressingMode>\n";
                    $t1p  .= "                  <SouceAddress>$intDiagSourceAddr</SouceAddress>\n";
                    $t1p  .= "                  <TargetAddress>$intDiagTargetAddr</TargetAddress>\n";
                    $t1p  .= "                  <UseServicesByLocId>$diagUseServiceByLocalId[$conSysNo]</UseServicesByLocId>\n";
                    $t1p  .= "                  <T1Identifier>$intDiagT1Identifier</T1Identifier>\n";
                    $t1p  .= "                  <T1LocalIdentifier>$intDiagLocalIdentifier</T1LocalIdentifier>\n";
                    $t1p  .= "                  <RxDataSize>$diagMaxRxDataSize[$conSysNo]</RxDataSize>\n";
                    $t1p  .= "                  <TxDataSize>$diagMaxTxDataSize[$conSysNo]</TxDataSize>\n";
                    $t1p  .= "                  <minTxDataSize>$diagMinTxDataSize[$conSysNo]</minTxDataSize>\n";
                    $t1p  .= "                  <OpenSession>$diagOpenSessionType[$conSysNo]</OpenSession>\n";
                    if( $diagOpenSessionType[$conSysNo] eq 'Custom' )
                    {
                        $t1p  .= "                  <CustomSessionId>$intDiagCustomSessionId</CustomSessionId>\n";
                    }
                    if( $diagTesterPresentPeriod[$conSysNo] != 0 )
                    {
                        $t1p  .= "                  <TesterPresentPeriod>$diagTesterPresentPeriod[$conSysNo]</TesterPresentPeriod>\n";
                    }
                    $t1p  .= "                </RoutingParameters>\n";
                }
                $t1p  .= "                <BusRoutingParameter xmlns:q3=\"Gliwa-CommunicationConfig\" xsi:type=\"q3:CanRoutingParameterType\">\n";
                $t1p  .= "                  <CanId>\n";
                $t1p  .= "                    <Id>$intCanTxId</Id>\n";
                $t1p  .= "                    <isExtended>$canExtendedIds[$conSysNo]</isExtended>\n";
                $t1p  .= "                  </CanId>\n";
                $t1p  .= "                </BusRoutingParameter>\n";
                $t1p  .= "              </LayerConfig>\n";
                $t1p  .= "              <BusRef>\n";
                $t1p  .= "                <Name>$txChannel[$conSysNo]1</Name>\n";
                $t1p  .= "                <BusType>$txChannel[$conSysNo]</BusType>\n";
                $t1p  .= "              </BusRef>\n";
                $t1p  .= "              <Direction>TX</Direction>\n";
                $t1p  .= "            </TxChannel>\n";
            }
            $t1p  .= "            <Timeout>$hostTimeoutMs[$conSysNo]</Timeout>\n";
            $t1p  .= "          </SystemCommunicationConfig>\n";
            $t1p  .= "        </SystemConnectionList>\n";
        }
    }
    $t1p  .= "      </TargetConnectionConfig>\n";
    $t1p  .= "    </CommunicationConfigList>\n";
}
$t1p  .= "  </Project>\n";
$t1p  .= "</T1>\n";

writeUnlessEqual( $projectFile, $t1p, 'utf-8' );

######################################################################################
# Create T1_config.h
######################################################################################

#----------------------------------------------------------------------------------
my $traceTaskMacro = FormatDocu( $enableDoxygenComments, 'T1_TRACE_TASK', undef ) . "#define T1_TRACE_TASK( taskId_ ) \\\n(  1 \\\n";

foreach my $exclName ( @targetExcludeFromTraceByName )
{
    $traceTaskMacro .= " && ((taskId_) != T1_${exclName}_ID) \\\n";
}
foreach my $exclId ( @targetExcludeFromTraceById )
{
   $traceTaskMacro .= " && ((taskId_) != $exclId) \\\n";
}
$traceTaskMacro .= ")\n";

#----------------------------------------------------------------------------------

if( $idHeader )
{
    # Use getFileBaseName() to optionally convert the filename to UTF-8
    my $idHeaderBaseName = getFileBaseName( $idHeader );

    my $idHeaderIncl = '';

    foreach my $inc ( @idHeaderIncludes )
    {
        $idHeaderIncl .= "#include $inc\n" if $inc;
    }

    my $t1idHIds = $t1ConfigHIds;  # copy all task ID macros to ID-header
    $t1ConfigHIds = '';            # delete all task ID macros from config header

    my $idHeaderContent = generateSourceFileHeader( $idHeaderBaseName, $genDate );
    my ($includeGuardStart, $includeGuardEnd) = generateIncludeGuard( $idHeaderBaseName );
    $idHeaderContent .= <<EOT;

${includeGuardStart}
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

#if defined T1_ENABLE
$t1IsrWrapper
#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/

${includeGuardEnd}
EOT

    writeUnlessEqual( $idHeader, $idHeaderContent, $sourceFileEncoding )
# PID-'002'
    ;
}

#----------------------------------------------------------------------------------

# Convert values in milliseconds to multiples of communications core T1_Handler period
if( '' ne $timeoutResponse )
{
    warn "-timeoutResponse is deprecated, please use -timeoutResponseMs instead!\n";
}
if( '' ne $timeoutTx )
{
    warn "-timeoutTx is deprecated, please use -timeoutTxMs instead!\n";
}
if( '' ne $timeoutRx )
{
    warn "-timeoutRx is deprecated, please use -timeoutRxMs instead!\n";
}
if( '' ne $timeoutResponseMs )
{
    $timeoutResponse = int( $timeoutResponseMs / $t1HandlerPeriodMs[$commsCoreOffset] );
}
$timeoutResponse = 65534 unless $timeoutResponse <= 65534;
if( '' ne $timeoutTxMs )
{
    $timeoutTx = int( $timeoutTxMs / $t1HandlerPeriodMs[$commsCoreOffset] );
}
$timeoutTx = 65535 unless $timeoutTx <= 65535;
if( '' ne $timeoutRxMs )
{
    $timeoutRx = int( $timeoutRxMs / $t1HandlerPeriodMs[$commsCoreOffset] );
}
$timeoutRx = 65535 unless $timeoutRx <= 65535;

# analysisCapacity defaults to traceBufferEntries (trace buffer size)
for my $sysNo (0 .. ($nOfCores-1))
{
    $analysisCapacity[$sysNo] = $traceBufferEntries[$sysNo] if 0 == $analysisCapacity[$sysNo];
}

# Create configuration hash for sharing with T1_config.pm
my %config;
$config{'rawTimerBitLength'} = \@rawTimerBitLength;
$config{'analysisCapacity'} = \@analysisCapacity;
$config{'bidHeader'} = $bidHeader;
$config{'canHardware'} = $canHardware;
$config{'canRxID'} = \@canRxID;
$config{'canTxID'} = \@canTxID;
$config{'canFDHardware'} = $canFDHardware;
$config{'canFDMaxRxDataSize'} = \@canFDMaxRxDataSize;
$config{'canFDMaxTxDataSize'} = \@canFDMaxTxDataSize;
$config{'ethHwName'} = $ethHwName;
$config{'ethUseIpv6'} = \@ethUseIpv6;
$config{'ethUseUdp'} = \@ethUseUdp;
$config{'ethPcIP'} = $ethPcIP;
$config{'ethEcuIP'} = \@ethEcuIP;
$config{'ethEcuDNSHostName'} = \@ethEcuDNSHostName;
$config{'ethEcuPort'} = \@ethEcuPort;
$config{'ethPcPort'} = \@ethPcPort;
$config{'connectionType'} = \@connectionType;
$config{'txChannel'} = \@txChannel;
$config{'rxChannel'} = \@rxChannel;
$config{'contRunsOnCore'} = \%contRunsOnCore;
$config{'cpuLoadAvgSamples'} = \@cpuLoadAvgSamples;
$config{'cpuLoadThreshold'} = \@cpuLoadThreshold;
$config{'cpuLoadTxPeriod'} = \@cpuLoadTxPeriod;
$config{'diagMinTxDataSize'} = \@diagMinTxDataSize;
$config{'diagMaxRxDataSize'} = \@diagMaxRxDataSize;
$config{'diagMaxTxDataSize'} = \@diagMaxTxDataSize;
$config{'ethMaxRxDataSize'} = \@ethMaxRxDataSize;
$config{'ethMaxTxDataSize'} = \@ethMaxTxDataSize;
$config{'t32HostToTargetBufferSize'} = \@t32HostToTargetBufferSize;
$config{'t32TargetToHostBufferSize'} = \@t32TargetToHostBufferSize;
$config{'initFeatureMask'} = $initFeatureMask;
$config{'nOfCores'} = $nOfCores;
$config{'commsCoreOffset'} = $commsCoreOffset;
$config{'nOfDelays'} = \@nOfDelays;
$config{'nOfFlexAddrs'} = \@nOfFlexAddrs;
$config{'numberOfFlexBufferEntries'} = \@numberOfFlexBufferEntries;
$config{'nOfFlexStopwatches'} = \@nOfFlexStopwatches;
$config{'numberOfConstraints'} = \@numberOfConstraints;
$config{'numberOfTasks'} = \@numberOfTasks;
$config{'numberOfUserStpws'} = \@numberOfUserStpws;
$config{'cat1IsrIdOffset'} = \@cat1IsrIdOffset;
$config{'cat2IsrIdOffset'} = \@cat2IsrIdOffset;
$config{'externalIsrIdOffset'} = \@externalIsrIdOffset;
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
$config{'traceWideSyncTimer'} = $traceWideSyncTimer;
$config{'syncTimerTickDurationNs'} = $syncTimerTickDurationNs;
$config{'t1BidHDefs'} = $t1BidHDefs;
$config{'t1FlexOverheadNs'} = \@t1FlexOverheadNs;
$config{'t1ScopeOverheadNs'} = \@t1ScopeOverheadNs;
$config{'tickDurationNs'} = \@tickDurationNs;
$config{'rawTickDurationNs'} = \@rawTickDurationNs;
$config{'timeoutResponse'} = $timeoutResponse;
$config{'timeoutRx'} = $timeoutRx;
$config{'timeoutTx'} = $timeoutTx;
$config{'traceBufferEntries'} = \@traceBufferEntries;
$config{'traceTimerDownCounting'} = \@traceTimerDownCounting;
$config{'syncTimerDownCounting'} = $syncTimerDownCounting;
$config{'traceTimerIsSyncTimer'} = \@traceTimerIsSyncTimer;
$config{'allTraceTimersAreSyncTimer'} = $allTraceTimersAreSyncTimer;
$config{'anyTraceTimerIsSyncTimer'} = $anyTraceTimerIsSyncTimer;
$config{'traceTimerBitLength'} = \@traceTimerBitLength;
$config{'allCoresRawToTickRatio'} = $allCoresRawToTickRatio;
$config{'allCoresTraceTickDurationNs'} = $allCoresTraceTickDurationNs;
$config{'allCoresRawTickDurationNs'} = $allCoresRawTickDurationNs;
$config{'useSameConnectionForAllSystems'} = $useSameConnectionForAllSystems;
$config{'numberOfFocusMeasurements'} = $numberOfFocusMeasurements;
$config{'featureMaskCallback'} = \@featureMaskCallback;
$config{'checkIntegration'} = $checkIntegration;
$config{'t1HandlerPeriodMs'} = \@t1HandlerPeriodMs;
$config{'taskData'} = \%taskData;
my @syncPeriod = map { int( 0.999 + $syncPeriodMs / $_ ) } @t1HandlerPeriodMs;
# Saturate to unsigned 8-bit max
foreach my $syncPeriod ( @syncPeriod )
{
    $syncPeriod = 255 if 255 < $syncPeriod;
}
$config{'syncPeriod'} = \@syncPeriod;
$config{'taskNames'} = \%taskNames;
$config{'traceTimeStampBitLength'} = $traceTimeStampBitLength;
$config{'taskIdClash'} = $taskIdClash;
$config{'enableDoxygenComments'} = $enableDoxygenComments;
$config{'applicationFeatures'} = \@applicationFeatures;
$config{'delays'} = \@delays;
$config{'userStopWatches'} = \@userStopWatches;
$config{'userEvents'} = \@userEvents;
$config{'constraints'} = \@constraints;
$config{'externalTraceBuffer'} = $externalTraceBuffer;
$cortexMFPBversion = 256 unless 'true' eq $cortex;
$config{'cortexMFPBversion'} = $cortexMFPBversion;
$config{'minT1HostSwVersion'} = $minT1HostSwVersion;
$config{'useDMStrampoline'} = \@useDMStrampoline;
$config{'foregroundCont'} = $foregroundCont;
$config{'trapCls3UserHandler'} = \@trapCls3UserHandler;

my $clFlagsString = join "\n ", @clFlags;
my $clFlagsComment = <<EOT;
/*************************************************************************************
 * Command line flags:
 *********************
 $clFlagsString
 ************************************************************************************/
EOT

######################################################################################
# Create T1_configGen.c
######################################################################################

my $taskActExtraTotal = 0;

if( $configGenC )
{
    my $tempConfigGenC = $configGenC . '_';
    my $includeBidHeader = '';
    $includeBidHeader = "#include \"" . File::Basename::basename($bidHeader) . "\"\n" if $bidHeader;

    # Use getFileBaseName() to optionally convert the filename to UTF-8
    my $configGenCBaseName = getFileBaseName( $configGenC );

    open my $fhtempConfigGenC, $sourceFileEncoding ? ">:encoding(${sourceFileEncoding})" : '>', $tempConfigGenC or die qq(Error: Unable to write file "${tempConfigGenC}"\n);

    print $fhtempConfigGenC generateSourceFileHeader( $configGenCBaseName, $genDate );
    print $fhtempConfigGenC <<EOT;

$clFlagsComment
/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$includeAllHeaders$includeBidHeader

/*----------------------------------------------------------------------------------*/
/*--- Config variables -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
    $taskActExtraTotal = GenT1ConfigC( $fhtempConfigGenC, \%config );
    close $fhtempConfigGenC;

    # Re-read temporary file into a string for writeUnlessEqual
    open $fhtempConfigGenC, $sourceFileEncoding ? "<:encoding(${sourceFileEncoding})" : '<', $tempConfigGenC or die qq(Error: Unable to re-read "${tempConfigGenC}"\n);
    my $configGenContent = join '', <$fhtempConfigGenC>;
    close $fhtempConfigGenC;
    unlink $tempConfigGenC;

    writeUnlessEqual( $configGenC, $configGenContent, $sourceFileEncoding )
# PID-'005'
    ;
}

######################################################################################
# Create T1_configGen.h
######################################################################################

if( $configHeader )
{
    my $tempConfigHeader = $configHeader . '_';
    # Use getFileBaseName() to optionally convert the filename to UTF-8
    my $configHeaderBaseName = getFileBaseName( $configHeader );
    my $t1config_IsrWrapper = '';

    createPath( $tempConfigHeader ) or die qq(Error: Unable to create path for file "${tempConfigHeader}"\n);

    open my $fhTmpCfgH, $sourceFileEncoding ? ">:encoding(${sourceFileEncoding})" : '>', $tempConfigHeader or die qq(Error: Unable to write file "${tempConfigHeader}"\n);

    my $globalMacros = "";
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_COUNT_PREEMPTION',               '1') if 'true' eq $countPreemption;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_FG_CONT',                        '1') if 'true' eq $foregroundCont;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_WAIT_RESUME',                    '1') if 'true' eq $waitResume;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_CROSS_CORE_ACT',                 '1') if 'true' eq $crossCoreAct;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_DISABLE_T1_CONT',                '1') if 'true' eq $disableT1Cont;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_DISABLE_T1_FLEX',                '1') if 'true' eq $disableT1Flex;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_DISABLE_T1_MOD',                 '1') if 'true' eq $disableT1Mod;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_DISABLE_T1_DELAY',               '1') if 'true' eq $disableT1Delay;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_SUPPORT_TIMER_OVERFLOW',         '1') if 'true' eq $supportTimerOverflow;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_DETECT_TIMER_OVERFLOW',          '1') if 'true' eq $detectTimerOverflow;
    $globalMacros  .= FormatConfigMacro( $enableDoxygenComments, 0, 'T1_CONT_NOF_VRTL_STPWS', $numberOfVirtualStopwatches) if defined $numberOfVirtualStopwatches;

    my $configHeaderIncl = "";

    foreach my $inc ( @configHeaderIncludes )
    {
        $configHeaderIncl .= "#include $inc\n" unless $inc eq "";
    }

    my $localTraceTaskMacro = "";
    if( '' eq $idHeader ) # only copy traceTaskMacro to config header if no ID header is generated
    {
        $localTraceTaskMacro = $traceTaskMacro;
        $t1config_IsrWrapper = $t1IsrWrapper;
    }

    print $fhTmpCfgH generateSourceFileHeader( $configHeaderBaseName, $genDate );
    my ($includeGuardStart, $includeGuardEnd) = generateIncludeGuard( $configHeaderBaseName );
    print $fhTmpCfgH <<EOT;

$clFlagsComment
${includeGuardStart}
/*----------------------------------------------------------------------------------*/
/*--- Global macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$globalMacros

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$configHeaderIncl

/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$t1ConfigHIds
EOT
    GenT1ConfigHAF(     $fhTmpCfgH,            \%config );
    GenT1ConfigHDL(     $fhTmpCfgH, $nOfCores, \%config );
    GenT1ConfigHUE(     $fhTmpCfgH, $nOfCores, \%config );
    GenT1ConfigHUserSw( $fhTmpCfgH, $nOfCores, \%config );
    print $fhTmpCfgH <<EOT;
/*----------------------------------------------------------------------------------*/
/*--- Config macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
    GenT1ConfigH( $fhTmpCfgH, \%config, $taskActExtraTotal );
    print $fhTmpCfgH <<EOT;

$localTraceTaskMacro

/*----------------------------------------------------------------------------------*/
/*--- Function wrapper -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE
$t1config_IsrWrapper
#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/

${includeGuardEnd}
EOT
# PID-'003'
# Referenced Perl Symbol: $fhTmpCfgH

    close $fhTmpCfgH;
    # Re-read temporary file into a string for writeUnlessEqual
    open $fhTmpCfgH, $sourceFileEncoding ? "<:encoding(${sourceFileEncoding})" : '<', $tempConfigHeader or die qq(Error: Unable to re-read "${tempConfigHeader}"\n);
    my $configContent = join '', <$fhTmpCfgH>;
    close $fhTmpCfgH;
    # Delete temporary file
    unlink $tempConfigHeader;

    writeUnlessEqual( $configHeader, $configContent, $sourceFileEncoding )
# PID-'004'
    ;
}

######################################################################################
# Create T1_configBuff.c if required
######################################################################################

if( 'true' eq $externalTraceBuffer )
{
    my $tempConfigBuffC = $configBuffC . '_';

    # Use getFileBaseName() to optionally convert the filename to UTF-8
    my $configBuffCBaseName = getFileBaseName( $configBuffC );

    open my $fhtempConfigBuffC, $sourceFileEncoding ? ">:encoding(${sourceFileEncoding})" : '>', $tempConfigBuffC or die qq(Error: Unable to write file "${tempConfigBuffC}"\n);

    print $fhtempConfigBuffC generateSourceFileHeader( $configBuffCBaseName, $genDate );
    print $fhtempConfigBuffC <<EOT;

$clFlagsComment
/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

$includeAllHeaders

/*----------------------------------------------------------------------------------*/
/*--- Config variables -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

EOT
    GenT1ConfigBuffC( $fhtempConfigBuffC, \%config );
    close $fhtempConfigBuffC;

    # Re-read temporary file into a string for writeUnlessEqual
    open $fhtempConfigBuffC, $sourceFileEncoding ? "<:encoding(${sourceFileEncoding})" : '<', $tempConfigBuffC or die qq(Error: Unable to re-read "${tempConfigBuffC}"\n);
    my $configBuffContent = join '', <$fhtempConfigBuffC>;
    close $fhtempConfigBuffC;
    unlink $tempConfigBuffC;

    writeUnlessEqual( $configBuffC, $configBuffContent, $sourceFileEncoding )
# PID-'007'
    ;
}

######################################################################################
# Create T1_bid.h
######################################################################################

if( $bidHeader )
{
    # Use getFileBaseName() to optionally convert the filename to UTF-8
    my $bidHeaderBaseName = getFileBaseName( $bidHeader );

    createPath( $bidHeader ) or die qq(Error: Unable to create path for file "${bidHeader}"\n);
    open my $fhBidHeader, $sourceFileEncoding ? ">:encoding(${sourceFileEncoding})" : '>', $bidHeader or die qq(Error: could not open file "${bidHeader}" for output\n);

    print $fhBidHeader generateSourceFileHeader( $bidHeaderBaseName, $genDate );
    my ($includeGuardStart, $includeGuardEnd) = generateIncludeGuard( $bidHeaderBaseName );
    print $fhBidHeader <<EOT;

$clFlagsComment
${includeGuardStart}
/*----------------------------------------------------------------------------------*/
/*--- Config macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1BidHDefs

/*----------------------------------------------------------------------------------*/

${includeGuardEnd}
EOT

    close $fhBidHeader;
}

######################################################################################
# Create T1_annot.t1a
######################################################################################

if( $t1LibAnnotationsFile )
{
    require T1_annot;
    import T1_annot;

    my @fhT1LibAnnotationsFilesPC = ();
    my $annotationBaseName = File::Basename::basename( $t1LibAnnotationsFile, '.t1a' );
    # Use getFileBaseName() to optionally convert the filename to UTF-8
    $annotationBaseName = getFileBaseName( $annotationBaseName );

    createPath( $t1LibAnnotationsFile ) or die qq(Error: Unable to create path for file "${t1LibAnnotationsFile}"\n);
    # Always write XML files using UTF-8 encoding
    open my $fhT1LibAnnotationsFile, '>:encoding(utf-8)', $t1LibAnnotationsFile or die qq(Error: could not open file "${t1LibAnnotationsFile}" for output\n);
    foreach my $sysNo (0 .. ($nOfCores-1))
    {
        open my $fhT1LibAnnotationsFileCoreX, '>:encoding(utf-8)', "$annotationBaseName\_Core$sysNo.t1a" or die qq(Error: could not open file "${"$annotationBaseName\_Core$sysNo.t1a"}" for output\n);
        push @fhT1LibAnnotationsFilesPC, $fhT1LibAnnotationsFileCoreX;
    }
    GenT1Annotations( \%config, $fhT1LibAnnotationsFile, \@fhT1LibAnnotationsFilesPC );
    close $fhT1LibAnnotationsFile;
    foreach my $fh (@fhT1LibAnnotationsFilesPC)
    {
        close $fh;
    }
}

######################################################################################
# Create runnable header if required
######################################################################################

if( $runnableHeader )
{
    # Use getFileBaseName() to optionally convert the filename to UTF-8
    my $runnableHeaderBaseName = getFileBaseName( $runnableHeader );
    my $runnableDefnitions = eval { OsGetRunnableDefinitions( ) };
    $runnableDefnitions = '' unless defined $runnableDefnitions;

    my $runnableHeaderIncl = '';

    foreach my $inc ( @runnableHeaderIncludes )
    {
        $runnableHeaderIncl .= "#include $inc\n" if $inc;
    }

    my $runnableHeaderContent = generateSourceFileHeader( $runnableHeaderBaseName, $genDate );
    my ($includeGuardStart, $includeGuardEnd) = generateIncludeGuard( $runnableHeaderBaseName );
    $runnableHeaderContent .= <<EOT;

$clFlagsComment
${includeGuardStart}
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
#if defined T1_TRACE_RUNNABLES

$runnableDefnitions

#endif /* defined T1_TRACE_RUNNABLES    */
/*----------------------------------------------------------------------------------*/

${includeGuardEnd}
EOT

    writeUnlessEqual( $runnableHeader, $runnableHeaderContent, $sourceFileEncoding )
# PID-'006'
    ;
}
