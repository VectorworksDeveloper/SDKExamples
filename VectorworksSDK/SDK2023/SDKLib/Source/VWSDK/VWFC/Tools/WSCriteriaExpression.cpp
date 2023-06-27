//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;

WSCriteriaExpression::WSCriteriaExpression()
	: fCompiled( nullptr )
{
}

WSCriteriaExpression::WSCriteriaExpression(Handle compiled)
	: fCompiled( compiled )
{
}

WSCriteriaExpression::WSCriteriaExpression(const void* compiledBuffer, size_t compiledBufferSize)
	: fCompiled( nullptr )
{
	this->SetBuffer( compiledBuffer, compiledBufferSize );
}

WSCriteriaExpression::WSCriteriaExpression(const std::vector<char>& compiledBuffer)
	: fCompiled( nullptr )
{
	if ( compiledBuffer.size() > 0 )
	{
		this->SetBuffer( &compiledBuffer[ 0 ], compiledBuffer.size() );
	}
}

WSCriteriaExpression::WSCriteriaExpression(const WSCriteriaExpression& src)
	: fCompiled( nullptr )
{
	this->SetBuffer( src.GetCompiledBuffer(), src.GetCompiledBufferSize() );
}

WSCriteriaExpression::~WSCriteriaExpression()
{
	if ( fCompiled )
		gVWMM->DisposeHandle( fCompiled );
	fCompiled = nullptr;
}

WSCriteriaExpression& WSCriteriaExpression::operator=(const WSCriteriaExpression& src)
{
	this->SetBuffer( src.GetCompiledBuffer(), src.GetCompiledBufferSize() );
	return *this;
}

WSCriteriaExpression& WSCriteriaExpression::operator=(const std::vector<char>& compiledBuffer)
{
	if ( compiledBuffer.size() > 0 )
	{
		this->SetBuffer( &compiledBuffer[ 0 ], compiledBuffer.size() );
	}
	else if ( fCompiled )
	{
		gVWMM->DisposeHandle( fCompiled );
		fCompiled = nullptr;
	}

	return *this;
}

void WSCriteriaExpression::SetBuffer(const void* buffer, size_t bufferSize)
{
	if ( fCompiled )
	{
		gVWMM->DisposeHandle( fCompiled );
		fCompiled = nullptr;
	}

	if ( buffer && bufferSize )
	{
		fCompiled = gVWMM->NewHandle( bufferSize );
		if ( fCompiled && *fCompiled )
		{
			memcpy( *fCompiled, buffer, bufferSize );
		}
	}
}

WSCriteriaExpression::operator Handle()
{
	return fCompiled;
}

bool WSCriteriaExpression::Compile(const TXString& criteriaExpression, VectorWorks::EExpressionContext context)
{
	fLastError = VectorWorks::ECriteriaExpressionError::None;
	fLastErrorOffset = 0;

	auto theErrorCallback = [&](ECriteriaExpressionError err, size_t errOffset)
	{
		fLastError = err;
		fLastErrorOffset = errOffset;
	};

	fCompiled = gSDK->CompileCriteriaExpression( criteriaExpression, theErrorCallback, context);
	return fCompiled;
}

bool WSCriteriaExpression::Decompile(TXString& outCriteriaExpression)
{
	return gSDK->DecompileCriteriaExpression( fCompiled, outCriteriaExpression );
}

bool WSCriteriaExpression::CompileAndBase64Encode(const TXString& criteriaExpression, TXString& outData, VectorWorks::EExpressionContext context)
{
	outData.Clear();
	bool	result	= false;

	if ( this->Compile(criteriaExpression, context) )
	{
		const void* pBuffer		= this->GetCompiledBuffer();
		size_t		bufferSize	= this->GetCompiledBufferSize();

		if ( pBuffer && bufferSize )
		{
			result	= this->Base64Encode(pBuffer, bufferSize, outData);
		}
	}

	return result;
}

bool WSCriteriaExpression::Base64DecodeAndDecompile(const TXString& data, TXString& outCriteriaExpression)
{
	outCriteriaExpression.Clear();
	bool	result	= false;

	if ( this->Base64Decode( data, *this ) )
	{
		result	= this->Decompile(outCriteriaExpression);
	}

	return result;
}

const void* WSCriteriaExpression::GetCompiledBuffer() const
{
	return fCompiled ? *fCompiled : nullptr;
}

size_t WSCriteriaExpression::GetCompiledBufferSize() const
{
	return gVWMM->GetHandleSize( fCompiled );
}

VectorWorks::ECriteriaExpressionError WSCriteriaExpression::GetLastError() const
{
	return fLastError;
}

size_t WSCriteriaExpression::GetLastErrorOffset() const
{
	return fLastErrorOffset;
}

bool WSCriteriaExpression::ExecWSExpression(MCObjectHandle h, VWVariant& outResult)
{
	bool result = false;
	if ( VERIFYN( kVStanev, fCompiled ) )
		result = gSDK->ExecWSExpression( h, fCompiled, outResult );

	return result;
}

bool WSCriteriaExpression::EvalWithCriteria(MCObjectHandle hObj)
{
	bool result = false;
	if ( VERIFYN( kVStanev, fCompiled ) )
		result = gSDK->EvalWithCriteria( hObj, fCompiled );

	return result;
}

void WSCriteriaExpression::EvalWithCriteria(const std::vector<MCObjectHandle>& arrInputObjs, std::vector<MCObjectHandle>& outMatchedObjects)
{
	if ( VERIFYN( kVStanev, fCompiled ) )
	{
		gSDK->EvalWithCriteria( arrInputObjs, fCompiled, outMatchedObjects );
	}
}

/*static*/ bool WSCriteriaExpression::Base64Encode(const void* buffer, size_t bufferSize, TXString& outData)
{
	bool result = false;

	using namespace VectorWorks::Filing;
	IXMLFilePtr xmlFile( IID_XMLFile );
	if ( VERIFYN( kVStanev, xmlFile ) )
		result = xmlFile->Base64Encode( buffer, bufferSize, outData );

	return result;
}

/*static*/ bool WSCriteriaExpression::Base64Encode(const WSCriteriaExpression& criteria, size_t bufferSize, TXString& outData)
{
	bool result = false;

	using namespace VectorWorks::Filing;
	IXMLFilePtr xmlFile( IID_XMLFile );
	if ( VERIFYN( kVStanev, xmlFile ) )
		result = xmlFile->Base64Encode( criteria.GetCompiledBuffer(), criteria.GetCompiledBufferSize(), outData );

	return result;
}

/*static*/ bool WSCriteriaExpression::Base64Decode(const TXString& data, std::vector<char>& outBuffer)
{
	bool result = false;

	using namespace VectorWorks::Filing;
	IXMLFilePtr xmlFile( IID_XMLFile );
	if ( VERIFYN( kVStanev, xmlFile ) )
		result = xmlFile->Base64Decode( data, outBuffer );

	return result;
}

/*static*/ bool WSCriteriaExpression::Base64Decode(const TXString& data, WSCriteriaExpression& outCriteria)
{
	bool result = false;

	using namespace VectorWorks::Filing;
	IXMLFilePtr xmlFile( IID_XMLFile );
	if ( VERIFYN( kVStanev, xmlFile ) )
	{
		std::vector<char>	buffer;
		result = xmlFile->Base64Decode( data, buffer );
		outCriteria = buffer;
	}

	return result;
}

