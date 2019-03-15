//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


# define NEW_VW_OBJECT(T)				(T*) new(malloc( sizeof(T))) T
# define DELETE_VW_OBJECT(T, p)			if ( p ) { p->~T(); free(p); p = NULL; }
# define NEW_OBJECT(T)					(T*) new(malloc( sizeof(T))) T
# define DELETE_OBJECT(T, p)			if ( p ) { p->~T(); free(p); p = NULL; }
# define NEW_DATA(size)					malloc( size);
# define DELETE_DATA(p)					if ( p ) free( p);
# define NEW_VW_DATA(size)				malloc( size);
# define DELETE_VW_DATA(p)				if ( p ) free( p);
# define NEW_OBJECTS_ARRAY(T, count)	new T[count];
# define DELETE_OBJECTS_ARRAY(T, p)		delete[] (T*)p; p = NULL;
# define NEW_VW_OBJECST_ARRAY(T, count)	new T[count];
# define DELETE_VW_OBJECTS_ARRAY(T, p)	delete[] (T*)p; p = NULL;
