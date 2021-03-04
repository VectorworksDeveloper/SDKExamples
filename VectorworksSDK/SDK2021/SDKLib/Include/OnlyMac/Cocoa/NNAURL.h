//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#import <Cocoa/Cocoa.h>

#ifndef __cplusplus
	#error This file should only be included by Objective-C++ source files.
#endif

class TXString;

@interface NSURL (NNAURLCategory) 

- (TXString)txStringPath;

@end
