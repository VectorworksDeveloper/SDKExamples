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
		// ----------------------------------------------------------------------------------------------------
		// {8F7B5F97-E009-43A5-866C-B805D6698FF9}
		static const VWGroupID GROUPID_ExtensionWebPalettes = { 0x8f7b5f97, 0xe009, 0x43a5, { 0x86, 0x6c, 0xb8, 0x5, 0xd6, 0x69, 0x8f, 0xf9 } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for web palette extension
		class DYNAMIC_ATTRIBUTE IExtensionWebPalette : public IExtension
		{
		public:
			virtual TXString	VCOM_CALLTYPE GetTitle() = 0;
			virtual TXString	VCOM_CALLTYPE GetInfoText()		{ return TXString(); }
			virtual TXString	VCOM_CALLTYPE GetInitialURL() = 0;
			virtual bool		VCOM_CALLTYPE GetInitialSize(ViewCoord& outCX, ViewCoord& outCY) { return false; }	// return true if providing initial size
			virtual bool		VCOM_CALLTYPE GetMinimalSize(ViewCoord& outCX, ViewCoord& outCY) { return false; }	// return true if providing initial size
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWebPaletteFrame
		{
		public:
			virtual ~IWebPaletteFrame() {}

			virtual void LoadURL(const TXString& url) = 0;
			virtual void ExecuteJavaScript(const TXString& code) = 0;
			virtual void ExecuteJavaScript(const TXString& code, std::function<void()> onCompleteCallback) = 0; // callback is executed outside UI thread
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		enum class ECallbackResult
		{
			  Proceed
			, Block
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		typedef std::map<TXString, TXString>	TStringKeyValueMap;

		// ----------------------------------------------------------------------------------------------------
		// {24F067C6-AF3F-445F-A276-E4BFEBD937C8}
		static const TSinkIID IID_WebCallbacksProvider			= { 0x24f067c6, 0xaf3f, 0x445f, { 0xa2, 0x76, 0xe4, 0xbf, 0xeb, 0xd9, 0x37, 0xc8 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWebCallbacksProvider : public IEventSink
		{
		public:
			class DYNAMIC_ATTRIBUTE IInitContext
			{
			public:
				virtual			~IInitContext()		{}
				virtual void	AddRequestResponse(const TXString& url, size_t& outID) = 0;
			};

		public:
			virtual void			VCOM_CALLTYPE OnInit(IInitContext* context)													{}

			// Notify before a request to obtain the headers of the request
			virtual void			VCOM_CALLTYPE OnGetRequestHeaders(const TXString& url, TStringKeyValueMap& outHeaders)		{}

			// Notify before a link will be opened in the browser
			virtual ECallbackResult	VCOM_CALLTYPE OnBeforeOpenLink(const TXString& url, bool isRedirect)						{ return ECallbackResult::Proceed; }
			virtual ECallbackResult	VCOM_CALLTYPE OnBeforeOpenNewWindowLink(const TXString& url, bool isRedirect)				{ return ECallbackResult::Proceed; }

			// Notify before a download occurs in the browser
			virtual ECallbackResult	VCOM_CALLTYPE OnBeforeDownload(const TXString& url, const TXString& suggestedFileName, TXString& outFullFilePath)				{ return ECallbackResult::Proceed; }
			virtual ECallbackResult	VCOM_CALLTYPE OnDownloadProgress(const TXString& url, bool isInProgress, bool isCompleted, bool isCanceled, Sint32 progress)	{ return ECallbackResult::Proceed; }

			// Notify for the content of the response after a request to a specific URL
			virtual ECallbackResult	VCOM_CALLTYPE OnRequestResponse(size_t id, const void* data, size_t dataSize)				{ return ECallbackResult::Proceed; }
  		};

		// ----------------------------------------------------------------------------------------------------
		// {7F0F75CE-A669-4FCC-956D-4428A2714C6C}
		static const TSinkIID IID_WebJavaScriptProvider			= { 0x7f0f75ce, 0xa669, 0x4fcc, { 0x95, 0x6d, 0x44, 0x28, 0xa2, 0x71, 0x4c, 0x6c } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWebJavaScriptProvider : public IEventSink
		{
		public:
			class DYNAMIC_ATTRIBUTE IInitContext
			{
			public:
				virtual	~IInitContext()		{}

				virtual IWebPaletteFrame*	GetWebFrame() = 0;	// borrowed pointer to the web frame, that belongs to the palette
				virtual void				AddExecute(const TXString& javaScriptCode) = 0;
				virtual void				AddVariable(const TXString& name, const VWVariant& value) = 0;
				// Add an asynchronous JavaScript function. The 'OnFunction' will be called on the Chromium UI thread without holding the JavaScript engine (which is in a separate Render Process)
				virtual void				AddFunction(const TXString& name) = 0;
			};

		public:
			virtual void		VCOM_CALLTYPE OnInit(IInitContext* context)	= 0;

			// the callback function should use the provided context to return data back to JavaScript (for JavaScript Promise support)
			// For example see the definition of VectorWorks::UI::IJSFunctionCallbackContex
			virtual void		VCOM_CALLTYPE OnFunction(const TXString& name, const std::vector<VWVariant>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)		{ }
  		};
	}
}