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

#ifdef ZSPACE_INLINE
#undef ZSPACE_INLINE
#endif

#if defined(ZSPACE_STATIC_LIBRARY)  || defined(ZSPACE_DYNAMIC_LIBRARY)
#  define ZSPACE_INLINE 
#else
#  define ZSPACE_INLINE inline
#endif

#ifdef ZSPACE_DYNAMIC_LIBRARY
#define ZSPACE_CORE __declspec(dllexport)
#define ZSPACE_API  __declspec(dllexport)
#define ZSPACE_TOOLS  __declspec(dllexport)
#define ZSPACE_APP  __declspec(dllexport)
#else
#define ZSPACE_CORE 
#define ZSPACE_API 
#define ZSPACE_TOOLS  
#define ZSPACE_APP  
#endif
