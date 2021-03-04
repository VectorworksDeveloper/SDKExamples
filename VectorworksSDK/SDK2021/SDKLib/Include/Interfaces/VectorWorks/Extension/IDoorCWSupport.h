//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
    
        // Include "IWindowCWSupport.h" BEFORE including this file.
        
    
		// --------------------------------------------------------------------------------------------------
		// {f2a48d47-03dd-4251-a2a3-27e753adc2a7}
		static const VWIID IID_VCOMDoorCW = {  0xf2a48d47, 0x03dd, 0x4251, {0xa2, 0xa3, 0x27, 0xe7, 0x53, 0xad, 0xc2, 0xa7} };

		class IDoorCWSupport : public IVWSingletonUnknown
		{
		public:
			//
			virtual void VCOM_CALLTYPE AttachData(MCObjectHandle theWinDoor, CWWinDoorAttachDataParameter *theParameter) = 0;
                 // CWWinDoorAttachDataParameter is declared in IWindowCWSupport.h which MUST be included before this file.
                 // theParameter must be a valid pointer to a variable of type CWWinDoorAttachDataParameter. AttachData will not release or destroy it.
                 // !!! Call this after the WinDoor was created.
                 // !!! Call ResetObject (theWinDoor)  after AttachData to force a regeneration.
            
            virtual Boolean VCOM_CALLTYPE IsDoorCWLicensed() = 0;
               // returns true if current serial number and attached dongle allow CW Doors.
               // !!!! This will also return true for whitelisted serial numbers
              
	
		
		};
	}
}
