//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace MigrationManager
	{
		//===============================================================================
		// Migration Manager Support
		static const VWIID IID_MigrationManagerSupport = { 0x9b9b6bfd, 0x79c, 0x476a, { 0x93, 0x80, 0xcc, 0x54, 0xfa, 0xeb, 0x2d, 0xfc } };

		class DYNAMIC_ATTRIBUTE IMigrationManagerSupport : public IVWSingletonUnknown
		{
		public:
			// Third-party developer should use this function to register the plugin to Migration Manager.
			virtual VCOMError AddCallbackAndDisplayName(const VWIID& callbackIID, const TXString& displayName) = 0;
			
			// The following functions are used by Migration Manager.
			virtual VCOMError GetDisplayNameArray(TXStringArray& displayNameArray) = 0;
			virtual VCOMError Migrate(const TXString& displayName, IFolderIdentifier* pInputFolderID, IFolderIdentifier* pOutputFolderID) = 0;
		};

		typedef VCOMPtr<IMigrationManagerSupport> IMigrationManagerSupportPtr;

		//===============================================================================
		// Migration Manager Callback
		static const VWIID IID_MigrationManagerCallback = { 0x6b5e224b, 0xf736, 0x40f4, { 0x9e, 0x68, 0x1f, 0x64, 0x52, 0x25, 0x41, 0x78 } };
		
		class DYNAMIC_ATTRIBUTE IMigrationManagerCallback : public IVWUnknown
		{
		public:
			// Third-party developer should use this function to migrate plugin's data.
			virtual VCOMError OnMigrate(IFolderIdentifier* pInputFolderID, IFolderIdentifier* pOutputFolderID) = 0;

		};
		
		typedef VCOMPtr<IMigrationManagerCallback> IMigrationManagerCallbackPtr;
	}
}
