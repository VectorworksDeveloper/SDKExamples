//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "DirectModellingSupport.h"
#include "WidgetsEditProvider.h"

#ifndef SDK_NEW
#define SDK_NEW new
#endif

namespace VWFC
{
	namespace PluginSupport
	{
		using namespace VectorWorks::Extension;

		class VWParametric_EventSink	: public VCOMImpl<IParametricEventSink>
		{
		public:
									VWParametric_EventSink(IVWUnknown* parent);
			virtual					~VWParametric_EventSink();

			void					SetUniversalName(const TXString& name);

		// Plug-in Object action/events constants 
		public:
			// initialization called on the first event
			virtual void			InitializeExt();
			// deitilialization, called on destructor time
			// (you can just use the destructor)
			virtual void			DeinitializeExt();
			// The Plug-in Object code should re-create all its component objects using current parameter values.
			virtual EObjectEvent	Recalculate();
			// Object Definition Procedure (ODP) may optionally present its own preferences dialog, or let VW pose the default dialog.
			virtual EObjectEvent	Preference();

		public:
			// The Plug-in Object may add extended properties.
			virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
			// The Plug-in Object called with kParametricOnMove when kHasMoveDependancy extended property set
			virtual EObjectEvent	OnSpecialEditID();
			virtual EObjectEvent	OnSpecialEditID(TObjectEditResult& outResult);
			// The user has pressed a button in the Properties UI of an object
			virtual EObjectEvent	OnObjectUIButtonHit(Sint32 buttonID);
			// Update object's shape pane widgets
			virtual bool			OnWidgetUpdate(IWidgetsProvider* pWidgetProvider);
			virtual bool			OnWidgetUpdateStyleParameters(IWidgetsProvider* pWidgetProvider, bool hideStyleParameters );

			// Handle widget change and different reset states.
			virtual EObjectEvent	OnAddState(ObjectState& stateInfo);
			// The user has manipulated one of plugin object's control points.
			virtual Sint32			OnCursorEvent(ParametricMessage* message);

			virtual Sint32			OnDrag(ParametricMessage* message);

			// Obtain the tool name that is to be activated for this object
			// when doing 'create similar object' command
			virtual TXString		OnGetToolName() const;
			// Object context menu support
			virtual void			OnContextMenuInit(IContextMenuProvider* pContextMenuProvider);
			virtual void			OnContextMenuEvent(const ObjectContextMenuEvent& eventData);
			// Eyedropper notifies that it is going to put the record 'hObjRecordCopy' as record for the current parametric object
			// In this event the object can alter the copy to ensure correct data transfer (the data has already been copied to the record)
			// NOTE! This object's record is still in place when this event is called
			virtual void			OnEyedropperPrepareCopy(MCObjectHandle hObjRecordCopy);
			// Eyedropper notification that has finished with copying this object
			virtual void			OnEyedropperAfterCopy(MCObjectHandle srcObject);
			// suply specific geometry
			virtual MCObjectHandle	OnGetSpecificGeometry(ObjectGetSpecificGeometryCall::ESpecifier geomType);

			virtual bool			OnGetObjectInCurtainWall();
			virtual void			OnSetObjectInCurtainWall( double width, double height, WorldPt& center, Sint32 index );
			virtual bool			OnGetSubtractPanelFromFrames();

			virtual bool			IsUsingLayerCutPlane();
			virtual bool			AllowWorksheetEdit( const TXString & fieldName );
			virtual void			OnAttributeQuery( ParametricCanEditAttrMessage& msg);
			virtual bool			OnQTOFunction(EQTOFunction function, const TXString& option, const std::vector<VWVariant>& args, MCObjectHandle hSubPart, VWVariant& outResult); // return true if handled

			virtual EObjectEvent	OnCreatePluginStyle(MCObjectHandle symDefHandle);
			virtual EObjectEvent	OnFinalizeCreatePluginStyle(MCObjectHandle symDefHandle);
			virtual EObjectEvent	OnValidateReplacePluginStyle(MCObjectHandle symDefHandle);
			virtual EObjectEvent	OnEditPluginStyle(MCObjectHandle symDefHandle );
			virtual EObjectEvent	OnUpdateStyledObject(MCObjectHandle symDefHandle );
			virtual EObjectEvent	OnFinalizeUpdateStyledObject(MCObjectHandle symDefHandle );
			virtual EObjectEvent	OnStyleWidgetChosen(int itemChosen );
			virtual EObjectEvent	OnForwardTranslateStyleToVW22(MCObjectHandle symDefHandle );
			virtual EObjectEvent	OnBeginStyledObjectsUpdate( MCObjectHandle symDefHandle );
			virtual EObjectEvent	OnEndStyledObjectsUpdate(MCObjectHandle symDefHandle );
			virtual EObjectEvent	OnFinalizeUpdateStyle(MCObjectHandle symDefHandle);

			/*	Gets the name of the folder, which will be selected and created, if not existing,
				by default in the select folder dialog, when creating new style.
				If the function returns false, the last selected folder will be selected and no new folder will be created.
				If the function returns true and outStyleFolderName is already taken by another object that is not a folder,
				the last selected folder will be selected and no new folder will be created.
			*/
			virtual bool			OnGetStyleFolder(TXString& outStyleFolderName);

			virtual EObjectEvent	OnGetCatalogPath( EFolderSpecifier & outFolderSpecifier, TXString & outRelativePath );

			// Handle the transformation from Rotate menu commands (Rotate 2D/3D, Rotate Left/Right, Flip), see kObjXHandlesCommand
			virtual EObjectEvent	OnModifyObjectCommand(const TransformMatrix& transformMat);

			// Get customized Bounds for Rotated, Align, Flip Horizontal and Flip Vertical
			virtual bool			OnGetCustomBounds(WorldRect& outBounds){ return false; }

			// Check if the profile group is page-based or world-based currently. See kObjXPropPageBaseProfileGroup
			virtual bool			OnIsProfileGroupPageBased(EPageBasedProfileGroupCheckingContext context){ return false; }

			// Auto Dimensioning callbacks
			virtual bool			OnAutoDimMessage_GetDisplayCategoryName(TXString& outstrCategory_UniversalName, TXString& outstrCategory_LocalizedNameName) { return false; }
			virtual bool			OnAutoDimMessage_GetLocalizedTypeName(const TXString& instrDimID_UniversalName, TXString& outstrDimID_LocalizedName)	{ return false; }
			virtual bool			OnAutoDimMessage_GetSupportedTypes(EViewTypes inView, std::vector<VectorWorks::Extension::TAutoDimensionTypeInfo>& outvecTypes)	{ return false; }
			virtual bool			OnAutoDimMessage_GetDimensionDefinitions(EViewTypes inView, const TXString& instrDimID_UniversalName, VectorWorks::Extension::EAutoDimensionPlacement inPlace, std::vector<VectorWorks::Extension::TAutoDimensionDefinition>& outvecDimensions) { return false; }

			virtual bool			OnPrepareForContext(VectorWorks::Extension::EParametricContext inContext, EViewTypes inView, short inBgRenderMode, short inFgRenderMode, bool& outbChanged) { return false; }

			virtual void			OnClosureGapQuery(ParametricProvidesClosureGapsMessage& msg);

			virtual EObjectEvent	OnGetInteractiveSizingParams(InteractiveSizingInformation& fInteractiveSizingInfo /* vector of SInteractiveSizingParameterInfo */);
			virtual EObjectEvent	OnSetInteractiveSizingParams(const InteractiveSizingInformation& fInteractiveSizingInfo /* vector of SInteractiveSizingParameterInfo */);

			// Handing related
			virtual EObjectEvent	OnParamPreModification(const EParamModification& modificationID);
			virtual EObjectEvent	OnParamGetHandingParams(HandingInformation& handingInfo /* vector of SInteractiveSizingParameterInfo */);
			virtual EObjectEvent	OnParamSetHandingParams(const HandingInformation& handingInfo /* vector of SInteractiveSizingParameterInfo */);

			virtual EObjectEvent	OnParamGetContainerHandingParams(ContainerHandingParams& localContainerHandingParams, SInteractiveSizingParameterInfo& newInteriorSide, Sint32 updatedHandingParamsSetID);
			virtual EObjectEvent	OnParamSetContainerHandingParams(const ContainerHandingParams& localContainerHandingParams, const SInteractiveSizingParameterInfo& newInteriorSide, Sint32 updatedHandingParamsSetID);

			// Before constraining WP to flat View
			virtual Sint32 			HandleOnGetToolWantsWPConstrainedToView();

			virtual void			OnEquipmentItemDataMessage(ParametricEquipmentItemDataMessage& msg) {};

			// Get custom scale
			virtual bool			OnGetCustomScale(double& outScale) { return false; }

			// Return kObjectEventHandled if the PIO handled the symbol insertion. See kObjXPropHandleSymbolInsertion
			virtual Sint32			OnSymbolInsertion(MCObjectHandle hSymbol);
			// Return kObjectEventHandled if the PIO handled the symbol removal. See kObjXPropHandleSymbolInsertion
			virtual Sint32			OnSymbolRemoval(MCObjectHandle hSymbol);
			// Return the constrained insertion point of the symbol. See kObjXPropHandleSymbolInsertion
			virtual WorldPt3		OnSymbolMoveConstraint(MCObjectHandle hSymbol, WorldPt3 interactiveInsertionPoint);

			// Get Path Elevation. It will be used into the reshape tool.
			virtual bool			OnGetOverrideRotatedPathElevation(double& outElevation) { return false; }

			// The default event notificaiotn
			// if no virutal is present for an event, this function is called to allow the user to catch everything
			virtual Sint32			OnDefaultEvent(ParametricMessage* message);

		// IParametricEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE	Execute(ParametricMessage* message);

		private:
			// DO NOT USE THESE!!!
			virtual void			GetUserData(void) const;
			virtual void			SetUserData(void) const;

			struct ParametricGetGlazingArea {};
			// use 'OnQTOFunction' instead of this one
			virtual void			OnGetGlazingArea(ParametricGetGlazingArea& message) {}

		protected:
			MCObjectHandle		fhObject;
			TXString			fUnivName;
			bool				fbInitialized;
			TObjectEdiReason	fObjectEditReason;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SParametricDef
		{
			SResString			fLocalizedName;
			EParametricSubType	fSubType;
			bool				fResetOnMove;
			bool				fResetOnRotate;
			bool				fWallInsertOnEdge;
			bool				fWallInsertNoBreak;
			bool				fWallInsertHalfBreak;
			bool				fWallInsertHideCaps;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SParametricDef_Legacy
		{
			SSTRResource		fLocalizedName;
			EParametricSubType	fSubType;
			bool				fResetOnMove;
			bool				fResetOnRotate;
			bool				fWallInsertOnEdge;
			bool				fWallInsertNoBreak;
			bool				fWallInsertHalfBreak;
			bool				fWallInsertHideCaps;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SParametricParamChc
		{
			short				fChcID;
			const TXString		fUniversalChoice;
			SResString			fLocalizedChoice;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SParametricParamChc_Legacy
		{
			short				fChcID;
			const TXString		fUniversalChoice;
			SSTRResource		fLocalizedChoice;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SParametricParamDef
		{
			TXString			fUniversalName;
			SResString			fLocalizedName;
			TXString			fDefaultImperial;
			TXString			fDefaultMetric;
			EFieldStyle			fFieldStyle;
			short				fChoicesChcID;		// mathing SParametricParamChc_Legacy::fChcID
		};

		// ------------------------------------------------------------------------------------------------------
		// A callback to let the developer set the default value manually based on the 'initialValue' from the fDefaultImerial or fDefaultMetric or .vwstrings
		typedef std::function<void(bool metric, const TXString& initialValue, const TXString& univParamName, IRecordItem* outValue)>	TDefaultValueCallback;

		// ------------------------------------------------------------------------------------------------------
		// Vectorworks 2025 parameter defintion with advanced default values via resources:
		//	<plugins VWR>/Defaults/<Parametric Univ Name>.json
		//		{
		//			"params": {
		//				"<Param Univ Name 1>": { "default": "<value - one for both>" },
		//				"<Param Univ Name 2>": { "default": { "metric": "<value>", "imerial": "<value>" } }
		//				"<Param Univ Name 1>": { "translate": true, "default": "<value - one for both>" },
		//			}
		//		}
		//
		//	Parameters:
		//		"params" - an object with definitions of the parameters by universal name.
		//			"default" - initial value for the parameter. It could be an object can be used to define metric and imparial initial values separately.
		//			"translate" - optional parameter, an indication for the translation tool to pick this value and show it in the translate tables.
		//						  Use this for defaults of resources, as resources names are typically localized from their (vwx) files.
		//						  Other uses are for strings that need to be translated to other languages.
		//						  Note, this doesn't include regular popups (not dynamic), as their defaults are universal names provided by SParametricParamChc
		//
		//	Note: Comma on the last element in the object {} would be considered a format error!!!
		//	Note: JSON file format cannot have comments
		//	Note: Missing json file will produce an assert. Missing parameters will create empty default
		//	Note: You can use online tools to validate the JSON file, e.g. https://jsonformatter.curiousconcept.com/
		struct SParametricParam2Def
		{
			SParametricParam2Def()
			{
				fLocalizedName.fStringIdentifier = 0;
				fLocalizedName.fResNameWithoutPathOrExtension = 0;
				fFieldStyle					= EFieldStyle(0);
				fChoicesChcID				= 0;
				fDefaultValueCallback		= nullptr;
			}

			SParametricParam2Def(const char* szUnivName, SResString locName, EFieldStyle style, short chcID=0, TDefaultValueCallback defCallback=nullptr)
			{
				fUniversalName				= szUnivName;
				fLocalizedName				= locName;
				fFieldStyle					= style;
				fChoicesChcID				= chcID;
				fDefaultValueCallback		= defCallback;
			}

			TXString				fUniversalName;
			SResString				fLocalizedName;
			EFieldStyle				fFieldStyle;
			short					fChoicesChcID;		// mathing SParametricParamChc_Legacy::fChcID
			TDefaultValueCallback	fDefaultValueCallback	= nullptr;	// can be 'nullptr'
																		// Note: the callback will be called during the undo event of the object's format creation.
		};

		// ------------------------------------------------------------------------------------------------------
		struct SParametricParamDef_Legacy
		{
			const TXString			fUniversalName;
			SSTRResource			fLocalizedName;
			const TXString			fDefaultImperial;
			const TXString			fDefaultMetric;
			EFieldStyle				fFieldStyle;
			short					fChoicesChcID;		// mathing SParametricParamChc_Legacy::fChcID
		};

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionParametric	: public VCOMImmediateImpl<IExtensionParametric>
		{
		public:
											VWExtensionParametric(	CallBackPtr cbp,
																	const SParametricDef& parametricDef,
																	const SParametricParam2Def* arrParamDefs,
																	const SParametricParamChc* arrParamChcs = NULL);
											VWExtensionParametric(	CallBackPtr cbp,
																	const SParametricDef& parametricDef,
																	const SParametricParamDef* arrParamDefs,
																	const SParametricParamChc* arrParamChcs = NULL);
											VWExtensionParametric(	CallBackPtr cbp,
																	const SParametricDef_Legacy& parametricDef,
																	const SParametricParamDef_Legacy* arrParamDefs,
																	const SParametricParamChc_Legacy* arrParamChcs = NULL);
			virtual							~VWExtensionParametric();


		// IExtension
		public:
			virtual IEventSink* VCOM_CALLTYPE		QueryEventSink(const TSinkIID& iid);

		// IExtensionParametric
		public:
			virtual EParametricSubType VCOM_CALLTYPE	GetObjectType();
			virtual const TXString& VCOM_CALLTYPE		GetLocalizedName();
			virtual void VCOM_CALLTYPE					GetResetModeOnMove(bool& outOnMove, bool& outOnRotate);
			virtual void VCOM_CALLTYPE					GetWallInsertMode(bool& outOnEdge, bool& outNoBreak, bool& outHalfBreak, bool& outHideCaps);

			
		// these functions allow an extension implementation to override localized strings provided by the resources
		// use them in the construtor of the extension as the base constructor reads the resources
		protected:
			virtual void VCOM_CALLTYPE			SetLocalizedParamDef( const short listID );
			virtual void VCOM_CALLTYPE			SetLocalizedParamChc( const short listID );
			virtual void VCOM_CALLTYPE			SetLocalizedParamDef( size_t paramIndex, const TXString& inLocalizedName );
			virtual void VCOM_CALLTYPE			SetLocalizedParamDef( const TXString& univParamName, const TXString& localizedParamName );
			virtual void VCOM_CALLTYPE			SetLocalizedParamChc( const TXString& univChoiceName, const TXString& localizedChoiceName );
			virtual void VCOM_CALLTYPE			SetLocalizedName( const TXString& localizedName );

			// Override this function to provide custom localized default values during run-time
            virtual bool						GetLocalizedDefault(bool isMetric, const TXString& szUniversalName, TXString& outValue);

			// Call this functions in the constructor of your extension if you want to provide subpart types for this parametric
			void	AddSubpartType(const char* univName, const TXString& localizedName);

			// access to the parameter defaults .json file, allowing you to access addiditonal data of the parameter than the "default"
			nlohmann::json			GetParamDefault(const TXString& univParamName) const;
			const nlohmann::json&	GetParamDefaults() const;

		protected:
			virtual void						OnRefCountZero();
			virtual IParametricEventSink*		CreateParametricEventSink(IVWUnknown* parent) = 0;
			virtual bool						GetProtectionSinkIID(TSinkIID& outIID);
			virtual IProviderProtection*		CreateProtectionSink(IVWUnknown* parent);
			virtual void						DefineSinks();
			template<class T> void				DefineSink(const TSinkIID& sinkIID);

		private:
			CallBackPtr						fCBP;

			typedef std::multimap<SSTRResource, TXString>					TResStringCache;
			typedef std::multimap<SResString, TXString>						TResStringCache_;
			typedef std::multimap<short, const SParametricParamChc_Legacy*>	TChcCache;
			typedef std::multimap<short, const SParametricParamChc*>		TChcCache_;

			TXString						fUniversalName;
			EParametricSubType				fSubType;
			bool							fResetOnMove;
			bool							fResetOnRotate;
			bool							fWallInsertOnEdge;
			bool							fWallInsertNoBreak;
			bool							fWallInsertHalfBreak;
			bool							fWallInsertHideCaps;

			TXString						fstrLocalizedName;
			TResStringCache					fResStringChache;
			TResStringCache_				fResStringChache_;
			size_t							fParamsCount;
			const SParametricParamDef_Legacy*		farrParamDefs;
			const SParametricParamChc_Legacy*		farrParamChcs;
			const SParametricParamDef*		farrParamDefs_;
			const SParametricParam2Def*		farrParam2Defs_;
			const SParametricParamChc*		farrParamChcs_;
			TChcCache						fParamChcCache;
			TChcCache_						fParamChcCache_;
			TXString						fEmptyString;

			std::vector<std::pair<TXString, TXString>>	farrSubpartTypes;

			class CParametersProvider;
			class CSubpartTypesProvider;

			CParametersProvider*			fParametersSink;
			IParametricEventSink*			fParametricEventSink;
			bool							fProtectionObtained;
			bool							fHasProtection;
			TSinkIID						fProtectionSinkIID;
			IProviderProtection*			fProtectionSink;
			CSubpartTypesProvider*			fSubpartTypesSink;

			typedef std::map<TSinkIID, IEventSink*> TSinksMap;
			TSinksMap						fmapSinks;
			TSinkIID						fDefinedSinkIID;
			IEventSink*						fDefinedSink;

			nlohmann::json					fParamDefaults;

		private:
			// -------------------------------------------------------------------
			class CParametersProvider : public VCOMImpl<IParametricParams2Provider>
			{
			public:
						CParametersProvider(VWExtensionParametric* parent);
				virtual	~CParametersProvider();

			// IParametricParamsProvider
			public:
				virtual size_t VCOM_CALLTYPE			GetParamsCount();
				virtual void VCOM_CALLTYPE				GetParamAt(size_t paramIndex, TXString& outUniversalName, EFieldStyle& outType);
				virtual const TXString& VCOM_CALLTYPE	GetParamNameAt(size_t paramIndex);
				virtual void VCOM_CALLTYPE				GetParamDefValueImperial(size_t paramIndex, IRecordItem* outValue);
				virtual void VCOM_CALLTYPE				GetParamDefValueMetric(size_t paramIndex, IRecordItem* outValue);
				virtual void VCOM_CALLTYPE				GetParamChoices(size_t paramIndex, TXStringArray& outArrUniversalNames, TXStringArray& outArrDisplayNames);

			private:
				void	GetDefaultValue(const TXString& defaultValue, TXString& outValue);
				
				struct SParamDefaults
				{
					TXString	fValueMetric;
					TXString	fValueImerial;
				};

				const SParamDefaults&	GetParamDefaults(size_t paramIndex);

			private:
				VWExtensionParametric*	fParent;

				SParamDefaults						fEmptyDefaults;
				std::map<size_t, SParamDefaults>	fmapParamDefaults;
			};

			// -------------------------------------------------------------------
			class CSubpartTypesProvider : public VCOMImpl<ISubpartTypesProvider>
			{
			public:
						CSubpartTypesProvider(VWExtensionParametric* parent);
				virtual	~CSubpartTypesProvider();

			// ISubpartTypesProvider
			public:
				virtual void VCOM_CALLTYPE Enumerate(ISubpartTypesContext& context);

			public:
				VWExtensionParametric*	fParent;
			};
		};
	}

	namespace PluginSupport
	{
		template<class T> void VWExtensionParametric::DefineSink(const TSinkIID& sinkIID)
		{
			if ( fDefinedSink == NULL && sinkIID == fDefinedSinkIID ) {
				T*	instance	= SDK_NEW T( this );
				fDefinedSink	= instance;
			}
		}
	}
}

