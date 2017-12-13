@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	build_monitor [[old-revision]:[new-revision]]
::
::  DESCRIPTION
::	�����Ŏw�肵��2�̃��r�W�����ɂ��āAsvn ����r���h���ʂƎ��s���ʂ�
::	���o���ă��|�[�g���쐬����. �����ɂ�郌�r�W�����w����ȗ������Ƃ���
::	�t�@�C�� revision.old �y�� revsion.new �Ŏw�肵�����r�W�������g�p����.
::	�쐬�������|�[�g��, �t�@�C�� ./report/YYYY-MMDD.report �ɏo�͂���.
::	������ YYYY-MMDD �́A�V���r�W�����ɑΉ�������t�ł���.
::  CAUTION
::	�o�̓t�@�C���� Windows ���猩�邱�Ƃ�O��Ƃ���, �����R�[�h�͂��ׂ�
::	ShiftJIS �ɕϊ�����.
::
::  VERSION
::	Ver 1.0  2013/01/16 F.Kanehori	Unix �ł��ڐA
::	Ver 1.1	 2014/02/03 F.Kanehori	Samples �ɂ��Ă� ErrorLog �ɕύX
::	Ver 1.2	 2017/10/18 F.Kanehori	�V���|�W�g���ɑΉ��iURL�̕ύX���j
::	Ver 1.3	 2017/11/20 F.Kanehori	�G���R�[�f�B���O�� utf8 �ɕύX
::	Ver 1.31 2017/11/22 F.Kanehori	�G���R�[�f�B���O�� utf8 BOM�t�� �ɕύX
::	Ver 1.32 2017/11/27 F.Kanehori	�����̍��ׂȕύX
:: ============================================================================
set PROG=%~n0

::----------------------------------------------
::  ���ʂ̏����v���O�����ɓn���I�v�V����
::	  -V  �o�[�o�X���o��
::	  -D  �f�o�b�O���o��
::  ���̃o�b�`�X�N���v�g�Ŏg�p����ϐ��̒�`
::	  -k  ��ƃt�@�C�����c��
::	  -m  ���[���𑗐M����i�������j
::	  -h  �g�p���@�̕\��
::	  -v  �o�[�o�X���o��
::	  -D  �f�o�b�O���o��
::----------------------------------------------
set OPT_K=0
set OPT_V=0
set OPT_W=0
set OPT_D=0
set VAL_D=0
set OPT_M=0
set ARGC=0
:next_arg
       if "%1" == "-k" ( set OPT_K=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-m" ( set OPT_M=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-h" ( call :usage && exit /b
) else if "%1" == "-v" ( set OPT_V=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-V" ( set OPT_W=1 && shift && set /a ARGC-=1 && goto :next_arg
) else if "%1" == "-D" ( set OPT_D=1 && set VAL_D=%2&& shift && shift && set /a ARGC-=2 && goto :next_arg
) else (
    set ARG=%1
    if "!ARG:~0,1!" == "-" (
	echo %PROG%: invalid option -- [%1]
	call :usage && exit /b
    )
)
for %%a in ( %* ) do set /a ARGC+=1
if %ARGC% gtr 1 (
    call :usage && exit /b
)
if %VAL_D% geq 1 ( echo ARGC=%ARGC% )

::----------------------------------------------
::  ���ʏ����v���O�����̃I�v�V�����̒�`
::
set MYDIFFOPT=
set FILTEROPT=
if %OPT_W% geq 1 ( set MYDIFFOPT=%MYDIFFOPT% -v)
if %OPT_W% geq 1 ( set FILTEROPT=%FILTEROPT% -v)
if %OPT_D% geq 1 ( set MYDIFFOPT=%MYDIFFOPT% -D %VAL_D% )
if %OPT_D% geq 1 ( set FILTEROPT=%FILTEROPT% -D %VAL_D% )
call :trim MYDIFFOPT "%MYDIFFOPT%"
call :trim FILTEROPT "%FILTEROPT%"
rem if %OPT_M% == 1 ( set REPORTBYMAIL=1 )

::----------------------------------------------
::  ���݂̓��t�Ǝ���
::
set DATESTR=%date:~0,4%-%date:~5,2%%date:~8,2% %time:~0,8%

::----------------------------------------------
::  ���ʂ�񍐂��郁�[���Ɋւ���
::	  REPORTBYMAIL	1 (���� -m ���w��) �Ȃ猋�ʂ����[���Œm�点��
::
set REPORTBYMAIL=0
set MAILSUBJECT=Daily-build Report on %DATESTR%
set MAILTOADDR=
set MAILFMADDR=

::----------------------------------------------
::  �g�p����f�B���N�g���̒�`
::
set BASEDIR=.
set BINDIR=%BASEDIR%\bin
set REPDIR=%BASEDIR%\..\report
set ETCDIR=%BASEDIR%\etc
set TMPDIR=%REPDIR%\tmp

::----------------------------------------------
::  �g�p����v���O�����̒�`
::
set ORDER=perl %BINDIR%\order.pl
set MYDIFF=perl %BINDIR%\mydiff.pl
set FILTER=perl %BINDIR%\filter.pl
set NKF=%BINDIR%\nkf.exe
set AWK=%BINDIR%\gawk.exe
::SENDMAIL=/usr/sbin/sendmail

::----------------------------------------------
::  ���r�W�����͈͂̌���
::
set OLDREV=0
set NEWREV=0
if %ARGC% == 1 (
    call :backquote OLDREV "echo %1 ^| %AWK% -f %BINDIR%\field.awk -v sep=":" -v field=1"
    call :backquote NEWREV "echo %1 ^| %AWK% -f %BINDIR%\field.awk -v sep=":" -v field=2"
)
if %VAL_D% geq 1 (
    echo -- OLDREV-1 [%OLDREV%]
    echo -- NEWREV-1 [%NEWREV%]
    call :show_options
)

::----------------------------------------------
::  ����svn(URL)���g�p����
::
set SVNURL=http://springhead.info/spr2/Springhead/trunk/
set STBLOGURL=%SVNURL%core/test/log/StubBuild.log
set BLDLOGURL=%SVNURL%core/test/log/Build.log
set RUNLOGURL=%SVNURL%core/test/log/Run.log
set SPLLOGURL=%SVNURL%core/test/log/SamplesBuild.log
set STBERRURL=%SVNURL%core/test/log/StubBuildError.log
set BLDERRURL=%SVNURL%core/test/log/BuildError.log
set RUNERRURL=%SVNURL%core/test/log/RunError.log
set SPLERRURL=%SVNURL%core/test/log/SamplesBuildError.log
if %OPT_V% == 1 (
    echo use following URLs:
    echo   %STBLOGURL%
    echo   %BLDLOGURL%
    echo   %RUNLOGURL%
    echo   %SPLLOGURL%
    echo   %STBERRURL%
    echo   %BLDERRURL%
    echo   %RUNERRURL%
    echo   %SPLERRURL%
)

::----------------------------------------------
::  �g�p����t�@�C���� (���͑�)
::  (�o�͂���t�@�C�����͌�����߂�)
::
set OLDREVFILE=%ETCDIR%\revision.old
set NEWREVFILE=%ETCDIR%\revision.new
set SVNLOGTMP=%TMPDIR%\svnlog.tmp

::----------------------------------------------
::  �V�O�i���g���b�v�̐ݒ�
::
rem trap "cleanup 1" SIGHUP SIGINT SIGQUIT SIGTERM

::----------------------------------------------
::  ��r�̊�ƂȂ郌�r�W����(old-revision)�̌���
::
if %OLDREV% == 0 (
    :: old-revision �t�@�C�������݂���΂���������o��
    if exist %OLDREVFILE% (
	call :backquote OLDREV "%AWK% -f %BINDIR%\field.awk -v start=2 %OLDREVFILE%"
	if "!OLDREV!" == "" ( set OLDREV=0 )
    )
    if !OLDREV! == 0 (
	echo %PROG%: Error: old-revision ���w�肳��Ă��܂���
	exit /b
    )
)

::----------------------------------------------
::  ��r���郌�r�W����(new-revision)�̌���
::
if %NEWREV% == 0 (
    :: new-revision �t�@�C�������݂���΂���������o��
    if exist %NEWREVFILE% (
	call :backquote NEWREV "%AWK% -f %BINDIR%\grep.awk -v pat=rev %NEWREVFILE%"
	call :backquote NEWREV "echo !NEWREV! ^| %AWK% -f %BINDIR%\field.awk -v start=2"
	if !NEWREV! == 0 (
	    :: ���r�W�����̑���� HEAD �Ǝw�肳��Ă�����ŐV�̃��r�W�������g�p����
	    call :backquote NEWREV "%AWK% -f %BINDIR%\grep.awk -v pat=head %NEWREVFILE%"
	    call :backquote NEWREV "echo !NEWREV! ^| %AWK% -f %BINDIR%\field.awk"
	    if "!NEWREV!" == "HEAD" (
		if %OPT_V% == 1 ( set /p=extracting HEAD revision from svn ... < NUL )
		svn log -q %SVNURL% -r HEAD > %SVNLOGTMP% 2> NUL
		call :backquote NEWREV "%AWK% -f %BINDIR%\line.awk -v line=2 %SVNLOGTMP%"
		call :backquote NEWREV "echo !NEWREV! ^| %AWK% -f %BINDIR%\field.awk -v start=2"
		if %OPT_V% == 1 ( echo done )
	    )
	)
    )
    if !NEWREV! == 0 (
	echo %PROG%: Error: new-revision ���w�肳��Ă��܂���.
        exit /b
    )
)
if %VAL_D% geq 1 (
    echo -- OLDREV-2 [%OLDREV%]
    echo -- NEWREV-2 [%NEWREV%]
)

::----------------------------------------------
::  svn ���� OLDREV �̓��t�Ǝ������擾����
::
svn log -r %OLDREV% %SVNURL% > %SVNLOGTMP% 2> NUL
call :backquote TMPDATE "%AWK% -f %BINDIR%\line.awk -v line=2 %SVNLOGTMP% ^| %AWK% -f %BINDIR%\field.awk -v block=3 field=1"
call :backquote TMPTIME "%AWK% -f %BINDIR%\line.awk -v line=2 %SVNLOGTMP% ^| %AWK% -f %BINDIR%\field.awk -v block=3 field=2"
set OLDDATE=%TMPDATE:~0,7%%TMPDATE:~8,2%
set OLDTIME=%TMPTIME%
 
::----------------------------------------------
::  svn ���� NEWREV �̓��t�Ǝ������擾����
::
svn log -r %NEWREV% %SVNURL% > %SVNLOGTMP% 2> NUL
call :backquote TMPDATE "%AWK% -f %BINDIR%\line.awk -v line=2 %SVNLOGTMP% ^| %AWK% -f %BINDIR%\field.awk -v block=3 field=1"
call :backquote TMPTIME "%AWK% -f %BINDIR%\line.awk -v line=2 %SVNLOGTMP% ^| %AWK% -f %BINDIR%\field.awk -v block=3 field=2"
set NEWDATE=%TMPDATE:~0,7%%TMPDATE:~8,2%
set NEWTIME=%TMPTIME%

if %OPT_V% == 1 (
    echo OLD-revision: %OLDREV% ^(%OLDDATE% %OLDTIME%^)
    echo NEW-revision: %NEWREV% ^(%NEWDATE% %NEWTIME%^)
)

::----------------------------------------------
::  �o�͂���t�@�C���������߂� (NEWDATE ��p����)
::
::     TMPOLDxxxFILE	svn cat -r $OLDREV | order �̌���
set TMPOLDSTBFILE=%TMPDIR%\r%OLDREV%.stblog.old
set TMPOLDBLDFILE=%TMPDIR%\r%OLDREV%.bldlog.old
set TMPOLDRUNFILE=%TMPDIR%\r%OLDREV%.runlog.old
set TMPOLDSPLFILE=%TMPDIR%\r%OLDREV%.spllog.old
set TMPOLDSTBERRF=%TMPDIR%\r%OLDREV%.stberrlog.old
set TMPOLDBLDERRF=%TMPDIR%\r%OLDREV%.blderrlog.old
set TMPOLDRUNERRF=%TMPDIR%\r%OLDREV%.runerrlog.old
set TMPOLDSPLERRF=%TMPDIR%\r%OLDREV%.splerrlog.old
::     TMPNEWxxxFILE	svn cat -r $NEWREV | order �̌���
set TMPNEWSTBFILE=%TMPDIR%\r%NEWREV%.stblog.new
set TMPNEWBLDFILE=%TMPDIR%\r%NEWREV%.bldlog.new
set TMPNEWRUNFILE=%TMPDIR%\r%NEWREV%.runlog.new
set TMPNEWSPLFILE=%TMPDIR%\r%NEWREV%.spllog.new
set TMPNEWSTBERRF=%TMPDIR%\r%NEWREV%.stberrlog.new
set TMPNEWBLDERRF=%TMPDIR%\r%NEWREV%.blderrlog.new
set TMPNEWRUNERRF=%TMPDIR%\r%NEWREV%.runerrlog.new
set TMPNEWSPLERRF=%TMPDIR%\r%NEWREV%.splerrlog.new
::     REPROTFILE	���|�[�g�t�@�C��
set REPORTFILE=%REPDIR%\%NEWDATE%.report
::     �Q�l���t�@�C��
set STBLOGDIFFFILE=%REPDIR%\%NEWDATE%.stblog.diff
set BLDLOGDIFFFILE=%REPDIR%\%NEWDATE%.bldlog.diff
set RUNLOGDIFFFILE=%REPDIR%\%NEWDATE%.runlog.diff
set SPLLOGDIFFFILE=%REPDIR%\%NEWDATE%.spllog.diff
::     TMPFILE		��ƃt�@�C��
set TMPFILE=%TMPDIR%\build_monitor.tmp
set TMPSTBLOGDIFFFILE=%TMPDIR%\%NEWDATE%.stblog.diff
set TMPBLDLOGDIFFFILE=%TMPDIR%\%NEWDATE%.bldlog.diff
set TMPRUNLOGDIFFFILE=%TMPDIR%\%NEWDATE%.runlog.diff
set TMPSPLLOGDIFFFILE=%TMPDIR%\%NEWDATE%.spllog.diff
set TMPSTBERRDIFFFILE=%TMPDIR%\%NEWDATE%.stberrlog.diff
set TMPBLDERRDIFFFILE=%TMPDIR%\%NEWDATE%.blderrlog.diff
set TMPRUNERRDIFFFILE=%TMPDIR%\%NEWDATE%.runerrlog.diff
set TMPSPLERRDIFFFILE=%TMPDIR%\%NEWDATE%.splerrlog.diff

if %OPT_V% == 1 (
    echo outout to:
    echo   %REPORTFILE%
)

::----------------------------------------------
::  OLDREV �� NEWREV �̃��O�t�@�C�������o��
::
if %OPT_V% == 1 ( set /p=extracting log info ... < NUL )
svn cat -r %OLDREV% %STBLOGURL% | %ORDER% > %TMPOLDSTBFILE%
svn cat -r %OLDREV% %BLDLOGURL% | %ORDER% > %TMPOLDBLDFILE%
svn cat -r %OLDREV% %RUNLOGURL% | %ORDER% > %TMPOLDRUNFILE%
svn cat -r %OLDREV% %SPLLOGURL% | %ORDER% > %TMPOLDSPLFILE%
svn cat -r %OLDREV% %STBERRURL% | %ORDER% > %TMPOLDSTBERRF%
svn cat -r %OLDREV% %BLDERRURL% | %ORDER% > %TMPOLDBLDERRF%
svn cat -r %OLDREV% %RUNERRURL% | %ORDER% > %TMPOLDRUNERRF%
svn cat -r %OLDREV% %SPLERRURL% | %ORDER% > %TMPOLDSPLERRF%

svn cat -r %NEWREV% %STBLOGURL% | %ORDER% > %TMPNEWSTBFILE%
svn cat -r %NEWREV% %BLDLOGURL% | %ORDER% > %TMPNEWBLDFILE%
svn cat -r %NEWREV% %RUNLOGURL% | %ORDER% > %TMPNEWRUNFILE%
svn cat -r %NEWREV% %SPLLOGURL% | %ORDER% > %TMPNEWSPLFILE%
svn cat -r %NEWREV% %STBERRURL% | %ORDER% > %TMPNEWSTBERRF%
svn cat -r %NEWREV% %BLDERRURL% | %ORDER% > %TMPNEWBLDERRF%
svn cat -r %NEWREV% %RUNERRURL% | %ORDER% > %TMPNEWRUNERRF%
svn cat -r %NEWREV% %SPLERRURL% | %ORDER% > %TMPNEWSPLERRF%
if %OPT_V% == 1 ( echo done )

::----------------------------------------------
::  �������Ƃ�
::
if %OPT_V% == 1 ( set /p=taking diff ... < NUL )
set MYDIFFOPT0=%MYDIFFOPT% -p 0
set MYDIFFOPT1=%MYDIFFOPT% -p 1
%MYDIFF% %MYDIFFOPT1% %TMPOLDSTBFILE% %TMPNEWSTBFILE% | %FILTER% %FILTEROPT% > %TMPSTBLOGDIFFFILE%
%MYDIFF% %MYDIFFOPT0% %TMPOLDBLDFILE% %TMPNEWBLDFILE% | %FILTER% %FILTEROPT% > %TMPBLDLOGDIFFFILE%
%MYDIFF% %MYDIFFOPT0% %TMPOLDRUNFILE% %TMPNEWRUNFILE% | %FILTER% %FILTEROPT% > %TMPRUNLOGDIFFFILE%
%MYDIFF% %MYDIFFOPT0% %TMPOLDSPLFILE% %TMPNEWSPLFILE% | %FILTER% %FILTEROPT% > %TMPSPLLOGDIFFFILE%
%MYDIFF% %MYDIFFOPT1% %TMPOLDSTBERRF% %TMPNEWSTBERRF% | %FILTER% %FILTEROPT% > %TMPSTBERRDIFFFILE%
%MYDIFF% %MYDIFFOPT0% %TMPOLDBLDERRF% %TMPNEWBLDERRF% | %FILTER% %FILTEROPT% > %TMPBLDERRDIFFFILE%
%MYDIFF% %MYDIFFOPT0% %TMPOLDRUNERRF% %TMPNEWRUNERRF% | %FILTER% %FILTEROPT% > %TMPRUNERRDIFFFILE%
%MYDIFF% %MYDIFFOPT0% %TMPOLDSPLERRF% %TMPNEWSPLERRF% | %FILTER% %FILTEROPT% > %TMPSPLERRDIFFFILE%
if %OPT_V% == 1 ( echo done )

::----------------------------------------------
::  �Q�l�����쐬����(utf8)
::
if %OPT_V% == 1 ( set /p=converting to utf8 ... < NUL )
%NKF% -w8 %TMPSTBLOGDIFFFILE%	> %STBLOGDIFFFILE%
%NKF% -w8 %TMPBLDLOGDIFFFILE%	> %BLDLOGDIFFFILE%
%NKF% -w8 %TMPRUNLOGDIFFFILE% 	> %RUNLOGDIFFFILE%
%NKF% -w8 %TMPSPLLOGDIFFFILE%	> %SPLLOGDIFFFILE%
rem if %OPT_V% == 1 ( echo done )

::----------------------------------------------
::  ���|�[�g�t�@�C���ɂ܂Ƃ߂�
::     ���������t�s�͏���(pattern is /���t : [0-9]{2}\.[0-9]{2}\.[0-9]{2}/)
::     ������ Shift-JIS �ł���
::
if %OPT_V% == 1 ( set /p=making report file ... < NUL )
echo Report on %DATESTR%				>  %REPORTFILE%
echo old revision: %OLDREV% (%OLDDATE% %OLDTIME%)	>> %REPORTFILE%
echo new revision: %NEWREV% (%NEWDATE% %NEWTIME%)	>> %REPORTFILE%

echo.							>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
echo. StubBuildError.log  				>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
%AWK% -f %BINDIR%\exclude.awk %TMPNEWSTBERRF%		>> %REPORTFILE%

echo.							>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
echo. BuildError.log					>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
%AWK% -f %BINDIR%\exclude.awk %TMPNEWBLDERRF%		>> %REPORTFILE%

echo.							>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
echo. Run.log �̍���					>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
%AWK% -f %BINDIR%\exclude.awk %TMPRUNLOGDIFFFILE%	>> %REPORTFILE%

echo.							>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
echo. SamplesBuildError.log				>> %REPORTFILE%
echo.====================				>> %REPORTFILE%
%AWK% -f %BINDIR%\exclude.awk %TMPNEWSPLERRF%		>> %REPORTFILE%

::----------------------------------------------
::  �G���R�[�f�B���O�� utf8 �ɂ���
::
%NKF% -w8 %REPORTFILE% > %TMPFILE%
copy %TMPFILE% %REPORTFILE%	> NUL
del %TMPFILE% 			> NUL
if %OPT_V% == 1 ( echo done )

::----------------------------------------------
::  ���ʂ����[������
::
if %REPORTBYMAIL% == 1 (
    if %OPT_V% == 1 ( set /p=mailing report file to ... < NUL )
    rem echo From: %MAILFMADDR%		>  %TMPFILE%
    rem echo To: %MAILTOADDR%		>> %TMPFILE%
    rem echo Subject: %MAILSUBJECT%		>> %TMPFILE%
    rem echo 				>> %TMPFILE%
    rem %NKF% -j %REPORTFILE%		>> %TMPFILE%
    rem %SENDMAIL% -t			<  %TMPFILE%
    if %OPT_V% == 1 ( echo done )
)

::----------------------------------------------
::  ��n�������ďI��
::
call :cleanup
exit /b


:: ==============================================
::  ���̃X�N���v�g���I������O�ɕK���Ăяo������
:: ==============================================
:cleanup
    if not %OPT_K% == 1 (
	if %OPT_V% == 1 ( set /p=clean up ... < NUL )
	rem del %STBLOGDIFFFILE%
	rem del %BLDLOGDIFFFILE%
	rem del %RUNLOGDIFFFILE%
	rem del %SPLLOGDIFFFILE%
	set DELLIST=
	for %%f in (%TMPDIR%^\*) do ( set DELLIST=!DELLIST! %%f )
	del !DELLIST!
	if %OPT_V% == 1 ( echo done )
    )
exit /b

:: ===========================================
::  �R�}���h�̎��s���ʂ�ϐ��ɐݒ肷��
::    call :backquote �ϐ��� "�R�}���h"
:: ===========================================
:backquote
    rem echo for /f %%i in ('%2') do set %1=%%i
    for /f %%i in ('%2') do set %1=%%i
exit /b

:: ===========================================
::  �O��̋󔒂���菜��
::    call :trim �ϐ��� ������
:: ===========================================
:trim
    set TRIM_ARG=%2
    set TRIM_ARG=%TRIM_ARG:"=%
    if "%TRIM_ARG%" == "" (
	exit /b
    )
    :trim_again_1
    if "%TRIM_ARG:~0,1%" == " " (
	set TRIM_ARG=%TRIM_ARG:~1%
	goto :trim_again_1
    )
    :trim_again_2
    if "%TRIM_ARG:~-1%" == " " (
	set TRIM_ARG=%TRIM_ARG:~0,-1%
	goto :trim_again_2
    )
    set %1=%TRIM_ARG%
exit /b

:: ====================
::  �g�p���@��\������
:: ====================
:usage
    echo Usage: %PROG% [options] [xxxx:yyyy]
    echo 	xxxx: old-revision-number
    echo 	yyyy: new-revision-number
    echo 	options:
    echo 	  -k:	keep temporary files
    rem echo 	  -m:	mail report to
    echo 	  -h:	show usage
    echo 	  -v:	set verbose mode (default)
    echo 	  -s:	set silent mode
    echo 	  -D n:	set debug level to 'n'
exit /b

:: ======================
::  �I�v�V������\������
:: ======================
:show_options
    echo options:
    if %OPT_K% == 1 echo.  -k
    if %OPT_M% == 1 echo.  -m
    if %OPT_V% == 1 echo.  -v
    if not %OPT_D% == 0 echo.  -D %VAL_D%
    echo.  MYDIFFOPT [%MYDIFFOPT%]
    echo.  FILTEROPT [%FILTEROPT%]
exit /b
