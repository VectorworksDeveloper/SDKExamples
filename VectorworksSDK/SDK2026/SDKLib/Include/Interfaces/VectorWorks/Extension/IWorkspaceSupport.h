//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		// {D459127C-F947-489D-9851-04A1C918E913}
		static const VWIID IID_WorkspaceSupport =
		{ 0xd459127c, 0xf947, 0x489d, { 0x98, 0x51, 0x4, 0xa1, 0xc9, 0x18, 0xe9, 0x13 } };

		// ---------------------------------------------------------------------------------------------------
		enum EWorkspaceEditorPane
		{
			eWorkspaceMenusPane = 0,
			eWorkspaceToolsPane,
			eWorkspaceKeysPane
		};
		
		struct TWorkspaceSupportOptions
		{
			EWorkspaceEditorPane defaultPane;
			TXString workspaceNameOrPath;
			TXString selectedItemIdentifier;
			
			TWorkspaceSupportOptions() : defaultPane(eWorkspaceMenusPane) {}
		};

		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWorkspaceSupport : public IVWSingletonUnknown
		{
		public:
			virtual void VCOM_CALLTYPE ShowWorkspacesDialog() = 0;
			virtual void VCOM_CALLTYPE ShowEditorWithOptions( const TWorkspaceSupportOptions & options ) = 0;
			virtual Sint32 VCOM_CALLTYPE ShowEditorForWorkspace(TXString & workspaceNameOrPath) = 0;
			virtual Sint32 VCOM_CALLTYPE CreateAndEditWorkspace(TXString & newWorkspacePath) = 0;
			virtual Sint32 VCOM_CALLTYPE ChangeToolShortcut(const TXString & name, TXString & path, const ViewPt & mousePos) = 0;
			virtual Sint32 VCOM_CALLTYPE ChangeMenuItemShortcut(Sint16 cmdID, const TXString & menuChunkName, TXString& path, const ViewPt & mousePos) = 0;
			virtual void VCOM_CALLTYPE ClearAvailableItems() = 0; // force to reload available items when needed
			virtual TXString VCOM_CALLTYPE GetPathForSavingWorkspace(const TXString & workspacePath) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IWorkspaceSupport>		IWorkspaceSupportPtr;
	}
}
