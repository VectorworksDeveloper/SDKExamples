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
			/// Perpetual, NFR and trial licenses fall into the non-renewing category
			NonRenewing,
			/// Perpetual VSS
			ServiceSelect,
			SubscriptionMontly,
			SubscriptionYearly
		};

		LDF_ENUM_METADATA(RenewalMethod, {
			{RenewalMethod::kNone, nullptr},
			{RenewalMethod::NonRenewing, "non-renewing"},
			{RenewalMethod::ServiceSelect, "service-select"},
			{RenewalMethod::SubscriptionMontly, "subscription-monthly"},
			{RenewalMethod::SubscriptionYearly, "subscription-yearly"}
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
			kConnectCAD,
			kThirdParty1,
			kThirdParty2,
			kThirdParty3,
			kThirdParty4,
			kThirdParty5
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
			{Module::kThirdParty1,	"third-party-1",	Legacy::kCodeThirdPartyModule1},
			{Module::kThirdParty2,	"third-party-2",	Legacy::kCodeThirdPartyModule2},
			{Module::kThirdParty3,	"third-party-3",	Legacy::kCodeThirdPartyModule3},
			{Module::kThirdParty4,	"third-party-4",	Legacy::kCodeThirdPartyModule4},
			{Module::kThirdParty5,	"third-party-5",	Legacy::kCodeThirdPartyModule5},
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
			kServiceSelectBenefits
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
			{LicenseFlag::kServiceSelectBenefits,		"service-select-benefits",			Legacy::kModeNotSet}
		})

		enum class LicenseType
		{
			kNone,
			/// For Devs
			kInternal,
			/// Standard license
			kProfessional,
			/// For marketing and promotions
			kNotForResale,
			/// For educational institutions, these typically use an educational file format.
			kEducationalStudentLabSeat,
			kEducationalStudent,
			kEducationalTeacher,
			/// Uses a time-limited eval token
			kEvaluation
		};

		LDF_ENUM_METADATA(LicenseType, {
			{LicenseType::kNone,						nullptr,						Legacy::kModeNotSet},
			{LicenseType::kInternal,					"internal",						Legacy::kModeFull},
			{LicenseType::kProfessional,				"professional",					Legacy::kModeFull},
			{LicenseType::kNotForResale,				"not-for-resale",				Legacy::kModeFull},
			{LicenseType::kEducationalStudentLabSeat,	"educational-student-lab-seat",	Legacy::kModeEducation},
			{LicenseType::kEducationalStudent,			"educational-student",			Legacy::kModeStudent},
			{LicenseType::kEducationalTeacher,			"educational-teacher",			Legacy::kModeEducation},
			{LicenseType::kEvaluation,					"evaluation",					Legacy::kModeFull},
		})

		using LicenseFlagSet = std::set<LicenseFlag>;
		using ModuleSet		 = std::set<Module>;
		using LicenseTypeSet = std::set<LicenseType>;

		// These are special constants meant to be used in ILicense::IsAny(*)Enabled functions for Modules, LicenseTypes and LicenseFlags.
		// They are not really part of the LDFs as they represent a set of things, but are convenient so that developers don't
		// have to be overly specific when checking for licensing conditions.
		const LicenseType kAnyLicenseType  = static_cast<LicenseType>(-1);
		const LicenseType kAnyFullLicenseType = static_cast<LicenseType>(-2);
		const LicenseType kAnyEducationalLicenseType = static_cast<LicenseType>(-3);

		const LicenseFlag kAnyLicenseFlag = static_cast<LicenseFlag>(-1);

		// Fundamentals is always present, so this is just a more obvious way to type it when searching for it.
		const Module kAnyModule = Module::kFundamentals;
		const Module kAnyDesignSeriesModule = static_cast<Module>(-2);
	}
}