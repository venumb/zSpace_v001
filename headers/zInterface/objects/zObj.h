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

#ifndef ZSPACE_OBJ_H
#define ZSPACE_OBJ_H

#pragma once

#include <headers/zCore/utilities/zUtilsCore.h>
#include <headers/zCore/utilities/zUtilsDisplay.h>
#include <headers/zCore/utilities/zUtilsJson.h>

namespace zSpace
{
	/** \addtogroup zInterface
	*	\brief The Application Program Interface of the library.
	*  @{
	*/

	/** \addtogroup zObjects
	*	\brief The object classes of the library.
	*  @{
	*/

	/*! \class zObj
	*	\brief The base object class.
	*	\since version 0.0.2
	*/

	/** @}*/

	/** @}*/

	class ZSPACE_API zObj
	{
	protected:
		
		/*! \brief pointer to display utilities object	*/
		zUtilsDisplay *displayUtils;

		/*! \brief pointer to core utilities object	*/
		zUtilsCore *coreUtils;
		
		/*! \brief boolean for displaying the object		*/
		bool showObject;

		/*! \brief boolean for displaying the object transform		*/
		bool showObjectTransform;

	public:
		//--------------------------
		//----  ATTRIBUTES
		//--------------------------		
			

		/*! \brief object transformation matrix			*/
		zTransformationMatrix transformationMatrix;
		

		//--------------------------
		//---- CONSTRUCTOR
		//--------------------------

		/*! \brief Default constructor.
		*
		*	\since version 0.0.2
		*/
		zObj();

		//--------------------------
		//---- DESTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.2
		*/
		~zObj();

		//--------------------------
		//---- VIRTUAL METHODS
		//--------------------------
		
		/*! \brief This method displays the object type.
		*
		*	\since version 0.0.2
		*/
		virtual void draw();
		
		/*! \brief This method gets the bounds of the object.
		*
		*	\since version 0.0.2
		*/
		virtual void getBounds(zVector &minBB, zVector &maxBB);
	
		//--------------------------
		//---- SET METHODS
		//--------------------------

		/*! \brief This method sets show object boolean.
		*
		*	\param		[in]	_showObject				- input show object boolean.
		*	\since version 0.0.2
		*/
		void setShowObject(bool _showObject);

		/*! \brief This method sets show object transform boolean.
		*
		*	\param		[in]	_showObjectTransform				- input show object transform boolean.
		*	\since version 0.0.2
		*/
		void setShowTransform(bool _showObjectTransform);

		/*! \brief This method sets display utils.
		*
		*	\param		[in]	_displayUtils			- input display utils.
		*	\param		[in]	_coreUtils				- input core utils.
		*	\since version 0.0.2
		*/
		void setUtils(zUtilsDisplay &_displayUtils, zUtilsCore &_coreUtils);

		

	};

}

#if defined(ZSPACE_STATIC_LIBRARY)  || defined(ZSPACE_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zInterface/objects/zObj.cpp>
#endif

#endif