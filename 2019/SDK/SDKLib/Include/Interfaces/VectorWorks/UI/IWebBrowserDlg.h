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
			virtual void VCOM_CALLTYPE SetInitialURL(const TXString& url) = 0;
			virtual void VCOM_CALLTYPE AddHomeURL(const TXString& url) = 0;
			virtual void VCOM_CALLTYPE AddContentFilter(IWebContentFilter* filter) = 0;

			virtual void VCOM_CALLTYPE SetTitle(const TXString& title) = 0;
			virtual void VCOM_CALLTYPE GetPosition(ViewCoord& outX, ViewCoord& outY) const = 0;
			virtual void VCOM_CALLTYPE SetPosition(ViewCoord x, ViewCoord y) = 0;
			virtual void VCOM_CALLTYPE GetSize(ViewCoord& outWidth, ViewCoord& outHeight) const = 0;
			virtual void VCOM_CALLTYPE SetSize(ViewCoord width, ViewCoord height) = 0;
			
			virtual void VCOM_CALLTYPE SetButtonOk(bool set) = 0;
			virtual void VCOM_CALLTYPE SetButtonOk(bool set, const TXString& btnText) = 0;

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

			// ------------------------------------------------------------------------
			// Tools

			virtual IWebBrowserFrame* VCOM_CALLTYPE GetLastBrowserFrame() = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IWebBrowserDlg>			IWebBrowserDlgPtr;
	}
}
