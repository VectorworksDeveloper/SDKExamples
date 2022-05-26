//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Math;
	using namespace Tools;
	namespace VWObjects
	{
		enum EVWLightKind
		{
			eWLightKind_Directional	= kDirectionalLight,
			eWLightKind_Point		= kPointLight,
			eWLightKind_Spot		= kSpotLight,
		};

		enum EVWLightDistanceFalloff
		{
			eVWLightDistanceFalloff_None			= kLightNoFalloff,
			eVWLightDistanceFalloff_Inverse			= kLightInverseDistance,
			eVWLightDistanceFalloff_InverseSquared	= kLightInverseDistanceSquared,
		};
		
		enum EVWLightAngularFalloff
		{
			eVWLightAngularFalloff_None			= kLightNoFalloff,
			eVWLightAngularFalloff_Linear		= kLightLinear,
			eVWLightAngularFalloff_Exponential	= kLightExponential,
			eVWLightAngularFalloff_Cosine		= kLightCosine,
		};

		enum EVWLightBrightnessUnit
		{
			eVWLightBrightnessUnit_Lumens		= 0,
			eVWLightBrightnessUnit_Candelas		= 1,
			eVWLightBrightnessUnit_Lux			= 2,
			eVWLightBrightnessUnit_Footcandels	= 3,
		};

		enum EVWLightCausticPhotons
		{
			eVWLightCausticNone		= kLightCausticNone,
			eVWLightCausticLow		= kLightCausticLow,
			eVWLightCausticMedium	= kLightCausticMedium,		
			eVWLightCausticHigh		= kLightCausticHigh,
			eVWLightCausticVeryHigh = kLightCausticVeryHigh,
		};

		// -------------------------------------------------------------------------------------------
		class VWLightObj : public VWObject
		{
		public:
							VWLightObj(const VWPoint3D& position, EVWLightKind kind, bool isOn, double brightness, const CRGBColor& color, bool castShadows);
							VWLightObj(MCObjectHandle hLight);
							VWLightObj(const VWLightObj& src);
			virtual			~VWLightObj();

			VWLightObj&	operator=(const VWLightObj& src);

		public:
			bool					GetIsOn() const;
			void					SetIsOn(bool value);

			double					GetBrightness() const;
			void					SetBrightness(double value);

			CRGBColor				GetColor() const;
			void					SetColor(const CRGBColor& color);

			bool					GetCastShadows() const;
			void					SetCastShadows(bool value);

			VWPoint3D				GetPosition() const;
			void					SetPosition(const VWPoint3D& pos);

			EVWLightKind			GetKind() const;
			void					SetKind(EVWLightKind value);

			VWPoint3D				GetDirectionVector() const;
			void					SetDirectionVector(const VWPoint3D& dir);

			// see ovLightDirectionVertAngle
			double					GetDirectionAngleVertical() const;
			void					SetDirectionAngleVertical(double value);

			// see ovLightDirectionHorizAngle
			double					GetDirectionAngleHorizontal() const;
			void					SetDirectionAngleHorizontal(double value);

			EVWLightDistanceFalloff	GetDistanceFalloff() const;
			void					SetDistanceFalloff(EVWLightDistanceFalloff value);
			EVWLightAngularFalloff	GetAngularFalloff() const;
			void					SetAngularFalloff(EVWLightAngularFalloff value);

			// see ovLightSpread
			double					GetSpread() const;
			void					SetSpread(double degValue);

			// see ovLightBeam
			double					GetBeam() const;
			void					SetBeam(double degValue);

			// see ovLightLitFog
			bool					GetLitFog() const;
			void					SetLitFog(bool value);

			// see ovLightSoftShadows
			bool					GetSoftShadows() const;
			void					SetSoftShadows(bool value);

			// see ovLightUseEmitter
			bool					GetUseEmitter() const;
			void					SetUseEmitter( bool value );

			// see ovLightEmitterBrightness
			double					GetEmitterBrightness() const;
			void					SetEmitterBrightness( double value );

			// see ovLightBrightnessUnit
			EVWLightBrightnessUnit	GetBrightnessUnit() const;
			void					SetBrightnessUnit( EVWLightBrightnessUnit value );

			// see ovLightUseTemperature
			bool					GetUseTemperature() const;
			void					SetUseTemperature( bool value );

			// see ovLightTemperature
			double					GetTemperature() const;
			void					SetTemperature( double value );

			// see ovLightCausticOnly
			bool					GetCausticOnly() const;
			void					SetCausticOnly( bool value );

			// see ovLightCausticPhotons
			EVWLightCausticPhotons	GetCausticPhotons() const;
			void					SetCausticPhotons( EVWLightCausticPhotons value );

		// tool
		public:
			// Return true if the specified object handle is 2D line
			static bool		IsLightObject(MCObjectHandle hObj);
		};
	}
}