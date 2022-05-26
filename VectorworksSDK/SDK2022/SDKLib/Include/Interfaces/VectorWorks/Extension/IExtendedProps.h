//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// object itself component ID
		const TComponentTypeID		kObjectRootComponentTypeID		= (TComponentTypeID) -1;

		// ----------------------------------------------------------------------------------------------------
		enum EComponentTypeProp {
			eComponentTypeProp_HasFillStyle,
			eComponentTypeProp_HasPenStyle,
			eComponentTypeProp_HasMarkerBeginning,
			eComponentTypeProp_HasMarkerEnding,
			eComponentTypeProp_HasTextStyle,
			eComponentTypeProp_HasTexture,
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWidgetsEditProvider : public IWidgetsProvider
		{
		public:
			virtual void	AddWidget(Sint32 widgetID, const TXString& paramName) = 0;
			virtual void	AddWidget(Sint32 widgetID, const TXString& paramName, const TXString& localizedName) = 0;
			virtual void	AddWidget(Sint32 widgetID, EWidgetType widgetType, const TXString& paramName, const TXString& localizedName) = 0;
			virtual void	AddWidget(Sint32 widgetID, EWidgetType widgetType, const TXString& localizedName) = 0;

			virtual void	InsertWidget(size_t beforeIndex, Sint32 widgetID, const TXString& paramName) = 0;
			virtual void	InsertWidget(size_t beforeIndex, Sint32 widgetID, const TXString& paramName, const TXString& localizedName) = 0;
			virtual void	InsertWidget(size_t beforeIndex, Sint32 widgetID, EWidgetType widgetType, const TXString& paramName, const TXString& localizedName) = 0;
			virtual void	InsertWidget(size_t beforeIndex, Sint32 widgetID, EWidgetType widgetType, const TXString& localizedName) = 0;

			virtual bool	SetWidget(size_t index, Sint32 widgetID, EWidgetType widgetType, const TXString& localizedName) = 0;

			virtual void	ClearWidgets() = 0;
			virtual bool	DeleteWidget(size_t index) = 0;

			virtual bool	FindWidgetIndex(Sint32 widgetID, size_t& outIndex) const = 0;

			virtual Sint32	GetWidgetIDByName(const char* widgetiD) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		struct SLoadData
		{

			enum class ELoadType
			{
				Point,
				Destributed
			};

			SLoadData()
				: fLoadType( ELoadType::Point )
				, fInclude( true )
				, fWeight( 0 )
				, fHandlePositionTransform( false )
				, fShowLoadInfoWidget( true )
				, fEnableWeightWidget( true )
			{}

			SLoadData( SLoadData::ELoadType type, const TXString & groupName, TXString loadObjectID, double weight )
			{
				fLoadType		= type;
				fInclude		= true;
				fGroupName		= groupName;
				fLoadObjectUID	= loadObjectID;
				fWeight			= weight;
				fHandlePositionTransform	= false;
				fShowLoadInfoWidget			= true;
				fEnableWeightWidget			= true;
			}

			ELoadType	fLoadType;
			bool		fInclude;
			TXString	fGroupName;
			TXString	fLoadObjectUID;
			TXString	fLoadUIDParamName;			// if not empty, then the loadUID is stored in the given parameter
			TXString	fLoadObjectName;
			TXString	fLoadNameParamName;			// if not empty, then the name is stored in the given parameter
			double		fWeight;
			TXString	fWeightParamName;			// if not empty, then the weight is stored in the given parameter
			TXString	fTotalDistWeightParamName;	// if not empty, the value will be shown in the OIP as total weight of the distributed load.
			bool		fHandlePositionTransform;	// if true, the object handles position move or rotate itself
			// Vw2020
			bool		fShowLoadInfoWidget;		// if true, load information group will be diplayed in the OIP
			// VW2021
			bool		fEnableWeightWidget;		// if false, Weight widgets in the load information group will be disabled
			// VW2022
			TXString	fPositionParamName;			// if not empty, then the position name is shown in the given parameter
		};

		// ----------------------------------------------------------------------------------------------------
		// {2257EB99-E08E-480c-88A7-D66B5E2FB386}
		static const VWIID IID_ExtendedProps = { 0x2257eb99, 0xe08e, 0x480c, { 0x88, 0xa7, 0xd6, 0x6b, 0x5e, 0x2f, 0xb3, 0x86 } };

		class DYNAMIC_ATTRIBUTE IExtendedProps : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	GetCodeRefID(MCObjectHandle hObject, CodeRefID& outCodeRefID) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetCodeRefID(TParametricFileIndex fileIndex, CodeRefID& outCodeRefID) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileIndex(CodeRefID codeRef, TParametricFileIndex& outFileIndex) = 0;

			virtual VCOMError VCOM_CALLTYPE	InitObjectProperties(CodeRefID codeRef) = 0;
			virtual VCOMError VCOM_CALLTYPE	ClearAllObjectProperties() = 0;
			virtual VCOMError VCOM_CALLTYPE	ClearObjectProperties(CodeRefID codeRefID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, bool value) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, Sint8 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, double value) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, Sint8& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, double& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(MCObjectHandle hObject, ObjectPropID propID, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(MCObjectHandle hObject, ObjectPropID propID, Sint8& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(MCObjectHandle hObject, ObjectPropID propID, double& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetTypeProperty(Sint16 objType, ObjectPropID propID, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetTypeProperty(Sint16 objType, ObjectPropID propID, Sint8& outValue) = 0;

			virtual VCOMError VCOM_CALLTYPE	InitToolProperties(CodeRefID codeRef) = 0;
			virtual VCOMError VCOM_CALLTYPE	ClearAllToolProperties() = 0;
			virtual VCOMError VCOM_CALLTYPE	ClearToolProperties(CodeRefID codeRefID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetToolProperty(CodeRefID codeRefID, ToolPropID propID, bool value) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetToolProperty(CodeRefID codeRefID, ToolPropID propID, Sint8 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetToolProperty(CodeRefID codeRefID, ToolPropID propID, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetToolProperty(CodeRefID codeRefID, ToolPropID propID, Sint8& outValue) = 0;

			virtual VCOMError VCOM_CALLTYPE	HandleObjectEvent(MCObjectHandle hObject, ParametricMessage& message, Sint32& callResult) = 0;
			virtual VCOMError VCOM_CALLTYPE	HandleObjectEvent(CodeRefID codeRefID, ParametricMessage& message, Sint32& callResult) = 0;

			virtual VCOMError VCOM_CALLTYPE	AddObjComponentType(CodeRefID inCodeRefID, TComponentTypeID typeID, const TXString& localizedName) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeName(CodeRefID inCodeRefID, TComponentTypeID typeID, TXString& outLocalizedName) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeProps(CodeRefID inCodeRefID, TComponentTypeID typeID, EComponentTypeProp propID, bool value) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefColors(CodeRefID inCodeRefID, TComponentTypeID typeID, const ObjectColorType& style, bool bPenByClass, bool bFilLByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefMarker(CodeRefID inCodeRefID, TComponentTypeID typeID, bool bBeginingMarker, const SMarkerStyle& style, bool bVisible, bool bByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefTextStyle(CodeRefID inCodeRefID, TComponentTypeID typeID, const STextStyle& style, bool bByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefFillPat(CodeRefID inCodeRefID, TComponentTypeID typeID, InternalIndex objIndex, bool bByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefPenPat(CodeRefID inCodeRefID, TComponentTypeID typeID, Sint16 penPat, bool bByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefLineWeight(CodeRefID inCodeRefID, TComponentTypeID typeID, Sint16 lineWeight, bool bByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetObjComponentTypeDefTexture(CodeRefID inCodeRefID, TComponentTypeID typeID, InternalIndex objIndex, bool bByClass) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeProps(CodeRefID inCodeRefID, TComponentTypeID typeID, EComponentTypeProp propID, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefColors(CodeRefID inCodeRefID, TComponentTypeID typeID, ObjectColorType& outStyle, bool& bOutPenByClass, bool& bOutFilLByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefMarker(CodeRefID inCodeRefID, TComponentTypeID typeID, bool bBeginingMarker, SMarkerStyle& outStyle, bool& bOutVisible, bool& bOutByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefTextStyle(CodeRefID inCodeRefID, TComponentTypeID typeID, STextStyle& outStyle, bool& bOutByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefFillPat(CodeRefID inCodeRefID, TComponentTypeID typeID, InternalIndex& outObjIndex, bool& bOutByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefPenPat(CodeRefID inCodeRefID, TComponentTypeID typeID, Sint16* outPenPat, bool& bOutByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefLineWeight(CodeRefID inCodeRefID, TComponentTypeID typeID, Sint16& outLineWeight, bool& bOutByClass) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeDefTexture(CodeRefID inCodeRefID, TComponentTypeID typeID, InternalIndex& outObjIndex, bool& bOutByClass) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeWidgets(CodeRefID inCodeRefID, TComponentTypeID typeID, IWidgetsProvider*& outWidgetProvider) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjComponentTypeWidgets(CodeRefID inCodeRefID, TComponentTypeID typeID, IWidgetsEditProvider*& outWidgetEditProvider) = 0;

			virtual IExtension* VCOM_CALLTYPE	GetExtension(TParametricFileIndex fileIndex) = 0;

			virtual Sint32 VCOM_CALLTYPE		DispatchScriptToolMessage(TParametricFileIndex fileIndex, ToolMessage& message) = 0;

		// VW2012
		public:
			virtual VCOMError	VCOM_CALLTYPE	GetFileIndexByName(const TXString& universalName, TParametricFileIndex& outFileIndex) = 0;
			virtual IExtension* VCOM_CALLTYPE	GetExtensionByName(const TXString& universalName) = 0;

		// VW2016
		public:
			virtual IExtension* VCOM_CALLTYPE	GetExtension(MCObjectHandle hParametric) = 0;

			// this function is for internal use, and is being called before the script dispatches a dialog event
			virtual void VCOM_CALLTYPE			ScriptPreDispatchDialogEvent(Sint32 dialogID, Sint32& itemHit, void* data) = 0;

		// VW2017
		public:
			virtual VCOMError VCOM_CALLTYPE	GetRecordFormatTypeWidgets(const TXString& name, IWidgetsProvider*& outWidgetProvider) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetRecordFormatTypeWidgets(const TXString& name, IWidgetsEditProvider*& outWidgetEditProvider) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(CodeRefID codeRefID, ObjectPropID propID, TXString& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetObjectProperty(MCObjectHandle hObject, ObjectPropID propID, TXString& outValue) = 0;

		// VW2018
		public:
			virtual void					VCOM_CALLTYPE RegisterExtensionEventSink(const TXString& universalName, TInternalID internalID, VWIID sinkIID, TSinkIID sinkGroupIID) = 0; 
			virtual VCOMSinkPtr<IEventSink>	VCOM_CALLTYPE QueryExtensionEventSink(MCObjectHandle hParametric, const TSinkIID& sinkGroupIID) = 0; 


			virtual void		VCOM_CALLTYPE AddObjectLoadData(CodeRefID codeRefID, const SLoadData& data) = 0;
			virtual size_t		VCOM_CALLTYPE GetObjectLoadDataCount(CodeRefID codeRefID) = 0;
			virtual bool		VCOM_CALLTYPE GetObjectLoadData(CodeRefID codeRefID, size_t at, SLoadData& outData) = 0;

			virtual VCOMError	VCOM_CALLTYPE	ReadSheetLayerCacheObjectFromFile(const TXString& fileFullPath, TXStringArray& outArrSheetLayerNames) = 0;
			virtual bool		VCOM_CALLTYPE	OpenOrActivateFile(const TXString& fileFullPath) = 0;
			virtual Sint16		VCOM_CALLTYPE	GetActiveDocumentIndex() = 0;
			virtual void		VCOM_CALLTYPE	ActivateDocument(Sint16 docIndex) = 0;

		// VW2019
		public:
			virtual VCOMError	VCOM_CALLTYPE	ReadLayerInfoFromFile(const TXString& fileFullPath, TXStringArray& outArrLayerNames, TXStringArray& outArrSheetTitles) = 0;

		// VW2020
		public:
			virtual VCOMSinkPtr<IEventSink>	VCOM_CALLTYPE QueryExtensionEventSink(const TXString& universalName, const TSinkIID& sinkGroupIID) = 0; 
		};

		typedef VCOMPtr<IExtendedProps>		IExtendedPropsPtr;
	}
}


