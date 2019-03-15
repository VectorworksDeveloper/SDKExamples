//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// This file contains the necessary VCOM interfaces required for reading and writing workspace files for VectorWorks version 13.

#pragma once

namespace VectorWorks
{
	namespace Workspaces
	{
		// ---------------------------------------------------------------------------------------------------
		// {E3054933-8EE3-4EF1-80B1-11A4FA8E9D4F}
		const VWIID IID_WorkspaceEdit = { 0xe3054933, 0x8ee3, 0x4ef1, {0x80, 0xb1, 0x11, 0xa4, 0xfa, 0x8e, 0x9d, 0x4f}};

		class DYNAMIC_ATTRIBUTE IWorkspaceEdit : public IVWSingletonUnknown
		{
		public:
			virtual void		EditStart(const TXString& companyName) = 0;
			virtual bool		EditEnd(bool restart) = 0;

			// use these between EditStart - EditEnd calls
			virtual void		AddMenu(const TXString& menuPath) = 0;
			virtual void		AddTool(const TXString& toolName, const short& toolType) = 0;
			virtual void		AddTool(const TXString& toolName, const TXString& underToolName, const short& toolType) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IWorkspaceEdit>		IWorkspaceEditPtr;
	}
}
