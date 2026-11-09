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
		static const VWGroupID GROUPID_UnitTest = { 0x32acd895, 0x4572, 0x406e, { 0xb3, 0x2f, 0xf9, 0x32, 0x58, 0x24, 0xa7, 0x7c } };

		// ----------------------------------------------------------------------------------------------------
		enum class EUnitTestType
		{
			  Generic
			, SpecialRun	// test that are executed one-by-one and generaly output specific data, or do speciif work
		};

		// ----------------------------------------------------------------------------------------------------
		class IUnitTestEnvironment
		{
		public:
			virtual				~IUnitTestEnvironment()		{}
			virtual	void		Fail(const TXString& msg, const TXString& file, size_t line) = 0;
			virtual void		Message(const TXString& msg, const TXString& file, size_t line) = 0;
			virtual size_t		GetParametersCount() = 0;
			virtual TXString	GetParameterAt(size_t at) = 0;
			virtual void		ExecuteAgain(Uint32 timeoutMilisec) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		class IUnitTest : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetTestName(TXString& outName, EUnitTestType& outType) = 0;
			virtual VCOMError VCOM_CALLTYPE GetTextEMail(TXString& outEMail) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSubTestsCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSubTestName(size_t subTestIndex, TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE Execute(IUnitTestEnvironment* pEnv) = 0;
			virtual VCOMError VCOM_CALLTYPE Execute(size_t subTestIndex, IUnitTestEnvironment* pEnv) = 0;
		};

		typedef VCOMPtr<IUnitTest>		IUnitTestPtr;
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
		struct SUnitTestDef {																		\
			SUnitTestDef(const char* szName, TFunction pFunc) {										\
				fszUnitTestName	= szName;															\
				fpUnitTestFunc	= pFunc;															\
			}																						\
			const char* fszUnitTestName;															\
			TFunction	fpUnitTestFunc;																\
		};																							\
		std::vector<SUnitTestDef>	farrUnitTest;													\
		IUnitTestEnvironment*		fpLocalEnv;														\
	public:																							\
		virtual VCOMError VCOM_CALLTYPE GetTestName(TXString& outName, EUnitTestType& outType) {	\
			outName = PName;																		\
			outType = PType;																		\
			return kVCOMError_NoError; }															\
		virtual VCOMError VCOM_CALLTYPE GetTextEMail(TXString& outEMail) {							\
			outEMail = PEMail;																		\
			return kVCOMError_NoError; }															\
		virtual VCOMError VCOM_CALLTYPE GetSubTestsCount(size_t& outCount) {						\
			farrUnitTest.clear();																	\
	// end CPPUNIT_TEST_SUITE2 definition

//--------------------------------------------------------------------------------------------------
#define CPPUNIT_TEST_SUITE(PClass, PName, PEMail)													\
	CPPUNIT_TEST_SUITE2( PClass, PName, PEMail, EUnitTestType::Generic )							\
	// end CPPUNIT_TEST_SUITE2 definition

//--------------------------------------------------------------------------------------------------
#define CPPUNIT_TEST( PFunction, PName )															\
	farrUnitTest.push_back( SUnitTestDef( PName, &TThisClass::PFunction ) );						\
	// end CPPUNIT_TEST definition
//--------------------------------------------------------------------------------------------------
#define CPPUNIT_TEST_SUITE_END()																	\
			outCount	= farrUnitTest.size();														\
			return kVCOMError_NoError;																\
		} /* GetSubTestsCount */																	\
		virtual VCOMError VCOM_CALLTYPE GetSubTestName(size_t subTestIndex, TXString& outName) {	\
			VCOMError	err	= kVCOMError_Failed;													\
			if ( subTestIndex < farrUnitTest.size() ) {												\
				outName	= farrUnitTest[subTestIndex].fszUnitTestName;								\
				err		= kVCOMError_NoError;														\
			}																						\
			return err;																				\
		}																							\
		virtual VCOMError VCOM_CALLTYPE Execute(IUnitTestEnvironment* pEnv) {						\
			fpLocalEnv			= pEnv;																\
			size_t	testsCnt	= farrUnitTest.size();												\
			this->GetSubTestsCount( testsCnt );														\
			testsCnt			= farrUnitTest.size();												\
			if ( testsCnt > 0 ) {																	\
				this->setUp();																		\
				for(size_t i=0; i<testsCnt; i++) {													\
					TFunction	pFunction	= farrUnitTest[i].fpUnitTestFunc;						\
					if ( pFunction ) {																\
						(this->*pFunction)();														\
					}																				\
				}																					\
				this->tearDown();																	\
			}																						\
			fpLocalEnv				= NULL;															\
			return kVCOMError_NoError;																\
		}																							\
		virtual VCOMError VCOM_CALLTYPE Execute(size_t subTestIndex, IUnitTestEnvironment* pEnv) {	\
			VCOMError	err		= kVCOMError_Failed;												\
			size_t	testsCnt	= farrUnitTest.size();												\
			this->GetSubTestsCount( testsCnt );														\
			if ( subTestIndex < farrUnitTest.size() ) {												\
				fpLocalEnv				= pEnv;														\
				TFunction	pFunction	= farrUnitTest[subTestIndex].fpUnitTestFunc;				\
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
		IUnitTestEnvironment* GetTestEnv() {														\
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
