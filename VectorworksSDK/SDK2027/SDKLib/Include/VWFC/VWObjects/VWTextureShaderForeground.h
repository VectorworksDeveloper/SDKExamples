//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWTextureShaderBase.h"

namespace VWFC
{
	namespace VWObjects
	{
		// --------------------------------------------------------------------------------
		class VWTextureShaderForegroundLitFog : public VWTextureShaderBase
		{
		public:
							VWTextureShaderForegroundLitFog(VWTextureObj& textureObj);
							VWTextureShaderForegroundLitFog(MCObjectHandle hShaderRecord);
							VWTextureShaderForegroundLitFog(const VWTextureShaderForegroundLitFog& src);
			virtual			~VWTextureShaderForegroundLitFog();

			VWTextureShaderForegroundLitFog&	operator=(const VWTextureShaderForegroundLitFog& src);

		public:
			double			GetPercent() const;
			void			SetPercent(double value);
			bool			GetSmoothNoisy() const;
			void			SetSmoothNoisy(bool value);
			bool			GetRcvShadow() const;
			void			SetRcvShadow(bool value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderForegroundLitFog& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderForegroundLitFog& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
	}
}
