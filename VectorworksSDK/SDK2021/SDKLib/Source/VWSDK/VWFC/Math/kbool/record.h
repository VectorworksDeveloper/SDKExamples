/*
	Program:	RECORD.H
*/

#ifndef RECORD_H
#define RECORD_H

#ifdef __GNUG__
#pragma interface
#endif

class Node;
#include "booleng.h"

#include "link.h"
#include "line.h"

enum BEAM_TYPE { NORMAL,FLAT};

enum DIRECTION  {GO_LEFT,GO_RIGHT};

extern void DeleteRecordPool();

class Record
{
	public:
					void deletepool();

					Record(KBoolLink* link);

					~Record();

					void* operator new(size_t size);

					void operator delete(void* recordptr);

					void SetNewLink(KBoolLink* link);

					void Set_Flags();

					void Calc_Ysp(Node* low);

					KBoolLink* GetLink();

					KBoolLine* GetLine();

					B_INT	Ysp();

					void SetYsp(B_INT ysp);

					DIRECTION Direction();

					bool Calc_Left_Right(Record* record_above_me);

					bool Equal(Record*);

	private:
					KBoolLine   _line;

					B_INT 		_ysp;

               //! going left are right in beam
					DIRECTION	_dir: 1;    

               //! how far in group_a
               Sint32         _a;               

               //! how far in group_b
               Sint32         _b;               

};

#endif 
