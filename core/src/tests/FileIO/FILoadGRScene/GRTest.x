xof 0302txt 0064

GRSdk{
	GRScene scene{
		GRCamera cam{
			0.2; 0.0;;			#	size	�X�N���[���̃T�C�Y
			0; 0;;					#	center	�J��������̃X�N���[���̂���
			0.1; 500;				#	front back	���_����N���b�v�ʂ܂ł̑��΋����i���̒l�Ŏw��j
			GRFrame frCam{
				1,0,0,0,0,1,0,0,0,0,1,0,0,0,4,1;;
			}
		}
		GRLight light1{
			0.5; 0.2; 0.2; 1.0;;	#	ambient		����
			1.5;0.1;0.1;1;;	#	diffuse		�g�U��
			1.0;0.1;0.1;1;;	#	emmisive	���ʌ�
			1;1;1;0;;	#	position	�����ʒu�iw=1.0�œ_�����Aw=0.0�ŕ��s�����j
			100; 			#	range	�����͂��͈́idevice��DirectX�̏ꍇ�̂ݗ��p�\�j
			1;				#	attenuation0	��茸����
			0;				#	attenuation1	���`������
			0;				#	attenuation2	2��������
			0;0;0;;		#	spotDirection	�X�|�b�g���C�g�̌���
			0;				#	spotFalloff		�X�|�b�g���C�g�̉~�����ł̌�����(�傫���قǋ}�s) 0..��
			0;				#	spotInner			�X�|�b�g���C�g�̒��S����(�����R�[��)�idevice��DirectX�̏ꍇ�̂ݗ��p�\�j 0..spotCutoff
			0;				#	spotCutoff	�X�|�b�g���C�g�̍L����p�x(�x)(�O���R�[��) 0..��(pi)
		}
		GRFrame fr1{
			1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1;;
			GRMesh{
				-2;0;0;,  2;0;0;,  0;2;0;;				#pos
				3; 2, 1, 0;;							#faces
				-1;0;1;,   0;0;1;,  1;0;1;;				#normal
				3; 2, 1, 0;;							#faceNormal
				1;0;1;1;,   0;1;1;1;,  1;1;0;1;;		#colors
				0;0;, 0;0;, 0;0;;						#texCoords
				0,0,0;									#materialList
			}
		}
		GRMaterial mat{
			0.2; 0.2; 1.2; 1.0;;	#ambient
			0.0; 0.0; 1.0; 1.0;;	#diffuse
			0.0; 0.0; 1.0; 1.0;;	#specular
			0.1; 0.1; 0.1; 1.0;;	#emmisive
			4.0;					#power
			"texture.ppm";
		}
		GRFrame fr2{
			1,0,0,0,	0,1,0,0,	0,0,1,0,	1,1,0,1;;
			GRMesh{
				-2;0;0;,  2;0;0;,  0;2;0;;	#pos
				3; 2, 1, 0;;				#faces
				-1;0;1;,   0;0;1;,  1;0;1;;	#normal
				3; 2, 1, 0;;							#faceNormal
				1;0;1;1;,   0;1;1;1;,  1;1;0;1;;		#colors
				0;0;, 1;1;, 1;0;;						#texCoords
				0,0,0;									#materialList
			}
		}		
	}
}
