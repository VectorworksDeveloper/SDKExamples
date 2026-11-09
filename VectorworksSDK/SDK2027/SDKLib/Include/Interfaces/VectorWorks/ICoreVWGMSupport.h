//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	using namespace VectorWorks;

	// {8306EA88-CC44-4437-B28F-CAB6DA18B7B4}
	static const VWIID IID_CoreVWGMSupport = { 0X8306EA88, 0XCC44, 0X4437, { 0xB2, 0x8F, 0xCA, 0xB6, 0xDA, 0x18, 0xB7, 0xB4 } };

	class DYNAMIC_ATTRIBUTE ICoreVWGMSupport : public IVWSingletonUnknown
	{
	public:
		virtual VCOMError DrawVWObjects(const ViewRect& inViewRect) = 0;
		virtual VCOMError Draw3DDepthTestedFeedback() = 0;
		virtual VCOMError Draw2DScreenFeedback() = 0;

		virtual VCOMError SetCameraToWorld() = 0;
		virtual VCOMError SetCameraToScreen() = 0;
	};
}
