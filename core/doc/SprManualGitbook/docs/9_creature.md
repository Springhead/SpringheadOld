Creature���W���[���́C�����V�~�����[�^��p���ăo�[�`�����N���[�`���i�������삷��L�����N�^�j���쐬����@�\��񋟂��܂��DSpringhead�̕����V�~�����[�V�����@�\�́C�l�ԁE�����E�L�����N�^�E���{�b�g���̐g�̓�����V�~�����[�V�������邱�Ƃɂ����Ă����p���l������܂��D���́E�֐ߌn�Őg�̃��f�����쐬���C�֐߂ɑg�ݍ��܂ꂽ����@�\��֐ߌn��IK�@�\��p���Đg�̓���𐶐����邱�Ƃ��ł��܂��D�����V�~�����[�^���̏��i���̂̉^���E�`��E�ڐG�͓��j�𗘗p���ăo�[�`�����Ȋ��o�i�Z���T�j���̐������ł��܂��D���o�E����̃��[�v���񂷂��ƂŎ������삷��L�����N�^�⃍�{�b�g�������ł��܂��D���������o�[�`�����ȃL�����N�^�E���{�b�g���𑍏̂��āC�o�[�`�����N���[�`���iCreature : �������j�ƌĂт܂��D
## Creature���W���[���̍\��
���}��Creature���W���[���̃V�[���c���[�\���������܂��B
```
CRSdk
+-- CRCreature
|   +-- CRBody
|   |   +-- CRBone
|   +-- CREngine (CRSensor, CRController)
```
*CRSdk*��Creature�̋@�\���g�p���鍪�{�ƂȂ�I�u�W�F�N�g�ł��B
```
CRSdkIf* crSdk = CRSdkIf::CreateSdk();
```
*CRCreature*�́C�o�[�`�����N���[�`��$1$�̕��̋@�\�𓝊�����I�u�W�F�N�g�ł��D�g�́A���o��A������L���Ă��܂��DCRCreatureDesc�ɂ͓��ɐݒ肷�ׂ����ڂ͂���܂���B
```
CRCreatureIf* crCreature = crSdk->CreateCreature(
  CDCreatureIf::GetIfInfoStatic(), CRCreatureDesc());
```
CRCreature���쐬������A�����V�~�����[�V�����̃V�[���Ɗ֘A�Â��邽�߂ɁAPHScene���q�I�u�W�F�N�g�Ƃ��ăZ�b�g���Ă��������B
```
// PHSceneIf* phScene;   // should be taken from somewhere
crCreature->AddChildObject(phScene);
```
�V�~�����[�V�������s���́A1�X�e�b�v��1��ACRCreature��Step���Ă�ł��������B������ĂԂ�Creature�����eEngine��Step�����s����܂��B
```
// Every time after simulation step
crCreature.Step();
```

### �g��
*CRBody*�́C�o�[�`�����N���[�`���̐g�̃��f���𓝊����܂��D�g�̃��f���͐g�̍\�����i�̏W���̂ł��D
```
CDBodyIf* crBody = crCreature->CreateBody(
  CRBodyIf::GetIfInfoStatic(), CRBodyDesc());
```
*CRBone*�́C�g�̍\�����i�ЂƂЂƂɑΉ�����I�u�W�F�N�g�ł��D���̂Ɗ֐߁AIK�̂��߂̃A�N�`���G�[�^�i�ꍇ�ɂ���Ă̓G���h�G�t�F�N�^�j���Z�b�g�ɂ������̂ł��B
```
CRBoneIf* crBone = crBody->CreateObject(
  CDBoneIf::GetIfInfoStatic(), CRBoneDesc());
```
CRBone�Ɋ֘A�Â���ׂ��I�u�W�F�N�g�͂��ׂĎq�I�u�W�F�N�g�Ƃ��Ă��������B
```
// ����Bone�ɑΉ����鍄��
// PHSolidIf* phSolid; 
crBone->AddChildObject(phSolid);

// ����Bone��eBone�ɐڑ�����֐߁BRoot Bone�̏ꍇ�͑��݂��Ȃ��̂Œǉ��s�v�B
// PHJointIf* phJoint;
crBone->AddChildObject(phJoint);

// IK�̃G���h�G�t�F�N�^�i���Ȃǁj�ł���ꍇ�͑Ή�����PHIKEndEffector
// PHIKEndEffectorIf* phIKEEff;
crBone->AddChildObject(phIKEEff);

// phJoint�ɑΉ�����IK�A�N�`���G�[�^
// PHIKActuatorIf* phIKAct;
crBone->AddChildObject(phIKAct);
```

### ���o��
���o��(CRSensor)��CREngine�̈��ł��B*CREngine*�́C�o�[�`�����N���[�`���̃X�e�b�v�����̎��s��̂ł��D*CRCreature*��*Step*�֐���1��Ă΂�邽�тɁC*CRCreature*���ێ�����S�Ă�*CREngine*��*Step*�֐������Ɏ��s����܂��DCRSensor�ɂ͎��o�iCRVisualSensor�j�A�G�o�iCRTouchSensor�j������܂��B\paragraph{���o}������ɂ��鍄�̂�1Step���ƂɃ��X�g�A�b�v����@�\�ł��B
```
// �ݒ�
CRVisualSensorDesc descVisualSensor;
/// ����̑傫���F �����p�x�C�����p�x
descVisualSensor.range = Vec2d(Rad(90), Rad(60));
// ���S����̑傫���F �����p�x�C�����p�x
descVisualSensor.centerRange = Vec2d(Rad(10), Rad(10));
// ���o�Z���T��Ώۍ��̂ɓ\��t����ʒu�E�p��
descVisualSensor.pose = Posed();
// ���̋������z�������͎̂���O        
descVisualSensor.limitDistance = 60;	

// �쐬
CRVisualSensorIf* crVisualSensor = crCreature->CreateEngine(
  CRVisualSensorIf::GetIfInfoStatic(), descVisualSensor);
```
���o����ǂݏo���ɂ� NVisibles() �� GetVisible(int n) ��p���܂��B���o���𗘗p����O�ɂ͕K��Update�����s���Ă��������BUpdate�����s����Ǝ��o��񂪍ŐV��Step�Ɋ�Â����ɍX�V����܂��B
```
crVisualSensor->Update();
for (int i=0; i<crVisualSensor->NVisibles(); ++i) {
	CRVisualInfo info = crVisualSensor->GetVisible(i);
	// �����̈���̎��o���
	info.posWorld;    // �����̂̃��[���h���W
	info.posLocal;    // ������Ƃ��������̂̃��[�J�����W
	info.velWorld;    // ���x
	info.velLocal;    // ���[�J�����W�ł̑��x
	info.angle;       // ���쒆�S���獄�̂܂ł̎��p�i���Ԃ�j
	info.solid;       // ������
	info.solidSensor; // ���o�Z���T���́i���Ƃ��ڂƂ��j
	info.sensorPose;  // ���o�Z���T���̂̈ʒu�E�p���i���Ԃ�j
	info.bMyBody;     // �����̐g�̂��\�����鍄�̂ł����true
	info.bCenter;     // ���S����ɓ����Ă����true
}
```

### �����
*CRController*��*CREngine*�̈��ŁC�o�[�`�����N���[�`���̐g�̐����S�����܂��D���ۂ̐���@�\��*CRController*���p�������e�N���X���S�����܂��D���B�^������A�ዅ�^������Ȃǂ�����܂��B
