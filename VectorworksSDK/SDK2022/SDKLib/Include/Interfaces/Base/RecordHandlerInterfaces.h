//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//



#pragma once

// ----------------------------------------------------------------------------------------------------------------------------
class DYNAMIC_ATTRIBUTE IRecordItem
{
public:
	virtual		~IRecordItem() {}

	virtual void		VCOM_CALLTYPE	Init(EFieldStyle aFieldStyle, TNumStyleClass ns = nsGeneral, Byte accuracy = 0) = 0;
	virtual void		VCOM_CALLTYPE	Copy(IRecordItem* src) = 0;

	virtual bool		VCOM_CALLTYPE	GetIsEmpty() const = 0;			// determines if the field has no value defined
	virtual void		VCOM_CALLTYPE	SetIsEmpty(bool value) = 0;

	virtual bool		VCOM_CALLTYPE	GetIsDataLinked() const = 0;		// determines if the field value will be determined by the data manager link
	virtual void		VCOM_CALLTYPE	SetIsDataLinked(bool value) = 0;

	virtual EFieldStyle	VCOM_CALLTYPE	GetFieldStyle() const = 0;

	virtual Boolean		VCOM_CALLTYPE	GetFieldValue			( Sint32& theValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldValue			( Sint32& lowValue, Sint32& highValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldValue			( Boolean& theValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldValue			( double_gs& theValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldValue			( TXString& outValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldClass			( InternalIndex& outResource) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldBuildingMaterial( InternalIndex& outResource) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldFill			( InternalIndex& outResource) const = 0;	// 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	virtual Boolean		VCOM_CALLTYPE	GetFieldPenStyle		( InternalIndex& outResource) const = 0;	// 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	virtual Boolean		VCOM_CALLTYPE	GetFieldPenWeight		( Uint8& outValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldColor			( ColorRef& outValue) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldTexture			( InternalIndex& outResource) const = 0;
	virtual Boolean		VCOM_CALLTYPE	GetFieldSymDef			( InternalIndex& outResource) const = 0;

	virtual Boolean		VCOM_CALLTYPE	GetFieldValueAsString (TXString& outString) const = 0;

	virtual void		VCOM_CALLTYPE	GetNumStyle(TNumStyleClass& numStyle, Byte& accuracy) const = 0;

	virtual Boolean		VCOM_CALLTYPE	SetFieldValue				( Sint32 theValue) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldValue				( Sint32 lowValue, Sint32 highValue) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldValue				( Boolean theValue) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldValue				( double_param theValue) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldValue				( const TXString& theValue) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldValue				( const UCChar* text, size_t size) = 0;			// size in bytes, including zero term UCChar
	virtual Boolean		VCOM_CALLTYPE	SetFieldClass				( InternalIndex resource) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldBuildingMaterial	( InternalIndex resource) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldFill				( InternalIndex resource) = 0;	// 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	virtual Boolean		VCOM_CALLTYPE	SetFieldPenStyle			( InternalIndex resource) = 0;	// 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	virtual Boolean		VCOM_CALLTYPE	SetFieldPenWeight			( Uint8 value) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldColor				( ColorRef value) = 0;
	virtual Boolean		VCOM_CALLTYPE	SetFieldTexture				( InternalIndex resource) = 0;	// that is kTextureNode
	virtual Boolean		VCOM_CALLTYPE	SetFieldSymDef				( InternalIndex resource) = 0;

	virtual Boolean		VCOM_CALLTYPE	SetFieldValueAsString (const TXString& inString) = 0;

	virtual void		VCOM_CALLTYPE	SetNumStyle(TNumStyleClass numStyle, Byte accuracy) = 0;

	virtual size_t		VCOM_CALLTYPE	PopupGetChoicesCount() = 0;
	virtual bool		VCOM_CALLTYPE	PopupGetChoice(size_t index, TXString& outKey, TXString& outValue) = 0;
	virtual bool		VCOM_CALLTYPE	PopupClearChoices() = 0;
	virtual bool		VCOM_CALLTYPE	PopupSetChoices(const TXStringArray& keyValuePairs, bool append) = 0;
};

// ----------------------------------------------------------------------------------------------------------------------------
class DYNAMIC_ATTRIBUTE IFormatBase
{
public:		
	virtual				~IFormatBase() {}

	virtual	TXString	VCOM_CALLTYPE	GetNameOfFormat() const = 0;
	virtual	short		VCOM_CALLTYPE	GetNumOfFields() const = 0;
	virtual	void		VCOM_CALLTYPE	GetNameOfField( short fieldIndex, TXString& nameOfField) const = 0;
	virtual	short		VCOM_CALLTYPE	GetFieldIndex( const TXString& nameOfField) const = 0;
	virtual	EFieldStyle	VCOM_CALLTYPE	GetFieldStyle( short fieldIndex) const = 0;
	virtual	Sint32		VCOM_CALLTYPE	GetFieldOffset( short fieldIndex) const = 0;
	virtual	Boolean		VCOM_CALLTYPE	GetFieldNumStyle( short fieldIndex, TNumStyleClass& numStyle, Byte& accuracy) = 0;
	virtual	Boolean		VCOM_CALLTYPE	SetFieldNumStyle( short fieldIndex, TNumStyleClass numStyle, Byte accuracy) = 0;

	virtual	void		VCOM_CALLTYPE	SetIsParametric(Boolean is = true) = 0;
	virtual	Boolean		VCOM_CALLTYPE	IsParametric() const = 0;
	virtual	void		VCOM_CALLTYPE	SetParametricVersion(short ver) = 0;
	virtual	short		VCOM_CALLTYPE	GetParametricVersion() = 0;
	virtual	void		VCOM_CALLTYPE	SetActiveParametricObjectStyle(RefNumber style) = 0;
	virtual	RefNumber	VCOM_CALLTYPE	GetActiveParametricObjectStyle() = 0;

	virtual	void		VCOM_CALLTYPE	HideFromUserInterface(Boolean inHideIt) = 0;
	virtual	Boolean		VCOM_CALLTYPE	IsHiddenFromUserInterface() const = 0;
    virtual MCObjectHandle VCOM_CALLTYPE	GetFormatHandle() = 0;

	virtual	TXString	VCOM_CALLTYPE	GetLocalizedName() const = 0;
	virtual	bool		VCOM_CALLTYPE	SetLocalizedName(const TXString& name) = 0;
	virtual	void		VCOM_CALLTYPE	GetNameOfFieldLocalized( short fieldIndex, TXString& nameOfField) const = 0;
	virtual	bool		VCOM_CALLTYPE	SetNameOfFieldLocalized( short fieldIndex, const TXString& nameOfField) = 0;
};

// ----------------------------------------------------------------------------------------------------------------------------
class DYNAMIC_ATTRIBUTE IRecordHandler : public IFormatBase
{	
public:
	virtual void		VCOM_CALLTYPE	Init(MCObjectHandle r) = 0;
	virtual void		VCOM_CALLTYPE	Init(MCObjectHandle r, MCObjectHandle fmtDef) = 0;
	
	virtual Boolean		VCOM_CALLTYPE	GetFieldObject(short fieldIndex, IRecordItem* value, Boolean needsByteSwap = false) = 0;	
	virtual Boolean		VCOM_CALLTYPE	SetFieldObject(short fieldIndex, IRecordItem* value, bool isUpdatingOfOIPSkipped = false) = 0; 

	virtual Boolean		VCOM_CALLTYPE	RecordsEqual(MCObjectHandle rec) = 0;
	virtual Boolean		VCOM_CALLTYPE	RecordsEqual(MCObjectHandle rec, Boolean thisRecNeedsByteSwap) = 0;
	
	virtual Boolean		VCOM_CALLTYPE	SetFieldObjectOptions(short fieldIndex, IRecordItem* value, bool isUpdatingOfOIPSkipped = false) = 0;
};

// ----------------------------------------------------------------------------------------------------------------------------
class DYNAMIC_ATTRIBUTE IFormatHandler : public IFormatBase
{
public:
	virtual void		VCOM_CALLTYPE	Init(MCObjectHandle f) = 0;
	virtual void		VCOM_CALLTYPE	Init(const TXString& name) = 0;
	virtual void		VCOM_CALLTYPE	Init(const TXString& name, Boolean inIsParametric) = 0;

	virtual void		VCOM_CALLTYPE	DeleteFormat() = 0;

	virtual short		VCOM_CALLTYPE	AddField( const TXString& fieldName, IRecordItem* defaultValue, Boolean updateExistingRecords = true) = 0;
												
	virtual void		VCOM_CALLTYPE	DeleteField( short fieldIndex) = 0;
	 
	virtual Boolean		VCOM_CALLTYPE	GetFieldDefault( short fieldIndex, IRecordItem* theValue) = 0; 
	virtual Boolean		VCOM_CALLTYPE	SetFieldDefault( short fieldIndex, IRecordItem* theValue) = 0;

	virtual void			VCOM_CALLTYPE	RemoveRecordFromObject(MCObjectHandle object) = 0;
	virtual MCObjectHandle	VCOM_CALLTYPE	AttachRecordToObject(MCObjectHandle object) = 0;
	virtual Boolean			VCOM_CALLTYPE	CountExistingRecords(Sint32& count) = 0;

	virtual void		VCOM_CALLTYPE	SetFieldName( short fieldIndex, const TXString& name) = 0;

	virtual bool		VCOM_CALLTYPE	EditWithUI() = 0;
	// return 0 if the operation was canceled, or the 1-based index of the new field
	virtual short		VCOM_CALLTYPE	AddFieldWithUI(const TXString& name, EFieldStyle style, const TXString& value) = 0;
	virtual short		VCOM_CALLTYPE	EditFieldWithUI(short fieldIndex) = 0;

	virtual bool		VCOM_CALLTYPE	EditFieldDefineWithUI(short fieldIndex) = 0;
};

// ----------------------------------------------------------------------------------------------------------------------------
// {197ACAC7-FC81-425B-8D1C-C4EE59E72DF5}
static const VWIID IID_FormatHandlerSupport = { 0x197acac7, 0xfc81, 0x425b, { 0x8d, 0x1c, 0xc4, 0xee, 0x59, 0xe7, 0x2d, 0xf5 } };

class DYNAMIC_ATTRIBUTE IFormatHandlerSupport : public IVWSingletonUnknown
{
public:
	virtual	void	New(IRecordItem*& out) = 0;
	virtual void	Delete(IRecordItem*& p) = 0;

	virtual	void	New(IRecordHandler*& out) = 0;
	virtual void	Delete(IRecordHandler*& p) = 0;

	virtual	void	New(IFormatHandler*& out) = 0;
	virtual void	Delete(IFormatHandler*& p) = 0;
};

typedef VCOMPtr<IFormatHandlerSupport>			IFormatHandlerSupportPtr;
