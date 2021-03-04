//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------
		enum EDocumentShadowOffsetUnit
		{
			eDocumentShadowOffsetUnit_Page,
			eDocumentShadowOffsetUnit_Documentument,
			eDocumentShadowOffsetUnit_FactorOfHeight,
		};
		
		// ------------------------------------------------------------------------
		enum EDocumentShadowFill
		{
			eDocumentShadowFill_Solid,
			eDocumentShadowFill_Hatch,
			eDocumentShadowFill_Image,
			eDocumentShadowFill_Gradient,
			eDocumentShadowFill_Tile,
			eDocumentShadowFill_ByClass,
		};

		struct SShadowFillInfo
		{
			ColorRef	fSolidColorRef;
			TXString	fShadowFillName;

						SShadowFillInfo()
						{
							fSolidColorRef	= 0;
						};
		};
		
		// ---------------------------------------------------------------------------------------------------
		// {10926AAB-9675-4076-B035-FA1EDB39AE38}
		static const VWIID IID_DocumentShadowSupport = { 0x10926aab, 0x9675, 0x4076, { 0xb0, 0x35, 0xfa, 0x1e, 0xdb, 0x39, 0xae, 0x38 } };
		
		class DYNAMIC_ATTRIBUTE IDocumentShadowSupport : public IVWUnknown
		{
		public:			
			virtual VCOMError	VCOM_CALLTYPE GetShadowOffset(double& shadowOffset) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowOffset(const double& shadowOffset) = 0;
			
			virtual VCOMError	VCOM_CALLTYPE GetShadowOffsetUnit(EDocumentShadowOffsetUnit& shadowOffsetUnit) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowOffsetUnit(const EDocumentShadowOffsetUnit& shadowOffsetUnit) = 0;
			
			virtual VCOMError	VCOM_CALLTYPE GetShadowAngle(double& shadowAnglet) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowAngle(const double& shadowAngle) = 0;
			
			virtual VCOMError	VCOM_CALLTYPE GetShadowOpacity(Sint32& shadowOpacity) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowOpacity(const Sint32& shadowOpacity) = 0;
			
			virtual VCOMError	VCOM_CALLTYPE GetShadowOpacityByClass(bool& shadowOpacityByClass) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowOpacityByClass(const bool& shadowOpacityByClass) = 0;
			
			virtual VCOMError	VCOM_CALLTYPE GetShadowFillStyle(EDocumentShadowFill& shadowFillStyle, SShadowFillInfo& shadowFillInfo) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowFillStyle(const EDocumentShadowFill& shadowFillStyle, const SShadowFillInfo& shadowFillInfo) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetShadowSolidColorRef(ColorRef& shadowSolidColorRef) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowSolidColorRef(const ColorRef& shadowSolidColorRef) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetShadowFillStyleName(const EDocumentShadowFill& shadowFillStyle, TXString& shadowFillName) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetShadowFillStyleName(const EDocumentShadowFill& shadowFillStyle, const TXString& shadowFillName) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetIsShadowUnderCanopy(bool& isShadowUnderCanopy) const = 0;
			virtual VCOMError	VCOM_CALLTYPE SetIsShadowUnderCanopy(const bool& isShadowUnderCanopy) = 0;

			virtual VCOMError	VCOM_CALLTYPE ApplyShadowSettings() = 0;
			virtual VCOMError	VCOM_CALLTYPE LoadDefaults() = 0;


			virtual MCObjectHandle	VCOM_CALLTYPE CreateShadowPoly(MCObjectHandle poly, MCObjectHandle parentLayer, const double& objectHeight, const InternalIndex& objectClass, const TransformMatrix& matrix) = 0;
		};
		
		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDocumentShadowSupport> IDocumentShadowSupportPtr;
	}
}