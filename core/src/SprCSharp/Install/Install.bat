@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	Install src-path dst-path [dry-run]
::
::  DESCRIPTION
::	src-path �Ŏw�肵���t�@�C���� dst-path �ɃR�s�[����.
::	������, dst-path ��u���ׂ��f�B���N�g�������݂��Ȃ���Ή������Ȃ�.
::
::  ARGUMENTS
::	src-oath	�R�s�[���̃t�@�C���p�X
::	dst-path	�R�s�[��̃f�B���N�g���p�X�܂��̓t�@�C���p�X
::	control		�o�ߑ[�u�p�����F
::			    "copy" �ȊO���w�肷��ƃR�s�[�͍s�Ȃ�Ȃ�.
::
::  VERSION
::	Ver 1.0  2017/08/09 F.Kanehori	����
::	Ver 1.1  2017/11/08 F.Kanehori	�R�s�[��f�B���N�g�����Ȃ���΍쐬����.
:: ============================================================================
set PROG=%~n0

::----------------------------------------------
:: �����̏���
::----------------------------------------------
set SRC=%~1
set DST=%~2
set COPYCONTROL=%3
if "%SRC%" == ""    ( call :usage && exit /b )
if "%DST%" == ""    ( call :usage && exit /b )
if exist %SRC%\	    ( call :error '%1' is not a file && exit /b )
if not exist %SRC%  ( call :error '%1': no such file && exit /b )

if exist %DST%\ (
	set DST_DIR=%DST%
	set DST=%DST%\%~nx1
) else (
	set DST_DIR=%~dp2
)

::----------------------------------------------
:: �R�s�[��̃f�B���N�g�����Ȃ���΍쐬����
::----------------------------------------------
if not exist %DST_DIR% (
	echo creating directory "%DST_DIR%"
	mkdir %DST_DIR%
)

::----------------------------------------------
:: �R�s�[�̎��s
::----------------------------------------------
set DO_COPY=
if "%COPYCONTROL%" == ""	set DO_COPY=yes
if "%COPYCONTROL%" == "copy"	set DO_COPY=yes

if "%DO_COPY%" == "yes" ( 
	echo copying %SRC% to %DST%
	copy %SRC% %DST% > NUL 2>&1
)
exit /b


::----------------------------------------------
:: �G���[���b�Z�[�W�Ǝg�p���@���o�͂���
::----------------------------------------------
:error
	echo Error: %*
	echo.
	call :usage
exit /b 

::----------------------------------------------
:: �g�p���@���o�͂���
::----------------------------------------------
:usage
	echo Usage: %PROG% src-path dst-path
	echo     src-path:    file path to be copied.
	echo     dst-path:    file path or dorectory path to copy.
exit /b

::end: Install.bat
