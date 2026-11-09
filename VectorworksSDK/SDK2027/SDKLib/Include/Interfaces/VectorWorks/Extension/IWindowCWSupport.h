//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
    
        const Sint16 kCWWinDoorAttachDataParameterVersion = 3; // Current version of Data type
    
        class CWWinDoorAttachDataParameter {
        
            public:
            
              CWWinDoorAttachDataParameter() {
                 m_SymbolName.Clear();
                 m_ErrorMessage.Clear();
                 m_VersionNumber = kCWWinDoorAttachDataParameterVersion;
                 m_SillHeight = 0.0;
              }
            
              Sint16 GetVersionNumber() {return m_VersionNumber;}
            
            protected:
            
             // Special:
            
             Sint16 m_VersionNumber; // Used by callee to check for incompatibilities
            
            public:
            
             // Input Parameter: (Calling routine may set all input parameters to meaningful values or leave them empty)
            
              TXString m_SymbolName; // Name of symbol that is used. Leave empty if PIO draws subobjects by itself.
            
              WorldCoord m_SillHeight; // Z-Distance from layer elevation to bottom edge of "hole in wall" for Window.
                                       // Value is in WorldCoords
                                       // Used by CW Window. Not used by CW Door.
            
             // Output:
            
             TXString m_ErrorMessage; // Empty if everything was OK
            
            
            
        
        }; // CWWinDoorAttachDataParameter
    
		// --------------------------------------------------------------------------------------------------
		// {00254a45-9999-4c04-9432-2fbab44cc305}
		static const VWIID IID_VCOMWindowCW = {  0x00254a45, 0x9999, 0x4c04, {0x94, 0x32, 0x2f, 0xba, 0xb4, 0x4c, 0xc3, 0x05} };
        
        
        

		class IWindowCWSupport : public IVWSingletonUnknown
		{
		public:
			//
			virtual void VCOM_CALLTYPE AttachData(MCObjectHandle theWinDoor, CWWinDoorAttachDataParameter *theParameter) = 0;
                 // theParameter must be a valid pointer to a variable of type CWWinDoorAttachDataParameter. AttachData will not release or destroy it.
                 // !!! Call this after the WinDoor was created.
                 // !!! Call ResetObject (theWinDoor)  after AttachData to force a regeneration.
            
            
            virtual Boolean VCOM_CALLTYPE IsWindowCWLicensed() = 0;
               // returns true if current serial number and dongle allows CW Windows.
               // !!!! This will also return true for whitelisted serial numbers
               // !!! so you will need to test this also with non-whitelisted numbers !!!
	
			
		};
	}
}
