
#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#include "Kernel/RecordHandler.h"


// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
TRecordItem::TRecordItem(EFieldStyle aFieldStyle, TNumStyleClass ns, Byte accuracy)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	fInstance->Init( aFieldStyle, ns, accuracy );
}

TRecordItem::~TRecordItem()
{
	gFormatHandlerSupport->Delete( fInstance );
}

TRecordItem::TRecordItem(const TRecordItem& r)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	fInstance->Copy( r.fInstance );
}

TRecordItem& TRecordItem::operator=(const TRecordItem& r)
{
	fInstance->Copy( r.fInstance );
	return *this;
}

TRecordItem::operator IRecordItem*()
{
	return fInstance;
}

EFieldStyle TRecordItem::GetFieldStyle() const
{
	return fInstance->GetFieldStyle();
}
	
Boolean TRecordItem::GetFieldValue( Sint32& theValue) const
{
	return fInstance->GetFieldValue( theValue );
}

Boolean TRecordItem::GetFieldValue( Sint32& lowValue, Sint32& highValue) const
{
	return fInstance->GetFieldValue( lowValue, highValue );
}

Boolean TRecordItem::GetFieldValue( Boolean& theValue) const
{
	return fInstance->GetFieldValue( theValue );
}

Boolean TRecordItem::GetFieldValue( double_gs& theValue) const
{
	return fInstance->GetFieldValue( theValue );
}

Boolean TRecordItem::GetFieldValue( TXString& outValue)
{
	return fInstance->GetFieldValue( outValue );
}

Boolean TRecordItem::GetFieldValueAsString (TXString& outString) const
{
	return fInstance->GetFieldValueAsString( outString );
}

void TRecordItem::GetNumStyle(TNumStyleClass& numStyle, Byte& accuracy) const
{
	fInstance->GetNumStyle( numStyle, accuracy );
}

Boolean TRecordItem::SetFieldValue( Sint32 theValue)
{
	return fInstance->SetFieldValue( theValue );
}

Boolean TRecordItem::SetFieldValue( Sint32 lowValue, Sint32 highValue)
{
	return fInstance->SetFieldValue( lowValue, highValue );
}

Boolean TRecordItem::SetFieldValue( Boolean theValue)
{
	return fInstance->SetFieldValue( theValue );
}

Boolean TRecordItem::SetFieldValue( double_param theValue)
{
	return fInstance->SetFieldValue( theValue );
}

Boolean TRecordItem::SetFieldValue( const TXString& theValue)
{
	return fInstance->SetFieldValue( theValue );
}

Boolean TRecordItem::SetFieldValue( const UCChar* text, size_t size)
{
	return fInstance->SetFieldValue( text, size );
}

Boolean TRecordItem::SetFieldValueAsString (const TXString& inString)
{
	return fInstance->SetFieldValueAsString( inString );
}

void TRecordItem::SetNumStyle(TNumStyleClass numStyle, Byte accuracy)
{
	fInstance->SetNumStyle( numStyle, accuracy );
}

size_t TRecordItem::PopupGetChoicesCount()
{
	return fInstance->PopupGetChoicesCount();
}

bool TRecordItem::PopupGetChoice(size_t index, TXString& outKey, TXString& outValue)
{
	return fInstance->PopupGetChoice( index, outKey, outValue );
}

bool TRecordItem::PopupClearChoices()
{
	return fInstance->PopupClearChoices();
}

bool TRecordItem::PopupSetChoices(const TXStringArray& keyValuePairs, bool append)
{
	return fInstance->PopupSetChoices( keyValuePairs, append );
}



// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
TFormatBase::TFormatBase(MCObjectHandle f)
	: fFormatHandler( nullptr )
{
	gFormatHandlerSupport->New( fFormatHandler );
	fFormatHandler->Init( f );

	fInstance	= fFormatHandler;
}

TFormatBase::TFormatBase()
	: fFormatHandler( nullptr )
{
	fInstance	= NULL;
}

TFormatBase::TFormatBase(const TFormatBase& f)
	: fFormatHandler( nullptr )
	, fInstance( nullptr )
{
}

TFormatBase& TFormatBase::operator=(const TFormatBase& f)
{
	if ( this != &f )
	{
		fInstance = nullptr;
		gFormatHandlerSupport->Delete( fFormatHandler );
	}

	return *this;
}

TFormatBase::~TFormatBase()
{
	fInstance	= NULL;
	gFormatHandlerSupport->Delete( fFormatHandler );
}
	
void TFormatBase::Init(IFormatBase* base)
{
	fInstance = base;
}

TXString TFormatBase::GetNameOfFormat() const
{
	return fInstance->GetNameOfFormat();
}

TXString TFormatBase::GetLocalizedName() const
{
	return fInstance->GetLocalizedName();
}

bool TFormatBase::SetLocalizedName(const TXString& name)
{
	return fInstance->SetLocalizedName( name );
}

short TFormatBase::GetNumOfFields() const
{
	return fInstance->GetNumOfFields();
}

void TFormatBase::GetNameOfField( short fieldIndex, TXString& nameOfField) const
{
	fInstance->GetNameOfField( fieldIndex, nameOfField );
}

void TFormatBase::GetNameOfFieldLocalized( short fieldIndex, TXString& nameOfField) const
{
	fInstance->GetNameOfFieldLocalized( fieldIndex, nameOfField );
}

bool TFormatBase::SetNameOfFieldLocalized( short fieldIndex, const TXString& nameOfField)
{
	return fInstance->SetNameOfFieldLocalized( fieldIndex, nameOfField );
}

short TFormatBase::GetFieldIndex( const TXString& nameOfField) const
{
	return fInstance->GetFieldIndex( nameOfField );
}

EFieldStyle TFormatBase::GetFieldStyle( short fieldIndex) const
{
	return fInstance->GetFieldStyle( fieldIndex );
}

Sint32 TFormatBase::GetFieldOffset( short fieldIndex) const
{
	return fInstance->GetFieldOffset( fieldIndex );
}

Boolean TFormatBase::GetFieldNumStyle( short fieldIndex, TNumStyleClass& numStyle, Byte& accuracy)
{
	return fInstance->GetFieldNumStyle( fieldIndex, numStyle, accuracy );
}

Boolean TFormatBase::SetFieldNumStyle( short fieldIndex, TNumStyleClass numStyle, Byte accuracy)
{
	return fInstance->SetFieldNumStyle( fieldIndex, numStyle, accuracy );
}

void TFormatBase::SetIsParametric(Boolean is)
{
	fInstance->SetIsParametric( is );
}

Boolean TFormatBase::IsParametric() const
{
	return fInstance->IsParametric();
}

void TFormatBase::SetParametricVersion(short ver)
{
	fInstance->SetParametricVersion( ver );
}

short TFormatBase::GetParametricVersion()
{
	return fInstance->GetParametricVersion();
}

void TFormatBase::SetActiveParametricObjectStyle(RefNumber style)
{
	fInstance->SetActiveParametricObjectStyle( style );
}

RefNumber TFormatBase::GetActiveParametricObjectStyle()
{
	return fInstance->GetActiveParametricObjectStyle();
}

void TFormatBase::HideFromUserInterface(Boolean inHideIt)
{
	fInstance->HideFromUserInterface( inHideIt );
}

Boolean TFormatBase::IsHiddenFromUserInterface() const
{
	return fInstance->IsHiddenFromUserInterface();
}

MCObjectHandle TFormatBase::GetFormatHandle()
{
    return fInstance->GetFormatHandle();
}



// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
TRecordHandler::TRecordHandler (MCObjectHandle r)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	TFormatBase::Init( fInstance );
	fInstance->Init( r );
}

TRecordHandler::TRecordHandler (MCObjectHandle r, MCObjectHandle fmtDef)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	TFormatBase::Init( fInstance );
	fInstance->Init( r, fmtDef );
}

TRecordHandler::TRecordHandler(const TRecordHandler& r)
	: fInstance( nullptr )
{
}

TRecordHandler& TRecordHandler::operator=(const TRecordHandler& r)
{
	if ( this != &r )
	{
		TFormatBase::operator=(r);
		gFormatHandlerSupport->Delete( fInstance );
	}

	return *this;
}

TRecordHandler::~TRecordHandler()
{
	gFormatHandlerSupport->Delete( fInstance );
}

Boolean TRecordHandler::GetFieldObject(short fieldIndex, TRecordItem& value, Boolean needsByteSwap)
{
	return fInstance->GetFieldObject( fieldIndex, value, needsByteSwap );
}

Boolean TRecordHandler::SetFieldObject(short fieldIndex, TRecordItem& value, bool isUpdatingOfOIPSkipped /*= false*/)
{
	return fInstance->SetFieldObject( fieldIndex, value, isUpdatingOfOIPSkipped );
}

Boolean TRecordHandler::RecordsEqual(MCObjectHandle rec, Boolean thisRecNeedsByteSwap)
{
	return fInstance->RecordsEqual( rec, thisRecNeedsByteSwap );
}

/*static*/ Boolean TRecordHandler::RecordsEqual(MCObjectHandle rec1, MCObjectHandle rec2)
{
	TRecordHandler	instance( rec1 );
	return instance.fInstance->RecordsEqual( rec2 );
}




// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
TFormatHandler::TFormatHandler(MCObjectHandle f)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	TFormatBase::Init( fInstance );
	fInstance->Init( f );
}

TFormatHandler::TFormatHandler(const TXString& name)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	TFormatBase::Init( fInstance );
	fInstance->Init( name );
}

TFormatHandler::TFormatHandler(const TXString& name, Boolean inIsParametric)
	: fInstance( nullptr )
{
	gFormatHandlerSupport->New( fInstance );
	TFormatBase::Init( fInstance );
	fInstance->Init( name, inIsParametric );
}

TFormatHandler::TFormatHandler(const TFormatHandler& f)
	: fInstance( nullptr )
{
}

TFormatHandler& TFormatHandler::operator=(const TFormatHandler& f)
{
	if ( this != &f )
	{
		TFormatBase::operator=(f);
		gFormatHandlerSupport->Delete( fInstance );
	}

	return *this;
}

TFormatHandler::~TFormatHandler()
{
	gFormatHandlerSupport->Delete( fInstance );
}

void TFormatHandler::DeleteFormat()
{
	fInstance->DeleteFormat();
}

short TFormatHandler::AddField( const TXString& fieldName, TRecordItem& defaultValue, Boolean updateExistingRecords)
{
	return fInstance->AddField( fieldName, defaultValue, updateExistingRecords );
}

void TFormatHandler::DeleteField( short fieldIndex)
{
	fInstance->DeleteField( fieldIndex );
}

Boolean TFormatHandler::GetFieldDefault( short fieldIndex, TRecordItem& theValue)
{
	return fInstance->GetFieldDefault( fieldIndex, theValue );
}

Boolean TFormatHandler::SetFieldDefault( short fieldIndex, TRecordItem& theValue)
{
	return fInstance->SetFieldDefault( fieldIndex, theValue );
}

void TFormatHandler::RemoveRecordFromObject(MCObjectHandle object)
{
	fInstance->RemoveRecordFromObject( object );
}

MCObjectHandle TFormatHandler::AttachRecordToObject(MCObjectHandle object)
{
	return fInstance->AttachRecordToObject( object );
}

Boolean TFormatHandler::CountExistingRecords(Sint32& count)
{
	return fInstance->CountExistingRecords( count );
}

bool TFormatHandler::EditWithUI()
{
	return fInstance->EditWithUI();
}

short TFormatHandler::AddFieldWithUI(const TXString& name, EFieldStyle style, const TXString& value)
{
	return fInstance->AddFieldWithUI( name, style, value );
}

short TFormatHandler::EditFieldWithUI(short fieldIndex)
{
	return fInstance->EditFieldWithUI( fieldIndex );
}

bool TFormatHandler::EditFieldDefineWithUI(short fieldIndex)
{
	return fInstance->EditFieldDefineWithUI( fieldIndex );
}
