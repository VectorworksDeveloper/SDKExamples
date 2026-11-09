//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Quarter Arc object utility class

#ifndef _UQARC_
#define _UQARC_

class TQArc
{
	protected:
		WorldRect 	fBounds;	
		short 		fQuadrant;
		
			
	public:
		TQArc()
			{ fBounds.Set(0L,0L,0L,0L); fQuadrant = 1L; }
		TQArc(WorldRect bounds) 
			{ fBounds = bounds; fQuadrant = 1L; }
		TQArc(WorldRect bounds, short quadrant) 
			{ fBounds = bounds; fQuadrant = quadrant;}
		TQArc(CallBackPtr cbp, Handle rQArc)
			{GS_GetObjectBounds(cbp, rQArc, fBounds); fQuadrant = GS_GetQArcQuadrant(cbp, rQArc);}
		
		
};

class TMCQArc : public TQArc
{
	protected:
		Handle fQArcHandle;
		CallBackPtr fCBP;	
		
	public:
	
		TMCQArc(CallBackPtr cbp, Handle qArc)
			{ GS_GetObjectBounds(cbp, qArc, fBounds); fQuadrant = GS_GetQArcQuadrant(cbp, qArc);
			  fQArcHandle = qArc; fCBP = cbp;}
			   
		WorldRect Bounds() { return fBounds; }
		short Quadrant() { return fQuadrant; }
		Handle QArcHandle() { return fQArcHandle; }
		CallBackPtr CBP() { return fCBP; }
		
		WorldRect GS_API QArcOvalBox();
		
		Handle GS_API ArcFromQArc();
		
		Handle GS_API OffsetQArc(const WorldCoord offset);
		WorldCoord GS_API Offset(WorldPt pt);
		
		void GS_API DrawCoordQArc();

		
		void DrawBounds() {GS_DrawCoordRect(fCBP, fBounds);}
};

#endif

