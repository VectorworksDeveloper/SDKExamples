//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#ifndef SDK_NEW
#define SDK_NEW new
#endif

namespace VWFC
{
	namespace PluginSupport
	{
		// ------------------------------------------------------------------------------------------------------
		// This resource identifier is used with TXResStr to obtain the actual resource string
		//		TXResStr is a convenience type intended to standardize requests for localized strings
		//		 in a concise way.  It assumes the default vwr contains the file in a "Strings" directory,
		//		 and that the strings file has extension ".vwstrings"
		//
		//		For conveniece fResNameWithoutPathOrExtension might actually contain a fully-quialified resource path (including .vwstring)
		//		 this will allow plug-ins to reuse resources from common resource file
		struct SResString
		{
			const char*	fResNameWithoutPathOrExtension;	// or fullPathWithExtension. see comment above
			const char*	fStringIdentifier;

			bool		operator<(const SResString& other) const;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SSTRResource
		{
			short	fListID;
			short	fIndex;

			bool	operator<(const SSTRResource& other) const;
		};

		// ------------------------------------------------------------------------------------------------------
		struct STEXTResource
		{
			short	fID;

			bool	operator<(const STEXTResource& other) const;
		};

		// ------------------------------------------------------------------------------
		enum EObjectEvent {
				kObjectEventNoErr			= kParametricNoErr,			//= 0;		// 
				kObjectEventSetupFailed		= kParametricSetupFailed,	//= -1;
				kObjectEventError			= kParametricError,			//= -2;
				kObjectEventNotImplemented	= kParametricNotImplemented,//= -3;		// The Plug-in did not present its own preference dialog, it is up to the VW application to do it.
				kObjectEventPrefOK			= kParametricPrefOK,		//= -4;		// The Plug-in presented its own preferences dialog, and the user hit OK.
				kObjectEventPrefCancel		= kParametricPrefCancel,	//= -5;		// The Plug-in presented its own preferences dialog, and the user hit Cancel.
				kObjectEventHadError		= kParametricHadError,		//= -6;		// The Plug-in compiled but had an error during execution.
				kObjectEventHadWarning		= kParametricHadWarning,	//= -7;		// The Plug-in compiled but had a warning during execution.
                kObjectEventStayLoaded      = -12,                      //= -12;    // The Plug-in returns this value on InitializeExt in order to stay loaded indefinitely
				kObjectEventUIButtonOK		= kObjectUIButtonHitOK,
				kObjectEventUIButtonCancel	= kObjectUIButtonHitCancel,
				kObjectEventUIButtonPreventReset = kObjectUIButtonHitPreventReset,
		};

		// ------------------------------------------------------------------------------
		enum EMenuCallbackEvent {
			kMenuCallbackEventActiveDocChange	= 'DOCC',		// Send when a different document becomes the frontmost one
			kMenuCallbackEventDocClose			= 'DCLS',		// Send when a document closes.
			kMenuCallbackEventSelChange			= 'SELC',
			kMenuCallbackEventLockObjectChange	= 'Lock',		// Object(s) have had their Lock flag changed.
			kMenuCallbackEventMenuDone			= 'DONE',
			kMenuCallbackEventWPChange			= 'wpch',
			kMenuCallbackEventWPListChange		= 'wpxx',
			kMenuCallbackEventDimStdChange		= 'DIMS',
			kMenuCallbackEventLayerChange		= 'LAYR',
			kMenuCallbackEventClassChange		= 'CLAS',
			kMenuCallbackEventSubscripAddDel	= 'SbAD',		// Send when a subscription [reference] has been added or deleted
			kMenuCallbackEvent3DViewChange		= '3DVC',
			kMenuCallbackEventViewChange		= 'VIEW',
			kMenuCallbackEventTextChange		= 'TEXT',		// Send when text menus or att palette is changed on a VW text object
			kMenuCallbackEventWallStyleChange	= 'WaCh',		// Send when a Wall Style has been added, deleted, or edited
			kMenuCallbackEventWallAdd		 	= 'WAdd',		// Send when a wall or round wall has been added
			kMenuCallbackEventWallDelete	 	= 'WDel',		// Send when a wall or round wall has been deleted
			kMenuCallbackEventWallEdit		 	= 'WEdt'		// Send when a wall or round wall has been edited
		};

		// ---------------------------------------------------------------------------
		enum EStandardCursor {
			kStandardCursor_Arrow			= 147,
			kStandardCursor_ArrowShort		= 140,
			kStandardCursor_ArrowDiagonal	= 107,
			kStandardCursor_ArrowVertical	= 401,
			kStandardCursor_FourArrows		= 93,
			kStandardCursor_HandFinger		= 304,
			kStandardCursor_HandLeft		= 104,
			kStandardCursor_Hand			= 145,
			kStandardCursor_CrossSmall		= 103,
			kStandardCursor_CrossBig		= 105,
			kStandardCursor_CrossBigDashed	= 106,
			kStandardCursor_CrossBezier		= 330,
			kStandardCursor_CrossCubic		= 331,
			kStandardCursor_CrossArc		= 332,
			kStandardCursor_Target			= 154,
			kStandardCursor_Bucket			= 126,
			kStandardCursor_Pipette			= 442,
			kStandardCursor_XCrosshairs		= 159,
		};

		// ---------------------------------------------------------------------------
		typedef		Sint32			TToolStatus;
		class IToolStatusProvider
		{
		public:
			virtual					~IToolStatusProvider() {}
			virtual	TToolStatus		GetOnePointToolStatus() const = 0;
			virtual TToolStatus		GetTwoPointToolStatus() const = 0;
			virtual TToolStatus		GetThreePointToolStatus() const = 0;
			virtual TToolStatus		GetPolyToolStatus() const = 0;
			virtual TToolStatus		GetClickDragToolStatus() const = 0;
		};

		// ---------------------------------------------------------------------------
		class IToolModeBarProvider
		{
		public:
			virtual					~IToolModeBarProvider() {}
			virtual void			EnableModeGroup(size_t modeGroupID, bool bEnable) const = 0;
			virtual void			SetHelpString(const TXString& helpMessage) const = 0;
			virtual void			SetHighlightedHelpString(const TXString& helpMessage) const = 0;
			virtual Sint32			GetModeGroupValue(size_t modeGroupID) const = 0;
			virtual void			SetModeGroupValue(size_t modeGroupID, Sint32 value) const = 0;
			virtual void			InsertPullDownMenuItem(size_t modeGroupID, const TXString& text) const = 0;
			virtual size_t			GetPullDownMenuSelection( size_t modeGroupID ) const = 0;
			virtual void			SetPullDownMenuSelection(size_t modeGroupID, size_t selection) const = 0;
			virtual void			SetPullDownResourceValue(size_t modeGroupID, const TXString& value) = 0;
			virtual Sint32			ShowPullDownResourcePopup(size_t modeGroupID, const SShowPullDownResourcePopup& data, const TXString& selectedName, ThumbnailSizeType thumbSize=kStandardSize) = 0;
			virtual Sint32			ShowPullDownResourcePopup(size_t modeGroupID, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize=kStandardSize) = 0;
			virtual bool			SetButtonsHelpText(const TXStringArray& arrHelpText) const = 0;
			virtual void			ClearPullDownMenu(size_t modeGroupID) const = 0;
			virtual void			SetEditTextValue(size_t modeGroupID, const TXString& value) = 0;
			virtual TXString		GetEditTextValue(size_t modeGroupID) = 0;
			virtual TXString		PullDownResourcePopupGetSelected(size_t modeGroupID) = 0;
			virtual void			PullDownResourcePopupSetSelected(size_t modeGroupID, const TXString& name) = 0;
			virtual bool			GetCheckGroupState( size_t modeGroupID ) const = 0;
			virtual void			SetCheckGroupState( size_t modeGroupID, bool state ) const = 0;
			virtual void			SetRadioModeGroupValue(size_t modeGroupID, Sint32 value, const TXStringArray& imageSpecs) const = 0;
		};

		// ---------------------------------------------------------------------------
		class IToolModeBarInitProvider : public IToolModeBarProvider
		{
		public:
			virtual				~IToolModeBarInitProvider() {}
			
			virtual void		AddButtonModeGroup(const TXString& imageSpec) const = 0;
			virtual void		AddCheckModeGroup(const TXString& imageSpec, bool initState) const = 0;

			virtual void		AddPullDownMenuModeGroup(const TXString& label) const = 0;
			virtual void		AddPullDownResourceModeGroup(const TXString& label, const TXString& value) const = 0;

			virtual void		AddRadioModeGroup(size_t initState, const TXStringArray& images) const = 0;
			virtual void		AddTextButtonModeGroup(const TXString& text) const = 0;

			virtual void		AddEditTextModeGroup(const TXString& label, const TXString& value) const = 0;
			virtual void		AddEditTextModeGroup(const TXString& label, const TXString& value, Sint32 textWidth) const = 0;

			virtual void		PullDownResourcePopupSet(size_t modeGroupID, VectorWorks::Extension::IResourceManagerContent*content) const = 0;
		};

		// ---------------------------------------------------------------------------
		class IToolDrawProvider
		{
		public:
			virtual				~IToolDrawProvider() {}

			// default drawing
			virtual void		DrawDefaultRect() const = 0;
			virtual void		DrawDefault2D() const = 0;
			virtual void		DrawDefault3D() const = 0;

			// simple drawing
			virtual void		DrawLine2D(const VWLine2D& line) const = 0;
			virtual void		DrawLine3D(const VWLine3D& line) const = 0;
			virtual void		DrawRect(const VWRectangle2D& rect) const = 0;
			virtual void		DrawArc(const VWArc2D& arc) const = 0;
			virtual void		DrawEllipse(const VWRectangle2D& rect) const = 0;

			// poly drawing
			virtual void		DrawPolyBegin() = 0;
			virtual void		DrawPoly_AddCornerVertex(const VWPoint2D& pt) = 0;
			virtual void		DrawPoly_AddBezierVertex(const VWPoint2D& pt) = 0;
			virtual void		DrawPoly_AddCubicVertex(const VWPoint2D& pt) = 0;
			virtual void		DrawPoly_AddArcVertex(const VWPoint2D& pt, double dRadius) = 0;
			virtual void		DrawPolyEnd() = 0;
			virtual void		DrawPolyEnd(const VWTransformMatrix& matrix) = 0;

			// object drawing
			virtual void		DrawObject(MCObjectHandle hObj, bool bDoSelect) const = 0;
			virtual void		DrawNurbsObject(MCObjectHandle hNurbsObj) const = 0;
			virtual void		DrawDataDisplayBar(bool bDrawFramesFirst = false) const = 0;

			// attributes
			virtual void		SetPenSize(short penSize = 0) const = 0;
			virtual void		SetPenPattern(short penPatIndex = 2) const = 0;
		};

		// ---------------------------------------------------------------------------
		class IToolPropertiesProvider
		{
		public:
			virtual				~IToolPropertiesProvider() {}
			virtual bool		SetProperty(Sint32 propID, bool bValue) = 0;
			virtual bool		SetPropertyChar(Sint32 propID, char value) = 0;
			virtual Sint32		GetCodeRefID() = 0;
		};
	}

	// Helper tools
	namespace PluginSupport
	{
		//------------------------------------------------------------------
		// Registeres a public VCOM interface implementation -- available in entire Vectorworks
		template<class T> void REGISTER_Interface(const VWIID& iid, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(iid, moduleInfo);
			}
			else if ( action == kVCOMQueryInterface ) {
				if ( inInterfaceID == iid ) {
					T*			instance	= SDK_NEW T( cbp );
					inOutInterface			= instance;
				}
				if ( inOutInterface == 0 || reply != kVCOMError_NoError ) {
					reply	= kVCOMError_NoInstance;
				}
			}
			else if ( action == kVCOMReleaseInterface ) {
				if ( inInterfaceID == iid ) {
					T* implementation = dynamic_cast<T*>( inOutInterface );
					if ( VERIFYN( kVStanev, implementation ) ) {
						delete implementation;
						implementation = nullptr;
						inOutInterface = nullptr;
					}
					if ( implementation == 0 || reply != kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
			else if ( action == kVCOMQueryInterfaceRTTI ) {
				if ( inInterfaceID == iid ) {
				}
			}
		}

		//------------------------------------------------------------------
		// Registeres a public VCOM interface implementation -- available in entire Vectorworks
		// Do not store cache for this interface
		// -- this will reduce the performance of the interface a little but
		//    but will allow more dynamic data for the interface
		template<class T> void REGISTER_Interface_NoCache(const VWIID& iid, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(iid, moduleInfo, false);
			}
			else {
				REGISTER_Interface<T>( iid, action, moduleInfo, inInterfaceID, inOutInterface, cbp, reply );
			}
		}

		//------------------------------------------------------------------
		// Registeres a public VCOM interface implementation -- available in entire Vectorworks
		template<class T> void REGISTER_Interface(const VWGroupID& iidGroup, const VWIID& iid, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(iid, iidGroup, moduleInfo);
			}
			else if ( action == kVCOMQueryInterface ) {
				if ( inInterfaceID == iid ) {
					T*			instance	= SDK_NEW T( cbp );
					inOutInterface			= instance;
				}
				if ( inOutInterface == 0 ) {
					// preserve the error
					if ( reply == kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
			else if ( action == kVCOMReleaseInterface ) {
				if ( inInterfaceID == iid ) {
					T* implementation = dynamic_cast<T*>( inOutInterface );
					if ( VERIFYN( kVStanev, implementation ) ) {
						delete implementation;
						implementation = nullptr;
						inOutInterface	= nullptr;
					}
					else {
						// preserve the error
						if ( reply == kVCOMError_NoError ) {
							reply	= kVCOMError_NoInstance;
						}
					}
				}
			}
		}
		
		//------------------------------------------------------------------
		// Registeres a public VCOM interface implementation -- available in entire Vectorworks
		// Do not store cache for this interface
		// -- this will reduce the performance of the interface a little but
		//    but will allow more dynamic data for the interface
		template<class T> void REGISTER_Interface_NoCache(const VWGroupID& iidGroup, const VWIID& iid, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(iid, moduleInfo, false);
			}
			else {
				REGISTER_Interface<T>( iidGroup, iid, action, moduleInfo, inInterfaceID, inOutInterface, cbp, reply );
			}
		}

		// --------------------------------------------------------------------------------------------------------
		// Registeres interface implementation available only through another interface
		template<class T> void REGISTER_HiddenInterface(const VWIID& iid, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			if ( action == kVCOMRegisterInterfaces ) {
				;
			}
			else if ( action == kVCOMQueryInterface ) {
				;
			}
			else if ( action == kVCOMReleaseInterface ) {
				if ( inInterfaceID == iid ) {
					T* implementation = dynamic_cast<T*>( inOutInterface );
					if ( VERIFYN( kVStanev, implementation ) ) {
						delete implementation;
						implementation = nullptr;
						inOutInterface = nullptr;
					}
					if ( implementation == 0 || reply != kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
		}

		// --------------------------------------------------------------------------------------------------------
		// Registeres extension application interface implementation
		template<class T> void REGISTER_Extension(const VWGroupID& groupID, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			using namespace VectorWorks::Extension;
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(T::_GetIID(), groupID, moduleInfo);
			}
			else if ( action == kVCOMQueryInterface ) {
				if ( inInterfaceID == T::_GetIID() ) {
					T*			instance	= SDK_NEW T( cbp );
					// check if this is the only one interface recognized
					ASSERTN( kVStanev, inOutInterface == 0 );
					inOutInterface			= instance;
					if ( inOutInterface == 0 || reply != kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
			else if ( action == kVCOMReleaseInterface ) {
				if ( inInterfaceID == T::_GetIID() ) {
					T* implementation = dynamic_cast<T*>( inOutInterface );
					if ( VERIFYN( kVStanev, implementation ) ) {
						delete implementation;
						implementation = nullptr;
						inOutInterface = nullptr;
					}
					if ( implementation == 0 || reply != kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
		}

		//------------------------------------------------------------------
		// Registeres extension application interface implementation
		// Do not store cache for this interface
		// -- this will reduce the performance of the interface a little but
		//    but will allow more dynamic data for the interface
		template<class T> void REGISTER_Extension_NoCache(const VWGroupID& groupID, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			using namespace VectorWorks::Extension;
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(T::_GetIID(), groupID, moduleInfo, false);
			}
			else {
				REGISTER_Extension<T>( groupID, action, moduleInfo, inInterfaceID, inOutInterface, cbp, reply );
			}
		}

		// --------------------------------------------------------------------------------------------------------
		// Registeres unit test interface implementation
		template<class T> void REGISTER_SystemTest(const VWIID& iid, Sint32 action, void* moduleInfo, const VWIID& inInterfaceID, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)
		{
			using namespace VectorWorks::Extension;
			if ( action == kVCOMRegisterInterfaces ) {
				::GS_VWRegisterInterface(iid, VectorWorks::Debug::GROUPID_SystemTest, moduleInfo);
			}
			else if ( action == kVCOMQueryInterface ) {
				if ( inInterfaceID == iid ) {
					T*			instance	= SDK_NEW T();
					// check if this is the only one interface recognized
					ASSERTN( kVStanev, inOutInterface == 0 );
					inOutInterface			= instance;
					if ( inOutInterface == 0 || reply != kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
			else if ( action == kVCOMReleaseInterface ) {
				if ( inInterfaceID == iid ) {
					T* implementation = dynamic_cast<T*>( inOutInterface );
					if ( VERIFYN( kVStanev, implementation ) ) {
						delete implementation;
						implementation = nullptr;
						inOutInterface = nullptr;
					}
					if ( implementation == 0 || reply != kVCOMError_NoError ) {
						reply	= kVCOMError_NoInstance;
					}
				}
			}
		}
	}
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_VWMenuExtension
#undef IMPLEMENT_VWMenuExtension
#define		DEFINE_VWMenuExtension																	\
 protected:																							\
	virtual VectorWorks::Extension::IMenuEventSink*	CreateMenuEventSink(IVWUnknown* parent);		\
 public:																							\
	static const VWIID&									_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_VWMenuExtension( TClass, TEventSkink, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	VectorWorks::Extension::IMenuEventSink*	TClass::CreateMenuEventSink(IVWUnknown* parent)	{ return SDK_NEW TEventSkink( parent ) ; }					\
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_VWParametricExtension
#undef IMPLEMENT_VWParametricExtension
#define		DEFINE_VWParametricExtension															\
 protected:																							\
	virtual VectorWorks::Extension::IParametricEventSink*	CreateParametricEventSink(IVWUnknown* parent);	\
 public:																							\
	static const VWIID&									_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_VWParametricExtension( TClass, TEventSkink, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	VectorWorks::Extension::IParametricEventSink*	TClass::CreateParametricEventSink(IVWUnknown* parent)	{ return SDK_NEW TEventSkink( parent ) ; }					\
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_VWToolExtension
#undef IMPLEMENT_VWToolExtension
#define		DEFINE_VWToolExtension																	\
 protected:																							\
	virtual VectorWorks::Extension::IToolEventSink*	CreateToolEventSink(IVWUnknown* parent);		\
 public:																							\
	static const VWIID&									_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_VWToolExtension( TClass, TEventSkink, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	VectorWorks::Extension::IToolEventSink*		TClass::CreateToolEventSink(IVWUnknown* parent)	{ return SDK_NEW TEventSkink( parent ) ; }					\
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_VWVSFunctionsExtension
#undef IMPLEMENT_VWVSFunctionsExtension
#define		DEFINE_VWVSFunctionsExtension																		\
 protected:																							\
	virtual VectorWorks::Extension::IVSFunctionsEventSink*	CreateVSFunctionsEventSink(IVWUnknown* parent);	\
 public:																							\
	static const VWIID&									_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_VWVSFunctionsExtension( TClass, TEventSkink, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	VectorWorks::Extension::IVSFunctionsEventSink*	TClass::CreateVSFunctionsEventSink(IVWUnknown* parent)	{ return SDK_NEW TEventSkink( parent ) ; }					\
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_VWWSFunctionOptionsExtension
#undef IMPLEMENT_VWWSFunctionOptionsExtension
#define		DEFINE_VWWSFunctionOptionsExtension														\
 protected:																							\
	virtual VectorWorks::Extension::IWSFunctionCallEventSink*	CreateWSFuncOptionsEventSink(IVWUnknown* parent);	\
 public:																							\
	static const VWIID&									_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_VWWSFunctionOptionsExtension( TClass, TEventSkink, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	VectorWorks::Extension::IWSFunctionCallEventSink*	TClass::CreateWSFuncOptionsEventSink(IVWUnknown* parent)	{ return SDK_NEW TEventSkink( parent ) ; }					\
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define		DEFINE_VWProtection		protected:																												\
									virtual VectorWorks::Extension::IProviderProtection*	CreateProtectionSink(IVWUnknown* parent);						\
									virtual bool											GetProtectionSinkIID(VectorWorks::Extension::TSinkIID& outIID);	\
									class CExtMenu_Protection : public VCOMImpl<VectorWorks::Extension::IProviderProtection> { public:						\
											CExtMenu_Protection(IVWUnknown* parent, Uint16 magicNumber, Uint32 products, Uint16 modes)	\
												: VCOMImpl<IProviderProtection>( parent )												\
												{ fMagicNumber = magicNumber; fProducts = products; fModes = modes; }					\
											virtual Uint16	VCOM_CALLTYPE	GetMagicNumber()	{ return fMagicNumber;	}				\
											virtual Uint32	VCOM_CALLTYPE	GetProducts()		{ return fProducts; }					\
											virtual Uint16	VCOM_CALLTYPE	GetModes()			{ return fModes; }						\
										private: Uint16 fMagicNumber; Uint32 fProducts; Uint16 fModes;									\
									};

#define		IMPLEMENT_VWProtection( TClass, IID, MAGIC_NUM, PRODUCTS, MODES )												\
					bool TClass::GetProtectionSinkIID(VectorWorks::Extension::TSinkIID& outIID) {							\
						outIID	= IID;																						\
						return true;																						\
					}																										\
					VectorWorks::Extension::IProviderProtection* TClass::CreateProtectionSink(IVWUnknown* parent) {			\
						return SDK_NEW CExtMenu_Protection( parent, MAGIC_NUM, PRODUCTS, MODES );								\
					}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_ChangeSubscriberExtension
#undef IMPLEMENT_ChangeSubscriberExtension
#define		DEFINE_ChangeSubscriberExtension															\
 public:																							\
	static  const VWIID&								_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_ChangeSubscriberExtension( TClass, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#undef DEFINE_VWPaletteExtension
#undef IMPLEMENT_VWPaletteExtension
#define		DEFINE_VWPaletteExtension																\
 public:																							\
	static const VWIID&									_GetIID();									\
	virtual Sint32 VCOM_CALLTYPE						GetVersion();								\
	virtual const TXString& VCOM_CALLTYPE				GetUniversalName();							\
 private:																							\
	TXString	fUniverslalName;

#define		IMPLEMENT_VWPaletteExtension( TClass, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	const VWIID&								TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE						TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE				TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _VWFC_LEGACY

#include "VWExtensionParametric.h"
#include "VWExtensionMenu.h"
#include "VWExtensionTool.h"
#include "VWExtensionVSFunctions.h"
#include "VWExtensionWSFuncOptions.h"

#endif
