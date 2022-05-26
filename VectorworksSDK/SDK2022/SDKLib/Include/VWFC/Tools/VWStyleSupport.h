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
	
		// --------------------------------------------------------------------------------------------------------
		class VWStyleSupport
		{
		public:
						VWStyleSupport();
			virtual		~VWStyleSupport();
			
		// parametric support
		//	use these functions for context that encapsulates one or several parametric objects
		public:
			bool		InitFromSymbolDefinition( MCObjectHandle hObject );
			bool		CreateUnstyledMap( MCObjectHandle hObject );
			bool		UpdateSymbolDefinition();
			void		SetUnstyled();
			void		ClearStyleSupport();

			TXString	GetStyleName();
			RefNumber	GetStyleRefNumber();
			void		SetStyleName( const TXString& styleName );


		
		// generic
		public:
			bool		AddItem( const TXString& key, EPluginStyleParameter styleType, bool saveStyle = true );
			bool		RemoveItem( const TXString & key );
			bool		KeyExists( const TXString& key );
			bool		GetStyleType( const TXString& key, EPluginStyleParameter & styleType) const;
			bool		SetStyleType( const TXString& key, EPluginStyleParameter styleType);
			bool		SetAllStyleTypes( EPluginStyleParameter styleType );
			bool		IsCatalogParam( const TXString& key );
			bool		IsCatalogParamByParamIndex( const size_t index );

			bool		GetStyleTypeByParamIndex( const size_t index,  EPluginStyleParameter & styleType);
			bool		SetStyleTypeByParamIndex( const size_t index,  EPluginStyleParameter styleType);

			bool		CanChangeParamWithoutConflicts( const TXString& key, bool editingAStyle, std::function<bool()> newValueIsSameAsOld = nullptr ) const;

			MCObjectHandle	GetStyleSourceObject();

			bool		FindPluginObject();

			bool		AddItemToEditList( const TXString& key, EPluginStyleEditList editListType, const TXString& displayName = "" );
			bool		GetStyleEditListType( const TXString& key, EPluginStyleEditList & editListType, TXString & displayName );
			bool		GetStyleEditListTypeByParamIndex( const size_t index, EPluginStyleEditList & editListType, TXString & displayName );
			bool		RemoveItemFromEditList( const TXString& key );
			bool		KeyExistsInEditList( const TXString& key );
			void		LoadEditList();
			void		LoadCatalogList();

			struct SStyleInfo {
				TXString		key;
				size_t			paramIndex;
				EPluginStyleParameter	styleType;
				bool			catalogParameter;

				SStyleInfo();
				~SStyleInfo();
			};

			typedef std::map<TXString, SStyleInfo>	TStyleInfoMap;
			typedef std::pair<TXString, SStyleInfo> TStyleInfo_Pair;	
			typedef std::map <TXString, SStyleInfo> :: iterator TStyleInfo_Iterator;

			TStyleInfoMap			fmapStyleInfo;
			MCObjectHandle			fhHostSymbolDefiniiton;
			MCObjectHandle			fhHostParametricObject;

			struct SStyleEditList {
				TXString				key;
				size_t					paramIndex;
				EPluginStyleEditList	editListType;
				TXString				displayName;

				SStyleEditList();
				~SStyleEditList();
			};

			typedef std::map<TXString, SStyleEditList>	TStyleEditListMap;
			typedef std::pair<TXString, SStyleEditList> TStyleEditList_Pair;	
			typedef std::map <TXString, SStyleEditList> :: iterator TStyleEditList_Iterator;

			TStyleEditListMap			fmapStyleEditList;

			bool				fSupportsCatalogs;
			bool				fCatItemByStyle;


		};

		class VWCatalogSupport {
			public:
							VWCatalogSupport();
				virtual		~VWCatalogSupport();

				void		SetCatalogName( const TXString & catalogName );
				TXString	GetCatalogName();

				bool		IsCatalogParam( const TXString & paramName );

				
				bool		LoadCatalogList( MCObjectHandle hObject );
				bool		SaveCatalogList();

				bool		ClearCatalogList();
	
				TXString	BuildCatalogItemName( MCObjectHandle hInObject = NULL );

				bool		GetCatalogItemByStyle();
				void		SetCatalogItemByStyle( const bool & catItemByStyle );

				size_t	FillCatalogList(MCObjectHandle hParamObj, VWListBrowserCtrl * fpListBrower = NULL, VWPullDownMenuCtrl * fpPullDown = NULL);

								

			typedef TXStringArray TCatalogParamList;			
			
			MCObjectHandle		fHostObject;
			TCatalogParamList	fCatParamList;
			TCatalogParamList	fCatKeyList;
			TCatalogParamList	fCatDescList;
			TXString			fCatalogName;

			bool				fCatItemByStyle;
			
		};
	}
}
