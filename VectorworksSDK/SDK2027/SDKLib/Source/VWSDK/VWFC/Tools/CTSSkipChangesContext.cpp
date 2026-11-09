//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

using namespace VWFC::Tools;

TSkipChangesState::TSkipChangesState(MCObjectHandle h)
	: context(IID_SkipChangesContext)
{
	context->Setup(h);
}

TSkipChangesState::~TSkipChangesState()
{
	context->Cleanup();
	context = nullptr;
}
