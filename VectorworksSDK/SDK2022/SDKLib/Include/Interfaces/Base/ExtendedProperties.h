//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//



#pragma once

typedef Sint32		CodeRefID;
typedef	Uint32		TComponentTypeID;
typedef	short		TParametricFileIndex;
typedef std::vector<MCObjectHandle>	TMCObjectHandlesSTLArray;

namespace VectorWorks
{
	namespace Extension
	{
		class IResourceManagerContent;
	}
}

struct ParametricInitXPropsMessage : public ParametricMessage
{
	enum { kAction = 5 };

	ParametricInitXPropsMessage(CodeRefID codeRefID) { fAction = ParametricInitXPropsMessage::kAction; fCodeRefID = codeRefID; }

	CodeRefID	fCodeRefID;
};

struct ToolInitXPropsMessage : public ToolMessage
{
	enum { kAction = 108 };

	ToolInitXPropsMessage(CodeRefID codeRefID) { fAction = ToolInitXPropsMessage::kAction; fCodeRefID = codeRefID; }

	CodeRefID	fCodeRefID;
};

//---------------------------------------------------
//---------------------------------------------------


struct EPE_Kludge
//
//	Structure for the private API between the ExtendedProperties Module and the application.
{
public:
	enum {
		kKludgeSelector = 3463,

		// DO NOT USE THOSE SELECTORS !!!
		// Ask Vlado how to do it without these!
		
		kKludgeSubSelector6 = 6,
		kKludgeSubSelector7 = 7,	// Extended Properties Application Access
		kKludgeSubSelector8 = 8,	// Extended Properties Application Access
		kKludgeSubSelector9 = 9,			// Extended Properties Application Access
		kKludgeSubSelector10 = 10,		// Extended Properties Application Access
		kKludgeSubSelector11 = 11,
		kKludgeSubSelector12 = 12,	
		kKludgeSubSelector13 = 13,
		kKludgeSubSelector14 = 14,
		kKludgeSubSelector15 = 15,
		kKludgeSubSelector16 = 16,
		kKludgeSubSelector17 = 17,
		kKludgeDrawDashed3DSeg = 18,
		kKludgeAddAssociation = 19,
		kKludgeRemoveAssociation = 20,
		kKludgeSubSelector21 = 21,		// Extended Properties Application Access
		kKludgeSubSelector22 = 22,
		kKludgeSubSelector23 = 23,
	};

	EPE_Kludge(short selector, void* inData) :
		fSelector(selector),
		fData(inData)
	{}
		
	short fSelector;
	void* fData;
	
	
	//	fData structs:
	//

	struct KludgeCallNearestPtOnRayToRayParams {
		Ray fOnRay;
		Ray	fToRay;
		WorldPt3 fGetPtValue;
	};
	struct KludgeDraw3DDashedSegParams {
		WorldPt3	fPoint1;
		WorldPt3	fPoint2;
		short		fDashDistance;
		short	fDashLength;
	};

};


struct WidgetInfoType
//
//	Information for a single object info palette widget.
{
	Sint32		fParameterType;			// Parameter type
	Sint32		fMappingID;				// Maps widget to a parameter
									// or widget ID for added parameters
	TXString	text;				// Widget text
	char		fFlag;

	enum { 
		kDefault = 0, 
		kHide = 1, 
		kShow = 2, 
		kDisable = 4 
	};

	WidgetInfoType() {
		fParameterType = fMappingID = 0;
		fFlag = kDefault;
	}
};

//----------------------------------------------------------
class DYNAMIC_ATTRIBUTE IWidgetData
{
public:
	virtual					~IWidgetData() {}
	virtual const TXString&	GetData() const = 0;
	virtual void			SetData(const TXString& data) = 0;
};

class DYNAMIC_ATTRIBUTE IWidgetDataPopup : public IWidgetData
{
public:
	virtual void		Clear() = 0;
	virtual void		Add(const TXString& idName, const TXString& text) = 0;

	virtual size_t		GetCount() const = 0;
	virtual bool		GetAt(size_t index, TXString& outIdName, TXString& outText) const = 0;
	virtual bool		SetAt(size_t index, const TXString& idName, const TXString& text) = 0;

	virtual void		Insert(size_t beforeIndex, const TXString& idName, const TXString& text) = 0;
	virtual void		RemoveAt(size_t index) = 0;

	virtual bool		IsModified() const = 0;
	virtual void		SetModified(bool bModified) = 0;

	virtual bool		GetTextByIDName(const TXString& idName, TXString& outText) = 0;
	virtual bool		GetIDNameByText(const TXString& text, TXString& outIdName) = 0;
	virtual bool		GetIndexByIDName(const TXString& idName, size_t& outIndex) = 0;

	virtual void		CopyInterfaceDataFrom(IWidgetDataPopup* interfaceData) = 0;
};

class DYNAMIC_ATTRIBUTE IWidgetSearchableDataPopup : public IWidgetData
{
public:
	virtual void		Clear() = 0;
	virtual void		Add(const TXString& idName, const TXString& text, const TXString& toolTip=TXString(), const TXString& iconSpec=TXString()) = 0;
	virtual void		AddChild(const TXString& idName, const TXString& text, const TXString& parentIdName, const TXString& toolTip=TXString(), const TXString& iconSpec=TXString()) = 0;

	// static choices show up at the top of the regular choices and cannot be search. they are used for general predefined fixed options typically
	virtual void		ClearStaticChoices() = 0;
	virtual void		AddStaticChoice(const TXString& idName, const TXString& text, const TXString& toolTip=TXString(), const TXString& iconSpec=TXString()) = 0;

	virtual bool		GetTextByID(const TXString& idName, TXString& outText) = 0;
	virtual bool		GetIDByText(const TXString& text, TXString& outIdName) = 0;
};

class DYNAMIC_ATTRIBUTE IWidgetDataBound : public IWidgetData
{
public:
	virtual Sint32			GetObjectBoundID() const = 0;
	virtual void			SetObjectBoundID(Sint32 data) = 0;
	virtual bool			GetIsTopBound() const = 0;
	virtual void			SetIsTopBound(bool value) = 0;
	virtual bool			GetIsBottomBound() const = 0;
	virtual void			SetIsBottomBound(bool value) = 0;
	virtual bool			GetIsDualBound() const = 0;
	virtual void			SetIsDualBound() = 0;
	virtual Sint16			GetBoundType() const = 0;
};

class DYNAMIC_ATTRIBUTE IWidgetDataResourceThumbnailPopup : public IWidgetData
{
public:
	virtual VectorWorks::Extension::IResourceManagerContent*	GetResContent() const = 0;
	virtual void												SetResContent(VectorWorks::Extension::IResourceManagerContent* resContent) = 0;
};

class DYNAMIC_ATTRIBUTE IWidgetLayerDataPopup : public IWidgetData
{
public:
	virtual void	ClearStaticChoices() = 0;
	virtual void	AddStaticChoice(const TXString& idName, const TXString& text) = 0;

	virtual size_t	GetStaticChoiceCount() const = 0;
	virtual bool	GetStaticChoiceAt(size_t index, TXString& outIdName, TXString& outText) const = 0;
};

//---------------------------------------------------------
enum class EEnergyDataType
{
	None,
	WindowOrDoorFrame,
	WindowOrDoorGlazing,
	WindowOrDoorGeneralShading,
	WindowOrDoorSurroundingShading,
	WindowOrDoorSummerShading,
	WindowOrDoorAdditionalShading,
	WallBoundaryType,
	SlabBoundaryType,
	RoofBoundaryType,
	DoorType,
};

//----------------------------------------------------------
struct SWidgetDefinition
// modern widget definiiton of the widget (WidgetInfoType)
//	This works with IWidgetsProvider for providing extended state of the widgets
{
	Sint32			fWidgetID;
	EWidgetType		fWidgetType;
	TXString		fWidgetText;
	bool			fWidgedVisible;
	bool			fWidgetEnabled;
	bool			fWidgetRed;
	bool			fWidgetRotatedCoord;
	Sint32			fWidgetIndentLevel;
	bool			fReadOnly;
	EEnergyDataType	fEnergyDataType;
	bool			fByStyle;

	// if ( fWidgetID == kWidgetPopUp )			fpWidgetData => (IWidgetDataPopup*)
	// if ( fWidgetID == kWidgetRadio )			fpWidgetData => (IWidgetDataPopup*)
	// if ( fWidgetID == kWidgetBoundPopup )	fpWidgetData => (IWidgetBound*)
	// if ( fWidgetID == kWidgetBoundOffset )	fpWidgetData => (IWidgetBound*)
	// if ( fWidgetID == kWidgetLayersPopup )	fpWidgetData => (IWidgetLayerDataPopup*)
	// else										fpWidgetData => (IWidgetData*)
	IWidgetData*	fpWidgetData;

	// data support
	TXString		fRecordName;
	Sint16			fRecordParamIndex;

					SWidgetDefinition() {
						fWidgetID = 0; fWidgedVisible = fWidgetEnabled = true;
						fpWidgetData = NULL;
						fRecordParamIndex = 0;
						fWidgetRed	= false;
						fWidgetRotatedCoord = false;
						fWidgetIndentLevel = 0;
						fReadOnly = false;
						fEnergyDataType = EEnergyDataType::None;
						fByStyle = false;
					}
};

//----------------------------------------------------------
class IWidgetsProvider
// Widgets provider interface for parametric objects
{
public:
	virtual						~IWidgetsProvider()		{}
	virtual bool				IsUsed(bool bCheck) = 0;
	virtual TComponentTypeID	GetComponentTypeID() const = 0;
	virtual size_t				GetWidgetsCount() const = 0;
	virtual	SWidgetDefinition&	GetWidgetAt(size_t index) = 0;
	virtual	SWidgetDefinition*	GetWidgetByID(Sint32 widgetID) = 0;
	virtual	SWidgetDefinition&	GetWidgetByIDSafe(Sint32 widgetID) = 0;
	virtual	SWidgetDefinition*	GetWidgetByID(const char* widgetID) = 0;
	virtual	SWidgetDefinition&	GetWidgetByIDSafe(const char* widgetID) = 0;
};

//----------------------------------------------------------
class IContextMenuProvider
// Context menu provider interface for parametric objects
{
public:
	virtual			~IContextMenuProvider() {};
	virtual Sint16	AddItemSeparator() = 0;
	virtual Sint16	AddItem(const TXString& text) = 0;
	virtual bool	AddItem(const TXString& text, IContextMenuProvider*& outSubMenuProvider) = 0;
	virtual Sint16	AddItem(const TXString& text, const char* szContextualHelpID, const TXString& helpString = "" ) = 0;
	virtual bool	AddItem(const TXString& text, const char* szContextualHelpID, IContextMenuProvider*& outSubMenuProvider) = 0;
	
	virtual void	EnableItem(Sint16 itemID, bool bEnable) = 0;
	virtual void	CheckItem(Sint16 itemID, bool bChecked) = 0;
};


#define GS_DEFINE_OLD_XPROP_NAMES 1 // remove for VW 12
 #if GS_DEFINE_OLD_XPROP_NAMES
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////		Old Names			////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////
//	Object Properties
const ObjectPropID kObjectEditGroupPropertyID = kObjXPropEditGroup;		// Object has non default "Enter Group" behavior	
const ObjectPropID kObjectSpecialEditPropertyID = kObjXPropSpecialEdit;	// object handles ParametricSpecialEditMessage::kAction event
const ObjectPropID kObjectPreferencePropertyID = kObjXPropPreference;		// Handles preferences dialog

const ObjectPropID kDirectModeling = kObjXPropDirectModeling;		// Under Development: Handles 3D Resahpe tool events
const ObjectPropID kAttributeTool = kObjXPropAttributeTool;		// Under Development: Handles Attribute tool events

const ObjectPropID kObjectHasUIOverrideID = kObjXPropHasUIOverride;			// Object adds widgets to Object Info Palette

const ObjectPropID kLastObjectPropertyID = kObjectHasUIOverrideID;		// last property ID
/////////////////////////////


/////////////////////////////
// OLD NAME:  kObjectEditGroupPropertyID property values:
const char kEditGroupDefaultProperty 	= kObjXPropEditGroupDefault;
const char kEditGroupProfile 			= kObjXPropEditGroupProfile;
const char kEditGroupPath 				= kObjXPropEditGroupPath;
const char kEditGroupCustom 			= kObjXPropEditGroupCustom;
/////////////////////////////


/////////////////////////////
// OLD NAMES: kObjectSpecialEditPropertyID property values:
const char kSpecialEditDefaultProperty 	= kObjXPropSpecialEditDefault;
const char kSpecialEditCustom 			= kObjXPropSpecialEditCustom;
const char kSpecialEditProperties 		= kObjXPropSpecialEditProperties;
const char kSpecialEditReshape 			= kObjXPropSpecialEditReshape;
/////////////////////////////



/////////////////////////////



// 	Current VectorScript Regeneration CodeRefID.  
//	Used by SetObjectProperty VectorScript implementation 
const CodeRefID kCurrentRegenObjectID = -1;



/////////////////////////////
//	Old XProp Names Tool Properties
const ToolPropID kToolSelectionChangeEventPropertyID = kToolXPropSelectionChange;	// tool wants selection change events.
const ToolPropID kToolEnterKeyEventPropertyID = kToolXPropSendModeBarEventOnEnterEscKeys;			// not supported
const ToolPropID kToolWantsMoveSelection2DEventsID = kToolXPropWantsMoveSelection2D;		// tool wants ToolMoveSel2DMessage::kAction event.
/////////////////////////////


#endif


//
//
//		END NNA DECLARATION SPACE:
//
//
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
