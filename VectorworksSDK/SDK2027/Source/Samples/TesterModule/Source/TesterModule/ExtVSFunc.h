#pragma once

namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CExtVSFuncs : public VWExtensionVSFunctions
	{
		DEFINE_VWVSFunctions;
	public:
										CExtVSFuncs(CallBackPtr cbp);
		virtual							~CExtVSFuncs();

	};


	// ------------------------------------------------------------------------------------------------------
	class CMyVSRoutines : public VWPluginLibraryRoutine
	{
	public:
											CMyVSRoutines();
		virtual								~CMyVSRoutines();

	public:
		// dispatch routine
		DEFINE_LIB_DISPATCH_MAP;

		// dispatch event functions
		//void				<function name>(VWPluginLibraryArgTable& argTable);
		void	OnAdd(VWPluginLibraryArgTable& argTable);
	};
}