//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// --------------------------------------------------------------------------------------------------

		// {36b89a33-ef1d-48a0-b6f2-981c1a34acd5}
		static const VWIID IID_VCOMGrade = { 0x36b89a33, 0xef1d, 0x48a0, {0xb6, 0xf2, 0x98, 0x1c, 0x1a, 0x34, 0xac, 0xd5} };
	
		class IGradeObjectSupport : public IVWSingletonUnknown
		{

		public:
			// Creates a grade object
			virtual MCObjectHandle VCOM_CALLTYPE Create(const WorldPt3& start, const WorldPt3& end) = 0;
	
			// ---------------------------------------------------------------------------
			typedef VCOMPtr<IGradeObjectSupport>	IGradeObjectSupportPtr;
		};
	}
}
