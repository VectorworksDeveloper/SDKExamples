#pragma once

#include "Constants.h"

namespace VectorWorks
{
	namespace Licensing
	{
		// {2B298396-B410-4A9E-8FCD-519F406A8101}
		static const VWIID IID_License = { 0x2b298396, 0xb410, 0x4a9e, { 0x8f, 0xcd, 0x51, 0x9f, 0x40, 0x6a, 0x81, 0x1 } };

		class DYNAMIC_ATTRIBUTE ILicense : public IVWSingletonUnknown
		{
		public:
			// Returns the full set of modules enabled by the current License. For ProtectionType::kSiteProtection,
			// these will be determined by the selection of modules in the login dialog and not just the LDF.
			virtual ModuleSet VCOM_CALLTYPE GetModules() = 0;
			virtual bool VCOM_CALLTYPE IsModuleEnabled(Module module) = 0;
			// Returns true if any of the modules in the given set are enabled.
			virtual bool VCOM_CALLTYPE IsAnyModuleEnabled(const ModuleSet& moduleSet) = 0;
			// Returns true if we *only* have the base (fundamentals) module enabled.
			virtual bool VCOM_CALLTYPE IsFundamentals() = 0;
			// Returns true if any of Architect, Landmark or Spotlight are enabled
			virtual bool VCOM_CALLTYPE IsAnyDesignSeriesModuleEnabled() = 0;
			// Disables the modules if they are currently enabled
			virtual void VCOM_CALLTYPE DisableModules(const ModuleSet& modules) = 0;

			virtual LicenseFlagSet VCOM_CALLTYPE GetLicenseFlags() = 0;
			virtual bool VCOM_CALLTYPE IsLicenseFlagEnabled(LicenseFlag flag) = 0;
			// Returns true if any of the flags in the given set are enabled.
			virtual bool VCOM_CALLTYPE IsAnyLicenseFlagEnabled(const LicenseFlagSet& flagSet) = 0;

			// Returns the license type, will be LicenseType::kNone for Demo and Viewer.
			virtual LicenseType VCOM_CALLTYPE GetLicenseType() = 0;
			virtual bool VCOM_CALLTYPE IsEducational() = 0;
			// Returns true for time-limited trial licenses using eval-tokens.
			virtual bool VCOM_CALLTYPE IsEvaluation() = 0;
			// Returns true for demo licenses that have no serial and time-limit, but with no file save allowed.
			virtual bool VCOM_CALLTYPE IsDemo() = 0;
			// Returns true for VW Viewer application.
			virtual bool VCOM_CALLTYPE IsViewer() = 0;
			// Returns true for full mode licenses, such as Professional, Internal, NFR and Eval.
			virtual bool VCOM_CALLTYPE IsFull() = 0;

			// Returns the protection type (series), will be ProtectionType::kNone for Demo and Viewer.
			virtual ProtectionType VCOM_CALLTYPE GetProtectionType() = 0;

			virtual TXString VCOM_CALLTYPE GetDistributorCode() = 0;
			virtual TXString VCOM_CALLTYPE GetLicenseSuffix() = 0;
			virtual TXString VCOM_CALLTYPE GetLicenseID() = 0;

			// Returns true if the specified combination of modules AND (flags OR types) are enabled.
			virtual bool VCOM_CALLTYPE IsFlaggedAvailable(const ModuleSet& modules, const LicenseFlagSet& flagSet, const LicenseTypeSet& licenseTypes) = 0;
		};

		typedef VCOMPtr<ILicense> ILicensePtr;
	}
}