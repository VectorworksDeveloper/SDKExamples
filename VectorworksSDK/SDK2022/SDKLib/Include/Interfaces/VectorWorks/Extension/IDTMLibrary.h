//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IDTMSettings.h"
#include "IDTMTIN.h"
#include "IDTMModifiersProvider.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {918290F7-CD4F-448d-932E-31AF500FEB0A}
		static const VWGroupID GROUPID_DTMSupport = { 0x918290f7, 0xcd4f, 0x448d, { 0x93, 0x2e, 0x31, 0xaf, 0x50, 0xf, 0xeb, 0xa } };
		// ---------------------------------------------------------------------------
		// {1C3A2856-EDC2-4cdb-BDFF-417CECF6B365}
		static const VWIID IID_DTMLibrary = { 0x1c3a2856, 0xedc2, 0x4cdb, { 0xbd, 0xff, 0x41, 0x7c, 0xec, 0xf6, 0xb3, 0x65 } };

		// ---------------------------------------------------------------------------
		enum class EDTMContextEdit
		{
			  ExistingGeometry
			, ExistingContours
			, ProposedGeometry
			, ProposedContours
			, RecreateFromSource
			, Crop
			, Components
			, GeologicalSurveyPoints
		};

		// ---------------------------------------------------------------------------
		enum class ESiteModelContourPolyState
		{
			  NotChanged
			, NewCreated
			, Modified
			, Deleted
			, OnlyLabelsDeleted
		};

		enum class EEntityType
		{
			MainByComponent,
			BorderByComponent,
			MainComposite,
			BorderComposite,
		};

		struct SEntityQuantityData
		{
			MCObjectHandle	fhComponentNode	= nullptr;
			size_t			fComponentID	= 0;

			TMCObjectHandlesSTLArray	fMeshes;

			double	fPerimeter				= 0.0;
			double	fGrossSurfaceArea		= 0.0;
			double	fNetSurfaceArea			= 0.0;
			double	fGrossProjectedArea		= 0.0;
			double	fNetProjectedArea		= 0.0;
			double	fGrossVolume			= 0.0;
			double	fNetVolume				= 0.0;
		};

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IDTMLibrary : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE EnsureUniqueName(MCObjectHandle hDrawingHdr, TXString& inOutName, MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE GetSettings(MCObjectHandle hDTMObj, const VWIID& iid, IDTMSettings** ppSettings) = 0;
			virtual VCOMError VCOM_CALLTYPE GetTIN(MCObjectHandle hDTMObj, ETINType type, const VWIID& iid, IDTMTIN** ppTIN) = 0;

			virtual VCOMError VCOM_CALLTYPE FindDTMObjectAtXY(MCObjectHandle hLayer, double x, double y, MCObjectHandle& hOutDTMObj) = 0;
			virtual VCOMError VCOM_CALLTYPE IsObjectReady(MCObjectHandle hDTMObj, bool& bIsObjectReadyToUse) = 0;
			virtual VCOMError VCOM_CALLTYPE GetZatXY(MCObjectHandle hDTMObj, const WorldCoord inX, const WorldCoord inY, WorldCoord& outZ) = 0;

			// vw2011
			virtual VCOMError VCOM_CALLTYPE	FindDTMObject(VectorWorks::Math::IPolyDef* polygon, MCObjectHandle& hOutDTMObj) = 0;
			virtual VCOMError VCOM_CALLTYPE	RisePolygon(MCObjectHandle hDTMObj, ETINType tinType, VectorWorks::Math::IPolyDef* polygon3D) = 0;
			virtual VCOMError VCOM_CALLTYPE	RisePolygon(MCObjectHandle hDTMObj, VectorWorks::Math::IPolyDef* polygon3D) = 0;
			virtual VCOMError VCOM_CALLTYPE	RisePolygon(ETINType tinType, VectorWorks::Math::IPolyDef* polygon3D) = 0;
			virtual VCOMError VCOM_CALLTYPE	RisePolygon(VectorWorks::Math::IPolyDef* polygon3D) = 0;


			virtual VCOMError VCOM_CALLTYPE	ClearModelCache(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE ClearModifiers(const VWGroupID& groupID) = 0;
			virtual VCOMError VCOM_CALLTYPE AddModifierBoundary(const VWGroupID& groupID, VectorWorks::Math::IPolyDef* polygon2D) = 0;
			virtual VCOMError VCOM_CALLTYPE AddModifierPad(const VWGroupID& groupID, ETINType applyTo, VectorWorks::Math::IPolyDef* polygon3D) = 0;
			virtual VCOMError VCOM_CALLTYPE AddModifierGrader(const VWGroupID& groupID, ETINType applyTo, WorldCoord dRise, VectorWorks::Math::IPolyDef* polygon2D) = 0;
			virtual VCOMError VCOM_CALLTYPE AddModifierTextureBed(const VWGroupID& groupID, ETINType applyTo, WorldCoord dRise, InternalIndex textureIndex, VectorWorks::Math::IPolyDef* polygon2D) = 0;

			// vw2012
			virtual VCOMError VCOM_CALLTYPE FindDTMObjectAtXYInDocument(MCObjectHandle hLayer, bool searchDocument, double x, double y, MCObjectHandle& hOutDTMObj) = 0;

			// vw2016
			virtual VCOMError VCOM_CALLTYPE FindDTMObject(MCObjectHandle hLayer, MCObjectHandle& hOutDTMObj) = 0;

			// vw2018
			virtual void	VCOM_CALLTYPE PrepareSiteModelEditContext(MCObjectHandle hObj, EDTMContextEdit mode) = 0;
			virtual void	VCOM_CALLTYPE SetSiteModelContourPolyElevation(MCObjectHandle hObj, double elev) = 0;
			virtual bool	VCOM_CALLTYPE GetSiteModelContourPolyElevation(MCObjectHandle hObj, double& outElev) = 0;
			virtual void	VCOM_CALLTYPE SetSiteModelContourPolyState(MCObjectHandle hObj, ESiteModelContourPolyState state) = 0;
			virtual bool	VCOM_CALLTYPE GetSiteModelContourPolyState(MCObjectHandle hObj, ESiteModelContourPolyState& outState) = 0;
			virtual bool	VCOM_CALLTYPE IsAtEditContoursMode() = 0;
			virtual void	VCOM_CALLTYPE SimplifySiteModelContour(MCObjectHandle hObj, double tolerance) = 0;

			// vw2019
			virtual bool	VCOM_CALLTYPE IsAtEditGeometryMode() = 0;
			virtual bool	VCOM_CALLTYPE GetGeometryModeSnappedTINEdge(double snapTolerance, WorldPt3& snapPt, WorldPt3& snapEdgeBeginPt, WorldPt3& snapEdgeEndPt) = 0;

			// vw2021
			virtual VCOMError VCOM_CALLTYPE GetElevationsForSetOfPositions( MCObjectHandle hDTMObj, std::vector<WorldPt>& inPoints, std::vector<double>& outZArray ) = 0;
			virtual VCOMError VCOM_CALLTYPE	FindDTMObjectInLayer(VectorWorks::Math::IPolyDef* polygon, MCObjectHandle hLayer, MCObjectHandle& hOutDTMObj) = 0;
			virtual void	  VCOM_CALLTYPE EnterSurveyPointSpecialGroup(MCObjectHandle hObj) = 0;
			virtual bool	  VCOM_CALLTYPE IsAtEditSurveyPointsMode() = 0;

			// vw2022
			virtual void		VCOM_CALLTYPE GetHardscapeMeshesQuantityInfo(MCObjectHandle hObject, EEntityType entityType, std::vector<SEntityQuantityData> &outQuantityDataContainer) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IDTMLibrary>	IDTMLibraryPtr;
	}
}