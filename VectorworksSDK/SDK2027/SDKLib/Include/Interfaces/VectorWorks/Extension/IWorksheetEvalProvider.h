//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {A6F71D3C-3C0E-4911-B0D2-5956E0BDC191}
		static const Extension::TSinkIID IID_WorksheetEvalProvider = { 0xa6f71d3c, 0x3c0e, 0x4911, { 0xb0, 0xd2, 0x59, 0x56, 0xe0, 0xbd, 0xc1, 0x91 } };

		class DYNAMIC_ATTRIBUTE IWorksheetEvalProvider : public Extension::IEventSink
		{
		public:
			virtual void	VCOM_CALLTYPE OnBeforeEval(MCObjectHandle hObject) = 0;
		};
	}
}