//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// ----------------------------------------------------------------------------------------
		class WSCriteriaExpression
		{
		public:
						WSCriteriaExpression();
						WSCriteriaExpression(Handle compiled);
						WSCriteriaExpression(const void* compiledBuffer, size_t compiledBufferSize);
						WSCriteriaExpression(const std::vector<char>& compiledBuffer);
						WSCriteriaExpression(const WSCriteriaExpression& src);
			virtual		~WSCriteriaExpression();

			WSCriteriaExpression&	operator=(const WSCriteriaExpression& src);
			WSCriteriaExpression&	operator=(const std::vector<char>& compiledBuffer);

						operator Handle();

			bool		Compile(const TXString& criteriaExpression, VectorWorks::EExpressionContext context = eLocal);
			bool		Decompile(TXString& outCriteriaExpression);

			bool		CompileAndBase64Encode(const TXString& criteriaExpression, TXString& outData, VectorWorks::EExpressionContext context = eLocal);
			bool		Base64DecodeAndDecompile(const TXString& data, TXString& outCriteriaExpression);

			const void*	GetCompiledBuffer() const;
			size_t		GetCompiledBufferSize() const;

			// error access after 'Compile' fails with false
			VectorWorks::ECriteriaExpressionError	GetLastError() const;
			size_t									GetLastErrorOffset() const;

		// API
		public:
			bool		ExecWSExpression(MCObjectHandle h, VWVariant& outResult);
			bool		EvalWithCriteria(MCObjectHandle hObj);
			void		EvalWithCriteria(const std::vector<MCObjectHandle>& arrInputObjs, std::vector<MCObjectHandle>& outMatchedObjects);

		// Tools
		public:
			static bool	Base64Encode(const void* buffer, size_t bufferSize, TXString& outData);
			static bool	Base64Encode(const WSCriteriaExpression& criteria, size_t bufferSize, TXString& outData);
			static bool	Base64Decode(const TXString& data, std::vector<char>& outBuffer);
			static bool	Base64Decode(const TXString& data, WSCriteriaExpression& outCriteria);

		private:
			void	SetBuffer(const void* buffer, size_t bufferSize);

		private:
			Handle		fCompiled;

			VectorWorks::ECriteriaExpressionError	fLastError			= VectorWorks::ECriteriaExpressionError::None;
			size_t									fLastErrorOffset	= 0;
		};
	}
}
