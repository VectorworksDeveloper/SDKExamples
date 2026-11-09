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
		// {F5380823-AE5A-4AD9-A56C-05979A598892}
		static const Extension::TSinkIID IID_ProviderMaterialValues = { 0xf5380823, 0xae5a, 0x4ad9, { 0xa5, 0x6c, 0x5, 0x97, 0x9a, 0x59, 0x88, 0x92 } };

		class DYNAMIC_ATTRIBUTE IProviderMaterialValues : public Extension::IEventSink
		{
		public:
			// GENERAL NOTE: return 'true' from a provider callback function if it has been implemented and is expected to return a value.

			// NOTE: return the value in outValue in the specified metric units (WorldArea).
			virtual bool	VCOM_CALLTYPE CalculateArea(MCObjectHandle hObject, const TXString& materialName, WorldArea& outValue) = 0;

			// NOTE: return the value in outValue in the specified metric units (WorldVolume).
			virtual bool	VCOM_CALLTYPE CalculateVolume(MCObjectHandle hObject, const TXString& materialName, WorldVolume& outValue) = 0;
		};
	}
}