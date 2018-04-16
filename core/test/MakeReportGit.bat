@echo off
setlocal enabledelayedexpansion
:: ==============================================================================
::  SYNOPSIS
::	MakeReport [-k] [-h] [-v] [-s] [-D level]
::
::  DESCRIPTION:
::	daily_build $B$N%l%]!<%H%U%!%$%k$r:n@.$9$k(B. $B<!$N%3%^%s%I$,%m!<%+%k$GF0:n(B
::	$B$9$kI,MW$,$"$k(B ($B$3$l$i$O(B bin $B%G%#%l%/%H%j$KCV$/$3$H(B).
::	    gawk.exe	( awk $B$NBeBXJ*$J$i$J$s$G$b$h$$(B )
::	    nkf.exe
::
::  VERSION:
::	Ver 1.0	 2012/11/03 F.Kanehori	$B=iHG(B (Unix $B8F=P$7HG(B)
::	Ver 2.0  2013/02/07 F.Kanehori	Windows $B0\?"=iHG(B
::	Ver 3.0  2017/10/18 F.Kanehori	$B?7%l%]%8%H%j9=B$BP1~(B
::	Ver 3.1  2017/11/22 F.Kanehori	$B3+;O(B/$B=*N;;~9o$rI=<((B
::	Ver 3.2  2017/12/21 F.Kanehori	Log directory on the web changed.
:: ==============================================================================
set PROG=%~n0
echo %PROG%: started at %date% %time%

::----------------------------------------------
::  $B2<0L$N=hM}%W%m%0%i%`$KEO$9%*%W%7%g%s(B
::    -k  $B:n6H%U%!%$%k$r;D$9(B
::    -V  $B%P!<%P%9>pJs=PNO!J%G%U%)%k%H!K(B
::    -D  $B%G%P%C%0>pJs=PNO(B
::  $B$3$N%P%C%A%9%/%j%W%H$G;HMQ$9$k%*%W%7%g%s(B
::    -c  $B%l%]!<%H%U%!%$%k$r%&%'%V$K%3%T!<$9$k(B
::    -h  $B;HMQJ}K!$NI=<((B
::    -v  $B%P!<%P%9>pJs=PNO!J%G%U%)%k%H!K(B
::    -s  $B%P!<%P%9>pJs=PNOM^@)!JA4%9%/%j%W%H!K(B
::----------------------------------------------
set OPT_C=0
set OPT_K=0
set OPT_S=0
set OPT_V=1
set OPT_W=0
set OPT_D=0
set VAL_D=0
set ARGC=0
:next_arg
       if "%1" == "-c" ( set OPT_C=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-k" ( set OPT_K=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if /i "%1" == "-h" ( call :usage && exit /b
) else if /i "%1" == "/h" ( call :usage && exit /b
) else if "%1" == "-V" ( set OPT_W=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-v" ( set OPT_V=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-s" ( set OPT_S=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-D" ( set OPT_D=1 && set VAL_D=%2&& shift && shift && set /a ARGC-=2 && goto :next_arg
) else (
    set ARG=%1
    if "!ARG:~0,1!" == "-" (
	echo %PROG%: invalid option -- [%1]
	call :usage && exit /b
    )
)
if %OPT_S% == 1 ( set OPT_V=0 && set OPT_W=0)
for %%a in ( %* ) do set /a ARGC+=1
if %ARGC% gtr 1 (
    call :usage && exit /b
)
set ARGS=
if %OPT_K% == 1 (set ARGS=%ARGS% -k)
if %OPT_V% == 1 (set ARGS=%ARGS% -v)
if %OPT_W% == 1 (set ARGS=%ARGS% -V)
if %OPT_D% == 1 (set ARGS=%ARGS% -D %VAL_D%)
if "%ARGS:~0,1%" == " " (
    set ARGS=!ARGS:~1!
)
if %ARGC% == 1 (set ARGS=%ARGS% %1)

::----------------------------------------------
::  $BF|IU>pJs$N<hF@(B
::
set YYYY=%DATE:~0,4%
set MM=%DATE:~5,2%
set DD=%DATE:~8,2%
set TODAY=%YYYY%-%MM%%DD%

::----------------------------------------------
::  $B;HMQ$9$k%W%m%0%i%`(B
::
set BASEDIR=.\Monitoring
set BINDIR=.\bin
set CMND=build_monitor_Git

::----------------------------------------------
::  $B%m!<%+%k%[%9%H>e$G%3%^%s%I$r<B9T(B
::
set CWD=%cd%
cd %BASEDIR%
cmd /c %BINDIR%\%CMND% %ARGS%
cd %CWD%

::----------------------------------------------
::  $B%3%T!<85(B/$B@h$N%G%#%l%/%H%j$NDj5A(B
::
set SELFPATH=%~dp0
set REPBASE=%SELFPATH%report
set WEBBASE=\\haselab\HomeDirs\WWW\docroots\springhead\dailybuild\log
set WEBREPT=%WEBBASE%

::----------------------------------------------
::  $B%&%'%V$K%3%T!<$9$k%U%!%$%k$NDj5A(B
::
set REPFILE=%TODAY%.report
set BLDDIFF=%TODAY%.bldlog.diff
set STBDIFF=%TODAY%.stblog.diff
set RUNDIFF=%TODAY%.runlog.diff
set SPLDIFF=%TODAY%.spllog.diff

:: $B%&%'%V>e$G$NL>>N(B
::
set WEB_REPFILE=Test.report
set WEB_BLDDIFF=Build.log.diff
set WEB_STBDIFF=StubBuild.log.diff
set WEB_RUNDIFF=Run.log.diff
set WEB_SPLDIFF=SamplesBuild.log.diff

::----------------------------------------------
::  $B%&%'%V$K%3%T!<(B
::
if %OPT_C% == 1 (
    if %OPT_V% == 1 ( echo copying files to the web ... )
    copy /Y %REPBASE%\%REPFILE% %WEBBASE%\%WEB_REPFILE%
    copy /Y %REPBASE%\%BLDDIFF% %WEBREPT%\%WEB_BLDDIFF%
    copy /Y %REPBASE%\%STBDIFF% %WEBREPT%\%WEB_STBDIFF%
    copy /Y %REPBASE%\%RUNDIFF% %WEBREPT%\%WEB_RUNDIFF%
    copy /Y %REPBASE%\%SPLDIFF% %WEBREPT%\%WEB_SPLDIFF%
    if %OPT_V% == 1 ( echo done )
)

::----------------------------------------------
::  $B%m!<%+%k$N%U%!%$%k$r:o=|(B
::
if not %OPT_K% == 1 (
    if %OPT_V% == 1 ( set /p=clearing directory %REPBASE% ... < NUL )
    rem del %REPBASE%\%REPFILE% 2> NUL
    del %REPBASE%\%BLDDIFF% 2> NUL
    del %REPBASE%\%STBDIFF% 2> NUL
    del %REPBASE%\%RUNDIFF% 2> NUL
    del %REPBASE%\%SPLDIFF% 2> NUL
    if %OPT_V% == 1 ( echo done )
)

echo %PROG%: teminated at %date% %time%
endlocal
exit /b

::----------------------------------------------
::  $B;HMQJ}K!$NI=<((B
::----------------------------------------------
:usage
    echo Usage: %PROG% [options] [xxxx:yyyy]
    echo 	xxxx: old-revision-number
    echo 	yyyy: new-revision-number
    echo 	options:
    echo 	  -c:	copy report file to the web
    echo 	  -k:	keep temporary files
    echo 	  -h:	show usage
    echo 	  -v:	set verbose mode
    echo 	  -V:	set precise verbose mode
    echo 	  -s:	set silent mode
    echo 	  -D n:	set debug level to 'n'
exit /b

:: end: MkaeReport.bat
