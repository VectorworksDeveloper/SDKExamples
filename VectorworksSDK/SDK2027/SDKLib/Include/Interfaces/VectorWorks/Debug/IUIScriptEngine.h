//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Debug
	{
		// ----------------------------------------------------------------------------------------------------
		// {A3F81C2D-7E4B-4C9A-B056-2D8F3A91E7C4}
		static const VWIID IID_UIScriptEngine = { 0xa3f81c2d, 0x7e4b, 0x4c9a, { 0xb0, 0x56, 0x2d, 0x8f, 0x3a, 0x91, 0xe7, 0xc4 } };

		// Sentinel returned by RunScriptedDialog when a "wait_for_user" action is encountered.
		// The caller (UIScriptInterceptHandler) must NOT re-register the timer and must NOT
		// send WM_COMMAND to close the dialog — it becomes fully interactive for the user.
		// When the user eventually dismisses the dialog, NotifyDialogComplete is called
		// through the normal close path.
		static const Sint32 kUIScriptYieldToUser = -1;

		class DYNAMIC_ATTRIBUTE IUIScriptEngine : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE LoadScriptFromDisk(const TXString& jsonPath) = 0;
			virtual VCOMError VCOM_CALLTYPE LoadScript(const TXString& json) = 0;
			virtual VCOMError VCOM_CALLTYPE UnloadScript() = 0;

			virtual bool      VCOM_CALLTYPE ShouldInterceptDialog(const TXString& tag) = 0;
			// Called once per dialog-timer tick (kDialogTimerEventMessage).
			// Processes ONE action from the current script step and returns:
			//   kDefaultButtonID      — all actions done (or explicit click_ok); close with OK.
			//   kCancelButtonID       — explicit click_cancel; close with Cancel.
			//   0                     — more actions remain; caller must re-register the timer.
			//   kUIScriptYieldToUser  — wait_for_user action hit; stop timer, leave dialog open.
			virtual Sint32    VCOM_CALLTYPE RunScriptedDialog(Sint32 layout,
			                                                   GS_EventHandlerProcPtr handler,
			                                                   void* env,
			                                                   const TXString& tag) = 0;
			virtual void      VCOM_CALLTYPE Log(const TXString& msg) = 0;
			virtual bool      VCOM_CALLTYPE HasPendingSteps() = 0;
			virtual void      VCOM_CALLTYPE NotifyDialogComplete(const TXString& tag, bool wasOK) = 0;

			// Returns kDefaultButtonID, kCancelButtonID, or 0 (show normally).
			// When a script is loaded and "dismiss_unscripted" is set, dialogs NOT in the
			// script are auto-dismissed with the specified result instead of being shown.
			virtual Sint32    VCOM_CALLTYPE GetDismissResultForUnscriptedDialog(const TXString& tag) = 0;

			// If a click_image_btn action stored a preset image path, returns true and
			// populates outPath, consuming the path (subsequent calls return false until
			// a new path is set). Called from GetImageFileToOpenDialog to bypass the
			// native OS file-chooser during automated scripted testing.
			virtual bool      VCOM_CALLTYPE GetAndConsumePresetImagePath(TXString& outPath) = 0;
		};

		typedef VCOMPtr<IUIScriptEngine> IUIScriptEnginePtr;
	}
}
