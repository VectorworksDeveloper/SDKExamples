//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	MiniCad polygon object utility class
	


#include "StdHeaders.h"

#include "GCL/UMCPolygon.h"
#include "GCL/ULine.h"
#include "GCL/Unclassified.h"

struct FEONearestTwoPtsDataType	{
	Handle 	pickObj;
	WorldPt pickPt;
	WorldPt p1;
	WorldPt p2;
	Boolean firstSect;
	Boolean sectFound;
};

extern "C" void GS_API FEOGetPolySects(Handle selObj, CallBackPtr cbp, void* env);



WorldPt GS_API TMCPolygon::VectorFromlen2len(const WorldCoord len1, const WorldCoord len2)
{
	WorldPt retVect(0L,0L);
	//Debug("poly %lx ; len1 : %ld ; len2 : %ld\n",PolyHandle(),len1,len2);
	if (PolyHandle() && len1 > 0L && len2 > len1) {
	
		WorldCoord tl = 0.0;
		short i = 1;
		while (tl < len1) {
			tl += SegLength(i);
			i++;
		}
		WorldPt p1 = Vertex(i-1) + (len2-tl)*UnitVector(i-1);
		while (tl < len2) {
			tl += SegLength(i);
			i++;
		}
		//Debug("index after len2 :ld ; len1 : %ld ; len2 : %ld ; tl : %lf\n",i,len1,len2,tl);
		WorldPt p2 = Vertex(i-1) + (len2-tl)*UnitVector(i-1);
		
		retVect = p2-p1;
	}
	return retVect;
}



WorldPt GS_API TMCPolygon::VectorToPtAtLen(const WorldCoord len)
{
	WorldPt retPt(0.0,0.0);
	WorldCoord tl = 0.0;
	short i = 1;
	while (tl < len) {
		tl += SegLength(i);
		i++;
	}
	retPt = Vertex(i) + (len-tl)*UnitVector(i);
	return retPt;
}

void GS_API TMCPolygon::InitFEONearestTwoPtsData(const WorldPt p, void* env)
{
	FEONearestTwoPtsDataType* data = (FEONearestTwoPtsDataType*) env;
	
	data->pickObj = PolyHandle();
	data->pickPt = p;
	data->sectFound = false;
	
	data->p1 = Vertex(1);
	data->p2 = Closed() ? Vertex(1) : Vertex(NumVerts());	
	data->firstSect = true;
}


Boolean GS_API TMCPolygon::NearestTwoPts(const WorldPt p, WorldPt& p1, WorldPt& p2)
{
	if (PolyHandle() ) {
		FEONearestTwoPtsDataType	data;
		
		InitFEONearestTwoPtsData(p, &data);
		
		GS_ForEachObject(fCBP, allSelected+descendIntoGroups, FEOGetPolySects, &data);
		
		if (Closed()) {
			short index;
			if (PathLengthFromStart(data.p1) < PathLengthFromStart(data.p2) ) {
				if (!IsAVertex(data.p1,index)) {
					index = SegAtLenFromStart(PathLengthFromStart(data.p1));
					InsertVertex(data.p1, (short) ++index);
				}
				Rotate(index);
			}
			else {
				if (!IsAVertex(data.p2,index)) {
					index = SegAtLenFromStart(PathLengthFromStart(data.p2));
					InsertVertex(data.p2, (short) ++index);
				}
				Rotate(index);
			}
		}
		
		p1 = data.p1;
		p2 = data.p2;
		
		return data.sectFound;
	}
	return false;
}


extern "C" void GS_API FEOGetPolySects(Handle selObj, CallBackPtr cbp, void* env)
{
	FEONearestTwoPtsDataType* data = (FEONearestTwoPtsDataType*) env;
	Boolean intersectFound = false;
	Handle h;
	
	if (selObj == data->pickObj) {
		intersectFound = true;
		Handle selfSectObj = GS_DuplicateObject(cbp, selObj);
		h = GS_IntersectObjects(cbp, selfSectObj, selObj, true);
		GS_DeleteObject(cbp, selfSectObj, false);
	}
	else 
	
		h = GS_IntersectObjects(cbp, data->pickObj, selObj, true);
		
	if (h ) {
		//Debug("intersections\n");

		size_t hSize;
		GS_GetHandleSize(cbp, (Handle) h, hSize);
		size_t num = hSize/sizeof(WorldPt);
		//Debug("there are %ld intersections \n",num);
		GS_HLock(cbp, (Handle) h);
		TMCPolygon poly(cbp, data->pickObj);
		
		WorldPt* cp = (WorldPt*) *h;
		intersectFound = true;
		
		
		if (data->firstSect && poly.Closed()) {
			data->p2 = *cp;
			data->p1 = *cp;
			data->firstSect = false;
		}
		
		for (size_t i = 0 ; i < num ; i++) {		// for each of the intersection points
		
			//DrawObject(cbp, CreateLocus(cbp,*cp),true);
			if ( poly.PositivePtToPt(data->pickPt,*cp) < poly.PositivePtToPt(data->pickPt,data->p2) ) {
				data->p2 = *cp;
			}

			else if ( poly.NegativePtToPt(data->pickPt,*cp) > poly.NegativePtToPt(data->pickPt,data->p1) ) {
				data->p1 = *cp;
			}			
			cp++;
		}
			
		GS_HUnlock(cbp, (Handle) h);
		GS_DisposeHandle(cbp, (Handle) h);
	}
	data->sectFound = data->sectFound || intersectFound;
}

WorldCoord GS_API TMCPolygon::PositivePtToPt(const WorldPt startPt, const WorldPt endPt)
{
	if (PolyHandle()) {
		WorldCoord toEnd = PathLengthFromStart(endPt);
		WorldCoord toStart = PathLengthFromStart(startPt);
		
		if (!Closed() ) {
			return toEnd-toStart > 0.0 ? toEnd-toStart : 1.0e23; 
		}
		else
			return toEnd-toStart > 0.0 ? toEnd-toStart : GetPolyLength()+(toEnd-toStart); 
	}
	return 0.0;

}

WorldCoord GS_API TMCPolygon::NegativePtToPt(const WorldPt startPt, const WorldPt endPt)
{
	if (PolyHandle() ) {
		WorldCoord toEnd = PathLengthFromStart(endPt);
		WorldCoord toStart = PathLengthFromStart(startPt);
		
		if (!Closed() ) {
			return toEnd-toStart < 0.0 ? toEnd-toStart : -1.0e23; 
		}
		else
			return toEnd-toStart < 0.0 ? toEnd-toStart : -(GetPolyLength()-(toEnd-toStart)); 
	}
	return 0.0;
}



Boolean GS_API TMCPolygon::CutPolyPtToPt(const WorldPt pickPt, const WorldPt p1, const WorldPt p2, 
								Handle& h1, Handle& h2, Handle& h3)
{

	if ( (PolyHandle() && !h1 && !h2 && !h3 &&
		(p1 != Vertex(1) && p2 != Vertex(NumVerts()) )) || ( p2 != Vertex(1) && p1 != Vertex(NumVerts()) ) ) {
	
		WorldCoord p1Len = PathLengthFromStart(p1);
		WorldCoord p2Len = PathLengthFromStart(p2);
		short index1 = SegAtLenFromStart(p1Len);
		short index2 = SegAtLenFromStart(p2Len);
		(void) PathLengthFromStart(pickPt);
				
		if (p1 == Vertex(1) || p1 == Vertex(NumVerts()) ){ 
		
			//Debug("index2 : %ld\n",index2);
			if (NotAVertex(p2)) {
				InsertVertex(p2, index2+1);
				index2++;
			}
			Split(index2, h2, h1);
		}
		else if ( p2 == Vertex(1) || p2 == Vertex(NumVerts()) ) {
			//Debug(" p1 is it\n");
			if (NotAVertex(p1)) {
				InsertVertex(p1, index1+1);
				index1++;
			}
			Split(index1, h1, h2);
		}
		
		else {
			//Debug(" p1 and p2 are it\n");
			if (NotAVertex(p1)) {
				InsertVertex(p1, index1+1);
				index1++;
			}
			
			Handle temp = nil;

			if ( p1Len <= p2Len ) {
				Split(index1, h1, temp);
				
				if (gSDK->GetObjectTypeN ( temp) == polyNode) {
					{	TMCPolygon poly(fCBP, temp);
						if (!poly.IsAVertex(p2,index2)) {
							index2 = poly.SegAtLenFromStart(poly.PathLengthFromStart(p2));
							poly.InsertVertex(p2, index2+1);
							index2++;
						}
						if (poly.PolyHandle())
							poly.Split(index2, h2, h3);
					}
					GS_DeleteObject(fCBP,temp, false);
				}
				else {
					h2 = temp;
				}
			}
			else {
				//Debug("Do Nothing Case \n");	
			}
		}
		return (h1 || h2 || h3);
	}
	return false;
}

void GS_API TMCPolygon::Split(const short index, Handle& h1, Handle& h2)
{	
	if (PolyHandle() && NumVerts() > 2) {
	
		short lastIndex = Closed() ? NumVerts()+1 : NumVerts();
		
		if (index > 2 && index < lastIndex-1) {
			//Debug("sub div into two polys\n");
			h1 = GS_CreatePolyshape(fCBP);
			
			{	TMCPolygon poly(fCBP, h1);
				for (short i = 1; i <= index; i++)
					poly.AddVertex(Vertex(i));
			}
			
			h2 = GS_CreatePolyshape(fCBP);
			{	TMCPolygon poly(fCBP, h2);
				for (short i = index; i <= lastIndex; i++)
					poly.AddVertex(Vertex(i));
			}
		}	
		else {
		
			if (index == 2) {
				//Debug("sub div into line and poly\n");

				h1 = GS_CreateLine(fCBP, Vertex(1),Vertex(2));
				h2 = GS_CreatePolyshape(fCBP);

				{	TMCPolygon poly(fCBP, h2);
					for (short i = 2; i <= lastIndex; i++)
						poly.AddVertex(Vertex(i));
				}
			}
			else {
				//Debug("sub div into poly and line \n");
				h1 = GS_CreatePolyshape(fCBP);
				{	TMCPolygon poly(fCBP, h1);
					for (short i = 1; i <= lastIndex-1; i++)
						poly.AddVertex(Vertex(i));
				}
				h2 = GS_CreateLine(fCBP, Vertex(lastIndex-1),Vertex(lastIndex));
			}
		}
		

	}
}

void GS_API TMCPolygon::MakeRegular(const WorldPt center, const short numSides, const WorldCoord radius, const WorldCoord startAngle)
{
	if (GS_CountVertices(fCBP, PolyHandle()) == 0 && numSides != 0) {
		
		GS_SetPolyShapeClose(fCBP,PolyHandle(),true); 
		
		WorldPt vertex;
		
		WorldCoord angleInc = 360.0/numSides;
		WorldCoord angle = startAngle;
		
		while (angle < startAngle+359.9) {
			vertex = center + radius*UnitVectorFromDeg(angle);
			this->AddVertex(vertex);
			angle = angle+angleInc;
		}
		
	}
		
}

