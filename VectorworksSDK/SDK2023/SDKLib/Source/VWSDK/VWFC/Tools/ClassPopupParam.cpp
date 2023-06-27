//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CClassPopupParam::CClassPopupParam()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CClassPopupParam::CClassPopupParam( const CClassPopupParam& inClassPopupParam )
: fstrRecordName( inClassPopupParam.fstrRecordName )
, fstrActualName( inClassPopupParam.fstrActualName )
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CClassPopupParam::~CClassPopupParam()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::Set( const TXString& strActualOrRecordName, const TXString& strObjClassName /*= TXString()*/ )
{
	if ( strActualOrRecordName.IsEmpty() ) {
		fstrRecordName.Clear();
		if ( strObjClassName.IsEmpty() ) {
			const VWClass defaultClass( VWClass::GetDefaultClass() );
			fstrActualName = VWAutoClassing::GetUserClass( defaultClass.GetName() );
		}
		else {
			fstrActualName = strObjClassName;
		}
	}
	else {
		fstrRecordName = VWAutoClassing::GetRefClass( strActualOrRecordName );
		this->ObtainActualClass( fstrActualName, fstrRecordName, strObjClassName );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::Set( const TXString& strActualOrRecordName, MCObjectHandle hParametricObj )
{
	TXString strObjClassUserName;
	if ( (NULL != hParametricObj) && VWParametricObj::IsParametricObject( hParametricObj ) ) {
		gSDK->ClassIDToName( gSDK->GetObjectClass( hParametricObj ), strObjClassUserName );
	}
	else {
		const VWClass defaultClass( VWClass::GetDefaultClass() );
		strObjClassUserName = VWAutoClassing::GetUserClass( defaultClass.GetName() );
	}

	this->Set( strActualOrRecordName, strObjClassUserName );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::Read( MCObjectHandle hParametricObj, const TXString& strUnivParamName )
{
	if ( (NULL != hParametricObj) && VWParametricObj::IsParametricObject( hParametricObj ) ) {
		VWParametricObj prmObj( hParametricObj );
		if ( kFieldClassesPopup == prmObj.GetParamStyle( strUnivParamName ) ) {
			this->Set( prmObj.GetParamString( strUnivParamName ), hParametricObj );
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::Write( MCObjectHandle hObj, const TXString& strUnivParamName ) const
{
	if ( NULL != hObj ) {
		const short nObjType = gSDK->GetObjectTypeN( hObj );
		if ( kParametricNode == nObjType ) {
			VWParametricObj obj( hObj );
			if ( kFieldClassesPopup == obj.GetParamStyle( strUnivParamName ) ) {
				obj.SetParamString( strUnivParamName, fstrRecordName );
			}
		}
		else if ( kFormatNode == nObjType ) {
			VWRecordFormatObj obj( hObj );
			if ( kFieldClassesPopup == obj.GetParamStyle( strUnivParamName ) ) {
				obj.SetParamString( strUnivParamName, fstrRecordName );
			}
		}
		else if ( kRecordNode == nObjType ) {
			VWRecordObj obj( hObj );
			if ( kFieldClassesPopup == obj.GetParamStyle( strUnivParamName ) ) {
				obj.SetParamString( strUnivParamName, fstrRecordName );
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::Process
(	CParamProviderAbstract&	paramProvider,
	const bool				bRead,
	const CClassPopupParam&	cppPrev,
	const size_t			nParamIndex,
	const TXString&			strObjClassName )
{
	paramProvider.ProcessParameter( bRead, fstrRecordName, cppPrev.fstrRecordName, nParamIndex );
	if ( bRead ) {
		const TXString strNewRecName = fstrRecordName;
		this->Set( strNewRecName, strObjClassName );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::Process
(	CParamProviderAbstract&	paramProvider,
 	const bool				bRead,
 	const CClassPopupParam&	cppPrev,
 	const size_t			nParamIndex,
 	MCObjectHandle			hParametricObj )
{
	paramProvider.ProcessParameter( bRead, fstrRecordName, cppPrev.fstrRecordName, nParamIndex );
	if ( bRead ) {
		const TXString strNewRecName = fstrRecordName;
		this->Set( strNewRecName, hParametricObj );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::ObtainActualClass( TXString& strOutClassNameActual, TXString& strInOutClassNameFromRec, const TXString& strObjectClass )
{
	strOutClassNameActual = strInOutClassNameFromRec;
	bool bUseObjectClass = false;
	if ( strInOutClassNameFromRec.IsEmpty() ) {
		bUseObjectClass = true;
	}
	else {
		VWAutoClassing::GetUserClassName( strInOutClassNameFromRec, strOutClassNameActual );
		MCObjectHandle hNamedObject = gSDK->GetNamedObject( strOutClassNameActual );
		if ( NULL == hNamedObject ) {
			// Default to the <Door Class> if the class creation was unsuccessful.
			bUseObjectClass = (0 == gSDK->AddClass( strOutClassNameActual ));
		}
		else if	( kClassDefNode != gSDK->GetObjectTypeN( hNamedObject ) ) {
			// Default to the <Door Class> if the name of the class is occupied by another object type.
			bUseObjectClass = true;
		}
	}

	if ( bUseObjectClass ) {
		strOutClassNameActual = strObjectClass;
		if ( ! strInOutClassNameFromRec.IsEmpty() ) {
			strInOutClassNameFromRec.Clear();
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CClassPopupParam& CClassPopupParam::operator=(const CClassPopupParam& inClassPopupParam)
{
	fstrRecordName = inClassPopupParam.fstrRecordName;
	fstrActualName = inClassPopupParam.fstrActualName;

	return *this;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
bool CClassPopupParam::AreRecordClassNamesEqual( const CClassPopupParam& inClassPopupParam ) const
{
	return fstrRecordName == inClassPopupParam.fstrRecordName;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
bool CClassPopupParam::AreActualClassNamesEqual( const CClassPopupParam& inClassPopupParam ) const
{
	return fstrActualName == inClassPopupParam.fstrActualName;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
bool CClassPopupParam::operator==( const CClassPopupParam& inClassPopupParam ) const
{
	return 
		fstrRecordName == inClassPopupParam.fstrRecordName &&
		fstrActualName == inClassPopupParam.fstrActualName;

}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
bool CClassPopupParam::operator!=( const CClassPopupParam& inClassPopupParam ) const
{
	return *this == inClassPopupParam;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
bool CClassPopupParam::IsObjectClassUsed() const
{
	return fstrRecordName.IsEmpty();
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::UseObjectClass( MCObjectHandle hParametricObj )
{
	TXString strObjClassUserName;
	if ( (NULL != hParametricObj) && VWParametricObj::IsParametricObject( hParametricObj ) ) {
		gSDK->ClassIDToName( gSDK->GetObjectClass( hParametricObj ), strObjClassUserName );
	}

	this->UseObjectClass( strObjClassUserName );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParam::UseObjectClass( const TXString& strInObjectClassName )
{
	fstrRecordName.Clear();
	if ( strInObjectClassName.IsEmpty() ) {
		const VWClass defaultClass( VWClass::GetDefaultClass() );
		fstrActualName = VWAutoClassing::GetUserClass( defaultClass.GetName() );
	}
	else {
		fstrActualName = strInObjectClassName;
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
/* static */ void CClassPopupParam::ConvertClassPopupObjDataToDlgData
(	TXString&				strOutDlgChoice,
 	short&					nOutChoice,
 	const CClassPopupParam&	inRecChoice,
 	const short&			nInUseObjClassLabelPos,
 	const TXString&			strInUseObjClassLabel )
{
	if ( inRecChoice.IsObjectClassUsed() ) {
		nOutChoice = nInUseObjClassLabelPos;
		strOutDlgChoice = strInUseObjClassLabel;
	}
	else {
		nOutChoice = -1;
		strOutDlgChoice = inRecChoice.GetActualClassName();
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
/* static */ void CClassPopupParam::ConvertClassPopupDlgDataToObjData
(	CClassPopupParam&	outRecChoice,
 	const TXString&		strInDlgChoice,
 	const short&		nInChoice,
 	const short&		nInUseObjClassLabelPos,
 	const TXString&		strObjClassName )
{
	if ( nInUseObjClassLabelPos == nInChoice ) {
		outRecChoice.UseObjectClass( strObjClassName );
	}
	else {
		outRecChoice.Set( strInDlgChoice );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
/* static */ void CClassPopupParam::ConvertClassPopupDlgDataToObjData
(	CClassPopupParam&	outRecChoice,
	const TXString&		strInDlgChoice,
	const short&		nInChoice,
	const short&		nInUseObjClassLabelPos,
	MCObjectHandle		hParametricObj )
{
	if ( nInUseObjClassLabelPos == nInChoice ) {
		outRecChoice.UseObjectClass( hParametricObj );
	}
	else {
		outRecChoice.Set( strInDlgChoice );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
/* static */ void CClassPopupParam::ConvertClassPopupObjDataToDlgData
(	TXString&		strOutDlgChoice,
 	short&			nOutChoice,
 	const TXString&	strInRecChoice,
 	const TXString& strInUseObjectClassLabelChoice,
 	const short		nInUseObjectClassLabelChoice )
{
	if ( strInRecChoice.IsEmpty() ) {
		nOutChoice		= nInUseObjectClassLabelChoice;
		strOutDlgChoice	= strInUseObjectClassLabelChoice;
	}
	else {
		nOutChoice		= -1; // initialize the classes pop-up control by the string ddx data, not by the index one
		strOutDlgChoice	= strInRecChoice;
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
/* static */ void CClassPopupParam::ConvertClassPopupDlgDataToObjData
(	TXString&		strOutRecChoice,
 	const TXString&	strInDlgChoice,
 	const short&	nInChoice,
 	const short		nInUseObjectClassLabelChoice )
{
	if ( nInUseObjectClassLabelChoice == nInChoice ) {
		strOutRecChoice.Clear();
	}
	else {
		strOutRecChoice = strInDlgChoice;
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// CClassPopupParamUpdater tool class implementation
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/*static*/ const size_t CClassPopupParamUpdater::fsknInitParamsCount = 32;
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CClassPopupParamUpdater::CClassPopupParamUpdater()
: fiterClassNamePairsEnd( fOldNewClassNamesMap.end() ) // std::map never invalidates its iterators.
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CClassPopupParamUpdater::~CClassPopupParamUpdater()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParamUpdater::AddClassNamePair( const TXString& strClassNameOld, const TXString& strClassNameNew )
{
	fOldNewClassNamesMap.insert(
		TOldNewClassNamePairsSTLMap::value_type(
			VWAutoClassing::GetRefClass( strClassNameOld ),
			VWAutoClassing::GetRefClass( strClassNameNew ) ) );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParamUpdater::Update
( MCObjectHandle hObj /* = gSDK->GetDrawingHeader() */
)
{
	if ( ! fOldNewClassNamesMap.empty() ) {
		this->UpdateClassPopupFields( hObj );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParamUpdater::UpdateClassPopupFields
( MCObjectHandle hObj /* = gSDK->GetDrawingHeader() */
)
{
	short nObjType = kTermNode;
	for	(	;
			( NULL		!= hObj ) &&
			( kTermNode	!= ( nObjType = gSDK->GetObjectTypeN( hObj ) ) );
			hObj = gSDK->NextObject( hObj )
		)
	{
		this->UpdateClassPopupFields( gSDK->FirstAuxObject( hObj ) );
		this->UpdateClassPopupFields( gSDK->FirstMemberObj( hObj ) );

		if ( kRecordNode == nObjType ) {
			VWFC::VWObjects::VWRecordObj recObj( hObj );
			if ( recObj.IsParametric() ) {
				const size_t nNumFields = recObj.GetParamsCount();
				for (	size_t i = 0 ;
						i < nNumFields;
						++ i )
				{
					if ( kFieldClassesPopup == recObj.GetParamStyle( i ) ) {
						if ( fiterClassNamePairsEnd != ( fiterClassNamePairsFound = fOldNewClassNamesMap.find( recObj.GetParamString( i ) ) ) ) {
							recObj.SetParamString( i, fiterClassNamePairsFound->second );
						}
					}
				}
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParamUpdater::CollectRecordsFormatsParametrics
( MCObjectHandle hObj /* = gSDK->GetDrawingHeader() */
)
{
	if ( ! fOldNewClassNamesMap.empty() ) {
		this->Collect( hObj );
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParamUpdater::Collect
( MCObjectHandle hObj /* = gSDK->GetDrawingHeader() */
)
{
	short nObjType = kTermNode;
	for	(	;
			( NULL		!= hObj ) &&
			( kTermNode	!= ( nObjType = gSDK->GetObjectTypeN( hObj ) ) );
			hObj = gSDK->NextObject( hObj ) )
	{
		this->Collect( gSDK->FirstAuxObject( hObj ) );
		this->Collect( gSDK->FirstMemberObj( hObj ) );

		if	( kRecordNode == nObjType ) {
			VWFC::VWObjects::VWRecordObj recObj( hObj );
			if ( recObj.IsParametric() ) {
				bool			bDoesntHaveClsPopups	= true;
				const size_t	nNumFields				= recObj.GetParamsCount();
				for (	size_t i = 0;
						i < nNumFields;
						++ i )
				{
					if ( kFieldClassesPopup == recObj.GetParamStyle( i ) ) {
						if ( fiterClassNamePairsEnd != ( fiterClassNamePairsFound = fOldNewClassNamesMap.find( recObj.GetParamString( i ) ) ) ) {
							if ( bDoesntHaveClsPopups ) {
								fiterRecObjsBack = farrRecObjs.insert( farrRecObjs.end(), TRecHandParamsToUpdatePair( hObj, TParamIDNewClassNamePtrVect() ) );
								fiterRecObjsBack->second.reserve( fsknInitParamsCount );
								
								farrPrmRecObjsParents.push_back( gSDK->AuxOwner( hObj ) );
								bDoesntHaveClsPopups = false;
							}
							fiterRecObjsBack->second.push_back( TParamIDNewClassNamePtrPair( i, & fiterClassNamePairsFound->second ) );
						}
					}
				}
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
void CClassPopupParamUpdater::UpdateCollectedRecords() const
{
	const size_t	nNumRecObjs	= farrRecObjs.size();
	
	size_t			nNumChoices	= 0;
	size_t			j			= 0;
	for (	size_t i = 0;
			i < nNumRecObjs;
			++ i )
	{
		const TRecHandParamsToUpdatePair& recHandParamInfoPair = farrRecObjs[i];
		VWFC::VWObjects::VWRecordObj recObj( recHandParamInfoPair.first );

		const TParamIDNewClassNamePtrVect& arrParamsInfo = recHandParamInfoPair.second;
		nNumChoices = arrParamsInfo.size();
		for (	j = 0;
				j < nNumChoices;
				++ j )
		{
			const TParamIDNewClassNamePtrPair& paramInfo = arrParamsInfo[j];
			recObj.SetParamString( paramInfo.first, *paramInfo.second );
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
const VWFC::VWObjects::TMCObjectHandlesSTLArray& CClassPopupParamUpdater::GetCollectedFormatsParametrics() const
{
	return farrPrmRecObjsParents;
}
