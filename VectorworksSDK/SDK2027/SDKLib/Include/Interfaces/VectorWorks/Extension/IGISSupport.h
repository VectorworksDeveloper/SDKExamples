//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		struct SGISCoord
		{
			double		fdLatitude;
			double		fdLongitude;

						SGISCoord()							{ fdLatitude = 0; fdLongitude = 0; }
						SGISCoord(double lat, double lon)	{ fdLatitude = lat; fdLongitude = lon; }
		};

		// ---------------------------------------------------------------------------------------------------
		typedef TXGenericArray< SGISCoord >			TVWArray_GISCoord;

		// ---------------------------------------------------------------------------------------------------
		enum class EImportShapeResult
		{
			Succeess,
			Cancelled,
			MissingFile,
			Failed,
		};

		enum class EGISImportSettings
		{
			None,
			UseDoc,
			UseImport,
			UseImportUpdateDoc,
		};

		struct SImportedGeoRefOrigin
		{
			bool	fbIsSet			= false;
			double	fLatitude		= 0.0;
			double	fLongitude		= 0.0;
			double	fEasting		= 0.0;
			double	fNorthing		= 0.0;
			double	fAngleToNorth	= 0.0;
		};

		// ----------------------------------------------------------------------------------------------------------------------------
		struct SLayerID
		{
			Sint32				fId;	// for ArcGIS feature layer
			TXString			fIdStr;	// for WFS layer
			TXString			fName;
			TXString			fType;

			SLayerID() : fId( 0 ), fName( "" ), fType("") { }
			SLayerID(Sint32 id, const TXString& name, const TXString& type) { fId = id; fName = name; fType = type; }

			void Clear() { fId = 0; fName.Clear(); fType.Clear(); };
		};

		// ----------------------------------------------------------------------------------------------------------------------------
		struct SGeoImageData
		{
			bool			fEnabled;
			TXString		fServerURL;
			TXString		fDefVersion;
			TXString		fServiceName;
			TXString		fServiceType;
			SLayerID		fServiceLayerId;
			TXString		fServiceRasterFunc;
			TXString		fServiceSubLayers;
			TXStringArray	farrRasterFunctions;
			Sint32			fResolution;
			bool			fStoreGeoimage;

			bool	fRequestTiles		= false;
			bool	fAutoTileLevel		= true;
			Sint32	fAutoAdjust			= 0;	// adjustment level for when fAutoTileLevel == true
			Sint32	fUsedTileLevel		= 19;
			Sint32	fMaxTileLevel		= 19;

			SGeoImageData() { fEnabled = false; fResolution = 0; fStoreGeoimage = false; }
		};

		// ----------------------------------------------------------------------------------------------------------------------------
		enum class EGeometryType
		{
			Unknown,
			Point,
			Polyline,
			Polygon,
			Group
		};

		struct SGeometryData
		{
			MCObjectHandle		fObject;
			TXString			fObjectName;
			EGeometryType		fGeometryType;
			double				fCenterX;
			double				fCenterY;

			std::vector<double> farrX;
			std::vector<double> farrY;
			std::vector<double> farrZ;
			std::vector<size_t> farrIndex;

			SGeometryData() { fObject = nullptr; fObjectName = ""; fGeometryType = EGeometryType::Unknown; }
		};

		// ---------------------------------------------------------------------------------------------------
		// {E8E36752-2EF8-437D-8031-9D7A4E34BEA5}
		static const VWIID IID_GISSupport	= { 0xe8e36752, 0x2ef8, 0x437d, { 0x80, 0x31, 0x9d, 0x7a, 0x4e, 0x34, 0xbe, 0xa5 } };

		class DYNAMIC_ATTRIBUTE IGISSupport : public IVWUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE SetLayer(MCObjectHandle hLayer) = 0;
			virtual VCOMError	VCOM_CALLTYPE AddLayer(MCObjectHandle hLayer) = 0;
			virtual VCOMError	VCOM_CALLTYPE EditWithUI() = 0;
			virtual VCOMError   VCOM_CALLTYPE ApplyNTV2Tranfrom( const TXString& targetProjWKT, const TXString& fileNTVFullPath ) = 0;

			virtual VCOMError	VCOM_CALLTYPE EnableGeoreferencing(bool enable, bool allowInLayers = false) = 0;

			// Data accessors
			virtual VCOMError	VCOM_CALLTYPE GetUseDocumentSettings(bool& outValue, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetUseDocumentSettings(bool value, bool useDocIfLayerIsNotGIS=false) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetOrigin(double& outLat, double& outLon, double& outAngleToNorth, bool useDocIfLayerIsNotGIS=false, bool useFormatGeogCS = false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetOrigin(double lat, double lon, double angleToNorth, bool useDocIfLayerIsNotGIS=false, bool useFormatGeogCS = false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetApplyUseOriginTransform(bool& outValue, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetApplyUseOriginTransform(bool value, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetApplyImageTransform(bool& value) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetProjection(TXString& outName, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetProjectionLocalizedName(TXString& outProjectionName, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetProjection(const TXString& value, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetProjectionParam(const TXString& name, TXString& outValue, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetProjectionParam(const TXString& name, const TXString& value, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetProjectionWKT(bool esriStyle, TXString& outValue) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetProjectionProj4(bool esriStyle, TXString& outValue) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetProjectionEPSG(size_t projEPSG) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetLayerProjectionEPSGDescription( MCObjectHandle srcLayer, size_t& outEPSG, TXString& outDescription, TXString& outGeoDatum, TXString& outVertDatum, TXString& outUnit ) = 0;

			virtual VCOMError	VCOM_CALLTYPE IsGeoreferenced(bool& outValue) = 0;
			virtual VCOMError	VCOM_CALLTYPE MoveGeographic(WorldPt& inOutCoord, double azimuth, double distance, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetVectorworksCoordinate(const SGISCoord& inCoord, WorldPt& outCoord, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetGeographicCoordinate(const WorldPt& inCoord, SGISCoord& outCoord, bool useDocIfLayerIsNotGIS=false, bool getWGS84Coord = false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetVectorworksCoordinate(const TVWArray_GISCoord& inArrCoord, TVWArray_WorldPt& outArrCoord, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetVectorworksCoordinate(const TVWArray_WorldPt& inCoord, const TXString& inProjWKT, TVWArray_WorldPt& outCoord, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetGeographicCoordinate(const TVWArray_WorldPt& inArrCoord, TVWArray_GISCoord& outArrCoord, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE CalcGreatCircle(const WorldPt& inStartCoord, const WorldPt& inEndCoord, size_t desiredPoints, TVWArray_WorldPt& outArrPoints, WorldCoord& outDistance, double& outAzimuth, bool useDocIfLayerIsNotGIS=false) = 0;

			virtual VCOMError	VCOM_CALLTYPE AngleToDMS(double inAngle, TXString& outDMS, const TXString& posDir = "", const TXString& negDir = "") = 0;

			// the projection info funciton provide access to the entire projection information as a string
			// they will work on the first layer added to the class
			virtual VCOMError	VCOM_CALLTYPE GetProjectionInfo(TXString& outInfo, bool useDocIfLayerIsNotGIS=false) = 0;

			virtual EImportShapeResult	VCOM_CALLTYPE ImportShapefiles(TVWArray_IFileIdentifier arrShapeFiles) = 0;
			
			virtual VCOMError	VCOM_CALLTYPE MoveObjectToLayer( MCObjectHandle srcLayer, MCObjectHandle destLayer, MCObjectHandle hObject ) = 0;

			virtual VCOMError	VCOM_CALLTYPE ImportECWJP2Image( const IFileIdentifierPtr& fileID, IFileIdentifierPtr& outFile, bool bPNGImage = true, bool bWarpImage = true ) = 0;

			//Fetches the affine transformation coefficients for transforming between pixel/line (P,L) raster space, and projection coordinates (Xp,Yp) space ( if they are present ).
			virtual VCOMError	VCOM_CALLTYPE GetECWJP2ImageGeotransform( const IFileIdentifierPtr& fileID, TXString& outProjWKT, TVWArray_Double& outCoords, size_t& outSizeX, size_t& outSizeY, size_t& outSizeTransformedX, size_t& outSizeTransformedY ) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetGeoTIFFImageGeotransform( const IFileIdentifierPtr& fileID, TXString& outProjWKT, TVWArray_Double& outCoords, size_t& outSizeX, size_t& outSizeY, size_t& outSizeTransformedX, size_t& outSizeTransformedY ) = 0;

			virtual VCOMError	VCOM_CALLTYPE ImportGeoTIFFImage( const IFileIdentifierPtr& fileID, IFileIdentifierPtr& outFile, bool bPNGImage = true, bool bWarpImage = true ) = 0;

			virtual VCOMError	VCOM_CALLTYPE FindCRS(  TXString& outWKT, size_t& outEPSG ) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetGISAndTransformGeometry(const std::vector<MCObjectHandle>& layers, const TXString& importedGeoRef, EGISImportSettings importSettings, bool isRawImport = false, const SImportedGeoRefOrigin* sourceOrigin = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetGISAndTransformReferencedCacheGeometry(const std::vector<MCObjectHandle>& layers, WorldPt srcUserOrigin, EGISImportSettings importSettings = EGISImportSettings::UseImport, MCObjectHandle hDestLayerGeoRefNode = nullptr, MCObjectHandle hSrcDocGeoRefNode = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetGISFromNode(const std::vector<MCObjectHandle>& layers, MCObjectHandle hGisNode = nullptr) = 0;

			virtual void			VCOM_CALLTYPE GetDefaultService(SGeoImageData& out) = 0;
			virtual bool			VCOM_CALLTYPE SelectService(SGeoImageData& inout, const bool& isFeatureLayerBinding = false) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE GetGeoImageForSiteModel(MCObjectHandle hDTM, double angle, const WorldPt& topLeft, const WorldPt& botRight, SGeoImageData& outData,
																WorldPt& outImageLocation, TransformMatrix& outImageRotation,
																WorldPt& outImageBoundsA, WorldPt& outImageBoundsB,
																double& outImageWidth, double& outImageHeight,
																Sint32& outResolution) = 0;

			// ------------------------------------------------------------------------------------------------------
			class IDownloadTiledContext
			{
			public:
				virtual		~IDownloadTiledContext() = default;

				// use this only when the point came from VCOM, so the class can be destroyed and flushed properly
				virtual		void	DeleteThis() = 0;

				virtual		const ViewRect&	GetImageRect() = 0;

				virtual		void	Init(VectorWorks::IDrawPadPtr drawPad) = 0;				// init on existing drawpad

				virtual		void	PrepareTiles() = 0;	// call on the thread to optimize the tile aquisition

				virtual		Sint32	GetRowStart() const = 0;
				virtual		Sint32	GetRowEnd() const = 0;
				virtual		Sint32	GetColStart() const = 0;
				virtual		Sint32	GetColEnd() const = 0;
				virtual		bool	DrawAvailableTile(Sint32 iRow, Sint32 iCol, VectorWorks::Imaging::ICompressedImagePtr& outImage, ViewRect& outRect) = 0;	// return false if not available
				virtual		void	DrawTile(Sint32 iRow, Sint32 iCol, VectorWorks::Imaging::ICompressedImagePtr& outImage, ViewRect& outRect) = 0;				// will download if it needs to (slow)

				virtual		size_t	GetSpiralGridCount() const = 0;
				virtual		bool	DrawAvailableTile(size_t spiralGridIndex, VectorWorks::Imaging::ICompressedImagePtr& outImage, ViewRect& outRect) = 0;		// return false if not available
				virtual		void	DrawTile(size_t spiralGridIndex, VectorWorks::Imaging::ICompressedImagePtr& outImage, ViewRect& outRect) = 0;				// will download if it needs to (slow)
				virtual		bool	GetSpiralGridRowCol( size_t spiralGridIndex, Sint32& outRow, Sint32& outCol ) const = 0;
			};

			virtual IDownloadTiledContext* VCOM_CALLTYPE	CreateDownloadTiledContext(const WorldPt& topLeft, const WorldPt& botRight, bool force=false) = 0;
		
			// get the origin XY inside the current coordinate system
			virtual bool		VCOM_CALLTYPE GetOriginXY(double& outX, double& outY) = 0;
			virtual void		VCOM_CALLTYPE GetFeatureLayerBinding(MCObjectHandle hLayer, SGeoImageData& out) = 0;
			virtual void		VCOM_CALLTYPE SetFeatureLayerBinding(MCObjectHandle hLayer, const SGeoImageData& in) = 0;

			virtual void		VCOM_CALLTYPE ProcessGeometryData(SGeometryData& geometryData, bool bGetData, bool inGroup = false) = 0;
			
			virtual void		VCOM_CALLTYPE ImportWFSFile(const IFileIdentifierPtr& pFileID, const WorldPt& ptA, const WorldPt& ptB, const bool& bViewRegion, const bool& createOnlyRecordFormat) = 0;

			virtual VCOMError   GetVectorworksCoordinateN(const SGISCoord& inCoord, WorldPt& outCoord, bool useDocIfLayerIsNotGIS=false, bool useWGS84=false) = 0;
			virtual VCOMError   GetVectorworksCoordinateN(const TVWArray_GISCoord& inArrCoord, VectorWorks::TVWArray_WorldPt& outArrCoord, bool useDocIfLayerIsNotGIS=false, bool useWGS84=false) = 0;

			virtual VCOMError	VCOM_CALLTYPE SetLocationWithUI(const WorldPt& inLocation, WorldPt& outLocation) = 0;

			virtual double		VCOM_CALLTYPE GetProjectElevation() = 0;
			virtual void		VCOM_CALLTYPE SetProjectElevation(double projectElevation) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetProjectionEPSGDescriptionFromWKT( const TXString& strWKT, size_t& outEPSG, TXString& outDescription, TXString& outGeoDatum, TXString& outVertDatum, TXString& outUnit ) = 0;
			virtual bool		VCOM_CALLTYPE GetOriginXYZFromWKT(const TXString& strWKT, double& outX, double& outY, double& outZ) = 0;

			// This function is for OnscreenViewControl to regurn all necessary data fast, with one data read, and allow for initialization of the background tiling without the need to call multiple functions to get the georef data
			virtual void		VCOM_CALLTYPE GetDocumentGeoref(bool& outIsGeoref, bool& outInternalOriginOverride, double& outGeorefAngle, bool initScreen) = 0;
			virtual void		VCOM_CALLTYPE ConvertDocumentGeorefToWGS84() = 0;

			virtual bool		VCOM_CALLTYPE IsSameProjection(MCObjectHandle geoRefNodeA, MCObjectHandle geoRefNodeB) = 0;

			virtual void		VCOM_CALLTYPE TransformObjectsOnPaste(TMCObjectHandlesSTLArray arrObjects, MCObjectHandle hSrcDoc, WorldPt srcDocUserOrigin) = 0;

			virtual MCObjectHandle	VCOM_CALLTYPE IsGeolocated() = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE Geolocate(MCObjectHandle hIntoLayer = nullptr) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetOriginEN(double& outEasting, double& outNorthing, double& outAngleToNorth) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetOriginEN(double easting, double northing, double angleToNorth) = 0;

			virtual VCOMError	VCOM_CALLTYPE EmbedGeoTransformInImage(const TXString& imagePath, WorldPt ul, WorldPt ur, WorldPt br, int width, int height) = 0;
			virtual VCOMError	VCOM_CALLTYPE CreateGeoWorldFile(const TXString& imagePath, WorldPt ul, WorldPt ur, WorldPt br, int width, int height) = 0;
			virtual VCOMError	VCOM_CALLTYPE ReadGeoWorldFile(const TXString& worldFilePath, int imageWidth, int imageHeight, WorldPt& outUL, WorldPt& outUR, WorldPt& outBR) = 0;

			virtual TXString	VCOM_CALLTYPE GetCurrentMapAttribution() = 0;

			struct SImportElevationsOptions
			{
				VCOMPtr<VectorWorks::Filing::IFileIdentifier> fFileID = nullptr;

				MCObjectHandle	fhBoundary		= nullptr;

				WorldPt		fOrigin;					// Grid origin in boundary coordinates; the grid extends from it in both directions at fGridSpacing. Required: the default (unset) value is invalid input.
				bool		fShowMap		= false;	// Transfer information on wheather to show the map on the surface
				bool		fOptimize		= false;	// optimize the points so it doesnt have extra points for flat surfaces
				// fFlatnessTolerance controls how aggressively flat areas are thinned when fOptimize is on (it is
				// ignored otherwise). It is the maximum height (Z) by which a point may deviate from the surrounding
				// surface and still be treated as lying on a flat patch - and therefore be removed - expressed in the
				// grid's elevation units (the same units as the imported heights). In UI terms it answers "how bumpy
				// may a region be and still count as flat?":
				//   - a larger value removes more points and gives a flatter, coarser surface;
				//   - a smaller value keeps more points and preserves more detail;
				//   - 0 removes only points that are exactly coplanar;
				//   - a negative value lets the importer pick an automatic tolerance from the elevation range.
				double		fFlatnessTolerance = -1;
				double		fGridSpacing	= 1;		// grid spacing in boundary coordinates
				bool		fPointsAtEdges	= false;	// generate grid points at boundary edges, even if they don't align with the grid spacing
				bool		fTriangleGrid	= false;	// Equilateral triangular lattice: alternate rows shift by half fGridSpacing; row spacing is sqrt(3)/2 * fGridSpacing.
			};

			// Counts grid points before elevation-based optimization; returns -1 for invalid input and clamps to the Sint32 maximum.
			virtual Sint32		VCOM_CALLTYPE EstimateGridPtCnt(const SImportElevationsOptions& opts) = 0;
			virtual bool		VCOM_CALLTYPE GetElevationImageBounds(VCOMPtr<VectorWorks::Filing::IFileIdentifier> fileID, WorldPt& outTopLeft, WorldPt& outBottomRight, WorldCoord& outSpacingX, WorldCoord& outSpacingY) = 0;
			virtual bool		VCOM_CALLTYPE ImportElevations(const SImportElevationsOptions& opts, std::vector<WorldPt3>& outGridElev) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IGISSupport>		IGISSupportPtr;

		// ---------------------------------------------------------------------------------------------------
		// Represent a GIS coordinate (x,y) in two modes:
		//	1. BIM coordinate (x,y) is a coordinate in Vectorworks model space, i.e. internal origin based cartesian distance in mm
		//	2. EPSG or WKT of the coordinates (x,y) or (longitude, latitude)
		//		- <number> - representing EPSG code
		//		- <string> - representing WKT
		//		- "vworks" - representing the coordinate system of Vectorworks drawing
		//		- add suffix: "|AzimEqui;%f;%f" to consider the coordinates as central (%f;%f) [lat/long] of an Azimuthal Equidistant projection
		struct EPSGCoord
		{
			bool		fBIMCoord;	// compensate for Vectorworks origin location
			TXString	fEPSG;		// number: EPSG; string: WKT;

			// cartesian or spherical coordinates
			union {
				double		x;
				double		longitude;
			};
			union {
				double		y;
				double		latitude;
			};

			EPSGCoord()						/* BIM Coordinates */						: fBIMCoord(true)				{ this->x = 0; this->y = 0; }
			EPSGCoord(double x, double y)	/* BIM Coordinates */						: fBIMCoord(true)				{ this->x = x; this->y = y; }
			EPSGCoord(const WorldPt& pt)	/* BIM Coordinates */						: fBIMCoord(true)				{ this->x = pt.x; this->y = pt.y; }
			EPSGCoord(const TXString& epsg)						/* EPSG Coordinates */	: fBIMCoord(false), fEPSG(epsg)	{ this->x = 0; this->y = 0; }
			EPSGCoord(const TXString& epsg, double x, double y)	/* EPSG Coordinates */	: fBIMCoord(false), fEPSG(epsg)	{ this->x = x; this->y = y; }
		};

		// ---------------------------------------------------------------------------------------------------
		// Represent a GIS bounds min/max (x,y) as EPSGCoord
		struct EPSGCoordBounds
		{
			bool		fBIMCoord;		// compensate for Vectorworks origin location
			TXString	fEPSG;			// number: EPSG; string: WKT;
			double		minx;			// represents longitude (degrees) when spherical coordinate system
			double		maxx;			// represents latitude (degrees)  when spherical coordinate system
			double		miny;			// represents longitude (degrees) when spherical coordinate system
			double		maxy;			// represents latitude (degrees)  when spherical coordinate system

			EPSGCoordBounds()											/* BIM Coordinates */							: fBIMCoord(true) { this->minx = this->maxx = this->miny = this->maxy = 0; }
			EPSGCoordBounds(const WorldPt& a, const WorldPt& b)			/* BIM Coordinates */							: fBIMCoord(true) { this->Set( a.x, a.y, b.x, b.y ); }
			EPSGCoordBounds(double ax, double ay, double bx, double by)	/* BIM Coordinates */							: fBIMCoord(true) { this->Set( ax, ay, bx, by ); }
			EPSGCoordBounds(const TXString& epsg)												/* EPSG Coordinates */	: fBIMCoord(false), fEPSG(epsg) { this->minx = this->maxx = this->miny = this->maxy = 0; }
			EPSGCoordBounds(const TXString& epsg, const WorldPt& a, const WorldPt& b)			/* EPSG Coordinates */	: fBIMCoord(false), fEPSG(epsg) { this->Set( a.x, a.y, b.x, b.y ); }
			EPSGCoordBounds(const TXString& epsg, double ax, double ay, double bx, double by)	/* EPSG Coordinates */	: fBIMCoord(false), fEPSG(epsg) { this->Set( ax, ay, bx, by ); }

			void Set(const EPSGCoord& a, const EPSGCoord& b)			{ DSTOPIF( a.fBIMCoord == b.fBIMCoord && a.fEPSG.Equal( b.fEPSG ), (kVStanev, "Inconsistent coordinates") ); fBIMCoord = a.fBIMCoord; fEPSG = a.fEPSG; this->minx = std::min( a.x, b.x ); this->maxx = std::max( a.x, b.x ); this->miny = std::min( a.y, b.y ); this->maxy = std::max( a.y, b.y ); }
			void Set(double x0, double y0, double x1, double y1)		{ this->minx = std::min( x0, x1 ); this->maxx = std::max( x0, x1 ); this->miny = std::min( y0, y1 ); this->maxy = std::max( y0, y1 ); }

			EPSGCoord	GetTL() const	/* (min-x, min-y) */			{ return fBIMCoord ? EPSGCoord( minx, miny ) : EPSGCoord( fEPSG, minx, miny ); }
			EPSGCoord	GetBR() const	/* (max-x, max-y) */			{ return fBIMCoord ? EPSGCoord( maxx, maxy ) : EPSGCoord( fEPSG, maxx, maxy ); }
			EPSGCoord	GetBL() const	/* (min-x, max-y) */			{ return fBIMCoord ? EPSGCoord( minx, maxy ) : EPSGCoord( fEPSG, minx, maxy ); }
			EPSGCoord	GetTR() const	/* (max-x, min-y) */			{ return fBIMCoord ? EPSGCoord( maxx, miny ) : EPSGCoord( fEPSG, maxx, miny ); }
		};

		// ---------------------------------------------------------------------------------------------------
		// {7DE216E1-08D0-4E7C-A89F-0760AB5D7000}
		static const VWIID IID_GISTransformer	= { 0x7de216e1, 0x8d0, 0x4e7c, { 0xa8, 0x9f, 0x7, 0x60, 0xab, 0x5d, 0x70, 0x0 } };

		class DYNAMIC_ATTRIBUTE IGISTransformer : public IVWUnknown
		{
		public:
			virtual TXString	VCOM_CALLTYPE GetDocumentWKT() = 0;					// CRS
			virtual bool		VCOM_CALLTYPE GetDocumentEPSG(Sint32& outEPSG) = 0;	// CRS
			virtual double		VCOM_CALLTYPE GetDocumentLinearUnits() = 0;			// CRS
			virtual bool		VCOM_CALLTYPE GetDocumentAreaOfUse(SGISCoord& outBoundsLon, SGISCoord& outBoundsLat) = 0;	// CRS
			virtual double		VCOM_CALLTYPE GetDocumentAngleToNorth() = 0;

			virtual double		VCOM_CALLTYPE GetInternalOriginLat() = 0;			// WGS84
			virtual double		VCOM_CALLTYPE GetInternalOriginLon() = 0;			// WGS84
			virtual double		VCOM_CALLTYPE GetInternalOriginEasting() = 0;		// Within CRS ("vworks")
			virtual double		VCOM_CALLTYPE GetInternalOriginNorthing() = 0;		// Within CRS ("vworks")

			virtual bool		VCOM_CALLTYPE HasSurveyPoint() = 0;					// IsGeolocated - presense of Survey Point defines fully georeferenced drawing
			virtual WorldPt		VCOM_CALLTYPE GetSurveyPointLocation() = 0;			// Vectorworks coordinates in mm
			virtual double		VCOM_CALLTYPE GetSurveyPointLat() = 0;				// WGS84
			virtual double		VCOM_CALLTYPE GetSurveyPointLon() = 0;				// WGS84
			virtual double		VCOM_CALLTYPE GetSurveyPointEasting() = 0;			// Within CRS ("vworks")
			virtual double		VCOM_CALLTYPE GetSurveyPointNorthing() = 0;			// Within CRS ("vworks")

			virtual bool	VCOM_CALLTYPE Transform(const EPSGCoord& in, EPSGCoord& out) = 0;
			virtual bool	VCOM_CALLTYPE Transform(const EPSGCoordBounds& in, EPSGCoordBounds& out) = 0;
			virtual bool	VCOM_CALLTYPE Transform(bool fromBIM, const TXString& fromEPSG, bool toBIM, const TXString& toEPSG, size_t ptsCnt, double* arrx, double* arry) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IGISTransformer>		IGISTransformerPtr;
	}
}
