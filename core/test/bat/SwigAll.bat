@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	SwigAll toolset_id configuration platform
::
::  DESCRIPTION
::	daily_build �ɂ����āA���̂��ׂẴv���W�F�N�g�̃r���h�ɐ旧���ĕK�v��
::	*stub.cpp ���쐬���邽�߂̃X�N���v�g.
::
::	������ RunSwig �v���W�F�N�g (make �v���W�F�N�g) �ōs�Ȃ����߁Astub ��
::	�쐬���K�v�ƂȂ�v���W�F�N�g�ɂ��ẮA���̂��Ƃ����Ă�������.
::	  (1) �v���W�F�N�g�̈ˑ��֌W: RunSwig �v���W�F�N�g�Ɉˑ�������.
::	  (2) �����̑ΏۂƂȂ�v���W�F�N�g�����A���̃t�@�C���ɋL�q����.
::		$(ETCDIR)/swigprojs.list
::	�L�q�́A�e�v���W�F�N�g1�s���Ƃ���.
::	���̃t�@�C����(="swigprojs.list")�́A���̃X�N���v�g���ŕύX�ł���.
::		$(BINDIR)/do_swigall.bat
::
::	����ł͎��̂悤�ɂȂ��Ă���.
::		$(BINDIR) = .../Springhead2/src/swig/bin
::		$(ETCDIR) = .../Springhead2/src/swig/etc
::	
::	�����̓��e�ɂ��ẮAmake �v���W�F�N�g���Q�Ƃ̂���.
::		�� ���ۂ̏����� $(BINDIR)/do_swigall.bat ���s�Ȃ�.
::
::  ARGUMENTS
::	toolset_id	�c�[���Z�b�g�̎��� { 10.0 | 11.0 | .. }
::	configuration	�r���h�\�� { Debug | Release | .. }
::	platform	�r���h�v���b�g�t�H�[�� { Win32 | x64 }
::
::  VERSION
::	Ver 1.0	  2012/10/17	F.Kanehori
::	Ver 1.0a  2012/11/14	F.Kanehori  ���̃X�N���v�g�̊i�[�ꏊ��ύX
::					    PATH�̐ݒ�̕ύX (x64�łɂ��Ή�)
::	Ver 1.0b  2012/11/21	F.Kanehori  �X�N���v�g�̊i�[�ꏊ�����ɖ߂���
::					    PATH�̐ݒ�̕ύX (�G���[�����ǉ�)
::	Ver 2.0	  2013/09/11	F.Kanehori  �o�b�`�t�@�C���̍č\��
::	Ver 2.1	  2013/12/05	F.Kanehori  Visual Studio 2008 �Ή�
::	Ver 2.1a  2016/06/02	F.Kanehori  �R�}���h���C���������O�ɏo��
:: ============================================================================
call :leaf_name PROG %0
set CWD=%cd%

::----------------------------------------------
:: �����̏���
::
set TOOLSET_ID=%1
set CONFIGURATION=%2
set PLATFORM=%3

set ARGS=TOOLSET_ID CONFIGURATION PLATFORM
for %%a in (%ARGS%) do (
	if "!%%a!" equ "" (echo %PROG%: missing argument %%a && exit /b -1)
)

if "%TOOLSET_ID%" equ "9" set TOOLSET_ID=9.0
if "%TOOLSET_ID%" equ "10" set TOOLSET_ID=10.0
set SOLUTIONFILE_ID=%TOOLSET_ID%
if "%SOLUTIONFILE_ID%" equ "9.0" set SOLUTIONFILE_ID=9
if "%SOLUTIONFILE_ID%" equ "10.0" set SOLUTIONFILE_ID=10

rem ------------------------------
rem  �K�v�ȃp�X�̐ݒ�
rem 
set DEVENVPATH=Microsoft Visual Studio %TOOLSET_ID%\Common7\IDE
set X64PATH="C:\Program Files (x86)\%DEVENVPATH%"
set X32PATH="C:\Program Files\%DEVENVPATH%"
set PROG=devenv.exe
set MAKEPATH=..\bin;.\bin\swig
if exist "%X32PATH:"=%\%PROG%" set PATH=%MAKEPATH%;%X32PATH:"=%;%DEVENVPATH%;%PATH%
if exist "%X64PATH:"=%\%PROG%" set PATH=%MAKEPATH%;%X64PATH:"=%;%DEVENVPATH%;%PATH%
rem if exist "%X32PATH:"=%\%PROG%" echo System: 32 bits
rem if exist "%X64PATH:"=%\%PROG%" echo System: 64 bits

set SOLUTIONDIR=..\src
set SOLUTIONFILE=Springhead%SOLUTIONFILE_ID%.sln
set SOLUTION=%SOLUTIONDIR%\%SOLUTIONFILE%

set BUILD_OPTION="%CONFIGURATION%|%PLATFORM%"
echo [ SwigAll.bat ]
echo %% devenv %SOLUTION% /build %BUILD_OPTION%
devenv %SOLUTION% /Build %BUILD_OPTION%

endlocal
exit /b


::----------------------------------------------
:: ���[�t���̎�o��
::	arg1:	�l��Ԃ����ϐ���
::	arg2:	�p�X��
::
:leaf_name
	set %1=%~n2
exit /b
::end SwigAll.bat
