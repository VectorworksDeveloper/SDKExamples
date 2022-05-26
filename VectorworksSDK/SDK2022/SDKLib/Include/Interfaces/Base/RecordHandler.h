//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//



#pragma once

#include "RecordHandlerInterfaces.h"

#ifdef _MINICAD_EXTERNAL_
	typedef MCObjectHandle		RecordHandle;
	typedef MCObjectHandle		FormatHandle;
#endif

// ----------------------------------------------------------------------------------------------------------------------------
class TRecordItem
{
public:
				TRecordItem(EFieldStyle aFieldStyle, TNumStyleClass ns = nsGeneral, Byte accuracy = 0); 	
				TRecordItem(const TRecordItem& r);
	virtual		~TRecordItem();

	TRecordItem&	operator=(const TRecordItem& r);

					operator IRecordItem*();

	bool GetIsEmpty() const;			// determines if the field has no value defined
	void SetIsEmpty(bool value);
		 
	bool GetIsDataLinked() const;		// determines if the field value will be determined by the data manager link
	void SetIsDataLinked(bool value);

	EFieldStyle	GetFieldStyle() const;
	
	// Get Functions, returns false if error
	Boolean GetFieldValue			( Sint32& theValue) const;
	Boolean GetFieldValue			( Sint32& lowValue, Sint32& highValue) const;
	Boolean GetFieldValue			( Boolean& theValue) const;
	Boolean GetFieldValue			( double_gs& theValue) const;
	Boolean GetFieldValue			( TXString& outValue);
	Boolean GetFieldClass			( InternalIndex& outResource) const;
	Boolean GetFieldBuildingMaterial( InternalIndex& outResource) const;
	Boolean GetFieldFill			( InternalIndex& outResource) const; // 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	Boolean GetFieldPenStyle		( InternalIndex& outResource) const; // 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	Boolean GetFieldPenWeight		( Uint8& outValue) const;
	Boolean GetFieldColor			( ColorRef& outValue) const;
	Boolean GetFieldTexture			( InternalIndex& outResource) const;
	Boolean GetFieldSymDef			( InternalIndex& outResource) const;

	Boolean GetFieldValueAsString (TXString& outString) const;  

	void GetNumStyle(TNumStyleClass& numStyle, Byte& accuracy) const;	// sets the parameters to fNumStyle
	
	// Set Functions, returns false if error
	Boolean SetFieldValue				( Sint32 theValue);
	Boolean SetFieldValue				( Sint32 lowValue, Sint32 highValue);
	Boolean SetFieldValue				( Boolean theValue);
	Boolean SetFieldValue				( double_param theValue);
	Boolean SetFieldValue				( const TXString& theValue);
	Boolean SetFieldValue				( const UCChar* text, size_t len);	// Copies text to fTextP -- len in number of UCChar characters
	Boolean SetFieldClass				( InternalIndex resource);
	Boolean SetFieldBuildingMaterial	( InternalIndex resource);
	Boolean SetFieldFill				( InternalIndex resource);	// // 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	Boolean SetFieldPenStyle			( InternalIndex resource);	// // 0 is none, a positive number is a pattern index, and a negative number is the negative of the RefNumber of a hatch, tile, gradient, or image
	Boolean SetFieldPenWeight			( Uint8 value);
	Boolean SetFieldColor				( ColorRef value);
	Boolean SetFieldTexture				( InternalIndex resource);
	Boolean SetFieldSymDef				( InternalIndex resource);

	Boolean SetFieldValueAsString (const TXString& inString);  // 

	void SetNumStyle(TNumStyleClass numStyle, Byte accuracy);	//Sets fNumStyle with the given paramters

	size_t	PopupGetChoicesCount();
	bool	PopupGetChoice(size_t index, TXString& outKey, TXString& outValue);
	bool	PopupClearChoices();
	bool	PopupSetChoices(const TXStringArray& keyValuePairs, bool append);

private:
	IRecordItem*	fInstance;
};

// ----------------------------------------------------------------------------------------------------------------------------
class TFormatBase
{
//
//	TFormatBase is constructed with a kFormatNode handle.
// 	It provides access to some basic functionality which is shared
//	between RecordHandler and FormatHandler
//
public:		
				TFormatBase(MCObjectHandle f);
	virtual		~TFormatBase(); 
	
	TXString	GetNameOfFormat() const;
	TXString	GetLocalizedName() const;
	bool		SetLocalizedName(const TXString& name);
	short		GetNumOfFields()const;
	void		GetNameOfField( short fieldIndex, TXString& nameOfField)const; // '' if index out of range
	void		GetNameOfFieldLocalized( short fieldIndex, TXString& nameOfField) const;
	bool		SetNameOfFieldLocalized( short fieldIndex, const TXString& nameOfField);
	short		GetFieldIndex( const TXString& nameOfField)const; 	// returns 0 if fails
	EFieldStyle	GetFieldStyle( short fieldIndex)const; 
	Sint32		GetFieldOffset( short fieldIndex)const; 
	Boolean		GetFieldNumStyle( short fieldIndex, TNumStyleClass& numStyle, Byte& accuracy);
	Boolean		SetFieldNumStyle( short fieldIndex, TNumStyleClass numStyle, Byte accuracy);

	void		SetIsParametric(Boolean is = true);
	Boolean		IsParametric() const;
	void		SetParametricVersion(short ver);
	short		GetParametricVersion();
	void		SetActiveParametricObjectStyle(RefNumber style);
	RefNumber	GetActiveParametricObjectStyle();

	void		HideFromUserInterface(Boolean inHideIt);
	Boolean		IsHiddenFromUserInterface() const;
    MCObjectHandle GetFormatHandle();

// there is no copy function for IFormatHandler, so we add copy constructor and operator= in protected
protected:
	TFormatBase(const TFormatBase& f);
	TFormatBase& operator=(const TFormatBase& f);
    
protected:
				TFormatBase();
	void		Init(IFormatBase* base);

private:
	IFormatBase*		fInstance;
	IFormatHandler*		fFormatHandler;

};

// ----------------------------------------------------------------------------------------------------------------------------
class TRecordHandler : public TFormatBase
{	
//
//	RecordHandler is used for editing the fields of a Record instance attached to a drawing object.
//	RecordHandlers are constructed with a handle to a recordNode. The RecordHandlers Get and Set 
//	functions pass around TRecordItems.
//
public:
	TRecordHandler (MCObjectHandle r);	// Creates a handler, given the record;
										//  uses GetDefinition to SetFormat in TFormatBase

	TRecordHandler (MCObjectHandle r, MCObjectHandle fmtDef);	// Creates a handler, given the record and format; can use
																//  most methods when record and/or format not in document
																//  (TFormatBase::GetNameOfFormat is not useable)
	
	virtual	~TRecordHandler();

	// Returns false if fieldIndex is out of range or the fieldStyle is wrong
	//  Otherwise it gives you a TRecordItem object for editing record data
	Boolean		GetFieldObject(short fieldIndex, TRecordItem& value, Boolean needsByteSwap = false);	
	Boolean		SetFieldObject(short fieldIndex, TRecordItem& value, bool isUpdatingOfOIPSkipped = false); 
	Boolean		SetFieldObjectOptions(short fieldIndex, TRecordItem& value, bool isUpdatingOfOIPSkipped = false);
	
	// Returns true if the fields are identical between the objects's record and the passed in record
	Boolean		RecordsEqual(MCObjectHandle rec, Boolean thisRecNeedsByteSwap);
	
	// Returns true if any of the Material type fields refers to the given MaterialRef
	Boolean		IsMaterialInUse(InternalIndex materialRef);

	// Returns true if all fields are identical between the two records
	static Boolean RecordsEqual(MCObjectHandle rec1, MCObjectHandle rec2);

// there is no copy function for IRecordHandler, so we add copy constructor and operator= in protected
protected:
	TRecordHandler(const TRecordHandler& r);
	TRecordHandler& operator=(const TRecordHandler& r);

private:
	IRecordHandler*	fInstance;
};


// ----------------------------------------------------------------------------------------------------------------------------
class TFormatHandler : public TFormatBase
{
// 
// TFormatHandler is constructed with a handle to a kFormatNode or with a string. If the string
// is not the name of an existing format then a new format is created using that name.
// 
public:
	TFormatHandler(MCObjectHandle f);			// set fFormat = f
										
	TFormatHandler(const TXString& name);					// sets fFormat to format named name. If there is no name, then
												// creates a new Format. If name is already in use, then name is 
												// modified so that it is unique and a new format is created
	virtual	~TFormatHandler();

	void	DeleteFormat();						// calls DeleteObject - removes format and its records

	short	AddField( const TXString& fieldName, TRecordItem& defaultValue, Boolean updateExistingRecords = true); // returns index of new field, 0 if fails 
												
	void	DeleteField( short fieldIndex);// deletes field in format and all records
	 
	// returns false if fieldIndex is out of range
	Boolean GetFieldDefault( short fieldIndex, TRecordItem& theValue); 
	Boolean SetFieldDefault( short fieldIndex, TRecordItem& theValue);

	void RemoveRecordFromObject(MCObjectHandle object);	//removes record from graphic object
	MCObjectHandle AttachRecordToObject(MCObjectHandle object); 
										//attaches a new record with default settings to object,
										// and returns a handle to the new record.
	Boolean CountExistingRecords(Sint32& count);	// count number of existing records which use this format.

	bool	EditWithUI();
	// return 0 if the operation was canceled, or the 1-based index of the new field
	short	AddFieldWithUI(const TXString& name, EFieldStyle style, const TXString& value);
	short	EditFieldWithUI(short fieldIndex);

	bool	EditFieldDefineWithUI(short fieldIndex);

// there is no copy function for IFormatHandler, so we add copy constructor and operator= in protected
protected:
	TFormatHandler(const TFormatHandler& f);
	TFormatHandler& operator=(const TFormatHandler& f);
    
protected:
	TFormatHandler(const TXString& name, Boolean inIsParametric);

private:
	IFormatHandler*	fInstance;
};


// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define GET_PARAM_TXSTRING_VAL(success, getTxStrVal, index, rh, fh) \
		{ TRecordItem item(fh.GetFieldStyle(index)); \
		if (rh.GetFieldObject(index, item)) { \
			item.GetFieldValueAsString(getTxStrVal); \
			success = true; \
		} \
		else { \
			success = false; \
		} }

#define GET_PARAM_COORD_VAL(success, getcoordvalue, index, rh, fh) \
		{ WorldCoord coordValue; \
		TRecordItem item(fh.GetFieldStyle(index)); \
		if (rh.GetFieldObject(index, item)) { \
			item.GetFieldValue(coordValue); \
			getcoordvalue = coordValue;  \
			success = true; \
		} \
		else { \
			success = false; \
		} }

#define GET_PARAM_BOOLEAN_VAL(success, getbooleanvalue, index, rh, fh) \
		{ Boolean booleanValue; \
		TRecordItem item(fh.GetFieldStyle(index)); \
		if (rh.GetFieldObject(index, item)) { \
			item.GetFieldValue(booleanValue); \
			getbooleanvalue = booleanValue;  \
			success = true; \
		} \
		else { \
			success = false; \
		} }

#define GET_PARAM_LONG_VAL(success, getvalue, index, rh, fh) \
		{ Sint32	longValue; \
		TRecordItem item(fh.GetFieldStyle(index));	\
		if (rh.GetFieldObject(index, item)) { \
			item.GetFieldValue(longValue); \
			getvalue = longValue; \
			success = true; \
		} \
		else { \
			success = false; \
		} }

#define SET_PARAM_VAL(success, setvalue, index, rh, fh) \
		{ TRecordItem item(fh.GetFieldStyle(index));	\
		if (rh.GetFieldObject(index, item)) { \
			item.SetFieldValue(setvalue); \
			rh.SetFieldObject(index, item); \
			success = true; \
		} \
		else { \
			success = false; \
		} }

#define SET_PARAM_TXSTRING_VAL(success, setTXStrvalue, index, rh, fh) \
		{ TRecordItem item(fh.GetFieldStyle(index));	\
		if (rh.GetFieldObject(index, item)) { \
			item.SetFieldValueAsString(setTXStrvalue); \
			rh.SetFieldObject(index, item); \
			success = true; \
		} \
		else { \
			success = false; \
		} }

#define SET_PARAM_COORD_VAL(success, setcoordvalue, index, rh, fh) 		SET_PARAM_VAL(success, setcoordvalue, index, rh, fh)
#define SET_PARAM_BOOLEAN_VAL(success, setbooleanvalue, index, rh, fh) 	SET_PARAM_VAL(success, setbooleanvalue, index, rh, fh)
#define SET_PARAM_LONG_VAL(success, setlongvalue, index, rh, fh) 		SET_PARAM_VAL(success, setlongvalue, index, rh, fh)
