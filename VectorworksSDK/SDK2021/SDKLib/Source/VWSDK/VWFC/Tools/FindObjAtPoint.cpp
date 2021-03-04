//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::Math;
using namespace VWFC::VWObjects;

CFindObjectAtPoint::CFindObjectAtPoint(MCObjectHandle hContainer)
{
	fIs3DSearch = false;
	fhContainer		= hContainer;
	if ( fhContainer == NULL ) {
		VWObject	layerObj( VWLayerObj::GetCurrentLayer() );
		if (  VWLayerObj::IsLayerObject( layerObj ) ) {
			fhContainer		= layerObj;
		}
		else {
			fhContainer		= layerObj.GetParentLayer();
		}
	}
}

CFindObjectAtPoint::~CFindObjectAtPoint()
{
}

void CFindObjectAtPoint::Search(EFindObjectOptions objOpt, EFindObjectTraversalOptions travOpt, const VWPoint3D& pt, double dRadius)
{
	farrFoundObjects.clear();

	Boolean bSaveInval	= ::GS_GetCallBackInval( gCBP );
	::GS_SetCallBackInval( gCBP, false );

	TProjection projection = gSDK->GetProjection( gSDK->GetActiveLayer() );
	
	fIs3DSearch = projection != /*TProjection::*/projectionPlan;


	this->Search( fhContainer, farrFoundObjects, objOpt, travOpt, pt, dRadius );

	::GS_SetCallBackInval( gCBP, bSaveInval );
}

size_t CFindObjectAtPoint::GetFoundObjectsCount() const
{
	return farrFoundObjects.size();
}

MCObjectHandle CFindObjectAtPoint::GetFoundObjectAt(size_t index) const
{
	MCObjectHandle	hObject	= NULL;
	ASSERTN( kVStanev, index < farrFoundObjects.size() );
	if ( index < farrFoundObjects.size() ) {
		hObject	= farrFoundObjects[ index ];
	}

	return hObject;
}

inline void AvoidWindowsUnresponsiveness() {
#if GS_WIN
	static std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (currentTime >= testTime) {
		testTime = currentTime + std::chrono::seconds(1);
		MSG msg;
		// http://stackoverflow.com/questions/402832/avoiding-not-responding-label-in-windows-while-processing-lots-of-data-in-one
		// Windows assumes we are dead unless we are actively looking at our messages (Note: We don't actually do anything).  JLoy - 6/17/16
		PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	}
#endif
}

void CFindObjectAtPoint::Search(MCObjectHandle hContainer, TObjectsArray& outArray, EFindObjectOptions objOpt, EFindObjectTraversalOptions travOpt, const VWPoint3D& pt, double dRadius)
{
	MCObjectHandle	hCurr	= ::GS_FirstMemberObj( gCBP, hContainer );
	while ( hCurr ) {
		short		type				= gSDK->GetObjectTypeN( hCurr );
		if ( type != 0 ) {
			Boolean		bIsVisible			= ::GS_IsVisible( gCBP, hCurr );
			Boolean		bIsSelected			= ::GS_IsSelected( gCBP, hCurr );
			Boolean		bIsLocked			= ::GS_IsLocked( gCBP, hCurr );
			Boolean		bCheckThisObject	= false;
			switch( objOpt ) {
				case EFindObjectOptions::AllObjs:			bCheckThisObject	= true;			break;
				case EFindObjectOptions::VisibleOnly:		bCheckThisObject	= bIsVisible;	break;
				case EFindObjectOptions::SelectedOnly:		bCheckThisObject	= bIsSelected;	break;
				case EFindObjectOptions::UnlockedOnly:		bCheckThisObject	= ! bIsLocked;	break;
			}

			if ( bCheckThisObject ) {
				AvoidWindowsUnresponsiveness();
				Boolean		bIsContainer	= VWGroupObj::IsGroupObject( hCurr );

				if ( ( bIsContainer && travOpt == EFindObjectTraversalOptions::Groups ) || VWLayerObj::IsLayerObject( hCurr ) ) {
					this->Search( hCurr, outArray, objOpt, travOpt, pt, dRadius );
				}
				else {
					if ( this->CheckObject( hCurr, pt, dRadius ) ) {
						outArray.push_back( hCurr );
					}
				}
			}
		}

		hCurr	= GS_NextObject( gCBP, hCurr );
	}
}

bool CFindObjectAtPoint::CheckObject(MCObjectHandle hObject, const VWPoint3D& pt, double dRadius)
{
	bool	bObjOk		= false;
	
	TPlanarRefID refId;
	gSDK->GetPlanarRefID( hObject, refId );
	bool isPlanarObj = gSDK->IsPlanarObject( hObject, refId );
	if( !(refId == kPlanarRefID_ScreenPlane && isPlanarObj && fIs3DSearch) )
	{
		if ( VWLocus2DObj::IsLocus2DObject( hObject ) )
		{
			VWLocus2DObj	locObj( hObject );

			if( fIs3DSearch )
			{
				VWPoint3D		locPt		= locObj.GetPoint();

				TransformMatrix matrix;
				matrix.SetToIdentity();
				gSDK->GetPlanarMatrix( refId, matrix );
				VWTransformMatrix planeMat( matrix );
				locPt = planeMat.PointTransform( locPt );

				bObjOk						= locPt.DistanceTo( pt ) < dRadius;
			}
			else
			{
				VWPoint2D		locPt		= locObj.GetPoint();
				bObjOk						= locPt.DistanceTo( pt ) < dRadius;
			}
		}
		else if( VWLocus3DObj::IsLocus3DObject( hObject ) )
		{
			VWLocus3DObj	locObj( hObject );

			VWPoint3D locPt = locObj.GetPoint();

			if( fIs3DSearch )
			{
				bObjOk = locPt.DistanceTo( pt ) < dRadius;
			}
			else
			{
				locPt.z = VWLayerObj( gSDK->GetActiveLayer() ).GetElevation();
				bObjOk = locPt.DistanceTo( pt ) < dRadius;
			}
		}
		else if ( VWLine2DObj::IsLine2DObject( hObject ) ) {
			VWLine2DObj		lineObj( hObject );

			if( fIs3DSearch )
			{
				VWPoint3D startPt	= lineObj.GetStartPoint();
				VWPoint3D endPt		= lineObj.GetEndPoint();

				TransformMatrix matrix;
				matrix.SetToIdentity();
				gSDK->GetPlanarMatrix( refId, matrix );
				VWTransformMatrix planeMat( matrix );
				startPt		= planeMat.PointTransform( startPt );
				endPt		= planeMat.PointTransform( endPt );

				VWLine3D	line( startPt, endPt );
				bObjOk		= line.GetDistance( pt ) < dRadius;
			}
			else
			{
				VWLine2D		line( lineObj.GetStartPoint(), lineObj.GetEndPoint() );
				VWPoint2D		linePtPerp	= line.PtPerpLine( pt );
				bObjOk						= linePtPerp.DistanceTo( pt ) < dRadius;
			}
		}
		else if ( VWPolygon2DObj::IsPoly2DObject( hObject ) ) {
			WorldRect	worldBounds;
			::GS_GetObjectBounds( gCBP, hObject, worldBounds );

			if ( ! worldBounds.IsEmpty() ) {
				// enlarge with the radius
				worldBounds.Outset( dRadius, dRadius );
				VWPoint3D rotPt = this->UpdatePtWithPlanRotation( gSDK->ParentObject( hObject ),  pt );
				WorldPt rotPt2D( rotPt.x, rotPt.y );
				if ( worldBounds.ContainsPoint( rotPt2D ) ) {
					MCObjectHandle	hThisObject		= hObject;
					bool			bDoPolygonize	= ! VWPolygon2DObj::IsPolygon2DObject( hThisObject );
					if ( bDoPolygonize ) {
						// polygonize
						VWPolygon2DObj	polygonizedObj( ::GS_DuplicateObject( gCBP, hThisObject ) );
						polygonizedObj.ConvertToPolygon();

						hThisObject			= polygonizedObj;
					}

					VWPolygon2DObj	polyObj( hThisObject );
					VWPolygon2D		poly;

					short type = gSDK->GetObjectTypeN( hObject );

					if ( type == kBoxNode ) 
					{
						using namespace VectorWorks::Objects;
						IRectangleObj*	pRectObj = NULL;
						if ( VCOM_SUCCEEDED( ::GS_VWQueryInterface( IID_RectangleObj, (IVWUnknown**) & pRectObj ) ) )  
						{
							WorldPt orientation;
							pRectObj->GetOrientation( hObject, orientation );

							WorldCoord width		= 0;
							pRectObj->GetWidth( hObject, width );
							WorldCoord height		= 0;
							pRectObj->GetHeight( hObject, height );

							if (Abs(width) > 0 && Abs(height) > 0) {
								WorldPt origin;
								pRectObj->GetOrigin( hObject, origin );
								WorldPt	b = width * orientation + origin;
								WorldPt d = height * orientation.Perpendicular() + origin;
								WorldPt c = width * orientation + d;
								poly.AddVertex( origin.x, origin.y );
								poly.AddVertex( b.x, b.y );
								poly.AddVertex( c.x, c.y );
								poly.AddVertex( d.x, d.y );
							}

							pRectObj->Release();
						}
					}
					else
					{
						polyObj.GetPolygon(poly);
					}

					bObjOk		= poly.IsPtInOrOnPoly2D( pt, dRadius );

					if ( ! bObjOk ) {
						size_t		objCnt	= polyObj.GetHoleObjectsCount();
						for(size_t i=0; i<objCnt; i++) {
							MCObjectHandle	hHole	= polyObj.GetHoleObjectAt( i );
							bObjOk					= this->CheckObject( hHole, pt, dRadius );
							if ( bObjOk ) {
								// STOP!
								break;
							}
						}
					}

					if ( bDoPolygonize ) {
						// delete temp polygonized object
						::GS_DeleteObject( gCBP, hThisObject, false );
					}
				}
			}
		}
		else if ( VWArcObj::IsArcObject( hObject ) ) {
			VWArcObj			arcObj( hObject );

			WorldRect	worldBounds;
			::GS_GetObjectBounds( gCBP, hObject, worldBounds );

			// enlarge with the radius
			worldBounds.Outset( dRadius, dRadius );

			VWPoint3D rotPt = this->UpdatePtWithPlanRotation( gSDK->ParentObject( hObject ),  pt );
			WorldPt rotPt2D( rotPt.x, rotPt.y );
			if ( worldBounds.ContainsPoint( rotPt2D ) ) {
				VWPoint2D			ptCenter;
				double				dStartAngleDeg;
				double				dSweepAngleDeg;
				double				dRadiusX;
				double				dRadiusY;

				arcObj.GetInfo( ptCenter, dStartAngleDeg, dSweepAngleDeg, dRadiusX, dRadiusY );
				if ( MathUtils::Equalish( dRadiusX, dRadiusY, 0.0001 ) ) {
					// we have circle
					VWArc2D		arc( ptCenter, dRadiusX, dStartAngleDeg, dSweepAngleDeg );
					VWPoint2D	ptOnAcr		= arc.PtPerpArc( pt );
					bObjOk					= ptOnAcr.DistanceTo( pt ) < dRadius;
				}
				else {
					// we have ellipse
					// NOT IMPLEMENTED !!!
					ASSERTN( kVStanev, false );
				}
			}
		}
		else if ( VWSymbolObj::IsSymbolObject( hObject ) ) {
			VWSymbolObj			symObj( hObject );

			WorldRect	worldBounds;
			WorldCube	worldCube;
			::GS_GetObjectBounds( gCBP, hObject, worldBounds );
			::GS_GetObjectCube( gCBP, hObject, worldCube );

			// enlarge with the radius
			worldBounds.Outset( dRadius, dRadius );
			worldCube.Outset( dRadius, dRadius, dRadius );

			VWPoint3D rotPt = this->UpdatePtWithPlanRotation( gSDK->ParentObject( hObject ),  pt );
			WorldPt rotPt2D( rotPt.x, rotPt.y );

			if	(	( worldBounds.ContainsPoint( rotPt2D ) && !fIs3DSearch )
				||	( worldCube.ContainsPoint( pt ) && fIs3DSearch )
				) 
			{
				MCObjectHandle		hSymDef		= symObj.GetSymbolDef();
				if ( VWSymbolDefObj::IsSymbolDefObject( hSymDef ) ) {
					VWTransformMatrix	objTransform;
					symObj.GetObjectMatrix( objTransform );

					VWPoint3D			locPt	= objTransform.InversePointTransform( pt );

					TObjectsArray		array;
					this->Search( hSymDef, array, EFindObjectOptions::AllObjs, EFindObjectTraversalOptions::Groups, locPt, dRadius );

					bObjOk						= array.size() > 0;
				}
			}
		}
		else if ( VWParametricObj::IsParametricObject( hObject ) ) {
			VWParametricObj		paramObj( hObject );

			WorldRect	worldBounds;
			WorldCube	worldCube;
			::GS_GetObjectBounds( gCBP, hObject, worldBounds );
			gSDK->GetObjectCube( hObject, worldCube );

			// enlarge with the radius
			worldBounds.Outset( dRadius, dRadius );
			worldCube.Outset( dRadius, dRadius, dRadius );

			VWPoint3D rotPt = this->UpdatePtWithPlanRotation( gSDK->ParentObject( hObject ),  pt );
			WorldPt rotPt2D( rotPt.x, rotPt.y );

			if	(	( worldBounds.ContainsPoint( rotPt2D ) && !fIs3DSearch )
				||	( worldCube.ContainsPoint( pt ) && fIs3DSearch )
				) 
			{
				VWTransformMatrix	objTransform;
				paramObj.GetObjectToWorldTransform( objTransform );

				VWPoint2D			locPt	= objTransform.InversePointTransform( pt );

				TObjectsArray		array;
				this->Search( hObject, array, EFindObjectOptions::AllObjs, EFindObjectTraversalOptions::Groups, locPt, dRadius );

				bObjOk						= array.size() > 0;
			}
		}
		else if ( VWTextBlockObj::IsTextBlockObject( hObject ) )
		{
			VWTextBlockObj	textObj( hObject );

			WorldRectVerts	boxVertices;
			textObj.GetTextBoundary( boxVertices );

			VWPolygon2D		poly;
			poly.AddVertex( boxVertices.topLeft );
			poly.AddVertex( boxVertices.topRight );
			poly.AddVertex( boxVertices.bottomRight );
			poly.AddVertex( boxVertices.bottomLeft );
			poly.SetClosed( true );

			bObjOk		= poly.IsPtInOrOnPoly2D( pt, dRadius );
		}
	}

	return bObjOk;
}

VWPoint3D CFindObjectAtPoint::UpdatePtWithPlanRotation(MCObjectHandle parentObj, const VWPoint3D& pt) const
{
	VWPoint2D	newPt		= pt;

	if ( gSDK->GetObjectTypeN( parentObj ) == kLayerNode && gSDK->IsPlanRotationView() )
	{
		// get plan rotation transform.
		VWTransformMatrix viewMatrix;
		gSDK->GetViewMatrix( parentObj, viewMatrix );

		newPt = viewMatrix.PointTransform( pt );
	}

	return newPt; 
}