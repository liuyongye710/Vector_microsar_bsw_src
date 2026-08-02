@rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem r
@rem
@rem File:          T1_projGen.bat
@rem
@rem Description:   Batch file to run T1_projGen.pl
@rem
@rem $Author: jialinli $
@rem
@rem $Revision: 370 $
@rem
@rem Copyright:     GLIWA embedded systems GmbH & Co. KG
@rem                Weilheim i.OB.
@rem                All rights reserved
@rem
@rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem rem r

@echo off
pushd %~dp0..

rem -I tells Perl where to look for modules
perl -I T1_neusarOS -I T1_Perl T1_Perl\T1_projGen.pl -UserCfg=T1_UserCfg.inv -Cfg=T1_Cfg.inv -OsPm=T1_neusarOS.pm -OsCfg=T1_OsCfg.inv
popd
pause