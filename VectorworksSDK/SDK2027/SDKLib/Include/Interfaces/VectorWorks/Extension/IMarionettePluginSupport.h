//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------------------------------------------
		// {95541C75-CDF6-43E8-8403-B80462D91B12}
		static const VWIID IID_MarionettePluginSupport = { 0x7baf1b, 0x3bf, 0x497c, { 0xa0, 0x8c, 0xdd, 0x1d, 0x3d, 0x20, 0x4e, 0xc6 } };
		/**	Provides access to specific functionality implemented in Marionette project (and not available in Core)
		*	Communication is achieved through Marionette::Interfaces::CMarionettePluginSupport
		*/

		class DYNAMIC_ATTRIBUTE IMarionettePluginSupport : public IVWUnknown
		{
		public:
			// --------------------------------------------------------------------------------------------------------
			virtual void			VCOM_CALLTYPE	RunMarionetteFromRM(MCObjectHandle hMarionetteObj) = 0;		
		};

		// ------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IMarionettePluginSupport> IMarionettePluginSupportPtr;
	}
}
