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
			VWFC::Math::VWPolygon2D	fPoly;				// 2D Polygon containing the 2D vertices of the segment.
	
			double				fZAtStart	= 0.0;		// Z-Value of step / landing at begin of segment. This is the z level where the feet are placed upon.
			double				fZAtEnd		= 0.0;		// Z-Value of step / landing at end of segment (should be equal to fZAtStart for landings)
	
			bool				fIsIgnored	= false;	// Don't create railing in this segment
			
			std::vector<SZValue> fAdditionalZValues; // Optional: Additional Z values at some vertices of fPoly.
			
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

		// ----------------------------------------------------------------------------------------------------
		// {54DD46CB-99D3-4AF8-9DE6-5F4B2D166C9A}
		static const Extension::TSinkIID IID_RailingProvider = { 0x54dd46cb, 0x99d3, 0x4af8, { 0x9d, 0xe6, 0x5f, 0x4b, 0x2d, 0x16, 0x6c, 0x9a } };

		class DYNAMIC_ATTRIBUTE IRailingProvider : public Extension::IEventSink
		{
		public:
			// Some complex objects may have more than a left and a right railing
			// The paths should be in the local coordinate system.
			virtual VCOMError	VCOM_CALLTYPE GetRailingPaths(MCObjectHandle hObject, TRailingPathsArray& outPathsArray) = 0;
		};
	}
}
