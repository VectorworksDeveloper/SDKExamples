//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFolderIdentifier.h"
#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// {AE4F54DD-C8E7-47a2-9F7B-BAF541D72950}
		static const VWIID IID_PathResolver = { 0xae4f54dd, 0xc8e7, 0x47a2, { 0x9f, 0x7b, 0xba, 0xf5, 0x41, 0xd7, 0x29, 0x50 } };

		class DYNAMIC_ATTRIBUTE IPathResolver : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Resolve(IFileIdentifier* pInOutFileIdentifier) = 0;
			virtual VCOMError VCOM_CALLTYPE	Resolve(IFolderIdentifier* pInOutFolderIdentifier) = 0;

			virtual VCOMError VCOM_CALLTYPE	CreateLink(IFolderIdentifier* pFolder, IFileIdentifier* pLinkToFileID, const TXString& linkName) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateLink(IFolderIdentifier* pFolder, IFolderIdentifier* pLinkToFolderID, const TXString& linkName) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPathResolver>		IPathResolverPtr;
	}
}
