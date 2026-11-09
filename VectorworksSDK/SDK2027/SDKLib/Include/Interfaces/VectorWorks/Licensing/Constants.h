#pragma once

#include <vector>
#include <set>

#include "LegacyConstants.h"

namespace VectorWorks
{
	namespace Licensing
	{
		/// Enum meta-data structure that holds extra information on how the value is represented as enum, json or legacy bitfield value.
		template<class T>
		struct EnumMetadata
		{
			T enumValue;
			const char* jsonValue;
			uint32_t bitfieldValue;
		};

		// Intentionally left undefined, so that we can't use enum meta-data for types we didn't specialize it for.
		template<class T>
		inline const std::vector<EnumMetadata<T>>& GetEnumMetaData();

		template<class BasicJsonType, class T>																		
		inline void GetEnumValueForJson(const BasicJsonType& j, T& e)
		{																									
			e = GetEnumMetaData<T>().front().enumValue;
			for (auto& meta : GetEnumMetaData<T>()) {
				if (meta.jsonValue && meta.jsonValue == j) {
					e = meta.enumValue;
				}
			}																								
		}

		template<class T>
		inline uint32_t GetBitfieldFromEnumSet(const std::set<T>& set)
		{
			uint32_t legacyBitfield = 0;
			for (auto& meta : GetEnumMetaData<T>()) {
				if (set.find(meta.enumValue) != set.end()) {
					legacyBitfield |= meta.bitfieldValue;
				}
			}

			return legacyBitfield;
		}

		template<class T>
		inline std::set<T> GetEnumSetFromBitfield(uint32_t bitfield)
		{
			std::set<T> set;
			for (auto& meta : GetEnumMetaData<T>()) {
				if (bitfield & meta.bitfieldValue) {
					set.insert(meta.enumValue);
				}
			}

			return set;
		}

		/// All enums are serialized to JSON strings. See the declarations after each enum.
		#define LDF_ENUM_METADATA(ENUM_TYPE, ...)																	\
			template<>																								\
			inline const std::vector<EnumMetadata<ENUM_TYPE>>& GetEnumMetaData()									\
			{																										\
				static_assert(std::is_enum<ENUM_TYPE>::value, #ENUM_TYPE " must be an enum!");						\
				static const std::vector<EnumMetadata<ENUM_TYPE>> metadata = __VA_ARGS__;							\
				return metadata;																					\
			}																										\
			template<class BasicJsonType>																			\
			inline void from_json(const BasicJsonType& j, ENUM_TYPE& e)												\
			{																										\
				 GetEnumValueForJson(j, e);																			\
			}


		enum class ProtectionType
		{
			kNone,
			/// Series E
			kInternet,
			/// Series B
			kDongle,
			/// Series G
			kSiteProtection
		};

		LDF_ENUM_METADATA(ProtectionType, {
			{ProtectionType::kNone, nullptr},
			{ProtectionType::kInternet, "internet"},
			{ProtectionType::kDongle, "dongle"},
			{ProtectionType::kSiteProtection, "site-protection"},
		})

		enum class Product
		{
			kNone,
			kVectorworks,
			kVision
		};

		LDF_ENUM_METADATA(Product, {
			{Product::kNone, nullptr},
			{Product::kVectorworks, "vectorworks"},
			{Product::kVision, "vision"},
		})

		enum class RenewalMethod
		{
			kNone,
			/// Perpetual and trial licenses fall into the non-renewing category
			NonRenewing,
			/// Perpetual VSS
			ServiceSelect,
			SubscriptionMontly,
			SubscriptionAnnual
		};

		LDF_ENUM_METADATA(RenewalMethod, {
			{RenewalMethod::kNone, nullptr},
			{RenewalMethod::NonRenewing, "non-renewing"},
			{RenewalMethod::ServiceSelect, "service-select"},
			{RenewalMethod::SubscriptionMontly, "subscription-monthly"},
			{RenewalMethod::SubscriptionAnnual, "subscription-annual"}
		})

		enum class Module
		{
			kNone,
			kFundamentals,
			kArchitect,
			kLandmark,
			kMechanical,
			kSpotlight,
			kBraceworks,
			kConnectCAD = 7,
			// Keep legacy Third Party modules values 8-12 reserved and undefined, so that old VS extensions 
			// that check for them are always disabled.
			kInteriorCAD = 13,
			kInteriorCADXS,
			kVectorwop,
			kSosiworks
		};

		LDF_ENUM_METADATA(Module, {
			{Module::kNone, nullptr},
			{Module::kFundamentals,	"fundamentals",		Legacy::kCodeFoundation},
			{Module::kArchitect,	"architect",		Legacy::kCodeArchitect},
			{Module::kLandmark,		"landmark",			Legacy::kCodeLandmark},
			{Module::kMechanical,	"mechanical",		Legacy::kCodeMechanical},
			{Module::kSpotlight,	"spotlight",		Legacy::kCodeSpotlight},
			{Module::kBraceworks,	"braceworks",		Legacy::kCodeBraceworks},
			{Module::kConnectCAD,	"connectcad",		Legacy::kCodeConnectCAD},

			// Modules below are new and have no legacy counterpart, so they are mapped to kCodeFoundation (0).
			// This ensures that doing a legacy-to-enum map will never return these modules no matter the input bitfield,
			// and that enum-to-legacy map will never set any bits for these modules.
			{Module::kInteriorCAD,	"interiorcad",		Legacy::kCodeFoundation},
			{Module::kInteriorCADXS,"interiorcadxs",	Legacy::kCodeFoundation},
			{Module::kVectorwop,	"vectorwop",		Legacy::kCodeFoundation},
			{Module::kSosiworks,	"sosiworks",		Legacy::kCodeFoundation},
		})

		enum class LicenseFlag
		{
			kNone,
			kDemo,
			kViewer,
			kEducationalBanner,
			kNewFilesAreWatermarked,
			kPrintWithWatermark,
			kSaveAsEducationalFileFormat,
			kOpenEducationalFileFormat,
			kAllowVectorscriptExport,
			kServiceSelectBenefits,
            kSubscriberBenefits
		};

		LDF_ENUM_METADATA(LicenseFlag, {
			{LicenseFlag::kNone,						nullptr,							Legacy::kModeNotSet},
			{LicenseFlag::kDemo,						"demo",								Legacy::kModeDemo},
			{LicenseFlag::kViewer,						"viewer",							Legacy::kModeViewer},
			{LicenseFlag::kEducationalBanner,			"educational-banner",				Legacy::kModeBanner},
			{LicenseFlag::kNewFilesAreWatermarked,		"new-files-are-watermarked",		Legacy::kModeWatermarkNewFiles},
			{LicenseFlag::kPrintWithWatermark,			"print-with-watermark",				Legacy::kModePrintWatermark},
			{LicenseFlag::kSaveAsEducationalFileFormat, "save-as-educational-file-format",	Legacy::kModeSaveEducationalFileFmt},
			{LicenseFlag::kOpenEducationalFileFormat,	"open-educational-file-format",		Legacy::kModeOpenEducationalFileFmt},
			{LicenseFlag::kAllowVectorscriptExport,		"allow-vectorscript-export",		Legacy::kModeVectorScriptExport},
			{LicenseFlag::kServiceSelectBenefits,		"service-select-benefits",			Legacy::kModeNotSet},
            {LicenseFlag::kSubscriberBenefits,          "subscriber-benefits",              Legacy::kModeNotSet}
		})

		enum class ApplicationMode
		{
			kNone,
			/// Standard license
			kFull,
			/// For educational institutions, these typically use an educational file format.
			kTeacherProFileFormat,
			kTeacherEduFileFormat,
			kStudentProFileFormat,
			kStudentEduFileFormat,
			kStudentLabSeat
		};

		LDF_ENUM_METADATA(ApplicationMode, {
			{ApplicationMode::kNone,				 nullptr,					Legacy::kModeNotSet},
			{ApplicationMode::kFull,				 "full",					Legacy::kModeFull},
			{ApplicationMode::kTeacherProFileFormat, "teacher-pro-file-format",	Legacy::kModeEducation},
			{ApplicationMode::kTeacherEduFileFormat, "teacher-edu-file-format",	Legacy::kModeEducation},
			{ApplicationMode::kStudentProFileFormat, "student-pro-file-format",	Legacy::kModeStudent},
			{ApplicationMode::kStudentEduFileFormat, "student-edu-file-format", Legacy::kModeStudent},
			{ApplicationMode::kStudentLabSeat,		 "student-lab-seat",		Legacy::kModeEducation},
		})

		enum class LicenseClass
		{
			kNone,
			/// Standard license
			kPro,
			/// For marketing and promotions
			kNFR,
			/// Trials are time-limited
			kTrial,
			/// For educational institutions, these typically use an educational file format, but not always.
			kAcademic
		};

		LDF_ENUM_METADATA(LicenseClass, {
			{LicenseClass::kNone,		nullptr},
			{LicenseClass::kPro,		"pro"},
			{LicenseClass::kNFR,		"nfr"},
			{LicenseClass::kTrial,		"trial"},
			{LicenseClass::kAcademic,	"academic"},	
		})

		enum class NFRType
		{
			kNone,
			/// Reserved for our internal systems.
			kSystem,
			/// For Vectorworks employees, these are typically used for internal testing and development.
			kEmployee,
		};

		LDF_ENUM_METADATA(NFRType, {
			{NFRType::kNone,	 nullptr},
			{NFRType::kSystem,   "system"},
			{NFRType::kEmployee, "employee"},
		})


		using LicenseFlagSet     = std::set<LicenseFlag>;
		using ModuleSet		     = std::set<Module>;
		using ApplicationModeSet = std::set<ApplicationMode>;

		// These are special constants meant to be used in ILicense::IsAny(*)Enabled functions for Modules, LicenseTypes and LicenseFlags.
		// They are not really part of the LDFs as they represent a set of things, but are convenient so that developers don't
		// have to be overly specific when checking for licensing conditions.
		const ApplicationMode kAnyApplicationMode			 = static_cast<ApplicationMode>(-1);
		const ApplicationMode kAnyEducationalApplicationMode = static_cast<ApplicationMode>(-3);

		const LicenseFlag kAnyLicenseFlag = static_cast<LicenseFlag>(-1);

		// Fundamentals is always present, so this is just a more obvious way to type it when searching for it.
		const Module kAnyModule = Module::kFundamentals;
		const Module kAnyDesignSeriesModule = static_cast<Module>(-2);

		struct S2SInfo
		{
			TXString	fCustomerPortalURL;
			unsigned	fDaysBeforeContractExpiration;
			bool		fbDaysBeforeContractExpirationIsNull;
			bool		fDisplay30DaysWarning;
			bool		fDisplay60DaysWarning;
			bool		fCanTransitionToSubcription;
		};
	}
}
