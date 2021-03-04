//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace DataCatalog
	{
		// ------------------------------------------------------------------------------------------------------
		enum class EManifestColumnType
		{
			Text,
			Bool,
			Real,
			Int,
			Percent,
			Degree,
			GenericDim,
			// Dimension - size
			in,
			mm,
			// Dimension - distance
			m,
			ft,
			// Pressure
			kPa,
			psi,
			// Flow
			lpm,
			lph,
			gpm,
			gph,
			// Velocity
			mPs,
			ftPs,
			inPh,
			mmPh,
		};

		// ------------------------------------------------------------------------------------------------------
		struct SManifestColumn
		{
			bool				fPullOut;
			bool				fExtend;
			bool				fKey;
			TXString			fParam;		// the parameter, or the left parameter of a range
			TXString			fParam1;	// the right parameter of a range
			EManifestColumnType	fType;
			TXString			fUnivName;
			size_t				fUIColumnDefSize;
			bool				fHideInUI;
			size_t				fDescIndex;
	
			SManifestColumn();
		};

		typedef std::map<size_t, SManifestColumn>		TManifestColumnsMap;
		typedef std::map<TXString,TXString>				TUnivName2ValueMap;

		// ------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IManifest
		{
		public:
			virtual		~IManifest() {}

			virtual void			Load(EFolderSpecifier folderSpec, const TXString& fileName) = 0;

			virtual const TManifestColumnsMap&	GetColumns() const = 0;

			virtual const SManifestColumn*		GetColumn(const char* univName) const = 0;
			virtual size_t						GetColumnIndex(const char* univName) const = 0;
			virtual size_t						GetLastKeyIndex() const = 0;

			virtual bool			DecodeValueDouble(const TXString& value, bool toOriginalUnits, size_t colIndex, bool& outIsPair, double& outPair1, double& outPair2) const = 0;
			virtual TXString		ValueToString(size_t colIndex, bool toOriginalUnits, bool isPair, double pair1, double pair2, bool incUnitMark) const = 0;
		};
	}
}
