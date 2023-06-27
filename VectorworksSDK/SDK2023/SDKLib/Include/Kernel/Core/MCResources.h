//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

//#######################################################################################
// This function is left unimplemented in the SDK as all plugins should implement it individially.
// If they dont, there will be a linker error of undefined external symbol
// The purpose of the function is to provide the VWR file name for each plugin when using TXResStr, TXResource, and TXLegacyResource APIs.
// All string related functions in the SDK use this function to get the base for resource files
const char* DefaultPluginVWRIdentifier();

#define NNA_WARN_ABOUT_EMPTY_STRING_RESOURCES 1

//#######################################################################################
class TXResource
{
public:
	TXResource(const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty = eDontAllowEmptyResult);
	TXResource(const char* resourceIdentifier);
	~TXResource();

	operator const TXString&();

	const char*		c_str();
	size_t			Size() const;
	const void*		Buffer() const;
	GSHandle 		GetHandle();

protected:
	TXResource(const TXResource& src);
	TXResource& operator = (const TXResource& src);

private:
	TXString	fString;
	GSHandle	fResource;
};

// TXResStr is a convenience type intended to standardize requests for localized strings
//  in a concise way.  It assumes the default vwr contains the file in a "Strings" directory,
//  and that the strings file has extension ".vwstrings"
class TXResStr
{
public:
	TXResStr(const char* stringsFileNameWithoutPathOrExtension, const char* resourceStringIdentifier, EEmptyHandling allowEmpty=eDontAllowEmptyResult);
	operator const TXString&();
private:
	TXString	fString;
};


//#######################################################################################
class TXLegacyResource
{
public:
	TXLegacyResource(short stringResID, short indexID, EEmptyHandling allowEmpty = eDontAllowEmptyResult);
	TXLegacyResource(const char* defaultResourceIdentifier, short stringResID, short indexID, EEmptyHandling allowEmpty = eDontAllowEmptyResult);
	TXLegacyResource(short textResID);
	TXLegacyResource(const char* resourceType, short resourceID);
	// I introduce this constructor only to help replace the legacy ISDK::GSGetResourceString call
	// there are 500+ calls and it is pain (high risk) to change those calls just like that
	TXLegacyResource(short stringResID, short indexID, TXString& outString);
	~TXLegacyResource();

	operator const TXString&();

	const char*		c_str();
	size_t			Size() const;
	const void*		Buffer() const;
	GSHandle 		GetHandle();

protected:
	TXLegacyResource(const TXLegacyResource& src);
	TXLegacyResource& operator = (const TXLegacyResource& src);

private:
	TXString	fString;
	GSHandle	fResource;
};

//#######################################################################################
class TXLegacyDialogResource
{
public:
	TXLegacyDialogResource(short dialogResourceID);

	operator const char*();

private:
	TXString	fString;
};
