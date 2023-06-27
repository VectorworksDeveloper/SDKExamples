//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	MiniCad polygon object utility class

#ifndef _UPOLYGON_
#define _UPOLYGON_


const double PSPi = 3.141592653589793;
const double PSRadToDeg = 180.0 / PSPi;		
const double PSDegToRad = PSPi/180.0;
const double tolerance = 1e-5;

class TMCPolygon
// XXX_JDW_MISC - this class is a complete mess.
// fNumVerts and some "index" variables were Coords, or longs, and as far as i know should all be shorts.
{
	protected:
		Handle  	fPolyHandle;
		short 		fNumVerts;
		Boolean 	fClosed;
		CallBackPtr	fCBP;
		
	public:
		TMCPolygon() { fPolyHandle = nil; fNumVerts = 0; fClosed = false; fCBP = nil; }
		GS_API TMCPolygon(CallBackPtr cbp, Handle thePolyShape);
		void CleanUpPolygon(Handle polygon, WorldCoord offset);
		Handle PolyHandle() { return this->fPolyHandle; }		
		short NumVerts() { return this->fNumVerts; }
		Boolean Closed() { return this->fClosed; }
		WorldCoord NearestDistance(WorldPt point);
		void GS_API AddVertex(const WorldPt& p);
		void AddVerticesToPoly();
		bool SelefIntersectingPolygon();
		
		void GS_API SetVertex(short vertexNum, const WorldPt& vertex);

		void GS_API InsertVertex(const WorldPt& p, short beforeVertex);

		void GS_API DeleteVertex(short vertexNum);
		void SetNumVerts() { fNumVerts = GS_CountVertices(fCBP, PolyHandle()); };	
		void GS_API DeleteVertices(const short startIndex, const short endIndex);
		
		/*
			For each of the following that return information about a side/edge of the polyshape, index 
			refers to the start index for that side/edge.
		*/
		
		inline short IndexInRange(const short index) { return (index % fNumVerts > 0) ? index % fNumVerts :  fNumVerts + index % fNumVerts; }

		WorldPt GS_API Vector(const short index);					
		
		inline WorldPt UnitVector(const short index) { return WorldPt(this->Vector(index)).Normal(); }
			
		WorldPt GS_API UnitPerpVector(const short index);
		
		inline WorldCoord SegLength(const short index) { return WorldPt(this->Vector(index)).Magnitude(); }
		
		WorldPt GS_API Vertex(const short index);

		void GS_API Draw();
		
		void GS_API Invert();
		void GS_API Rotate(const short index);
		void GS_API RotateSoPtOn1stSeg(const WorldPt p);
		WorldCoord GS_API ScalarProjection(const WorldPt vector, const short index);
		inline WorldPt GS_API VectorProjection(const WorldPt vector, const short index) { return vector.Normal()*this->ScalarProjection(vector,index); }
		inline WorldCoord GS_API PerpScalarProjection(const WorldPt vector, const short index) { return DotProduct(vector,this->UnitPerpVector(index)); }
		short GS_API NearestSegStart(WorldPt pt, WorldCoord& dist);
		short GS_API NearestSegStart(const WorldPt pt);
		WorldPt GS_API VectorFromSegStart(const short index, const WorldPt pt);
		WorldPt GS_API VectorFromNearestSegStart(const WorldPt pt);
		WorldCoord GS_API SumDistToBothVerticies(const short index, const WorldPt pt);	
		WorldCoord GS_API MinSumDistToBothVerticies(const WorldPt pt, short& index);	
		WorldCoord GS_API MinDistTo(const WorldPt pt, short& index);
		WorldCoord GS_API PathLengthFromStart(const WorldPt pt);
		short GS_API SegAtLenFromStart(const WorldCoord pathLength);
		double GS_API ATanAngleRad(const short index);
		inline double ATanAngleDeg(const short index)
			{ return this->ATanAngleRad(index) * PSRadToDeg; }
		short GS_API VectorQuadrant(const short index);
		WorldCoord GS_API Angle0To2Pi(const short index);
		inline WorldCoord  Angle0To360(const short index)
			{ return this->Angle0To2Pi(index) * PSRadToDeg; }
		void GS_API RemoveDuplicateVertices(void);	
		WorldCoord GS_API Offset(const WorldPt pt);
		WorldCoord GS_API AngleBetweenRad(const short index);
		inline WorldCoord AngleBetweenDeg(const short index)
			{ return this->AngleBetweenRad(index) * PSRadToDeg; }
		Handle GS_API OffsetPoly(const WorldCoord offset, const Boolean clipCollisions);
		WorldPt GS_API OffsetVertex(const short index, const WorldCoord offset);
		inline Boolean EndPointVertex(const short index)
			{ return ((index == 1 || index == fNumVerts) && !GS_GetPolyShapeClose(fCBP, fPolyHandle) ); }
		WorldPt GS_API OffsetVector(const short index, const WorldCoord offset);

		Boolean GS_API PtInSegArea(const short index, const WorldPt pt);

		inline Boolean ConcaveOnLeft(const short index)
			{ return (DotProduct(this->UnitVector(this->IndexInRange(index)),
								 this->UnitPerpVector(this->IndexInRange(index-1))) > 0); }

		void GS_API Test();
		WorldCoord GS_API GetPolyLength();
		Boolean GS_API NotAVertex(const WorldPt p);
		Boolean GS_API IsAVertex(const WorldPt p, short& index);
		WorldCoord GS_API Area();
		WorldPt GS_API Centroid();
		Boolean GS_API ThisOffVectIntersectsNextOffVect(const short index, const WorldCoord offset);
		Boolean GS_API IntersectsBackward(const short index, const WorldCoord offset);
		Boolean GS_API IntersectsForward(const short index, const WorldCoord offset);
		Boolean GS_API OffsetSegsIntersect(const short a, const short b, 
										WorldCoord offset, WorldPt& sect);

		void GS_API RemoveBadOffsetVerts(Handle poly, const WorldCoord offset);
		Boolean GS_API LastSegIntersectsSelf(short& indexPriorToIntersect, WorldPt& sect);
		WorldCoord GS_API TurnsThroughDeg();
		void GS_API DrawCoordPoly();
		Boolean GS_API SectPtOn(const WorldPt& p);
		WorldPt GS_API VectorFromlen2len(const WorldCoord len1, const WorldCoord len2);
		WorldPt GS_API VectorToPtAtLen(const WorldCoord len);
		Boolean GS_API NearestTwoPts(const WorldPt p, WorldPt& p1, WorldPt& p2);
		Boolean GS_API CutPolyPtToPt(const WorldPt pickPt, const WorldPt p1, const WorldPt p2, 
								Handle& h1, Handle& h2, Handle& h3);
		void GS_API Split(const short index, Handle& h1, Handle& h2);	
		void GS_API InitFEONearestTwoPtsData(const WorldPt p, void* env);
				
		WorldCoord GS_API PositivePtToPt(const WorldPt startPt, const WorldPt endPt);
		WorldCoord GS_API NegativePtToPt(const WorldPt startPt, const WorldPt endPt);
		Boolean GS_API TooSmall(const short index, const WorldCoord thresh);
		void GS_API MakeRegular(const WorldPt center, const short numSides, const WorldCoord radius, const WorldCoord startAngle);
								
};


#endif

