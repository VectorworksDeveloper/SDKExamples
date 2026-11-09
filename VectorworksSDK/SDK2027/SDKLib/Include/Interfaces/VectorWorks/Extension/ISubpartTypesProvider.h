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
		class ISubpartTypesContext
		{
		public:
			virtual			~ISubpartTypesContext() {}
			virtual void	AddPartType(const TXString& univName, const TXString& localizedName) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {8B77901A-5458-4FFF-AA2D-D8F3C885301B}
		static const TSinkIID IID_SubpartTypesProvider = { 0x8b77901a, 0x5458, 0x4fff, { 0xaa, 0x2d, 0xd8, 0xf3, 0xc8, 0x85, 0x30, 0x1b } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ISubpartTypesProvider : public IEventSink
		{
		public:
			virtual void VCOM_CALLTYPE Enumerate(ISubpartTypesContext& context) = 0;
		};
	}
}
