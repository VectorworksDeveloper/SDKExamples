//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace ResourcePopup
{
	class CDlgResourcePopupSample : public VWDialog
	{
	public:
							CDlgResourcePopupSample(VectorWorks::Extension::IResourceManagerContentPtr content);
		virtual				~CDlgResourcePopupSample();

	// virtuals
	protected:
		virtual bool		CreateDialogLayout();
		virtual void		OnInitializeContent();
		virtual void		OnDDXInitialize();
		virtual void		OnUpdateUI();

	// dispatch map
	protected:
		DEFINE_EVENT_DISPATH_MAP;

	// DDX
	protected:

	// Inner data
	private:
		VectorWorks::Extension::IResourceManagerContentPtr	fContent;
	};
}

