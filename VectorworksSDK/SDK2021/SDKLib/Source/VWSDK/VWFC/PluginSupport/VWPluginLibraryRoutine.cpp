//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC//PluginSupport/VWPluginLibraryRoutine.h"


using namespace VWFC::PluginSupport;

VWPluginLibraryRoutine::VWPluginLibraryRoutine()
{
}

VWPluginLibraryRoutine::~VWPluginLibraryRoutine()
{
}

void VWPluginLibraryRoutine::SetUserData(SintptrT userData)
{
}

SintptrT VWPluginLibraryRoutine::GetUserData() const
{
	return 0;
}

VCOMError VWPluginLibraryRoutine::RegisterInterfaces(void* pModule)
{
	return kVCOMError_NoError;
}

void VWPluginLibraryRoutine::CreateInterfaceInstance(const VWIID& iid, IVWUnknown** ppOutInterface)
{
	if ( ppOutInterface ) {
		*ppOutInterface	= NULL;
	}
}

void VWPluginLibraryRoutine::DeleteInterfaceInstance(const VWIID& iid, IVWUnknown* pInterface)
{
}
