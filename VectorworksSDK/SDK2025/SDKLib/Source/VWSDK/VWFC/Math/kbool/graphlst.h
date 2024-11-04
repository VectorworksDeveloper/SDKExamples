/* @@(#) $Source: /cvs/wlv/src/pde/source/adb/kbool/graphlst.h,v $ $Revision: 1.1 $ $Date: 2001/09/26 01:59:40 $ */

/*
Program	GRAPHLST.H
Purpose	Implements a list of graphs (header)
Last Update	11-03-1996
*/

#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#ifdef __GNUG__
#pragma interface
#endif

#include "_lnk_itr.h"

#include "graph.h"

class Debug_driver;


class GraphList: public DL_List<void*>
{
	public:

		friend class Debug_driver;

		GraphList();
		~GraphList();

		void				MakeOneGraph(Graph *total);

		void				Prepare(Graph *total);
		void 				MakeRings();
		void 				Correction();

		void				Simplify( double marge);
		void 				Smoothen( double marge);
		void 				Merge();
		void 				Boolean(BOOL_OP operation);

      void           WriteGraphs();

	protected:
		void				Renumber();
		void				UnMarkAll();

};


#endif
