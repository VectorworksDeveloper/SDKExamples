//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#if _MINICAD_
# include "HelpText.X.h"
#endif

# include "VWFC//PluginSupport/VWExtensions.h"
# include "VWFC//PluginSupport/VWExtensionParametric.h"

using namespace VWFC::PluginSupport;

// ------------------------------------------------------------------------------------------------------
bool SResString::operator<(const SResString& other) const
{
	if ( strcmp( fResNameWithoutPathOrExtension, other.fResNameWithoutPathOrExtension ) == 0 ) {
		return strcmp( fStringIdentifier, other.fStringIdentifier ) < 0;
	}
	else {
		return strcmp( fResNameWithoutPathOrExtension, other.fResNameWithoutPathOrExtension ) < 0;
	}
}

// ------------------------------------------------------------------------------------------------------
bool SSTRResource::operator<(const SSTRResource& other) const
{
	if ( fListID == other.fListID ) {
		return fIndex < other.fIndex;
	}
	else {
		return fListID < other.fListID;
	}
}

// ------------------------------------------------------------------------------------------------------
bool STEXTResource::operator<(const STEXTResource& other) const
{
	return fID < other.fID;
}

// ------------------------------------------------------------------------------------------------------
VWExtensionParametric::VWExtensionParametric(CallBackPtr cbp,
								const SParametricDef& parametricDef,
								const SParametricParam2Def* arrParamDefs,
								const SParametricParamChc* arrParamChcs)
	: fCBP( cbp )
	, fSubType				( parametricDef.fSubType				)
	, fResetOnMove			( parametricDef.fResetOnMove			)
	, fResetOnRotate		( parametricDef.fResetOnRotate			)
	, fWallInsertOnEdge		( parametricDef.fWallInsertOnEdge		)
	, fWallInsertNoBreak	( parametricDef.fWallInsertNoBreak		)
	, fWallInsertHalfBreak	( parametricDef.fWallInsertHalfBreak	)
	, fWallInsertHideCaps	( parametricDef.fWallInsertHideCaps		)
	, farrParamDefs_		( nullptr )
	, farrParam2Defs_		( arrParamDefs )
	, farrParamChcs_		( arrParamChcs )
	, farrParamDefs			( nullptr )
	, farrParamChcs			( nullptr )
	, fParametersSink		( nullptr )
	, fParametricEventSink	( nullptr )
	, fProtectionObtained	( false )
	, fHasProtection		( false )
	, fProtectionSink		( nullptr )
	, fSubpartTypesSink		( nullptr )
{
	gCBP				= fCBP;
	fParamsCount		= 0;
	
	fstrLocalizedName	= TXResStr( parametricDef.fLocalizedName.fResNameWithoutPathOrExtension, parametricDef.fLocalizedName.fStringIdentifier );

	// first count the number of things we will need to store
	const SParametricParam2Def*	currParam	= farrParam2Defs_;
	while ( currParam && !currParam->fUniversalName.IsEmpty() ) 
	{
		fParamsCount++;
		currParam++;
	}

	// These arrays will be used to store temporary ID/Index pairs.
	const Sint32 numStaticElements = 256;
	const char* idsStaticArray[numStaticElements], **idsArray = idsStaticArray;
	const char* indexStaticArray[numStaticElements], **indexArray = indexStaticArray;
	SResString localizedNameIDIndexPairsStaticArray[numStaticElements], *localizedNameIDIndexPairs = localizedNameIDIndexPairsStaticArray;
	if (fParamsCount > numStaticElements)
	{	// most of the time, static storage is used. If param count is too big to fit, we use heap storage.
		idsArray = SDK_NEW const char*[fParamsCount];
		indexArray = SDK_NEW const char*[fParamsCount];
		localizedNameIDIndexPairs = SDK_NEW SResString[fParamsCount];
	}

	Sint32 numItemsNotCached = 0;
	for (Sint32 curParamIndex = 0; curParamIndex < (Sint32) fParamsCount; ++curParamIndex)
	{
		currParam = &farrParam2Defs_[curParamIndex];
		TResStringCache_::iterator	resIt	= fResStringChache_.find( currParam->fLocalizedName );
		if ( resIt == fResStringChache_.end() ) 
		{	// if not found in cache already
			localizedNameIDIndexPairs[numItemsNotCached] = currParam->fLocalizedName;
			idsArray[numItemsNotCached] = currParam->fLocalizedName.fResNameWithoutPathOrExtension;
			indexArray[numItemsNotCached] = currParam->fLocalizedName.fStringIdentifier;
			++numItemsNotCached;
		}
	}

	TXString param;
	// Insert them in the cache.
	for (Sint32 i = 0; i < numItemsNotCached; ++i)
	{
		param = TXResStr(idsArray[i], indexArray[i], eAllowEmptyResult);
		fResStringChache_.insert( TResStringCache_::value_type(localizedNameIDIndexPairs[i], param) );
	}

	// ------------------------------------- 
	// Now do the same for the chc array, which to my knowledge isn't necessarily the same as fParamsCount - if it is, some housekeeping can be removed below
	// First, count them.
	Sint32 numChcs = 0;
	const SParametricParamChc*	currChc		= farrParamChcs_;
	while( currChc && currChc->fChcID ) 
	{
		++numChcs;
		currChc++;
	}

	if (numChcs > (Sint32) fParamsCount)
	{	// we may need to reallocate our arrays
		if (numChcs > numStaticElements)
		{	
			// deallocate if necessary
			if (idsArray != idsStaticArray)
			{
				delete [] idsArray;
				delete [] indexArray;
				delete [] localizedNameIDIndexPairs;
			}
			idsArray = SDK_NEW const char*[numChcs];
			indexArray = SDK_NEW const char*[numChcs];
			localizedNameIDIndexPairs = SDK_NEW SResString[numChcs];
		}
	}

	numItemsNotCached = 0;
	for (Sint32 curChcIndex = 0; curChcIndex < numChcs; ++curChcIndex)
	{
		const SParametricParamChc* currChc = &farrParamChcs_[curChcIndex];
		TResStringCache_::iterator	resIt	= fResStringChache_.find( currChc->fLocalizedChoice );
		if ( resIt == fResStringChache_.end() ) {	// not already cached
			localizedNameIDIndexPairs[numItemsNotCached] =  currChc->fLocalizedChoice;
			idsArray[numItemsNotCached] = currChc->fLocalizedChoice.fResNameWithoutPathOrExtension;
			indexArray[numItemsNotCached] = currChc->fLocalizedChoice.fStringIdentifier;
			++numItemsNotCached;
		}

		TChcCache_::const_iterator	chcIt	= fParamChcCache_.find( currChc->fChcID );	
		if ( chcIt == fParamChcCache_.end() ) {
			// all concequitive chc values have to have the same ID
			fParamChcCache_.insert( TChcCache_::value_type( currChc->fChcID, currChc ) );
		}

		currChc++;
	}

	// Insert them in the cache.
	for (Sint32 i = 0; i < numItemsNotCached; ++i)
	{
		fResStringChache_.insert( TResStringCache_::value_type( localizedNameIDIndexPairs[i], TXResStr(idsArray[i], indexArray[i]) ) );
	}

	// deallocate if necessary
	if (idsArray != idsStaticArray)
	{
		delete [] idsArray;
		delete [] indexArray;
		delete [] localizedNameIDIndexPairs;
	}
}

VWExtensionParametric::VWExtensionParametric(CallBackPtr cbp,
								const SParametricDef& parametricDef,
								const SParametricParamDef* arrParamDefs,
								const SParametricParamChc* arrParamChcs)
	: fCBP( cbp )
	, fSubType				( parametricDef.fSubType				)
	, fResetOnMove			( parametricDef.fResetOnMove			)
	, fResetOnRotate		( parametricDef.fResetOnRotate			)
	, fWallInsertOnEdge		( parametricDef.fWallInsertOnEdge		)
	, fWallInsertNoBreak	( parametricDef.fWallInsertNoBreak		)
	, fWallInsertHalfBreak	( parametricDef.fWallInsertHalfBreak	)
	, fWallInsertHideCaps	( parametricDef.fWallInsertHideCaps		)
	, farrParamDefs_		( arrParamDefs )
	, farrParam2Defs_		( nullptr )
	, farrParamChcs_		( arrParamChcs )
	, farrParamDefs			( nullptr )
	, farrParamChcs			( nullptr )
	, fParametersSink		( nullptr )
	, fParametricEventSink	( nullptr )
	, fProtectionObtained	( false )
	, fHasProtection		( false )
	, fProtectionSink		( nullptr )
	, fSubpartTypesSink		( nullptr )
{
	gCBP				= fCBP;
	fParamsCount		= 0;
	
	fstrLocalizedName	= TXResStr( parametricDef.fLocalizedName.fResNameWithoutPathOrExtension, parametricDef.fLocalizedName.fStringIdentifier );

	// first count the number of things we will need to store
	const SParametricParamDef*	currParam	= farrParamDefs_;
	while ( currParam && !currParam->fUniversalName.IsEmpty() ) 
	{
		fParamsCount++;
		currParam++;
	}

	// These arrays will be used to store temporary ID/Index pairs.
	const Sint32 numStaticElements = 256;
	const char* idsStaticArray[numStaticElements], **idsArray = idsStaticArray;
	const char* indexStaticArray[numStaticElements], **indexArray = indexStaticArray;
	SResString localizedNameIDIndexPairsStaticArray[numStaticElements], *localizedNameIDIndexPairs = localizedNameIDIndexPairsStaticArray;
	if (fParamsCount > numStaticElements)
	{	// most of the time, static storage is used. If param count is too big to fit, we use heap storage.
		idsArray = SDK_NEW const char*[fParamsCount];
		indexArray = SDK_NEW const char*[fParamsCount];
		localizedNameIDIndexPairs = SDK_NEW SResString[fParamsCount];
	}

	Sint32 numItemsNotCached = 0;
	for (Sint32 curParamIndex = 0; curParamIndex < (Sint32) fParamsCount; ++curParamIndex)
	{
		currParam = &farrParamDefs_[curParamIndex];
		TResStringCache_::iterator	resIt	= fResStringChache_.find( currParam->fLocalizedName );
		if ( resIt == fResStringChache_.end() ) 
		{	// if not found in cache already
			localizedNameIDIndexPairs[numItemsNotCached] = currParam->fLocalizedName;
			idsArray[numItemsNotCached] = currParam->fLocalizedName.fResNameWithoutPathOrExtension;
			indexArray[numItemsNotCached] = currParam->fLocalizedName.fStringIdentifier;
			++numItemsNotCached;
		}
	}

	TXString param;
	// Insert them in the cache.
	for (Sint32 i = 0; i < numItemsNotCached; ++i)
	{
		param = TXResStr(idsArray[i], indexArray[i], eAllowEmptyResult);
		fResStringChache_.insert( TResStringCache_::value_type(localizedNameIDIndexPairs[i], param) );
	}

	// ------------------------------------- 
	// Now do the same for the chc array, which to my knowledge isn't necessarily the same as fParamsCount - if it is, some housekeeping can be removed below
	// First, count them.
	Sint32 numChcs = 0;
	const SParametricParamChc*	currChc		= farrParamChcs_;
	while( currChc && currChc->fChcID ) 
	{
		++numChcs;
		currChc++;
	}

	if (numChcs > (Sint32) fParamsCount)
	{	// we may need to reallocate our arrays
		if (numChcs > numStaticElements)
		{	
			// deallocate if necessary
			if (idsArray != idsStaticArray)
			{
				delete [] idsArray;
				delete [] indexArray;
				delete [] localizedNameIDIndexPairs;
			}
			idsArray = SDK_NEW const char*[numChcs];
			indexArray = SDK_NEW const char*[numChcs];
			localizedNameIDIndexPairs = SDK_NEW SResString[numChcs];
		}
	}

	numItemsNotCached = 0;
	for (Sint32 curChcIndex = 0; curChcIndex < numChcs; ++curChcIndex)
	{
		const SParametricParamChc* currChc = &farrParamChcs_[curChcIndex];
		TResStringCache_::iterator	resIt	= fResStringChache_.find( currChc->fLocalizedChoice );
		if ( resIt == fResStringChache_.end() ) {	// not already cached
			localizedNameIDIndexPairs[numItemsNotCached] =  currChc->fLocalizedChoice;
			idsArray[numItemsNotCached] = currChc->fLocalizedChoice.fResNameWithoutPathOrExtension;
			indexArray[numItemsNotCached] = currChc->fLocalizedChoice.fStringIdentifier;
			++numItemsNotCached;
		}

		TChcCache_::const_iterator	chcIt	= fParamChcCache_.find( currChc->fChcID );	
		if ( chcIt == fParamChcCache_.end() ) {
			// all concequitive chc values have to have the same ID
			fParamChcCache_.insert( TChcCache_::value_type( currChc->fChcID, currChc ) );
		}

		currChc++;
	}

	// Insert them in the cache.
	for (Sint32 i = 0; i < numItemsNotCached; ++i)
	{
		fResStringChache_.insert( TResStringCache_::value_type( localizedNameIDIndexPairs[i], TXResStr(idsArray[i], indexArray[i]) ) );
	}

	// deallocate if necessary
	if (idsArray != idsStaticArray)
	{
		delete [] idsArray;
		delete [] indexArray;
		delete [] localizedNameIDIndexPairs;
	}
}

VWExtensionParametric::VWExtensionParametric(CallBackPtr cbp,
								const SParametricDef_Legacy& parametricDef,
								const SParametricParamDef_Legacy* arrParamDefs,
								const SParametricParamChc_Legacy* arrParamChcs)
	: fCBP( cbp )
	, fSubType				( parametricDef.fSubType				)
	, fResetOnMove			( parametricDef.fResetOnMove			)
	, fResetOnRotate		( parametricDef.fResetOnRotate			)
	, fWallInsertOnEdge		( parametricDef.fWallInsertOnEdge		)
	, fWallInsertNoBreak	( parametricDef.fWallInsertNoBreak		)
	, fWallInsertHalfBreak	( parametricDef.fWallInsertHalfBreak	)
	, fWallInsertHideCaps	( parametricDef.fWallInsertHideCaps		)
	, farrParamDefs			( arrParamDefs )
	, farrParamChcs			( arrParamChcs )
	, farrParamDefs_		( nullptr )
	, farrParam2Defs_		( nullptr )
	, farrParamChcs_		( nullptr )
	, fParametersSink		( nullptr )
	, fParametricEventSink	( nullptr )
	, fProtectionObtained	( false )
	, fHasProtection		( false )
	, fProtectionSink		( nullptr )
	, fSubpartTypesSink		( nullptr )
{
	gCBP				= fCBP;
	fParamsCount		= 0;
	
	fstrLocalizedName	= TXLegacyResource( parametricDef.fLocalizedName.fListID, parametricDef.fLocalizedName.fIndex );

	// first count the number of things we will need to store
	const SParametricParamDef_Legacy*	currParam	= farrParamDefs;
	while ( currParam && !currParam->fUniversalName.IsEmpty() ) 
	{
		fParamsCount++;
		currParam++;
	}

	// These arrays will be used to store temporary ID/Index pairs.
	const Sint32 numStaticElements = 256;
	short idsStaticArray[numStaticElements], *idsArray = idsStaticArray;
	short indexStaticArray[numStaticElements], *indexArray = indexStaticArray;
	SSTRResource localizedNameIDIndexPairsStaticArray[numStaticElements], *localizedNameIDIndexPairs = localizedNameIDIndexPairsStaticArray;
	if (fParamsCount > numStaticElements)
	{	// most of the time, static storage is used. If param count is too big to fit, we use heap storage.
		idsArray = SDK_NEW short[fParamsCount];
		indexArray = SDK_NEW short[fParamsCount];
		localizedNameIDIndexPairs = SDK_NEW SSTRResource[fParamsCount];
	}

	Sint32 numItemsNotCached = 0;
	for (Sint32 curParamIndex = 0; curParamIndex < (Sint32) fParamsCount; ++curParamIndex)
	{
		currParam = &farrParamDefs[curParamIndex];
		TResStringCache::iterator	resIt	= fResStringChache.find( currParam->fLocalizedName );
		if ( resIt == fResStringChache.end() ) 
		{	// if not found in cache already
			localizedNameIDIndexPairs[numItemsNotCached] = currParam->fLocalizedName;
			idsArray[numItemsNotCached] = currParam->fLocalizedName.fListID;
			indexArray[numItemsNotCached] = currParam->fLocalizedName.fIndex;
			++numItemsNotCached;
		}
	}

	TXString param;
	// Insert them in the cache.
	for (Sint32 i = 0; i < numItemsNotCached; ++i)
	{
		param = TXLegacyResource(idsArray[i], indexArray[i], eAllowEmptyResult);
		fResStringChache.insert( TResStringCache::value_type(localizedNameIDIndexPairs[i], param) );
	}

	// ------------------------------------- 
	// Now do the same for the chc array, which to my knowledge isn't necessarily the same as fParamsCount - if it is, some housekeeping can be removed below
	// First, count them.
	Sint32 numChcs = 0;
	const SParametricParamChc_Legacy*	currChc		= farrParamChcs;
	while( currChc && currChc->fChcID ) 
	{
		++numChcs;
		currChc++;
	}

	if (numChcs > (Sint32) fParamsCount)
	{	// we may need to reallocate our arrays
		if (numChcs > numStaticElements)
		{	
			// deallocate if necessary
			if (idsArray != idsStaticArray)
			{
				delete [] idsArray;
				delete [] indexArray;
				delete [] localizedNameIDIndexPairs;
			}
			idsArray = SDK_NEW short[numChcs]; //-V121
			indexArray = SDK_NEW short[numChcs]; //-V121
			localizedNameIDIndexPairs = SDK_NEW SSTRResource[numChcs]; //-V121
		}
	}

	numItemsNotCached = 0;
	for (Sint32 curChcIndex = 0; curChcIndex < numChcs; ++curChcIndex)
	{
		const SParametricParamChc_Legacy* currChc = &farrParamChcs[curChcIndex];
		TResStringCache::iterator	resIt	= fResStringChache.find( currChc->fLocalizedChoice );
		if ( resIt == fResStringChache.end() ) {	// not already cached
			localizedNameIDIndexPairs[numItemsNotCached] =  currChc->fLocalizedChoice;
			idsArray[numItemsNotCached] = currChc->fLocalizedChoice.fListID;
			indexArray[numItemsNotCached] = currChc->fLocalizedChoice.fIndex;
			++numItemsNotCached;
		}

		TChcCache::const_iterator	chcIt	= fParamChcCache.find( currChc->fChcID );	
		if ( chcIt == fParamChcCache.end() ) {
			// all concequitive chc values have to have the same ID
			fParamChcCache.insert( TChcCache::value_type( currChc->fChcID, currChc ) );
		}

		currChc++;
	}

	// Insert them in the cache.
	for (Sint32 i = 0; i < numItemsNotCached; ++i)
	{
		fResStringChache.insert( TResStringCache::value_type( localizedNameIDIndexPairs[i], TXLegacyResource(idsArray[i], indexArray[i]) ) );
	}

	// deallocate if necessary
	if (idsArray != idsStaticArray)
	{
		delete [] idsArray;
		delete [] indexArray;
		delete [] localizedNameIDIndexPairs;
	}
}

VWExtensionParametric::~VWExtensionParametric()
{
}

void VWExtensionParametric::SetLocalizedParamDef( const short listID )
{
	if ( farrParamDefs )
	{
		const SParametricParamDef_Legacy*	currParam	= farrParamDefs;
		while ( currParam && !currParam->fUniversalName.IsEmpty() ) {
			TXString	str	= TXLegacyResource( listID, currParam->fLocalizedName.fIndex, eDontAllowEmptyResult );

			if ( !str.IsEmpty() ) {
				TResStringCache::iterator	resIt	= fResStringChache.find( currParam->fLocalizedName );
				if ( resIt != fResStringChache.end() ) {
					resIt->second = str;
				}
			}
			currParam++;
		}
	}
}

void VWExtensionParametric::SetLocalizedParamDef( size_t paramIndex, const TXString& inLocalizedName )
{
	ASSERTN( kJWarshaw, paramIndex < fParamsCount );	
	if ( paramIndex < fParamsCount ) {
		if ( farrParamDefs )
		{
			const SParametricParamDef_Legacy&		thisParam	= farrParamDefs[ paramIndex ];
			TResStringCache::iterator	resIt	= fResStringChache.find( thisParam.fLocalizedName );
			if ( resIt != fResStringChache.end() ) {
				resIt->second = inLocalizedName;
			}
		}
		else if ( farrParam2Defs_ )
		{
			const SParametricParam2Def&		thisParam	= farrParam2Defs_[ paramIndex ];
			TResStringCache_::iterator	resIt	= fResStringChache_.find( thisParam.fLocalizedName );
			if ( resIt != fResStringChache_.end() ) {
				resIt->second = inLocalizedName;
			}
		}
		else if ( farrParamDefs_ )
		{
			const SParametricParamDef&		thisParam	= farrParamDefs_[ paramIndex ];
			TResStringCache_::iterator	resIt	= fResStringChache_.find( thisParam.fLocalizedName );
			if ( resIt != fResStringChache_.end() ) {
				resIt->second = inLocalizedName;
			}
		}
	}
}


void VWExtensionParametric::SetLocalizedParamChc( const short listID )
{
	const SParametricParamChc_Legacy*	currChc		= farrParamChcs;
	while( currChc && currChc->fChcID ) {
		TXString	str	= TXLegacyResource( listID, currChc->fLocalizedChoice.fIndex, eDontAllowEmptyResult );

		if ( !str.IsEmpty() ) {
			TResStringCache::iterator	resIt	= fResStringChache.find( currChc->fLocalizedChoice );
			if ( resIt != fResStringChache.end() ) {
				resIt->second = str;
			}
		}
		currChc++;
	}

}

void VWExtensionParametric::SetLocalizedParamDef( const TXString& univParamName, const TXString& localizedParamName )
{
	if ( ! localizedParamName.IsEmpty() )
	{
		const SParametricParamDef*	foundParam = nullptr;
		if ( farrParam2Defs_ )
		{
			for(const SParametricParam2Def* thisParam = farrParam2Defs_; thisParam && !thisParam->fUniversalName.IsEmpty(); ++thisParam)
			{
				if ( univParamName == thisParam->fUniversalName )
				{
					foundParam = thisParam;
					break;
				}
			}
		}
		else if ( farrParamDefs_ )
		{
			for(const SParametricParamDef* thisParam =farrParamDefs_; thisParam && !thisParam->fUniversalName.IsEmpty(); ++thisParam)
			{
				if ( univParamName == thisParam->fUniversalName )
				{
					foundParam = thisParam;
					break;
				}
			}
		}

		if ( foundParam )
		{
			auto	resIt		= fResStringChache_.find( foundParam->fLocalizedName );
			if ( resIt != fResStringChache_.end() )
			{
				resIt->second = localizedParamName;
			}
		}
	}
}

void VWExtensionParametric::SetLocalizedParamChc( const TXString& univChoiceName, const TXString& localizedChoiceName )
{
	if ( ! localizedChoiceName.IsEmpty() )
	{
		const SParametricParamChc*	foundChc = nullptr;
		for(const SParametricParamChc* thisChc = farrParamChcs_; thisChc && !thisChc->fUniversalChoice.IsEmpty(); ++thisChc)
		{
			if ( univChoiceName == thisChc->fUniversalChoice )
			{
				foundChc = thisChc;
				break;
			}
		}

		if ( foundChc )
		{
			auto	resIt		= fResStringChache_.find( foundChc->fLocalizedChoice );
			if ( resIt != fResStringChache_.end() )
			{
				resIt->second = localizedChoiceName;
			}
		}
	}
}

void VWExtensionParametric::SetLocalizedName( const TXString& localizedName )
{
	if ( ! localizedName.IsEmpty() )
	{
		fstrLocalizedName	= localizedName;
	}
}

bool VWExtensionParametric::GetLocalizedDefault(bool isMetric, const TXString& szUniversalName, TXString& outValue)
{
    isMetric; szUniversalName; outValue;
    return false;
}

void VWExtensionParametric::OnRefCountZero()
{
	if ( fParametricEventSink ) {
		delete fParametricEventSink;
		fParametricEventSink	= nullptr;
	}

	if ( fParametersSink ) {
		delete fParametersSink;
		fParametersSink	= nullptr;
	}

	if ( fProtectionSink ) {
		delete fProtectionSink;
		fProtectionSink	= nullptr;
	}

	if ( fSubpartTypesSink ) {
		delete fSubpartTypesSink;
		fSubpartTypesSink	= nullptr;
	}

	for(TSinksMap::iterator it=fmapSinks.begin(); it!=fmapSinks.end(); it++) {
		IEventSink*	theSink	= it->second;
		if ( theSink ) {
			delete theSink;
		}
	}

	fmapSinks.clear();
}

IEventSink* VWExtensionParametric::QueryEventSink(const TSinkIID& iid)
{
	if ( fProtectionObtained == false ) {
		fHasProtection			= this->GetProtectionSinkIID( fProtectionSinkIID );
		fProtectionObtained		= true;
	}

	IEventSink*	pResult	= nullptr;
	if ( IID_ParametricParams2Provider == iid || IID_ParametricParamsProvider == iid ) {
		if ( fParametersSink == nullptr ) {
			fParametersSink	= SDK_NEW CParametersProvider( this );
		}

		if ( fParametersSink ) {
			fParametersSink->AddRef();
		}

		pResult	= fParametersSink;
	}
	else if ( IID_ParametricEventSink == iid ) {
		if ( fParametricEventSink == nullptr ) {
			fParametricEventSink	= this->CreateParametricEventSink( this );
			if ( fParametricEventSink ) {
				if ( fUniversalName.IsEmpty() )
					fUniversalName		= this->GetUniversalName();

				fParametricEventSink->AddRef();
				VWParametric_EventSink*	vwfcSink	= dynamic_cast<VWParametric_EventSink*>( fParametricEventSink );
				if ( vwfcSink ) {
					vwfcSink->SetUniversalName( fUniversalName );
				}
			}
		}
		pResult	= fParametricEventSink;
	}
	else if ( fHasProtection && fProtectionSinkIID == iid ) {
		if ( fProtectionSink == nullptr ) {
			fProtectionSink	= this->CreateProtectionSink( this );
			if ( fProtectionSink == nullptr ) {
				fHasProtection	= false;
			}
		}

		if ( fProtectionSink ) {
			fProtectionSink->AddRef();
			pResult	= fProtectionSink;
		}
	}
	else if ( IID_SubpartTypesProvider == iid && farrSubpartTypes.size() ) {
		if ( fSubpartTypesSink == nullptr ) {
			fSubpartTypesSink	= SDK_NEW CSubpartTypesProvider( this );
		}

		if ( fSubpartTypesSink )
			fSubpartTypesSink->AddRef();

		pResult	= fSubpartTypesSink;
	}
	else {
		IEventSink*			theSink	= nullptr;
		TSinksMap::iterator	it		= fmapSinks.find( iid );
		if ( it != fmapSinks.end() ) {
			theSink	= it->second;
		}
		else {
			fDefinedSink		= nullptr;
			fDefinedSinkIID		= iid;
			this->DefineSinks();
			if ( fDefinedSink ) {
				fmapSinks.insert( TSinksMap::value_type( iid, fDefinedSink ) );
				theSink			= fDefinedSink;
				fDefinedSink	= nullptr;
			}
		}

		if ( theSink ) {
			theSink->AddRef();
			pResult			= theSink;
		}
	}

	return pResult;
}

void VWExtensionParametric::DefineSinks()
{
}

bool VWExtensionParametric::GetProtectionSinkIID(TSinkIID& outIID)
{
	return false;
}

IProviderProtection* VWExtensionParametric::CreateProtectionSink(IVWUnknown* parent)
{
	return nullptr;
}

const TXString& VWExtensionParametric::GetLocalizedName()
{
	return fstrLocalizedName;
}

EParametricSubType VWExtensionParametric::GetObjectType()
{
	return fSubType;
}

void VWExtensionParametric::GetResetModeOnMove(bool& outOnMove, bool& outOnRotate)
{
	outOnMove		= fResetOnMove;
	outOnRotate		= fResetOnRotate;
}
void VWExtensionParametric::GetWallInsertMode(bool& outOnEdge, bool& outNoBreak, bool& outHalfBreak, bool& outHideCaps)
{
	outOnEdge		= fWallInsertOnEdge;
	outNoBreak		= fWallInsertNoBreak;
	outHalfBreak	= fWallInsertHalfBreak;
	outHideCaps		= fWallInsertHideCaps;
}

void VWExtensionParametric::AddSubpartType(const char* univName, const TXString& localizedName)
{
	farrSubpartTypes.push_back( std::make_pair( univName, localizedName ) );
}

// --------------------------------------------------------------------------------------------------------
VWExtensionParametric::CParametersProvider::CParametersProvider(VWExtensionParametric* parent)
	: fParent( parent )
{
}

VWExtensionParametric::CParametersProvider::~CParametersProvider()
{
}

size_t VWExtensionParametric::CParametersProvider::GetParamsCount()
{
	return fParent->fParamsCount;
}

void VWExtensionParametric::CParametersProvider::GetParamAt(size_t paramIndex, TXString& outUniversalName, EFieldStyle& outType)
{
	if ( VERIFYN( kVStanev, paramIndex < fParent->fParamsCount ) )
	{
		if ( fParent->farrParamDefs_ || fParent->farrParam2Defs_ )
		{
			const SParametricParamDef&	thisParam	= fParent->farrParamDefs_ ? fParent->farrParamDefs_[ paramIndex ] : fParent->farrParam2Defs_[ paramIndex ];;

			outUniversalName	= thisParam.fUniversalName;
			outType				= thisParam.fFieldStyle;
		}
		else
		{
			const SParametricParamDef_Legacy&	thisParam	= fParent->farrParamDefs[ paramIndex ];

			outUniversalName	= thisParam.fUniversalName;
			outType				= thisParam.fFieldStyle;
		}
	}
}

const TXString& VWExtensionParametric::CParametersProvider::GetParamNameAt(size_t paramIndex)
{
	if ( VERIFYN( kVStanev, paramIndex < fParent->fParamsCount ) )
	{
		if ( fParent->farrParamDefs_ || fParent->farrParam2Defs_ )
		{
			const SParametricParamDef&			thisParam	= fParent->farrParamDefs_ ? fParent->farrParamDefs_[ paramIndex ] : fParent->farrParam2Defs_[ paramIndex ];;
			TResStringCache_::const_iterator	resIt		= fParent->fResStringChache_.find( thisParam.fLocalizedName );
			return ( VERIFYN( kVStanev, resIt != fParent->fResStringChache_.end() ) ) ? resIt->second : fParent->fEmptyString;
		}
		else
		{
			const SParametricParamDef_Legacy&		thisParam	= fParent->farrParamDefs[ paramIndex ];
			TResStringCache::const_iterator	resIt		= fParent->fResStringChache.find( thisParam.fLocalizedName );
			return ( VERIFYN( kVStanev, resIt != fParent->fResStringChache.end() ) ) ? resIt->second : fParent->fEmptyString;
		}
	}
	else
	{
		return fParent->fEmptyString;
	}
}

void VWExtensionParametric::CParametersProvider::GetParamDefValueImperial(size_t paramIndex, IRecordItem* outValue)
{
	if ( VERIFYN( kVStanev, paramIndex < fParent->fParamsCount ) )
	{
		if ( fParent->farrParam2Defs_ )
		{
			const SParametricParam2Def&	thisParam	= fParent->farrParam2Defs_[ paramIndex ];

			TXString theValue = thisParam.fDefaultImperial;
			if ( thisParam.fAutoReadDefaultsFromVWR )
			{
				if ( fParent->fUniversalName.IsEmpty() )
					fParent->fUniversalName		= fParent->GetUniversalName();

				TXString resFile;
				resFile.Format( "%s_Imperial", fParent->fUniversalName );
				theValue = TXResStr( resFile, thisParam.fUniversalName );
			}

			if ( thisParam.fDefaultValueCallback )
				thisParam.fDefaultValueCallback( false, theValue, thisParam.fUniversalName, outValue );
			else
				outValue->SetFieldValueAsString( theValue );
		}
		else if ( fParent->farrParamDefs_ )
		{
			const SParametricParamDef&	thisParam	= fParent->farrParamDefs_[ paramIndex ];

			TXString	theValue;
			if ( !fParent->GetLocalizedDefault( false, thisParam.fUniversalName, theValue ) )
			{
				this->GetDefaultValue( thisParam.fDefaultImperial, theValue );
			}

			outValue->SetFieldValueAsString( theValue );
		}
		else
		{
			const SParametricParamDef_Legacy&	thisParam	= fParent->farrParamDefs[ paramIndex ];

			TXString	theValue;
			if ( !fParent->GetLocalizedDefault( false, thisParam.fUniversalName, theValue ) )
			{
				this->GetDefaultValue( thisParam.fDefaultImperial, theValue );
			}

			outValue->SetFieldValueAsString( theValue );
		}
	}
}

void VWExtensionParametric::CParametersProvider::GetParamDefValueMetric(size_t paramIndex, IRecordItem* outValue)
{
	if ( VERIFYN( kVStanev, paramIndex < fParent->fParamsCount ) )
	{
		if ( fParent->farrParam2Defs_ )
		{
			const SParametricParam2Def&	thisParam	= fParent->farrParam2Defs_[ paramIndex ];

			TXString theValue = thisParam.fDefaultMetric;
			if ( thisParam.fAutoReadDefaultsFromVWR )
			{
				if ( fParent->fUniversalName.IsEmpty() )
					fParent->fUniversalName		= fParent->GetUniversalName();

				TXString resFile;
				resFile.Format( "%s_Metric", fParent->fUniversalName );
				theValue = TXResStr( resFile, thisParam.fUniversalName );
			}

			if ( thisParam.fDefaultValueCallback )
				thisParam.fDefaultValueCallback( true, theValue, thisParam.fUniversalName, outValue );
			else
				outValue->SetFieldValueAsString( theValue );
		}
		else if ( fParent->farrParamDefs_ )
		{
			const SParametricParamDef&	thisParam	= fParent->farrParamDefs_[ paramIndex ];

			TXString	theValue;
			if ( !fParent->GetLocalizedDefault( true, thisParam.fUniversalName, theValue ) )
			{
				this->GetDefaultValue( thisParam.fDefaultMetric, theValue );
			}

			outValue->SetFieldValueAsString( theValue );
		}
		else
		{
			const SParametricParamDef_Legacy&	thisParam	= fParent->farrParamDefs[ paramIndex ];

			TXString	theValue;
			if ( !fParent->GetLocalizedDefault( true, thisParam.fUniversalName, theValue ) )
			{
				this->GetDefaultValue( thisParam.fDefaultMetric, theValue );
			}

			outValue->SetFieldValueAsString( theValue );
		}
	}
}

void VWExtensionParametric::CParametersProvider::GetParamChoices(size_t paramIndex, TXStringArray& outArrUniversalNames, TXStringArray& outArrDisplayNames)
{
	outArrUniversalNames.Clear();
	outArrDisplayNames.Clear();

	if ( VERIFYN( kVStanev, paramIndex < fParent->fParamsCount ) )
	{
		if ( fParent->farrParamDefs_ || fParent->farrParam2Defs_ )
		{
			const SParametricParamDef&	thisParam	= fParent->farrParamDefs_ ? fParent->farrParamDefs_[ paramIndex ] : fParent->farrParam2Defs_[ paramIndex ];

			if ( thisParam.fChoicesChcID > 0 )
			{
				TChcCache_::const_iterator	chcIt	= fParent->fParamChcCache_.find( thisParam.fChoicesChcID );
				if ( chcIt != fParent->fParamChcCache_.end() )
				{
					const SParametricParamChc*	currChc	= chcIt->second;
					while ( currChc && thisParam.fChoicesChcID == currChc->fChcID && !currChc->fUniversalChoice.IsEmpty() )
					{

						TXString	universalChoice	= currChc->fUniversalChoice;
						outArrUniversalNames.Append( universalChoice );

						TResStringCache_::const_iterator	resIt	= fParent->fResStringChache_.find( currChc->fLocalizedChoice );
						outArrDisplayNames.Append( ( VERIFYN( kVStanev, resIt != fParent->fResStringChache_.end() ) ) ? resIt->second : "" );

						currChc++;
					}
				}
			}
		}
		else
		{
			const SParametricParamDef_Legacy&	thisParam	= fParent->farrParamDefs[ paramIndex ];

			if ( thisParam.fChoicesChcID > 0 )
			{
				TChcCache::const_iterator	chcIt	= fParent->fParamChcCache.find( thisParam.fChoicesChcID );
				if ( chcIt != fParent->fParamChcCache.end() )
				{
					const SParametricParamChc_Legacy*	currChc	= chcIt->second;
					while ( currChc && thisParam.fChoicesChcID == currChc->fChcID && !currChc->fUniversalChoice.IsEmpty() )
					{

						TXString	universalChoice	= currChc->fUniversalChoice;
						outArrUniversalNames.Append( universalChoice );

						TResStringCache::const_iterator	resIt	= fParent->fResStringChache.find( currChc->fLocalizedChoice );
						outArrDisplayNames.Append( ( VERIFYN( kVStanev, resIt != fParent->fResStringChache.end() ) ) ? resIt->second : "" );

						currChc++;
					}
				}
			}
		}
	}
}

void VWExtensionParametric::CParametersProvider::GetDefaultValue(const TXString& defaultValue, TXString& outValue)
{
	if ( defaultValue[0] == 0x01 || defaultValue[0] == 0x02 )
	{
		if ( VERIFYN( kVStanev, defaultValue[1] != 0x00 ) )
		{
			ASSERTN( kVStanev, defaultValue[1] == '@' );
			TXString	resListIDStr	= defaultValue.Mid(2);
			ptrdiff_t	indexAt			= resListIDStr.Find( ',' );
			if ( indexAt >= 0 ) {
				TXString	resIndexStr	= resListIDStr.Mid( indexAt + 1 );
				if ( defaultValue[0] == 0x02 )
				{
					resListIDStr	= resListIDStr.Left( indexAt );
					outValue = TXResStr( resListIDStr, resIndexStr );
				}
				else
				{
					short		resListID		= resListIDStr.atoi();
					short		resIndex	= resIndexStr.atoi();

					outValue = TXLegacyResource( resListID, resIndex, eAllowEmptyResult );
				}
			}
		}
	}
	else {
		outValue	= defaultValue;
	}
}

// ------------------------------------------------------------------------------------------------------
VWExtensionParametric::CSubpartTypesProvider::CSubpartTypesProvider(VWExtensionParametric* parent)
	: fParent( parent )
{
}

VWExtensionParametric::CSubpartTypesProvider::~CSubpartTypesProvider()
{
}

void VWExtensionParametric::CSubpartTypesProvider::Enumerate(ISubpartTypesContext& context)
{
	for(const auto& it : fParent->farrSubpartTypes)
		context.AddPartType( it.first, it.second );
}

// ------------------------------------------------------------------------------------------------------
VWParametric_EventSink::VWParametric_EventSink(IVWUnknown* parent)
	: VCOMImpl<IParametricEventSink>( parent )
{
	fhObject			= nullptr;
	fbInitialized		= false;
	fObjectEditReason	= kObjectEdit_ExplicitEdit;
}

VWParametric_EventSink::~VWParametric_EventSink()
{
	this->DeinitializeExt();
}

void VWParametric_EventSink::InitializeExt()
{
}

void VWParametric_EventSink::DeinitializeExt()
{
}

void VWParametric_EventSink::GetUserData(void) const
{
	// DO NOT USE THIS
	// This is to prevent old code from using it
}

void VWParametric_EventSink::SetUserData(void) const
{
	// DO NOT USE THIS
	// This is to prevent old code from using it
}

void VWParametric_EventSink::SetUniversalName(const TXString& name)
{
	fUnivName	= name;
}

Sint32 VWParametric_EventSink::Execute(ParametricMessage* message)
{
	Sint32	reply	= kParametricNoErr;

	MCObjectHandle	saved_fhObject	= fhObject;

	fhObject		= message->fParametricHandle;

	if ( ! fbInitialized ) {
		this->InitializeExt();
		fbInitialized	= true;
	}

	switch ( message->fAction )
	{
		case ParametricRecalculate::kAction:
			reply	= (Sint32) this->Recalculate();
			break;
		case ParametricPreferencesMessage::kAction: {
				ParametricPreferencesMessage*	theMessage	= dynamic_cast<ParametricPreferencesMessage*>( message );
				ASSERTN( kVStanev, theMessage ); theMessage;

				reply	= (Sint32) this->Preference();
			} break;
		case ParametricInitXPropsMessage::kAction: {
				ParametricInitXPropsMessage*	theMessage	= dynamic_cast<ParametricInitXPropsMessage*>( message );
				if ( VERIFYN( kVStanev, theMessage ) )
				{
					reply	= (Sint32) this->OnInitXProperties( theMessage->fCodeRefID );
				}
			} break;
		case ParametricSpecialEditMessage::kAction: {
			ParametricSpecialEditMessage*		theMessage	= dynamic_cast<ParametricSpecialEditMessage*>( message );
				fObjectEditReason	= theMessage ? theMessage->fEditReason : kObjectEdit_ExplicitEdit;
				reply	= (Sint32) this->OnSpecialEditID(  theMessage->fEditResult );
			} break;
		case ParametricUIButtonHitMessage::kAction: {
				ParametricUIButtonHitMessage*	theMessage = dynamic_cast<ParametricUIButtonHitMessage*>( message );
				if ( VERIFYN( kVStanev, theMessage ) )
				{
					reply	= (Sint32) this->OnObjectUIButtonHit( theMessage->fButtonID );
				}
			} break;
		case OnObjectWidgetPrepCall::kAction: {
				OnObjectWidgetPrepCall* pThisCall		= dynamic_cast<OnObjectWidgetPrepCall*>( message );
				IWidgetsProvider*       pWidgetProvider = pThisCall ? (IWidgetsProvider*) pThisCall->fpWidgetProvider : nullptr;
				if ( pWidgetProvider && this->OnWidgetUpdate( pWidgetProvider ) ) {
					reply	= kObjectEventHandled;
				}
			} break;
		case ObjectState::kAction: {
				ObjectState*	pObjState	= dynamic_cast<ObjectState*>( message );
				if ( pObjState ) {
					reply	= (Sint32) this->OnAddState( *pObjState );
				}
			} break;
		case ParametricCursorMessage::kAction_Draw:
		case ParametricCursorMessage::kAction_MouseDown:
		case ParametricCursorMessage::kAction_Complete:
		case ParametricCursorMessage::kAction_Cancel:
		case ParametricCursorMessage::kAction_MouseMove:
		case ParametricCustomBarMessage::kAction_OnCursor:
			reply = this->OnCursorEvent( message );
			break;
		case ParametricDragMessage::kAction:
			reply = this->OnDrag( message );
			break;
		case ParametricGetToolNameMessage::kAction: {
				ParametricGetToolNameMessage*	theMessage = dynamic_cast<ParametricGetToolNameMessage*>( message );
				if ( VERIFYN( kVStanev, theMessage ) )
				{
					theMessage->fToolName	= this->OnGetToolName();
					if ( ! theMessage->fToolName.IsEmpty() ) {
						reply		= kObjectEventHandled;
					}
				}
			} break;
		case ObjectContextMenuEvent::kAction_Init: {
				const ObjectContextMenuEvent* pEventData           = dynamic_cast<const ObjectContextMenuEvent*>( message );
				IContextMenuProvider*         pContextMenuProvider = (pEventData && pEventData->fData)
																? (IContextMenuProvider*) pEventData->fData : nullptr;
				if ( pContextMenuProvider ) {
					this->OnContextMenuInit( pContextMenuProvider );
				}
			} break;
		case ObjectContextMenuEvent::kAction_Event: {
				const ObjectContextMenuEvent* pEventData    = dynamic_cast<const ObjectContextMenuEvent*>( message );
				if ( pEventData ) {
					this->OnContextMenuEvent( *pEventData );
				}
			} break;
		case ParametricEyeDropperMessage::kAction_PrepareCopy: {
				ParametricEyeDropperMessage*	theMessage = dynamic_cast<ParametricEyeDropperMessage*>( message );
				if ( VERIFYN( kVStanev, theMessage ) )
				{
					this->OnEyedropperPrepareCopy( theMessage->fRecordHandle );
				}
			} break;
		case ParametricEyeDropperMessage::kAction_AfterCopy: {
				ParametricEyeDropperMessage*	theMessage = dynamic_cast<ParametricEyeDropperMessage*>( message );
				if ( VERIFYN( kVStanev, theMessage ) )
				{
					this->OnEyedropperAfterCopy( theMessage->fSourceObjHandle );
				}
			} break;
		case ObjectGetSpecificGeometryCall::kAction: {
				ObjectGetSpecificGeometryCall*	data	= (ObjectGetSpecificGeometryCall*) message;
				if ( data ) {
					data->fhGeometry	= this->OnGetSpecificGeometry( (ObjectGetSpecificGeometryCall::ESpecifier) data->fSpecifier );
				}
			} break;
		case ParametricGetInCurtainWallMessage::kAction : {
				ParametricGetInCurtainWallMessage* data = (ParametricGetInCurtainWallMessage*) message;
				if ( data ) {
					data->fInCurtainWall = this->OnGetObjectInCurtainWall() ? 1 : 0;
				}
			} break;

		case ParametricSetObjectInCurtainWallMessage::kAction : {
			ParametricSetObjectInCurtainWallMessage* theMessage = dynamic_cast<ParametricSetObjectInCurtainWallMessage*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					this->OnSetObjectInCurtainWall( theMessage->fWidth, theMessage->fHeight, theMessage->fCenter, theMessage->fIndex );
				}																	
			} break;

		case ParametricGetQTOValue::kAction : {
			ParametricGetQTOValue* msg = dynamic_cast<ParametricGetQTOValue*>( message );

			if ( VERIFYN( kVStanev, msg) )
			{
				if ( this->OnQTOFunction( msg->fFunction, msg->fOption, msg->farrArguments, msg->fValue ) )
					reply = kObjectEventHandled;
			}
		} break;

		case ParametricCanEditAttrMessage::kAction : {
			ParametricCanEditAttrMessage* msg = dynamic_cast<ParametricCanEditAttrMessage*>(message);
			if ( VERIFYN(kAHiguera, msg) )
				this->OnAttributeQuery(*msg);
		} break;

		case ParametricSubtractPanelFromFrames::kAction : {
				ParametricSubtractPanelFromFrames* data = (ParametricSubtractPanelFromFrames*) message;
				if ( data ) {
					data->fSubtractPanelFromFrames = this->OnGetSubtractPanelFromFrames() ? 1 : 0;
				}
			} break;

		case OnObjectStyleWidgetPrepCall::kAction: {
				OnObjectStyleWidgetPrepCall* pThisCall		= dynamic_cast<OnObjectStyleWidgetPrepCall*>( message );
				IWidgetsProvider*		pWidgetProvider = pThisCall ? (IWidgetsProvider*) pThisCall->fpWidgetProvider : nullptr;
				bool					bHideStyleParameters = pThisCall ? (bool) pThisCall->fHideStyleParameters : FALSE;
				if ( pWidgetProvider && this->OnWidgetUpdateStyleParameters( pWidgetProvider, bHideStyleParameters ) ) {
					reply = kObjectEventHandled;
				}
				else {
					reply = kObjectEventNotHandled;
				}
			} break;

		case ParametricValidateReplacePluginStyle::kAction: {
			ParametricValidateReplacePluginStyle* theMessage = dynamic_cast<ParametricValidateReplacePluginStyle*>(message);
			if ( VERIFYN( kJWarshaw, theMessage ) ) {
				reply = this->OnValidateReplacePluginStyle( theMessage->fSymDefHandle );
			}
		} break;

		case ParametricEditPluginStyle::kAction : {
					ParametricEditPluginStyle* theMessage = dynamic_cast<ParametricEditPluginStyle*>( message );
					if ( VERIFYN( kJWarshaw, theMessage ) ) {
						reply = this->OnEditPluginStyle( theMessage->fSymDefHandle );
					}
				} break;


		case ParametricCreatePluginStyle::kAction : {
				ParametricCreatePluginStyle* theMessage = dynamic_cast<ParametricCreatePluginStyle*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnCreatePluginStyle( theMessage->fSymDefHandle );
				}
			} break;

		case ParametricStyleMessage::kAction_FinalizeCreateStyle : {
				ParametricStyleMessage* theMessage = dynamic_cast<ParametricStyleMessage*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnFinalizeCreatePluginStyle( theMessage->fSymDefHandle );
				}
			} break;

		case ParametricStyleMessage::kAction_FinalizeUpdateStyledObject : {
				ParametricStyleMessage* theMessage = dynamic_cast<ParametricStyleMessage*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnFinalizeUpdateStyledObject( theMessage->fSymDefHandle );
				}
			} break;

		case ParametricStyleMessage::kAction_BeginStyledObjectsUpdate: {
			ParametricStyleMessage* theMessage = dynamic_cast<ParametricStyleMessage*>(message);
			if ( VERIFYN( kJWarshaw, theMessage ) ) {
				reply = this->OnBeginStyledObjectsUpdate( theMessage->fSymDefHandle );
			}
		} break;

		case ParametricStyleMessage::kAction_EndStyledObjectsUpdate: {
			ParametricStyleMessage* theMessage = dynamic_cast<ParametricStyleMessage*>(message);
			if ( VERIFYN( kJWarshaw, theMessage ) ) {
				reply = this->OnEndStyledObjectsUpdate( theMessage->fSymDefHandle );
			}
		} break;

		case ParametricStyleMessage::kAction_FinalizeUpdateStyle: {
			ParametricStyleMessage* theMessage = dynamic_cast<ParametricStyleMessage*>(message);
			if ( VERIFYN( kIBorisov, theMessage ) ) {
				reply = this->OnFinalizeUpdateStyle( theMessage->fSymDefHandle );
			}
		} break;

		case ParametricGetStyleFolder::kAction: {
			ParametricGetStyleFolder* theMessage = dynamic_cast<ParametricGetStyleFolder*>(message);
			if ( VERIFYN( kNZhelyazkov, theMessage ) ) {
				if ( this->OnGetStyleFolder( theMessage->fStyleFolderName ) )
				{
					reply = EObjectEvent::kObjectEventNoErr;
				}
				else
				{
					reply = EObjectEvent::kObjectEventSetupFailed;
				}
			}
		} break;


		case ParametricStyleMessage::kAciton_ForwardTranslateStyleToVW22 : {
				ParametricStyleMessage* theMessage = dynamic_cast<ParametricStyleMessage*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnForwardTranslateStyleToVW22( theMessage->fSymDefHandle );
				}
			} break;


		case ParametricUpdatePluginStyleObject::kAction : {
				ParametricUpdatePluginStyleObject* theMessage = dynamic_cast<ParametricUpdatePluginStyleObject*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnUpdateStyledObject( theMessage->fSymDefHandle );
				}
			} break;

		case ParametricStyleWidgetChosen::kAction: {
				ParametricStyleWidgetChosen* theMessage = dynamic_cast<ParametricStyleWidgetChosen*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnStyleWidgetChosen( theMessage->fItemChosen );
				}
			} break;


		case ParametricGetUsingLayerCutPlane::kAction : {
				ParametricGetUsingLayerCutPlane * theMessage = dynamic_cast<ParametricGetUsingLayerCutPlane*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					theMessage->fUsingLayerCutPlane = this->IsUsingLayerCutPlane() ? 1 : 0;
				}
			} break;

		case ParametricAllowWorksheetEdit::kAction: {
				ParametricAllowWorksheetEdit * theMessage = dynamic_cast<ParametricAllowWorksheetEdit*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					theMessage->fAllowEdit = this->AllowWorksheetEdit( theMessage->fFieldName ) ? 1 : 0;
				}
			} break;

		case ParametricGetCatalogPath::kAction: {
				ParametricGetCatalogPath * theMessage = dynamic_cast<ParametricGetCatalogPath*>( message );
				if ( VERIFYN( kJWarshaw, theMessage ) ) {
					reply = this->OnGetCatalogPath( theMessage->fFolderSpecifier, theMessage->fRelativePath ); 
				}
			} break;
		
		case ObjectCommand::kAction:
			{
				ObjectCommand* theMessage = dynamic_cast<ObjectCommand*>(message);
				if ( VERIFYN( kYKostadinov, theMessage ) )
				{
					bool	handleMatrixTransform	= ( theMessage->fSpecifier == ObjectCommand::kOnMatrixTransform );
					if ( handleMatrixTransform )
					{
						reply	= this->OnModifyObjectCommand( *( (TransformMatrix*) theMessage->fData ) );
					}
					
					if ( ! handleMatrixTransform || reply == kObjectEventNotImplemented )
					{
						reply	= this->OnDefaultEvent( message );
					}
					else
					{
						// convert the EObjectEvent to the core event handling constants.
						reply	= ( reply == kObjectEventNoErr ) ? kObjectEventHandled : kObjectEventNotHandled;
					}
				}
			} break;

		case ParametricGetCustomBounds::kAction:
			{
				ParametricGetCustomBounds * theMessage = dynamic_cast<ParametricGetCustomBounds*>( message );
				if ( VERIFYN( kKIvanov, theMessage ) )
				{
					if ( this->OnGetCustomBounds( theMessage->fBounds ) )
					{
						reply = kObjectEventHandled;
					}
					else
					{
						reply = kObjectEventNotHandled;
					}
				}
			} break;

		default:
			reply = this->OnDefaultEvent( message );
			break;
	}

	fhObject	= saved_fhObject;

	return reply;
}

// The Plug-in Object code should re-create all its component objects using current parameter values.
EObjectEvent VWParametric_EventSink::Recalculate()
{
	return kObjectEventNoErr;
}

// Object Definition Procedure (ODP) may optionally present its own preferences dialog, or let VW pose the default dialog.
EObjectEvent VWParametric_EventSink::Preference()
{
	return kObjectEventNotImplemented;
}

// The Plug-in Object may add extended properties.
EObjectEvent VWParametric_EventSink::OnInitXProperties(CodeRefID /*objectID*/)
{
	return kObjectEventNoErr;
}

// The Plug-in Object called with kParametricOnMove when kHasMoveDependancy extended property set
EObjectEvent VWParametric_EventSink::OnSpecialEditID(TObjectEditResult& outResult)
{
	EObjectEvent result = kObjectEventPrefCancel;
	EObjectEvent eventRet = this->OnSpecialEditID();
	switch ( eventRet )
	{
		// meaningful results
		case kObjectEventPrefOK:
		case kObjectEventUIButtonOK:
			outResult	= kObjectEditResult_DoNothing;
			result		= kObjectEventNoErr;
			break;

		case kObjectEventPrefCancel:
			outResult	= kObjectEditResult_DoNothing;
			result		= kObjectEventPrefCancel;
			break;

		case kObjectEventUIButtonPreventReset:
			outResult	= kObjectEditResult_DoNothing;
			result		= kObjectEventUIButtonPreventReset;
			break;
		case kObjectEventSetupFailed:
			break;
		case kObjectEventError:
			break;
		case kObjectEventNotImplemented:
			break;
		case kObjectEventHadError:
			break;
		case kObjectEventHadWarning:
			break;
		case kObjectEventStayLoaded:
			break;
		default:
			DSTOP((kNZhelyazkov, "Misssing a case"));
	}

	return result;
}

EObjectEvent VWParametric_EventSink::OnSpecialEditID()
{
	return kObjectEventNoErr;
}

// The user has pressed a button in the Properties UI of an object
EObjectEvent VWParametric_EventSink::OnObjectUIButtonHit(Sint32 /*buttonID*/)
{
	return kObjectEventNoErr;
}

bool VWParametric_EventSink::OnWidgetUpdate(IWidgetsProvider* pWidgetProvider)
{
	return false;
}

bool VWParametric_EventSink::OnWidgetUpdateStyleParameters(IWidgetsProvider* pWidgetProvider, bool hideStyleParameters )
{
	return false;
}


EObjectEvent VWParametric_EventSink::OnAddState(ObjectState& stateInfo)
{
	return kObjectEventNoErr;
}

Sint32 VWParametric_EventSink::OnCursorEvent(ParametricMessage* message)
{
    return(kObjectEventNotHandled);
}

Sint32 VWParametric_EventSink::OnDrag(ParametricMessage* message)
{
    return(kObjectEventNotHandled);
}

Sint32 VWParametric_EventSink::OnDefaultEvent(ParametricMessage* message)
{
	return 0;
}

TXString VWParametric_EventSink::OnGetToolName() const
{
	return TXString();
}

void VWParametric_EventSink::OnContextMenuInit(IContextMenuProvider* pContextMenuProvider)
{
}

void VWParametric_EventSink::OnContextMenuEvent(const ObjectContextMenuEvent& eventData)
{
}

void VWParametric_EventSink::OnEyedropperPrepareCopy(MCObjectHandle hObjRecordCopy)
{
}

void VWParametric_EventSink::OnEyedropperAfterCopy(MCObjectHandle hObjRecordCopy)
{
}

MCObjectHandle VWParametric_EventSink::OnGetSpecificGeometry(ObjectGetSpecificGeometryCall::ESpecifier geomType)
{
	return nullptr;
}

bool VWParametric_EventSink::OnGetObjectInCurtainWall()
{
	return false;
}

void VWParametric_EventSink::OnSetObjectInCurtainWall( double width, double height, WorldPt& center, Sint32 index )
{
}

bool VWParametric_EventSink::OnGetSubtractPanelFromFrames()
{
	return false;
}

EObjectEvent VWParametric_EventSink::OnCreatePluginStyle( MCObjectHandle symDefHandle )
{
	return kObjectEventNotImplemented;
}

EObjectEvent VWParametric_EventSink::OnFinalizeCreatePluginStyle( MCObjectHandle symDefHandle )
{
	return kObjectEventNoErr;
}

EObjectEvent VWParametric_EventSink::OnForwardTranslateStyleToVW22( MCObjectHandle symDefHandle )
{
	return kObjectEventNoErr;
}

EObjectEvent VWParametric_EventSink::OnValidateReplacePluginStyle( MCObjectHandle symDefHandle )
{
	return kObjectEventNotImplemented;
}

EObjectEvent VWParametric_EventSink::OnEditPluginStyle( MCObjectHandle symDefHandle )
{
	return kObjectEventNoErr;
}

EObjectEvent VWParametric_EventSink::OnBeginStyledObjectsUpdate( MCObjectHandle symDefHandle )
{
	return kObjectEventNotImplemented;
}

EObjectEvent VWParametric_EventSink::OnUpdateStyledObject( MCObjectHandle symDefHandle )
{
	return kObjectEventNotImplemented;
}

EObjectEvent VWParametric_EventSink::OnFinalizeUpdateStyledObject( MCObjectHandle symDefHandle )
{
	return kObjectEventNoErr;
}

EObjectEvent VWParametric_EventSink::OnEndStyledObjectsUpdate( MCObjectHandle symDefHandle )
{
	return kObjectEventNotImplemented;
}

EObjectEvent VWParametric_EventSink::OnFinalizeUpdateStyle( MCObjectHandle symDefHandle )
{
	return kObjectEventNoErr;
}

bool VWParametric_EventSink::OnGetStyleFolder(TXString& outStyleFolderName)
{
	return false;
}


bool VWParametric_EventSink::IsUsingLayerCutPlane()
{
	return false;
}

EObjectEvent VWParametric_EventSink::OnStyleWidgetChosen( int itemChosen )
{
	return kObjectEventNotImplemented;
}

bool VWParametric_EventSink::AllowWorksheetEdit( const TXString & fieldName )
{
	return true;
}

void VWParametric_EventSink::OnAttributeQuery(ParametricCanEditAttrMessage& msg)
{
	// ParametricCanEditAttrMessage default constructor is such that all
	// controls enabled in attribute pane unless object overrides.
}

bool VWParametric_EventSink::OnQTOFunction(EQTOFunction function, const TXString& option, const std::vector<VWVariant>& args, VWVariant& outResult) 
{
	// not handled
	return false;
}

EObjectEvent VWParametric_EventSink::OnGetCatalogPath( EFolderSpecifier & outFolderSpecifier, TXString & outRelativePath )
{
	return kObjectEventNotImplemented;
}

EObjectEvent VWParametric_EventSink::OnModifyObjectCommand( const TransformMatrix& transformMat )
{
	return kObjectEventNotImplemented;
}
