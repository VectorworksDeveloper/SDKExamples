//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#ifndef CatchSystemTest_h
#define CatchSystemTest_h

#define CATCH_CHECK CPPUNIT_ASSERT
#define CATCH_REQUIRE CPPUNIT_ASSERT_RETURN
#define CATCH_SECTION(unused) {}

/*#define CATCH_CONFIG_PREFIX_ALL
#include "catch.hpp"*/

// ================================================================================================
//These functions are for use in Catch-style system tests.
extern VectorWorks::Debug::ISystemTestEnvironment* gTestEnv;
void RunCatchTest(int argc, char** argv);

inline VWIID GenWeakVWIID(const char* str)

{
	VWIID iid;
	unsigned char* bytes = (unsigned char*)&iid;
	memset(bytes, 0, sizeof(iid));
	size_t len = strlen(str);
	for( size_t i=0; i<len; i++ )
		bytes[i%sizeof(iid)] ^= str[i];
	return iid;
}
// Use this in your Catch tests to open and, specifically, to ensure that the 
// file closes when a REQUIRE fails -- because REQUIRE throws an exception and 
// TEST_OpenDocument's destructor will run which will close the file.
//
class TEST_OpenDocument
{
public:
	TEST_OpenDocument(const std::string& relativeFilePath, bool inbShowErrorMessages = false);
	//Opens a new empty file
	TEST_OpenDocument();
	~TEST_OpenDocument();
	bool IsOpened();
	std::string AbsoluteFolderPath();
private:
	bool fOpened = false;
	std::string fAbsoluteFolderPath;
};
// VW_TEST_CASE documentation:
// For example usage search in files for VW_TEST_CASE.
// This style of writing automated tests (call it "Catch" style named after the Catch2 library) has a few rules:
// 1. When you declare VW_TEST_CASE(..) then the code below it will automatically run when VW autobuilds (depending the on third parameter).
// 2. Use REQUIRE as the assert mechanism
// 3. When an REQUIRE fails the code below it will not run because REQUIRE throws an exception so use destructors for clean up
// 4. SECTION is not required but is useful.  SECTION creates a new branch of an execution tree.  The TEST_CASE code will be called for every path to leaf nodes in said tree, e.g.:
//		This code:
//		VW_TEST_CASE(...) {
//			SECTION("A") {
//				SECTION("C") {
//				}
//				SECTION("D") {
//					SECTION("G") {
//					}
//				}
//			}
//			SECTION("B") {
//				SECTION("E") {
//				}
//				SECTION("F") {
//				}
//			}
//		}
//		will generate an execution tree like this:
//                      R for root
//                    /   \
//                 A         B
//                / \       / \
//               C   D     E   F
//                   |
//                   G   
//	the VW_TEST_CASE code will be called 4 times because there are 4 leaf sections and the paths will be RAC, RADG, RBE, RBF
//
#define VW_TEST_CASE( TestName, email, runType)														\
	class TestName : public VCOMImmediateImpl<VectorWorks::Debug::ISystemTest>					\
	{																								\
		CPPUNIT_TEST_SUITE2(TestName, #TestName, #email, runType);									\
		CPPUNIT_TEST(testFunc, "testFunc");														\
		CPPUNIT_TEST_SUITE_END();																	\
	public:																							\
		virtual void setUp() { gTestEnv = GetTestEnv();}																		\
		virtual void tearDown() {}																	\
		void testFunc();																		\
	};																								\
	REGISTER_CATCH_TEST(TestName)																	\
	void TestName::testFunc()
	

#ifdef _MINICAD_
#include "../Core/Source/Interfaces/StandardInterfacesManager.h"

extern std::vector<std::function<bool(EStandardInterfaceManagerMapState, SStandardInterfaceManagerMapData&)>>& CatchTests();

#define REGISTER_CATCH_TEST(TestName)																															\
	struct REGISTER##TestName {																																	\
		REGISTER##TestName() {																																	\
			VWIID Piid = GenWeakVWIID(#TestName);																												\
			CatchTests().push_back([Piid](EStandardInterfaceManagerMapState state, SStandardInterfaceManagerMapData& data) {									\
				switch( state ) {																																\
					case EStandardInterfaceManagerMapState::eStandardInterfaceManagerMapState_Register:	::GS_VWRegisterInterface( Piid, VectorWorks::Debug::GROUPID_SystemTest, NULL );	break;						\
					case EStandardInterfaceManagerMapState::eStandardInterfaceManagerMapState_GetName:		if ( data.iid == Piid ) { data.name	= (const char*) #TestName; return true; } break;	\
					case EStandardInterfaceManagerMapState::eStandardInterfaceManagerMapState_New:			if ( data.iid == Piid ) { data.pInterface = new TestName(); return true; } break;		\
					case EStandardInterfaceManagerMapState::eStandardInterfaceManagerMapState_Delete:		if ( data.iid == Piid ) { delete (TestName*) data.pInterface; return true; } break;		\
					default: break;																																\
				}																																				\
				return false;																																	\
			});																																					\
		}																																						\
	} gRegister##TestName;

#define	REGISTER_CATCH_SYSTEMTESTS		for( auto& test : CatchTests() ) if( test(state, data) ) return true;

#else

extern std::vector<std::function<void(Sint32 action, void* moduleInfo, const VWIID& iid, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)>>& CatchTests();

#define REGISTER_CATCH_TEST(TestName)																																		\
	struct REGISTER##TestName {																																				\
		REGISTER##TestName() {																																				\
			VWIID Piid = GenWeakVWIID(#TestName);																															\
			CatchTests().push_back([Piid](Sint32 action, void* moduleInfo, const VWIID& iid, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply) {					\
				VWFC::PluginSupport::REGISTER_SystemTest<TestName>(Piid, action, moduleInfo, iid, inOutInterface, cbp, reply);												\
			});																																								\
		}																																									\
	} gRegister##TestName;

//Call this in your plugin ModuleMain.cpp, in your plugin_module_main function.  
#define REGISTER_CATCH_SYSTEMTESTS(action, moduleInfo, iid, inOutInterface, cbp, reply) for(auto& test : CatchTests()) {	test(action, moduleInfo, iid, inOutInterface, cbp, reply); }
#endif

#endif
