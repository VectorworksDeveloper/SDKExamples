//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
    namespace Tools
    {
        // This class supplements VWParametricObj and adds support for a tag label component.
        // Users should derive from this class, call InitTag during initialization, and
        // implement DrawTagBody to display the tag data.  A call to DrawTag will draw the
        // leader line and call back to DrawTagBody with the correct parameters.
        class VWTaggedObj
        {
        public:

			VWTaggedObj();
			virtual ~VWTaggedObj();

            // Internal ID numbers for the control points
            enum EPointID {
                kTagPoint = 1,
                kShoulderPoint= 2,
                kEndPoint = 3
            };

            // Enumeration for the orientation options for the tag.
            enum ETagOrientation {
                kTagNone = 0,           // Do not draw the tag
                kTagLeft = 1,           // The shoulder should always be facing left
                kTagRight = 2,          // The shoulder should always be facing right
                kTagFloating = 3,
                kTagOrientationMax = 3
            };

            static const char*	TagOrientationStrings[];

            // Call this function to initialize the tag on your parametric object.
            void InitTag(   const MCObjectHandle taggedObjectPtr,
                            short tagControlPointIdx, 
                            short shoulderControlPointIdx, 
                            short endControlPointIdx,
                            short approachLineAngleIdx,
                            short shoulderLineAngleIdx,
                            short tagOrientationIdx,
                            bool useEndMarker,
                            bool useLeaderLineShoulder,
							bool isWorldOrientationUsed = false,
							bool isUpdatingSkipped = false,
							bool isChangeTagLengthOnly = false,
							bool isChangeShoulderLengthOnly = false,
							bool isTagOrientationConstrained = false,
							double shoulderAngleFromStyle = 0.0,
							bool isMoveEntireTagFromEndPt = false);

            // Returns the coordinates of the specified control point
            WorldPt GetTagControlPoint(EPointID controlPointID);
    
            // Call this function to draw the tag.  Will call DrawTagBody after the leader line.
            void DrawTag(InternalIndex classID);

            // Call this function to draw the leader line in interactive mode, such as while a
            // control point is being dragged.
            void DrawTagInteractive(EPointID movedPointID, VWPoint2D *cursorOffset = nil);


            // Call this function when a control point has been moved by the user.
            void OnMoveTagControlPoint(EPointID movedPointID, VWPoint2D *cursorOffset = nil);

            void OnControlPointSelected(EPointID movedPointID);

			// Call this function when the tag orentation is changed. This function shud be call if the World Orientation is used.
			void UpdateTagOrentation();

            // Abstract function to be defined by the inheriting class
            // This function should draw the tag body and data with the given parameters.
            virtual void DrawTagBody(VWPoint2D point, double rotation, bool isRightOriented, MCObjectHandle leaderLine = NULL, MCObjectHandle shoulderLine = NULL) = 0;

        protected:

            // Returns the absolute angle of the shoulder line.
            double GetAngle(WorldPt a, WorldPt b);

			// Returns if it is a floating tag.
			bool	IsFloatingTag();

        private:

            //Returns the orientation of the tag.
            ETagOrientation GetTagOrientation();

            //Sets the orientation of the tag
            void SetTagOrientation(ETagOrientation orientation);

            //Draws just the leader line.
            void DrawLeaderLine(InternalIndex classID, MCObjectHandle& leaderLine, MCObjectHandle& shoulderLine);

			// Return point with changed length only
			WorldPt GetPointWithChangedLengthOnly(WorldPt startPt, WorldPt endPt, WorldPt currentToolPt);

			// Return Tag pt at positon 90 or -90 degrees if tag position is changed
			WorldPt GetTagPotAtNinetyDegIfOrientationChanged(WorldPt currentToolPt);

			// Return Shoulder angle from style if Tag orientation is incorrect
			double GetShoulderAngleFromStyleIfNeeded(double currentShoulderAngle, double shoulderAngleFromStyle);

            short tagPointIdx;
            short shoulderPointIdx;
            short endPointIdx;
            short approachAngleIdx;
            short shoulderAngleIdx;
            short orientationIdx;
			WorldRect fDrawArea;

            bool useMarker;
            bool useShoulder;
            MCObjectHandle objectHandle;

			bool fIsWorldOrientationUsed;
			bool fIsChangeTagLengthOnly;
			bool fIsChangeShoulderLengthOnly;
			bool fIsTagOrientationConstrained;
			bool fIsMoveEntireTagFromEndPt;
        };
    }
}
