//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// {D71FC731-D2EB-4538-B8EA-326EC454BC16}
		static const VWIID IID_IImportArMeasure = { 0xd71fc731, 0xd2eb, 0x4538, { 0xb8, 0xea, 0x32, 0x6e, 0xc4, 0x54, 0xbc, 0x16 } };

		class DYNAMIC_ATTRIBUTE IImportArMeasure : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifierPtr fileID) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportArMeasure>		IImportArMeasurePtr;
	}
}