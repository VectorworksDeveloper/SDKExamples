//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {14269af3-b1d1-404b-b089-20ff6262ca79}
		static const TSinkIID IID_AssemblyCornerObject = { 0x14269af3, 0xb1d1, 0x404b, { 0xb0, 0x89, 0x20, 0xff, 0x62, 0x62, 0xca, 0x79 } };

		class DYNAMIC_ATTRIBUTE IAssemblyCornerObject : public IEventSink
		{
		public:
			struct CornerEdgeData {
				bool fIsLowerCorner = false;
				bool fIsUpperCorner = false;
				double fTanLower = 0;
				double fTanUpper = 0;
				double fMiterPlaneOffset = 0;
			};
			
			virtual CornerEdgeData VCOM_CALLTYPE GetCornerEdgeData(MCObjectHandle hObj) = 0;			
		};
	
		typedef VCOMPtr<IAssemblyCornerObject>			IAssemblyCornerObjectPtr;
	}

	
}
