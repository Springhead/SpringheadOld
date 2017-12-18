@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	TestMainGit [/t toolset_id] [/c config] [/p platform] [/h]
::
::  DESCRIPTION
::	dailybuild �����s����.
::	
::  ARGUMENTS
::	/t toolset_id	�c�[���Z�b�g�̎��� { 14.0 <default> | .. }
::	/c config	�r���h�\�� { Debug | Release <default> | .. }
::	/p platform	�r���h�v���b�g�t�H�[�� { Win32 | x64 <default> }
::	/r repository	�e�X�g���|�W�g���w��
::	/h              �g�p���@�̕\��
::
::  VERSION
::	Ver 1.0  2017/12/03 F.Kanehori	GitHub ���Ή��ŁiPython�ł����܂Łj�B
::	Ver 1.1  2017/12/18 F.Kanehori	Springhead �}�j���A���쐬�ǉ�
:: ============================================================================
set PROG=%~n0
set CWD=%cd%

::----------------------------------------------
:: �����̏���
::
set TOOLSET_ID=14.0
set CONFIGURATION=Release
set PLATFORM=x64
set TEST_REPOSITORY=SpringheadTest
call :get_args %*
if not %$status% == 0 (
    goto :done
)
echo Test parameters:
echo.   TOOLSET_ID:      [%TOOLSET_ID%]
echo.   CONFIGURATION:   [%CONFIGURATION%]
echo.   PLATFORM:        [%PLATFORM%]
echo.   TEST_REPOSITORY: [%TEST_REPOSITORY%]

::----------------------------------------------
:: �e�X�g���|�W�g���̃`�F�b�N
::
if not exist ..\..\..\%TEST_REPOSITORY% (
    echo %PROG%: test repository "%TEST_REPOSITORY%" does not exist!
    set $status=-1
    goto :done
)
cd ..\..\..\%TEST_REPOSITORY%

::----------------------------------------------
:: �r���h�ƃe�X�g�͎��̃t�H���_�ōs�Ȃ�
::
set MAYBE_EMPTY=0
if not exist core\test       set MAYBE_EMPTY=1
if not exist core\test\bat   set MAYBE_EMPTY=1
if %MAYBE_EMPTY% == 1 (
    echo %PROG%: test repository "%TEST_REPOSITORY%\core" may be empty
    set $status=%ERRORLEVEL%
    goto :done
)

::----------------------------------------------
:: ���J�ł��Ȃ��t�@�C���̍폜�Ɛݒ�ύX
::
call :check_condition DAILYBUILD_ELIMINATE_CLOSED
if %$status% == 0 (
    rem echo removing closed files
    rem del /F /S /Q closed
    echo unset USE_CLOSED_SRC flag
    echo #undef USE_CLOSED_SRC > core/include/UseClosedSrcOrNot.h
)

::----------------------------------------------
:: �e�X�g���s�Ȃ�
::
cd core\test
call :check_condition DAILYBUILD_EXECUTE_TESTALL
if %$status% == 0 (
    call bat\TestAllGit.bat %TOOLSET_ID% %CONFIGURATION% %PLATFORM% %TEST_REPOSITORY%
    if not !$status! == 0 (
	goto :done
    )
)

::----------------------------------------------
:: �h�L�������g(doxygen)�����
::
call :check_condition DAILYBUILD_EXECUTE_MAKEDOC
if %$status% == 0 (
    echo making documents
    call bat\MakeDoc.bat

    path="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin";%path%
    cd ..\doc\SprManual
    make
    cd ..\..\test
)

::----------------------------------------------
:: dailybuild �Ő������ꂽ�t�@�C���� Web �ɃR�s�[
::
set WEBBASE=\\haselab\HomeDirs\WWW\docroots\springhead\dailybuild_generated

call :check_condition DAILYBUILD_COPYTO_WEBBASE
if %$status% == 0 (
    echo copying generated files to web

    cd ..\..\generated
    set DIRLIST=bin doc lib
    set FILELIST=
    echo DIRLIST:  [!DIRLIST!]
    echo FILELIST: [!FILELIST!]
    for %%d in (!DIRLIST!) do call :copy_dir %%d !WEBBASE!
    for %%f in (!FILELIST!) do call :copy_file %%f !WEBBASE!
    cd ..\core\test
)

::----------------------------------------------
:: OK
::
set $status=0
echo done.

::----------------------------------------------
:: �����I��
::
:done
endlocal && set $status=%$status%
exit /b


::=============================================================================
::----------------------------------------------
:: �R�}���h�����̏���
::
:get_args
    set $status=0
:get_args_loop
    if "%1" equ "" goto :get_args_exit
    if /i "%1" equ "/t" ((set TOOLSET_ID=%2) && shift && shift && goto :get_args_loop)
    if /i "%1" equ "/c" ((set CONFIGURATION=%2) && shift && shift && goto :get_args_loop)
    if /i "%1" equ "/p" ((set PLATFORM=%2) && shift && shift && goto :get_args_loop)
    if /i "%1" equ "/r" ((set TEST_REPOSITORY=%2) && shift && shift && goto :get_args_loop)
    if /i "%1" equ "/h" (call :usage && set $status=-1 && goto :get_args_exit)
    echo bad arg [%1] && set $status=-1 && shift
    goto :get_args_loop
:get_args_exit
exit /b

::----------------------------------------------
:: �f�B���N�g���S�̂̃R�s�[
::
:copy_dir
    echo copying directory %cd%\%1\ to %2\%1\
    if "%1" neq "" (
	rem rmdir /s /q %2\%1 > NUL
	if exist %2\%1 (
		cd %2\%1
		for /f %%d in ('dir /ad /b /w *') do rmdir /s /q %%d
		del /f /q *
		cd ..\..
	)
	xcopy /e/c/f/h/i/y %1 %2\%1 > NUL
    )
exit /b

::----------------------------------------------
:: �t�@�C���̃R�s�[
::
:copy_file
    echo copying file %cd%\%1 to %WEBBASE%\%1
    if "%1" neq "" (
	del %WEBBASE%\%1 > NUL
	copy /y %1 %WEBBASE%\%1 > NUL
    )
exit /b

::----------------------------------------------
:: ���ϐ��ɂ����s����
::	arg1:	���s������ϐ���
::
:check_condition
    setlocal
    set RET=0
    call set VAL=%%%1%%
    if "%VAL%" equ "skip" (
	if "%2" neq "silent" (
	    echo skip ..%1..
	)
	set RET=-1
    ) 
    endlocal && set $status=%RET%
exit /b

::----------------------------------------------
:: �g�p���@�̕\��
::
:usage
    echo Usage: %PROG% [/t toolset] [/c config] [/p platform] [/h]
    echo        /t toolset         �c�[���Z�b�g�̎��� { 14.0 ^<default^> ^| .. }
    echo        /c configuration   �r���h�\�� { Debug ^| Release ^<default^> ^| .. }
    echo        /p platform        �r���h�v���b�g�t�H�[�� { Win32 ^| x64 ^<default^>}
    echo        /r                 �e�X�g���|�W�g�� (SpringheadTest ^<default^>)
    echo        /h                 �g�p���@�̕\��
exit /b

::end TestMainGit.bat
