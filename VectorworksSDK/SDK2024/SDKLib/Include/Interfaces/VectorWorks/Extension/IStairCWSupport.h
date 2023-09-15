//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once



// ************************************************************

// ---------  String constants for IFC Export  --------------

// https://jira.vectorworks.net/browse/VB-179759

// Name of VW internal Pset that holds names of building materials:

#define kNameOfVWMaterialPset "Material"

// Material name that is exported if stair component has no building material:

#define kNameOfIFCComponentDefaultMaterial "Default"





// !!!!!!!!!!!!!

/*

As we need to export 10 different materials for a stair flight, but  Pset "Material" contains only 8 properties (Component 1-8),

 some properties
 
 - kStairMaterialPropertyRisersFrontBackFace (contains material names for front face and back face)
 - kStairMaterialPropertyTreadsTopBottom (contains material names for top and bottom face)
 
 contain the names of building materials of two stair components.
 
 if either have the same building material (i.e. if front face and back face material of risers are identical), the property contains the name of thius material.
 
 If the material names for these two amterials are different,
 
 the names of these components are written into the same property, separated by
 
 kStairMaterialSeparator (see also below)
 
 This was discussed with Misho Rizov in https://jira.vectorworks.net/browse/VB-179759
 
*/

#define kStairMaterialSeparator  L"\u2980"  /* Separator between material names - see above. Unicode 2980: Triple Vertical Bar Delimiter. This character should never appear in any material name */

// -------- PSet Properties used for Materials of Stair flights (and Landings/Slabs)

#define kStairMaterialPropertyStairStructureTopFace "Component 1"
#define kStairMaterialPropertyStairStructureBottomFace "Component 2"
#define kStairMaterialPropertyStairStructureFrontFace "Component 3"
#define kStairMaterialPropertyStairStructureEdges "Component 4"

#define kStairMaterialPropertyRisersFrontBackFace "Component 5" /* Special handling (2 materials) - see above. String is <MatOfFrontFace kStairMaterialSeparator MatOfBackFace> if materials are different */
#define kStairMaterialPropertyRisersEdges "Component 6"

#define kStairMaterialPropertyTreadsTopBottom "Component 7" /* Special handling (2 materials) - see above.  String is <MatOfTopFace kStairMaterialSeparator MatOfBottomFace> if materials are different */
#define kStairMaterialPropertyTreadsEdges "Component 8"

// ----------- PSet Properties used for Materials of Railings

#define kStairMaterialPropertyTopRail "Component 1"
#define kStairMaterialPropertyRailingPosts "Component 2"
#define kStairMaterialPropertyRailingFrame "Component 3"
#define kStairMaterialPropertyRailingFrameBars "Component 4"


// ************************************************************

namespace VectorWorks
{
	namespace Extension
	{
    
              // Beware of Proxy objects! If the stair passed by the calling function is a proxy, all Get/Set functions will be applied to the proxy parent instead.
              // Use CWStairVCOM::IsProxy() (or VS/SDK routines) to find out if the stair is a proxy.
              // Plug-ins trying to gather statistics should make sure not to count proxy AND proxy parent.
    
    
               enum StairCWComponentType {
                   ErrorComponentType = -1, /* Returned by VCOM functions if some error occurs */
                   StairCWIs2D = 1,  /* Numbers need to match strings in string files and need to be consistent for compatibility so do not change order and values of these constants */
                   StairCWIsHybrid
               };
    
              enum StairCWStandardConfigurationType {
                ErrorStandardConfiguration = -1, /* Returned by VCOM functions if some error occurs */
                StraightStair = 1, /* Numbers need to match strings in string files and need to be consistent for compatibility so do not change order and values of these constants */
                StraightTwoRuns,
                LSingleLanding,
                USingleLanding,
                UDoubleLandings,
                LWinder,
                UDoubleWinder,
                USingleWinder,
                CircularStair,
                Unused1, /* Required for compatibility */
                StraightThreeRuns,
                LFixedAngleWinder,
                UDoubleFixedAngleWinder,
                USingleFixedAngleWinder,
                ZSingleLanding, /* not supported yet */
                ZDoubleLandings, /* not supported yet */
                DoubleUDoubleLandings, /* O-Stair with two 180 degree landings */
                OStairTripleLandings/* O-Stair with three 90 degree landings */
               
              };
    
              enum StairCWOptionTotalRise {  /* Numbers need to match strings in string files and need to be consistent for compatibility so do not change order and values of these constants */
                      ErrorOptionTotalRise = -1,
                      TotalRiseByValue = 0,
                      TotalRiseByLayerElevation
              };
    
              enum StairCWConstructionType {
                      ErrorConstructionType = -1,
                      Solid = 1, /* Numbers need to match strings in string files and need to be consistent for compatibility so do not change order and values of these constants */
                      StringerUnderneath,
                      StringerOutside,
                      Concrete,
                      CircularWithTangentialSteps /* Special type used by circular stairs only */
              };
    
              enum StairCWTopGraphicOnUpperFloorMode {
                  ErrorTopGraphicOnUpperFloor = -1,
                  HasNoTopGraphicOnUpperFloor = 0,
                  HasTopGraphicOnUpperFloor = 1
              };
    
    
                 const Sint16 kCWStairVCOMParameterVersion = 1; // Current version of Data type. Increase when changing data type CWStairVCOMParameter.
             
                 class CWStairVCOMParameter {
                 
                     public:
                     
                        CWStairVCOMParameter() {
                          m_ErrorMessage.Clear();
                          m_VersionNumber = kCWStairVCOMParameterVersion;
                          m_IsProxy = false;
                          
                          SetErrorData();
                        };
                     
                       Sint16 GetVersionNumber() {return m_VersionNumber;}
                     
                       bool IsTotalRiseByValue() {return (m_OptionTotalRise == StairCWOptionTotalRise::TotalRiseByValue);}
                       bool IsTotalRiseByLayerElevation() {return (m_OptionTotalRise == StairCWOptionTotalRise::TotalRiseByLayerElevation);}
                     
                       bool HasTopGraphicOnUpperFloor() {return (m_TopGraphicOnUpperFloorMode == StairCWTopGraphicOnUpperFloorMode::HasTopGraphicOnUpperFloor);};
                       void SetHasTopGraphicOnUpperFloor(bool val) {m_TopGraphicOnUpperFloorMode = (val)?(StairCWTopGraphicOnUpperFloorMode::HasTopGraphicOnUpperFloor):(StairCWTopGraphicOnUpperFloorMode::HasNoTopGraphicOnUpperFloor);}
                     
                       bool IsHybrid() {return (m_Components==StairCWComponentType::StairCWIsHybrid);};
                       bool Is2DOnly() {return (m_Components==StairCWComponentType::StairCWIs2D);};
                           
                       void SetIsHybrid(bool val) {m_Components = (val)?(StairCWComponentType::StairCWIsHybrid):(StairCWComponentType::StairCWIs2D);};
                     
                       bool IsOK() {return m_ErrorMessage.IsEmpty();} // Returns false if some error has occurred
                     
                       bool IsProxy(){return m_IsProxy;}// Returns true if stair is proxy object
                        
                       TXString GetErrorMessage() {return m_ErrorMessage;} // Returns error message in case of error
                     
                     void SetErrorData() {
                           m_ConfigurationType = StairCWStandardConfigurationType::ErrorStandardConfiguration;
                           m_OptionTotalRise = StairCWOptionTotalRise::ErrorOptionTotalRise;
                           m_TotalRiseInMeter = -1.0;
                           m_WidthOfFirstFlightInMeter = -1.0;
                           m_ConstructionType = StairCWConstructionType::ErrorConstructionType;
                         
                           m_Side1InMeter = -1.0;
                           m_Side2InMeter = -1.0;
                           m_Side3InMeter = -1.0;
                           m_Side4InMeter = -1.0;
                           m_Side5InMeter = -1.0;
                         
                           m_NumRisers1 = -1;
                           m_NumRisers2 = -1;
                           m_NumRisers3 = -1;
                           m_NumRisers4 = -1;
                         
                           m_TopGraphicOnUpperFloorMode = StairCWTopGraphicOnUpperFloorMode::ErrorTopGraphicOnUpperFloor;
                           m_Components = StairCWComponentType::ErrorComponentType;
                     };
                     
                     protected:
                     
                      // Special:
                     
                      Sint16 m_VersionNumber; // Used by callee to check for incompatibilities
                     
                     public:
                     
                      // Inp/Out Parameters:
                     
                      bool m_IsProxy;
                     
                      StairCWStandardConfigurationType m_ConfigurationType; // one of enum StairCWConfigurationType
                      StairCWOptionTotalRise m_OptionTotalRise; // One of enum StairCWOptionTotelRise
                      StairCWConstructionType m_ConstructionType; // One of enum StairCWConstructionType. Refers to construction type of high deteil level.
                     
                      double m_TotalRiseInMeter;
                      double m_WidthOfFirstFlightInMeter;
                     
                      double m_Side1InMeter;
                      double m_Side2InMeter;
                      double m_Side3InMeter;
                      double m_Side4InMeter;
                      double m_Side5InMeter;
                     
                      Sint16 m_NumRisers1;
                      Sint16 m_NumRisers2;
                      Sint16 m_NumRisers3;
                      Sint16 m_NumRisers4;
                     
                      StairCWComponentType m_Components; // Component Pull-Down menu: 2D or 2D/3D? One of enum StairCWComponentType
                     
                      StairCWTopGraphicOnUpperFloorMode m_TopGraphicOnUpperFloorMode;
                     
                    
                      
                     public:
                     
                      // Output:
                     
                      TXString m_ErrorMessage; // Empty if everything was OK
                     
                     
                     
                 
                 }; // CWStairVCOMParameter
             
                 // --------------------------------------------------------------------------------------------------
    
    
		// --------------------------------------------------------------------------------------------------
		// {405fdf83-6d4a-4802-be7c-a2097a86441c }
		static const VWIID IID_VCOMStairCW = { 0x405fdf83, 0x6d4a, 0x4802, {0xbe, 0x7c, 0xa2, 0x09, 0x7a, 0x86, 0x44, 0x1c}};

		class IStairCWSupport : public IVWSingletonUnknown
		{
		
		public:
            

            
            virtual bool VCOM_CALLTYPE IsProxy(MCObjectHandle theStair) = 0;
            
            virtual bool VCOM_CALLTYPE GetData(MCObjectHandle theStair, CWStairVCOMParameter *theParameter) = 0;
                          // Fills theParameter with data of theStair
                          // theParameter must be a valid pointer to a variable of type CWStairVCOMParameter. GetData will not release or destroy it.
                          
            
            virtual bool VCOM_CALLTYPE SetData(MCObjectHandle theStair, CWStairVCOMParameter *theParameter) = 0;
                // Copies Data from theParameter into theStair.
                // !!! It is not recommended to change geometrical values or configuration types !!!
                // !!! This may cause internal inconsistencies and the stair may not be able to recalculate itself !!!
                // theParameter must be a valid pointer to a variable of type CWStairVCOMParameter. SetData will not release or destroy it.
                // !!! Call ResetObject (theStair)  after SetData to force a regeneration.
                // !!! Calling function must take care of undo support !!!

            virtual StairCWTopGraphicOnUpperFloorMode VCOM_CALLTYPE GetTopGraphicOnUpperFloorMode(MCObjectHandle theStair) = 0; // Returns one of enum StairCWTopGraphicOnUpperFloorMode. Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE HasTopGraphicOnUpperFloor(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE SetHasTopGraphicOnUpperFloor(MCObjectHandle theStair, bool val) =  0;
       
            virtual StairCWComponentType VCOM_CALLTYPE GetComponentType(MCObjectHandle theStair) = 0; // Returns one of enum StairCWComponentType. Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE IsHybrid(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE SetIsHybrid(MCObjectHandle theStair, bool val) =  0;
                  
            
            virtual StairCWStandardConfigurationType VCOM_CALLTYPE GetStandardConfigurationType(MCObjectHandle theStair) = 0; // Returns one of enum StairCWStandardConfigurationType. Use GetData to retrieve multiple values for faster performance
            virtual bool SetStandardConfigurationType(MCObjectHandle theStair, StairCWStandardConfigurationType theType) = 0; // Not recommended for use. See above.
            
            virtual StairCWConstructionType VCOM_CALLTYPE GetConstructionType(MCObjectHandle theStair) = 0; // Returns one of enum StairCWConstructionType. Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE SetConstructionType(MCObjectHandle theStair, StairCWConstructionType theType) = 0; // Not recommended for use. See above.
            
            virtual StairCWOptionTotalRise VCOM_CALLTYPE GetTotalRiseOption(MCObjectHandle theStair) =  0;
            
            
            virtual bool VCOM_CALLTYPE IsTotalRiseByValue(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE SetTotalRiseByValue(MCObjectHandle theStair) =  0; // Sets m_OptionRise, but not total rise itself
            
            
            virtual bool VCOM_CALLTYPE IsTotalRiseByLayerElevation(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool VCOM_CALLTYPE SetTotalRiseByLayerElevation(MCObjectHandle theStair) =  0; // Sets m_OptionRise, but not total rise itself
            
            virtual double VCOM_CALLTYPE GetTotalRiseInMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetTotalRiseInMeter(MCObjectHandle theStair, double totalRiseInM) = 0; // Sets value of total rise AND sets OptionRise to StairCWOptionRise::ByValue. Not recommended for use. See above.
            
            virtual double VCOM_CALLTYPE GetWidthOfFirstFlightInMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetWidthOfFirstFlightInMeter(MCObjectHandle theStair, double widthInM) = 0; // Not recommended for use. See above.
            
            virtual double VCOM_CALLTYPE GetLengthOfSide1InMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetLengthOfSide1InMeter(MCObjectHandle theStair, double widthInM) = 0; // Not recommended for use. See above.
            
            virtual double VCOM_CALLTYPE GetLengthOfSide2InMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetLengthOfSide2InMeter(MCObjectHandle theStair, double widthInM) = 0; // Not recommended for use. See above.
            
            virtual double VCOM_CALLTYPE GetLengthOfSide3InMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetLengthOfSide3InMeter(MCObjectHandle theStair, double widthInM) = 0; // Not recommended for use. See above.
            
            virtual double VCOM_CALLTYPE GetLengthOfSide4InMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetLengthOfSide4InMeter(MCObjectHandle theStair, double widthInM) = 0; // Not recommended for use. See above.
            
            virtual double VCOM_CALLTYPE GetLengthOfSide5InMeter(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetLengthOfSide5InMeter(MCObjectHandle theStair, double widthInM) = 0; // Not recommended for use. See above.
            
            virtual Sint16 VCOM_CALLTYPE GetNumRisers1(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetNumRisers1(MCObjectHandle theStair, Sint16 num) = 0; // Not recommended for use. See above.
            
            virtual Sint16 VCOM_CALLTYPE GetNumRisers2(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetNumRisers2(MCObjectHandle theStair, Sint16 num) = 0; // Not recommended for use. See above.
            
            virtual Sint16 VCOM_CALLTYPE GetNumRisers3(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetNumRisers3(MCObjectHandle theStair, Sint16 num) = 0; // Not recommended for use. See above.
            
            virtual Sint16 VCOM_CALLTYPE GetNumRisers4(MCObjectHandle theStair) = 0; // Use GetData to retrieve multiple values for faster performance
            virtual bool  VCOM_CALLTYPE SetNumRisers4(MCObjectHandle theStair, Sint16 num) = 0; // Not recommended for use. See above.
            
      
             
		};
    

    
	}
}
