//
//  NNAImageResourceCategory.h
//  Vectorworks SDK
//
//  Created by Lyndsey Ferguson on 7/26/13.
//
//

#import <Cocoa/Cocoa.h>

enum ENNAImageSizeType
{
	eNNAImageSizeType_Natural	= 0,
	eNNAImageSizeType_Dialog	= 1
};

@interface NSImage (NNAImageResourceCategory)

+ (NSImage*) imageWithIconSpecifier:(const char*)iconSpec;
+ (NSImage*) imageWithIconSpecifier:(const char*)iconSpec sizeType:(ENNAImageSizeType)sizeType;

@end
