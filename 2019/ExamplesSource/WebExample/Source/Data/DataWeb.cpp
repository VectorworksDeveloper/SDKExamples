#include "StdAfx.h"

#include "DataWeb.h"
#include "Data.h"
#include "../UI/DlgLogin.h"

#define kConnectTimeoutLimit		6 /*seconds*/

using namespace Data;
using namespace UI;

extern bool gLocalDebugLogFileCreateEnabled;

#ifdef _WINDOWS
# ifndef CURL_STATICLIB
	// you must have this defined, otherwise you'll see unresolved curl functions during link
#  error In order to link properly, you must define CURL_STATICLIB in your project (typically in the Compiler properties of the project)
# endif
#endif

// --------------------------------------------------------------------------------------------------------------------
static int _Download_curlDebugCallback(CURL* curlHandle, curl_infotype type, char* data, size_t size, void* userptr)
{
	CGenericLogger* logger = (CGenericLogger*) userptr;

    std::string msg;
    std::string prefix;
    msg.assign(data, size);
    switch(type)
    {
        case CURLINFO_TEXT:			prefix = "Text: "; break;
        case CURLINFO_HEADER_IN:	prefix = "Header In: "; break;
        case CURLINFO_HEADER_OUT:	prefix = "Header Out: "; break;
        case CURLINFO_SSL_DATA_OUT:	prefix = "SSL Data Out: "; break;
		case CURLINFO_SSL_DATA_IN:	prefix = "Data In: "; break;
        case CURLINFO_DATA_IN:		prefix = "Dat In: "; break;
		case CURLINFO_DATA_OUT:		prefix = "Data Out: "; break;
        default: prefix = "?: "; break;
    }
	
	TXString str = prefix.c_str();
	str += " ";
	str += msg.c_str();
	str.Replace( "\n", "" );
	str.Trim();
	logger->AddLogLine( TXString::Formatted( "curl_debug_callback: %s", str ) );

    return 0;
}

static std::size_t _DownloadwriteBufferCallback(const char* in, std::size_t size, std::size_t num, std::vector<char>* out)
{
    const std::size_t totalBytes(size * num);
    if (totalBytes > 0)
        out->insert( out->end(), in, in+totalBytes);
    return totalBytes;
}

static size_t _DownloadwriteFileCallback(void* data, size_t elementSize, size_t elementCount, FILE** context)
{
	size_t written = std::fwrite( data, elementSize, elementCount, *context );

	return written;
}

int _XFeringInfoCallback(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	TProgressCallback callback = *(TProgressCallback*)p;

	int result = 0; // continue
	if ( ! callback( dltotal, dlnow, ultotal, ulnow ) )
		result = 1; // stop

	return result;
} 

// --------------------------------------------------------------------------------------------------------------------
CWebException::CWebException(const char* logInfo)
{
	fLogInfo = logInfo;
}

const char* CWebException::GetLogInfo() const throw()
{
	return fLogInfo;
}

// --------------------------------------------------------------------------------------------------------------------
CCurlRequest::CCurlRequest(CGenericLogger& logger, TProgressCallback progressCallback)
	: fLogger( logger )
	, fProgressCallback( progressCallback )
{
	fmapHeaders["Content-Type"] = "multipart/form-data";
	curl_global_init( CURL_GLOBAL_DEFAULT );
	fCurl = curl_easy_init();
}

CCurlRequest::~CCurlRequest()
{
	curl_easy_cleanup( fCurl );
	fCurl = nullptr;
}

void CCurlRequest::ClearHeaders()
{
	fmapHeaders.clear();
}

void CCurlRequest::SetHeader(const TXString& key, const TXString& value)
{
	fmapHeaders[key] = value;
}

CCurlRequest::ExecResult CCurlRequest::Execute(const TXString& url, const TParamValues& params, std::function<void(CURL* curl)> preSendCallback, std::string& outResultBody)
{
	std::vector<char>	body;

	ExecResult result = this->Execute( url, params, preSendCallback, body );

	size_t bodySize = body.size();
	if ( bodySize )
		outResultBody = std::string( &body[0], body.size() );
	else
		outResultBody = std::string();
	return result;
}

TXString CCurlRequest::URLEncodeParams(const TParamValues& params, bool addStartDelimiter)
{
	TXString	result;

	bool firstParam = true;
	for(const auto it : params)
	{
		result += firstParam ? (addStartDelimiter?"?":"") : "&";

		char* prmName = curl_easy_escape( fCurl, it.first.operator const char *(), DemoteTo<int>(kVStanev, it.first.GetEncodingLength( ETXEncoding::eUTF8 )) );
		result += prmName;
		curl_free( prmName );

		result += "=";

		char* prmValue = curl_easy_escape( fCurl, it.second.operator const char *(), DemoteTo<int>(kVStanev, it.second.GetEncodingLength( ETXEncoding::eUTF8 )) );
		result += prmValue;
		curl_free(prmValue);

		firstParam = false;
	}

	return result;
}

CCurlRequest::ExecResult CCurlRequest::Execute(const TXString& url, const TParamValues& params, std::function<void(CURL* curl)> preSendCallback, std::vector<char>& outResultBody)
{
	ExecResult result;

	if ( gLocalDebugLogFileCreateEnabled )
	{
		fLogger.AddLogLine( TXString::Formatted( "CCurlRequest::Execute: %s", url ) );
		for(const auto it : params)
		{
			fLogger.AddLogLine( TXString::Formatted( "               Param: %s = %s", it.first, it.second ) );
		}
	}

	if ( fCurl )
	{
		struct curl_slist*	headerslist = nullptr;
		for(const auto& it : fmapHeaders )
			headerslist = curl_slist_append( headerslist, it.first + ": " + it.second );

		if ( gLocalDebugLogFileCreateEnabled )
		{
			// log the request
			curl_easy_setopt(fCurl, CURLOPT_VERBOSE, 1L);
			curl_easy_setopt(fCurl, CURLOPT_DEBUGFUNCTION, _Download_curlDebugCallback);
			curl_easy_setopt(fCurl, CURLOPT_DEBUGDATA, & fLogger );
		}

		TXString fullURL = url;
		fullURL += this->URLEncodeParams( params, true );

		curl_easy_setopt(fCurl, CURLOPT_URL, fullURL.operator const char*());
		curl_easy_setopt(fCurl, CURLOPT_FAILONERROR, 1);
		curl_easy_setopt(fCurl, CURLOPT_NOPROGRESS, 1L);

		std::vector<char> readBody;
		curl_easy_setopt(fCurl, CURLOPT_WRITEFUNCTION, _DownloadwriteBufferCallback);
		curl_easy_setopt(fCurl, CURLOPT_WRITEDATA, &readBody);
		//std::string readHeader;
		//curl_easy_setopt(fCurl, CURLOPT_HEADERFUNCTION, _DownloadwriteCallback);
		//curl_easy_setopt(fCurl, CURLOPT_HEADERDATA, &readHeader);

		curl_easy_setopt(fCurl, CURLOPT_CONNECTTIMEOUT, kConnectTimeoutLimit);

		if ( fProgressCallback )
		{
			curl_easy_setopt(fCurl, CURLOPT_NOPROGRESS, FALSE);
			curl_easy_setopt(fCurl, CURLOPT_XFERINFOFUNCTION, _XFeringInfoCallback);
			curl_easy_setopt(fCurl, CURLOPT_XFERINFODATA, &fProgressCallback);
		}

		// this puts headers in the body, which screws up json decoding
		//curl_easy_setopt(fCurl, CURLOPT_HEADER, 1L);
		curl_easy_setopt(fCurl, CURLOPT_HTTPHEADER, headerslist);

		TXString proxy, address, userName, password;
		Sint32 port;
		if ( gSDK->GetCurlProxyInfo( proxy, address, port, userName, password ) )
		{
			curl_proxytype proxyType;
			if ( proxy.EqualNoCase("SOCKS4")  )
				proxyType = CURLPROXY_SOCKS4;
			else if ( proxy.EqualNoCase("SOCKS5")  )
				proxyType = CURLPROXY_SOCKS5;
			else
				proxyType = CURLPROXY_HTTP;

			CURLcode supported = curl_easy_setopt( fCurl, CURLOPT_PROXYTYPE, proxyType );
			if (supported == CURLE_OK)
			{
				curl_easy_setopt(fCurl, CURLOPT_PROXY, address.operator const char *());
				curl_easy_setopt(fCurl, CURLOPT_PROXYPORT, port);
				curl_easy_setopt(fCurl, CURLOPT_PROXYUSERNAME, userName.operator const char *());
				curl_easy_setopt(fCurl, CURLOPT_PROXYPASSWORD, password.operator const char *());
			}
			else
			{
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_setopt() unsupported proxy: %s", proxy ) );
			}
		}

		if ( preSendCallback )
			preSendCallback( fCurl );
		
		result.fCURLResult = curl_easy_perform(fCurl);

 		long httpResult = 0;
		curl_easy_getinfo(fCurl, CURLINFO_RESPONSE_CODE, &httpResult);
		result.fHTTPResult = httpResult;

		if ( result.fCURLResult == CURLE_OK )
		{
			if ( gLocalDebugLogFileCreateEnabled )
			{
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() RequestURL: %s", url ) );
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() execute result (%d): %s", result.fCURLResult, curl_easy_strerror(result.fCURLResult) ) );
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() HTTP result: %d", result.fHTTPResult ) );
			}

			if ( result.fHTTPResult == 200 )
			{
				outResultBody = readBody;
				result.fResult = true;
			}
		}
		else if ( result.fCURLResult == CURLE_ABORTED_BY_CALLBACK )
		{
			result.fResult = false;
		}
		else
		{
			// report an error in the log, unless it is one of the expected HTTP failures that will be handled by the caller
			if (  result.fHTTPResult == 404 )
			{
				result.fResult = false;
			}
			if (  result.fHTTPResult == 409 )
			{
				result.fResult = false;
			}
			else
			{
				result.fResult = false;
				const char* err = curl_easy_strerror( result.fCURLResult );
				err = err;

				fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() RequestURL: %s", url ) );
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() failed (%d): %s", result.fCURLResult, curl_easy_strerror(result.fCURLResult) ) );
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() HTTP result: %d", result.fHTTPResult ) );
			}
		}

		curl_slist_free_all( headerslist );
	}

	return result;
}

bool CCurlRequest::DownloadURL(const TXString& url, std::vector<char>& outBuffer)
{
	return this->DownloadURL( url, nullptr, &outBuffer );
}

bool CCurlRequest::DownloadURL(const TXString& url, IFileIdentifierPtr outputFile)
{
	std::vector<char> buffer;
	return this->DownloadURL( url, outputFile, nullptr );
}

bool CCurlRequest::DownloadURL(const TXString& url, IFileIdentifierPtr outputFile, std::vector<char>* outBuffer)
{
	bool result = false;

	TXString outputFilePath;
	if ( outputFile )
		outputFile->GetFileFullPath( outputFilePath );

	if ( gLocalDebugLogFileCreateEnabled )
	{
		fLogger.AddLogLine( TXString::Formatted( "CCurlRequest::DownloadURL: %s", url ) );
		if ( outputFile )
			fLogger.AddLogLine( TXString::Formatted( "    output in file: %s", outputFilePath ) );
		if ( outBuffer )
			fLogger.AddLogLine( "    output in buffer" );
	}

	CURL* _curl = curl_easy_init();
	if ( _curl )
	{
		TXString	strRequestURL = url;

		if ( gLocalDebugLogFileCreateEnabled )
		{
			// log the request
			curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1L);
			curl_easy_setopt(_curl, CURLOPT_DEBUGFUNCTION, _Download_curlDebugCallback);
			curl_easy_setopt(_curl, CURLOPT_DEBUGDATA, & fLogger );
		}

		curl_easy_setopt(_curl, CURLOPT_FAILONERROR, 1);
		curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, 1L);

		// Turning off peer verify is a security hole, but needed due to a failure
		// (PC only) complaining about a self-signed cert in the chain even though
		// https://www.digicert.com/help/ is perfectly happy.
		curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 2L);
	
		curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, kConnectTimeoutLimit);

		// https://curl.haxx.se/libcurl/c/example.html
		curl_easy_setopt( _curl, CURLOPT_URL, strRequestURL.operator const char*() );

		FILE* fileContext = nullptr;
		if ( outputFile )
		{
 			curl_easy_setopt( _curl, CURLOPT_WRITEFUNCTION, _DownloadwriteFileCallback );
			curl_easy_setopt( _curl, CURLOPT_WRITEDATA, &fileContext );
		}

		if ( outBuffer )
		{
			curl_easy_setopt(fCurl, CURLOPT_WRITEFUNCTION, _DownloadwriteBufferCallback);
			curl_easy_setopt(fCurl, CURLOPT_WRITEDATA, &outBuffer);
		}

		TXString proxy, address, userName, password;
		Sint32 port;
		if ( gSDK->GetCurlProxyInfo( proxy, address, port, userName, password ) )
		{
            curl_proxytype proxyType;
            if ( proxy.EqualNoCase("SOCKS4")  )
                proxyType = CURLPROXY_SOCKS4;
            else if ( proxy.EqualNoCase("SOCKS5")  )
                proxyType = CURLPROXY_SOCKS5;
            else
                proxyType = CURLPROXY_HTTP;

            CURLcode supported = curl_easy_setopt( _curl, CURLOPT_PROXYTYPE, proxyType );
            if (supported == CURLE_OK)
            {
                curl_easy_setopt(_curl, CURLOPT_PROXY, address.operator const char *());
                curl_easy_setopt(_curl, CURLOPT_PROXYPORT, port);
                curl_easy_setopt(_curl, CURLOPT_PROXYUSERNAME, userName.operator const char *());
                curl_easy_setopt(_curl, CURLOPT_PROXYPASSWORD, password.operator const char *());
            }
            else
            {
				fLogger.AddLogLine( TXString::Formatted( "curl_easy_setopt() unsupported proxy: %s", proxy ) );
            }
		}

		bool repeatDownloadAttempt;
		do
		{
			repeatDownloadAttempt = false;

			if ( outputFile )
			{
				std::remove( outputFilePath );

				fileContext	= std::fopen( outputFilePath, "wb" );
			}

			if ( fileContext )
			{
				CURLcode res = curl_easy_perform( _curl );

				if ( fileContext )
				{
					std::fclose( fileContext );
					fileContext = nullptr;
				}

				long httpResult = 0;
				curl_easy_getinfo( _curl, CURLINFO_RESPONSE_CODE, &httpResult );

				if ( res != CURLE_OK )
				{
					fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() RequestURL: %s", strRequestURL ) );
					fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() HTTP Result: %d", httpResult ) );
					fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() CURL failed (CURLcode=%d): %s", res, curl_easy_strerror(res) ) );
				}
				else
				{
					if( (res == CURLE_OK) && ((httpResult / 100) != 3))
					{
						// a redirect implies a 3xx response code
						result = true;
					}
					else
					{
						char* location = nullptr;
						res = curl_easy_getinfo( _curl, CURLINFO_REDIRECT_URL, &location );
 
						if((res == CURLE_OK) && location)
						{
							// This is the new absolute URL that you could redirect to, even if
							// the Location: response header may have been a relative URL.
							curl_easy_setopt( _curl, CURLOPT_URL, location);
							strRequestURL = location;
							repeatDownloadAttempt = true;
						}
						else
						{
							fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() RequestURL: %s", strRequestURL ) );
							fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() HTTP Result: %d", httpResult ) );
							fLogger.AddLogLine( TXString::Formatted( "curl_easy_perform() CURL failed (CURLcode=%d): %s", res, curl_easy_strerror(res) ) );
						}
					}
				}
			}
			else
			{
				fLogger.AddLogLine( TXString::Formatted( "Could not open download file for write: %s", outputFilePath ) );
			}
		} while ( repeatDownloadAttempt );

		curl_easy_cleanup( _curl );
		_curl = nullptr;
	}
	else
	{
		fLogger.AddLogLine( "curl_easy_init(); failed!" );
	}

	return result;
}

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------
CWebContext::CWebContext(const TXString& serverURL)
	: fErrorLogger( kExternalDataFolder, TXString(DefaultPluginVWRIdentifier()) + "_WebContextLog.txt" )
	, fProgressCallback( nullptr )
    , fServerURL( serverURL )
{
}

CWebContext::~CWebContext()
{
}

CGenericLogger& CWebContext::GetErrorLogger()
{
	return fErrorLogger;
}

const TXString& CWebContext::GetOAuthToken()
{
	this->QueryOAuth( false );
	return fOAuthToken;
}

const TXString& CWebContext::GetUserToken() const
{
	return fUserToken;
}

const TXString& CWebContext::GetServerURL() const
{
    return fServerURL;
}

void CWebContext::SetServerURL(const TXString& value)
{
    fServerURL = value;
}

void CWebContext::SetProgressCallback(TProgressCallback callback)
{
	fProgressCallback = callback;
}

TProgressCallback CWebContext::GetProgressCallback() const
{
	return fProgressCallback;
}


bool CWebContext::LogInIfNeeded(bool force)
{
	bool result = false;

	bool alreadyLoggedIn = false;
	if (!force) // when forcing, it doesn't matter if we are logged in or not
		//alreadyLoggedIn = !this->GetOAuthToken().IsEmpty();
		alreadyLoggedIn = !this->fUserToken.IsEmpty();
	if (alreadyLoggedIn)
		result = true;

	if (force || !alreadyLoggedIn)
	{
		CUserCredentials& userCredentials = CUserCredentials::Instance();

		TXString	username, password;
		userCredentials.GetCredentials(username, password);

		if (!alreadyLoggedIn && !force)
		{
			if (!username.IsEmpty() && !password.IsEmpty())
				result = this->LogIn(username, password);
		}

		if (!result || force)
		{
			TXString	strRememberValue;
			gSDK->GetSavedSetting("ExtMenuESRI", "rememberLogin", strRememberValue);
			bool		rememberLogin = (/*strRememberValue.IsEmpty() ||*/ strRememberValue == "yes" || strRememberValue == "true");

			while (true)
			{
				CDlgLogin	dlg(alreadyLoggedIn && !force, username, password, rememberLogin);
				if (dlg.RunDialogLayout("LogInToService") == kDialogButton_Ok)
				{
					dlg.GetData(username, password, rememberLogin);

					gSDK->SetSavedSetting("ExtMenuESRI", "rememberLogin", rememberLogin ? "yes" : "no");
					userCredentials.SetCredentials(username, password);

					if (alreadyLoggedIn)
					{
						// log out
						fUserToken.Clear();
						if (!rememberLogin)
						{
							userCredentials.ClearUserStoredCredentials();
							userCredentials.SetCredentials("", "");
						}

						VWDialog::AlertInform(TXResStr("ExtMenuESRI", "alert_logout_msg"));

						break;
					}
					else
					{
						result = this->LogIn(username, password);

						if (result)
						{
							if (rememberLogin && !username.IsEmpty() && !password.IsEmpty())
								userCredentials.SaveUserStoredCredentials();
							else
								userCredentials.ClearUserStoredCredentials();

							using namespace VectorWorks::UI;
							IInfoBarPtr	pInfoBar(IID_InfoBar);
							if (pInfoBar)
							{
								pInfoBar->SetMinorAlert(TXResStr("ExtMenuESRI", "alert_login_ok_msg"), eInfoMsgBackColor_Standard);
							}
							break;
						}
						else
						{
							if (!rememberLogin)
								userCredentials.ClearUserStoredCredentials();

							VWDialog::AlertInform(
								TXResStr("ExtMenuESRI", "alert_login_err_msg"),
								TXResStr("ExtMenuESRI", "alert_login_err_adv"));

						}
					}
				}
				else
				{
					result = false;
					break;
				}
			}
		}
	}

	return result;
}

bool CWebContext::LogIn(const TXString& username, const TXString& password)
{
	fUserToken.Clear();

	this->QueryOAuth(false);

	CCurlRequest	curlRequest(fErrorLogger, fProgressCallback);

	bool result = false;

	std::string	resultBody;
	CCurlRequest::ExecResult execResult = curlRequest.Execute(
		"https://<SERVER>/generateUserToken",
		TParamValues(),
		[&](CURL* curl)
	{
		struct curl_httppost *post = NULL;
		struct curl_httppost *last = NULL;

		curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "access_token",
			CURLFORM_COPYCONTENTS, fOAuthToken.operator const char*(),
			CURLFORM_END
		);

		curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "username",
			CURLFORM_COPYCONTENTS, username.operator const char*(),
			CURLFORM_END
		);

		curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "password",
			CURLFORM_COPYCONTENTS, password.operator const char*(),
			CURLFORM_END
		);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	},
		resultBody);

	if (execResult.fResult)
	{
		Json::Reader jsonReader;
		Json::Value jsonResponse;
		if (jsonReader.parse(resultBody, jsonResponse))
		{
			bool success = true;
			if (jsonResponse.isMember("error"))
			{
				TXString errorStr = jsonResponse["error"].asCString();
				errorStr;
				success = false;
			}

			if (success)
			{
				if (jsonResponse.isMember("token"))
				{
					fUserToken = jsonResponse["token"].asCString();
					result = !fUserToken.IsEmpty();
				}
			}
		}

	}

	return result;
}

bool CWebContext::QueryOAuth(bool force)
{
	bool result = true;
	if ( fOAuthToken.IsEmpty() || force )
	{
		CCurlRequest	curlRequest( fErrorLogger, fProgressCallback );

		std::string	resultBody;
		CCurlRequest::ExecResult execResult = curlRequest.Execute(
			"https://<SERVER>/rest/oauth2/token",
			TParamValues(),
			[&](CURL* curl)
			{
				struct curl_httppost *post = NULL;
				struct curl_httppost *last = NULL;

				curl_formadd(&post, &last,
					CURLFORM_COPYNAME, "client_id",
					CURLFORM_COPYCONTENTS, "XXXXXXXXXXXXXXXXXXXX", 
					CURLFORM_END
				);

				curl_formadd(&post, &last,
					CURLFORM_COPYNAME, "client_secret",
					CURLFORM_COPYCONTENTS, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 
					CURLFORM_END
				);

				curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
			},
			resultBody );

		result = false;
		if ( execResult.fResult )
		{
			Json::Reader jsonReader;
			Json::Value jsonResponse;
			if ( jsonReader.parse( resultBody, jsonResponse ) )
			{
				if ( jsonResponse.isMember( "access_token" ) )
				{
					fOAuthToken = jsonResponse["access_token"].asCString();
					result = ! fOAuthToken.IsEmpty();
				}
			}
		}
	}

	return result;
}

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------
CExampleRequest::CExampleRequest(CWebContext& webContext)
	: fWebContext( webContext )
{
}

CExampleRequest::~CExampleRequest()
{
}

void CExampleRequest::DoWork()
{
	TXString accessToken = fWebContext.GetOAuthToken();
	TXString userToken = fWebContext.GetUserToken();

	CCurlRequest	curlRequest( fWebContext.GetErrorLogger(), fWebContext.GetProgressCallback() );

	std::string	resultBody;
	CCurlRequest::ExecResult execResult = curlRequest.Execute(
		fWebContext.GetServerURL() + "/rest/command",
		TParamValues() = { 
			{"f",				"json"},
			{"access_token",	accessToken},
			{"user_token",		userToken},
			{"data1",			"123"},
			{"data2",			"456"},
		},
		nullptr,
		resultBody );

	if ( execResult.fResult )
	{
		Json::Reader jsonReader;
		Json::Value jsonResponse;
		jsonReader.parse( resultBody, jsonResponse );
	}
}
