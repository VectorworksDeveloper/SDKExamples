//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Contains four-character OSType codes for VW resources, Apple resources,
// file types, creator codes, etc.
//
// Note: for some platforms we would need to use Apple's FOUR_CHAR_CODE() macro,
// but for now we don't.
//

#pragma once

// XXX_JDW_ALTURA - organize and label these. More defined in ResourceByteSwap.cpp

// ***NOTE*** if the file version has changed. Change the string value of OST_CreatorCode to the new version and add a new define of the form, OST_CreatorVWXX for the previous version.

/* Miscellaneous Resource Types, Filetypes, and Creator Codes */
#define OST_SpcSpcSpcSpc  '    '
#define OST_ListTXT     '#TXT'
#define OST_PctBangPS   '%!PS'
#define OST_ATTR        'ATTR'
#define OST_AZIM		'AZIM'
#define OST_BLU2        'BLU2'	// VectorWorks Lt application creator code
#define OST_BUGS        'BUGS'	// Resource holding debugging preferences for VW - not used
#define OST_CADF        'CADF'	// Old, obsolete filetype (3-D?)
#define OST_CADP        'CADP'
#define OST_CADT        'CADT'	// Old, obsolete filetype (3-D?)
#define OST_CCUS        'CCUS'
#define OST_CDP3        'CDP3'	// Pre-VectorWorks 12 application creator code

// *** File_Version_Advanced - Major - Initial One Time Change REQUIRED: update OST_CreatorCode to new version.
#define OST_CreatorCode	'VW27'	// VectorWorks Application Creator Code; See VectorWorks.r, "plist" discussion for more information regarding changing creator codes.
								// Also know that we will be changing creator codes for every version upto 20.

// *** File_Version_Advanced - Major - Initial One Time Change REQUIRED: add new creator code constant for old version.
#define OST_Creator26	'VW26'	// Creator code for VW 26
#define OST_Creator25	'VW25'	// Creator code for VW 25
#define OST_Creator24	'VW24'	// Creator code for VW 24
#define OST_Creator23	'VW23'	// Creator code for VW 23
#define OST_Creator22	'VW22'	// Creator code for VW 22
#define OST_Creator21	'VW21'	// Creator code for VW 21
#define OST_Creator20	'VW20'	// Creator code for VW 20
#define OST_Creator19	'VW19'	// Creator code for VW 19
#define OST_Creator18	'VW18'	// Creator code for VW 18
#define OST_Creator17	'VW17'	// Creator code for VW 17
#define OST_Creator16	'VW16'	// Creator code for VW 16
#define OST_Creator15	'VW15'	// Creator code for VW 15	
#define OST_Creator14	'VW14'	// Creator code for VW 14
#define OST_Creator13	'VW13'	// Creator code for VW 13
#define OST_Creator12	'VW12'	// Creator code for VW 12
#define OST_CHtc        'CHtc'	// Obsolete hatch resource
#define OST_CPrf        'CPrf'	// Obsolete Cam preferences resource
#define OST_data        'data'	// Mac-only, or Byte[] - NOT BYTESWAPPED ON WINDOWS
#define OST_dmsg        'dmsg'
#define OST_DMSN        'DMSN'
#define OST_MRKR		'MRKR'
#define OST_dosc        'dosc'
#define OST_DPat        'DPat'
#define OST_EPSF        'EPSF'
#define OST_FDPR		'FDPR'	// Required by Fancy Door External (MiniCAD 6 era, obsolete)
#define OST_File		'File'
#define	OST_FMap		'FMap'
#define OST_Guid		'Guid'	// Guides class attributes
#define OST_GSTx		'GSTx'	// Same as TEXT but QuickTime doesn't know about it so doesn't clobber it. B042728
#define OST_itxt        'itxt'
#define OST_KCHR        'KCHR'
#define	OST_LWCV		'LWCV'
#define OST_MPlusPf     'M+Pf'	// VectorWorks Preferences handle
#define OST_PPos		'PPos'	// Apparently obsolete palette position resource for workspaces
#define OST_MITM        'MITM'
#define OST_MMNU        'MMNU'
#define OST_MPEd		'MPEd'
#define OST_MPSSpc      'MPS '
#define OST_MPXI        'MPXI'
#define OST_OEdF        'OEdF'
#define OST_OEd2        'OEd2'	// VectorWorks workspace, pre-9.0.1
#define OST_OEd3        'OEd3'	// VectorWorks workspace, post-9.0.1
#define OST_OEky        'OEky'
#define OST_OEmu        'OEmu'	// External command filetype
#define OST_OEtl        'OEtl'	// External tool filetype
#ifndef OST_PALT
#define OST_PALT        'PALT'
#endif
#define OST_PXRX        'PXRX'
#define OST_RMri        'RMri'
#define OST_scod        'scod'
#define OST_SLTH		'SLTH'	// New Slash Thickness resource - states slash thickness in mils
#define OST_snd			'snd '
#define OST_SPAL        'SPAL'	// Workspace/overlay resource - Obsolete in VW8
#define	OST_Splt		'Splt'	// Polygon split limit for printing
#define OST_SPrf		'SPrf'	// Required by Shutter External - Obsolete in VW8
#define OST_STAK        'STAK'	// Mac stack info - Obsolete with Carbon in VW9.5
#define OST_TBLT        'TBLT'
#define OST_TDef        'TDef'
#define OST_TOOL        'TOOL'
#define OST_TSTL		'TSTL'	// Required by Dialog Help View class, version 1
#define OST_ttxt        'ttxt'	// SimpleText application creator code
#define OST_UNIT        'UNIT'
#define OST_UNT2		'UNT2'
#define OST_UNT3		'UNT3'
#define OST_Wall        'Wall'
#define OST_XCOD        'XCOD'
#define OST_MicroBulletDB 'DB'
#define OST_PDef		'PDef'	// SDK Plug-in Object - definition resource
#define OST_PDEf		'PDEf'	// SDK Plug-in Object - definition resource to replace OST_PDef. New for VW 10
#define OST_PARM		'PARM'	// SDK Plug-in Object - parameter resource
#define OST_Prm			'Prm#'	// SDK Plug-in Object - parameter resource to replace OST_PDef. New for VW 10
#define OST_Chc			'Chc#'	// SDK Plug-in Object - parameter resource to hold popup choices. New for VW 10
#define OST_POpt		'POpt'	// SDK Plug-in Object - options resource
#define OST_PExt		'PExt'	// SDK Plug-in Object - extended resource (for path plug-ins)
#define OST_PXpr		'PXpr'	// SDK Plug-in Object - extended properties resource
#define OST_VLIB		'VLIB'	// SDK Plug-in Library Routine definition resource.
#define OST_PIPa		'PIPa'	// Generic Palette placement info - for storing palette positions in workspace
#define OST_PIRe		'PIRe'	// Resizable palette placement info
#define OST_PIZm		'PIZm'	// Zoomable palette placement info
#define OST_PIOi		'PIOi'	// Object Info palette placement info
#define OST_PINP		'PINP'	// Navigation palette placement info
#define OST_PRBi		'PRBi'	// Resource Browser palette placement info
#define OST_PIAp		'PIAp'	// Application window placement info
#define OST_ANIM		'ANIM'  // QuickTime External Animation plug-ins
#define OST_MCpa		'MCpa'	// SDK Plug-in Object filetype (C++)
#define OST_MCmp		'MCmp'	// VS Plug-in filetype (VectorScript)
#define OST_VWlb		'VWlb'	// VectorWorks Plug-in Library (C++) filetype
#define OST_Coll		'Coll'	// version 8.5 symbol collections for the object browser
#define OST_CCol		'CCol'	// version 8.5 current collection for the object browser
#define OST_Col2		'Col2'	// Symbol collections saved in preferences for the object browser
#define OST_CCo2		'CCo2'	// Current collection saved in preferences for the object browser
#define	OST_WFWC		'WFWC'  // WallFramer Wall Class
#define	OST_WFLT		'WFLT'	// WallFramer Lumber Type
#define OST_VRML		'VRML'  // VRML export
#define OST_PSXT		'PSXT'  // Parasolid XT Export
#define OST_IGES		'IGES'  // IGES Export
#define OST_STL			'STL '  // STL export 
#define OST_WKVR		'WKVR'	// Workspace file version
#define OST_QTVR		'MooV'  // QuickTime VR export
#define	OST_TVOD		'TVOD'	// QuickTime Player
#define OST_Flag		'Flag'	// flag resource to indicate special notices.
#define OST_EPIX		'ePix'  // ePix/Piranesi export
#define OST_SAT			'SAT '	// SAT export
#define OST_3DS			'3DS '	// 3DS export
#define OST_MINT		'MINT'	// miscellaneous Sint32 integers
#if GS_WIN
#define OST_ASID		'ASID'	// ASID resource - used to define auxiliary 'DLOG'/'DITL' information (required for Mac. Emulated Dialogs).
#endif	//#if GS_WIN
#define OST_PALW 		'PALW'	// Platform Specific Palette Information for MS Windows
#define OST_PALM		'PALM'	// Platform Specific Palette Information for Apple Macintosh
#define OST_TPAL		'TPAL' // New Tool Palette (Tool Sets) type
#define OST_TEAR		'TEAR' // Tear Off Tool Set Palette
#define OST_TSET		'TSET' // Tool Set.
#define OST_C4D			'C4D '	// Cinema4D export
#define OST_3DM		    '3DM'  // 3DM Export
#define OST_FBX			'FBX' // FBX Export
#define OST_COLLADA		'DAE' //COLLADA Export
#define OST_STEP		'STEP' // STEP Export

/*-------------------------------------------------------------------*/
// Macintosh Filetypes (also used in Windows code)
//
// When adding filetypes for a new version, you must:
//  (1) Use new OST_xxxx types for kCurMCDocType, kCurMCStatType, 
//       kCurMCLtDocType, and kCurMCLtStatType in FileVersionInfo.h.
//  (2) Add new kMiniCadNFileVersion constant in FileVersionInfo.h.
//  (3) Increase kMaxBTIndex in UFile.h (typically will add 4).
//  (4) Add prior versions' OST_xxxx types to initialization of
//       btTypeList in InitTDManUnld() in NewTD.cpp (typically as
//       entries 4-7 and renumber older ones to help Mac Easy Open).
//  (5) In IdentifyVWDrawingFile in UFile.cpp, add new identifying
//       values for the version and a new "if" block to the code.
//  (6) In TReverseTranslate::OpenFile in ReverseTranslate.cpp,
//       add new cases to switch statement for output versions.
//  (7) Only if Windows filename extensions change, add prior
//       versions entries to wp_mac_map[] in ASIWMain.c.
//  (8) Add 'BNDL' entries (including 'FREF' and icon family) to
//       the appropriate application resource files (for Mac).
//  (9) Add 'kind' entries to the appropriate resource files.
//       These provide the Kind strings displayed by the Finder.
/*-------------------------------------------------------------------*/

// ***NOTE*** if the file version has changed. Add a new define of the form, OST_VWXX for the new version. Change OST_FileType to new version.

/* Drawing Document Filetypes */
#define OST_CADPlus     'CAD+'  // MiniCad 1.x and 2.x document
#define OST_MCPlus3     'MC+3'  // MiniCad 3.x document
#define OST_MCPlus4     'MC+4'  // MiniCad 4.x and 5.x document
#define OST_MC6d     	'MC6d'  // MiniCad 6.x document
#define OST_MC7d     	'MC7d'	// MiniCAD 7.x document
#define OST_MC8d     	'MC8d'	// VectorWorks 8.x document
#define OST_MC9d     	'MC9d'	// VectorWorks 9.x document
#define OST_VW10		'DO10'	// VectorWorks 10.x document
#define OST_VW11		'DO11'	// VectorWorks 11.x document
#define OST_VW12		'DO12'	// VectorWorks 12.x document
#define OST_VW13		'DO13'	// VectorWorks 13.x document
#define OST_VW14		'DO14'	// VectorWorks 14.x document
#define OST_VW15		'DO15'	// VectorWorks 15.x document
#define OST_VW16		'DO16'	// VectorWorks 16.x document
#define OST_VW17		'DO17'	// VectorWorks 17.x document
#define OST_VW18		'DO18'	// VectorWorks 18.x document
#define OST_VW19		'DO19'	// VectorWorks 19.x document
#define OST_VW20		'DO20'	// VectorWorks 20.x document
#define OST_VW21		'DO21'	// VectorWorks 21.x document
#define OST_VW22		'DO22'	// VectorWorks 22.x document
#define OST_VW23		'DO23'	// VectorWorks 23.x document
#define OST_VW24		'DO24'	// VectorWorks 24.x document
#define OST_VW25		'DO25'	// VectorWorks 25.x document
#define OST_VW26		'DO26'	// VectorWorks 26.x document
#define OST_VW27		'DO27'	// VectorWorks 27.x document
// *** File_Version_Advanced - Major - Initial One Time Change REQUIRED: add new OST_VW## constant for new version.

#define OST_BluD        'BluD'	// Blueprint 1.x document (similar to CAD+)
#define OST_Blu2        'Blu2'	// Blueprint 2.x document (similar to MC+3)
#define OST_Blu3        'Blu3'	// Blueprint 3.x and 5.x document (similar to MC+4)
#define OST_Blu7        'Blu7'	// MiniCAD Lt 7.x document (similar to MC7d)
#define OST_FileType	OST_VW26

/* Drawing Stationery Filetypes */
#define OST_sCPlus3     'sC+3'	// MiniCad 3.x stationery
#define OST_sCPlus4     'sC+4'	// MiniCad 4.x and 5.x stationery
#define OST_sC6d     	'sC6d'	// MiniCad 6.x stationery
#define OST_sC7d     	'sC7d'	// MiniCAD 7.x stationery
#define OST_sC8d     	'sC8d'	// VectorWorks 8.x stationery
#define OST_sC9d     	'sC9d'	// VectorWorks 9.x stationery
#define OST_sW10		'DT10'	// VectorWorks 10.x stationery (document template)
#define OST_sW11		'DT11'	// VectorWorks 11.x stationery (document template)
#define OST_sW12		'DT12'	// VectorWorks 12.x stationery (document template)
#define OST_sW13		'DT13'	// VectorWorks 13.x stationery (document template)
#define OST_sW14		'DT14'	// VectorWorks 14.x stationery (document template)
#define OST_sW15		'DT15'	// VectorWorks 15.x stationery (document template)
#define OST_sW16		'DT16'	// VectorWorks 16.x stationery (document template)
#define OST_sW17		'DT17'	// VectorWorks 17.x stationery (document template)
#define OST_sW18		'DT18'	// VectorWorks 18.x stationery (document template)
#define OST_sW19		'DT19'	// VectorWorks 19.x stationery (document template)
#define OST_sW20		'DT20'	// VectorWorks 20.x stationery (document template)
#define OST_sW21		'DT21'	// VectorWorks 21.x stationery (document template)
#define OST_sW22		'DT22'	// VectorWorks 22.x stationery (document template)
#define OST_sW23		'DT23'	// VectorWorks 23.x stationery (document template)
#define OST_sW24		'DT24'	// VectorWorks 24.x stationery (document template)
#define OST_sW25		'DT25'	// VectorWorks 25.x stationery (document template)
#define OST_sW26		'DT26'	// VectorWorks 26.x stationery (document template)
#define OST_sW27		'DT27'	// VectorWorks 26.x stationery (document template)
// *** File_Version_Advanced - Major - Initial One Time Change REQUIRED: add new OST_sW## constant for new version.

#define OST_slu2        'slu2'	// Blueprint 2.x stationery (similar to sC+3)
#define OST_slu3        'slu3'	// Blueprint 3.x and 5.x stationery (similar to sC+4)
#define OST_slu7        'slu7'	// MiniCAD Lt 7.x stationery (similar to sC7d)
#define OST_StationeryFileType OST_sW26

// OpenDWG Filetypes
#define OST_DXF         'DXF '	// AutoCAD DXF file (binary style, normal is 'TEXT')
#define OST_DWG         'DWG '	// AutoCAD DWG file
#define	OST_SHP    		'SHP '

#if GS_WIN
// Windows-only filetypes
  // Additional worksheet import formats
  #define OST_DIFSpc	'DIF '
  #define OST_CSVSpc	'CSV '
  #define OST_SLKSpc	'SLK '
#else
// Macintosh-only filetypes
#endif

// Microsoft Excel Filetypes
#define OST_XLS			'XLS '
#define OST_XLSX		'XLSX'


#define FNT_80          '\200'
#define FNT_85          '\205'
#define FNT_86          '\206'
#define FNT_8A          '\212'
#define FNT_9A          '\232'
#define FNT_9F          '\237'
#define FNT_A1          '\241'
#define FNT_A5          '\245'
#define FNT_AD          '\255'
#define FNT_AF          '\257'
#define FNT_B1          '\261'
#define FNT_B2          '\262'
#define FNT_B3          '\263'
#define FNT_B7          '\267'
#define FNT_B9          '\271'
#define FNT_C0          '\300'
#define FNT_C3          '\303'
#define FNT_C5          '\305'
#define FNT_CA          '\312'
#define FNT_CF          '\317'
#define FNT_D6          '\326'


// Apple resource types
#define	OST_4Star	'****'
#define	OST_ALRT	'ALRT'
#define	OST_CDEF	'CDEF'
#define	OST_DITL	'DITL'
#define	OST_DLOG	'DLOG'
#define OST_dlgx	'dlgx'
#define	OST_DRVR	'DRVR'
#define	OST_FOND	'FOND'
#define	OST_ICNList	'ICN#'
#define	OST_INTL	'INTL'
#define	OST_MBAR	'MBAR'
#define OST_mctb	'mctb'
#define	OST_MDEF	'MDEF'
#define	OST_MENU	'MENU'
#define	OST_PATList	'PAT#'
#define OST_PICT	'PICT'
#define	OST_pltt	'pltt'
#define	OST_SICN	'SICN'
#define	OST_STR		'STR '
#define OST_STRList	'STR#'
#define	OST_TEXT	'TEXT'
#define	OST_WDEF	'WDEF'
#define	OST_clut	'CLUT'
#define	OST_ppat	'ppat'
#define	OST_pref	'pref'
#define	OST_sfnt	'sfnt'
#define	OST_sndSPC	'snd '
#define	OST_styl	'styl'
#define	OST_vers	'vers'
#define	OST_hmnu	'hmnu'
#define	OST_icsList	'ics#'
#define	OST_ics4	'ics4'
#define	OST_ics8	'ics8'
#define	OST_icl8	'icl8'
#define OST_PNG		'PNGf'
#define OST_PDF		'PDF_'

// Windows File Extensions (#defined so we can include these (tiny) strings globally)
#define kVectorWorksExtension			"vwx"
#define kOldMiniCadExtension			"mcd"
#define kStationeryExtension			"sta"
#define kTextExtension					"txt"	// Also drawings exported as VS
#define kVectorScriptExtension			"vss"	// VS command files
#define kVectorScriptExtensionAlt		"vs"	// VS command files
#define kVectorScriptEncryptedExtension	"px"	// VS command files
#define kMiniPascalExtension			"mpc"	// Obsolete for MP command files
#define kEncryptedMiniPascalExtension	"xxt"	// Encrypted VS files
#define kOverlayExtension900			"ovl"	// Workspace files, pre-9.0.1
#define kOverlayExtension				"vww"	// Workspace files, post-9.0.1
#define kPythonScriptExtensionPY		"py"	// Pyhton Script file
#define kPythonScriptExtensionPYC		"pyc"	// Pyhton Script file
#define kVWProjectFileExtension         "vwxp"  // Vectorworks Project File
#define kVWWorkingFileExtension         "vwxw"  // Vectorworks Working File

// XXX_JDW_ALTURA [2003-01-31] - urk
#if GS_WIN
	#undef kOverlayExtension
	#define kOverlayExtension "qtr"
#endif

#define kWorkspaceExtension				"vww"
#define kDXFExtension					"dxf"
#define kDWGExtension					"dwg"
#define kPICTExtension					"pct"
#define kEPSExtension					"eps"
#define kVRMLExtension					"wrl"
#define kPSXTExtension					"X_T"
#define kIGESExtension					"iges"
#define kIGSExtension					"igs"
#define kSTLExtension					"stl"
#define kSATExtension					"sat"
#define k3DMExtension					"3dm"
#define kSTEPExtension					"step"
#define kSTPExtension					"stp"
#define k3DSExtension					"3ds"
#define kCIEExtension					"cie" 
#define kIESExtension					"ies" 
#define kCIBExtension					"cib" 
#define kLDTExtension					"ldt"
#define kSHPExtension					"shp"
#define kPNGExtension					"png"
#define kJPGExtension					"jpg"
#define kJPEGExtension                  "jpeg"
#define kJP2Extension					"jp2"
#define kPNTExtension					"pnt"
#define kPSDExtension					"psd"
#define kQTIExtension					"qti"
#define kSGIExtension					"sgi"
#define kTIFFExtension					"tif"
#define kTGAExtension					"tga"
#define kBMPExtension					"bmp"
#define kHDRExtension 					"hdr"
#define kEXRExtension					"exr"
#define kPDFExtension					"pdf"
#define kXMLExtension					"xml"
#define kKMLExtension					"kml"
// worksheet import/export formats
#define kDIFExtension					"dif"
#define kCSVExtension					"csv"
#define kSLKExtension					"slk"
#define kExcel97Extension				"xls"
#define kExcelExtension					"xlsx"

// Filename extensions for Workspace Files
#define WORKSPACEFILENAMEXTENSION		".vww"

// Filename extensions for Contextual Help Files
#define CONTEXTUALHELPFILENAMEEXTENSION ".xml"

// Filename extensions for Plug-ins. 
#define VSMENUFILENAMEEXTENSION 		".vsm"
#define VSTOOLFILENAMEEXTENSION 		".vst"
#define VSOBJECTFILENAMEEXTENSION 		".vso"


#if GS_WIN
	#define SDKMENUFILENAMEEXTENSION 		".dll"
	#define SDKTOOLFILENAMEEXTENSION 		".dll"
	#define SDKOBJECTFILENAMEEXTENSION 		".sdo"
	#define SDKLIBRARYFILENAMEEXTENSION		".vlb"
#elif GS_MAC
	#define SDKMENUFILENAMEEXTENSION 		".vwplugin"
	#define SDKTOOLFILENAMEEXTENSION 		".vwplugin"
	#define SDKOBJECTFILENAMEEXTENSION 		".vwobject"
	#define SDKLIBRARYFILENAMEEXTENSION		".vwlibrary"
	
	#define MACAPPLICATIONPACKAGEEXTENSION	".app"
#endif

