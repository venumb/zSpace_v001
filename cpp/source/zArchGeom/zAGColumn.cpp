// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2019 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Vishu Bhooshan <vishu.bhooshan@zaha-hadid.com>
//


#include<headers/zArchGeom/zAgColumn.h>

namespace zSpace
{
	//---- CONSTRUCTOR

	ZSPACE_INLINE zAgColumn::zAgColumn(){}

	ZSPACE_INLINE zAgColumn::zAgColumn(zObjMesh&_inMeshObj, zVector&_position, zVector & x, zVector & y, zVector & z, float height_)
	{
		inMeshObj = &_inMeshObj;
		fnInMesh = zFnMesh(*inMeshObj);
		position = _position;

		zPointArray pointArray;
		zIntArray polyConnect;
		zIntArray polyCount;

		x.normalize();
		y.normalize();
		z.normalize();

		zVector midP = (x + y) / 2;
		midP.normalize();
		midP *= nodeDepth;

		float xDepth = nodeDepth * 0.8;
		float yDepth = nodeDepth * 0.8;

#pragma region ColumnMesh
		for (int i = 0; i < 12; i++)
		{
			zVector vPos = position;

			if (i == 11) vPos += z * height_ + (x * 0.1);//13
			else if (i == 10) vPos += z * height_ + (y * 0.1);//12
			else if (i == 9) vPos += z * nodeHeight + (y * 0.2);//11
			else if (i == 8) vPos += z * nodeHeight + (x * 0.2);//10
			else if (i == 7) vPos += z * beamB_Height + (x * (xDepth * 0.75));//9
			else if (i == 6) vPos += z * beamA_Height + (y * (yDepth * 0.6));//8
			else if (i == 5) vPos += z * beamA_Height + (y * (yDepth * 0.85));//7dup
			else if (i == 4) vPos += z * beamB_Height + (x * xDepth); //6dup

			else if (i == 3)//6
			{
				vPos += z * beamB_Height + (x * xDepth);
				c = vPos;
			}

			else if (i == 2) vPos += z * beamA_Height + (y * (yDepth * 0.85));//7

			else if (i == 1)//4
			{
				vPos += z * beamA_Height + (y * (yDepth * 0.85)); //change to 1.0
				a = vPos;
			}

			else if (i == 0)//5
			{
				vPos += z * beamB_Height + midP;
				b = vPos;
			}

			pointArray.push_back(vPos);
		}

		for (int i = 0; i < 8; i++)
		{
			zVector vPos = position;

			if (i == 0) vPos += z * height_; //12
			else if (i == 1) vPos += z * height_ + (x * 0.1);
			else if (i == 2) vPos += z * nodeHeight + (x * 0.2);
			else if (i == 3) vPos += z * nodeHeight;
			else if (i == 4) vPos += z * beamB_Height + (x * (xDepth * 0.75));
			else if (i == 5) vPos += z * 0.1;
			else if (i == 6) vPos += z * beamB_Height + (x * xDepth); 
			else if (i == 7) vPos = position; //19


			pointArray.push_back(vPos);
		}


		for (int i = 0; i < 8; i++)
		{
			zVector vPos = position;

			if (i == 0) vPos += z * height_; //20
			if (i == 1) vPos += z * nodeHeight;
			if (i == 2) vPos += z * nodeHeight + (y * 0.2);
			if (i == 3) vPos += z * height_ + (y * 0.1);
			if (i == 4) vPos += z * 0.1;
			if (i == 5) vPos += z * beamA_Height + (y * (yDepth * 0.6));
			if (i == 6) vPos = position;
			if (i == 7)  vPos += z * beamA_Height + (y * (yDepth * 0.85));

			pointArray.push_back(vPos);


		}


		//array of ordered vertices
		polyConnect.push_back(0);
		polyConnect.push_back(1);
		polyConnect.push_back(2);
		polyConnect.push_back(3);//1

		polyConnect.push_back(4);
		polyConnect.push_back(5);
		polyConnect.push_back(6);
		polyConnect.push_back(7);

		polyConnect.push_back(7);
		polyConnect.push_back(6);
		polyConnect.push_back(9);
		polyConnect.push_back(8);//3

		polyConnect.push_back(8);
		polyConnect.push_back(9);
		polyConnect.push_back(10);
		polyConnect.push_back(11);

		polyConnect.push_back(12);
		polyConnect.push_back(13);
		polyConnect.push_back(14);
		polyConnect.push_back(15);//5

		polyConnect.push_back(15);
		polyConnect.push_back(14);
		polyConnect.push_back(16);
		polyConnect.push_back(17);

		polyConnect.push_back(17);
		polyConnect.push_back(16);
		polyConnect.push_back(18);
		polyConnect.push_back(19);//7

		polyConnect.push_back(20);
		polyConnect.push_back(21);
		polyConnect.push_back(22);
		polyConnect.push_back(23);

		polyConnect.push_back(22);
		polyConnect.push_back(21);
		polyConnect.push_back(24);
		polyConnect.push_back(25);//9

		polyConnect.push_back(25);
		polyConnect.push_back(24);
		polyConnect.push_back(26);
		polyConnect.push_back(27);//10



		//number of vertices per face array
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);
		polyCount.push_back(4);

#pragma endregion

		printf("\n point array: %i ", pointArray.size());

		fnInMesh.create(pointArray, polyCount, polyConnect);
		fnInMesh.smoothMesh(2, false);		
	}

	//---- DESTRUCTOR

	ZSPACE_INLINE zAgColumn::~zAgColumn() {}

	//---- SET METHODS



	

}