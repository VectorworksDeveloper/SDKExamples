#include "StdAfx.h"

#include "SampleDlg3.h"

// dialog control IDs
#define		kOK                    1
#define		kCancel                2
#define		kTextPopupText         4
#define		kTextPopup             5
#define		kTextEnhPopupText      6
#define		kTextEnhPopup          7
#define		kMarkerPopupText       8
#define		kMarkerPopup           9
#define		kPattPopupText         10
#define		kPattPopup             11
#define		kLWPopupText           12
#define		kLWPopup               13
#define		kLSPopupText           14
#define		kLSPopup               15
#define		kLAttrPopupText        16
#define		kLAttrPopup            17
#define		kColorPopupText        18
#define		kColorPopup            19
#define		kImagePopupText        20
#define		kImagePopup            21
#define		kResourceTextPopupText 22
#define		kResourceTextPopup     23


using namespace UI;

EVENT_DISPATCH_MAP_BEGIN( CSampleDlg3 );
//ADD_DISPATCH_EVENT( kTextPopup, OnPopupControl );
EVENT_DISPATCH_MAP_END;

CSampleDlg3::CSampleDlg3()
{
    this->SetSavedSettingsTag( "sampleDlg", "CSampleDlg3" ); 

	fTextPopup					= 1;
	fPattPopupIndex				= 1;
	fLWPopup					= 1;
	fLSPopup					= 1;
	fLAttrPopupLineStyle		= 1;
	fLAttrPopupLineWeight		= 1;
	fPattPopupForeColor.red		= 0xFFFF;
	fPattPopupForeColor.green	= 0xFFFF;
	fPattPopupForeColor.blue	= 0xFFFF;
	fPattPopupBackColor.red		= 0x0000;
	fPattPopupBackColor.green	= 0x0000;
	fPattPopupBackColor.blue	= 0x0000;
	fColorPopup.red				= 0xFFFF;
	fColorPopup.green			= 0xFFFF;
	fColorPopup.blue			= 0xFFFF;

	CBBoolean		visibility;
	::GS_GetDefaultBeginningMarker( gCBP, fMarkerPopup, visibility );
}

CSampleDlg3::~CSampleDlg3()
{
}

bool CSampleDlg3::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "VWUI Dialogs Sample/DialogLayout/SampleDlg3.vs" );
}

void CSampleDlg3::InitializeTextPopup()
{
	VWPullDownMenuCtrl*	pTextPopup = this->GetPullDownMenuCtrlByID(kTextPopup);
	for (size_t i = 0; i < 5; i++)
	{
		pTextPopup->AddItem(TXResStr("SampleDlg3_extra", "item" + TXString::ToStringInt(i + 1)));
	}
}

void CSampleDlg3::InitializeImagePopup()
{
	VectorWorks::Extension::IResourceManagerContentPtr fResourceContent(VectorWorks::Extension::IID_ResourceManagerContent);
	//(no need to query if IID passed in the constructor)

	if (fResourceContent != nullptr)
	{
		auto filter = [this](MCObjectHandle hDef)
		{
			const TXString defName = VWSymbolDefObj(hDef).GetObjectName();

			return defName.GetLength() > 0
				&& !defName.EqualNoCase("__NNA_TEMP_SEATING_SYMDEF")
				&& defName.Find("__NNA_TEMP_SEAT_SYMDEF") == -1; // not found
		};

		fResourceContent->InitByTDType(kSymDefNode);
		fResourceContent->AddContent(kDefaultSeatingLayoutFolder);
		fResourceContent->SetFilter(filter);

		//Clear out selection so it will show first available.
		fResourceContent->SetSelectedItemText("");

		//other option:
		//select first available resource
		/*SSearchProperties searchProp;
		searchProp.fOnlyCurrentDoc = false;
		searchProp.fSearchOnline = false;
		searchProp.fSkipCurrentDoc = true;
		TXString symbolName;
		fResourceContent->SelectFirstAvailableResource(symbolName, searchProp);*/
	}

	gSDK->PullDownResourceLayoutInit(this->GetDialogID(), kImagePopup, fResourceContent);

	//see InitializeResourceTextPopup() for other ways to set up the content
}

void CSampleDlg3::InitializeResourceTextPopup()
{
	VectorWorks::Extension::IResourceManagerContentPtr fResourceContent;
	if (fResourceContent == nullptr)
	{
		fResourceContent.Query(VectorWorks::Extension::IID_ResourceManagerContent);
	}

	if (fResourceContent != nullptr)
	{
		fResourceContent->InitByTDType(kSymDefNode);
		fResourceContent->AddContent(kDefaultPlantsFolder);

		//Clear out selection so it will show first available.
		fResourceContent->SetSelectedItemText("");
	}
	
	//instead of gSDK->PullDownResourceLayoutInit(), you can also use this inside a class that derives from VWDialog:
	if (VWResourceTextPopupCtrl* pResourceTextPopupCtrl = this->GetResourceTextPopupCtrlByID(kResourceTextPopup))
		pResourceTextPopupCtrl->PullDownResourceLayoutInit(fResourceContent);

	//see InitializeImagePopup() for other ways to set up the content
}

void CSampleDlg3::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	// Fill up your dialog controls here
	InitializeTextPopup();
	InitializeImagePopup();
	InitializeResourceTextPopup();
}

void CSampleDlg3::OnDDXInitialize()
{
	this->AddDDX_PulldownMenu( kTextPopup, & fTextPopup );
	this->AddDDX_MarkerPopup( kMarkerPopup, & fMarkerPopup );
	this->AddDDX_PatternPopup( kPattPopup, & fPattPopupIndex, & fPattPopupForeColor, & fPattPopupBackColor );
	this->AddDDX_LineWeightPopup( kLWPopup, & fLWPopup );
	this->AddDDX_LineStylePopup( kLSPopup, & fLSPopup );
	this->AddDDX_LineAttribsPopup( kLAttrPopup, & fLAttrPopupLineStyle, & fLAttrPopupLineWeight );
	this->AddDDX_ColorPopup( kColorPopup, & fColorPopup );
	this->AddDDX_ImagePopup( kImagePopup, & fImagePopup);
	this->AddDDX_ResourceTextPopup( kResourceTextPopup, & fResourceTextPopup);
}

void CSampleDlg3::OnDefaultButtonEvent()
{
	VWDialog::OnDefaultButtonEvent();

	TXString resultsStr =	TXResStr("SampleDlg3_extra", "SelectedItems") +
							TXString(TXResStr("SampleDlg3_extra", "TextPopup"))
								.Replace("%d", TXResStr("SampleDlg3_extra", "item" + TXString::ToStringInt(fTextPopup + 1))) +
							TXString(TXResStr("SampleDlg3_extra", "MarkerPopup"))
								.Replace("%d", TXString::ToStringInt(fMarkerPopup.style)) +
							TXString(TXResStr("SampleDlg3_extra", "PatternPopup"))
								.Replace("%d", TXString::ToStringInt(fPattPopupIndex)) +
							TXString(TXResStr("SampleDlg3_extra", "ForegroundColor"))
								.Replace("%1", TXString::ToStringInt(fPattPopupForeColor.red))
								.Replace("%2", TXString::ToStringInt(fPattPopupForeColor.red))
								.Replace("%3", TXString::ToStringInt(fPattPopupForeColor.red)) +
							TXString(TXResStr("SampleDlg3_extra", "BackgroundColor"))
								.Replace("%1", TXString::ToStringInt(fPattPopupBackColor.red))
								.Replace("%2", TXString::ToStringInt(fPattPopupBackColor.red))
								.Replace("%3", TXString::ToStringInt(fPattPopupBackColor.red)) +
							TXString(TXResStr("SampleDlg3_extra", "LineWeightPopup"))
								.Replace("%d", TXString::ToStringInt(fLWPopup)) +
							TXString(TXResStr("SampleDlg3_extra", "LineStylePopup"))
								.Replace("%d", TXString::ToStringInt(fLSPopup)) +
							TXString(TXResStr("SampleDlg3_extra", "LineAttributesPopup"))
								.Replace("%1", TXString::ToStringInt(fLAttrPopupLineStyle))
								.Replace("%2", TXString::ToStringInt(fLAttrPopupLineWeight)) +
							TXString(TXResStr("SampleDlg3_extra", "ColorPopup"))
								.Replace("%1", TXString::ToStringInt(fColorPopup.red))
								.Replace("%2", TXString::ToStringInt(fColorPopup.red))
								.Replace("%3", TXString::ToStringInt(fColorPopup.red)) +
							TXString(TXResStr("SampleDlg3_extra", "PatternPopup"))
								.Replace("%d", fImagePopup) +
							TXString(TXResStr("SampleDlg3_extra", "PatternPopup"))
								.Replace("%d", fResourceTextPopup);
	gSDK->AlertInform(resultsStr);

	//Regarding Resource Text popup, you can also do:
	//	VWResourceTextPopupCtrl* pResourceTextPopup = this->GetResourceTextPopupCtrlByID(kResourceTextPopup);
	//and use the following methods:
	// - void			PullDownResourceLayoutSetSelectedResourceName(const TXString& name);
	// - TXString		PullDownResourceLayoutGetSelectedResourceName() const;
	//or use SDK functions:
	// - gSDK->PullDownResourceLayoutSetSelectedResourceName(fpParentDlg->GetDialogID(), kResourceTextPopup, name);
	// - gSDK->PullDownResourceLayoutGetSelectedResourceName(fpParentDlg->GetDialogID(), fControlID);
}

void CSampleDlg3::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}


