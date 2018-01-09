@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	SetTestEnv [/k] [/a] [/h]
::
::  DESCRIPTION
::	daily_build �̎��s�𐧌䂷�邽�߂́g���ϐ��h�ݒ���s�Ȃ�.
::	�g�p������ϐ��ɂ́A�ړ����gDAILYBUILD_�h��t�^����.
::
::  ARGUMENTS
::	/k	���݂̊��ϐ��l���f�t�H���g�l�Ƃ���
::	/a	�S�X�e�b�v���s���f�t�H���g�l�Ƃ���
::	/h	�g�p���@�̕\��
::     [/b]	��ƃo�b�`�t�@�C�����c�� (for debug)
::
::  CAUTION
::	���ϐ��̎g����
::	�E�ʏ�͂����ň������ϐ��ɂ͉����ݒ肳��Ă��Ȃ����̂Ƃ���
::	�E���ϐ���"skip"�Ɛݒ肵�����̂ݑΉ��������X�L�b�v����
::
::  VERSION
::	Ver 1.0  2013/10/24 F.Kanehori	�o�b�`�t�@�C���̍č\�z
::	Ver 1.1  2013/11/20 F.Kanehori	�V�ϐ������FMAKE_ARCHIVE
::	Ver 1.1a 2013/11/20 F.Kanehori	e/s �� alias �Ƃ��� y/n �𓱓�
::	Ver 1.1b 2014/10/23 F.Kanehori	bug fixed
::	Ver 1.2  2016/06/02 F.Kanehori	�V����ϐ��̓��� (.._ELIMINATE_CLOSED)
::	Ver 1.3  2017/08/07 F.Kanehori	�ύX (.._SPRINGHEAD2 -> .._SPRINGHEAD)
::	Ver 1.4  2017/12/21 F.Kanehori	�ύX (.._COPYTO_TAGS -> .._GEN_HISTORY)
::	Ver 1.5  2017/12/25 F.Kanehori	TestAll ���s�����ύX
:: ============================================================================
set PROG=%~n0

::----------------------------------------------
:: ����p���ϐ����ʐړ����̒�`
::
set PREFIX=DAILYBUILD_

::----------------------------------------------
:: �g�p������ϐ��̒�`�i%PREFIX%�������������j
::
rem for TestMain.bat
set ENVMAIN1=%PREFIX%UPDATE_SPRINGHEAD %PREFIX%CLEANUP_WORKSPACE %PREFIX%ELIMINATE_CLOSED
set ENVMAIN2=%PREFIX%EXECUTE_MAKEDOC %PREFIX%COPYTO_WEBBASE
rem for TestALL.bat
set ENVTEST1=%PREFIX%EXECUTE_STUBBUILD %PREFIX%EXECUTE_BUILDRUN %PREFIX%EXECUTE_SAMPLEBUILD
set ENVTEST2=%PREFIX%GEN_HISTORY %PREFIX%COPYTO_BUILDLOG
::
:: (these are SVN version only)
rem set ENVMAIN2=%PREFIX%EXECUTE_MAKEDOC %PREFIX%COPYTO_WEBBASE %PREFIX%MAKE_ARCHIVE
rem set ENVTEST2=%PREFIX%GEN_HISTORY %PREFIX%COMMIT_BUILDLOG %PREFIX%COPYTO_BUILDLOG
::
set ENV_ALL=%ENVMAIN1% %ENVTEST1% %ENVTEST2% %ENVMAIN2%
set ENVMAIN=%ENVMAIN1% %ENVMAIN2%
set ENVTEST=%ENVTEST1% %ENVTEST2%
set ENVEXEC=%PREFIX%EXECUTE_TESTALL
::
call :max_length LEN %ENV_ALL% %ENVEXEC%
set MAXWIDTH=%LEN%

::----------------------------------------------
:: �I�v�V�����ϐ��̏����l
::
set EXECUTE_ALL=
set KEEP_VALUES=

::----------------------------------------------
:: �����̏���
::
call :get_args %*
if not %$status% == 0 goto :done
rem echo EXECUTE_ALL: [%EXECUTE_ALL%]
rem echo KEEP_VALEUS: [%KEEP_VALUES%]

::----------------------------------------------
:: ���ϐ��̏����ݒ�
::
for %%v in (%ENV_ALL% %ENVEXEC%) do (
    if "%KEEP_VALUES%" equ "yes" (
	    set VAR=%%v
	    call set VAL=%%!VAR!%%
	    set VALUES[%%v]=!VAL!
    ) else if "%EXECUTE_ALL%" equ "yes" (
	    set VALUES[%%v]=
    ) else (
	    set VALUES[%%v]=skip
    )
)
echo �����l�͎��̂Ƃ���
call :show STDOUT

::----------------------------------------------
:: ���s�w��̓���
::
echo.
echo ���s������̂����I��ł������� [e^(xec^)/s^(kip^)]
for %%v in (%ENVMAIN1%) do (call :input %%v)
echo.
for %%v in (%ENVTEST1%) do (call :input %%v)
for %%v in (%ENVTEST2%) do (call :input %%v)
echo.
for %%v in (%ENVMAIN2%) do (call :input %%v)

::----------------------------------------------
:: TestAll ���s�̔���
::
set COUNT=0
for %%v in (%ENVTEST1% %ENVTEST2%) do (
    set VAL=VALUES[%%v]
    call set VAL=%%!VAL!%%
    if "!VAL!" neq "skip" set /a COUNT+=1
)
if %COUNT% equ 0 (
    set VALUES[%ENVEXEC%]=skip
) else (
    set VALUES[%ENVEXEC%]=
)

::----------------------------------------------
:: �m�F
::
echo.
echo �w�肳�ꂽ�p�����[�^�͎��̂Ƃ���ł�.
call :show STDOUT

echo.
set YN=
:try_again
set /p YN="�w�肵���l��ݒ肵�܂���[y/n] ? "
if /i "%YN%" neq "y" if /i "%YN%" neq "n" goto :try_again
::
:: ���ϐ��̐ݒ�͊O���̍�ƃo�b�`�t�@�C������čs�Ȃ�.
::   �o�b�`�t�@�C���̎��s���ƍ폜���ɂ��t�@�C�������w�肷��K�v�����邪,
:: �@�r���ł�������O���[�o���X�R�[�v�ɔ����邽��,
::   �����Őݒ肵���t�@�C�����͂��̎��_�Ŗ����ƂȂ��Ă��܂�.
:: �@�ēx�t�@�C�������w�肷��Ƃ���, �����ł̎w��Ɩ������Ȃ��悤���ӂ��K�v.
::   (169�s�ڋy��170�s��)
::
set BATFILE=%~n0.tmp.bat
if exist %BATFILE% del %BATFILE%

if /i "%YN%" neq "y" (
    set MSG=�ݒ�͈ȑO�̂܂܂ł�.
    set CMD=rem set
) else (
    set MSG=���̂悤�ɐݒ肵�܂���.
    set CMD=set
)

echo @echo off > %BATFILE%
for %%v in (%ENV_ALL% %ENVEXEC%) do (
    set VAL=VALUES[%%v]
    call set VAL=%%!VAL!%%
    echo %CMD% %%v=!VAL!>> %BATFILE%
)
echo echo. >> %BATFILE%
echo echo %MSG%>> %BATFILE%
call :show %BATFILE%
echo exit /b>> %BATFILE%
echo :display_string >> %BATFILE%
echo if "%%2" equ "skip" ^(>> %BATFILE%
echo.  set %%1=.... skip>> %BATFILE%
echo ^) else ^(>> %BATFILE%
echo.  set %%1=exec>> %BATFILE%
echo ^)>> %BATFILE%
echo exit /b>>%BATFILE%

::----------------------------------------------
:: ��ƃo�b�`�t�@�C���̎��s�ƍ폜
:: �@�o�b�`�t�@�C���̓O���[�o���X�R�[�v�Ŏ��s����.
::   �Ăяo���o�b�`�t�@�C������, 133�s�ڂŎw�肵������(BATFILE)��
::   �������Ȃ��悤�ɒ��ӂ��邱��.
::
endlocal
call %~n0.tmp.bat
del %~n0.tmp.bat
setlocal

:: �I��
::
set $status=0
:done
endlocal && set $status=%$status%
exit /b

::------------------------------------------------------------------------------
::------------------------------------------------------------------------------
:: �R�}���h�����̏���
::
:get_args
    set $status=0
:get_args_loop
    if "%1" equ "" goto :get_args_exit
    if /i "%1" equ "/a" ((set EXECUTE_ALL=yes) && shift && goto :get_args_loop)
    if /i "%1" equ "/k" ((set KEEP_VALUES=yes) && shift && goto :get_args_loop)
    if /i "%1" equ "/h" (call :usage && goto :get_args_exit)
    echo bad arg [%1] && set $status=-1 && shift
    goto :get_args_loop
:get_args_exit
exit /b

::----------------------------------------------
:: ���ϐ��l�̕\��
::	arg1:	STDOUT: ��ʂɕ\��
::		���̑�: �t�@�C���ɏo��
::
:show
    setlocal
    set OUTTO=%1
    set /a MAX_MAIN=%MAXWIDTH%+1
    set /a MAX_TEST=%MAX_MAIN%-2
    call :values_dump %OUTTO% 2 %MAX_MAIN% %ENVMAIN1%
    call :values_dump %OUTTO% 2 %MAX_MAIN% %ENVEXEC%
    call :values_dump %OUTTO% 4 %MAX_TEST% %ENVTEST1%
    call :values_dump %OUTTO% 4 %MAX_TEST% %ENVTEST2%
    call :values_dump %OUTTO% 2 %MAX_MAIN% %ENVMAIN2%
    endlocal
exit /b

::----------------------------------------------
:: ���s�w��̓��͏���
::	arg1:	���ϐ���
::	���͂����l��, VALUES[arg1] �Ɋi�[�����
::
:input
    setlocal
    set VAR=%1
    set VAL=VALUES[%VAR%]
    call set VAL=%%%VAL%%%
    if not defined VAL set VAL=exec
    call :fixlen VAR %MAXWIDTH%
    call :fixlen VAL 4
    set YN=
    set /p YN=%VAR% (%VAL%)? 
    set RET=%VAL%
    if /i "%YN%" equ "e" (
	    set RET=
    ) else if /i "%YN%" equ "y" (
	    set RET=
    ) else if /i "%YN%" equ "s" (
	    set RET=skip
    ) else if /i "%YN%" equ "n" (
	    set RET=skip
    ) else if "%KEEP_VALUES%" neq "yes" (
	    set RET=skip
    )
    endlocal && set VALUES[%1]=%RET%
exit /b

:: ----------------------------------------------------
::  �ϐ��Ɏw�肵�����̋󔒕������ݒ肷��
::	arg1:	�ϐ��� <$string>
::	arg2:	�󔒂̐�
:: 
:spaces
    setlocal
    set VAR=$string
    set CHK=%2
    if defined CHK set VAR=%1&&shift
    set $result=
    for /l %%n in (1,1,%1) do set $result= !$result!
    endlocal && call set %VAR%=%$result%
exit /b

:: ----------------------------------------------------
::  �ϐ��̓��e���w�肵�������ɒ�������
::	arg1:	�ϐ���
::	arg2:	����
::     [arg3:]	�z�u�i'left' or 'right') <'left'>
::     [arg4:]	�[�U������ <�󔒕�����>
:: 
:fixlen
    setlocal
    set SPACES=%4
    if not defined SPACES call :spaces SPACES %2
    if "%3" equ "right" (
	call set $string=%SPACES%%%%1%%
	    set CMD=$string:~-%2
    ) else (
	    call set $string=%%%1%%%SPACES%
	    set CMD=$string:~0,%2
    )
    call set $string=%%!CMD!%%
    endlocal && set %1=%$string%
exit /b

:: ----------------------------------------------------
::  �ϐ��̒��������߂�
::     [arg1]:	�l��Ԃ��ϐ����i�ȗ��F�ȗ����� $result�j
::	arg2:	�ϐ���
:: 
:strlen
    setlocal
    set RET=%1
    set STR=%2
    if not defined STR (
	    set RET=$result
	    set STR=%1
    )
    set LEN=0
:strlen_loop
    if defined STR (
	    set /a LEN+=1
	    set STR=!STR:~0,-1!
	    goto :strlen_loop
    )
    endlocal && set %RET%=%LEN%
exit /b

::----------------------------------------------
:: �ϐ��l�̕\��
::	arg1:	���C���f���g��
::	arg2:	�ϐ����ő啝 (0=�ő�ϐ���)
::	arg3:	�ϐ��̃��X�g
::
:values_dump
    setlocal
    set OUTTO=%1&& shift
    set INDENT=%1&& shift
    rem set /a MAXWIDTH=%1+2 && shift
    set MAXWIDTH=%1 && shift
    set LIST=%1 && shift
:values_dump_loop
    if "%1" neq "" (
	    set LIST=!LIST! %1
	    shift
	    goto :values_dump_loop
    )
    if %MAXWIDTH% leq 0 call :max_length MAXWIDTH %LIST%
        set /a MAXWIDTH+=2
        call :spaces SPACES %INDENT%
        if "%OUTTO%" equ "STDOUT" (
	        for %%v in (%LIST%) do (
	            set VAR=%%v
	            call :fixlen VAR %MAXWIDTH%
		        set VAL=VALUES[%%v]
		        call set VAL=%%!VAL!%%
		        call :display_string STR !VAL!
		        echo %SPACES%!VAR! !STR!
	        )
        ) else (
	    echo setlocal enabledelayedexpansion>> %OUTTO%
	    for %%v in (%LIST%) do (
	        set VAR=%%v
	        call :fixlen VAR %MAXWIDTH%
	        echo set VAL=%%%%v%%>> %OUTTO%
	        echo call :display_string STR %%VAL%%>> %OUTTO%
	        rem echo echo %SPACES%!VAR! %%%%v%% >> %OUTTO%
	        echo echo %SPACES%!VAR! %%STR%%>> %OUTTO%
	    )
	    echo endlocal>> %OUTTO%
    )
    endlocal
exit /b

::----------------------------------------------
:: �ő啶���񒷂����߂�
::	arg1:	���ʂ��i�[����ϐ���
::	arg2..:	�ϐ����̃��X�g
::
:max_length
    setlocal
    set VAR=%1&& shift
    set LIST=
:max_length_loop
    if "%1" neq "" (
	    set LIST=!LIST! %1
	    shift
	    goto :max_length_loop
    )
    set LIST=%LIST:~1%
    set MAXLEN=0
    for %%v in (%LIST%) do (
	    call :strlen LEN %%v
	    if !LEN! gtr !MAXLEN! set MAXLEN=!LEN!
    )
    rem set /a MAXLEN+=1
    endlocal && set %VAR%=%MAXLEN%
exit /b

::----------------------------------------------
:: ���ϐ��l�\��������̍쐬
::	arg1:	���ʂ��i�[����ϐ���
::	arg2:	���ϐ��l
::
:display_string
    if "%2" equ "skip" (
	    set %1=.... skip
    ) else (
	    set %1=exec
    )
exit /b

::----------------------------------------------
:: �g�p���@�̕\��
::
:usage
    echo Usage: %PROG% [/a] [/k] [/h]
    echo.        /a      Executes all steps.
    echo.        /k      Use current values as a base set.
    echo.        /h      Print this.
    set $status=-1
exit /b
