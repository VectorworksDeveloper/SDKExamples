//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_STRING_CONVERTOR__H
#define VECTORWORKS_STRING_CONVERTOR__H

#pragma once

namespace VWFC
{
	namespace Tools
	{
		class VWStringConv
		{
		public:
							VWStringConv(const TXString& str);
							VWStringConv(double value);
							VWStringConv(Sint32 value);
			virtual			~VWStringConv();

		public:
			double			GetScale() const;
			TXString		GetScaleString(double dEpsilon = kNearlyEqualEpsilonForDoubles) const;

			double			GetDimCoord() const;
			// uses SDK call for converting to dim string
			TXString		GetDimCoordString() const;
			// uses general SDK call for covnerting to dim string
			TXString		GetDimGeneralCoordString() const;

			double			GetAngleDeg() const;
			TXString		GetAngleDegString() const;

			double			GetArea() const;
			//debug
			// additional parameter: if the number is to be preserved or is to be converted in document units
			TXString		GetAreaString(bool bPreserveNumber = false) const;

			double			GetVolume() const;
			TXString		GetVolumeString() const;

			// converts the value to match the current document's number formatting
			double			GetVWDocumentDouble(TNumStyleClass style) const;
			TXString		GetVWDocumentDoubleString(TNumStyleClass style, Uint8 accuracy, Uint8 format) const;

			// line thickness conversion
			Sint32			GetMils(VectorWorks::EThicknessUnitsType unitsType = VectorWorks::eThicknessUnitsType_Default) const;
			TXString		GetMilsString(VectorWorks::EThicknessUnitsType unitsType = VectorWorks::eThicknessUnitsType_Default) const;

		public:
			static TXString	GetDimCoordUnitString();
			static TXString	GetAreaUnitString();
			static TXString	GetVolumeUnitString();

			static double	ConvertDimCoord_ToDocumentUnits(double value);
			static double	ConvertDimCoord_FromDocumentUnits(double value);
			static double	ConvertArea_ToDocumentUnits(double value);
			static double	ConvertArea_FromDocumentUnits(double value);
			static double	ConvertVolume_ToDocumentUnits(double value);
			static double	ConvertVolume_FromDocumentUnits(double value);

			// to string containing a double number with the correct precission
			static void		ConvertDimCoord_DoubleToString(double value, TXString& outValue, bool incUnitMark = true);
			static void		ConvertArea_DoubleToString(double value, TXString& outValue, bool incUnitMark = true);
			static void		ConvertVolume_DoubleToString(double value, TXString& outValue, bool incUnitMark = true);

			// Worksheet related functions
			static TXString	WorksheetParamDelimiter();

		protected:
			bool				fbIsString;
			TXString			fTheString;
			double				fdValue;
		};
	}
}

#endif // VECTORWORKS_STRING_CONVERTOR__H
