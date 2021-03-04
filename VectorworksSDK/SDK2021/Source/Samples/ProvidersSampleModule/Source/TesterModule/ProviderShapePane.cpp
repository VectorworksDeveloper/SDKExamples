#include "StdAfx.h"

#include "ProviderShapePane.h"

using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	// widget constants
	const Sint32	kWidgetID_Widget1					= 1;
	const Sint32	kWidgetID_Widget2					= 2;
	const Sint32	kWidgetID_Widget3					= 3;
	const Sint32	kWidgetID_Widget4					= 4;
}

CProviderShapePane::CProviderShapePane(IVWUnknown* parent)
	: VCOMImpl<IProviderShapePane>( parent )
{
}

CProviderShapePane::~CProviderShapePane()
{
}

void CProviderShapePane::Init(CodeRefID objectID, IExtendedProps* extProps)
{
	IWidgetsEditProvider*	widgetsProvider	= NULL;
	if ( extProps && VCOM_SUCCEEDED( extProps->GetObjComponentTypeWidgets( objectID, kObjectRootComponentTypeID, widgetsProvider ) ) ) {
		TXString localizedName = TXResStr("ExtObjClassName", "settings_oip_button"); 

		widgetsProvider->AddWidget( kWidgetID_Widget1,		"p1" );
		widgetsProvider->AddWidget( kWidgetID_Widget2,		"p2" );
		widgetsProvider->AddWidget( kWidgetID_Widget3,		kWidgetSeparator,		"" );
		widgetsProvider->AddWidget( kWidgetID_Widget4,		"p3" );
		widgetsProvider->AddWidget( kWidgetID_Widget3,		kWidgetButton, localizedName);
	}
}

void CProviderShapePane::Activate(MCObjectHandle hObject, const SSelectionContext& selContext)
{
}

void CProviderShapePane::Deactivate()
{
}

void CProviderShapePane::Update(IWidgetsProvider* widgetProvider)
{
}

bool CProviderShapePane::OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)
{
	return false;
}



