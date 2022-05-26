//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWWallObj::VWWallObj(const VWPoint2D& startPt, const VWPoint2D& endPt, double thickness/*=0*/)
{
	fhObject		= ::GS_CreateWall( gCBP, startPt, endPt, thickness );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create wall" );
}

VWWallObj::VWWallObj(const VWPoint2D& startPt, const VWPoint2D& ptOnArc, const VWPoint2D& endPt, double thickness/*=0*/)
{
	fhObject		= ::GS_CreateRoundWall( gCBP, startPt, ptOnArc, endPt, thickness );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create wall" );
}

VWWallObj::VWWallObj(const VWLine2D& line, double thickness)
{
	fhObject		= ::GS_CreateWall( gCBP, line.GetStart(), line.GetEnd(), thickness );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create wall" );
}

VWWallObj::VWWallObj(const VWArc2D& arc, double thickness)
{
	VWPoint2D	startPt, ptOnArc, endPt;
	arc.GetArc( startPt, ptOnArc, endPt );
	fhObject		= ::GS_CreateRoundWall( gCBP, startPt, ptOnArc, endPt, thickness );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create wall" );
}

VWWallObj::VWWallObj(MCObjectHandle h)
{
	short	type	= gSDK->GetObjectTypeN( h );
	VWFC_ASSERT( type == kWallNode );
	if ( type != kWallNode )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= h;
	VWFC_ASSERT( fhObject != nil );
}

VWWallObj::VWWallObj(const VWWallObj& src)
{
	fhObject		= src.fhObject;
}

VWWallObj::~VWWallObj()
{
	fhObject		= nil;
}

VWWallObj& VWWallObj::operator=(const VWWallObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

VWPoint2D VWWallObj::GetStartPoint() const
{
	VWFC_ASSERT( fhObject );
	WorldPt			startPt;
	EWallPathType wallPathType = gSDK->GetWallPathType( fhObject );
	if ( wallPathType == eWallPathType_arc )
	{
		VWArc2D		arc	= this->GetRoundWall( true );
		startPt		= arc.GetStartPt();
	}
	else if ( wallPathType == eWallPathType_line ) {
		WorldPt			endPt;
		::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );
	}
	return startPt;
}

VWPoint2D VWWallObj::GetEndPoint() const
{
	VWFC_ASSERT( fhObject );
	WorldPt		endPt;
	EWallPathType wallPathType = gSDK->GetWallPathType( fhObject );
	if ( wallPathType == eWallPathType_arc )
	{
		VWArc2D		arc	= this->GetRoundWall( true );
		endPt		= arc.GetEndPt();
	}
	else if ( wallPathType == eWallPathType_line ) {
		WorldPt			startPt;
		::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );
	}
	return endPt;
}

void VWWallObj::GetPoints(VWPoint2D& startPt, VWPoint2D& endPt) const
{
	VWFC_ASSERT( fhObject );
	EWallPathType wallPathType = gSDK->GetWallPathType( fhObject );
	if ( wallPathType == eWallPathType_arc )
	{
		VWArc2D		arc	= this->GetRoundWall( true );
		startPt		= arc.GetStartPt();
		endPt		= arc.GetEndPt();
	}
	else if ( wallPathType == eWallPathType_line ) {
		WorldPt			sPt;
		WorldPt			ePt;
		::GS_GetEndPoints( gCBP, fhObject, sPt, ePt );
		startPt			= sPt;
		endPt			= ePt;
	}
}

void VWWallObj::SetPoints(const VWPoint2D& startPt, const VWPoint2D& endPt)
{
	gSDK->SetEndPoints( fhObject, startPt, endPt );
}

bool VWWallObj::IsRound() const
{
	VWFC_ASSERT( fhObject );
	EWallPathType wallPathType = gSDK->GetWallPathType( fhObject );
	return wallPathType == eWallPathType_arc;
}

VWArc2D VWWallObj::GetRoundWall(bool negativeSweepForCWWall) const
{
	VWArc2D		arc;

	VWFC_ASSERT( fhObject );
	EWallPathType wallPathType = gSDK->GetWallPathType( fhObject );
	VWFC_ASSERT( wallPathType == eWallPathType_arc );
	if ( wallPathType == eWallPathType_arc ) {
		WorldPt			cenPt;
		double			radius;
		double			startAngle, sweepAngle;
		::GS_GetArcInfoN( gCBP, fhObject, startAngle, sweepAngle, cenPt, radius, radius );

		if ( negativeSweepForCWWall == false )
		{
			arc.SetArc( cenPt, radius, startAngle, sweepAngle );
		}
		else
		{
			if ( this-> IsRoundCCW() )
			{
				arc.SetArc( cenPt, radius, startAngle, sweepAngle );
			}
			else 
			{ 
				arc.SetArc( cenPt, radius, startAngle + sweepAngle, -sweepAngle );
			}
		}
	}

	return arc;
}

VWLine2D VWWallObj::GetWall() const
{
	WorldPt			sPt;
	WorldPt			ePt;
	VWFC_ASSERT( fhObject );
	::GS_GetEndPoints( gCBP, fhObject, sPt, ePt );
	return VWLine2D( sPt, ePt );
}

bool VWWallObj::IsRoundCCW() const
{
	bool		ccw		= false;

	VWFC_ASSERT( fhObject );
	EWallPathType wallPathType = gSDK->GetWallPathType( fhObject );
	VWFC_ASSERT( wallPathType == eWallPathType_arc );
	if ( wallPathType == eWallPathType_arc ) {
		TVariableBlock	value;
		::GS_GetObjectVariable( gCBP, fhObject, ovRoundWallCounterClockwise, value );
		Boolean			isCCW = false;
		VERIFYN( kVStanev, value.GetBoolean( isCCW ) );
		ccw				= isCCW ? true : false;
	}

	return ccw;
}

// Switch the left and right side of a wall by reversing the direction of the wall.
// This is an interface to the button with the same name on the Object Info palette.
void VWWallObj::ReverseSides()
{
	VWFC_ASSERT( fhObject != nil );
	::GS_ReverseWallSides( gCBP, fhObject );
}

// Gets/Sets the heights of the start and end of the specified wall.
// The distances are measured from the ground plane on the layer in which the wall exists.
void VWWallObj::GetHeights(double& startHeightTop, double& startHeightBottom, double& endHeightTop, double& endHeightBottom) const
{
	VWFC_ASSERT( fhObject != nil );
	::GS_GetWallHeights( gCBP, fhObject, startHeightTop, startHeightBottom, endHeightTop, endHeightBottom );
}

double VWWallObj::GetStartHeightTop() const
{
	VWFC_ASSERT( fhObject != nil );
	double	startHeightTop, startHeightBottom, endHeightTop, endHeightBottom;
	::GS_GetWallHeights( gCBP, fhObject, startHeightTop, startHeightBottom, endHeightTop, endHeightBottom );
	return startHeightTop;
}

double VWWallObj::GetStartHeightBottom() const
{
	VWFC_ASSERT( fhObject != nil );
	double	startHeightTop, startHeightBottom, endHeightTop, endHeightBottom;
	::GS_GetWallHeights( gCBP, fhObject, startHeightTop, startHeightBottom, endHeightTop, endHeightBottom );
	return startHeightBottom;
}

void VWWallObj::SetHeights(double startHeightTop, double startHeightBottom, double endHeightTop, double endHeightBottom)
{
	VWFC_ASSERT( fhObject != nil );
	::GS_SetWallHeights( gCBP, fhObject, startHeightTop, startHeightBottom, endHeightTop, endHeightBottom );
}

// The width of the wall.
double VWWallObj::GetWidth() const
{
	VWFC_ASSERT( fhObject != nil );
	//return ::GS_GetWallWidth( gCBP, fhObject );
	double	width;
	::GS_WrapGetWallWidth( gCBP, fhObject, width );
	return width;
}

void VWWallObj::SetWidth(double width)
{
	VWFC_ASSERT( fhObject != nil );
	::GS_SetWallWidth( gCBP, fhObject, width );
}

// Available in VW Architect only. Moves the wall perpendiclar to its definition line by the specified offset,
// and maintains all wall connections Offsets to the left hand side of the wall are positive, and to the right hand side are negative.
void VWWallObj::MoveByOffset(double& offset)
{
	VWFC_ASSERT( fhObject != nil );
	::GS_MoveWallByOffset( gCBP, fhObject, offset );
}

// COMPONENTS ////////////////////////////////////////////////////////////////////////////////
size_t VWWallObj::GetComponentCount() const
{
	short	componentCount	= 0;
	
	::GS_GetNumberOfComponents( gCBP, fhObject, componentCount );

	return (size_t) componentCount;
}

SWallComponentInfo VWWallObj::GetComponentInfo(size_t index) const
{
	VWFC_ASSERT( fhObject != nil );
	VWFC_ASSERT(index < 32768);

	SWallComponentInfo info;

	VWFC_VERIFY( ::GS_GetComponentName( gCBP,  fhObject, (CBSignedShort) index, info.componentName ) );
	VWFC_VERIFY( ::GS_GetComponentWidth( gCBP,  fhObject, (CBSignedShort) index, info.width ) );
	VWFC_VERIFY( ::GS_GetComponentClass( gCBP,  fhObject, (CBSignedShort) index, info.componentClass ) );

	// fill
	CBUnsignedShort		fillFore, fillBack;
	VWFC_VERIFY( ::GS_GetComponentUseFillClassAttr( gCBP,  fhObject, (CBSignedShort) index, info.fillUseClass ) );
	VWFC_VERIFY( ::GS_GetComponentFill( gCBP,  fhObject, (CBSignedShort) index, info.fillPat ) );
	VWFC_VERIFY( ::GS_GetComponentFillColors( gCBP,  fhObject, (CBSignedShort) index, fillFore, fillBack ) );
	info.fillColorFore.SetColor( (ColorRef) fillFore );
	info.fillColorBack.SetColor( (ColorRef) fillBack );

	// lines
	CBUnsignedShort		penLeftFore, penLeftBack, penRightFore, penRightBack;
	VWFC_VERIFY( ::GS_GetComponentUsePenClassAttr( gCBP,  fhObject, (CBSignedShort) index, info.penLeftUseClass, info.penRightUseClass ) );
	VWFC_VERIFY( ::GS_GetComponentPenColors( gCBP,  fhObject, (CBSignedShort) index, penLeftFore, penLeftBack, penRightFore, penRightBack ) );
	VWFC_VERIFY( gSDK->GetComponentPenStylesN(fhObject, (CBSignedShort) index, info.penLeftStyle, info.penRightStyle ) );
	VWFC_VERIFY( ::GS_GetComponentPenWeights( gCBP,  fhObject, (CBSignedShort) index, info.penLeftWeight, info.penRightWeight ) );

	info.penLeftColorFore.SetColor( (ColorRef) penLeftFore );
	info.penLeftColorBack.SetColor( (ColorRef) penLeftBack );
	info.penRightColorFore.SetColor( (ColorRef) penRightFore );
	info.penRightColorBack.SetColor( (ColorRef) penRightBack );

	return info;
}

void VWWallObj::SetComponentInfo(size_t index, const SWallComponentInfo& info)
{
	VWFC_ASSERT( fhObject != nil );
	VWFC_ASSERT(index < 32768);

	InternalName compName = info.componentName;
	VWFC_VERIFY( ::GS_SetComponentName( gCBP,  fhObject, (CBSignedShort) index, compName ) );
	VWFC_VERIFY( ::GS_SetComponentWidth( gCBP,  fhObject, (CBSignedShort) index, info.width ) );
	VWFC_VERIFY( ::GS_SetComponentClass( gCBP,  fhObject, (CBSignedShort) index, info.componentClass ) );

	// fill
	VWFC_VERIFY( ::GS_SetComponentUseFillClassAttr( gCBP,  fhObject, (CBSignedShort) index, info.fillUseClass ) );
	VWFC_VERIFY( ::GS_SetComponentFill( gCBP,  fhObject, (CBSignedShort) index, info.fillPat ) );
	VWFC_VERIFY( ::GS_SetComponentFillColors( gCBP,  fhObject, (CBSignedShort) index, info.fillColorFore.GetColorIndex(), info.fillColorBack.GetColorIndex() ) );

	// lines
	VWFC_VERIFY( ::GS_SetComponentUsePenClassAttr( gCBP,  fhObject, (CBSignedShort) index, info.penLeftUseClass, info.penRightUseClass ) );
	VWFC_VERIFY( ::GS_SetComponentPenColors( gCBP,  fhObject, (CBSignedShort) index, info.penLeftColorFore.GetColorIndex(), info.penLeftColorBack.GetColorIndex(), info.penRightColorFore.GetColorIndex(), info.penRightColorBack.GetColorIndex() ) );
	VWFC_VERIFY( gSDK->SetComponentPenStylesN(fhObject, (CBSignedShort) index, info.penLeftStyle, info.penRightStyle ) );
	VWFC_VERIFY( ::GS_SetComponentPenWeights( gCBP,  fhObject, (CBSignedShort) index, info.penLeftWeight, info.penRightWeight ) );
}

bool VWWallObj::InsertNewComponent(size_t beforeIndex, const SWallComponentInfo& info)
{
	VWFC_ASSERT( fhObject != nil );
	
	bool ret = gSDK->InsertNewComponentN(fhObject, (short) beforeIndex, info.width, info.fillPat, (CBSignedByte)info.penLeftWeight, (CBSignedByte)info.penRightWeight, info.penLeftStyle, info.penRightStyle );
	if(ret)
		SetComponentInfo(beforeIndex, info);
	return ret;
}

bool VWWallObj::DeleteComponent(size_t index)
{
	return GS_DeleteComponent( gCBP, fhObject, (short) index );
}

// BREAKS //////////////////////////////////////////////////////////////////////////////////
void VWWallObj::EnumerateBreaks(IWallBreakListener* pBreakListener) const
{
	VWFC_ASSERT( fhObject != nil );
	::GS_ForEachBreak( gCBP, fhObject, VWWallObj::GetAllBreaksCallback, pBreakListener );
}

Boolean VWWallObj::GetAllBreaksCallback(MCObjectHandle, Sint32 index, double off, Sint32 breakType, void* breakData, CallBackPtr , void* env)
{
	IWallBreakListener* pBreakListener	= (IWallBreakListener*) env;

	if ( pBreakListener ) {
		if ( breakType == kSymbolBreak ) {
			SymbolBreakType*	pBreak	= (SymbolBreakType*) breakData;
			if ( pBreak ) {
				SWallSymbolBreak	symBreak;
				symBreak.index			= (size_t) index; //-V201
				symBreak.offset			= off;
				symBreak.symBreak		= *pBreak;
				pBreakListener->NotifySymbolBreak( symBreak );
			}
		}
		else if ( breakType == kHalfBreak ) {
			HalfBreakType*		pBreak	= (HalfBreakType*) breakData;
			if ( pBreak ) {
				SWallHalfBreak		halfBreak;
				halfBreak.index			= (size_t) index; //-V201
				halfBreak.offset		= off;
				halfBreak.halfBreak	= *pBreak;
				pBreakListener->NotifyHalfBreak( halfBreak );
			}
		}
		else if ( breakType == kCapBreak ) {
			CapBreakType*		pBreak	= (CapBreakType*) breakData;
			if ( pBreak ) {
				SWallCapBreak		capBreak;
				capBreak.index			= (size_t) index; //-V201
				capBreak.offset			= off;
				capBreak.capBreak		= *pBreak;
				pBreakListener->NotifyCapBreak( capBreak );
			}
		}
		else if ( breakType == kPeakBreak ) {
			PeakBreakType*		pBreak	= (PeakBreakType*) breakData;
			if ( pBreak ) {
				SWallPeakBreak		peakBreak;
				peakBreak.index			= (size_t) index; //-V201
				peakBreak.offset		= off;
				peakBreak.peakBreak		= *pBreak;
				pBreakListener->NotifyPeakBreak( peakBreak );
			}
		}
	}

	return false;
}

class VWWallDefaultBreakEnumerator : public IWallBreakListener
{
public:
					VWWallDefaultBreakEnumerator()						{ fparrSymbolBreaks = NULL; fparrHalfBreaks = NULL; fparrCapBreaks = NULL; fparrPeakBreaks = NULL; }
	virtual void	NotifySymbolBreak(const SWallSymbolBreak& brk)		{ if ( fparrSymbolBreaks ) fparrSymbolBreaks->push_back( brk ); }
	virtual void	NotifyHalfBreak(const SWallHalfBreak& brk)			{ if ( fparrHalfBreaks ) fparrHalfBreaks->push_back( brk ); }
	virtual void	NotifyCapBreak(const SWallCapBreak& brk)			{ if ( fparrCapBreaks ) fparrCapBreaks->push_back( brk ); }
	virtual void	NotifyPeakBreak(const SWallPeakBreak& brk)			{ if ( fparrPeakBreaks ) fparrPeakBreaks->push_back( brk ); }
public:
	TWallSymbolBreaksArray*		fparrSymbolBreaks;
	TWallHalfBreaksArray*		fparrHalfBreaks;
	TWallCapBreaksArray*		fparrCapBreaks;
	TWallPeakBreaksArray*		fparrPeakBreaks;
};

void VWWallObj::EnumerateBreaks(TWallSymbolBreaksArray& outArrSymbolBreaks) const
{
	outArrSymbolBreaks.clear();
	VWWallDefaultBreakEnumerator	enumerator;
	enumerator.fparrSymbolBreaks		= & outArrSymbolBreaks;
	this->EnumerateBreaks( & enumerator );
}

void VWWallObj::EnumerateBreaks(TWallHalfBreaksArray& outArrHalfBreaks) const
{
	outArrHalfBreaks.clear();
	VWWallDefaultBreakEnumerator	enumerator;
	enumerator.fparrHalfBreaks		= & outArrHalfBreaks;
	this->EnumerateBreaks( & enumerator );
}

void VWWallObj::EnumerateBreaks(TWallCapBreaksArray& outArrCapBreaks) const
{
	outArrCapBreaks.clear();
	VWWallDefaultBreakEnumerator	enumerator;
	enumerator.fparrCapBreaks		= & outArrCapBreaks;
	this->EnumerateBreaks( & enumerator );
}

void VWWallObj::EnumerateBreaks(TWallPeakBreaksArray& outArrPeakBreaks) const
{
	outArrPeakBreaks.clear();
	VWWallDefaultBreakEnumerator	enumerator;
	enumerator.fparrPeakBreaks		= & outArrPeakBreaks;
	this->EnumerateBreaks( & enumerator );
}

size_t VWWallObj::AddBreak(const SWallSymbolBreak& brk)
{
	return (size_t) ::GS_AddBreak( gCBP, fhObject, brk.offset, kSymbolBreak, (void*) & brk.symBreak );
}

size_t VWWallObj::AddBreak(const SWallHalfBreak& brk)
{
	return (size_t) ::GS_AddBreak( gCBP, fhObject, brk.offset, kHalfBreak, (void*) & brk.halfBreak );
}

size_t VWWallObj::AddBreak(const SWallCapBreak& brk)
{
	return (size_t) ::GS_AddBreak( gCBP, fhObject, brk.offset, kCapBreak, (void*) & brk.capBreak );
}

size_t VWWallObj::AddBreak(const SWallPeakBreak& brk)
{
	return (size_t) ::GS_AddBreak( gCBP, fhObject, brk.offset, kPeakBreak, (void*) & brk.peakBreak );
}

void VWWallObj::SetBreak(const SWallSymbolBreak& brk)
{
	gSDK->SetBreak( fhObject, (short)brk.index, brk.offset, kSymbolBreak, (void*) & brk.symBreak );
}

void VWWallObj::SetBreak(const SWallHalfBreak& brk)
{
	gSDK->SetBreak( fhObject, (short)brk.index, brk.offset, kHalfBreak, (void*) & brk.halfBreak );
}

void VWWallObj::SetBreak(const SWallCapBreak& brk)
{
	gSDK->SetBreak( fhObject, (short)brk.index, brk.offset, kCapBreak, (void*) & brk.capBreak );
}

void VWWallObj::SetBreak(const SWallPeakBreak& brk)
{
	gSDK->SetBreak( fhObject, (short)brk.index, brk.offset, kPeakBreak, (void*) & brk.peakBreak );
}

void VWWallObj::DeleteBreak(size_t index)
{
	::GS_DeleteBreak( gCBP, fhObject, DemoteTo<short>( kVStanev, index ) );
}

bool VWWallObj::FindBreak(MCObjectHandle hSymbol, SWallSymbolBreak& brk)
{
	TWallSymbolBreaksArray	arrSymbolBreaks;
	this->EnumerateBreaks( arrSymbolBreaks );

	bool result = false;
	for(size_t i=0, cnt=arrSymbolBreaks.size(); i<cnt; ++i)
	{
		const SWallSymbolBreak& breakData = arrSymbolBreaks[ i ];
		if ( breakData.symBreak.theSymbol == hSymbol )
		{
			brk	= breakData;
			result = true;
			break;
		}
	}

	return result;
}

// Return true if the specified object handle is straight wall or round wall
bool VWWallObj::IsWallObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kWallNode;
}

// Return true if the specified object handle is a round wall
bool VWWallObj::IsRoundWallObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	EWallPathType wallPathType = eWallPathType_line;
	if ( type == kWallNode )
		wallPathType = gSDK->GetWallPathType( hObj );
	return type == kWallNode && wallPathType == eWallPathType_arc;
}

TSTLPolygons2DArray VWWallObj::GetWall2DPolygons_() const
{
	TSTLPolygons2DArray	polygonArr;
	VWTransformMatrix	theMat;

	// go through children objects
	this->GetWall2DPolygons( theMat, *this, polygonArr );
	
	return	polygonArr;
}

void VWWallObj::GetWall2DPolygons(const VWTransformMatrix& theMat, MCObjectHandle hGroup, TSTLPolygons2DArray& polygonArr) const
{
	for(	MCObjectHandle hObj = ::GS_FirstMemberObj( gCBP, hGroup ) ; 
			hObj ; 
			hObj = GS_NextObject( gCBP, hObj ) )
	{
		// check the type
		VWObject	obj( hObj );
		short		type = obj.GetType();

		// if it is a poly
		if ( type == kPolygonNode || type == kPolylineNode || type == kBoxNode ) {

			// get polygon
			VWPolygon2DObj	polyObj( hObj );
			VWPolygon2D		outPolygon;
			polyObj.GetPolygon( outPolygon );
			outPolygon.CleanUpPolygon( VWPoint2D::sEpsilon );
			outPolygon.SetClosed( true );

			// dispose the polygon
			outPolygon.PointsTransform( theMat );

			// add this polygon only if it is a correct one
			if ( std::abs( (int)outPolygon.GetArea() ) > VWPoint2D::sEpsilon ) {

				// add to array: if newly found polygon contains fully an already added then replace it.
				// if it is fully inside an already added polygon, then do not add this.
				bool	bAdded	= false;
				size_t	polyCnt	= polygonArr.size();
				for ( size_t i = 0 ; i < polyCnt ; i ++ ) {
					VWPolygon2D&	poly	= polygonArr[ i ];
					if ( outPolygon.IsFullyInside( poly, VWPoint2D::sEpsilon ) ) {
						poly	= outPolygon;
						bAdded	= true;
						break;
					}
					if ( poly.IsFullyInside( outPolygon, VWPoint2D::sEpsilon ) ) {
						bAdded	= true;
						break;
					}
				}
				if ( !bAdded ) {
					polygonArr.push_back( outPolygon );
				}
			}
		}
		// a parametric built-in object in the wall
		else if ( type == kParametricNode ) {

			// get local matrix
			VWTransformMatrix	theLocalMat;
			obj.GetObjectMatrix( theLocalMat );
			theLocalMat			= theMat * theLocalMat;

			// call recursively
			this->GetWall2DPolygons( theLocalMat, obj, polygonArr );
		}
		// a symbol built-in object in the wall
		else if ( type == kSymbolNode ) {

			// get local matrix
			VWTransformMatrix	theLocalMat;
			obj.GetObjectMatrix( theLocalMat );
			theLocalMat			= theMat * theLocalMat;

			// call recursively
			this->GetWall2DPolygons( theLocalMat, ::GS_GetDefinition( gCBP, obj ), polygonArr );
		}
		else if ( type == kGroupNode ) {

			// recursively look inside the group
			this->GetWall2DPolygons( theMat, obj, polygonArr );
		}
	}
}

bool VWWallObj::GetPolyFromWallElevation( VWPolygon2D& polyOut, bool removeCaps  )
{
	bool result = false;
	polyOut.ClearVertices();
	
	TWallPeakBreaksArray peaks;
	this->EnumerateBreaks( peaks );
	TWallPeakBreaksArray::iterator itr = peaks.begin();
	double len;
	if(!this->IsRound())
	{
		len = this->GetStartPoint().DistanceTo( this->GetEndPoint() );
	}
	else
	{
		len = this->GetRoundWall().GetLength();
	}
	double stT, stB, edT, edB, top, bottom;
	double stX = 0;
	double edX = len;
	gSDK->GetWallOverallHeights( fhObject, top, bottom );
	this->GetHeights( stT, stB, edT, edB );		
		
	//Account for caps
	if(removeCaps)
	{
		TWallCapBreaksArray caps;
		this->EnumerateBreaks(caps);
		if(VERIFYN(kMFlamer, caps.size() == 2))
		{
			stX = (caps.at(0).capBreak.rightOff + caps.at(0).capBreak.leftOff)/2; 
			edX = len + (caps.at(1).capBreak.rightOff + caps.at(1).capBreak.leftOff)/2; 
		}
	}

	polyOut.AddVertex( VWPoint2D( stX, stT - bottom) );
	//traverse vector forwards for top peaks
	while( itr != peaks.end() )
	{
		bool top = itr->peakBreak.topPeak;
		if(top) 
		{
			VWPoint2D pnt( itr->offset, itr->peakBreak.peakHeight - bottom );
			polyOut.AddVertex( pnt );
		}
		itr++;
	}

		
	polyOut.AddVertex( VWPoint2D( edX, edT - bottom) );
	polyOut.AddVertex( VWPoint2D( edX, edB - bottom) );

	TWallPeakBreaksArray::reverse_iterator ritr;
	//traverse in reverse for bottom peaks
	for( ritr = peaks.rbegin(); ritr != peaks.rend(); ritr++ )
	{
		bool top = ritr->peakBreak.topPeak;
		if(!top) 
		{
			VWPoint2D pnt( ritr->offset, ritr->peakBreak.peakHeight - bottom );
			polyOut.AddVertex( pnt );
		}			
	}
	polyOut.AddVertex( VWPoint2D( stX, stB - bottom) );
	polyOut.SetClosed( true );
	result = true;
	
	return result;
}

MCObjectHandle VWWallObj::GetWallFootPrint() const
{
	MCObjectHandle footPrint = nil;
	
	MCObjectHandle newWall = *this;

	if ( newWall )
	{
		//Start an internal undo event which we will remove at the end of the function
		Boolean onlyRecognizePrim = true;
		Boolean beginInternalEvent = true;

		gSDK->SetProgramVariable(9872, &onlyRecognizePrim);
		gSDK->SetProgramVariable(varTreatSubsequentObjectOperationsTemporary, &beginInternalEvent);
		
		gSDK->AddBothSwapObject(newWall);

		// remove all symbol breaks
		VWWallObj wallObj( newWall );
		wallObj.GetObjectAttribs().SetFillSolid();

		TWallSymbolBreaksArray	symbolBreaksArr;
		wallObj.EnumerateBreaks( symbolBreaksArr );

		for ( size_t i = 0 ; i < symbolBreaksArr.size() ; i ++ )
		{
			wallObj.DeleteBreak( symbolBreaksArr[ i ].index );
		}
		
		wallObj.ResetObject();
		
		MCObjectHandle trav = ::GS_FirstMemberObj( gCBP, newWall );
		MCObjectHandle curentFootPrint = nil;
		
		double area = 0;

		while ( trav )
		{
			short type = gSDK->GetObjectTypeN( trav );
			if ( type == kPolygonNode || type == kPolylineNode )
			{
				// get area
				double thisArea;
				::GS_CalcAreaN( gCBP, trav, thisArea );

				if ( thisArea > area )
				{	
					area = thisArea;
					curentFootPrint = trav;
				}
			}
			trav = ::GS_NextObject( gCBP, trav );
		}
			
		footPrint = ::GS_DuplicateObject( gCBP, curentFootPrint );

		onlyRecognizePrim  = false;
		beginInternalEvent = false;

		gSDK->SetProgramVariable(varTreatSubsequentObjectOperationsTemporary, &onlyRecognizePrim);
		gSDK->SetProgramVariable(9872, &beginInternalEvent);
	}

	return footPrint;
}

void VWWallObj::GetWallFootPrintEx(VWPolygon2D& footPoly) const
{

	
	footPoly.ClearVertices();

	if (fhObject == NULL || IsRound())
		return;
	
	VWPoint2D wallStartPt, wallEndPt;
	this->GetPoints(wallStartPt, wallEndPt);

	double			distStart = 1E300,	distEnd = 1E300;
	MCObjectHandle  polyStart = nil,	polyEnd = nil;
	MCObjectHandle  trav = ::GS_FirstMemberObj( gCBP, *this );

	// Find closest polygons to start and end
	while ( trav )
	{
		short type = gSDK->GetObjectTypeN( trav );
		if ( type == kPolygonNode || type == kPolylineNode || type == kBoxNode )
		{
			VWPolygon2DObj	wallPolyObj( trav );
			
			size_t count = wallPolyObj.GetVertexCount();
			if (count > 2) {
			for (size_t i = 0; i < count; i++){
				VWPoint2D ptPoly = wallPolyObj.GetVertexPoint( i );
				double dist1 = ptPoly.DistanceTo( wallStartPt );
				double dist2 = ptPoly.DistanceTo( wallEndPt   );

				if ( distStart > dist1 ) {
					 distStart = dist1;
					 polyStart = trav;
				}

				if ( distEnd > dist2 ) {
					 distEnd = dist2;
					 polyEnd = trav;
				}
			}
		}
		}
		trav = ::GS_NextObject( gCBP, trav );
	}

	// Find closest vertices from the closest polygons
	if (polyStart && polyEnd){
		VWPoint2D startPt1, startPt2, endPt1, endPt2;

		{ // 2 points near wall start
			VWPolygon2DObj	wallPolyObj( polyStart );
			size_t count =  wallPolyObj.GetVertexCount();
			double			dist2Pts = 1E300;

			for (size_t i = 0; i < count; i++){
				VWPoint2D ptPoly1 = wallPolyObj.GetVertexPoint( i );
				VWPoint2D ptPoly2 = wallPolyObj.GetVertexPoint((i < count-1) ? i + 1 : 0 );

				double dist = ptPoly1.DistanceTo( wallStartPt ) + ptPoly2.DistanceTo( wallStartPt );

				if ( dist2Pts > dist ) {
					 dist2Pts = dist;
					 startPt1 = ptPoly1; startPt2 = ptPoly2;
				}
			}
		}

		{ // 2 points near wall end
			VWPolygon2DObj	wallPolyObj( polyEnd );
			size_t count =  wallPolyObj.GetVertexCount();
			double			dist2Pts = 1E300;

			for (size_t i = 0; i < count; i++){
				VWPoint2D ptPoly1 = wallPolyObj.GetVertexPoint( i );
				VWPoint2D ptPoly2 = wallPolyObj.GetVertexPoint((i < count-1) ? i + 1 : 0 );

				double dist = ptPoly1.DistanceTo( wallEndPt ) + ptPoly2.DistanceTo( wallEndPt );

				if ( dist2Pts > dist ) {
					 dist2Pts = dist;
					 endPt1 = ptPoly1; endPt2 = ptPoly2;
				}
			}
		}

		// Extend to full width if components present
		if (this->GetComponentCount() > 1)
		{
			if ( !MathUtils::Equalish( startPt1.DistanceTo( startPt2 ), 0.0, VWPoint2D::sEpsilon ) && 
				 !MathUtils::Equalish( endPt1.DistanceTo( endPt2 ),     0.0, VWPoint2D::sEpsilon )		)
			{
				double	halfWallWidth	= this->GetWidth() / 2;
				VWPoint2D		dirConn	= (startPt2  - startPt1).Normalize();

				startPt1				= wallStartPt + halfWallWidth * dirConn;
				startPt2				= wallStartPt - halfWallWidth * dirConn;

				dirConn					= (endPt2  - endPt1).Normalize();
				endPt1					= wallEndPt + halfWallWidth * dirConn;
				endPt2					= wallEndPt - halfWallWidth * dirConn;
			}
		}
		
		// Build the polygon
		VWLine2D line ( startPt2, endPt1 );

		footPoly.AddVertex( startPt1 );
		footPoly.AddVertex( startPt2 );

		if (line.AreOnSameSide( startPt1, endPt2 )){	
			footPoly.AddVertex( endPt1 );
			footPoly.AddVertex( endPt2 );
		}
		else {
			footPoly.AddVertex( endPt2 );
			footPoly.AddVertex( endPt1 );
		}

		footPoly.SetClosed( true );
	}
}

// get wall's underlying 2D path polygon.
// a line for a straight wall and a polygon (polygonized arc) for a round wall.
void VWWallObj::GetWall2DPath(VWPolygon2D& pathPoly) const
{
	// clear.
	pathPoly.ClearVertices();
	
	if ( VWWallObj::IsRoundWallObject( *this ) ) {	// if a round walls.

		// get arc poly.
		VWArc2D				wallArc		=	this->GetRoundWall();
		wallArc.GetPolygon( pathPoly );
		pathPoly.SetClosed( false );

		// polygonize.
		VWPolygon2DObj		poly2DObj( pathPoly );	// temp object.
		poly2DObj.ConvertToPolygon( 16 );			// Low Convert Res.
		poly2DObj.GetPolygon( pathPoly );

		poly2DObj.DeleteObject( false );			// delete the temp object.
	}
	else {

		VWLine2D			wallLine	=	this->GetWall();
		const VWPoint2D&	startPt		=	wallLine.GetStart();
		const VWPoint2D&	endPt		=	wallLine.GetEnd();

		pathPoly.AddVertex( startPt );
		pathPoly.AddVertex( endPt );
		pathPoly.SetClosed( false );
	}
}

// Having an underlying 3D path, send the wall bottom to this 3D path (using wall breaks).
// The projection of the 3D path in 2D has to coincide with the wall's 2D path (needs validation).
// Whole wall is risen with the projection of bottom wall start point to the 3D path.
void VWWallObj::SendBotTo3DPath(const VWPolygon3D& path3D, bool bUpdateOveallHeight)
{
	// validate the path.
	VWPolygon3D		path		=	path3D;		// copy the 3D path.
	bool			isValidPath	=	this->IsValidWall3DPath( path, VWPoint2D::sEpsilon );
	if ( ! isValidPath ) {
		// try to fix the path.
		isValidPath				=	this->FixWall3DPath( path, VWPoint2D::sEpsilon );
	}

	size_t			cntPts		=	path.GetVertexCount();
	if ( isValidPath && ( cntPts > 0 ) ) {		// a valid path.

		gSDK->AddBothSwapObject( *this );		// wall will be updated.

		// get wall heights.
		double					startHgtTop, startHgtBot, endHgtTop, endHgtBot;
		this->GetHeights( startHgtTop, startHgtBot, endHgtTop, endHgtBot );

		// get elevation change for the whole wall.
		const VWPoint3D&		startPathPt			=	path.GetVertexAt( 0 );
		const VWPoint3D&		endPathPt			=	path.GetVertexAt( cntPts - 1 );
		double					wallElevCorrection	=	( startPathPt.z - startHgtBot );

		// correct height values.
		if ( bUpdateOveallHeight )
			startHgtTop				+=	wallElevCorrection;
		startHgtBot				=	startPathPt.z;

		if (bUpdateOveallHeight)
			endHgtTop				+=	wallElevCorrection;

		endHgtBot				=	endPathPt.z;

		// get all wall peaks.
		TWallPeakBreaksArray	peaksArr;
		this->EnumerateBreaks( peaksArr );

		// remove bottom peaks and correct elevations of top peaks.
		// --------------------------------------------------------
		size_t					cntPeaks			=	peaksArr.size();
		for( size_t i = 0 ; i < cntPeaks ; ++ i ) {
			SWallPeakBreak&		peak				=	peaksArr[ cntPeaks - i - 1 ];

			if ( ! peak.peakBreak.topPeak ) {	// remove only bottom peaks.
				this->DeleteBreak( peak.index );
			}
			else {								// correct the elevation of top peaks.
				if ( bUpdateOveallHeight )
				{
					peak.peakBreak.peakHeight		+=	wallElevCorrection;	// correct elevation.
					this->SetBreak( peak );									// set corrected peak.
				}							
			}
		}

		// reload peaks.
		peaksArr.clear();
		this->EnumerateBreaks( peaksArr );

		// set corrected wall heights.
		this->SetHeights( startHgtTop, startHgtBot, endHgtTop, endHgtBot );

		// get wall arc or line, and its lenght.
		// -------------------------------------
		VWArc2D					wallArc;
		VWLine2D				wallLine;
		double					lenghtWall;
		bool					isRoundWall		=	this->IsRoundWallObject( *this );
		if ( isRoundWall ) {	// get wall arc.
			wallArc				=	this->GetRoundWall();
			lenghtWall			=	wallArc.GetLength();
		}
		else {					// get wall line.
			wallLine			=	this->GetWall();
			lenghtWall			=	wallLine.GetLength();
		}

		// correct the bottom of the wall to lie on the 3D path.
		// -----------------------------------------------------
		// already checked whether cntPts > 0.
		// pass middle wall path points.
		double					prevOffset	=	0.0;
		for ( size_t i = 1 ; i < ( cntPts - 1 ) ; ++ i ) {
			const VWPoint3D&	pt			=	path.GetVertexAt( i );

			// prepare the new peak.
			SWallPeakBreak		newPeak;
			newPeak.peakBreak.topPeak		=	false;
			newPeak.peakBreak.peakHeight	=	pt.z;							// set elevation.

			// get peak's offset.
			if ( isRoundWall ) {
				wallArc.IsPtOnArc( pt, VWPoint2D::sEpsilon, newPeak.offset );	// set offset.
			}
			else {
				const VWPoint2D& startPt	=	wallLine.GetStart();
				newPeak.offset				=	startPt.DistanceTo( pt );
			}

			// check if the peak's offset is correct.
			bool				hasBadOffset, hasBadElev;
			double				maxAllowedElev;
			this->IsCorrectBotPeak( newPeak, peaksArr, prevOffset, lenghtWall, hasBadOffset, hasBadElev, maxAllowedElev );
			if ( ! hasBadOffset ) {		// has correct offset.

				if ( hasBadElev ) {		// elevation has to be corrected.
					newPeak.peakBreak.peakHeight	=	maxAllowedElev;
				}

				this->AddBreak( newPeak );
				prevOffset							=	newPeak.offset;
			}
		}

		this->ResetObject();	// reset object.
	}
}

// Having an underlying 3D path, send the wall top to this 3D path (using wall breaks).
// The projection of the 3D path in 2D has to coincide with the wall's 2D path (needs validation).
// Whole wall is risen with the projection of top wall start point to the 3D path.
void VWWallObj::SendTopTo3DPath(const VWPolygon3D& path3D)
{
	// validate the path.
	VWPolygon3D		path		=	path3D;		// copy the 3D path.
	bool			isValidPath	=	this->IsValidWall3DPath( path, VWPoint2D::sEpsilon );
	if ( ! isValidPath ) {
		// try to fix the path.
		isValidPath				=	this->FixWall3DPath( path, VWPoint2D::sEpsilon );
	}

	size_t			cntPts		=	path.GetVertexCount();
	if ( isValidPath && ( cntPts > 0 ) ) {		// a valid path.

		gSDK->AddBothSwapObject( *this );		// wall will be updated.

		// get wall heights.
		double					startHgtTop, startHgtBot, endHgtTop, endHgtBot;
		this->GetHeights( startHgtTop, startHgtBot, endHgtTop, endHgtBot );

		// get elevation change for the whole wall.
		const VWPoint3D&		startPathPt			=	path.GetVertexAt( 0 );
		const VWPoint3D&		endPathPt			=	path.GetVertexAt( cntPts - 1 );
		double					wallElevCorrection	=	( startPathPt.z - startHgtTop );

		// correct height values.
		startHgtBot				+=	wallElevCorrection;
		startHgtTop				=	startPathPt.z;
		endHgtBot				+=	wallElevCorrection;
		endHgtTop				=	endPathPt.z;

		// get all wall peaks.
		TWallPeakBreaksArray	peaksArr;
		this->EnumerateBreaks( peaksArr );

		// remove top peaks and correct elevations of bottom peaks.
		// --------------------------------------------------------
		size_t					cntPeaks			=	peaksArr.size();
		for( size_t i = 0 ; i < cntPeaks ; ++ i ) {
			SWallPeakBreak&		peak				=	peaksArr[ cntPeaks - i - 1 ];

			if ( peak.peakBreak.topPeak ) {		// remove only top peaks.
				this->DeleteBreak( peak.index );
			}
			else {								// correct the elevation of bottom peaks.

				peak.peakBreak.peakHeight		+=	wallElevCorrection;	// correct elevation.
				this->SetBreak( peak );									// set corrected peak.
			}
		}

		// reload peaks.
		peaksArr.clear();
		this->EnumerateBreaks( peaksArr );

		// set corrected wall heights.
		this->SetHeights( startHgtTop, startHgtBot, endHgtTop, endHgtBot );

		// get wall arc or line, and its lenght.
		// -------------------------------------
		VWArc2D					wallArc;
		VWLine2D				wallLine;
		double					lenghtWall;
		bool					isRoundWall		=	this->IsRoundWallObject( *this );
		if ( isRoundWall ) {	// get wall arc.
			wallArc				=	this->GetRoundWall();
			lenghtWall			=	wallArc.GetLength();
		}
		else {					// get wall line.
			wallLine			=	this->GetWall();
			lenghtWall			=	wallLine.GetLength();
		}

		// correct the top of the wall to lie on the 3D path.
		// --------------------------------------------------
		// already checked whether cntPts > 0.
		// pass middle wall path points.
		double					prevOffset	=	0.0;
		for ( size_t i = 1 ; i < ( cntPts - 1 ) ; ++ i ) {
			const VWPoint3D&	pt			=	path.GetVertexAt( i );

			// prepare the new peak.
			SWallPeakBreak		newPeak;
			newPeak.peakBreak.topPeak		=	true;
			newPeak.peakBreak.peakHeight	=	pt.z;							// set elevation.

			// get peak's offset.
			if ( isRoundWall ) {
				wallArc.IsPtOnArc( pt, VWPoint2D::sEpsilon, newPeak.offset );	// set offset.
			}
			else {
				const VWPoint2D& startPt	=	wallLine.GetStart();
				newPeak.offset				=	startPt.DistanceTo( pt );
			}

			// check if the peak's offset is correct.
			bool				hasBadOffset, hasBadElev;
			double				minAllowedElev;
			this->IsCorrectTopPeak( newPeak, peaksArr, prevOffset, lenghtWall, hasBadOffset, hasBadElev, minAllowedElev );
			if ( ! hasBadOffset ) {			// has correct offset.

				if ( hasBadElev ) {			// elevation has to be corrected.
					newPeak.peakBreak.peakHeight	=	minAllowedElev;
				}

				this->AddBreak( newPeak );	// add this peak.
				prevOffset							=	newPeak.offset;
			}
		}

		this->ResetObject();	// reset object.
	}
}

// Check if a 3D polygon is a valid wall's 3D path (its projection coincides with the wall's 2D path).
bool VWWallObj::IsValidWall3DPath(const VWPolygon3D& path3D, double dEpsilon) const
{
	// validation of the 3D path points.
	bool			isValid		=	true;
	size_t			cntPts		=	path3D.GetVertexCount();

	// check whether path's ends coincide with wall's ends.
	// start and end wall points.
	const VWPoint2D& begWallPt	=	this->GetStartPoint();
	const VWPoint2D& endWallPt	=	this->GetEndPoint();

	// start and end path points.
	const VWPoint2D& begPathPt	=	path3D.GetVertexAt( 0 );
	const VWPoint2D& endPathPt	=	path3D.GetVertexAt( cntPts - 1 );

	// check if start path point coincides with one of wall's ends.
	if ( ! MathUtils::Equalish( begPathPt, begWallPt, dEpsilon ) && 
		 ! MathUtils::Equalish( begPathPt, endWallPt, dEpsilon ) ) {
		isValid					=	false;
	}

	// check if end path point coincides with one of wall's ends.
	if ( ( isValid ) &&
		 ! MathUtils::Equalish( endPathPt, begWallPt, dEpsilon ) && 
		 ! MathUtils::Equalish( endPathPt, endWallPt, dEpsilon ) ) {
		isValid					=	false;
	}

	bool			isRoundWall	=	VWWallObj::IsRoundWallObject( *this );

	// get arc or line depending on the wall type.
	VWArc2D			wallArc;
	VWLine2D		wallLine;
	if ( isRoundWall ) {	// get wall arc.
		wallArc					=	this->GetRoundWall();
	}
	else {					// get wall line.
		wallLine				=	this->GetWall();
	}

	// validation of the rest of 3D path points.
	for ( size_t i = 0 ; ( i < cntPts ) && ( isValid ) ; ++ i ) {
		const VWPoint3D&	pt	=	path3D.GetVertexAt( i );

		if ( isRoundWall ) {	// use the wall arc.

			if ( ! wallArc.IsPtOnArc( pt, dEpsilon ) ) {
				isValid			=	false;
			}
		}
		else {					// use the wall line.

			if ( ! wallLine.PtOnLine( pt, dEpsilon ) ) {
				isValid			=	false;
			}
		}
	}

	return	isValid;
}

// Tries to fix an invalid 3D wall path.
bool VWWallObj::FixWall3DPath(VWPolygon3D& path3D, double dEpsilon) const
{
	// validation of the 3D path points.
	bool			isValid		=	true;
	size_t			cntPts		=	path3D.GetVertexCount();

	// check whether path's ends coincide with wall's ends.
	// start and end wall points.
	const VWPoint2D& begWallPt	=	this->GetStartPoint();
	const VWPoint2D& endWallPt	=	this->GetEndPoint();

	// start and end path points.
	const VWPoint2D& begPathPt	=	path3D.GetVertexAt( 0 );
	const VWPoint2D& endPathPt	=	path3D.GetVertexAt( cntPts - 1 );

	bool			isReversed	=	false;

	// check if start path point coincides with one of wall's ends.
	if ( 		MathUtils::Equalish( begPathPt, begWallPt, dEpsilon ) ) {
		isReversed				=	false;
	}
	else if (	MathUtils::Equalish( begPathPt, endWallPt, dEpsilon ) ) {
		isReversed				=	true;
	}
	else {		// invalid start path point.
		isValid					=	false;
	}

	// check if end path point coincides with one of wall's ends.
	if ( isValid ) {
		if ( 		MathUtils::Equalish( endPathPt, begWallPt, dEpsilon ) ) {
			if ( ! isReversed ) {
				isValid			=	false;
			}
		}
		else if ( 	MathUtils::Equalish( endPathPt, endWallPt, dEpsilon ) ) {
			if ( isReversed ) {
				isValid			=	false;
			}
		}
		else {	// invalid end path point.
			isValid				=	false;
		}
	}

	bool			isRoundWall	=	VWWallObj::IsRoundWallObject( *this );

	// get arc or line depending on the wall type.
	VWArc2D			wallArc;
	VWLine2D		wallLine;
	if ( isRoundWall ) {	// get wall arc.
		wallArc					=	this->GetRoundWall();
	}
	else {					// get wall line.
		wallLine				=	this->GetWall();
	}

	// validation of the rest of 3D path points.
	for ( size_t i = 0 ; ( i < cntPts ) && ( isValid ) ; ++ i ) {

		VWPoint3D&	pt			=	path3D.GetVertexAt( i );
		if ( isRoundWall ) {	// use the wall arc.

			if ( ! wallArc.IsPtOnArc( pt, dEpsilon ) ) {		// check if point lies on the wall arc.

				const VWPoint2D& proj	=	wallArc.PtPerpArc( pt );	// project point on the wall arc.
				if ( ! wallArc.IsPtOnArc( proj, dEpsilon ) ) {			// check if projection lies on the wall arc.
					isValid				=	false;
				}
				else {	// change 2D position of the 3D path point
					pt.x				=	proj.x;
					pt.y				=	proj.y;
				}
			}
		}
		else {					// use the wall line.

			if ( ! wallLine.PtOnLine( pt, dEpsilon ) ) {		// check if point lies on the wall line.

				const VWPoint2D& proj	=	wallLine.PtPerpLine( pt );	// project point on the wall line.
				if ( ! wallLine.PtOnLine( proj, dEpsilon ) ) {
					isValid				=	false;
				}
				else {	// change 2D position of the 3D path point
					pt.x				=	proj.x;
					pt.y				=	proj.y;
				}
			}
		}
	}

	// reverse path if necessary.
	if ( isValid && isReversed ) {
		path3D.ReversePoints();
	}

	return	isValid;
}

// Check if proposed bottom peak is correct.
void VWWallObj::IsCorrectBotPeak(const SWallPeakBreak& botPeak, const TWallPeakBreaksArray& peaksArr,
								 double minOffset, double maxOffset,
								 bool& outBadOffset, bool& outBadElev, double& outMaxElev) const
{
	// a constant: epsilon for elevations comparison.
	const double	kElevationEpsilon		=	0.001;
	
	outBadOffset							=	false;
	outBadElev								=	false;

	VWFC_ASSERT( MathUtils::Greaterish( maxOffset, minOffset, VWPoint2D::sEpsilon ) );

	// check if the new bottom peak's offset is correct.
	// -------------------------------------------------
	if ( ! MathUtils::Greaterish(	botPeak.offset, minOffset, VWPoint2D::sEpsilon ) ||
		 ! MathUtils::Lesserish(	botPeak.offset, maxOffset, VWPoint2D::sEpsilon ) ) {
		outBadOffset						=	true;
	}

	// check if the elevation of the new bottom peak is correct.
	// ---------------------------------------------------------
	if ( ! outBadOffset ) {	// still correct.

		// get wall heights.
		double					startHgtTop, startHgtBot, endHgtTop, endHgtBot;
		this->GetHeights( startHgtTop, startHgtBot, endHgtTop, endHgtBot );

		// find the top peak with nearest lesser offset.
		size_t					cntPeaks		=	peaksArr.size();
		double					minOffsetDiff	=	maxOffset;	// init value.
		SWallPeakBreak			prevPeak;
		bool					hasPrevPeak		=	false;
		for( size_t i = 0 ; i < cntPeaks ; ++ i ) {
			const SWallPeakBreak&	peak		=	peaksArr[ i ];

			if ( peak.peakBreak.topPeak ) {	// top peaks.

				if ( MathUtils::GEish( botPeak.offset, peak.offset, VWPoint2D::sEpsilon ) ) {

					double	currOffsetDiff		=	Abs( peak.offset - botPeak.offset );
					if ( currOffsetDiff < minOffsetDiff ) {
						minOffsetDiff			=	currOffsetDiff;
						prevPeak				=	peak;
						hasPrevPeak				=	true;
					}
				}
			}
		}
		if ( ! hasPrevPeak ) {	// use the top beginning of the wall.
			prevPeak.offset						=	0.0;
			prevPeak.peakBreak.peakHeight		=	startHgtTop;
		}

		// find the top peak with nearest bigger offset.
		minOffsetDiff							=	maxOffset;	// init value.
		SWallPeakBreak			nextPeak;
		bool					hasNextPeak		=	false;
		for( size_t i = 0 ; i < cntPeaks ; ++ i ) {
			const SWallPeakBreak&	peak		=	peaksArr[ i ];

			if ( peak.peakBreak.topPeak ) {	// top peaks.

				if ( MathUtils::LEish( botPeak.offset, peak.offset, VWPoint2D::sEpsilon ) ) {

					double	currOffsetDiff		=	Abs( peak.offset - botPeak.offset );
					if ( currOffsetDiff < minOffsetDiff ) {
						minOffsetDiff			=	currOffsetDiff;
						nextPeak				=	peak;
						hasNextPeak				=	true;
					}
				}
			}
		}
		if ( ! hasNextPeak ) {	// use the top ending of the wall.
			nextPeak.offset						=	maxOffset;
			nextPeak.peakBreak.peakHeight		=	endHgtTop;
		}

		// find maximum elevation for the new bottom peak.
		double	delta							=	( nextPeak.offset	- prevPeak.offset );
		double	deltaPrev						=	( botPeak.offset	- prevPeak.offset );
		double	deltaNext						=	( nextPeak.offset	- botPeak.offset  );

		double	elevMax							=	prevPeak.peakBreak.peakHeight;
		if ( ! MathUtils::Equalish( delta, 0.0, VWPoint2D::sEpsilon ) ) {
			elevMax								=	( ( prevPeak.peakBreak.peakHeight * deltaNext ) +
													  ( nextPeak.peakBreak.peakHeight * deltaPrev ) ) / delta;
		}

		// check if the elevation of the new bottom peak is less than maximum elevation at this offset.
		outBadElev								=	! MathUtils::Lesserish( botPeak.peakBreak.peakHeight, elevMax, kElevationEpsilon );
		outMaxElev								=	( elevMax - kElevationEpsilon );
	}
}

// Check if proposed top peak is correct.
void VWWallObj::IsCorrectTopPeak(const SWallPeakBreak& topPeak, const TWallPeakBreaksArray& peaksArr,
								 double minOffset, double maxOffset,
								 bool& outBadOffset, bool& outBadElev, double& outMinElev) const
{
	// a constant: epsilon for elevations comparison.
	const double	kElevationEpsilon		=	0.001;
	
	outBadOffset							=	false;
	outBadElev								=	false;

	VWFC_ASSERT( MathUtils::Greaterish( maxOffset, minOffset, VWPoint2D::sEpsilon ) );

	// check if the new top peak's offset is correct.
	// -------------------------------------------------
	if ( ! MathUtils::Greaterish(	topPeak.offset, minOffset, VWPoint2D::sEpsilon ) ||
		 ! MathUtils::Lesserish(	topPeak.offset, maxOffset, VWPoint2D::sEpsilon ) ) {
		outBadOffset						=	true;
	}

	// check if the elevation of the new top peak is correct.
	// ---------------------------------------------------------
	if ( ! outBadOffset ) {	// still correct.

		// get wall heights.
		double					startHgtTop, startHgtBot, endHgtTop, endHgtBot;
		this->GetHeights( startHgtTop, startHgtBot, endHgtTop, endHgtBot );

		// find the bottom peak with nearest lesser offset.
		size_t					cntPeaks		=	peaksArr.size();
		double					minOffsetDiff	=	maxOffset;	// init value.
		SWallPeakBreak			prevPeak;
		bool					hasPrevPeak		=	false;
		for( size_t i = 0 ; i < cntPeaks ; ++ i ) {
			const SWallPeakBreak&	peak		=	peaksArr[ i ];

			if ( ! peak.peakBreak.topPeak ) {	// bottom peaks.

				if ( MathUtils::GEish( topPeak.offset, peak.offset, VWPoint2D::sEpsilon ) ) {

					double	currOffsetDiff		=	Abs( peak.offset - topPeak.offset );
					if ( currOffsetDiff < minOffsetDiff ) {
						minOffsetDiff			=	currOffsetDiff;
						prevPeak				=	peak;
						hasPrevPeak				=	true;
					}
				}
			}
		}
		if ( ! hasPrevPeak ) {	// use the bottom beginning of the wall.
			prevPeak.offset						=	0.0;
			prevPeak.peakBreak.peakHeight		=	startHgtBot;
		}

		// find the bottom peak with nearest bigger offset.
		minOffsetDiff							=	maxOffset;	// init value.
		SWallPeakBreak			nextPeak;
		bool					hasNextPeak		=	false;
		for( size_t i = 0 ; i < cntPeaks ; ++ i ) {
			const SWallPeakBreak&	peak		=	peaksArr[ i ];

			if ( ! peak.peakBreak.topPeak ) {	// bottom peaks.

				if ( MathUtils::LEish( topPeak.offset, peak.offset, VWPoint2D::sEpsilon ) ) {

					double	currOffsetDiff		=	Abs( peak.offset - topPeak.offset );
					if ( currOffsetDiff < minOffsetDiff ) {
						minOffsetDiff			=	currOffsetDiff;
						nextPeak				=	peak;
						hasNextPeak				=	true;
					}
				}
			}
		}
		if ( ! hasNextPeak ) {	// use the bottom ending of the wall.
			nextPeak.offset						=	maxOffset;
			nextPeak.peakBreak.peakHeight		=	endHgtBot;
		}

		// find maximum elevation for the new top peak.
		double	delta							=	( nextPeak.offset	- prevPeak.offset );
		double	deltaPrev						=	( topPeak.offset	- prevPeak.offset );
		double	deltaNext						=	( nextPeak.offset	- topPeak.offset  );

		double	elevMin							=	prevPeak.peakBreak.peakHeight;
		if ( ! MathUtils::Equalish( delta, 0.0, VWPoint2D::sEpsilon ) ) {
			elevMin								=	( ( prevPeak.peakBreak.peakHeight * deltaNext ) +
													  ( nextPeak.peakBreak.peakHeight * deltaPrev ) ) / delta;
		}

		// check if the elevation of the new top peak is less than maximum elevation at this offset.
		outBadElev								=	! MathUtils::Greaterish( topPeak.peakBreak.peakHeight, elevMin, kElevationEpsilon );
		outMinElev								=	( elevMin + kElevationEpsilon );
	}
}
