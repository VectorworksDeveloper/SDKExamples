//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// --------------------------------------------------------------------------------------------------------
		enum class EProgressLayoutType
		{
			  Standard // three-line
			, Narrow
		};

		// --------------------------------------------------------------------------------------------------------
		// This class provides easier access to the progress dialog VectorWorks::UI::IProgressDialogPtr
		//
		// The class is designed so Start and End define one loop of work and
		//	DoYield must be called on each interation (internal times will make sure it doesn't spend too much time)
		// The VectorScript call [http://developer.vectorworks.net/index.php/VS:ProgressDlgOpen] uses this class.
		//
		// Note: The infinite progress dialog doesn't require Start and End, just DoYield to let the messages go through for the animation
		//
		// Example:
		//		CProgressDlg	progressDlg;
		//		progressDlg.Open( "title" );
		//
		//		progressDlg.Start( 40, 100 );	// 40% of the work will be done in 100 loops
		//		for(size_t i=0; i<100; ++i)
		//		{
		//			...
		//			progressDlg.DoYield();
		//		}
		//		progressDlg.End();
		//
		//		progressDlg.Start( 60, 12 );	// 60% of the work will be done in 12 loops
		//		for(size_t i=0; i<12; ++i)
		//		{
		//			...
		//			progressDlg.DoYield();
		//		}
		//		progressDlg.End();
		//
		//		progressDlg.Close();
		//
		class CProgressDlg
		{
		public:
						CProgressDlg();
                        CProgressDlg(EProgressLayoutType type);
			virtual		~CProgressDlg();

			void		Open(const TXString& title, bool canCancel);
			void		OpenDelayed(const TXString& title, bool canCancel, Uint32 delayMiliSec = 3000 /*3 sec*/);

			void		OpenInfinite(const TXString& title, bool canCancel);
			void		OpenInfiniteDelayed(const TXString& title, bool canCancel, Uint32 delayMiliSec = 3000 /*3 sec*/);

			void		Close();

			void		SetTopText(const TXString& message);
			void		SetBottomText(const TXString& message);
			void		SetMeterText(const TXString& message);

			bool		HasCancel();

			void		Start(double percent, Sint32 loopCount);
			void		End();

			void		DoYield(Sint32 count = 1);
            
            void        CallBaseYield();

		protected:
			void		CheckDelayedOpen();

		private:
			VectorWorks::UI::IProgressDialogPtr		fProgressDlg;
			bool					fInfinite;
            EProgressLayoutType		fLayoutType;
			bool					fProgressStarted;
			double					fProgressBeginContextPercentage;
			Sint32					fProgressBeginContextLoopCount;
			Sint32					fProgressCurrentLoopCount;
			Uint16					fProgressCurrentPosition;

			bool		fDelayedOpen;
			Uint32		fDelayOpenTimeDiff;
			Uint32		fDelayOpenLastTime;
			TXString	fTitle;
			bool		fCanCancel;

			bool		fTopTextInitialized;
			bool		fTopTextUpdated;
			TXString	fTopText;
			bool		fBottomTextInitialized;
			bool		fBottomTextUpdated;
			TXString	fBottomText;
			bool		fMeterInitialized;
			bool		fMeterUpdated;
			TXString	fMeterText;
		};
	}
}