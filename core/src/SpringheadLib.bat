@echo off
setlocal enabledelayedexpansion
rem ===========================================================================
rem @echo ���C�u�������}�[�W���܂��DVisualC++�̃��C�u�����Ǘ��c�[�� LIB.EXE �Ƀp�X��ʂ��Ă����Ă��������D

rem �����̏���
rem	��1�����F�@platform (x86|win32 �܂��� x64|win64)
rem	��2�����F�@���C�u������ ([VS-version]+[configuration]+[platform])
rem 
set SUBDIR=%1
if "!%SUBDIR!"=="x64" set SUBDIR=win64 
set EXT=%2

rem �o�͐�
rem	$(SPR_TOP)/generated/lib/{win32|win64}
rem 
set GENTOP=..\..\generated\lib
set GENDIR=%GENTOP%\%SUBDIR%
call :create_dir OUTDIR %GENDIR%
if not exist %OUTDIR% (
    mkdir %OUTDIR%
)
set OUTPUT=%OUTDIR%/Springhead%EXT%.lib

echo off
rem echo param [%1],[%2]
rem echo GENIR,EXT [%GENDIR%],[%EXT%]

rem ���̓t�@�C��
rem 
set INPUT=Base/Base%EXT%.lib
set INPUT=%INPUT% Foundation/Foundation%EXT%.lib 
set INPUT=%INPUT% Collision/Collision%EXT%.lib
set INPUT=%INPUT% Physics/Physics%EXT%.lib
set INPUT=%INPUT% Graphics/Graphics%EXT%.lib
set INPUT=%INPUT% FileIO/FileIO%EXT%.lib
set INPUT=%INPUT% Framework/Framework%EXT%.lib
set INPUT=%INPUT% HumanInterface/HumanInterface%EXT%.lib
set INPUT=%INPUT% Creature/Creature%EXT%.lib

if "%INPUT%"=="" echo ���ϐ��p�������̋󂫂��s�����Ă��܂��D
if "%INPUT%"=="" echo �󂫂𑝂₵�Ă�����x���s���܂��D
if "%INPUT%"=="" echo ���̃��b�Z�[�W�������ĕ\�������ꍇ�́C
if "%INPUT%"=="" echo �R�}���h�v�����v�g�̐ݒ���C�����Ă��������D
if "%INPUT%"=="" command /e:4096 /c%0 %1 %2 %3


rem lib�̎��s
rem 
if not "%INPUT%"=="" (
    LIB /OUT:%OUTPUT% %INPUT%
    echo Springhead: %OUTPUT% created.
)

endlocal
exit /b

rem ===========================================================================
rem  ��΃p�X�̐ݒ�
rem 
:create_dir
    set %1=%~f2
exit /b

