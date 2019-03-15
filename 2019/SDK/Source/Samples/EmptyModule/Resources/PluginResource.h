//
//	PluginResource.h
//
//	Copyright © Nemetschek North America, Inc  2005.
//	All Rights Reserved.
//
// Contain constands for the access to the resources

#pragma once

// define C++ constants for resources indices defined in PluginResource.r

enum {
	kWarningString = 10010,
	
	kString1 = 1,
	kString2 = 2
};

// You can define string ID's as constant shorts still...
const short kPluginStringResourceID = 10000;
const short kTestStringIndex = 1;

// Or use the modern format where they are specified by character values
const char* kModernTestStringName = "ModernTestString";
const char* kModernTestStringResourceName = "EmptyModule/Strings/11000 *";

