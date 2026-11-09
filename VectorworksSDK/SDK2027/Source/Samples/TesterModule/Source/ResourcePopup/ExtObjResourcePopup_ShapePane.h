//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace ResourcePopup
{
	using namespace VectorWorks::Extension;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CExtObjResourcePopup_ShapePane : public VCOMImpl<IProviderShapePane>
	{
	public:
						CExtObjResourcePopup_ShapePane(IVWUnknown* parent);
		virtual			~CExtObjResourcePopup_ShapePane();
	
	// IProviderShapePane
	public:
		virtual void VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
		virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk);

	protected:
		void	CopyObject(CGenericParamProvider& dest, CGenericParamProvider& src);

	private:
		MCObjectHandle		fhObject;
		SSelectionContext	fSelContext;

		VectorWorks::Extension::IResourceManagerContentPtr		fContent;
	};
}

