//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// ---------------------------------------------------------------------------------------------------
// Defines
#define DATA_OBJECT_TAG (OSType) 'ESPB'

// Forward Declarations
class IVisionPlugin;
class VWColorData;
class QString;
class QDomElement;


// ---------------------------------------------------------------------------------------------------
namespace VectorWorks {
	// {1B284CE8-A5E9-4376-9F19-2B6D718E73C4}
	static const VWIID IID_VisionCommon
		= { 0x1b284ce8, 0xa5e9, 0x4376, {0x9f, 0x19, 0x2b, 0x6d, 0x71, 0x8e, 0x73, 0xc4}};

	// -----------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IVisionCommon : public IVWSingletonUnknown
	{

	public:

		struct VWPolygon
		{
			std::vector<WorldPt3> verts;
			std::vector<WorldPt3> normals;
			std::vector<WorldPt3> texcoords;
			unsigned int color;
			TXString texture;
			bool double_sided;
		};
		typedef std::vector<VWPolygon> VWMesh;
		typedef VWMesh::iterator MeshIterator;

		enum LitFilenameDisplaynameIdx
		{
			eDisplayname  = 0,
			eFilename     = 1,
			eCategoryname = 2
		};
		typedef std::tuple<TXString,TXString> VisionRes;
		typedef std::vector<VisionRes>        VisionResCont;
		typedef std::vector<VisionResCont>    VisionResContCont;

	public:
		
		///@note VisionPlugin dylib/dll singleton
		virtual IVisionPlugin*       VisionPluginInstance() = 0;
		virtual TXString             GetSymbolNameSource() = 0;
		virtual TXString             GetUniverseSource() = 0;
		virtual TXString             GetChannelSource() = 0;
		virtual TXString             GetUnitNumberSource() = 0;
		virtual TXString             GetCommonDir() = 0;
		virtual void                 SetCommonDir(const TXString& commonDir) = 0;
		
		///@note JSON Helper for Gobos
		class IGoboDataJsonHelper
		{
		public:
			virtual ~IGoboDataJsonHelper(){};
			virtual TXString CArrayToJson(char* goboData, const int numGoboWheels, const int numGobosPerWheel[]) = 0;
			virtual char* JsonToCArray(const TXString& strGoboData, int& numGoboWheels, int** numGobosPerWheel) = 0;
		};
		virtual IGoboDataJsonHelper* GoboDataJsonHelperInstance() = 0;

		///@note JSON Helper for Colors
		class IColorDataJsonHelper
		{
		public:
			virtual ~IColorDataJsonHelper(){};
			virtual TXString CArrayToJson(VWColorData* colorData, const int numColorWheels, const int numColorsPerWheel[]) = 0;
			virtual VWColorData* JsonToCArray(const TXString& strColorData, int& numColorWheels, int** numColorsPerWheel) = 0;
		};
		virtual IColorDataJsonHelper* ColorDataJsonHelperInstance() = 0;
	
		///@note JSON Helper for Animations (Color Flags)
		class IColorFlagDataJsonHelper
		{
		public:
			virtual ~IColorFlagDataJsonHelper(){};
			virtual TXString CArrayToJson(char* colorFlagData, const int numColorFlagWheels) = 0;
			virtual char* JsonToCArray(const TXString& strColorFlagData, int& numColorFlagWheels) = 0;
		};
		virtual IColorFlagDataJsonHelper* ColorFlagDataJsonHelperInstance() = 0;

		///@note Common / Executable path helper
		class IPathingHelper
		{
		public:
			virtual ~IPathingHelper(){};
			virtual QString GetVisionExecutablePath() = 0;
			virtual bool SetCommonDir() = 0;
		};
		virtual IPathingHelper* PathingHelperInstance() = 0;
			
		///@note VW Method helper
		class IVWHelper
		{
		public:
			virtual ~IVWHelper(){};
			virtual TXString GetFieldData(GSHandle hObj, const char *field_name) = 0;
			virtual void SetFieldData(GSHandle hObj, const char *field_name, const char *field_data) = 0;
			virtual TXString GetSpotlightName(GSHandle hObj) = 0;
			virtual bool PointCallback(WorldPt3 point3D, CallBackPtr cbp, void *env) = 0;
		};
		virtual IVWHelper* VWHelperInstance() = 0;
			
		///@mote Math function helper
		class IMathHelper
		{
		public:
			virtual ~IMathHelper(){};
			virtual void QuatMul( float q1x   , float q1y   , float q1z   , float q1w   ,
			                      float q2x   , float q2y   , float q2z   , float q2w   ,
			                      float *resx , float *resy , float *resz , float *resw ) = 0;
			virtual void EulerToQuat( float roll, float pitch, float yaw,
			                          float *quatx, float *quaty, float *quatz, float *quatw ) = 0;
		};
		virtual IMathHelper* MathHelperInstance() = 0;
		
	};
	typedef VCOMPtr<IVisionCommon> IVisionCommonPtr;
}
typedef VectorWorks::IVisionCommon VWVC;
