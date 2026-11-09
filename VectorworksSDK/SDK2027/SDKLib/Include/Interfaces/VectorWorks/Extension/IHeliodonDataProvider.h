//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		// {2B668D74-7CB2-4813-A373-0BD38720AF04}
		static const VWIID IID_HeliodonDataProvider = { 0x2b668d74, 0x7cb2, 0x4813, { 0xa3, 0x73, 0xb, 0xd3, 0x87, 0x20, 0xaf, 0x4 } };
		
		class DYNAMIC_ATTRIBUTE IHeliodonDataProvider : public IEventSink
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE Init(MCObjectHandle heliodon) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetLatitude(double& latitude) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetLongitude(double& longitude) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetMeridianDrgrees(double& meridianDrgrees) const = 0;
	
			virtual VCOMError	VCOM_CALLTYPE GetDaylightSavings(bool& daylightSavings) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetHour(Sint32& hour) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetMinute(Sint32& minute) const = 0;

			virtual VCOMError	VCOM_CALLTYPE GetMonth(Sint32& month) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetDay(Sint32& day) const = 0;

			virtual VCOMError	VCOM_CALLTYPE GetSunBrightness(double& sunBrightness) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetSoftShadows(bool& softShadows) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetPhysicalSun(bool& physicalSun) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetPhysicalSky(bool& physicalSky) const = 0;
			virtual VCOMError	VCOM_CALLTYPE GetWarmColors(bool& warmColors) const = 0;

			virtual VCOMError	VCOM_CALLTYPE ShowSolarAnimationDialog(bool& success) = 0;
		};
		
		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IHeliodonDataProvider> IHeliodonDataProviderPtr;
	}
}