include Fox

#
# �w�肳�ꂽ�^�C�v�̃I�u�W�F�N�g���̈ꗗ���쐬����
#
class SprNameList < FXComboBox
	SOLIDS = 0
	JOINTS = 1
	SHAPES = 2
	JOINTTYPE = 3
	def initialize(owner, type=nil, obj=nil)
		super(owner, 25, nil, 0, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK)
		numVisible = 4

		update(type, obj) if type
	end

	def update(type, obj)
		clearItems
		phsdk = $sprapp.GetSdk.GetPHSdk
		phscene = $sprapp.GetSdk.GetScene.GetPHScene
		if type == SOLIDS
			for i in 0..phscene.NSolids()-1
				solid = phscene.GetSolids()[i]
				appendItem(solid.GetName(), solid)
			end
		elsif type == JOINTS
			for i in 0..phscene.NJoints()-1
				joint = phscene.GetJoints(i)
				appendItem(joint.GetName(), joint)
			end
		elsif type == SHAPES
			if obj			# �����solid���Q�Ƃ���shape�̈ꗗ
				for i in 0..obj.NShapes()-1
					shape = obj.GetShape(i)
					appendItem(shape.GetName(), shape)
				end
			else			# sdk���ۗL����shape�̈ꗗ
				for i in 0..phsdk.NShapes()-1
					shape = phsdk.GetShape(i)
					appendItem(shape.GetName(), shape)
				end
			end
		elsif type == JOINTTYPE
			appendItem('hinge')
			appendItem('slider')
			appendItem('balljoint')
			appendItem('spring')
		end
	end
end