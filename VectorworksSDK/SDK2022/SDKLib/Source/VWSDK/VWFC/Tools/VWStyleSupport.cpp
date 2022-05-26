//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;

#define kCatalogGroup_Name		0
#define kCatalogGroup_ParamList 1
#define kCatalogGroup_KeyList	2
#define kCatalogGroup_DescList	3
#define kCatalogGroup_CatItem	4
	#define kCatItem_ByStyle	0
	
const OSType kPluginStyleAttachedCatalogDataTag		= 'PSAC';
const OSType kPluginCatalogListDataTag				= 'CTLG';


// ------------------------------------------------------------------------------------------------

VWStyleSupport::SStyleInfo::SStyleInfo()
{
	key.Clear();
	paramIndex = 0;
	styleType = kPluginStyleParameter_ByInstance;
	catalogParameter = false;

}

VWStyleSupport::SStyleInfo::~SStyleInfo()
{
}

VWStyleSupport::SStyleEditList::SStyleEditList()
{
	key.Clear();
	displayName.Clear();
	paramIndex = 0;
	editListType = kPluginStyleEditList_Unused;

}

VWStyleSupport::SStyleEditList::~SStyleEditList()
{
}



VWStyleSupport::VWStyleSupport()
{
	fhHostSymbolDefiniiton = NULL;
	fhHostParametricObject = NULL;

	fSupportsCatalogs = false;
	fCatItemByStyle = false;
}

VWStyleSupport::~VWStyleSupport()
{
}

MCObjectHandle VWStyleSupport::GetStyleSourceObject()
{
	return fhHostParametricObject;
}

void VWStyleSupport::ClearStyleSupport()
{
	fhHostSymbolDefiniiton = NULL;
	fhHostParametricObject = NULL;

	fSupportsCatalogs = false;
	fCatItemByStyle = false;
	fmapStyleInfo.clear();
	fmapStyleEditList.clear();
}


bool VWStyleSupport::InitFromSymbolDefinition( MCObjectHandle hObject )
{
	fmapStyleInfo.clear();

	bool bReturn = true;
	if ( VWSymbolDefObj::IsSymbolDefObject( hObject ) == false ) {
		bReturn = false;
	}
	else {
		fhHostSymbolDefiniiton = hObject;
		bReturn = this->FindPluginObject();
	}

	
	if ( bReturn ) {
		VWSymbolDefObj styleDefNode( hObject );
		VWParametricObj paramObj( fhHostParametricObject );

		VWDataSerializerSimple ser( fhHostSymbolDefiniiton, 'PSMP' );
		ser.Load();
		size_t groupCount = ser.GetGroupCount();

		if ( groupCount > 0 ) {
			TXString strName;
			SStyleInfo sInfo;
			for ( short index = 1; index <= groupCount; index++ ) {
		
				if ( ser.GetValueOutTXString( index, kPluginStyleMapPosition_ParameterName, strName ) ) {
					sInfo.key = strName;				
					sInfo.paramIndex = paramObj.GetParamIndex( strName );
					if ( sInfo.paramIndex == (size_t)-1 ) {
						sInfo.paramIndex = 0;
					}
					sInfo.styleType = ser.GetValueEnum( index, kPluginStyleMapPosition_StyleType, kPluginStyleParameter_ByInstance );
					fmapStyleInfo.insert( TStyleInfo_Pair( strName, sInfo ) );
				}
			}
		}
		else {
			size_t numOfFields = paramObj.GetParamsCount();
			TXString name;
			SStyleInfo sInfo;
			for (size_t i = 0; i <= numOfFields; i++) {			
				name = paramObj.GetParamName( i );
				sInfo.key = name;
				sInfo.paramIndex = i;
				sInfo.styleType = kPluginStyleParameter_ByInstance;
				fmapStyleInfo.insert( TStyleInfo_Pair( name, sInfo ) );
				
			}
			this->UpdateSymbolDefinition();
		}

		this->LoadEditList();

		this->LoadCatalogList();


	}

	return bReturn;
}

void VWStyleSupport::LoadEditList()
{
	if ( fhHostSymbolDefiniiton == NULL || fhHostParametricObject == NULL ) {
		return;
	}

	fmapStyleEditList.clear();

	VWParametricObj paramObj( fhHostParametricObject );

	VWDataSerializerSimple serEditList( fhHostSymbolDefiniiton, 'PSEL' );

	serEditList.Load();
	size_t groupCount = serEditList.GetGroupCount();
	if ( groupCount > 0 ) {
		for ( short index = 1; index <= groupCount; index++ ) {
			TXString strName;
			if ( serEditList.GetValueOutTXString( index, kPluginStyleMapEditListPosition_ParameterName, strName ) ) {
				SStyleEditList sEditList;
				sEditList.key = strName;
				sEditList.paramIndex = paramObj.GetParamIndex( strName );
				sEditList.editListType = serEditList.GetValueEnum( index, kPluginStyleMapEditListPosition_EditListType, kPluginStyleEditList_Unused );
				sEditList.displayName = serEditList.GetValueTXString( index, kPluginStyleMapEditListPosition_DisplayName, strName );
				fmapStyleEditList.insert( TStyleEditList_Pair( strName, sEditList ) );
			}

		}
	}

}

void VWStyleSupport::LoadCatalogList()
{
	bool supportsCatalogs = false;

	using namespace VectorWorks::Extension;
	IExtendedPropsPtr		extProps( IID_ExtendedProps );
	extProps->GetObjectProperty( fhHostParametricObject, kObjXCatalogSupport, supportsCatalogs );

	if ( supportsCatalogs ) {
		VWCatalogSupport cat;
		cat.LoadCatalogList( fhHostSymbolDefiniiton );

		for ( auto iter = fmapStyleInfo.begin( ) ; iter != fmapStyleInfo.end( ); iter++ ) {
			iter->second.catalogParameter = false;
		}

		for ( size_t i = 0; i < cat.fCatParamList.GetSize(); i++ ) {
			auto it  = fmapStyleInfo.find( cat.fCatParamList[i] );
			if ( it !=  fmapStyleInfo.end() ) {
				it->second.catalogParameter = true;
			}

		}

		fCatItemByStyle = cat.GetCatalogItemByStyle();
		fSupportsCatalogs = true;

	}


	
}

void VWStyleSupport::SetUnstyled()
{
	fhHostParametricObject = NULL;
	fhHostSymbolDefiniiton = NULL;

	TStyleInfo_Iterator iter;
	for ( iter = fmapStyleInfo.begin( ) ; iter != fmapStyleInfo.end( ); iter++ ) {
		iter->second.styleType = kPluginStyleParameter_ByInstance;
		iter->second.catalogParameter = false;
	}

}


bool VWStyleSupport::CreateUnstyledMap( MCObjectHandle hObject )
{
	fmapStyleInfo.clear();
	fhHostSymbolDefiniiton = NULL;

	if ( hObject == NULL ) return false;

	VWParametricObj paramObj( hObject );
	size_t numOfFields = paramObj.GetParamsCount();
	
	for (size_t i = 0; i <= numOfFields; i++) {			
		TXString name = paramObj.GetParamName( i );
		SStyleInfo sInfo;
		sInfo.key = name;
		sInfo.paramIndex = i;
		sInfo.styleType = kPluginStyleParameter_ByInstance;
		fmapStyleInfo.insert( TStyleInfo_Pair( name, sInfo ) );
	}


	return true;
}

bool VWStyleSupport::SetAllStyleTypes( EPluginStyleParameter styleType )
{
	if ( fhHostSymbolDefiniiton == NULL ) {
		return false;
	}

	TStyleInfo_Iterator iter;
	for ( iter = fmapStyleInfo.begin( ) ; iter != fmapStyleInfo.end( ); iter++ ) {
		iter->second.styleType = styleType;
	}

	return true;
}

bool VWStyleSupport::UpdateSymbolDefinition()
{
	if ( fhHostSymbolDefiniiton == NULL ) {
		return false;
	}

	VWDataSerializerSimple ser( fhHostSymbolDefiniiton, 'PSMP' );

	ser.Load();
	ser.Clear();

	short index = 1;
	TStyleInfo_Iterator iter;
	for ( iter = fmapStyleInfo.begin() ; iter != fmapStyleInfo.end(); iter++ ) {
		ser.SetValueTXString( index, 0, iter->second.key );
		ser.SetValueEnum( index, 1, iter->second.styleType );
		index++;
	}

	bool bReturn = ser.Save();

	VWDataSerializerSimple serEdit( fhHostSymbolDefiniiton, 'PSEL' );

	serEdit.Load();
	serEdit.Clear();

	if ( fmapStyleEditList.size() > 0 ) {
		short index = 1;
		TStyleEditList_Iterator iterEdit;
		for ( iterEdit = fmapStyleEditList.begin() ; iterEdit != fmapStyleEditList.end(); iterEdit++ ) {
			serEdit.SetValueTXString( index, kPluginStyleMapEditListPosition_ParameterName, iterEdit->second.key );
			serEdit.SetValueEnum( index, kPluginStyleMapEditListPosition_EditListType, iterEdit->second.editListType );
			serEdit.SetValueTXString( index, kPluginStyleMapEditListPosition_DisplayName, iterEdit->second.displayName );
			index++;
		}
	}
	serEdit.Save();


	return bReturn;
	
}

TXString VWStyleSupport::GetStyleName()
{
	TXString styleName;
	if ( fhHostSymbolDefiniiton != NULL ) {
		gSDK->GetObjectName( fhHostSymbolDefiniiton, styleName );
	}
	return styleName;
}

RefNumber VWStyleSupport::GetStyleRefNumber()
{
	RefNumber refNum = 0;
	if ( fhHostSymbolDefiniiton != NULL ) {
		gSDK->NameToInternalIndexN( this->GetStyleName(), refNum );
	}
	return refNum;
}

void VWStyleSupport::SetStyleName( const TXString& styleName )
{	
	gSDK->SetObjectName( fhHostSymbolDefiniiton, styleName );
}

bool VWStyleSupport::GetStyleType(const TXString& key, EPluginStyleParameter & styleType ) const
{
	bool bReturn = true;
	styleType = kPluginStyleParameter_ByInstance;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		auto iter = fmapStyleInfo.find( key );
		if ( iter != fmapStyleInfo.end() ) {
			styleType = iter->second.styleType;
		}
		else {
			bReturn = false;
		}
	}
	
	return bReturn;
}

bool VWStyleSupport::IsCatalogParam( const TXString& key )
{
	bool bReturn = false;
	
	if ( key.IsEmpty() == false ) {
		TStyleInfo_Iterator iter = fmapStyleInfo.find( key );
		if ( iter != fmapStyleInfo.end() ) {
			if ( iter->second.catalogParameter ) {
				return true;
			}
		}
	}
	
	return bReturn;
}

bool VWStyleSupport::IsCatalogParamByParamIndex( const size_t index )
{
	bool bReturn = false;

	if ( index > 0 ) {
		VWParametricObj pObj( fhHostParametricObject );
		TXString name = pObj.GetParamName( index - 1 );
		bReturn = IsCatalogParam( name );
	}

	return bReturn;

}

bool VWStyleSupport::GetStyleTypeByParamIndex( const size_t index,  EPluginStyleParameter & styleType)
{
	bool bReturn = true;
	styleType = kPluginStyleParameter_ByInstance;

	if ( index <= 0 ) {
		bReturn = false;
	}

	if ( bReturn ) {
		VWParametricObj pObj( fhHostParametricObject );
		TXString name = pObj.GetParamName( index - 1 );
		bReturn = GetStyleType( name, styleType );
	}
			
	return bReturn;
}

bool VWStyleSupport::SetStyleType(const TXString& key, EPluginStyleParameter styleType )
{
	bool bReturn = true;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TStyleInfo_Iterator iter = fmapStyleInfo.find( key );
		if ( iter != fmapStyleInfo.end() ) {			
			iter->second.styleType = styleType;

		}
		else {
			bReturn = false;
		}
	}
	return bReturn;
}

bool VWStyleSupport::SetStyleTypeByParamIndex(const size_t index, EPluginStyleParameter styleType )
{
	bool bReturn = true;

	if ( index <= 0 ) {
		bReturn = false;
	}

	if ( bReturn ) {
		VWParametricObj pObj( fhHostParametricObject );
		TXString name = pObj.GetParamName( index - 1 );
		bReturn = SetStyleType( name, styleType );
	}
	return bReturn;
}

bool VWStyleSupport::CanChangeParamWithoutConflicts(const TXString& key, bool editingAStyle, std::function<bool()> newValueIsSameAsOld) const
{
	EPluginStyleParameter	parameterStyleType;

	return editingAStyle			// if editing a style
		|| !this->GetStyleType( key, parameterStyleType )	// or the parameter is not in the style map
		|| setmember( parameterStyleType, kPluginStyleParameter_ByInstance, kPluginStyleParameter_AllwaysByInstance )	// or the parameter is by instance
		|| !newValueIsSameAsOld		// or the value doesn't need checking
		|| newValueIsSameAsOld();	// or the new value matches the old one
}


bool VWStyleSupport::AddItem( const TXString& key, EPluginStyleParameter styleType, bool saveStyle )
{
	if ( fhHostSymbolDefiniiton == NULL ) {
		return false;
	}


	SStyleInfo sInfo;		
	sInfo.styleType = styleType;
	sInfo.key = key;
			
	bool bReturn = true;
	TStyleInfo_Iterator iter = fmapStyleInfo.find( key );
	if ( iter == fmapStyleInfo.end() ) {			
		fmapStyleInfo.insert( TStyleInfo_Pair( key, sInfo ) );

		if ( saveStyle ) {
			VWDataSerializerSimple ser( fhHostSymbolDefiniiton, 'PSMP' );
			ser.Load();

			size_t count = ser.GetGroupCount();
			short groupID = (short)count + 1;
			ser.SetValueTXString( groupID, kPluginStyleMapPosition_ParameterName, key );
			ser.SetValueEnum( groupID, kPluginStyleMapPosition_StyleType, styleType );
			bReturn = ser.Save();
		}

	}
	else {	
		bReturn = false;		
	}

	return bReturn;
	
}

bool VWStyleSupport::RemoveItem( const TXString& key )
{
	if ( fhHostSymbolDefiniiton == NULL ) {
		return false;
	}

	bool bReturn = false;
	TStyleInfo_Iterator iter = fmapStyleInfo.find( key );
	if ( iter  != fmapStyleInfo.end() ) {
		fmapStyleInfo.erase( iter );
		bReturn = UpdateSymbolDefinition();
			
	}

	return bReturn;
}

bool VWStyleSupport::FindPluginObject()
{
	fhHostParametricObject = nil;

	VWSymbolDefObj symDef( fhHostSymbolDefiniiton );
	/*if ( symDef.HasPluginStyleSupport() == false ) {
		return false;
	}*/

	bool foundBadSymbol = false;

	// Search symdefnode's sublist, looking for Plug-in Object and no other nodes except maybe UndoPlaceholders.
	short numberOfParametrics = 0; 
	for ( VWObjectIterator symIter = symDef.GetFirstMemberIterator() ;  symIter.GetType() != kTermNode ; symIter++ ) {
		if ( symIter.GetType() == kParametricNode ){ 
			fhHostParametricObject = symIter.GetObject();
			numberOfParametrics++;
			if (numberOfParametrics > 1) {
				foundBadSymbol = true;
				fhHostParametricObject = NULL;
			}
		}
		else if ( symIter.GetType() != kUndoPlaceholderNode) {
			foundBadSymbol = true;
		}
	}
	

	if ( (fhHostParametricObject != NULL) && (foundBadSymbol == false) ) {
		return true;
	}
		
	return false;

}

bool VWStyleSupport::KeyExists( const TXString& key )
{
	bool bReturn = false;
	if ( fmapStyleInfo.size() > 0 ) {
	
		TStyleInfo_Iterator iter = fmapStyleInfo.find( key );
		if ( iter != fmapStyleInfo.end() ) {	
			bReturn = true;
		}
	}
			
	return bReturn;
}

bool VWStyleSupport::AddItemToEditList( const TXString& key, EPluginStyleEditList editListType, const TXString& displayName )
{
	if ( fhHostSymbolDefiniiton == NULL ) {
		return false;
	}

	VWParametricObj paramObj( fhHostParametricObject );

	VWDataSerializerSimple ser( fhHostSymbolDefiniiton, 'PSEL' );
	ser.Load();

	SStyleEditList sEditInfo;		
	sEditInfo.editListType = editListType;
	sEditInfo.key = key;
	if ( displayName.IsEmpty() == false ) {
		sEditInfo.displayName = displayName;
	}
	else {
		sEditInfo.displayName = key;
	}
	sEditInfo.paramIndex = paramObj.GetParamIndex( key );

	bool bReturn = true;
	TStyleEditList_Iterator iter = fmapStyleEditList.find( key );
	if ( iter == fmapStyleEditList.end() ) {			
		fmapStyleEditList.insert( TStyleEditList_Pair( key, sEditInfo ) );
		size_t count = ser.GetGroupCount();
		short groupID = (short)count + 1; 
		ser.SetValueTXString( groupID, kPluginStyleMapEditListPosition_ParameterName, key ); 
		ser.SetValueEnum( groupID, kPluginStyleMapEditListPosition_EditListType, editListType );
		ser.SetValueTXString( groupID, kPluginStyleMapEditListPosition_DisplayName, sEditInfo.displayName );
		bReturn = ser.Save();

	}
	else if ( editListType == kPluginSytleEditList_NewDisplayName ) {
		iter->second.displayName = displayName;
		bReturn = UpdateSymbolDefinition();
	}
	else {	
		bReturn = false;		
	}

	return bReturn;

}

bool VWStyleSupport::RemoveItemFromEditList( const TXString& key )
{
	if ( fhHostSymbolDefiniiton == NULL ) {
		return false;
	}

	bool bReturn = false;
	TStyleEditList_Iterator iter = fmapStyleEditList.find( key );
	if ( iter  != fmapStyleEditList.end() ) {
		fmapStyleEditList.erase( iter );
		bReturn = UpdateSymbolDefinition();
			
	}

	return bReturn;

}

bool VWStyleSupport::GetStyleEditListType( const TXString& key, EPluginStyleEditList & editListType, TXString & displayName )
{
	bool bReturn = true;
	editListType = kPluginStyleEditList_Unused;
	displayName.Clear();

	if ( fhHostSymbolDefiniiton == NULL || fhHostParametricObject == NULL ) {
		bReturn = false;
	}

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TStyleEditList_Iterator iter = fmapStyleEditList.find( key );
		if ( iter != fmapStyleEditList.end() ) {
			editListType = iter->second.editListType;
			displayName = iter->second.displayName;
			bReturn = true;
		}
		else {
			bReturn = false;
		}
	}
	
	return bReturn;
}

bool VWStyleSupport::GetStyleEditListTypeByParamIndex( const size_t index, EPluginStyleEditList & editListType, TXString & displayName )
{
	bool bReturn = true;
	editListType = kPluginStyleEditList_Unused;
	displayName.Clear();

	if ( fhHostSymbolDefiniiton == NULL || fhHostParametricObject == NULL ) {
		bReturn = false;
	}

	if ( index <= 0 ) {
		bReturn = false;
	}

	if ( bReturn ) {
		VWParametricObj pObj( fhHostParametricObject );
		TXString name = pObj.GetParamName( index - 1 );
		bReturn = GetStyleEditListType( name, editListType, displayName );
	}
	return bReturn;

}

bool VWStyleSupport::KeyExistsInEditList( const TXString& key )
{
	bool bReturn = false;
	if ( fmapStyleEditList.size() > 0 ) {
	
		TStyleEditList_Iterator iter = fmapStyleEditList.find( key );
		if ( iter != fmapStyleEditList.end() ) {	
			bReturn = true;
		}
	}
			
	return bReturn;

}

// ------------------------------------------------------------------------------------------------
//
// VWCatalogSupport
//
// ------------------------------------------------------------------------------------------------

VWCatalogSupport::VWCatalogSupport()
{
	fHostObject = NULL;
	fCatParamList.Clear();
	fCatalogName.Clear();
	fCatKeyList.Clear();
	fCatDescList.Clear();
	fCatItemByStyle = false;
}

VWCatalogSupport::~VWCatalogSupport()
{
}

bool VWCatalogSupport::LoadCatalogList( MCObjectHandle hObject )
{
	if ( hObject == NULL ) {
		ASSERTN( kJWarshaw, FALSE );
		return false;
	}

	fHostObject = hObject;

	MCObjectHandle hSymDefObj;
	MCObjectHandle hParamObj;

	if ( VWParametricObj::IsParametricObject( hObject ) ) {
		hParamObj = hObject;
		gSDK->GetPluginStyleSymbol( hObject, hSymDefObj );

	}
	else if ( VWSymbolDefObj::IsSymbolDefObject( hObject ) ) {
		hSymDefObj = hObject;
	}
	else {
		ASSERTN( kJWarshaw, FALSE );
		return false;
	}

	if (fHostObject == NULL || hSymDefObj == NULL) {
		return false;
	}

	VWDataSerializerSimple ser( hSymDefObj, kPluginStyleAttachedCatalogDataTag );
	if ( ser.Load() ) {
		ser.GetValueOutTXString( kCatalogGroup_Name, 0, fCatalogName );

		fCatParamList.Clear();
		size_t i = 0;
		bool getNext = true;
		while ( getNext ) {
			if ( ser.HasValue( kCatalogGroup_ParamList, i ) )  {
				TXString param = ser.GetValueTXString( kCatalogGroup_ParamList, i, "" );
				if ( param.IsEmpty() == false ) {
					fCatParamList.Append( param );
					i++;
				}
				else {
					getNext = false;
				}
			}
			else {
				getNext = false;
			}
		}		

		fCatKeyList.Clear();
		i = 0;
		getNext = true;
		while ( getNext ) {
			if ( ser.HasValue( kCatalogGroup_KeyList, i ) )  {
				TXString param = ser.GetValueTXString( kCatalogGroup_KeyList, i, "" );
				if ( param.IsEmpty() == false ) {
					fCatKeyList.Append( param );
					i++;
				}
				else {
					getNext = false;
				}
			}
			else {
				getNext = false;
			}
		}		


		fCatDescList.Clear();
		i = 0;
		getNext = true;
		while ( getNext ) {
			if ( ser.HasValue( kCatalogGroup_DescList, i ) )  {
				TXString param = ser.GetValueTXString( kCatalogGroup_DescList, i, "" );
				if ( param.IsEmpty() == false ) {
					fCatDescList.Append( param );
					i++;
				}
				else {
					getNext = false;
				}
			}
			else {
				getNext = false;
			}
		}

		fCatItemByStyle = false;
		if ( ser.HasValue( kCatalogGroup_CatItem, kCatItem_ByStyle ) ) {
			fCatItemByStyle = ser.GetValueBool( kCatalogGroup_CatItem, kCatItem_ByStyle, false );
		}
	}
	else
	{
		// Catalogs not supported.
		return false;
	}

	return true;
}

void VWCatalogSupport::SetCatalogName( const TXString & catalogName )
{
	fCatalogName = catalogName;
}

TXString VWCatalogSupport::GetCatalogName()
{
	return fCatalogName;
}

bool VWCatalogSupport::SaveCatalogList()
{
	MCObjectHandle hSymDefObj = nullptr;

	if ( VWParametricObj::IsParametricObject( fHostObject ) ) {
		gSDK->GetPluginStyleSymbol( fHostObject, hSymDefObj );

	}
	else if ( VWSymbolDefObj::IsSymbolDefObject( fHostObject ) ) {
		hSymDefObj = fHostObject;
	}

	VWDataSerializerSimple ser( hSymDefObj, kPluginStyleAttachedCatalogDataTag );
	ser.Clear();
	ser.SetValueTXString( kCatalogGroup_Name, 0, fCatalogName );

	for ( size_t i = 0; i < fCatParamList.GetSize(); i++ ) {
		ser.SetValueTXString( kCatalogGroup_ParamList, i, fCatParamList[i] );
	}

	for ( size_t i = 0; i < fCatKeyList.GetSize(); i++ ) {
		ser.SetValueTXString( kCatalogGroup_KeyList, i, fCatKeyList[i] );
	}

	for ( size_t i = 0; i < fCatDescList.GetSize(); i++ ) {
		ser.SetValueTXString( kCatalogGroup_DescList, i, fCatDescList[i] );
	}

	ser.SetValueBool( kCatalogGroup_CatItem, kCatItem_ByStyle, fCatItemByStyle );

	return ser.Save();
}

bool VWCatalogSupport::ClearCatalogList()
{
	fCatalogName.Clear();
	fCatParamList.Clear();
	fCatKeyList.Clear();
	fCatDescList.Clear();
	return true;
}

TXString VWCatalogSupport::BuildCatalogItemName( MCObjectHandle hInObject )
{
	TXString itemName = "";
	bool bContinue = true;

	MCObjectHandle hObj = fHostObject;
	if ( hInObject != NULL ) {
		hObj = hInObject;
	}
	
	if ( hObj == NULL ) {
		bContinue = false;
	}
	else if ( VWParametricObj::IsParametricObject( hObj ) == false ) {
		bContinue = false;
	}

	if ( bContinue ) {
		VWParametricObj obj( hObj );
		if ( fCatDescList.GetSize() > 0 ) {
			TXString paramValue = obj.GetParamValue( fCatDescList[0] );
			itemName = paramValue; 
			for ( size_t i = 1; i < fCatDescList.GetSize(); i++ ) {
				paramValue = obj.GetParamValue( fCatDescList[i] );
				if ( paramValue.IsEmpty() == false ) {
					itemName+= ", ";
					itemName+= paramValue;
				}
			}

		}
	
		else if ( fCatKeyList.GetSize() > 0 ) {
			TXString paramValue = obj.GetParamValue( fCatKeyList[0] );
			itemName = paramValue; 
			for ( size_t i = 1; i < fCatKeyList.GetSize(); i++ ) {
				paramValue = obj.GetParamValue( fCatKeyList[i] );
				if ( paramValue.IsEmpty() == false ) {
					itemName+= ", ";
					itemName+= paramValue;
				}
			}

		}
	}

	if ( itemName.IsEmpty() ) {
		itemName = TXResource( "Vectorworks/Strings/SelectCatalog.vwstrings", "NoCatalogItem" );
	}

	if ( itemName.FindNotOneOf( "-, " ) == -1 ) {
		itemName = TXResource( "Vectorworks/Strings/SelectCatalog.vwstrings", "NoCatalogItem" );;
	}

	return itemName;
}

bool VWCatalogSupport::IsCatalogParam( const TXString & paramName )
{
	bool bReturn = false;
	ASSERTN( kJWarshaw, paramName.IsEmpty() == false );
	ASSERTN( kJWarshaw, fCatalogName.IsEmpty() == false );

	for ( size_t i = 0; i < fCatParamList.GetSize(); i++ ) {
		if ( paramName.EqualNoCase( fCatParamList[i] )  ) {
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

bool VWCatalogSupport::GetCatalogItemByStyle()
{
	return fCatItemByStyle;
}

void VWCatalogSupport::SetCatalogItemByStyle( const bool & catItemByStyle )
{
	fCatItemByStyle = catItemByStyle;
}
								
using namespace VectorWorks::Filing;
/////////////////////////////////////////////////////////////////////////////////////////
class CatalogFolderContentListener : IFolderContentListener
{
public:
	VWListBrowserCtrl * fpListBrower;
	VWPullDownMenuCtrl * fpPullDown;
	TXStringArray * fpXMLNames;
	TXStringArray * fpTXTNames;
	virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFolderContent(IFolderIdentifier* pFolderID);
	virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFileContent(IFileIdentifier* pFileID);
};

EFolderContentListenerResult CatalogFolderContentListener::OnFolderContent(IFolderIdentifier* pFolderID)
{
	return eFolderContentListenerResult_Continue;
}

EFolderContentListenerResult CatalogFolderContentListener::OnFileContent(IFileIdentifier* pFileID)
{

	TXString txFileName;
	TXString txExtension;
	pFileID->GetFileExtension(txExtension);
	txExtension.MakeUpper();
	pFileID->GetFileNameWithoutExtension(txFileName);
	if (txExtension == "XML") {
		fpXMLNames->Append(txFileName);
	}
	else if (txExtension == "TXT") {
		fpTXTNames->Append(txFileName);
	}


	return eFolderContentListenerResult_Continue;
}


size_t	VWCatalogSupport::FillCatalogList( MCObjectHandle hParamObj, VWListBrowserCtrl * fpListBrower, VWPullDownMenuCtrl * fpPullDown)
{
	size_t catCount = 0;
	TXStringArray		fXMLCatalogNames;
	TXStringArray		fTXTCatalogNames;


	if (hParamObj == NULL) {
		ASSERTN(kJWarshaw, false);
		return false;
	}


	EFolderSpecifier folderSpec = kObjectStylesFolder;
	TXString relativePath;

	CatalogFolderContentListener fListener;

	gSDK->GetCatalogPath(hParamObj, folderSpec, relativePath);

	fListener.fpXMLNames = &fXMLCatalogNames;
	fListener.fpTXTNames = &fTXTCatalogNames;

	IApplicationFoldersPtr	appFolders(IID_ApplicationFolders);
	appFolders->ForEachFileInStandardFolderN(folderSpec, relativePath, ETraverse::NonRecursively_IncludeWorkgroupFolders, (IFolderContentListener*)&fListener);

	catCount = fXMLCatalogNames.GetSize();

	for (size_t i = 0; i < catCount; i++) {
		TXString catalogName;
		catalogName = fXMLCatalogNames[i];
		if (fTXTCatalogNames.Find(catalogName, true) != -1) {
			if (fpPullDown) {
				fpPullDown->AddItem(catalogName);
			
			}

		}
	}

	if (catCount > 0 && fCatalogName.IsEmpty() == false) {
		if (fpPullDown) {
			fpPullDown->SelectItem(fCatalogName);
		}
	}

	return catCount;
}
