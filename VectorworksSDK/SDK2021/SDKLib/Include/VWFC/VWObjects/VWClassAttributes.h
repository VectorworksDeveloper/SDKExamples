//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Tools;
	namespace VWObjects
	{
		class VWClass;

		class VWClassAttr
		{
			friend class VWClass;
		protected:
								VWClassAttr(InternalIndex classIndex);
		public:
			virtual				~VWClassAttr();

		public:
			CRGBColor			GetPenForeColor() const;
			CRGBColor			GetPenBackColor() const;
			void				SetPenForeColor(const CRGBColor& color);
			void				SetPenBackColor(const CRGBColor& color);

			CRGBColor			GetFillForeColor() const;
			CRGBColor			GetFillBackColor() const;
			void				SetFillForeColor(const CRGBColor& color);
			void				SetFillBackColor(const CRGBColor& color);

			short				GetLineWeightInMils() const;
			void				SetLineWeightInMils(short mils);

			MarkerType			GetMarker(short& size, short& angle) const;
			void				SetMarker(MarkerType marker,short size, short angle);

			VWPattern			GetPenPattern() const;
			void				SetPenPattern(const InternalIndex& dashIndex); // Legacy - Was used for dash indices; now taking InternalIndex but would be better to use newer method.
			void				SetPenPattern(const VWPattern& pattern);
			VWPattern			GetFillPattern() const;
			void				SetFillPattern(const VWPattern& pattern);

			void				SetUseGeneralTexture(bool useTexture);
			
			void				SetGeneralTexture(InternalIndex texture);
			InternalIndex		GetGeneralTexture() const;

		protected:
			InternalIndex		fClassIndex;
		};
	}
}