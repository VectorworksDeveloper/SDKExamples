//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include <algorithm>	// for std::sort

#ifndef _WINDOWS
#include <algorithm>	
#endif

using namespace VWFC::Tools;

/*static*/ TXString	VWAutoClassing::GetLocStr(short tableID, short stringID)
{
	TXString		str;
	switch( tableID ) {
		// {VA Setup - worksheet, symbol amd file names - miscellaneous names - DO NOT TRANSLATE}
		case 12017:
			switch( stringID ) {
				case 1: str = "ClassNameStds"; break;	// {WS for VWA, AIA, and user defined class names and attributes}
				case 2: str = "LayerNameStds"; break;	// {WS for VWA, AIA, and user defined layer names}
				case 3: str = "ViewNameStds"; break;	// {WS for VWA, AIA, and user defined view/viewport names}
				case 4: str = "LayerMap.G"; break;		//  {WS for the components of the standard VA sheets}
				case 5: str = " Symbol"; break;
				case 6: str = "VA Setup Data-Imperial.vwx"; break;	// {File that contains the LayerMap.G and the other worksheets - Imperial version}
				case 7: str = "DwgSizes.txt"; break;	// {File that contains drawing sizes}
				case 8: str = "Sheet-Common"; break;
				case 9: str = "VA Setup Data-Metric.vwx"; break;	// {File that contains the LayerMap.G and the other worksheets - metric version}
			}
			break;

		// {Hidden VA Setup record format and field names - DO NOT TRANSLATE}
		case 12018:
			switch( stringID ) {
				case 0: str = "Setup Record_10"; break;
				case 1: str = "Version"; break;
				case 2: str = "Active Class Std"; break;
				case 3: str = "Active Layer Std"; break;
				case 4: str = "Active Sheet Std"; break;
				case 5: str = "Num Basements"; break;
				case 6: str = "Num Floors"; break;
				case 7: str = "Use Zero"; break;
				case 8: str = "Basement Prefix"; break;
				case 9: str = "Floor Plan Scale"; break;
				case 10: str = "Site Plan Scale"; break;
				case 11: str = "Aux View Scale"; break;
				case 12: str = "Note Sheet Scale"; break;
				case 13: str = "Units"; break;
				case 14: str = "Border Type"; break;
				case 15: str = "Border Option"; break;
				case 16: str = "First Time-Setup"; break;
				case 17: str = "First Time-Model"; break;
				case 18: str = "First Time-Layers"; break;
				case 19: str = "First Time-Sheets"; break;
				case 20: str = "Default Floor Height"; break;
				case 21: str = "Default Slab Thk"; break;
				case 22: str = "Default Bsmt Hgt"; break;
				case 23: str = "Default Fdn Thk"; break;
				case 24: str = "Default Ceiling Hgt"; break;
				case 25: str = "Has Roof"; break;
				case 26: str = "Has Foundation"; break;
				case 27: str = "Create Slab Layers"; break;
				case 28: str = "Use Auto-classing"; break;
				case 29: str = "Title Block Type"; break;
			}
			break;

		// {Hidden VA Setup Sheet Info record format and field names - DO NOT TRANSLATE}
		case 12019:
			switch( stringID ) {
				case 0: str = "Sheet Record"; break;
				case 1: str = "Sheet Name"; break;
				case 2: str = "Sheet Type"; break;
				case 3: str = "Instance"; break;
				case 4: str = "Has Border"; break;
				case 5: str = "Border Type"; break;
				case 6: str = "Has Sheet Changed"; break;
				case 7: str = "Has Border Changed"; break;
				case 8: str = "New Border Type"; break;
				case 9: str = "Sheet Scale"; break;
				case 10: str = "List Number"; break;
			}
			break;

		// {Hidden VA Setup Model Layer Info record format and field names - DO NOT TRANSLATE}
		case 12020:
			switch( stringID ) {
				case 0: str = "Model Layer Record"; break;
				case 1: str = "Layer Type"; break;
				case 2: str = "Instance"; break;
				case 3: str = "HasLayerChanged"; break;
				case 4: str = "Old Instance"; break;
				case 5: str = "Elevation"; break;
				case 6: str = "Ceiling Height"; break;
				case 7: str = "Slab Thickness"; break;
				case 8: str = "DefaultWallHgtI"; break;
				case 9: str = "Fixed Wall Height"; break;
				case 10: str = "Layer Scale"; break;
			}
			break;
	}

	return str;
}

/*static*/ bool VWAutoClassing::IsAutoClassingTurnedOn()
	{
	bool retVal = false;

	TXString		recName		= VWAutoClassing::GetLocStr (12018, 0);

	MCObjectHandle f = gSDK->GetNamedObject( recName);

	if (f) {

		short type = gSDK->GetObjectTypeN(f);

		if (type == kFormatNode) {

			VWFC::VWObjects::VWRecordFormatObj	formatObj( f );
			size_t				fieldIndex	= formatObj.GetParamIndex( VWAutoClassing::GetLocStr (12018, 28) );
			if ( fieldIndex != (size_t) -1 ) {
				retVal	= formatObj.GetParamBool( fieldIndex );
			}

		} // ** formatNode **

	} // ** f ** 

  return retVal;
}

/*static*/ TXString VWAutoClassing::GetRRield(MCObjectHandle hRec, const TXString& fieldName)
{
	TXString		valueStr;
	if ( VWRecordObj::IsRecordObject( hRec ) ) {
		VWRecordObj		recObj( hRec );
		size_t			fieldIndex	= recObj.GetParamIndex( fieldName );
		if ( fieldIndex != (size_t) -1 ) {
			valueStr	= recObj.GetParamValue( fieldIndex );
		}
	}
	else if ( VWRecordFormatObj::IsRecordFormatObject( hRec ) ) {
		VWRecordFormatObj	formatObj( hRec );
		size_t				fieldIndex	= formatObj.GetParamIndex( fieldName );
		if ( fieldIndex != (size_t) -1 ) {
			valueStr	= formatObj.GetParamValue( fieldIndex );
		}
	}

	return valueStr;
}

/*static*/ bool VWAutoClassing::GetRField(MCObjectHandle hRec, const TXString& fieldName)
{
	bool result = false;

	if ( VWRecordObj::IsRecordObject( hRec ) ) {
		VWRecordObj		recObj( hRec );
		size_t			fieldIndex	= recObj.GetParamIndex( fieldName );
		if ( fieldIndex != (size_t) -1 ) {
			result		= recObj.GetParamBool( fieldIndex );
		}
	}
	else if ( VWRecordFormatObj::IsRecordFormatObject( hRec ) ) {
		VWRecordFormatObj	formatObj( hRec );
		size_t				fieldIndex	= formatObj.GetParamIndex( fieldName );
		if ( fieldIndex != (size_t) -1 ) {
			result		= formatObj.GetParamBool( fieldIndex );
		}
	}

	return result;
}

// {* This function looks for the VA Arch setup record and user class name worksheet. If found,	*}
// {* and there is a user defined class naming standard being used, the user name for the default	*}
// {* class name will be returned and the value of the function will be set to 'TRUE.' If the	*}
// {* setup record or worksheet are not found, a value of 'FALSE' will be returned.			*}
/*static*/ bool VWAutoClassing::GetUserClassName(const TXString& defaultClassName, TXString& outUserClassName)
{
	outUserClassName		= defaultClassName;

	// {* Get the record name and handle *}
	TXString		recName		= VWAutoClassing::GetLocStr (12018, 0);
	MCObjectHandle	recHand		= VWObject::GetNamedObject( recName );

	// {* Check for the ClassNameStds worksheet *}
	MCObjectHandle	wksHand		= VWObject::GetNamedObject (VWAutoClassing::GetLocStr (12017,1));

	bool	bResult		= (recHand != NULL) && (wksHand != NULL);
	if ( bResult ) {
		// {* Get the user standard index *}
		// userIndex := Str2Num (Copy (GetRfield (recHand, recName, getLocStr (12018, 2)), 1, 1));
		TXString		strValue	= VWAutoClassing::GetRRield( recHand, VWAutoClassing::GetLocStr (12018, 2) );
		short			userIndex	= strValue.atoi();

		if ( userIndex > 1 ) {
			short	rows, cols;
			::GS_GetWorksheetRowColumnCount( gCBP, wksHand, rows, cols );
			short	numClasses	= rows;
			for(short i=0; i<numClasses; i++) {
				//GetWSCellString (wksHand, i+1, 1, tempStr);
				TCellID		cell;
				cell.y				= i + 1;
				cell.x				= 1;
				TXString		cellString;
				::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );

				if ( cellString == defaultClassName ) {
					// GetWSCellString (wksHand, i+1, userIndex, outUserClassName);
					cell.y				= i + 1;
					cell.x				= userIndex;
					::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );
					if ( !cellString.IsEmpty() )
					{
						outUserClassName	= cellString;
					}
					break;
				}

			}
		}
	}

	return bResult;
}

// {====================================================================================================}
// {* This procedure looks for the VA Arch setup record and user class name worksheet. If found,	*}
// {* the class named 'className' will be created using the class attributes from the user class	*}
// {* name worksheet.													*}
/*static*/ void VWAutoClassing::CreateUserClass(const TXString& userClassName)
{
	const	size_t	kNumCols = 8;	// {This is the number of columns of class attribute data}

	// {* Get the record name and handle *}
	TXString		recName		= VWAutoClassing::GetLocStr (12018, 0);
	MCObjectHandle	recHand		= VWObject::GetNamedObject( recName );

	// {* Check for the ClassNameStds worksheet *}
	MCObjectHandle	wksHand		= VWObject::GetNamedObject (VWAutoClassing::GetLocStr (12017,1));

	if ( (recHand != NULL) && (wksHand != NULL) ) {
		// {* Get the user standard index *}
		// userIndex := Str2Num (Copy (GetRfield (recHand, recName, getLocStr (12018, 2)), 1, 1));
		TXString		strValue	= VWAutoClassing::GetRRield( recHand, VWAutoClassing::GetLocStr (12018, 2) );
		short			userIndex	= strValue.atoi();

		//GetWSRowColumnCount (wksHand, rows, cols);
		short	rows, cols;
		::GS_GetWorksheetRowColumnCount( gCBP, wksHand, rows, cols );
		short	numClasses		= rows;
		short	row				= 0;
		bool	classFound		= false;
		for(short i=0; i<numClasses; i++ ) {
			//GetWSCellString (wksHand, i+1, userIndex, tempStr);
			TCellID		cell;
			cell.y				= i + 1;
			cell.x				= userIndex;
			TXString			cellString;
			::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );

			classFound			= (cellString == userClassName);
			if ( classFound ) {
				row = i + 1;
				break;
			}

		}

		// {* Create the class, if it does not already exist *}
		if ( VWObject::GetNamedObject (userClassName) == NULL ) {
			short	col = cols - kNumCols;
			
			VWClass theNewClass(userClassName);

			// {* If the class was found in the worksheet, apply the attributes to the class *}
			if ( classFound ) {
				VWClassAttr		attr	= theNewClass.GetClassAttribs();

				TCellID			cell;
				double			cellValue;
				TXString		cellString;

				// GetWSCellValue (wksHand, row, col+1, tempInt);	{pen color}
				// ColorIndexToRGB (tempInt, r, g, b);
				// SetClPenFore (userClassName, r, g, b);
				cell.y		= row;	cell.x	= col+1;
				::GS_GetWorksheetCellValue( gCBP, wksHand, cell, cellValue );
				attr.SetPenForeColor( CRGBColor( Uint16(cellValue) ) );

				// GetWSCellValue (wksHand, row, col+2, tempInt);	{line weight}
				// SetClLW (userClassName, tempInt);
				cell.y		= row;	cell.x	= col+2;
				::GS_GetWorksheetCellValue( gCBP, wksHand, cell, cellValue );
				attr.SetLineWeightInMils( short(cellValue) );

				// GetWSCellValue (wksHand, row, col+3, tempInt);	{line style}
				// SetClLS (userClassName, tempInt);
				cell.y		= row;	cell.x	= col+3;
				::GS_GetWorksheetCellValue( gCBP, wksHand, cell, cellValue );
				attr.SetPenPattern( VWPattern( InternalIndex(cellValue), false ) );

				// GetWSCellValue (wksHand, row, col+4, tempInt);	{fill pattern}
				// SetClFPat (userClassName, tempInt);
				cell.y		= row;	cell.x	= col+4;
				::GS_GetWorksheetCellValue( gCBP, wksHand, cell, cellValue );
				attr.SetFillPattern( VWPattern( InternalIndex(cellValue), true ) );

				// GetWSCellValue (wksHand, row, col+5, tempInt);	{fill fore pen color}
				// ColorIndexToRGB (tempInt, r, g, b);
				// SetClFillFore (userClassName, r, g, b);
				cell.y		= row;	cell.x	= col+5;
				::GS_GetWorksheetCellValue( gCBP, wksHand, cell, cellValue );
				attr.SetFillForeColor( CRGBColor( Uint16(cellValue) ) );

				// GetWSCellValue (wksHand, row, col+6, tempInt);	{fill back pen color}
				// ColorIndexToRGB (tempInt, r, g, b);
				// SetClFillBack (userClassName, r, g, b);
				cell.y		= row;	cell.x	= col+6;
				::GS_GetWorksheetCellValue( gCBP, wksHand, cell, cellValue );
				attr.SetFillBackColor( CRGBColor( Uint16(cellValue) ) );

				// GetWSCellString (wksHand, row, col+7, tempStr);	{use at creation}
				// SetClUseGraphic (userClassName, Str2Boo(tempStr));
				cell.y		= row;	cell.x	= col+7;
				::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );
				theNewClass.SetUseGraphics( TXString(cellString).EqualNoCase( "TRUE" )  );

				// GetWSCellString (wksHand, row, col+8, tempStr);	{description} 
				cell.y		= row;	cell.x	= col+8;
				::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );
				theNewClass.SetClassDescription(TXString(cellString));

			}
		}
	}
}

// {====================================================================================================}
/*static*/ void VWAutoClassing::SetAttrsByClass(MCObjectHandle hObject)
{
	if ( hObject ) {
		VWObjectAttr	objAttr( hObject );

		objAttr.SetFillColorByClass();
		objAttr.SetFillPatternByClass();
		objAttr.SetPenPatternByClass();
		objAttr.SetPenColorByClass();
		objAttr.SetLineWeightByClass();
		objAttr.SetArrowByClass();
		objAttr.SetOpacityByClass();
	}
}

// {====================================================================================================}
// {* This procedure assigns the default class, or a user defined class, to a plug-in object *}
/*static*/ bool VWAutoClassing::AutoClass(MCObjectHandle hPlugin, const TXString& defaultClassName)
{
	// {* Get the setup record name and handle *}
	TXString		recName		= VWAutoClassing::GetLocStr (12018, 0);
	MCObjectHandle	recHand		= VWObject::GetNamedObject( recName );

	// {* Check to see if the setup record is set to use auto-classing *}
	bool			autoClassOK	= false;
	if ( recHand != NULL ) {
		//tempStr = GetRfield (recHand, recName, getLocStr (12018, 28));

		autoClassOK = VWAutoClassing::GetRField( recHand, VWAutoClassing::GetLocStr (12018, 28) );
	}

	bool result = false;

	// {* If auto-classing is in effect, continue *}
	if ( autoClassOK ) {
		// {* Check to see that the drawing has been setup to use standard classes (Standard Naming	*}
		// {* or Create Standard Sheets have been run which create the ClassNameStds worksheet.	*}
		TXString		userClassName;
		if ( VWAutoClassing::GetUserClassName (defaultClassName, userClassName) ) {
			// {* If the class does not yet exist, create it *}
			if ( VWObject::GetNamedObject (userClassName) == NULL ) {
				VWAutoClassing::CreateUserClass (userClassName);
			}

			// {* Change to the class. If the class name if being used by another object,	*}
			// {* the class will not be created and a VectorScript message will appear.	*}
			VWClass	theClass( userClassName );

			// {* If the class exists, assign the class to the plug-in. *}
			if ( hPlugin && VWObject::GetNamedObject (userClassName)  != NULL ) {
				if ( gSDK->GetObjectTypeN(VWObject::GetNamedObject (userClassName)) == 94 ) {
					//SetClass (pluginH, userClassName);
					VWObject		obj( hPlugin );
					obj.SetObjectClass( theClass );
					if ( theClass.GetUseGraphics () ) {
						VWAutoClassing::SetAttrsByClass (hPlugin);
					}

					result = true;
				}
			}
		}
	}

	return result;
}

// {====================================================================================================}
// {* This procedure assigns the default class, or a user defined class, to a plug-in object *}
/*static*/ bool VWAutoClassing::AutoClassByObject(MCObjectHandle hObject, const TXString& defaultClassName)
{
	bool	AutoClassByObject = false;

	// {* Get the setup record name and handle *}
	TXString		recName		= VWAutoClassing::GetLocStr (12018, 0);
	MCObjectHandle	recHand		= VWObject::GetNamedObject( recName );

	// {* Check to see if the setup record is set to use auto-classing *}
	bool			autoClassOK = false;
	if ( recHand != NULL && VWRecordFormatObj::IsRecordFormatObject( recHand ) ) {
		//tempStr = GetRfield (recHand, recName, getLocStr (12018, 28));
		TXString		valueStr	= VWAutoClassing::GetRRield( recHand, VWAutoClassing::GetLocStr (12018, 28) );
		autoClassOK = valueStr.EqualNoCase( "TRUE" ) ;
	}

	// {* If auto-classing is in effect and the default class name is not blank, continue *}
	if ( (autoClassOK) && (! defaultClassName.IsEmpty() ) ) {

		// {* Check to see that the drawing has been setup to use standard classes (Standard Naming	*}
		// {* or Create Standard Sheets have been run which create the ClassNameStds worksheet.	*}
		TXString	userClassName;
		if ( VWAutoClassing::GetUserClassName (defaultClassName, userClassName) ) {
			// {* If the class does not yet exist, create it *}
			if ( VWObject::GetNamedObject (userClassName) == NULL ) {
				VWAutoClassing::CreateUserClass (userClassName);
			}

			// {* Change to the class. If the class name if being used by another object,	*}
			// {* the class will not be created and a VectorScript message will appear.	*}
			VWClass	theClass( userClassName );

			// {* If the class exists, assign object to the class *}
			if ( hObject && VWObject::GetNamedObject (userClassName)  != NULL ) {
				if ( gSDK->GetObjectTypeN( VWObject::GetNamedObject (userClassName)) == 94 ) {
					VWObject		obj( hObject );
					obj.SetObjectClass( theClass );
					if ( theClass.GetUseGraphics () ) {
						VWAutoClassing::SetAttrsByClass (hObject);
					}
				}
			}
			AutoClassByObject = true;
		}
	}

	return AutoClassByObject;
}

// {====================================================================================================}
// {* This function is the inverse of getUserClassName -- it gets the ref name, given the user name	*}
/*static*/ bool VWAutoClassing::GetRefClassName(const TXString& userClassName, TXString& defaultClassName)
{
	defaultClassName			= userClassName;

	// {* Get the record name and handle *}
	TXString		recName		= VWAutoClassing::GetLocStr (12018, 0);
	MCObjectHandle	recHand		= VWObject::GetNamedObject( recName );

	// {* Check for the ClassNameStds worksheet *}
	MCObjectHandle	wksHand		= VWObject::GetNamedObject (VWAutoClassing::GetLocStr (12017,1));

	bool			bRes		= false;
	if ( (recHand != NULL) && (wksHand != NULL) && VWRecordFormatObj::IsRecordFormatObject( recHand ) ) {
		// {* Get the user standard index *}
		//userIndex := Str2Num (Copy (GetRfield (recHand, recName, getLocStr (12018, 2)), 1, 1));
		TXString		strValue	= VWAutoClassing::GetRRield( recHand, VWAutoClassing::GetLocStr (12018, 2) );
		short			userIndex	= strValue.atoi();

		if ( userIndex > 0 ) {
            TXString		cellString;
			//GetWSRowColumnCount (wksHand, rows, cols);
			short	rows, cols;
			::GS_GetWorksheetRowColumnCount( gCBP, wksHand, rows, cols );
			short	numClasses	= rows - 1;
			for(short i=1; i<=numClasses; i++ ) {
				//GetWSCellString (wksHand, i+1, userIndex, tempStr);
				TCellID		cell;
				cell.y				= i + 1;
				cell.x				= userIndex;
                cellString.Clear();
				::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );

				if ( cellString == defaultClassName ) {
					// GetWSCellString (wksHand, i+1, 1, userClassName);
					cell.y				= i + 1;
					cell.x				= 1;
					::GS_GetWorksheetCellString( gCBP, wksHand, cell, cellString );
					defaultClassName	= cellString;
					bRes				= true;
					break;
				}
			}
		}
	}

	return bRes;
}

// {====================================================================================================}
// {* A short-hand function *}
/*static*/ TXString VWAutoClassing::GetUserClass(const TXString& refClass)
{
	TXString	GetUserClass = refClass;
	TXString	str;
	if ( VWAutoClassing::GetUserClassName(refClass, str) ) {
		GetUserClass = str;
	}

	return GetUserClass;
}

// {====================================================================================================}
// {* A short-hand function *}
/*static*/ TXString VWAutoClassing::GetRefClass(const TXString& userClass)
{
	TXString	GetRefClass = userClass;
	TXString	str;
	if ( VWAutoClassing::GetRefClassName(userClass, str) ) {
		GetRefClass = str;
	}

	return GetRefClass;
}

// {====================================================================================================}
// {* This procedure loads an array with None, AutoClass, and the document class list *}
// this is the 'LoadAutoClassPopup' VS equivalent
/*static*/ void VWAutoClassing::GetAutoClassList(const TXString& inStandardClass, const TXString& inSelectedClass, TXStringSTLArray& outArrStrings, size_t& outSelectedIndex)
{
	TXString	standardClass	= VWAutoClassing::GetUserClass( inStandardClass );
	TXString	selectedClass	= VWAutoClassing::GetUserClass( inSelectedClass );

	outSelectedIndex			= size_t(-1);
	outArrStrings.clear();

	InternalIndex	nFirstClassID	= ::GS_GetNoneClassID( gCBP );
	InternalIndex	nLastClassID	= ::GS_MaxClassID( gCBP );

	InternalName	noneClassName;
	::GS_ClassIDToName( gCBP, nFirstClassID, noneClassName );

	outArrStrings.push_back( noneClassName );		// {'None'}
	outArrStrings.push_back( standardClass );			// {the standard class}
	outArrStrings.push_back( "-" );

	TXStringSTLArray	arrClassNames;
	for(InternalIndex classID=nFirstClassID; classID<=nLastClassID; classID++) {
		InternalName	className;
		::GS_ClassIDToName( gCBP, classID, className );
		if ( className.GetLength() > 0) {
			if (className.Left(4) != "NNA#")
				arrClassNames.push_back( className );
		}
	}

	std::sort( arrClassNames.begin(), arrClassNames.end() );

	size_t	clsNamesCnt	= arrClassNames.size();
	for(size_t i=0; i<clsNamesCnt; i++) {
		outArrStrings.push_back( arrClassNames[ i ]);
		if ( arrClassNames[ i ] == selectedClass ) {
			outSelectedIndex		= outArrStrings.size() - 1;
		}
	}

	if ( selectedClass == noneClassName )		outSelectedIndex	= 0;
	else if ( selectedClass == standardClass )		outSelectedIndex	= 1;
}

// default value for divider index is 2.
// But one could change the position by adding new popup elements at the beginning of a list popup.
/*static*/ TXString VWAutoClassing::GetAutoClassListSelection(size_t& inOutSelIndex, const TXString& selText, size_t dividerIndex /*= 2*/)
{
	TXString	userClass	= selText;
	if ( inOutSelIndex == size_t(-1) || inOutSelIndex == dividerIndex ) {
		InternalName	noneClassName;
		InternalIndex	nFirstClassID	= ::GS_GetNoneClassID( gCBP );
		::GS_ClassIDToName( gCBP, nFirstClassID, noneClassName );
		userClass	= noneClassName;

		if ( inOutSelIndex == 2 ) {
			inOutSelIndex = 0;
		}
	}

	return VWAutoClassing::GetRefClass( userClass );
}

/*
// {====================================================================================================}
procedure GetAutoClassPopup(controlID :INTEGER; var refClass, userClass :STRING);
// {* This procedure gets the value of an auto-class pop-up *}

VAR
	choiceNumber :INTEGER;
BEGIN
	GetSelChoice(controlID, 0, choiceNumber, userClass);
	if choiceNumber = 2 then BEGIN {if the user picks the separator}
		SelChoice(controlID, 2, TRUE);
		GetSelChoice(controlID, 0, choiceNumber, userClass);
	END;
	refClass := GetRefClass(userClass);
END;
*/
