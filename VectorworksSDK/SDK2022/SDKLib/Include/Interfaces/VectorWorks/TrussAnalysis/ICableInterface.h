//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2020 www.deersoft.de
//-----------------------------------------------------------------------------

#pragma once

namespace VectorWorks
{
	namespace TrussAnalysis
	{
		

		using LocalicedStringArray = std::vector<std::pair< TXString, TXString> >;  // <NativeStr, LocalicedStr >
		using ConnectionOption     = std::vector<std::pair< TXString, TXString> >;  // <Key, Text >

		struct SConnection
		{
            SConnection()
            {
                Consumption  = 0.0;
                MaximumPower = 0.0;
                Voltage      = 0;
                
                ShowConsuption      = false;
                ShowMaximumPower    = false;
                ShowVoltage         = false;
                ShowConnector       = false;
                ShowLinkedGenerator = false;
            }			

            TXString            ConnectionName;
            ConnectionOption    Options;
            
            bool        ShowConsuption;
            double      Consumption;
            bool        ShowMaximumPower;
            double      MaximumPower;
            bool        ShowVoltage;
            double      Voltage;
            bool        ShowConnector;
            TXString    Connector;
            bool        ShowLinkedGenerator;
            TXString    LinkedGenerator;
		};

		class DYNAMIC_ATTRIBUTE ICableInterface : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	GetConnectors(LocalicedStringArray& outArray) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetConnector_NativeName(const TXString & locNam, TXString& out_NativeNam) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetConnector_Localiced (const TXString & nativeNam, TXString& out_LocNam) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetConnectorAdapters(LocalicedStringArray& outArray) = 0;

			// Connection Support VW2022
			virtual bool     VCOM_CALLTYPE SupportConnections(MCObjectHandle object) = 0;
			virtual bool     VCOM_CALLTYPE LoadConnections(MCObjectHandle object) = 0;
			virtual size_t   VCOM_CALLTYPE GetConnectionCount() = 0;

			// UI Support
			virtual bool      VCOM_CALLTYPE GetConnectionOptions(size_t index, VectorWorks::TrussAnalysis::SConnection& out) = 0;
			virtual bool      VCOM_CALLTYPE SetConnection(size_t index, const TXString& value) = 0;
            
            virtual bool      VCOM_CALLTYPE SetConsumption(size_t index, double value) = 0;
            virtual bool      VCOM_CALLTYPE SetVoltage(size_t index, double value) = 0;
            virtual bool      VCOM_CALLTYPE SetMaxiumumPower(size_t index, double value) = 0;
            virtual bool      VCOM_CALLTYPE SelectLinkedGenerator(size_t index) = 0;

			virtual void      VCOM_CALLTYPE AdaptConnectedCablesOnMove(MCObjectHandle device) = 0;

			virtual void      VCOM_CALLTYPE  OnTrussMove(MCObjectHandle truss, const TransformMatrix& transform) = 0;

            virtual void      VCOM_CALLTYPE  CablePath_OnAddState(MCObjectHandle h, ObjectState& stateInfo) = 0;
			virtual bool      VCOM_CALLTYPE  SupportsPowerplaning(MCObjectHandle h) = 0;
		};

		typedef VCOMPtr<ICableInterface>	ICableInterfacePtr;
		const VWIID IID_ICableInterface = { 0x8c604dc2, 0x4355, 0x43a3, {0x9c, 0x76, 0x37, 0xff, 0x84, 0x1b, 0x0b, 0x8d} };
	}
} // Namespace
