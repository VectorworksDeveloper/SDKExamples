//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		using namespace VectorWorks::Extension;

		// ------------------------------------------------------------------------------------------------------
		// Utility function to generate the standard URL for when the front-end is inside the plug-ins .vwr resource folder
		// Uses the plugins 'DefaultPluginVWRIdentifier' function to get the name of the VWR folder
		// DEBUG will use short-cuts/aliaces to point directly to the .VWR folder, allowing palette/dialog refresh to pick up changes (for dev purposes)
		// For dev purpuses the URL can be overriden via .vwr files placed in the user's folder.
		// This allows the URL of the feature to be redirected and this way front-end can be delveloped with autobuild version.
		//		file:	"DevSettings_" + DefaultPluginVWRIdentifier() + ".vwr/Strings/settings.vwstrings"
		//		key:	"url"
		// Param "htmlFolderName" - override the name of the folder containing the html. By default it's "html"
		// Param "htmlFile" -- override the html file that will be loaded. By default it's "index.html"
		TXString	GetStandardURL(const TXString& htmlFolderName = "html", const TXString& htmlFile = "index.html");

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionPaletteJSProvider : public VCOMImmediateImpl<IWebJavaScriptProvider>
		{
		public:
						VWExtensionPaletteJSProvider(IVWUnknown* parent);
			virtual		~VWExtensionPaletteJSProvider();

		public:
			virtual void	OnInit(IInitContext* context) override;
			virtual void	OnFunctionCall(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context) = 0;

		protected:
			virtual void	OnFunction(const TXString& name, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context) override;

		protected:
			IVWUnknown*			fParent;
			IWebPaletteFrame*	fWebFrame		= nullptr;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionWebPalette :	public VCOMImmediateImpl<IExtensionWebPalette>
		{
		public:
						VWExtensionWebPalette();
						VWExtensionWebPalette(const char* htmlFolderName);
						VWExtensionWebPalette(const char* htmlFolderName, const char* htmlFile);
			virtual		~VWExtensionWebPalette();

		public:
			virtual void						DefineSinks() = 0;
			template<class T> void				DefineSink(const TSinkIID& sinkIID);

		// IExtensionWebPalette
		public:
			virtual IEventSink* VCOM_CALLTYPE	QueryEventSink(const TSinkIID& iid);
			virtual TXString	VCOM_CALLTYPE	GetInitialURL();

		protected:
			virtual void						OnRefCountZero();
			virtual bool						GetProtectionSinkIID(TSinkIID& outIID);
			virtual IProviderProtection*		CreateProtectionSink(IVWUnknown* parent);


		private:
			typedef std::map<TSinkIID, IEventSink*> TSinksMap;
			TSinksMap			fmapSinks;
			TSinkIID			fDefinedSinkIID	= {};
			IEventSink*			fDefinedSink	= nullptr;

			bool				fProtectionObtained = false;
			bool				fHasProtection = false;
			TSinkIID			fProtectionSinkIID;

			TXString			fHTMLFolderName;
			TXString			fHTMLFile;
		};
	}

	namespace PluginSupport
	{
		template<class T> void VWExtensionWebPalette::DefineSink(const TSinkIID& sinkIID)
		{
			if ( fDefinedSink == NULL && sinkIID == fDefinedSinkIID ) {
				T*	instance	= SDK_NEW T( this );
				fDefinedSink	= instance;
			}
		}
	}
}

#define		DEFINE_WebPalette_DISPATCH_MAP						virtual void OnFunctionCall(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);

#define		BEGIN_WebPalette_DISPATCH_MAP(clas)					void clas::OnFunctionCall(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context) { \
																	if ( false ) ;
#define		ADD_WebPalette_FUNCTION(TName, TFunction)				else if ( functionName == TName ) TFunction( objName, functionName, args, context );
#define		END_WebPalette_DISPATCH_MAP								else { DSTOP((kVStanev, "Unknown Web JS function hook: %s.%s", objName.operator const char*(), functionName.operator const char*())); } \
																}
