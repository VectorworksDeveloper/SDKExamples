/*
Program	LINE.H
Purpose	Mainy used for calculating crossings
Last Update	12-12-1995
*/

#ifndef LINE_H
#define LINE_H

#ifdef __GNUG__
#pragma interface
#endif

#include "link.h"

// Status of a point to a line
enum PointStatus {LEFT_SIDE, RIGHT_SIDE, ON_AREA, IN_AREA};

class Graph;

class KBoolLine
{
	public:

		// constructors and destructor
		KBoolLine();
		KBoolLine(KBoolLink*);
		~KBoolLine();

		void			Set(KBoolLink *);
		KBoolLink*		GetLink();

      //! Get the beginnode from a line
		Node*		GetBeginNode();		
      
      //! Get the endnode from a line
		Node*		GetEndNode();   										  	

      //! Check if two lines intersects
		Sint32					CheckIntersect(KBoolLine*, double Marge);	

      //! Intersects two lines
		Sint32					Intersect(KBoolLine*, double Marge);    	 
		Sint32               Intersect_simple(KBoolLine * lijn);
		bool				   Intersect2(Node* crossing,KBoolLine * lijn);

      //!For an infinite line
		PointStatus			PointOnLine(Node* a_node, double& Distance, double Marge ); 

      //!For a non-infinite line
		PointStatus			PointInLine(Node* a_node, double& Distance, double Marge ); 

      //! Caclulate Y if X is known
      B_INT					Calculate_Y(B_INT X); 								
		B_INT         		Calculate_Y_from_X(B_INT X);
		void              Virtual_Point( LPoint *a_point, double distance);

      //! assignment operator
		KBoolLine& 			operator=(const KBoolLine&); 					

		Node* 				OffsetContour(KBoolLine* const nextline,Node* last_ins, double factor,Graph *shape);
		Node* 				OffsetContour_rounded(KBoolLine* const nextline,Node* _last_ins, double factor,Graph *shape);
		bool 				   OkeForContour(KBoolLine* const nextline,double factor,Node* LastLeft,Node* LastRight, LinkStatus& _outproduct);
		bool				   Create_Ring_Shape(KBoolLine* nextline,Node** _last_ins_left,Node** _last_ins_right,double factor,Graph *shape);
		void 					Create_Begin_Shape(KBoolLine* nextline,Node** _last_ins_left,Node** _last_ins_right,double factor,Graph *shape);
		void 					Create_End_Shape(KBoolLine* nextline,Node* _last_ins_left,Node* _last_ins_right,double factor,Graph *shape);

      //! Calculate the parameters if nessecary
		void  CalculateLineParameters(); 								

      //! Adds a crossing between the intersecting lines
		void  AddLineCrossing(B_INT , B_INT , KBoolLine *); 		

		void  AddCrossing(Node *a_node);
		Node* AddCrossing(B_INT X, B_INT Y);
		bool  ProcessCrossings(TDLI<KBoolLink>* _LI);

// Linecrosslist
		void	SortLineCrossings();
		bool	CrossListEmpty();
		DL_List<void*>*		GetCrossList();
//		bool	HasInCrossList(Node*);

	private:

      //! Function needed for Intersect
		Sint32   ActionOnTable1(PointStatus,PointStatus); 							
      //! Function needed for Intersect
		Sint32   ActionOnTable2(PointStatus,PointStatus); 						

		double 		_AAA;
		double		_BBB;
		double		_CCC;
		KBoolLink*	_link;
		bool			_valid_parameters;

      //! List with crossings through this link
		DL_List<void*>	 *linecrosslist;
};

#endif
