#pragma once

#include "MyControl.h"
//#include "MyOverrideCtrl.h"

namespace UI
{
	enum EThumbnailType
	{
		kThumbnailType_Hatches,
		kThumbnailType_WallHatches,
		kThumbnailType_Gradients,
		kThumbnailType_Images,
		kThumbnailType_LineStyle,
	};

	class CSampleDlg4 : public VWDialog
	{
	public:
							CSampleDlg4();
		virtual				~CSampleDlg4();

	// virtuals
	protected:
		virtual bool		CreateDialogLayout();
		virtual void		OnInitializeContent();
		virtual void		OnDDXInitialize();
		virtual void		OnUpdateUI();

	// events
	protected:

	// dispatch map
	protected:
		DEFINE_EVENT_DISPATH_MAP;
		void				OnButtonCtrl(long controlID, VWDialogEventArgs& eventArgs);
		void				OnColorButton(long controlID, VWDialogEventArgs& eventArgs);
		void				OnColorPopup(long controlID, VWDialogEventArgs& eventArgs);
		void				OnLefButton(long controlID, VWDialogEventArgs& eventArgs);

		void				OnHatchesRadio(long controlID, VWDialogEventArgs& eventArgs);
		void				OnWallHatchesRadio(long controlID, VWDialogEventArgs& eventArgs);
		void				OnGradientsRadio(long controlID, VWDialogEventArgs& eventArgs);
		void				OnImagesRadio(long controlID, VWDialogEventArgs& eventArgs);
		void				OnGetThumbnailButton (long controlID, VWDialogEventArgs& eventArgs);
		void				OnSetThumbnailButton(long controlID, VWDialogEventArgs& eventArgs);

	private:
		void				BuildResourceImages(bool bFree);
		void				FillThumbnail(EThumbnailType type);

	// DDX
	protected:
		bool                      fUnnamed8;
		CMyControl                fMyCustomCtrl1;
		CMyControl                fMyCustomCtrl2;
		RGBColor                  fColorButton;
		RGBColor                  fColorPopup;
//		CMyOverrideCtrl			  fMyOverrideCtrl;

	private:
		EThumbnailType			fActiveType;
		InternalIndex			fThumbPatternIndex;

		// default resouce lists
		VWResourceList			fResourcesHatch;
		VWResourceList			fResourcesWallHatch;
		VWResourceList			fResourcesGradient;
		VWResourceList			fResourcesImage;
		VWResourceList			fResourcesLineStyle;

	// Inner data
	private:

	};
}
