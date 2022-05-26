//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		// {2AA586C5-35E4-41be-9646-F39A13DC5A55}
		static const VWIID IID_DBContext = { 0x2aa586c5, 0x35e4, 0x41be, { 0x96, 0x46, 0xf3, 0x9a, 0x13, 0xdc, 0x5a, 0x55 } };

		class DYNAMIC_ATTRIBUTE IDBErrorContext : public IVWUnknown
		{
		public:
			virtual bool		VCOM_CALLTYPE	HasErrors() = 0;
			virtual size_t		VCOM_CALLTYPE	GetNumErrors() = 0;

			virtual VCOMError	VCOM_CALLTYPE	ShowErrors() = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBErrorContext>		IDBErrorContextPtr;
	}
}