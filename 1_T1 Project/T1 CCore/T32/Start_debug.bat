@ECHO OFF
REM script to start debugger for core_0.
REM GTM core will be started by practice script

REM SET EXE_DIR=bin\windows64
SET EXE_DIR=bin\windows64

REM Set the directives of the project
SET P1_PORT=10000
SET P2_TITLE=Core0
SET P3_TMP=D:\APP\T32\temp
SET P4_SYS=D:\APP\T32
SET P5_HELP=D:\APP\T32\pdf

IF "%1"=="" (
  SET P6_PBI=USB
  SET P7_OPT=CORE=1
  SET P8_OPT=
  SET P9_OPT=
) ELSE (
  SET P6_PBI=NET
  SET P7_OPT=NODE=%1
  SET P8_OPT=PACKLEN=1024
  SET P9_OPT=CORE=1
)

REM call the c:\T32\bin\windows64\t32mtc using config_multicore.t32,
REM and start with executing the tc27x_tc29x_demo.cmm
REM the GTM windows will be fired by the script file
start %P4_SYS%\%EXE_DIR%\t32mppc -c config_multicore.t32 %P1_PORT% %P2_TITLE% %P3_TMP% %P4_SYS% %P5_HELP% %P6_PBI% %P7_OPT% %P8_OPT% %P9_OPT% -s ccfc3007pt_petter.cmm
