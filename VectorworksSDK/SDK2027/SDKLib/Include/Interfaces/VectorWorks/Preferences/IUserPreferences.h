//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Preferences
	{
		// ----------------------------------------------------------------------------------------------------
		// {16104BD9-9056-4CCE-B1AA-45387197D6D2}
		static const VWIID IID_UserPreferences =  { 0x16104bd9, 0x9056, 0x4cce, { 0xb1, 0xaa, 0x45, 0x38, 0x71, 0x97, 0xd6, 0xd2 } };

		class DYNAMIC_ATTRIBUTE IUserPreferences : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Read( const IFileIdentifierPtr& /*fileId*/ ) = 0;
			virtual VCOMError VCOM_CALLTYPE WriteToDefaultLocation() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IUserPreferences>		IUserPreferencesPtr;
	}
}