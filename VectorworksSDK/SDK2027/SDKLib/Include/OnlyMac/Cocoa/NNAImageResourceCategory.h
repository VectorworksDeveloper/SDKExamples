//
//  NNAImageResourceCategory.h
//  Vectorworks SDK
//
//  Created by Lyndsey Ferguson on 7/26/13.
//
//

#import <Cocoa/Cocoa.h>

@interface NSImage (NNAImageResourceCategory)

+ (NSImage*) imageWithIconSpecifier:(const char*)iconSpec;

@end
