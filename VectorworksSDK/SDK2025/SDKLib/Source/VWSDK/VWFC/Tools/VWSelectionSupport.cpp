//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

using namespace VWFC::Tools;

// ------------------------------------------------------------------------------------------------

VWSelectionSupport::SSelectionInfo::SSelectionInfo()
{
	key.Clear();
	determinate = true;
	edited = false;
	value.Clear();
	fIsFlagsParameter	= false;
	fDeterminateFlags	= 0;
	fEditedFlags		= 0;
	fFlagsValue			= 0;
	fFlags.clear();
}

VWSelectionSupport::SSelectionInfo::~SSelectionInfo()
{
}



VWSelectionSupport::VWSelectionSupport()
{
}

VWSelectionSupport::~VWSelectionSupport()
{
}

THandleUSet VWSelectionSupport::GetSelection() const
{
	return fSelectedObjects;
}

bool VWSelectionSupport::InitFromParametricObject( MCObjectHandle hObject )
{
	fSelectedObjects.clear();
	fmapSelectionInfo.clear();

	bool bReturn = true;
	if ( VWParametricObj::IsParametricObject( hObject ) == false ) {
		bReturn = false;
	}
	
	if ( bReturn ) {
		VWParametricObj	paramObj( hObject );
		fhHostObject	= hObject;
		fStyleID		= paramObj.GetStyleRefNumber();
		fSelectedObjects.insert( hObject );

		for ( size_t index = 0, paramCount = paramObj.GetParamsCount(); index < paramCount; index++ ) {
		
			TXString strName = paramObj.GetParamName( index );

			SSelectionInfo sInfo;
			sInfo.key = strName;
			sInfo.value = paramObj.GetParamValue( strName );
		
			fmapSelectionInfo.insert( TSelectionInfo_Pair( strName, sInfo ) );

		}
	}

	return bReturn;
}

bool VWSelectionSupport::CompareToParametricObject( MCObjectHandle hObject )
{
	bool bReturn = true;
	if ( VWParametricObj::IsParametricObject( hObject ) == false ) {
		bReturn = false;
	}

	if ( bReturn && hObject == fhHostObject ) {
		bReturn = false;
	}

	if ( bReturn && fmapSelectionInfo.empty() ) {
		bReturn = false;
	}

	
	if ( bReturn ) {
		VWParametricObj paramObj( hObject );

		fStyleID = (fStyleID == paramObj.GetStyleRefNumber()) ? fStyleID : kHeterogeneousStyles;
		fSelectedObjects.insert( hObject );

		for ( size_t index = 0, paramCount = paramObj.GetParamsCount(); index < paramCount; index++ ) {
		
			TXString strName = paramObj.GetParamName( index );
			TXString newValue = paramObj.GetParamValue( strName );
			
			TSelectionInfo_Iterator iter = fmapSelectionInfo.find( strName );
			if ( iter != fmapSelectionInfo.end() ) {			
			
				if ( newValue != iter->second.value ) {
					iter->second.determinate = false;
				}
				
				if( iter->second.fIsFlagsParameter && !iter->second.fFlags.empty() )
				{
					Sint32	newFlagsValue	= paramObj.GetParamLong( strName );
					size_t	len				= iter->second.fFlags.size();
					for( size_t i = 0; i < len; ++i )
					{
						TValueFlags&	currentFlag		= iter->second.fFlags[ i ];
						Sint32			newObjFlag		= newFlagsValue & currentFlag;
						Sint32			paramObjFlag	= iter->second.fFlagsValue & currentFlag;

						// "Exclude" non-determinate flags.
						if( paramObjFlag != newObjFlag )
						{
							iter->second.fDeterminateFlags &= ~currentFlag;
						}
					}
				}
			}
		}
	}

	return bReturn;
}

bool VWSelectionSupport::UpdateValuesFromParametricObject( MCObjectHandle hObject ) 
{
	bool bReturn = true;
	if ( VWParametricObj::IsParametricObject( hObject ) == false ) {
		bReturn = false;
	}

	if ( bReturn && fmapSelectionInfo.empty() ) {
		bReturn = false;
	}

	
	if ( bReturn ) {
		VWParametricObj paramObj( hObject );

		size_t paramCount = paramObj.GetParamsCount();

		for ( size_t index = 0; index < paramCount; index++ ) {
		
			TXString strName = paramObj.GetParamName( index );
			TXString newValue = paramObj.GetParamValue( strName );
			
			TSelectionInfo_Iterator iter = fmapSelectionInfo.find( strName );
			if ( iter != fmapSelectionInfo.end() ) {			
			
				iter->second.value = newValue;

				if( iter->second.fIsFlagsParameter )
				{
					iter->second.fFlagsValue = paramObj.GetParamLong( strName );
				}
			}
		

		}
	}

	return bReturn;
}

bool VWSelectionSupport::UpdateParametric(MCObjectHandle hObject, bool updateSourceObj/* = false*/) const
{
	bool bReturn = VWParametricObj::IsParametricObject( hObject ) && !fmapSelectionInfo.empty();

	if ( bReturn && hObject == fhHostObject )
	{
		bReturn = updateSourceObj;
	}

	if ( bReturn )
	{
		bReturn = false;

		// check if target object is styled
		VWParametricObj	paramObj( hObject );
		MCObjectHandle	styleHandle	= paramObj.GetStyleHandle();
		bool			isStyled	= false;
		VWStyleSupport	styleSupport;

		if ( styleHandle != nullptr )
		{
			isStyled = styleSupport.InitFromSymbolDefinition( styleHandle );
		}

		// use for checking it parameter can be updateted - may be excluded due to style/catalog
		EPluginStyleParameter	styleType			= kPluginStyleParameter_ByInstance;

		for ( const auto& iter : fmapSelectionInfo )
		{
			// check if parameter exists
			if ( paramObj.GetParamIndex( iter.first ) != ((size_t) -1) )
			{
				// always default to ByInstance to allow updating non-styled objects
				styleType			= kPluginStyleParameter_ByInstance;

				// check for style typing
				if ( isStyled )
				{
					styleSupport.GetStyleType( iter.first, styleType );

					if ( styleSupport.IsCatalogParam( iter.first ) )
					{
						styleType = kPluginStyleParameter_ByCatalog;
					}
				}

				if ( styleType == kPluginStyleParameter_ByInstance ) // can update parameter
				{
					if ( iter.second.fIsFlagsParameter && !iter.second.fFlags.empty() )
					{
						Sint32	flagsValue	= paramObj.GetParamLong( iter.first );

						for ( const TValueFlags& flagValueIter : iter.second.fFlags )
						{
							if ( iter.second.fEditedFlags & flagValueIter )
							{
								flagsValue &= ~flagValueIter;
								if ( iter.second.fFlagsValue & flagValueIter )
								{
									flagsValue |= flagValueIter;
								}
							}
						}

						paramObj.SetParamLong( iter.first, flagsValue );
					}
					else if ( iter.second.edited )
					{
						paramObj.SetParamValue( iter.first, iter.second.value );
						bReturn = true;
					}
				}
			}
		}
	}

	return bReturn;
}

bool VWSelectionSupport::SetFlagsParameter( MCObjectHandle hObject, const TXString& key, const TFlagsArray& flags )
{
	bool isOK = true;

	if ( key.IsEmpty() )
	{
		isOK = false;
	}

	if ( isOK )
	{
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() )
		{			
			iter->second.fIsFlagsParameter	= true;

			VWParametricObj paramObj( hObject );
			iter->second.fFlagsValue		= paramObj.GetParamLong( key );

			if( !iter->second.fFlags.empty() )
			{
				iter->second.fFlags.clear();
			}

			size_t len = flags.size();
			for( size_t i = 0; i < len; ++i )
			{
				iter->second.fFlags.push_back( flags[i] );

				// Initially include all flags as determinate, later non-determinate flags will be "excluded".
				iter->second.fDeterminateFlags |= flags[i];
			}
		}
		else
		{
			isOK = false;
		}
	}
	return isOK;
}

void VWSelectionSupport::Clear()
{
	fmapSelectionInfo.clear();
}

void VWSelectionSupport::AddRawDataKey(const TXString& key, bool determinate)
{
	TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
	if ( iter == fmapSelectionInfo.end() )
	{
		SSelectionInfo sInfo;
		sInfo.key = key;
		sInfo.determinate = determinate;
		
		fmapSelectionInfo.insert( TSelectionInfo_Pair( key, sInfo ) );
	}
	else
	{
		iter->second.determinate = determinate;
	}
}

void VWSelectionSupport::SetRawDataKey(const TXString& key, const TXString& compareValue)
{
	TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
	if ( iter == fmapSelectionInfo.end() )
	{
		SSelectionInfo sInfo;
		sInfo.key = key;
		sInfo.value = compareValue;
		
		fmapSelectionInfo.insert( TSelectionInfo_Pair( key, sInfo ) );
	}
	else
	{
		if ( compareValue != iter->second.value )
		{
			iter->second.determinate = false;
		}
	}
}

void VWSelectionSupport::SetRawDataKey(const TXString& key, const Sint32& compareValue)
{
	TXString	strCompareValue;
	strCompareValue.Format( "%d", compareValue );
	this->SetRawDataKey( key, strCompareValue );
}

void VWSelectionSupport::SetRawDataKey(const TXString& key, const Uint32& compareValue)
{
	TXString	strCompareValue;
	strCompareValue.Format( "%d", compareValue );
	this->SetRawDataKey( key, strCompareValue );
}

void VWSelectionSupport::SetRawDataKey(const TXString& key, const double& compareValue)
{
	TXString	strCompareValue;
	strCompareValue.Format( "%.5f", compareValue );
	this->SetRawDataKey( key, strCompareValue );
}

bool VWSelectionSupport::GetRawDataModifed(const TXString& key)
{
	TSelectionInfo_Iterator iter	= fmapSelectionInfo.find( key );
	return iter != fmapSelectionInfo.end() ? iter->second.edited : false;
}

bool VWSelectionSupport::IsDeterminate(const TXString& key, bool & determinate, TValueFlags flag )
{
	bool bReturn = true;
	determinate = true;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {
			if( iter->second.fIsFlagsParameter && flag != 0 )
			{
				determinate = iter->second.fDeterminateFlags & flag;
			}
			else
			{
				determinate = iter->second.determinate;
			}
		}
		else {
			bReturn = false;
		}
	}
	
	return bReturn;
}

bool VWSelectionSupport::SetDeterminate(const TXString& key, bool determinate, TValueFlags flag )
{
	bool bReturn = true;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {			
			iter->second.determinate = determinate;

			if( iter->second.fIsFlagsParameter && flag != 0 )
			{
				if( determinate )
				{
					iter->second.fDeterminateFlags |= flag;
				}
				else
				{
					iter->second.fDeterminateFlags &= ~flag;
				}
			}
		}
		else {
			bReturn = false;
		}
	}
	return true;
}

bool VWSelectionSupport::IsEdited(const TXString& key, bool & edited, TValueFlags flag )
{
	bool bReturn = true;
	edited = true;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {
			if( iter->second.fIsFlagsParameter && flag != 0 )
			{
				edited = iter->second.fEditedFlags & flag;
			}
			else
			{
				edited = iter->second.edited;
			}
		}
		else {
			bReturn = false;
		}
	}
	
	return bReturn;
}

bool VWSelectionSupport::SetEdited(const TXString& key, bool edited, TValueFlags flag )
{
	bool bReturn = true;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {			
			iter->second.edited = edited;

			if( iter->second.fIsFlagsParameter && flag != 0 )
			{
				if( edited )
				{
					iter->second.fEditedFlags |= flag;
				}
				else
				{
					iter->second.fEditedFlags &= ~flag;
				}
			}
		}
		else {
			bReturn = false;
		}
	}
	return true;
}

void VWSelectionSupport::OnStyleChange(MCObjectHandle hSymDef)
{
	fStyleID = gSDK->GetObjectInternalIndex( hSymDef );

	if ( hSymDef )
	{
		this->SetEditedOnStyleChange( hSymDef );
	}
}

void VWSelectionSupport::SetEditedOnStyleChange(MCObjectHandle hSymDef)
{
	const VWStyleSupport	styleSupport( hSymDef );

	// For each parameter: if locked for editing (by style/catalog) - mark as determinate AND edited.
	for ( auto& [key, selInfo] : fmapSelectionInfo )
	{
		if ( !styleSupport.CanEditParameter( key ) )
		{
			selInfo.determinate	= true;
			selInfo.edited		= true;
		}
	}
}

bool VWSelectionSupport::IsStyleHomogeneousMultiSel() const
{
	// Determine if style selection is homogeneous
	//	a) single selection
	//	b) multiple selection with homogeneous style (id > 0) or all unstyled (id = -1)

	return fStyleID != kHeterogeneousStyles;
}

bool VWSelectionSupport::GetValue(const TXString& key, TXString & value )
{
	bool bReturn = true;
	value.Clear();

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {			
			value = iter->second.value;
		}
		else {
			bReturn = false;
		}
	}
	
	return bReturn;
}

bool VWSelectionSupport::SetValue(const TXString& key, const TXString& value)
{
	bool bReturn = true;

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {			
			iter->second.value = value;
		}
		else {
			bReturn = false;
		}
	}
	return true;
}

bool VWSelectionSupport::AddItem(const TXString& key, const TXString& value, bool determinate, bool edited )
{
	SSelectionInfo sInfo;
		
	sInfo.key = value;
	sInfo.determinate = determinate;
	sInfo.edited = edited;
	sInfo.value = value;
			
	bool bReturn = true;
	TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
	if ( iter == fmapSelectionInfo.end() ) {			
		fmapSelectionInfo.insert( TSelectionInfo_Pair( key, sInfo ) );
	}
	else {	
		bReturn = false;		
	}

	return bReturn;
	
}

bool VWSelectionSupport::KeyExists(const TXString& key )
{
	bool bReturn = false;
	
	if ( key.IsEmpty() == false ) {	
		TSelectionInfo_Iterator iter = fmapSelectionInfo.find( key );
		if ( iter != fmapSelectionInfo.end() ) {			
			bReturn = true;
		}
	}

	return bReturn;
}

Sint32	VWSelectionSupport::GetItemCount()
{
	return (Sint32) fmapSelectionInfo.size();
}

MCObjectHandle VWSelectionSupport::GetHostObject()
{
	return fhHostObject;
}
