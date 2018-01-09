@echo off
:: ***********************************************************************************
::  File:
::	CSharpSwig.bat
::
::  SYNOPSIS:
::	CSharpSwig module [swigmacro]
::
::  ARGUMENTS:
::	module		���W���[����
::	swigmacro	swig �ɓn���}�N���i#ifdef swigmacro �Ƃ��Ďg���j
::
::  Description:
::	Springhead �̃��C�u����(DLL) �� C# ���痘�p���邽�߂̃R�[�h�𐶐�����B
::
:: ***********************************************************************************
::  Version:
::	Ver 1.0	 2015/01/26 F.Kanehori  ����
::	Ver 2.0	 2016/02/08 F.Kanehori  wrapper file ����
::	Ver 3.0	 2016/12/01 F.Kanehori  �^�[�Q�b�g�w�����
::	Ver 3.1  2016/12/15 F.Kanehori	���b�p�t�@�C���쐬�����ύX
::	Ver 3.2	 2017/01/16 F.Kanehori	NameManger ����
:: ***********************************************************************************
setlocal enabledelayedexpansion
set PROG=%~n0
set CWD=%cd%
set DEBUG=1

if %DEBUG% == 1 (
    set CS_INFO=SprInfo
    if not exist !CS_INFO! mkdir !CS_INFO!
)

set MODULE=%1
if "%MODULE%" equ "" (
    echo %PROG%: Error: Module name MUST be specified.
    exit /b
)
set MACRO=%2
if "%MACRO%" neq "" set MACRO=-D%MACRO%

set DUMPTREE=0
if "%1" equ "dumptree" set DUMPTREE=1

if %DEBUG% == 1 (
    echo %~nx0
    echo MODULE: [%MODULE%]
    echo MACRO:  [%MACRO%]
)

:: ------------------------
::  ���ʊ��ϐ���ǂݍ���
:: ------------------------
call .\NameManager\NameManager.bat
echo. 
echo *** %MODULE% ***
echo using src directory: %SRCDIR%

:: ----------
::  �e���`
:: ----------
set PATH=%SWIGDIR%;%PATH% 
set ARGS=-sprcs -DSWIG_CS_SPR -c++ -I%SWIGPATH%\Lib -w305,312,319,325,401,402

:: ----------
::  �����J�n
:: ----------
if exist %MODULE%.i (
    if %DUMPTREE% == 1 (
        cmd /c %SWIG% -debug-module 4 %MODULE%.i > CS%MODULE%.tree
    ) else (
	cmd /c %SWIG% %ARGS% -DSWIG_%MODULE% %MACRO% %MODULE%.i
	move /Y %MODULE%Cs.cs  %CS_SRC%\CS%MODULE%.cs  > NUL 2>&1
	move /Y %MODULE%CsP.cs %CS_IMP%\CS%MODULE%.cs  > NUL 2>&1
	move /Y %MODULE%Cs.cpp %CS_EXP%\CS%MODULE%.cpp > NUL 2>&1
	echo %SUBDIR_SRC%\CS%MODULE%.cs  created
	echo %SUBDIR_IMP%\CS%MODULE%.cs  created
	echo %SUBDIR_EXP%\CS%MODULE%.cpp created
	if %DEBUG% == 1 (
	    move /Y %MODULE%CS.info %CS_INFO%\CS%MODULE%.info >NUL 2>&1
	) else (
	    del %MODULE%CS.info 2>NUL
	)
	type NUL > %WRAPPERSBUILTFILE%
    )
) else (
    echo "%MODULE%.i" not found
)
echo. 

:: ----------
::  �����I��
:: ----------
endlocal
exit /b

::end CSharpSWig.bat
