//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


using namespace VectorWorks::UI;
using namespace VWFC::Tools;

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CProgressDlg::CProgressDlg()
{
	fInfinite		= false;
	fDelayedOpen	= false;
	fLayoutType     = EProgressLayoutType::Standard;

	fTopTextInitialized		= false;
	fTopTextUpdated			= false;
	fBottomTextInitialized	= false;
	fBottomTextUpdated		= false;
	fMeterInitialized		= false;
	fMeterUpdated			= false;

	fProgressStarted					= false;
	fProgressBeginContextPercentage		= 0;
	fProgressBeginContextLoopCount		= 0;
	fProgressCurrentLoopCount			= 0;
	fProgressCurrentPosition			= 0;
}

CProgressDlg::CProgressDlg(EProgressLayoutType type)
{
    fInfinite		= false;
    fDelayedOpen	= false;
    fLayoutType     = type;
    
    fProgressStarted					= false;
    fProgressBeginContextPercentage		= 0;
    fProgressBeginContextLoopCount		= 0;
    fProgressCurrentLoopCount			= 0;
    fProgressCurrentPosition			= 0;
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::Open(const TXString& title, bool canCancel)
{
	fTitle		= title;
	fCanCancel	= canCancel;

	if ( fProgressDlg )
	{
		fProgressDlg->Close();
		fProgressDlg.Release();
	}

	fDelayedOpen	= false;
	fProgressDlg.Query( VectorWorks::UI::IID_ProgressDialog );
	if ( fProgressDlg )
	{
        fProgressDlg->SetLayoutType((int)fLayoutType);
		fProgressDlg->Open( title );
		fProgressDlg->AllowUserCancel( canCancel );
		fProgressDlg->ResetMeter( 100 );	// we work in percentages with the progress
	}
}

void CProgressDlg::OpenDelayed(const TXString& title, bool canCancel, Uint32 delayMiliSec)
{
	fTitle		= title;
	fCanCancel	= canCancel;

	fDelayedOpen		= true;
	fDelayOpenTimeDiff	= delayMiliSec;
	fDelayOpenLastTime	= 0;
}

void CProgressDlg::OpenInfinite(const TXString& title, bool canCancel)
{
	fTitle		= title;
	fCanCancel	= canCancel;
	fInfinite	= true;

	if ( fProgressDlg )
	{
		fProgressDlg->Close();
		fProgressDlg.Release();
	}

	fDelayedOpen	= false;
	fProgressDlg.Query( VectorWorks::UI::IID_ProgressDialog );
	if ( fProgressDlg )
	{
        fProgressDlg->SetLayoutType((int)fLayoutType);
		fProgressDlg->Open( title );
		fProgressDlg->AllowUserCancel( canCancel );
		fProgressDlg->ResetMeter( Uint16(-1) );
	}
}

void CProgressDlg::OpenInfiniteDelayed(const TXString& title, bool canCancel, Uint32 delayMiliSec)
{
	fTitle		= title;
	fCanCancel	= canCancel;
	fInfinite	= true;

	fDelayedOpen		= true;
	fDelayOpenTimeDiff	= delayMiliSec;
	fDelayOpenLastTime	= 0;
}

void CProgressDlg::Close()
{
	if ( fProgressDlg )
	{
		fProgressDlg->Close();
		fProgressDlg.Release();
	}
}

void CProgressDlg::SetTopText(const TXString& message)
{
	fTopText	= message;

	if ( fProgressDlg )
	{
		if ( ! fTopTextInitialized )
		{
			fTopTextInitialized = true;
			fProgressDlg->SetTopText( fTopText );
		}
		else
			fTopTextUpdated = true;
	}
}

void CProgressDlg::SetBottomText(const TXString& message)
{
	fBottomText	= message;

	if ( fProgressDlg )
	{
		if ( ! fBottomTextInitialized )
		{
			fBottomTextInitialized = true;
			fProgressDlg->SetBottomText( fBottomText );
		}
		else
			fBottomTextUpdated	= true;
	}
}

void CProgressDlg::SetMeterText(const TXString& message)
{
	fMeterText	= message;

	if ( fProgressDlg )
	{
		if ( !fMeterInitialized )
		{
			fMeterInitialized = true;
			fProgressDlg->SetMeterText( fMeterText );
		}
		else
			fMeterUpdated = true;
	}
}

bool CProgressDlg::HasCancel()
{
	bool	result	= false;
	if ( fProgressDlg )
	{
		fProgressDlg->HasUserCanceled( result );
	}

	return result;
}

void CProgressDlg::Start(double percent, Sint32 loopCount)
{
	if ( fProgressStarted )
	{
		this->End();
	}

	if ( percent >= 0 )
	{
		fProgressBeginContextPercentage	= percent;
	}

	if ( loopCount > 0 )
	{
		fProgressBeginContextLoopCount	= loopCount;
	}

	fProgressCurrentLoopCount		= 0;
	fProgressCurrentPosition		= 0;
	fProgressStarted				= true;

	this->CheckDelayedOpen();
}

void CProgressDlg::End()
{
	double	percDone	= (double(fProgressCurrentLoopCount) / double(fProgressBeginContextLoopCount)) * fProgressBeginContextPercentage;
	Uint16	newPosition	= Uint16(percDone);
	if ( newPosition > fProgressCurrentPosition )
	{
		this->CheckDelayedOpen();
		if ( fProgressDlg )
		{
			if ( ! fInfinite )
			{
				fProgressDlg->IncrementMeter( newPosition - fProgressCurrentPosition );
			}

			fProgressDlg->DoYield();
		}
	}

	fProgressBeginContextPercentage	= 0;
	fProgressBeginContextLoopCount	= 0;
	fProgressCurrentLoopCount		= 0;
	fProgressCurrentPosition		= 0;
	fProgressStarted				= false;
}

void CProgressDlg::DoYield(Sint32 count)
{
	this->CheckDelayedOpen();

	fProgressCurrentLoopCount	+= count;

	if ( fProgressDlg )
	{
		Uint32	kTimeDiffForYeld	= 1000; // 1 sec
		if ( fInfinite )
			kTimeDiffForYeld	= 500; // 1/2 sec

		static Uint32	timeLast = 0;
		Uint32			timeCurrent	= 0;
#ifdef _WINDOWS
		timeCurrent		= (Uint32) ::GetTickCount();
#else
		timeCurrent		= gSDK->TickCount() * 17;	// Mac returns 1 /60th of a second
#endif

		if ( timeLast == 0 )
			timeLast	= timeCurrent;

		if ( timeCurrent > timeLast + kTimeDiffForYeld )
		{
			timeLast	= timeCurrent;

			if ( fTopTextUpdated )
			{
				fProgressDlg->SetTopText( fTopText );
				fTopTextUpdated = false;
			}

			if ( fBottomTextUpdated	)
			{
				fProgressDlg->SetBottomText( fBottomText );
				fBottomTextUpdated = false;
			}

			if ( fMeterUpdated )
			{
				fProgressDlg->SetMeterText( fMeterText );
				fMeterUpdated = false;
			}

			if ( fProgressCurrentLoopCount <= fProgressBeginContextLoopCount )
			{
				double	percDone	= (double(fProgressCurrentLoopCount) / double(fProgressBeginContextLoopCount)) * fProgressBeginContextPercentage;
				Uint16	newPosition	= Uint16(percDone);

				if ( newPosition > fProgressCurrentPosition )
				{
					if ( fProgressDlg && ! fInfinite )
					{
						fProgressDlg->IncrementMeter( newPosition - fProgressCurrentPosition );
					}

					fProgressCurrentPosition	= newPosition;
				}
			}

			fProgressDlg->DoYield();
		}
	}
}

void CProgressDlg::CallBaseYield()
{
    if ( fProgressDlg )
    {
        fProgressDlg->DoYield();
    }
}

void CProgressDlg::CheckDelayedOpen()
{
	if ( fDelayedOpen )
	{
		Uint32			timeCurrent	= 0;
#ifdef _WINDOWS
		timeCurrent		= (Uint32) ::GetTickCount();
#else
		timeCurrent		= gSDK->TickCount() * 17;	// Mac returns 1 /60th of a second
#endif
	
		if ( fDelayOpenLastTime == 0 )
			fDelayOpenLastTime	= timeCurrent;
	
		//if ( fProgressCurrentPosition <= 50 )
		{
			if ( timeCurrent > fDelayOpenLastTime + fDelayOpenTimeDiff )
			{
				if ( fProgressDlg == NULL )
				{
					fProgressDlg.Query( VectorWorks::UI::IID_ProgressDialog );
					if ( fProgressDlg )
					{
						fProgressDlg->Open( fTitle );
						fProgressDlg->AllowUserCancel( fCanCancel );
						if ( ! fInfinite )
						{
							fProgressDlg->ResetMeter( 100 );	// we work in percentages with the progress
							fProgressDlg->IncrementMeter( fProgressCurrentPosition );
						}
						else
						{
							fProgressDlg->ResetMeter( Uint16(-1) );
						}
						fProgressDlg->DoYield();

						if ( ! fTopText.IsEmpty() )		fProgressDlg->SetTopText( fTopText );
						if ( ! fBottomText.IsEmpty() )	fProgressDlg->SetBottomText( fBottomText );
						if ( ! fMeterText.IsEmpty() )	fProgressDlg->SetMeterText( fMeterText );
					}
				}

				fDelayedOpen		= false;
				fDelayOpenLastTime	= timeCurrent;
			}
		}
	}
}
