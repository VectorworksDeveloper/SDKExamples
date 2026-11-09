//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		class DYNAMIC_ATTRIBUTE ISelectSimilarContext
		{
		public:
			virtual			~ISelectSimilarContext() {}

			virtual void	AddValueBool(bool value, EFieldStyle style = kFieldBoolean) = 0;
			virtual void	AddValueReal(double value, EFieldStyle style = kFieldReal) = 0;
			virtual void	AddValueLong(Sint32 value, EFieldStyle style = kFieldLongInt) = 0;
			virtual void	AddValueString(const TXString& value, EFieldStyle style = kFieldText) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		// {DF7F5047-9C30-460A-A29C-13020B074D68}
		static const VWIID IID_SelectSimilarProvider = { 0xdf7f5047, 0x9c30, 0x460a, { 0xa2, 0x9c, 0x13, 0x2, 0xb, 0x7, 0x4d, 0x68 } };

		class DYNAMIC_ATTRIBUTE ISelectSimilarProvider : public IEventSink
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE    ProcessObject(MCObjectHandle formatOrRecord, ISelectSimilarContext* context) = 0;
			virtual VCOMError	VCOM_CALLTYPE    GetSubType(MCObjectHandle hObject, TXString& outSubType) = 0;
		};
	}
}
