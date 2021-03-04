//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/Control.h"
#include "VWFC/VWUI/ComplexDialog.h"
#include "DialogData.h"


#if _MINICAD_
	#ifdef _WINDOWS
	# include <commctrl.h>
	#endif
#endif

using namespace VWFC::VWUI;

typedef std::map<TControlID, IDDXValidator*>	TValidatorsMap;

// ========================================================================================================================
VWComplexDialog::VWComplexDialog( void )
{
	fpData			= SDK_NEW TValidatorsMap;

#ifdef _WINDOWS
	fpToolTipItem	= NULL;
	fhToolTip		= NULL;
	fszMessage		= NULL;
#else
#endif
}

VWComplexDialog::~VWComplexDialog( void ) 
{
	this->HideInvalidMessage();

	TValidatorsMap*	pMapValidators	= (TValidatorsMap*) fpData;
	for(TValidatorsMap::iterator it	= pMapValidators->begin(); it != pMapValidators->end(); ++it) {
		IDDXValidator* pValidator	= it->second;
		if ( pValidator ) {
			delete pValidator;
		}
	}
	pMapValidators->clear();

	delete pMapValidators;
	fpData	= NULL;
}

void VWComplexDialog::ResetDDX( void )
{
	TDDXDataArray &arrDDX	= *((TDDXDataArray*)fpArrDDXData);
	
	arrDDX.clear();
	this->OnDDXInitialize();
}

void VWComplexDialog::AddDDXValidator(TControlID controlID, IDDXValidator* pValidator)
{
	TValidatorsMap*	pMapValidators	= (TValidatorsMap*) fpData;
	pMapValidators->insert( TValidatorsMap::value_type( controlID, pValidator ) );
}

void VWComplexDialog::OnDefaultButtonEvent()
{
	if ( this->Validate() ) {
		VWDialog::OnDefaultButtonEvent();
	}
}

void VWComplexDialog::OnActivateInvalidControl(TControlID controlID)
{
	::GS_SelectEditText( gCBP, this->GetDialogID(), controlID );
}

bool VWComplexDialog::Validate()
{
	return this->Validate( 0 );
}

bool VWComplexDialog::Validate(TControlID controlID)
{
	bool			bValid			= true;

	TValidatorsMap*	pMapValidators	= (TValidatorsMap*) fpData;

	bool			bCheckAll	= controlID == 0;

	TValidatorsMap::iterator	it	= bCheckAll ? pMapValidators->begin() : pMapValidators->find( controlID );
	while( it != pMapValidators->end() ) {
		TControlID		thisCtrlID	= it->first;
		IDDXValidator*	pValidator	= it->second;
		if ( pValidator ) {
			TXString	value;
			if ( this->GetDDXControlValue( thisCtrlID, value ) ) {
				if ( ! pValidator->Validate( value ) ) {
					this->ShowInvalidMessage( thisCtrlID, pValidator );
					if ( bCheckAll ) {
						this->OnActivateInvalidControl( thisCtrlID );
					}

					bValid	= false;
					break;
				}
			}
		}

		++it;
		if ( ! bCheckAll )
			break;
	}

	return bValid;
}

void VWComplexDialog::OnBeforeDispatchEvent(TControlID controlID, VWDialogEventArgs& eventArg)
{
	this->HideInvalidMessage();

	VWDialog::OnBeforeDispatchEvent( controlID, eventArg );

	this->Validate( controlID );
}

void VWComplexDialog::ShowInvalidMessage(TControlID controlID, IDDXValidator* pValidator)
{
#ifdef _WINDOWS
	HWND	hWnd		= ::GS_GetMainHWND( gCBP );
	HWND	hControlWnd	= ::GetDlgItem( hWnd, controlID );

	if ( fpToolTipItem == NULL ) {
		fpToolTipItem	= malloc( sizeof(TOOLINFO) );

		fhToolTip		= CreateWindowEx( 0, TOOLTIPS_CLASS, L"", 
								WS_POPUP | TTS_BALLOON | TTS_NOPREFIX | TTS_ALWAYSTIP, 
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
								CW_USEDEFAULT, hControlWnd, 0, 0, 0);

		DSTOPIF( fhToolTip == NULL, (kVStanev, "Cannot create tooltip window.") );

		if ( fszMessage ) {
			delete fszMessage;
			fszMessage	= NULL;
		}
		TXString	message		= pValidator->GetErrorMessage();
		fszMessage				= SDK_NEW wchar_t[ message.GetLength() + 1 ];
		message.CopyInto( fszMessage, (message.GetLength() + 1) );

		TOOLINFO*	pToolTip	= static_cast<TOOLINFO*>(fpToolTipItem);

		memset( pToolTip, 0, sizeof(TOOLINFO) );
		pToolTip->cbSize		= sizeof(TOOLINFO);
		pToolTip->uFlags		= TTF_SUBCLASS | TTF_TRACK | TTF_TRANSPARENT /*TTF_CENTERTIP*/ | TTF_IDISHWND;
		pToolTip->hwnd			= hControlWnd;
		pToolTip->lpszText		= fszMessage;
		pToolTip->uId			= (UINT_PTR) hControlWnd;

		SendMessage( fhToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) pToolTip );
	}

	Sint32	initial	= GetDoubleClickTime();
	Sint32	autopop	= GetDoubleClickTime() * 10;
	Sint32	reshow	= GetDoubleClickTime() / 5;

	SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_INITIAL,		MAKELONG(initial, 0) ); 
	SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_AUTOPOP,		MAKELONG(autopop, 0) ); 
	SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_RESHOW,		MAKELONG(reshow, 0) ); 
	//SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_AUTOMATIC,	MAKELONG(, 0) );

	SendMessage( fhToolTip, TTM_SETMAXTIPWIDTH, 0, 500 );

	SendMessage( fhToolTip, TTM_SETTITLE, 3/*ERROR*/, (LPARAM) (const char*) pValidator->GetErrorTitle() );

	RECT	ctrlRect;
	GetClientRect( hControlWnd, & ctrlRect );
	POINT	pt;
	pt.x		= ctrlRect.left;
	pt.y		= ctrlRect.bottom;
	ClientToScreen( hControlWnd, &pt );

	SendMessage( fhToolTip, TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x, pt.y) ); 
	SendMessage( fhToolTip, TTM_TRACKACTIVATE, (WPARAM) TRUE, (LPARAM) (TOOLINFO*) fpToolTipItem );
	//SendMessage( fhToolTip, TTM_ACTIVATE, true, 0 );
#else

#endif
}

void VWComplexDialog::HideInvalidMessage()
{
#ifdef _WINDOWS
	if ( fszMessage ) {
		delete fszMessage;
		fszMessage	= NULL;
	}

	if ( fhToolTip ) {
		DestroyWindow( fhToolTip );
	}
	if ( fpToolTipItem ) {
		free( (TOOLINFO*) fpToolTipItem );
	}
	fpToolTipItem	= NULL;
	fhToolTip		= NULL;
#else
#endif
}

// ========================================================================================================================
CDDXValidator_NumberInRange::CDDXValidator_NumberInRange(const TXString& title, const TXString& message, Sint32 value, bool bLessThan, bool bEqual)
{
	fTitle		= title;
	fMessage	= message;
	fMinValue	= value;
	fMaxValue	= value;
	fbSection	= true;
	fbLessThan	= bLessThan;
	fbEqual		= bEqual;
}

CDDXValidator_NumberInRange::CDDXValidator_NumberInRange(const TXString& title, const TXString& message, Sint32 minValue, Sint32 maxValue)
{
	fTitle		= title;
	fMessage	= message;
	fMinValue	= minValue;
	fMaxValue	= maxValue;
	fbSection	= false;
	fbLessThan	= false;
	fbEqual		= false;
}

TXString CDDXValidator_NumberInRange::GetErrorTitle() const
{
	return fTitle;
}

TXString CDDXValidator_NumberInRange::GetErrorMessage() const
{
	return fMessage;
}

bool CDDXValidator_NumberInRange::IsNumber(const TXString& value) const
{
	bool	bIsNumber	= true;
	size_t	cnt			= value.GetLength();
	for(size_t i=0; i<cnt; i++) {
		UCChar	ch	= value.GetAt( i );
		if ( ch == '-' || ch == '+' ) {
			if ( i != 0 ) { 
				bIsNumber	= false;
				break;
			}
		}
		else if ( ! ( (((ch) >= '0') && ((ch) <= '9')) ) ) {
			bIsNumber	= false;
			break;
		}
	}

	return bIsNumber;
}

bool CDDXValidator_NumberInRange::Validate(const TXString& value) const
{
	bool	bValid		= false;
	if ( this->IsNumber( value ) ) {
		Sint32	thisValue	= value.atoi();
		if ( fbSection ) {
			bValid	= fbLessThan ? (thisValue < fMinValue) : (thisValue > fMaxValue);
			if ( ! bValid && fbEqual ) {
				bValid	= (thisValue == fMinValue);
			}
		}
		else {
			bValid	= (fMinValue <= thisValue) && (thisValue <= fMaxValue);
		}
	}

	return bValid;
}

// ========================================================================================================================
CDDXValidator_RealInRange::CDDXValidator_RealInRange(const TXString& title, const TXString& message, double value, bool bLessThan, bool bEqual, double dEpsilon)
{
	fTitle		= title;
	fMessage	= message;
	fEpsilon	= dEpsilon;
	fMinValue	= value;
	fMaxValue	= value;
	fbSection	= true;
	fbLessThan	= bLessThan;
	fbEqual		= bEqual;
}

CDDXValidator_RealInRange::CDDXValidator_RealInRange(const TXString& title, const TXString& message, double minValue, double maxValue, double dEpsilon)
{
	fTitle		= title;
	fMessage	= message;
	fEpsilon	= dEpsilon;
	fMinValue	= minValue;
	fMaxValue	= maxValue;
	fbSection	= false;
	fbLessThan	= false;
	fbEqual		= false;
}

TXString CDDXValidator_RealInRange::GetErrorTitle() const
{
	return fTitle;
}

TXString CDDXValidator_RealInRange::GetErrorMessage() const
{
	return fMessage;
}

bool CDDXValidator_RealInRange::IsNumber(const TXString& value) const
{
	bool	bIsNumber	= true;
	size_t	cnt			= value.GetLength();
	for(size_t i=0; i<cnt; i++) {
		UCChar	ch	= value.GetAt( i );
		if ( ch == '-' || ch == '+' ) {
			if ( i != 0 ) { 
				bIsNumber	= false;
				break;
			}
		}
		else if ( ch == '.' ) {
			// it is ok!
		}
		else if ( ! ( (((ch) >= '0') && ((ch) <= '9')) ) ) {
			bIsNumber	= false;
			break;
		}
	}

	return bIsNumber;
}

bool CDDXValidator_RealInRange::Validate(const TXString& value) const
{
	bool	bValid		= false;
	if ( this->IsNumber( value ) ) {
		double	thisValue	= value.atof();
		if ( fbSection ) {
			bValid	= fbLessThan ? (thisValue < fMinValue) : (thisValue > fMaxValue);
			if ( ! bValid && fbEqual ) {
				bValid	= Abs(thisValue - fMinValue) < fEpsilon;
			}
		}
		else {
			bValid	= (fMinValue < thisValue && thisValue < fMaxValue) || Abs(thisValue - fMinValue) < fEpsilon;
		}
	}

	return bValid;
}
