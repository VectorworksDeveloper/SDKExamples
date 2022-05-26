/*
     File:       QTHeader.h
 
     Contains:   Definition of QuickTime data types and functions. They are now implemented natively in Vectorworks.
	 Support the QTRemoval project
	 
	 Created by Hugues Tsafak
*/

#ifndef __QTHEADER__
#define __QTHEADER__


#pragma once

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

//-----------------------------------------------------------------------------------------------------------------------
// QT TYPES - 
// The types defined in this section may still be needed -  QTREMOVAL
//-----------------------------------------------------------------------------------------------------------------------
// From Aliases.h
struct AliasRecord {
    OSType                          userType;                   /* appl stored type like creator type */
    unsigned short                  aliasSize;                  /* alias record size in bytes, for appl usage */
};
typedef struct AliasRecord              AliasRecord;

typedef AliasRecord *                   AliasPtr;
typedef AliasPtr *                      AliasHandle;
/* alias record information type */
typedef short                           AliasInfoType;

//------------------------------------------------------------------------------------------------------------------------
// From FixMath.h
#define fixed1              ((Fixed) 0x00010000L)


//------------------------------------------------------------------------------------------------------------------------
// From Fonts.h
enum {
    systemFont                  = 0,
    applFont                    = 1
};

enum {
    commandMark                 = 17,
    checkMark                   = 18,
    diamondMark                 = 19,
    appleMark                   = 20
};

enum {
    kFontIDNewYork              = 2,
    kFontIDGeneva               = 3,
    kFontIDMonaco               = 4,
    kFontIDVenice               = 5,
    kFontIDLondon               = 6,
    kFontIDAthens               = 7,
    kFontIDSanFrancisco         = 8,
    kFontIDToronto              = 9,
    kFontIDCairo                = 11,
    kFontIDLosAngeles           = 12,
    kFontIDTimes                = 20,
    kFontIDHelvetica            = 21,
    kFontIDCourier              = 22,
    kFontIDSymbol               = 23,
    kFontIDMobile               = 24
};

//------------------------------------------------------------------------------------------------------------------------
// From Menus.h
enum {
    noMark                      = 0                             /*mark symbol for MarkItem*/
};

//------------------------------------------------------------------------------------------------------------------------
// From DateTimeUtils.h
struct DateTimeRec {
    short                           year;
    short                           month;
    short                           day;
    short                           hour;
    short                           minute;
    short                           second;
    short                           dayOfWeek;
};

//------------------------------------------------------------------------------------------------------------------------
// From QuickDraw.h
struct RGBColor {
    unsigned short                  red;                        /*magnitude of red component*/
    unsigned short                  green;                      /*magnitude of green component*/
    unsigned short                  blue;                       /*magnitude of blue component*/
};
typedef struct RGBColor                 RGBColor;
typedef RGBColor *                      RGBColorPtr;
typedef RGBColorPtr *                   RGBColorHdl;


struct Pattern {
    Uint8                           pat[8];
};
typedef struct Pattern                  Pattern;

typedef Sint8                           GrafVerb; // needed ??

//------------------------------------------------------------------------------------------------------------------------
// From TextEdit.h
typedef char                            Chars[32001];
typedef char *                          CharsPtr;
typedef CharsPtr *                      CharsHandle;

enum {
                                                                /* Justification (word alignment) styles */
    teJustLeft                  = 0,
    teJustCenter                = 1,
    teJustRight                 = -1,
    teForceLeft                 = -2,                           /* new names for the Justification (word alignment) styles */
    teFlushDefault              = 0,                            /*flush according to the line direction */
    teCenter                    = 1,                            /*center justify (word alignment) */
    teFlushRight                = -1,                           /*flush right for all scripts */
    teFlushLeft                 = -2                            /*flush left for all scripts */
};

//------------------------------------------------------------------------------------------------------------------------
// From Files.h
enum {
    fsAtMark                    = 0,                            /* positioning modes in ioPosMode */
    fsFromStart                 = 1,
    fsFromLEOF                  = 2,
    fsFromMark                  = 3
};

enum {
    fsCurPerm                   = 0x00,                         /* open access permissions in ioPermssn */
    fsRdPerm                    = 0x01,
    fsWrPerm                    = 0x02,
    fsRdWrPerm                  = 0x03,
    fsRdWrShPerm                = 0x04,
    fsRdDenyPerm                = 0x10,                         /* for use with OpenDeny and OpenRFDeny */
    fsWrDenyPerm                = 0x20                          /* for use with OpenDeny and OpenRFDeny */
};

//------------------------------------------------------------------------------------------------------------------------
// From dialogs.h
enum {
                                                                /* standard dialog item numbers*/
    kStdOkItemIndex             = 1,
    kStdCancelItemIndex         = 2,                            /* old names*/
    ok                          = kStdOkItemIndex,
    cancel                      = kStdCancelItemIndex
};


//------------------------------------------------------------------------------------------------------------------------
// From QDOffscreen.h

enum {
    pixPurgeBit                 = 0,
    noNewDeviceBit              = 1,
    useTempMemBit               = 2,
    keepLocalBit                = 3,
    useDistantHdwrMemBit        = 4,
    useLocalHdwrMemBit          = 5,
    pixelsPurgeableBit          = 6,
    pixelsLockedBit             = 7,
    mapPixBit                   = 16,
    newDepthBit                 = 17,
    alignPixBit                 = 18,
    newRowBytesBit              = 19,
    reallocPixBit               = 20,
    clipPixBit                  = 28,
    stretchPixBit               = 29,
    ditherPixBit                = 30,
    gwFlagErrBit                = 31
};

enum {
    pixPurge                    = 1L << pixPurgeBit,
    noNewDevice                 = 1L << noNewDeviceBit,
    useTempMem                  = 1L << useTempMemBit,
    keepLocal                   = 1L << keepLocalBit,
    useDistantHdwrMem           = 1L << useDistantHdwrMemBit,
    useLocalHdwrMem             = 1L << useLocalHdwrMemBit,
    pixelsPurgeable             = 1L << pixelsPurgeableBit,
    pixelsLocked                = 1L << pixelsLockedBit,
    kAllocDirectDrawSurface     = 1L << 14,
    mapPix                      = 1L << mapPixBit,
    newDepth                    = 1L << newDepthBit,
    alignPix                    = 1L << alignPixBit,
    newRowBytes                 = 1L << newRowBytesBit,
    reallocPix                  = 1L << reallocPixBit,
    clipPix                     = 1L << clipPixBit,
    stretchPix                  = 1L << stretchPixBit,
    ditherPix                   = 1L << ditherPixBit,
    gwFlagErr                   = 1L << gwFlagErrBit
};

//------------------------------------------------------------------------------------------------------------------------
// From Events.h

typedef Uint16                          EventModifiers;
typedef Uint16                          EventKind;
typedef Uint16                          EventMask;

struct EventRecord {
    EventKind                       what;
    Uint32                          message;
    Uint32                          when;
    Point                           where;
    EventModifiers                  modifiers;
};
typedef struct EventRecord              EventRecord;


enum {
    nullEvent                   = 0,
    mouseDown                   = 1,
    mouseUp                     = 2,
    keyDown                     = 3,
    keyUp                       = 4,
    autoKey                     = 5,
    updateEvt                   = 6,
    diskEvt                     = 7,
    activateEvt                 = 8,
    osEvt                       = 15,
    kHighLevelEvent             = 23
};

enum {
    mDownMask                   = 1 << mouseDown,               /* mouse button pressed*/
    mUpMask                     = 1 << mouseUp,                 /* mouse button released*/
    keyDownMask                 = 1 << keyDown,                 /* key pressed*/
    keyUpMask                   = 1 << keyUp,                   /* key released*/
    autoKeyMask                 = 1 << autoKey,                 /* key repeatedly held down*/
    updateMask                  = 1 << updateEvt,               /* window needs updating*/
    diskMask                    = 1 << diskEvt,                 /* disk inserted*/
    activMask                   = 1 << activateEvt,             /* activate/deactivate window*/
    highLevelEventMask          = 0x0400,                       /* high-level events (includes AppleEvents)*/
    osMask                      = 1 << osEvt,                   /* operating system events (suspend, resume)*/
    everyEvent                  = 0xFFFF                        /* all of the above*/
};

enum {
                                                                /* modifiers */
    activeFlagBit               = 0,                            /* activate? (activateEvt and mouseDown)*/
    btnStateBit                 = 7,                            /* state of button?*/
    cmdKeyBit                   = 8,                            /* command key down?*/
    shiftKeyBit                 = 9,                            /* shift key down?*/
    alphaLockBit                = 10,                           /* alpha lock down?*/
    optionKeyBit                = 11,                           /* option key down?*/
    controlKeyBit               = 12,                           /* control key down?*/
    rightShiftKeyBit            = 13,                           /* right shift key down?*/
    rightOptionKeyBit           = 14,                           /* right Option key down?*/
    rightControlKeyBit          = 15                            /* right Control key down?*/
};

enum {
    activeFlag                  = 1 << activeFlagBit,
    btnState                    = 1 << btnStateBit,
    cmdKey                      = 1 << cmdKeyBit,
    shiftKey                    = 1 << shiftKeyBit,
    alphaLock                   = 1 << alphaLockBit,
    optionKey                   = 1 << optionKeyBit,
    controlKey                  = 1 << controlKeyBit,
    rightShiftKey               = 1 << rightShiftKeyBit,
    rightOptionKey              = 1 << rightOptionKeyBit,
    rightControlKey             = 1 << rightControlKeyBit
};

enum {
    kNullCharCode               = 0,
    kHomeCharCode               = 1,
    kEnterCharCode              = 3,
    kEndCharCode                = 4,
    kHelpCharCode               = 5,
    kBellCharCode               = 7,
    kBackspaceCharCode          = 8,
    kTabCharCode                = 9,
    kLineFeedCharCode           = 10,
    kVerticalTabCharCode        = 11,
    kPageUpCharCode             = 11,
    kFormFeedCharCode           = 12,
    kPageDownCharCode           = 12,
    kReturnCharCode             = 13,
    kFunctionKeyCharCode        = 16,
    kEscapeCharCode             = 27,
    kClearCharCode              = 27,
    kLeftArrowCharCode          = 28,
    kRightArrowCharCode         = 29,
    kUpArrowCharCode            = 30,
    kDownArrowCharCode          = 31,
    kDeleteCharCode             = 127,
    kNonBreakingSpaceCharCode   = 202
};

//------------------------------------------------------------------------------------------------------------------------
// From MacErrors.h ( most of it may not be used - Revisit. QTREMOVAL


enum {
                                                                /* Memory Manager errors*/
    memROZWarn                  = -99,                          /*soft error in ROZ*/
    memROZError                 = -99,                          /*hard error in ROZ*/
    memROZErr                   = -99,                          /*hard error in ROZ*/
    memFullErr                  = -108,                         /*Not enough room in heap zone*/
    nilHandleErr                = -109,                         /*Master Pointer was NIL in HandleZone or other*/
    memWZErr                    = -111,                         /*WhichZone failed (applied to free block)*/
    memPurErr                   = -112,                         /*trying to purge a locked or non-purgeable block*/
    memAdrErr                   = -110,                         /*address was odd; or out of range*/
    memAZErr                    = -113,                         /*Address in zone check failed*/
    memPCErr                    = -114,                         /*Pointer Check failed*/
    memBCErr                    = -115,                         /*Block Check failed*/
    memSCErr                    = -116,                         /*GSSize Check failed*/
    memLockedErr                = -117                          /*trying to move a locked block (MoveHHi)*/
};

enum {
                                                                /* ENET error codes */
    eLenErr                     = -92,                          /*Length error ddpLenErr*/
    eMultiErr                   = -91                           /*Multicast address error ddpSktErr*/
};

enum {
    paramErr                    = -50,                          /*error in user parameter list*/
    noHardwareErr               = -200,                         /*Sound Manager Error Returns*/
    notEnoughHardwareErr        = -201,                         /*Sound Manager Error Returns*/
    userCanceledErr             = -128,
    qErr                        = -1,                           /*queue element not found during deletion*/
    vTypErr                     = -2,                           /*invalid queue element*/
    corErr                      = -3,                           /*core routine number out of range*/
    unimpErr                    = -4,                           /*unimplemented core routine*/
    SlpTypeErr                  = -5,                           /*invalid queue element*/
    seNoDB                      = -8,                           /*no debugger installed to handle debugger command*/
    controlErr                  = -17,                          /*I/O System Errors*/
    statusErr                   = -18,                          /*I/O System Errors*/
    readErr                     = -19,                          /*I/O System Errors*/
    writErr                     = -20,                          /*I/O System Errors*/
    badUnitErr                  = -21,                          /*I/O System Errors*/
    unitEmptyErr                = -22,                          /*I/O System Errors*/
    openErr                     = -23,                          /*I/O System Errors*/
    closErr                     = -24,                          /*I/O System Errors*/
    dRemovErr                   = -25,                          /*tried to remove an open driver*/
    dInstErr                    = -26                           /*DrvrInstall couldn't find driver in resources*/
};

enum {
    abortErr                    = -27,                          /*IO call aborted by KillIO*/
    iIOAbortErr                 = -27,                          /*IO abort error (Printing Manager)*/
    notOpenErr                  = -28,                          /*Couldn't rd/wr/ctl/sts cause driver not opened*/
    unitTblFullErr              = -29,                          /*unit table has no more entries*/
    dceExtErr                   = -30,                          /*dce extension error*/
    slotNumErr                  = -360,                         /*invalid slot # error*/
    gcrOnMFMErr                 = -400,                         /*gcr format on high density media error*/
    dirFulErr                   = -33,                          /*Directory full*/
    dskFulErr                   = -34,                          /*disk full*/
    nsvErr                      = -35,                          /*no such volume*/
    ioErr                       = -36,                          /*I/O error (bummers)*/
    bdNamErr                    = -37,                          /*there may be no bad names in the final system!*/
    fnOpnErr                    = -38,                          /*File not open*/
    eofErr                      = -39,                          /*End of file*/
    posErr                      = -40,                          /*tried to position to before start of file (r/w)*/
    mFulErr                     = -41,                          /*memory full (open) or file won't fit (load)*/
    tmfoErr                     = -42,                          /*too many files open*/
    fnfErr                      = -43,                          /*File not found*/
    wPrErr                      = -44,                          /*diskette is write protected.*/
    fLckdErr                    = -45                           /*file is locked*/
};

enum {
    vLckdErr                    = -46,                          /*volume is locked*/
    fBsyErr                     = -47,                          /*File is busy (delete)*/
    dupFNErr                    = -48,                          /*duplicate filename (rename)*/
    opWrErr                     = -49,                          /*file already open with with write permission*/
    rfNumErr                    = -51,                          /*refnum error*/
    gfpErr                      = -52,                          /*get file position error*/
    volOffLinErr                = -53,                          /*volume not on line error (was Ejected)*/
    permErr                     = -54,                          /*permissions error (on file open)*/
    volOnLinErr                 = -55,                          /*drive volume already on-line at MountVol*/
    nsDrvErr                    = -56,                          /*no such drive (tried to mount a bad drive num)*/
    noMacDskErr                 = -57,                          /*not a mac diskette (sig bytes are wrong)*/
    extFSErr                    = -58,                          /*volume in question belongs to an external fs*/
    fsRnErr                     = -59,                          /*file system internal error:during rename the old entry was deleted but could not be restored.*/
    badMDBErr                   = -60,                          /*bad master directory block*/
    wrPermErr                   = -61,                          /*write permissions error*/
    dirNFErr                    = -120,                         /*Directory not found*/
    tmwdoErr                    = -121,                         /*No free WDCB available*/
    badMovErr                   = -122,                         /*Move into offspring error*/
    wrgVolTypErr                = -123,                         /*Wrong volume type error [operation not supported for MFS]*/
    volGoneErr                  = -124                          /*Server volume has been disconnected.*/
};

enum {
    fidNotFound                 = -1300,                        /*no file thread exists.*/
    fidExists                   = -1301,                        /*file id already exists*/
    notAFileErr                 = -1302,                        /*directory specified*/
    diffVolErr                  = -1303,                        /*files on different volumes*/
    catChangedErr               = -1304,                        /*the catalog has been modified*/
    desktopDamagedErr           = -1305,                        /*desktop database files are corrupted*/
    sameFileErr                 = -1306,                        /*can't exchange a file with itself*/
    badFidErr                   = -1307,                        /*file id is dangling or doesn't match with the file number*/
    notARemountErr              = -1308,                        /*when _Mount allows only remounts and doesn't get one*/
    fileBoundsErr               = -1309,                        /*file's EOF, offset, mark or size is too big*/
    fsDataTooBigErr             = -1310,                        /*file or volume is too big for system*/
    volVMBusyErr                = -1311,                        /*can't eject because volume is in use by VM*/
    badFCBErr                   = -1327,                        /*FCBRecPtr is not valid*/
    errFSUnknownCall            = -1400,                        /* selector is not recognized by this filesystem */
    errFSBadFSRef               = -1401,                        /* FSRef parameter is bad */
    errFSBadForkName            = -1402,                        /* Fork name parameter is bad */
    errFSBadBuffer              = -1403,                        /* A buffer parameter was bad */
    errFSBadForkRef             = -1404,                        /* A ForkRefNum parameter was bad */
    errFSBadInfoBitmap          = -1405,                        /* A CatalogInfoBitmap or VolumeInfoBitmap has reserved or invalid bits set */
    errFSMissingCatInfo         = -1406,                        /* A CatalogInfo parameter was NULL */
    errFSNotAFolder             = -1407,                        /* Expected a folder, got a file */
    errFSForkNotFound           = -1409,                        /* Named fork does not exist */
    errFSNameTooLong            = -1410,                        /* File/fork name is too long to create/rename */
    errFSMissingName            = -1411,                        /* A Unicode name parameter was NULL or nameLength parameter was zero */
    errFSBadPosMode             = -1412,                        /* Newline bits set in positionMode */
    errFSBadAllocFlags          = -1413,                        /* Invalid bits set in allocationFlags */
    errFSNoMoreItems            = -1417,                        /* Iteration ran out of items to return */
    errFSBadItemCount           = -1418,                        /* maximumItems was zero */
    errFSBadSearchParams        = -1419,                        /* Something wrong with CatalogSearch searchParams */
    errFSRefsDifferent          = -1420,                        /* FSCompareFSRefs; refs are for different objects */
    errFSForkExists             = -1421,                        /* Named fork already exists. */
    errFSBadIteratorFlags       = -1422,                        /* Flags passed to FSOpenIterator are bad */
    errFSIteratorNotFound       = -1423,                        /* Passed FSIterator is not an open iterator */
    errFSIteratorNotSupported   = -1424,                        /* The iterator's flags or container are not supported by this call */
    envNotPresent               = -5500,                        /*returned by glue.*/
    envBadVers                  = -5501,                        /*Version non-positive*/
    envVersTooBig               = -5502,                        /*Version bigger than call can handle*/
    fontDecError                = -64,                          /*error during font declaration*/
    fontNotDeclared             = -65,                          /*font not declared*/
    fontSubErr                  = -66,                          /*font substitution occurred*/
    fontNotOutlineErr           = -32615,                       /*bitmap font passed to routine that does outlines only*/
    firstDskErr                 = -84,                          /*I/O System Errors*/
    lastDskErr                  = -64,                          /*I/O System Errors*/
    noDriveErr                  = -64,                          /*drive not installed*/
    offLinErr                   = -65,                          /*r/w requested for an off-line drive*/
    noNybErr                    = -66                           /*couldn't find 5 nybbles in 200 tries*/
};

enum {
    noAdrMkErr                  = -67,                          /*couldn't find valid addr mark*/
    dataVerErr                  = -68,                          /*read verify compare failed*/
    badCksmErr                  = -69,                          /*addr mark checksum didn't check*/
    badBtSlpErr                 = -70,                          /*bad addr mark bit slip nibbles*/
    noDtaMkErr                  = -71,                          /*couldn't find a data mark header*/
    badDCksum                   = -72,                          /*bad data mark checksum*/
    badDBtSlp                   = -73,                          /*bad data mark bit slip nibbles*/
    wrUnderrun                  = -74,                          /*write underrun occurred*/
    cantStepErr                 = -75,                          /*step handshake failed*/
    tk0BadErr                   = -76,                          /*track 0 detect doesn't change*/
    initIWMErr                  = -77,                          /*unable to initialize IWM*/
    twoSideErr                  = -78,                          /*tried to read 2nd side on a 1-sided drive*/
    spdAdjErr                   = -79,                          /*unable to correctly adjust disk speed*/
    seekErr                     = -80,                          /*track number wrong on address mark*/
    sectNFErr                   = -81,                          /*sector number never found on a track*/
    fmt1Err                     = -82,                          /*can't find sector 0 after track format*/
    fmt2Err                     = -83,                          /*can't get enough sync*/
    verErr                      = -84,                          /*track failed to verify*/
    clkRdErr                    = -85,                          /*unable to read same clock value twice*/
    clkWrErr                    = -86,                          /*time written did not verify*/
    prWrErr                     = -87,                          /*parameter ram written didn't read-verify*/
    prInitErr                   = -88,                          /*InitUtil found the parameter ram uninitialized*/
    rcvrErr                     = -89,                          /*SCC receiver error (framing; parity; OR)*/
    breakRecd                   = -90                           /*Break received (SCC)*/
};

enum {
                                                                /*Scrap Manager errors*/
    noScrapErr                  = -100,                         /*No scrap exists error*/
    noTypeErr                   = -102                          /*No object of that type in scrap*/
};

enum {
                                                                /*  AFP Protocol Errors */
    afpAccessDenied             = -5000,                        /* Insufficient access privileges for operation */
    afpAuthContinue             = -5001,                        /* Further information required to complete AFPLogin call */
    afpBadUAM                   = -5002,                        /* Unknown user authentication method specified */
    afpBadVersNum               = -5003,                        /* Unknown AFP protocol version number specified */
    afpBitmapErr                = -5004,                        /* Bitmap contained bits undefined for call */
    afpCantMove                 = -5005,                        /* Move destination is offspring of source, or root was specified */
    afpDenyConflict             = -5006,                        /* Specified open/deny modes conflict with current open modes */
    afpDirNotEmpty              = -5007,                        /* Cannot delete non-empty directory */
    afpDiskFull                 = -5008,                        /* Insufficient free space on volume for operation */
    afpEofError                 = -5009,                        /* Read beyond logical end-of-file */
    afpFileBusy                 = -5010,                        /* Cannot delete an open file */
    afpFlatVol                  = -5011,                        /* Cannot create directory on specified volume */
    afpItemNotFound             = -5012,                        /* Unknown UserName/UserID or missing comment/APPL entry */
    afpLockErr                  = -5013,                        /* Some or all of requested range is locked by another user */
    afpMiscErr                  = -5014,                        /* Unexpected error encountered during execution */
    afpNoMoreLocks              = -5015,                        /* Maximum lock limit reached */
    afpNoServer                 = -5016,                        /* Server not responding */
    afpObjectExists             = -5017,                        /* Specified destination file or directory already exists */
    afpObjectNotFound           = -5018,                        /* Specified file or directory does not exist */
    afpParmErr                  = -5019,                        /* A specified parameter was out of allowable range */
    afpRangeNotLocked           = -5020,                        /* Tried to unlock range that was not locked by user */
    afpRangeOverlap             = -5021,                        /* Some or all of range already locked by same user */
    afpSessClosed               = -5022,                        /* Session closed*/
    afpUserNotAuth              = -5023,                        /* No AFPLogin call has successfully been made for this session */
    afpCallNotSupported         = -5024,                        /* Unsupported AFP call was made */
    afpObjectTypeErr            = -5025,                        /* File/Directory specified where Directory/File expected */
    afpTooManyFilesOpen         = -5026,                        /* Maximum open file count reached */
    afpServerGoingDown          = -5027,                        /* Server is shutting down */
    afpCantRename               = -5028,                        /* AFPRename cannot rename volume */
    afpDirNotFound              = -5029,                        /* Unknown directory specified */
    afpIconTypeError            = -5030,                        /* Icon size specified different from existing icon size */
    afpVolLocked                = -5031,                        /* Volume is Read-Only */
    afpObjectLocked             = -5032,                        /* Object is M/R/D/W inhibited*/
    afpContainsSharedErr        = -5033,                        /* the folder being shared contains a shared folder*/
    afpIDNotFound               = -5034,
    afpIDExists                 = -5035,
    afpDiffVolErr               = -5036,
    afpCatalogChanged           = -5037,
    afpSameObjectErr            = -5038,
    afpBadIDErr                 = -5039,
    afpPwdSameErr               = -5040,                        /* Someone tried to change their password to the same password on a mantadory password change */
    afpPwdTooShortErr           = -5041,                        /* The password being set is too short: there is a minimum length that must be met or exceeded */
    afpPwdExpiredErr            = -5042,                        /* The password being used is too old: this requires the user to change the password before log-in can continue */
    afpInsideSharedErr          = -5043,                        /* The folder being shared is inside a shared folder OR the folder contains a shared folder and is being moved into a shared folder */
                                                                /* OR the folder contains a shared folder and is being moved into the descendent of a shared folder.*/
    afpInsideTrashErr           = -5044,                        /* The folder being shared is inside the trash folder OR the shared folder is being moved into the trash folder */
                                                                /* OR the folder is being moved to the trash and it contains a shared folder */
    afpPwdNeedsChangeErr        = -5045,                        /* The password needs to be changed*/
    afpPwdPolicyErr             = -5046,                        /* Password does not conform to servers password policy */
    afpAlreadyLoggedInErr       = -5047,                        /* User has been authenticated but is already logged in from another machine (and that's not allowed on this server) */
    afpCallNotAllowed           = -5048                         /* The server knows what you wanted to do, but won't let you do it just now */
};

enum {
                                                                /*  AppleShare Client Errors */
    afpBadDirIDType             = -5060,
    afpCantMountMoreSrvre       = -5061,                        /* The Maximum number of server connections has been reached */
    afpAlreadyMounted           = -5062,                        /* The volume is already mounted */
    afpSameNodeErr              = -5063                         /* An Attempt was made to connect to a file server running on the same machine */
};


enum {
    resourceInMemory            = -188,                         /*Resource already in memory*/
    writingPastEnd              = -189,                         /*Writing past end of file*/
    inputOutOfBounds            = -190,                         /*Offset of Count out of bounds*/
    resNotFound                 = -192,                         /*Resource not found*/
    resFNotFound                = -193,                         /*Resource file not found*/
    addResFailed                = -194,                         /*AddResource failed*/
    addRefFailed                = -195,                         /*AddReference failed*/
    rmvResFailed                = -196,                         /*RmveResource failed*/
    rmvRefFailed                = -197,                         /*RmveReference failed*/
    resAttrErr                  = -198,                         /*attribute inconsistent with operation*/
    mapReadErr                  = -199,                         /*map inconsistent with operation*/
    CantDecompress              = -186,                         /*resource bent ("the bends") - can't decompress a compressed resource*/
    badExtResource              = -185,                         /*extended resource has a bad format.*/
    noMemForPictPlaybackErr     = -145,
    rgnOverflowErr              = -147,
    rgnTooBigError              = -147,
    pixMapTooDeepErr            = -148,
    insufficientStackErr        = -149,
    nsStackErr                  = -149
};

enum {
    smResrvErr                  = -307,                         /*Fatal reserved error. Resreved field <> 0.*/
    smUnExBusErr                = -308,                         /*Unexpected BusError*/
    smBLFieldBad                = -309,                         /*ByteLanes field was bad.*/
    smFHBlockRdErr              = -310,                         /*Error occurred during _sGetFHeader.*/
    smFHBlkDispErr              = -311,                         /*Error occurred during _sDisposePtr (Dispose of FHeader block).*/
    smDisposePErr               = -312,                         /*_DisposePointer error*/
    smNoBoardSRsrc              = -313,                         /*No Board sResource.*/
    smGetPRErr                  = -314,                         /*Error occurred during _sGetPRAMRec (See SIMStatus).*/
    smNoBoardId                 = -315,                         /*No Board Id.*/
    smInitStatVErr              = -316,                         /*The InitStatusV field was negative after primary or secondary init.*/
    smInitTblVErr               = -317,                         /*An error occurred while trying to initialize the Slot Resource Table.*/
    smNoJmpTbl                  = -318,                         /*SDM jump table could not be created.*/
    smReservedSlot              = -318,                         /*slot is reserved, VM should not use this address space.*/
    smBadBoardId                = -319,                         /*BoardId was wrong; re-init the PRAM record.*/
    smBusErrTO                  = -320,                         /*BusError time out.*/
                                                                /* These errors are logged in the  vendor status field of the sInfo record. */
    svTempDisable               = -32768L,                      /*Temporarily disable card but run primary init.*/
    svDisabled                  = -32640,                       /*Reserve range -32640 to -32768 for Apple temp disables.*/
    smBadRefId                  = -330,                         /*Reference Id not found in List*/
    smBadsList                  = -331,                         /*Bad sList: Id1 < Id2 < Id3 ...format is not followed.*/
    smReservedErr               = -332,                         /*Reserved field not zero*/
    smCodeRevErr                = -333                          /*Code revision is wrong*/
};

extern "C" short GetAppFont(void);
//extern "C" void LowercaseText(
//		  Ptr          textPtr,
//		  short        len,
//		  ScriptCode   script);








//-----------------------------------------------------------------------------------------------------------------------
// QT TYPES - 
// The types defined in this section are just temporary stubs to allow the project to compile.
// They have been copied from the QuickTime lib header files and most of the member variables have been stripped out.
// They are used in QT Functions that are going to be being removed. - *QTREMOVAL
//-----------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------
// From QuickDrawText.h
struct FontInfo {
    short                           ascent;
    short                           descent;
    short                           widMax;
    short                           leading;
};
typedef struct FontInfo                 FontInfo;

//------------------------------------------------------------------------------------------------------------------------
// From QuickDraw.h


typedef Uint32                   DeviceLoopFlags;

typedef struct GDevice                  GDevice;
typedef GDevice *                       GDPtr;
typedef GDPtr *                         GDHandle;

struct GDevice {
    short                           gdRefNum;                   /*driver's unit number*/
    short                           gdID;                       /*client ID for search procs*/
    short                           gdType;                     /*fixed/CLUT/direct*/
    // QTREMOVAL
	//
};

struct ColorSpec {
    short                           value;                      /*index or other value*/
    RGBColor                        rgb;                        /*true color*/
};
typedef struct ColorSpec                ColorSpec;
typedef ColorSpec *                     ColorSpecPtr;

typedef ColorSpec                       CSpecArray[1];

struct ColorTable {
    Sint32                            ctSeed;                     /*unique identifier for table*/
    short                           ctFlags;                    /*high bit: 0 = PixMap; 1 = device*/
    short                           ctSize;                     /*number of entries in CTTable*/
    CSpecArray                      ctTable;                    /*array [0..0] of ColorSpec*/
    // QT REMOVAL
};
typedef struct ColorTable               ColorTable;
typedef ColorTable *                    CTabPtr;
typedef CTabPtr *                       CTabHandle;


#define FOUR_CHAR_CODE(x)           (x)

/* values for PixMap.pixelFormat*/
enum {
    k16LE555PixelFormat         = FOUR_CHAR_CODE('L555'),       /* 16 bit LE rgb 555 (PC)*/
    k16LE5551PixelFormat        = FOUR_CHAR_CODE('5551'),       /* 16 bit LE rgb 5551*/
    k16BE565PixelFormat         = FOUR_CHAR_CODE('B565'),       /* 16 bit BE rgb 565*/
    k16LE565PixelFormat         = FOUR_CHAR_CODE('L565'),       /* 16 bit LE rgb 565*/
    k24BGRPixelFormat           = FOUR_CHAR_CODE('24BG'),       /* 24 bit bgr */
    k32BGRAPixelFormat          = FOUR_CHAR_CODE('BGRA'),       /* 32 bit bgra    (Matrox)*/
    k32ABGRPixelFormat          = FOUR_CHAR_CODE('ABGR'),       /* 32 bit abgr    */
    k32RGBAPixelFormat          = FOUR_CHAR_CODE('RGBA'),       /* 32 bit rgba    */
    kYUVSPixelFormat            = FOUR_CHAR_CODE('yuvs'),       /* YUV 4:2:2 byte ordering 16-unsigned = 'YUY2'*/
    kYUVUPixelFormat            = FOUR_CHAR_CODE('yuvu'),       /* YUV 4:2:2 byte ordering 16-signed*/
    kYVU9PixelFormat            = FOUR_CHAR_CODE('YVU9'),       /* YVU9 Planar    9*/
    kYUV411PixelFormat          = FOUR_CHAR_CODE('Y411'),       /* YUV 4:1:1 Interleaved  16*/
    kYVYU422PixelFormat         = FOUR_CHAR_CODE('YVYU'),       /* YVYU 4:2:2 byte ordering   16*/
    kUYVY422PixelFormat         = FOUR_CHAR_CODE('UYVY'),       /* UYVY 4:2:2 byte ordering   16*/
    kYUV211PixelFormat          = FOUR_CHAR_CODE('Y211'),       /* YUV 2:1:1 Packed   8*/
    k2vuyPixelFormat            = FOUR_CHAR_CODE('2vuy')        /* UYVY 4:2:2 byte ordering   16*/
};

struct PixMapExtension {
    Sint32                      extSize;                    /*size of struct, duh!*/
    Uint32						pmBits;                     /*pixmap attributes bitfield*/
    void *                      pmGD;                       /*this is a GDHandle*/
    Sint32                      pmSeed;
    Fixed                       gammaLevel;                 /*pixmap gammalevel*/
    Fixed                       requestedGammaLevel;
    Uint32						reserved2;
    Sint32                      longRowBytes;               /*used when rowBytes > 16382*/
    Uint32						signature;
    Handle                      baseAddrHandle;
};
typedef struct PixMapExtension          PixMapExtension;
typedef PixMapExtension *               PixMapExtPtr;
typedef PixMapExtPtr *                  PixMapExtHandle;

struct PixMap {
    Ptr                             baseAddr;                   /*pointer to pixels*/
    short                           rowBytes;                   /*offset to next line*/
	Rect                            bounds;
	short                           pmVersion;                  /*pixMap version number*/
    short                           packType;                   /*defines packing format*/
    Sint32                            packSize;                   /*length of pixel data*/
    Fixed                           hRes;                       /*horiz. resolution (ppi)*/
    Fixed                           vRes;                       /*vert. resolution (ppi)*/
    short                           pixelType;                  /*defines pixel type*/
    short                           pixelSize;                  /*# bits in pixel*/
    short                           cmpCount;                   /*# components in pixel*/
    short                           cmpSize;                    /*# bits per component*/

	OSType                          pixelFormat;                /*fourCharCode representation*/
    CTabHandle                      pmTable;                    /*color map for this pixMap*/
	PixMapExtHandle                 pmExt;                      /*Handle to pixMap extension*/
    // QTREMOVAL
	//
};
typedef struct PixMap                   PixMap;
typedef PixMap *                        PixMapPtr;
typedef PixMapPtr *                     PixMapHandle;


struct PixPat {
    short                           patType;                    /*type of pattern*/
    PixMapHandle                    patMap;                     /*the pattern's pixMap*/
    Handle                          patData;                    /*pixmap's data*/
    Handle                          patXData;                   /*expanded Pattern data*/
    short                           patXValid;                  /*flags whether expanded Pattern valid*/
    Handle                          patXMap;                    /*Handle to expanded Pattern data*/
    Pattern                         pat1Data;                   /*old-Style pattern/RGB color*/
};

typedef struct PixPat                   PixPat;
typedef PixPat *                        PixPatPtr;
typedef PixPatPtr *                     PixPatHandle;


struct MacRegion {
    unsigned short                  rgnSize;                    /*size in bytes*/
    Rect                            rgnBBox;                    /*enclosing rectangle*/
};
typedef struct MacRegion                MacRegion;
typedef MacRegion *                     RgnPtr;
typedef RgnPtr *                        RgnHandle;

typedef short                           Bits16[16];
struct Cursor {
    Bits16                          data;
    Bits16                          mask;
    Point                           hotSpot;
};
typedef struct Cursor                   Cursor;
typedef Cursor *                        CursPtr;
typedef CursPtr *                       CursHandle;

struct PenState {
    Point                           pnLoc;
    Point                           pnSize;
    short                           pnMode;
    Pattern                         pnPat;
};
typedef struct PenState                 PenState;

struct BitMap {
    Ptr                             baseAddr;
    short                           rowBytes;
    Rect                            bounds;
};
typedef struct BitMap                   BitMap;
typedef BitMap *                        BitMapPtr;
typedef BitMapPtr *                     BitMapHandle;


typedef const Pattern *                 ConstPatternParam;
typedef Pattern *                       PatPtr;
typedef PatPtr *                        PatHandle;
typedef SignedByte                      QDByte;
typedef QDByte *                        QDPtr;
typedef QDPtr *                         QDHandle;
typedef short                           QDErr;

typedef Uint32			                GWorldFlags;



struct GrafPort {
    short                           device;

	// QTREMOVAL
	//
};
typedef struct GrafPort                 GrafPort;
typedef GrafPort *                      GrafPtr;

typedef GrafPtr                         WindowPtr;
typedef WindowPtr                       DialogPtr;
typedef WindowPtr                       WindowRef;


struct Picture {
    short                           picSize;
    Rect                            picFrame;
};
typedef struct Picture                  Picture;
typedef Picture *                       PicPtr;
typedef PicPtr *                        PicHandle;

struct MacPolygon {
    short                           polySize;
    Rect                            polyBBox;
    Point                           polyPoints[1];
};
typedef struct MacPolygon               MacPolygon;

typedef MacPolygon *                    PolyPtr;
typedef PolyPtr *                       PolyHandle;


typedef struct CGrafPort                CGrafPort;
typedef CGrafPort *                     CGrafPtr;



struct ITab {
    Sint32                            iTabSeed;                   /*copy of CTSeed from source CTable*/
    // QTREMOVAL
};
typedef struct ITab                     ITab;
typedef ITab *                          ITabPtr;
typedef ITabPtr *                       ITabHandle;


struct QDGlobals {
    char                            privates[76];
    Sint32                            randSeed;
    BitMap                          screenBits;
    Cursor                          arrow;
    Pattern                         dkGray;
    Pattern                         ltGray;
    Pattern                         gray;
    Pattern                         black;
    Pattern                         white;
    GrafPtr                         thePort;
};
typedef struct QDGlobals                QDGlobals;
typedef QDGlobals *                     QDGlobalsPtr;
typedef QDGlobalsPtr *                  QDGlobalsHdl;


enum {
                                                                /* transfer modes */
    srcCopy                     = 0,                            /*the 16 transfer modes*/
    srcOr                       = 1,
    srcXor                      = 2,
    srcBic                      = 3,
    notSrcCopy                  = 4,
    notSrcOr                    = 5,
    notSrcXor                   = 6,
    notSrcBic                   = 7,
    patCopy                     = 8,
    patOr                       = 9,
    patXor                      = 10,
    patBic                      = 11,
    notPatCopy                  = 12,
    notPatOr                    = 13,
    notPatXor                   = 14,
    notPatBic                   = 15,                           /* Special Text Transfer Mode */
    grayishTextOr               = 49,
    hilitetransfermode          = 50,
    hilite                      = 50,                           /* Arithmetic transfer modes */
    blend                       = 32,
    addPin                      = 33,
    addOver                     = 34,
    subPin                      = 35,
    addMax                      = 37,
    adMax                       = 37,
    subOver                     = 38,
    adMin                       = 39,
    ditherCopy                  = 64,                           /* Transparent mode constant */
    transparent                 = 36
};


enum {
    kQDGrafVerbFrame            = 0,
    kQDGrafVerbPaint            = 1,
    kQDGrafVerbErase            = 2,
    kQDGrafVerbInvert           = 3,
    kQDGrafVerbFill             = 4
};


//------------------------------------------------------------------------------------------------------------------------
// From QDOffscreen.h
typedef CGrafPtr                        GWorldPtr;


//------------------------------------------------------------------------------------------------------------------------
// From Menu.h
typedef Sint16                          MenuID;
typedef Uint16                          MenuItemIndex;
typedef Uint32                          MenuCommand;

struct MenuInfo {
    MenuID                          menuID;
    // QTREMOVAL

};
typedef struct MenuInfo                 MenuInfo;
typedef MenuInfo *                      MenuPtr;
typedef MenuPtr *                       MenuHandle;
typedef MenuHandle                      MenuRef;

//------------------------------------------------------------------------------------------------------------------------
// From Icons.h
typedef Sint16                          IconAlignmentType;
typedef Sint16                          IconTransformType;
struct CIcon {
    PixMap                          iconPMap;                   /*the icon's pixMap*/
    BitMap                          iconMask;                   /*the icon's mask*/
    BitMap                          iconBMap;                   /*the icon's bitMap*/
    Handle                          iconData;                   /*the icon's data*/
    Sint16                          iconMaskData[1];            /*icon's mask and BitMap data*/
    // QT REMOVAL
};
typedef struct CIcon                    CIcon;
typedef CIcon *                         CIconPtr;
typedef CIconPtr *                      CIconHandle;

//------------------------------------------------------------------------------------------------------------------------
// From Events.h



//------------------------------------------------------------------------------------------------------------------------
// From Files.h
struct FSSpec {
    short		vRefNum;
    Sint32		parID;
    Str255		name;
};
typedef struct FSSpec                   FSSpec;
typedef FSSpec *                        FSSpecPtr;
typedef FSSpecPtr *                     FSSpecHandle;
/* pointer to array of FSSpecs */
typedef FSSpecPtr                       FSSpecArrayPtr;
/* 
    The only difference between "const FSSpec*" and "ConstFSSpecPtr" is 
    that as a parameter, ConstFSSpecPtr is allowed to be NULL 
*/

typedef const FSSpec *                  ConstFSSpecPtr;


//------------------------------------------------------------------------------------------------------------------------
// From Controls.h
typedef struct ControlRecord            ControlRecord;
typedef ControlRecord *                 ControlPtr;
typedef ControlPtr *                    ControlRef;
typedef ControlRef                      ControlHandle;
typedef Sint16                          ControlPartCode;
struct ControlRecord {
    ControlRef                      nextControl;
	// QTREMOVAL
	//
};


typedef Sint16                          DialogItemIndexZeroBased;
typedef Sint16                          DialogItemIndex;
typedef Sint16                          DialogItemType;

//------------------------------------------------------------------------------------------------------------------------
// From TextEdit.h
typedef struct TERec                    TERec;
typedef TERec *                         TEPtr;
typedef TEPtr *                         TEHandle;


//------------------------------------------------------------------------------------------------------------------------
// From Palettes.h
struct Palette {
    short                           pmEntries;                  /*entries in pmTable*/
   // QTREMOVAL
};
typedef struct Palette                  Palette;
typedef Palette *                       PalettePtr;
typedef PalettePtr *                    PaletteHandle;


enum {
    pmCourteous                 = 0,                            /*Record use of color on each device touched.*/
    pmDithered                  = 0x0001,
    pmTolerant                  = 0x0002,                       /*render ciRGB if ciTolerance is exceeded by best match.*/
    pmAnimated                  = 0x0004,                       /*reserve an index on each device touched and render ciRGB.*/
    pmExplicit                  = 0x0008,                       /*no reserve, no render, no record; stuff index into port.*/
    pmWhite                     = 0x0010,
    pmBlack                     = 0x0020,
    pmInhibitG2                 = 0x0100,
    pmInhibitC2                 = 0x0200,
    pmInhibitG4                 = 0x0400,
    pmInhibitC4                 = 0x0800,
    pmInhibitG8                 = 0x1000,
    pmInhibitC8                 = 0x2000,                       /* NSetPalette Update Constants */
    pmNoUpdates                 = 0x8000,                       /*no updates*/
    pmBkUpdates                 = 0xA000,                       /*background updates only*/
    pmFgUpdates                 = 0xC000,                       /*foreground updates only*/
    pmAllUpdates                = 0xE000                        /*all updates*/
};

//------------------------------------------------------------------------------------------------------------------------
// From MacWindows.h
typedef Sint16 WindowPartCode;



//------------------------------------------------------------------------------------------------------------------------
// From QTML.h
enum {
    kQTMLNoIdleEvents           = (1L << 1)                     /* ask for a non-auto-idled port to be created*/
};

//------------------------------------------------------------------------------------------------------------------------
// From Lists.h
struct ListRec {
    Rect                            rView;
    //QTREMOVAL
};
typedef struct ListRec                  ListRec;
typedef ListRec *                       ListPtr;
typedef ListPtr *                       ListHandle;


//------------------------------------------------------------------------------------------------------------------------
// From Scripts.h

// Meta script codes:
enum {
    smSystemScript              = -1,                           /* designates system script.*/
    smCurrentScript             = -2,                           /* designates current font script.*/
    smAllScripts                = -3                            /* designates any script*/
};


//------------------------------------------------------------------------------------------------------------------------
// From ImageCompression.h

typedef OSType                          CodecType;
typedef unsigned short                  CodecFlags;
typedef Uint32                   CodecQ;

struct ImageDescription {
    Sint32                            idSize;                     /* total size of ImageDescription including extra data ( CLUTs and other per sequence data ) */
    CodecType                       cType;                      /* what kind of codec compressed this data */
    Sint32                            resvd1;                     /* reserved for Apple use */
    short                           resvd2;                     /* reserved for Apple use */
    short                           dataRefIndex;               /* set to zero  */
    short                           version;                    /* which version is this data */
    short                           revisionLevel;              /* what version of that codec did this */
    Sint32                            vendor;                     /* whose  codec compressed this data */
	CodecQ                          temporalQuality;            /* what was the temporal quality factor  */
	CodecQ                          spatialQuality;             /* what was the spatial quality factor */
    short                           width;                      /* how many pixels wide is this data */
    short                           height;                     /* how many pixels high is this data */
    Fixed                           hRes;                       /* horizontal resolution */
    Fixed                           vRes;                       /* vertical resolution */
    Sint32                            dataSize;                   /* if known, the size of data for this image descriptor */
    short                           frameCount;                 /* number of frames this description applies to */
    Str31                           name;                       /* name of codec ( in case not installed )  */
    short                           depth;                      /* what depth is this data (1-32) or ( 33-40 grayscale ) */
    short                           clutID;                     /* clut id or if 0 clut follows  or -1 if no clut */
};
typedef struct ImageDescription         ImageDescription;
typedef ImageDescription *              ImageDescriptionPtr;
typedef ImageDescriptionPtr *           ImageDescriptionHandle;


//------------------------------------------------------------------------------------------------------------------------
// From Fonts.h
struct FamRec {
    short                           ffFlags;                    /*flags for family*/
    short                           ffFamID;                    /*family ID number*/
    short                           ffFirstChar;                /*ASCII code of 1st character*/
    short                           ffLastChar;                 /*ASCII code of last character*/
    short                           ffAscent;                   /*maximum ascent for 1pt font*/
    short                           ffDescent;                  /*maximum descent for 1pt font*/
    short                           ffLeading;                  /*maximum leading for 1pt font*/
    short                           ffWidMax;                   /*maximum widMax for 1pt font*/
    Sint32                            ffWTabOff;                  /*offset to width table*/
    Sint32                            ffKernOff;                  /*offset to kerning table*/
    Sint32                            ffStylOff;                  /*offset to style mapping table*/
    short                           ffProperty[9];              /*style property info*/
    short                           ffIntl[2];                  /*for international use*/
    short                           ffVersion;                  /*version number*/
};
typedef struct FamRec                   FamRec;

enum {
    kInvalidGeneration          = 0L,
    kInvalidFontFamily          = -1,
    kInvalidFont                = 0L,
    kFMCurrentFilterFormat      = 0L,
    kFMDefaultOptions           = kNilOptions,
    kFMUseGlobalScopeOption     = 0x00000001
};

//------------------------------------------------------------------------------------------------------------------------
// From macerrors.h
enum {
    componentDllLoadErr         = -2091,                        /* Windows specific errors (when component is loading)*/
    componentDllEntryNotFoundErr = -2092,                       /* Windows specific errors (when component is loading)*/
    qtmlDllLoadErr              = -2093,                        /* Windows specific errors (when qtml is loading)*/
    qtmlDllEntryNotFoundErr     = -2094,                        /* Windows specific errors (when qtml is loading)*/
    qtmlUninitialized           = -2095,
    unsupportedOSErr            = -2096,
    unsupportedProcessorErr     = -2097
};



//------------------------------------------------------------------------------------------------------------------------
// From Balloons.h
enum {
                                                                /* Constants for Help Types in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources */
    kHMStringItem               = 1,                            /* pstring used in resource */
    kHMPictItem                 = 2,                            /* 'PICT' ResID used in resource */
    kHMStringResItem            = 3,                            /* 'STR#' ResID & index used in resource */
    kHMTEResItem                = 6,                            /* Styled Text Edit ResID used in resource ('TEXT' & 'styl') */
    kHMSTRResItem               = 7,                            /* 'STR ' ResID used in resource */
    kHMSkipItem                 = 256,                          /* don't display a balloon */
    kHMCompareItem              = 512,                          /* Compare pstring in menu item w/ PString in resource item ('hmnu' only) */
    kHMNamedResourceItem        = 1024,                         /* Use pstring in menu item to get 'STR#', 'PICT', or 'STR ' resource ('hmnu' only) */
    kHMTrackCntlItem            = 2048                          /* Reserved */
};



//----------------------------------------------------------------------------------------------------

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif


#endif /* __QTHEADER__ */
