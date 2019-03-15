#pragma once

namespace VGS
{
	struct Operation;
}

namespace VectorWorks
{
	namespace Extension
	{
		namespace VGS
		{
			// ---------------------------------------------------------------------------------------------------
			// {C15C61EF-3A7C-4637-B095-77B1C97F154D}
			static const VWIID IID_VGS = { 0xc15c61ef, 0x3a7c, 0x4637,{ 0xb0, 0x95, 0x77, 0xb1, 0xc9, 0x7f, 0x15, 0x4d } };

			class DYNAMIC_ATTRIBUTE IVGS : public IEventSink
			{
			public:
				virtual	bool VCOM_CALLTYPE IsRegistered(const TXString& inRenderEngineID) = 0;
				virtual bool VCOM_CALLTYPE Register(const TXString& inRenderEngineID, std::function<void(::VGS::Operation&)> inRenderPluginCallback) = 0;
				virtual bool VCOM_CALLTYPE Unregister(const TXString& inRenderEngineID) = 0;
				virtual bool VCOM_CALLTYPE GetActiveSceneId(uint64_t& outSceneId) = 0;
			};
		}
	}
}