//
//  UiControlTintType.h
//  VectorWorks
//
//  Created by Ayodeji Oshinnaiye on 8/28/18.
//

#pragma once

/*!
 *  Text color tints - UI text colors
 *   cannot be directly specified from
 *   outside of UI code, as the colors
 *   may conflict with the color associated
 *   with a specific usage context, as
 *   imposed by the active UI appearance.
 *   Color tints are not guaranteed to
 *   appear as expected.
 */
enum class EUiControlTextTint
{
    // Context-specific tints
    eDefaultTint,
    eDisabledTint,
    eRotatedCoordTint,
    ePageBasedSymTint,
    ePluginSymTint,
    eGroupSymTint,
    eAllLayersTint,
    eCustomItem1Tint,
    
    // Approximate color tints
    // (only present for compatibility
    // with legacy, user-selected
    // color reproduction behavior -
    // context-specific tints should
    // be used when possible, or amended
    // if a specific tint is absent)
    eGenericRedTint,
    eGenericGreenTint,
    eGenericBlueTint,
    eGenericOrangeTint,
    eGenericYellowTint,
    eGenericBrownTint,
    eGenericPurpleTint,
    eGenericPinkTint,
    eGenericGrayTint,
	eGenericBlackTint,
	eGenericWhiteTint
};
