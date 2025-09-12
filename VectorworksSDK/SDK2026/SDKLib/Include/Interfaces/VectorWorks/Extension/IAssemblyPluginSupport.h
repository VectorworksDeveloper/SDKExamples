//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
	
		static const VWIID IID_AssemblyPluginSupport = { 0xfec3b474, 0xd4fd, 0x4344, { 0xbb, 0x05, 0xa2, 0xc6, 0x1f, 0x50, 0x3e, 0x3c } };

		class DYNAMIC_ATTRIBUTE IAssemblyPluginSupport : public IVWSingletonUnknown
		{
		public:
			virtual void VCOM_CALLTYPE CreateAssembly() = 0;
			virtual std::vector<TXString> GetAssemblyUnitObjectTypeNames() = 0;
			virtual std::vector<TXString> GetAssemblyUnitObjectDisplayNames() = 0;
			virtual void VCOM_CALLTYPE ChangeAssemblyUnitType(MCObjectHandle h, TXString newUnitType) = 0;
			virtual void BeginStyleUpdate(MCObjectHandle symDefHandle) = 0;
			virtual bool AddUnitObjectToUpdateList(MCObjectHandle unit) = 0;
			virtual void EndStyleUpdate(MCObjectHandle symDefHandle) = 0;
			virtual bool GetUseUnitProvidedFramesForAssembly(MCObjectHandle assembly) = 0;
			// GetUnitOffsetReferenceForAssembly returns the localized string for the selected setting (Interior/Center/Exterior of frame)
			virtual TXString GetUnitOffsetReferenceForAssembly(MCObjectHandle assembly) = 0;
			virtual void VCOM_CALLTYPE DistributeSpacing() = 0;
			virtual void VCOM_CALLTYPE DistributeCenterlines() = 0;
			
		};
	
	   	typedef VCOMPtr<IAssemblyPluginSupport> IAssemblyPluginSupportPtr;
	}
}
