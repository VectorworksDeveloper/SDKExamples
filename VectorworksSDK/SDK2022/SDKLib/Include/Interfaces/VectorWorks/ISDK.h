//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IDrawPad.h"
#include "IToolInteractiveDraw.h"
#include "Filing/IFileIdentifier.h"
#include "Filing/IFolderIdentifier.h"
#include "UI/IIcon.h"
#include "Workspaces/IWorkspaces.h"
#include "Units/IUnits.h"

#if _MINICAD_
#define DEFAULTVWRIDENTIFIER "Vectorworks"
#else
#define DEFAULTVWRIDENTIFIER DefaultPluginVWRIdentifier()
#endif

namespace VectorWorks
{
	using namespace VectorWorks::Filing;

	namespace Extension
	{
		class IResourceManagerContent;
	}

    struct LayerProjectInfo
    {
        bool        masterLayer;
        Sint32      modificationDate;
        Sint32      checkoutDate;
        TXString    checkoutOwner;
        TXString    workingFileId;
        TXString    comment;
        bool        outOfDate;

        LayerProjectInfo() : masterLayer(false), modificationDate(0), checkoutDate(0), checkoutOwner(""), workingFileId(""), comment(""), outOfDate(false) {}
    };

    enum class EUserProjectPermission
    {
        None = 0,
        Readonly,
        LayersRestricted,
        LayersUnrestricted,
        LayersAndResources,
        Project,
        Admin
    };

	// ---------------------------------------------------------------------------------------------------
	typedef void*		TOSWndPtr;

	//------------------------------------------------------------------------------------
	// ISDK::ImportResourceToCurrentFileN callback
	enum EImportResourceConflictResult
	{
		eImportResourceConflictResult_DoNotImport,
		eImportResourceConflictResult_Replace,
		eImportResourceConflictResult_Rename,
		eImportResourceConflictResult_AskWithUI
	};

	typedef EImportResourceConflictResult (*TImportResourceConflictCallbackProcPtr)(TXString& inoutName, void* env);

	//------------------------------------------------------------------------------------
	enum EStoryObjectBound
	{
		eStoryObjectBound_LayerElevation,
		eStoryObjectBound_LayerWallHeight,
		eStoryObjectBound_Story,
	};

	struct SStoryObjectData
	{
		EStoryObjectBound	fBound;
		Sint8				fBoundStory;	// used with fBound = eStoryObjectBound_Story
											//	if fBoundStory == 0 then it is this story
											//	if fBoundStory == 1 then it is the story above
											//	if fBoundStory == -1 then it is the story below
		TXString			fLayerLevelType;
		double				fOffset;
	};

	typedef Sint32			TObjectBoundID;

	enum EStoryLevelPopupBoundType
	{
		eTopBoundType = 0,
		eDualBoundType = 1,
		eBottomBoundType = 2
	};

    //Story boundID for parametrics that are using story level support added in 2017. 
    const TObjectBoundID    kPIOGenericStoryLevelBoundID = -3; 

	// ---------------------------------------------------------------------------------------------------
    struct SOpenFileInformation
	{
        IFileIdentifierPtr  fpFileID;
        Sint32              fFileRef;
        bool                fIsActive;   //whether this is the active file
        bool                fIsInMemoryOnly;  //true if this file hasn't been save to disk
		SOpenFileInformation(): fpFileID(IID_FileIdentifier), fFileRef(0), fIsActive(false), fIsInMemoryOnly(false) {}
	};
	
	// ---------------------------------------------------------------------------------------------------
	struct SReferencedFileInfo
	{
		short id;
		Byte type;
		TXString macFilePathName;
		TXString winFilePathName;
		Uint32 lastUpdateTimeStamp;
		Uint32 lastModifiedTimeStamp;
		Boolean bUpdateOnOpen;
		Boolean bIgnoreUserOrigin;
		Boolean bUpdateClasses;
		Boolean bCreateLayerLinks;
		Boolean bSaveCache;
		Boolean bUseLayerColors;
	};

	//-----------------------------------------------------------------------------------------------------
	struct SDeleteFileOptions
	{
		Boolean askUserIfImporting;
		Boolean keepLayers;
		Boolean keepResources;
		SDeleteFileOptions(): askUserIfImporting(true), keepLayers(true), keepResources(true) {}
	};

	// ---------------------------------------------------------------------------------------------------
	typedef TXGenericArray< WorldPt >			TVWArray_WorldPt;
	typedef TXGenericArray< WorldPt3 >			TVWArray_WorldPt3;
	typedef TXGenericArray< MCObjectHandle >	TVWArray_MCObjectHandle;
	typedef TXGenericArray< double >			TVWArray_Double;
	typedef TXGenericArray< size_t >			TVWArray_SizeT;
	typedef TXGenericArray< InternalIndex >		TVWArray_InternalIndex;
    typedef TXGenericArray< SOpenFileInformation > TVWArray_OpenFileInformation;
    typedef TXGenericArray< IFileIdentifierPtr > TVWArray_IFileIdentifierPtr;
	typedef TXGenericArray< SReferencedFileInfo > TVWArray_ReferencedFileInfo;

	//-----------------------------------------------------------------------------------------------------

	struct SHoleFaceTextureInfo {
		Sint32 fHoleNumber;
		TVWArray_InternalIndex fSideFaceTexRefs;
	};
	typedef TXGenericArray< SHoleFaceTextureInfo > THoleFaceTextureInfoArray;

	struct SProfileFaceTextureInfo {

		Sint32 fProfileNumber;
		InternalIndex fBottomFaceTexRef;
		InternalIndex fTopFaceTexRef;
		TVWArray_InternalIndex fSideFaceTexRefs;
		THoleFaceTextureInfoArray fHoleFacesTextureInfoArray;
	};

	typedef TXGenericArray< SProfileFaceTextureInfo > TProfileFaceTextureInfoArray;

	struct SFaceTextureInfo {
		TProfileFaceTextureInfoArray fProfileFacefarrItems;
	};

	// ---------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IVertexListener
	{
	public:
		virtual			~IVertexListener()			{}
		virtual void	BeginVertex(short index) = 0;
		virtual void	EndVertex(short index) = 0;
		virtual	void	MoveTo(const WorldPt& pt) = 0;
		virtual	void	LineTo(const WorldPt& pt) = 0;
	};

	class DYNAMIC_ATTRIBUTE ICustomBatchConvertParams
	{
	public:
		virtual			~ICustomBatchConvertParams() {}
		virtual bool	ShouldOpenFileForConvert(const TXString& path) = 0;
		virtual void	ConvertFile(const TXString& path) = 0;
		virtual void	GetSourceFolder(IFolderIdentifier** outFolder) = 0;
		virtual void	GetDestinationFolder(IFolderIdentifier** outFolder) = 0;
		virtual bool	ShouldWriteLogFile() = 0;
	};
	
	// ---------------------------------------------------------------------------------------------------
	enum EThicknessUnitsType
	{
		eThicknessUnitsType_Default = -1,
		eThicknessUnitsType_Mils = 0,
		eThicknessUnitsType_Points = 1,
		eThicknessUnitsType_MM = 2,
	};

	//----------------------------------------------------------------------------------------------------
	enum BackgroundType
	{
		eNone = 0,
		eCloudsBackground = 1,
		eOneColorBackground = 2,
		eTwoColorBackground = 3, 
		ePhysicalSkyBackground = 4

		//eImageBackground = 5,
		//eEnvironmentBackground = 6,
		
	};

	// ---------------------------------------------------------------------------------------------------
	enum EModeBarButtonType
	{
		eModeBarButtonType_RadioMode,
		eModeBarButtonType_ButtonMode,
		eModeBarButtonType_PrefButtonMode,
		eModeBarButtonType_CheckMode,
		eModeBarButtonType_EditTextMode,
		eModeBarButtonType_PullDownMode
	};

	struct SModeBarButtonHelp
	{
		TXString				fModeName;
		TXString				fHelpText;
		EModeBarButtonType		fModeType;
		SModeBarButtonHelp()
		{
			fModeType = eModeBarButtonType_ButtonMode;
		}
		  
		SModeBarButtonHelp( const TXString& modeName, const TXString& helpText, EModeBarButtonType modeType )
		{
			fModeName = modeName;
			fHelpText = helpText;
			fModeType = modeType;
		};
	};

	typedef TXGenericArray< SModeBarButtonHelp > TVWModeBarButtonHelpArray;

	// ---------------------------------------------------------------------------------------------------
	enum EInteractiveMode
	{
		eInteractiveMode_Pan,
		eInteractiveMode_WalkThrough,
		eInteractiveMode_FlyOver,
        eInteractiveMode_FlyOverOrigin, 
	};

    
    enum ELayoutCoordinateSpace
    {
        eLayoutCoordinateSpacePoints,
        eLayoutCoordinateSpacePixels
    };

	// ---------------------------------------------------------------------------------------------------

	struct SViewportClassOverride
	{
		ColorRef				fFillFore;
		ColorRef				fFillBack;
		ColorRef				fPenFore;
		ColorRef				fPenBack;

		OpacityRef				fFillOpacity;
		OpacityRef				fPenOpacity;

		InternalIndex			fLineStyle;
		Uint8					fLineWeight;

		Boolean					fMarkerTypeMenusAreLinked;
		SMarkerStyle			fStartMarker;
		SMarkerStyle			fEndMarker;

		SDropShadowData			fDropShadowData;

		InternalIndex			fFillRef;

		InternalIndex			fMaterialRef;
		InternalIndex			fRightMaterialRef;
		InternalIndex			fLeftMaterialRef;
		InternalIndex			fCenterMaterialRef;
		InternalIndex			fTopMaterialRef;
		InternalIndex			fDormerMaterialRef;
	};

	struct SViewportLightOverride
	{
		Boolean					fIsOn;			
		Boolean					fCastShadows;				
		Boolean					fUseEmitter;
		Boolean					fEmissionFromFile;
		Boolean					fUseColorTemperature;
		Boolean					fLitFog;

		double					fRed;
		double					fGreen;
		double					fBlue;

		double					fBrightness;
		double					fEmitterBrightness;
		double					fColorTemperature;
		short					fBrightnessUnit;
	};

	struct SViewportLayerOverride
	{
		ColorRef				fFillFore;
		ColorRef				fFillBack;
		ColorRef				fPenFore;
		ColorRef				fPenBack;

		double					fPercentOpacity;
	};

	struct SViewportLayerPropertiesOverride
	{
		Boolean					fUseLayerColor;
	};

	struct SMeshFace
	{
		TVWArray_SizeT		farrVertexIndices;
		WorldPt3			fNormal;
		InternalIndex		fTextureRef;
	};

	typedef TXGenericArray< SMeshFace > TVWMeshFacesArray;

	namespace MeshSmoothing
	{
		enum EMeshSmoothing
		{
			eNone,
			eUseDocumentPreference,
			eCustomCrease,
			eImported
		};
	}

	struct SExportImageOptions
	{
		ViewRect	fExportRect;	// leave empty for the entire screen
		bool		fUpdateVewports;
		bool		fResetAllPlugIns;
		bool		fExportGeoreferencing;

		SExportImageOptions() { fUpdateVewports = fResetAllPlugIns = true; fExportGeoreferencing = false; }
	};

	struct SDateTimeData
	{
		Uint32	fYear;
		Uint32	fMonth;
		Uint32	fDay;
		Uint32	fHour;
		Uint32	fMinute;
		Uint32	fSecond;
	};

	enum class EFitExtrudeToObjectsOption
	{
		FixedHeight,
		ClippingObjects,
		FixedHeightAndClippingObjects,
	};
	
	enum class EFitExtrudeToObjectsRoofAndSlabOption
	{
		TopFaceOfRoofSlab,
		BottomOfTopFace,
		CenterOfDatumComponent,
		BotomFaceOfDatumComponent,
		TopFaceOfBottomComponent,
		BottomFaceOfRoofSlab,
	};

	class DYNAMIC_ATTRIBUTE IMeshData : public IVWUnknown
	{
	public:
		virtual			~IMeshData() {}

		virtual bool			Save(bool inGenerateChecksum = true) = 0;

		// vertex data
		virtual	bool			HasVertexUVCoords() const = 0;
		virtual	bool			HasVertexNormals() const = 0;

		virtual	void			ClearVertex() = 0;
		virtual	size_t			GetVertexCount() const = 0;

		virtual	bool			GetVertexPosition(size_t vertexIndex, WorldPt3& outVertex) const = 0;
		virtual	void			SetVertexPosition(size_t vertexIndex, const WorldPt3& vertex) = 0;

		virtual	bool			GetVertexUVCoord(size_t vertexIndex, WorldPt& outUVCoord) const = 0;
		virtual	void			SetVertexUVCoord(size_t vertexIndex, const WorldPt& uvCoord) = 0;
		virtual void			ClearVertexUVCoords() = 0;

		virtual	bool			GetVertexNormal(size_t vertexIndex, WorldPt3& outNormal) const = 0;
		virtual	void			SetVertexNormal(size_t vertexIndex, const WorldPt3& normal) = 0;
		virtual void			ClearVertexNormals() = 0;

		virtual	void			ClearVertexNormalsAndUVCoords() = 0;

		virtual void			GetMeshSmoothing(MeshSmoothing::EMeshSmoothing & outMeshSmoothing) const = 0;
		virtual void			SetMeshSmoothing(MeshSmoothing::EMeshSmoothing inMeshSmoothing) = 0;

		virtual void			GetCreaseAngle(double & outCreaseAngle) const = 0;
		virtual void			SetCreaseAngle(double inCreaseAngle) = 0;

		// face data
		virtual	bool			HasFaceTextures() const = 0;

		virtual	void			ClearFaces() = 0;
		virtual	size_t			GetFaceCount() const = 0;

		virtual	size_t			GetFaceIndex(MCObjectHandle hMeshFace) const = 0;
		virtual	MCObjectHandle	GetFaceObject(size_t faceIndex) const = 0;

		virtual	bool			GetFaceVertices(size_t faceIndex, TVWArray_SizeT& outArrVertexIndices) const = 0;
		virtual	bool			SetFaceVertices(size_t faceIndex, const TVWArray_SizeT& arrVertexIndices) = 0;

		virtual	bool			GetFacePart(size_t faceIndex, size_t& partIndex) const = 0;
		virtual	void			SetFacePart(size_t faceIndex, size_t partIndex) = 0;

		// parts data
		virtual void			ClearParts() = 0;
		virtual size_t			GetPartsCount() const = 0;
		virtual size_t			AddPart() = 0;
		virtual size_t			AddPart(const RefNumber& texture) = 0;
		virtual bool			GetPartTexture(size_t partIndex, RefNumber& outTexture) const = 0;
		virtual bool			SetPartTexture(size_t partIndex, const RefNumber& texture) = 0;
	};

	typedef VCOMPtr<IMeshData>		IMeshDataPtr;

	// ---------------------------------------------------------------------------------------------------
	// Data to provide data for the ShowPullDownResourcePopup function
	struct SShowPullDownResourcePopup
	{
		TXString	fSpecialItemName;	// Special item, that is displayed always first
		TXString	fSpecialItemImage;	// Typically used for the 'None' item

		struct SItem
		{
			Sint32		fResourceListID;	// leave this as -1 and set a name to show a separator
			TXString	fSeparatorName;

			SItem() { fResourceListID = -1; }
		};

		typedef TXGenericArray< SItem > TItemsArray;

		TItemsArray		farrItems;

		void	AddItem(Sint32 resListID)				{ SItem item; item.fResourceListID = resListID; farrItems.Append( item ); }
		void	AddItem(const TXString& separatorName)	{ SItem item; item.fSeparatorName = separatorName; farrItems.Append( item ); }
	};

	// ---------------------------------------------------------------------------------------------------
	// To provide data for the RefreshLibrariesInResourceManager function
	struct SRefreshLibrariesOptions 
	{
		bool fUpdateVWLibs; 
		bool fUpdateVWOnlineLibs;
		bool fUpdateSubscriptionLibs;
		bool fUpdateUserLibs;
		bool fUpdateWorkgroupsLibs;

		SRefreshLibrariesOptions():fUpdateVWLibs(true), fUpdateVWOnlineLibs(true), fUpdateSubscriptionLibs(true), fUpdateUserLibs(true), fUpdateWorkgroupsLibs(true) {};
	};

	// ---------------------------------------------------------------------------------------------------
	// To provide data for the DownloadLibraryFile function
	enum class ELibrariesID {              
       elVWLibrary = 0,
       elVSSLibrary,
	   elAnother
	};

	enum class EDownloadErrors {
		errNoError = 0,
		errCancelled,
		errFileNotExists,
		errConnectionError,
		errDiskAccessError,
		errWrongFileVersionOrFormat,
		errUnknownError
	};

	struct SDownloadParams {
        bool sdpShowErrors;              // if true, we show the same errors report as for the file download command from the Resource manager; false - no error reporting

	SDownloadParams():sdpShowErrors(true){};
	};

	enum class EDocumentPrefsTab {
		saved = -1,
		display = 0,
		dimensions = 1,
		resolution = 2,
		planeMode = 3,
		planShadows = 4
	};

	// ---------------------------------------------------------------------------------------------------
	struct STesselateOptions {
		bool	fRenderWallComponent;			// true when only a single component should be exported. use fRenderWallComponentIndex to specify which component is to be rendered
		Sint32	fRenderWallComponentIndex;		// identify the component when fRenderWallComponent is 'true'; 0 is the index of the first component

		bool	fRenderWallChildObjects;		// render objects inside the wall
		STesselateOptions()		{ fRenderWallComponent = false; fRenderWallComponentIndex = 0; fRenderWallChildObjects = true; }
	};

	// bit-flags, use with | operator to mix them (note, the operator is defined underneath)
	enum EWorksheetSelectFunctionLayoutMode : Uint16
	{
		Functions	= 0x0001,
		Records		= 0x0002,
		Styles		= 0x0004,
		IFC			= 0x0008,
		COBie		= 0x0010,
		DataSheets	= 0x0020,
		All			= 0xFFFF,
	};

	inline EWorksheetSelectFunctionLayoutMode operator|(EWorksheetSelectFunctionLayoutMode lhs, EWorksheetSelectFunctionLayoutMode rhs) 
	{
		return static_cast<EWorksheetSelectFunctionLayoutMode>(static_cast<Uint16>(lhs) | static_cast<Uint16>(rhs));
	}

	// ---------------------------------------------------------------------------------------------------
	enum class ECriteriaExpressionError
	{
		  None
		, Unkonwn
		, CommaExpected
		, InvalCellRef
		, InvalChar
		, InvalExpr
		, InvalFactor
		, InvalIdent
		, InvalOperator
		, InvalRecordRef
		, InvalString
		, InvalTypes
		, LeftBracketExpected
		, LeftParenExpected
		, PeriodExpected
		, RightBracketExpected
		, RightParenExpected
	};

	//-----------------------------------------------------------------------------------------------------------------
	enum EExpressionContext : Sint16
	{
		eUniversal,  // Eval and compile using universal expressions
		eScriptUniversal, // Eval and compile for scripts using universal expressions
		eLocal,      // Eval and compile using local expressions
	};

	// ---------------------------------------------------------------------------------------------------
	// {9C3E6ED0-8290-410f-9984-0C44B71702ED}
	static const VWIID IID_SDK	= { 0x9c3e6ed0, 0x8290, 0x410f, { 0x99, 0x84, 0xc, 0x44, 0xb7, 0x17, 0x2, 0xed } };

	class DYNAMIC_ATTRIBUTE ISDK : public IVWSingletonUnknown
	{
	//  pre VW2009
	public:
		virtual Boolean VCOM_CALLTYPE GetClassBeginningMarker(InternalIndex index, SMarkerStyle& mstyle) = 0;
		virtual Boolean VCOM_CALLTYPE GetClassEndMarker(InternalIndex index, SMarkerStyle& mstyle) = 0;
		virtual void VCOM_CALLTYPE GetClColor(InternalIndex index, ObjectColorType& color) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetClFillPat(InternalIndex index) = 0;
		virtual short VCOM_CALLTYPE GetClLineWeight(InternalIndex index) = 0;
		virtual void VCOM_CALLTYPE GetClMarker(InternalIndex index, MarkerType& style, short& size, short& angle) = 0;
		virtual Boolean VCOM_CALLTYPE GetClUseGraphic(InternalIndex index) = 0;
		virtual short VCOM_CALLTYPE GetClVisibility(InternalIndex index) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetVPClassFillStyle(MCObjectHandle viewport, InternalIndex classIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetClassBeginningMarker(InternalIndex index, SMarkerStyle mstyle) = 0;
		virtual Boolean VCOM_CALLTYPE SetClassEndMarker(InternalIndex index, SMarkerStyle mstyle) = 0;
		virtual void VCOM_CALLTYPE SetClColor(InternalIndex index, ObjectColorType color) = 0;
		virtual void VCOM_CALLTYPE SetClFillPat(InternalIndex index, InternalIndex fill) = 0;
		virtual void VCOM_CALLTYPE SetClLineWeight(InternalIndex index, short mils) = 0;
		virtual void VCOM_CALLTYPE SetClMarker(InternalIndex index, MarkerType style, short size, short angle) = 0;
		virtual void VCOM_CALLTYPE SetClUseGraphic(InternalIndex index, Boolean use) = 0;
		virtual void VCOM_CALLTYPE SetClVisibility(InternalIndex index, short vis) = 0;
		virtual Boolean VCOM_CALLTYPE VPClassHasOverride(MCObjectHandle viewport, InternalIndex classIndex) = 0;
		virtual Boolean VCOM_CALLTYPE DeleteAllDLComponents() = 0;
		virtual Boolean VCOM_CALLTYPE DeleteDLComponent(Sint16 index) = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultArrowByClass() = 0;
		virtual void VCOM_CALLTYPE GetDefaultArrowHeads(Boolean& starting, Boolean& ending, ArrowType& style, short& size) = 0;
		virtual void VCOM_CALLTYPE GetDefaultArrowHeadsN(Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size) = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultBeginningMarker(SMarkerStyle& mstyle, Boolean& visibility) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetDefaultClass() = 0;
		virtual void VCOM_CALLTYPE GetDefaultColors(ObjectColorType& colors) = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultEndMarker(SMarkerStyle& mstyle, Boolean& visibility) = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultFColorsByClass() = 0;
		virtual InternalIndex VCOM_CALLTYPE GetDefaultFillPat() = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultFPatByClass() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultHatch() = 0;
		virtual short VCOM_CALLTYPE GetDefaultLineWeight() = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultLWByClass() = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultPColorsByClass() = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultPPatByClass() = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentClass(Sint16 index, Sint32 &componentClass) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentFill(Sint16 index, Sint32 &fill) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentFillColors(Sint16 index, ColorRef &fillForeColor, ColorRef &fillBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentName(Sint16 index, TXString& outComponentName) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentPenColors(Sint16 index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentPenWeights(Sint16 index, Uint8 &penWeightLeft, Uint8 &penWeightRight) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentUseFillClassAttr(Sint16 index, Boolean &useClassAttr) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentUsePenClassAttr(Sint16 index, Boolean &leftPenUseClassAttr, Boolean &rightPenUseClassAttr) = 0;
		virtual Boolean VCOM_CALLTYPE GetDLComponentWidth(Sint16 index, WorldCoord &width) = 0;
		virtual WorldCoord VCOM_CALLTYPE GetDLControlOffset() = 0;
		virtual Sint16 VCOM_CALLTYPE GetDLOptions() = 0;
		virtual WorldCoord VCOM_CALLTYPE GetDLSeparation() = 0;
		virtual InternalIndex VCOM_CALLTYPE GetDocumentDefaultSketchStyle() = 0;
		virtual Boolean VCOM_CALLTYPE GetNumberOfDLComponents(short& numComponents) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetObjectInternalIndex(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetProgramVariable(short variableSelector, void* result) = 0;
		virtual Boolean VCOM_CALLTYPE GetWallPrefStyle(InternalIndex& wallStyleNum) = 0;
		virtual Boolean VCOM_CALLTYPE GetWallStyle(MCObjectHandle theWall, InternalIndex& wallStyle) = 0;
		virtual void VCOM_CALLTYPE SetDefaultArrowByClass() = 0;
		virtual void VCOM_CALLTYPE SetDefaultArrowHeads(Boolean starting, Boolean ending, ArrowType style, short size) = 0;
		virtual void VCOM_CALLTYPE SetDefaultArrowHeadsN(Boolean starting, Boolean ending, ArrowType style, double_param size) = 0;
		virtual Boolean VCOM_CALLTYPE SetDefaultBeginningMarker(SMarkerStyle mstyle, Boolean visibility) = 0;
		virtual void VCOM_CALLTYPE SetDefaultClass(InternalIndex classID) = 0;
		virtual void VCOM_CALLTYPE SetDefaultColors(ObjectColorType colors) = 0;
		virtual Boolean VCOM_CALLTYPE SetDefaultEndMarker(SMarkerStyle mstyle, Boolean visibility) = 0;
		virtual void VCOM_CALLTYPE SetDefaultFColorsByClass() = 0;
		virtual void VCOM_CALLTYPE SetDefaultFillPat(InternalIndex theFill) = 0;
		virtual void VCOM_CALLTYPE SetDefaultFPatByClass() = 0;
		virtual Boolean VCOM_CALLTYPE SetDefaultHatch(MCObjectHandle inHatchDef) = 0;
		virtual void VCOM_CALLTYPE SetDefaultLineWeight(short mils) = 0;
		virtual void VCOM_CALLTYPE SetDefaultLWByClass() = 0;
		virtual void VCOM_CALLTYPE SetDefaultPColorsByClass() = 0;
		virtual void VCOM_CALLTYPE SetDefaultPPatByClass() = 0;
		virtual void VCOM_CALLTYPE SetDefaultWallThickness(WorldCoord thickness) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentClass(Sint16 index, Sint32 componentClass) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentFill(Sint16 index, Sint32 fill) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentFillColors(Sint16 index, ColorRef fillForeColor, ColorRef fillBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentName(Sint16 index, const TXString& componentName) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentPenColors(Sint16 index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentPenWeights(Sint16 index, Uint8 penWeightLeft, Uint8 penWeightRight) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentUseFillClassAttr(Sint16 index, Boolean useClassAttr) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentUsePenClassAttr(Sint16 index, Boolean leftPenUseClassAttr, Boolean rightPenUseClassAttr) = 0;
		virtual Boolean VCOM_CALLTYPE SetDLComponentWidth(Sint16 index, WorldCoord width) = 0;
		virtual void VCOM_CALLTYPE SetDLControlOffset(WorldCoord controlOffset) = 0;
		virtual void VCOM_CALLTYPE SetDLOptions(Sint16 options) = 0;
		virtual void VCOM_CALLTYPE SetDLSeparation(WorldCoord separation) = 0;
		virtual Boolean VCOM_CALLTYPE SetDocumentDefaultSketchStyle(InternalIndex sketchIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetProgramVariable(short variableSelector, const void* value) = 0;
		virtual Boolean VCOM_CALLTYPE SetWallPrefStyle(InternalIndex wallStyleNum) = 0;
		virtual void VCOM_CALLTYPE WrapGetDefaultWallThickness(double_gs& outCoordLen) = 0;
		virtual void VCOM_CALLTYPE Add3DVertex(MCObjectHandle h, const WorldPt3& v, Boolean recalcBounds = true) = 0;
		virtual void VCOM_CALLTYPE AddVertex(MCObjectHandle h, const WorldPt& p, VertexType t = vtCorner, WorldCoord arcRadius = 0, Boolean recalcBounds = true) = 0;
		virtual void VCOM_CALLTYPE CalcAreaN(MCObjectHandle h, double_gs& area) = 0;
		virtual void VCOM_CALLTYPE CalcPerimN(MCObjectHandle h, double_gs& perim) = 0;
		virtual double_gs VCOM_CALLTYPE CalcSurfaceArea(MCObjectHandle h) = 0;
		virtual double_gs VCOM_CALLTYPE CalcVolume(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE Centroid3D(MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG) = 0;
		virtual short VCOM_CALLTYPE CountVertices(MCObjectHandle h) = 0;
		virtual short VCOM_CALLTYPE CreateSkylight(MCObjectHandle object) = 0;
		virtual void VCOM_CALLTYPE DeleteVertex(MCObjectHandle h, short vertexNum) = 0;
		virtual void VCOM_CALLTYPE ForEach3DPointInObject(MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env) = 0;
		virtual void VCOM_CALLTYPE ForEachPolyEdge( MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv) = 0;
		virtual void VCOM_CALLTYPE Get3DVertex(MCObjectHandle h, short vertexNum, WorldPt3& vertex) = 0;
		virtual void VCOM_CALLTYPE GetArcInfoN(MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY) = 0;
		virtual Boolean VCOM_CALLTYPE GetBatAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint) = 0;
		virtual void VCOM_CALLTYPE GetControlVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius) = 0;
		virtual Boolean VCOM_CALLTYPE GetDormerAttributes(MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset) = 0;
		virtual void VCOM_CALLTYPE GetEndPoints(MCObjectHandle h, WorldPt& startPt, WorldPt& endPt) = 0;
		virtual void VCOM_CALLTYPE GetEntityMatrix(MCObjectHandle h, TransformMatrix& theMat) = 0;
		virtual void VCOM_CALLTYPE GetExtrudeValues(MCObjectHandle h, WorldCoord& bottom, WorldCoord& top) = 0;
		virtual Boolean VCOM_CALLTYPE GetGableAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang) = 0;
		virtual Boolean VCOM_CALLTYPE GetHipAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang) = 0;
		virtual void VCOM_CALLTYPE GetLocus3DPosition(MCObjectHandle h, WorldPt3& locPos) = 0;
		virtual void VCOM_CALLTYPE GetLocusPosition(MCObjectHandle h, WorldPt& locPos) = 0;
		virtual void VCOM_CALLTYPE GetMarkerPolys(MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly) = 0;
		virtual short VCOM_CALLTYPE GetNumRoofElements(MCObjectHandle object) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjectBoundingBoxVerts(MCObjectHandle h, WorldRectVerts &outBoxVerts) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjectBounds(MCObjectHandle h, WorldRect& bounds) = 0;
		virtual void VCOM_CALLTYPE GetObjectCube(MCObjectHandle h, WorldCube& boundsCube) = 0;
		virtual short VCOM_CALLTYPE GetPolyDirection(MCObjectHandle polyToCheck) = 0;
		virtual Boolean VCOM_CALLTYPE GetPolyShapeClose(MCObjectHandle h) = 0;
		virtual short VCOM_CALLTYPE GetQArcQuadrant(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetRoofAttributes(MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter) = 0;
		virtual Boolean VCOM_CALLTYPE GetRoofElementType(MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType) = 0;
		virtual void VCOM_CALLTYPE GetRRectDiameters(MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam) = 0;
		virtual Boolean VCOM_CALLTYPE GetShedAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang) = 0;
		virtual Boolean VCOM_CALLTYPE GetSkylight(MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName) = 0;
		virtual void VCOM_CALLTYPE GetSweepAnglesN(MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle) = 0;
		virtual Boolean VCOM_CALLTYPE GetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope) = 0;
		virtual void VCOM_CALLTYPE GetVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius) = 0;
		virtual void VCOM_CALLTYPE Insert3DVertex(MCObjectHandle h, const WorldPt3& p, short beforeVertex, Boolean recalcBounds = true) = 0;
		virtual void VCOM_CALLTYPE InsertVertex(MCObjectHandle h, const WorldPt& p, short beforeVertex, VertexType t = vtCorner, WorldCoord arcRadius = 0, Boolean recalcBounds = true) = 0;
		virtual Boolean VCOM_CALLTYPE Moments3D(MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsCurveEvaluatePoint(MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt) = 0;
		virtual Sint32 VCOM_CALLTYPE NurbsCurveGetNumPieces(MCObjectHandle nHandle) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsCurveType(MCObjectHandle nHandle, Sint32 index, bool& isByWeight) = 0;
		virtual short VCOM_CALLTYPE NurbsDegree(MCObjectHandle nHandle, Sint32 index) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsDelVertex(MCObjectHandle nHandle, Sint32 index1, Sint32 index2) = 0;
		virtual Sint32 VCOM_CALLTYPE NurbsGetNumPts(MCObjectHandle nHandle, Sint32 index) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsGetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsGetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot) = 0;
		virtual Sint32 VCOM_CALLTYPE NurbsNumKnots(MCObjectHandle nHandle, Sint32 index) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsSetKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsSetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsSetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight) = 0;
		virtual Boolean VCOM_CALLTYPE NurbsSurfaceEvaluatePoint(MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt) = 0;
		virtual double_gs VCOM_CALLTYPE ObjArea(MCObjectHandle h) = 0;
		virtual double_gs VCOM_CALLTYPE ObjSurfaceArea(MCObjectHandle h) = 0;
		virtual double_gs VCOM_CALLTYPE ObjVolume(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE Products3D(MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx) = 0;
		virtual void VCOM_CALLTYPE RemoveRoofElement(MCObjectHandle object, short id) = 0;
		virtual void VCOM_CALLTYPE Set3DVertex(MCObjectHandle h, short vertexNum, const WorldPt3& vertex, Boolean recalcBounds = true) = 0;
		virtual void VCOM_CALLTYPE SetArcAnglesN(MCObjectHandle h, double_param startAngle, double_param sweepAngle) = 0;
		virtual Boolean VCOM_CALLTYPE SetBatAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, WorldCoord topWidth, WorldCoord baseHeight, double_param topSlope, WorldCoord controlPoint) = 0;
		virtual Boolean VCOM_CALLTYPE SetDormerAttributes(MCObjectHandle object, const short dormerID, short edgeIndex, WorldCoord cornerOffset, Boolean isPerpOffset, WorldCoord perpOrHeightOffset, InternalIndex symName, Boolean centerSymbol, WorldCoord symOffset) = 0;
		virtual void VCOM_CALLTYPE SetDormerThick(MCObjectHandle object, WorldCoord wallThick, WorldCoord roofThick) = 0;
		virtual void VCOM_CALLTYPE SetEndPoints(MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt) = 0;
		virtual void VCOM_CALLTYPE SetEntityMatrix(MCObjectHandle h, const TransformMatrix& theMat) = 0;
		virtual void VCOM_CALLTYPE SetExtrudeValues(MCObjectHandle h, WorldCoord bottom, WorldCoord top) = 0;
		virtual Boolean VCOM_CALLTYPE SetGableAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, WorldCoord overhang) = 0;
		virtual Boolean VCOM_CALLTYPE SetHipAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, double_param frontSlope, WorldCoord overhang) = 0;
		virtual void VCOM_CALLTYPE SetLocus3DPosition(MCObjectHandle h, const WorldPt3& locPos) = 0;
		virtual void VCOM_CALLTYPE SetLocusPosition(MCObjectHandle h, const WorldPt& locPos) = 0;
		virtual void VCOM_CALLTYPE SetObjectBounds(MCObjectHandle h, const WorldRect& bounds) = 0;
		virtual void VCOM_CALLTYPE SetPolyShapeClose(MCObjectHandle h, Boolean closed) = 0;
		virtual void VCOM_CALLTYPE SetQArcQuadrant(MCObjectHandle h, short quadrant) = 0;
		virtual void VCOM_CALLTYPE SetRoofAccessoriesParameters(MCObjectHandle roof, Boolean insertAttic, Boolean insertSoffit, Boolean insertFascia, WorldCoord fasciaWidth, WorldCoord fasciaHeight, WorldCoord atticHeight, WorldCoord recess, WorldCoord rakeThick, WorldCoord trimDepth) = 0;
		virtual void VCOM_CALLTYPE SetRoofAttributes(MCObjectHandle object, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter) = 0;
		virtual void VCOM_CALLTYPE SetRRectDiameters(MCObjectHandle h, WorldCoord xDiam, WorldCoord yDiam) = 0;
		virtual Boolean VCOM_CALLTYPE SetShedAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param topSlope, WorldCoord overhang) = 0;
		virtual Boolean VCOM_CALLTYPE SetSkylight(MCObjectHandle object, const short skylightID, short edgeIndex, WorldCoord cornerOffset, WorldCoord perpOffset, InternalIndex symName) = 0;
		virtual void VCOM_CALLTYPE SetSweepAnglesN(MCObjectHandle theSweep, double_param startAngle, double_param arcAngle, double_param incrAngle) = 0;
		virtual void VCOM_CALLTYPE SetSweepScrew(MCObjectHandle theSweep, WorldCoord dist) = 0;
		virtual Boolean VCOM_CALLTYPE SetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, Boolean useTopWidth, WorldCoord topWidth, double_param leftSlope, double_param rightSlope, double_param topSlope) = 0;
		virtual void VCOM_CALLTYPE SetVertex(MCObjectHandle h, short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius, Boolean recalcBounds = true) = 0;
		virtual void VCOM_CALLTYPE WrapGetSweepScrew(MCObjectHandle theSweep, double_gs& outCoordLen) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCircularDimension(const WorldPt& center, const WorldPt& end, WorldCoord startOffset, WorldCoord textOffset, const WorldRect& box, Boolean isRadius) = 0;
		virtual Boolean VCOM_CALLTYPE GetArrowByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE GetArrowHeads(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size) = 0;
		virtual void VCOM_CALLTYPE GetArrowHeadsN(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size) = 0;
		virtual Boolean VCOM_CALLTYPE GetColor(MCObjectHandle h, ObjectColorType& colors) = 0;
		virtual OpacityRef VCOM_CALLTYPE GetDefaultOpacity() = 0;
		virtual Boolean VCOM_CALLTYPE GetDefaultOpacityByClass() = 0;
		virtual Boolean VCOM_CALLTYPE GetFColorsByClass(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetFillIAxisEndPoint(MCObjectHandle objectHandle, WorldPt& iAxisEndPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetFillJAxisEndPoint(MCObjectHandle objectHandle, WorldPt& jAxisEndPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetFillOriginPoint(MCObjectHandle objectHandle, WorldPt& originPoint) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetFillPat(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetFillPoints(MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetFPatByClass(MCObjectHandle h) = 0;
		virtual short VCOM_CALLTYPE GetLineWeight(MCObjectHandle h) = 0;
		virtual short VCOM_CALLTYPE GetLineWeightDisplayMM(short mils) = 0;
		virtual short VCOM_CALLTYPE GetLineWeightDisplayPt(short mils) = 0;
		virtual Boolean VCOM_CALLTYPE GetLWByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE GetMarker(MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjBeginningMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjEndMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility) = 0;
		virtual OpacityRef VCOM_CALLTYPE GetOpacity(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetOpacityByClass(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetPColorsByClass(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetPPatByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE GetVertexVis(MCObjectHandle h, short vertNum, Boolean& vis) = 0;
		virtual void VCOM_CALLTYPE SetArrowByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE SetArrowHeads(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, short size) = 0;
		virtual void VCOM_CALLTYPE SetArrowHeadsN(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, double_param size) = 0;
		virtual void VCOM_CALLTYPE SetColor(MCObjectHandle h, ObjectColorType colors) = 0;
		virtual void VCOM_CALLTYPE SetDefaultOpacity(OpacityRef inOpacity) = 0;
		virtual void VCOM_CALLTYPE SetDefaultOpacityByClass() = 0;
		virtual void VCOM_CALLTYPE SetFColorsByClass(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE SetFillIAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint) = 0;
		virtual Boolean VCOM_CALLTYPE SetFillJAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint) = 0;
		virtual Boolean VCOM_CALLTYPE SetFillOriginPoint(MCObjectHandle objectHandle, const WorldPt& originPoint) = 0;
		virtual void VCOM_CALLTYPE SetFillPat(MCObjectHandle h, InternalIndex theFill) = 0;
		virtual void VCOM_CALLTYPE SetFPatByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE SetLineWeight(MCObjectHandle h, short mils) = 0;
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayMM(short hundredths) = 0;
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayPt(short sixteenths) = 0;
		virtual void VCOM_CALLTYPE SetLWByClass(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE SetObjBeginningMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility) = 0;
		virtual Boolean VCOM_CALLTYPE SetObjEndMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility) = 0;
		virtual void VCOM_CALLTYPE SetOpacity(MCObjectHandle h, OpacityRef  inNewOpacity) = 0;
		virtual void VCOM_CALLTYPE SetOpacityByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE SetPColorsByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE SetPPatByClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE SetVertexVis(MCObjectHandle h, short vertNum, Boolean vis) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetDefinition(MCObjectHandle h) = 0;
		virtual short VCOM_CALLTYPE GetDXFColorToLineWeight(const short inDXFColorIndex) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedObject(const TXString& objName) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetObjectClass(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE GetObjectName(MCObjectHandle h, TXString& outName) = 0;
		virtual short VCOM_CALLTYPE GetObjectType(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE GetSymbolDefinitionIcon(MCObjectHandle theSymDef, Sint32 icon[32] ) = 0;
		virtual short VCOM_CALLTYPE GetSymbolDefinitionType(MCObjectHandle theSymDef) = 0;
		virtual Boolean VCOM_CALLTYPE IsLocked(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE IsSelected(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE IsVisible(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE LockObject(MCObjectHandle h, Boolean lock = true) = 0;
		virtual void VCOM_CALLTYPE SelectObject(MCObjectHandle h, Boolean select = true) = 0;
		virtual void VCOM_CALLTYPE SetDXFColorToLineWeight(const short inDXFColorIndex, const short inLineWeight) = 0;
		virtual void VCOM_CALLTYPE SetObjectClass(MCObjectHandle h, InternalIndex classID) = 0;
		virtual GSError VCOM_CALLTYPE SetObjectName(MCObjectHandle h, const TXString& name) = 0;
		virtual void VCOM_CALLTYPE SetSymbolDefinitionIcon(MCObjectHandle theSymDef, const Sint32 icon[32] ) = 0;
		virtual void VCOM_CALLTYPE SetVisibility(MCObjectHandle h, Boolean visible) = 0;
		virtual void VCOM_CALLTYPE AttachAuxObject(MCObjectHandle h, MCObjectHandle newOwner) = 0;
		virtual void VCOM_CALLTYPE DeleteAuxObject(MCObjectHandle h, MCObjectHandle owner) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE FindAuxObject(MCObjectHandle owner, short objectType) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE FindDataObject(MCObjectHandle owner, OSType tag) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE FirstAuxObject(MCObjectHandle h) = 0;
		virtual OSType VCOM_CALLTYPE GetDataTag(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE GetPluginType(const TXString& name, EVSPluginType& type) = 0;
		virtual Boolean VCOM_CALLTYPE IsPluginFormat(MCObjectHandle h) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE NewDataObject(MCObjectHandle attachTo, OSType tag, size_t objectSize) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE NextAuxObject(MCObjectHandle start, short objectType) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE NextDataObject(MCObjectHandle start, OSType tag) = 0;
		virtual void VCOM_CALLTYPE RemoveAuxObject(MCObjectHandle h, MCObjectHandle owner) = 0;
		virtual Boolean VCOM_CALLTYPE TaggedDataCreate(MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,Sint32 numDataElements) = 0;
		virtual Boolean VCOM_CALLTYPE TaggedDataGet(MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,Sint32 dataIndex, void* getData) = 0;
		virtual Boolean VCOM_CALLTYPE TaggedDataGetNumElements(MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,Sint32* getData) = 0;
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveContainer(MCObjectHandle inOwnerObj,OSType dataContainer) = 0;
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveTag(MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag) = 0;
		virtual Boolean VCOM_CALLTYPE TaggedDataSet(MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,Sint32 dataIndex, const void* data) = 0;
		virtual double_gs VCOM_CALLTYPE CoordLengthToPageLengthN(WorldCoord len) = 0;
		virtual double_gs VCOM_CALLTYPE CoordLengthToPagePoints(WorldCoord len) = 0;
		virtual Boolean VCOM_CALLTYPE CoordLengthToPixelLength(WorldCoord numCoords, short& numPixels) = 0;
		virtual double_gs VCOM_CALLTYPE CoordLengthToUnitsLengthN(WorldCoord len) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateOvalN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height) = 0;
		virtual Boolean VCOM_CALLTYPE DimStringToCoord(const TXString& s, WorldCoord& c) = 0;
		virtual void VCOM_CALLTYPE FPCoordLengthToPageLength(double_param coordLen, double_gs& pageLen) = 0;
		virtual void VCOM_CALLTYPE FPCoordLengthToUnitsLength(double_param coordLen, double_gs& unitsLen) = 0;
		virtual void VCOM_CALLTYPE ModelPt2DToScreenPt(WorldPt& vertex) = 0;
		virtual void VCOM_CALLTYPE ModelVecToScreenVec(WorldPt& vertex) = 0;
		virtual void VCOM_CALLTYPE PageLengthToFPCoordLength(double_param pageLen, double_gs& coordLen) = 0;
		virtual WorldCoord VCOM_CALLTYPE PagePointsToCoordLength(double_gs& points) = 0;
		virtual void VCOM_CALLTYPE PixelLengthToCoordLength(short numPixels, WorldCoord& numCoords) = 0;
		virtual void VCOM_CALLTYPE ScreenPtToModelPt2D(WorldPt& vertex) = 0;
		virtual void VCOM_CALLTYPE ScreenVecToModelVec(WorldPt& vertex) = 0;
		virtual void VCOM_CALLTYPE UnitsLengthToFPCoordLength(double_param unitsLen, double_gs& coordLen) = 0;
		virtual WorldCoord VCOM_CALLTYPE WorldCoordsPerDrawingUnit() = 0;
		virtual void VCOM_CALLTYPE WrapPageLengthToCoordLengthN(double_param len, double_gs& outCoordLen) = 0;
		virtual void VCOM_CALLTYPE WrapUnitsLengthToCoordLengthN(double_param len, double_gs& outCoordLen) = 0;
		virtual short VCOM_CALLTYPE AddSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid) = 0;
		virtual Boolean VCOM_CALLTYPE AppendRoofEdge(MCObjectHandle object, const WorldPt& edgePt, double_param slope, WorldCoord projection, WorldCoord eaveHeight) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE Create3DPoly() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateAngleDimension(const WorldPt& center, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateArcN(const WorldRect& bounds, double_param startAngle, double_param sweepAngle) = 0;
		virtual short VCOM_CALLTYPE CreateBatDormer(MCObjectHandle object) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateChainDimension(MCObjectHandle h1, MCObjectHandle h2) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCombineIntoSurface(const WorldPt& inPoint) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCone(const WorldPt3& center, const WorldPt3 &tip, WorldCoord radius) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateContourCurves(MCObjectHandle h, double_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomDimensionStandard(const TXString& name) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObject(const TXString& name, const WorldPt& location, double_param angle = 0.0, bool bInsert = true) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectDoubleClick(const TXString& name) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectPath(const TXString& name, MCObjectHandle pathHand = NULL, MCObjectHandle profileGroupHand = NULL) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrude(WorldCoord bottom, WorldCoord top) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrudeAlongPath(MCObjectHandle pathHandle, MCObjectHandle profileHandle) = 0;
		virtual short VCOM_CALLTYPE CreateGableDormer(MCObjectHandle object) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateGroup() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateHemisphere(const WorldPt3& center, const WorldPt3 &topPoint) = 0;
		virtual short VCOM_CALLTYPE CreateHipDormer(MCObjectHandle object) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageProp(TXString& propName, InternalIndex textureRef, WorldCoord height, WorldCoord width, Boolean enforceImageAspectRatio, Boolean crossedPlanes, Boolean createPlugin, Boolean autoRotate, Boolean createSymbol) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateInterpolatedSurface(MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayer(const TXString& layerName, short layerType) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayerN(const TXString& name, double_param scale) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLightN(const WorldPt3& pos, short kind, Boolean isOn, double_param brightness, const WorldPt3& color, Boolean castShadows) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLine(const WorldPt& startPt, const WorldPt& endPt) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLinearDimension(const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset, WorldCoord textOffset, const Vector2& dir, short dimType) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus(const WorldPt& location) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus3D(const WorldPt3& location) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateLoftSurfaces(MCObjectHandle groupCurvesH, Boolean bRule, Boolean  bClose, Boolean bSolid) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsCurve(WorldPt3 firstPt, bool byCtrlPts, short degree) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsSurface(Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateOval(const WorldRect& bounds) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreatePolyshape() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateQArc(const WorldRect& bounds, short quadrant) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangle(const WorldRect& bounds) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoof(Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoundWall(const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, WorldCoord wallThickness = 0) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangle(const WorldRect& bounds, WorldCoord xDiam, WorldCoord yDiam) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, Boolean isProportional) = 0;
		virtual short VCOM_CALLTYPE CreateShedDormer(MCObjectHandle object) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateBasicSlab(short slabKind) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateSphere(const WorldPt3& center, WorldCoord radius) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatch(const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatchFromObject(MCObjectHandle inObj, const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle) = 0;
		virtual Boolean VCOM_CALLTYPE CreateSurfacefromCurvesNetwork() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateSweepN(double_param startAngle, double_param arcAngle, double_param incrAngle, WorldCoord screwDist) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolDefinition(TXString& inoutName) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolFolder(const TXString& name) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateTaperedExtrude(MCObjectHandle profileH, const double_param angle = 0.0, const double_param height = 1.0 ) = 0;
		virtual short VCOM_CALLTYPE CreateTrapeziumDormer(MCObjectHandle object) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateViewport(MCObjectHandle parentHandle) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateWall(const WorldPt& startPt, const WorldPt& endPt, WorldCoord thickness = 0) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE DefineCustomObject(const TXString& name, Byte prefWhen = kCustomObjectPrefAlways) = 0;
		virtual void VCOM_CALLTYPE DuplicateSelection(WorldCoord dx, WorldCoord dy) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsCurve(MCObjectHandle curveHandle, double_param distance, Boolean bStart, Boolean bLinear) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsSurface(MCObjectHandle surfaceHandle, double_param distance, Boolean bStart, Boolean bLinear, Boolean bUDir) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GenerateBezierApproximationFromPolygon(MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GroupSelection() = 0;
		virtual short VCOM_CALLTYPE IntersectSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolByNameN(const TXString& symName, const WorldPt& location, double_param rotation = 0.0) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolN(MCObjectHandle definition, const WorldPt& location, double_param rotation = 0.0) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE RevolveWithRail(MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH) = 0;
		virtual void VCOM_CALLTYPE Split2DObjectByLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles) = 0;
		virtual short VCOM_CALLTYPE SubtractSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid) = 0;
		virtual void VCOM_CALLTYPE AddChoice(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short nItemIndex) = 0;
		virtual void VCOM_CALLTYPE AddListBoxTabStop(Sint32 dialogID, Sint32 componentID, Sint32 tabStop) = 0;
		virtual Boolean VCOM_CALLTYPE AdjustComponentPixelPos(Sint32 nDialogID, Sint32 nComponentID, Sint32 nHorizontalPixels, Sint32 nVerticalPixels) = 0;
		virtual void VCOM_CALLTYPE AlertCritical(const TXString& text, const TXString& advice = "") = 0;
		virtual void VCOM_CALLTYPE AlertInform(const TXString& text, const TXString& advice = "", bool minorAlert = false, const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "") = 0;
		virtual short VCOM_CALLTYPE AlertQuestion(const TXString& question, const TXString& advice = "", short defaultButton = 0, const TXString& OKOverrideText = "", const TXString& CancelOverrideText = "", const TXString& customButtonAText = "", const TXString& customButtonBText = "", const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "") = 0;
		virtual bool VCOM_CALLTYPE AlignBottomEdge(Sint32 dialogID, Sint32 srcItemID, short bottomID, short alignMode = 1) = 0;
		virtual bool VCOM_CALLTYPE AlignLeftEdge(Sint32 dialogID, Sint32 srcItemID, short leftID, short alignMode = 1) = 0;
		virtual bool VCOM_CALLTYPE AlignRightEdge(Sint32 dialogID, Sint32 srcItemID, short rightID, short alignMode = 1) = 0;
		virtual Boolean VCOM_CALLTYPE AreListBrowserColumnLinesEnabled(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean VCOM_CALLTYPE AreListBrowserRadioColumnLinesEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE ClearGradientSliderSegments(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean VCOM_CALLTYPE Confirm(const TXString & strNode, Boolean yesOrNo) = 0;
		virtual void VCOM_CALLTYPE CreateCenteredStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateCheckBox(Sint32 dialogID, Sint32 itemID, const TXString& name) = 0;
		virtual void VCOM_CALLTYPE CreateCheckBoxGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame) = 0;
		virtual Boolean VCOM_CALLTYPE CreateClassPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateCMYKColorSwatch(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreateColorPopup(Sint32 dialogID, Sint32 itemID, short widthInStdChar = -1) = 0;
		virtual void VCOM_CALLTYPE CreateControl(Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data) = 0;
		virtual void VCOM_CALLTYPE CreateCustomControl(Sint32 dlogID, Sint32 controlID, short widthInPixels, short heightInPixels) = 0;
		virtual Boolean VCOM_CALLTYPE CreateDesignLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateEditInteger(Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, short widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateEditReal(Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, short widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateEditText(Sint32 dialogID, Sint32 itemID, const TXString& defaultText, short widthInStdChar, short heightInLines = 1) = 0;
		virtual Boolean VCOM_CALLTYPE CreateEnhancedPullDownMenu(Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, Boolean bShowIconInMainWindow) = 0;
		virtual void VCOM_CALLTYPE CreateGroupBox(Sint32 dialogID, Sint32 itemID, const TXString& name, Boolean hasFrame) = 0;
		virtual Boolean VCOM_CALLTYPE CreateIconPushButton(Sint32 nDialogID, Sint32 nComponentID, Sint32 nIconID, Sint32 widthInStdChar) = 0;	// DEPRECATED
		virtual Boolean VCOM_CALLTYPE CreateImageControl(Sint32 liDialogID, Sint32 liComponentID, Sint32 iWidthPixels, Sint32 iHeightPixels, MCObjectHandle hImage) = 0;
		virtual Sint32 VCOM_CALLTYPE CreateLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName) = 0;
		virtual void VCOM_CALLTYPE CreateLineAttributePopup(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreateLineStylePopup(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreateLineWeightPopup(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreateListBox(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines) = 0;
		virtual void VCOM_CALLTYPE CreateListBoxN(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines, Boolean isMultiSel) = 0;
		virtual void VCOM_CALLTYPE CreateListBrowser(Sint32 dialogID, Sint32 componentID, Sint16 widthInStdChar, Sint16 heightInLines) = 0;
		virtual void VCOM_CALLTYPE CreateMarkerPopup(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreatePatternPopup(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreatePullDownMenu(Sint32 dialogID, Sint32 itemID, short widthInStdChar) = 0;
		virtual Boolean VCOM_CALLTYPE CreatePullDownMenuGroupBox(Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, const TXString& strLabel, Boolean bHasFrame) = 0;
		virtual void VCOM_CALLTYPE CreatePushButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName) = 0;
		virtual void VCOM_CALLTYPE CreateRadioButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName) = 0;
		virtual void VCOM_CALLTYPE CreateRadioButtonGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame) = 0;
		virtual Sint32 VCOM_CALLTYPE CreateResizableLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, Boolean widthResizable, Boolean heightResizable) = 0;
		virtual void VCOM_CALLTYPE CreateRightStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar) = 0;
		virtual Boolean VCOM_CALLTYPE CreateSeparator(Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInPixels) = 0;
		virtual Boolean VCOM_CALLTYPE CreateSheetLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateStandardIconControl(Sint32 dialogID, Sint32 iconControlID, Sint32 iconNumber) = 0;
		virtual void VCOM_CALLTYPE CreateStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar) = 0;
		virtual void VCOM_CALLTYPE CreateSwapControl(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void VCOM_CALLTYPE CreateSwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID) = 0;
		virtual void VCOM_CALLTYPE CreateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut) = 0;
		virtual void VCOM_CALLTYPE CreateTabControl(Sint32 dialogID, short itemID) = 0;
		virtual void VCOM_CALLTYPE CreateTabPane(Sint32 dialogID, short itemID, short groupID) = 0;
		virtual Boolean VCOM_CALLTYPE CreateThreeStateCheckBox(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName) = 0;
		virtual Boolean VCOM_CALLTYPE CreateTreeControl(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar, Sint32 heightInLines) = 0;
		virtual void VCOM_CALLTYPE DeleteAllItems(Sint32 dialogID, Sint32 itemID) = 0;
		virtual Boolean VCOM_CALLTYPE DeleteAllListBrowserItems(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
		virtual void VCOM_CALLTYPE DeselectEditText(Sint32 dialogID, Sint32 controlID) = 0;
		virtual Boolean VCOM_CALLTYPE DisplayColorPopup(Sint32 top, Sint32 left, Sint32 bottom, Sint32 right, Boolean inDisplayByClassOption, ColorRef& ioColorRef, Boolean& ioIsByClass) = 0;
		virtual void VCOM_CALLTYPE DisplaySwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber) = 0;
		virtual void VCOM_CALLTYPE DisplayTabPane(Sint32 dialogID, Sint32 controlID, Sint32 groupNumber) = 0;
		virtual void VCOM_CALLTYPE EnableItem(Sint32 dialogID, Sint32 itemID, Boolean bEnable) = 0;
		virtual Boolean VCOM_CALLTYPE EnableListBrowser(Sint32 dialogID, Sint32 componentID, Boolean enable) = 0;
		virtual Boolean VCOM_CALLTYPE EnableListBrowserClickAllDataChange(Sint32 dialogID, Sint32 componentID, Boolean enable) = 0;
		virtual void VCOM_CALLTYPE EnableListBrowserColumnLines(Sint32 dialogID, Sint32 componentID, Boolean enableColumnLines) = 0;
		virtual void VCOM_CALLTYPE EnableListBrowserColumnTracking(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableColumnTracking) = 0;
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable) = 0;
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDropOnIndices(Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartIndex, Sint32 iEndIndex, Boolean bEnable) = 0;
		virtual void VCOM_CALLTYPE EnableListBrowserRadioColumnLines(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableRadioColumnLines) = 0;
		virtual Boolean VCOM_CALLTYPE EnableListBrowserSingleLineSelection(Sint32 dialogID, Sint32 componentID, Boolean enable) = 0;
		virtual void VCOM_CALLTYPE EnableListBrowserSorting(Sint32 dialogID, Sint32 componentID, Boolean enableSorting) = 0;
		virtual Boolean VCOM_CALLTYPE EnableListBrowserUpdates(Sint32 liDialogID, Sint32 liComponentID, Boolean bEnableUpdates) = 0;
		virtual Boolean VCOM_CALLTYPE EnsureListBrowserItemIsVisible(Sint32 dialogID, Sint32 componentID, Sint32 iIndex) = 0;
		virtual Boolean VCOM_CALLTYPE ExpandTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, Boolean bExpand) = 0;
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& columnDataItemIndex) = 0;
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& itemIndex) = 0;
		virtual Boolean VCOM_CALLTYPE FormatTextDialog(FormatTextType& formatTextRec) = 0;
		virtual Sint32 VCOM_CALLTYPE GetActiveEditItem(Sint32 dialogID) = 0;
		virtual Sint32 VCOM_CALLTYPE GetActivePane(Sint32 dialogID, Sint32 controlID) = 0;
		virtual void VCOM_CALLTYPE GetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean& state) = 0;
		virtual void VCOM_CALLTYPE GetChoiceCount(Sint32 dialogID, Sint32 itemID, short& numItems) = 0;
		virtual void VCOM_CALLTYPE GetChoiceIndex(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex) = 0;
		virtual void VCOM_CALLTYPE GetChoiceText(Sint32 dialogID, Sint32 itemID, short nItemIndex, TXString& outItemText) = 0;
		virtual void VCOM_CALLTYPE GetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor) = 0;
		virtual void VCOM_CALLTYPE GetColorButton(Sint32 dialogID, Sint32 itemID, RGBColor& rgb) = 0;
		virtual void VCOM_CALLTYPE GetColorChoice(Sint32 dialogID, Sint32 itemID, short& colorIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentRect(Sint32 nDialogID, Sint32 nComponentID, Sint32& nLeft, Sint32& nTop, Sint32& nRight, Sint32& nBottom, ELayoutCoordinateSpace cooredinateSpace = eLayoutCoordinateSpacePoints) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentTextWidth(Sint32 nDialogID, Sint32 nComponentID, Sint32& nWidthInLMUnits) = 0;
		virtual void VCOM_CALLTYPE GetControlData(Sint32 dialogID, Sint32 itemID, SControlDataBase& data) = 0;
		virtual void VCOM_CALLTYPE GetCustomControlScrollArea(Sint32 dialogID, Sint32 component, Sint32 *leftStart, Sint32 *topStart) = 0;
		virtual bool VCOM_CALLTYPE GetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32& value) = 0;
		virtual bool VCOM_CALLTYPE GetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double& value) = 0;
		virtual Boolean VCOM_CALLTYPE GetGradientSliderData(Sint32 dialogID, Sint32 componentID, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color) = 0;
		virtual Boolean VCOM_CALLTYPE GetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType) = 0;
		virtual Boolean VCOM_CALLTYPE GetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetImagePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
		virtual short VCOM_CALLTYPE GetImagePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) = 0;
		virtual short VCOM_CALLTYPE GetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void VCOM_CALLTYPE GetItemText(Sint32 dialogID, Sint32 itemID, TXString& outCurrentText) = 0;
		virtual Boolean VCOM_CALLTYPE GetLayoutDialogPosition(Sint32 dialogID, short& left, short& top, short& right, short& bottom) = 0;
		virtual void VCOM_CALLTYPE GetLayoutDialogSize(Sint32 dialogID, short& width, short& height) = 0;
		virtual void VCOM_CALLTYPE GetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short& lineWeight) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short columnIndex, short& width) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnDataItemInfo(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex, TXString& itemString, short &imageOn, short &imageOff, Sint32 &itemData) = 0;
		virtual Sint32 VCOM_CALLTYPE GetListBrowserColumnSortState(Sint32 dialogID, Sint32 componentID, Sint32 columnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 &iOwnerDrawnType) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 &iJustification) = 0;
		virtual short VCOM_CALLTYPE GetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual short VCOM_CALLTYPE GetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserEventInfo(Sint32 dialogID, Sint32 componentID, Sint32& iEventType, Sint32& iRowIndex, Sint32& iColumnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32& nUserData) = 0;
		virtual short VCOM_CALLTYPE GetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &liRefNumber) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, short& imageIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &justification) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, unsigned char &textStyle) = 0;
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &redIndex, Sint32 &greenIndex, Sint32 &blueIndex) = 0;
		virtual Sint32 VCOM_CALLTYPE GetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void VCOM_CALLTYPE GetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType& style, Sint8& angle, double& size, double& width, Uint8& thicknessBasis, double& thickness) = 0;
		virtual short VCOM_CALLTYPE GetMarkerPopupSelectedItem(Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size) = 0;
		virtual GSHandle VCOM_CALLTYPE GetMultilineText(Sint32 dialogID, Sint32 itemID) = 0;
		virtual short VCOM_CALLTYPE GetNumGradientSliderSegments(Sint32 dialogID, Sint32 componentID) = 0;
		virtual short VCOM_CALLTYPE GetNumImagePopupItems(Sint32 dialogID, Sint32 componentID) = 0;
		virtual short VCOM_CALLTYPE GetNumListBrowserColumns(Sint32 dialogID, Sint32 componentID) = 0;
		virtual short VCOM_CALLTYPE GetNumListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual short VCOM_CALLTYPE GetNumListBrowserItems(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Sint32 VCOM_CALLTYPE GetNumSelectedListBrowserItems(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void VCOM_CALLTYPE GetPatternData(Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor) = 0;
		virtual void VCOM_CALLTYPE GetSelChoiceIndex(Sint32 dialogID, Sint32 itemID, short inStartIndex, short& outSelectedIndex) = 0;
		virtual void VCOM_CALLTYPE GetSelectedChoiceIndex(Sint32 dialogID, Sint32 itemID, short& nItemIndex) = 0;
		virtual void VCOM_CALLTYPE GetSelectionRange(Sint32 dialogID, Sint32 controlID, Sint32& startPos, Sint32& endPos) = 0;
		virtual Boolean VCOM_CALLTYPE GetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, Sint32& iState) = 0;
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData) = 0;
		virtual Boolean VCOM_CALLTYPE GetTreeControlSelectedItem(Sint32 nDialogID, Sint32 nComponentID, Sint32& nItemID) = 0;
		virtual short VCOM_CALLTYPE InsertGradientSliderSegment(Sint32 dialogID, Sint32 componentID, double_param spotPosition, const WorldPt3& color) = 0;
		virtual short VCOM_CALLTYPE InsertImagePopupObjectItem(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) = 0;
		virtual Sint32 VCOM_CALLTYPE InsertImagePopupResource(Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index) = 0;
		virtual Sint32 VCOM_CALLTYPE InsertImagePopupSeparator(Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel) = 0;
		virtual short VCOM_CALLTYPE InsertListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& headerString, short width) = 0;
		virtual short VCOM_CALLTYPE InsertListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short imageOn, short imageOff, Sint32 itemData) = 0;
		virtual short VCOM_CALLTYPE InsertListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex, const TXString& itemString) = 0;
		virtual Sint32 VCOM_CALLTYPE InsertTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, Sint32 nParentID, Sint32 nAfterID) = 0;
		virtual Boolean VCOM_CALLTYPE IsItemEnabled(Sint32 nDialogID, Sint32 nComponentID) = 0;
		virtual Boolean VCOM_CALLTYPE IsItemVisible(Sint32 nDialogID, Sint32 nComponentID) = 0;
		virtual Boolean VCOM_CALLTYPE IsListBrowserColumnTrackingEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemSelected(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
        virtual Boolean VCOM_CALLTYPE SetListBrowserItemInteractionType(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, EListBrowserItemInteractionType interactionType) = 0;
		virtual Boolean VCOM_CALLTYPE IsListBrowserSortingEnabled(Sint32 dialogID, Sint32 componentID) = 0;
        virtual Boolean VCOM_CALLTYPE GetListBrowserItemCheckState(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, int& iState) = 0;
        virtual Boolean VCOM_CALLTYPE SetListBrowserItemCheckState(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const int iState) = 0;
        virtual void VCOM_CALLTYPE SetListBrowserReadOnly(Sint32 dialogID, Sint32 componentID, bool bReadOnly = true) = 0;
        virtual Boolean VCOM_CALLTYPE IsListBrowserReadOnly(Sint32 dialogID, Sint32 componentID) = 0;
        virtual void VCOM_CALLTYPE SetListBrowserItemReadOnly(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex, bool bReadOnly = true) = 0;
        virtual Boolean VCOM_CALLTYPE IsListBrowserItemReadOnly(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex) = 0;
		virtual Boolean VCOM_CALLTYPE NotifyPullDownClicked(Sint32 nDialogID, Sint32 nComponentID) = 0;
		virtual TOSWndPtr VCOM_CALLTYPE OverrideControl(Sint32 dlogID, Sint32 controlID, void* pCallbackOSFunction) = 0;
		virtual void VCOM_CALLTYPE PostMinorNoteAlert(const TXString& msgStr) = 0;
		virtual void VCOM_CALLTYPE PostMinorStopAlert(const TXString& msgStr) = 0;
		virtual void VCOM_CALLTYPE PostNoteAlert(const TXString& msgStr) = 0;
		virtual void VCOM_CALLTYPE PostStopAlert(const TXString& msgStr) = 0;
		virtual Boolean VCOM_CALLTYPE RefreshItem(Sint32 liDialogID, Sint32 liComponentID) = 0;
		virtual Boolean VCOM_CALLTYPE RefreshListBrowser(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveAllImagePopupItems(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void VCOM_CALLTYPE RemoveAllListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex) = 0;
		virtual void VCOM_CALLTYPE RemoveChoice(Sint32 dialogID, Sint32 itemID, short itemIndexToRemove) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveEnhancedPullDownMenuItemRange(Sint32 liDialogID, Sint32 liComponentID, int iStartItemIndexToRemove, int iEndItemIndexToRemove) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveGradientSliderSegment(Sint32 dialogID, Sint32 componentID, short segmentIndex) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveImagePopupItem(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
		virtual void VCOM_CALLTYPE RemoveListBoxTabStop(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID) = 0;
		virtual Sint32 VCOM_CALLTYPE RunLayoutDialog(Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& contextualHelpID, const bool bEnableContextualHelp = true) = 0;
		virtual void VCOM_CALLTYPE SelectChoice(Sint32 dialogID, Sint32 itemID, short nItemIndex, Boolean bSelect = true) = 0;
		virtual void VCOM_CALLTYPE SelectEditText(Sint32 dialogID, Sint32 itemID) = 0;
		virtual Boolean VCOM_CALLTYPE SelectTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID) = 0;
		virtual bool VCOM_CALLTYPE SetBelowItem(Sint32 dialogID, Sint32 srcItemID, Sint32  belowItemID, short indentStdCh = 0, short lineSpacing = 0) = 0;
		virtual void VCOM_CALLTYPE SetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean bSelect) = 0;
		virtual void VCOM_CALLTYPE SetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor) = 0;
		virtual void VCOM_CALLTYPE SetColorButton(Sint32 dialogID, Sint32 itemID, const RGBColor& rgb) = 0;
		virtual void VCOM_CALLTYPE SetColorChoice(Sint32 dialogID, Sint32 itemID, short colorIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentIndeterminate(Sint32 nDialogID, Sint32 nComponentID, Boolean bIndeterminateState) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentSize(Sint32 nDialogID, Sint32 nComponentID, int nWidthPixels, int nHeightPixels) = 0;
		virtual void VCOM_CALLTYPE SetControlData(Sint32 dialogID, Sint32 itemID, const SControlDataBase& data) = 0;
		virtual void VCOM_CALLTYPE SetEdgeBinding(Sint32 dialogID, Sint32 itemID, Boolean boundToLeft, Boolean boundToRight, Boolean boundToTop, Boolean boundToBottom) = 0;
		virtual void VCOM_CALLTYPE SetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32 value) = 0;
		virtual void VCOM_CALLTYPE SetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double value) = 0;
		virtual bool VCOM_CALLTYPE SetFirstGroupItem(Sint32 dialogID, Sint32 groupID, Sint32 firstItemID) = 0;
		virtual bool VCOM_CALLTYPE SetFirstLayoutItem(Sint32 dialogID, Sint32 firstItemID) = 0;
		virtual Boolean VCOM_CALLTYPE SetFocusOnItem(Sint32 liDialogID, Sint32 liComponentID) = 0;
		virtual Boolean VCOM_CALLTYPE SetFocusOnListBrowser(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean VCOM_CALLTYPE SetGradientSliderData(Sint32 dialogID, Sint32 componentID, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color) = 0;
		virtual Boolean VCOM_CALLTYPE SetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short segmentIndex, short markerType) = 0;
		virtual void VCOM_CALLTYPE SetHelpText(Sint32 dialogID, Sint32 itemID, const TXString& helpText) = 0;
		virtual Boolean VCOM_CALLTYPE SetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean bPressed) = 0;
		virtual Boolean VCOM_CALLTYPE SetImageControlHandle(Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage) = 0;
		virtual Boolean VCOM_CALLTYPE SetImageControlPath(Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath) = 0;
		virtual Boolean VCOM_CALLTYPE SetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
		virtual void VCOM_CALLTYPE SetItemText(Sint32 dialogID, Sint32 itemID, const TXString& strNewText) = 0;
		virtual Boolean VCOM_CALLTYPE SetItemToolTipText(Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, int nIndex, int nSubIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetLayoutDialogPosition(Sint32 dialogID, short left, short top) = 0;
		virtual void VCOM_CALLTYPE SetLayoutDialogSize(Sint32 dialogID, short width, short height) = 0;
		virtual Boolean VCOM_CALLTYPE SetLayoutOption(Sint32 dialogID, short option, Sint32 value) = 0;
		virtual void VCOM_CALLTYPE SetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short lineWeight) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short fromColumn, short toColumn, short width) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int iOwnerDrawnType) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int iJustification) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnImage(Sint32 nDialogID, Sint32 nComponentID, int nColumnIndex, int nImageIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex, short controlType) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserDragAndDropColumn(Sint32 dialogID, Sint32 componentID, int iColumnIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32 nUserData) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, short imageIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int justification) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char textStyle) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int redIndex, int greenIndex, int blueIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemUsingColumnDataItem(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short columnDataItemIndex) = 0;
		virtual Boolean VCOM_CALLTYPE SetListBrowserSelection(Sint32 dialogID, Sint32 componentID, short firstItemIndex, short lastItemIndex, Boolean select) = 0;
		virtual void VCOM_CALLTYPE SetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID, int columnIndex, Boolean isAscending) = 0;
		virtual void VCOM_CALLTYPE SetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType style, Sint8 angle, double size, double width, Uint8 thicknessBasis, double thickness) = 0;
		virtual void VCOM_CALLTYPE SetMultilineText(Sint32 dialogID, Sint32 itemID, GSHandle text) = 0;
		virtual void VCOM_CALLTYPE SetPatternData(Sint32 dialogID, Sint32 itemID, short patternIndex, short foreColor, short backColor) = 0;
		virtual void VCOM_CALLTYPE SetProportionalBinding(Sint32 dialogID, Sint32 itemID, Boolean leftProportional, Boolean rightProportional, Boolean topProportional, Boolean bottomProportional) = 0;
		virtual bool VCOM_CALLTYPE SetRightItem(Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, short indentStdCh = 0, short lineSpacing = 0) = 0;
		virtual void VCOM_CALLTYPE SetSelectionRange(Sint32 dialogID, Sint32 controlID, int startPos, int endPos) = 0;
		virtual void VCOM_CALLTYPE SetTextEditable(Sint32 dialogID, Sint32 itemID, Boolean editable) = 0;
		virtual Boolean VCOM_CALLTYPE SetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int iState) = 0;
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemID, SintptrT nItemData) = 0;
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData2(Sint32 nDialogID, Sint32 nComponentID, int nItemID, const TXString & itemData) = 0;
		virtual Boolean VCOM_CALLTYPE ShowEnhancedPullDownMenuGroupIcon(Sint32 liDialogID, Sint32 liComponentID, Boolean bShowGroupIcon) = 0;
		virtual void VCOM_CALLTYPE ShowItem(Sint32 dialogID, Sint32 itemID, Boolean bShow) = 0;
		virtual void VCOM_CALLTYPE UpdateCustomControlScrollArea(Sint32 dialogID, Sint32 component, int width, int height, int leftStart, int topStart, int stepSize, bool liveUpdate, bool alwaysShowHoriz = false, bool alwaysShowVert = false ) = 0;
		virtual void VCOM_CALLTYPE UpdateSymbolDisplayControl           (Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut) = 0;
		virtual bool VCOM_CALLTYPE VerifyLayout(Sint32 dialogID) = 0;
		virtual InternalIndex VCOM_CALLTYPE AddClass(const TXString& className) = 0;
		virtual InternalIndex VCOM_CALLTYPE AddGuidesClass() = 0;
		virtual void VCOM_CALLTYPE ColorIndexToName(const ColorRef& inColorRef, TXString& outColorName) = 0;
		virtual void VCOM_CALLTYPE ColorIndexToRGB(ColorRef colorIndex, RGBColor& rgb) = 0;
		virtual Boolean VCOM_CALLTYPE CopySymbol(const TXString& inFilePath, const TXString& symName) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateGradient(const TXString& name) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateHatch(const TXString& inName, Boolean inUsePageUnits, Boolean inRotateInWalls, Boolean inRotateInSymbols, Boolean inTransparent,  ColorRef inFillColorIndex) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageFromPaint(MCObjectHandle paint, const TXString& imageName) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreatePaintFromImage(MCObjectHandle image) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateWallStyle(const TXString& wallStyleName) = 0;
		virtual void VCOM_CALLTYPE DeleteClass(const TXString& className) = 0;
		virtual void VCOM_CALLTYPE DeselectAll() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetActiveSymbolDef() = 0;
		virtual Boolean VCOM_CALLTYPE GetClassVisibility(InternalIndex index) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetCurrentLayer() = 0;
		virtual TStandardView VCOM_CALLTYPE GetCurrentView() = 0;
		virtual InternalIndex VCOM_CALLTYPE GetDimensionClassID() = 0;
		virtual Boolean VCOM_CALLTYPE GetGradientData(MCObjectHandle gradient, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color) = 0;
		virtual Boolean VCOM_CALLTYPE GetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double& position) = 0;
		virtual void VCOM_CALLTYPE GetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, WorldPt3& color) = 0;
		virtual Boolean VCOM_CALLTYPE GetGradientSpotPosition(MCObjectHandle gradient, short segmentIndex, double& position) = 0;
		virtual void VCOM_CALLTYPE GetGridUnits(WorldCoord& x, WorldCoord& y) = 0;
		virtual Boolean VCOM_CALLTYPE GetHatchLevel(MCObjectHandle inHatchDef, short inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight) = 0;
		virtual void VCOM_CALLTYPE GetLayerScaleN(MCObjectHandle h, double_gs& scale) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedLayer(const TXString& layerName) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetNoneClassID() = 0;
		virtual short VCOM_CALLTYPE GetNumGradientSegments(MCObjectHandle gradient) = 0;
		virtual void VCOM_CALLTYPE GetPageBounds(WorldRect& bounds) = 0;
		virtual Boolean VCOM_CALLTYPE GetPatternBits(short inIndex, Uint8 outPattern[8]) = 0;
		virtual Boolean VCOM_CALLTYPE GetSheetLayerUserOrigin(MCObjectHandle layerHandle, WorldPt& origin) = 0;
		virtual void VCOM_CALLTYPE GetUnits(UnitsType& currentUnits) = 0;
		virtual void VCOM_CALLTYPE GetUserOrigin(WorldPt& origin) = 0;
		virtual Boolean VCOM_CALLTYPE GetUserOriginFP(WorldPt& outOrigin) = 0;
		virtual short VCOM_CALLTYPE InsertGradientSegment(MCObjectHandle gradient, double_param spotPosition, double_param midpointPosition, const WorldPt3& color) = 0;
		virtual void VCOM_CALLTYPE MarkCurrentDocChanged() = 0;
		virtual Sint32 VCOM_CALLTYPE NumSelectedObjects() = 0;
		virtual Boolean VCOM_CALLTYPE RemoveGradientSegment(MCObjectHandle gradient, short segmentIndex) = 0;
		virtual void VCOM_CALLTYPE ResetAllObjectsVisibility() = 0;
		virtual void VCOM_CALLTYPE RGBToColorIndex(const RGBColor& rgb, ColorRef& colorIndex) = 0;
		virtual void VCOM_CALLTYPE SelectAll() = 0;
		virtual void VCOM_CALLTYPE SetActiveSymbolDef(MCObjectHandle aSymDef) = 0;
		virtual void VCOM_CALLTYPE SetClassVisibility(InternalIndex index, Boolean visible) = 0;
		virtual void VCOM_CALLTYPE SetCurrentLayer(MCObjectHandle theLayer) = 0;
		virtual Boolean VCOM_CALLTYPE SetGradientData(MCObjectHandle gradient, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color) = 0;
		virtual Boolean VCOM_CALLTYPE SetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double_param position) = 0;
		virtual Boolean VCOM_CALLTYPE SetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, const WorldPt3& color) = 0;
		virtual Boolean VCOM_CALLTYPE SetGradientSpotPosition(MCObjectHandle gradient, short& segmentIndex, double_param position) = 0;
		virtual Boolean VCOM_CALLTYPE SetHatchLevel(MCObjectHandle inHatchDef, short inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, double_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, short inMilsLineWeight) = 0;
		virtual void VCOM_CALLTYPE SetLayerScaleN(MCObjectHandle theLayer, double_param newScale) = 0;
		virtual void VCOM_CALLTYPE SetMarker(MCObjectHandle obj, MarkerType style, short size, short angle, Boolean start, Boolean end) = 0;
		virtual void VCOM_CALLTYPE SetProjection(MCObjectHandle theLayer, TProjection newProj, Boolean confirmWithUser, Boolean doProgress) = 0;
		virtual Boolean VCOM_CALLTYPE SetRenderMode(MCObjectHandle theLayer, TRenderMode newRenderMode, Boolean immediate, Boolean doProgress) = 0;
		virtual Boolean VCOM_CALLTYPE SetSheetLayerUserOrigin(MCObjectHandle layerHandle, const WorldPt& origin) = 0;
		virtual void VCOM_CALLTYPE SetUserOrigin(const WorldPt& origin) = 0;
		virtual Boolean VCOM_CALLTYPE SetUserOriginFP(const WorldPt& inOrigin) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ShowCreateImageDialog() = 0;
		virtual Boolean VCOM_CALLTYPE ShowGradientEditorDialog(MCObjectHandle& gradient) = 0;
		virtual Boolean VCOM_CALLTYPE ValidClass(InternalIndex classID) = 0;
		virtual TTesselator VCOM_CALLTYPE CreateTessellator(short convertRes3D) = 0;
		virtual void VCOM_CALLTYPE DeleteTessellator(TTesselator pTess) = 0;
		virtual bool VCOM_CALLTYPE TesselateObject(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv) = 0;
		virtual Boolean VCOM_CALLTYPE UpdateThumbnailPreview(InternalIndex inIndex) = 0;
		virtual void VCOM_CALLTYPE CloseXCode(Sint32 extCodeInfoID) = 0;
		virtual GenericFunctionPtr VCOM_CALLTYPE OpenXCode(Sint32 extCodeInfoID, Boolean needsResourceFileOpen) = 0;
		virtual void VCOM_CALLTYPE GSDisposeHandle(GSHandle handle) = 0;
		virtual void VCOM_CALLTYPE GSDisposePtr(void* p) = 0;
		virtual void VCOM_CALLTYPE GSGetHandleSize(GSHandle handle, size_t& size) = 0;
		virtual void VCOM_CALLTYPE GSGetHandleState(GSHandle handle, Boolean& isLocked) = 0;
		virtual void VCOM_CALLTYPE GSHLock(GSHandle handle) = 0;
		virtual void VCOM_CALLTYPE GSHUnlock(GSHandle handle) = 0;
		virtual GSHandle VCOM_CALLTYPE GSNewHandle(size_t size) = 0;
		virtual VoidPtr VCOM_CALLTYPE GSNewPtr(size_t size) = 0;
		virtual void VCOM_CALLTYPE GSReduceHandleSize(GSHandle handle, size_t size) = 0;
		virtual Boolean VCOM_CALLTYPE GSSetHandleSize(GSHandle handle, size_t size) = 0;
		virtual void VCOM_CALLTYPE GSSetHandleState(GSHandle handle, Boolean isLocked) = 0;
		virtual VoidPtr VCOM_CALLTYPE GSSetPtrSize(void* p, size_t size) = 0;
		virtual Sint32 VCOM_CALLTYPE AddResourceToList(Sint32 listID, MCObjectHandle resource) = 0;
		virtual Sint32 VCOM_CALLTYPE BuildResourceList(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems) = 0;
		virtual void VCOM_CALLTYPE DeleteResourceFromList(Sint32 listID, Sint32 index) = 0;
		virtual void VCOM_CALLTYPE DisposeResourceList(Sint32 listID) = 0;
		virtual void VCOM_CALLTYPE GetActualNameFromResourceList(Sint32 listID, Sint32 index, TXString& name) = 0;
		virtual short VCOM_CALLTYPE GetMyMenuCommandIndex() = 0;
		virtual void VCOM_CALLTYPE GetNameFromResourceList(Sint32 listID, Sint32 index, TXString& name) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetResourceFromList(Sint32 listID, Sint32 index) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ImportResourceToCurrentFile(Sint32 listID, Sint32 index) = 0;
		virtual Boolean VCOM_CALLTYPE RegisterMenuForCallback(short menuIndex, OSType whichChange) = 0;
		virtual Sint32 VCOM_CALLTYPE ResourceListSize(Sint32 listID) = 0;
		virtual void VCOM_CALLTYPE UnregisterMenuForCallback(short menuIndex, OSType whichChange) = 0;
		virtual void VCOM_CALLTYPE AddPullDownMenuItem(short group, const TXString& item) = 0;
		virtual void VCOM_CALLTYPE AddPullDownMenuMode(const TXString& label) = 0;
		virtual void VCOM_CALLTYPE AddTxtBtnMode(const TXString& theText) = 0;
		virtual void VCOM_CALLTYPE EnableMode(short modeNum, Boolean enable) = 0;
		virtual short VCOM_CALLTYPE GetModeValue(short modeNum) = 0;
		virtual void VCOM_CALLTYPE SetHelpString(const TXString& helpMessage) = 0;
		virtual void VCOM_CALLTYPE SetModeValue(short modeNum, short theValue) = 0;
		virtual void VCOM_CALLTYPE SetPullDownMenuSelection(short group, short selectedItem) = 0;
		virtual void VCOM_CALLTYPE ClassIDToName(InternalIndex classID, TXString& outClassName) = 0;
		virtual InternalIndex VCOM_CALLTYPE ClassNameToID(const TXString& className) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE InternalIndexToHandle(InternalIndex index) = 0;
		virtual void VCOM_CALLTYPE InternalIndexToNameN(InternalIndex index, TXString& outName) = 0;
		virtual InternalIndex VCOM_CALLTYPE MaxClassID() = 0;
		virtual Boolean VCOM_CALLTYPE NameToInternalIndexN(const TXString& name, InternalIndex& index) = 0;
		virtual Boolean VCOM_CALLTYPE SetPolyVertexLoopDirection(MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec) = 0;
		virtual void VCOM_CALLTYPE AddToConstraintModel(MCObjectHandle obj) = 0;
		virtual Boolean VCOM_CALLTYPE AddViewportAnnotationObject(MCObjectHandle viewportHandle, MCObjectHandle annotationHandle) = 0;
		virtual Boolean VCOM_CALLTYPE AppendParameterWidget(Sint32 ObjectID, Sint32 parameterID, const TXString& text, Sint32 data) = 0;
		virtual Boolean VCOM_CALLTYPE AppendWidget(Sint32 ObjectID, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ConvertTo3DPolygons(MCObjectHandle h, Boolean preserveOriginal = false) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE ConvertToNURBS(MCObjectHandle h, Boolean keepOrig = false) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygon(MCObjectHandle h, Boolean preserveOriginal = false) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygonN(MCObjectHandle h, Boolean preserveOriginal , short conversionResolution) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolyline(MCObjectHandle h, Boolean preserveOriginal = false) = 0;
		virtual Boolean VCOM_CALLTYPE ConvertToUnstyledWall(MCObjectHandle theWall) = 0;
		virtual void VCOM_CALLTYPE CreateConstraintModel(MCObjectHandle obj, Boolean useSelection) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateOffsetNurbsObjectHandle(MCObjectHandle h,   double offset) = 0;
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsCreate( MCObjectHandle inOwnerObj, Sint32 numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc,void* env) = 0;
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsRemove(MCObjectHandle inOwnerObj) = 0;
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtSet(MCObjectHandle inOwnerObj,Sint32 dataIndex, const WorldPt3& pt,Boolean is2DOnly,Boolean isHidden,Sint32 inClientID) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CustomObjectGetSurfaceProxy(MCObjectHandle inPathObject) = 0;
		virtual Boolean VCOM_CALLTYPE CustomObjectReplacePath(MCObjectHandle inPathObject, MCObjectHandle pathPolyline) = 0;
		virtual Boolean VCOM_CALLTYPE DeleteAllComponents(MCObjectHandle object) = 0;
		virtual Boolean VCOM_CALLTYPE DeleteComponent(MCObjectHandle object, short componentIndex) = 0;
		virtual void VCOM_CALLTYPE DeleteConstraint(MCObjectHandle obj, MCObjectHandle constraint) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateObject(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE EnableParameter(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetEnabled) = 0;
		virtual Boolean VCOM_CALLTYPE EvaluateNurbsSurfacePointAndNormal(MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point,  WorldPt3& normal) = 0;
		virtual void VCOM_CALLTYPE ForEachLayer( GS_ForEachObjectProcPtr action, void *actionEnv) = 0;
		virtual void VCOM_CALLTYPE ForEachObject( short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv) = 0;
		virtual void VCOM_CALLTYPE Get2DPt(MCObjectHandle obj, short index, WorldPt& loc) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2) = 0;
		virtual void VCOM_CALLTYPE GetClosestPt(MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj) = 0;
		virtual void VCOM_CALLTYPE GetClosestSide(MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentClass(MCObjectHandle object, short componentIndex, Sint32 &componentClass) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentFill(MCObjectHandle object, short componentIndex, Sint32 &fill) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef &fillForeColor, ColorRef &fillBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentName(MCObjectHandle object, short componentIndex, TXString &componentName) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 &leftPenWeight, Uint8 &rightPenWeight) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean &useFillClassAttributes) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean &useLeftPenClassAttributes, Boolean &useRightPenClassAttributes) = 0;
		virtual Boolean VCOM_CALLTYPE GetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord &width) = 0;
		virtual Boolean VCOM_CALLTYPE GetCustomObjectColor(MCObjectHandle objectHand, Sint32 iTagID, ColorRef& ioColorRef) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectPath(MCObjectHandle objectHand) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectProfileGroup(MCObjectHandle objectHand) = 0;
		virtual Boolean VCOM_CALLTYPE GetDimensionStandardVariable(short dimensionIndex, short fieldSelector, TVariableBlock& value) = 0;
		virtual Boolean VCOM_CALLTYPE GetDistanceAlongNurbsCurve(MCObjectHandle inNurbsCurve, double_param inParameter1, Sint32 inParameter1CurveIndex,  double_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance) = 0;
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginChoice(const TXString& pluginName, const TXString& parameterName, Sint32 choiceIndex, TXString& localizedChoice) = 0;
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginName(const TXString& pluginName, TXString& outLocalizedName) = 0;
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginParameter(const TXString& pluginName, const TXString& parameterName, TXString& localizedParameterName) = 0;
		virtual Boolean VCOM_CALLTYPE GetNumberOfComponents(MCObjectHandle object, short &numComponents) = 0;
		virtual Boolean VCOM_CALLTYPE GetNurbsObjectDistanceFromPoint(MCObjectHandle h, const WorldPt&  point,  double& distance) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjectProperty(MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjectPropertyChar(MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjectVariable(MCObjectHandle theObject, short setSelector, TVariableBlock& value) = 0;
		virtual Boolean VCOM_CALLTYPE GetParameterOnNurbsCurve(MCObjectHandle h, const WorldPt3&  point,  double& parameter, Sint32& index) = 0;
		virtual Boolean VCOM_CALLTYPE GetPointAndParameterOnNurbsCurveAtGivenLength(MCObjectHandle inNurbCurve, double_param inPercentOfLength, WorldPt3& outPointOnCurve,  double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex) = 0;
		virtual Boolean VCOM_CALLTYPE GetRoofEdge(MCObjectHandle object, short index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB) = 0;
		virtual Boolean VCOM_CALLTYPE GetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportCropObject(MCObjectHandle viewportHandle) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroup(MCObjectHandle viewportHandle, short groupType) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroupParent(MCObjectHandle groupHandle) = 0;
		virtual Boolean VCOM_CALLTYPE GetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType) = 0;
		virtual MeshErrorType VCOM_CALLTYPE GroupToMesh(MCObjectHandle theMesh) = 0;
		virtual Boolean VCOM_CALLTYPE HasConstraint(MCObjectHandle obj) = 0;
		virtual Boolean VCOM_CALLTYPE InsertAllParametersAsWidgets(Sint32 inObjectID) = 0;
		virtual Boolean VCOM_CALLTYPE InsertParameterWidget(Sint32 ObjectID, Sint32 position, Sint32 parameterID, const TXString& text, Sint32 data) = 0;
		virtual Boolean VCOM_CALLTYPE InsertWidget(Sint32 ObjectID, Sint32 position, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data) = 0;
		virtual Boolean VCOM_CALLTYPE IsObjectFromReferencedFile(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE IsViewportGroupContainedObject(MCObjectHandle objectHandle,  short groupType) = 0;
		virtual void VCOM_CALLTYPE MakePolyshapeValid(MCObjectHandle thePoly) = 0;
		virtual MeshErrorType VCOM_CALLTYPE MeshToGroup(MCObjectHandle theMesh) = 0;
		virtual void VCOM_CALLTYPE MoveObject(MCObjectHandle h, WorldCoord dx, WorldCoord dy) = 0;
		virtual void VCOM_CALLTYPE MoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz, bool inMoveScreenObjectsWith3D = false) = 0;
		virtual void VCOM_CALLTYPE NotifyLayerChange(StatusData liAdditionalData = 0) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveCustomObjectColor(MCObjectHandle objectHand, Sint32 iTagID) = 0;
		virtual Boolean VCOM_CALLTYPE RemoveRoofEdge(MCObjectHandle object, short index) = 0;
		virtual Boolean VCOM_CALLTYPE ResetObject(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE RotateObjectN(MCObjectHandle& h, const WorldPt& rotCenter, double_param angle) = 0;
		virtual Boolean VCOM_CALLTYPE ScaleObject3D(MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector) = 0;
		virtual void VCOM_CALLTYPE ScaleObjectN(MCObjectHandle h, const WorldPt& scaleCen, double_param scaleX, double_param scaleY) = 0;
		virtual Boolean VCOM_CALLTYPE SetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentClass(MCObjectHandle object, short componentIndex, Sint32 componentClass) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentFill(MCObjectHandle object, short componentIndex, Sint32 fill) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef fillForeColor, ColorRef fillBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentName(MCObjectHandle object, short componentIndex, const TXString &componentName) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 leftPenWeight, Uint8 rightPenWeight) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean useFillClassAttributes) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean useLeftPenClassAttributes, Boolean useRightPenClassAttributes) = 0;
		virtual Boolean VCOM_CALLTYPE SetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord width) = 0;
		virtual void VCOM_CALLTYPE SetConstraintValue(MCObjectHandle constraint, double_param value) = 0;
		virtual Boolean VCOM_CALLTYPE SetCustomDimensionStandardVariable(short dimensionIndex, short fieldSelector, const TVariableBlock& value) = 0;
		virtual Boolean VCOM_CALLTYPE SetCustomObjectColor(MCObjectHandle objectHand, Sint32 iTagID, ColorRef inColorRef) = 0;
		virtual Boolean VCOM_CALLTYPE SetCustomObjectControlPointVisibility(MCObjectHandle objectHand, short controlPtIndex, Boolean setVisible) = 0;
		virtual Boolean VCOM_CALLTYPE SetCustomObjectPath(MCObjectHandle objectHand, MCObjectHandle pathHand) = 0;
		virtual Boolean VCOM_CALLTYPE SetCustomObjectProfileGroup(MCObjectHandle objectHand, MCObjectHandle profileGroupHand) = 0;
		virtual void VCOM_CALLTYPE SetDefinition(MCObjectHandle h, MCObjectHandle newDef) = 0;
		virtual Boolean VCOM_CALLTYPE SetObjectProperty(Sint32 inCodeRefID, Sint32 inPropID, Boolean inValue) = 0;
		virtual Boolean VCOM_CALLTYPE SetObjectPropertyChar(Sint32 inCodeRefID, Sint32 inPropID, unsigned char inValue) = 0;
		virtual Boolean VCOM_CALLTYPE SetObjectVariable(MCObjectHandle theObject, short setSelector, const TVariableBlock& value) = 0;
		virtual void VCOM_CALLTYPE SetParameterVisibility(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetVisible) = 0;
		virtual void VCOM_CALLTYPE SetRoofEdge(MCObjectHandle object, short index, const WorldPt& vertexPt, double_param slope, WorldCoord projection, WorldCoord eaveHeight) = 0;
		virtual Boolean VCOM_CALLTYPE SetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB) = 0;
		virtual Boolean VCOM_CALLTYPE SetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short visibilityType) = 0;
		virtual Boolean VCOM_CALLTYPE SetViewportCropObject(MCObjectHandle viewportHandle, MCObjectHandle cropHandle) = 0;
		virtual Boolean VCOM_CALLTYPE SetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short visibilityType) = 0;
		virtual Boolean VCOM_CALLTYPE TrimToSelectedObjects(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2) = 0;
		virtual Boolean VCOM_CALLTYPE UpdateConstraintModel() = 0;
		virtual void VCOM_CALLTYPE UpdateViewport(MCObjectHandle viewportHandle) = 0;
		virtual Boolean VCOM_CALLTYPE ViewportHasCropObject(MCObjectHandle viewportHandle) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE FirstSelectedObject() = 0;
		virtual void VCOM_CALLTYPE GetSelectionBounds(WorldRect& bounds, BoundsType type = kRefreshBounds) = 0;
		virtual Sint32 VCOM_CALLTYPE GetSelectionBoundsCube(WorldCube &theCube) = 0;
		virtual void VCOM_CALLTYPE MoveSelection(WorldCoord dx, WorldCoord dy) = 0;
		virtual void VCOM_CALLTYPE MoveSelection3D(WorldCoord dx, WorldCoord dy, WorldCoord dz) = 0;
		virtual void VCOM_CALLTYPE RotateSelectionN(const WorldPt& rotCen, double_param rotAngle) = 0;
		virtual void VCOM_CALLTYPE ScaleSelectionN(const WorldPt& scaleCen, double_param scaleX, double_param scaleY) = 0;
		virtual Boolean VCOM_CALLTYPE AddText(MCObjectHandle textBlock, Sint32 beforeChar, Handle newText) = 0;
		virtual Boolean VCOM_CALLTYPE AddTextFromBuffer(MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextBlock(const TXString& textStr, const WorldPt& textOrigin, Boolean fixedSize, WorldCoord width) = 0;
		virtual void VCOM_CALLTYPE DeleteText(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars) = 0;
		virtual Sint32 VCOM_CALLTYPE GetCharNumFromPoint(MCObjectHandle textBlock, const WorldPt& pt) = 0;
		virtual TXString VCOM_CALLTYPE GetTextChars(MCObjectHandle textBlock) = 0;
		virtual void VCOM_CALLTYPE GetTextColor(MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor) = 0;
		virtual void VCOM_CALLTYPE GetTextFontIndex(MCObjectHandle textBlock, Sint32 charNum, short& fontIndex) = 0;
		virtual void VCOM_CALLTYPE GetTextJustification(MCObjectHandle textBlock, short& justification) = 0;
		virtual Sint32 VCOM_CALLTYPE GetTextLength(MCObjectHandle textBlock) = 0;
		virtual void VCOM_CALLTYPE GetTextLineHeight(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height) = 0;
		virtual void VCOM_CALLTYPE GetTextOrientationN(MCObjectHandle h, double_gs& angle, short& flipState) = 0;
		virtual void VCOM_CALLTYPE GetTextSize(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize) = 0;
		virtual void VCOM_CALLTYPE GetTextStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle) = 0;
		virtual void VCOM_CALLTYPE GetTextVerticalAlignment(MCObjectHandle textBlock, short& verticalAlignment) = 0;
		virtual void VCOM_CALLTYPE GetTextVerticalSpacing(MCObjectHandle textBlock, short& spacing, WorldCoord& height) = 0;
		virtual Boolean VCOM_CALLTYPE GetTextWidth(MCObjectHandle textBlock, WorldCoord& width) = 0;
		virtual Boolean VCOM_CALLTYPE GetTextWrap(MCObjectHandle textBlock, Boolean& wrapped) = 0;
		virtual void VCOM_CALLTYPE SetTextColor(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor) = 0;
		virtual void VCOM_CALLTYPE SetTextFontIndex(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, short fontIndex) = 0;
		virtual void VCOM_CALLTYPE SetTextJustification(MCObjectHandle textBlock, short justification) = 0;
		virtual void VCOM_CALLTYPE SetTextOrientationN(MCObjectHandle h, double_param angle, short flipState) = 0;
		virtual void VCOM_CALLTYPE SetTextSize(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, WorldCoord charSize) = 0;
		virtual void VCOM_CALLTYPE SetTextStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char charStyle) = 0;
		virtual void VCOM_CALLTYPE SetTextVerticalAlignment(MCObjectHandle textBlock, short verticalAlignment) = 0;
		virtual void VCOM_CALLTYPE SetTextVerticalSpacing(MCObjectHandle textBlock, short spacing, WorldCoord height) = 0;
		virtual void VCOM_CALLTYPE SetTextWidth(MCObjectHandle textBlock, WorldCoord width) = 0;
		virtual void VCOM_CALLTYPE SetTextWrap(MCObjectHandle textBlock, Boolean wrapped) = 0;
		virtual void VCOM_CALLTYPE SpellCheckTextBuffer(GSHandle charsHandle, Boolean textChanged) = 0;
		virtual void VCOM_CALLTYPE AttachDefaultTextureSpace(MCObjectHandle object, short multiPartID, Sint32 partCategoryID = 0) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateShaderRecord(MCObjectHandle texture, Sint32 family, Sint32 prototype) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateTexture() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmap() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmapFromPaintNode(MCObjectHandle paintNodeObject) = 0;
		virtual void VCOM_CALLTYPE DeleteTextureSpace(MCObjectHandle object, short multiPartID) = 0;
		virtual Boolean VCOM_CALLTYPE EditShaderRecord(MCObjectHandle shaderRecord) = 0;
		virtual Boolean VCOM_CALLTYPE EditTexture(MCObjectHandle texture) = 0;
		virtual Boolean VCOM_CALLTYPE EditTextureSpace(MCObjectHandle texturedObject, short multiPartID) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetClGenTexture(InternalIndex index) = 0;
		virtual void VCOM_CALLTYPE GetClRoofTextures(InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer) = 0;
		virtual Boolean VCOM_CALLTYPE GetClUseTexture(InternalIndex index) = 0;
		virtual void VCOM_CALLTYPE GetClWallTextures(InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetShaderRecord(MCObjectHandle parentNode, Sint32 family) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, short multiPartID, Boolean resolveByClass) = 0;
		virtual void VCOM_CALLTYPE GetTextures(MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetTextureSpace(MCObjectHandle object, short multiPartID) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetVPClassGenTexture(MCObjectHandle viewport, InternalIndex classIndex) = 0;
		virtual void VCOM_CALLTYPE GetVPClassRoofTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer) = 0;
		virtual void VCOM_CALLTYPE GetVPClassWallTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center) = 0;
		virtual void VCOM_CALLTYPE SetClGenTexture(InternalIndex index, InternalIndex texture) = 0;
		virtual void VCOM_CALLTYPE SetClRoofTextures(InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer) = 0;
		virtual void VCOM_CALLTYPE SetClUseTexture(InternalIndex index, Boolean use) = 0;
		virtual void VCOM_CALLTYPE SetClWallTextures(InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center) = 0;
		virtual void VCOM_CALLTYPE SetDefaultTextureSpace(MCObjectHandle object, MCObjectHandle space, short multiPartID) = 0;
		virtual void VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, short multiPartID) = 0;

		virtual MCObjectHandleID VCOM_CALLTYPE AddToolPersistentDraw(GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv) = 0;
		virtual MCObjectHandleID VCOM_CALLTYPE AddToolSnapGeometry(MCObjectHandle inSnapGeometry) = 0;
		virtual void VCOM_CALLTYPE BoxToolDraw() = 0;
		virtual Boolean VCOM_CALLTYPE ClearAllToolPts() = 0;
		virtual void VCOM_CALLTYPE ClearDataDisplayBar() = 0;
		virtual Sint32 VCOM_CALLTYPE ClickDragToolStatus() = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarCreate(short inNumFields, CustomBarRefID& outCustomBarRefID) = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarGetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, CustomBarFieldInfo& inFieldInfo) = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarInstall(CustomBarRefID inCustomBarID) = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarRelease(CustomBarRefID inCustomBarRefID) = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldAngle(CustomBarRefID inCustomBarID, short inFieldIndex, const double& inDegrees) = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, const CustomBarFieldInfo& inFieldInfo) = 0;
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldWorldCoord(CustomBarRefID inCustomBarID, short inFieldIndex, const WorldCoord& inCoordVal) = 0;
		virtual void VCOM_CALLTYPE Default2DToolDraw() = 0;
		virtual void VCOM_CALLTYPE Default3DToolDraw() = 0;
		virtual void VCOM_CALLTYPE DrawCoordArcN(const WorldRect& theBox, double_param startAngle, double_param sweepAngle) = 0;
		virtual void VCOM_CALLTYPE DrawCoordEllipse(WorldRect& theBox) = 0;
		virtual void VCOM_CALLTYPE DrawCoordLine(const WorldPt& p1, const WorldPt& p2) = 0;
		virtual void VCOM_CALLTYPE DrawCoordLine3D(const WorldPt3& p1, const WorldPt3& p2) = 0;
		virtual void VCOM_CALLTYPE DrawCoordRect(const WorldRect& theBox) = 0;
		virtual void VCOM_CALLTYPE DrawDataDisplayBar(Boolean drawFramesFirst = false) = 0;
		virtual void VCOM_CALLTYPE DrawNurbsObject(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE DrawObject(MCObjectHandle h, Boolean doSelect) = 0;
		virtual void VCOM_CALLTYPE GetCoords(WorldPt& p, ViewPt& m) = 0;
		virtual Sint32 VCOM_CALLTYPE GetNumToolPts() = 0;
		virtual const ICoreToolAccess* VCOM_CALLTYPE GetToolCoreInterface() = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPt2D(Sint32 inIndex, WorldPt& outToolPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPt3D(Sint32 inIndex, WorldPt3& outToolPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent2D(WorldPt& outToolPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent3D(WorldPt3& outToolPt) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentViewPt(ViewPt& outToolPt) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentWorkingPlane(WorldPt3& outToolPt) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPtViewPoint(Sint32 inIndex, ViewPt& outToolPoint) = 0;
		virtual Boolean VCOM_CALLTYPE GetToolPtWorkingPlane(Sint32 inIndex, WorldPt3& outToolPoint) = 0;
		virtual void VCOM_CALLTYPE InstallConstraintAlong3DLine(const Ray& inConstraintDescription) = 0;
		virtual void VCOM_CALLTYPE Interactive2DDraw( short options, short shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env) = 0;
		virtual Sint32 VCOM_CALLTYPE OnePointToolStatus() = 0;
		virtual Sint32 VCOM_CALLTYPE PolyToolStatus() = 0;
		virtual Boolean VCOM_CALLTYPE PopLastToolPt() = 0;
		virtual void VCOM_CALLTYPE RemoveHotSpot(HotSpotRefID inHotSpotID) = 0;
		virtual void VCOM_CALLTYPE RemoveToolPersistentDraw(MCObjectHandleID persistentDrawRefID) = 0;
		virtual void VCOM_CALLTYPE RemoveToolSnapGeometry(MCObjectHandleID inSnapGeometryID) = 0;
//		virtual Boolean VCOM_CALLTYPE RunTemporary2DTool( Sint32& ioUserData, ToolDefProcPtr inToolProc) = 0;
//		virtual Boolean VCOM_CALLTYPE RunTemporary3DTool( Sint32& ioUserData, ToolDefProcPtr inToolProc) = 0;
		virtual void VCOM_CALLTYPE SetCursorMode() = 0;
		virtual void VCOM_CALLTYPE SetDataDisplayBarField(short fieldNum, BarNumberType barType, const TXString& inBarLabel) = 0;
		virtual void VCOM_CALLTYPE SetDimUserBarValue(short fieldNum, WorldCoord dimVal) = 0;
		virtual void VCOM_CALLTYPE SetFloatUserBarValueN(short fieldNum, double_param floatVal, short numPlaces) = 0;
		virtual void VCOM_CALLTYPE SetTextUserBarValue(short fieldNum, const TXString& textVal) = 0;
		virtual Boolean VCOM_CALLTYPE SetToolProperty(Sint32 inCodeRefID, Sint32 inToolPropID, Boolean inValue) = 0;
		virtual Boolean VCOM_CALLTYPE SetToolPropertyChar(Sint32 inCodeRefID, Sint32 inToolPropID, char inValue) = 0;
		virtual Sint32 VCOM_CALLTYPE ThreePointToolStatus() = 0;
		virtual HotSpotRefID VCOM_CALLTYPE TrackHotSpot(Boolean& outIs3d, WorldPt3& outLocation) = 0;
		virtual void VCOM_CALLTYPE TrackTool(MCObjectHandle& overObject, short& overPart, SintptrT& code) = 0;
		virtual Sint32 VCOM_CALLTYPE TwoPointToolStatus() = 0;
		virtual void VCOM_CALLTYPE AddObjectToContainer(MCObjectHandle h, MCObjectHandle container) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE AuxOwner(MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE DeleteObject(MCObjectHandle h, Boolean useUndo = true) = 0;
		virtual Boolean VCOM_CALLTYPE FindHandleDeep(MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE FirstMemberObj(MCObjectHandle h) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultContainer() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetDrawingHeader() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetHatchListHeader() = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetSymbolLibraryHeader() = 0;
		virtual void VCOM_CALLTYPE InsertObjectAfter(MCObjectHandle h, MCObjectHandle afterObject) = 0;
		virtual void VCOM_CALLTYPE InsertObjectBefore(MCObjectHandle h, MCObjectHandle beforeObject) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE LastMemberObj(MCObjectHandle h) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE NextObject(MCObjectHandle h) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ParentObject(MCObjectHandle h) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE PrevObject(MCObjectHandle h) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE SearchForAncestorType(Sint16 objectType, MCObjectHandle h) = 0;
		virtual void VCOM_CALLTYPE SetPageBounds(const WorldRect& bounds) = 0;
		virtual Boolean VCOM_CALLTYPE AcquireExportPDFSettingsAndLocation(Boolean inbSeparateDocuments) = 0;
		virtual void VCOM_CALLTYPE ClosePDFDocument() = 0;
		virtual short VCOM_CALLTYPE ExportPDFPages(const TXString& inSavedViewNameStr) = 0;
		virtual Boolean VCOM_CALLTYPE OpenPDFDocument(const TXString& inFileNameStr) = 0;
		virtual Boolean VCOM_CALLTYPE AddAfterMoveObject(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE AddAfterSwapObject(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE AddBeforeMoveObject(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE AddBeforeSwapObject(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE AddBothSwapObject(MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject2D(MCObjectHandle h, WorldCoord dx, WorldCoord dy) = 0;
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz) = 0;
		virtual Boolean VCOM_CALLTYPE EndUndoEvent() = 0;
		virtual void VCOM_CALLTYPE NameUndoEvent(const TXString& name) = 0;
		virtual Boolean VCOM_CALLTYPE NonUndoableActionOK() = 0;
		virtual void VCOM_CALLTYPE SetUndoMethod(short undoType) = 0;
		virtual void VCOM_CALLTYPE SupportUndoAndRemove() = 0;
		virtual void VCOM_CALLTYPE UndoAndRemove() = 0;
		virtual void VCOM_CALLTYPE AngleToStringN(double_param angle, TXString& s) = 0;
		virtual void VCOM_CALLTYPE AssociateLinearDimension(MCObjectHandle h, Boolean selectedObjectsMode) = 0;
		virtual Boolean VCOM_CALLTYPE CallPluginLibrary(const TXString& routineName, PluginLibraryArgTable* argumentTable, Sint32 status) = 0;
		virtual void VCOM_CALLTYPE ClipSurface(MCObjectHandle h1, MCObjectHandle h2) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CombineIntoSurface(const WorldPt& insidePt) = 0;
		virtual void VCOM_CALLTYPE CoordToDimString(WorldCoord c, TXString& s) = 0;
		virtual Sint16 VCOM_CALLTYPE CStringCompare(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags) = 0;
		virtual Boolean VCOM_CALLTYPE CStringEqual(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags) = 0;
		virtual void VCOM_CALLTYPE DisableModules(Sint32 modules) = 0;
		virtual void VCOM_CALLTYPE DisplayContextHelpOfCurrentPlugin() = 0;
		virtual Boolean VCOM_CALLTYPE DisplayContextualHelp(const TXString& helpIdentifier) = 0;
		virtual void VCOM_CALLTYPE DisplayOrganizationDialog(short tabToSelect) = 0;
		virtual short VCOM_CALLTYPE DoMenuName(const TXString& name, short chunkIndex) = 0;
		virtual Sint32 VCOM_CALLTYPE DoProgramAction(short actionSelector, void* actionEnv) = 0;
		virtual void VCOM_CALLTYPE DoubleToString(TNumStyleClass inNumStyle,  Byte inAccuracy, Byte inFormat, double_param inDouble, TXString& outString) = 0;
		virtual void VCOM_CALLTYPE DrawScreen(const ViewRect& clipRect = ViewRect(), Boolean isLastFrame = true) = 0;
		virtual void VCOM_CALLTYPE EllipseEllipseIntersect(const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects) = 0;
		virtual Sint32 VCOM_CALLTYPE ExternalNameToID(const TXString& fnName) = 0;
		virtual short VCOM_CALLTYPE FontIndexFromName(const TXString& fontName) = 0;
		virtual void VCOM_CALLTYPE FontNameFromIndex(short fontIndex, TXString& fontName, Boolean useMappingTable) = 0;
		virtual void VCOM_CALLTYPE GetActiveSerialNumber(TXString& outSerialNumber) = 0;
		virtual Boolean VCOM_CALLTYPE GetCallBackInval() = 0;
		virtual short VCOM_CALLTYPE GetCurrentMode() = 0;
		virtual Sint32 VCOM_CALLTYPE GetDataBarCursorVisState() = 0;
		virtual Sint32 VCOM_CALLTYPE GetEnabledModules() = 0;
		virtual void VCOM_CALLTYPE GetHostInfo(short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& outProductName, TXString& outProductVersion) = 0;
		virtual void VCOM_CALLTYPE GetModifierFlags(Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag) = 0;
		virtual void VCOM_CALLTYPE GetProduct(short& product, Sint32& modules) = 0;
		virtual Boolean VCOM_CALLTYPE GetSavedSetting(const TXString& category, const TXString& setting, TXString& value) = 0;
		virtual void VCOM_CALLTYPE HandlePendingUpdatesAndActivates() = 0;
		virtual void VCOM_CALLTYPE HilitePalettesAndTopDocument(Boolean doHilite) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE IntersectObjects(MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs) = 0;
		virtual Boolean VCOM_CALLTYPE Kludge(short selector, void* in, void* out) = 0;
		virtual void VCOM_CALLTYPE LineEllipseIntersect(const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects) = 0;
		virtual void VCOM_CALLTYPE LineLineIntersect(const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ObjectNearCoordPt(const WorldPt& p) = 0;
		virtual Boolean VCOM_CALLTYPE PlaySoundResource(Handle soundResource, Boolean async, Boolean forcePlay) = 0;
		virtual Boolean VCOM_CALLTYPE PointInsidePoly(const WorldPt& checkPt, MCObjectHandle h) = 0;
		virtual Boolean VCOM_CALLTYPE PointOnPolyEdge(const WorldPt& checkPt, MCObjectHandle h, WorldCoord checkRadius) = 0;
		virtual Sint32 VCOM_CALLTYPE RegisterExternal(const TXString& fileName, short codeResID, OSType codeResType) = 0;
		virtual Boolean VCOM_CALLTYPE RegisterNotificationProcedure(StatusProcPtr proc, OSType whichChange) = 0;
		virtual void VCOM_CALLTYPE SetCallBackInval(Boolean turnInvalOn) = 0;
		virtual void VCOM_CALLTYPE SetPersistentHighlight(MCObjectHandle theObject, Boolean highlightState) = 0;
		virtual void VCOM_CALLTYPE SetSavedSetting(const TXString& category, const TXString& setting, const TXString& value) = 0;
		virtual Boolean VCOM_CALLTYPE StringToAngleN(const TXString& s, double_gs& angle) = 0;
		virtual Boolean VCOM_CALLTYPE StringToDouble(TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble) = 0;
		virtual Boolean VCOM_CALLTYPE SymbolContainsLight(MCObjectHandle symbol) = 0;
		virtual void VCOM_CALLTYPE ToggleObjectHighlight(MCObjectHandle theObject) = 0;
		virtual void VCOM_CALLTYPE UnregisterNotificationProcedure(StatusProcPtr proc, OSType whichChange) = 0;
		virtual Boolean VCOM_CALLTYPE VerifyPluginLibrary(const TXString& routineName) = 0;
		virtual void VCOM_CALLTYPE GetPerspectiveInfo(MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect) = 0;
		virtual TProjection VCOM_CALLTYPE GetProjection(MCObjectHandle theLayer) = 0;
		virtual TRenderMode VCOM_CALLTYPE GetRenderMode(MCObjectHandle theLayer) = 0;
		virtual short VCOM_CALLTYPE GetScreenDPI() = 0;
		virtual void VCOM_CALLTYPE GetViewCenter(WorldPt& center) = 0;
		virtual void VCOM_CALLTYPE GetViewMatrix(MCObjectHandle theLayer, TransformMatrix& theMat) = 0;
		virtual void VCOM_CALLTYPE GetWorkingPlane(Axis &theAxis) = 0;
		virtual void VCOM_CALLTYPE NewCurrentViewMatrix(const TransformMatrix& theMat, Boolean interactive) = 0;
		virtual void VCOM_CALLTYPE NewWorkingPlane(const Axis &theAxis) = 0;
		virtual void VCOM_CALLTYPE PreviewDrawFrame(Handle thisPreview, Boolean selectedOnly = false) = 0;
		virtual void VCOM_CALLTYPE PreviewFinish(Handle& thisPreview) = 0;
		virtual Handle VCOM_CALLTYPE PreviewSetup(Boolean doDynamicSpeedups = true, double_param targetFPS = 0.0, Boolean drawGroundPlane = true, Boolean drawPage = true, Boolean drawCropRect = true) = 0;
		virtual void VCOM_CALLTYPE RedrawRect(const WorldRect& redrawR) = 0;
		virtual void VCOM_CALLTYPE SetViewCenter(const WorldPt& center) = 0;
		virtual void VCOM_CALLTYPE SetViewMatrix(MCObjectHandle theLayer, const TransformMatrix& theMatrix) = 0;
		virtual void VCOM_CALLTYPE SetWorkingPlaneAxis(const Vector &si, const Vector &sj, const Vector &sk) = 0;
		virtual void VCOM_CALLTYPE SetWorkingPlaneVertex(const WorldPt3 &v) = 0;
		virtual void VCOM_CALLTYPE SetZoomFactorN(double_param zoomFac) = 0;
		virtual void VCOM_CALLTYPE ViewRotWorldZN(double_param angle, Boolean interactive) = 0;
		virtual Boolean VCOM_CALLTYPE WorldRect2ViewRect(const WorldRect& wRect, ViewRect& vRect) = 0;
		virtual short VCOM_CALLTYPE AddBreak(MCObjectHandle theWall, WorldCoord off, short breakType, void* breakData) = 0;
		virtual void VCOM_CALLTYPE DeleteBreak(MCObjectHandle theWall, short index) = 0;
		virtual void VCOM_CALLTYPE ForEachBreak( MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv) = 0;
		virtual void VCOM_CALLTYPE GetPolyBreakGeometry(MCObjectHandle theWall, short breakIndex, MCObjectHandle& polyline) = 0;
		virtual void VCOM_CALLTYPE GetWallCaps(MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round) = 0;
		virtual void VCOM_CALLTYPE GetWallCapsOffsets(MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset) = 0;
		virtual void VCOM_CALLTYPE GetWallCornerHeights(MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom) = 0;
		virtual Boolean VCOM_CALLTYPE JoinWalls(MCObjectHandle firstWall, MCObjectHandle secondWall,  const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, Boolean capped, Boolean showAlerts) = 0;
		virtual void VCOM_CALLTYPE MoveWallByOffset(MCObjectHandle theWall, WorldCoord& offset) = 0;
		virtual void VCOM_CALLTYPE ReverseWallSides(MCObjectHandle theWall) = 0;
		virtual void VCOM_CALLTYPE SetAsPolyBreak(MCObjectHandle& thePolyline, MCObjectHandle theWall, short breakIndex) = 0;
		virtual void VCOM_CALLTYPE SetBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData) = 0;
		virtual Boolean VCOM_CALLTYPE SetWallCaps(MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round) = 0;
		virtual Boolean VCOM_CALLTYPE SetWallCapsOffsets(MCObjectHandle theWall, WorldCoord leftCapLeftOffset, WorldCoord leftCapRightOffset, WorldCoord rightCapLeftOffset, WorldCoord rightCapRightOffset) = 0;
		virtual Boolean VCOM_CALLTYPE SetWallCornerHeights(MCObjectHandle theWall, WorldCoord startHeightTop, WorldCoord startHeightBottom, WorldCoord endHeightTop, WorldCoord endHeightBottom) = 0;
		virtual Boolean VCOM_CALLTYPE SetWallStyle(MCObjectHandle theWall, InternalIndex wallStyle, WorldCoord selectedOffset, WorldCoord replacingOffset) = 0;
		virtual Boolean VCOM_CALLTYPE SetWallWidth(MCObjectHandle theWall, WorldCoord newWidth) = 0;
		virtual void VCOM_CALLTYPE WrapGetWallWidth(MCObjectHandle theWall, double_gs& outCoordLen) = 0;
		virtual Boolean VCOM_CALLTYPE GetScreenSize(ViewRect& screenRect) = 0;
		virtual void VCOM_CALLTYPE AutoFitWorksheetRowHeights(MCObjectHandle worksheet, short fromRow, short toRow) = 0;
		virtual void VCOM_CALLTYPE ClearWorksheetCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheet(const TXString& name, short rows, short columns) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheetImage(MCObjectHandle worksheet, const WorldPt& topLeftCorner) = 0;
		virtual void VCOM_CALLTYPE DeleteWorksheetColumns(MCObjectHandle worksheet, short startColumn, short numColumns) = 0;
		virtual void VCOM_CALLTYPE DeleteWorksheetRows(MCObjectHandle worksheet, short startRow, short numRows) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetTopVisibleWorksheet() = 0;
		virtual void VCOM_CALLTYPE GetWkSheetSubrowCellActualString(MCObjectHandle worksheet, const ViewPt& cell, Sint16 subrow, TXString& cellString) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& cell, TXString& formula) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& cell, short& style, short& accuracy, TXString& leaderString, TXString& trailerString) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell, TXString& cellString) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& cell, short& angle) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellValue(MCObjectHandle worksheet, const ViewPt& cell, double& cellValue) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetColumnWidth(MCObjectHandle worksheet, short column, short& width) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetFromImage(MCObjectHandle worksheetImage) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetImage(MCObjectHandle worksheet) = 0;
		virtual Boolean VCOM_CALLTYPE GetWorksheetMergedCellRange(MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetPlacement(MCObjectHandle worksheet, ViewRect& windowPosition) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetRowColumnCount(MCObjectHandle worksheet, short& numRows, short& numColumns) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetRowHeight(MCObjectHandle worksheet, short row, short& height) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetRowHLockState(MCObjectHandle worksheet, short row, Boolean& lockState) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetSelection(MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow, TXString& cellString) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellValue(MCObjectHandle worksheet, const ViewPt& cell, short subrow, double& cellValue) = 0;
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCount(MCObjectHandle worksheet, short databaseRow, short& numSubrows) = 0;
		virtual void VCOM_CALLTYPE InsertWorksheetColumns(MCObjectHandle worksheet, short beforeColumn, short numColumns) = 0;
		virtual void VCOM_CALLTYPE InsertWorksheetRows(MCObjectHandle worksheet, short beforeRow, short numRows) = 0;
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetCell(MCObjectHandle worksheet, const ViewPt& cell) = 0;
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetRange(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) = 0;
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetSubrowCell(MCObjectHandle worksheet, const ViewPt& cell, short subrow) = 0;
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellNumber(MCObjectHandle worksheet, const ViewPt& cell) = 0;
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell) = 0;
		virtual Boolean VCOM_CALLTYPE IsWorksheetDatabaseRow(MCObjectHandle worksheet, short databaseRow) = 0;
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellNumber(MCObjectHandle worksheet, const ViewPt& cell, short subrow) = 0;
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow) = 0;
		virtual Boolean VCOM_CALLTYPE IsWorksheetVisible(MCObjectHandle worksheet) = 0;
		virtual void VCOM_CALLTYPE RecalculateWorksheet(MCObjectHandle worksheet) = 0;
		virtual void VCOM_CALLTYPE SetTopVisibleWorksheet(MCObjectHandle worksheet) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short cellAlignment) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellBorders(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline, Boolean insideHorz, Boolean insideVert) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, ColorRef bgcolor, ColorRef fgcolor, short fillpattern) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, short accuracy, const TXString& leaderString, const TXString& trailerString) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short fontIndex, short size, short style) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short angle) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short vAlignment) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean wrapTextFlag) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short sort1, short sort2, short sort3, short sum1, short sum2, short sum3) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetColumnWidth(MCObjectHandle worksheet, short fromColumn, short toColumn, short width) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetCurrentCell(MCObjectHandle worksheet, const ViewPt& currentCell) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetPlacement(MCObjectHandle worksheet, const ViewRect& windowPosition) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetRowsHeight(MCObjectHandle worksheet, short fromRow, short toRow, short height, Boolean updatePalette, Boolean lockHeight) = 0;
		virtual void VCOM_CALLTYPE SetWorksheetSelection(MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, short topRangeSubrow, const ViewPt& bottomRightRangeCell, short bottomRangeSubrow) = 0;
		virtual void VCOM_CALLTYPE ShowWorksheet(MCObjectHandle worksheet, Boolean show) = 0;
		virtual void VCOM_CALLTYPE ShowWorksheetDialog(short dialogType) = 0;
		virtual Boolean VCOM_CALLTYPE WorksheetMergeCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) = 0;
		virtual Boolean VCOM_CALLTYPE WorksheetSplitCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) = 0;
		virtual void VCOM_CALLTYPE GetCurrentWorkspaceFile(TXString& outFileName) = 0;
		virtual void VCOM_CALLTYPE SetWorkspaceFileToReload(const TXString& inFileName) = 0;
		virtual Boolean VCOM_CALLTYPE WSAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName) = 0;
		virtual Boolean VCOM_CALLTYPE WSAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, char inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier) = 0;
		virtual Boolean VCOM_CALLTYPE WSAddTool(Sint32 inWorkspaceReference, const TXString& inToolIdentifier, char inShortcutKey, Uint32 inKeyModifiers) = 0;
		virtual Boolean VCOM_CALLTYPE WSAddToolPalette(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier) = 0;
		virtual Boolean VCOM_CALLTYPE WSAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize) = 0;
		virtual Boolean VCOM_CALLTYPE WSGetVersion(Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion) = 0;
		virtual Boolean VCOM_CALLTYPE WSMenuAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName) = 0;
		virtual Boolean VCOM_CALLTYPE WSMenuBarAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier) = 0;
		virtual Boolean VCOM_CALLTYPE WSOpen(const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference) = 0;
		virtual Boolean VCOM_CALLTYPE WSPaletteGetHomeCorner(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner) = 0;
		virtual Boolean VCOM_CALLTYPE WSPaletteSetHomeCorner(Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, short inWindowHomeCorner) = 0;
		virtual Boolean VCOM_CALLTYPE WSSetVersion(Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion) = 0;
		virtual Boolean VCOM_CALLTYPE WSToolPaletteAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier) = 0;
		virtual Boolean VCOM_CALLTYPE WSToolSetAddTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize) = 0;
		virtual Boolean VCOM_CALLTYPE WSToolSetAddToolChildToTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier) = 0;

	// pre VW2009 - OS dependent
	public:
//if _WINDOWS
//		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iPatternIndex) = 0;
//endif
//if !_WIN_EXTERNAL_ && !_GSWINSDK_
//		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPattern(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* &pPattern) = 0;
//endif
//if _WINDOWS
//		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iPatternIndex) = 0;
//endif
//if !_WIN_EXTERNAL_ && !_GSWINSDK_
//		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPattern(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* pPattern) = 0;
//#endif

		//  Image Manipulation
//if _WINDOWS
//		virtual HBITMAP VCOM_CALLTYPE CreateDIBFromPaintNode(MCObjectHandle h) = 0;
//endif
//if _WINDOWS
//		virtual HBITMAP VCOM_CALLTYPE CreateDIBFromPreview(InternalIndex &inIndex, short pixelWidth, short pixelHeight) = 0;
//endif
//if _WINDOWS
//		virtual MCObjectHandle VCOM_CALLTYPE CreatePaintNodeFromDIB(HBITMAP hBitmap) = 0;
//endif
//if _WINDOWS
//		virtual void VCOM_CALLTYPE DisposeDIB(HBITMAP hBitmap) = 0;
//endif
//if !_WIN_EXTERNAL_ && !_GSWINSDK_
//		virtual void VCOM_CALLTYPE DoUpdateOrActivate(EventRecord& theEvent) = 0;
//endif
//if _WINDOWS
//		virtual void VCOM_CALLTYPE EnterMoveableWindow(HWND hDialog) = 0;
//		virtual void VCOM_CALLTYPE ExitMoveableWindow(HWND hDialog) = 0;
//endif
//if !_WIN_EXTERNAL_ && !_GSWINSDK_
//		virtual void VCOM_CALLTYPE FPDisposeDialog(DialogPtr theDialog) = 0;
//		virtual void VCOM_CALLTYPE FPShowWindow(WindowPtr theWindow) = 0;
//		virtual HWND VCOM_CALLTYPE GetMainHWND() = 0;
//endif

	// VW2009
	public:
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFileInStandardFolder(GS_ForEachFilePathProcPtr processFile, EFolderSpecifier folderSpec, void* env) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInStandardFolder(GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInFolder(GS_ForEachFilePathNProcPtr processFile, IFolderIdentifier* pStartFolderID, bool doRecursive, void* pEnv) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInPluginFolder(GS_ForEachFilePathNProcPtr processFile, void* pEnv) = 0;
		virtual bool			VCOM_CALLTYPE GetActiveDocument(IFileIdentifier** ppOutFileID, bool& outSaved) = 0;
		virtual bool			VCOM_CALLTYPE OpenDocumentPath(IFileIdentifier* pFileID, bool bShowErrorMessages) = 0;
		virtual GSError			VCOM_CALLTYPE SaveActiveDocumentPath(IFileIdentifier* pFileID) = 0;
		virtual bool			VCOM_CALLTYPE EncryptVSPluginFile(IFileIdentifier* pPluginFileID, bool doObfuscation = true) = 0;
		virtual bool			VCOM_CALLTYPE ReadVSExternalFile(IFileIdentifier* pFileID, TMPExternalDataForWorkspace& outData) = 0;
		virtual short			VCOM_CALLTYPE ImportDXF(IFileIdentifier* pFileID) = 0;
		virtual bool			VCOM_CALLTYPE WriteMaterialImageFile(IFileIdentifier* pFileID, MCObjectHandle hMaterial, Sint32 type, Sint32 shaderFamily) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE ReadMaterialImageFile(IFileIdentifier* pFileID) = 0;

		virtual void			VCOM_CALLTYPE ClearComponentInstances(MCObjectHandle hContainer, TComponentTypeID componentTypeID = (TComponentTypeID)-1) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE FindFirstComponentInstance(MCObjectHandle hContainer, TComponentTypeID componentTypeID) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE FindNextComponentInstance(TComponentTypeID componentTypeID, MCObjectHandle hComponent) = 0;
		virtual bool			VCOM_CALLTYPE AssignAsComponentInstance(MCObjectHandle hParentContainer, TComponentTypeID componentTypeID, MCObjectHandle hComponent) = 0;
		virtual bool			VCOM_CALLTYPE EnableComponentInstance(MCObjectHandle hComponent, bool bEnable) = 0;
		virtual bool			VCOM_CALLTYPE IsEnabledComponentInstance(MCObjectHandle hComponent) = 0;
		virtual bool			VCOM_CALLTYPE GetComponentInstanceTypeID(MCObjectHandle hComponent, TComponentTypeID& outComponentTypeID) = 0;
		virtual bool			VCOM_CALLTYPE SetComponentInstanceName(MCObjectHandle hComponent, const TXString& localizedName) = 0;
		virtual bool			VCOM_CALLTYPE GetComponentInstanceName(MCObjectHandle hComponent, TXString& outLocalizedName) = 0;
		virtual bool			VCOM_CALLTYPE EmptyToolHighlightingList() = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingObject(MCObjectHandle hHighlightObject) = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingSegment( const WorldPt& startPt,  const WorldPt& endPt) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE AddToolHighlightingPolyCreate() = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPoly(MCObjectHandle polyID, bool bClosed) = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPolyAddVertex(MCObjectHandle polyID, const WorldPt& pt, VertexType type = vtCorner, WorldCoord arcRadius = 0) = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingSegment3D( const WorldPt3& startPt,  const WorldPt3& endPt) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE AddToolHighlightingPoly3DCreate() = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPoly3D(MCObjectHandle polyID, bool bClosed) = 0;
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPoly3DAddVertex(MCObjectHandle polyID, const WorldPt3& pt) = 0;
		virtual bool			VCOM_CALLTYPE OpenURL(const TXString& url) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertNurbsToPolylineArcs(MCObjectHandle hNurbs, double precision, bool insert = false) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE CreateOffsetObjectHandle(MCObjectHandle h, double offset, bool smoothConers = false) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE UnfoldSurface(MCObjectHandle surfaceToUnfold, short conversionRes) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE CreateWallHoleGroup(MCObjectHandle h) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroup(MCObjectHandle h) = 0;
		virtual void			VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK partID) = 0;
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID) = 0;
		virtual void			VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID, const TextureMappingInfoSDK& mappingInfo) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE PerformMultipleUnion(Sint32 numberOf2dObjsToAdd, MCObjectHandle h, bool insert) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetSubrowHeight(MCObjectHandle worksheet, short databaserow, short subrow, short& height) = 0; 
		virtual bool			VCOM_CALLTYPE SetCustomObjectWallHoleGroup(MCObjectHandle objectHand, MCObjectHandle hGeomGroup) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetCustomObjectSelectionGroup(MCObjectHandle objectHand) = 0;
		virtual bool			VCOM_CALLTYPE SetCustomObjectSelectionGroup(MCObjectHandle objectHand, MCObjectHandle hSelGroup) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFootPrint(MCObjectHandle hWall) = 0;
        virtual bool            VCOM_CALLTYPE ExportResource(MCObjectHandle resource, IFileIdentifier* pFileID = nil, bool suppressDialogs = false) = 0;
		virtual Sint32			VCOM_CALLTYPE CallDefaultTool(ToolMessage* message, std::shared_ptr<void>& messageContext) = 0;
		virtual void			VCOM_CALLTYPE EnableDrawingWorksheetPalette(bool enable, MCObjectHandle worksheet = nil) = 0;
		virtual bool			VCOM_CALLTYPE GetWorksheetAutoRecalcState(MCObjectHandle worksheet) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetAutoRecalcState(MCObjectHandle worksheet, bool state) = 0;

	// VW2010
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWorkingPlane(const Axis &theAxis, const TXString& name) = 0;
		virtual Axis			VCOM_CALLTYPE SetWPHybridTool(bool bRestore) = 0;
		virtual void			VCOM_CALLTYPE RestoreWPHybridTool(bool bRestore) = 0;
		virtual void			VCOM_CALLTYPE ClearWPHybridTool() = 0;
		virtual void			VCOM_CALLTYPE SetCursorByView() = 0;
		virtual bool			VCOM_CALLTYPE AddUndoDeselectObj(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE AddUndoSelectObj(MCObjectHandle hObject) = 0;
		virtual TOSWndPtr		VCOM_CALLTYPE GetLayoutDialogOSHandle(Sint32 dialogID) = 0;
		virtual TOSWndPtr		VCOM_CALLTYPE GetLayoutControlOSHandle(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void			VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, TexturePartSDK texPartID, Sint32 texLayerID) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, TexturePartSDK texPartID, Sint32 texLayerID, Boolean resolveByClass) = 0;
		virtual void			VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID) = 0;
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID) = 0;
		virtual void			VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID, const TextureMappingInfoSDK& mappingInfo) = 0;
		virtual Sint32			VCOM_CALLTYPE GetNumTextureLayers(MCObjectHandle h, TexturePartSDK texPartID) = 0;
		virtual bool			VCOM_CALLTYPE SetStaticTextStyle(Sint32 dialogID, Sint32 itemID, Sint32 style) = 0;
		virtual bool			VCOM_CALLTYPE SetStaticTextColor(Sint32 dialogID, Sint32 itemID, Sint32 red, Sint32 green, Sint32 blue) = 0;
		virtual bool			VCOM_CALLTYPE SetItemClickable(Sint32 dialogID, Sint32 itemID, bool clickable) = 0;
		virtual bool			VCOM_CALLTYPE SetSliderLiveUpdate(Sint32 dialogID, Sint32 itemID, bool liveUpdate) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePaintNode(IDrawPad* pDrawPad) = 0;
		virtual bool			VCOM_CALLTYPE DrawSymbolPreview(IDrawPad* pDrawPad, InternalIndex resourceRefNum, const ViewRect& destRect, short viewMode=1, TRenderMode renderMode=renderWireFrame, ViewRect* outDrawBounds=NULL) = 0;
		virtual void			VCOM_CALLTYPE NotifyClassChange(StatusData liAdditionalData = 0) = 0;
		virtual bool		   	VCOM_CALLTYPE RegisterDialogForTimerEvents(Sint32 dialogID, Uint32 numberOfMilliseconds) = 0;
		virtual void		   	VCOM_CALLTYPE DeregisterDialogFromTimerEvents(Sint32 dialogID) = 0;
		virtual bool		   	VCOM_CALLTYPE SetImageControlData(Sint32 nDialogID, Sint32 nComponentID, void *imageData, size_t imageDataByteSize) = 0;
		virtual void			VCOM_CALLTYPE SetListItemEnabled(Sint32 dialogID, Sint32 componentID, short itemIndex, bool enabled = true) = 0;
		virtual void			VCOM_CALLTYPE SetFullBreakRecord(MCObjectHandle theWall, short index, WorldCoord off, SymbolBreakType* breakData) = 0;
		virtual bool			VCOM_CALLTYPE SetObjectAsCornerBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool CornerBreak) = 0;
		virtual bool			VCOM_CALLTYPE SetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord offset) = 0;
		virtual EWallCapAttributesType VCOM_CALLTYPE GetWallCapAttributesType(MCObjectHandle wall) = 0;
		virtual void			VCOM_CALLTYPE SetWallCapAttributesType(MCObjectHandle wall, EWallCapAttributesType wallCapAttributesType) = 0;
		virtual short			VCOM_CALLTYPE GetCoreWallComponent(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetCoreWallComponent(MCObjectHandle object, short componentIndex) = 0;
		virtual EWallHoleTexturePart VCOM_CALLTYPE GetWallHoleTexturePart(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetWallHoleTexturePart(MCObjectHandle object, EWallHoleTexturePart part) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFeature(MCObjectHandle wall, MCObjectHandle profile, EWallFeatureType wallFeatureType) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetActiveLayer() = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix, bool bInsert) = 0;
		virtual void			VCOM_CALLTYPE SetHighlightedHelpString(const TXString& helpMessage) = 0;
		virtual void			VCOM_CALLTYPE GetCurrentLocalization(TXString& outLanguage, TXString& outSubLanguage) = 0;
		virtual void			VCOM_CALLTYPE RGBToColorIndexN(const RGBColor& rgb, ColorRef& colorIndex, Boolean bIgnoreBlackBackground) = 0;
		virtual void			VCOM_CALLTYPE ColorIndexToRGBN(ColorRef colorIndex, RGBColor& rgb, Boolean bIgnoreBlackBackground) = 0;
		virtual void			VCOM_CALLTYPE RefreshRenderingForSelectedObjects() = 0;
		virtual void			VCOM_CALLTYPE RefreshResourceBrowserResourcesList(bool immediate) = 0;
		virtual bool			VCOM_CALLTYPE GetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short& outPatternIndex) = 0;
		virtual bool			VCOM_CALLTYPE SetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short patternIndex) = 0;
		virtual InternalIndex	VCOM_CALLTYPE SetDashStyle(const TXString& name, bool scaleWithThick, const std::vector<double>& inVectors) = 0; //returns style (negative InternalIndex) suitable for use in SetPenPatN, etc.
		virtual bool			VCOM_CALLTYPE PointInsideAnEnclosedRegionOfTheGroup(MCObjectHandle h, WorldPt &pickPt) = 0;

	// VW2011
	public:
		virtual MCObjectHandle  VCOM_CALLTYPE CreateArcLengthDimension(const WorldPt& dimStartPt, const WorldPt& dimEndPt, const WorldPt& arcCenterPt, const WorldCoord& startOffset, const bool clockwiseArc, bool witnessPerpChord, const bool arcIndicator) = 0;
		virtual void			VCOM_CALLTYPE GetTextCustomStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& customStyle) = 0;
		virtual void			VCOM_CALLTYPE SetTextCustomStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char customStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetRoofRunRise(Sint32 dialogID, Sint32 componentID, double& run, double& rise, double& value) = 0;
		virtual Sint32			VCOM_CALLTYPE CallDefaultToolN(EDefaultToolType type, bool isStandard, ToolMessage* message, std::shared_ptr<void>& messageContext) = 0;
		virtual bool			VCOM_CALLTYPE SetModeBarButtonsHelpText(const TXStringArray& arrHelpText) = 0;

		virtual HotSpotRefID	VCOM_CALLTYPE TrackHotSpotN(Boolean& outIs3d, WorldPt3& outLocation, Sint32& outData) = 0;
		virtual void			VCOM_CALLTYPE ShowRecFormatResourceDialog(MCObjectHandle& hFormat, Boolean isNewResource, bool hideInvisibleParameters = false) = 0;
		virtual bool			VCOM_CALLTYPE AlignColumnEdge(Sint32 dialogID, Sint32 srcItemID, short columnID, short alignMode ) = 0;
		virtual void			VCOM_CALLTYPE DeleteSymbolDefinition(MCObjectHandle hSymDef, Boolean bCompletely, Boolean useUndo = true) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetTilePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
		virtual short			VCOM_CALLTYPE GetTilePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) = 0;
		virtual short			VCOM_CALLTYPE GetTilePopupSelectedItem(Sint32 dialogID, Sint32 componentID) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetHatchPopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex) = 0;
		virtual short			VCOM_CALLTYPE GetHatchPopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) = 0;
		virtual short			VCOM_CALLTYPE GetHatchPopupSelectedItem(Sint32 dialogID, Sint32 componentID) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTile(const TXString& name) = 0;
		virtual bool			VCOM_CALLTYPE ShowEditTileDialog(MCObjectHandle& tileHandle) = 0;
		virtual bool			VCOM_CALLTYPE ShowEditTileSettingsDialog(MCObjectHandle& tileHandle) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE ShowNewTileDialog () = 0;
		virtual bool			VCOM_CALLTYPE GetTileBackgroundColor(MCObjectHandle tile, ColorRef& backgroundColor) = 0;
		virtual bool			VCOM_CALLTYPE SetTileBackgroundColor(MCObjectHandle tile , const ColorRef& backgroundColor) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetTileGeometryGroup (MCObjectHandle tileHandle) = 0;
		virtual bool	 		VCOM_CALLTYPE GetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &liRefNumber) = 0;
		virtual bool	 		VCOM_CALLTYPE SetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, Sint32 liRefNumber) = 0;
		virtual void	        VCOM_CALLTYPE AddToolEditTextMethod(const TXString & label, const TXString & value) = 0;
		virtual void			VCOM_CALLTYPE SetToolEditTextMethodValue(short group, const TXString& value) = 0;
		virtual TXString        VCOM_CALLTYPE GetToolEditTextMethodValue(short group) = 0;
		virtual void            VCOM_CALLTYPE EditRealConvertToStringUtility(short editRealType, double value, TXString& valueText) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GSNewObjectHandle(short objectType) = 0;
		virtual void			VCOM_CALLTYPE InvalObj(MCObjectHandle h) = 0;
		virtual bool			VCOM_CALLTYPE SetTextAdorner(MCObjectHandle textBlock, MCObjectHandle textAdorner, const WorldPt& scalePt) = 0;
		virtual Boolean			VCOM_CALLTYPE GetTreeControlItemText(Sint32 dialogID, Sint32 componentID, Sint32 nItemID, TXString& itemText) = 0;
		virtual Boolean			VCOM_CALLTYPE GetTreeControlSelectedItemText(Sint32 dialogID, Sint32 componentID, TXString& itemText) = 0;
		virtual bool			VCOM_CALLTYPE AddTileGeometryObject(MCObjectHandle tileHandle, MCObjectHandle objectHandle) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetTileGroupParent(MCObjectHandle objectHandle) = 0;
		virtual bool			VCOM_CALLTYPE IsTileGroupContainedObject(MCObjectHandle objectHandle) = 0;
		virtual Boolean VCOM_CALLTYPE GetObjectPlanarBounds(MCObjectHandle h, WorldRectVerts& outBoxVerts) = 0;
		virtual void			VCOM_CALLTYPE GetCurrToolInteractiveDraw(IToolInteractiveDraw** outInteractiveDraw) = 0;
		virtual bool			VCOM_CALLTYPE ArePlanarMatricesCoplanar(TransformMatrix & inMat1, TransformMatrix & inMat2, TransformMatrix& outTransformFrom2To1) = 0;
		virtual void			VCOM_CALLTYPE DrawCoordLineOnPlane( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID = 0 ) = 0;
		virtual void			VCOM_CALLTYPE DrawCoordLineOnPlane3D( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID = 0 ) = 0;
		virtual bool			VCOM_CALLTYPE GetPlanarMatrix(const TPlanarRefID& planarRefID, TransformMatrix& outMatrix)  = 0;
		virtual void			VCOM_CALLTYPE GetPlanarRefID( MCObjectHandle objectHandle, TPlanarRefID& outRefID ) = 0;
		virtual bool			VCOM_CALLTYPE IsScreenPlanarRefID(const TPlanarRefID& planarRefID)  = 0;
		virtual bool			VCOM_CALLTYPE IsPlanarObject( MCObjectHandle objectHandle, TPlanarRefID& outPlanarRefID ) = 0;
		virtual bool			VCOM_CALLTYPE IsPlanarObjectIn3DView( MCObjectHandle objectHandle ) = 0;
		virtual bool			VCOM_CALLTYPE PlanarPtTo3DModelPt( const TPlanarRefID& refID, const WorldPt& inPt, WorldPt3& outPt ) = 0;
		virtual bool			VCOM_CALLTYPE PlanarPtToScreenPlanePt( const TPlanarRefID& refID, WorldPt& outPt) = 0;
		virtual void			VCOM_CALLTYPE ScreenPlanePtToPlanarPt( const TPlanarRefID& refID, WorldPt& outPt ) = 0;
		virtual void			VCOM_CALLTYPE SetPlanarRefID( MCObjectHandle objectHandle, const TPlanarRefID& refID ) = 0;	
		virtual void			VCOM_CALLTYPE SetPlanarRefIDToGround( MCObjectHandle objectHandle ) = 0;	
		virtual TPlanarRefID	VCOM_CALLTYPE GetCurrentPlanarRefID( ) = 0;	
		virtual short			VCOM_CALLTYPE GetObjectTypeN(MCObjectHandle h) = 0;
		virtual void			VCOM_CALLTYPE ResizeSelectedDims( MCObjectHandle origH, const WorldCoord valueChange, const Sint32 dimCount, const Boolean onDraw, const Boolean dimLineResize, const Boolean fixedLengthWitLines ) = 0;
		virtual TXString		VCOM_CALLTYPE GetImageFileName(TXString &resourceFileName, Sint32 family, MCObjectHandle imageNode) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateImageDefNodeFromPNGData(void* pngData, size_t pngDataSize) = 0;
		virtual void			VCOM_CALLTYPE CompressTextureImage(MCObjectHandle image) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTextureBitmapNoDialog(MCObjectHandle parentShaderRecord) = 0;
		virtual Boolean			VCOM_CALLTYPE ShowListBrowserRadioToolTips(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void            VCOM_CALLTYPE Default2DToolDrawNew(const TPlanarRefID& planarRefID) = 0;
		virtual void			VCOM_CALLTYPE SetTextStyleRef(MCObjectHandle object, InternalIndex styleRef) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetTextStyleRef(MCObjectHandle object) = 0;
		virtual short			VCOM_CALLTYPE AlertQuestionDefault(const TXString& question, const TXString& advice = "", short defaultButton = 0, const TXString& OKOverrideText = "", const TXString& CancelOverrideText = "", const TXString& customButtonAText = "", const TXString& customButtonBText = "", const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "", short defaultAnswer = -1) = 0;
		virtual Boolean			VCOM_CALLTYPE SetColorName(ColorRef colorIndex, const TXString& colorName) = 0;
		virtual TXString		VCOM_CALLTYPE GetColorName(ColorRef colorIndex) = 0;
		virtual bool			VCOM_CALLTYPE IsScreenObject( MCObjectHandle objectHandle ) = 0;
		virtual bool	        VCOM_CALLTYPE PieceWiseNurbsCurveReverseInPlace( MCObjectHandle objectHandle ) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePieceWiseNurbsCurveReverse( MCObjectHandle objectHandle ) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlab(MCObjectHandle profile) = 0;
		virtual bool			VCOM_CALLTYPE ModifySlab(MCObjectHandle slab, MCObjectHandle modifier, bool isClipObject, Uint32 componentFlags) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetSlabStyle(MCObjectHandle slab) = 0;
		virtual void			VCOM_CALLTYPE SetSlabStyle(MCObjectHandle slab, InternalIndex slabStyle) = 0;
		virtual void			VCOM_CALLTYPE ConvertToUnstyledSlab(MCObjectHandle slab) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetSlabPreferencesStyle() = 0;
		virtual void			VCOM_CALLTYPE SetSlabPreferencesStyle(InternalIndex slabStyle) = 0;
		virtual void			VCOM_CALLTYPE BeginMultipleDuplicate() = 0;
		virtual void			VCOM_CALLTYPE EndMultipleDuplicate() = 0;
		virtual void			VCOM_CALLTYPE BuildConstraintModelForObject(MCObjectHandle objectHandle, bool traverseContainers) = 0;
		virtual void			VCOM_CALLTYPE RecordModifiedObjectInConstraintModel(MCObjectHandle objectHandle, bool useSelection)= 0;
		virtual Boolean	        VCOM_CALLTYPE GetCurveEndsAndTangents( MCObjectHandle objectHandle, WorldPt3& startPt, WorldPt3& endPt, WorldPt3& startTangent, WorldPt3& endTangent ) = 0;
		virtual Boolean			VCOM_CALLTYPE AreWorksheetGridLinesVisible( MCObjectHandle worksheet) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetGridLinesVisibility( MCObjectHandle worksheet, Boolean bVisible) = 0;
		virtual bool			VCOM_CALLTYPE AreUpdateChecksEnabled(void) = 0;	// returns true if update checking is supported
		virtual void			VCOM_CALLTYPE CheckForUpdates(void) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectPathNoOffset(const TXString& name, MCObjectHandle pathHand = NULL, MCObjectHandle profileGroupHand = NULL) = 0;		
		virtual short			VCOM_CALLTYPE NumberCustomDimensionStandards(void) = 0;
		virtual Boolean			VCOM_CALLTYPE ConsolidatePlanarObjects(const MCObjectHandle objectHandle, MCObjectHandle& objectHandleToBeTransformed) = 0;
		virtual Boolean         VCOM_CALLTYPE FindClosestPointOnNURBSObjectFrom3DPoint(MCObjectHandle h, const WorldPt3& point3D, WorldPt3 &outClosestPoint) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetSlabHeight(MCObjectHandle slab) = 0;
		virtual void			VCOM_CALLTYPE SetSlabHeight(MCObjectHandle slab, WorldCoord height) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlabStyle(const TXString &slabStyleName) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallPreferences() = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetSlabPreferences() = 0;
		virtual ETextureSet		VCOM_CALLTYPE GetTextureSet(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetTextureSet(MCObjectHandle object, ETextureSet textureSet) = 0;
		virtual short			VCOM_CALLTYPE GetDatumSlabComponent(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetDatumSlabComponent(MCObjectHandle object, short componentIndex) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallTop) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallTop) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallBottom) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallBottom) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followTopWallPeaks) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean followTopWallPeaks) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followBottomWallPeaks) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean followBottomWallPeaks) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound &autoBoundEdgeOffset) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound autoBoundEdgeOffset) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord &manualEdgeOffset) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord manualEdgeOffset) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex &texture) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex texture) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetComponentNetArea(MCObjectHandle object, short componentIndex) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetComponentNetVolume(MCObjectHandle object, short componentIndex) = 0;
		virtual void			VCOM_CALLTYPE FontMapReplace(const TXStringArray& arrFonts, bool doUserInterface) = 0;
		virtual void			VCOM_CALLTYPE FontMapGetReplacement(const TXString& orgFont, TXString& outReplFont) = 0;
		virtual short			VCOM_CALLTYPE ConvertFontIDToIndex(short fontID) = 0;
		virtual short			VCOM_CALLTYPE ConvertIndexToFontID(short fontIndex) = 0;
		virtual void            VCOM_CALLTYPE Get2DPolyAreaAndPerimeter(MCObjectHandle h, double &area, double &perimeter) = 0;
		virtual void			VCOM_CALLTYPE IFC_ResetGUID(MCObjectHandle hRecord) = 0;
		virtual bool			VCOM_CALLTYPE IFC_IsIFCRecord(MCObjectHandle hRecord) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallComponentPoly(MCObjectHandle hWall, short componentIndex) = 0;
		

	// VW2012
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectHiddenLine(MCObjectHandle hGeometry3D, double cuttingHeight, bool bottomOfCuttingPlane) = 0;
		virtual Boolean			VCOM_CALLTYPE AddBeforeModifyWorkingPlane() = 0;
		virtual bool			VCOM_CALLTYPE ModelPtToPlanarPt(const TPlanarRefID& refID, const WorldPt3& inModelPt, WorldPt& outPlanarPt) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE ImportResourceToCurrentFileN(Sint32 listID, Sint32 index, TImportResourceConflictCallbackProcPtr conflictCallback, void* env) = 0;
		virtual TXString		VCOM_CALLTYPE CoordToPrimaryDimensionString(WorldCoord coord) = 0;
		virtual TXString		VCOM_CALLTYPE CoordToSecondaryDimensionString(WorldCoord coord) = 0;
		virtual void			VCOM_CALLTYPE GetWallOverallHeights(MCObjectHandle theWall, WorldCoord& overallHeightTop, WorldCoord& overallHeightBottom) = 0;
		virtual bool			VCOM_CALLTYPE SetWallOverallHeights(MCObjectHandle theWall, const SStoryObjectData &bottomData, const SStoryObjectData &topData) = 0;
		virtual bool			VCOM_CALLTYPE CheckParametricNameConflictWithUI(const TXString& name) = 0;
		virtual void			VCOM_CALLTYPE ShowByClassChoice(Sint32 dialogID, Sint32 componentID) = 0;
		virtual Boolean			VCOM_CALLTYPE IsClassChoiceSelected(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void			VCOM_CALLTYPE SelectClassChoice(Sint32 dialogID, Sint32 componentID, Boolean select) = 0;
		virtual Sint32			VCOM_CALLTYPE GetMeshVertexCount(MCObjectHandle hMesh) = 0;
		virtual WorldPt3		VCOM_CALLTYPE GetMeshVertexAt(MCObjectHandle hMesh, size_t at) = 0;
		virtual void			VCOM_CALLTYPE SetMeshVertexAt(MCObjectHandle hMesh, size_t at, const WorldPt3& pt) = 0;
		virtual void			VCOM_CALLTYPE RunTempTool(const VWIID& iidToolExt) = 0;
		virtual bool			VCOM_CALLTYPE RenderPoly(MCObjectHandle hPoly, IVertexListener* listener, short convRes = 0) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE NewCreateCombineIntoSurface(const WorldPt& inPoint, short columnsAndPilastersEnum, bool goThrougLayre, MCObjectHandle listOfObjs) = 0;
			
		virtual void			VCOM_CALLTYPE PushPullPlanarGetInternalProcPtrAndUserData(PushPullHandleCompletionRoutinePtr& outProcPtr, void*& outUserData) = 0;
		virtual void			VCOM_CALLTYPE PushPullPlanarBegin(PushPullHandleCompletionRoutinePtr inCompletionProcPtr, void* inUserData) = 0;
		virtual void			VCOM_CALLTYPE PushPullPlanarAddObjectID(MCObjectHandle inHandleIDOfPlanarObjectToPushPull) = 0;
		virtual void			VCOM_CALLTYPE PushPullPlanarEnd() = 0;
		virtual bool			VCOM_CALLTYPE PushPullPlanarIsEnabled() = 0;
		virtual void			VCOM_CALLTYPE PushPullPlanarSetEnabled(bool inSetVal) = 0;
		virtual bool			VCOM_CALLTYPE PushPullPlanarNeedsPickLoop() = 0;
		virtual void			VCOM_CALLTYPE PushPullPlanarActionHandler(ToolMessage* message, Sint32& outPushPullReturn, bool& outHandledExclusively) = 0;
		virtual void			VCOM_CALLTYPE PushPullPlanarAddPrefButton() = 0;
		
		virtual MCObjectHandle	VCOM_CALLTYPE CreateProxyObjOnLayer(MCObjectHandle hParametric, MCObjectHandle hLayer) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetProxyParent(MCObjectHandle hProxyObj) = 0;

		virtual InternalIndex	VCOM_CALLTYPE AddClassWithUI(TXString& inOutName) = 0;
		virtual bool			VCOM_CALLTYPE EditClassWithUI(InternalIndex classIndex) = 0;
		virtual bool			VCOM_CALLTYPE EditClassWithUI(InternalIndex* arrClassIndex, size_t len) = 0;

		virtual void			VCOM_CALLTYPE ViewPt2WorldPt(const ViewPt& viewPt, WorldPt& outWorldPt) = 0;
		virtual bool			VCOM_CALLTYPE WorldPt2ViewPt(const WorldPt& worldPt, ViewPt& outViewPt) = 0;

		virtual bool			VCOM_CALLTYPE CloseDocument() = 0;
		virtual short			VCOM_CALLTYPE GetNumStories() = 0;
		virtual short			VCOM_CALLTYPE GetNumLayerLevelTypes() = 0;
		virtual short			VCOM_CALLTYPE GetNumStoryLayerTemplates() = 0;
		virtual TXString		VCOM_CALLTYPE GetLayerLevelType(MCObjectHandle layer) = 0;
		virtual bool			VCOM_CALLTYPE SetLayerLevelType(MCObjectHandle layer, TXString& layerLevelType) = 0;
		virtual TXString		VCOM_CALLTYPE GetStoryLayerTemplateName(short index) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryOfLayer(MCObjectHandle layer) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetLayerForStory(MCObjectHandle story, const TXString &layerLevelType) = 0;
		virtual bool			VCOM_CALLTYPE CreateStory(TXString& name, TXString& suffix) = 0;
		virtual bool			VCOM_CALLTYPE CreateLayerLevelType(TXString& name) = 0;
		virtual bool			VCOM_CALLTYPE CreateStoryLayerTemplate(TXString& name, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index) = 0;
		virtual bool			VCOM_CALLTYPE DeleteStoryLayerTemplate(short index) = 0;
		virtual bool			VCOM_CALLTYPE AssociateLayerWithStory(MCObjectHandle layer, MCObjectHandle story) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryAbove(MCObjectHandle story) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryBelow(MCObjectHandle story) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetStoryElevation(MCObjectHandle story) = 0;
		virtual bool			VCOM_CALLTYPE SetStoryElevation(MCObjectHandle story, WorldCoord elevation) = 0;
		virtual TXString		VCOM_CALLTYPE GetStorySuffix(MCObjectHandle story) = 0;
		virtual bool			VCOM_CALLTYPE SetStorySuffix(MCObjectHandle story, const TXString & suffix) = 0;
		virtual bool			VCOM_CALLTYPE HasObjectStoryBounds(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE HasObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id) = 0;
		virtual bool			VCOM_CALLTYPE GetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, SStoryObjectData& outData) = 0;
		virtual bool			VCOM_CALLTYPE SetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, const SStoryObjectData& data) = 0;
		virtual bool			VCOM_CALLTYPE DelObjectStoryBounds(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE DelObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id) = 0;
		virtual size_t			VCOM_CALLTYPE GetObjectStoryBoundsCount(MCObjectHandle hObject) = 0;
		virtual TObjectBoundID	VCOM_CALLTYPE GetObjectStoryBoundsAt(MCObjectHandle hObject, size_t index) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetObjectBoundElevation(MCObjectHandle hObject, TObjectBoundID id) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToPolylineWithTangentVertices(MCObjectHandle hNonPoly) = 0;


		virtual HotSpotRefID			VCOM_CALLTYPE AddHotSpotN(short inHotSpotType, const WorldPt3& inLocation, const TXString& cursorSpec, const TXString& inTip, Sint32 data) = 0;

		virtual bool			VCOM_CALLTYPE CreateImageControl2(Sint32 dialogID, Sint32 controlID, Sint32 widthInPixels, Sint32 heightInPixels, const TXString& imageSpecifier) = 0;
		virtual bool			VCOM_CALLTYPE UpdateImageControl2(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier) = 0;
		virtual bool			VCOM_CALLTYPE CreateImageButton(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar, const TXString& imageSpecifier) = 0;
		virtual bool			VCOM_CALLTYPE UpdateImageButton(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier) = 0;
		virtual bool			VCOM_CALLTYPE CreateThumbnailPopup(Sint32 dialogID, Sint32 controlID) = 0;
		
		virtual void			VCOM_CALLTYPE AddButtonMode(const TXString& iconSpec) = 0;
		virtual void			VCOM_CALLTYPE AddCheckMode(short initialSetting, const TXString& iconSpec) = 0;
		virtual void			VCOM_CALLTYPE AddRadioMode(short initialSetting, const TXStringArray& imageSpecs) = 0;
	
		virtual short			VCOM_CALLTYPE AddListBrowserImage(Sint32 dialogID, Sint32 componentID, const TXString& imageSpecifier, const TXString& selectedImageSpecifier = "") = 0;
		virtual Boolean			VCOM_CALLTYPE GetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, TXString& imageSpec0, TXString& imageSpec1, TXString& imageSpec2) = 0;
		virtual Boolean			VCOM_CALLTYPE SetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, const TXString& imageSpec0, const TXString& imageSpec1, const TXString& imageSpec2) = 0;
		virtual Sint32				VCOM_CALLTYPE InsertEnhancedPullDownMenuItem(Sint32 dialogID, Sint32 componentID, const TXString& strName, const TXString& imageSpecifier) = 0;
		virtual Boolean			VCOM_CALLTYPE InsertProposedClassOrLayerItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, const TXString& iconSpec) = 0;

		virtual bool			VCOM_CALLTYPE AreAlertsAllowed() = 0;

		virtual bool  			VCOM_CALLTYPE HasWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType) = 0;
		virtual EWSColumnDatabaseSortType VCOM_CALLTYPE GetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseSortType sortType) = 0;
		virtual short  			VCOM_CALLTYPE GetWorksheetColumnSortPrecedence(MCObjectHandle worksheet, short databaseRow, short column) = 0;
		virtual void 			VCOM_CALLTYPE MoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short fromColumn, short toColumn, EWSColumnDatabaseOperatorType operatorType) = 0;
		virtual void 			VCOM_CALLTYPE AddWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType) = 0;
		virtual void 			VCOM_CALLTYPE RemoveAllWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, EWSColumnDatabaseOperatorType operatorType) = 0;
		virtual void 			VCOM_CALLTYPE RemoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType) = 0;
		virtual void			VCOM_CALLTYPE GetStoryBoundChoiceStrings(MCObjectHandle story, bool topBound, TXStringArray& strings) = 0;
		virtual void			VCOM_CALLTYPE GetStoryBoundDataFromChoiceString(const TXString& string, SStoryObjectData& data) = 0;
		virtual void			VCOM_CALLTYPE GetChoiceStringFromStoryBoundData(const SStoryObjectData& data, TXString& string) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderworksStyle() = 0;
		virtual Boolean			VCOM_CALLTYPE Get3DObjEdgeData(const ViewPt& viewPt, MCObjectHandle objectH, WorldPt3& edgeStart, WorldPt3& edgeEnd) = 0;
		virtual bool			VCOM_CALLTYPE GetStoryLayerTemplateInfo(short index, TXString& name, double& scaleFactor, TXString& layerLevelType, double& elevationOffset, double& defaultWallHeight) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectGeneratingAutoPlane() = 0;

		virtual WorldCoord		VCOM_CALLTYPE GetVertexMaxRadius(MCObjectHandle h, short vertexNum) = 0;

		virtual void			VCOM_CALLTYPE AlertSetAlwaysDoValue(const TXString& category, const TXString& item, short value) = 0;

		virtual Sint32				VCOM_CALLTYPE GetCSGAction(MCObjectHandle hCSG) = 0;

	
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderBackground(BackgroundType backgroundType)=0;

		virtual bool            VCOM_CALLTYPE ExportResourceN(MCObjectHandle resource, IFileIdentifier* pFileID = nil, TImportResourceConflictCallbackProcPtr conflictCallback = nil) = 0;

	// VW2013
	public:
		virtual void			VCOM_CALLTYPE CustomBatchConvert(ICustomBatchConvertParams* params)=0;
		virtual void			VCOM_CALLTYPE GetAllObjectNames(TXStringArray& names)=0;
		virtual void			VCOM_CALLTYPE GetAllLayerNames(TXStringArray& names)=0;
		virtual void			VCOM_CALLTYPE SetListBoxTabStops( Sint32 dialogID, Sint32 componentID, Sint32 numTabStops, Sint32* tabStops ) = 0;
		virtual void			VCOM_CALLTYPE SupportCustomControlKeyEvents( Sint32 dialogID, Sint32 componentID) = 0;
		virtual void			VCOM_CALLTYPE SetTextJustificationN( MCObjectHandle textBlock, short justification) = 0;
		virtual void			VCOM_CALLTYPE SetTextVerticalAlignmentN( MCObjectHandle textBlock, short verticalAlignment) = 0;
		virtual TXString		VCOM_CALLTYPE GetLayerLevelTypeName(short index)=0;
		virtual bool			VCOM_CALLTYPE SetLayerLevelTypeName(short index, const TXString& name)=0;
		virtual bool			VCOM_CALLTYPE SetStoryLayerTemplateName(short index, const TXString& name)=0;
		virtual bool			VCOM_CALLTYPE GetUserOriginGlobal(WorldPt& outOrigin)=0;
		virtual bool			VCOM_CALLTYPE CreateSolid(MCObjectHandle blank, const TVWArray_MCObjectHandle &toolList, bool add, MCObjectHandle& newSolid)=0;
		virtual TXString		VCOM_CALLTYPE GetVectorworksSessionID() = 0;
		virtual void			VCOM_CALLTYPE EnableListBrowserHierarchicalDisplay(Sint32 dialogID, Sint32 componentID, Boolean enableHierarchicalDisplay)=0;
		virtual void			VCOM_CALLTYPE SetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID, short columnID)=0;
		virtual Boolean			VCOM_CALLTYPE SetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, double itemVal, short imageIndex)=0;

		virtual TXString		VCOM_CALLTYPE MilsToString(Sint32 value, EThicknessUnitsType unitType) = 0;
		virtual Boolean			VCOM_CALLTYPE StringToMils(const TXString& str, EThicknessUnitsType unitType, Sint32& outValue) = 0;
		virtual Boolean			VCOM_CALLTYPE StringToArea(const TXString& str, double& outArea) = 0;
		virtual Boolean			VCOM_CALLTYPE StringToVolume(const TXString& str, double& outVolume) = 0;

		virtual Boolean			VCOM_CALLTYPE IsListBrowserDisplayHierarchical(Sint32 dialogID, Sint32 componentID)=0;
		virtual void			VCOM_CALLTYPE HierarchicalListBrowserItemOpened(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive, short& outNumbRedisplayedItems)=0;
		virtual void			VCOM_CALLTYPE HierarchicalListBrowserItemClosed(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive)=0;
		virtual Boolean			VCOM_CALLTYPE HierarchicalListBrowserItemIsClosed(Sint32 dialogID, Sint32 componentID, short itemIndex)=0;
		virtual Boolean			VCOM_CALLTYPE HierarchicalListBrowserItemIsContainer(Sint32 dialogID, Sint32 componentID, short itemIndex)=0;
		virtual void			VCOM_CALLTYPE GetDisplayedItemsCountInHierarchicalContainer(Sint32 dialogID, Sint32 componentID, short itemIndex, short& outDisplayedItemsCount)=0;
		virtual TXString		VCOM_CALLTYPE GetListBrowserItemOriginalName(Sint32 dialogID, Sint32 componentID, short itemIndex)=0;
		virtual void			VCOM_CALLTYPE AddListBrowserOriginalName(Sint32 dialogID, Sint32 componentID, const TXString& originalName)=0;
		virtual void			VCOM_CALLTYPE GetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean& outLeve1Closed, Boolean& outLevel2Closed, Boolean& outLevel3Closed)=0;
		virtual void			VCOM_CALLTYPE SetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean level1Closed, Boolean level2Closed, Boolean level3Closed)=0;
		virtual void			VCOM_CALLTYPE CollapseAllListBrowserItems(Sint32 dialogID, Sint32 componentID)=0;
		virtual void			VCOM_CALLTYPE ExpandAllListBrowserItems(Sint32 dialogID, Sint32 componentID)=0;
		virtual Boolean			VCOM_CALLTYPE CreateStyledStaticText(Sint32 dialogID, Sint32 componentID, const TXString & strText, short widthInStdChar, EStaticTextType enumType)=0;

		virtual bool			VCOM_CALLTYPE SetModeBarButtonsText( const TVWModeBarButtonHelpArray& arrModeBarButtonsHelp ) = 0;
		virtual bool			VCOM_CALLTYPE SetToolHelpMessage( const TXString& modeText, const TXString& descriptionText ) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE FindWallsSurroundingPoint(MCObjectHandle inBoundedObject, const WorldPt& inPoint, short inColumnsAndPilastersEnum,
				MCObjectHandle inListOfObjects, bool ignoreClassVisibility, bool bExcludePiosNiches = true) = 0;
		virtual short			VCOM_CALLTYPE GetNumAssociations(MCObjectHandle handle) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetAssociation(MCObjectHandle handle, short index, Sint16& associationKind, Sint16& value) = 0;
		virtual void			VCOM_CALLTYPE AdjustPathForWrapping(TXString& path, short maxWidth) = 0;

		virtual void			VCOM_CALLTYPE DoBatchPrintOrExport(short inBatchOperationType) = 0;

		virtual void 			VCOM_CALLTYPE DeleteObjectNoNotify(MCObjectHandle h) = 0;

		virtual void			VCOM_CALLTYPE EditObjectSpecial(MCObjectHandle h, TObjSpecialEdit editMode) = 0;

		virtual short			VCOM_CALLTYPE GetNumSavedViews() = 0;
		virtual bool			VCOM_CALLTYPE GetSavedView(short index, TXString& view) = 0;
		virtual void			VCOM_CALLTYPE RestoreSavedView(const TXString& savedView) = 0;

		virtual bool			VCOM_CALLTYPE CreateCustomThumbnailPopup(Sint32 dialogID, Sint32 controlID, ThumbnailSizeType sizeKind)=0;
		virtual InternalIndex	VCOM_CALLTYPE GetClPenPatN(InternalIndex classIndex)=0;
		virtual void			VCOM_CALLTYPE SetClPenPatN(InternalIndex classIndex, InternalIndex penPat)=0;
		virtual InternalIndex	VCOM_CALLTYPE GetDefaultPenPatN()=0;
		virtual void			VCOM_CALLTYPE SetDefaultPenPatN(InternalIndex penPat)=0;
		virtual InternalIndex	VCOM_CALLTYPE GetPenPatN(MCObjectHandle h)=0;
		virtual void			VCOM_CALLTYPE SetPenPatN(MCObjectHandle h, InternalIndex penPat)=0;

		virtual void			VCOM_CALLTYPE GetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex& lineStyle, short& lineWeight) = 0;
		virtual void			VCOM_CALLTYPE SetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex lineStyle, short lineWeight) = 0;
		virtual void			VCOM_CALLTYPE GetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32& lineTypeRefNumber) = 0;
		virtual void			VCOM_CALLTYPE SetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32 lineTypeRefNumber) = 0;
		virtual void			VCOM_CALLTYPE ShowComplexLineTypesInLineAttributePopup(Sint32 dialogID, Sint32 itemID) = 0;
		virtual Boolean			VCOM_CALLTYPE GetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iLineRef, Sint32 &iLineWeight) = 0;
		virtual Boolean			VCOM_CALLTYPE SetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iStyleIndex, Sint32 iLineWeight) = 0;

		virtual Boolean			VCOM_CALLTYPE IsWorksheetCellImage (MCObjectHandle worksheet, short row, short column, short subrow = 0) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageType (MCObjectHandle worksheet, short row, short column, short& type) = 0;
		virtual short			VCOM_CALLTYPE GetWorksheetCellImageSizeType (MCObjectHandle worksheet, short row, short column) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageSize (MCObjectHandle worksheet, short row, short column, short& height, short& width) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageAngle (MCObjectHandle worksheet, short row, short column, double& angle) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageView (MCObjectHandle worksheet, short row, short column, TStandardView& view) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageRenderMode (MCObjectHandle worksheet, short row, short column, TRenderMode& renderMode) = 0;
		virtual Boolean			VCOM_CALLTYPE GetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, short row, short column) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageScale (MCObjectHandle worksheet, short row, short column, double& scale) = 0;
		virtual Boolean			VCOM_CALLTYPE GetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, short row, short column) = 0;
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageMarginSize (MCObjectHandle worksheet, short row, short column, unsigned char& marginSize) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short type) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageSizeType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short imageSizeType) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short height, short width) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageAngle (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double angle) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageView (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, TStandardView view) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageRenderMode (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, TRenderMode renderMode) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useLayerScale) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double scale) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useObjectImage) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageMarginSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, unsigned char marginSize) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE DoPolylineRadiusSmoothing(MCObjectHandle hPoly) = 0;
		virtual Boolean			VCOM_CALLTYPE SetImageControlDataN(Sint32 dialogID, Sint32 componentID, VectorWorks::UI::IIcon* icon) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWalls(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum, bool bExcludePiosNiches = true) = 0;

		//For Windows, the file path string contained in an IFileIdentifier passed to BuildResourceListN should be Ansi-encoded.
		virtual Sint32 VCOM_CALLTYPE BuildResourceListN(short objectType, IFileIdentifier* fileID, Sint32& numItems) = 0;

		virtual Boolean			VCOM_CALLTYPE TrimNurbsSurface(MCObjectHandle iNurbsSurface, MCObjectHandle iNurbsCurve) = 0;

		virtual void			VCOM_CALLTYPE InteractiveViewOperation_Begin(EInteractiveMode type, const ViewPt& viewPt) = 0;
		virtual void			VCOM_CALLTYPE InteractiveViewOperation_End() = 0;
		virtual void			VCOM_CALLTYPE InteractiveViewOperation_Move(const ViewPt& viewPt) = 0;

		virtual Boolean			VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName) = 0;
		virtual Boolean			VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName, size_t modebarGroupID, size_t modebarButtonID) = 0;
		virtual void			VCOM_CALLTYPE SetToolByIndex(short index) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateLayerWithUI(TXString& name) = 0;
		virtual bool			VCOM_CALLTYPE EditLayerWithUI(MCObjectHandle layer) = 0;

		virtual bool			VCOM_CALLTYPE CreateSavedViewWithUI(TXString& outName) = 0;
		virtual bool			VCOM_CALLTYPE EditSavedViewWithUI(TXString& inOutName) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateExtrudeAlongPath2(MCObjectHandle pathHandle, MCObjectHandle profileHandle, Boolean bExponentialScale, double scale, Boolean bLockProfilePlane, Boolean bFixProfile) = 0;
		virtual short			VCOM_CALLTYPE SectionSolid(MCObjectHandle obj1, MCObjectHandle obj2, Boolean useSectionColor, Boolean flipSection, MCObjectHandle& newSolid) = 0;
		virtual bool			VCOM_CALLTYPE IsGBXMLExportAllowed() = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToGenericSolid(MCObjectHandle objectHandle ) = 0;

		virtual void			VCOM_CALLTYPE AddWallToContainer(MCObjectHandle wallHandle, MCObjectHandle container) = 0;
		virtual void			VCOM_CALLTYPE SyncMatrixToStoryBound(MCObjectHandle h, TObjectBoundID id) = 0;
        virtual void            VCOM_CALLTYPE SplitPolylineByMultiple2DLoci(MCObjectHandle h, TVWArray_WorldPt loci, bool killOriginal, bool insert, TVWArray_MCObjectHandle & arrayHandle) = 0;

		virtual bool			VCOM_CALLTYPE ExportDocumentPreviewImageFile(IFileIdentifier* pFileID, Sint32 compressionType) = 0;

		virtual void			VCOM_CALLTYPE DeleteAssociations(MCObjectHandle h, Sint16 associationKind) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE CreateTaperedExtrude2(MCObjectHandle profileH, const double_param angle = 0.0, const double_param height = 1.0 ) = 0;

	// VW 2014
	public:
		virtual Boolean			VCOM_CALLTYPE EnableTreeControlDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable) = 0;
		virtual void			VCOM_CALLTYPE EnableDragBetweenControls( Sint32 dialogID, Sint32 source, Sint32 destination ) = 0;
		virtual Boolean			VCOM_CALLTYPE GetTreeControlItemParent( Sint32 dialogID, Sint32 componentID, Sint32 itemID, Sint32 & parentID ) = 0;
		virtual Sint32			VCOM_CALLTYPE CopyTreeControlSubtree( Sint32 dialogID, Sint32 sourceTree, Sint32 targetTree, Sint32 sourceItem, Sint32 destinationItem, Sint32 destinationItemParent ) = 0;
		virtual Boolean			VCOM_CALLTYPE SetTreeControlItemImage( Sint32 dialogID, Sint32 componentID, Sint32 itemID, const TXString & imageSpecifier ) = 0;
		virtual Boolean			VCOM_CALLTYPE SetTreeControlItemImageFromIcon( Sint32 dialogID, Sint32 componentID, Sint32 itemID, VectorWorks::UI::IIcon* icon ) = 0;

		virtual Boolean         VCOM_CALLTYPE TrimToSelectedObjectsN(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2, const Boolean bTrimToSelectedObjects = false) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateComplexLineType(const TXString& name) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetComplexLineTypeGeometryGroup (MCObjectHandle lineTypeH) = 0;
		virtual bool			VCOM_CALLTYPE AddComplexLineTypeGeometryObject(MCObjectHandle lineTypeH, MCObjectHandle objectH) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetComplexLineTypeGroupParent(MCObjectHandle groupH) = 0;
		virtual bool			VCOM_CALLTYPE IsComplexLineTypeGroupContainedObject(MCObjectHandle objectH) = 0;
		virtual bool			VCOM_CALLTYPE SetComplexLineTypePageSpace(MCObjectHandle lineTypeH, Boolean isPageSpace) = 0;
		virtual bool			VCOM_CALLTYPE IsComplexLineTypeInPageSpace(MCObjectHandle lineTypeH) = 0;
		virtual bool			VCOM_CALLTYPE SetComplexLineTypeGapSize(MCObjectHandle lineTypeH, const WorldCoord newGapSize) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetComplexLineTypeGapSize(MCObjectHandle lineTypeH) = 0;

		virtual void			VCOM_CALLTYPE RemoveAllTreeControlItems( Sint32 dialogID, Sint32 componentID ) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateGroupOutline( MCObjectHandle objectHandle ) = 0;

		virtual void			VCOM_CALLTYPE SetViewMatrixByVector(const WorldPt3& lookFrom, const WorldPt3& lookTo, const WorldPt3& upVector, TransformMatrix& outMatrix, MCObjectHandle activeViewport = NULL) = 0;

		virtual short			VCOM_CALLTYPE GetNumberOfLineTypesItems(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void			VCOM_CALLTYPE GetLineTypeAtIndex(Sint32 dialogID, Sint32 itemID, short index, InternalIndex& outLineTypeRefNumber) = 0;
		virtual bool			VCOM_CALLTYPE GetSimpleLineTypeData(MCObjectHandle lineTypeH, bool& outScaleWithThick, std::vector<double>& outData) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE Create2DObjectShadow(MCObjectHandle h2DObject, const WorldPt & offsetPt) = 0;

		virtual Boolean			VCOM_CALLTYPE GetToolPtCurrentIsSnapped() = 0;
		virtual Boolean			VCOM_CALLTYPE Project3DModelPtToScreen(const WorldPt3& inwpt3Model, WorldPt& outwptScreen) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE GetImageCropObject(MCObjectHandle object) = 0;
		virtual bool			VCOM_CALLTYPE IsImageCropped(MCObjectHandle object) = 0;
		virtual bool			VCOM_CALLTYPE IsImageCropVisible(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetImageCropVisible(MCObjectHandle object, bool isVisible) = 0;
		virtual bool			VCOM_CALLTYPE SetImageCropObject(MCObjectHandle imageObject, MCObjectHandle cropObject) = 0;

		virtual void			VCOM_CALLTYPE TransformGraphicObject(MCObjectHandle object, TransformMatrix& inMatrix) = 0;

		virtual size_t			VCOM_CALLTYPE GetNumViewportClassOverrides(MCObjectHandle viewportHandle) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetViewportClassOverrideClass(MCObjectHandle viewportHandle, size_t index) = 0;
		virtual Boolean			VCOM_CALLTYPE CreateViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex) = 0;
		virtual Boolean			VCOM_CALLTYPE GetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, SViewportClassOverride& outOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE SetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, const SViewportClassOverride& inOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE RemoveViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex) = 0;

		virtual size_t			VCOM_CALLTYPE GetNumViewportLightOverrides(MCObjectHandle viewportHandle) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLightOverrideLight(MCObjectHandle viewportHandle, size_t index) = 0;
		virtual Boolean			VCOM_CALLTYPE CreateViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex) = 0;
		virtual Boolean			VCOM_CALLTYPE GetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, SViewportLightOverride& outOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE SetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, const SViewportLightOverride& inOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex) = 0;

		virtual size_t			VCOM_CALLTYPE GetNumViewportLayerOverrides(MCObjectHandle viewportHandle) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLayerOverrideLayer(MCObjectHandle viewportHandle, size_t index) = 0;
		virtual Boolean			VCOM_CALLTYPE CreateViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) = 0;
		virtual Boolean			VCOM_CALLTYPE GetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerOverride& outOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE SetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerOverride& inOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) = 0;

		virtual size_t			VCOM_CALLTYPE GetNumViewportLayerPropertiesOverrides(MCObjectHandle viewportHandle) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLayerPropertiesOverrideLayer(MCObjectHandle viewportHandle, size_t index) = 0;
		virtual Boolean			VCOM_CALLTYPE CreateViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) = 0;
		virtual Boolean			VCOM_CALLTYPE GetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerPropertiesOverride& outOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE SetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerPropertiesOverride& inOverride) = 0;
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) = 0;

		virtual size_t			VCOM_CALLTYPE GetNumViewportLayerStackingOverrides(MCObjectHandle viewportHandle) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLayerStackingOverrideLayer(MCObjectHandle viewportHandle, size_t index) = 0;
		virtual Boolean			VCOM_CALLTYPE GetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, Sint32& outStackingPosition) = 0;
		virtual Boolean			VCOM_CALLTYPE SetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const Sint32& inStackingPosition) = 0;
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) = 0;

		virtual Boolean			VCOM_CALLTYPE IsDesignLayerViewport(MCObjectHandle hObj) = 0;

		virtual Boolean 		VCOM_CALLTYPE DeleteSavedSetting(const TXString& category) = 0;
		virtual Boolean 		VCOM_CALLTYPE DeleteSavedSetting(const TXString& category, const TXString& setting) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE TrackToolViewport(Boolean trackDLVP) = 0;

		virtual void VCOM_CALLTYPE ForEachObjectInList(MCObjectHandle hFirst, GS_ForEachObjectProcPtr action, void *actionEnv) = 0;

		virtual OpacityRef		VCOM_CALLTYPE GetClOpacity(InternalIndex classIndex) = 0;
		virtual void			VCOM_CALLTYPE SetCLOpacity(InternalIndex classIndex, OpacityRef opacity) = 0;
		virtual TPlanarRefID	VCOM_CALLTYPE GetWorkingPlanePlanarRefID( ) = 0;

		virtual Boolean			VCOM_CALLTYPE CreateScriptResource(const TXString& scriptName, const TXString& paletteName, bool paletteOpen, const TXString& script, bool python) = 0;
		virtual Boolean			VCOM_CALLTYPE GetScriptResource(const TXString& scriptName, TXString& outScript, bool& outPython) = 0;
		virtual Boolean			VCOM_CALLTYPE SetScriptResource(const TXString& scriptName, const TXString& script, bool python) = 0;
		virtual Boolean			VCOM_CALLTYPE OpenScriptResPalette(const TXString& paletteName, bool paletteOpen) = 0;

		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroupDeep(MCObjectHandle h) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateTextStyleResource(const TXString &name) = 0;

	// VW 2015
	public:
		virtual void			VCOM_CALLTYPE GetVWResourceString(TXString& outValue, const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty) = 0;
		virtual GSHandle		VCOM_CALLTYPE GetVWResource(const char* resourceIdentifier) = 0;
		virtual Sint32			VCOM_CALLTYPE CreateLayoutDialogFromVWResource(const char* resIdentifier) = 0;

		virtual void			VCOM_CALLTYPE GetListOfWorkingPlanes( TVWArray_MCObjectHandle& planesList ) = 0;
		virtual Boolean			VCOM_CALLTYPE GetWorkingPlaneInfo( MCObjectHandle planeH, TXString& outName, Axis& outAxis ) = 0;
		virtual Boolean			VCOM_CALLTYPE SetWorkingPlaneInfo( MCObjectHandle planeH, const TXString & name, const Axis axis ) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE DuplicateWorkingPlane( MCObjectHandle planeH ) = 0;
		virtual void			VCOM_CALLTYPE DeleteWorkingPlane( MCObjectHandle planeH ) = 0;
	
        virtual void            VCOM_CALLTYPE SysBeep(short duration) = 0;
		virtual Uint32			VCOM_CALLTYPE TickCount() = 0; // returns 1/60th of a second. Approx: mili_sec = gSDK->TickCount() * 17;

		virtual bool			VCOM_CALLTYPE IsCurtainWall( MCObjectHandle hWall ) = 0;
		virtual bool			VCOM_CALLTYPE GetCurtainWallPanelInfo( MCObjectHandle hWall, const WorldPt & inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight ) = 0;

        virtual bool            VCOM_CALLTYPE IsFontAvailable(short fontID) = 0;

		virtual void			VCOM_CALLTYPE ResetVisibilityForSymbol(MCObjectHandle symDef) = 0;
    
        virtual void            VCOM_CALLTYPE GetStandardFontList (TXStringArray& fontList) = 0;
		virtual bool			VCOM_CALLTYPE CanSymbolBeAddedLegal(MCObjectHandle container, MCObjectHandle symDef) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateMesh() = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateMesh(IMeshData** outMeshData) = 0;
		virtual bool			VCOM_CALLTYPE GetMesh(MCObjectHandle hMesh, IMeshData** outMeshData) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE AddMeshFace(MCObjectHandle hMesh, const TVWArray_SizeT& arrVertexIndices) = 0;
        virtual  bool           VCOM_CALLTYPE GetPointInsidePoly(MCObjectHandle poly, WorldPt &insideWorldPt) = 0;

		virtual bool			VCOM_CALLTYPE GetGradientDataN(MCObjectHandle gradient, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity) = 0;
		virtual bool			VCOM_CALLTYPE GetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity) = 0;
		virtual bool			VCOM_CALLTYPE GetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, OpacityRef& opacity) = 0;
		virtual Sint16			VCOM_CALLTYPE InsertGradientSegmentN(MCObjectHandle gradient, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity) = 0;
		virtual Sint16			VCOM_CALLTYPE InsertGradientSliderSegmentN(Sint32 dialogID, Sint32 componentID, Real64 spotPosition, const WorldPt3& color, const OpacityRef& opacity) = 0;
		virtual bool			VCOM_CALLTYPE SetGradientDataN(MCObjectHandle gradient, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity) = 0;
		virtual bool			VCOM_CALLTYPE SetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity) = 0;
		virtual bool			VCOM_CALLTYPE SetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, const OpacityRef& opacity) = 0;
        
        virtual short           VCOM_CALLTYPE GetStandardFontListSize() = 0;
		
		virtual void			VCOM_CALLTYPE SetTreeControlItemAsDivider(Sint32 dialogID, Sint32 componentID, Sint32 itemID, bool isDivider) = 0;
		virtual size_t			VCOM_CALLTYPE GetTreeControlItemNumberOfChildren(Sint32 dialogID, Sint32 componentID, Sint32 itemID) = 0;
		virtual Sint32			VCOM_CALLTYPE GetTreeControlItemChildID(Sint32 dialogID, Sint32 componentID, Sint32 parentID, Sint32 index) = 0;
		virtual void			VCOM_CALLTYPE SetTreeControlItemSelectionState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, bool select) = 0;
		

		virtual MCObjectHandle  VCOM_CALLTYPE GetVerticesFromSolid(MCObjectHandle handle) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetNurbsCurvesFromSolid(MCObjectHandle handle) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetNurbsSurfacesFromSolid(MCObjectHandle handle) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetNurbsCurvesOnCuttingPlane(MCObjectHandle handle, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal) = 0;
		virtual Boolean			VCOM_CALLTYPE CustomObjectControlPtGet(MCObjectHandle inOwnerObj, Sint32 dataIndex, WorldPt3& outPt, Boolean* outIs2DOnly=NULL, Boolean* outIsHidden=NULL, Sint32* outClientID=NULL) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE CreateImageMaskFromAlphaChannel(MCObjectHandle inImage, bool useAlpha=true) = 0;
		virtual MCObjectHandle VCOM_CALLTYPE ConvertPolylineToPolylineWithOnlyArcVertices(MCObjectHandle handle, bool insert = false) = 0;
		virtual bool			VCOM_CALLTYPE GetTextTabStopCount(MCObjectHandle textBlock, Sint32& count) = 0;
		virtual bool			VCOM_CALLTYPE GetTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord& location) = 0;
		virtual bool			VCOM_CALLTYPE MoveTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord location) = 0;
		virtual bool			VCOM_CALLTYPE AddTextTabStop(MCObjectHandle textBlock, WorldCoord location) = 0;
		virtual bool			VCOM_CALLTYPE RemoveTextTabStop(MCObjectHandle textBlock, Sint32 index) = 0;
		virtual bool			VCOM_CALLTYPE GetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, float& trackingValue) = 0;
		virtual bool			VCOM_CALLTYPE SetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, Sint32 numChars, float trackingValue) = 0;

		virtual bool			VCOM_CALLTYPE GetTextStyleByClass(MCObjectHandle handle) = 0;
		virtual void			VCOM_CALLTYPE SetTextStyleByClass(MCObjectHandle handle) = 0;
		virtual bool			VCOM_CALLTYPE GetClUseTextStyle(InternalIndex classId) = 0;
		virtual void			VCOM_CALLTYPE SetClUseTextStyle(InternalIndex classId, bool use) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetClTextStyleRef(InternalIndex classId) = 0;
		virtual void			VCOM_CALLTYPE SetClTextStyleRef(InternalIndex classId, InternalIndex textStyleRef) = 0;

		virtual bool			VCOM_CALLTYPE GetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& offset) = 0;
		virtual bool			VCOM_CALLTYPE SetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord height) = 0;
		virtual bool			VCOM_CALLTYPE GetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& height) = 0;


		virtual void			VCOM_CALLTYPE SetHatchReferenceForMaterialNode(MCObjectHandle inMaterial, RefNumber inHatchReference) = 0;
		virtual void			VCOM_CALLTYPE ClearHatchReferenceForMaterialNode(MCObjectHandle inMaterial) = 0;
		virtual RefNumber		VCOM_CALLTYPE GetHatchReferenceForMaterialNode(MCObjectHandle inMaterial) = 0;

		virtual TXString		VCOM_CALLTYPE GetDescriptionText(MCObjectHandle hObj) = 0;
		virtual bool			VCOM_CALLTYPE SetDescriptionText(MCObjectHandle hObj, const TXString& descriptionText) = 0;

		virtual void			VCOM_CALLTYPE RefreshModeBar() = 0;
		virtual void			VCOM_CALLTYPE ClearClearPullDownMenu(short group) = 0;

		virtual Boolean			VCOM_CALLTYPE RefreshClassPopup(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void			VCOM_CALLTYPE SetPerspectiveInfo(TProjection projKind, TRenderMode renderMode, WorldCoord persDistance, const WorldPt &pt1, const WorldPt &pt2) = 0;


		virtual short			VCOM_CALLTYPE GetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE GetPDFPageCropObject(MCObjectHandle object)	= 0;
		virtual bool			VCOM_CALLTYPE IsPDFPageCropped(MCObjectHandle object)		= 0;
		virtual bool			VCOM_CALLTYPE IsPDFPageCropVisible(MCObjectHandle object)	= 0;
		virtual void			VCOM_CALLTYPE SetPDFPageCropVisible(MCObjectHandle object, bool isVisible) = 0;
		virtual bool			VCOM_CALLTYPE SetPDFPageCropObject(MCObjectHandle pdfPageObject, MCObjectHandle cropObject) = 0;
		virtual bool			VCOM_CALLTYPE SetPDFPageWidthAndHeight(MCObjectHandle pdfPageObject, WorldCoord newWidth, WorldCoord newHeight) = 0;

		virtual void			VCOM_CALLTYPE SetCurrentView(TStandardView view, bool direct = false) = 0;

		virtual void			VCOM_CALLTYPE CreateSymbolFolderN(const TXString& folderPath, TVWArray_MCObjectHandle & outFolderPath) = 0;// use / for delimiter of the folderPath parameter( i.e. "Folder1/Folder2" )
		virtual bool			VCOM_CALLTYPE IsCurrentlyBuildingAnUndoEvent() = 0;
		virtual bool			VCOM_CALLTYPE ShowCustomDimensionStandardsDialog() = 0;
		virtual bool			VCOM_CALLTYPE SetTextStyleRefN(MCObjectHandle textBlock, short firstChar, short numChars, InternalIndex styleRef) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetTextStyleRefN(MCObjectHandle h, short atChar) = 0;
		virtual bool			VCOM_CALLTYPE SetTextStyleByClassN(MCObjectHandle textBlock, short firstChar, short numChars) = 0;
		virtual bool			VCOM_CALLTYPE GetTextStyleByClassN(MCObjectHandle h, short atChar) = 0;

		virtual short			VCOM_CALLTYPE GetNumStoryLevelTemplates() = 0;
		virtual TXString		VCOM_CALLTYPE GetStoryLevelTemplateName(short index) = 0;
		virtual bool			VCOM_CALLTYPE SetStoryLevelTemplateName(short index, const TXString& name) = 0;
		virtual bool			VCOM_CALLTYPE CreateStoryLevelTemplate(TXString& name, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index) = 0;
		virtual bool			VCOM_CALLTYPE DeleteStoryLevelTemplate(short index) = 0;
		virtual bool			VCOM_CALLTYPE GetStoryLevelTemplateInfo(short index, TXString& name, double& scaleFactor, TXString& layerLevelType, double& elevationOffset, double& defaultWallHeight) = 0;
		virtual bool			VCOM_CALLTYPE AddStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord elevation, const TXString& layerName) = 0;
		virtual bool			VCOM_CALLTYPE AddStoryLevelFromTemplate(MCObjectHandle storyHandle, short index) = 0;
		virtual bool			VCOM_CALLTYPE RemoveStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, bool bDeleteLayer) = 0;
		virtual bool			VCOM_CALLTYPE SetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord newElevation) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType) = 0;
		virtual bool			VCOM_CALLTYPE ResetDefaultStoryLevels(bool bDeleteExisting ) = 0;
		
		virtual MCObjectHandle	VCOM_CALLTYPE TrackToolInViewportAnnotatons(MCObjectHandle &proxyObj, Boolean &worldObjInVP, bool createProxy) = 0;

		virtual Boolean			VCOM_CALLTYPE GetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &topIsRelativeToStory) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean topIsRelativeToStory) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &bottomIsRelativeToStory) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean bottomIsRelativeToStory) = 0;

		virtual void			VCOM_CALLTYPE ShowListBrowserHeader(Sint32 dialogID, Sint32 componentID, bool show) = 0;

		virtual Boolean			VCOM_CALLTYPE GetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, double& itemVal, short& imageIndex) = 0;

	// VW 2015 SP1
		virtual bool			VCOM_CALLTYPE GetCurtainWallPanelInfoExtended( MCObjectHandle hWall, const WorldPt & inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight, 
													WorldCoord& panelThickness,   //This is the thickness of the panel as it subtracts from the frames. It is a property of the panel
													WorldCoord& panelOffset,         // This is the dimension from the center of the panel to the center of the wall
													WorldCoord& frameInsetTop,   // The frame inset is the distance the panel extends into and subtracts from the frame. 
													WorldCoord& frameInsetBottom, 
													WorldCoord& frameInsetRight, 
													WorldCoord& frameInsetLeft) = 0;
        
        virtual void  VCOM_CALLTYPE Trim2DObjectWithLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, bool insert, TVWArray_MCObjectHandle & hResultArray) = 0;


	public:

	// VW 2016
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE GetOtherObjectFromBinaryConstraint(CBSignedShort type, MCObjectHandle obj, CBSignedShort objVertexA, CBSignedShort objVertexB, InternalIndex containedObj, MCObjectHandle& outContraint) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE FindBinbaryConstraintToObject(CBSignedShort type, MCObjectHandle obj, MCObjectHandle toObject, CBSignedShort& outToObjectVertexA, CBSignedShort& outToObjectVertexB, InternalIndex& outToObjectContainedObj) = 0;
    
		// ForEach lambda support
		virtual void				VCOM_CALLTYPE ForEach3DPointInObjectN(MCObjectHandle h, std::function<bool(const WorldPt3& point3D)> callbackLambda) = 0;
		virtual void				VCOM_CALLTYPE ForEachPolyEdgeN( MCObjectHandle inPolyH, std::function<void(const SPolyEdge& edge)> callbackLambda) = 0;
		virtual void				VCOM_CALLTYPE ForEachLayerN( std::function<void(MCObjectHandle h)> callbackLambda) = 0;
		virtual void				VCOM_CALLTYPE ForEachObjectN( short traverseWhat, std::function<void(MCObjectHandle h)> callbackLambda) = 0;
		virtual void				VCOM_CALLTYPE ForEachBreakN( MCObjectHandle theWall, std::function<bool(MCObjectHandle h, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData)> callbackLambda) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFileInStandardFolderN(EFolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInStandardFolderN(FolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInFolderN(IFolderIdentifier* pStartFolderID, bool doRecursive, std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) = 0;
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInPluginFolderN(std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) = 0;
		virtual void				VCOM_CALLTYPE ForEachObjectInListN(MCObjectHandle hFirst, std::function<void(MCObjectHandle h)> callbackLambda) = 0;

		virtual Sint32				VCOM_CALLTYPE SendActiveToolMessage(ToolMessage& message) = 0;

		virtual void				VCOM_CALLTYPE AddPullDownResourceMethod(const TXString& label, const TXString& value) = 0;
		virtual void				VCOM_CALLTYPE SetPullDownResourceValue(short group, const TXString& value) = 0;
		virtual Sint32				VCOM_CALLTYPE ShowPullDownResourcePopup(short group, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize = kStandardSize) = 0;
		virtual void				VCOM_CALLTYPE SetImagePopupResourceAdvanced(Sint32 dialogID, Sint32 componentID) = 0;
		virtual void				VCOM_CALLTYPE SetImagePopupResourceCategories(Sint32 dialogID, Sint32 componentID, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex) = 0;

		virtual bool				VCOM_CALLTYPE GetClassSharedAndUpdateReference (MCObjectHandle hDLVPort, InternalIndex classIndex, bool& outSharedRef, bool& outUpdateRef) = 0;
		
		virtual bool				VCOM_CALLTYPE SetObjectAsSpanWallBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool spanWallBreak) = 0;

		virtual bool				VCOM_CALLTYPE GetTreeControlItemCheckBoxState(Sint32 dialogID, Sint32 componentID, int itemID, Sint32& outState) = 0;	// VWFC::VWUI::ECheckButtonCtrlState
		virtual bool				VCOM_CALLTYPE SetTreeControlItemCheckBoxState(Sint32 dialogID, Sint32 componentID, int itemID, Sint32 state) = 0;
        virtual OSType				VCOM_CALLTYPE GetDataMapDataClientID(MCObjectHandle h) = 0;

		virtual MCObjectHandle		VCOM_CALLTYPE CreateShellSolid(MCObjectHandle surface, double thickness) = 0;

		virtual bool				VCOM_CALLTYPE CreateSlabModifier(MCObjectHandle slab, MCObjectHandle profile, bool isSubtract, Sint16 componentID, bool clipToBoundary) = 0;

		virtual bool				VCOM_CALLTYPE ExportImage(IFileIdentifier* fileID, const SExportImageOptions& options) = 0;
		virtual bool				VCOM_CALLTYPE ExportSTL(IFileIdentifier* fileID, bool exportBinary, double percentTess, Sint16 exportObjectsOptions) = 0;

		virtual void				VCOM_CALLTYPE ForEachClass( Boolean doGuestClasses, std::function<void(MCObjectHandle h)> callbackLambda) = 0;

		virtual void				VCOM_CALLTYPE GetParentFolderNameFromResourceList(Sint32 listID, Sint32 index, TXString& name) = 0;
		virtual bool				VCOM_CALLTYPE ExportSymbolResource(MCObjectHandle symbolresource, const TXString& symbolFolderDest, IFileIdentifier* pFileID = nil, bool suppressDialogs = false, TImportResourceConflictCallbackProcPtr conflictCallback = nil) = 0; // Pass empty string to insert symbol at the root level.
        virtual InternalIndex       VCOM_CALLTYPE GetRoofStyle(MCObjectHandle roof) = 0;
        virtual void                VCOM_CALLTYPE SetRoofStyle(MCObjectHandle roof, InternalIndex roofStyle) = 0;
        virtual void                VCOM_CALLTYPE ConvertToUnstyledRoof(MCObjectHandle roof) = 0;
        virtual InternalIndex       VCOM_CALLTYPE GetRoofPreferencesStyle() = 0;
        virtual void                VCOM_CALLTYPE SetRoofPreferencesStyle(InternalIndex roofStyle) = 0;
        virtual MCObjectHandle      VCOM_CALLTYPE CreateRoofStyle(const TXString &roofStyleName) = 0;
        virtual MCObjectHandle      VCOM_CALLTYPE GetRoofPreferences() = 0;
        virtual short               VCOM_CALLTYPE GetDatumRoofComponent(MCObjectHandle object) = 0;
        virtual void                VCOM_CALLTYPE SetDatumRoofComponent(MCObjectHandle object, short componentIndex) = 0;

		virtual bool				VCOM_CALLTYPE ExportDocument(IFileIdentifier* fileID, short version) = 0;		
		
		        // For BuildResourceListFromOpenFile, the fileRef can be obtained from GetOpenFilesList. The fileRef will always be non-negative for open files.
		virtual Sint32				VCOM_CALLTYPE BuildResourceListFromOpenFile(const short objectType, const size_t fileRef, Sint32& numItems) = 0;

				//The file path string in IFileIdentifiers passed back by GetFavoritesList and GetOpenFilesList uses Mac-encoding. On Mac platforms only, the  
				//paths are the Posix paths.
        virtual void                VCOM_CALLTYPE GetFavoritesList (TVWArray_IFileIdentifierPtr& outFavorites) = 0;
        virtual void                VCOM_CALLTYPE GetOpenFilesList (TVWArray_OpenFileInformation& outInformation) = 0;

				// For SwitchToOpenFile, the fileRef can be obtained from GetOpenFilesList. Returns false if fileRef is invalid or no longer open.
		virtual bool				VCOM_CALLTYPE SwitchToOpenFile (Sint32 fileRef) = 0;

        virtual bool                VCOM_CALLTYPE TranslateToCurrentVersion (IFileIdentifier* pSrcFileID, IFileIdentifier* pDstFileID) = 0;

		virtual void                VCOM_CALLTYPE CalcRoofTopArea(MCObjectHandle object, double& outArea) = 0;

		virtual void				VCOM_CALLTYPE SwitchFromPlanTo3DView() = 0;

		virtual void				VCOM_CALLTYPE UngroupObject(MCObjectHandle object) = 0;
		virtual MCObjectHandle		VCOM_CALLTYPE ConvertToGroup(MCObjectHandle object, short convertAction) = 0;
		virtual void				VCOM_CALLTYPE ConvertObjectToLines(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode) = 0;
		virtual void				VCOM_CALLTYPE ConvertObjectToPolygons(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode) = 0;
		virtual void				VCOM_CALLTYPE SymbolToGroup(MCObjectHandle &theSymbol) = 0;
		virtual void				VCOM_CALLTYPE SymbolsInGroupToGroups(MCObjectHandle inObject) = 0;		

		virtual	GSHandle			VCOM_CALLTYPE ViewCreateCurrent() = 0;
		virtual void				VCOM_CALLTYPE ViewDelete(GSHandle hView) = 0;
		virtual	GSHandle			VCOM_CALLTYPE ViewDuplicate(GSHandle hView) = 0;
		virtual size_t				VCOM_CALLTYPE ViewGetNumLayers(GSHandle hView) = 0;
		virtual void				VCOM_CALLTYPE ViewGetLayerVisibility(GSHandle hView, size_t index, InternalIndex& outName, short& outVisibility) = 0;
		virtual size_t				VCOM_CALLTYPE ViewGetNumClasses(GSHandle hView) = 0;
		virtual void				VCOM_CALLTYPE ViewGetClassVisibility(GSHandle hView, size_t index, InternalIndex& outClassID, short& outVisibility) = 0;
		virtual void				VCOM_CALLTYPE ViewStore(GSHandle hView) = 0;
		virtual void				VCOM_CALLTYPE ViewRestore(GSHandle hView) = 0;

        virtual bool                VCOM_CALLTYPE GetCheckoutsComment(TXString& comment) = 0;
        virtual bool                VCOM_CALLTYPE SetCheckoutsComment(const TXString& comment) = 0;
        virtual bool                VCOM_CALLTYPE GetCurrentUserId(TXString& userid) = 0;
        virtual bool                VCOM_CALLTYPE GetProjectFullPath(TXString& outFilePath) = 0;
        virtual bool                VCOM_CALLTYPE GetWorkingFileId(TXString& uuid) = 0;
        virtual bool                VCOM_CALLTYPE IsAWorkingFile() = 0;
        virtual bool                VCOM_CALLTYPE IsProjectOffline() = 0;
        virtual bool                VCOM_CALLTYPE GetProjectUserNames(TXStringArray& users) = 0;
        virtual bool                VCOM_CALLTYPE GetProjectUser(const TXString& userId, TXString fullName, EUserProjectPermission& permission) = 0;
        virtual bool                VCOM_CALLTYPE GetLayerProjectInfo(MCObjectHandle layer, LayerProjectInfo& layerInfo) = 0;

		virtual MCObjectHandle		VCOM_CALLTYPE GetCustomScreenFeedbackGroup(MCObjectHandle hObject) = 0;
		virtual bool				VCOM_CALLTYPE SetCustomScreenFeedbackGroup(MCObjectHandle hObject, MCObjectHandle hFeedbackGroup) = 0;
		
        virtual void                VCOM_CALLTYPE SetCurrentLayerN(MCObjectHandle theLayer, Boolean bAllowUnifiedViewMaintenance = false) = 0;
		virtual bool				VCOM_CALLTYPE GetViewFromAndToPoints(WorldPt3& fromPt, WorldPt3& toPt) = 0;
        virtual void                VCOM_CALLTYPE UpdateBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData) = 0;

		virtual Boolean				VCOM_CALLTYPE GetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean &datumIsTopOfComponent) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean datumIsTopOfComponent) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound &wallAssociatedBound) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound wallAssociatedBound) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint &wallAssociatedSectionFillChangePoint) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint wallAssociatedSectionFillChangePoint) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification &wallAssociatedModification) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification wallAssociatedModification) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound &manualBound) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound manualBound) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord &boundOffset) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord boundOffset) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean &alwaysAutoJoinInCappedJoinMode) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean alwaysAutoJoinInCappedJoinMode) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 &alternateSectionFill) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 alternateSectionFill) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex &leftPenStyle, InternalIndex &rightPenStyle) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex leftPenStyle, InternalIndex rightPenStyle) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef &alternateSectionFillForeColor, ColorRef &alternateSectionFillBackColor) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef alternateSectionFillForeColor, ColorRef alternateSectionFillBackColor) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForFill) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForFill) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForFill) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForFill) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForAlternateSectionFill) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForAlternateSectionFill) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForAlternateSectionFill) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForAlternateSectionFill) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForLeftPen) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForLeftPen) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForLeftPen) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForLeftPen) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForLeftPen) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForLeftPen) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForRightPen) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForRightPen) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForRightPen) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForRightPen) = 0;
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForRightPen) = 0;
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForRightPen) = 0;

		virtual void				VCOM_CALLTYPE SetIsCurtainWall(MCObjectHandle wall, bool isCurtainWall) = 0;
		virtual WorldCoord			VCOM_CALLTYPE GetCurtainWallCutPlane(MCObjectHandle wall) = 0;
		virtual void				VCOM_CALLTYPE SetCurtainWallCutPlane(MCObjectHandle wall, WorldCoord curtainWallCutPlane) = 0;

		virtual MCObjectHandle		VCOM_CALLTYPE MirrorObject(MCObjectHandle h, bool dup, const WorldPt& p1, const WorldPt& p2) = 0;

	// VW 2017
	public:
		virtual Sint32				VCOM_CALLTYPE ShowPullDownResourcePopupN(const ViewPt& pt, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize = kStandardSize) = 0;
		virtual Boolean             VCOM_CALLTYPE ResetNurbsCurve(MCObjectHandle curveHandle, const WorldPt3& firstPt, bool byCtrlPts, short degree) = 0;
		virtual Boolean				VCOM_CALLTYPE SetArc(MCObjectHandle hArc, const WorldPt& center, double radius, double startAngle, double sweepAngle) = 0;

		virtual void				VCOM_CALLTYPE GetOpacityN(	MCObjectHandle h, OpacityRef& outPenOpacity, OpacityRef& outFillOpacity ) = 0;
		virtual void				VCOM_CALLTYPE SetOpacityN(	MCObjectHandle h, OpacityRef inNewPenOpacity, OpacityRef inNewFillOpacity ) = 0;
		virtual void				VCOM_CALLTYPE SetOpacityByClassN(	MCObjectHandle h, Boolean inPenOpacityByClass, Boolean inFillOpacityByClass ) = 0;
		virtual void				VCOM_CALLTYPE GetOpacityByClassN(	MCObjectHandle h, Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass ) = 0;
		virtual void				VCOM_CALLTYPE GetDefaultOpacityN( OpacityRef& outPenOpacity, OpacityRef& outFillOpacity ) = 0;
		virtual void				VCOM_CALLTYPE SetDefaultOpacityN( OpacityRef inPenOpacity,	OpacityRef inFillOpacity ) = 0;
		virtual void				VCOM_CALLTYPE GetDefaultOpacityByClassN( Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass ) = 0;
		virtual void				VCOM_CALLTYPE SetDefaultOpacityByClassN( Boolean inPenOpacityByClass,	Boolean inFillOpacityByClass ) = 0;
		virtual void				VCOM_CALLTYPE GetClOpacityN(	InternalIndex classIndex, OpacityRef& penOpacity,	OpacityRef& fillOpacity ) = 0;
		virtual void				VCOM_CALLTYPE SetCLOpacityN(	InternalIndex classIndex, OpacityRef penOpacity,	OpacityRef fillOpacity ) = 0;
        
        //For PointTools_Isolating points
        virtual Boolean             VCOM_CALLTYPE MarqueeEmptyList() = 0;
        virtual Boolean             VCOM_CALLTYPE MarqueeAddObject(MCObjectHandle hInObject) = 0;
        virtual MCObjectHandle      VCOM_CALLTYPE GetFreehandInteractivePoly() = 0;
        virtual void                VCOM_CALLTYPE BeginFreehandInteractive() = 0;
        virtual void                VCOM_CALLTYPE UpdateFreehandInteractive() = 0;
        virtual MCObjectHandle      VCOM_CALLTYPE EndFreehandInteractive() = 0;

		virtual Boolean				VCOM_CALLTYPE IsPlanRotationView() = 0;
		virtual MCObjectHandle	    VCOM_CALLTYPE CreateHelicalAlongCurve(MCObjectHandle curveHandle, double radius1, double radius2, double startAngle, double& pitch, double& numTurns, bool bPitch, bool bReverseTwist, bool bFlat) = 0;

		virtual void				VCOM_CALLTYPE ViewRestoreN(MCObjectHandle hView, Boolean bDontRegen3DBounds) = 0;
		virtual void				VCOM_CALLTYPE RestoreSavedViewN(const TXString& savedView, Boolean bDontRegen3DBounds) = 0;
        virtual void                VCOM_CALLTYPE PerformMultipleUnion_2(TVWArray_MCObjectHandle  hArray, TVWArray_MCObjectHandle & hArrayResult, bool insert) = 0;
		virtual Boolean	            VCOM_CALLTYPE CreateDuplicateAlongPath(TVWArray_MCObjectHandle hProfileArray, MCObjectHandle inPathH, Boolean bUseNumber, Sint32 inNumber, double inDistance, double inStartOffset, Boolean bCenterObject, Boolean bTangent, Boolean bKeepOrienation, TVWArray_MCObjectHandle &outDuplicateArray) = 0;
        virtual void				VCOM_CALLTYPE RemoveCustomTextureParts(MCObjectHandle h, Sint32 partCategoryID = 0) = 0;
		virtual void				VCOM_CALLTYPE AddCustomTexturePart(MCObjectHandle h, Sint32 partID, const TXString& partName, Sint32 partCategoryID = 0) = 0;
		virtual Boolean				VCOM_CALLTYPE CustomTexturePartExists(MCObjectHandle h, Sint32 partID, Sint32 partCategoryID = 0) = 0;
		virtual void				VCOM_CALLTYPE ApplyCustomTexturePart(MCObjectHandle srcObj, MCObjectHandle destObj, Sint32 partID, Sint32 partCategoryID = 0) = 0;

		virtual Boolean				VCOM_CALLTYPE GetPluginObjectStyle( MCObjectHandle h, RefNumber& styleRefNumber ) = 0;
		virtual Boolean				VCOM_CALLTYPE SetPluginObjectStyle( MCObjectHandle h, RefNumber styleRefNumber ) = 0;
		virtual bool				VCOM_CALLTYPE GetPluginStyleForTool( const TXString & toolUnivName, RefNumber& styleRefNumber ) = 0;
		virtual bool				VCOM_CALLTYPE SetPluginStyleForTool( const TXString & toolUnivName, const RefNumber styleRefNumber ) = 0;

		virtual bool				VCOM_CALLTYPE GetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType& insertMode ) = 0;
		virtual bool				VCOM_CALLTYPE SetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType insertMode ) = 0;
		virtual bool				VCOM_CALLTYPE GetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType& breakMode ) = 0;
		virtual bool				VCOM_CALLTYPE SetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType breakMode ) = 0;

		virtual void				VCOM_CALLTYPE ViewRect2WorldRect(const ViewRect& vRect, WorldRect& wRect) = 0;

        virtual MCObjectHandle      VCOM_CALLTYPE GetObjectByUuid(const TXString& uuid) = 0;

        //Returns false if the object does not have a Uuid
        virtual bool                VCOM_CALLTYPE GetObjectUuid(MCObjectHandle h, TXString& uuid) = 0;

		// Drop Shadow changes
		virtual bool				VCOM_CALLTYPE IsDropShadowEnabled(MCObjectHandle h) = 0 ;
		virtual void				VCOM_CALLTYPE EnableDropShadow (MCObjectHandle h, bool enable) = 0;
 
		virtual bool				VCOM_CALLTYPE GetDropShadowData(MCObjectHandle h, SDropShadowData & outDropShadowData) = 0;
		virtual void				VCOM_CALLTYPE SetDropShadowData(MCObjectHandle h, const SDropShadowData& inDropShadowData) = 0;
		virtual void				VCOM_CALLTYPE DeleteDropShadowData(MCObjectHandle h) = 0;
 
		virtual void				VCOM_CALLTYPE ShowDropShadowDialog(SDropShadowData& ioSDropShadowData, bool& ioByClass) = 0;
 
		virtual bool				VCOM_CALLTYPE IsDropShadowByClass(MCObjectHandle h) = 0;
		virtual void				VCOM_CALLTYPE SetDropShadowByClass(MCObjectHandle h, bool inSetByClass) = 0; 
 
		virtual void				VCOM_CALLTYPE GetClDropShadowData(InternalIndex classIndex, SDropShadowData& outDropShadowData) = 0;
		virtual void				VCOM_CALLTYPE SetClDropShadowData(InternalIndex classIndex, SDropShadowData& inDropShadowData) = 0;
 
		virtual bool				VCOM_CALLTYPE IsDropShadowEnabledInDocument() = 0;
		virtual void				VCOM_CALLTYPE SetDropShadowByClassInDocument(bool inSetByClass) = 0; 
 
		virtual void				VCOM_CALLTYPE GetDocumentDropShadowData( SDropShadowData& outDropShadowData) = 0;
		virtual void				VCOM_CALLTYPE SetDocumentDropShadowData( const SDropShadowData& inDropShadowData) = 0;
		virtual bool				VCOM_CALLTYPE DropShadowDataAreEqual(const SDropShadowData& inDropShadowData1, const SDropShadowData& inDropShadowData2) = 0;

		virtual bool				VCOM_CALLTYPE GetAllCombinedsurfaces(MCObjectHandle baseObject, const TVWArray_MCObjectHandle& arrClipObjects, TXGenericArray< std::pair<MCObjectHandle, TVWArray_SizeT> >& result, std::function<bool/*true to cancel*/(size_t i,size_t cnt)> progressCallback=nullptr) = 0; // returns false when function did not complete ok

		// For Slab drainage (Flat Roofs)
		virtual short				VCOM_CALLTYPE AddDrain(MCObjectHandle slab, WorldPt location, WorldCoord height, double angle) = 0;
		virtual short				VCOM_CALLTYPE ConnectDrains(MCObjectHandle slab, short index1, short index2, short connectionType, double slopeAngle, double splitSlopeAngle) = 0;
		virtual short				VCOM_CALLTYPE AddSlopeValley(MCObjectHandle slab, short index, WorldPt controlPoint, double slope, double edgeHeight) = 0;
		virtual short				VCOM_CALLTYPE GetNumDrains(MCObjectHandle slab) = 0;
		virtual short				VCOM_CALLTYPE GetNumDrainConnections(MCObjectHandle slab) = 0;
		virtual bool				VCOM_CALLTYPE SetDrainHeight(MCObjectHandle slab, short index, double height) = 0;
		virtual double				VCOM_CALLTYPE GetDrainHeight(MCObjectHandle slab, short index) = 0;
		virtual WorldPt				VCOM_CALLTYPE GetDrainLocation(MCObjectHandle slab, short index) = 0;
		virtual bool				VCOM_CALLTYPE SetDrainLocation(MCObjectHandle slab, short index, const WorldPt& location) = 0;
		virtual void                VCOM_CALLTYPE RotateDrain(MCObjectHandle slab, short index, double angle) = 0;
		virtual double				VCOM_CALLTYPE GetDrainDrainageArea(MCObjectHandle slab, short index) = 0;
		virtual MCObjectHandle		VCOM_CALLTYPE GetDrainSymbol(MCObjectHandle slab, short index) = 0;
		virtual bool				VCOM_CALLTYPE SetDrainSymbol(MCObjectHandle slab, short index, MCObjectHandle symbol) = 0;
		virtual short				VCOM_CALLTYPE GetNumDrainSlopeValleys(MCObjectHandle slab, short index) = 0;
		virtual bool				VCOM_CALLTYPE GetDrainSlopeValley(MCObjectHandle slab, short drain, short valley, WorldPt& controlPt, double& slope, double& edgeHeight, bool& heightLocked) = 0;
		virtual void                VCOM_CALLTYPE SetDrainSlopeValley (MCObjectHandle slab, short drain, short valley, WorldPt controlPt, double slope, double edgeHeight, bool lockHeight) = 0;
		virtual short				VCOM_CALLTYPE GetNumDrainConnections(MCObjectHandle slab, short drain) = 0;
		virtual short				VCOM_CALLTYPE GetDrainConnectionIndex(MCObjectHandle slab, short drain, short index) = 0;
		virtual bool				VCOM_CALLTYPE GetDrainConnection(MCObjectHandle slab, short index, short& drain1, short& drain2, short& style, double& angle1, double& angle2) = 0;
		virtual bool				VCOM_CALLTYPE SetDrainConnection(MCObjectHandle slab, short index, short style, double angle1, double angle2) = 0;
		virtual bool				VCOM_CALLTYPE DeleteDrainConnection(MCObjectHandle slab, short index) = 0;
		virtual bool				VCOM_CALLTYPE DeleteSlopeValley(MCObjectHandle, short drain, short index, bool forceDelete) = 0;
		virtual bool				VCOM_CALLTYPE DeleteDrain(MCObjectHandle slab, short index) = 0;
		
		virtual RefNumber	VCOM_CALLTYPE ChoosePluginStyleForTool( TInternalID internalToolID, RefNumber excludeRefNumber, const TXString & title = "", const TXString & message = ""  ) = 0;
		virtual void		VCOM_CALLTYPE ChoosePluginStyleForReplace( MCObjectHandle hObj ) = 0;
		virtual Sint32		VCOM_CALLTYPE GetSymbolDefSubType( MCObjectHandle hObj ) = 0;
		virtual void		VCOM_CALLTYPE SetSymbolDefSubType( MCObjectHandle hObj, Sint32 subType ) = 0;
		virtual bool		VCOM_CALLTYPE GetPluginStyleSymbol( MCObjectHandle hObj, MCObjectHandle & hSymbolDefinition ) = 0;
		virtual EPluginStyleParameter		VCOM_CALLTYPE GetPluginStyleParameterType( MCObjectHandle object, const TXString& paramName ) = 0;
		virtual void						VCOM_CALLTYPE SetPluginStyleParameterType( MCObjectHandle hSymbol, const TXString& paramName, EPluginStyleParameter styleType ) = 0;
		virtual void						VCOM_CALLTYPE SetAllPluginStyleParameters( MCObjectHandle hSymbol, EPluginStyleParameter styleType ) = 0;

		virtual bool			VCOM_CALLTYPE GetLayerEnableCutPlane(MCObjectHandle layer) = 0;
		virtual void			VCOM_CALLTYPE SetLayerEnableCutPlane(MCObjectHandle layer, bool enableCutPlane) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetLayerCutPlane(MCObjectHandle layer) = 0;
		virtual void			VCOM_CALLTYPE SetLayerCutPlane(MCObjectHandle layer, WorldCoord cutPlane) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetWallBelowCutPlaneClass(MCObjectHandle wall) = 0;
		virtual void			VCOM_CALLTYPE SetWallBelowCutPlaneClass(MCObjectHandle wall, InternalIndex belowCutPlaneClass) = 0;
		virtual short			VCOM_CALLTYPE GetTaperedComponent(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetTaperedComponent(MCObjectHandle object, short componentIndex) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord &autoBoundEdgeOffsetOffset) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord autoBoundEdgeOffsetOffset) = 0;
		virtual Boolean			VCOM_CALLTYPE GetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean &masterSnapOnLeft, Boolean &masterSnapOnRight) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean masterSnapOnLeft, Boolean masterSnapOnRight) = 0;

		//Flyover Origin - Interactive Flyover related.
		virtual void		VCOM_CALLTYPE InteractiveViewOperation_GetFlyOverOrigin( ViewPt& curFlyOverOrigin ) = 0; 

		// Resource Manager support
		virtual void			VCOM_CALLTYPE PullDownResourceSetToolBarPopup(short group, VectorWorks::Extension::IResourceManagerContent* content) = 0;
		virtual TXString		VCOM_CALLTYPE PullDownResourceGetSelectedResourceName(short group) = 0;
		virtual void			VCOM_CALLTYPE PullDownResourceSetSelectedResourceName(short group, const TXString& name) = 0;
		virtual void			VCOM_CALLTYPE PullDownResourceLayoutInit(Sint32 dialogID, Sint32 itemID, VectorWorks::Extension::IResourceManagerContent* content) = 0;
		virtual TXString		VCOM_CALLTYPE PullDownResourceLayoutGetSelectedResourceName(Sint32 dialogID, Sint32 itemID) = 0;
		virtual void			VCOM_CALLTYPE PullDownResourceLayoutSetSelectedResourceName(Sint32 dialogID, Sint32 itemID, const TXString& name) = 0;

		virtual double			VCOM_CALLTYPE GetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage) = 0;
		virtual bool			VCOM_CALLTYPE SetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage, double scale, bool redrawImage) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetCellsImageResolution(MCObjectHandle hWorksheet, Sint16 dpiResolution) = 0;
		virtual Sint16			VCOM_CALLTYPE GetWorksheetCellsImageResolution(MCObjectHandle hWorksheet) = 0;

		virtual MCObjectHandle  VCOM_CALLTYPE CreateResourceFolder(const TXString& name, Sint16 resourceType) = 0;
		virtual void			VCOM_CALLTYPE CreateResourceFolderN(const TXString& folderPath, Sint16 resourceType, TVWArray_MCObjectHandle & outFolderPath) = 0;// use / for delimiter of the folderPath parameter( i.e. "Folder1/Folder2" )
		virtual bool			VCOM_CALLTYPE AddResourceTags(MCObjectHandle h, const TXStringArray& arrTags) = 0;
		virtual bool			VCOM_CALLTYPE GetResourceTags(MCObjectHandle h, TXStringArray& arrTags) = 0;
        
        //Set tool help message and the displayed tool name on mode bar
        virtual bool            VCOM_CALLTYPE SetToolHelpMessageAndTitle( const TXString& titleText, const TXString& modeText, const TXString& descriptionText ) = 0;
		
		virtual bool			VCOM_CALLTYPE IsPluginStyle( MCObjectHandle h ) = 0;

        //Indicates whether the active symbol is in the current active document without importing the symbol into the document.
        virtual bool            VCOM_CALLTYPE IsActiveSymbolInCurrentDocument() = 0;

		virtual bool			VCOM_CALLTYPE AddItemToPluginStyle( MCObjectHandle hSymDef, const TXString & itemName, EPluginStyleParameter styleType ) = 0;
		virtual bool			VCOM_CALLTYPE RemoveItemFromPluginStyle( MCObjectHandle hSymDef, const TXString & itemName ) = 0;

		virtual bool			VCOM_CALLTYPE GetDimensionsAssociatedToPlugin( MCObjectHandle hPlugin, TVWArray_MCObjectHandle &dimHandles ) = 0; 
		virtual bool			VCOM_CALLTYPE GetChainThatContainsDimension( MCObjectHandle hDim, MCObjectHandle &hChain ) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateVWObjectFromSplineData(const TVWArray_WorldPt3& controlPoints, const TVWArray_Double& weights, const TVWArray_Double& knots, Sint32 degree, bool isRational, bool isClosed, bool create2D) = 0;

        //Allows setting/getting the default story bound for a plugin that uses the PIO generic story bound introduced in 2016. 
		//The default story bound is accessed using the parametric's format.
		virtual bool            VCOM_CALLTYPE SetDefaultGenericStoryLevelBound( MCObjectHandle hFormat, const SStoryObjectData& data ) = 0;
		virtual bool            VCOM_CALLTYPE GetDefaultGenericStoryLevelBound( MCObjectHandle hFormat, SStoryObjectData& outData ) = 0;

		//For new dual-bound popup (combines top bound and bottom-bound choices).
		virtual void            VCOM_CALLTYPE GetStoryBoundChoiceStringsN( MCObjectHandle story, TXStringArray& outStrings, EStoryLevelPopupBoundType boundType) = 0;
		
		//For unsorted resources in Resource list
		virtual Sint32			VCOM_CALLTYPE AddResourceToListUnsorted(Sint32 listID, MCObjectHandle obj) = 0;
		virtual Sint32			VCOM_CALLTYPE BuildResourceListUnsorted(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems) = 0;

		virtual bool			VCOM_CALLTYPE CreateReference(IFileIdentifier* pFileID) = 0;

		virtual bool			VCOM_CALLTYPE RebuildFileInResourceManager(IFileIdentifier*   pFileID) = 0;
		// inoutOptions - input - list of libraries to be updated (by default all)
		// inoutOptions - output - list of updated libraries (some libraries could be not updated because they are turned off in preferences 
		//														or they don't need update (not changed), or user cancelled the operation)
		virtual bool			VCOM_CALLTYPE RefreshLibrariesInResourceManager(SRefreshLibrariesOptions& inoutOptions) = 0;

	// VW 2017 SP 2
	public:
		virtual void			VCOM_CALLTYPE UpdateStyledObjects( RefNumber styleRefNumber ) = 0;
		virtual void			VCOM_CALLTYPE GetStoryLevels( MCObjectHandle story, TXStringArray& outStrings) = 0;
	
	// VW 2017 SP3
	public:
		virtual void			VCOM_CALLTYPE InitClassOverrideData(InternalIndex classIndex, SViewportClassOverride& outData) = 0;
		virtual void			VCOM_CALLTYPE InitLayerOverrideData(InternalIndex layerIndex, SViewportLayerOverride& outData) = 0;
		virtual void			VCOM_CALLTYPE InitLightOverrideData(InternalIndex lightIndex, SViewportLightOverride& outData) = 0;

	// VW 2018
	public:
		//Exposes STEP export
		virtual bool			VCOM_CALLTYPE ExportSTEP(IFileIdentifier* fileID, bool exportSolidAsSurface) = 0;
		virtual void			VCOM_CALLTYPE GetCurrentWorkspace(VectorWorks::Workspaces::IWorkspaceFile** outWorkspace) = 0;
		virtual bool 			VCOM_CALLTYPE InstallConstraintPlane(TPlanarRefID constrainPlanarRefID, const WorldPt& wptStartPt) = 0;

	
		// Paremetric Style Edit List
		virtual bool			VCOM_CALLTYPE AddItemToPluginStyleEditList( MCObjectHandle hObj, const TXString & itemName, EPluginStyleEditList editListType, const TXString & displayName = "" ) = 0;
		virtual bool			VCOM_CALLTYPE RemoveItemFromPluginStyleEditList( MCObjectHandle hObj, const TXString & itemName ) = 0;
		virtual bool			VCOM_CALLTYPE GetPluginStyleEditListType( MCObjectHandle hObj, const TXString& paramName, EPluginStyleEditList & editListTyle, TXString & displayName ) = 0;
        virtual MCObjectHandle  VCOM_CALLTYPE OffsetPolyClosed(MCObjectHandle h, double offset, bool smoothConers) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateImgFromSymbol( const TXString & symbolName, SymbolImgInfo& imgInfoInout) = 0;

        virtual void            VCOM_CALLTYPE GetSelInsertsInWall( MCObjectHandle hObj, TVWArray_MCObjectHandle& selInserts) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CreateFillSpace(MCObjectHandle owner) = 0;
		virtual short 			VCOM_CALLTYPE CountFillSpaces(MCObjectHandle h) = 0;
		virtual MCObjectHandle 	VCOM_CALLTYPE GetFillSpace(MCObjectHandle h, short index) = 0;

		//Gets proxy information for cURL requests
		virtual bool 			VCOM_CALLTYPE GetCurlProxyInfo(TXString& outProxyType, TXString& outAddress, Sint32& outPort, TXString& outUsername, TXString& outPassword) = 0;

		virtual TXString		VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat) = 0;
		virtual TXString		VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat, const SDateTimeData& dateTimeData) = 0;
		virtual TXString		VCOM_CALLTYPE GetLocalSystemDateTimeString(EDateFormat dateFormat, EInfoFormat infoFormat) = 0;
		virtual bool			VCOM_CALLTYPE GetDateTimeIntlData(TDateTimeIntlData& outDateTimeIntlData) = 0;

		virtual void			VCOM_CALLTYPE SetHotSpotColor(HotSpotRefID inHotSpotID, GSColor color) = 0;
		virtual void			VCOM_CALLTYPE DrawHotSpots() = 0;

		virtual void			VCOM_CALLTYPE EnterObjectGroup(MCObjectHandle hGroup, const EEditPartContext& context = EEditPartContext::Generically2d) = 0;

		// Function for use inside a resource selector filter, when filtering for a symbol instance replacement.
		// This provides a check that isn't otherwise to plug-in developers, relating to preventing a
		// circular reference caused by replacing a symbol during the edit of a symbol. 
		// If IsSymDefUsedInEditContext returns true, the symbol definition is NOT allowed as a replacement.
		virtual bool			VCOM_CALLTYPE IsSymDefUsedInEditContext (MCObjectHandle hSymDef) = 0;

		virtual bool			VCOM_CALLTYPE GetCatalogPath( MCObjectHandle hObj, EFolderSpecifier & folderSpec, TXString & relativePath ) = 0;
		virtual bool			VCOM_CALLTYPE SelectPluginCatalog( MCObjectHandle hSymDef ) = 0;
		virtual bool			VCOM_CALLTYPE SelectItemFromPluginCatalog( MCObjectHandle hObj,  const TXString & catName = "", std::function<TXString(const TXString & id, EEmptyHandling opt)> columnNamesLocalizer = nullptr ) = 0;
		virtual bool			VCOM_CALLTYPE AplyFirstCatalogItem( MCObjectHandle hObj,  const TXString & catName = "" ) = 0;
		virtual bool			VCOM_CALLTYPE IsCatalogParameter( MCObjectHandle hObj, const TXString & paramName ) = 0;
		virtual void			VCOM_CALLTYPE SetUseCatalogItem( MCObjectHandle hObj, const bool & useCatItem ) = 0;
		virtual bool			VCOM_CALLTYPE GetUseCatalogItem( MCObjectHandle hObj ) = 0;
		virtual void			VCOM_CALLTYPE SetCatalogItemByStyle( MCObjectHandle hObj, const bool & byStyle ) = 0;
		virtual bool			VCOM_CALLTYPE GetCatalogItemByStyle( MCObjectHandle hObj ) = 0;


		virtual Boolean			VCOM_CALLTYPE GetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction &function) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction function) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE FitExtrudeToObjects(MCObjectHandle hExtrude, bool isTopFit, EFitExtrudeToObjectsOption boundOption, double defaultHeight, TVWArray_MCObjectHandle clippingHandleArray, EFitExtrudeToObjectsRoofAndSlabOption roofSlabOption) = 0;

		// Resource Manager support
		// folderPath - input - path relative to Libraries folder; path separators are '\' 
		// example, Defaults\folder1\folder2
		// pOutFileID - output in case of success - downloaded file on the local drive
		virtual EDownloadErrors VCOM_CALLTYPE DownloadLibraryFile(ELibrariesID libraryID, const TXString& folderPath, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params) = 0;
		virtual EDownloadErrors VCOM_CALLTYPE DownloadLibraryFile(ELibrariesID libraryID, EFolderSpecifier folderID, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params) = 0;
        virtual MCObjectHandle	VCOM_CALLTYPE GetWallEndCapFootPrint(MCObjectHandle theWall, bool atStart) = 0;

		virtual bool            VCOM_CALLTYPE SimplifyMesh(MCObjectHandle meshHandle, float quality) = 0;

		virtual bool			VCOM_CALLTYPE SetToolPt2D(Sint32 inIndex, const WorldPt& inToolPoint) = 0;
		virtual bool			VCOM_CALLTYPE SetToolPt3D(Sint32 inIndex, const WorldPt3& inToolPoint) = 0;

		virtual short			VCOM_CALLTYPE GetObjTypeProperties(short objectType) = 0;

		virtual bool			VCOM_CALLTYPE GetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage) = 0;
		virtual void			VCOM_CALLTYPE SetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage, bool show, bool redrawImage) = 0; 
		
		virtual void			VCOM_CALLTYPE DisplayDocumentPreferences(EDocumentPrefsTab tabToSelect) = 0;

		virtual size_t			VCOM_CALLTYPE GetResourceStringTableSize(const char* resIdentifier) = 0;
		
		virtual bool			VCOM_CALLTYPE UpdateImageControlUsingFullFilePath(Sint32 dialogID, Sint32 controlID, IFileIdentifier* imgFileID) = 0;
		virtual void			VCOM_CALLTYPE GetReferencedFilesInfo (TVWArray_ReferencedFileInfo& outRefFilesInfo) = 0;
		virtual void			VCOM_CALLTYPE DeleteReferencedFiles (TVWArray_ReferencedFileInfo& outRefFilesInfo, const SDeleteFileOptions fileOptions) = 0;

		// For Multiview controller
		virtual void			VCOM_CALLTYPE SetFocusOnSelectedViewPane(bool bMakeItActive = true, bool bUpdateUI = false) = 0;

		virtual void			VCOM_CALLTYPE GetPageBoundsN(MCObjectHandle hLayer, WorldRect& bounds) = 0;
		virtual void			VCOM_CALLTYPE TrackToolN(MCObjectHandle& overObject, MCObjectHandle& overSubObject, short& overPart, SintptrT& code) = 0;

	// VW 2018 SP 1
	public:
		virtual void			VCOM_CALLTYPE SetWorksheetCellCOBieValue(MCObjectHandle worksheet, const ViewPt& cell, const TXString& formula) = 0;
        
    // VW 2018 SP 3
    public:
        virtual void            VCOM_CALLTYPE GetSlabHolesAndTheirMiters(MCObjectHandle hSlab, TVWArray_MCObjectHandle& outHolesArray, TVWArray_SizeT& outMitersArray) = 0;

	// VW 2019
	public:
		virtual short			VCOM_CALLTYPE GetDlgCtrlWidthStdChar(const TXString& str) = 0;	// Returns the width in standard characters (widthInStdChar) for dialog control creation. E.g. CreateStaticText

		virtual bool            VCOM_CALLTYPE ExportResourceList(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID = nullptr, bool suppressDialogs = false) = 0;
		virtual bool            VCOM_CALLTYPE ExportResourceListN(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID = nullptr, TImportResourceConflictCallbackProcPtr conflictCallback = nullptr) = 0;

		virtual TXString		VCOM_CALLTYPE GetHierarchicalListBrowserRowContainerPath(Sint32 dialogID, Sint32 componentID, Sint32 rowIndex) = 0;
		virtual bool			VCOM_CALLTYPE SelectInResourceManager( MCObjectHandle requestedResource ) = 0;

		
		// These two finctions are for data tag moving system. If the system is turned off, this means that data tag will not be moved
		// when tagged object is moved. BeginMultipleMove starts data tag moving system. EndMultipleMove stops data tag moving system.
		virtual bool            VCOM_CALLTYPE BeginMultipleMove() = 0;
		virtual bool            VCOM_CALLTYPE EndMultipleMove() = 0;
		
		// Get Wall unit vector for a given rotation center
		virtual bool			VCOM_CALLTYPE GetWallAngleVector(const MCObjectHandle& wallHandle, const WorldPt& rotationCenter, WorldPt& wallVector) = 0;

		// Convert a dimension value to a string using the specified custom unit. If the unit is NULL or not specified, the conversion will be done using the document units.
		virtual void			VCOM_CALLTYPE CoordToDimStringInUnits(WorldCoord value, VectorWorks::Units::IVWUnits* dimUnit, TXString& str) = 0;
		virtual void			VCOM_CALLTYPE DoubleToStringInUnits(TNumStyleClass inNumStyle, Byte inAccuracy, Byte inFormat, double_param inDouble, VectorWorks::Units::IVWUnits* dimUnit, TXString& outString) = 0;
		//

		// Determine the number of Annotations associated with a PDF page. 
		virtual size_t			VCOM_CALLTYPE GetPDFAnnotationsCount(MCObjectHandle object) = 0;

		// Line type reengineering new functions. Instead of changing existing functions, new ones are being added. The difference is that
		// they use the internal index of line type containing the dash pattern instead of a dash index, since the task is removing the dash pattern table.
		// In cases where the original calls used a negative dash index, the new ones use a negative internal index.

		virtual Boolean			VCOM_CALLTYPE GetCumulativeDashPat(InternalIndex lineTypeRef, DashPatType& outDashPat) = 0;		//replacement for GetDashPat - does NOT give pattern suitable for use in CreateOrFindSimpleLineType. 
		virtual Boolean			VCOM_CALLTYPE GetSimpleLineTypeDefinition(const InternalIndex lineTypeRef, DashPatDef& outDashPat) = 0;	//new, retrieves dash pattern suitable for use in CreateOrFindSimpleLineType
		virtual InternalIndex	VCOM_CALLTYPE CreateOrFindSimpleLineTypeDefinition(const DashPatDef& inDashPat) = 0;	//new, returns the positive InternalIndex of a simple line type, given a dash pattern. Will look in default content and import if necessary. Will create line type if not found.
		virtual InternalIndex	VCOM_CALLTYPE GetDashLineStyle(bool scaleWithThick, const std::vector<double>& theVectors) = 0; //replacement for GetDashStyleIndex
		virtual Boolean			VCOM_CALLTYPE SetDashLineTypeName(InternalIndex lineTypeRef, const TXString& dashStyleName) = 0; //replacement for SetDashStyleName
		virtual TXString		VCOM_CALLTYPE GetDashLineTypeName(InternalIndex lineTypeRef) = 0; //replacement for GetDashStyleName
		virtual Boolean			VCOM_CALLTYPE GetDLComponentPenStylesN(Sint16 index, InternalIndex& outPenStyleLeft, InternalIndex& outPenStyleRight) = 0; //replacement for GetDLComponentPenStyles
		virtual Boolean			VCOM_CALLTYPE SetDLComponentPenStylesN(Sint16 index, InternalIndex penStyleLeft, InternalIndex penStyleRight) = 0; //replacement for SetDLComponentPenStyles
		virtual Boolean			VCOM_CALLTYPE InsertNewDLComponentN(Sint16 beforeIndex, WorldCoord width, Sint32 fill, Uint8 penWeightLeft, Uint8 penWeightRight, InternalIndex penStyleLeft, InternalIndex penStyleRight) = 0; //replacement for InsertNewDLComponent
		virtual Boolean			VCOM_CALLTYPE InsertNewComponentN(MCObjectHandle object, short beforeComponentIndex, WorldCoord width, Sint32 fill, Uint8 leftPenWeight, Uint8 rightPenWeight, InternalIndex leftPenStyle, InternalIndex rightPenStyle) = 0; //replacementfor InsertNewComponent
		virtual Boolean			VCOM_CALLTYPE IsDashLineStyle(InternalIndex lineStyle) = 0; //new, replaces validation provided by kludge calls kKludgeGetDashStyleIndexFromLineType and kKludgeGetLineTypeFromDashIndex

		// Line type reengineering new functions for worksheet cell borders. Instead of using dash index for cell border style, these use InternalIndex.
		// In cases where the original calls used a negative dash index, the new ones use a negative internal index.
		virtual void			VCOM_CALLTYPE GetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& cell, TCellBorderRefNum& top, TCellBorderRefNum& left, TCellBorderRefNum& bottom, TCellBorderRefNum& right) = 0; //replacement for GetWSCellAllBorders
		virtual void			VCOM_CALLTYPE SetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, TCellBorderRefNum top, TCellBorderRefNum left, TCellBorderRefNum bottom, TCellBorderRefNum right, TCellBorderRefNum insideVert, TCellBorderRefNum insideHorz) = 0; //replacement for SetWSCellAllBorders
		virtual void			VCOM_CALLTYPE SetWSCellBottomBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellBottomBorder
		virtual void			VCOM_CALLTYPE SetWSCellInsideHorizBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellInsideHorizBorder
		virtual void			VCOM_CALLTYPE SetWSCellInsideVertBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellInsideVertBorder
		virtual void			VCOM_CALLTYPE SetWSCellLeftBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellLeftBorder
		virtual void			VCOM_CALLTYPE SetWSCellOutlineBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellOutlineBorder
		virtual void			VCOM_CALLTYPE SetWSCellRightBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellRightBorder
		virtual void			VCOM_CALLTYPE SetWSCellTopBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) = 0; //replacement for SetWSCellTopBorder

		// Line type reengineering new functions to get a "pseudo" index for a dashed line style's internal index or vice versa.
		// These allow plugins to store an index rather than a reference number. The index is based on counting the
		// line types in a file and is not guaranteed to produce the same line in different files, nor when reverse translated.
		// These indices are substitutes for the old dash index (and like the old, are negative values for dashed line types, as are the internal index arguments).
		virtual bool			VCOM_CALLTYPE GetPseudoDashIndexFromDashLineType(const InternalIndex lineStyle, Sint16& pseudoIndex) = 0; 
		virtual bool			VCOM_CALLTYPE GetDashLineTypeFromPseudoDashIndex(const Sint16 pseudoIndex, InternalIndex& lineStyle) = 0;
		virtual void			VCOM_CALLTYPE BeginMultiplePseudoDashIndexConvert() = 0;
		virtual void			VCOM_CALLTYPE EndMultiplePseudoDashIndexConvert() = 0;

		// End of line type reengineering new functions.

		virtual void			VCOM_CALLTYPE CreateSearchEditBox(Sint32 dialogID, Sint32 itemID, const TXString& promptText, short widthInStdChar) = 0;
        
        // create a symbol definition only for dialog display control
        virtual MCObjectHandle  VCOM_CALLTYPE CreateSymbolDefinitionForDisplayControl(TXString& inoutName) = 0;

        //New functions that use UuidStorage to get Uuids, functionality is identical to GetObjectByUuid and GetObjectUuid
        virtual MCObjectHandle  VCOM_CALLTYPE GetObjectByUuidN(const UuidStorage& uuid) = 0;
        //Returns false if the object does not have a Uuid
        virtual bool                VCOM_CALLTYPE GetObjectUuidN(MCObjectHandle h, UuidStorage& uuid) = 0;

		// T01818� Planar Swap Graphics for Hybrid Objects

		// Sets the specified 2D component group of a symbol definition or plug-in object
		virtual ESetSpecialGroupErrors	VCOM_CALLTYPE Set2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hGroup, EViewTypes component) = 0;
		//Gets the specified 2D component group of a symbol definition or plug-in object
		virtual MCObjectHandle	VCOM_CALLTYPE Get2DComponentGroup(MCObjectHandle hObject, EViewTypes component) = 0;

		// Adds the object to the specified 2D component group of a symbol definition or plug-in object
		virtual ESetSpecialGroupErrors	VCOM_CALLTYPE AddObjectTo2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hObjectToAdd, EViewTypes component) = 0;

		//Sets the specified 2D component of a worksheet cell image
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageComponent(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, EImageViewComponent component) = 0;
		// Gets the specified 2D component of a worksheet cell image
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageComponent(MCObjectHandle worksheet, short row, short column, EImageViewComponent& outComponent) = 0;
		
		// Gets the 2D component that is shown in Top/Plan view for a symbol definition or plug-in object
		virtual bool			VCOM_CALLTYPE SetTopPlan2DComponent(MCObjectHandle hObject, ETopPlanViewComponent component) = 0;
		// Gets the 2D component that is shown in Top/Plan view for a symbol definition or plug-in object
		virtual ETopPlanViewComponent VCOM_CALLTYPE GetTopPlan2DComponent(MCObjectHandle hObject) = 0;

		// Sets whether a 3D object in a symbol definition or plug-in object is shown when the specified 2D 
		virtual bool			VCOM_CALLTYPE SetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component, bool isVisible) = 0;
		// Gets whether a 3D object in a symbol definition or plug-in object is shown when the specified 2D 
		virtual bool			VCOM_CALLTYPE GetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component) = 0;

		// Sets whether the opposite view graphics are mirrored for empty 2D components of a symbol definition or plug-in object
		virtual bool			VCOM_CALLTYPE SetMirrorEmpty2DComponents(MCObjectHandle hObject, bool doMirror) = 0;
		// Gets whether the opposite view graphics are mirrored for empty 2D components of a symbol definition or plug-in object 
		virtual bool			VCOM_CALLTYPE GetMirrorEmpty2DComponents(MCObjectHandle hObject) = 0;

		// Generates the specified 2D component of a symbol definition or plug-in object from the 3D component
		virtual bool			VCOM_CALLTYPE Generate2DFrom3DComponent(MCObjectHandle hObject, EViewTypes component, TRenderMode renderMode, ELevelsOfDetail levelOfDetails) = 0;

		// T01818� Planar Swap Graphics for Hybrid Objects


		// Get information about the active symbol
		virtual TXString		VCOM_CALLTYPE GetActiveSymbolName() = 0;
		virtual bool			VCOM_CALLTYPE GetFilePathForActiveSymbolInOpenDocument(IFileIdentifier** ppOutFileID, bool& outFolderIsSet) = 0;
		//This allows the user to assign a Uuid to a handle after the handle has been created.  Use with care!
		//If we assign a uuid that already exists somewhere in the document, there will be duplicates. TUuidCheckTable 
		//creates a list of every Uuid in the document so we can check for those duplicates.  Just be careful not to let 
		//the table get stale, create a new one if the document has changed.  
		virtual bool			VCOM_CALLTYPE AssignUuidToHandle(MCObjectHandle h, const UuidStorage& uuid, TDocumentUuidsCheckTable& checkTable) = 0;

		virtual void			VCOM_CALLTYPE CreateEditPassword(Sint32 dialogID, Sint32 itemID, short widthInStdChar) = 0;
		//This lets the user assign text tags to an object
		virtual bool			VCOM_CALLTYPE AddObjectTags(MCObjectHandle h, const TXStringArray& arrTags) = 0;
		virtual bool			VCOM_CALLTYPE GetObjectTags(MCObjectHandle h, TXStringArray& arrTags) = 0;

		virtual bool			VCOM_CALLTYPE ShowChooseDateFormatDialog(EDateTimeFormat& inOutDateFormat) = 0;
        
        virtual MCObjectHandle  VCOM_CALLTYPE CreateTemporaryCustomObject(const TXString& name, const WorldPt& location, double_param angle = 0.0) = 0;
        virtual MCObjectHandle  VCOM_CALLTYPE CreateTemporaryCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix) = 0;
        virtual MCObjectHandle  VCOM_CALLTYPE CreateTemporaryCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix) = 0;

		virtual void			VCOM_CALLTYPE UpdatePIOFromStyle( MCObjectHandle h ) = 0;
		virtual void			VCOM_CALLTYPE GetPageMargins(MCObjectHandle hLayer, double& left, double& right, double& bottom, double& top) = 0;

		virtual Boolean			VCOM_CALLTYPE CreateLayerPullDownMenu(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar) = 0;
        
        // SP2 VW2019
        virtual WorldPt3		VCOM_CALLTYPE Project3DPointOnPlane(const WorldPt3& given3DPoint, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal, const WorldPt3& projectionDir) = 0;
	
	// VW 2020
	public:
		//Displays a summary of Nodes memory usage for the actively opeaned File, 
		//a detailed report can be downloaded by clicking on Dump to CSV button in the dialog
		virtual void			VCOM_CALLTYPE ShowDetailedMemoryInfoDlg() = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetCustomObjectProfileGroupInAux(MCObjectHandle objectHand) = 0;

		virtual bool			VCOM_CALLTYPE EditSymbolMarkersDialog(const TXString& dialogTitle, const TXString& contextHelpID, TXString& inOutStartMarkerSymName, TXString& inOutEndMarkerSymName) = 0;

		virtual bool			VCOM_CALLTYPE ImportParasolidXT(IFileIdentifier* pFileID, ViewPt* position=nullptr) = 0;

		virtual bool			VCOM_CALLTYPE CreateSearchablePulldownMenu(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar) = 0;
		virtual bool			VCOM_CALLTYPE InsertStaticItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec, bool shouldUpdate = true) = 0;
		virtual bool			VCOM_CALLTYPE InsertItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec, bool shouldUpdate = true) = 0;
		virtual bool			VCOM_CALLTYPE InsertChildItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& parentIDStr, const TXString& itemToolTip, const TXString& itemImageSpec, bool shouldUpdate = true) = 0;
		virtual void			VCOM_CALLTYPE ClearChoicesFromSearchablePulldown(Sint32 dialogID, Sint32 controlID, bool clearStaticItems) = 0;
		virtual TXString		VCOM_CALLTYPE GetActiveIDStrFromSearchablePulldown(Sint32 dialogID, Sint32 controlID) = 0;
		virtual bool			VCOM_CALLTYPE SetActiveIDStrInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& activeIDStr) = 0;
		virtual bool			VCOM_CALLTYPE GetDisplayNameFromIDStrInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& idStrToFind, TXString& outName) = 0;
		virtual bool			VCOM_CALLTYPE GetIDStrFromDisplayNameInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& nameToFind, TXString& outIDStr) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE GetWallRecessGeometryGroup(MCObjectHandle objectHand) = 0;
		virtual bool			VCOM_CALLTYPE SetWallRecessGeometryGroup(MCObjectHandle objectHand, MCObjectHandle hNewGroup) = 0;

		virtual Boolean VCOM_CALLTYPE EnableListBrowserItem3StateCheckBox(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, bool /*bEnable*/ = true) = 0;
		virtual Boolean VCOM_CALLTYPE IsListBrowserItem3StateCheckBoxEnabled(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex) = 0;

		// This function is similar to EndUndoEvent, but it ends the current event and removes it from the table. Refer to the SDK Manual for details.
		virtual Boolean 		VCOM_CALLTYPE EndAndRemoveUndoEvent() = 0;
		
		// This function clears the entire undo table. The user can no longer undo or redo their actions. Refer to the SDK Manual for details.
		virtual void 			VCOM_CALLTYPE ClearUndoTableDueToUnsupportedAction() = 0;

		virtual void			VCOM_CALLTYPE AlertDialogWithHyperlink(const TXString& message, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink) = 0;

		// Sets the color of a list browser item text by color tint
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextColorN(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, EUiControlTextTint colorTint) = 0;

		// This function will return the RefNumbers of wall inserts bounding the given space object.
		virtual bool			VCOM_CALLTYPE GetSpaceWallInserts(MCObjectHandle space, bool includeExteriorWallInserts, bool includeInteriorWallInserts, std::vector<InternalIndex> &wallInserts) = 0;
		
		virtual bool			VCOM_CALLTYPE IsListBrowserExternalSortEnabled(Sint32 dialogID, Sint32 controlID) const = 0;
		virtual void			VCOM_CALLTYPE EnableListBrowserExternalSort(Sint32 dialogID, Sint32 controlID, bool /*bEnable*/ = true) = 0;

		virtual bool 			VCOM_CALLTYPE TesselateObjectN(TTesselator pTess, const STesselateOptions& options, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv) = 0;

		virtual void			VCOM_CALLTYPE Get2DComponentLocation(MCObjectHandle hObject, EViewTypes component, bool &onBoundsCube, double &offset) = 0;
		virtual bool			VCOM_CALLTYPE Set2DComponentLocation(MCObjectHandle hObject, EViewTypes component, bool onBoundsCube, double offset) = 0;
		virtual EObjectCutPlane VCOM_CALLTYPE GetHorizontalSectionCutPlane(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetHorizontalSectionCutPlane(MCObjectHandle hObject, EObjectCutPlane objectCutPlane) = 0;
		virtual EObjectCutPlane VCOM_CALLTYPE GetVerticalSectionCutPlane(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetVerticalSectionCutPlane(MCObjectHandle hObject, EObjectCutPlane objectCutPlane) = 0;
		virtual bool			VCOM_CALLTYPE Get2DComponentsByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE Set2DComponentsByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetMirrorEmpty2DComponentsByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetMirrorEmpty2DComponentsByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetTopPlan2DComponentByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetTopPlan2DComponentByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetHorizontalSectionCutPlaneByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetHorizontalSectionCutPlaneByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetVerticalSectionCutPlaneByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetVerticalSectionCutPlaneByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		
		virtual bool			VCOM_CALLTYPE SetLayerName(MCObjectHandle hLayer, const TXString& layerName, bool updateLayerDependencies) = 0;
		virtual bool			VCOM_CALLTYPE SetSheetLayerTitle(MCObjectHandle hLayer, const TXString& sheetTitle) = 0;

		virtual void			VCOM_CALLTYPE AlertCriticalWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink) = 0;
		virtual void			VCOM_CALLTYPE AlertInformWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink, bool minorAlert = false, const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "") = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE DuplicateObjectWithNotification(MCObjectHandle h) = 0;

	// VW 2021
	public:
		virtual Boolean 		VCOM_CALLTYPE SetHorizontalDimensionConstraint(MCObjectHandle obj1, const WorldPt& pt1, const WorldPt& pt2, WorldCoord distance, ViewCoord offset) = 0;
		virtual bool			VCOM_CALLTYPE SetVerticalDimensionConstraint(MCObjectHandle hObj, const WorldPt& pt1, const WorldPt& pt2, WorldCoord distance, ViewCoord offset) = 0;
		virtual Boolean 		VCOM_CALLTYPE DeleteDimensionConstraints(MCObjectHandle obj1) = 0;

		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec) = 0;
		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon) = 0;

		virtual bool			VCOM_CALLTYPE InsertStaticItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon, bool shouldUpdate = true) = 0;
		virtual bool			VCOM_CALLTYPE InsertItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon, bool shouldUpdate = true) = 0;
		virtual bool			VCOM_CALLTYPE InsertChildItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& parentIDStr, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon, bool shouldUpdate = true) = 0;

		virtual void			VCOM_CALLTYPE EnableItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, bool enableItem) = 0;

		virtual InternalName	VCOM_CALLTYPE CheckAndResolveDuplicateInternalName(const InternalName& inName) = 0;
		virtual bool			VCOM_CALLTYPE GetVWResourceStringKeys(const char* resourceIdentifier, std::vector<TXString>& outvecKeys) = 0;

		virtual bool			VCOM_CALLTYPE CreateClassPullDownMenuN(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, bool bShowDefaultStaticItems = true) = 0;
		virtual bool			VCOM_CALLTYPE CreateLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) = 0;
		virtual bool			VCOM_CALLTYPE CreateSheetLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) = 0;
		virtual bool			VCOM_CALLTYPE CreateDesignLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) = 0;

		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip) = 0;
		virtual void			VCOM_CALLTYPE PixelLengthToLineWeight(short inPixels, short& outLineWeightMils) = 0;
		virtual void			VCOM_CALLTYPE LineWeightToPixelLength(short inLineWeightMils, short& outPixels) = 0;
		virtual bool			VCOM_CALLTYPE ShowFloatingDataBar(bool bShow) = 0;
		virtual Boolean			VCOM_CALLTYPE IsDesignLayerSectionViewport(MCObjectHandle hObj) = 0;
		virtual void			VCOM_CALLTYPE UpdateSLVPForOnlyAnnotationsChange(MCObjectHandle inhSLVP, const WorldRect& inwrBoxBefore_SLVP, const WorldRect& inwrBoxBefore_Annots) = 0;

		virtual MCObjectHandle  VCOM_CALLTYPE GetBoundFromWalls(TVWArray_MCObjectHandle & wallList, const TXString& UUID, int columnsAndPilastersEnum, MCObjectHandle existingProfil) = 0;

		// This group of methods allows to make conversion between world and page values using the given scale parameters regardless of the current active layer scale;
		// paperScale represents the desired layer scale. If it is 1:48, for example, paperScale == 48.0;
		// photographicScale ==  1, scaling is 100% (no scaling)
		// photographicScale == .5, scaling is 200% 
		virtual double			VCOM_CALLTYPE CoordLenToPageLenScale(WorldCoord coordLength, double paperScale, double photographicScale) = 0;
		virtual double			VCOM_CALLTYPE CoordLenToPagePtsScale(WorldCoord coordLength, double paperScale, double photographicScale) = 0;
		virtual double			VCOM_CALLTYPE PageLenToCoordLenScale(double pageLength, double paperScale, double photographicScale) = 0;
		virtual double			VCOM_CALLTYPE PagePtsToCoordLenScale(double pagePoints, double paperScale, double photographicScale) = 0;
		virtual void			VCOM_CALLTYPE ForEachObjectAtPoint( short traverseWhat, const WorldPt& pt, WorldCoord dRadius, std::function<bool(MCObjectHandle h)> callbackLambda) = 0;
		
		virtual MCObjectHandle  VCOM_CALLTYPE CreateMaterial(const TXString& name, bool isSimpleMaterial) = 0;
		virtual bool			VCOM_CALLTYPE GetObjectMaterialName(MCObjectHandle objectHandle, TXString& outMaterialName) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectMaterialHandle(MCObjectHandle objectHandle) = 0;
		virtual bool			VCOM_CALLTYPE SetObjectMaterialHandle(MCObjectHandle objectHandle, MCObjectHandle materialHandle) = 0;
		virtual bool			VCOM_CALLTYPE IsMaterialSimple(MCObjectHandle materialHandle) = 0;
		virtual InternalIndex   VCOM_CALLTYPE GetMaterialTexture(MCObjectHandle materialHandle) = 0;
		virtual bool			VCOM_CALLTYPE SetMaterialTexture(MCObjectHandle materialHandle, InternalIndex textureIndex) = 0;
		virtual InternalIndex	VCOM_CALLTYPE GetMaterialFillStyle(MCObjectHandle materialHandle) = 0;
		virtual bool			VCOM_CALLTYPE SetMaterialFillStyle(MCObjectHandle materialHandle, InternalIndex fillStyle) = 0;
		virtual bool			VCOM_CALLTYPE IsMaterialFillStyleByClass(MCObjectHandle materialHandle) = 0;
		virtual bool			VCOM_CALLTYPE SetMaterialFillStyleByClass(MCObjectHandle materialHandle, bool isByClass) = 0;
		virtual bool			VCOM_CALLTYPE GetMaterialFillColor(MCObjectHandle materialHandle, ObjectColorType& fillColors) = 0;
		virtual bool			VCOM_CALLTYPE SetMaterialFillColor(MCObjectHandle materialHandle, const ObjectColorType& fillColors) = 0;
		virtual bool			VCOM_CALLTYPE SetSubmaterialsInMaterial(MCObjectHandle materialHandle, const CompoundSubmaterialDataVector& dataVector) = 0;
		virtual bool			VCOM_CALLTYPE GetSubmaterialsFromMaterial(MCObjectHandle materialHandle, CompoundSubmaterialDataVector& dataVector) = 0;
		virtual bool			VCOM_CALLTYPE AddSubmaterialToMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName, double fraction = 1.0, bool makePrimary = false) = 0;
		virtual bool			VCOM_CALLTYPE RemoveSubmaterialFromMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName) = 0;
		virtual bool			VCOM_CALLTYPE UpdateSubmaterialInMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName, double fraction = 1.0, bool makePrimary = false) = 0;

		virtual void			VCOM_CALLTYPE SetExcludeObjectFromDataVisualization(MCObjectHandle objectHandle, Boolean exclude) = 0;

		// this function must be used during the Regenerate event when kObjXPropPreserveContents Is defined
		// it will delete the regenerable sub objects from child list of the parametric, emulating the standard behaviour
		virtual void			VCOM_CALLTYPE DeleteRegenerableSubObjects ( MCObjectHandle hParametric ) = 0;

		virtual Boolean			VCOM_CALLTYPE GetComponentMaterial(MCObjectHandle object, short componentIndex, InternalIndex &material) = 0;
		virtual Boolean			VCOM_CALLTYPE SetComponentMaterial(MCObjectHandle object, short componentIndex, InternalIndex material) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE CustomObjectGetPathProxy(MCObjectHandle inPathObject, ObjectPropID inPurpose) = 0; // returns a duplicate you must delete

		virtual void			VCOM_CALLTYPE EditPluginStyle(MCObjectHandle hStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetWorksheetCellFlagChanged(MCObjectHandle worksheet, const ViewPt& cell) = 0;
		virtual bool			VCOM_CALLTYPE GetWorksheetCellFlagInvalid(MCObjectHandle worksheet, const ViewPt& cell) = 0;

		virtual bool			VCOM_CALLTYPE CreateResourceTextPopup(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar) = 0;
		virtual double			VCOM_CALLTYPE GetRotationAroundAxis(MCObjectHandle hObject, MajorAxisSpec aroundAxis) = 0;
		virtual void			VCOM_CALLTYPE TransformObject(MCObjectHandle hObject, const TransformMatrix& transformMatrix) = 0;
		virtual Boolean 		VCOM_CALLTYPE AddBothSwapLayerProperties(MCObjectHandle h) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWallsAndApplyOffset(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum, double OffsetDistance, bool bExcludePiosNiches = true) = 0;

		virtual bool			VCOM_CALLTYPE GetClassByStyle(MCObjectHandle h) = 0;
		virtual bool			VCOM_CALLTYPE SetClassByStyle(MCObjectHandle h, bool byStyle) = 0;

		virtual double			VCOM_CALLTYPE GetMaterialArea(MCObjectHandle hObject, const TXString& materialName) = 0;
		virtual double			VCOM_CALLTYPE GetMaterialVolume(MCObjectHandle hObject, const TXString& materialName) = 0;
		virtual void            VCOM_CALLTYPE ComposeObjectHandles(TVWArray_MCObjectHandle& objsToComposeArray, bool bInsert, TVWArray_MCObjectHandle& composedObjsArray) = 0;
		virtual bool            VCOM_CALLTYPE GetProjectName(TXString& outName) = 0;
		virtual MCObjectHandle	VCOM_CALLTYPE DuplicateObjectIgnoreConstraints(MCObjectHandle h) = 0;
		virtual WorldCoord      VCOM_CALLTYPE GetStoryObjectDataBoundHeight(const SStoryObjectData& storyData, MCObjectHandle hContainer) = 0;
		virtual void			VCOM_CALLTYPE ForEachMaterial(bool onlyUsed, std::function<void(MCObjectHandle h)> callbackLambda ) = 0;

	// VW2022
	public:
		// Create an extended (syntax coloring) text box. 
		virtual void VCOM_CALLTYPE CreateEditColorText(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines) = 0;
		// The 'strConfig' parameter configures the control by key-value pairs configuring the control.
		// It can point to a file full path containing configuration for reusability
		// More info of the choices can be found in the developer.vectorworks.net
		virtual bool VCOM_CALLTYPE SetEditColorTextStyle(Sint32 dialogID, Sint32 itemID, const TXString& strConfig, VWVariant* outResult = nullptr, VWVariant* outParam2 = nullptr) = 0;

		virtual EWallPathType	VCOM_CALLTYPE GetWallPathType(MCObjectHandle wall) = 0;

		virtual void			VCOM_CALLTYPE AddToolEditTextMethodN(const TXString& label, const TXString& value, Sint32 textWidth) = 0;

		virtual bool			VCOM_CALLTYPE RunWorksheetSelectFunctionLayout(bool forUseInDatabase, TXString& inoutSelection, EWorksheetSelectFunctionLayoutMode mode) = 0;

		// Compile the given Worksheet criteria/expression and return the binary code of it
		// The handle is a pointer of a pointer to the memory: void* memory = *h and size = gVWMM->GetHandleSize( h )
		// You must delete the handle with gVWMM->DisposeHandle
		// You must specify the context of the criteria expression. Universal expression or localized expression
		// Example: expression = "Area()/2" // executes the Area() function and divides it in half; note: no '=' prefix
		// UseVWFC::Tools::WSCriteriaExpression for convenience
		virtual Handle			VCOM_CALLTYPE CompileCriteriaExpression(const TXString& criteria, std::function<void(ECriteriaExpressionError err, size_t errOffset)> onErrorCallback, EExpressionContext context = eLocal) = 0;
		virtual bool			VCOM_CALLTYPE DecompileCriteriaExpression(Handle compiledCriteria, TXString& outCriteria) = 0;

		// Executes a compiled worksheet expression on an object, similarly how it calculates a cell value for a database row in the worksheets.
		// Use gSDK->CompileCriteriaExpression to compile an expression or create a handle with pre-precompiled expression with gVWMM->NewHandle
		// UseVWFC::Tools::WSCriteriaExpression for convenience
		virtual bool			VCOM_CALLTYPE ExecWSExpression(MCObjectHandle h, Handle compiledExpression, VWVariant& outResult) = 0;

		// Executes a Quantity Take Off function with an option (string representation of registered options on functions by various objects)
		virtual bool			VCOM_CALLTYPE ExecQTOFunction(MCObjectHandle h, EQTOFunction function, const TXString& option, VWVariant& outResult) = 0;
		virtual bool			VCOM_CALLTYPE ExecQTOFunction(MCObjectHandle h, EQTOFunction function, const TXString& option, std::vector<VWVariant>& args, VWVariant& outResult) = 0;

		// call the callback lambda function for each object in the document that matches the criteria
		virtual void			VCOM_CALLTYPE ForEachObjectInCriteria(const TXString& criteria, std::function<void(MCObjectHandle h)> callback) = 0;

		virtual void			VCOM_CALLTYPE SplitNurbsCurveByPoint(MCObjectHandle h, const WorldPt3& pt3, bool killOriginal, bool insert, TVWArray_MCObjectHandle & hResultArray) = 0;

		//This function shows the MoveSymbolDlg dialog with the input folder preset. If the input is null ActSymbolLayer will be used.
		virtual void			VCOM_CALLTYPE ShowCreateSymbolSelectFolderDlg(MCObjectHandle& hInOutFolder) = 0;
        
        //Methods for tagging PIO sub-objects as parts.
        //The "partTypeName" is type of part
        //The "dataID" is an optional numeric data attached to the part
        //The "instanceUniqueName" is an optinal internal unique name identifier for each instance of the part in the PIO. If using this option, the names must be unique for each instance of the part within an object.
        virtual bool            VCOM_CALLTYPE TagSubObjectAsPart(MCObjectHandle h, const TXString& partTypeName, const Sint32 dataID = 0, const TXString& instanceUniqueName = "") = 0;
        virtual bool            VCOM_CALLTYPE SetPartInstanceUniqueName(MCObjectHandle h, const TXString& instanceUniqueName) = 0;
        virtual bool            VCOM_CALLTYPE SetPartDataID(MCObjectHandle h, const Sint32 dataID) = 0;
        virtual bool            VCOM_CALLTYPE RemovePartTag(MCObjectHandle h) = 0;
        virtual bool            VCOM_CALLTYPE IsSubObjectTaggedAsPart(MCObjectHandle h) = 0;
        virtual bool            VCOM_CALLTYPE GetPartTypeName(MCObjectHandle h, TXString& partTypeName) = 0;
        virtual bool            VCOM_CALLTYPE GetPartInstanceUniqueName(MCObjectHandle h, TXString& instanceUniqueName) = 0;
        virtual bool            VCOM_CALLTYPE GetPartDataID(MCObjectHandle h, Sint32& dataID) = 0;
        virtual bool            VCOM_CALLTYPE GetPartInfo(MCObjectHandle h, TXString& partTypeName, Sint32& dataID, TXString& uniqueInstanceName) = 0;

		// Appends hSourceNurbs to hDestNurbs
		virtual void			VCOM_CALLTYPE AppendNurbsCurves(MCObjectHandle hSourceNurbs, MCObjectHandle hDestNurbs) = 0;

		// Checks if two PieceWiseNurbsCurves are intersecting and returns the intersection points as output parameter
		virtual bool			VCOM_CALLTYPE AreNurbsIntersecting(MCObjectHandle hNurbs1, MCObjectHandle hNurbs2, TVWArray_WorldPt3& outIntersPts) = 0;

		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectSecondProfileGroup(MCObjectHandle inhObject) = 0;
		virtual Boolean VCOM_CALLTYPE SetCustomObjectSecondProfileGroup(MCObjectHandle inhObject, MCObjectHandle inhSecondProfileGroup) = 0;

		// Use gSDK->CompileCriteriaExpression to compile an expression or create a handle with pre-precompiled expression with gVWMM->NewHandle, and you must gVWMM->DisposeHandle
		// The handle is a pointer of a pointer to the memory: void* memory = *h and size = gVWMM->GetHandleSize( h )
		// UseVWFC::Tools::WSCriteriaExpression for convenience
		virtual bool			VCOM_CALLTYPE EvalWithCriteria(MCObjectHandle hObj, Handle compiledCriteria) = 0;
		virtual void			VCOM_CALLTYPE EvalWithCriteria(const std::vector<MCObjectHandle>& arrInputObjs, Handle compiledCriteria, std::vector<MCObjectHandle>& outMatchedObjects) = 0;		

		virtual Boolean 		VCOM_CALLTYPE SetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2 color) = 0;
		virtual Boolean 		VCOM_CALLTYPE SetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2 color) = 0;
		virtual Boolean 		VCOM_CALLTYPE GetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2& color) = 0;
		virtual Boolean 		VCOM_CALLTYPE GetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2& color) = 0;
		
		virtual void 			VCOM_CALLTYPE SetColorButton(Sint32 dialogID, Sint32 itemID, const TGSColorV2& color) = 0;
		virtual void 			VCOM_CALLTYPE GetColorButton(Sint32 dialogID, Sint32 itemID, TGSColorV2& color) = 0;

		virtual bool			VCOM_CALLTYPE AddToolFaceHighlightingPoly3D(MCObjectHandle polyID) = 0;

		virtual void			VCOM_CALLTYPE SetRadioButtonModeValue(Sint32 modeGroupID, Sint32 value, const TXStringArray& imageSpecs) = 0;
		virtual bool			VCOM_CALLTYPE SetCustomObjectWallClosureGroup( MCObjectHandle objectHand, MCObjectHandle hGeomGroup ) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallClosureGroup( MCObjectHandle h ) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallClosureGroupDeep( MCObjectHandle h ) = 0;

		virtual void			VCOM_CALLTYPE SetFaceTextureForPrimitiveObject(MCObjectHandle hObject, const SFaceTextureInfo& faceTextureInfo) = 0;
		virtual bool			VCOM_CALLTYPE GetFaceTextureForPrimitiveObject(MCObjectHandle hObject, SFaceTextureInfo& faceTextureInfo) = 0;

		virtual void			VCOM_CALLTYPE AddCustomTexturePartCategory(MCObjectHandle h, short partCategoryID, const TXString& categoryName) = 0;
		virtual bool			VCOM_CALLTYPE HasCustomTexturePartCategory(MCObjectHandle h, short partCategoryID) = 0;
		virtual void			VCOM_CALLTYPE RemoveCustomTexturePartCategory(MCObjectHandle h, short partCategoryID) = 0;

		virtual void			VCOM_CALLTYPE SetTextureRefN(MCObjectHandle object, InternalIndex textureRef, short multiPartID, short partCategoryID) = 0;
		virtual InternalIndex VCOM_CALLTYPE GetTextureRefN(MCObjectHandle object, short multiPartID, short partCategoryID, Boolean resolveByClass) = 0;
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfoN(MCObjectHandle h, short multiPartID, short partCategoryID) = 0;
		virtual void			VCOM_CALLTYPE SetTextureMappingInfoN(MCObjectHandle h, short multiPartID, short partCategoryID, const TextureMappingInfoSDK& mappingInfo) = 0;
		virtual void			VCOM_CALLTYPE SetDefaultTextureMappingN(MCObjectHandle h, short multiPartID, short partCategoryID) = 0;
		virtual bool			VCOM_CALLTYPE IsPartTexturedFromOveral(MCObjectHandle h, short multiPartID, short partCategoryID = 0) = 0;
		virtual bool			VCOM_CALLTYPE RevertPartTextureToOveral(MCObjectHandle h, short multiPartID, short partCategoryID = 0) = 0;

		virtual void 			VCOM_CALLTYPE CreatePluginStyle(MCObjectHandle hObj) = 0;

		//Reset bounds of symbol with calculated linked texts
		virtual void			VCOM_CALLTYPE ClearLinkedTextBounds(MCObjectHandle hSymbol) = 0;
		
		virtual bool	 		VCOM_CALLTYPE GetListBrowserItemHatchRefNumber(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, InternalIndex &liRefNumber) = 0;
		virtual bool	 		VCOM_CALLTYPE SetListBrowserItemHatchRefNumber(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, InternalIndex liRefNumber) = 0;

		virtual bool			VCOM_CALLTYPE GetListBrowserItemMarkerChoice(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, MarkerType& style, Sint8& angle, double& size, double& width, Uint8& thicknessBasis, double& thickness) = 0;
		virtual bool			VCOM_CALLTYPE SetListBrowserItemMarkerChoice(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, MarkerType style, Sint8 angle, double size, double width, Uint8 thicknessBasis, double thickness) = 0;
		virtual bool			VCOM_CALLTYPE GetListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& bByClass) = 0;
		virtual bool			VCOM_CALLTYPE SetListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool bByClass) = 0;

		// Returns true if h supports 3D rotation. 
		virtual bool			VCOM_CALLTYPE CanFreelyTransformObject(MCObjectHandle h) = 0;
        
        virtual void            VCOM_CALLTYPE SetListBrowserItemResourceOnlyCurrentDocument(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex, bool bCurrentDocOnly) = 0;
        virtual Boolean         VCOM_CALLTYPE IsListBrowserItemResourceOnlyCurrentDocument(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex) = 0;

		// Changes nurbs point from smooth to corner or from corner to smooth
		virtual void			VCOM_CALLTYPE ChangeNurbsPointType(MCObjectHandle hNurbs, Sint16 pointIndex) = 0;

		virtual void			VCOM_CALLTYPE NurbsInsertPtAtIndex(MCObjectHandle hNurbs, Sint16 atIndex, const WorldPt3& point) = 0;
		virtual double			VCOM_CALLTYPE GetNurbsLength(MCObjectHandle hNurbs) = 0;

		virtual bool			VCOM_CALLTYPE ShowListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool bShowByClass) = 0;
		virtual bool			VCOM_CALLTYPE ShowListBrowserItemMarkerEditList(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool bShowEditList) = 0;

		virtual bool			VCOM_CALLTYPE GetWebPaletteVisibility(const VWIID& iidWebPalette) = 0;
		virtual bool			VCOM_CALLTYPE SetWebPaletteVisibility(const VWIID& iidWebPalette, bool visible) = 0;

		virtual MCObjectHandle	VCOM_CALLTYPE GetWallAtPoint( const WorldPt& point ) = 0;

		virtual void			VCOM_CALLTYPE GetSimpleMaterialsRefNumbers(MCObjectHandle hMaterial, std::vector<RefNumber>& outData) = 0;

		virtual InsertModeType	VCOM_CALLTYPE GetWallInsertLocation(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetWallInsertLocation(MCObjectHandle hObject, InsertModeType insertLocation) = 0;
		virtual WorldCoord		VCOM_CALLTYPE GetWallInsertLocationOffset(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetWallInsertLocationOffset(MCObjectHandle hObject, WorldCoord insertLocationOffset) = 0;
		virtual bool			VCOM_CALLTYPE GetUseWallClosure(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetUseWallClosure(MCObjectHandle hObject, bool useWallClosure) = 0;
		virtual bool			VCOM_CALLTYPE GetWallInsertLocationByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetWallInsertLocationByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetWallInsertLocationOffsetByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetWallInsertLocationOffsetByStyle(MCObjectHandle hObject, bool byStyle) = 0;
		virtual bool			VCOM_CALLTYPE GetUseWallClosureByStyle(MCObjectHandle hObject) = 0;
		virtual bool			VCOM_CALLTYPE SetUseWallClosureByStyle(MCObjectHandle hObject, bool byStyle) = 0;

		virtual bool			VCOM_CALLTYPE GetObjectWallInsertLocationOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord &insertLocationOffset) = 0;
		virtual bool			VCOM_CALLTYPE SetObjectWallInsertLocationOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord insertLocationOffset) = 0;

		virtual bool			VCOM_CALLTYPE GetWallHoleObjectIgnoreClosure(MCObjectHandle object) = 0;
		virtual void			VCOM_CALLTYPE SetWallHoleObjectIgnoreClosure(MCObjectHandle object, bool ignoreClosure) = 0;

		virtual void			VCOM_CALLTYPE SetObjectClassN(MCObjectHandle h, InternalIndex classID, bool descendIntoGroup) = 0;

		virtual bool			VCOM_CALLTYPE ShowCriteriaDialog(TXString& inOutCriteria, bool showObjectsCount) = 0;

		// For BuildResourceListFromOpenFileN, the fileRef can be obtained from GetOpenFilesList. The fileRef will always be non-negative for open files.
		virtual Sint32			VCOM_CALLTYPE BuildResourceListFromOpenFileN(short objectType, size_t fileRef, bool sort, Sint32& numItems) = 0;
	};
}

