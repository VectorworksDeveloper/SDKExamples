//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWTextureShaderColor.h"
#include "VWTextureShaderReflectivity.h"
#include "VWTextureShaderTransparency.h"
#include "VWTextureShaderBump.h"
#include "VWTextureShaderForeground.h"

namespace VWFC
{
	namespace VWObjects
	{
		class VWTextureObj : public VWObject
		{
		public:
							VWTextureObj(const TXString& name);
							VWTextureObj(MCObjectHandle hTexture);
							VWTextureObj(const VWTextureObj& src);
			virtual			~VWTextureObj();

			VWTextureObj&	operator=(const VWTextureObj& src);

		public:
			InternalIndex	GetTextureRef() const;
			TXString		GetName() const;
			void			SetName(const TXString& name);

			WorldCoord		GetSize() const;
			void			SetSize(WorldCoord value);
			WorldCoord		GetUVAspectRatio() const;

			void			ApplyToObject(MCObjectHandle hObject, TexturePartSDK partID);

			void			UpdateThumbnailPreview();

			template <class TShader>	bool	CreateShader(TShader& outValue);
			template <class TShader>	bool	GetShader(TShader& outValue);

		// tool
		public:
			// Return true if the specified object handle is 3D locus
			static bool		IsTextureObject(MCObjectHandle hObj);
			static bool		IsTextureObject(InternalIndex index);
		};
	}
}


namespace VWFC
{
	namespace VWObjects
	{
		template <class TShader>	bool	VWTextureObj::CreateShader(TShader& outValue)
		{
			return TShader::CreateShader( fhObject, outValue );
		}

		template <class TShader>	bool	VWTextureObj::GetShader(TShader& outValue)
		{
			return TShader::GetShader( fhObject, outValue );
		}
	}
}
