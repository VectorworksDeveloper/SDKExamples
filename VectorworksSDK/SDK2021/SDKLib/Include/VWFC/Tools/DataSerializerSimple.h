//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "DataSerializer.h"

namespace VWFC
{
	namespace Tools
	{
		// ---------------------------------------------------------------------------
		// Centralized energy data in a VW handle accessor
		// The category specifies what is the user data node tag that stores this data, so we can support sets of data in a handle
		// Uses VWDataSerializer for the actual storage
		class VWDataSerializerSimple
		{
		public:
						VWDataSerializerSimple();
						VWDataSerializerSimple(MCObjectHandle h, Uint32/*FourCharCode*/ category);
						VWDataSerializerSimple(const VWDataSerializerSimple& src);
			virtual		~VWDataSerializerSimple();

			bool		Load();
			bool		Save(bool undo=false);

			void		Clear();

			bool		IsLoaded() const;

			VWDataSerializer&	GetSerializer();

		public:
			struct GroupID
			{
				GroupID(TDataIdentifier id)									{ groupID_level1 = id; groupID_level2 = -1; }
				GroupID(TDataIdentifier id, TDataIdentifier id2)			{ groupID_level1 = id; groupID_level2 = id2; }

				TDataIdentifier		groupID_level1;
				TDataIdentifier		groupID_level2;
			};

			bool		HasValue(const GroupID& groupID, size_t valueIndex) const;

			// fast accessor functions
			// however, if multiple calls to GetValue are needed, it might be faster to call Load first
			bool		GetValueBool		(const GroupID& groupID, size_t valueIndex, bool defaultValue) const;
			Sint8		GetValueSint8		(const GroupID& groupID, size_t valueIndex, Sint8 defaultValue) const;
			Uint8		GetValueUint8		(const GroupID& groupID, size_t valueIndex, Uint8 defaultValue) const;
			Sint16		GetValueSint16		(const GroupID& groupID, size_t valueIndex, Sint16 defaultValue) const;
			Uint16		GetValueUint16		(const GroupID& groupID, size_t valueIndex, Uint16 defaultValue) const;
			Sint32		GetValueSint32		(const GroupID& groupID, size_t valueIndex, Sint32 defaultValue) const;
			Uint32		GetValueUint32		(const GroupID& groupID, size_t valueIndex, Uint32 defaultValue) const;
			size_t		GetValueSizeT		(const GroupID& groupID, size_t valueIndex, size_t defaultValue) const;
			double		GetValueDouble		(const GroupID& groupID, size_t valueIndex, double defaultValue) const;
			TXString	GetValueTXString	(const GroupID& groupID, size_t valueIndex, const TXString& defaultValue) const;
			template<class T>
			T			GetValueEnum		(const GroupID& groupID, size_t valueIndex, const T& defaultValue) const;
			// a set of gets that return success
			bool		GetValueOutBool		(const GroupID& groupID, size_t valueIndex, bool& outValue) const;
			bool		GetValueOutSint8	(const GroupID& groupID, size_t valueIndex, Sint8& outValue) const;
			bool		GetValueOutUint8	(const GroupID& groupID, size_t valueIndex, Uint8& outValue) const;
			bool		GetValueOutSint16	(const GroupID& groupID, size_t valueIndex, Sint16& outValue) const;
			bool		GetValueOutUint16	(const GroupID& groupID, size_t valueIndex, Uint16& outValue) const;
			bool		GetValueOutSint32	(const GroupID& groupID, size_t valueIndex, Sint32& outValue) const;
			bool		GetValueOutUint32	(const GroupID& groupID, size_t valueIndex, Uint32& outValue) const;
			bool		GetValueOutSizeT	(const GroupID& groupID, size_t valueIndex, size_t& outValue) const;
			bool		GetValueOutDouble	(const GroupID& groupID, size_t valueIndex, double& outValue) const;
			bool		GetValueOutTXString	(const GroupID& groupID, size_t valueIndex, TXString& outValue) const;
			template<class T>
			bool		GetValueOutEnum		(const GroupID& groupID, size_t valueIndex, T& outValue) const;

			bool		GetValueMemory		(const GroupID& groupID, size_t valueIndex, std::vector<char>& outValue) const;

			// set functions must be used after Load, and a Save must be called to store the information in the handle
			// note, these operations can be potentially show
			void		SetValueBool		(const GroupID& groupID, size_t valueIndex, bool value);
			void		SetValueSint8		(const GroupID& groupID, size_t valueIndex, Sint8 value);
			void		SetValueUint8		(const GroupID& groupID, size_t valueIndex, Uint8 value);
			void		SetValueSint16		(const GroupID& groupID, size_t valueIndex, Sint16 value);
			void		SetValueUint16		(const GroupID& groupID, size_t valueIndex, Uint16 value);
			void		SetValueSint32		(const GroupID& groupID, size_t valueIndex, Sint32 value);
			void		SetValueUint32		(const GroupID& groupID, size_t valueIndex, Uint32 value);
			void		SetValueSizeT		(const GroupID& groupID, size_t valueIndex, size_t value);
			void		SetValueDouble		(const GroupID& groupID, size_t valueIndex, double value);
			void		SetValueTXString	(const GroupID& groupID, size_t valueIndex, const TXString& value);
			template<class T>
			void		SetValueEnum		(const GroupID& groupID, size_t valueIndex, const T& value);
			void		SetValueMemory		(const GroupID& groupID, size_t valueIndex, const std::vector<char>& value);

			bool		ResetValueString	(const GroupID& groupID, size_t valueIndex);

			size_t		GetGroupCount();
			size_t		GetChildGroupCount(const GroupID& groupID);
			void		ClearChildGroups	(const GroupID& groupID);

		private:
			VWDataSerializerSimple&		operator=(const VWDataSerializerSimple&); // hidden, use the copy constructor instead

		private:
			VWDataSerializerGroup*		GetGroup(const GroupID& groupID) const;
			VWDataSerializerGroup*		GetCreateGroup(const GroupID& groupID);
			void						ReadLocal(VWDataSerializer::IReadContext* context) const;

			class CLocalReader : public VWDataSerializer::IReadContext
			{
			public:
							CLocalReader(const GroupID& groupID, size_t valueIndex);
				virtual		~CLocalReader();

				bool					HasValue() const;
				bool					HasValue(size_t bytesCnt) const;
				VWDataSerializerValue*	GetValue();

			public:
				virtual void	BeginGroup(TDataIdentifier id, const char* szGroupName);
				virtual void	EndGroup(TDataIdentifier id, const char* szGroupName);
				virtual bool	AddValue(VWDataSerializerContext& context, void* buffer, size_t bufferSize, size_t index, const char* szValueName); // return false to interrupt traversal

			private:
				const GroupID&			fGroupID;
				size_t					fValueIndex;
				VWDataSerializerValue*	fValue;

				static const size_t	kDataIdentifiersSize	= 5;
				TDataIdentifier	farrDataIdentifiers[ kDataIdentifiersSize ];
				size_t			fDataIdentifierIndex;
			};

		private:
			MCObjectHandle		fhObject;
			Uint32				fDataTag;
			mutable VWDataSerializer fSerializer;
			bool				fLoaded;
		};

		// ----------------------------------------------------------------------------------------------------
		// {20027E9A-3E9C-488D-94CB-8B85DF6F2804}
		static const VWGroupID GROUPID_DataSerializerTranslate = { 0x20027e9a, 0x3e9c, 0x488d, { 0x94, 0xcb, 0x8b, 0x85, 0xdf, 0x6f, 0x28, 0x4 } };

		// ----------------------------------------------------------------------------------------------------
		// Base class for user node based on Data Serializer translate between Vectorworks 2017 and Vectorworks 2018
		class DYNAMIC_ATTRIBUTE IDataSerializerTranslate : public IVWSingletonUnknown
		{
			// Note:
			//	You SHOULD NOT access the document at this time as it is not fully loaded/saved yet
			//	This function is only to work with the 'serializer' provided as it has a safe copy of the data
		public:
			// implement this to return all UserData node types that this implementation can handle
			virtual void	VCOM_CALLTYPE GetTagIDs(std::vector<OSType>& outArr) = 0;

			enum class TranslateType
			{
				  VWDataSerializer
				, VWDataSerializerSimple
				, Generic
				, TaggedData
			};

			virtual TranslateType	VCOM_CALLTYPE GetTranslateType(OSType tagID) = 0;

			// implement this function to handle TXString data translation
			// you must just read and write the string values (you can use single function for that)
			// Example:
			//	VWDataSerializerGroup*	pVisualGroup			= serializer.FindChildDataGroup( kVisualGroupID );
			//	VWDataSerializerGroup*	pVisualGraphicsGroup	= pVisualGroup->FindChildDataGroup( kVisualGraphicsGroupID );
 			//	VWDataSerializerGroup*	pVGSiteClassingGroup	= pVisualGraphicsGroup->FindChildDataGroup( kVisualGraphicsClassingGroupID );
			//	pVGSiteClassingGroup->ResetValueString( kClassing_2DContoursMajorClass		);
			//	pVGSiteClassingGroup->ResetValueString( kClassing_2DContoursMajorPropClass	);
			//	...
			virtual void	VCOM_CALLTYPE Translate(OSType tagID, VWDataSerializer& serializer) {};

			// implement this function to handle TXString data translation
			// you must just read and write the string values (you can use single function for that)
			// Example:
			//	TBD
			//	...
			virtual void	VCOM_CALLTYPE Translate(OSType tagID, VWDataSerializerSimple& serializer) {};

			virtual bool	VCOM_CALLTYPE GetDynamicTagIDs(OSType type, VWDataSerializer& serializer, std::vector<OSType>& outArr){ outArr.clear(); return false; };
			virtual bool	VCOM_CALLTYPE GetDynamicTagIDs(OSType type, VWDataSerializerSimple& serializer, std::vector<OSType>& outArr){ outArr.clear(); return false; };

			// Generic translation
			virtual size_t	VCOM_CALLTYPE GenericConvertFromVW22ToVW23_GetNewSize(OSType tagID, const void* oldData, size_t oldDataSize) { return 0; };
			virtual void	VCOM_CALLTYPE GenericConvertFromVW22ToVW23_Copy(OSType tagID, const void* oldData, size_t oldDataSize, void* newData, size_t newDataSize) {};
			virtual size_t	VCOM_CALLTYPE GenericConvertFromVW23ToVW22_GetNewSize(OSType tagID, const void* oldData, size_t oldDataSize) { return 0; };
			virtual void	VCOM_CALLTYPE GenericConvertFromVW23ToVW22_Copy(OSType tagID, const void* oldData, size_t oldDataSize, void* newData, size_t newDataSize) {};

			// For TaggedData
			virtual bool	VCOM_CALLTYPE IsTaggedDataString(OSType type, TDataIdentifier tagID, Uint64 version){ return false; };
			virtual bool	VCOM_CALLTYPE HasVersion(OSType type, TDataIdentifier& outVersionTagID){ return false; };
		};
	}
}

// --------------
// Implementation
namespace VWFC
{
	namespace Tools
	{
		// ---------------------------------------------------------------------------
		template<class T> T VWDataSerializerSimple::GetValueEnum(const GroupID& groupID, size_t valueIndex, const T& defaultValue) const
		{
			T result = (T) this->GetValueSint16( groupID, valueIndex, (Sint16) defaultValue );
			return result;
		}

		template<class T> bool VWDataSerializerSimple::GetValueOutEnum(const GroupID& groupID, size_t valueIndex, T& outValue) const
		{
			Sint16	value = 0;
			bool result = this->GetValueOutSint16( groupID, valueIndex, value );
			outValue = (T) value;
			return result;
		}

		template<class T> void VWDataSerializerSimple::SetValueEnum(const GroupID& groupID, size_t valueIndex, const T& value)
		{
			this->SetValueSint16( groupID, valueIndex, (Sint16) value );
		}
	}
}
