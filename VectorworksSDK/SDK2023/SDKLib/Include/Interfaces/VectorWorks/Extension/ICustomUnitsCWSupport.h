//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
    
        
		// --------------------------------------------------------------------------------------------------
		// {00254a45-9999-4c04-9432-2fbab44cc305}
		static const VWIID IID_VCOMCustomUnitsCW = {  0xab8e9000, 0xcd39, 0x438a, {0xaa, 0xbc, 0xf0, 0x4b, 0x42, 0x12, 0x0f, 0x36} };
        
        /****************************************
         
         The implementation of this class contains a global variable that contains all custom units settings of ComputerWorks plug-ins.
         
         Plug-Ins can access these variables directly via this class and don't have to load them from data tag or settings file unless
         
         data tag or settings file have actually changed.
         
         This class keeps track about these changes (i.e., if a settings file was saved/loaded/written in data tag...).
         
         
         
        ***************************************/
        

		class ICustomUnitsCWSupport : public IVWSingletonUnknown
		{
		public:
			//
			
            
            
            virtual Boolean VCOM_CALLTYPE GetCWCustomUnitsArray( // Gets pointer to global custom units array. If necessary, the required settings file / data tag is loaded into global variable.
                                                          Sint16 VersionNumber, /* Version number of data type. Needs to be passed so callee can detect if caller and callee are compatible */
                                                          void **CustomUnitsArray /* Returns address of variable that contains custom unit */
            ) = 0; // Returns false if error occurred, true otherwise
            
            virtual Boolean VCOM_CALLTYPE SetCWCustomUnitsArray( // Sets  global variable to passed CustomUnitsArray and writes it to Settings file resp. data tag.
                                                          Sint16 VersionNumber, /* Version number of data type. Needs to be passed so callee can detect if caller and callee are compatible */
                                                          void *CustomUnitsArray /* Address of variable that contains custom unit */
            ) = 0; // Returns false if error occurred, true otherwise

            virtual void VCOM_CALLTYPE Debug(const char *s) = 0; // For test purposes. Implementation function is empty in release mode
			
		};
	}
}
