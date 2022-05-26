//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum class EPDFHyperlinkType
		{
			OpenWebPage,
			ActivateSheetLayer,
			ActivateSheetAndZoomArea,
		};

		// ----------------------------------------------------------------------------------------------------
		struct SPDFTargetKeyData
		{
			InternalIndex	fInternalIndex = 0;
			Sint32			fAdditionalKey = 0;

			bool operator<( const SPDFTargetKeyData& other ) const
			{
				// Provide comparison for usage in std::map
				bool result = fInternalIndex < other.fInternalIndex;

				if ( fInternalIndex == other.fInternalIndex )
				{
					result = fAdditionalKey < other.fAdditionalKey;
				}

				return result;
			}
		};

		// ----------------------------------------------------------------------------------------------------
		struct SPDFLinkData
		{
			EPDFHyperlinkType	fLinkType		= EPDFHyperlinkType::ActivateSheetLayer;

			// The target string.
			// if fLinkType == EPDFHyperlinkType::ActivateSheetLayer		-> fTargetStr is Sheet Name
			// if fLinkType == EPDFHyperlinkType::OpenWebPage				-> fTargetStr is webpage
			// if fLinkType == EPDFHyperlinkType::ActivateSheetAndZoomArea	-> fTargetStr is empty and fTargetKeyData is the unique SPDFTargetKeyData of the target object
			TXString			fTargetStr;
			SPDFTargetKeyData	fTargetKeyData;

			// The bounds of the hyperlink object that will be clickable.
			WorldRect			fSourceRect;
		};
		typedef std::vector<SPDFLinkData>	TPDFLinkDataArr;

		// ----------------------------------------------------------------------------------------------------
		struct SPDFTargetData
		{
			WorldRect			fTargetBounds;

			// The name of the target. If one object defines multiple targets, use the object internal index with unique SPDFTargetKeyData::fAdditionalKey,
			// in order to avoid collisions for the objects' targets.
			SPDFTargetKeyData	fTargetKeyData;
		};
		typedef std::vector<SPDFTargetData>	TPDFTargetDataArr;

		// ----------------------------------------------------------------------------------------------------
		// {FF1E5136-7E5E-43AF-B9AD-99B756BA0EFC}
		static const TSinkIID IID_ProviderPDFHyperlink = { 0xff1e5136, 0x7e5e, 0x43af, { 0xb9, 0xad, 0x99, 0xb7, 0x56, 0xba, 0xe, 0xfc } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderPDFHyperlink : public IEventSink
		{
			public:
				// Used to return the PDF hyperlink action
				virtual bool VCOM_CALLTYPE GetHyperlinkAction(MCObjectHandle hObject, TPDFLinkDataArr& outPDFLinkDataArr) = 0;

				// Used to return different bounds than the object bounds for PDF link target.
				virtual bool VCOM_CALLTYPE GetBoundsAsPDFTarget(MCObjectHandle hObject, TPDFTargetDataArr& outPDFTargetDataArr) = 0;
		};
	}
}
