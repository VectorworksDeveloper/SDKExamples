//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {0D93C85B-B4B2-4375-A8D5-821B7608D75A}
		static const TSinkIID IID_WSFunctionCallEventSink = { 0xd93c85b, 0xb4b2, 0x4375, { 0xa8, 0xd5, 0x82, 0x1b, 0x76, 0x8, 0xd7, 0x5a } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWSFunctionCallEventSink : public IEventSink
		{
		public:
			virtual bool VCOM_CALLTYPE Execute(EQTOFunction function, const TXString& optionName, MCObjectHandle obj, MCObjectHandle subpart, const std::vector<VWVariant>& args, VWVariant& outResul, bool isEditing) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		struct SIExtensionWSFunctionDefDesc
		{
			TXString		fDefinition;	// name and parameters
			TXString		fDescription;
		};

		// ----------------------------------------------------------------------------------------------------
		// {B9962D19-BDD5-4979-A101-6B5F8A1727AC}
		static const VWGroupID GROUPID_ExtensionWSFunctionOptions = { 0xb9962d19, 0xbdd5, 0x4979, { 0xa1, 0x1, 0x6b, 0x5f, 0x8a, 0x17, 0x27, 0xac } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for VectorSrcipt functions provider extension application
		class DYNAMIC_ATTRIBUTE IExtensionWSFunctionOptions : public IExtension
		{
		public:
			virtual size_t			VCOM_CALLTYPE	GetFunctionsCount() = 0;
			virtual bool			VCOM_CALLTYPE	GetFunctionOption(size_t funcIndex, EQTOFunction& outFunction, TXString& outUnivName /*lower case*/, bool& outEditable) = 0;
			virtual bool			VCOM_CALLTYPE	GetFunctionOptionDesc(size_t funcIndex,  TXString& outCategory, SIExtensionWSFunctionDefDesc& outFuncDef, SIExtensionWSFunctionDefDesc& outFuncDBDef, TXString& outImageSpec, TXString& outExample) = 0;
			virtual size_t			VCOM_CALLTYPE	GetFunctionOptionObjsCount(size_t funcIndex) = 0;
			virtual bool			VCOM_CALLTYPE	GetFunctionOptionObj(size_t funcIndex, size_t objIndex, short& outTdType, TInternalID& outInternalIndex, TXString& outUnivName) = 0;
		};
	}
}