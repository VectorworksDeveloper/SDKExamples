//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


/*
 Metrowerks changed the global new_handler identifier for the MW 10 release.
 */

#if __MWERKS__ < 0x1000
extern void (*new_handler)();
#define NEW_HANDLER new_handler
#else
#include <new>
namespace std {
	extern new_handler	__new_handler;
#define NEW_HANDLER __new_handler
}
#endif

#ifdef _UNDEFINED_SAFEMEMORY_NEWOVERRIDE

/************************************************************************/
/*	Purpose..: 	Allocate memory											*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	pointer to memory or 0L									*/
/************************************************************************/
void *operator new(size_t size) throw(std::bad_alloc)
{
	void *ptr;
	
	while((ptr=QTMM::NewPtr(size))==NULL)
	{
		break;
	}
	return(ptr);
}

/************************************************************************/
/*	Purpose..: 	Dispose memory											*/
/*	Input....:	pointer to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
void operator delete(void *ptr) throw()
{
	if(ptr) QTMM::DisposePtr((Ptr)ptr);
}
#endif
