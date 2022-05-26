//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include <set>
#include <unordered_set>

// A version of UUID that does not automatically generate when using default construction
class UuidStorage
{
public:
    UuidStorage();  // main constructor does not generate a uuid
    UuidStorage(const TXString& s);
    // It is not intended for this class to have any other constructors

    bool IsEmpty() const;
    void Reset();
    
    bool operator==(const UuidStorage& id) const;
    bool operator!=(const UuidStorage& id) const { return !this->operator==(id); }
    bool operator<(const UuidStorage& id) const;
	operator const TXString() const { return this->ToString(); }
    
    TXString ToString() const;
    
    bool Generate();

	typedef Uint8 Data[16];

    // Access to serialize/deserialize, without providing an arbitrary constructor
    const Data& SerializeToBytes() const { return fData; }
    void DeserializeFromBytes(const Data& bytes) { memcpy(fData, bytes, sizeof(fData)); }

    size_t hash() const; 

protected:
    Data		fData;
    
};

typedef std::vector<UuidStorage>		UuidStorageList;
typedef std::set<UuidStorage>			UuidStorageSet;
typedef std::unordered_set<UuidStorage> UuidStorageUnorderedSet;

extern const UuidStorage        kEmptyUuidStorage; // An empty uuid storage
extern const UuidStorageList    kEmptyUuidStorageList;
extern const UuidStorageSet     kEmptyUuidStorageSet;


namespace std { 
    template <>
    struct hash<UuidStorage> {
        size_t operator()(const UuidStorage& x) const
        { 
            return x.hash(); 
        } 
    };
}

typedef std::unordered_set<UuidStorage> UuidTable;
class TDocumentUuidsCheckTable
{
private:
	UuidTable fUuids;
	//We don't have access to handles here, so we're going to store the path instead
	TXString fDocumentPath;
public:
	TDocumentUuidsCheckTable();
	void AddUuidToCheckTable(const TXString& uuid);
	bool IsUuidInCheckTable(const TXString& uuid);
	void RemoveUuidFromCheckTable(const TXString& uuid);
	bool IsTableForActiveDocument();
};

