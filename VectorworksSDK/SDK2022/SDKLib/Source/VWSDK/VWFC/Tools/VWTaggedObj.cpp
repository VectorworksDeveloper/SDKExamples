//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::Math;

const char* VWTaggedObj::TagOrientationStrings[] = {
    "None",
    "Left",
    "Right",
    "Floating"
};

VWTaggedObj::VWTaggedObj()
	: fIsWorldOrientationUsed( false )
{
	objectHandle	=	NULL;
}

VWTaggedObj::~VWTaggedObj()
{
	if (!fDrawArea.IsEmpty()) {
		gSDK->RedrawRect(fDrawArea);
	}
}

WorldPt VWTaggedObj::GetTagControlPoint(EPointID controlPointID)
{
    WorldPt point;

    VWParametricObj taggedObject(objectHandle);

    switch(controlPointID) {
        case kTagPoint:
            point.x = taggedObject.GetParamReal(tagPointIdx);
            point.y = taggedObject.GetParamReal(tagPointIdx+1);
            break;
        case kShoulderPoint:
            point.x = taggedObject.GetParamReal(shoulderPointIdx);
            point.y = taggedObject.GetParamReal(shoulderPointIdx+1);
            break;
        case kEndPoint:
            point.x = taggedObject.GetParamReal(endPointIdx);
            point.y = taggedObject.GetParamReal(endPointIdx+1);
            break;
    }
    return(point);
}

void VWTaggedObj::DrawTag(InternalIndex classID)
{
    ASSERTN(kBAtwood, objectHandle != nil);

    ETagOrientation orientation = GetTagOrientation();
    VWParametricObj taggedObject(objectHandle);
	MCObjectHandle leaderLine = NULL;
	MCObjectHandle shoulderLine = NULL;

    if(orientation != kTagNone) {
        WorldPt shoulderPoint = GetTagControlPoint(kShoulderPoint);
        WorldPt tagPoint = GetTagControlPoint(kTagPoint);
        
        bool isRightOriented = (GetTagOrientation() != kTagLeft);
        if(kTagFloating != orientation) {
            DrawLeaderLine(classID, leaderLine, shoulderLine);
        }
        double angle = 0;

        if(useShoulder && kTagFloating != orientation) {

			if(shoulderPoint != tagPoint) {
                angle = isRightOriented ? GetAngle(shoulderPoint, tagPoint) : GetAngle(shoulderPoint, tagPoint)+180;
            } else {
                angle = 0;
            }
        } else {
            // If there is no shoulder, the tag should be drawn horizontally, always.
            // Thus it is necessary to counteract the tagged object's rotation.
            VWTransformMatrix matrix;
            taggedObject.GetObjectMatrix(matrix);
			if  ( fIsWorldOrientationUsed )
			{
				VWPoint2D pt1	= VWPoint2D( 0.0, 0.0 );
				VWPoint2D pt2	= VWPoint2D( 1.0, 0.0 );
				pt1				= matrix.PointTransform( pt1 );
				pt2				= matrix.PointTransform( pt2 );
				angle			= -1 * ( pt2 - pt1 ).CalcAng360();
			}
			else
			{
				VWPoint2D uvec	= matrix.GetUVector();
				angle			= -1 * uvec.CalcAng180();
				// compensate for the site to appear flipped when the angle is above |90|
				if ( Double1_GT_Double2( Abs(angle), 90.0 ) )
				{
					angle	+= 180;
				}
			}
        }

		if( !useShoulder )
		{
			tagPoint = shoulderPoint;
		}

        DrawTagBody(tagPoint, angle, isRightOriented, leaderLine, shoulderLine);
    }
}

void VWTaggedObj::InitTag(  MCObjectHandle taggedObjectHandle,
                            short tagControlPointIdx, 
                            short shoulderControlPointIdx, 
                            short endControlPointIdx,
                            short approachLineAngleIdx,
                            short shoulderLineAngleIdx,
                            short tagOrientationIdx,
                            bool useEndMarker,
                            bool useLeaderLineShoulder,
							bool isWorldOrientationUsed/* = false*/,
							bool isUpdatingSkipped/* = false*/,
							bool isChangeTagLengthOnly /*= false*/,
							bool isChangeShoulderLengthOnly /*= false*/,
							bool isTagOrientationConstrained /*= false*/,
							double shoulderAngleFromStyle /*= 0.0*/,
							bool isMoveEntireTagFromEndPt /*= false*/)
{
    objectHandle = taggedObjectHandle;
    tagPointIdx = tagControlPointIdx;
    shoulderPointIdx = shoulderControlPointIdx;
    endPointIdx = endControlPointIdx;
    approachAngleIdx = approachLineAngleIdx;
    shoulderAngleIdx = shoulderLineAngleIdx;
    orientationIdx = tagOrientationIdx;
    useMarker = useEndMarker;
    useShoulder = useLeaderLineShoulder;
	fIsWorldOrientationUsed = isWorldOrientationUsed;
	fIsChangeTagLengthOnly	= isChangeTagLengthOnly;
	fIsChangeShoulderLengthOnly	= isChangeShoulderLengthOnly;
	fIsTagOrientationConstrained = isTagOrientationConstrained;
	fIsMoveEntireTagFromEndPt = isMoveEntireTagFromEndPt;

    ASSERTN(kBAtwood, objectHandle != nil);

    VWParametricObj taggedObject(objectHandle);

    bool duringFileRead;
    GS_GetProgramVariable(gCBP, varIsResettingPlugInsDuringFileRead, &duringFileRead);

    taggedObject.EnableParameter_OBSOLETE(approachAngleIdx, useLeaderLineShoulder);
    taggedObject.EnableParameter_OBSOLETE(shoulderAngleIdx, useLeaderLineShoulder);

    if(!duringFileRead && !isUpdatingSkipped) {
        // Rectify the tag to account for changes in the plant data.
        WorldPt tagPoint = GetTagControlPoint(kTagPoint);
        WorldPt shoulderPoint = GetTagControlPoint(kShoulderPoint);
        WorldPt endPoint = GetTagControlPoint(kEndPoint);
        double prevApproachAngle = GetAngle(endPoint, shoulderPoint);
        double prevShoulderAngle = GetAngle(shoulderPoint, tagPoint);
        double approachAngle = taggedObject.GetParamReal(approachAngleIdx);
        double shoulderAngle = taggedObject.GetParamReal(shoulderAngleIdx);
		
		// Mod division before comparing angles
		prevApproachAngle = fmod( prevApproachAngle, 360.0 );
		if ( prevApproachAngle < 0 )
			prevApproachAngle += 360.0;

		approachAngle = fmod( approachAngle, 360.0 );
		if ( approachAngle < 0 )
			approachAngle += 360.0;

		prevShoulderAngle = fmod( prevShoulderAngle, 360.0 );
		if ( prevShoulderAngle < 0 )
			prevShoulderAngle += 360.0;

		shoulderAngle = fmod( shoulderAngle, 360.0 );
		if ( shoulderAngle < 0 )
			shoulderAngle += 360.0;

		// Fix case where "-0.00" is displayed
		if ( approachAngle == 0.0 )
			approachAngle = std::abs( (int)approachAngle );
		if ( shoulderAngle == 0.0 )
			shoulderAngle = std::abs( (int)shoulderAngle );

		shoulderAngle = this->GetShoulderAngleFromStyleIfNeeded(shoulderAngle, shoulderAngleFromStyle);

		taggedObject.SetParamReal(approachAngleIdx, approachAngle );
		taggedObject.SetParamReal(shoulderAngleIdx, shoulderAngle );

        bool approachChanged = !DoublesAreNearlyEqual(prevApproachAngle, approachAngle);
        bool shoulderChanged = !DoublesAreNearlyEqual(prevShoulderAngle, shoulderAngle);
        ETagOrientation orientation = GetTagOrientation();

		VWTransformMatrix matrix;
        taggedObject.GetObjectMatrix( matrix );
		
        if(approachChanged) {

            WorldPt newShoulder;
            newShoulder.SetAngle(approachAngle*(PI/180.0));
            newShoulder += endPoint;
            WorldPt perpPoint;
            perpPoint.SetAngle((shoulderAngle+90)*(PI/180));
            VWLine2D perpLine(VWPoint2D(tagPoint), VWPoint2D(tagPoint+perpPoint));

			WorldPt	tempPoint	= tagPoint;		// init.
			if ( shoulderPoint == tagPoint )	// shoulder point coincides with tag point.
			{
				// being here (approach angle changed) means that either the end point or the shoulder point is moved.
				// also, the shoulder coincides with the tag point and we can't use the intersecting lines function (second line has zero length).
				// the case could be: the shoulder control point was picked up to be moved, but as it coincides with the tag point,
				// actually was moved the tag point (as coincident). However, the shoulder control point (the picked one) was also internally moved,
				// so as a result we again have them coincident. In this case the shoulder angle is still the angle between the old shoulder point and the new tag point,
				// this is what we can use to compose the second line for the following function for intersecting lines.

				tempPoint.SetAngle( shoulderAngle * ( PI / 180 ) );
				tempPoint		+= shoulderPoint;
			}

            VWPoint2D intersection;
            bool parallel;
            bool onShoulder;
            bool onApproach;
            VWLine2D::IntersectLines(VWPoint2D(endPoint), 
                                     VWPoint2D(newShoulder), 
                                     VWPoint2D(shoulderPoint),
                                     VWPoint2D(tempPoint),
                                     intersection, parallel, onShoulder, onApproach);

            if(parallel || 
               !perpLine.AreOnSameSide(shoulderPoint.x, shoulderPoint.y, intersection.x, intersection.y) ||
               !DoublesAreNearlyEqual(GetAngle(endPoint, intersection), approachAngle) ||
			   !useShoulder)
			{
                // If we can't find a point along the shoulder line to place the new shoulder,
                // we fall through and use the shoulderChanged case.
                
                shoulderChanged = true;
            } else {
                shoulderPoint = intersection;
            }

        }
        
        if(shoulderChanged) {
            //Apply changes to shoulder angle, if any
            double approachLength = sqrt(pow(shoulderPoint.x-endPoint.x, 2)+ 
                                         pow(shoulderPoint.y-endPoint.y, 2));
            double shoulderLength = sqrt(pow(tagPoint.x-shoulderPoint.x, 2)+ 
                                         pow(tagPoint.y-shoulderPoint.y, 2));
            shoulderPoint.x = endPoint.x + (cos(approachAngle*(PI/180.0)) * approachLength);
            shoulderPoint.y = endPoint.y + (sin(approachAngle*(PI/180.0)) * approachLength);
            tagPoint.x = shoulderPoint.x + (cos(shoulderAngle*(PI/180.0)) * shoulderLength);
            tagPoint.y = shoulderPoint.y + (sin(shoulderAngle*(PI/180.0)) * shoulderLength);

			WorldPt orgTagPoint			= tagPoint;
			WorldPt orgShoulderPoint	= shoulderPoint;

			if ( fIsWorldOrientationUsed )
			{
				orgTagPoint			= matrix.PointTransform( tagPoint );
				orgShoulderPoint	= matrix.PointTransform( shoulderPoint );
			}

            if(orientation == kTagRight && orgTagPoint.x < orgShoulderPoint.x) {
                SetTagOrientation(kTagLeft);
            } else if(orientation == kTagLeft && orgTagPoint.x > orgShoulderPoint.x) {
                SetTagOrientation(kTagRight);
            }
        } 
        
		// if fIsWorldOrientationUsed is true, this means that the orantation is update manually by the function UpdateTagOrentation.
        if( !fIsWorldOrientationUsed && !(shoulderChanged || approachChanged)){
            // If the angles were not changed, we should flip the tag around to respect
            // the chosen orientation
            if((orientation == kTagRight && tagPoint.x < shoulderPoint.x) ||
                (orientation == kTagLeft && tagPoint.x > shoulderPoint.x)) {

                if(orientation != kTagFloating) {
                    tagPoint.x += 2*(shoulderPoint.x-tagPoint.x);
                } else {
                    shoulderPoint.x += 2*(tagPoint.x-shoulderPoint.x);
                }

				double	newShoulderAng = GetAngle(shoulderPoint, tagPoint);
				newShoulderAng = fmod( newShoulderAng, 360.0 );
				if ( newShoulderAng < 0 )
					newShoulderAng += 360.0;
                taggedObject.SetParamReal(shoulderAngleIdx, newShoulderAng);

				double	newApproachAng = GetAngle(endPoint, shoulderPoint);
				if ( newApproachAng < 0 )
					newApproachAng += 360.0;
                taggedObject.SetParamReal(approachAngleIdx, newApproachAng);

            }
        }
		else if ( fIsWorldOrientationUsed )
		{
			WorldPt orgTagPoint			= matrix.PointTransform( tagPoint );
			WorldPt orgShoulderPoint	= matrix.PointTransform( shoulderPoint );

            if ( orientation == kTagRight && orgTagPoint.x < orgShoulderPoint.x )
			{
                this->SetTagOrientation( kTagLeft );
            }
			else if ( orientation == kTagLeft && orgTagPoint.x > orgShoulderPoint.x )
			{
                this->SetTagOrientation(kTagRight);
            }
		}

        taggedObject.SetParamReal(shoulderPointIdx, shoulderPoint.x);
        taggedObject.SetParamReal(shoulderPointIdx+1, shoulderPoint.y);
        taggedObject.SetParamReal(tagPointIdx, tagPoint.x);
        taggedObject.SetParamReal(tagPointIdx+1, tagPoint.y);
        
    }
}

void VWTaggedObj::DrawTagInteractive(EPointID movedPointID, VWPoint2D* cursorOffset)
{        
    ASSERTN(kBAtwood, objectHandle != nil);

    if(GetTagOrientation() != kTagFloating) {

        VWParametricObj taggedObject(objectHandle);

        WorldPt movedPoint;
        WorldPt tagPoint = GetTagControlPoint(kTagPoint);
        WorldPt shoulderPoint = GetTagControlPoint(kShoulderPoint);
        WorldPt endPoint = GetTagControlPoint(kEndPoint);

        if((movedPointID == kShoulderPoint && tagPoint == shoulderPoint) ||
           (movedPointID == kEndPoint && endPoint == tagPoint)) {
            movedPointID = kTagPoint;
        } else if(movedPointID == kEndPoint && endPoint == shoulderPoint) {
            movedPointID = kShoulderPoint;
        }

        VWTransformMatrix matrix;
        taggedObject.GetObjectMatrix(matrix);

        tagPoint = matrix.PointTransform(tagPoint);
        shoulderPoint = matrix.PointTransform(shoulderPoint);
        endPoint = matrix.PointTransform(endPoint);

        if(nil == cursorOffset) {
            GS_GetToolPtCurrent2D(gCBP, movedPoint);
        } else {
            movedPoint = kTagPoint == movedPointID ? tagPoint : (kShoulderPoint == movedPointID ? shoulderPoint : endPoint);
            movedPoint += *cursorOffset;
        }

        switch(movedPointID) {
            case kTagPoint:
                if(shoulderPoint == tagPoint && endPoint == tagPoint) {
                    shoulderPoint.x = (movedPoint.x+endPoint.x)/2;
                    shoulderPoint.y = movedPoint.y;
                }

				if (fIsChangeTagLengthOnly)
				{
					tagPoint = this->GetPointWithChangedLengthOnly(tagPoint, shoulderPoint, movedPoint);
				}
				else if (fIsTagOrientationConstrained)
				{
					tagPoint = this->GetTagPotAtNinetyDegIfOrientationChanged(movedPoint);
				}
				else
				{
					tagPoint += movedPoint - tagPoint;
				}

                break;
            case kShoulderPoint:

				if (fIsChangeShoulderLengthOnly)
				{
					WorldPt oldShoulderPoint	= shoulderPoint;
					shoulderPoint				= this->GetPointWithChangedLengthOnly(shoulderPoint, endPoint, movedPoint);
					tagPoint					+= shoulderPoint - oldShoulderPoint;
				}
				else
				{
					tagPoint += movedPoint - shoulderPoint;
					shoulderPoint += movedPoint - shoulderPoint;
				}

                break;
            case kEndPoint:
				if (fIsMoveEntireTagFromEndPt)
				{
					WorldPt offset	= movedPoint - endPoint;
					tagPoint		+= offset;
					shoulderPoint	+= offset;
					endPoint		= movedPoint;
				}
				else
				{
					endPoint += movedPoint - endPoint;
				}
                break;
        }

        if(useShoulder) {
            GS_DrawCoordLine(gCBP, tagPoint, shoulderPoint);
            GS_DrawCoordLine(gCBP, shoulderPoint, endPoint);
			fDrawArea.Unite( tagPoint );
			fDrawArea.Unite( shoulderPoint );
			fDrawArea.Unite( endPoint );
			
        } else {

            GS_DrawCoordLine(gCBP, shoulderPoint, endPoint);
			fDrawArea.Unite( shoulderPoint );
			fDrawArea.Unite( endPoint );

        }
    }
}

void VWTaggedObj::OnMoveTagControlPoint(EPointID movedPointID, VWPoint2D* cursorOffset)
{
    ASSERTN(kBAtwood, objectHandle != nil);

    WorldPt endPoint = GetTagControlPoint(kEndPoint);
    WorldPt shoulderPoint = GetTagControlPoint(kShoulderPoint);
    WorldPt tagPoint = GetTagControlPoint(kTagPoint);
    ETagOrientation orientation  = GetTagOrientation();

    if((movedPointID == kShoulderPoint && tagPoint == shoulderPoint) ||
       (movedPointID == kEndPoint && endPoint == tagPoint)) {
        movedPointID = kTagPoint;
    } else if(movedPointID == kEndPoint && endPoint == shoulderPoint) {
        movedPointID = kShoulderPoint;
    }

    VWParametricObj taggedObject(objectHandle);

    WorldPt movedPoint;
    VWTransformMatrix matrix;
    taggedObject.GetObjectMatrix(matrix);
        
    if(nil == cursorOffset) {
        GS_GetToolPtCurrent2D(gCBP, movedPoint);
        movedPoint = matrix.InversePointTransform(movedPoint);
    } else {
        movedPoint = kTagPoint == movedPointID ? tagPoint : (kShoulderPoint == movedPointID ? shoulderPoint : endPoint);
        movedPoint = matrix.PointTransform(movedPoint);
        movedPoint += *cursorOffset;
        movedPoint = matrix.InversePointTransform(movedPoint);
    }  

    switch(movedPointID) {
        case kTagPoint:
			if(shoulderPoint == tagPoint && endPoint == tagPoint) {
				shoulderPoint.x = (movedPoint.x + endPoint.x)/2;
				shoulderPoint.y = movedPoint.y;
			} else if(orientation == kTagFloating) {
				//if the shoulder point is disabled, move it along with the tag.
				shoulderPoint += (movedPoint-tagPoint);
			} else if(shoulderPoint == tagPoint) {
				shoulderPoint = movedPoint;
			}			

			if (fIsChangeTagLengthOnly)
			{
				tagPoint = this->GetPointWithChangedLengthOnly(tagPoint, shoulderPoint, movedPoint);
			}
			else if (fIsTagOrientationConstrained)
			{
				WorldPt movedPointGlobal;
				gSDK->GetToolPtCurrent2D(movedPointGlobal);
				movedPoint	= this->GetTagPotAtNinetyDegIfOrientationChanged(movedPointGlobal);
				tagPoint	= matrix.InversePointTransform(movedPoint);
			}
			else
			{
				tagPoint = movedPoint;
			}
            break;
        case kShoulderPoint:

			if (fIsChangeShoulderLengthOnly)
			{
				WorldPt oldShoulderPoint	= shoulderPoint;
				shoulderPoint				= this->GetPointWithChangedLengthOnly(shoulderPoint, endPoint, movedPoint);
				tagPoint					+= shoulderPoint - oldShoulderPoint;
			}
			else
			{
				tagPoint += movedPoint - shoulderPoint;
				shoulderPoint = movedPoint;
			}
            break;
        case kEndPoint:
			if (fIsMoveEntireTagFromEndPt)
			{
				WorldPt offset	= movedPoint - endPoint;
				tagPoint		+= offset;
				shoulderPoint	+= offset;
			}

			endPoint = movedPoint;
			
            break;
    }

	WorldPt orgTagPoint			= tagPoint;
	WorldPt orgShoulderPoint	= shoulderPoint;

	if ( fIsWorldOrientationUsed )
	{
		orgTagPoint			= matrix.PointTransform( tagPoint );
		orgShoulderPoint	= matrix.PointTransform( shoulderPoint );
	}

    //update the tag orientation to match the new location.
    if(orientation == kTagRight && orgTagPoint.x < orgShoulderPoint.x) {
        SetTagOrientation(kTagLeft);        
    } else if(orientation == kTagLeft && orgTagPoint.x > orgShoulderPoint.x) {
        SetTagOrientation(kTagRight);
    }

	gSDK->RedrawRect( fDrawArea );

    taggedObject.SetParamReal(tagPointIdx, tagPoint.x);
    taggedObject.SetParamReal(tagPointIdx+1, tagPoint.y);
    taggedObject.SetParamReal(shoulderPointIdx, shoulderPoint.x);
    taggedObject.SetParamReal(shoulderPointIdx+1, shoulderPoint.y);
    taggedObject.SetParamReal(endPointIdx, endPoint.x);
    taggedObject.SetParamReal(endPointIdx+1, endPoint.y);
    taggedObject.SetParamReal(approachAngleIdx, GetAngle(endPoint, shoulderPoint));
    taggedObject.SetParamReal(shoulderAngleIdx, GetAngle(shoulderPoint, tagPoint));
}

void VWTaggedObj::OnControlPointSelected(EPointID movedPointID)
{
    ASSERTN(kBAtwood, objectHandle != nil);

    WorldPt snapStartPoint;
    VWParametricObj taggedObject(objectHandle);

    switch(movedPointID) {
        case kTagPoint:
			snapStartPoint = GetTagControlPoint(kShoulderPoint);
            break;
        case kShoulderPoint:
            snapStartPoint = GetTagControlPoint(kEndPoint);
            break;
        case kEndPoint:
			snapStartPoint = GetTagControlPoint(kShoulderPoint);
            break;
            
    }

    VWTransformMatrix matrix;
    taggedObject.GetObjectMatrix(matrix);
    snapStartPoint = matrix.PointTransform(snapStartPoint);
	fDrawArea	   = WorldRect( GetTagControlPoint(kTagPoint), snapStartPoint );

    GS_SetProgramVariable(gCBP, varSmartCursorStartPt2DEx, &snapStartPoint);
}

void VWTaggedObj::UpdateTagOrentation()
{
	if ( fIsWorldOrientationUsed )
	{
		ETagOrientation		orientation			= this->GetTagOrientation();
		WorldPt				tagPoint			= this->GetTagControlPoint( kTagPoint );
		WorldPt				shoulderPoint		= this->GetTagControlPoint( kShoulderPoint );
		WorldPt				endPoint			= this->GetTagControlPoint( kEndPoint );

		VWParametricObj		taggedObject( objectHandle );
		VWTransformMatrix	matrix;
		taggedObject.GetObjectMatrix( matrix );
		WorldPt				orgTagPoint			= matrix.PointTransform( tagPoint );;
		WorldPt				orgShoulderPoint	= matrix.PointTransform( shoulderPoint );
		if ( ( orientation == kTagRight && orgTagPoint.x < orgShoulderPoint.x ) || ( orientation == kTagLeft && orgTagPoint.x > orgShoulderPoint.x ) )
		{
			if ( orientation != kTagFloating )
			{
				tagPoint.x += 2 * ( shoulderPoint.x - tagPoint.x );
				taggedObject.SetParamReal( tagPointIdx, tagPoint.x );
			}

			double newShoulderAng	= this->GetAngle( shoulderPoint, tagPoint );
			newShoulderAng			= fmod( newShoulderAng, 360.0 );
			if ( newShoulderAng < 0 )
			{
				newShoulderAng += 360.0;
			}
			taggedObject.SetParamReal( shoulderAngleIdx, newShoulderAng );

			double newApproachAng	= this->GetAngle( endPoint, shoulderPoint );
			if ( newApproachAng < 0 )
			{
				newApproachAng += 360.0;
			}
			taggedObject.SetParamReal( approachAngleIdx, newApproachAng );
		}
	}
}

double VWTaggedObj::GetAngle(WorldPt a, WorldPt b)
{
    double angle = b.DegreeAngleFrom(a);
    
    // Force tiny angles to be zero.
    if(DoubleIsNearlyZero(angle)) {
        angle = 0.0;
    }
    return(angle);
}

// Returns if it is a floating tag.
bool VWTaggedObj::IsFloatingTag()
{
	return	( ( ! useShoulder ) || ( this->GetTagOrientation() == kTagFloating ) );
}

void VWTaggedObj::DrawLeaderLine(InternalIndex classID, MCObjectHandle& leaderLine, MCObjectHandle& shoulderLine)
{
    //MCObjectHandle leaderLine;

    WorldPt tagPoint = GetTagControlPoint(kTagPoint);
    WorldPt shoulderPoint = GetTagControlPoint(kShoulderPoint);
    WorldPt endPoint = GetTagControlPoint(kEndPoint);

    if(useShoulder) {
        //Create the shoulder line
        shoulderLine = GS_CreateLine(gCBP, tagPoint, shoulderPoint);
        
        //Set the leader line properties
        if (shoulderLine != nil && classID > 0 ) {
	        GS_SetObjectClass(gCBP, shoulderLine, classID);

			VWClass	theClass( classID );
			if ( theClass.GetUseGraphics() )
			{
				GS_SetFColorsByClass(gCBP, shoulderLine);
				GS_SetFPatByClass(gCBP, shoulderLine);
				GS_SetLWByClass(gCBP, shoulderLine);
				GS_SetPColorsByClass(gCBP, shoulderLine);
				GS_SetPPatByClass(gCBP, shoulderLine);
			}
        }
    }

    //Create the approach line
    leaderLine = GS_CreateLine(gCBP, shoulderPoint, endPoint);

    //Set the leader line properties
    SMarkerStyle mstyle;
    GS_GetClassEndMarker(gCBP, classID, mstyle);
    if (leaderLine != nil ) {
		if ( classID > 0 ) {
			GS_SetObjectClass(gCBP, leaderLine, classID);
			gSDK->SetObjEndMarker( leaderLine, mstyle, useMarker );
			VWClass	theClass( classID );
			if ( theClass.GetUseGraphics() )
			{
				GS_SetFColorsByClass(gCBP, leaderLine);
				GS_SetFPatByClass(gCBP, leaderLine);
				GS_SetLWByClass(gCBP, leaderLine);
				GS_SetPColorsByClass(gCBP, leaderLine);
				GS_SetPPatByClass(gCBP, leaderLine);
				gSDK->SetArrowByClass( leaderLine );
			}
		}
    }
}

VWTaggedObj::ETagOrientation VWTaggedObj::GetTagOrientation()
{
    VWParametricObj taggedObject(objectHandle);
    TXString text = taggedObject.GetParamString(orientationIdx);

    for(Sint32 i=0; i<= kTagOrientationMax; i++) {
        if(text == TagOrientationStrings[i]) {
            return((ETagOrientation)i);
        }
    }
    return(kTagNone);
}

void VWTaggedObj::SetTagOrientation(ETagOrientation orientation)
{
    VWParametricObj taggedObject(objectHandle);
    VERIFYN(kBAtwood, orientation <= kTagOrientationMax && orientation >= (ETagOrientation)0);
    taggedObject.SetParamString(orientationIdx, TagOrientationStrings[(Sint32)orientation]); 
}

WorldPt VWTaggedObj::GetPointWithChangedLengthOnly(WorldPt startPt, WorldPt endPt, WorldPt currentToolPt)
{
	WorldPt shoulderVector;
	double	currLength;
	double	shoulderLenght;

	shoulderVector	= startPt - endPt;
	currLength		= (endPt - currentToolPt).Magnitude();
	shoulderLenght	= shoulderVector.Magnitude();
	shoulderVector	*= (currLength / shoulderLenght);

	return (endPt + shoulderVector); // new point
}

WorldPt VWTaggedObj::GetTagPotAtNinetyDegIfOrientationChanged(WorldPt currentToolPt)
{
	VWParametricObj taggedObject(objectHandle);

	VWTransformMatrix matrix;
	taggedObject.GetObjectMatrix(matrix);

	VWPoint2D shoulerPtLocalCord	= this->GetTagControlPoint(kShoulderPoint);
	VWPoint2D movedPtLocalCord		= matrix.InversePointTransform(currentToolPt);
	bool isOldOrientationLeft		= this->GetTagOrientation() == ETagOrientation::kTagLeft;
	double newAngle					= (movedPtLocalCord - shoulerPtLocalCord ).CalcAng360();
	bool isNewOrentationLeft		= (newAngle > 90 && newAngle < 270);

	if (isOldOrientationLeft != isNewOrentationLeft)
	{
		double difAngle				= newAngle > 180 ? -90 : 90;
		double currLength			= movedPtLocalCord.DistanceTo(shoulerPtLocalCord);

		VWPoint2D pt2D(1, 0);
		pt2D.SetPointByAngle(difAngle, currLength);

		pt2D						+= shoulerPtLocalCord;
		currentToolPt				= matrix.PointTransform(pt2D);
	}

	return currentToolPt;
}

double VWTaggedObj::GetShoulderAngleFromStyleIfNeeded(double currentShoulderAngle, double shoulderAngleFromStyle)
{
	ETagOrientation tagOrientation = this->GetTagOrientation();
	bool isLeftAngle = (currentShoulderAngle > 90.0 && currentShoulderAngle < 270);

	if (	fIsTagOrientationConstrained
		&&	(	(tagOrientation == ETagOrientation::kTagLeft && !isLeftAngle)
			||	(tagOrientation == ETagOrientation::kTagRight && isLeftAngle)))
	{		
		currentShoulderAngle = shoulderAngleFromStyle;
	}

	return currentShoulderAngle;
}
