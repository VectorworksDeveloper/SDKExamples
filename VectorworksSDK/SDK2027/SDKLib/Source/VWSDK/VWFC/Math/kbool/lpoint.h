/* @@(#) $Source: /cvs/wlv/src/pde/source/adb/kbool/lpoint.h,v $ $Revision: 1.1 $ $Date: 2001/09/26 01:59:41 $ */

/*
Program	LPOINT.H
Purpose	Definition of GDSII pointtype structure
Last Update	12-12-1995
*/

#ifndef LPOINT_H
#define LPOINT_H

#ifdef __GNUG__
#pragma interface
#endif

#include "booleng.h"

class LPoint
{
	public:
		LPoint();
		LPoint(B_INT const ,B_INT const);
		LPoint(LPoint* const);

		void		Set(const B_INT,const B_INT);
		void		Set(const LPoint &);

		LPoint		GetPoint();
		B_INT		GetX();
		B_INT		GetY();
		void 		SetX(B_INT);
		void		SetY(B_INT);
		bool		Equal(const LPoint a_point, B_INT Marge );
		bool		Equal(const B_INT,const B_INT , B_INT Marge);
		bool		ShorterThan(const LPoint a_point, B_INT marge);
		bool		ShorterThan(const B_INT X, const B_INT Y, B_INT);

		LPoint	&operator=(const LPoint &);
		LPoint	&operator+(const LPoint &);
		LPoint	&operator-(const LPoint &);

		LPoint	&operator*(Sint32);
		LPoint	&operator/(Sint32);

		Sint32		operator==(const LPoint &) const;
		Sint32		operator!=(const LPoint &) const;

	protected:
		B_INT _x;
		B_INT _y;

};

#endif
