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
		// {FBFAAFB6-B95B-4A5C-94EF-C27F9177EBB3}
		static const TSinkIID IID_ObjectShapePaneProvider = { 0xfbfaafb6, 0xb95b, 0x4a5c, { 0x94, 0xef, 0xc2, 0x7f, 0x91, 0x77, 0xeb, 0xb3 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IObjectShapePaneProvider : public IEventSink
		{
		public:
			virtual void VCOM_CALLTYPE InitializeWidgets(IWidgetsEditProvider* widgetsProvider) = 0;
			virtual void VCOM_CALLTYPE Update(MCObjectHandle hObject, IWidgetsEditProvider* widgetProvider) = 0;
			virtual bool VCOM_CALLTYPE TransferValue(SShapePaneWidgetTransferValue& data) = 0;
			virtual bool VCOM_CALLTYPE OnWidgetChange(SShapePaneWidgetOnWidgetChange& data) = 0;
			virtual bool VCOM_CALLTYPE GetLabel(bool isPlural, TXString& objectLabel) { return false; };
			virtual bool VCOM_CALLTYPE ShouldRecreateWidgets() { return false; }
		};

		typedef VCOMPtr<VectorWorks::Extension::IObjectShapePaneProvider>	IObjectShapePaneProviderPtr;
	}
}
