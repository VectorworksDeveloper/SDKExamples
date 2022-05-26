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
# include "VWFC//PluginSupport/VWExtensionMenu.h"

using namespace VWFC::PluginSupport;

// --------------------------------------------------------------------------------------------------------
VWExtensionMenu::VWExtensionMenu(	CallBackPtr cbp,
									const SMenuDef& menuDef,
									const SMenuChunkDef* arrMenuChunks,
									EMenuChunkType chunkType)
	: fCBP( cbp )
	, fNeeds			( menuDef.fNeeds			 )
	, fNeedsNot			( menuDef.fNeedsNot			 )
	, fVersionCreated	( menuDef.fVersionCreated	 )
	, fVersoinModified	( menuDef.fVersoinModified	 )
	, fVersoinRetired	( menuDef.fVersoinRetired	 )
	, fLegacyEventSink( NULL )
	, fMenuChunkSink( NULL )
	, fProtectionObtained( false )
	, fHasProtection( false )
	, fProtectionSink( NULL )
	, fMenuChunkType( chunkType )
	, fMenuChunkIsDirty( false )
{
	gCBP			= fCBP;
	fstrTitle		= TXResStr( menuDef.fTitle.fResNameWithoutPathOrExtension, menuDef.fTitle.fStringIdentifier );
	fstrCategory	= TXResStr( menuDef.fCategory.fResNameWithoutPathOrExtension, menuDef.fCategory.fStringIdentifier );
	fstrHelp		= TXResStr( menuDef.fHelpText.fResNameWithoutPathOrExtension, menuDef.fHelpText.fStringIdentifier );


	const SMenuChunkDef* currChunk	= arrMenuChunks;
	while(currChunk && currChunk->fItemText.fResNameWithoutPathOrExtension && currChunk->fItemText.fStringIdentifier)
	{
		SChunkInfo	item;
		item.fItem				= TXResStr( currChunk->fItemText.fResNameWithoutPathOrExtension, currChunk->fItemText.fStringIdentifier );
		if (currChunk->fOverrideHelpID)
		{
			item.fOverrideHelpID	= currChunk->fOverrideHelpID;
		}

		if ( item.fItem != "-" )
		{
			item.fHelpText =  TXResStr( currChunk->fHelpText.fResNameWithoutPathOrExtension, currChunk->fHelpText.fStringIdentifier );
		}

		farrSubItems.push_back( item );

		++currChunk;
	}

	if ( menuDef.fOverrideHelpID ) {
		fstrOverrideHelpID	= menuDef.fOverrideHelpID;
	}
	else 
		fstrOverrideHelpID = txu(""); // no help associated
}

VWExtensionMenu::VWExtensionMenu(	CallBackPtr				cbp,
									const SMenuDef_Legacy&			menuDef,
									const SMenuChunkDef_Legacy*	arrMenuChunks,
									EMenuChunkType			chunkType)
	: fCBP( cbp )
	, fNeeds			( menuDef.fNeeds			 )
	, fNeedsNot			( menuDef.fNeedsNot			 )
	, fVersionCreated	( menuDef.fVersionCreated	 )
	, fVersoinModified	( menuDef.fVersoinModified	 )
	, fVersoinRetired	( menuDef.fVersoinRetired	 )
	, fLegacyEventSink( NULL )
	, fMenuChunkSink( NULL )
	, fProtectionObtained( false )
	, fHasProtection( false )
	, fProtectionSink( NULL )
	, fMenuChunkType( chunkType )
	, fMenuChunkIsDirty( false )
{
	gCBP			= fCBP;
	fstrTitle = TXLegacyResource( menuDef.fTitle.fListID, menuDef.fTitle.fIndex );
	fstrCategory = TXLegacyResource( menuDef.fCategory.fListID, menuDef.fCategory.fIndex );
	if (menuDef.fHelpText.fID > 0)
	{
		fstrHelp	= TXLegacyResource( menuDef.fHelpText.fID );
	}
#if _MINICAD_
	else
    {
		if (!VERIFYN( kVStanev, HelpTextManager::GetHelpTextFromResourceID ( menuDef.fHelpText.fID, fstrHelp ) )) {
			DMSG((kEveryone, "Missing help text for (%d,%d) = '%s', possibly should be at (%s,%d)\n",
				  menuDef.fTitle.fListID, menuDef.fTitle.fIndex, TXSTRINGPRINT(fstrTitle),
				  "HelpText", menuDef.fHelpText.fID));
		}
    }
#endif


	const SMenuChunkDef_Legacy* currChunk	= arrMenuChunks;
	while(currChunk && currChunk->fItemText.fListID && currChunk->fItemText.fIndex)
	{
		SChunkInfo	item;
		item.fItem				= TXLegacyResource( currChunk->fItemText.fListID, currChunk->fItemText.fIndex );
		if (currChunk->fOverrideHelpID)
		{
			item.fOverrideHelpID	= currChunk->fOverrideHelpID;
		}

		if ( item.fItem != "-" )
		{
			item.fHelpText =  TXLegacyResource( currChunk->fHelpText.fID );
		}

		farrSubItems.push_back( item );

		++currChunk;
	}

	if ( menuDef.fOverrideHelpID ) {
		fstrOverrideHelpID	= menuDef.fOverrideHelpID;
	}
	else 
		fstrOverrideHelpID = txu(""); // no help associated
}

VWExtensionMenu::~VWExtensionMenu()
{
}

void VWExtensionMenu::OnRefCountZero()
{
	if ( fLegacyEventSink ) {
		delete fLegacyEventSink;
		fLegacyEventSink	= NULL;
	}

	if ( fMenuChunkSink ) {
		delete fMenuChunkSink;
		fMenuChunkSink	= NULL;
	}

	if ( fProtectionSink ) {
		delete fProtectionSink;
		fProtectionSink	= NULL;
	}

	// immediatelly delete this instance
	::GS_VWNotifyDeleteInterface( this );
}


IEventSink* VWExtensionMenu::QueryEventSink(const TSinkIID& iid)
{
	if ( fProtectionObtained == false ) {
		fHasProtection			= this->GetProtectionSinkIID( fProtectionSinkIID );
		fProtectionObtained		= true;
	}

	IEventSink*	pResult	= NULL;
	if ( IID_MenuEventSink == iid ) {
		if ( fLegacyEventSink == NULL ) {
			fLegacyEventSink	= this->CreateMenuEventSink( this );
			if ( fLegacyEventSink ) {
				fLegacyEventSink->AddRef();
				VWMenu_EventSink*	vwfcSink	= dynamic_cast<VWMenu_EventSink*>( fLegacyEventSink );
				if ( vwfcSink ) {
					vwfcSink->SetUniversalName( this->GetUniversalName() );
				}
			}
		}
		pResult	= fLegacyEventSink;
	}
	else if ( IID_MenuChunk2Provider == iid ) {
		if ( farrSubItems.size() > 0 || fMenuChunkType != eMenuChunkType_Regular ) {
			if ( fMenuChunkSink == NULL ) {
				fMenuChunkSink	= SDK_NEW CMenuChunk( this );
			}

			if ( fMenuChunkSink ) {
				fMenuChunkSink->AddRef();
			}

			pResult	= fMenuChunkSink;
		}
	}
	else if ( fHasProtection && fProtectionSinkIID == iid ) {
		if ( fProtectionSink == NULL ) {
			fProtectionSink	= this->CreateProtectionSink( this );
			if ( fProtectionSink == NULL ) {
				fHasProtection	= false;
			}
		}

		if ( fProtectionSink ) {
			fProtectionSink->AddRef();
			pResult	= fProtectionSink;
		}
	}

	return pResult;
}

bool VWExtensionMenu::GetProtectionSinkIID(TSinkIID& outIID)
{
	return false;
}

IProviderProtection* VWExtensionMenu::CreateProtectionSink(IVWUnknown* parent)
{
	return NULL;
}

const TXString& VWExtensionMenu::GetTitle()
{
	return fstrTitle;
}

const TXString& VWExtensionMenu::GetCategory()
{
	return fstrCategory;
}

const TXString& VWExtensionMenu::GetHelpText()
{
	return fstrHelp;
}

const TXString& VWExtensionMenu::GetOverrideHelpID(size_t chunkIndex)
{
	if ( chunkIndex == size_t(-1) ) {
		return fstrOverrideHelpID;
	}
	else {
		if ( chunkIndex < farrSubItems.size() ) {
			const SChunkInfo&	chunkInfo	= farrSubItems[ chunkIndex ];
			return chunkInfo.fOverrideHelpID;
		}
		else {
			return fstrOverrideHelpID;
		}
	}
}

void VWExtensionMenu::GetNeedsFlags(Uint16& outNeeds, Uint16& outNeedsNot)
{
	outNeeds	= fNeeds;
	outNeedsNot	= fNeedsNot;
}

void VWExtensionMenu::GetVersionInfo(Sint16& outCreated, Sint16& outModified, Sint16& outRetired)
{
	outCreated	= fVersionCreated;
	outModified	= fVersoinModified;
	outRetired	= fVersoinRetired;
}

void VWExtensionMenu::GetSubMenuItems(TSubItemsVector& outArrItems)
{
	outArrItems	= farrSubItems;
}

void VWExtensionMenu::SetSubMenuItems(const TSubItemsVector& arrItems)
{
	fMenuChunkIsDirty	= true;
	farrSubItems		= arrItems;
}

void VWExtensionMenu::SetTitle(const TXString& value)
{
	fstrTitle = value;
}

// --------------------------------------------------------------------------------------------------------
VWExtensionMenu::CMenuChunk::CMenuChunk(VWExtensionMenu* parent)
	: VCOMImpl<IMenuChunk2Provider>( parent )
	, fParent( parent )
{
}

VWExtensionMenu::CMenuChunk::~CMenuChunk()
{
}

size_t VWExtensionMenu::CMenuChunk::GetItemsCount()
{
	return fParent->farrSubItems.size();
}

const TXString& VWExtensionMenu::CMenuChunk::GetItemTitle(size_t index)
{
	ASSERTN( kVStanev, index < fParent->farrSubItems.size() );
	return fParent->farrSubItems[ index ].fItem;
}

const TXString& VWExtensionMenu::CMenuChunk::GetOverrideHelpID(size_t index)
{
	ASSERTN( kVStanev, index < fParent->farrSubItems.size() );
	return fParent->farrSubItems[ index ].fOverrideHelpID;
}

EMenuChunkType VWExtensionMenu::CMenuChunk::GetType()
{
	return fParent->fMenuChunkType;
}

const TXString& VWExtensionMenu::CMenuChunk::GetItemHelp(size_t index)
{
	ASSERTN( kVStanev, index < fParent->farrSubItems.size() );
	return fParent->farrSubItems[ index ].fHelpText;
}

bool VWExtensionMenu::CMenuChunk::IsChunkDirty()
{
	return fParent->fMenuChunkIsDirty;
}

void VWExtensionMenu::CMenuChunk::ClearChunkDirty()
{
	fParent->fMenuChunkIsDirty	= false;
}

// --------------------------------------------------------------------------------------------------------
VWMenu_EventSink::VWMenu_EventSink(IVWUnknown* parent)
	: VCOMImpl<IMenuEventSink>( parent )
{
	fpMenuChunkInfo		= NULL;
	fResult				= 0;
}

VWMenu_EventSink::~VWMenu_EventSink()
{
}

void VWMenu_EventSink::SetUniversalName(const TXString& name)
{
	fUnivName	= name;
}

Sint32 VWMenu_EventSink::Execute(MenuMessage* message)
{
	Sint32	reply = 0;

	switch( message->fAction )
	{
		case MenuDoInterfaceMessage::kAction:
			this->SetMenuChunkInfo( dynamic_cast<MenuChunkInfo*>( message ) );
			this->DoInterface();
			reply	= this->GetResult();
			break;

		case MenuAddItemsMessage::kAction:
			this->OnDynamicVariableChunkUpdate();
			break;

		case MenuCheckHiliteMessage::kAction:
			this->OnDynamicVariableChunkUpdate();
			break;

		case MenuItemEnabledMessage::kAction: {
				MenuChunkInfo*	chunkInfo = dynamic_cast<MenuChunkInfo*>( message );

				this->SetMenuChunkInfo( chunkInfo );

				bool	bIsItemEnabled	= this->GetItemEnabled();
				reply					= this->GetResult();
				if ( reply == 0 ) {
					reply	= bIsItemEnabled ? kMenuItemIsEnabled : kMenuItemIsDisabled;
				}
			} break;

		case MenuItemSpec::kAction:
			break;


		default:
			reply = this->OnDefaultEvent( message );
			break;
	}

	return reply;
}

void VWMenu_EventSink::DoInterface()
{
}

bool VWMenu_EventSink::GetItemEnabled()
{
	return true;
}

SintptrT VWMenu_EventSink::GetUserData() const
{
	return 0;
}

void VWMenu_EventSink::SetUserData(SintptrT /*userData*/)
{
}

Sint32 VWMenu_EventSink::GetResult() const
{
	return fResult;
}

void VWMenu_EventSink::SetResult(Sint32 result)
{
	fResult	= result;
}

void VWMenu_EventSink::SetMenuChunkInfo(MenuChunkInfo* pMenuChunkInfo)
{
	fpMenuChunkInfo		= pMenuChunkInfo;
}

Sint32 VWMenu_EventSink::OnDefaultEvent(MenuMessage* /*message*/)
{
	return 0;
}

void VWMenu_EventSink::OnDynamicVariableChunkUpdate()
{
}
