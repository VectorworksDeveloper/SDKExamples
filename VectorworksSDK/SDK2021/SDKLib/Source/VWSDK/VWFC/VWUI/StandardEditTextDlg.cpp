//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/StandardEditTextDlg.h"


#define			kStaticTextControl				4
#define			kEditTextControl				5
#define			kEditRealControl				6
#define			kEditIntegerControl				7
#define			kEditRealControlX				8
#define			kEditRealControlY				9
#define			kEditRealControlZ				10
#define			kStaticTextControlX				11
#define			kStaticTextControlY				12
#define			kStaticTextControlZ				13


using namespace VWFC::VWUI;
using namespace VWFC::Math;

EVENT_DISPATCH_MAP_BEGIN( CStandardEditTextBoxDlg );
ADD_DISPATCH_EVENT( kEditTextControl, OnEditControl );
EVENT_DISPATCH_MAP_END;

// ------------------------------------------------------------------------------------------
// SDDXVec3D.
// ------------------------------------------------------------------------------------------
void CStandardEditTextBoxDlg::SDDXVec3D::Set2D(const VWPoint2D& vec2D)
{
	fX	= vec2D.x;
	fY	= vec2D.y;
}

// ------------------------------------------------------------------------------------------
void CStandardEditTextBoxDlg::SDDXVec3D::Set3D(const VWPoint3D& vec3D)
{
	fX	= vec3D.x;
	fY	= vec3D.y;
	fZ	= vec3D.z;
}

// ------------------------------------------------------------------------------------------
VWPoint2D CStandardEditTextBoxDlg::SDDXVec3D::Get2D() const
{
	return	( VWPoint2D( fX, fY ) );
}

// ------------------------------------------------------------------------------------------
VWPoint3D CStandardEditTextBoxDlg::SDDXVec3D::Get3D() const
{
	return	( VWPoint3D( fX, fY, fZ ) );
}

// ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------
CStandardEditTextBoxDlg::CStandardEditTextBoxDlg(	const TXString& 	strTitle,
													const TXString& 	strLabel,
													const TXString& 	strValue,
													const TXString& 	strOkBtnText,
													const TXString& 	strCancelBntText)
: fStaticTextCtrl	( kStaticTextControl	),
  fStaticTextCtrlX	( kStaticTextControlX	),
  fStaticTextCtrlY	( kStaticTextControlY	),
  fStaticTextCtrlZ	( kStaticTextControlZ	),
  fEditTextCtrl		( kEditTextControl		),
  fEditIntegerCtrl	( kEditIntegerControl	),
  fEditRealCtrl		( kEditRealControl		),
  fEditRealCtrlX	( kEditRealControlX		),
  fEditRealCtrlY	( kEditRealControlY		),
  fEditRealCtrlZ	( kEditRealControlZ		)
{
	fbAllowEmtpyResult	= false;
	fbIsReadOnly		= false;
	fstrTitle			= strTitle;
	fstrLabel			= strLabel;
	fDDXTypeDlg			= EDlgValType::eDlgVal_String;
	fDDXTextValue		= strValue;
	fstrOrgValue		= strValue;
	fnBoxWidth			= 35;
	fnBoxHeight			= 1;
	fstrOkBtnText		= strOkBtnText;
	fstrCancelBntText	= strCancelBntText;

	if ( fstrOkBtnText.IsEmpty() )
		fstrOkBtnText = TXResource("Vectorworks/Strings/144 *", "1" );
	if ( fstrCancelBntText.IsEmpty() )
		fstrCancelBntText = TXResource("Vectorworks/Strings/144 *", "6" );
}

CStandardEditTextBoxDlg::CStandardEditTextBoxDlg(	const TXString& 	strTitle,
													const TXString& 	strLabel,
													const TXString& 	strValue,
													size_t				nBoxWidth,
													size_t				nBoxHeight,
													const TXString& 	strOkBtnText,
													const TXString& 	strCancelBntText)
: fStaticTextCtrl	( kStaticTextControl	),
  fStaticTextCtrlX	( kStaticTextControlX	),
  fStaticTextCtrlY	( kStaticTextControlY	),
  fStaticTextCtrlZ	( kStaticTextControlZ	),
  fEditTextCtrl		( kEditTextControl		),
  fEditIntegerCtrl	( kEditIntegerControl	),
  fEditRealCtrl		( kEditRealControl		),
  fEditRealCtrlX	( kEditRealControlX		),
  fEditRealCtrlY	( kEditRealControlY		),
  fEditRealCtrlZ	( kEditRealControlZ		)
{
	fbAllowEmtpyResult	= false;
	fbIsReadOnly		= false;
	fstrTitle			= strTitle;
	fstrLabel			= strLabel;
	fDDXTypeDlg			= EDlgValType::eDlgVal_String;
	fDDXTextValue		= strValue;
	fstrOrgValue		= strValue;
	fnBoxWidth			= nBoxWidth;
	fnBoxHeight			= nBoxHeight;
	fstrOkBtnText		= strOkBtnText;
	fstrCancelBntText	= strCancelBntText;

	if ( fstrOkBtnText.IsEmpty() )
		fstrOkBtnText = TXResource("Vectorworks/Strings/144 *", "1" );
	if ( fstrCancelBntText.IsEmpty() )
		fstrCancelBntText = TXResource("Vectorworks/Strings/144 *", "6" );
}

CStandardEditTextBoxDlg::CStandardEditTextBoxDlg(	const TXString& 	strTitle,
													const TXString& 	strLabel,
													const EDlgValType&	numValType,
													const TXString& 	strOkBtnText,
													const TXString& 	strCancelBntText)
: fStaticTextCtrl	( kStaticTextControl	), 
  fStaticTextCtrlX	( kStaticTextControlX	),
  fStaticTextCtrlY	( kStaticTextControlY	),
  fStaticTextCtrlZ	( kStaticTextControlZ	),
  fEditTextCtrl		( kEditTextControl		),
  fEditIntegerCtrl	( kEditIntegerControl	),
  fEditRealCtrl		( kEditRealControl		),
  fEditRealCtrlX	( kEditRealControlX		),
  fEditRealCtrlY	( kEditRealControlY		),
  fEditRealCtrlZ	( kEditRealControlZ		)
{
	fbAllowEmtpyResult	= false;
	fbIsReadOnly		= false;
	fstrTitle			= strTitle;
	fstrLabel			= strLabel;
	fDDXTypeDlg			= numValType;
	fnBoxWidth			= 35;
	fnBoxHeight			= 1;
	fstrOkBtnText		= strOkBtnText;
	fstrCancelBntText	= strCancelBntText;

	fDDXIntVal			= 0;
	fDDXVec3DVal.fX		= 0.0;
	fDDXVec3DVal.fY		= 0.0;
	fDDXVec3DVal.fZ		= 0.0;

	if ( fstrOkBtnText.IsEmpty() )
		fstrOkBtnText = TXResource("Vectorworks/Strings/144 *", "1" );
	if ( fstrCancelBntText.IsEmpty() )
		fstrCancelBntText = TXResource("Vectorworks/Strings/144 *", "6" );
}

CStandardEditTextBoxDlg::CStandardEditTextBoxDlg(	const TXString& 	strTitle,
													const TXString& 	strLabel,
													const EDlgValType&	numValType,
													size_t				nBoxWidth,
													size_t				nBoxHeight,
													const TXString& 	strOkBtnText,
													const TXString& 	strCancelBntText)
: fStaticTextCtrl	( kStaticTextControl	), 
  fStaticTextCtrlX	( kStaticTextControlX	),
  fStaticTextCtrlY	( kStaticTextControlY	),
  fStaticTextCtrlZ	( kStaticTextControlZ	),
  fEditTextCtrl		( kEditTextControl		),
  fEditIntegerCtrl	( kEditIntegerControl	),
  fEditRealCtrl		( kEditRealControl		),
  fEditRealCtrlX	( kEditRealControlX		),
  fEditRealCtrlY	( kEditRealControlY		),
  fEditRealCtrlZ	( kEditRealControlZ		)
{
	fbAllowEmtpyResult	= false;
	fbIsReadOnly		= false;
	fstrTitle			= strTitle;
	fstrLabel			= strLabel;
	fDDXTypeDlg			= numValType;
	fnBoxWidth			= 35;
	fnBoxHeight			= 1;
	fstrOkBtnText		= strOkBtnText;
	fstrCancelBntText	= strCancelBntText;

	fDDXIntVal			= 0;
	fDDXVec3DVal.fX		= 0.0;
	fDDXVec3DVal.fY		= 0.0;
	fDDXVec3DVal.fZ		= 0.0;

	if ( fstrOkBtnText.IsEmpty() )
		fstrOkBtnText = TXResource("Vectorworks/Strings/144 *", "1" );
	if ( fstrCancelBntText.IsEmpty() )
		fstrCancelBntText = TXResource("Vectorworks/Strings/144 *", "6" );
}

CStandardEditTextBoxDlg::~CStandardEditTextBoxDlg()
{
}

void CStandardEditTextBoxDlg::SetReadOnly(bool bReadOnly)
{
	fbIsReadOnly		= bReadOnly;
}

void CStandardEditTextBoxDlg::SetAllowEmptyResult(bool bAllowEmptyRes)
{
	fbAllowEmtpyResult	= bAllowEmptyRes;
}

void CStandardEditTextBoxDlg::SetValuePrefixLabels(const TXString& strX, const TXString& strY, const TXString& strZ)
{
	fstrPrefixX = strX;
	fstrPrefixY = strY;
	fstrPrefixZ = strZ;
}

void CStandardEditTextBoxDlg::SetRealValue(double realValue) 
{
	fDDXVec3DVal.fX		= realValue;
}

void CStandardEditTextBoxDlg::SetIntegerValue(Sint32 integerValue) 
{
	fDDXIntVal			= integerValue;
}

void CStandardEditTextBoxDlg::SetPoint2D(const VWPoint2D& point2D)
{
	fDDXVec3DVal.Set2D( point2D );
}

void CStandardEditTextBoxDlg::SetPoint3D(const VWPoint3D& point3D)
{
	fDDXVec3DVal.Set3D( point3D );
}

void CStandardEditTextBoxDlg::SetAngleValue(double angleValue)
{
	fDDXVec3DVal.fX		= angleValue;
}

void CStandardEditTextBoxDlg::Set2DAngleValue(double angleValueX, double angleValueY)
{
	fDDXVec3DVal.fX		= angleValueX;
	fDDXVec3DVal.fY		= angleValueY;
	fDDXVec3DVal.fZ		= 0;
}

void CStandardEditTextBoxDlg::Set3DAngleValue(double angleValueX, double angleValueY, double angleValueZ)
{
	fDDXVec3DVal.fX		= angleValueX;
	fDDXVec3DVal.fY		= angleValueY;
	fDDXVec3DVal.fZ		= angleValueZ;
}

TXString CStandardEditTextBoxDlg::GetValue() const
{
	return fDDXTextValue;
}

double	CStandardEditTextBoxDlg::GetRealValue() const
{
	return ( fDDXVec3DVal.fX );
}

Sint32 CStandardEditTextBoxDlg::GetIntegerValue() const
{
	return fDDXIntVal;
}

VWPoint2D CStandardEditTextBoxDlg::GetPoint2D() const
{
	return ( fDDXVec3DVal.Get2D() );
}

VWPoint3D CStandardEditTextBoxDlg::GetPoint3D() const
{
	return ( fDDXVec3DVal.Get3D() );
}

double CStandardEditTextBoxDlg::GetAngleValue() const
{
	return fDDXVec3DVal.fX;
}

void CStandardEditTextBoxDlg::Get2DAngleValue(double& angleValueX, double& angleValueY)
{
	angleValueX		= fDDXVec3DVal.fX;
	angleValueY		= fDDXVec3DVal.fY;
}

void CStandardEditTextBoxDlg::Get3DAngleValue(double& angleValueX, double& angleValueY, double& angleValueZ)
{
	angleValueX		= fDDXVec3DVal.fX;
	angleValueY		= fDDXVec3DVal.fY;
	angleValueZ		= fDDXVec3DVal.fZ;
}

bool CStandardEditTextBoxDlg::CreateDialogLayout()
{
	// init.
	bool	isOK	= true;

	bool resizeHeight = fDDXTypeDlg == EDlgValType::eDlgVal_String && fnBoxHeight > 1;

	// create the dialog layout.
	isOK	= this->CreateDialog( fstrTitle, fstrOkBtnText, fstrCancelBntText, false, true, resizeHeight );

	// create the controls in the dialog.
	isOK	= ( isOK && fStaticTextCtrl.CreateControl( this, fstrLabel ) );

	if ( isOK )
	{
		switch ( fDDXTypeDlg )
		{
			case EDlgValType::eDlgVal_String:
				{
					isOK	= fEditTextCtrl.CreateControl( this, fDDXTextValue, (short) fnBoxWidth, (short) fnBoxHeight );

					if ( isOK )
					{
						fEditTextCtrl.SetEdgeBinding( true, true, true, true );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fEditTextCtrl );
					}
				}
				break;

			case EDlgValType::eDlgVal_Real:
				{
					isOK	= fEditRealCtrl.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlReal );

					if ( isOK )
					{
						fEditRealCtrl.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fEditRealCtrl );
					}
				}
				break;

			case EDlgValType::eDlgVal_Int:
				{
					isOK	= fEditIntegerCtrl.CreateControl( this, fDDXIntVal, (short) fnBoxWidth );

					if ( isOK )
					{
						fEditIntegerCtrl.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fEditIntegerCtrl );
					}
				}
				break;

			case EDlgValType::eDlgVal_Angle:
				{
					isOK	= fEditRealCtrl.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlAngle );

					if ( isOK )
					{
						fEditRealCtrl.SetEdgeBinding( true, true, false, false );
					
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddRightControl( & fStaticTextCtrl, & fEditRealCtrl );
					}
				}
				break;

			case EDlgValType::eDlgVal_Angle2D:
				{
					isOK	= fEditRealCtrlX.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlAngle );
					isOK	= ( isOK && fEditRealCtrlY.CreateControl( this, fDDXVec3DVal.fY, (short) fnBoxWidth, VWEditRealCtrl::kEditControlAngle ) );

					TXString x = fstrPrefixX.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "4" ) : fstrPrefixX;
					TXString y = fstrPrefixY.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "5" ) : fstrPrefixY;
					short w = -1;
					if ( ! x.IsEmpty() || ! y.IsEmpty() )
					{
						w = DemoteTo<short>( kVStanev, x.GetLength() );
						w = std::max( w, DemoteTo<short>( kVStanev, y.GetLength() ) );
					}

					isOK	= ( isOK && fStaticTextCtrlX.CreateControl( this, x, w ) );
					isOK	= ( isOK && fStaticTextCtrlY.CreateControl( this, y, w ) );

					if ( isOK )
					{
						fEditRealCtrlX.SetEdgeBinding( true, true, false, false );
						fEditRealCtrlY.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fStaticTextCtrlX );
						this->AddRightControl( & fStaticTextCtrlX, & fEditRealCtrlX);

						this->AddBelowControl( & fStaticTextCtrlX, & fStaticTextCtrlY );
						this->AddRightControl( & fStaticTextCtrlY, & fEditRealCtrlY);
					}
				}
				break;

			case EDlgValType::eDlgVal_Angle3D:
				{
					isOK	= fEditRealCtrlX.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlAngle );
					isOK	= ( isOK && fEditRealCtrlY.CreateControl( this, fDDXVec3DVal.fY, (short) fnBoxWidth, VWEditRealCtrl::kEditControlAngle ) );
					isOK	= ( isOK && fEditRealCtrlZ.CreateControl( this, fDDXVec3DVal.fZ, (short) fnBoxWidth, VWEditRealCtrl::kEditControlAngle ) );

					TXString x = fstrPrefixX.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "4" ) : fstrPrefixX;
					TXString y = fstrPrefixY.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "5" ) : fstrPrefixY;
					TXString z = fstrPrefixZ.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "6" ) : fstrPrefixZ;
					short w = -1;
					if ( ! x.IsEmpty() || ! y.IsEmpty() || ! z.IsEmpty() )
					{
						w = DemoteTo<short>( kVStanev, x.GetLength() );
						w = std::max( w, DemoteTo<short>( kVStanev, y.GetLength() ) );
						w = std::max( w, DemoteTo<short>( kVStanev, z.GetLength() ) );
					}

					isOK	= ( isOK && fStaticTextCtrlX.CreateControl( this, x, w ) );
					isOK	= ( isOK && fStaticTextCtrlY.CreateControl( this, y, w ) );
					isOK	= ( isOK && fStaticTextCtrlZ.CreateControl( this, z, w ) );

					if ( isOK )
					{
						fEditRealCtrlX.SetEdgeBinding( true, true, false, false );
						fEditRealCtrlY.SetEdgeBinding( true, true, false, false );
						fEditRealCtrlZ.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fStaticTextCtrlX );
						this->AddRightControl( & fStaticTextCtrlX, & fEditRealCtrlX);

						this->AddBelowControl( & fStaticTextCtrlX, & fStaticTextCtrlY );
						this->AddRightControl( & fStaticTextCtrlY, & fEditRealCtrlY);

						this->AddBelowControl( & fStaticTextCtrlY, & fStaticTextCtrlZ );
						this->AddRightControl( & fStaticTextCtrlZ, & fEditRealCtrlZ);
					}
				}
				break;

			case EDlgValType::eDlgVal_Pt2D:
				{
					isOK	= fEditRealCtrlX.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlReal );
					isOK	= ( isOK && fEditRealCtrlY.CreateControl( this, fDDXVec3DVal.fY, (short) fnBoxWidth, VWEditRealCtrl::kEditControlReal ) );

					TXString x = fstrPrefixX.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "4" ) : fstrPrefixX;
					TXString y = fstrPrefixY.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "5" ) : fstrPrefixY;
					short w = -1;
					if ( ! x.IsEmpty() || ! y.IsEmpty() )
					{
						w = DemoteTo<short>( kVStanev, x.GetLength() );
						w = std::max( w, DemoteTo<short>( kVStanev, y.GetLength() ) );
					}

					isOK	= ( isOK && fStaticTextCtrlX.CreateControl( this, x, w ) );
					isOK	= ( isOK && fStaticTextCtrlY.CreateControl( this, y, w ) );

					if ( isOK )
					{
						fEditRealCtrlX.SetEdgeBinding( true, true, false, false );
						fEditRealCtrlY.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fStaticTextCtrlX );
						this->AddRightControl( & fStaticTextCtrlX, & fEditRealCtrlX);

						this->AddBelowControl( & fStaticTextCtrlX, & fStaticTextCtrlY );
						this->AddRightControl( & fStaticTextCtrlY, & fEditRealCtrlY);
					}
				}
				break;

			case EDlgValType::eDlgVal_Pt3D:
				{
					isOK	= fEditRealCtrlX.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlReal );
					isOK	= ( isOK && fEditRealCtrlY.CreateControl( this, fDDXVec3DVal.fY, (short) fnBoxWidth, VWEditRealCtrl::kEditControlReal ) );
					isOK	= ( isOK && fEditRealCtrlZ.CreateControl( this, fDDXVec3DVal.fZ, (short) fnBoxWidth, VWEditRealCtrl::kEditControlReal ) );

					TXString x = fstrPrefixX.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "4" ) : fstrPrefixX;
					TXString y = fstrPrefixY.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "5" ) : fstrPrefixY;
					TXString z = fstrPrefixZ.IsEmpty() ? TXResource( "Vectorworks/Strings/204 *", "6" ) : fstrPrefixZ;
					short w = -1;
					if ( ! x.IsEmpty() || ! y.IsEmpty() || ! z.IsEmpty() )
					{
						w = DemoteTo<short>( kVStanev, x.GetLength() );
						w = std::max( w, DemoteTo<short>( kVStanev, y.GetLength() ) );
						w = std::max( w, DemoteTo<short>( kVStanev, z.GetLength() ) );
					}

					isOK	= ( isOK && fStaticTextCtrlX.CreateControl( this, x, w ) );
					isOK	= ( isOK && fStaticTextCtrlY.CreateControl( this, y, w ) );
					isOK	= ( isOK && fStaticTextCtrlZ.CreateControl( this, z, w ) );

					if ( isOK )
					{
						fEditRealCtrlX.SetEdgeBinding( true, true, false, false );
						fEditRealCtrlY.SetEdgeBinding( true, true, false, false );
						fEditRealCtrlZ.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fStaticTextCtrlX );
						this->AddRightControl( & fStaticTextCtrlX, & fEditRealCtrlX);

						this->AddBelowControl( & fStaticTextCtrlX, & fStaticTextCtrlY );
						this->AddRightControl( & fStaticTextCtrlY, & fEditRealCtrlY);

						this->AddBelowControl( & fStaticTextCtrlY, & fStaticTextCtrlZ );
						this->AddRightControl( & fStaticTextCtrlZ, & fEditRealCtrlZ);
					}
				}
				break;

				case EDlgValType::eDlgVal_Dim:
				{
					isOK	= fEditRealCtrl.CreateControl( this, fDDXVec3DVal.fX, (short) fnBoxWidth, VWEditRealCtrl::kEditControlDimension );

					if ( isOK )
					{
						fEditRealCtrl.SetEdgeBinding( true, true, false, false );
						
						this->AddFirstGroupControl( & fStaticTextCtrl );
						this->AddBelowControl( & fStaticTextCtrl, & fEditRealCtrl );
					}
				}
				break;

			default:
				{
					VWFC_ASSERT( false );	// 'fDDXTypeDlg' not set.
					isOK	= false;
				}
				break;
		}
	}

	// result.
	return	( isOK );
}

void CStandardEditTextBoxDlg::OnDDXInitialize()
{
	// add DDX variables to the control.
	switch ( fDDXTypeDlg )
	{
		case EDlgValType::eDlgVal_String:
			this->AddDDX_EditText	( kEditTextControl		,	& fDDXTextValue	);
			break;

		case EDlgValType::eDlgVal_Real:	
			this->AddDDX_EditReal	( kEditRealControl		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlReal	);
			break;

		case EDlgValType::eDlgVal_Int:	
			this->AddDDX_EditInteger( kEditIntegerControl	,	& fDDXIntVal );
			break;

		case EDlgValType::eDlgVal_Angle:
			this->AddDDX_EditReal	( kEditRealControl		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlAngle	);
			break;

		case EDlgValType::eDlgVal_Angle2D:
			this->AddDDX_EditReal	( kEditRealControlX		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlAngle	);
			this->AddDDX_EditReal	( kEditRealControlY		,	& fDDXVec3DVal.fY		,	VWEditRealCtrl::kEditControlAngle	);
			break;

		case EDlgValType::eDlgVal_Angle3D:
			this->AddDDX_EditReal	( kEditRealControlX		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlAngle	);
			this->AddDDX_EditReal	( kEditRealControlY		,	& fDDXVec3DVal.fY		,	VWEditRealCtrl::kEditControlAngle	);
			this->AddDDX_EditReal	( kEditRealControlZ		,	& fDDXVec3DVal.fZ		,	VWEditRealCtrl::kEditControlAngle	);
			break;

		case EDlgValType::eDlgVal_Pt2D:
			this->AddDDX_EditReal	( kEditRealControlX		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlReal	);
			this->AddDDX_EditReal	( kEditRealControlY		,	& fDDXVec3DVal.fY		,	VWEditRealCtrl::kEditControlReal	);
			break;

		case EDlgValType::eDlgVal_Pt3D:
			this->AddDDX_EditReal	( kEditRealControlX		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlReal	);
			this->AddDDX_EditReal	( kEditRealControlY		,	& fDDXVec3DVal.fY		,	VWEditRealCtrl::kEditControlReal	);
			this->AddDDX_EditReal	( kEditRealControlZ		,	& fDDXVec3DVal.fZ		,	VWEditRealCtrl::kEditControlReal	);
			break;

		case EDlgValType::eDlgVal_Dim:	
			this->AddDDX_EditReal	( kEditRealControl		,	& fDDXVec3DVal.fX		,	VWEditRealCtrl::kEditControlDimension	);
			break;

		default:
			VWFC_ASSERT( false );	// 'fDDXTypeDlg' not set.
	}
}

void CStandardEditTextBoxDlg::OnSetUpEvent()
{
	VWDialog::OnSetUpEvent();
}

void CStandardEditTextBoxDlg::OnEditControl(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	if ( fbIsReadOnly ) {
		fDDXTextValue	= fstrOrgValue;
		this->UpdateData( true );
	}
}

void CStandardEditTextBoxDlg::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	if ( ! fbAllowEmtpyResult ) 
	{
		switch ( fDDXTypeDlg )
		{
			case EDlgValType::eDlgVal_String:
				this->EnableControl( kDefaultButtonID, ( ! fDDXTextValue.IsEmpty() ) );
				break;

			case EDlgValType::eDlgVal_Int:
				this->EnableControl( kDefaultButtonID, ( ! fEditIntegerCtrl.GetControlText().IsEmpty() ) );
				break;

			case EDlgValType::eDlgVal_Real:
			case EDlgValType::eDlgVal_Angle:
			case EDlgValType::eDlgVal_Dim:
				this->EnableControl( kDefaultButtonID, ( ! fEditRealCtrl.GetControlText().IsEmpty() ) );
				break;

			case EDlgValType::eDlgVal_Pt2D:
			case EDlgValType::eDlgVal_Angle2D:
				this->EnableControl( kDefaultButtonID, ( ! fEditRealCtrlX.GetControlText().IsEmpty() &&
														 ! fEditRealCtrlY.GetControlText().IsEmpty() ) );
				break;

			case EDlgValType::eDlgVal_Angle3D:
			case EDlgValType::eDlgVal_Pt3D:
				this->EnableControl( kDefaultButtonID, ( ! fEditRealCtrlX.GetControlText().IsEmpty() &&
														 ! fEditRealCtrlY.GetControlText().IsEmpty() &&
														 ! fEditRealCtrlZ.GetControlText().IsEmpty() ) );
				break;

			default:
				VWFC_ASSERT( false );	// 'fDDXTypeDlg' not set.
		}
	}
}
