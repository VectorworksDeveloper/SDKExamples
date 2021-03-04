//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// ---------------------------------------------------------------------------------------------------
		enum ETaggedDataType
		{
			eTaggedDataType_Byte			= kTaggedDataByteArrayTypeID,
			eTaggedDataType_Integer			= kTaggedDataUint32ArrayTypeID,
			eTaggedDataType_Real			= kTaggedDataDoubleArrayTypeID,
			eTaggedDataType_Matrix			= kTaggedDataTramsformMatrixTypeID,
			eTaggedDataType_ColorRef		= kTaggedDataColorRefArrayTypeID,
			eTaggedDataType_InternalIndex	= kTaggedDataObjectRefArrayTypeID,
		};

		// ---------------------------------------------------------------------------------------------------
		typedef Sint32		TTaggedDataTagID;

		class CTaggedDataContainer;
		// ---------------------------------------------------------------------------------------------------
		class CTaggedDataTag
		{
			friend class CTaggedDataContainer;
		public:
								CTaggedDataTag(const CTaggedDataTag& src);
			virtual				~CTaggedDataTag();

			CTaggedDataTag&		operator=(const CTaggedDataTag& src);

		public:
			bool				IsValid() const;

			TTaggedDataTagID	GetID() const;
			ETaggedDataType		GetType() const;

			size_t				GetValuesCount() const;

			Uint8				GetValueUint8(size_t index) const;
			void				SetValueUint8(size_t index, Uint8 value);
			Sint8				GetValueSint8(size_t index) const;
			void				SetValueSint8(size_t index, Sint8 value);
			Uint16				GetValueUint16(size_t index) const;
			void				SetValueUint16(size_t index, Uint16 value);
			Sint16				GetValueSint16(size_t index) const;
			void				SetValueSint16(size_t index, Sint16 value);
			Uint32				GetValueUint32(size_t index) const;
			void				SetValueUint32(size_t index, Uint32 value);
			Sint32				GetValueSint32(size_t index) const;
			void				SetValueSint32(size_t index, Sint32 value);
			double				GetValueReal(size_t index) const;
			void				SetValueReal(size_t index, double value);
			void				SetValueString(const TXString& value);
			TXString			GetValueString() const;
			void				SetValueMatrix(const VWFC::Math::VWTransformMatrix& value);
			VWTransformMatrix	GetValueMatrix() const;
			ColorRef			GetValueColorRef(size_t index) const;
			void				SetValueColorRef(size_t index, ColorRef value);
			InternalIndex		GetValueInternalIndex(size_t index) const;
			void				SetValueInternalIndex(size_t index, InternalIndex value);

		protected:
								CTaggedDataTag();
			void				Set(MCObjectHandle hOwnerObj, OSType ownerID, ETaggedDataType type, TTaggedDataTagID id);

			// general functions for the biggest type
			double				GetValue(size_t index) const;
			void				SetValue(size_t index, double value);

		private:
			MCObjectHandle		fhOwnerObj;
			OSType				fOwnerID;
			ETaggedDataType		fType;
			TTaggedDataTagID	fId;
		};

		// ---------------------------------------------------------------------------------------------------
		class CTaggedDataContainer
		{
		public:
						CTaggedDataContainer(MCObjectHandle hOwnerObj, Uint32 id);
						CTaggedDataContainer(const CTaggedDataContainer& src);
			virtual		~CTaggedDataContainer();

			CTaggedDataContainer&	operator=(const CTaggedDataContainer& src);

		public:
			void			Clear();

			// create used when writing
			CTaggedDataTag	CreateTagUint8(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagSint8(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagUint16(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagSint16(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagUint32(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagSint32(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagReal(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagColor(TTaggedDataTagID id, size_t count = 1);
			CTaggedDataTag	CreateTagString(TTaggedDataTagID id, const TXString& value);
			CTaggedDataTag	CreateTagMatrix(TTaggedDataTagID id, const VWFC::Math::VWTransformMatrix& value);
			CTaggedDataTag	CreateTagInternalIndex(TTaggedDataTagID id, size_t count = 1);

			// get used when reading
			CTaggedDataTag	GetTagUint8(TTaggedDataTagID id);
			CTaggedDataTag	GetTagSint8(TTaggedDataTagID id);
			CTaggedDataTag	GetTagUint16(TTaggedDataTagID id);
			CTaggedDataTag	GetTagSint16(TTaggedDataTagID id);
			CTaggedDataTag	GetTagUint32(TTaggedDataTagID id);
			CTaggedDataTag	GetTagSint32(TTaggedDataTagID id);
			CTaggedDataTag	GetTagReal(TTaggedDataTagID id);
			CTaggedDataTag	GetTagColor(TTaggedDataTagID id);
			CTaggedDataTag	GetTagString(TTaggedDataTagID id);
			CTaggedDataTag	GetTagMatrix(TTaggedDataTagID id);
			CTaggedDataTag	GetTagInternalIndex(TTaggedDataTagID id);

		private:
			MCObjectHandle		fhOwnerObj;
			OSType				fID;
		};
	}
}