//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IProviderShapePane.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {ae0365e8-aa9d-46d3-86cc-a9c8748ebb4b}
		static const TSinkIID IID_ProviderDataPane = { 0xae0365e8, 0xaa9d, 0x46d3, {0x86, 0xcc, 0xa9, 0xc8, 0x74, 0x8e, 0xbb, 0x4b} };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderDataPane : public IEventSink
		{
		public:
			virtual void VCOM_CALLTYPE		Init(const TXString& recordFormatName, IExtendedProps* extProps) = 0;
			virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, MCObjectHandle hRecord, const SSelectionContext& selContext) = 0;
			virtual void VCOM_CALLTYPE		Deactivate() = 0;
			virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider) = 0;
            
            virtual bool VCOM_CALLTYPE		OnPreWidgetChange(SShapePaneWidgetOnWidgetChange& data)                     { return false; }

			// return true if the message is handled. if not handled, the ParametricUIButtonHitMessage will be sent to the parametric
			// outNeedReset will cause the object to be reset by Vectorworks
			// when outChangeOk is false, the UndoAndRemove will be executed.
			//
			// NOTE! The outChangeOk parameter is the equivalent of the return value of the old function!
			//
			virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)	{ return false; }

			// return true if the message is handled and no default translation is to be done
			virtual bool VCOM_CALLTYPE		TransferValue(SShapePaneWidgetTransferValue& data)							{ return false; }
			virtual bool VCOM_CALLTYPE		ShouldRecreateWidgets()														{ return false; }
            virtual void VCOM_CALLTYPE		OnFullClean()																{ }    

		private:
			// Do not use this function, use the equivalent with the extra parameter outChangeOk
			// Also, note that the new function should return true if the event was handled.
			// The return value was changed so the compiler will report for the function change. this function will be removed in future versions
			virtual void VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset)	{ }
		};
	}
}