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
		// {74253F0F-AC9A-4411-9BC1-D388D4AD97D0}
		static const VWGroupID GROUPID_ExtensionMenu = { 0x74253f0f, 0xac9a, 0x4411, { 0x9b, 0xc1, 0xd3, 0x88, 0xd4, 0xad, 0x97, 0xd0 } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for menu extension application
		class DYNAMIC_ATTRIBUTE IExtensionMenu : public IExtension
		{
		public:
			virtual const TXString& VCOM_CALLTYPE	GetTitle() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetCategory() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetHelpText() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetOverrideHelpID(size_t chunkIndex = size_t(-1)) = 0;
			virtual	void VCOM_CALLTYPE				GetNeedsFlags(Uint16& outNeeds, Uint16& outNeedsNot) = 0;
			virtual	void VCOM_CALLTYPE				GetVersionInfo(Sint16& outCreated, Sint16& outModified, Sint16& outRetired) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {2BAD0312-F3C4-469c-9FF5-5A966FFEDD3B}
		static const TSinkIID IID_MenuChunkProvider					= { 0x2bad0312, 0xf3c4, 0x469c, { 0x9f, 0xf5, 0x5a, 0x96, 0x6f, 0xfe, 0xdd, 0x3b } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IMenuChunkProvider : public IEventSink
		{
		public:
			virtual size_t VCOM_CALLTYPE			GetItemsCount() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetItemTitle(size_t index) = 0;
			virtual const TXString& VCOM_CALLTYPE	GetOverrideHelpID(size_t index) = 0;
  		};

		// ----------------------------------------------------------------------------------------------------
		enum EMenuChunkType
		{
			eMenuChunkType_Regular,
			eMenuChunkType_Dynamic,
			eMenuChunkType_DynamicVariable
		};

		// ----------------------------------------------------------------------------------------------------
		// {7D426B60-AD19-443D-92D4-4C80740533D6}
		static const TSinkIID IID_MenuChunk2Provider			= { 0x7d426b60, 0xad19, 0x443d, { 0x92, 0xd4, 0x4c, 0x80, 0x74, 0x5, 0x33, 0xd6 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IMenuChunk2Provider : public IMenuChunkProvider
		{
		public:
			virtual EMenuChunkType VCOM_CALLTYPE	GetType() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetItemHelp(size_t index) = 0;
			virtual bool VCOM_CALLTYPE				IsChunkDirty() = 0;
			virtual void VCOM_CALLTYPE				ClearChunkDirty() = 0;
  		};
	}
}
