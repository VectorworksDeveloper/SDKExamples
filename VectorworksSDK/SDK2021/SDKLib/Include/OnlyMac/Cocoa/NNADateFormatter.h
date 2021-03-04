//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#import <Cocoa/Cocoa.h>

#ifndef __cplusplus
	#error This file should only be included by Objective-C++ source files.
#endif

extern const Sint16 NNADateOrderMDY;
extern const Sint16 NNADateOrderDMY;
extern const Sint16 NNADateOrderYMD;

@interface NSDateFormatter (NNADateFormatterCategory)

/*!
 * Returns the time separator that is to be
 *  used when formatting time values
 * @return An NSString object that contains the time
 *         separator (autoreleased when used within an
 *         autorelease pool)
 */
+(NSString*)timeSeparator;

/*!
 * Returns the date separator that is to be
 *  used when formatting date values
 * @return An NSString object that contains the data
 *         separator (autoreleased when used within an
 *         autorelease pool)
 */
+(NSString*)dateSeparator;
+(Sint16)dateOrder;

@end
