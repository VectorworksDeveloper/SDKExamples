#pragma once

namespace ResourcePopup
{
	class CDlgResourcePopupComplex : public VWDialog
	{
	public:
						CDlgResourcePopupComplex(const TXString& selItem);
		virtual			~CDlgResourcePopupComplex();

		TXString		GetSelectedItem();

	// virtuals
	protected:
		virtual bool		CreateDialogLayout();
		virtual void		OnInitializeContent();
		virtual void		OnDDXInitialize();
		virtual void		OnUpdateUI();

	// events
	protected:
		virtual void		OnDefaultButtonEvent();

	// dispatch map
	protected:
		DEFINE_EVENT_DISPATH_MAP;
		void	OnPlantImagePopup(Sint32 controlID, VWDialogEventArgs &eventArgs);

	// DDX
	protected:

	private:
		void	UpdateSymbol();

	// Inner data
	private:
		VectorWorks::Extension::IResourceManagerContentPtr fContent;

		TXString	fSelItem;
	};
}
