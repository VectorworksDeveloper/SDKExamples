//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "Filing/IFileIdentifier.h"

namespace VectorWorks
{
	using namespace VectorWorks::Filing;

	// ----------------------------------------------------------------------------------------------------
	struct SColorRecord {
		float			fCyan;
		float			fMagenta;
		float			fYellow;
		float			fKey;
		TXString		fColorName;
		Bool8			fbUserColor;
		
		SColorRecord()
		{
			fCyan = fMagenta = fYellow = fKey = 0;
			bColorIntialized = false;
		}
		
		SColorRecord(const TGSColorV2& colorIn)
		{
			color = colorIn;
			color.GetCMYK(fCyan, fMagenta, fYellow, fKey);
			bColorIntialized = true;
		}
		
		operator TGSColorV2& ()
		{
			if(bColorIntialized)
				color.GetCMYK(fCyan, fMagenta, fYellow, fKey);
			else
				color.SetCMYK(fCyan, fMagenta, fYellow, fKey);
			
			return color;
		}
		
		const TGSColorV2& fColor() const
		{
			return color;
		}
	private:
		TGSColorV2		color;
		bool bColorIntialized;
	};
    
    inline bool operator==(const SColorRecord& lhs, const SColorRecord& rhs)
    {
        if(lhs.fCyan == rhs.fCyan &&
           lhs.fMagenta == rhs.fMagenta &&
           lhs.fYellow == rhs.fYellow &&
           lhs.fKey == rhs.fKey &&
           lhs.fColorName == rhs.fColorName &&
           lhs.fbUserColor == rhs.fbUserColor)
        {
            return true;
        }
        
        return false;
    }

	// ----------------------------------------------------------------------------------------------------
	enum EColorRecordReceiverResult
	{
		eColorRecordReceiverResult_Continue,
		eColorRecordReceiverResult_StopNoError,
		eColorRecordReceiverResult_StopError,
	};

	// ----------------------------------------------------------------------------------------------------
	class IColorRecordReceiver
	{
	public:
		virtual ~IColorRecordReceiver()	{}

		virtual EColorRecordReceiverResult VCOM_CALLTYPE ReceiveColorRecordCount(Uint32 numRecordsToFollow) = 0;
		virtual EColorRecordReceiverResult VCOM_CALLTYPE ReceiveColorRecord(const SColorRecord& inColorRec) = 0;
	};
	
	// ----------------------------------------------------------------------------------------------------
	// {2d13c2d0-7c96-11db-9fe1-0800200c9a66}
	static const VWIID IID_DocumentColorTable = { 0x2d13c2d0, 0x7c96, 0x11db, { 0x9f, 0xe1, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 } };
	
	class DYNAMIC_ATTRIBUTE IDocumentColorTable : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE LoadDocumentColorTableFromDisk(IFileIdentifier *inFileID, IColorRecordReceiver* inpRecReceiver) = 0;

		virtual VCOMError VCOM_CALLTYPE	InsertColor(const SColorRecord& inColorRecord, ColorRef& outColorRef) = 0;			
		virtual VCOMError VCOM_CALLTYPE	GetColorRecord(const ColorRef& inColorRef, SColorRecord& outColorRec) = 0;
		virtual VCOMError VCOM_CALLTYPE	GetNumColorRecords(Uint32& outNumRecords) = 0;
		virtual VCOMError VCOM_CALLTYPE	PurgeUnusedColors() = 0;
		virtual VCOMError VCOM_CALLTYPE ReplaceUserColors( const TGSColorV2 *newColors, const TXString *colorNames, const Sint32 *originalIndices, Uint32 nColors ) = 0;
		virtual VCOMError VCOM_CALLTYPE SetColorName(const ColorRef& inColorRef, const TXString& name) = 0;
	};
}


