

 - TestMain.bat���s������ - 

1. "Springhead/src�t�H���_"�ȉ��̃t�@�C�������ׂď�������

 ������������ ���ӁI�I ������������������������������������������������������
 �� ����ɂ���āA�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@                           ��
 �� VSS�ɏオ���Ă��Ȃ������̃��[�J���ɂ����Ȃ��t�@�C���������Ă��܂��܂��B��
 �� �]���āA���[�J���Ŏ��s����ۂɂ͏\�����ӂ���悤�ɂ��Ă��������B       ��
 ����������������������������������������������������������������������������

2. "bat\GetSpringhead.bat"�����s���A
   VSS����"Springhead�t�H���_"�ȉ��̃t�@�C�����擾����B
   �܂��A���O��"log\GetVSS.log"�֏o�͂���B

3. "bat\TestAll.bat"�����s���A
   �r���h�e�X�g�y�сA�r���h��������"Springhead�t�H���_"�ւ̃��x���t�����s���B
   (���x���ɂ͓������A�R�����g�ɂ̓r���h�ɐ����������ڂ��t������)
   �܂��A�r���h�e�X�g���s�����ڂ�ǉ��������ꍇ�͂���"TestAll.bat"�ɒǉ�����B
   �ڂ����͎��ߎQ�ƁB


 - �r���h�e�X�g���s�����ڂ�ǉ�����ɂ� - 

bat\TestAll.bat(TestMain.bat�ł͂Ȃ��̂Œ���!)�̈ȉ��̂Q�ӏ���

1. bat\BuildMFC.bat (�r���h���s��dsp�t�@�C���̂���f�B���N�g��) (dsp�t�@�C����)
      ��������
   bat\BuildBCB.bat (�r���h���s��bpg�t�@�C���̂���f�B���N�g��) (bpg�t�@�C����)

2.bat\Label.bat (exe�t�@�C���̂���f�B���N�g��) (exe�t�@�C����)

�����ꂼ��ǉ�����

------ TestAll.bat ----------------------------------------------

			�F
			�F

rem **** �r���h�e�X�g���s��(�e�X�g���s���t�@�C���͈����Ŏw��) **** 
rem call bat\BuildMFC(BuildBCB).bat (����1) (����2) 
rem (����1) : �v���W�F�N�g�t�@�C���̏ꏊ
rem (����2) : �v���W�F�N�g�t�@�C����(BuildMFC-.dsp�̑O�̕���, BuildBCB-.bpg�̑O�̕���)

rem ----- ���̉��Ƀr���h���s���t�@�C����ǉ����� -----
call bat\BuildMFC.bat Springhead\src\Samples\MFCD3DDyna MFCD3DDyna
call bat\BuildBCB.bat Springhead\src Springhead
														�����������ɒǉ�����
rem ----- �����܂� -----

			�F
			�F

rem **** ���x���t�� **** 
rem ��ōs�����r���h��1�ł��������Aexe�t�@�C�����ł��Ă���$/Project/Springhead�ɐ������x����t����
rem �܂��A�r���h�����������t�@�C�������R�����g�ɗ��񂷂� 
rem call bat\Label.bat (����1) (����2)
rem (����1) : exe�t�@�C���̏ꏊ
rem (����2) : exe�t�@�C����

rem ----- ���̉��Ƀr���h���s�����t�@�C����ǉ����� -----
call bat\Label.bat Springhead\src\Samples\MFCD3DDyna\MFCDebug MFCD3DDyna 
call bat\Label.bat Springhead\src\BCBGui\Test Test
														�����������ɒǉ�����
rem ----- �����܂� -----

------------------------------------------------------------------------------


 - ���O�ɂ��� - 
�e�X�g�A�v�������s�����"Springhead\test\log�t�H���_"�ɂ��낢�냍�O���o�͂���܂��B�ʏ��VSS�ɏオ���Ă��郍�O������΂����Ǝv���܂��i1��1��X�V�j�B

�EBuild.log
	�r���h����

�EBuildError.log
	Build.log�ŃG���[�Ɋ֌W����Ǝv����Ƃ��낾�����o��

�EHistory.log
	Springhead�t�H���_�̗������̍ŐV50���ڂ��o��


4. "bat\MakeDoc.bat"�����s���A
   doxygen�𗘗p�����h�L�������g���쐬����B
�@ �h�L�������g��src\html�ȉ��ɍ����B

