xof 0303txt 0032

Scene {
	Camera  {
		1.000000, 0.000000, 0.000000, 0.000000,      # 視点行列
		0.000000, 0.700000,0.300000, 0.000000,
		0.000000, -0.300000, 0.700000, 0.000000,
		0.000000, 0.4, -1.0, 1.000000;;
		0.01; 0.01;         # スクリーンの幅,高さ
		0.0; 0.0;           # カメラからのスクリーンのずれ(X,Y)
		0.01; 100.0;        # カメラとクリッピング平面の距離(front,back)
  }
	SolidContainer{
	    Solid Pointer1{
	      0.25;
	      1.0, 0.0, 0.0,
	      0.0, 1.0, 0.0,
	      0.0, 0.0, 1.0;;
	      0.0; 0.0; 0.0;;
	      0.0; 0.0; 0.0;;
	      0.0; 0.0; 0.0;;
	      {frPointer1}
	    }
		Solid soBlock1{
			10.0;
			10.0, 0.0, 0.0,
			0.0, 10.0, 0.0,
			0.0, 0.0, 10.0;;
			0.0; 0.0; 0.0;;
			0.0; 0.0; 0.0;;
			0.0; 0.0; 0.0;;
			{frBlock1}
		}
		Solid soBlock2{
			10.0;
			10.0, 0.0, 0.0,
			0.0, 10.0, 0.0,
			0.0, 0.0, 10.0;;
			0.0; 0.0; 0.0;;
			0.0; 0.0; 0.0;;
			0.0; 0.0; 0.0;;
			{frBlock2}
		}
		Solid soBlock3{
			10.0;
			10.0, 0.0, 0.0,
			0.0, 10.0, 0.0,
			0.0, 0.0, 10.0;;
			0.0; 0.0; 0.0;;
			0.0; 0.0; 0.0;;
			0.0; 0.0; 0.0;;
			{frBlock3}
		}
	}
	GravityEngine{
		0.0; -98.0; 0.0;;
		{soBlock1}
		{soBlock2}
		{soBlock3}
	}
	ContactEngine{
		{frFloor}
		{Pointer1}
		{soBlock1}
		{soBlock2}
		{soBlock3}
	}
	Frame frPointer1{
		FrameTransformMatrix  {
			1.000000,0.000000,0.000000,0.000000,
			0.000000,1.000000,0.000000,0.000000,
			0.000000,0.000000,1.000000,0.000000,
			0.300000,0.200000,0.300000,1.000000;;
		}
	}
	Frame frLight {
		FrameTransformMatrix  {
			0.707107,0.000000,-0.707107,0.000000,
			0.500000,0.707107,0.500000,0.000000,
			0.500000,-0.707107,0.500000,0.000000,
			0.000000,0.000000,0.000000,1.00000;;
		}
	}
	Light8{
		3;
		0.900000;0.900000;0.900000;0.900000;;
		0.900000;0.900000;0.900000;0.900000;;
		0.000000;0.000000;0.000000;0.000000;;
		0.000000;0.000000;0.000000;;
		-0.3 ;-0.3 ; -0.3;;
		20.000000;
		1.000000;
		0.800000;
		0.800000;
		0.800000;
		0.300000;
		0.330000;
		{ frLight }
	}
	Frame frBlock3 {
		FrameTransformMatrix  {
			1.000000,0.000000,0.000000,0.000000,
			0.000000,1.000000,0.000000,0.000000,
			0.000000,0.000000,1.000000,0.000000,
			0.100000,0.000000,0.000000,1.000000;;
		}
		Mesh {
			8;
			-0.1; 0.05 ; 0.1;,
			0.1;0.05;0.1;,
			0.1;0.05;-0.1;,
			-0.1;0.05;-0.1;,
			0.1;-0.05;-0.1;,
			-0.1;-0.05;-0.1;,
			0.1;-0.05;0.1;,
			-0.1;-0.05;0.1;;
			
			6;
			4;0,1,2,3;,
			4;3,2,4,5;,
			4;5,4,6,7;,
			4;7,6,1,0;,
			4;1,6,4,2;,
			4;7,0,3,5;;
			
			MeshMaterialList {
				1;
				6;
				0,
				0,
				0,
				0,
				0,
				0;;
				Material {
					0.019608;1.000000;0.721569;1.000000;;
					22.000000;
					0.430000;0.430000;0.430000;;
					0.004902;0.250000;0.180392;;
				}
			}
		}
	}
	
	Frame frBlock2 {
		
		
		FrameTransformMatrix  {
			1.000000,0.000000,0.000000,0.000000,
			0.000000,1.000000,0.000000,0.000000,
			0.000000,0.000000,1.000000,0.000000,
			0.200000,0.200000,0.000000,1.000000;;
		}
		
		Mesh {
			8;
			-0.075;0.05;0.075;,
			0.075;0.05;0.075;,
			0.075;0.05;-0.075;,
			-0.075;0.05;-0.075;,
			0.075;-0.05;-0.075;,
			-0.075;-0.05;-0.075;,
			0.075;-0.05;0.075;,
			-0.075;-0.05;0.075;;
			
			6;
			4;0,1,2,3;,
			4;3,2,4,5;,
			4;5,4,6,7;,
			4;7,6,1,0;,
			4;1,6,4,2;,
			4;7,0,3,5;;
			
			MeshMaterialList {
				1;
				6;
				0,
				0,
				0,
				0,
				0,
				0;;
				Material {
					1.000000;0.125490;0.078431;1.000000;;
					25.000000;
					0.830000;0.830000;0.830000;;
					0.280000;0.035137;0.021961;;
				}
			}
		}
	}
	
	Frame frBlock1 {
		FrameTransformMatrix  {
			1.000000,0.000000,0.000000,0.000000,
			0.000000,1.000000,0.000000,0.000000,
			0.000000,0.000000,1.000000,0.000000,
			0.100000,0.400000,0.000000,1.000000;;
		}
		Mesh {
			8;
			-0.1;0.05;0.1;,
			0.1;0.05;0.1;,
			0.1;0.05;-0.1;,
			-0.1;0.05;-0.1;,
			0.1;-0.05;-0.1;,
			-0.1;-0.05;-0.1;,
			0.1;-0.05;0.1;,
			-0.1;-0.05;0.1;;
			
			6;
			4;0,1,2,3;,
			4;3,2,4,5;,
			4;5,4,6,7;,
			4;7,6,1,0;,
			4;1,6,4,2;,
			4;7,0,3,5;;
			MeshMaterialList {
				1;
				6;
				0,
				0,
				0,
				0,
				0,
				0;;
				Material {
					1.000000;0.933333;0.003922;1.000000;;
					25.000000;
					0.670000;0.670000;0.670000;;
					0.310000;0.289333;0.001216;;
				}
			}
		}
	}
	Frame frFloor{
		FrameTransformMatrix  {
			1.000000,0.000000,0.000000,0.000000,
			0.000000,1.000000,0.000000,0.000000,
			0.000000,0.000000,1.000000,0.000000,
			0.000000,-0.100000,0.000000,1.000000;;
		}
		Mesh {
			8;
			-5.00000;0.00000;5.00000;,
			5.00000;0.00000;5.00000;,
			5.00000;0.00000;-5.00000;,
			-5.00000;0.00000;-5.00000;,
			5.00000;-1.00000;-5.00000;,
			-5.00000;-1.00000;-5.00000;,
			5.00000;-1.00000;5.00000;,
			-5.00000;-1.00000;5.00000;;
			
			6;
			4;0,1,2,3;,
			4;3,2,4,5;,
			4;5,4,6,7;,
			4;7,6,1,0;,
			4;1,6,4,2;,
			4;7,0,3,5;;
			PhysicalMaterial {
				1.0; 1.0; 1.0; 1.0; 2.0, 2.0;
			}
			MeshMaterialList {
				1;
				6;
				0,
				0,
				0,
				0,
				0,
				0;;
				Material {
					1.000000;1.000000;1.000000;1.000000;;
					0.000000;
					0.000000;0.000000;0.000000;;
					0.000000;0.000000;0.000000;;
				}
			}
			PhysicalMaterial{
					1.0;	#	FLOAT reflexSpring
					1.0;	#	FLOAT reflexDamper
					1.0;	#	FLOAT frictionSpring
					1.0;	#	FLOAT frictionDamper
					1.0;	#	FLOAT staticFriction
					1.0;	#	FLOAT dynamicFriction
			}
		}
	}
}
