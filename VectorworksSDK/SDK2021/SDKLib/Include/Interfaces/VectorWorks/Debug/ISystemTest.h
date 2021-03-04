//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Debug
	{
		// ----------------------------------------------------------------------------------------------------
		// {32ACD895-4572-406e-B32F-F9325824A77C}
		static const VWGroupID GROUPID_SystemTest = { 0x32acd895, 0x4572, 0x406e, { 0xb3, 0x2f, 0xf9, 0x32, 0x58, 0x24, 0xa7, 0x7c } };

		// ----------------------------------------------------------------------------------------------------
		enum class ESystemTestType
		{
			  Generic
			, SpecialRun	// test that are executed one-by-one and generaly output specific data, or do speciif work
		};

		// ----------------------------------------------------------------------------------------------------
		class ISystemTestEnvironment
		{
		public:
			virtual				~ISystemTestEnvironment()		{}
			virtual	void		Fail(const TXString& msg, const TXString& file, size_t line) = 0;
			virtual void		Message(const TXString& msg, const TXString& file, size_t line) = 0;
			virtual size_t		GetParametersCount() = 0;
			virtual TXString	GetParameterAt(size_t at) = 0;
			virtual void		ExecuteAgain(Uint32 timeoutMilisec) = 0;
			virtual bool		GetTestFileDirectory(VectorWorks::Filing::IFolderIdentifierPtr& testFilesDir) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		class ISystemTest : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetTestName(TXString& outName, VectorWorks::Debug::ESystemTestType& outType) = 0;
			virtual VCOMError VCOM_CALLTYPE GetTextEMail(TXString& outEMail) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSubTestsCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSubTestName(size_t subTestIndex, TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE Execute(ISystemTestEnvironment* pEnv) = 0;
			virtual VCOMError VCOM_CALLTYPE Execute(size_t subTestIndex, ISystemTestEnvironment* pEnv) = 0;
		};

		typedef VCOMPtr<ISystemTest>		ISystemTestPtr;
	}
}

// =================================================================================================
// Macro definitions to make it look like CPPUNIT

// =================================================================================================
// =================================================================================================
#define CPPUNIT_TEST_SUITE2(PClass, PName, PEMail, PType)											\
	private:																						\
		typedef PClass	TThisClass;																	\
		typedef void (TThisClass::*TFunction)();													\
		struct SSystemTestDef {																		\
			SSystemTestDef(const char* szName, TFunction pFunc) {										\
				fszSystemTestName	= szName;															\
				fpSystemTestFunc	= pFunc;															\
			}																						\
			const char* fszSystemTestName;															\
			TFunction	fpSystemTestFunc;																\
		};																							\
		std::vector<SSystemTestDef>	farrSystemTest;													\
		VectorWorks::Debug::ISystemTestEnvironment*		fpLocalEnv;														\
	public:																							\
		virtual VCOMError VCOM_CALLTYPE GetTestName(TXString& outName, VectorWorks::Debug::ESystemTestType& outType) {	\
			outName = PName;																		\
			outType = PType;																		\
			return kVCOMError_NoError; }															\
		virtual VCOMError VCOM_CALLTYPE GetTextEMail(TXString& outEMail) {							\
			outEMail = PEMail;																		\
			return kVCOMError_NoError; }															\
		virtual VCOMError VCOM_CALLTYPE GetSubTestsCount(size_t& outCount) {						\
			farrSystemTest.clear();																	\
	// end CPPUNIT_TEST_SUITE2 definition

//--------------------------------------------------------------------------------------------------
#define CPPUNIT_TEST_SUITE(PClass, PName, PEMail)													\
	CPPUNIT_TEST_SUITE2( PClass, PName, PEMail, VectorWorks::Debug::ESystemTestType::Generic )							\
	// end CPPUNIT_TEST_SUITE2 definition

//--------------------------------------------------------------------------------------------------
#define CPPUNIT_TEST( PFunction, PName )															\
	farrSystemTest.push_back( SSystemTestDef( PName, &TThisClass::PFunction ) );						\
	// end CPPUNIT_TEST definition
//--------------------------------------------------------------------------------------------------
#define CPPUNIT_TEST_SUITE_END()																	\
			outCount	= farrSystemTest.size();														\
			return kVCOMError_NoError;																\
		} /* GetSubTestsCount */																	\
		virtual VCOMError VCOM_CALLTYPE GetSubTestName(size_t subTestIndex, TXString& outName) {	\
			VCOMError	err	= kVCOMError_Failed;													\
			if ( subTestIndex < farrSystemTest.size() ) {												\
				outName	= farrSystemTest[subTestIndex].fszSystemTestName;								\
				err		= kVCOMError_NoError;														\
			}																						\
			return err;																				\
		}																							\
		virtual VCOMError VCOM_CALLTYPE Execute(VectorWorks::Debug::ISystemTestEnvironment* pEnv) {						\
			fpLocalEnv			= pEnv;																\
			size_t	testsCnt	= farrSystemTest.size();												\
			this->GetSubTestsCount( testsCnt );														\
			testsCnt			= farrSystemTest.size();												\
			if ( testsCnt > 0 ) {																	\
				this->setUp();																		\
				for(size_t i=0; i<testsCnt; i++) {													\
					TFunction	pFunction	= farrSystemTest[i].fpSystemTestFunc;						\
					if ( pFunction ) {																\
						(this->*pFunction)();														\
					}																				\
				}																					\
				this->tearDown();																	\
			}																						\
			fpLocalEnv				= NULL;															\
			return kVCOMError_NoError;																\
		}																							\
		virtual VCOMError VCOM_CALLTYPE Execute(size_t subTestIndex, VectorWorks::Debug::ISystemTestEnvironment* pEnv) {	\
			VCOMError	err		= kVCOMError_Failed;												\
			size_t	testsCnt	= farrSystemTest.size();												\
			this->GetSubTestsCount( testsCnt );														\
			if ( subTestIndex < farrSystemTest.size() ) {												\
				fpLocalEnv				= pEnv;														\
				TFunction	pFunction	= farrSystemTest[subTestIndex].fpSystemTestFunc;				\
				if ( pFunction ) {																	\
					(this->*pFunction)();															\
					fpLocalEnv				= NULL;													\
					err						= kVCOMError_NoError;									\
				}																					\
			}																						\
			return err;																				\
		}																							\
		void		failIf(bool bCondition, const TXString& msg, const char* szFile, size_t line) {	\
			if ( bCondition ) {																		\
				ASSERTN( kVStanev, fpLocalEnv );													\
				fpLocalEnv->Fail( msg, szFile, line );												\
			}																						\
		}																							\
		VectorWorks::Debug::ISystemTestEnvironment* GetTestEnv() {														\
			return fpLocalEnv;																		\
		}																							\
	// end CPPUNIT_TEST_SUITE_END definition
//--------------------------------------------------------------------------------------------------
#define CPPUNIT_ASSERT(condition)																	\
		( this->failIf(		!(condition),															\
							TXString(	"Assertion Failed"											\
										"Expression: " #condition),									\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_ASSERT definition
//--------------------------------------------------------------------------------------------------
// variant on assert which, when failing, calls return
#define CPPUNIT_ASSERT_RETURN(condition)															\
{ 																									\
	bool expr = condition;																			\
	this->failIf(			!expr,																	\
							TXString(	"Assertion Failed"											\
										"Expression: " #condition),									\
							__FILE__, __LINE__ ); 													\
	if( !expr )																						\
	{																								\
		return;																						\
	}																								\
}																									\
	// end CPPUNIT_ASSERT_RETURN definition
//--------------------------------------------------------------------------------------------------
// No expression. Expression containing Unicode characters should use this one.
#define CPPUNIT_ASSERT_NE(condition)																\
		( this->failIf(		!(condition),															\
							TXString(	"Assertion Failed" ),										\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_ASSERT_NE definition
//--------------------------------------------------------------------------------------------------
#define CPPUNIT_ASSERT_MESSAGE(message,condition)													\
		( this->failIf(		!(condition),															\
                            TXString(	"Assertion Failed"											\
                                        "Expression: "												\
										#condition ": " ) +	message,								\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_ASSERT_MESSAGE definition
//--------------------------------------------------------------------------------------------------
#define CPPUNIT_FAIL( message )                                    									\
		( this->failIf(		true,																	\
							TXString( "Forced Failure: " ) + message, 								\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_FAIL definition
//--------------------------------------------------------------------------------------------------
#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message,expected,actual)										\
 		( this->failIf(		!(expected==actual),													\
							TXString( "Assertion Failed: " ) + message,								\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_ASSERT_EQUAL_MESSAGE definition
#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected,actual,delta)											\
 		( this->failIf(		!(Abs(expected-actual)<delta),											\
							TXString( "Assertion Failed!" ),										\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_ASSERT_DOUBLES_EQUAL definition
#define CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(message,expected,actual,delta)							\
 		( this->failIf(		!(Abs(expected-actual)<delta),											\
							TXString( "Assertion Failed: " ) + message,								\
							__FILE__, __LINE__ ) )													\
	// end CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE definition
// ================================================================================================
