/*
Program	NODE.H
Purpose	Holds a GDSII node structure (Header)
*/

#ifndef NODE_H
#define NODE_H

#ifdef __GNUG__
#pragma interface
#endif

//#include <math.h>
#include "booleng.h"

#include "lpoint.h"

#include "link.h"
#include "_lnk_itr.h" // LinkBaseIter

#ifdef  MAXDOUBLE
#undef  MAXDOUBLE
#endif
#define MAXDOUBLE       1.7976931348623157e+308

enum NodePosition { N_LEFT, N_ON, N_RIGHT};

class Node : public LPoint
{
	public:
		// friend must be deleted in the final version!
		friend class Debug_driver;

		// constructors and destructors
		Node();

		Node(const B_INT, const B_INT);
	
		Node(LPoint* const a_point);
		Node(Node * const);
		Node& operator=(const Node &other_node);
		~Node();

		//public member functions
		void		AddLink(KBoolLink*);
		DL_List<void*>* GetLinklist();

		KBoolLink*  GetMost( KBoolLink* const prev ,LinkStatus whatside);
		KBoolLink* 	GetNotFlat();

		Sint32		Merge(Node*);
		void	RemoveLink(KBoolLink*);
		bool	Simplify(Node* First, Node* Second, B_INT Marge );

		//  memberfunctions for maximum performance
		void        Round(B_INT grid);
		KBoolLink*	GetIncomingLink();

		Sint32		   GetNumberOfLinks();
		KBoolLink* GetNextLink();
		KBoolLink* GetOtherLink(KBoolLink*);
		KBoolLink* GetOutgoingLink();
		KBoolLink* GetPrevLink();

		KBoolLink* Follow(KBoolLink* const prev );
		KBoolLink* GetBinHighest(bool binset);

	protected:
		DL_List<void*>*		_linklist;
   private:
		static TDLI<KBoolLink> 	_linkiter;
};

#endif
