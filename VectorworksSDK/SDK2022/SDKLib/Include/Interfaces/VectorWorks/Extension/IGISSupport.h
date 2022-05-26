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
			TXString		fServiceName;
			TXString		fServiceType;
			SLayerID		fServiceLayerId;
			TXString		fServiceRasterFunc;
			TXStringArray	farrRasterFunctions;
			Sint32			fResolution;
			bool			fStoreGeoimage;

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

			virtual VCOMError	VCOM_CALLTYPE EnableGeoreferencing(bool enable) = 0;

			// Data accessors
			virtual VCOMError	VCOM_CALLTYPE GetUseDocumentSettings(bool& outValue, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetUseDocumentSettings(bool value, bool useDocIfLayerIsNotGIS=false) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetOrigin(double& outLat, double& outLon, double& outAngleToNorth, bool useDocIfLayerIsNotGIS=false) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetOrigin(double lat, double lon, double angleToNorth, bool useDocIfLayerIsNotGIS=false) = 0;
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
			virtual VCOMError	VCOM_CALLTYPE SetGISAndTransformGeometry(const std::vector<MCObjectHandle>& layers, const TXString& importedGeoRef, EGISImportSettings importSettings, bool isRawImport = false) = 0;

			virtual void			VCOM_CALLTYPE GetDefaultService(SGeoImageData& out) = 0;
			virtual bool			VCOM_CALLTYPE SelectService(SGeoImageData& inout, const bool& isFeatureLayerBinding = false) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE GetGeoImage(MCObjectHandle hLayer, double angle, const WorldPt& topLeft, const WorldPt& botRight, const SGeoImageData& data,
																WorldPt& outImageLocation, TransformMatrix& outImageRotation,
																WorldPt& outImageBoundsA, WorldPt& outImageBoundsB,
															  	double& outImageWidth, double& outImageHeight,
																Sint32& outResolution) = 0;
		
			// get the origin XY inside the current coordinate system
			virtual bool		VCOM_CALLTYPE GetOriginXY(double& outX, double& outY) = 0;
			virtual void		VCOM_CALLTYPE GetFeatureLayerBinding(MCObjectHandle hLayer, SGeoImageData& out) = 0;
			virtual void		VCOM_CALLTYPE SetFeatureLayerBinding(MCObjectHandle hLayer, const SGeoImageData& in) = 0;

			virtual void		VCOM_CALLTYPE ProcessGeometryData(SGeometryData& geometryData, bool bGetData, bool inGroup = false) = 0;
			
			virtual void		VCOM_CALLTYPE ImportWFSFile(const IFileIdentifierPtr& pFileID, const WorldPt& ptA, const WorldPt& ptB, const bool& bViewRegion) = 0;

			virtual VCOMError GetVectorworksCoordinateN(const SGISCoord& inCoord, WorldPt& outCoord, bool useDocIfLayerIsNotGIS=false, bool useWGS84=false) = 0;
			virtual VCOMError GetVectorworksCoordinateN(const TVWArray_GISCoord& inArrCoord, VectorWorks::TVWArray_WorldPt& outArrCoord, bool useDocIfLayerIsNotGIS=false, bool useWGS84=false) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IGISSupport>		IGISSupportPtr;
	}
}
