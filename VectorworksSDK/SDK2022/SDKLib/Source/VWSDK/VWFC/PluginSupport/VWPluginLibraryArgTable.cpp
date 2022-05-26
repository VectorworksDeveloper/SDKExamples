//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC//PluginSupport/VWPluginLibraryArgTable.h"

using namespace VWFC::Tools;
using namespace VWFC::PluginSupport;


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
VWPluginLibraryArgTable::VWPluginLibraryArgTable()
{
	// init the new art table
	for(size_t i=0; i<kMaxPluginLibraryArgs; i++ )
		fNewArgTable.args[i].argType	= kNullArgType;
	fNewArgTable.functionResult.argType	= kNullArgType;

	// set arg table pointers
	fpArgTable		= & fNewArgTable;
	for(size_t i=0; i<kMaxPluginLibraryArgs; i++ )
		farrArguments[ i ].fpArgument	= & fpArgTable->args[ i ];
	fResultArgument.fpArgument		= & fpArgTable->functionResult;
}

VWPluginLibraryArgTable::VWPluginLibraryArgTable(PluginLibraryArgTable* pArgTable)
{
	// init the new art table
	for(size_t i=0; i<kMaxPluginLibraryArgs; i++ )
		fNewArgTable.args[i].argType	= kNullArgType;
	fNewArgTable.functionResult.argType	= kNullArgType;

	fpArgTable		= pArgTable;
	for(size_t i=0; i<kMaxPluginLibraryArgs; i++ )
		farrArguments[ i ].fpArgument	= & fpArgTable->args[ i ];
	fResultArgument.fpArgument		= & fpArgTable->functionResult;
}

VWPluginLibraryArgTable::~VWPluginLibraryArgTable()
{
}

VWPluginLibraryArgument& VWPluginLibraryArgTable::GetArgument(size_t index)
{
	VWFC_ASSERT( fpArgTable );
	VWFC_ASSERT( index < kMaxPluginLibraryArgs );

	VWPluginLibraryArgument&	argument	= farrArguments[ index ];

	return argument;
}

VWPluginLibraryArgument& VWPluginLibraryArgTable::GetResult()
{
	return fResultArgument;
}

VWPluginLibraryArgTable::operator PluginLibraryArgTable*()
{
	return fpArgTable;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
VWPluginLibraryArgument::VWPluginLibraryArgument()
{
	fpArgument			= NULL;
}

VWPluginLibraryArgument::~VWPluginLibraryArgument()
{

}

//kIntegerArgType			// use intValue field of PluginLibraryArg
//kIntegerVarArgType		// use intValue
short VWPluginLibraryArgument::GetArgInteger() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kIntegerArgType );
	return fpArgument->intValue;
}

short& VWPluginLibraryArgument::GetArgIntegerVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kIntegerVarArgType || fpArgument->argType == kIntegerInOutArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kIntegerVarArgType;
	return fpArgument->intValue;
}

void VWPluginLibraryArgument::SetArgInteger(short value)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != kIntegerVarArgType && fpArgument->argType != kIntegerInOutArgType ) {
		fpArgument->argType		= kIntegerArgType;
	}
	fpArgument->intValue	= value;
}

//kLongArgType			// use longValue
//kLongVarArgType		// use longValue
Sint32 VWPluginLibraryArgument::GetArgLong() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kLongArgType );
	Sint32 result = 0;
	if ( fpArgument->argType == kLongArgType )
		result = fpArgument->longValue;
	else if ( fpArgument->argType == kIntegerArgType )
		result = fpArgument->intValue;

	return result;
}

Sint32& VWPluginLibraryArgument::GetArgLongVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kLongVarArgType || fpArgument->argType == kLongInOutArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kLongVarArgType;
	return fpArgument->longValue;
}

void VWPluginLibraryArgument::SetArgLong(Sint32 value)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != kLongVarArgType && fpArgument->argType != kLongInOutArgType ) {
		fpArgument->argType		= kLongArgType;
	}
	fpArgument->longValue	= value;
}

//kRealArgType			// use realValue
//kRealVarArgType		// use realValue
double_gs VWPluginLibraryArgument::GetArgReal() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kRealArgType );
	return fpArgument->realValue;
}

double_gs& VWPluginLibraryArgument::GetArgRealVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kRealVarArgType || fpArgument->argType == kRealInOutArgType ) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kRealVarArgType;
	return fpArgument->realValue;
}

void VWPluginLibraryArgument::SetArgReal(double_gs value)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != kRealVarArgType && fpArgument->argType != kRealInOutArgType ) {
		fpArgument->argType		= kRealArgType;
	}
	fpArgument->realValue	= value;
}

//kAngleArgType			// use realValue
double_gs VWPluginLibraryArgument::GetArgAngle() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kAngleArgType );
	return fpArgument->realValue;
}

void VWPluginLibraryArgument::SetArgAngle(double_gs value)
{
	VWFC_ASSERT( fpArgument );
	fpArgument->argType		= kAngleArgType;
	fpArgument->realValue	= value;
}

//kDistanceArgType		// use realValue
double_gs VWPluginLibraryArgument::GetArgDistance() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kDistanceArgType );
	return fpArgument->realValue;
}

void VWPluginLibraryArgument::SetArgDistance(double_gs value)
{
	VWFC_ASSERT( fpArgument );
	fpArgument->argType			= kDistanceArgType;
	fpArgument->realValue		= value;
}

//kPointArgType				// use ptValue in SDK.  Use 2 REAL variables in VS.
//kGlobalPointArgType		// use ptValue in SDK.  Use 2 REAL variables in VS.
//kGlobalPointVarArgType	// use ptValue in SDK.  Use 2 REAL variables in VS.
_WorldPt VWPluginLibraryArgument::GetArgPoint() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kPointArgType || fpArgument->argType == kGlobalPointArgType || fpArgument->argType == kGlobalPointInOutArgType);
	return fpArgument->ptValue;
}

_WorldPt& VWPluginLibraryArgument::GetArgPointVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kGlobalPointVarArgType || fpArgument->argType == kGlobalPointInOutArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kGlobalPointVarArgType;
	return fpArgument->ptValue;
}

void VWPluginLibraryArgument::SetArgPoint(const _WorldPt& value)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != kGlobalPointVarArgType && fpArgument->argType != kGlobalPointInOutArgType ) {
		fpArgument->argType		= kPointArgType;
	}
	fpArgument->ptValue		= value;
}

//k3DPointArgType			// use pt3Value in SDK.  Use 3 REAL variables in VS.
//k3DPointVarArgType		// use pt3Value in SDK.  Use 3 REAL variables in VS.
_WorldPt3 VWPluginLibraryArgument::GetArg3DPoint() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == k3DPointArgType );
	return fpArgument->pt3Value;
}

_WorldPt3& VWPluginLibraryArgument::GetArg3DPointVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == k3DPointVarArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = k3DPointVarArgType;
	return fpArgument->pt3Value;
}

void VWPluginLibraryArgument::SetArg3DPoint(const _WorldPt3& value)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != k3DPointVarArgType ) {
		fpArgument->argType			= k3DPointArgType;
	}
	fpArgument->pt3Value		= value;
}

//kVectorArgType		// use vec.vecValue
//kVectorVarArgType		// use vec.vecValue
_WorldPt3 VWPluginLibraryArgument::GetArgVector() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kVectorArgType );
	return fpArgument->vecValue;
}

_WorldPt3& VWPluginLibraryArgument::GetArgVectorVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kVectorVarArgType || fpArgument->argType == kVectorInOutArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kVectorVarArgType;
	return fpArgument->vecValue;
}

void VWPluginLibraryArgument::SetArgVector(const _WorldPt3& value)
{
	VWFC_ASSERT( fpArgument );
	fpArgument->argType			= kVectorArgType;
	fpArgument->vecValue		= value;
}

//kBooleanArgType			// use boolValue
//kBooleanVarArgType		// use boolValue
Boolean VWPluginLibraryArgument::GetArgBoolean() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kBooleanArgType );
	return fpArgument->boolValue;
}

Boolean& VWPluginLibraryArgument::GetArgBooleanVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kBooleanVarArgType || fpArgument->argType == kBooleanInOutArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kBooleanVarArgType;
	return fpArgument->boolValue;
}

void VWPluginLibraryArgument::SetArgBoolean(Boolean value)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != kBooleanVarArgType && fpArgument->argType != kBooleanInOutArgType ) {
		fpArgument->argType		= kBooleanArgType;
	}
	fpArgument->boolValue	= value;
}

//kStringArgType			// use strValue
//kStringVarArgType			// use strValue
TXString VWPluginLibraryArgument::GetArgString() const
{
	VWFC_ASSERT(fpArgument);
	if (!fpArgument)
		return "";
	
	if (fpArgument->argType == kStringArgType || fpArgument->argType == kStringVarArgType || 
		fpArgument->argType == kCharDynarrayArgType || fpArgument->argType == kCharDynarrayVarArgType)
		return fpArgument->strValue;

	VWFC_ASSERT(false);

	return "";
}

void VWPluginLibraryArgument::SetArgString(const TXString& value) const
{
	VWFC_ASSERT( fpArgument );

	if ( fpArgument->argType != kStringVarArgType && fpArgument->argType != kStringInOutArgType ) {
		fpArgument->argType		= kStringArgType;
	}

	fpArgument->strValue = value;
}


//kCharArgType				// use charValue
//kCharVarArgType			// use charValue
UCChar VWPluginLibraryArgument::GetArgChar() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kCharArgType );
	return fpArgument->charValue;
}

UCChar& VWPluginLibraryArgument::GetArgCharVar()
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kCharVarArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kCharVarArgType;
	return fpArgument->charValue;
}

// kVoidPtr
void* VWPluginLibraryArgument::GetArgVoidPtr() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kVoidPtr );
	return fpArgument->voidData;
}

void VWPluginLibraryArgument::SetArgVoidPtr(void* ptr)
{
	VWFC_ASSERT( fpArgument );
	fpArgument->argType			= kVoidPtr;
	fpArgument->voidData		= ptr;
}

//kHandleArgType		// use handleValue
//kHandleVarArgType		// use handleValue
MCObjectHandle VWPluginLibraryArgument::GetArgHandle() const
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kHandleArgType );
	return (MCObjectHandle) fpArgument->handleValue;
}

MCObjectHandle& VWPluginLibraryArgument::GetArgHandleVar() const
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kHandleVarArgType || fpArgument->argType == kHandleInOutArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kHandleVarArgType;
	return (MCObjectHandle&) fpArgument->handleValue;
}

void VWPluginLibraryArgument::SetArgHandle(MCObjectHandle handle)
{
	VWFC_ASSERT( fpArgument );
	if ( fpArgument->argType != kHandleVarArgType && fpArgument->argType != kHandleInOutArgType ) {
		fpArgument->argType		= kHandleArgType;
	}
	fpArgument->handleValue	= (GSHandle) handle;
}

TXString VWPluginLibraryArgument::GetArgDynArrayChar() const
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kCharDynarrayArgType || fpArgument->argType == kStringArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kCharDynarrayArgType;

	return fpArgument->strValue;
}

void VWPluginLibraryArgument::SetArgDynArrayChar(const TXString& value)
{
	fpArgument->argType		= kCharDynarrayArgType;
	fpArgument->strValue	= value;
}

void VWPluginLibraryArgument::SetArgDynArrayCharVar(const TXString& value)
{
	fpArgument->argType		= kCharDynarrayVarArgType;
	fpArgument->strValue	= value;
}

void* VWPluginLibraryArgument::GetArgFunctionRef() const
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kFunctionkArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kFunctionkArgType;
	return fpArgument->voidData;
}

void* VWPluginLibraryArgument::GetArgProcedureRef() const
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kNullArgType || fpArgument->argType == kProcedureArgType) );
	if ( fpArgument->argType == kNullArgType ) fpArgument->argType = kProcedureArgType;
	return fpArgument->voidData;
}


// kPointerArgType		// use ptrValue
// kPointerVarArgType	// use ptrValue
void* VWPluginLibraryArgument::GetArgPointer() const
{
	VWFC_ASSERT( fpArgument && (fpArgument->argType == kPointerArgType || fpArgument->argType == kPointerVarArgType));
	return fpArgument->ptrValue;
}

void*& VWPluginLibraryArgument::GetArgPointerVar()
{
	VWFC_ASSERT( fpArgument && fpArgument->argType == kPointerVarArgType );
	return fpArgument->ptrValue;
}

void VWPluginLibraryArgument::SetArgPointer(void* ptr)
{
	VWFC_ASSERT( fpArgument );
	fpArgument->argType		= kPointerArgType;
	fpArgument->ptrValue	= ptr;
}

void* VWPluginLibraryArgument::GetArgDynArrayBuffer(size_t& outSize) const
{
	void* result = nullptr;

	VWFC_ASSERT( fpArgument );
	if ( VWFC_VERIFY( fpArgument && fpArgument->argType == kDynarrayArgType ) )
	{
		result	= fpArgument->arrayVar.buffer;
		outSize	= fpArgument->arrayVar.bufferSize;
	}

	return result;
}

EPluginLibraryArgType VWPluginLibraryArgument::GetArgDynArrayValuetype() const
{
	EPluginLibraryArgType result = kNullArgType;

	VWFC_ASSERT( fpArgument );
	if ( VWFC_VERIFY( fpArgument && fpArgument->argType == kDynarrayArgType ) )
	{
		result	= fpArgument->arrayVar.valueType;
	}

	return result;
}

Sint32 VWPluginLibraryArgument::GetArgDynArrayRowsCount() const
{
	Sint32 result = 0;
	VWFC_ASSERT( fpArgument );
	if ( VWFC_VERIFY( fpArgument && fpArgument->argType == kDynarrayArgType ) )
	{
		result = fpArgument->arrayVar.cntRows;
	}

	return result;
}

Sint32 VWPluginLibraryArgument::GetArgDynArrayColumnsCount() const
{
	Sint32 result = 0;
	VWFC_ASSERT( fpArgument );
	if ( VWFC_VERIFY( fpArgument && fpArgument->argType == kDynarrayArgType ) )
	{
		result = fpArgument->arrayVar.cntCols;
	}

	return result;
}

//kCharDynarrayArgType	// use dadValue
//kCharDynarrayVarArgType	// use dadValue
//kCharArrayVarArgType	// use dadValue
//kColorArgType			// use intValue
//kColorVarArgType		// use intValue
//kStyleArgType			// use styleValue

//kPointRecArgType		// use ptValue in SDK.  Use new "POINT" data structure in VS.  New for VW 10.
//kPointRecVarArgType		// use ptValue in SDK.  Use new "POINT" data structure in VS. New for VW 10.
//kPoint3DRecArgType		// use pt3Value in SDK. Use new "POINT3D" data structure in VS. New for VW 10.
//kPoint3DRecVarArgType	// use pt3Value in SDK. Use new "POINT3D" data structure in VS. New for VW 10. 
//kRGBColorRecArgType		// use colorVar in SDK. Use new "RGBCOLOR" data structure in VS. New for VW 10.
//kRGBColorRecVarArgType	// use colorVar in SDK. Use new "RGBCOLOR" data structure in VS. New for VW 10.
