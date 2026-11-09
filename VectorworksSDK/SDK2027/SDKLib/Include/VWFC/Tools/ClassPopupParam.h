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
		class CClassPopupParam
		{
		public:
			CClassPopupParam();
			CClassPopupParam( const CClassPopupParam& inClassPopupParam );
			~CClassPopupParam();

			inline const TXString& 	GetActualClassName() const;
			inline const TXString& 	GetRecordClassName() const;
			bool					IsObjectClassUsed() const;

			void 				Set( const TXString& strActualOrRecordName, const TXString& strObjClassName = TXString() );
			void 				Set( const TXString& strActualOrRecordName, MCObjectHandle hParametricObj );

			void 				Read( MCObjectHandle hParametricObj, const TXString& strUnivParamName );
			void 				Write( MCObjectHandle hObj, const TXString& strUnivParamName ) const;

			void				Process(	CParamProviderAbstract&	paramProvider,
											const bool				bRead,
											const CClassPopupParam&	cppPrev,
											const size_t			nParamIndex,
											const TXString&			strObjClassName );
			void				Process(	CParamProviderAbstract&	paramProvider,
									   		const bool				bRead,
									   		const CClassPopupParam&	cppPrev,
									   		const size_t			nParamIndex,
									   		MCObjectHandle			hParametricObj );

			void 				UseObjectClass( MCObjectHandle hParametricObj );
			void 				UseObjectClass( const TXString& strInObjectClassName );

			CClassPopupParam&	operator=( const CClassPopupParam& inClassPopupParam );
			bool 				operator==( const CClassPopupParam& inClassPopupParam ) const;
			bool 				operator!=( const CClassPopupParam& inClassPopupParam ) const;

			bool				AreRecordClassNamesEqual( const CClassPopupParam& inClassPopupParam ) const;
			bool				AreActualClassNamesEqual( const CClassPopupParam& inClassPopupParam ) const;

			// tools for object <-> dialog communication
		public:
			// Object -> Dialog
			static void			ConvertClassPopupObjDataToDlgData
				(	TXString&				strOutDlgChoice,
					short&					nOutChoice,
					const CClassPopupParam&	inRecChoice,
					const short&			nInUseObjClassLabelPos,
					const TXString&			strInUseObjClassLabel );
			static void			ConvertClassPopupObjDataToDlgData
				(	TXString&				strOutDlgChoice,
					short&					nOutChoice,
					const TXString&			strInRecChoice,
					const TXString& 		strInUseObjectClassLabelChoice,
					const short				nInUseObjectClassLabelChoice );
			
			// Dialog -> Object
			static void			ConvertClassPopupDlgDataToObjData
				(	CClassPopupParam&		outRecChoice,
					const TXString&			strInDlgChoice,
					const short&			nInChoice,
					const short&			nInUseObjClassLabelPos,
					const TXString&			strObjClassName );
			static void			ConvertClassPopupDlgDataToObjData
				(	CClassPopupParam&		outRecChoice,
					const TXString&			strInDlgChoice,
					const short&			nInChoice,
					const short&			nInUseObjClassLabelPos,
					MCObjectHandle			hParametricObj );
			static void			ConvertClassPopupDlgDataToObjData
				(	TXString&				strOutRecChoice,
					const TXString&			strInDlgChoice,
					const short&			nInChoice,
					const short				nInUseObjectClassLabelChoice );

		private:
			void				ObtainActualClass
				(	TXString& 		strOutClassNameActual,
					TXString& 		strInOutClassNameFromRec,
					const TXString&	strObjectClass );

		private:
			TXString fstrRecordName;
			TXString fstrActualName;
		};

		// --------------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------------
		inline const TXString& CClassPopupParam::GetActualClassName() const
		{
			return fstrActualName;
		}

		// --------------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------------
		inline const TXString& CClassPopupParam::GetRecordClassName() const
		{
			return fstrRecordName;
		}


		// --------------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------------
		class CClassPopupParamUpdater
		{
		public:
			CClassPopupParamUpdater();
			~CClassPopupParamUpdater();

			void AddClassNamePair( const TXString& strClassNameOld, const TXString& strClassNameNew );

			// Routine 1: Straight update of the parametric record fields given the classes' name replacement pairs.
			void Update( MCObjectHandle hObj = gSDK->GetDrawingHeader() );

			// Routine 2:
			// First collect parametric records (kRecordNode) as well as their parents (kFormatNode and kParametricNode).
			void CollectRecordsFormatsParametrics( MCObjectHandle hObj = gSDK->GetDrawingHeader() );

			// Get the parents (kFormatNode and kParametricNode) on demand.
			const VWFC::VWObjects::TMCObjectHandlesSTLArray& GetCollectedFormatsParametrics() const;
			
			// Update the fields of the parametric records (kRecordNode) on demand.
			void UpdateCollectedRecords() const;

		private:
			//   Updates the current choices of all class pop-up record fields in all records
			//   that exist in the current Vectorworks document if the names of the classes e.g.
			//   the names of the current choices of the class pop-ups coincide with the names of
			//   the classes that have been changed in the class tab pane.
			//   This is the multiple classes' name change handling version.
			void UpdateClassPopupFields( MCObjectHandle hObj = gSDK->GetDrawingHeader() );

			// Routine 2
			void Collect( MCObjectHandle hObj = gSDK->GetDrawingHeader() );

		private:
			typedef std::map< TXString, TXString > TOldNewClassNamePairsSTLMap;
			TOldNewClassNamePairsSTLMap	fOldNewClassNamesMap;
			// Performance
			TOldNewClassNamePairsSTLMap::const_iterator	fiterClassNamePairsEnd;
			TOldNewClassNamePairsSTLMap::const_iterator	fiterClassNamePairsFound;

			// Routine 2 specific
			// std::map never invalidates its iterators, so a pointer to the replacement string is kept.
			typedef std::pair< size_t, const TXString* > TParamIDNewClassNamePtrPair;
			typedef std::vector< TParamIDNewClassNamePtrPair > TParamIDNewClassNamePtrVect;

			typedef std::pair< MCObjectHandle, TParamIDNewClassNamePtrVect > TRecHandParamsToUpdatePair;
			typedef std::vector< TRecHandParamsToUpdatePair > TRecHandParamsToUpdateVect;
			
			TRecHandParamsToUpdateVect farrRecObjs;
			// Performance
			TRecHandParamsToUpdateVect::iterator fiterRecObjsBack;

			VWFC::VWObjects::TMCObjectHandlesSTLArray farrPrmRecObjsParents;
			
			// Performance
			static const size_t fsknInitParamsCount;
		};
	}
}
