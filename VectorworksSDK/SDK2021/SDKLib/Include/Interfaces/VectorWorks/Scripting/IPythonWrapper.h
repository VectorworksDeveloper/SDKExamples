//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Scripting
	{
		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IPythonLogger
		{
			public:
				virtual ~IPythonLogger() {}

				virtual void VCOM_CALLTYPE LogStdOut(const char* msg) = 0;
				virtual void VCOM_CALLTYPE LogStdErr(const char* msg) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		class IPythonWrapperInitListenerContext
		{
		public:
			virtual			~IPythonWrapperInitListenerContext()	{}
			virtual bool	LoadModule(const TXString& moduleName) = 0;
			virtual bool	LoadModule(const TXString& moduleName, void* memory, size_t memorySize) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		class IPythonWrapperInitListener
		{
		public:
			virtual			~IPythonWrapperInitListener()	{}
			virtual void	Init(IPythonWrapperInitListenerContext* context) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		// {196DB14F-F32C-445E-A785-15E16CAB9E83}
		static const VWIID IID_PythonWrapper = { 0x196db14f, 0xf32c, 0x445e, { 0xa7, 0x85, 0x15, 0xe1, 0x6c, 0xab, 0x9e, 0x83 } };

		class DYNAMIC_ATTRIBUTE IPythonWrapper : public IVWUnknown
		{
		public:
			// this function must be the first call of a new instance of this interface
			// in order for the python environment to be created with this logger
			virtual void		VCOM_CALLTYPE InitLogger(IPythonLogger* logger) = 0; 

			virtual void		VCOM_CALLTYPE AddPath(const char* path) = 0;
			virtual void		VCOM_CALLTYPE AddInitListener(IPythonWrapperInitListener* listener) = 0;

			virtual bool		VCOM_CALLTYPE CompileText(const char* pythonCode) = 0;
			virtual void		VCOM_CALLTYPE RunText(const char* pythonCode) = 0;
			virtual bool		VCOM_CALLTYPE Call(const char* functionName, const TXStringArray& arrParams) = 0;
			virtual bool		VCOM_CALLTYPE Call(const char* moduleName, const char* functionName, const TXStringArray& arrParams) = 0;
	
			virtual TXString	VCOM_CALLTYPE GetCallResult() const = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPythonWrapper>	IPythonWrapperPtr;
	}
}

// Utility classes for IPythonWrapper class
namespace VectorWorks
{
	namespace Scripting
	{
		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE CDefaultPythonLogger : public IPythonLogger
		{
		public:
			CDefaultPythonLogger()				{}
			virtual ~CDefaultPythonLogger()		{}

		public:
			virtual void VCOM_CALLTYPE LogStdOut(const char* msg) { fOutput += msg; }
			virtual void VCOM_CALLTYPE LogStdErr(const char* msg) { fErrors += msg; }

		public:
			TXString		fOutput;
			TXString		fErrors;
		};
	}
}