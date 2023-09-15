//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once


namespace VectorWorks
{
	namespace Extension
	{
		namespace PlantDefinition
		{
			// ----------------------------------------------------------------------------------------------------
			enum class EEnumType
			{
				  All
				, DataPaneOnly
				, DBOnly
				, VisibleInMoreDataPane
			};

			// ----------------------------------------------------------------------------------------------------
			// {FE677989-8143-4869-86E6-C32BEA6881DC}
			static const VWIID IID_PlantRecordDefinition = { 0xfe677989, 0x8143, 0x4869, { 0x86, 0xe6, 0xc3, 0x2b, 0xea, 0x68, 0x81, 0xdc } };

			// ----------------------------------------------------------------------------------------------------------------------------------
			// Access to the plant definition record
			class IPlantRecordDefinition : public IVWSingletonUnknown
			{
			public:
				virtual size_t			GetIndex(const TXString& univName) const = 0;
				virtual const TXString&	GetUniversalNameAt(size_t index) const = 0;
				virtual const TXString&	GetLocalizedName(const TXString& univName) const = 0;
				virtual const TXString&	GetDBName(const TXString& univName) const = 0;
				virtual const TXString&	GetColType(const TXString& univName) const = 0;
				virtual const bool		GetDataPaneOnlyTag(const TXString& univName) const = 0;
				virtual const bool		IsActualData() const = 0;
				virtual void			SetActualData(bool isActualData) = 0;
				virtual void			UpdateRecordDef(const std::vector<TXString>& arrColNames) = 0;
				virtual void			SetShowInVisibilityDlgField( const TXString& univName, bool value ) = 0;

				class IIterator : public IVWUnknown
				{
				public:
					virtual bool			HasMore() const = 0;
					virtual void			Next() = 0;

					virtual const TXString&	GetUniversalName() const = 0;
					virtual const TXString&	GetLocalizedName() const = 0;
					virtual const TXString&	GetDBName() const = 0;
					virtual const TXString&	GetColType() const = 0;
					virtual TNumStyleClass	GetNumStyleClass() const = 0;
					virtual bool			GetShowInVisibilityDlg()const = 0;
					virtual bool			GetDataPaneOnlyTag()const = 0;
				};

				typedef VCOMPtr<IIterator>	IIteratorPtr;

				// iterator accessors
				virtual IIteratorPtr	GetIterator(EEnumType itState) const = 0;
				virtual IIteratorPtr	GetIteratorDB() const = 0;
			};

			typedef VCOMPtr<IPlantRecordDefinition>		IPlantRecordDefinitionPtr;

			// ----------------------------------------------------------------------------------------------------
			// {5AD3E464-FD66-4E8A-8CB5-5A252EEA6680}
			static const VWIID IID_PlantRefRecord = { 0x5ad3e464, 0xfd66, 0x4e8a, { 0x8c, 0xb5, 0x5a, 0x25, 0x2e, 0xea, 0x66, 0x80 } };

			// ----------------------------------------------------------------------------------------------------
			// Base class object update support implementations
			class DYNAMIC_ATTRIBUTE IPlantRefRecord : public IVWUnknown
			{
			public:
				virtual bool			Load(MCObjectHandle h) = 0;
				virtual void			Delete() = 0;
				virtual void			AddBothSwapObject() = 0;

				virtual bool			GetClassCode(TXString& outValue) = 0;

				virtual void			SetLatinName(const TXString& latinName) = 0;
				virtual void			SetCommonName(const TXString& commonName) = 0;
				virtual void			SetPlantID(const TXString& id) = 0;
				virtual void			SetNumberOfPlants(size_t numPlants) = 0;
				virtual void			SetArea(double area) = 0;

				virtual bool			ValidateAndGetParamValue(TXString& name, TXString& outValue, const bool& isCustomTag) = 0;

				virtual size_t			GetRecordFieldsCnt() const = 0;
				virtual TXString		GetRecordFieldValue(const TXString& name) const = 0; // Note: the name is the name of the record field, which is localized
				virtual void			SetRecordFieldValue(const TXString& name, const TXString& value) = 0; // Note: the name is the name of the record field, which is localized

				virtual bool			HasTheRecordAttached(MCObjectHandle h) = 0;
			};

			typedef VCOMPtr<IPlantRefRecord>		IPlantRefRecordPtr;
		}
	}
}
