//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::Tools;
using namespace VWFC::VWObjects;

VWObject::VWObject()
{
	fhObject	= nullptr;
}

VWObject::VWObject(const VWObject& src)
{
	fhObject	= src.fhObject;
}

VWObject::VWObject(MCObjectHandle hObj)
{
	fhObject	= hObj;
}

VWObject::~VWObject()
{
}

VWObject& VWObject::operator=(const VWObject& obj)
{
	fhObject	= obj.fhObject;
	return *this;
}

VWObject::operator MCObjectHandle() const
{
	return fhObject;
}

void VWObject::DeleteObject(bool bUseUndo/*=true*/)
{
	VWFC_ASSERT( fhObject );
	::GS_DeleteObject( gCBP, fhObject, bUseUndo );
	fhObject		= nullptr;
}

void VWObject::InsertAfterObject(MCObjectHandle afterObj)
{
	VWFC_ASSERT( fhObject );
	::GS_InsertObjectAfter( gCBP, fhObject, afterObj );
}

void VWObject::InsertBeforeObject(MCObjectHandle beforeObj)
{
	VWFC_ASSERT( fhObject );
	::GS_InsertObjectBefore( gCBP, fhObject, beforeObj );
}

MCObjectHandle VWObject::GetThisObject() const
{
	return fhObject;
}

MCObjectHandle VWObject::GetNextObject() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_NextObject( gCBP, fhObject );
}

MCObjectHandle VWObject::GetPrevObject() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_PrevObject( gCBP, fhObject );
}

MCObjectHandle VWObject::GetParentObject() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_ParentObject( gCBP, fhObject );
}

MCObjectHandle VWObject::GetParentLayer() const
{
	MCObjectHandle	hLayer		= fhObject;
	do {
		MCObjectHandle	hParent		= ::GS_ParentObject( gCBP, hLayer );
		if ( hParent == nullptr && hLayer ) {
			// there is no parent, get the AUX owner
			hParent		= ::GS_AuxOwner( gCBP, hLayer );
		}

		hLayer		= hParent;
	} while ( hLayer && ! VWLayerObj::IsLayerObject( hLayer ) );
	return hLayer;
}

MCObjectHandle VWObject::FindNextObject(short type) const
{
	MCObjectHandle h = fhObject;
	while ( h )
	{
		short thisType = gSDK->GetObjectTypeN(h);
		if ( thisType == type )
			return h;
		h = gSDK->NextObject( h );
	}

	return nullptr;
}

void VWObject::GetContainerInfo(MCObjectHandle* pOutContainerHandle, short* pOutContainerType, double* pOutContainerScale) const
{
	MCObjectHandle		hContainer		= fhObject;
	MCObjectHandle		h				= fhObject;
	short				type			= gSDK->GetObjectTypeN( h );
	// Stop when you get to the document header or a nil parent.
	while ( h != nullptr && type != kHeaderNode && type != kTermNode ) {
		hContainer		= h;
		h				= ::GS_ParentObject( gCBP, h );
		type			= gSDK->GetObjectTypeN( h );
	}

	double				dContainerScale	= 1;
	short				nContainerType	= gSDK->GetObjectTypeN( hContainer );
	short				containerType	= nContainerType;
	switch( nContainerType ) {
		case kGroupNode: {
				containerType	= kViewportNode;

				hContainer		= ::GS_GetViewportGroupParent( gCBP, hContainer );

				TVariableBlock		value;
				::GS_GetObjectVariable( gCBP, hContainer, ovViewportScale, value );
				VERIFYN( kVStanev, value.GetReal64( dContainerScale ) );
			} break;
		case kLayerNode: {
				::GS_GetLayerScaleN( gCBP, hContainer, dContainerScale );

				TVariableBlock		value;
				::GS_GetObjectVariable( gCBP, hContainer, ovLayerType, value );
				short				sheetType;
				VERIFYN( kVStanev, value.GetSint16( sheetType ) );

				if ( sheetType == 2 )
					containerType = - containerType;	// sheet layer
			} break;
		case symListNode:
		default:	{
				dContainerScale				= 1;

				// find the first selected layer
				MCObjectHandle	hDrawing	= ::GS_GetDrawingHeader( gCBP );
				MCObjectHandle	hLayer		= ::GS_FirstMemberObj( gCBP, hDrawing );
				while( hLayer ) {
					short	type	= gSDK->GetObjectTypeN( hLayer );
					if ( type == kLayerNode ) {
						// check if this layer is selected
						if ( ::GS_IsSelected( gCBP, hLayer ) ) {
							hContainer		= hLayer;
							::GS_GetLayerScaleN( gCBP, hContainer, dContainerScale );
							break;
						}
					}

					hLayer		= ::GS_NextObject( gCBP, hLayer );
				}
			} break;
	}

	// set output
	if ( pOutContainerType )
		*pOutContainerType			= containerType;
	if ( pOutContainerHandle )
		*pOutContainerHandle		= hContainer;
	if ( pOutContainerScale )
		*pOutContainerScale			= dContainerScale;
}

void VWObject::ResetObject()
{
	VWFC_ASSERT( fhObject );
	::GS_ResetObject( gCBP, fhObject );
}

short VWObject::GetType() const
{
	VWFC_ASSERT( fhObject );
	return gSDK->GetObjectTypeN( fhObject );
}

VWClass VWObject::GetObjectClass() const
{
	VWFC_ASSERT( fhObject );
	return VWClass( ::GS_GetObjectClass( gCBP, fhObject ) );
}

void VWObject::SetObjectClass(const VWClass& clas)
{
	VWFC_ASSERT( fhObject );
	::GS_SetObjectClass( gCBP, fhObject, clas );
}

VWObjectAttr& VWObject::GetObjectAttribs()
{
	fObjAttribs.fhObject	= fhObject;
	return fObjAttribs;
}

// XXX Vlado
// Singleton fix for Mac OS X 10.3 -- it has problems with static local variables
static VWObjectAttr		g_staticProps( nullptr );
const VWObjectAttr& VWObject::GetObjectAttribs() const
{
	g_staticProps			= fObjAttribs;
	g_staticProps.fhObject	= fhObject;
	return g_staticProps;
}

bool VWObject::IsVisible() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_IsVisible( gCBP, fhObject ) ? true : false;
}

void VWObject::SetVisible(bool bVisible /*=true*/)
{
	VWFC_ASSERT( fhObject );
	return ::GS_SetVisibility( gCBP, fhObject, bVisible );
}

bool VWObject::IsLocked() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_IsLocked( gCBP, fhObject ) ? true : false;
}

void VWObject::SetLock(bool bLock /*=true*/)
{
	VWFC_ASSERT( fhObject );
	::GS_LockObject( gCBP, fhObject, bLock );
}

bool VWObject::IsSelected() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_IsSelected( gCBP, fhObject ) ? true : false;
}

void VWObject::SetSelected(bool bSelect /*=true*/)
{
	VWFC_ASSERT( fhObject );
	::GS_SelectObject( gCBP, fhObject, bSelect );
}

TXString VWObject::GetObjectName() const
{
	VWFC_ASSERT( fhObject );
	TXString		intName;
	gSDK->GetObjectName(fhObject, intName );
	return intName;
}

void VWObject::SetObjectName(const TXString& name)
{
	VWFC_ASSERT( fhObject );
	GSError	err	= ::GS_SetObjectName( gCBP, fhObject, name );

	err;	// dumb use
	//bool b1 = err == 0;		// no err
	//bool b2 = err == nameNotUniqueErr;
	//bool b3 = err == nameTableFullErr;
}

InternalIndex VWObject::GetInternalIndex() const
{
	VWFC_ASSERT( fhObject );
	InternalIndex result = gSDK->GetObjectInternalIndex( fhObject );
	return result;
}

void VWObject::GetObjectBounds(VWRectangle2D& bounds) const
{
	WorldRect	worldBounds;
	::GS_GetObjectBounds( gCBP, fhObject, worldBounds );

	bounds.SetRect( worldBounds.Left(), worldBounds.Right(), worldBounds.Top(), worldBounds.Bottom() );
}

VWRectangle2D VWFC::VWObjects::VWObject::GetObjectBounds() const
{
	VWRectangle2D	result;
	this->GetObjectBounds( result );
	return result;
}

// get the object matrix.
// currently: get the object matrix to the layer if object is inside a layer.
void VWObject::GetObjectMatrix(VWTransformMatrix& outMatrix) const
{
	TransformMatrix			theMat;
	::GS_GetEntityMatrix( gCBP, fhObject, theMat );
	outMatrix		= theMat;
}

// --------------------------------------------------------------------------------------------------

void VWObject::SetObjectMatrix(const VWTransformMatrix& matrix)
{
	if ( VERIFYN( kAndrewB, fhObject ) )
	{
		if ( VWLocus3DObj::IsLocus3DObject( fhObject ) )
		{
			VWLocus3DObj	locus( fhObject );
			locus.SetObjectMatrix( matrix );
		}
		else
		{
			::GS_SetEntityMatrix( gCBP, fhObject, matrix );
		}
	}
}

VWTransformMatrix VWObject::GetObjectModelMatrix() const
{
	VWTransformMatrix	result;
	gSDK->GetEntityMatrix( fhObject, result );
	return result;
}

void VWObject::SetObjectModelMatrix( const VWTransformMatrix & matrix )
{
	gSDK->SetEntityMatrix( fhObject, matrix );
}

void VWObject::ApplyObjectMatrix(const VWTransformMatrix& matrix)
{
	VWTransformMatrix	objMatrix;
	this->GetObjectMatrix( objMatrix );
	this->SetObjectMatrix( objMatrix * matrix );
}

void VWObject::TransformObject(const VWTransformMatrix& matrix, bool applyTo3D, bool applyTo2D)
{
	this->TransformObjectReq( fhObject, matrix, applyTo3D, applyTo2D );
}

void VWObject::TransformObjectReq(MCObjectHandle hObject, const VWTransformMatrix& transf, bool applyTo3D, bool applyTo2D)
{
	short		type	= gSDK->GetObjectTypeN( hObject );
	switch( type ) {
		case kTermNode:
		case kUndoPlaceholderNode:
			break;

		case kGroupNode:
			{
				MCObjectHandle	hInnerObj	= gSDK->FirstMemberObj( hObject );
				while ( hInnerObj ) {
					this->TransformObjectReq( hInnerObj, transf, applyTo3D, applyTo2D );
					hInnerObj	= gSDK->NextObject( hInnerObj );
				}
			} break;

		// 3D
		case kLocus3DNode:
			if ( applyTo3D ) {
				VWLocus3DObj	locusObj( hObject );
				VWPoint3D		pt	= locusObj.GetPoint();
				pt					= transf.PointTransform( pt );
				locusObj.SetPoint( pt );
			}
			break;

		case qPolyNode:
			if ( applyTo3D ) {
				size_t			ptsCnt	= gSDK->CountVertices( hObject );
				for(size_t i=0; i<ptsCnt; i++) {
					short		ind		= DemoteTo<short>( kVStanev, i );
					WorldPt3	pt3( 0, 0, 0 );
					gSDK->Get3DVertex( hObject, ind+1, pt3 );
					VWPoint3D	pt		= transf.PointTransform( pt3 );
					gSDK->Set3DVertex( hObject, ind+1, pt, false );
				}
			}
			break;

		case kExtrudeNode:
		case kMultiExtrudeNode:
		case kSweepNode:
		case kCSGTreeNode:
		case kSymbolNode:
		case kParametricNode:
		case kMeshNode:
			if ( applyTo3D ) {
				VWObject(hObject).ApplyObjectMatrix( transf );
			}
			break;

		case kPieceWiseNurbsCurveNode:
		case kNurbsSurfaceNode: 
			if ( applyTo3D ) {
				TransformMatrix tempTransform(transf);
				gSDK->TransformGraphicObject( hObject, tempTransform);
			}
			break;

		// 2D ------------------------------------------------------------------------------------------------------------------------
		case kLocusNode:
			if ( applyTo2D ) {
				VWLocus2DObj	locusObj( hObject );
				VWPoint2D		pt	= locusObj.GetPoint();
				locusObj.SetPoint( transf.PointTransform( pt ) );
			}
			break;

		case kLineNode:
			if ( applyTo2D ) {
				VWLine2DObj		lineObj( hObject );
				VWPoint2D		a, b;
				lineObj.GetLine( a, b );
				lineObj.SetLine( transf.PointTransform( a ), transf.PointTransform( b ) );
			}
			break;

		case kBoxNode:
		case rBoxNode:
		case kOvalNode:
			if ( applyTo2D ) {
				WorldRect	rect;
				gSDK->GetObjectBounds( hObject, rect );

				WorldPt	cenHold		= rect.Center();
				WorldPt	cenOff		= cenHold;
				cenOff				= transf.PointTransform( cenOff );
				cenOff				-= cenHold;
				if ( ! cenOff.IsZero() )
				{
					gSDK->MoveObject( hObject, cenOff.x, cenOff.y );
				}

				VWPoint2D	rotateDir		= transf.GetUVector();
				double		angle			= rotateDir.CalcAng180();
				if ( ! MathUtils::Equalish( angle, 0, VWPoint2D::sEpsilon ) ) {
					gSDK->RotateObjectN( hObject, rect.Center() + cenOff, angle );
				}
			}
			break;

		case kArcNode:
			if ( applyTo2D ) {
				VWArcObj	arcObj( hObject );
				VWPoint2D	arcCenter	= arcObj.GetCenter();
				VWPoint2D	cenHold		= arcCenter;
				arcCenter				= transf.PointTransform( arcCenter );
				arcCenter				-= cenHold;
				gSDK->MoveObject( hObject, arcCenter.x, arcCenter.y );
				
				VWPoint2D	rotateDir	= transf.GetUVector();
				double		angle		= rotateDir.CalcAng180();
				if ( ! MathUtils::Equalish( angle, 0, VWPoint2D::sEpsilon ) ) {
					double	startAngleDeg, sweepAngleDeg;
					arcObj.GetAngles( startAngleDeg, sweepAngleDeg );
					arcObj.SetAngles( startAngleDeg + angle, sweepAngleDeg );
				}
			}
			break;

		case kTextNode:
			if ( applyTo2D ) {
				WorldPt		pt( 0, 0 );
				gSDK->GetLocusPosition( hObject, pt );
				gSDK->SetLocusPosition( hObject, transf.PointTransform( pt ) );

				
				VWPoint2D	rotateDir	= transf.GetUVector();
				double		angle		= rotateDir.CalcAng180();
				if ( ! MathUtils::Equalish( angle, 0, VWPoint2D::sEpsilon ) ) {
					double textRot = 0;
					short textFlip = 0;
					gSDK->GetTextOrientationN( hObject, textRot, textFlip );
					gSDK->SetTextOrientationN( hObject, angle + textRot, textFlip );
				}
			}
			break;

		case kPolygonNode:
		case kPolylineNode:
			if ( applyTo2D ) {
				VWPolygon2DObj	polyObj( hObject );
				size_t			vertsCnt	= polyObj.GetVertexCount();
				for(size_t i=0; i<vertsCnt; i++) {
					VWPoint2D	pt	= polyObj.GetVertexPoint( i );
					pt				= transf.PointTransform( pt );
					if ( polyObj.IsVertexCorner( i ) ) {
						polyObj.SetCornerVertex( i, pt, false );
					}
					else if ( polyObj.IsVertexBezier( i ) ) {
						polyObj.SetBezierVertex( i, pt, false );
					}
					else if ( polyObj.IsVertexCubic( i ) ) {
						polyObj.SetCubicVertex( i, pt, false );
					}
					else if ( polyObj.IsVertexArc( i ) ) {
						double	radius	= polyObj.GetVertexRadius( i );
						polyObj.SetArcVertex( i, pt, radius, false );
					}
					else if ( polyObj.IsVertexRadius( i ) )
					{
						polyObj.SetRadiusVertex( i, pt, false );
					}
				}

				size_t holeCnt = polyObj.GetHoleObjectsCount();
				for ( size_t i = 0; i < holeCnt; ++i )
				{
					this->TransformObjectReq( polyObj.GetHoleObjectAt( i ), transf, applyTo3D, applyTo2D );
				}
			}
			break;

		default:
			DSTOP((kVStanev, "VWObject::TransformObjectReq unsupported object type=%d", type));
			break;
	}
}

void VWObject::MoveObject(const VWPoint2D& offset)
{
	::GS_MoveObject( gCBP, fhObject, offset.x, offset.y );
}

void VWObject::MoveObject(double dx, double dy)
{
	::GS_MoveObject( gCBP, fhObject, dx, dy );
}

void VWObject::MoveObject3D(const VWPoint3D& offset)
{
	::GS_MoveObject3D( gCBP, fhObject, offset.x, offset.y, offset.z, false );
}

void VWObject::MoveObject3D(double dx, double dy, double dz)
{
	::GS_MoveObject3D( gCBP, fhObject, dx, dy, dz, false );
}

void VWObject::RotateObject(const VWPoint2D& pt, double dAngle)
{
	::GS_RotateObjectN( gCBP, fhObject, pt, dAngle );
}

void VWObject::ScaleObject(const VWPoint2D& cenPt, const VWPoint2D& scale)
{
	gSDK->ScaleObjectN( fhObject, cenPt, scale.x, scale.y );
}

void VWObject::ScaleObject(const VWPoint2D& cenPt, double scaleX, double scaleY)
{
	gSDK->ScaleObjectN( fhObject, cenPt, scaleX, scaleY );
}

bool VWObject::ScaleObject3D(const VWPoint3D& cenPt, const VWPoint3D& scale)
{
	return gSDK->ScaleObject3D( fhObject, cenPt, scale );
}

bool VWObject::ScaleObject3D(const VWPoint3D& cenPt, double scaleX, double scaleY, double scaleZ)
{
	return gSDK->ScaleObject3D( fhObject, cenPt, VWPoint3D( scaleX, scaleY, scaleZ ) );
}

void VWObject::TransformObjectN(const VWTransformMatrix& matrix)
{
	gSDK->TransformObject( fhObject, matrix );
}

double VWObject::GetRotationAroundAxis(MajorAxisSpec aroundAxis)
{
	return gSDK->GetRotationAroundAxis( fhObject, aroundAxis );
}

bool VWObject::IsPlanar() const
{
	TVariableBlock	var;
	gSDK->GetObjectVariable( fhObject, ovHasAssociatedPlane, var );
	bool	hasPlane	= ( var.GetBoolean( hasPlane ) && hasPlane );
	
	return	hasPlane;
}

bool VWObject::GetPlanarRef(TPlanarRefID& outPlanarRef) const
{
	bool	isPlanar	= this->IsPlanar();
	if ( isPlanar )
	{
		gSDK->GetPlanarRefID( fhObject, outPlanarRef );
	}
	return isPlanar;
}

void VWObject::SetPlanarRef(const TPlanarRefID& planarRef)
{
	gSDK->SetPlanarRefID( fhObject, planarRef );
}

void VWObject::SetPlanarRefToGround()
{
	gSDK->SetPlanarRefIDToGround( fhObject );
}

void VWObject::AttachAuxObject(MCObjectHandle hAuxObject)
{
	::GS_AttachAuxObject( gCBP, hAuxObject, fhObject );
}

void VWObject::DeleteAuxObject(MCObjectHandle hAuxObject)
{
	::GS_DeleteAuxObject( gCBP, hAuxObject, fhObject );
}

MCObjectHandle VWObject::FindAuxObject(short type, MCObjectHandle hLastAuxObject) const
{
	if ( hLastAuxObject == nullptr )
		return ::GS_FindAuxObject( gCBP, fhObject, type );
	else {
		MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hLastAuxObject );
		return ::GS_NextAuxObject( gCBP, hNextAux, type );
	}
}

MCObjectHandle VWObject::GetFirstAuxObject() const
{
	return ::GS_FirstAuxObject( gCBP, fhObject );
}

MCObjectHandle VWObject::GetParentAUX() const
{
	return ::GS_AuxOwner( gCBP, fhObject );
}

VWObjectIterator VWObject::GetFirstAuxObjectIterator() const
{
	return VWObjectIterator( ::GS_FirstAuxObject( gCBP, fhObject ) );
}

MCObjectHandle VWObject::FindRecordObject(const TXString& recordName, MCObjectHandle hLastAuxObject) const
{
	MCObjectHandle hRecObj	= this->FindAuxObject( kRecordNode, hLastAuxObject );
	while ( hRecObj && ! VWRecordObj::IsRecordObject( hRecObj, recordName ) ) {
		hRecObj	= this->FindAuxObject( kRecordNode, hRecObj );
	}

	return hRecObj;
}

void VWObject::SetTexture(InternalIndex textureRef, TexturePartSDK partID)
{
	gSDK->SetTextureRef( fhObject, textureRef, partID );
}

void VWObject::SetTexture(MCObjectHandle hTexture, TexturePartSDK partID)
{
	InternalIndex textureRef = gSDK->GetObjectInternalIndex(hTexture);
	gSDK->SetTextureRef( fhObject, textureRef, partID );
}

void VWObject::SetDefaultTextureMapping(TexturePartSDK partID)
{
	gSDK->SetDefaultTextureMapping( fhObject, partID );
}

void VWObject::GetTextureMappingInfo(TexturePartSDK partID, TextureMappingInfoSDK& outMappingInfo)
{
	outMappingInfo = gSDK->GetTextureMappingInfo( fhObject, partID, 0 );
}

void VWObject::GetTextureMappingInfo(TexturePartSDK partID, Sint32 decalLayerNum, TextureMappingInfoSDK& outMappingInfo)
{
	outMappingInfo = gSDK->GetTextureMappingInfo( fhObject, partID, decalLayerNum );
}

void VWObject::SetTextureMappingInfo(TexturePartSDK partID, const TextureMappingInfoSDK& mappingInfo)
{
	gSDK->SetTextureMappingInfo( fhObject, partID, 0, mappingInfo );
}

void VWObject::SetTextureMappingInfo(TexturePartSDK partID, Sint32 layerNum, const TextureMappingInfoSDK& mappingInfo)
{
	gSDK->SetTextureMappingInfo( fhObject, partID, layerNum, mappingInfo );
}

Sint32 VWObject::GetTextureMappingDecalLayerCount(TexturePartSDK partID)
{
	return gSDK->GetNumTextureLayers( fhObject, partID );
}

/*static*/void VWObject::ResetObjectsVisibility()
{
	::GS_ResetAllObjectsVisibility( gCBP );
}
//	extern "C" InternalIndex GS_CALLBACK GS_GetObjectClass(CallBackPtr, MCObjectHandle h);
//	extern "C" void GS_CALLBACK GS_SetObjectClass(CallBackPtr, MCObjectHandle h, InternalIndex classID);

/*static*/bool VWObject::IsSelected(MCObjectHandle hObj)
{
	return ::GS_IsSelected( gCBP, hObj );
}

// XXX Vlado This should be in VWDocument
/*static*/void VWObject::DeselectAll()
{
	::GS_DeselectAll( gCBP );
}

/*static*/void VWObject::DeleteObject(MCObjectHandle hObj, bool bUseUndo)
{
	::GS_DeleteObject( gCBP, hObj, bUseUndo );
}

/*static*/void VWObject::ResetObject(MCObjectHandle hObj)
{
	::GS_ResetObject( gCBP, hObj );
}

/*static*/ MCObjectHandle VWObject::GetNamedObject(const TXString& objName)
{
	return ::GS_GetNamedObject( gCBP, objName );
}

/*static*/ void VWObject::MakeUniqueObjectName(TXString& objName)
{
	objName = gSDK->CheckAndResolveDuplicateInternalName( objName );
}

/*static*/ InternalIndex VWObject::Handle2InternalIndex(MCObjectHandle hObject)
{
	InternalIndex result = hObject ? gSDK->GetObjectInternalIndex( hObject ) : 0;
	return result;
}

/*static*/ MCObjectHandle VWObject::InternalIndex2Handle(InternalIndex internalIndex)
{
	MCObjectHandle result = gSDK->InternalIndexToHandle( internalIndex );
	return result;
}
