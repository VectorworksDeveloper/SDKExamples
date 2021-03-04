//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtObjResourcePopup_ShapePane.h"

using namespace ResourcePopup;

// --------------------------------------------------------------------------------------------------------
CExtObjResourcePopup_ShapePane::CExtObjResourcePopup_ShapePane(IVWUnknown* parent)
	: VCOMImpl<IProviderShapePane>( parent )
{
}

CExtObjResourcePopup_ShapePane::~CExtObjResourcePopup_ShapePane()
{
}

void CExtObjResourcePopup_ShapePane::Init(CodeRefID objectID, IExtendedProps* extProps)
{
	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( extProps, objectID );

	widgetProvider.AddWidget( "shape",		"shape" );
	widgetProvider.AddWidget( "text",		"text" );
	widgetProvider.AddWidget( "size",		"size" );
	widgetProvider.AddWidget( "btnCopyFromResource", kWidgetButton, TXResStr("ExtObjResourcePopup", "btnCopyFromResource") );
	widgetProvider.AddWidget( "btnSaveAsResource", kWidgetButton, TXResStr("ExtObjResourcePopup", "btnSaveAsResource") );

}

void CExtObjResourcePopup_ShapePane::Activate(MCObjectHandle hObject, const SSelectionContext& selContext)
{
	fhObject	= hObject;
	fSelContext	= selContext;
}

void CExtObjResourcePopup_ShapePane::Deactivate()
{
	fhObject	= nullptr;
}

void CExtObjResourcePopup_ShapePane::Update(IWidgetsProvider* widgetProvider)
{
	bool	isTool	= ! VWParametricObj::IsParametricObject( fhObject );

	widgetProvider->GetWidgetByIDSafe( "btnCopyFromResource" ).fWidgedVisible	= ! isTool;
	widgetProvider->GetWidgetByIDSafe( "btnSaveAsResource" ).fWidgedVisible		= ! isTool;
}

bool CExtObjResourcePopup_ShapePane::OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)
{
	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( fhObject );
	if ( data.fLastSelObj && data.fWidgetID == widgetProvider->GetWidgetByIDSafe( "btnCopyFromResource" ).fWidgetID )
	{
		if ( fContent == nullptr )
		{
			fContent.Query( VectorWorks::Extension::IID_ResourceManagerContent );
			fContent->InitByUnivName( "ResourcePopupObject" );
		}

		if ( data.fWidgetAccess->ShowPullDownResourcePopup( data.fViewWidget, fContent ) )
		{
			MCObjectHandle hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::eImportResourceConflictResult_Replace );
			if ( hSymbol && VWParametricObj::IsParametricObject( gSDK->FirstMemberObj(hSymbol), "ResourcePopupObject" ) )
			{
				CGenericParamProvider	paramsSrc( gSDK->FirstMemberObj(hSymbol), "ResourcePopupObject" );
				CGenericParamProvider	paramsDest( fhObject, "ResourcePopupObject" );

				this->CopyObject( paramsDest, paramsSrc );

				VWObjectIterator it( gSDK->FirstSelectedObject() );
				while ( *it )
				{
					if ( VWParametricObj::IsParametricObject( *it, "ResourcePopupObject" ) )
					{
						if ( *it != fhObject )
						{
							// this was processed outside as it shoudl work for a record, and they are not processed via selection
							CGenericParamProvider	paramsDest( fhObject, "ResourcePopupObject" );
							this->CopyObject( paramsDest, paramsSrc );
						}

						gSDK->ResetObject( *it );
					}

					it.MoveNextSelected();
				}
			}
		}
	}
	else if ( data.fLastSelObj && data.fWidgetID == widgetProvider->GetWidgetByIDSafe( "btnSaveAsResource" ).fWidgetID )
	{
		CStandardEditTextBoxDlg	dlgSymbolName(	TXResStr("ExtObjResourcePopup","SaveDlg_Title"),
												TXResStr("ExtObjResourcePopup","SaveDlg_Label"),
												TXResStr("ExtObjResourcePopup","SaveDlg_DefaultName"),
												TXResStr("ExtObjResourcePopup","SaveDlg_OkButton"),
												TXResStr("ExtObjResourcePopup","SaveDlg_CancelButton"));
		dlgSymbolName.SetAllowEmptyResult( false );
		if ( dlgSymbolName.RunDialogLayout( "" ) == kDialogButton_Ok )
		{
			TXString	symbolName	= dlgSymbolName.GetValue();
			VWObject::MakeUniqueObjectName( symbolName );

			MCObjectHandle hCopy = gSDK->DuplicateObject( fhObject );

            MCObjectHandle symDef = gSDK->CreateSymbolDefinition( symbolName );
            gSDK->AddObjectToContainer( hCopy, symDef );

			gSDK->ResetObject( symDef );	// reset symbol, very important
			NotifyAnyStuff notification(kNotifySymChange);
			gSDK->Kludge(kKludgeNotifyAny, &notification, nil);

			gSDK->SetObjectVariable( symDef, ovSymbolInsertAsGroup, TVariableBlock( (Boolean) true ) );
		}
	}

	return true;
}


void CExtObjResourcePopup_ShapePane::CopyObject(CGenericParamProvider& dest, CGenericParamProvider& src)
{
	dest.SetParamString(	"shape"	, src.GetParamString(	"shape"	) );
	dest.SetParamString(	"text"	, src.GetParamString(	"text"	) );
	dest.SetParamReal(		"size"	, src.GetParamReal(		"size"	) );
}
