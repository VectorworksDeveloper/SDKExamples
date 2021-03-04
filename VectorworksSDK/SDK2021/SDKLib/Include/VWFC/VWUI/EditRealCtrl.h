//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWEditRealCtrl : public VWControl
		{
		public:
			// 1 - Real, regular old real type;
			// 2 - Angle, SDK input and output is always in degrees but display and user input is based on documents Unit settings;
			// 3 - Dimension, usually an offset this is a distance that is not tied to the origin;
			// 4 - CoordinateX, this is an exact x location on the drawing;
			// 5 - CoordinateY, this is an exact y location on the drawing. There are separate x and y controls to account for changes the user may make to the origin.  Z coordinates should use the offset mode.
			enum EEditControlType
			{
				kEditControlReal		= kEditReal,
				kEditControlAngle		= kEditAngle,
				kEditControlDimension	= kEditDimension,
				kEditControlCoordinateX	= kEditCoordinateX,
				kEditControlCoordinateY	= kEditCoordinateY
			};

		public:
							VWEditRealCtrl(TControlID id);
			virtual			~VWEditRealCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, double dDefaultValue, short widthInStdChar, EEditControlType type);

		// attributes
		public:
			double			GetEditReal(EEditControlType type) const;
			bool			GetEditReal(EEditControlType type, double& outValue) const;
			void			SetEditReal(double value, EEditControlType type);
			void			SelectContent();

		};
	}
}