//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Scripting
	{
		// ---------------------------------------------------------------------------------------------------
		enum ELanguage
		{
			eLanguage_TextFile,
			eLanguage_VectorScript,
			eLanguage_Python,
		};

		// ---------------------------------------------------------------------------------------------------
		struct TScriptEditorData
		{	
			ELanguage	fLanguage;
			TXString	fScript;
			bool		fIsEditable;
			TXString	fVectorScriptSource;
			Sint16		fParameterCount;
			Sint32		fLineToSelect;
			Sint16		fCaretPosition;
			bool		fShouldLimitTo32KChars;
			bool		fPythonExclusive;

				TScriptEditorData()
				{
					fLanguage = eLanguage_Python;
					fIsEditable = true;
					fParameterCount = 0;
					fLineToSelect = 0;
					fCaretPosition = 0;
					fShouldLimitTo32KChars = false;
					fPythonExclusive = false;
				}
		};
		
		// ---------------------------------------------------------------------------------------------------
		// {8F1B2EFB-3326-417B-8435-E2DC058CAB19}
		static const VWIID IID_ScritpEditor = { 0x8F1B2EFB, 0x3326, 0x417B, { 0x84, 0x35, 0xE2, 0xDC, 0x05, 0x8C, 0xAB, 0x19 }};
		
		class IScriptEditor : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE Display( TScriptEditorData& editorData, ViewRect& windowBounds, bool& dismissedWithOK ) = 0;
			virtual VCOMError VCOM_CALLTYPE GetBuiltinPaths( TXStringArray& outBuiltInPathsArray ) = 0;
			virtual VCOMError VCOM_CALLTYPE GetUserPaths( TXStringArray& outUserPathsArray ) = 0;
			virtual VCOMError VCOM_CALLTYPE SetUserPaths( const TXStringArray& inUserPathsArray ) = 0;
			virtual VCOMError VCOM_CALLTYPE GetHomePath( TXString& outHomePath ) = 0;
		};

		typedef VCOMPtr<IScriptEditor>	IScriptEditorPtr;

	}
}