//
//  CoreUiTintSupport.cpp
//  NNACore A to M
//
//  Created by Ayodeji Oshinnaiye on 8/17/18.
//

#include "StdHeaders.h"
#include "Kernel/CoreUiTintSupport.h"
#include <set>
#include <cmath>

namespace CoreUiTintSupport
{
    /*!
     *  Class that facilitates the conversion of
     *   specific RGB colors into generalized
     *   UI tint specifications
     *
     *  @author Ayodeji Oshinnaiye, August 9, 2018
     */
    class ColorToTintConversionUtility
    {
    public:
        ColorToTintConversionUtility();
       
        /*
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
        EUiControlTextTint ExpressColorAsTint(const COLORREF& queryColor) const;
        
        /*!
         *  Expresses a tint as an approximate RGB
         *   color specification. This color specification
         *   should not be considered as the specific UI
         *   intepretation of the tint.
         *
         *  @param queryTint A color tint specification
         *
         *  @return A color that corresponds to the color tint
         *          specification
         *
         *  @author Ayodeji Oshinnaiye, August 20, 2018
         */
        COLORREF ExpressTintAsColor(const EUiControlTextTint queryTint) const;
        
    protected:
        // Hue/Color angle equivalency sourced from
        // New Mexico Tech Homepage - "Introduction to Color Theory":
        // http://infohost.nmt.edu/tcc/help/pubs/colortheory/web/hsv.html
        enum class HsvStartAngles
        {
            eRedColor               = 0,
            eYellowColor            = 60,
            eGreenColor             = 120,
            eCyanColor              = 180,
            eBlueColor              = 240,
            eMagentaColor           = 300
        };
        
        // Colors with a saturation less than this
        // value will be classified as a gray-tone color.
        const TUnitColorComponent fkGrayToneSaturationThreshold = (TUnitColorComponent)0.10;

		// Colors with a value less than this value will
		// be classified as the color black.
		const TUnitColorComponent fkBlackValueThreshold = (TUnitColorComponent)0.20;
        
        /*!
         *  Retrieves a collection of hue values that correspond to the
		 *   primary HSV colors
         *
         *  @return A collection of hue values that correspond to the primary
		 *          HSV colors
         *
         *  @author Ayodeji Oshinnaiye, August 20, 2018
         */
        const std::set<THueColorComponent> GetPrimaryColorHueAngleSet() const;
		
        /*!
         *  Retrieves a hue value from the internally-defined set
         *   of values that most closely corresponds to the provided
         *   hue value
         *
         *  @param Hue value for which a corresponding value from the
         *         internally-defined set should be found
         *
         *  @return A corresponding hue value
         *
         *  @author Ayodeji Oshinnaiye, December 18, 2018
         */
        HsvStartAngles GetNearestHueValueInSet(const THueColorComponent hueValue) const;
        
		/*!
		 *  Generates a generalized UI tint specifier,
		 *   using a provided hue and saturation magnitude
		 *   from the HSV color model
		 *
		 *  @param hueValue             An HSV color model hue value
		 *  @param saturationMagnitude  An HSV color model saturation magnitude
		 *
		 *  @return A generalized UI tint specification
		 *
		 *  @author Ayodeji Oshinnaiye, December 17, 2018
		 */
		EUiControlTextTint GetNonGrayTintFromHueAndSaturation(const TUnitColorComponent hueValue,
			const TUnitColorComponent saturationMagnitude) const;

		/*!
		*  Adjusts a UI tint specifier (lighten/darken),
		*   using a provided HSV color model value component
		*
		*  @param baseTintValue  Generalized UI tint specifier to be
		*                        adjusted
		*  @param valueMagnitude Magnitude of the HSV value
		*                        component
		*
		*  @return An adjusted generalized UI tint specification
		*
		*  @author Ayodeji Oshinnaiye, December 17, 2018
		*/
		EUiControlTextTint GetAdjustedTintWithValue(const EUiControlTextTint baseTintValue,
			const TUnitColorComponent valueMagnitude) const;
        
        typedef std::map<TUnitColorComponent, EUiControlTextTint> SaturationTintMap;
        const std::map<HsvStartAngles, SaturationTintMap> GetTintSaturationTuningMap() const;

		typedef std::map<TUnitColorComponent, EUiControlTextTint> ValueTintMap;
		const std::map<EUiControlTextTint, ValueTintMap> GetTintValueTuningMap() const;
    };

    //------------------------------------------------------------------------
    ColorToTintConversionUtility::ColorToTintConversionUtility()
    {
    }

    //------------------------------------------------------------------------
    EUiControlTextTint ColorToTintConversionUtility::ExpressColorAsTint(const COLORREF& queryColor) const
    {        
        EUiControlTextTint tintValue = EUiControlTextTint::eGenericGrayTint;
        
        // Convert the RGB color to an HSV color in order to attain a
        // more accurate mapping to a canonical color name.
        const TGSColorV2 gsColor(GetRedValue(queryColor), GetGreenValue(queryColor), GetBlueValue(queryColor));
        THueColorComponent hueValue = kUndefinedHueColorComponent;
        TUnitColorComponent saturationMagnitude = kMinUnitColorComponent;
        TUnitColorComponent valueMagnitude = kMinUnitColorComponent;
        
        gsColor.GetHSV(hueValue, saturationMagnitude, valueMagnitude);
        
        if ((saturationMagnitude >= kMinUnitColorComponent) && (saturationMagnitude <= kMaxUnitColorComponent))
        {
            if (saturationMagnitude < fkGrayToneSaturationThreshold)
            {
				tintValue = GetAdjustedTintWithValue(EUiControlTextTint::eGenericGrayTint, valueMagnitude);
            }
			else if ((hueValue >= kMinHueColorComponent) && (hueValue < kMaxHueColorComponent))
			{
				// Convert the hue to a tint...
				EUiControlTextTint baseTintValue = GetNonGrayTintFromHueAndSaturation(hueValue, saturationMagnitude);
				// ...Adjust the final tint using the magnitude of the value component
				// (required for the generation of dark colors, such as brown).
				tintValue = GetAdjustedTintWithValue(baseTintValue, valueMagnitude);
			}
        }
        
        return tintValue;
    }
    
    //------------------------------------------------------------------------
    COLORREF ColorToTintConversionUtility::ExpressTintAsColor(const EUiControlTextTint queryTint) const
    {
        COLORREF rgbValue = GenerateRGB(0, 0, 0);

        // Tint values, matched with standard color representations that
        // can be associated with a tint. Context-specific tint values are
        // not included (see ExpressTintAsColor declaration).
        static const std::map<EUiControlTextTint, COLORREF> kTintToColorMap =
        {
            { EUiControlTextTint::eGenericRedTint,              GenerateRGB(255, 0, 0)      },
            { EUiControlTextTint::eGenericBlueTint,             GenerateRGB(0, 0, 255)      },
            { EUiControlTextTint::eGenericGreenTint,            GenerateRGB(0, 255, 0)      },
            { EUiControlTextTint::eGenericBlueTint,             GenerateRGB(0, 0, 255)      },
            { EUiControlTextTint::eGenericOrangeTint,           GenerateRGB(255, 160, 0)    },
            { EUiControlTextTint::eGenericYellowTint,           GenerateRGB(255, 255, 0)    },
            { EUiControlTextTint::eGenericBrownTint,            GenerateRGB(96, 48, 0)      },
            { EUiControlTextTint::eGenericPurpleTint,           GenerateRGB(255, 0, 255)    },
            { EUiControlTextTint::eGenericPinkTint,             GenerateRGB(255, 160, 255)  },
            { EUiControlTextTint::eGenericGrayTint,             GenerateRGB(63, 63, 63)     },
			{ EUiControlTextTint::eGenericBlackTint,			GenerateRGB(0, 0, 0)		}
        };
        
        auto tintToColorMapEntry = kTintToColorMap.find(queryTint);
        if (tintToColorMapEntry != kTintToColorMap.end())
        {
            rgbValue = tintToColorMapEntry->second;
        }
        
        return rgbValue;
    }

    //------------------------------------------------------------------------
    const std::set<THueColorComponent>
    ColorToTintConversionUtility::GetPrimaryColorHueAngleSet() const
    {
        static const std::set<THueColorComponent> kPrimaryColorHueAngleSet =
        {
            (THueColorComponent)HsvStartAngles::eRedColor,
            (THueColorComponent)HsvStartAngles::eYellowColor,
            (THueColorComponent)HsvStartAngles::eGreenColor,
            (THueColorComponent)HsvStartAngles::eCyanColor,
            (THueColorComponent)HsvStartAngles::eBlueColor,
            (THueColorComponent)HsvStartAngles::eMagentaColor
        };
        
        return kPrimaryColorHueAngleSet;
    }
    
    //------------------------------------------------------------------------
    ColorToTintConversionUtility::HsvStartAngles
    ColorToTintConversionUtility::GetNearestHueValueInSet
    (
        const THueColorComponent hueValue
    ) const
    {
        HsvStartAngles nearestStartAngle = HsvStartAngles::eRedColor;
        
        const THueColorComponent normalizedHueComponent = std::fmod(hueValue, kMaxHueColorComponent);
        
        // Retrieve the data which contains the correlation of hue values to
        // primary colors / primary color blends.
        auto primaryColorHueAngleSet = GetPrimaryColorHueAngleSet();
        
        // Find the hue in the pre-defined set of hue magnitudes that
        // is the closest match.
        THueColorComponent nearestDifference = kMaxHueColorComponent;
        
        auto primaryColorFromHueIterator = primaryColorHueAngleSet.rbegin();
        while (primaryColorFromHueIterator != primaryColorHueAngleSet.rend())
        {
            THueColorComponent currentDifference = std::abs(*primaryColorFromHueIterator - normalizedHueComponent);
            if (currentDifference < nearestDifference)
            {
                nearestDifference = currentDifference;
                nearestStartAngle = (HsvStartAngles)(long)*primaryColorFromHueIterator;
            }
            
            primaryColorFromHueIterator++;
        }
        
        return nearestStartAngle;
    }

	//------------------------------------------------------------------------
	EUiControlTextTint ColorToTintConversionUtility::GetNonGrayTintFromHueAndSaturation
	(
		const TUnitColorComponent hueValue,
		const TUnitColorComponent saturationMagnitude
	) const
	{
		EUiControlTextTint tintValue = EUiControlTextTint::eGenericGrayTint;

		if ((saturationMagnitude >= kMinUnitColorComponent) && (saturationMagnitude <= kMaxUnitColorComponent) &&
			(hueValue >= kMinHueColorComponent) && (hueValue < kMaxHueColorComponent))
		{
            // Convert the hue to an approximate primary color / blend of primary colors.
            HsvStartAngles hsvStartAngle = GetNearestHueValueInSet(hueValue);

            auto tintTuningSaturationMap = GetTintSaturationTuningMap();

            // Find the saturation-to-tint mapping for the determined color.
            auto saturationTintTuningMapEntry = tintTuningSaturationMap.find(hsvStartAngle);
            if (saturationTintTuningMapEntry != tintTuningSaturationMap.end())
            {
                // Retrieve a tint specifier using the saturation-to-tint
                // mapping.
                auto saturationTintMapIterator = saturationTintTuningMapEntry->second.rbegin();
                while ((saturationTintMapIterator != saturationTintTuningMapEntry->second.rend()) &&
                    (saturationTintMapIterator->first > saturationMagnitude))
                {
                    saturationTintMapIterator++;
                }

                if (saturationTintMapIterator != saturationTintTuningMapEntry->second.rend())
                {
                    tintValue = saturationTintMapIterator->second;
                }
            }
		}

		return tintValue;
	}

	//------------------------------------------------------------------------
	EUiControlTextTint ColorToTintConversionUtility::GetAdjustedTintWithValue
	(
		const EUiControlTextTint baseTintValue,
		const TUnitColorComponent valueMagnitude
	) const
	{
		EUiControlTextTint tintValue = baseTintValue;

	if ((valueMagnitude >= kMinUnitColorComponent) && (valueMagnitude <= kMaxUnitColorComponent))
		{
			auto tintValueTuningMap = GetTintValueTuningMap();

			// Find the value component tint adjustment mapping for the
			// specified tint.
			auto valueTintTuningMapEntry = tintValueTuningMap.find(baseTintValue);
			if (valueTintTuningMapEntry != tintValueTuningMap.end())
			{
				// Retrieve a tint specifier using the value-to-tint mapping
				// adjustment for the provided tint.
				auto valueTintMapIterator = valueTintTuningMapEntry->second.begin();
				while ((valueTintMapIterator != valueTintTuningMapEntry->second.end()) &&
					(valueTintMapIterator->first < valueMagnitude))
				{
					valueTintMapIterator++;
				}

				if (valueTintMapIterator != valueTintTuningMapEntry->second.end())
				{
					tintValue = valueTintMapIterator->second;
				}
			}
		}

		return tintValue;
	}

    //------------------------------------------------------------------------
    const std::map<ColorToTintConversionUtility::HsvStartAngles, ColorToTintConversionUtility::SaturationTintMap>
    ColorToTintConversionUtility::GetTintSaturationTuningMap() const
    {
        static const SaturationTintMap RedToneSaturationMap =
        {
            { fkGrayToneSaturationThreshold,        EUiControlTextTint::eGenericPinkTint    },
            { (TUnitColorComponent)0.50,            EUiControlTextTint::eGenericRedTint     }
        };
        
        static const SaturationTintMap YellowToneSaturationMap =
        {
            {fkGrayToneSaturationThreshold,         EUiControlTextTint::eGenericYellowTint  }
        };
        
        static const SaturationTintMap GreenToneSaturationMap =
        {
            {fkGrayToneSaturationThreshold,         EUiControlTextTint::eGenericGreenTint	}
        };
        
        static const SaturationTintMap CyanToneSaturationMap =
        {
            {fkGrayToneSaturationThreshold,         EUiControlTextTint::eGenericBlueTint	}
        };
        
        static const SaturationTintMap BlueToneSaturationMap =
        {
            {fkGrayToneSaturationThreshold,         EUiControlTextTint::eGenericBlueTint	}
        };
        
        static const SaturationTintMap MagentaToneSaturationMap =
        {
            {fkGrayToneSaturationThreshold,         EUiControlTextTint::eGenericPurpleTint  }
        };
        
        
        static const std::map<HsvStartAngles, SaturationTintMap> kTintSaturationTuningMap =
        {
            { HsvStartAngles::eRedColor,                RedToneSaturationMap        },
            { HsvStartAngles::eYellowColor,             YellowToneSaturationMap     },
            { HsvStartAngles::eGreenColor,              GreenToneSaturationMap      },
            { HsvStartAngles::eCyanColor,               CyanToneSaturationMap       },
            { HsvStartAngles::eBlueColor,               BlueToneSaturationMap       },
            { HsvStartAngles::eMagentaColor,            MagentaToneSaturationMap    }
        };
        
        return kTintSaturationTuningMap;
    }

	//------------------------------------------------------------------------
	const std::map<EUiControlTextTint, ColorToTintConversionUtility::ValueTintMap>
	ColorToTintConversionUtility::GetTintValueTuningMap() const
	{
		static const ValueTintMap RedTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint		},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericRedTint			}
		};

		static const ValueTintMap GreenTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint		},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericGreenTint		}
		};

		static const ValueTintMap BlueTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint		},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericBlueTint		}
		};

		static const ValueTintMap OrangeTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint		},
			{ (TUnitColorComponent)0.50,			EUiControlTextTint::eGenericBrownTint		},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericOrangeTint		}
		};

		static const ValueTintMap YellowTintMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint	},
			{ (TUnitColorComponent)0.50,			EUiControlTextTint::eGenericBrownTint	},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericYellowTint	}
		};

		static const ValueTintMap PurpleTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint	},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericPurpleTint	}
		};

		static const ValueTintMap PinkTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint },
		};

		static const ValueTintMap GrayTintValueMap =
		{
			{ fkBlackValueThreshold,				EUiControlTextTint::eGenericBlackTint	},
			{ (TUnitColorComponent)0.5,				EUiControlTextTint::eGenericGrayTint	},
			{ (TUnitColorComponent)1.0,				EUiControlTextTint::eGenericWhiteTint	}
		};


		static const std::map<EUiControlTextTint, ValueTintMap> kTintValueTuningMap =
		{
			{ EUiControlTextTint::eGenericRedTint,		RedTintValueMap			},
			{ EUiControlTextTint::eGenericGreenTint,	GreenTintValueMap		},
			{ EUiControlTextTint::eGenericBlueTint,		BlueTintValueMap		},
			{ EUiControlTextTint::eGenericOrangeTint,	OrangeTintValueMap		},
			{ EUiControlTextTint::eGenericYellowTint,	YellowTintMap			},
			{ EUiControlTextTint::eGenericBrownTint,	OrangeTintValueMap		},
			{ EUiControlTextTint::eGenericPurpleTint,	PurpleTintValueMap		},
			{ EUiControlTextTint::eGenericPinkTint,		PinkTintValueMap		},
			{ EUiControlTextTint::eGenericGrayTint,		GrayTintValueMap		},
			{ EUiControlTextTint::eGenericBlackTint,	GrayTintValueMap		},
			{ EUiControlTextTint::eGenericWhiteTint,	GrayTintValueMap		}
		};

		return kTintValueTuningMap;
	}

    //------------------------------------------------------------------------
    EUiControlTextTint ExpressColorAsTint(const COLORREF& queryColor)
    {
        EUiControlTextTint tintValue = EUiControlTextTint::eGenericGrayTint;
        
        ColorToTintConversionUtility colorToTintConversionUtility;
        tintValue = colorToTintConversionUtility.ExpressColorAsTint(queryColor);
        
        return tintValue;
    }

    //------------------------------------------------------------------------
    EUiControlTextTint ExpressColorAsTint(const GSColor& queryColor)
    {
        return ExpressColorAsTint(GenerateRGB(queryColor.red, queryColor.green, queryColor.blue));
    }
    
    //------------------------------------------------------------------------
    COLORREF ExpressTintAsColor(const EUiControlTextTint queryTint)
    {
        COLORREF rgbValue = GenerateRGB(0, 0, 0);
        
        ColorToTintConversionUtility colorToTintConversionUtility;
        rgbValue = colorToTintConversionUtility.ExpressTintAsColor(queryTint);
        
        return rgbValue;
    }
}
