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

@interface NSString (NNAStringCategory) 

+ (NSString*) stringWithTXString:(const TXString &)txs;
+ (NSString*) stringWithoutAmpersandWithTXString:(const TXString &)txs;

+ (NSString*) stringWithUUID;
+ (NSString*) stringWithLeadingZerosStrippedFromString:(NSString*)theString;
+ (NSString*) stringForKeyCode:(unsigned short)keyCode withModifierFlags:(NSUInteger)modifierFlags;

- (TXString)  txString;
- (TXString)  toTXString;
- (NSRange)	  rangeOfRepeatingCharacters:(NSCharacterSet*)aCharacter;
- (CGRect)    dimensionsForAttributedString:(NSAttributedString *)asp;
- (CGRect)    dimensionsForString:(NSString*) s font: (NSString*)fontName size:(CGFloat)fontSize;

- (unichar)   SafeCharacterAtIndex:(NSUInteger)index;  // returns 0 if index is out of range instead of throwing exception

@end


inline GS_HIDDEN_VISIBILITY NSString* NSStringWithIDAndIndex(short stringResourceID, short index, bool assert=true)
{
	return [NSString stringWithTXString:TXLegacyResource(stringResourceID, index, eAllowEmptyResult)];
}


inline GS_HIDDEN_VISIBILITY NSString* NSStringWithoutAmpersandWithIDAndIndex(short stringResourceID, short index)
{
	return [NSString stringWithoutAmpersandWithTXString:TXLegacyResource(stringResourceID, index)];
}
