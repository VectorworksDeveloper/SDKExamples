//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	// ------------------------------------------------------------------------------------------------------------------------------------
	// {88861F32-310F-4E54-8675-D06F0FAA5C40}
	static const VWIID IID_SustainabilityData = { 0x88861f32, 0x310f, 0x4e54, { 0x86, 0x75, 0xd0, 0x6f, 0xf, 0xaa, 0x5c, 0x40 } };

	// ------------------------------------------------------------------------------------------------------------------------------------
    class DYNAMIC_ATTRIBUTE ISustainabilityData : public IVWUnknown
	{
	public:
		virtual void	Load(const TXString& data) = 0;		// JSON storage
		virtual void	Save(TXString& outData) = 0;		// JSON storage
		virtual void	Load(MCObjectHandle hObject) = 0;	// FormatRecord storage
		virtual void	Save(MCObjectHandle hObject) = 0;	// FormatRecord storage
		virtual void	RemoveAll(MCObjectHandle hObject) = 0;

		struct SAttachedFramework
		{
			TXString	fFrameworkName;
			TXString	fFrameworkDisplay;
		};

		virtual void		GetAvailableFrameworks(TXStringSTLArray& outArr) = 0;
		virtual void		GetAttachedFrameworks(std::vector<SAttachedFramework>& outArr) = 0;
		virtual TXString	GetFrameworkDisplay(size_t index) = 0;
		virtual bool		EditFramework(size_t index, MCObjectHandle context) = 0;
		virtual void		SetFramework(size_t index, const TXString& frameworkName) = 0;
		virtual void		DeleteFramework(size_t index) = 0;
		virtual bool		GetSimpleValue(const TXString& frameworkName, double& outValue, TXString& outName) = 0;	// when outName is empty, it will default to "Value"
		virtual bool		SetSimpleValue(const TXString& frameworkName, double value) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	typedef VCOMPtr<ISustainabilityData>	ISustainabilityDataPtr;
}
