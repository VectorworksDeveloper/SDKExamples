//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#if _MINICAD_
#else
#include "VWFC/PluginSupport/VWExtensions.h"
#endif

namespace VWFC
{
	namespace PluginSupport
	{

		// ------------------------------------------------------------------------------------------------------------------
		class CDrawProvider : public VWFC::PluginSupport::IToolDrawProvider
		{
		public:
								CDrawProvider();

		public:
			// default drawing
			virtual void		DrawDefaultRect() const;
			virtual void		DrawDefault2D() const;
			virtual void		DrawDefault3D() const;

			// simple drawing
			virtual void		DrawLine2D(const VWLine2D& line) const;
			virtual void		DrawLine3D(const VWLine3D& line) const;
			virtual void		DrawRect(const VWRectangle2D& rect) const;
			virtual void		DrawArc(const VWArc2D& arc) const;
			virtual void		DrawEllipse(const VWRectangle2D& rect) const;

			// poly drawing
			virtual void		DrawPolyBegin();
			virtual void		DrawPoly_AddCornerVertex(const VWPoint2D& pt);
			virtual void		DrawPoly_AddBezierVertex(const VWPoint2D& pt);
			virtual void		DrawPoly_AddCubicVertex(const VWPoint2D& pt);
			virtual void		DrawPoly_AddArcVertex(const VWPoint2D& pt, double dRadius);
			virtual void		DrawPolyEnd();
			virtual void		DrawPolyEnd(const VWTransformMatrix& matrix);

			// object drawing
			virtual void		DrawObject(MCObjectHandle hObj, bool bDoSelect) const;
			virtual void		DrawNurbsObject(MCObjectHandle hNurbsObj) const;
			virtual void		DrawDataDisplayBar(bool bDrawFramesFirst = false) const;

			// attributes
			virtual void		SetPenSize(short penSize=0) const;
			virtual void		SetPenPattern(short penPatIndex = 2) const;

		protected:
			struct SPolyVertex {
				Sint32				fType;
				Sint32				fTypeOriginal;
				VWPoint2D		fPt;
				VWPoint2D		fControlPt;
				double			fdRadius;
			};

			typedef std::vector<SPolyVertex>		TPointsArray;

		protected:
			void				RenderPolyline(TPointsArray& arrVertices);
			void				DisplaySplineSubSection(const VWPoint2D &v1, const VWPoint2D &v2, const VWPoint2D &v3, short level );
			void				CalculatePolyline(TPointsArray& arrVertices);
			void				SwapControlPts(TPointsArray& arrVertices);
			void				DrawPolyVert(const SPolyVertex& lastVert, const SPolyVertex& thisVert, const SPolyVertex& nextVert );
			void				DisplayArc(const VWPoint2D& lastPt, const VWPoint2D& thisPt, const VWPoint2D& nextPt, double radius);
			bool				CalcChamfer(const VWPoint2D& pt1, const VWPoint2D& int0Value, const VWPoint2D& pt4, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double& radius, double &lastAngle, double &thisAngle);
			void				InterLoc(const VWPoint2D& a1, const VWPoint2D& a2, const VWPoint2D& b1, const VWPoint2D& b2, bool& intersect, bool& parallel, VWPoint2D& int0);
			void				DisplayArc(const VWPoint2D &lastPt, const VWPoint2D &/*thisPt*/, const VWPoint2D &nextPt, double radius, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double myStart, double myArc);
			void				SegmentArc(double inMyStart, double inMyArc, const VWPoint2D& cen, double radius );
			void				RenderArc(double arcStart, double arcEnd, short currentLevel, const VWPoint2D& cen, double radius);
			VWPoint2D			NextLoc(double a, const VWPoint2D& cen, double radius);

			void				PolyRenderDrawLine(const VWLine2D& line) const;

		protected:
			TPointsArray		farrPoints;

			// current point while rendering polyline
			VWPoint2D			fCurrPolyPt;

			bool				fbPoly3DRender;
			VWTransformMatrix	fPoly3DMatrix;
		};

		// ------------------------------------------------------------------------------------------------------------------
		class CStatusProvider : public VWFC::PluginSupport::IToolStatusProvider
		{
		public:
			virtual	VWFC::PluginSupport::TToolStatus		GetOnePointToolStatus() const;
			virtual VWFC::PluginSupport::TToolStatus		GetTwoPointToolStatus() const;
			virtual VWFC::PluginSupport::TToolStatus		GetThreePointToolStatus() const;
			virtual VWFC::PluginSupport::TToolStatus		GetPolyToolStatus() const;
			virtual VWFC::PluginSupport::TToolStatus		GetClickDragToolStatus() const;
		};

		// ------------------------------------------------------------------------------------------------------------------
		class CModeBarProvider : public  VWFC::PluginSupport::IToolModeBarProvider
		{
		public:
			virtual void			EnableModeGroup(size_t modeGroupID, bool bEnable) const;
			virtual void			SetHelpString(const TXString& helpMessage) const;
			virtual void			SetHighlightedHelpString(const TXString& helpMessage) const;
			virtual Sint32			GetModeGroupValue(size_t modeGroupID) const;
			virtual void			SetModeGroupValue(size_t modeGroupID, Sint32 value) const;
			virtual void			InsertPullDownMenuItem(size_t modeGroupID, const TXString& text) const;
			virtual size_t			GetPullDownMenuSelection( size_t modeGroupID ) const;
			virtual void			SetPullDownMenuSelection(size_t modeGroupID, size_t selection) const;
			virtual void			SetPullDownResourceValue(size_t modeGroupID, const TXString& value);
			virtual Sint32			ShowPullDownResourcePopup(size_t modeGroupID, const SShowPullDownResourcePopup& data, const TXString& selectedName, ThumbnailSizeType thumbSize=kStandardSize);
			virtual Sint32			ShowPullDownResourcePopup(size_t modeGroupID, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize=kStandardSize);
			virtual bool			SetButtonsHelpText(const TXStringArray& arrHelpText) const;
			virtual void			ClearPullDownMenu(size_t modeGroupID) const;
			virtual void			SetEditTextValue(size_t modeGroupID, const TXString& value);
			virtual TXString		GetEditTextValue(size_t modeGroupID);
			virtual TXString		PullDownResourcePopupGetSelected(size_t modeGroupID);
			virtual void			PullDownResourcePopupSetSelected(size_t modeGroupID, const TXString& name);
			virtual bool			GetCheckGroupState( size_t modeGroupID ) const;
			virtual void			SetCheckGroupState( size_t modeGroupID, bool state ) const;
			virtual void            SetRadioModeGroupValue(size_t modeGroupID, Sint32 value, const TXStringArray& imageSpecs) const;
		};

		// ------------------------------------------------------------------------------------------------------------------
		class CModeBarInitProvider : public  VWFC::PluginSupport::IToolModeBarInitProvider
		{
		public:

			virtual void			AddButtonModeGroup(const TXString& imageSpec) const;
			virtual void			AddCheckModeGroup(const TXString& imageSpec, bool initState) const;
			virtual void			AddPullDownMenuModeGroup(const TXString& label) const;
			virtual void			AddRadioModeGroup(size_t initState, const TXStringArray& images) const;
			virtual void			AddPullDownResourceModeGroup(const TXString& label, const TXString& value) const;
			virtual void			AddTextButtonModeGroup(const TXString& text) const;
			virtual void			AddEditTextModeGroup(const TXString& label, const TXString& value) const;
			virtual void			AddEditTextModeGroup(const TXString& label, const TXString& value, Sint32 textWidth) const;
			virtual void			PullDownResourcePopupSet(size_t modeGroupID, VectorWorks::Extension::IResourceManagerContent*content) const;

		public:
			virtual void			EnableModeGroup(size_t modeGroupID, bool bEnable) const;
			virtual void			SetHelpString(const TXString& helpMessage) const;
			virtual void			SetHighlightedHelpString(const TXString& helpMessage) const;
			virtual Sint32			GetModeGroupValue(size_t modeGroupID) const;
			virtual void			SetModeGroupValue(size_t modeGroupID, Sint32 value) const;
			virtual void			InsertPullDownMenuItem(size_t modeGroupID, const TXString& text) const;
			virtual size_t			GetPullDownMenuSelection( size_t modeGroupID ) const;
			virtual void			SetPullDownMenuSelection(size_t modeGroupID, size_t selection) const;
			virtual void			SetPullDownResourceValue(size_t modeGroupID, const TXString& value);
			virtual Sint32			ShowPullDownResourcePopup(size_t modeGroupID, const SShowPullDownResourcePopup& data, const TXString& selectedName, ThumbnailSizeType thumbSize=kStandardSize);
			virtual Sint32			ShowPullDownResourcePopup(size_t modeGroupID, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize=kStandardSize);
			virtual bool			SetButtonsHelpText(const TXStringArray& arrHelpText) const;
			virtual void			ClearPullDownMenu(size_t modeGroupID) const;
			virtual void			SetEditTextValue(size_t modeGroupID, const TXString& value);
			virtual TXString		GetEditTextValue(size_t modeGroupID);
			virtual TXString		PullDownResourcePopupGetSelected(size_t modeGroupID);
			virtual void			PullDownResourcePopupSetSelected(size_t modeGroupID, const TXString& name);
			virtual bool			GetCheckGroupState( size_t modeGroupID ) const;
			virtual void			SetCheckGroupState( size_t modeGroupID, bool state ) const;
			virtual void            SetRadioModeGroupValue(size_t modeGroupID, Sint32 value, const TXStringArray& imageSpecs) const;
		};


		// ------------------------------------------------------------------------------------------------------------------
		class CToolPropertiesProvider : public VWFC::PluginSupport::IToolPropertiesProvider
		{
		public:
								CToolPropertiesProvider(Sint32 codeRefID);
			virtual bool		SetProperty(Sint32 propID, bool bValue);
			virtual bool		SetPropertyChar(Sint32 propID, char value);
			virtual Sint32		GetCodeRefID();
		private:
			Sint32 fCodeRefID;
		};

	}
}