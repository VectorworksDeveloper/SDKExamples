/*
Program	LINK.H
Purpose	Part of a graph, connection between nodes (Header)
Last Update	11-03-1996
*/

#ifndef LINK_H
#define LINK_H

#ifdef __GNUG__
#pragma interface
#endif

#include "booleng.h"
#include "_lnk_itr.h"

enum LinkStatus {IS_LEFT,IS_ON,IS_RIGHT};

class LPoint;
class Node;

//!   segment within a graph 
/*
   A Graph contains a list of KBoolLink, the KBoolLink or connected by Node's. 
   Several KBoolLink can be connected to one Node. 
   A KBoolLink has a direction defined by its begin and end node.
   Node do have a list of connected KBoolLink's.
   So one can walk trough a graph in two ways:
   1- via its KBoolLink list 
   2- via the node connected to the KBoolLink's 
*/
class KBoolLink
{
	public:
		//! must be deleted in the final version!
		friend class Debug_driver;

		//! contructors 
		KBoolLink();

		//! contructors 
		KBoolLink(Sint32 graphnr, Node* begin, Node* end);

		//! contructors 
		KBoolLink(Node *begin, Node *end);

		//! destructors
		~KBoolLink();


      //! Merges the other node with argument
		void MergeNodes(Node* const);      				

      //! outproduct of two links
      LinkStatus OutProduct(KBoolLink* const two,double accur);              
		
      //! link three compared to this and two
      LinkStatus PointOnCorner(KBoolLink* const, KBoolLink* const);	

      //! Removes argument from the link
		void Remove(Node*);		
      
      //! replaces olddone in the link by newnode
		void Replace(Node* oldnode, Node* newnode);		

      //!top hole marking
		void SetTopHole(bool value);

      //!top hole marking
		bool IsTopHole();

      //! Marking functions
		void UnMark();
      //! Marking functions
		void Mark();
      //! Marking functions
		void SetMark(bool);
      //! Marking functions
		bool IsMarked();

      //! holelink Marking functions
		void SetHoleLink(bool val);

      //! holelink Marking functions
		bool GetHoleLink();
	
      //! Bin functions
		void SetNotBeenHere();
      //! Bin functions
		void SetBeenHere();
      //! Have you been here ??
		bool BeenHere();										

      //! Removes all the references to this
		void	UnLink();												

		//! functions for maximum performance
		Node*	GetBeginNode();      				  	

      //! Datamember access functions
		Node*	GetEndNode();
		Node*	GetLowNode();
		Node*	GetHighNode();

      //! Returns a next link beginning with argument
		KBoolLink* Forth(Node*); 	
      
		Sint32 GetGraphNum();
		bool GetInc();
      bool GetLeftA();
		bool GetLeftB();
		bool GetRightA();
		bool GetRightB();
		void GetLRO(LPoint*, Sint32&, Sint32&, double);

      //! Return a node not equal to arg.
		Node*	GetOther(const Node* const);			
      //! Is this link unused ?
		bool IsUnused();									

      //! Used for given operation ?
		bool IsMarked(BOOL_OP operation);            

      //! is this a hole link for given operation
		bool IsHole(BOOL_OP operation);				
      
		bool IsHoleMarked();

      //! Are the nodes on about the same coordinates ?
		bool IsZero(B_INT marge );		
		bool ShorterThan(B_INT marge );

      //! Resets the link
		void Reset(Node* begin, Node* end, Sint32 graphnr = 0);	
		void Set(Node* begin, Node* end);
		void SetBeginNode(Node*);
		void SetEndNode(Node*);
		void SetGraphNum(const Sint32);
		void SetInc(bool);
      void SetLeftA(bool);
		void SetLeftB(bool);
		void SetRightA(bool);
		void SetRightB(bool);
		void SetGroup(kbGroupType);
		kbGroupType Group();
		void SetHole(bool);
      //! Flag calculation (internal only)
		void SetLineTypes();
		void Reset();
		void Reset_flags();

      //!put in this direction
      void Redirect(Node* a_node); 

	protected:

      //! The mainitems of a link
		Node 		*beginnode, *endnode;
      //! Marker for walking over the graph
		bool	bin    	: 1;				
      //! Is this a part of hole ?
		bool	hole     : 1;				
      //! link that is toplink of hole?
		bool	hole_top : 1;				
      //! going in one more time in this graph if true  else going out one time
		bool 	Inc   	: 1;    			
      //! Is left in polygongroup A
      bool 	LeftA 	: 1;    			
      //! Is right in polygon group A
		bool 	RightA	: 1;    			
      //! Is left in polygon group B
		bool 	LeftB 	: 1;    			
      //! Is right in polygongroup B
		bool	RightB	: 1;    			
      //! General purose marker, internally unused
		bool	mark		: 1;    			
      //! link for linking holes
		bool	holelink : 1;    			
      //! Marker for Merge
		bool 	merge 	: 1;				
      //! Marker for substract a-b
		bool 	a_substract_b: 1;	  		
      //! Marker for substract b-a
		bool 	b_substract_a: 1;	  		
      //! Marker for intersect
		bool 	intersect: 1;				
      //! Marker for X-OR
		bool 	exor		: 1;				
      //! belongs to group A or B
		kbGroupType group : 1;      
      
		Sint32	graphnum;

};

#endif

