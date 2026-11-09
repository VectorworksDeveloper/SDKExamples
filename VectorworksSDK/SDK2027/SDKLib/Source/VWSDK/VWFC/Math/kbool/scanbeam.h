/*
	Program:	SCANBEAM.H
*/

#ifndef SCANBEAM_H
#define SCANBEAM_H

#ifdef __GNUG__
#pragma interface
#endif

#include "_lnk_itr.h"

#include "record.h"
#include "link.h"

enum SCANTYPE{NODELINK,LINKLINK,GENLR,LINKHOLES,INOUT};

class ScanBeam : public DL_List<void*>
{
	public:
			ScanBeam();
			~ScanBeam();
         void SetType(Node* low,Node* high);

			bool  FindNew(SCANTYPE scantype,TDLI<KBoolLink>* _II);
			bool  RemoveOld(SCANTYPE scantype,TDLI<KBoolLink>* _II);

   private:

			bool  ProcessHoles(bool atinsert,TDLI<KBoolLink>* _LI);
         void	Process_LinkToLink_Crossings();			// find crossings
			Sint32 	Process_PointToLink_Crossings();
			Sint32 	Process_LinkToLink_Flat(KBoolLine* flatline);
         void	SortTheBeam();
			bool 	checksort();
			bool 	writebeam();
			void	Calc_Ysp();
			Sint32 	FindCloseLinksAndCross(TDLI<KBoolLink>* _II,Node* _lowf);
         void 	Generate_INOUT(Sint32 graphnumber);

         Node*				_low;
         TDLI<Record> 	_BI;
         Sint32 				lastinserted;
         BEAM_TYPE		_type;
};

#endif 
