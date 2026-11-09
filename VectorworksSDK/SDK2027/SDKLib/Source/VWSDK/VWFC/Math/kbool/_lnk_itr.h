//! author="Klaas Holwerda"
//! version="1.0"
/*
 * Definitions of classes, for list implementation
 * template list and iterator for any list node type
*/
#ifndef _LinkBaseIter_H
#define _LinkBaseIter_H

#ifdef __GNUG__
#pragma interface
#endif

//! headerfiles="_dl_itr.h stdlib.h misc.h gdsmes.h"
//#include <stdlib.h>

#include "booleng.h"

#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))

#include "_dl_itr.h"

//! codefiles="_dl_itr.cpp"

//!  Template class TDLI
/*!
 class for iterator on DL_List<void*> that is type casted version of DL_Iter
 \sa DL_Iter for further documentation
*/
template<class Type> class TDLI : public DL_Iter<void*>
{
	public:
		//!constructor
      /*!
      \param list to iterate on.
      */
		TDLI(DL_List<void*>* list);

 		//!constructor
	   TDLI(DL_Iter<void*>* otheriter);

		//! nolist constructor
		TDLI();

		//! destructor
		~TDLI();

		//!call fp for each item
      void 	  foreach_f(void (*fp) (Type* item) );

      //!call fp for each item
      void 	  foreach_mf(void (Type::*fp) () );

		/* list mutations */


		//! delete all items
		void    delete_all		();


      //! insert at end
		void    insend		      (Type* n);

      //! insert at begin
		void    insbegin		   (Type* n);

      //! insert before current
		void    insbefore       (Type* n);

      //! insert after current
		void    insafter        (Type* n);

      //! insert at end unsave (works even if more then one iterator is on the list
      //! the user must be sure not to delete/remove items where other iterators
      //! are pointing to.
		void    insend_unsave	 (Type* n);

      //! insert at begin unsave (works even if more then one iterator is on the list
      //! the user must be sure not to delete/remove items where other iterators
      //! are pointing to.
		void    insbegin_unsave	 (Type* n);

      //! insert before iterator position unsave (works even if more then one iterator is on the list
      //! the user must be sure not to delete/remove items where other iterators
      //! are pointing to.
		void    insbefore_unsave (Type* n);

      //! insert after iterator position unsave (works even if more then one iterator is on the list
      //! the user must be sure not to delete/remove items where other iterators
      //! are pointing to.
		void    insafter_unsave  (Type* n);

      //! \sa DL_Iter::takeover(DL_List< Dtype >* otherlist )
		void    takeover        (DL_List<void*>* otherlist);
      //! \sa DL_Iter::takeover(DL_Iter* otheriter)
		void    takeover        (TDLI* otheriter);
      //! \sa DL_Iter::takeover(DL_Iter* otheriter, Sint32 maxcount)
		void    takeover        (TDLI* otheriter, Sint32 maxcount);

      //! \sa DL_Iter::has
		bool  has             (Type*);
      //! \sa DL_Iter::toitem
		bool  toitem          (Type*);

      //!get the item then iterator is pointing at
      Type*   item            ();

      //! \sa DL_Iter::mergesort
		void    mergesort             (Sint32 (*f)(Type* a,Type* b));
      //! \sa DL_Iter::cocktailsort
		void    cocktailsort          (Sint32 (*)(Type* a,Type* b), void (*)(Type* c,Type* d)=NULL);

};

//!  Template class TDLIsort
/*!
// class for sort iterator on DL_List<void*> that is type casted version of DL_SortIter
// see also inhereted class DL_SortIter for further documentation
*/
template<class Type> class TDLISort : public DL_SortIter<void*>
{
	public:

      //!constructor givin a list and a sort function
		TDLISort(DL_List<void*>* list, Sint32 (*newfunc)(void*,void*));
		~TDLISort();

      //!delete all items from the list
		void    		 delete_all();
		bool       has     (Type*);
		bool       toitem  (Type*);
		Type* item    ();
};

//!  Template class TDLIStack
/*!
 class for iterator on DL_List<void*> that is type casted version of DL_StackIter
 see also inhereted class DL_StackIter for further documentation
*/
template<class Type> class TDLIStack : public DL_StackIter<void*>
{
   public:
      //constructor givin a list
		TDLIStack(DL_List<void*>* list);

		~TDLIStack();

		void            push(Type*);
		Type*           pop();
};

//=======================================================================
// implementation class LinkBaseIter
//=======================================================================

template<class Type>
TDLI<Type>::TDLI(DL_List<void*>* newlist):DL_Iter<void*>(newlist)
{
}

template<class Type>
TDLI<Type>::TDLI(DL_Iter<void*>* otheriter):DL_Iter<void*>(otheriter)
{
}

template<class Type>
TDLI<Type>::TDLI():DL_Iter<void*>()
{
}

// destructor TDLI
template<class Type>
TDLI<Type>::~TDLI()
{
}

template<class Type>
void TDLI<Type>::delete_all()
{
   DL_Node<void*>* node;
   Type* obj;
	for (Sint32 i=0; i< NB; i++)
	{
		node = HD;
		HD = node->_next;
      obj=(Type*)(node->_item);
      delete obj;
		delete node;
	}
	NB=0; //reset memory used (no lost pointers)
   TL=RT;
   _current=RT;
}

template<class Type>
void TDLI<Type>::foreach_f(void (*fp) (Type* item) )
{
   DL_Iter<void*>::foreach_f( (void (*)(void*))fp); //call fp for each item
}

template<class Type>
void TDLI<Type>::foreach_mf(void (Type::*mfp) ())
{

   DL_Node<void*>* node=HD; //can be 0 if empty
   Type* obj;
   for(Sint32 i=0; i< NB; i++)
   {
     obj=(Type*)(node->_item);
     (obj->*mfp)();
     node=node->_next;
   }
}

template<class Type>
void TDLI<Type>::takeover(DL_List<void*>* otherlist)
{
   DL_Iter<void*>::takeover( (DL_List<void*>*) otherlist);
}

template<class Type>
void TDLI<Type>::takeover(TDLI* otheriter)
{
   DL_Iter<void*>::takeover( (DL_Iter<void*>*) otheriter);
}

template<class Type>
void TDLI<Type>::takeover(TDLI* otheriter,Sint32 maxcount)
{
   DL_Iter<void*>::takeover( (DL_Iter<void*>*) otheriter,maxcount);
}

// is item element of the list?
template<class Type>
bool TDLI<Type>::has(Type* otheritem)
{
   return DL_Iter<void*>::has( (void*) otheritem);
}

// goto to item
template<class Type>
bool TDLI<Type>::toitem(Type* item)
{
   return DL_Iter<void*>::toitem( (void*) item);
}

// get current item
template<class Type>
Type*    TDLI<Type>::item()
{
   return (Type*) DL_Iter<void*>::item();
}

template<class Type>
void TDLI<Type>::insend(Type* newitem)
{
   DL_Iter<void*>::insend( (void*) newitem);
}

template<class Type>
void TDLI<Type>::insbegin(Type* newitem)
{
   DL_Iter<void*>::insbegin( (void*) newitem);
}

template<class Type>
void TDLI<Type>::insbefore(Type* newitem)
{
   DL_Iter<void*>::insbefore( (void*) newitem);
}

template<class Type>
void TDLI<Type>::insafter(Type* newitem)
{
   DL_Iter<void*>::insafter( (void*) newitem);
}

template<class Type>
void TDLI<Type>::insend_unsave(Type* newitem)
{
   short iterbackup=_list->_iterlevel;
   _list->_iterlevel=0;
   DL_Iter<void*>::insend( (void*) newitem);
   _list->_iterlevel=iterbackup;
}

template<class Type>
void TDLI<Type>::insbegin_unsave(Type* newitem)
{
   short iterbackup=_list->_iterlevel;
   _list->_iterlevel=0;
   DL_Iter<void*>::insbegin( (void*) newitem);
   _list->_iterlevel=iterbackup;
}

template<class Type>
void TDLI<Type>::insbefore_unsave(Type* newitem)
{
   short iterbackup=_list->_iterlevel;
   _list->_iterlevel=0;
   DL_Iter<void*>::insbefore( (void*) newitem);
   _list->_iterlevel=iterbackup;
}

template<class Type>
void TDLI<Type>::insafter_unsave(Type* newitem)
{
   short iterbackup=_list->_iterlevel;
   _list->_iterlevel=0;
   DL_Iter<void*>::insafter( (void*) newitem);
   _list->_iterlevel=iterbackup;
}

template<class Type>
void TDLI<Type>::mergesort(Sint32 (*f)(Type* a,Type* b))
{
   DL_Iter<void*>::mergesort( (Sint32 (*)(void*,void*)) f);
}

template<class Type>
void TDLI<Type>::cocktailsort(Sint32 (*f)(Type* a,Type* b),void (*f2)(Type* c,Type* d))
{
   DL_Iter<void*>::cocktailsort( (Sint32 (*)(void*,void*)) f,(void (*)(void*,void*)) f2);
}

template<class Type>
TDLISort<Type>::TDLISort(DL_List<void*>* list, Sint32 (*newfunc)(void*,void*))
								 :DL_SortIter<void*>(list, newfunc)
{
}

template<class Type>
TDLISort<Type>::~TDLISort()
{
}

template<class Type>
void TDLISort<Type>::delete_all()
{
   DL_Node<void*>* node;
   Type* obj;
	for (Sint32 i=0; i< NB; i++)
	{
		node = HD;
		HD = node->_next;
      obj=(Type*)(node->_item);
      delete obj;
		delete node;
	}
	NB=0; //reset memory used (no lost pointers)
   TL=RT;
   _current=RT;
}

// is item element of the list?
template<class Type>
bool TDLISort<Type>::has(Type* otheritem)
{
   return DL_Iter<void*>::has( (void*) otheritem);
}

// goto to item
template<class Type>
bool TDLISort<Type>::toitem(Type* item)
{
   return DL_Iter<void*>::toitem( (void*) item);
}

// get current item
template<class Type>
Type*    TDLISort<Type>::item()
{
   return (Type*) DL_Iter<void*>::item();
}

template<class Type>
TDLIStack<Type>::TDLIStack(DL_List<void*>* newlist):DL_StackIter<void*>(newlist)
{
}

// destructor TDLI
template<class Type>
TDLIStack<Type>::~TDLIStack()
{
}

// plaats nieuw item op stack
template<class Type>
void TDLIStack<Type>::push(Type* newitem)
{
	DL_StackIter<void*>::push((Type*) newitem);
}


// haal bovenste item van stack
template<class Type>
Type* TDLIStack<Type>::pop()
{
  return (Type*) DL_StackIter<void*>::pop();
}

#endif
