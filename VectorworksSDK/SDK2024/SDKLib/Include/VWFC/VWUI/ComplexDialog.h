//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Dialog.h"

namespace VWFC
{
	namespace VWUI
	{
		// ---------------------------------------------------------
		class IDDXValidator
		{
		public:
			virtual				~IDDXValidator()	{}
			virtual TXString	GetErrorTitle() const = 0;
			virtual TXString	GetErrorMessage() const = 0;
			virtual bool		Validate(const TXString& value) const = 0;
		};

		// ---------------------------------------------------------
		class VWComplexDialog : public VWDialog
		{
		protected:
							VWComplexDialog( void );

		public:
			virtual			~VWComplexDialog( void );

		// events
		protected:
			virtual void	OnDefaultButtonEvent();
			virtual void	OnBeforeDispatchEvent(TControlID controlID, VWDialogEventArgs& eventArg);

		protected:
			virtual void	ResetDDX( void );

			bool			Validate();
			bool			Validate(TControlID controlID);
			void			AddDDXValidator(TControlID controlID, IDDXValidator* pValidator);
			void			OnActivateInvalidControl(TControlID controlID);

		protected:
			virtual void	ShowInvalidMessage(TControlID controlID, IDDXValidator* pValidator);
			virtual void	HideInvalidMessage();

		private:
			void*			fpData;
			
#ifdef _WINDOWS
	#if defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
			void*			fpToolTipItem;
			HWND			fhToolTip;
			wchar_t *		fszMessage;
	#else
			void*			fpToolTipItem;
			void*			fhToolTip;
			void*			fszMessage;
	#endif
#else
#endif
		};		

		// ---------------------------------------------------------
		class CDDXValidator_NumberInRange : public IDDXValidator
		{
		public:
			CDDXValidator_NumberInRange(const TXString& title, const TXString& message, Sint32 value, bool bLessThan, bool bEqual);
			CDDXValidator_NumberInRange(const TXString& title, const TXString& message, Sint32 minValue, Sint32 maxValue);

		// IDDXValidator
		public:
			virtual TXString	GetErrorTitle() const;
			virtual TXString	GetErrorMessage() const;
			virtual bool		Validate(const TXString& value) const;

		protected:
			bool				IsNumber(const TXString& value) const;

		private:
			TXString			fTitle;
			TXString			fMessage;
			Sint32				fMinValue;
			Sint32				fMaxValue;
			bool				fbSection;
			bool				fbLessThan;
			bool				fbEqual;
		};

		// ---------------------------------------------------------
		class CDDXValidator_RealInRange : public IDDXValidator
		{
		public:
			CDDXValidator_RealInRange(const TXString& title, const TXString& message, double value, bool bLessThan, bool bEqual, double dEpsilon = 0.00001);
			CDDXValidator_RealInRange(const TXString& title, const TXString& message, double minValue, double maxValue, double dEpsilon = 0.00001);

		// IDDXValidator
		public:
			virtual TXString	GetErrorTitle() const;
			virtual TXString	GetErrorMessage() const;
			virtual bool		Validate(const TXString& value) const;

		protected:
			bool				IsNumber(const TXString& value) const;

		private:
			TXString			fTitle;
			TXString			fMessage;
			double				fEpsilon;
			double				fMinValue;
			double				fMaxValue;
			bool				fbSection;
			bool				fbLessThan;
			bool				fbEqual;
		};
	}
}