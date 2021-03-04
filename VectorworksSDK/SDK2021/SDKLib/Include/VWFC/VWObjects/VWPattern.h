//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		class VWPattern
		{
			friend class VWClassAttributes;
			friend class VWObjectAttr;
		public:
								VWPattern(bool isFillPattern);
								VWPattern(InternalIndex index, bool isFillPattern);
								
			virtual				~VWPattern();

			operator InternalIndex() const;
			

		public:
			Boolean				IsNonePattern() const;
			void				SetNonePattern();
			Boolean				IsSolidPattern() const;
			void				SetSolidPattern();
			Boolean				IsHatchPattern() const;
			Boolean				IsGradientPattern() const;
			Boolean				IsImagePattern() const;
			Boolean				IsTilePattern() const;
			Boolean				IsLineTypePattern() const;

		protected:
			bool				fbIsFillPattern;
			InternalIndex		fFillPatternIndex;
			InternalIndex		fPenPatternIndex;
		};
	}
}