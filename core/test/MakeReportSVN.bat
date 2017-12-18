@echo off
setlocal enabledelayedexpansion
:: ==============================================================================
::  SYNOPSIS
::	MakeReport [-k] [-h] [-v] [-s] [-D level]
::
::  DESCRIPTION:
::	daily_build �̃��|�[�g�t�@�C�����쐬����. ���̃R�}���h�����[�J���œ���
::	����K�v������ (������ bin �f�B���N�g���ɒu������).
::	    gawk.exe	( awk �̑�֕��Ȃ�Ȃ�ł��悢 )
::	    nkf.exe
::
::  VERSION:
::	Ver 1.0	 2012/11/03 F.Kanehori	���� (Unix �ďo����)
::	Ver 2.0  2013/02/07 F.Kanehori	Windows �ڐA����
::	Ver 3.0  2017/10/18 F.Kanehori	�V���|�W�g���\���Ή�
::	Ver 3.1  2017/11/22 F.Kanehori	�J�n/�I��������\��
::	Ver 3.11 2017/12/06 F.Kanehori	Bug fixed
:: ==============================================================================
set PROG=%~n0
echo %PROG%: started at %date% %time%

::----------------------------------------------
::  ���ʂ̏����v���O�����ɓn���I�v�V����
::    -k  ��ƃt�@�C�����c��
::    -V  �o�[�o�X���o�́i�f�t�H���g�j
::    -D  �f�o�b�O���o��
::  ���̃o�b�`�X�N���v�g�Ŏg�p����I�v�V����
::    -c  ���|�[�g�t�@�C�����E�F�u�ɃR�s�[����
::    -h  �g�p���@�̕\��
::    -v  �o�[�o�X���o�́i�f�t�H���g�j
::    -s  �o�[�o�X���o�͗}���i�S�X�N���v�g�j
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
::  ���t���̎擾
::
set YYYY=%DATE:~0,4%
set MM=%DATE:~5,2%
set DD=%DATE:~8,2%
set TODAY=%YYYY%-%MM%%DD%

::----------------------------------------------
::  �g�p����v���O����
::
set BASEDIR=.\Monitoring
set BINDIR=.\bin
set CMND=build_monitor_SVN

::----------------------------------------------
::  ���[�J���z�X�g��ŃR�}���h�����s
::
set CWD=%cd%
cd %BASEDIR%
cmd /c %BINDIR%\%CMND% %ARGS%
cd %CWD%

::----------------------------------------------
::  �R�s�[��/��̃f�B���N�g���̒�`
::
set SELFPATH=%~dp0
set REPBASE=%SELFPATH%report
set WEBBASE=\\haselab\HomeDirs\WWW\docroots\springhead\daily_build
set WEBREPT=%WEBBASE%\report

::----------------------------------------------
::  �E�F�u�ɃR�s�[����t�@�C���̒�`
::
set REPFILE=%TODAY%.report
set BLDDIFF=%TODAY%.bldlog.diff
set STBDIFF=%TODAY%.stblog.diff
set RUNDIFF=%TODAY%.runlog.diff
set SPLDIFF=%TODAY%.spllog.diff

:: �E�F�u��ł̖���
::
set WEB_REPFILE=Test.report
set WEB_BLDDIFF=Build.log.diff
set WEB_STBDIFF=StubBuild.log.diff
set WEB_RUNDIFF=Run.log.diff
set WEB_SPLDIFF=SamplesBuild.log.diff

::----------------------------------------------
::  �E�F�u�ɃR�s�[
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
::  ���[�J���̃t�@�C�����폜
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
::  �g�p���@�̕\��
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
