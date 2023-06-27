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
		typedef Uint16		TDataIdentifier;
		
		// ---------------------------------------------------------------------------
		class VWDataSerializer;
		class VWDataSerializerGroup;
		class CWriteFromMemoryContext;

		// ---------------------------------------------------------------------------
		class VWDataSerializerContext
		{
		public:
			Sint32		fByteSwap;
			bool		fSaveStringsInMacEncoding;
			bool		fSaveWithSwapBytes;
			
		protected:
			friend class VWDataSerializer;
			VWDataSerializerContext();
			virtual ~VWDataSerializerContext();
		};
		// ---------------------------------------------------------------------------
		class VWDataSerializerValue
		{
			friend class VWDataSerializer;
			friend class VWDataSerializerGroup;
			friend class CWriteFromMemoryContext;
		public:
										VWDataSerializerValue(VWDataSerializerContext& context, Sint8 data);
										VWDataSerializerValue(VWDataSerializerContext& context, Uint8 data);
										VWDataSerializerValue(VWDataSerializerContext& context, Sint16 data);
										VWDataSerializerValue(VWDataSerializerContext& context, Uint16 data);
										VWDataSerializerValue(VWDataSerializerContext& context, Sint32 data);
										VWDataSerializerValue(VWDataSerializerContext& context, Uint32 data);
										VWDataSerializerValue(VWDataSerializerContext& context, Sint64 data);
										VWDataSerializerValue(VWDataSerializerContext& context, double data);
										VWDataSerializerValue(VWDataSerializerContext& context, Uint32 data, const char* szEnum1, ...);
										VWDataSerializerValue(VWDataSerializerContext& context, void* pData, size_t size);
										VWDataSerializerValue(VWDataSerializerContext& context, const TXString& str);
										VWDataSerializerValue(const VWDataSerializerValue& src);
										~VWDataSerializerValue();

			VWDataSerializerValue&		operator=(const VWDataSerializerValue& src);

										operator Sint8() const;
										operator Uint8() const;
										operator Sint16() const;
										operator Uint16() const;
										operator Sint32() const;
										operator Uint32() const;
										operator Sint64() const;
										operator double() const;
										operator TXString() const;
			
			VWDataSerializerContext&	GetContext();
			void						AllowSwappedBytesProcessing();
			
			const TXString&				GetName() const;
			void						SetName(const TXString& name);
			
			VWDataSerializerValue&		SetEnumValues(const char* szEnum1, ...);

			Sint32						GetSIntValue() const;
			Uint32						GetUIntValue() const;
			TXString					GetTXStringValue() const;
			void						SetValue(Sint8 data);
			void						SetValue(Uint8 data);
			void						SetValue(Sint16 data);
			void						SetValue(Uint16 data);
			void						SetValue(Sint32 data);
			void						SetValue(Uint32 data);
			void						SetValue(Sint64 data);
			void						SetValue(double data);
			void						SetValue(void* pData, size_t size);
			void						SetValue(const TXString& str);

			size_t						GetBytesCount() const;
			const void*					GetBytes() const;
			void						CopyInto(void* pData, size_t size) const;

			void						SetValueAsString(const TXString& str);
			// this returns string representation of the data
			// if the data is a memory block, the string representation will be 0x123456789
			// TXString is kept as memory data, so for reading it use 'GetTXStringValue' or 'operator TXString'
			TXString					GetValueAsString();
			// set the value as a string but unknown actually type
			// all get functions will convert the string appropriately
			void						SetValueUnknownType(const TXString& value);

		protected:
			void			SetData(void* pData, size_t size);

			TXString		GetDefaultStringRepresentation() const; // used for the error cases

			VWDataSerializerContext&	m_context;
			TXString					m_name;
			bool						m_bUnkonwnType;
			Uint8*						m_pBytes;
			size_t						m_nBytesCnt;
			TXStringSTLArray			m_arrEnumValues;

			enum class EValueAsStringType
			{
				  Unknown
				, Int
				, Real
				, String
			};

			union TValueAsString
			{
				Sint32				fInt;
				double				fReal;
			};

			EValueAsStringType	m_valueAsStringType;
			TValueAsString		m_valueAsString;
		};

		// ---------------------------------------------------------------------------
		typedef std::vector<VWDataSerializerValue*>		TDataSerializerValuesArray;
		typedef std::vector<VWDataSerializerGroup*>		TDataSerializerGroupsArray;

		// ---------------------------------------------------------------------------
		class VWDataSerializerGroup
		{
			friend class VWDataSerializer;
			friend class CWriteFromMemoryContext;
											VWDataSerializerGroup(VWDataSerializerContext& context, TDataIdentifier id, const char* szName);
		public:
											~VWDataSerializerGroup();

			bool							IsGroupIdentifier(TDataIdentifier id);

			void							ClearChildGroups();
			VWDataSerializerGroup*			CreateChildDataGroup(TDataIdentifier id, const char* szGroupName);
			VWDataSerializerGroup*			FindChildDataGroup(TDataIdentifier id, const char* szGroupName) const;
			void							FindChildDataGroups(TDataSerializerGroupsArray& outArray, TDataIdentifier id, const char* szGroupName) const;
			size_t							GetChildGroupsCount() const;
			VWDataSerializerGroup*			GetChildGorupAt(size_t index);
			
			VWDataSerializerContext&		GetContext();
			void							AllowSwappedBytesProcessing();
			
			const TXString&					GetName() const;
			TDataIdentifier					GetIdentifier() const;

			void							AddValue(const VWDataSerializerValue& value, size_t index, const char* szValueName);
			VWDataSerializerValue			GetValue(size_t index, const char* szValueName) const;
			bool							GetValue(size_t index, const char* szValueName, VWDataSerializerValue& outValue) const;
			bool							HasValue(size_t index, const char* szValueName) const;
			bool							ResetValueString(size_t index, const char* szValueName);

			VWDataSerializerGroup*			GetChildGroup(TDataIdentifier id, const char* szGroupName);

		protected:
			VWDataSerializerValue*			GetValuePtr(size_t index, const char* szValueName) const;

			VWDataSerializerContext&		m_context;
			TDataIdentifier					m_identifier;
			TXString						m_szName;

			TDataSerializerValuesArray		m_arrValues;
			TDataSerializerGroupsArray		m_arrChildGroups;
		};

		// ---------------------------------------------------------------------------
		// Chunk based serializator
		class VWDataSerializer
		{
		public:
										VWDataSerializer(const char* szSerializerName);
			virtual						~VWDataSerializer();

			VWDataSerializerContext&	GetContext();
			void						AllowSwappedBytesProcessing();
			void						SaveStringsInMacEncoding();
			void						SaveWithSwapBytes();

		public:
			class IReadContext
			{
			public:
				virtual			~IReadContext()		{}
				virtual void	BeginGroup(TDataIdentifier id, const char* szGroupName) = 0;
				virtual void	EndGroup(TDataIdentifier id, const char* szGroupName) = 0;
				virtual bool	AddValue(VWDataSerializerContext& context, void* buffer, size_t bufferSize, size_t index, const char* szValueName) = 0; // return false to interrupt traversal
			};

			class IWriteContext
			{
			public:
				virtual			~IWriteContext()		{}

				// Group retrieval functions
				virtual bool			GroupBegin(size_t iGroup) = 0;	// return true if there is a sub group at index 'iGroup'; This call will be called incrementing 'iGroup' until it returns 'false'
				virtual void			GroupEnd(size_t iGroup) = 0;

				virtual TDataIdentifier	GroupGetID() = 0;	// return the ID of the current group (after BeginGroup was called)

				// Value retrieval funcitons
				virtual bool			ValueBegin(size_t iValue) = 0;	// return true if there is a sub group at index 'iGroup'; This call will be called incrementing 'iGroup' until it returns 'false'
				virtual void			ValueEnd(size_t iValue) = 0;

				virtual Uint32			ValueGetByteCnt() = 0;
				virtual void			ValueCopyInto(void* dst, size_t dstSize) = 0;
			};

		public:
			void						ClearChildGroups();
			VWDataSerializerGroup*		CreateChildDataGroup(TDataIdentifier id, const char* szGroupName);
			VWDataSerializerGroup*		FindChildDataGroup(TDataIdentifier id, const char* szGroupName) const;
			void						FindChildDataGroups(TDataSerializerGroupsArray& outArray, TDataIdentifier id, const char* szGroupName) const;
			size_t						GetChildGroupsCount() const;
			VWDataSerializerGroup*		GetChildGorupAt(size_t index);

			// read/save in raw memory
			size_t						GetDataBytesCount() const;
			void						SaveDataInMemory(void* pData) const;
			bool						ReadDataFromMemory(void* pData, size_t size);
			size_t						GetDataBytesCount(IWriteContext* writeContext) const;
			void						SaveDataInMemory(void* pData, IWriteContext* writeContext) const;
			bool						ReadDataFromMemory(void* pData, size_t size, IReadContext* readContext);

			// read/save in Vectorworks settings file
			void						SaveDataInVWSettings() const;
			bool						ReadDataFromVWSettings();

			// read/save in custom XML settings file
			void						SaveDataInXMLSettings(VectorWorks::Filing::IFileIdentifierPtr fileID) const;
			bool						ReadDataFromXMLSettings(VectorWorks::Filing::IFileIdentifierPtr fileID);

			// read/save in custom XML string
			bool						SaveDataInXMLString(TXString& outData) const;
			bool						ReadDataFromXMLString(const TXString& data);

			// read/save in binary file
			void						SaveDataInBinaryFile(VectorWorks::Filing::IFileIdentifierPtr fileID) const;
			bool						ReadDataInBinaryFile(VectorWorks::Filing::IFileIdentifierPtr fileID);

		private:
			size_t						SaveDataInMemoryReq(IWriteContext* context, Uint8* pData) const;
			bool						ReadDataFromMemoryReq(IReadContext* context, Uint8* pData, size_t size);
			void						SaveDataInVWSettingsReq(VWDataSerializerGroup* pGroup, const TXString& category) const;
			bool						ReadDataFromVWSettingsReq(VWDataSerializerGroup* pGroup, const TXString& category);
			void						SaveDataInXMLSettingsReq(VectorWorks::Filing::IXMLFileNodePtr xmlNode, VWDataSerializerGroup* pGroup) const;
			bool						ReadDataFromXMLSettingsReq(VectorWorks::Filing::IXMLFileNodePtr xmlNode, VWDataSerializerGroup* pGroup);

		protected:
			VWDataSerializerContext		m_context;
			VWDataSerializerGroup*		m_pMainGroup;
		};
	}
}
