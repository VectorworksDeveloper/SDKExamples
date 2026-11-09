#pragma once


namespace UI
{
	class CSampleDlg3 : public VWDialog
	{
	public:
							CSampleDlg3();
		virtual				~CSampleDlg3();

	// virtuals
	protected:
		virtual bool		CreateDialogLayout();
		virtual void		OnInitializeContent();
		virtual void		OnDDXInitialize();
		virtual void		OnUpdateUI();
		virtual void		OnDefaultButtonEvent();

	// events (dispatch map)
	protected:
		DEFINE_EVENT_DISPATH_MAP;
		//void				OnPopupControl(TControlID controlID, VWDialogEventArgs& eventArgs);

	//user methods
	protected:
		void				InitializeTextPopup();
		void				InitializeImagePopup();
		void				InitializeResourceTextPopup();

	// DDX
	protected:
		short                     fTextPopup;
		SMarkerStyle              fMarkerPopup;
		short                     fPattPopupIndex;
		RGBColor                  fPattPopupForeColor;
		RGBColor                  fPattPopupBackColor;
		short                     fLWPopup;
		InternalIndex             fLSPopup;
		InternalIndex             fLAttrPopupLineStyle;
		short                     fLAttrPopupLineWeight;
		RGBColor                  fColorPopup;
		TXString                  fImagePopup;
		TXString                  fResourceTextPopup;

	// Inner data
	private:

	};

}

