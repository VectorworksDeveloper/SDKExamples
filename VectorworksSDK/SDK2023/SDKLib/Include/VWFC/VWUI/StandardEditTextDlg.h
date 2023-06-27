//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Dialog.h"
#include "StaticTextCtrl.h"
#include "EditTextCtrl.h"
#include "EditRealCtrl.h"
#include "EditIntegerCtrl.h"

namespace VWFC
{
	namespace VWUI
	{
		enum EDlgValType
		{
			eDlgVal_String,
			eDlgVal_String2,
			eDlgVal_Real,
			eDlgVal_Int,
			eDlgVal_Angle,
			eDlgVal_Angle2D,
			eDlgVal_Angle3D,
			eDlgVal_Pt2D,
			eDlgVal_Pt3D,
			eDlgVal_Dim,
		};

		// ---------------------------------------------------------------------------------------------------------------
		class CStandardEditTextBoxDlg : public VWDialog
		{
		public:
								// One single-line edit field
								CStandardEditTextBoxDlg(const TXString& 	strTitle,
														const TXString& 	strLabel,
														const TXString& 	strValue,
														const TXString& 	strOkBtnText		= "",	// default "OK"
														const TXString& 	strCancelBntText	= "",	// default "Cancel" 
														const TXString&		strHelpText			= "" );

								// One multi-line edit field
								CStandardEditTextBoxDlg(const TXString& 	strTitle,
														const TXString& 	strLabel,
														const TXString& 	strValue,
														size_t				nBoxWidth,
														size_t				nBoxHeight,
														const TXString& 	strOkBtnText		= "",	// default "OK"
														const TXString& 	strCancelBntText	= "",	// default "Cancel" 
														const TXString&		strHelpText			= "" );

								// One or two single-line edit fields depending on the 'EDlgValType'
								CStandardEditTextBoxDlg(const TXString& 	strTitle,
														const TXString& 	strLabel,
														const EDlgValType&	numValType,
														const TXString& 	strOkBtnText		= "",	// default "OK"
														const TXString& 	strCancelBntText	= "",	// default "Cancel" 
														const TXString&		strHelpText			= "" );

								// One or two single-line edit fields depending on the 'EDlgValType'
								CStandardEditTextBoxDlg(const TXString& 	strTitle,
														const TXString& 	strLabel,
														const EDlgValType&	numValType,
														size_t				nBoxWidth,
														size_t				nBoxHeight,
														const TXString& 	strOkBtnText		= "",	// default "OK"
														const TXString& 	strCancelBntText	= "",	// default "Cancel" 
														const TXString&		strHelpText			= "" );
							
								// Two single-line text edit fields
								CStandardEditTextBoxDlg(const TXString& 	strTitle,
														const TXString& 	strLabel1,
														const TXString& 	strLabel2,
														const TXString& 	strValue1,
														const TXString& 	strValue2,
														const TXString&		strHelpText1,
														const TXString&		strHelpText2,
														const TXString& 	strOkBtnText		= "",	// default "OK"
														const TXString& 	strCancelBntText	= "" );	// default "Cancel" 

			virtual				~CStandardEditTextBoxDlg();

			void				SetReadOnly(bool bReadOnly);
			void				SetAllowEmptyResult(bool bAllowEmptyRes, bool allowEmptyValue2=true);
			// used for prefixes of points and angle's x,y,z values
			// pass in empty strings to use default
			void				SetValuePrefixLabels(const TXString& strX, const TXString& strY, const TXString& strZ);

			void				SetRealValue(double realValue);
			void				SetIntegerValue(Sint32 integerValue);
			void				SetPoint2D(const VWPoint2D& point2D);
			void				SetPoint3D(const VWPoint3D& point3D);			
			void				SetAngleValue(double angleValue);
			void				Set2DAngleValue(double angleValueX, double angleValueY);
			void				Set3DAngleValue(double angleValueX, double angleValueY, double angleValueZ);

			TXString			GetValue() const;
			TXString			GetValue2() const;
			double				GetRealValue() const;
			Sint32				GetIntegerValue() const;
			VWPoint2D			GetPoint2D() const;
			VWPoint3D			GetPoint3D() const;
			double				GetAngleValue() const;
			void				Get2DAngleValue(double& angleValueX, double& angleValueY);
			void				Get3DAngleValue(double& angleValueX, double& angleValueY, double& angleValueZ);

		protected:
			virtual bool		CreateDialogLayout();
			virtual	void		OnDDXInitialize();

			virtual void		OnSetUpEvent();
			virtual void		OnUpdateUI();
			virtual void		OnDefaultButtonEvent();

		// dispatch map
		protected:
			DEFINE_EVENT_DISPATH_MAP;
			void				OnEditControl(TControlID controlID, VWDialogEventArgs& eventArgs);
			void				OnEditControl2(TControlID controlID, VWDialogEventArgs& eventArgs);

		protected:
			bool				ValidateRealControl(VWEditRealCtrl& ctrl, VWEditRealCtrl::EEditControlType type);

		private:
			VWStaticTextCtrl	fStaticTextCtrl;
			VWStaticTextCtrl	fStaticTextCtrl2;
			VWStaticTextCtrl	fStaticTextCtrlX;
			VWStaticTextCtrl	fStaticTextCtrlY;
			VWStaticTextCtrl	fStaticTextCtrlZ;

			VWEditIntegerCtrl	fEditIntegerCtrl;
			VWEditRealCtrl		fEditRealCtrl;
			VWEditRealCtrl		fEditRealCtrlX;
			VWEditRealCtrl		fEditRealCtrlY;
			VWEditRealCtrl		fEditRealCtrlZ;
			VWEditTextCtrl		fEditTextCtrl;
			VWEditTextCtrl		fEditTextCtrl2;

			bool				fbIsReadOnly;
			bool				fbAllowEmtpyResult;
			bool				fbAllowEmtpyResult2	= true;

			TXString			fstrTitle;
			TXString			fstrLabel;
			TXString			fstrLabel2;
			TXString			fstrOkBtnText;
			TXString			fstrCancelBntText;
			TXString			fstrOrgValue;
			TXString			fstrOrgValue2;
			TXString			fstrPrefixX;
			TXString			fstrPrefixY;
			TXString			fstrPrefixZ;

			size_t				fnBoxWidth;
			size_t				fnBoxHeight;

			TXString 			fHelpText;
			TXString 			fHelpText2;

			EDlgValType			fDDXTypeDlg;

			// DDX.
			struct SDDXVec3D
			{
				void			Set2D(const VWPoint2D& vec2D);
				void			Set3D(const VWPoint3D& vec3D);

				VWPoint2D		Get2D() const;
				VWPoint3D		Get3D() const;

				double			fX, fY, fZ;
			};

			TXString			fDDXTextValue;
			TXString			fDDXTextValue2;

			union
			{
				Sint32			fDDXIntVal;
				SDDXVec3D		fDDXVec3DVal;
			};
		};
	}
}