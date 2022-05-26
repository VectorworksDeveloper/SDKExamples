//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {DDBBCF43-0EC4-470F-980F-75292D75C0E9}
		static const TSinkIID IID_ProviderSaveCleaner = { 0xddbbcf43, 0xec4, 0x470f, { 0x98, 0xf, 0x75, 0x29, 0x2d, 0x75, 0xc0, 0xe9 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderSaveCleaner : public IEventSink
		{
		public:
			virtual void VCOM_CALLTYPE		PreSave(MCObjectHandle h) = 0;	// the user could remove child objects of h from drawing before the save opeartion. Must not remove h!
			virtual void VCOM_CALLTYPE		PostSave(MCObjectHandle h) = 0;	// the user would restore removed objects after the save operation
			
			virtual bool VCOM_CALLTYPE		ReverseTranslate2014(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2014
			virtual bool VCOM_CALLTYPE		ReverseTranslate2015(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2015
			virtual bool VCOM_CALLTYPE		ReverseTranslate2016(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2016
			virtual bool VCOM_CALLTYPE		ReverseTranslate2017(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2017
			virtual bool VCOM_CALLTYPE		ReverseTranslate2018(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2018
			virtual bool VCOM_CALLTYPE		ReverseTranslate2019(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2019
			virtual bool VCOM_CALLTYPE		ReverseTranslate2020(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2020
			virtual bool VCOM_CALLTYPE		ReverseTranslate2021(MCObjectHandle h) = 0;	// return true if this object is to be preserved by reverse translate to 2021

			virtual void VCOM_CALLTYPE		PreReverseTranslate(MCObjectHandle h) {}	// the user could remove child objects of h before reverse translation. Must not remove h!
			virtual void VCOM_CALLTYPE		PostReverseTranslate(MCObjectHandle h) {}	// the user would restore removed objects after reverse translation
		};
	}
}


