//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

using namespace VWFC::Tools;

CChangeTrackingSystemContext::CChangeTrackingSystemContext()
{
	gSDK->Kludge(7541, nullptr, nullptr);
}

CChangeTrackingSystemContext::~CChangeTrackingSystemContext()
{
	gSDK->Kludge(7542, nullptr, nullptr);
}

