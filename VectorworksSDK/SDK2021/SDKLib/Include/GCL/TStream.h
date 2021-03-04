//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef _TSTREAM_
#define _TSTREAM_


#if THINK_C || __SC__
	#include <oops.h>
#endif
#include <Files.h>
#include <Errors.h>

// GS_SDKPPC_JAK - 
// Now that the SDK plug-ins are PPC, the type "extended" is not defined for PPC.
// So I can either define double_t as double, or call fp.h to do it for me, or simply replace double_t with double here.
// typedef extended double_t;
// typedef double double_t; 
#include "fp.h"		// fp.h will define double_t to be double on PPC.


#if THINK_C || __SC__
class TStream : PascalObject
#else
class TStream
#endif
{
	public:
		TStream() {}
		virtual void GS_API Free();
		
		virtual OSErr GS_API GetSize(Sint32 &size);
		virtual OSErr GS_API SetSize(Sint32 size);
		virtual OSErr GS_API GetPos(Sint32 &pos);
		virtual OSErr GS_API SetPos(Sint32 pos);
		virtual OSErr GS_API SkipBytes(Sint32 d);
		virtual OSErr GS_API ToStart();
		virtual OSErr GS_API ToEnd();
		
		virtual Boolean GS_API AtEnd();
		
		virtual OSErr GS_API ReadBytes(void *buf, Sint32 &count);
		OSErr ReadBytesNC(void *buf, Sint32 count)
			{ Sint32 c = count; return this->ReadBytes(buf,c); }
		virtual OSErr GS_API UnReadBytes(Sint32 count);

		OSErr operator>>(char &c)				{return this->ReadBytesNC(&c,1);}
		OSErr operator>>(unsigned char &c)		{return this->ReadBytesNC(&c,1);}
		OSErr operator>>(Sint32 &l)				{return this->ReadBytesNC(&l,sizeof(Sint32));}
		OSErr operator>>(short &s)				{return this->ReadBytesNC(&s,sizeof(short));}
		OSErr operator>>(double_t &d)			{return this->ReadBytesNC(&d,sizeof(double_t));}
};

class TFileStream : public TStream {
	protected:
		short 	fRefNum;
		
	public:
		TFileStream(): fRefNum(0) 	{}
		virtual void GS_API Free();
		
		OSErr GS_API Open(Str255 fileName, short vRefNum);
		OSErr GS_API Close();
	
		virtual OSErr GS_API GetSize(Sint32 &size);
		virtual OSErr GS_API SetSize(Sint32 size);
		virtual OSErr GS_API GetPos(Sint32 &pos);
		virtual OSErr GS_API SetPos(Sint32 pos);
		virtual OSErr GS_API SkipBytes(Sint32 d);
		virtual OSErr GS_API ToStart();
		virtual OSErr GS_API ToEnd();
		virtual Boolean GS_API AtEnd();
		
		OSErr GS_API ReadBytes(void *buf, Sint32 &count);
		OSErr GS_API UnReadBytes(Sint32 count);
};

#endif
