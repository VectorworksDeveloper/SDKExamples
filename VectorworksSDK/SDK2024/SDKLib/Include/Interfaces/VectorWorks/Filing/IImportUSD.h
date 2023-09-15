//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		struct SImportUSDOptions
		{
			bool	fbCreateTextures			= true;
			bool	fbCreateTexturesForColors	= false;
			bool	fbImportAsSymbol			= false;
			bool	fbRecaleUnitsPerMeter		= true;
			double	fUnitsPerMeter				= 1;
			bool	fbOffsetImportedModel		= true;
			double	fOffsetX					= 0;
			double	fOffsetY					= 0;
			double	fOffsetZ					= 0;
			bool	fbRedefineUpAxis			= true;
			bool	fbUpAxisY					= true;
		};

		// ----------------------------------------------------------------------------------------------------
		// {F16BA47F-F2FE-4715-890B-DE99822BED04}
		static const VWIID IID_IImportUSD = { 0xf16ba47f, 0xf2fe, 0x4715, { 0x89, 0xb, 0xde, 0x99, 0x82, 0x2b, 0xed, 0x4 } };

		class DYNAMIC_ATTRIBUTE IImportUSD : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE Import( IFileIdentifierPtr fileID = nullptr, bool bShowUI = true ) = 0;
			virtual VCOMError VCOM_CALLTYPE Import( IFileIdentifierPtr fileID, const SImportUSDOptions& options ) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportUSD>		IImportUSDPtr;
	}
}