#include "StdHeaders.h"

#include <iomanip>

const UuidStorage       kEmptyUuidStorage; // An empty uuid storage
const UuidStorageList   kEmptyUuidStorageList;
const UuidStorageSet    kEmptyUuidStorageSet;

UuidStorage::UuidStorage()
{
    Reset();
}

UuidStorage::UuidStorage(const TXString& s)
{
    size_t i=0;
    bool high = true;

    Reset();
    for (size_t j=0; j < s.GetLength() && i<sizeof(fData); ++j)
    {
        TXChar c = s.GetAt(j);
        if (c == '{' ||
			c == '}' ||
			c == '-')
            continue;
        if (c >= '0' && c <= '9')
            fData[i] |= c - '0';
        else if (c >= 'a' && c <= 'f')
            fData[i] |= c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            fData[i] |= c - 'A' + 10;
        //else error, char skipped, value stays 0

        if (high)
            fData[i] <<= 4;
        else
            ++i;
        high = !high;
    }
}

bool UuidStorage::IsEmpty() const
{
    bool result = false;

    if (*this == kEmptyUuidStorage)
        result = true;
    return result;
}

void UuidStorage::Reset()
{
    memset(fData, 0, sizeof(fData));
}

bool UuidStorage::operator<(const UuidStorage& id) const
{
    for(Sint32 i=0; i<16; i++) {
        if ( fData[i] < id.fData[i] )
            return true;
        else if ( fData[i] > id.fData[i] )
            return false;
    }
    return false;
}

bool UuidStorage::operator==(const UuidStorage& id) const
{
    for(Sint32 i=0; i<16; i++) {
        if ( fData[i] != id.fData[i] )
            return false;
    }
    return true;
}

TXString UuidStorage::ToString() const
{
    std::ostringstream s;
    s << std::hex << std::setfill('0');
    for (auto i=0; i < sizeof(fData); ++i)
    {
        switch (i)
        {
            case 4:
            case 6:
            case 8:
            case 10: s << "-"; break;
        }
        s << std::setw(2) << static_cast<unsigned int>(fData[i]);
    }
    
    TXString str = s.str().c_str();
    str.MakeLower();
    return str;
}

bool UuidStorage::Generate()
{
    bool success = false;
#ifdef _WINDOWS
    GUID	guid;
    HRESULT result = CoCreateGuid(&guid);
    if(result == S_OK)
    {
        fData[0] = (Uint8) ((guid.Data1 >> 24) & 0xFF);
        fData[1] = (Uint8) ((guid.Data1 >> 16) & 0xFF);
        fData[2] = (Uint8) ((guid.Data1 >> 8) & 0xFF);
        fData[3] = (Uint8) (guid.Data1 & 0xFF);
        fData[4] = guid.Data2 >> 8;
        fData[5] = guid.Data2 & 0xFF;
        fData[6] = guid.Data3 >> 8;
        fData[7] = guid.Data3 & 0xFF;
        fData[8] = guid.Data4[0];
        fData[9] = guid.Data4[1];
        fData[10] = guid.Data4[2];
        fData[11] = guid.Data4[3];
        fData[12] = guid.Data4[4];
        fData[13] = guid.Data4[5];
        fData[14] = guid.Data4[6];
        fData[15] = guid.Data4[7];
        success = true;
    }
#else
    CFUUIDRef		myUUID			= ::CFUUIDCreate( kCFAllocatorDefault );
    if ( myUUID ) {
        CFUUIDBytes bytes = CFUUIDGetUUIDBytes(myUUID);
        NSData* data  = [NSData dataWithBytesNoCopy:&bytes length: sizeof(bytes) freeWhenDone:NO];
        [data getBytes: fData length: sizeof(fData)];
        ::CFRelease( myUUID );
        success = true;
    }
#endif
    return success;
}

size_t UuidStorage::hash() const 
{
    size_t hashFunc = 17;
    for (const auto& it : fData)
        hashFunc = hashFunc * 19 + it;
    return hashFunc;
}

TDocumentUuidsCheckTable::TDocumentUuidsCheckTable()
{
	fUuids = UuidTable();
	VectorWorks::Filing::IFileIdentifierPtr curFile(VectorWorks::Filing::IID_FileIdentifier);
	bool saved;
	gSDK->GetActiveDocument(&curFile, saved);
	curFile->GetFileFullPath(fDocumentPath);
	Boolean disableTempFlag = true;
	gSDK->Kludge(6036, &disableTempFlag, nullptr);
	gSDK->ForEachObjectN(allObjects+descendIntoAll+descendIntoViewports+descendIntoAuxLists, [&](MCObjectHandle h) {
		TXString uuid;
		gSDK->GetObjectUuid(h, uuid);
		fUuids.insert(uuid);
	});
	disableTempFlag = false;
	gSDK->Kludge(6036, &disableTempFlag, nullptr);
}

void TDocumentUuidsCheckTable::AddUuidToCheckTable(const TXString& uuid)
{
	fUuids.insert(uuid);
}

bool TDocumentUuidsCheckTable::IsUuidInCheckTable(const TXString& uuid)
{
	bool success = false;
	if (fUuids.find(uuid) != fUuids.end())
	{
		success = true;
	}
	return success;
}

void TDocumentUuidsCheckTable::RemoveUuidFromCheckTable(const TXString& uuid)
{
	if (fUuids.find(uuid) != fUuids.end())
	{
		fUuids.erase(uuid);
	}
}

bool TDocumentUuidsCheckTable::IsTableForActiveDocument()
{
	VectorWorks::Filing::IFileIdentifierPtr curFile(VectorWorks::Filing::IID_FileIdentifier);
	bool saved;
	gSDK->GetActiveDocument(&curFile, saved);
	TXString curFilePath;
	curFile->GetFileFullPath(curFilePath);
	return fDocumentPath.EqualNoCase(curFilePath);
}

