//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	MiniCad polyline object utility class

#ifndef _UPOLYLINE_
#define _UPOLYLINE_

const double PLPi = 3.141592653589793;
const double PLRadToDeg = 180.0 / PLPi;		
const double PLDegToRad = PLPi/180.0;		


class TMCPolyline
// This class was a complete monstrosity of incorrect use of WorldCoord for anything that moved under the sun.
// should be better now but revisit. XXX_JDW_MISC
{
	protected:
		Handle  	fPolyHandle;
		short 		fNumVerts;
		Boolean 	fClosed;
		CallBackPtr	fCBP;
		
	public:
		TMCPolyline() { fPolyHandle = nil; fNumVerts = 0L; fClosed = false; fCBP = nil; }
		GS_API TMCPolyline(CallBackPtr cbp, Handle thePolyShape);

		Handle PolyHandle() { return this->fPolyHandle; }		
		short NumVerts() { return this->fNumVerts; }
		Boolean Closed() { return this->fClosed; }
		
		/*
			For each of the following that return information about a side/edge of the polyshape, index 
			refers to the start index for that side/edge.
		*/

		void GS_API DrawCoordPoly();
		
		void GS_API AddVertex(const WorldPt& p, VertexType vType, WorldCoord arcRadius);
		
		void GS_API SetVertex(short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius);

		void GS_API InsertVertex(const WorldPt& p, short beforeVertex, VertexType vType, WorldCoord arcRadius);
		
		short IndexInRange(short index) { return (index % fNumVerts > 0) ? index % fNumVerts :  fNumVerts + index % fNumVerts; }
			
		WorldPt GS_API Vector(const short index, const Boolean controlPoint);					
		
		WorldPt UnitVector(const short index, const Boolean controlPoint) 
			{ return WorldPt(Vector(index,controlPoint)).Normal(); }
			
		WorldPt GS_API UnitPerpVector(const short index, const Boolean controlPoint);
		
		WorldCoord SegLength(const short index, const Boolean controlPoint) 
			{ return WorldPt(this->Vector(index, controlPoint)).Magnitude(); }
		
		WorldPt GS_API Vertex(const short index);

		WorldPt GS_API ControlVertex(const short index);

		void GS_API Draw();
		
		void GS_API Invert();

		void GS_API Rotate(const short index);
		
		
		WorldCoord GS_API ScalarProjection(const WorldPt vector, const short index, const Boolean controlPoint);
		
		WorldPt VectorProjection(const WorldPt vector, const short index, const Boolean controlPoint) 
			{ return vector.Normal()*this->ScalarProjection(vector,index, controlPoint); }
			
		WorldCoord PerpScalarProjection(const WorldPt vector, const short index, const Boolean controlPoint) 
			{ return DotProduct(vector,this->UnitPerpVector(index, controlPoint)); }

		short GS_API NearestSegStart(WorldPt pt, WorldCoord& dist);
		short GS_API NearestSegStart(const WorldPt pt);
		WorldPt GS_API VectorFromSegStart(const short index, const WorldPt pt);
		WorldPt GS_API VectorFromNearestSegStart(const WorldPt pt);
		WorldCoord GS_API SumDistToBothVerticies(const short index, const WorldPt pt);	
		WorldCoord GS_API MinSumDistToBothVerticies(const WorldPt pt, WorldCoord& index);	
		WorldCoord GS_API MinDistTo(const WorldPt pt, WorldCoord& index, const Boolean controlPoint);
		WorldCoord GS_API PathLengthFromStart(const WorldPt pt);
		double GS_API ATanAngleRad(const short index, const Boolean controlPoint);
		double ATanAngleDeg(const short index, const Boolean controlPoint)
			{ return this->ATanAngleRad(index, controlPoint) * PLRadToDeg; }
		short GS_API VectorQuadrant(const short index, const Boolean controlPoint);
		WorldCoord GS_API Angle0To2Pi(const short index, const Boolean controlPoint);
		WorldCoord  Angle0To360(const short index, const Boolean controlPoint)
			{ return this->Angle0To2Pi(index, controlPoint) * PLRadToDeg; }
		Boolean GS_API GetIntersection(WorldPt *OutputVertex, WorldPt FormerLineStart, 
			WorldPt FormerLineEnd, WorldPt LatterLineStart, WorldPt LatterLineEnd);
		double GS_API  EuclideanDistanceSquaredOver10ToThe8th(WorldPt Point1, WorldPt Point2);
		WorldCoord GS_API  CityBlockDistance(WorldPt FormerVertex, WorldPt LatterVertex);
		WorldCoord GS_API Offset(const WorldPt pt);
		Boolean GS_API  RemoveCrossovers(CallBackPtr fCBP, Handle poly, const WorldCoord offset);
		Boolean GS_API  RemoveBowTies(CallBackPtr fCBP, Handle poly);

		Boolean GS_API  DirectionAboutTheSame(WorldPt FormerLineStart, WorldPt FormerLineEnd, 
			WorldPt LatterLineStart, WorldPt LatterLineEnd, double threshold);
			// Determines whether two lines are running in about the same direction.  Returns TRUE iff
			//	the normalized dot product of the associated vectors exceeds the threshold.
		short GS_API CalcMaxCells(Handle thePoly, short cnvrtRes);
		Boolean GS_API PolygonalizeByColinearity(Handle poly, short CurrentVertexCount, 
			WorldCoord ColinearityThreshold);
		Handle GS_API OffsetPoly(const WorldCoord off);
		WorldPt GS_API OffsetVertex(const short index, const WorldCoord offset, const Boolean controlPoint);
		WorldCoord GS_API AngleBetweenRad(const short index, const Boolean controlPoint);
		WorldCoord AngleBetweenDeg(const short index, const Boolean controlPoint)
			{ return this->AngleBetweenRad(index,controlPoint) * PLRadToDeg; }
		Boolean EndPointVertex(const short index)
			{ return ((index == 1 || index == fNumVerts) && !GS_GetPolyShapeClose(fCBP, fPolyHandle) ); }
		WorldPt GS_API OffsetVector(const short index, const WorldCoord offset, const Boolean controlPoint);

		Boolean GS_API PtInSegArea(const short index, const WorldPt pt);
		Boolean ConcaveOnLeft(const short index, const Boolean controlPoint)
			{ return (DotProduct(this->UnitVector(this->IndexInRange(index),controlPoint),
								 this->UnitPerpVector(this->IndexInRange(index-1),controlPoint)) > 0); }

		


		Boolean GS_API ArcVertex(const short index, WorldPt& vertex, 
							WorldPt& startPt, WorldPt& endPt, WorldPt& centerPt);
							
		WorldCoord GS_API ArcRadius(const short index);
		
		WorldCoord GS_API MCArcRadius(const short index);
		
		VertexType GS_API VertType(const short index);
		
		WorldPt GS_API PriorControlPoint(const short index);
		
		WorldPt VectorToPriorControlPoint(const short index)
			{ return PriorControlPoint(index) - ControlVertex(index); }
			
		WorldPt GS_API NextControlPoint(const short index);
		
		WorldPt VectorToNextControlPoint(const short index)
			{ return NextControlPoint(index) - ControlVertex(index); }
			
		void GS_API AddTMCVertex(WorldPt vertex, VertexType vType, WorldCoord arcRadius);
								 
		WorldCoord GS_API OffsetRadius(const short index, WorldCoord offset);
		void GS_API DrawControlPoints(); 
		VertexType GS_API ControlNeighborhood(const short index, 
									WorldPt& prevCtrlPt, WorldPt& cntrlVertex, 
									WorldPt& nextCtrlPt, WorldPt& centerPt);
		void GS_API Test();
		Handle AssociatedPolgon() { return GS_ConvertToPolygon(fCBP, PolyHandle(), true); }
		WorldCoord GS_API GetPolyLength();
		
		short GS_API AddSplineCntrolPtsAt(const short index);
		void GS_API SetArcRad(const short index);
		void SetNumVerts() { fNumVerts = GS_CountVertices(fCBP, PolyHandle()); };	
		void GS_API AddSplineControlPtsAndSetArcRad();	
		void GS_API AddSplineControlPts();
		void GS_API AdjustArcVertex(const short index);
		Boolean PolyTurnsRight(const short index) 
			{ return (DotProduct(UnitVector(index-1,true),UnitPerpVector(index,true)) > 0.0); }
		Handle GS_API ControlPolygon();
		void GS_API AddCornerVertsBetweenCurveVerts();
		void GS_API OffsetControlVerts(const WorldCoord offset);
		WorldPt GS_API GetArcVertex(const short index, const WorldPt arcCenter, 
									const WorldPt arcBeg, const WorldPt arcEnd);
									
		void GS_API AddCurveEndPointsAtVert(const short index);

		void GS_API AddCurveEndPoints();

};


#endif

