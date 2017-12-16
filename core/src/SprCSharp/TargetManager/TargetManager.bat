@echo off
:: ***********************************************************************************
::  FILE:
::      TargetManager.bat
::
::  SYNOPSIS:
::	TargetManager target
::	    target:		�^�[�Q�b�g��
::
::  DESCRIPTION:
::      �t�@�C��"target.last"�ɋL�^���ꂽ�^�[�Q�b�g���ƈ����Ŏw�肳�ꂽ�^�[�Q�b�g��
::	�Ƃ��قȂ��Ă����Ȃ�΁A�^�[�Q�b�g RunSwig_CSharp ����������t�@�C�����폜
::	���邱�Ƃł��̃^�[�Q�b�g���K�����s�����悤�ɂ���.
::
:: ***********************************************************************************
::  Version:
::	Ver 1.0	 2016/12/07 F.Kanehori	����
::	Ver 1.1	 2017/01/16 F.Kanehori	NameManger ����
::	Ver 1.1a 2017/01/18 F.Kanehori	Bug fixed.
:: ***********************************************************************************
setlocal enabledelayedexpansion
set PROG=%~n0
set DEBUG=1

:: ------------
::  �����̏���
:: ------------
set TARGET=%1
if "%TARGET%" equ "" (
	echo %PROG%: Error: missing arg "target"
	echo.
	call :usage
	exit /b
)

:: ------------------------
::  ���ʊ��ϐ���ǂݍ���
:: ------------------------
call ..\NameManager\NameManager.bat
if %DEBUG% == 1 (
	echo TARGET FILE:  %TARGETFILE%
	echo CLEAN SCRIPT: %CSHARPCLEAN%
)

:: ----------------------------------
::  �L�^���ꂽ�^�[�Q�b�g����ǂݏo��
:: ----------------------------------
for /f %%t in (%TARGETFILE%) do set LASTTARGET=%%t
if %DEBUG% == 1 echo LASTTARGET: %LASTTARGET%

:: --------------------------
::  ��r���s�Ȃ����������߂�
:: --------------------------
if "%TARGET%" equ "%LASTTARGET%" (
	:: ��v�����̂ŉ������Ȃ��ėǂ�
	echo %PROG%: %LASTTARGET% -^> %TARGET%
) else (
	:: �قȂ����̂Ńt�@�C���̍폜���s�Ȃ�
	echo %PROG%: %LASTTARGET% -^> %TARGET%, clearing files
	%CSHARPCLEAN% 
)

:: ----------
::  �����I��
:: ----------
endlocal
exit /b

:: -----------------------------------------------------------------------------------
:: -----------------------------------------------------------------------------------
:usage
	echo Usage: %PROG% target
	echo            target:	ALL ^| Physics ^| ...
exit /b

::end TargetManager.bat
