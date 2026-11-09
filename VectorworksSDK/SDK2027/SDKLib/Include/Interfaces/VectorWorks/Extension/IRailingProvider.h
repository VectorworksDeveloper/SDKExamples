//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once


namespace VectorWorks
{
	namespace Extension
	{
	
		struct SZValue {
			size_t fIndex = (size_t)(-1); // 0-based index of vertex in fPoly. We can not provide Z values for all vertices as some vertices might be non-corner vertices.
			double fZ = 0.0;  // zValue at "fPoly.vertex[iIndex]"
		};
	
		// Each Railing Segment represents a part of the railing path where the PIO path
		// either maintains the same Z level or increases/decreases by an (approximately) constant rate.
		struct SRailingSegment
		{
			struct SStepLine
			{
				enum class EType { Tread, Riser };
				VWFC::Math::VWLine3D	fLine;
				EType					fType;
			};

			VWFC::Math::VWPolygon2D	fPoly;				// 2D Polygon containing the 2D vertices of the segment.
	
			double				fZAtStart	= 0.0;		// Z-Value of step / landing at begin of segment. This is the z level where the feet are placed upon.
			double				fZAtEnd		= 0.0;		// Z-Value of step / landing at end of segment (should be equal to fZAtStart for landings)
	
			bool				fIsIgnored	= false;	// Don't create railing in this segment
			
			std::vector<SZValue> fAdditionalZValues;	// Optional: Additional Z values at some vertices of fPoly.
			
			std::vector<SStepLine> fStepLines;			// A list of 3D lines that will be used by associated railings to position posts
														// more precisely and draw infill that follows the steps of a stair. The line ends
														// are expected to project onto the fPoly. The lines describe a (potentially
														// non-continuous) 3D polygon that goes along the treads and risers of a stair.
														// The polygon should go along the same direction as the fPoly. The lines should be
														// provided in the same direction as the fPoly and be in local coords.
		};
		typedef std::vector<SRailingSegment> TRailingSegmentsArray;

		// Railing Path defines a path from beginning to end of the PIO where a railing should be placed upon.
		// For instance, the left railing path of a stair with one landing will contain three segments:
		// one before the landing, one along the landing and one after the landing.
		struct SRailingPath
		{
			enum class EOrientation
			{
				General,
				Left,
				Right,
			};			
	
			TRailingSegmentsArray	fSegments;			// Segments should be ordered from beginnng to end of path
			EOrientation			fOrientation = EOrientation::General;
		};
		typedef std::vector<SRailingPath> TRailingPathsArray;

		enum class ERailingBreakType
		{
			Plain,
			Dashed,
			DashedBelow,
			DashedAbove,
			Solid,
			BelowOnly,
			DashedBelowOnly,
			AboveOnly,
			DashedAboveOnly,
		};

		struct SRailingBreak2D
		{
			// Whether to draw a 2D break. The other members are valid only if this is set to true.
			bool					fIsEnabled				= false;
			// Controls the break lines and which set of attributes will be used for the top/bottom graphic on the bottom floor.
			ERailingBreakType		fBottomBreakType		= ERailingBreakType::Plain;
			// Controls the break lines and which set of attributes will be used for the top/bottom graphic on the top floor.
			ERailingBreakType		fTopBreakType			= ERailingBreakType::Plain;
			// The layer onto which the railing should draw its top graphic. A top graphic will not be created if this is left at 0.
			InternalIndex			fTopLayer				= 0;
			// Controls whether the railing should draw the break line at the bottom floor. Ignored if the chosen break type has no bottom line.
			bool					fDrawBottomBreakLine	= true;
			// Controls whether the railing should draw the break line at the top floor. Ignored if the chosen break type has no top line.
			bool					fDrawTopBreakLine		= true;
			// The 2D coordinates of the center of the break in the local coordinate system.
			VWFC::Math::VWPoint2D	fCenterPt;
			// A vector representing the object direction at fCenterPt in the local coordinate system.
			VWFC::Math::VWPoint2D	fPathDir;
			// The break angle in degrees rotating CCW. 0 degrees means perpendicular to fPathDir.
			double					fAngle					= 0.0;
			// The distance between the two break lines.
			double					fGapWidth				= 0.0;
			// The length of the break line extensions. Measured perpendicular to fPathDir, instead of along the angled break line.
			double					fLeftExtension			= 0.0;
			double					fRightExtension			= 0.0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {54DD46CB-99D3-4AF8-9DE6-5F4B2D166C9A}
		static const Extension::TSinkIID IID_RailingProvider = { 0x54dd46cb, 0x99d3, 0x4af8, { 0x9d, 0xe6, 0x5f, 0x4b, 0x2d, 0x16, 0x6c, 0x9a } };

		class DYNAMIC_ATTRIBUTE IRailingProvider : public Extension::IEventSink
		{
		public:
			// Some complex objects may have more than a left and a right railing
			// The paths should be in the local coordinate system.
			virtual VCOMError		VCOM_CALLTYPE GetRailingPaths(MCObjectHandle hObject, TRailingPathsArray& outPathsArray) = 0;

			// Return true here to allow railings to associate to this object.
			// Associated railings will track the paths returned by GetRailingPaths and will attempt to react to any changes.
			virtual bool			VCOM_CALLTYPE AllowsRailingAssociation(MCObjectHandle hObject) { return false; }

			// If this object supports a 2D break, it can implement this function to inform any associated railings about what
			// break settings should be applied to them.
			virtual SRailingBreak2D	VCOM_CALLTYPE GetBreak2D(MCObjectHandle hObject) { return SRailingBreak2D {}; }
		};
	}
}
