//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IWebContentFilter.h"

namespace VectorWorks
{
	namespace UI
	{
		// ------------------------------------------------------------------------------------------------------------------------------------
		enum class EWebBrowserDlgRes
		{
			  Unknown		// the window what closed directly
			, OKButton
			, CancelButton
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		enum class EEventResult
		{
			  Proceed
			, Block
			, CloseDialogWithOk
			, CloseDialogWithCancel
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		enum class EAddressBarMode
		{
			  Invisible
			, ReadOnly
			, Editable
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		typedef std::map<TXString, TXString> 	TStringKeyValueMap;
  
		// ------------------------------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWebBrowserFrame
		{
		public:
			virtual ~IWebBrowserFrame()		{}

			virtual void LoadURL(const TXString& url) = 0;
			virtual void Close(bool ok) = 0;
			virtual void ExecuteJavaScript(const TXString& code) = 0;
			virtual void ExecuteJavaScript(const TXString& code, std::function<void()> onCompleteCallback) = 0; // callback is executed outside UI thread
			virtual void SetTitle(const TXString& title) = 0;
			virtual void SetOKButtonText(const TXString& btnText) = 0;
			virtual void SetOKButtonState(bool enabled) = 0;
			virtual void SetCancelButtonText(const TXString& btnText) = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		// Example of how to return data back to JavaScript
		// ------------------------------------------------------------------------------------------------------------------------------------
		//	C++ code:
		//		ptr->AddJavaScriptFunctionPromise( "API.getDataInternal",
		//			[&](const TXString& name, const std::vector<nlohmann::json>& args, IJSFunctionCallbackContext* context)
		//			{
		//				TXString result = "return data to JavaScript";
		//
		//				std::vector<nlohmann::json> callArgs;
		//				callArgs.push_back( result );		// add the arguments to be passed to the 'resolve' function
		//				context->Resolve( callArgs );		// resolve the promise created by this call
		//			});
		//
		// JavaScript:
		//		API.getData().then(function(response) {
		//			alert("Success!", response);
		//		});
		//
		// Info: https://developers.google.com/web/fundamentals/primers/promises
		//
		class DYNAMIC_ATTRIBUTE IJSFunctionCallbackContext
		{
		public:
			virtual ~IJSFunctionCallbackContext() {}
			virtual void Call(const nlohmann::json& function) = 0;
			virtual void Call(const nlohmann::json& function, const nlohmann::json& arg) = 0;
			virtual void Call(const nlohmann::json& function, const std::vector<nlohmann::json>& args) = 0;

			// for when used by a promise implementation (via IWebBrowserDlg::AddJavaScriptFunctionPromise or IWebJavaScriptProvider::IInitContext::AddFunctionPromise)
			virtual void Resolve(const nlohmann::json& arg) = 0;
			virtual void Reject(const TXString& message) = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		// {B92641BF-69C5-4FF1-9BC3-39E8D67E865B}
		static const VWIID IID_WebBrowserDlg = { 0xb92641bf, 0x69c5, 0x4ff1, { 0x9b, 0xc3, 0x39, 0xe8, 0xd6, 0x7e, 0x86, 0x5b } };

		class DYNAMIC_ATTRIBUTE IWebBrowserDlg : public IVWUnknown
		{
		public:
			virtual EWebBrowserDlgRes VCOM_CALLTYPE RunModalDialog(const TXString& contextualHelpID) = 0;
			
			// ------------------------------------------------------------------------
			// Setttings
			virtual void VCOM_CALLTYPE SetLabelText(const TXString& txt) = 0;
			virtual void VCOM_CALLTYPE SetInitialURL(const TXString& url, bool addToHomeUrls = true) = 0;
			virtual void VCOM_CALLTYPE AddHomeURL(const TXString& url) = 0;
			virtual void VCOM_CALLTYPE AddContentFilter(IWebContentFilter* filter) = 0;

			virtual void VCOM_CALLTYPE SetTitle(const TXString& title) = 0;
			virtual void VCOM_CALLTYPE GetPosition(ViewCoord& outX, ViewCoord& outY) const = 0;
			virtual void VCOM_CALLTYPE SetPosition(ViewCoord x, ViewCoord y) = 0;
			virtual void VCOM_CALLTYPE GetSize(ViewCoord& outWidth, ViewCoord& outHeight) const = 0;
			virtual void VCOM_CALLTYPE SetSize(ViewCoord width, ViewCoord height) = 0;
			virtual void VCOM_CALLTYPE SetMinSize(ViewCoord width, ViewCoord height) = 0;
			virtual void VCOM_CALLTYPE SetDefSize(ViewCoord width, ViewCoord height) = 0;	// Default size that will be used, if the dialog doesn't have fixed size, and doesn't have previous saved size (from prev use)
			virtual void VCOM_CALLTYPE GetCurrentURL(TXString& outUrl) const = 0;
			
			virtual void VCOM_CALLTYPE SetButtonOk(bool set) = 0;
			virtual void VCOM_CALLTYPE SetButtonOk(bool set, const TXString& btnText) = 0;
			virtual void VCOM_CALLTYPE SetButtonOkState(bool enable) = 0;

			virtual void VCOM_CALLTYPE SetButtonCancel(bool set) = 0;
			virtual void VCOM_CALLTYPE SetButtonCancel(bool set, const TXString& btnText) = 0;

			typedef std::function<void()>			TOnSettingsButtonCallback;
			virtual void VCOM_CALLTYPE SetButtonSettings(bool set, TOnSettingsButtonCallback callback) = 0;
			virtual void VCOM_CALLTYPE SetButtonSettings(bool set, TOnSettingsButtonCallback callback, const TXString& btnTextOrImageResourceSpecifier, bool isImage) = 0;	// pass empty string for default icon, or default text

			virtual void VCOM_CALLTYPE SetButtonNavigation(bool set) = 0; // Back, Forward, Reload buttons
			virtual void VCOM_CALLTYPE SetButtonNavigation(bool set, const TXString& imageBack_ResourceSpecifier, const TXString& imageForward_ResourceSpecifier, const TXString& imageReload_ResourceSpecifier) = 0;
			
			virtual void VCOM_CALLTYPE SetButtonHome(bool set) = 0;
			virtual void VCOM_CALLTYPE SetButtonHome(bool set, const TXString& image_ResourceSpecifier) = 0;

			virtual void VCOM_CALLTYPE SetButtonReload(bool set) = 0;
			
			virtual void VCOM_CALLTYPE SetAddressBar(EAddressBarMode set) = 0;

			typedef std::function<TXString(const TXString&)>		TOnOpenInExternalBrowserCallback;	// input: current URL; output: URL to navigate to
			virtual void VCOM_CALLTYPE SetButtonOpenInExternalBrowser(bool set, TOnOpenInExternalBrowserCallback callback=nullptr) = 0;

			virtual void VCOM_CALLTYPE SetEnableLocalResourceAccess(bool enableLocalResourceAccess) = 0;
			
			// The 'CloseDialog' can be used on the JS thread. It already accounts for main thread sync
			virtual void VCOM_CALLTYPE CloseDialog(bool ok) = 0;
			
			// Disable the context menu inside the brower
			virtual void VCOM_CALLTYPE SetShouldHideContextMenu(bool shouldHideContextMenu) = 0;
			
			// Show the Chromium DevTools when the dialog opens.
			// This is useful during development, so tha the DevTool window is opened always, and early enough to capture all events
			// It doesn't make sense typically to leave this code in RELEASE code
			virtual void VCOM_CALLTYPE ShowDevTools() = 0;

			// ------------------------------------------------------------------------
			// Callbacks

			// Notify before a request to obtain the headers of the request
			typedef std::function<void(const TXString& url, TStringKeyValueMap& outHeaders)>	TOnGetRequestHeadersCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnGetRequestHeaders(TOnGetRequestHeadersCallback callback) = 0;

			// Notify before a link will be opened in the browser
			typedef std::function<EEventResult(const TXString& url, bool isRedirect)>	TOnBeforeOpenLinkCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnBeforeOpenLink(TOnBeforeOpenLinkCallback callback) = 0;
			virtual void VCOM_CALLTYPE SetCallback_OnBeforeOpenNewWindowLink(TOnBeforeOpenLinkCallback callback) = 0;

			// Notify before a download occurs in the browser
			typedef std::function<EEventResult(const TXString& url, const TXString& suggestedFileName, TXString& outFullFilePath)>			TOnBeforeDownloadCallback;
			typedef std::function<EEventResult(const TXString& url, bool isInProgress, bool isCompleted, bool isCanceled, Sint32 progress)>	TOnDownloadProgressCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnDownload(TOnBeforeDownloadCallback beforeDownloadCallback, TOnDownloadProgressCallback progressCallback = nullptr) = 0;

			// Notify for the content of the response after a request to a specific URL
			typedef std::function<EEventResult(const void* data, size_t dataSize)>			TOnResponseDataCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnRequestResponse(const TXString& url, TOnResponseDataCallback responseDataCallback) = 0;

			// Process key event
			typedef std::function<void(bool cmd, bool ctrl, bool optAlt, bool shift, char16_t key)>	TOnKeyDownCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnKeyDown(TOnKeyDownCallback callback) = 0;
			
			// Process file dragging event
			typedef std::function<void(std::vector<TXString>)>	TOnDragFilesCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnDragFiles(TOnDragFilesCallback callback) = 0;
			
			virtual void VCOM_CALLTYPE AddJavaScriptExecute(const TXString& code) = 0;			// pre-code: execute before defining variables and functions
			virtual void VCOM_CALLTYPE AddJavaScriptPostExecute(const TXString& code) = 0;		// post-code: execute after defining variables and functions
			virtual void VCOM_CALLTYPE AddJavaScriptVariable(const TXString& name, const nlohmann::json& value) = 0;

			// Add an asynchronous JavaScript function called on the JS thread, or synchronous -- on the main Vectorworks thread (safe to call the SDK)
			// the callback function would receive parameters from JS. The context in the callback can be used to call functions passed as parameters (legacy Promise support)
			// For example see the definition of VectorWorks::UI::IJSFunctionCallbackContex
			typedef std::function<void(const TXString& name, const std::vector<nlohmann::json>& args, IJSFunctionCallbackContext* context)>	TOnJSFunctionCallback;
			virtual void VCOM_CALLTYPE AddJavaScriptFunction(const TXString& name, TOnJSFunctionCallback callback) = 0;
			virtual void VCOM_CALLTYPE AddJavaScriptFunctionSync(const TXString& name, TOnJSFunctionCallback callback) = 0;

			// Direct promise suport. Asynchronous or synchronous as explained above.
			// This function will add a function which returns a promise. That must be satisfied with resolve/reject via the 'context' of the callback
			// Example how to call in JS:
			//		function_name().then( (res) => { console.log( res ); } )
			//		function_name().then( (res) => { console.log( res ); } ).catch( (err) => { console.error( err ) } )
			//		function_name().then( (res) => { console.log( res ); } ).catch( (err) => { console.error( err ) } )..finally( () => { ... } )
			//		function_name(param).then( (res) => { console.log( res, param ); } )
			virtual void VCOM_CALLTYPE AddJavaScriptFunctionPromise(const TXString& name, TOnJSFunctionCallback callback) = 0;
			virtual void VCOM_CALLTYPE AddJavaScriptFunctionPromiseSync(const TXString& name, TOnJSFunctionCallback callback) = 0;


			// ------------------------------------------------------------------------
			// Tools

			virtual IWebBrowserFrame* VCOM_CALLTYPE GetLastBrowserFrame() = 0;

			// Notify when the OK or Cancel buttons are clicked
			// Return 'true' to close the dialog; false -- to prevent closing
			typedef std::function<bool()>	TOnDefaultButtonCallback;
			virtual void VCOM_CALLTYPE SetCallback_OnOkButton(TOnDefaultButtonCallback callback) = 0;
			virtual void VCOM_CALLTYPE SetCallback_OnCancelButton(TOnDefaultButtonCallback callback) = 0;

			// Disable the close button, and menu, provided by the OS for the web-dialog
			// This will make it only possible to close the dialog via a button, and/or a JS call
			// This can only be called before the dialog is displayed
			virtual void VCOM_CALLTYPE DisableWindowClose() = 0;

			// Add standard .vwr resource accessor function inside the provided integratorObj.
			// 'pluginVWRIdentifier' should be provided from call to DefaultPluginVWRIdentifier()
			// Example Backend:  webBrowserPtr->AddReourceAccessFunction( "myIntegrator", DefaultPluginVWRIdentifier() );
			// Exmpale Frontend: myIntegrator.getResource('Strings/html.vwstrings').then( (arr) => { ... } );
			virtual void VCOM_CALLTYPE AddReourceAccessFunction(const TXString& integratorObj, const TXString& pluginVWRIdentifier) = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IWebBrowserDlg>			IWebBrowserDlgPtr;
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------
// The old way of implementing data return from function implementations
// There is a new AddJavaScriptFunctionPromise to do this directly.
// See the example above.
// ------------------------------------------------------------------------------------------------------------------------------------
//	C++ code:
//		ptr->AddJavaScriptExecute( 
//			"API = {};"
//			"API.getData = () => new Promise(function(resolve, reject) { API.getDataInternal(resolve, reject); } );"
//		);
//
//		ptr->AddJavaScriptFunction( "API.getDataInternal",
//			[&](const TXString& name, const std::vector<nlohmann::json>& args, IJSFunctionCallbackContext* context)
//			{
//				TXString result = "return data to JavaScript";
//
//				std::vector<nlohmann::json> callArgs;
//				callArgs.push_back( result );		// add the arguments to be passed to the 'resolve' function
//				context->Call( args[0], callArgs ); // this relies on the call from the Promise above: args[0] = <the resolve function>; args[1] = <the reject function>;
//			});
//
// JavaScript:
//		API.getData().then(function(response) {
//			alert("Success!", response);
//		});
//
// Info: https://developers.google.com/web/fundamentals/primers/promises
// Note: it is possible to pass parameters to the API.getData. You must revise the promise so it passes them to the getDataInternal
//
