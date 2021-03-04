//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace ResourcePopup
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CToolResourcePopupSimple_EventSink : public VWTool_EventSink
	{
	public:
						CToolResourcePopupSimple_EventSink(IVWUnknown* parent);
		virtual			~CToolResourcePopupSimple_EventSink();

	public:
		virtual bool	DoSetUp(bool bRestore, const IToolModeBarInitProvider* inModeBarInitProvider);
		virtual void	DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID);
		virtual void	HandleComplete();

	protected:
		void	OnPreferences();
		void	OnSampleDialog();
		void	OnContent();

		enum class EShape
		{
			  Line
			, Circle
			, Box
		};

		EShape		GetShape(const TXString& str);
		TXString	GetShape(const EShape& shape);

	private:
		enum EModeBarGroupSimple
		{
			  Content
			, Configuration
			, SampleDlgButton
			, PrefsButton
		};

		EShape		fBarState_Shape;

		VectorWorks::Extension::IResourceManagerContentPtr		fContent;
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtToolResourcePopupSimple : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
						CExtToolResourcePopupSimple(CallBackPtr cbp);
		virtual			~CExtToolResourcePopupSimple();

	};
}
