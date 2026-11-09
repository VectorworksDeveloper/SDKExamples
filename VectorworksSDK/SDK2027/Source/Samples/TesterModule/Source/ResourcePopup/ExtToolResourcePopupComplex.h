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
	class CToolResourcePopupComplex_EventSink : public VWTool_EventSink
	{
	public:
							CToolResourcePopupComplex_EventSink(IVWUnknown* parent);
		virtual				~CToolResourcePopupComplex_EventSink();

	public:
			virtual bool	DoSetUp(bool bRestore, const IToolModeBarInitProvider* inModeBarInitProvider);
			virtual void	DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID);
			virtual void	GetCursorSpecifier(TXString& cursorSpecifier);
			virtual void	HandleComplete();

	protected:
		void				OnPreferences();
		void				OnContent();

	private:
		enum EModeBarGroupComplex
		{
			  InsertMode
			, Content
			, PrefsButton
		};

		enum class EToolInsertMode
		{
			  Point
			, Pickup
		};

		EToolInsertMode	fBarState_Insert;
		VectorWorks::Extension::IResourceManagerContentPtr fContent;
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtToolResourcePopupComplex : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
						CExtToolResourcePopupComplex(CallBackPtr cbp);
		virtual			~CExtToolResourcePopupComplex();

	};
}
