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
CInfoBar::CInfoBar()
	: fInfoBar ( VectorWorks::UI::IID_InfoBar )
{
	fCurrentProgress	= 0;
	fMaxProgress		= 0;
	fLabel				= "";
	
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CInfoBar::~CInfoBar()
{
	fInfoBar->EndProgressIndicator();
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
TXString CInfoBar::GetLabel()
{
	return this->fLabel;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
size_t CInfoBar::GetCurrentProgress()
{
	return fCurrentProgress;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CInfoBar::SetLabel( const TXString& strLabel )
{
	fLabel	= strLabel;
	fInfoBar->SetProgressIndicator( fCurrentProgress, fLabel );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CInfoBar::SetProgress( Uint16 nProgress )
{
	fCurrentProgress	= nProgress;
	fInfoBar->SetProgressIndicator( fCurrentProgress, fLabel );
	//Sleep( 1000 );
}

// --------------------------------------------------------------------------------------------------------
// Start progress bar and set his label and max progress.
// --------------------------------------------------------------------------------------------------------
void CInfoBar::StartProgressIndicator( const TXString& strLabel, Uint16 nMaxProgress )
{
	fMaxProgress			= nMaxProgress;
	fLabel					= strLabel;
	fInfoBar->StartProgressIndicator( fLabel, fMaxProgress );
}

// --------------------------------------------------------------------------------------------------------
// Fill current progress to max and end progress indicator.
// --------------------------------------------------------------------------------------------------------
void CInfoBar::EndProgressIndicator()
{	
	fInfoBar->SetProgressIndicator( fMaxProgress, fLabel );
	fInfoBar->EndProgressIndicator();
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CInfoBar::Restart( Uint16 nProgress, const TXString& strLabel )
{
	fInfoBar->EndProgressIndicator();
	
	fLabel				= strLabel;
	fCurrentProgress	= 0;
	fMaxProgress		= nProgress;
	
	fInfoBar->StartProgressIndicator( fLabel, fMaxProgress );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CInfoBar::IncrementProgressIndicatorWithStep( Uint16 nProgress )
{
	fCurrentProgress	+= nProgress;
	fInfoBar->SetProgressIndicator( fCurrentProgress, fLabel );	
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CInfoBar::IncrementProgressIndicatorWithPercent( Uint16 nPercent )
{
	double progress	= (double)fMaxProgress * (double)nPercent / 100.0;
	while ( progress >= 1 ) {
		fCurrentProgress++;
		progress--;
	}
	fInfoBar->SetProgressIndicator( fCurrentProgress, fLabel );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CProgressStepper::CProgressStepper(CInfoBar& infoBar, double dPercent, size_t iterations)
	: fInfoBar( infoBar )
	, fpParent( NULL )
	, fPercent( dPercent )
{
	fCurrLoops	= 0;
	fTotalLoops	= iterations;
	this->Init( fPercent, fTotalLoops );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CProgressStepper::CProgressStepper(CProgressStepper& parent, size_t iterations)
	: fInfoBar( parent.fInfoBar )
	, fpParent( &parent )
{
	fCurrLoops	= 0;
	fTotalLoops	= iterations;
	this->Init( fpParent->fStep, fTotalLoops );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CProgressStepper::~CProgressStepper()
{
	// unfinished progress???
	VWFC_ASSERT( fCurrLoops == fTotalLoops );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CProgressStepper::End()
{
	double	totalStep	= 0;
	for(size_t i=fCurrLoops; i<fTotalLoops; i++) {
		double	step = this->LoopNext();
		totalStep	+= step;
	}

	if ( totalStep > 0 ) {
		fInfoBar.IncrementProgressIndicatorWithPercent( (Uint16)totalStep );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CProgressStepper::Init(double dPercent, size_t iterations)
{
	fStep			= dPercent / (double)iterations;
	fIteratorCount	= 1;		// how many iterations
	while ( fStep < 1 ) {
		fStep			*= 10;
		fIteratorCount	*= 10;
	}

	fIterator	= fIteratorCount;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
double CProgressStepper::LoopNext()
{
	double	step = 0;

	fCurrLoops++;
	VWFC_ASSERT( fCurrLoops <= fTotalLoops );
	if ( fCurrLoops <= fTotalLoops ) {
		step = this->UpdateProgress();

		fIterator--;
		if ( fIterator <= 0 ) {
			fIterator = fIteratorCount;
		}
	}

	return step;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CProgressStepper::Next()
{
	double	step = this->LoopNext();
	if ( step > 0 ) {
		fInfoBar.IncrementProgressIndicatorWithPercent( (Uint16) step );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
double CProgressStepper::UpdateProgress()
{
	bool	bDoUpdate	= true;

	CProgressStepper*	pCurrent	= this;
	while ( pCurrent && bDoUpdate ) {
		bDoUpdate	= bDoUpdate && (pCurrent->fIterator == 1);

		pCurrent	= pCurrent->fpParent;
	}

	double	step	= 0;
	if ( bDoUpdate ) {
		step = fStep;
	}

	return step;
}
