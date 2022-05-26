//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		enum class ECutListAction
		{
			CutForDelete,
			CutForCut,
			CutForGroup,
			CutForGroupDefinition,
		};

		enum class ETagDeleteAction
		{
			None,
			CancelTagDelete,
			DoTheSameForTaggedObject,
		};

		using TXStringSTLUnorderedSet = std::unordered_set<TXString>;
		// ----------------------------------------------------------------------------------------------------
		// {765AF7C7-417F-4D8D-BADF-59B074A44F07}
		static const TSinkIID IID_ITaggedObjectProvider = { 0x765af7c7, 0x417f, 0x4d8d, { 0xba, 0xdf, 0x59, 0xb0, 0x74, 0xa4, 0x4f, 0x7 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ITaggedObjectProvider : public IEventSink
		{
			public:
				// Used to return an array of values to be displayed
				virtual bool VCOM_CALLTYPE GetParameterValue(MCObjectHandle hObject, MCObjectHandle hDataTag, const TXString& paramName, std::vector<TXString>& outValues) { return false; }
				// Used to delegate the updating of a parameter to the tagged object. Return true if handled by the tagged object.
				virtual bool VCOM_CALLTYPE SetParameterValue(MCObjectHandle hObject, MCObjectHandle hDataTag, const TXString& paramName, const VWVariant& newValue) { return false; }
				// Used to detirmine whether the tagged objects wants to disable the parameter's editing in the "Edit Tag Data" dialogue
				virtual bool VCOM_CALLTYPE IsParameterDisabled(MCObjectHandle hObject, const TXString& paramName) { return false; }

				// Use the output parameter outAction for:
				// ETegDeleteAction::None						- nothing happens
				// ETegDeleteAction::CancelTagDelete			- the Data Tag deletion will be canceled
				// ETegDeleteAction::DoTheSameForTaggedObject	- hObject will get cutListAction applied to it as the Data Tag
				// 
				// If you are displaying a dialog in this function, make sure you display it once for object type, using setNotifiedObjects
				virtual void VCOM_CALLTYPE OnDataTagDelete(MCObjectHandle hObject, MCObjectHandle hDataTag, const TXStringSTLUnorderedSet& setNotifiedObjects, const ECutListAction& cutListAction, ETagDeleteAction& outAction) { outAction = ETagDeleteAction::None; }

				// Used to determine if the Data Tag will be moved to the top of the drawing, when the PIOs get modified
				virtual bool VCOM_CALLTYPE MoveDataTagsToTop() { return false; }

				// Return true if the parameter with name paramName is a sequence parameter of hObject
				virtual bool VCOM_CALLTYPE IsSequenceParameter(MCObjectHandle hObject, const TXString& paramName) { return false; }

				// Handles clicking on Manage... button in the Edit Tag Data if the parameter with name paramName
				// is a sequence parameter as specified in IsSequenceParameter
				// This is handled in a separate undo event and returning false here will not undo the changes
				// done in the Edit Tag Data dialog.
				virtual bool VCOM_CALLTYPE EditSequenceParameter(MCObjectHandle hObject, const TXString& paramName) { return false; }
		};
	}
}
