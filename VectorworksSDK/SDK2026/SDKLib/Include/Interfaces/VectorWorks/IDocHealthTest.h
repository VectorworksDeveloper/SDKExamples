//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace DocumentHealth
	{
		// ----------------------------------------------------------------------------------------------------
		// {9CCFFB58-0DF6-42BA-A53D-3057B4B0843B}
		static const VWGroupID GROUPID_DocHealthTest = { 0x9ccffb58, 0xdf6, 0x42ba, { 0xa5, 0x3d, 0x30, 0x57, 0xb4, 0xb0, 0x84, 0x3b } };


		// ----------------------------------------------------------------------------------------------------
		enum class EHealthTestCategory
		{
			eGeometry,
			eSettings,
			eResources,
			eNone,
			eEnd
		};
	
		enum class EHealthTestUse // to filter out tests
		{
			ePublicTest,
			eDeveloperTest
		};

		enum class ERealType
		{
			eReal = kEditReal,
			eAngle = kEditAngle,
			eDimension = kEditDimension,
			eCoordX = kEditCoordinateX,
			eCoordY = kEditCoordinateY
		};
	
		struct STestParameter {
			TXString fName;
			TXString fDescription;
			TVariableBlock fValue;
			TVariableBlock fMinValue;
			TVariableBlock fMaxValue;
			ERealType fRealType = ERealType::eReal;
		};

		struct STestInfo {
			TXString fName;
			TXString fDescription;
			TXString fFixConfirmation;	// to be asked before the fix starts
			EHealthTestCategory fCategory = EHealthTestCategory::eNone;
			EHealthTestUse fUse = EHealthTestUse::ePublicTest;
		};
	
		class IHealthTest;
		using IHealthTestPtr = VCOMPtr<IHealthTest>;

		class IHealthTestEnvironment;
		class IHealthTestCommunicationInterface;

		// ----------------------------------------------------------------------------------------------------

		class IHealthTestCommunicationInterface
		{
		public:
			IHealthTestCommunicationInterface(IHealthTestEnvironment* inEnv):fEnv(inEnv) {};
			virtual				~IHealthTestCommunicationInterface() {}

			// this is called by the tests to report problematic objects;
			// Please, see the description of the ReportError method in the IHealthTestEnvironment class.
			virtual void		ReportError(const std::vector<MCObjectHandle>& inObjects, bool inProblemIsInsideContainer, const TXString& inError, bool fixAvailable = false) = 0;
			virtual	bool		GetTestConfiguration(std::vector<STestParameter>& outTestParameters) = 0;

		protected:
			IHealthTestEnvironment* fEnv = nullptr;
			
		};

		// ----------------------------------------------------------------------------------------------------
		class IHealthTestEnvironment
		{
		public:
			virtual				~IHealthTestEnvironment()		{}
			
			virtual	std::map<IHealthTestPtr, STestInfo>		ListAllTests() = 0;
			virtual	void		ExecuteAllTests() = 0;
			virtual	void		ExecuteTest(const IHealthTestPtr inTest) = 0;
			virtual	void		ConfigureTest(const IHealthTestPtr inTest) = 0;
			// inTest = nullptr means active test
			virtual	bool		GetTestConfiguration(std::vector<STestParameter>& outTestParameters, const IHealthTestPtr inTest = nullptr) = 0;

			// this is called by the tests to report problematic objects;
			// If there are multiple top level objects, which share the same error, they can be reported as a vector;
			// Each object will be shown separately in the list of results.
			// Note!!! If, for example, multiple connected lines are found inside a profile of a high level object, only the parent container should be reported.
			// 
			// inProblemIsInsideContainer == true means that the reported object is the parent container for offending objects. 
			// For example, if a problem is found in a profile of an extrude, the extrude should be reported, and inProblemIsInsideContainer == true;
			// if a problem is found in a profile group of a parametric, the profile group should be reported, and inProblemIsInsideContainer == true;
			// if the offending object is the parametric itself, it should be reported, and inProblemIsInsideContainer == false;
			virtual void		ReportError(const std::vector<MCObjectHandle>& inObjects, bool inProblemIsInsideContainer, const TXString& inError, bool inFixAvailable = false) = 0;

		public:

			IHealthTestPtr fActiveTest = nullptr;
			
		};

		// ----------------------------------------------------------------------------------------------------
		class IHealthTest : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetTestInfo(STestInfo& outTestInfo) const { outTestInfo = fTestInfo; return kVCOMError_NoError; };
			virtual VCOMError VCOM_CALLTYPE GetTestParameters(std::vector<STestParameter>& outTestParameters) const { outTestParameters = fTestParameters; return kVCOMError_NoError; };
			virtual VCOMError VCOM_CALLTYPE RunTest(IHealthTestCommunicationInterface* inEnv) = 0;

			// Fixes the selected objects. The list of UUID's is sorted
			virtual VCOMError VCOM_CALLTYPE RunFix(IHealthTestCommunicationInterface* inEnv, const std::vector<UuidStorage>& inSelection) { return kVCOMError_NotImplemented; };

		protected:
			STestInfo						fTestInfo;
			std::vector<STestParameter>	fTestParameters;	 // default values provided by the test; ConfigureTest can be used to change them
		};

		
	}
}

