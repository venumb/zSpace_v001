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

#ifndef ZSPACE_HC_AGGREGATION_H
#define ZSPACE_HC_AGGREGATION_H

#pragma once

#include <headers/zInterface/model/zModel.h>
#include <headers/zCore/base/zExtern.h>

#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

#include <headers/zHousing/architecture/zHcUnit.h>
#include <headers/zHousing/base/zHcEnumerators.h>
//#include <headers/zHousing/base/zHcTypeDef.h>
//#include <headers/zApp/include/zHousing.h>
//#include <headers/zApp/include/zArchGeom.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;


namespace zSpace
{

	/*! \class zHcAggregation
	*	\brief A toolset for housing units aggegation
	*	\since version 0.0.4
	*/

	/** @}*/
	
	class ZSPACE_AG zHcAggregation
	{
	protected:
		//--------------------------
		//---- PROTECTED ATTRIBUTES
		//--------------------------

	public:
		//--------------------------
		//---- PUBLIC ATTRIBUTES
		//--------------------------

		/*!	\brief input mesh Object  */
		zObjMeshArray unitObjs;

		/*!	\brief input mesh function set  */
		vector<zFnMesh> fnUnitMeshArray;

		/*!	\brief container of housing units pointer  */
		vector<zHcUnit> unitArray;

		/*!	\brief interface manager, handles an input path directory*/
		zUtilsCore core;

		//--------------------------
		//---- CONSTRUCTOR
		//--------------------------
		/*! \brief Default constructor.
		*
		*	\since version 0.0.4
		*/
		zHcAggregation();


		//--------------------------
		//---- DESTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.4
		*/
		~zHcAggregation();

		//--------------------------
		//---- SET METHODS
		//--------------------------
			   
		//--------------------------
		//---- CREATE METHODS
		//--------------------------

		/*! \brief This method creates housing units.
		*
		*	\param		[in]	_structureType				- input structure type
		*	\since version 0.0.4
		*/
		void createHousingUnits(zStructureType _structureType);

		/*! \brief This method creates housing units from an imported mesh.
		*
		*	\param		[in]	_path				- directory of files
		*	\param		[in]	_type				- file type
		*	\since version 0.0.4
		*/
		void importMeshesFromDirectory(string&_path);

		/*! \brief This method creates layouts for housing units from  imported meshes.
		*
		*	\param		[in]	_path				- directory of files
		*	\param		[in]	_type				- file type
		*	\since version 0.0.4
		*/
		void importLayoutMeshesFromDirectory(vector<string>_pathFlats, vector<string>_pathVerticals, vector<string>_pathLandscapes);


		//--------------------------
		//---- UPDATE METHODS
		//--------------------------

		/*! \brief This method updates the structure of the units
		*
		*	\param		[in]	_structureType				- input structure type
		*	\since version 0.0.4
		*/
		void updateStructureType(zStructureType _structureType);

		/*! \brief This method updates the structure of the units
		*
		*	\param		[in]	_structureType				- input structure type
		*	\since version 0.0.4
		*/
		void updateLayout(int unitId, zLayoutType&_layoutType, bool flip);

		

#ifndef ZSPACE_UNREAL_INTEROP

		//--------------------------
		//---- DISPLAY SET METHODS
		//--------------------------

		/*! \brief This method sets the display model not for Unreal.
		*
		*	\param		[in]	_index				- input housing unit index
		*	\since version 0.0.4
		*/
		void setDisplayModel(zModel&_model);

		//--------------------------
		//---- DISPLAY METHODS
		//--------------------------

		/*! \brief This method sets the display of the arch geom elements
		*
		*	\param		[in]	showColumn				- display boolean
		*	\param		[in]	showSlab				- display boolean
		*	\param		[in]	showWall				- display boolean
		*	\param		[in]	showFacade				- display boolean
		*	\param		[in]	showRoof				- display boolean
		*	\since version 0.0.4
		*/
		void showArchGeom(bool&_showColumn, bool&_showSlab, bool&_showWall, bool&_showFacade, bool&_showRoof);


		/*! \brief This method sets if columns should be showned
		*
		*	\param		[in]	showFacade				- display boolean
		*	\since version 0.0.4
		*/
		void showLayout (int&_index, bool&_showLayout);

		protected:
			//--------------------------
			//---- PROTECTED DISPLAY ATTRIBUTES
			//--------------------------

			/*!	\brief pointer to display model  */
			zModel *model;
#endif

	};


}

#if defined(ZSPACE_STATIC_LIBRARY)  || defined(ZSPACE_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zHousing/architecture/zHcAggregation.cpp>
#endif

#endif