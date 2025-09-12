//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	// ---------------------------------------------------------------------------------------------------
	// {572198f2-636c-4e3a-b45d-45fa556eed60}
	static const VWIID IID_SkipChangesContext = { 0x572198f2, 0x636c, 0x4e3a, {0xb4, 0x5d, 0x45, 0xfa, 0x55, 0x6e, 0xed, 0x60}};

	class DYNAMIC_ATTRIBUTE ISkipChangesContext : public IVWUnknown
	{
	public:
		//
		// Setup() is used to cease tracking of the passed in MCObjectHandle for the Change Tracking System.  After calling Setup(),
		// the passed in MCObjectHandle will not be processed by the Change Tracking System's observers (Project Sharing). To restore
		// tracking to the passed in MCObjectHandle, call the Cleanup() method.
		//
		virtual void Setup(MCObjectHandle h) = 0;
		
		//
		// Cleanup() is used to restore tracking of the passed in MCObjectHandle for the Change Tracking System.  After calling Cleanup(),
		// the MCObjectHandle that was used previously in the Setup() method, will now begin to be processed by the Change Tracking
		// System's observers (Project Sharing).
		//
		virtual void Cleanup() = 0;
	};

	// ---------------------------------------------------------------------------------------------------
	typedef VCOMPtr<ISkipChangesContext> ISkipChangesContextPtr;
}
