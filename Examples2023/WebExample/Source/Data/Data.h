#pragma once


namespace Data
{
    // ------------------------------------------------------------------------------------------------------
	class CUserCredentials
	{
	protected:
		CUserCredentials();
	public:
		virtual	~CUserCredentials();

		static CUserCredentials& Instance();

		void	SetCredentials(const TXString& username, const TXString& password);
		bool	GetCredentials(TXString& outUsername, TXString& outPassword) const;
		bool	LoadUserStoredCredentials();
		void	SaveUserStoredCredentials();
		void	ClearUserStoredCredentials();

	private:
		size_t				fUserCredentialsDataSize;
		std::vector<char>	fUserCredentialsBuffer;
		bool				fUserCredentialsDirty;
	};


	// ------------------------------------------------------------------------------------------------------
	class CCommunicationProgressDlg : protected CProgressDlg
	{
	public:
					CCommunicationProgressDlg();

		void		Open_Login();
		void		Close();

		enum class EContext
		{
			// Login
			Communicating,
			LoggingIn,
		};

		void		Begin(EContext context);
		void		Begin(double percent, Sint32 loopCount);
		void		End();

		void		DoYield();
		bool		HasCancel();

	private:
		bool	fVisible;
	};
}

// ---------------------------------------------------------------------------------------------------------------------------
#ifndef _WINDOWS

@interface AuthenticationTools : NSObject
{
}

+(NSURLProtectionSpace*)createProtectionSpaceForBasicAuthentication:(const TXString&)storageName;

+(void)createCredentialForUsername : (const TXString&)userName
                          Password : (const TXString&)password
                       StorageName : (const TXString&)storageName;

+(bool)getCredentials : (TXString&)outUserName
             Password : (TXString&)outPassword
          StorageName : (const TXString&)storageName;

@end

#endif
