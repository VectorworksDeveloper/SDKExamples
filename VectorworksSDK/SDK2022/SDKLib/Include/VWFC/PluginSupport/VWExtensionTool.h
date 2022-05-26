//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		using namespace VectorWorks::Extension;

		// ------------------------------------------------------------------------------------------------------
		class VWTool_EventSink	: public VCOMImpl<IToolEventSink>
		{
		public:
									VWTool_EventSink(IVWUnknown* parent);
			virtual					~VWTool_EventSink();

			Sint32					GetResult() const;
			void					SetResult(Sint32 result);

			void					SetUniversalName(const TXString& name);

		public:
			virtual	void			OnInitXProperties(IToolPropertiesProvider* pPropsProvider);

			virtual void			OnSelectionChange();
			virtual void			OnCustomBar_Setup();
			virtual void			OnCustomBar_Setdown();
			virtual void			OnCustomBar_UpdateValues();
			virtual void			OnCustomBar_LockValue(size_t fieldIndex, const TXString& userString);
			virtual void			OnCustomBar_UnlockValue(size_t fieldIndex);
			virtual void			OnCustomBar_LockValue(const CustomBarLockValueData& lockData);
			virtual void			OnCustomBar_UnlockValue(const CustomBarLockValueData& lockData);

			// When tool is selected or resumed
			virtual bool			DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider);
			// When tool is deselected	or paused
			virtual void			DoSetDown(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider);
			virtual void			DoDrawScrMod();
			virtual void			DoUndrawScrMod();

			// init the tool data for creation of the specified object
			virtual void			OnToolInitByObject(MCObjectHandle hObject, const IToolModeBarProvider* pModeBarInitProvider);

			// When tool selected and curs in doc
			virtual void			GetCursorSpecifier(TXString& cursorSpecifier);
			// When app needs tool's status
			virtual TToolStatus		GetStatus(const IToolStatusProvider* pStatusProvider);

			// When mouse is clicked in drawing
			virtual void			PointAdded();
			// When app removes a point
			virtual void			PointRemoved(bool bClearAllPts);
			// Whenever tool needs to draw
			virtual void			Draw(IToolDrawProvider* pDrawProvider);
			// When mouse moves in drawing
			virtual void			MouseMove();
			// When tool is done getting points
			virtual void			HandleComplete() = 0;

			// When mouse is clicked in mode bar
			virtual void			DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID);
			// When tool is double-clicked
			virtual void			DoDoubleClick();
			// When double-click in drawing
			virtual bool			DrawingDoubleClick();
			// After every key event.
			virtual void			GenericStateChange();

			// After view change 2D/3D
			virtual void			OnViewChange();

			// The default event notificaiotn
			// if no virutal is present for an event, this function is called to allow the user to catch everything
			virtual Sint32			OnDefaultEvent(ToolMessage* message);

		// tool points
		public:
			size_t					GetToolPointsCount() const;
			void					ClearAllToolPoints();
			VWPoint2D				GetToolPt2D(size_t ptIndex, bool includeCurrent=false) const; // includeCurrent=true then return current if ptIndex==GetToolPointsCount 
			VWPoint3D				GetToolPt3D(size_t ptIndex, bool includeCurrent=false) const;
			bool					GetToolPtCurren2D(VWPoint2D& outPt) const;
			bool					GetToolPtCurren3D(VWPoint3D& outPt) const;
			bool					PopLastToolPt();

		// hot spot points
		public:

			HotSpotRefID			HotSpotAdd(HotSpotType type, const VWPoint3D& pt, const TXString& cursorSpec);
			HotSpotRefID			HotSpotAdd(HotSpotType type, const VWPoint3D& pt, const TXString&, const TXString& strTip);

			HotSpotRefID			HotSpotAdd(HotSpotType type, const VWPoint3D& pt, Sint32 cursorID);
			HotSpotRefID			HotSpotAdd(HotSpotType type, const VWPoint3D& pt, Sint32 cursorID, const TXString& strTip);

			HotSpotRefID			HotSpotTrack(bool& bOutIs3D, VWPoint3D& outLocation);
			void					HotSpotRemove(HotSpotRefID hotSpotID);

			void					SetHotSpotColor(HotSpotRefID inHotSpotID, GSColor color);

		// snap geometry
		public:
			MCObjectHandleID		SnapGeometryAdd(MCObjectHandle hSnapGeometry);
			void					SnapGeometryRemove(MCObjectHandleID snapGeometryID);

		// help text
		public:
			void					SetModeBarHelpText(const TXString& helpText);

		// mode bar
		public:
			void					RefreshModeBar();

		// cursor highlight
		public:
			static void				DrawCrosshairHighlight(const WorldPt3& centerPt);

		protected:
			// callback to performe the update. return true if the mode bar changed
			virtual bool			OnRefreshModeBar(const IToolModeBarProvider* modeBarInitProvider);

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE	Execute(ToolMessage* message);

		protected:
			virtual void			Default();

		protected:
			IToolModeBarProvider*	fpModeBarProvider;
			ToolMessage*			fMessage;;
			Sint32					fResult;
			TXString				fUnivName;
			TXString				fCustomHelpText;
		};

		namespace ToolDef
		{
			enum EPickAndUpdate			{ disablePickUpdate, pickAndUpdate };
			enum ENeedScreenPlane		{ doesntNeedScreenPlane, needsScreenPlane };
			enum ENeed3DView			{ doesntNeed3DView, needs3DView };
			enum EUseCursor				{ use2DCursor, use3DCursor };
			enum EConstrantCursor		{ constrainCursor, screenBasedCursor };
			enum ENeedPerspective		{ doesntNeedPerspective, needsPerspective };
			enum EShowScreenHints		{ showScreenHints, dontShowScreenHints };
			enum ENeedsPlanarContext	{ needsPlanarContext, doesntNeedPlanarContext };
		}
		// ------------------------------------------------------------------------------------------------------
		struct SToolDef
		{
			EExtensionToolType				fToolType;
			const char*						fParametricName;	// use eExtensionToolType_Normal if you specify parametric name
																// the type will be determined by the type of the parametric
			ToolDef::EPickAndUpdate			fPickAndUpdate;
			ToolDef::ENeedScreenPlane		fNeedScreenPlane;
			ToolDef::ENeed3DView			fNeed3DView;
			ToolDef::EUseCursor				fUseCursor;
			ToolDef::EConstrantCursor		fConstrainCursor;
			ToolDef::ENeedPerspective		fNeedPerspective;
			ToolDef::EShowScreenHints		fShowScreenHints;
			ToolDef::ENeedsPlanarContext	fNeedsPlanarContext;

			SResString						fMessage;
			Sint16							fWaitMoveDistance;
			Sint16							fConstraintFlags;
			EToolBarDisplay					fBarDisplay;
			Sint16							fMinimumCompatibleVersion;
			SResString						fTitle;
			SResString						fCategory;
			SResString						fHelpText;
			Uint16							fVersionCreated;
			Uint16							fVersoinModified;
			Uint16							fVersoinRetired;
			const char*						fOverrideHelpID;
			const char*						fIconSpec;
			const char*						fCursorImageSpec;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SToolDef_Legacy
		{
			EExtensionToolType				fToolType;
			const char*						fParametricName;	// use eExtensionToolType_Normal if you specify parametric name
																// the type will be determined by the type of the parametric
			ToolDef::EPickAndUpdate			fPickAndUpdate;
			ToolDef::ENeedScreenPlane		fNeedScreenPlane;
			ToolDef::ENeed3DView			fNeed3DView;
			ToolDef::EUseCursor				fUseCursor;
			ToolDef::EConstrantCursor		fConstrainCursor;
			ToolDef::ENeedPerspective		fNeedPerspective;
			ToolDef::EShowScreenHints		fShowScreenHints;
			ToolDef::ENeedsPlanarContext	fNeedsPlanarContext;

			SSTRResource					fMessage;
			Sint16							fWaitMoveDistance;
			Sint16							fConstraintFlags;
			EToolBarDisplay					fBarDisplay;
			Sint16							fMinimumCompatibleVersion;
			SSTRResource					fTitle;
			SSTRResource					fCategory;
			STEXTResource					fHelpText;
			Uint16							fVersionCreated;
			Uint16							fVersoinModified;
			Uint16							fVersoinRetired;
			const char*						fOverrideHelpID;
			const char*						fIconSpec;
			const char*						fCursorImageSpec;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionTool   : public VCOMImmediateImpl<IExtensionTool>
		{
		public:
											VWExtensionTool(	CallBackPtr cbp,
																const SToolDef& toolDef);
											VWExtensionTool(	CallBackPtr cbp,
																const SToolDef_Legacy& toolDef);
			virtual							~VWExtensionTool();

		// IExtension
		public:
			virtual IEventSink* VCOM_CALLTYPE		QueryEventSink(const TSinkIID& iid);

		// IExtensionTool
		public:
			virtual EExtensionToolType				GetType();
			virtual const TXString& VCOM_CALLTYPE	GetTitle();
			virtual const TXString& VCOM_CALLTYPE	GetCategory();
			virtual const TXString& VCOM_CALLTYPE	GetHelpText();
			virtual const TXString& VCOM_CALLTYPE	GetMessageText();
			virtual const TXString& VCOM_CALLTYPE	GetOverrideHelpID();
			virtual const TXString&	VCOM_CALLTYPE	GetParametricName();
			virtual bool VCOM_CALLTYPE				GetPickAndUpdate();
			virtual bool VCOM_CALLTYPE				GetNeedScreenPlane();
			virtual bool VCOM_CALLTYPE				GetNeed3DProjection();
			virtual bool VCOM_CALLTYPE				GetUse2DCursor();
			virtual bool VCOM_CALLTYPE				GetConstrainCursor();
			virtual bool VCOM_CALLTYPE				GetNeedPerspective();
			virtual bool VCOM_CALLTYPE				GetShowScreenHints();
			virtual bool VCOM_CALLTYPE				GetNeedsPlanarContext();
			virtual void VCOM_CALLTYPE				GetIconSpec(TXString& outImageSpec);
			virtual void VCOM_CALLTYPE				GetDefaultCursorImageSpec(TXString& outImageSpec);
			virtual Sint16 VCOM_CALLTYPE			GetWaitMoveDistance();
			virtual Sint16 VCOM_CALLTYPE			GetConstraintFlags();
			virtual EToolBarDisplay VCOM_CALLTYPE	GetBarDisplay();
			virtual	Sint16 VCOM_CALLTYPE			GetMinimumCompatibleVersion();
			virtual	void VCOM_CALLTYPE				GetVersionInfo(Uint16& outCreated, Uint16& outModified, Uint16& outRetired);
			

		// these functions allow an extension implementation to override localized strings provided by the resources
		// use them in the construtor of the extension as the base constructor reads the resources
		protected:
			virtual void VCOM_CALLTYPE			SetLocalizedTitle( const TXString& localizedTitle );
			virtual void VCOM_CALLTYPE			SetLocalizedCategory( const TXString& localizedCategory );
			virtual void VCOM_CALLTYPE			SetLocalizedHelpText( const TXString& localizedHelpText );
			virtual void VCOM_CALLTYPE			SetLocalizedMessage( const TXString& localizedMessage );

		protected:
			virtual void						OnRefCountZero();
			virtual IToolEventSink*				CreateToolEventSink(IVWUnknown* parent) = 0;
			virtual bool						GetProtectionSinkIID(TSinkIID& outIID);
			virtual IProviderProtection*		CreateProtectionSink(IVWUnknown* parent);
			virtual bool						IsToolEventSink(const TSinkIID& iid);

		private:
			CallBackPtr						fCBP;

			EExtensionToolType				fToolType;
			ToolDef::EPickAndUpdate			fPickAndUpdate;
			ToolDef::ENeedScreenPlane		fNeedScreenPlane;
			ToolDef::ENeed3DView			fNeed3DView;
			ToolDef::EUseCursor				fUseCursor;
			ToolDef::EConstrantCursor		fConstrainCursor;
			ToolDef::ENeedPerspective		fNeedPerspective;
			ToolDef::EShowScreenHints		fShowScreenHints;
			ToolDef::ENeedsPlanarContext	fNeedsPlanarContext;
			Sint16							fWaitMoveDistance;
			Sint16							fConstraintFlags;
			EToolBarDisplay					fBarDisplay;
			Sint16							fMinimumCompatibleVersion;
			const char*						fIconSpec;
			const char*						fCursorImageSpec;
			Uint16							fVersionCreated;
			Uint16							fVersoinModified;
			Uint16							fVersoinRetired;

			TXString						fstrTitle;
			TXString						fstrCategory;
			TXString						fstrHelp;
			TXString						fstrMessage;
			TXString						fstrOverrideHelpID;
			TXString						fstrParametricName;

			IToolEventSink*					fToolEventSink;
			bool							fProtectionObtained;
			bool							fHasProtection;
			TSinkIID						fProtectionSinkIID;
			IProviderProtection*			fProtectionSink;
		};

		// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------
		// Specific purpose event sinks implementations


		// ------------------------------------------------------------------------------------------------------
		class VWToolEmpty_EventSink	: public VCOMImpl<IToolEventSink>
		{
		public:
									VWToolEmpty_EventSink(IVWUnknown* parent);
			virtual					~VWToolEmpty_EventSink();

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);
		};

		// ------------------------------------------------------------------------------------------------------
		class VWToolDefault_EventSink	: public VWTool_EventSink
		{
		public:
									VWToolDefault_EventSink(IVWUnknown* parent, const TXString& objectName);
			virtual					~VWToolDefault_EventSink();

			void					UpdatePreview();

			MCObjectHandle			GetLastCreated();

		public:
			// override to modify the fToolInfo. Set 'fUseToolInfo' to true of the info is valid
			virtual void			Init(const TXString& universalName);

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);

		// VWTool_EventSink
		public:
			virtual void			Draw(IToolDrawProvider* pDrawProvider);
			virtual void			HandleComplete();

		protected:
			virtual void			Default();

		protected:
			TXString				fObjectName;
			EDefaultToolType		fToolType;
			bool					fIsStandardTool;
			std::shared_ptr<void>	fDataContext;

			struct SActionData
			{
				ToolMessage*		fMessage;
				MCObjectHandle		fhLastCreated;
			};

			typedef std::vector<SActionData>	TActionDataArray;
			TActionDataArray		fLastActions;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWToolDefaultPoint_EventSink	: public VWToolDefault_EventSink
		{
		public:
									VWToolDefaultPoint_EventSink(IVWUnknown* parent, const TXString& objectName);
			virtual					~VWToolDefaultPoint_EventSink();

		public:
			// override to modify the fToolInfo. Set 'fUseToolInfo' to true of the info is valid
			virtual void					Init(const TXString& universalName);
			const SDefaultPointToolInfo&	GetToolInfo() const;
			void							SetToolInfo(const SDefaultPointToolInfo& info);

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);

		private:
			SDefaultPointToolInfo	fToolInfo;
			SDefaultPointToolInfo	fVWToolInfo;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWToolDefaultLine_EventSink	: public VWToolDefault_EventSink
		{
		public:
									VWToolDefaultLine_EventSink(IVWUnknown* parent, const TXString& objectName);
			virtual					~VWToolDefaultLine_EventSink();

		public:
			// override to modify the fToolInfo. Set 'fUseToolInfo' to true of the info is valid
			virtual void				Init(const TXString& universalName);
			const SDefaultLineToolInfo&	GetToolInfo() const;
			void						SetToolInfo(const SDefaultLineToolInfo& info);

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);

		private:
			SDefaultLineToolInfo	fToolInfo;
			SDefaultLineToolInfo	fVWToolInfo;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWToolDefaultRect_EventSink	: public VWToolDefault_EventSink
		{
		public:
									VWToolDefaultRect_EventSink(IVWUnknown* parent, const TXString& objectName);
			virtual					~VWToolDefaultRect_EventSink();

		public:
			// override to modify the fToolInfo. Set 'fUseToolInfo' to true of the info is valid
			virtual void				Init(const TXString& universalName);
			const SDefaultRectToolInfo&	GetToolInfo() const;
			void						SetToolInfo(const SDefaultRectToolInfo& info);
			
		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);

		private:
			SDefaultRectToolInfo	fToolInfo;
			SDefaultRectToolInfo	fVWToolInfo;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWToolDefault2DPoly_EventSink	: public VWToolDefault_EventSink
		{
		public:
									VWToolDefault2DPoly_EventSink(IVWUnknown* parent, const TXString& objectName);
			virtual					~VWToolDefault2DPoly_EventSink();

		public:
			// override to modify the fToolInfo. Set 'fUseToolInfo' to true of the info is valid
			virtual void					Init(const TXString& universalName);
			const SDefault2DPolyToolInfo&	GetToolInfo() const;
			void							SetToolInfo(const SDefault2DPolyToolInfo& info);

			// Finishes the tool by creating a handle to the path object
			// The returned handle is created in the layer, so you'll have to manage it
			// This function is designed to be used inside VWTool_EventSink::HandleComplete override
			// If using this function do not call VWTool_EventSink::Default
			MCObjectHandle					DefaultHandleCreate();

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);

		private:
			SDefault2DPolyToolInfo	fToolInfo;
			SDefault2DPolyToolInfo	fVWToolInfo;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWToolDefault3DPoly_EventSink	: public VWToolDefault_EventSink
		{
		public:
									VWToolDefault3DPoly_EventSink(IVWUnknown* parent, const TXString& objectName);
			virtual					~VWToolDefault3DPoly_EventSink();

		public:
			// override to modify the fToolInfo. Set 'fUseToolInfo' to true of the info is valid
			virtual void					Init(const TXString& universalName);
			const SDefault3DPolyToolInfo&	GetToolInfo() const;
			void							SetToolInfo(const SDefault3DPolyToolInfo& info);

		// IToolEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE Execute(ToolMessage* message);

		private:
			SDefault3DPolyToolInfo	fToolInfo;
			SDefault3DPolyToolInfo	fVWToolInfo;
		};
	}
}
