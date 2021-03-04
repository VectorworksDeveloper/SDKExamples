#import <Cocoa/Cocoa.h>
#import "Data.h"
#import "OnlyMac/Cocoa/NNAString.h"

@implementation AuthenticationTools

+(NSURLProtectionSpace*) createProtectionSpaceForBasicAuthentication:(const TXString&)storageName
{
    TXString baseUrl = storageName;
    
    TXString host = baseUrl;
    intptr_t at = baseUrl.Find("//");
    if ( at >= 0 )
        host = host.Mid( at + 2 );
    
    TXString protocol = "https";
    at = baseUrl.Find(':');
    if ( at >= 0 )
        protocol = baseUrl.Left( at );
    
    NSURLProtectionSpace* protectionSpace = [[NSURLProtectionSpace alloc]
                                             initWithHost:[NSString stringWithTXString:host]
                                             port:0
                                             protocol:[NSString stringWithTXString:protocol]
                                             realm:nil
                                             authenticationMethod:NSURLAuthenticationMethodHTTPBasic];
    return protectionSpace;
}

+(void) createCredentialForUsername:(const TXString&)userName
                           Password:(const TXString&)password
                        StorageName:(const TXString&)storageName
{
    NSString* user = [NSString stringWithTXString:userName];
    NSString* pass = [NSString stringWithTXString:password];
    NSURLCredential* credentialObject = [NSURLCredential credentialWithUser:user password:pass persistence:NSURLCredentialPersistencePermanent];
    
    NSURLProtectionSpace* protectionSpace = [AuthenticationTools createProtectionSpaceForBasicAuthentication:storageName];
    [[NSURLCredentialStorage sharedCredentialStorage] setCredential:credentialObject forProtectionSpace:protectionSpace];
}

+(bool) getCredentials:(TXString&)outUserName
              Password:(TXString&)outPassword
           StorageName:(const TXString&)storageName
{
    NSURLProtectionSpace* protectionSpace = [AuthenticationTools createProtectionSpaceForBasicAuthentication:storageName];
    
    NSDictionary* credentials = [[NSURLCredentialStorage sharedCredentialStorage] credentialsForProtectionSpace:protectionSpace];
    NSURLCredential* credential = [credentials.objectEnumerator nextObject];
    
    bool result = false;
    if ( credential )
    {
        outUserName = [credential.user toTXString];
        outPassword = [credential.password toTXString];
        result = true;
    }
    
    return result;
}

@end
