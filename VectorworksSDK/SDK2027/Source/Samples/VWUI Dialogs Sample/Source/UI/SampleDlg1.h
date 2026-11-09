#pragma once
#include "MyControl.h"


namespace UI
{
	class CMyDialog : public VWComplexDialog
	{
	public:
							CMyDialog();
		virtual				~CMyDialog();

	// virtuals
	protected:
		virtual bool		CreateDialogLayout();
		virtual void		OnInitializeContent();
		virtual void		OnDDXInitialize();

	// events
	protected:

	// dispatch map
	protected:
		DEFINE_EVENT_DISPATH_MAP;
		void				EditIntegerChanged(TControlID controlID, VWDialogEventArgs& eventArgs);

	protected:		
		class CDataItem
		{
		public:
						CDataItem(const TXString& value, bool visible = true, bool createChild = true);
			virtual		~CDataItem();
			
			bool		IsVisible();
			size_t		GetChildCount();
			CDataItem*	GetChildAt(size_t index);

			int			OnPaint(VWCustomCtrl& parent, VWCustomCtrlDC& dc, const ViewPt& pt);
			void		OnMouseClick(VWCustomCtrl& parent, const SCustomCtrlMouseEvent& event, bool isDoubleClick);

		public:
			bool		fVisible;
			TXString	fName;

			std::vector<CDataItem>	farrChildItems;
		};

		typedef std::vector<CDataItem>	 TDataItemsArray;

	// DDX
	protected:
		VWStaticTextCtrl						fStaticTextCtrl;
		VWEditIntegerCtrl						fEditIntegerCtrl;
		VWListCustomCtrl<TDataItemsArray>		fMyCustomCtrl1;

		Sint32				fIntControlValue;

	// Inner data
	private:

		TDataItemsArray		farrItems;
	};
}
