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

/*!
 * Returns the order that is to be used when
 *  formatting date values
 *  @return An Sint16 value (0 = MDY, 1 = DMY, 2 = YMD)
 */
+(Sint16)dateOrder;

/*!
 * Returns whether the complete year should be used
 * when fomatting date values.
 * @return A bool value indicating whether to use
 * 		   the complete year
 */
+(bool)completeYear;

/*!
 * Returns whether to use leading zeros for the month and
 * date when formatting date values.
 * @return A bool value indicating whether to use
 * 		   leading zeros for month and date
 */
+(bool)leadingZeros;

@end
