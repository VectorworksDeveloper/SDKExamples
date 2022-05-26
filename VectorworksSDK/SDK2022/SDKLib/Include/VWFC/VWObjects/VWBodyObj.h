//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Math;

	namespace VWObjects
	{
		class VWBodyObj : public VWObject
		{
		public:
							VWBodyObj();
							VWBodyObj(const VWBodyObj& src);
							VWBodyObj(MCObjectHandle hObj);
			virtual			~VWBodyObj();

			VWBodyObj&		operator=(const VWBodyObj& src);

		public:
			size_t			GetBodyCount();
			bool			GetBody(size_t index, VWBody& outBody);

			void			AddToolHighlighting(const VWBodyFace& face);
			void			AddToolHighlighting(const VWBodyEdge& edge);

			bool			IsFaceBelongsToThisObject(const VWBodyFace& face);

			// Face Texturing
			InternalIndex		GetFaceTexture(const VWBodyFace& face);
			void				SetFaceTexture(InternalIndex textureRef, const VWBodyFace& face);
			void				SetFaceTexture(MCObjectHandle hTexture, const VWBodyFace& face);
			void				GetFaceTextureMappingInfo(const VWBodyFace& face, TextureMappingInfoSDK& outMappingInfo);
			void				GetFaceTextureMappingInfo(const VWBodyFace& face, Sint32 decalLayerNum, TextureMappingInfoSDK& outMappingInfo);
			void				SetFaceTextureMappingInfo(const VWBodyFace& face, const TextureMappingInfoSDK& mappingInfo);
			void				SetFaceTextureMappingInfo(const VWBodyFace& face, Sint32 decalLayerNum, const TextureMappingInfoSDK& mappingInfo);
			Sint32				GetFaceTextureMappingDecalLayerCount(const VWBodyFace& face);	// number of decal layers on a texture part


		// tool
		public:
			// Return true if the specified object handle is suitable for body creation
			static bool		IsBodyObject(MCObjectHandle hObj);

		private:
			typedef TXGenericArray< Sint32 >	TBodiesArray;

			TBodiesArray		fBodies;
			IVWUnknown*			fpAPI;
			IVWUnknown*			fp;
		};
	}
}