#pragma once

#include "json/json.h"
#include "curl.h"

using namespace VectorWorks::Filing;

namespace Data
{
	using namespace VWFC::Tools;

	// ---------------------------------------------------------------------------------------------------------------------------
	// return true to continue; false to stop
	typedef std::function<bool(Sint64 dltotal, Sint64 dlnow, Sint64 ultotal, Sint64 ulnow)>	TProgressCallback;
	typedef std::function<void(CURL* curl)>													TCURLCallback;
	typedef std::map<TXString, TXString>													TParamValues;

	// ---------------------------------------------------------------------------------------------------------------------------
	class CWebException : public std::exception
	{
	public:
		CWebException(const char* logInfo);

		const char* GetLogInfo() const throw();

	private:
		const char* fLogInfo;
	};

	// ---------------------------------------------------------------------------------------------------------------------------
	class CCurlRequest
	{
	public:
				CCurlRequest(CGenericLogger& logger, TProgressCallback progressCallback);
		virtual	~CCurlRequest();

		void	ClearHeaders();
		void	SetHeader(const TXString& key, const TXString& value);

		struct ExecResult
		{
			bool		fResult;
			CURLcode	fCURLResult;
			Sint32		fHTTPResult;

			ExecResult() { fResult = false; fCURLResult = CURL_LAST; fHTTPResult = 0; }
		};

		ExecResult	Execute(const TXString& url, const TParamValues& params, TCURLCallback preSendCallback, std::string& outResultBody);
		ExecResult	Execute(const TXString& url, const TParamValues& params, TCURLCallback preSendCallback, std::vector<char>& outResultBody);
            

		bool		DownloadURL(const TXString& url, std::vector<char>& outBuffer);
		bool		DownloadURL(const TXString& url, IFileIdentifierPtr outputFile);

	// Tools
	public:
		TXString	URLEncodeParams(const TParamValues& params, bool addStartDelimiter);
            
	private:
		bool		DownloadURL(const TXString& url, IFileIdentifierPtr outputFile, std::vector<char>* outBuffer);

	private:
		CGenericLogger&					fLogger;
		TProgressCallback				fProgressCallback;
		CURL*							fCurl;
		std::map<TXString, TXString>	fmapHeaders;
	};

	// ---------------------------------------------------------------------------------------------------------------------------
	class CWebContext
	{
	public:
				CWebContext(const TXString& serverURL);
		virtual	~CWebContext();

		CGenericLogger&		GetErrorLogger();
		const TXString&		GetOAuthToken();
		const TXString&		GetUserToken() const;
            
        const TXString&     GetServerURL() const;
        void                SetServerURL(const TXString& value);

		void				SetProgressCallback(TProgressCallback callback);
		TProgressCallback	GetProgressCallback() const;

        bool        LogInIfNeeded(bool force);
		bool        LogIn(const TXString& username, const TXString& password);
		bool		QueryOAuth(bool force);

	private:
		CGenericLogger		fErrorLogger;
		TProgressCallback	fProgressCallback;
		TXString			fOAuthToken;
 		TXString			fUserToken;
		TXString            fServerURL;
	};

	// ---------------------------------------------------------------------------------------------------------------------------
	class CExampleRequest
	{
	public:
					CExampleRequest(CWebContext& webContext);
		virtual		~CExampleRequest();

		void	DoWork();

	protected:

	private:
		CWebContext&	fWebContext;
	};

}
