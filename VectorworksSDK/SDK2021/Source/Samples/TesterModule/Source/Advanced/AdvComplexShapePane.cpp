#include "StdAfx.h"

#include "AdvComplexShapePane.h"

using namespace Advanced;

namespace Advanced
{
	// --------------------------------------------------------------------------------------------------------
	const Sint32	kWidgetID_Separator1				= 1;
	const Sint32	kWidgetID_Edit						= 2;
	const Sint32	kWidgetID_ParamLayer				= 3;
	const Sint32	kWidgetID_Separator2				= 4;
	const Sint32	kWidgetID_Param1					= 5;
	const Sint32	kWidgetID_Param2					= 6;
}

// --------------------------------------------------------------------------------------------------------
CAdvComplexShapePane::CAdvComplexShapePane(IVWUnknown* parent)
	: VCOMImpl<IProviderShapePane>( parent )
{
}

CAdvComplexShapePane::~CAdvComplexShapePane()
{
}

void CAdvComplexShapePane::Init(CodeRefID objectID, IExtendedProps* extProps)
{
	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( extProps, objectID );

	widgetProvider.AddWidget( kWidgetID_Separator1,	kWidgetSeparator, TXString(TXResource("CExtObjAdvComplex", "oip_sep1" )) );
	widgetProvider.AddWidget( kWidgetID_Edit,		kWidgetButton,  TXString(TXResource("CExtObjAdvComplex", "oip_button_settings")) ).SetIndent( 1 );

	widgetProvider.AddWidget( kWidgetID_ParamLayer,	"layer" ).SetIndent( 1 );

	widgetProvider.AddWidget( kWidgetID_Separator1,	 kWidgetSeparator,  TXString(TXResource("CExtObjAdvComplex", "oip_sep2")) );
	widgetProvider.AddWidget( kWidgetID_Param1,		"p1" ).SetIndent( 1 );
	widgetProvider.AddWidget( kWidgetID_Param2,		"p2" ).SetIndent( 1 );
}

void CAdvComplexShapePane::Activate(MCObjectHandle hObject, const SSelectionContext& selContext)
{
	MCObjectHandle	hProxyParent	= gSDK->GetProxyParent( hObject );

	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( hProxyParent ? hProxyParent : hObject );

	widgetProvider.GetWidget( kWidgetID_ParamLayer ).SetEnabled( hProxyParent == NULL );
}

void CAdvComplexShapePane::Deactivate()
{
}

void CAdvComplexShapePane::Update(IWidgetsProvider* widgetProvider)
{
}



