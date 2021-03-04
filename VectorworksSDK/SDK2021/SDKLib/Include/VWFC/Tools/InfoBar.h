//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "../../../Include/Interfaces/VectorWorks/UI/IInfoBar.h"

namespace VWFC
{
	namespace Tools
	{
		// --------------------------------------------------------------------------------------------------------
		class CInfoBar
		{
		public:
						CInfoBar();
			virtual		~CInfoBar();
			
			TXString	GetLabel();
			size_t		GetCurrentProgress();
			double		GetCurrentProgressPercent();
			void		SetLabel(const TXString& strLabel);
			void		SetProgress(Uint16 nProgress=1);

			void		StartProgressIndicator(const TXString& strLabel, Uint16 nMaxProgress=100);
			void		EndProgressIndicator();

			void		Restart(Uint16 nProgress, const TXString& strLabel = "");
			void		IncrementProgressIndicatorWithStep(Uint16 nProgress);
			void		IncrementProgressIndicatorWithPercent(Uint16 nPercent);
		
		private:
			Uint16							fCurrentProgress;
			Uint16							fMaxProgress;
			TXString						fLabel;
			VectorWorks::UI::IInfoBarPtr	fInfoBar;
		};

		// --------------------------------------------------------------------------------------------------------
		class CProgressStepper
		{
		public:
						CProgressStepper(CInfoBar& infoBar, double dPercent, size_t iterations);
						CProgressStepper(CProgressStepper& parent, size_t iterations);
			virtual		~CProgressStepper();

			void		Next();
			void		End();

		protected:
			void		Init(double dPercent, size_t iterations);
			double		UpdateProgress();
			double		LoopNext();

		private:
			CInfoBar&				fInfoBar;
			CProgressStepper*		fpParent;
			double					fPercent;
			double					fStep;
			size_t					fIteratorCount;
			size_t					fIterator;
			size_t					fCurrLoops;
			size_t					fTotalLoops;
		};
	}
}