//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace VWFC
{
	using namespace Tools;
	
	namespace PluginSupport
	{
		// ---------------------------------------------------------------------------------
		class VWPluginLibraryArgTable;
		class VWPluginLibraryArgument
		{
			friend class VWPluginLibraryArgTable;
		public:
			virtual			~VWPluginLibraryArgument();

			short			GetArgInteger() const;
			short&			GetArgIntegerVar();
			void			SetArgInteger(short value);

			Sint32			GetArgLong() const;
			Sint32&			GetArgLongVar();
			void			SetArgLong(Sint32 value);

			double_gs		GetArgReal() const;
			double_gs&		GetArgRealVar();
			void			SetArgReal(double_gs value);

			double_gs		GetArgAngle() const;
			void			SetArgAngle(double_gs value);

			double_gs		GetArgDistance() const;
			void			SetArgDistance(double_gs value);

			_WorldPt		GetArgPoint() const;
			_WorldPt&		GetArgPointVar();
			void			SetArgPoint(const _WorldPt& value);

			_WorldPt3		GetArg3DPoint() const;
			_WorldPt3&		GetArg3DPointVar();
			void			SetArg3DPoint(const _WorldPt3& value);

			_WorldPt3		GetArgVector() const;
			_WorldPt3&		GetArgVectorVar();
			void			SetArgVector(const _WorldPt3& value);

			Boolean			GetArgBoolean() const;
			Boolean&		GetArgBooleanVar();
			void			SetArgBoolean(Boolean value);

			TXString		GetArgString() const;
			void			SetArgString(const TXString& value) const;

			UCChar			GetArgChar() const;
			UCChar&			GetArgCharVar();

			void*			GetArgVoidPtr() const;
			void			SetArgVoidPtr(void* ptr);

			MCObjectHandle	GetArgHandle() const;
			MCObjectHandle&	GetArgHandleVar() const;
			void			SetArgHandle(MCObjectHandle handle);

			TXString		GetArgDynArrayChar() const;
			void			SetArgDynArrayChar(const TXString& value);
			void			SetArgDynArrayCharVar(const TXString& value);

			void*			GetArgFunctionRef() const;
			void*			GetArgProcedureRef() const;

			void*			GetArgPointer() const;
			void*&			GetArgPointerVar();
			void			SetArgPointer(void* ptr);

			// The returned poiter is a the array memory of the specified 'valueType' (kIntegerArgType would mean two bytes per item)
			// The memory can be broken into two dim array by scripting using 'GetArgDynArrayColumnsCount'
			// The returned poiter will be 'nullptr' if the type is not correct
			// Note: Python does not have kIntegerArgType, it will pass kLongArgType for integer numbers
			//
			// Example 1: -- type independent traversal
			//
			//		size_t	bufferSize	= 0;
			//		void*	buffer		= arg.GetArgDynArrayBuffer( bufferSize );
			//		Sint32	rowsCnt		= arg.GetArgDynArrayRowsCount();
			//		if (arg.GetArgDynArrayValuetype() == kIntegerArgType || arg.GetArgDynArrayValuetype() == kLongArgType )
			//		{
			//			size_t	elemSizeOf	= bufferSize / rowsCnt;
			//			Uint8*	elemMem		= (Uint8*)buffer;
			//			for(size_t i=0; i<rowsCnt; i++)
			//			{
			//				Sint16&	data	= *(Sint16*)elemMem;
			//				DMSG((kEveryone, "%d\n", data));
			//	
			//				elemMem += elemSizeOf;
			//			}
			//
			//
			// Example 2: - type dependent
			//
			//		size_t bufferSize = 0;
			//		void*  buffer = arg.GetArgDynArrayBuffer( bufferSize );
			//		if ( arg.GetArgDynArrayValuetype() == kIntegerArgType )
			//		{
			//			size_t	dataCnt	= bufferSize / sizeof(Sint16);
			//			Sint16* data	= (Sint16*)buffer;
			//			for(size_t i=0; i<dataCnt; i++)
			//				data[i] = data[i] + 1;
			//
			void*					GetArgDynArrayBuffer(size_t& outSize) const;
			EPluginLibraryArgType	GetArgDynArrayValuetype() const;
			Sint32					GetArgDynArrayRowsCount() const;
			Sint32					GetArgDynArrayColumnsCount() const;

		protected:
							VWPluginLibraryArgument();

			PluginLibraryArg*		fpArgument;
		};

		
		// ---------------------------------------------------------------------------------
		class VWPluginLibraryArgTable
		{
		public:
										VWPluginLibraryArgTable();
										VWPluginLibraryArgTable(PluginLibraryArgTable* pArgTable);
			virtual						~VWPluginLibraryArgTable();

			VWPluginLibraryArgument&	GetArgument(size_t index);
			VWPluginLibraryArgument&	GetResult();

										operator PluginLibraryArgTable*();
		private:
			PluginLibraryArgTable		fNewArgTable;
			PluginLibraryArgTable*		fpArgTable;
			VWPluginLibraryArgument		farrArguments[ kMaxPluginLibraryArgs ];
			VWPluginLibraryArgument		fResultArgument;
		};
	}
}