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
		class VWSymbolObj : public VWObject
		{
		public:
							VWSymbolObj(const TXString& symDefName, const VWPoint2D& location, double dRotDeg=0);
							VWSymbolObj(const VWSymbolDefObj& symDef, const VWPoint2D& location, double dRotDeg=0);
							VWSymbolObj(MCObjectHandle hSymbolDef, const VWPoint2D& location, double dRotDeg=0);
							VWSymbolObj(const VWSymbolDefObj& symDef, const VWTransformMatrix& transform);
							VWSymbolObj(MCObjectHandle hSymbolDef, const VWTransformMatrix& transform);
							VWSymbolObj(MCObjectHandle hSymbol);
							VWSymbolObj(const VWSymbolObj& src);
			virtual			~VWSymbolObj();

			VWSymbolObj&	operator=(const VWSymbolObj& src);

		public:
			MCObjectHandle	GetSymbolDef() const;

			void			SetScaleType(ESymScaleType type);
			ESymScaleType	GetScaleType() const;
			void			SetScaleFactorX(double scale);
			double			GetScaleFactorX() const;
			void			SetScaleFactorY(double scale);
			double			GetScaleFactorY() const;
			void			SetScaleFactorZ(double scale);
			double			GetScaleFactorZ() const;

		// tool
		public:
			// Return true if the specified object handle is a symbol
			static bool		IsSymbolObject(MCObjectHandle hObj);
			static bool		IsSymbolObject(MCObjectHandle hObj, const TXString& name);
		};
	}
}