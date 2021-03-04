//
//  CoreUiTintSupport.h
//  NNACore A to M
//
//  Created by Ayodeji Oshinnaiye on 8/17/18.
//

#pragma once
#include "UiControlTintType.h"
#include "MiniCadCallBacks.h"
#include "GSGeometry.h"


/*!
 *  Classes and functions that support the
 *   usage of UI color tints (generalized
 *   application/modification of UI color
 *   tones that permit the UI to apply the
 *   appropriate contextual modifications
 *   required to promote element visibility /
 *   legibility).
 *
 *  @see EUiControlTextTint
 */
namespace CoreUiTintSupport
{
    /*!
     *  Converts a specific RGB color specification
     *   into a generalized UI tint
     *
     *  @param queryColor Specific RGB color specification
     *
     *  @return A color tint value that roughly corresponds to
     *          the provided RGB color specification
     *
     *  @author Ayodeji Oshinnaiye, August 9, 2018
     */
    EUiControlTextTint ExpressColorAsTint(const COLORREF& queryColor);
    EUiControlTextTint ExpressColorAsTint(const GSColor& queryColor);
    
    /*!
     *  Expresses a tint as an approximate RGB
     *   color specification. This color specification
     *   should not be considered as the specific UI
     *   intepretation of the tint.
     *   (Primarily included for compatibility with
     *   legacy code)
     *
     *  @param queryTint A color tint specification
     *
     *  @return A color that corresponds to the color tint
     *          specification
     *
     *  @author Ayodeji Oshinnaiye, August 20, 2018
     */
    COLORREF ExpressTintAsColor(const EUiControlTextTint queryTint);
}

