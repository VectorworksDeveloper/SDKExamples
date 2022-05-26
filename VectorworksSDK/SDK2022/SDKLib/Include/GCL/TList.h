//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef _TLinkedList_
#define _TLinkedList_

#if THINK_C || __SC__
#include <oops.h>
#endif

#if _WINDOWS
	#include <MacTypes.h>
#endif

struct TLinkedListNode
{
	void *data;
	TLinkedListNode *prev;
	TLinkedListNode *next;
};

class TLLIterator;


#if THINK_C || __SC__
class TLinkedList : public PascalObject
#else
class TLinkedList
#endif
{
	protected:	
		TLinkedListNode		*head;
		TLinkedListNode		*tail;
		TLinkedListNode		*current;
	
	public:
		Boolean GS_API ILinkedList();
		virtual void GS_API Free();
		
		Boolean Empty() {return head == nil;}
		
		void *Get() {if (current) return current->data; else return nil;}
	
		Boolean GS_API InsertBefore(void *data);
		Boolean GS_API InsertAfter(void *data);
		void GS_API Remove();
		
		TLinkedListNode* GetListHead() { return head; }
		TLinkedListNode* GetListTail() { return tail; }
		
		void First() {current = head;}
		void Last() {current = tail;}
		Boolean GS_API Next();
		Boolean GS_API Previous();
		short GS_API SetPos(short pos);
	
};


class TLLIterator 
{
	protected:
		TLinkedListNode		*current;
		TLinkedList 		*list;
	
	public:
		TLLIterator() {current = nil; list = nil;}
		TLLIterator(TLinkedList *theList)  { current = nil; list = theList;}

		void *FirstItem() { current = list->GetListHead(); return (current ? current->data : nil); }
		Boolean More() { return (current != nil); }
		void *NextItem() { if (!current) return nil; current = current->next; return (current ? current->data : nil); }

		//void *PrevItem()	{ if (!current) return nil;  current = current->prev; return (current ? current->data : nil); }

};


enum CompareResult {k1LessThan2, k1Equal2, k1GreaterThan2};

class TSortedList : public TLinkedList
{
	protected:
		
		Boolean insertionSort;
	
	public:
		Boolean GS_API ISortedList();
		virtual void GS_API Free();
		
		void GS_API Sort();
		void Sorting(Boolean sortOnInsert) { insertionSort = sortOnInsert; }
		// current will equal first after where key would be if key were there
		Boolean GS_API Find(void *key);
		void GS_API Insert(void *data);
		
		// OVERRIDE this if you want a sorted list
		virtual CompareResult GS_API Compare(void *one, void *two);
};



#endif
