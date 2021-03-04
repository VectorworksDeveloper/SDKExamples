#include "StdAfx.h"

#include "Data.h"
#include "DataWeb.h"

#ifdef _WINDOWS
# include <wincred.h>
#endif

// ------------------------------------------------------------------------------------------------------
// Use local fixed encryption for added security
// This is not GDPR compliant, it's only to encrypt the data for store in memory
// GDPR compliance comes from storing in the OS credential storage
const char* kPasswordEncryptKeyword		= "afRU=a?jpW8`/}M2";

// the name under which the data will be stored in the OS credential storage
const char* kCredentialStorageURL		= "https://www.myserver.com";

using namespace Data;

// ---------------------------------------------------------------------------------------------------------------------------
CUserCredentials::CUserCredentials()
{
}

CUserCredentials::~CUserCredentials()
{
}

/*static*/ CUserCredentials& CUserCredentials::Instance()
{
    static CUserCredentials sInstance;
    static bool sCredentialsLoaded = false;
    
    if (!sCredentialsLoaded)
    {
        sInstance.LoadUserStoredCredentials();
        sCredentialsLoaded = true;
    }
    
    return sInstance;
}

void CUserCredentials::SetCredentials(const TXString& username, const TXString& password)
{
    TXString thisUsername, thisPassword;
    bool thisOk = this->GetCredentials(thisUsername, thisPassword);
    if (thisOk == false || (thisUsername != username || thisPassword != password))
    {
        TXString data = username + ":" + password;
        
        VWFC::Tools::CEncryptedData	encrypt;
        encrypt.Set(data, kPasswordEncryptKeyword);
        
        fUserCredentialsDataSize = encrypt.GetDataSize();
        encrypt.GetMemory(fUserCredentialsBuffer);
        fUserCredentialsDirty = true;
    }
}

bool CUserCredentials::GetCredentials(TXString& outUsername, TXString& outPassword) const
{
    outUsername.Clear();
    outPassword.Clear();
    
    bool result = false;
    
    if (fUserCredentialsDataSize > 0 && fUserCredentialsBuffer.size() > 0)
    {
        VWFC::Tools::CEncryptedData	decrypt(fUserCredentialsBuffer, fUserCredentialsDataSize);
        TXString data = decrypt.Get(kPasswordEncryptKeyword);
        
        ptrdiff_t at = data.Find(':');
        if (at >= 0)
        {
            outUsername = data.Left(at);
            outPassword = data.Mid(at + 1);
            result = true;
        }
    }
    
    return result;
}

bool CUserCredentials::LoadUserStoredCredentials()
{
    bool result = false;
    
    TXString username, password;
    
#ifdef _WINDOWS
    TXString targetName = kCredentialStorageURL;
    
    PCREDENTIALW pcred;
    BOOL ok = ::CredReadW(targetName, CRED_TYPE_GENERIC, 0, &pcred);
    if (ok)
    {
        TXString data((const char*)pcred->CredentialBlob, pcred->CredentialBlobSize);
        
        ptrdiff_t at = data.Find(':');
        if (at >= 0)
        {
            username = data.Left(at);
            password = data.Mid(at + 1);
            result = true;
        }
    }
    ::CredFree(pcred);
#else
    result = [AuthenticationTools getCredentials : username
                                        Password : password
                                     StorageName : kCredentialStorageURL];
#endif
    
    this->SetCredentials(username, password);
    fUserCredentialsDirty = false;
    
    return result;
}

void CUserCredentials::SaveUserStoredCredentials()
{
    if (fUserCredentialsDirty)
    {
        TXString username, password;
        this->GetCredentials(username, password);
        
#ifdef _WINDOWS
        TXString targetName = kCredentialStorageURL;
        
        TXString data = username + ":" + password;
        
        CREDENTIALW cred = { 0 };
        cred.Type = CRED_TYPE_GENERIC;
        cred.TargetName = (LPWSTR)targetName.operator const wchar_t *();
        cred.CredentialBlob = (LPBYTE)data.operator const char* ();
        cred.CredentialBlobSize = (DWORD)data.GetEncodingLength(ETXEncoding::eUTF8);
        cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
        cred.UserName = (LPWSTR)username.operator const wchar_t * ();
        
        BOOL ok = ::CredWriteW(&cred, 0);
        ok;
        
#else
        [AuthenticationTools createCredentialForUsername : username
                                                Password : password
                                             StorageName : kCredentialStorageURL];
#endif
    }
}

void CUserCredentials::ClearUserStoredCredentials()
{
#ifdef _WINDOWS
    TXString targetName = kCredentialStorageURL;
    
    BOOL ok = ::CredDeleteW(targetName, CRED_TYPE_GENERIC, 0);
    ok;
#else
    TXString empty;
    [AuthenticationTools createCredentialForUsername : empty
                                            Password : empty
                                         StorageName : kCredentialStorageURL];
#endif
    
    fUserCredentialsDirty = true;
}


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CCommunicationProgressDlg::CCommunicationProgressDlg()
: CProgressDlg(EProgressLayoutType::Narrow)
, fVisible(false)
{
}

void CCommunicationProgressDlg::Open_Login()
{
    if (!fVisible)
        CProgressDlg::OpenInfiniteDelayed(TXResStr("ExtMenuESRI", "progress_login_title"), true);
    fVisible = true;
}

void CCommunicationProgressDlg::Close()
{
    CProgressDlg::Close();
    fVisible = false;
}

void CCommunicationProgressDlg::Begin(EContext context)
{
    if (fVisible)
    {
        switch (context)
        {
                // Login
            case EContext::Communicating:	CProgressDlg::SetMeterText(TXResStr("ExtMenuESRI", "progress_login_msg_comm"));		break;
            case EContext::LoggingIn:		CProgressDlg::SetMeterText(TXResStr("ExtMenuESRI", "progress_login_msg_working"));	break;
                
            default:
                CProgressDlg::SetMeterText("");
                break;
        }
        
        CProgressDlg::Start(100, 1);
    }
}

void CCommunicationProgressDlg::Begin(double percent, Sint32 loopCount)
{
    if (fVisible)
    {
        CProgressDlg::Start(percent, loopCount);
    }
}

void CCommunicationProgressDlg::End()
{
    if (fVisible)
        CProgressDlg::End();
}

void CCommunicationProgressDlg::DoYield()
{
    if (fVisible)
        CProgressDlg::DoYield();
}

bool CCommunicationProgressDlg::HasCancel()
{
    bool result = false;
    if (fVisible)
        result = CProgressDlg::HasCancel();
    return result;
}
