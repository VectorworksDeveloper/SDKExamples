#pragma once

namespace VectorWorks
{
	namespace Licensing
	{
		namespace Legacy
		{
			/** @defgroup legacyConstants Legacy constants
				These constants were (are) used all throughout VW for licensing. We are moving towards a system that uses new constants
				that come from LDFs directly.
				@{
			*/

			//-----------------------------------------------
			// Legacy modules constants
			//-----------------------------------------------
			const uint32_t	kCodeFoundation = 0x00000000;
			const uint32_t	kCodeRenderWorks = 0x00000001;
			const uint32_t	kCodeArchitect = 0x00000002;
			const uint32_t	kCodeLandmark = 0x00000004;
			const uint32_t	kCodeSpotlight = 0x00000008;
			const uint32_t	kCodeMechanical = 0x00000010;
			const uint32_t	kCodePro = 0x00000020;
			const uint32_t	kCodeHomeBuilder = 0x00000040;
			const uint32_t  kCodeBraceworks = 0x00000080;
			const uint32_t  kCodeConnectCAD = 0x00000100;
			const uint32_t	kCodeThirdPartyModule5 = 0x00000200;
			const uint32_t	kCodeThirdPartyModule4 = 0x00000400;
			const uint32_t	kCodeThirdPartyModule3 = 0x00000800;
			const uint32_t	kCodeThirdPartyModule2 = 0x00001000;
			const uint32_t	kCodeThirdPartyModule1 = 0x00002000;

			/** This includes only thirdy-party modules (excludes NNA modules) */
			const uint32_t	kCodeThirdPartyModuleAll = kCodeThirdPartyModule1 | kCodeThirdPartyModule2 |
			kCodeThirdPartyModule3 | kCodeThirdPartyModule4 |
			kCodeThirdPartyModule5;

			/** The restricted product flag is used by default at application startup
				to prevent anything from working.  The high order bit is used
				since it's unlikely this will be used by any other product code.
			*/
			const uint32_t	kCodeRestricted = 0x80000000;  //-V112

			/** This includes only NNA modules */
			const uint32_t	kCodeAllNNAProducts = kCodeFoundation | kCodeRenderWorks | kCodeArchitect | kCodeLandmark | kCodeSpotlight | kCodeMechanical | kCodePro | kCodeBraceworks | kCodeConnectCAD;

			/** This includes all products including third-party modules */
			const uint32_t	kCodeAllProducts = 0x0FFFFFFF;

			//-----------------------------------------------
			// Legacy mode constants
			//-----------------------------------------------
			const uint16_t	kModeNotSet = 0;

			/** Obsolete, DO NOT USE in new code. Only used to check plug-in bits. */
			const uint16_t	kModeFull = 0x0001;

			const uint16_t	kModeDemo = 0x0002;

			/** Obsolete, DO NOT USE in new code. Only used to check plug-in bits. */
			const uint16_t	kModeEducation = 0x0004;

			/** Obsolete, DO NOT USE in new code. Only used to check plug-in bits. */
			const uint16_t	kModeStudent = 0x0008;

			/** Runs as a viewer application only.  No editing is allowed. */
			const uint16_t	kModeViewer = 0x0010;

			/** new for 10.0.0 */
			const uint16_t	kModeUnlicensed = 0x0020;

			/** Display 'educational' text in the caption area of the window. */
			const uint16_t	kModeBanner = 0x0040;

			/** Save new file with watermark tag files. */
			const uint16_t	kModeWatermarkNewFiles = 0x0080;

			/** new for 10.1.0 - Print watermarked tagged files with the watermark. */
			const uint16_t	kModePrintWatermark = 0x0100;

			/** new for 10.1.0 - Save files tagged as educational format. */
			const uint16_t	kModeSaveEducationalFileFmt = 0x0200;

			/** new for 10.1.0 - Open files tagged as educational format. */
			const uint16_t	kModeOpenEducationalFileFmt = 0x0400;

			/** new for 10.1.0 - Enable the export to VectorScript menu item? */
			const uint16_t	kModeVectorScriptExport = 0x0800;

			/** new for 10.1.0 - Does the user have a beta serial number? */
			const uint16_t	kModeBetaSN = 0x1000;

			/** The restricted mode is used by default at application startup
				to prevent anything from working.  The high order bit is used
				since it's unlikely this will be used by any other mode
			*/
			const uint16_t	kModeRestricted = 0x8000;

			const uint16_t	kAllModes = kModeFull | kModeDemo | kModeEducation | kModeStudent | kModeViewer |
			kModeUnlicensed | kModeBanner | kModeWatermarkNewFiles | kModePrintWatermark |
			kModeSaveEducationalFileFmt | kModeOpenEducationalFileFmt | kModeVectorScriptExport | kModeBetaSN;
			/*@}*/
		}
	}
}