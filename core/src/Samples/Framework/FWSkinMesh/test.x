xof 0302txt 0064

FWScene fwScene{
	{grScene}
}

GRScene grScene{
	Import{"human.x";}
		GRFrame frCam{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,5,1;;
		}
	GRCamera cam{
		0.2; 0.0;;				#	size	�X�N���[���̃T�C�Y
		0; 0;;					#	center	�J��������̃X�N���[���̂���
		0.1; 500;				#	front back	���_����N���b�v�ʂ܂ł̑��΋����i���̒l�Ŏw��j
		{frCam}
	}
	
}
