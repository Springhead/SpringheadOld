rem Project�ȉ���VSS����擾���܂�

rem ���̃t�@�C���͂��łɎg���Ă��Ȃ��悤�Ɍ����܂�
rem SVN���|�W�g���ɂ�Springhead�ȉ���������Ă��Ȃ��̂ł����Ă��Ӗ��Ȃ��ł�

cd ..\..
ss Workfold $/Project .
ss Get $/Project -R > Springhead\test\log\GetVSS.log
cd Springhead\test
