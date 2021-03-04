//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		// --------------------------------------------------------------------------------
		class VWTextureObj;

		// --------------------------------------------------------------------------------
		class VWTextureShaderBase : public VWObject
		{
		public:
							VWTextureShaderBase(MCObjectHandle hShaderRecord);
							VWTextureShaderBase(const VWTextureShaderBase& src);
			virtual			~VWTextureShaderBase();

			VWTextureShaderBase&	operator=(const VWTextureShaderBase& src);

		public:
			bool				GetShaderRecordFamilyAndPrototype(ShaderFamily& family, Sint32& prototype) const;

			Sint32				GetShaderRecordLong(short fieldID) const;
			void				SetShaderRecordLong(short fieldID, Sint32 value);

			double				GetShaderRecordDouble(short fieldID) const;
			void				SetShaderRecordDouble(short fieldID, double value);

			WorldCoord			GetShaderRecordCoord(short fieldID) const;
			void				SetShaderRecordCoord(short fieldID, WorldCoord value);

			Tools::CRGBColor	GetShaderRecordColor(short fieldID) const;
			void				SetShaderRecordColor(short fieldID, const Tools::CRGBColor& color);

			bool				GetShaderRecordBool(short fieldID) const;
			void				SetShaderRecordBool(short fieldID, bool value);

		// tool
		public:
			static bool		GetShaderRecordFamilyAndPrototype(MCObjectHandle hObj, ShaderFamily& family, Sint32& prototype);

		protected:
						VWTextureShaderBase();
		};
	}
}
