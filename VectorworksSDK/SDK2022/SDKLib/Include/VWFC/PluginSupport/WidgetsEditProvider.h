//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		// ------------------------------------------------------------------------------------------------------
		class CWidgetsEditProvider
		{
		public:
						CWidgetsEditProvider(	CodeRefID			objectID,
												TComponentTypeID	compType		= VectorWorks::Extension::kObjectRootComponentTypeID);

						CWidgetsEditProvider(	VectorWorks::Extension::IExtendedProps*		extProps,
												CodeRefID									objectID,
												TComponentTypeID							compType		= VectorWorks::Extension::kObjectRootComponentTypeID);

						CWidgetsEditProvider(	MCObjectHandle		hObject,
												TComponentTypeID	compType		= VectorWorks::Extension::kObjectRootComponentTypeID);


						CWidgetsEditProvider(	VectorWorks::Extension::IExtendedProps*		extProps,
											 	const TXString& 							recordFormatName );

			virtual		~CWidgetsEditProvider();

			VectorWorks::Extension::IWidgetsEditProvider*	operator->();

		public:
			class CWidget
			{
			public:
							CWidget();
							CWidget(const CWidget& src);
				virtual		~CWidget();
				CWidget&	operator=(const CWidget& src);

				Sint32		GetID() const;

				CWidget&	SetIndent(Sint32 indent);
				CWidget&	SetVisible(bool value);
				CWidget&	SetEnabled(bool value);
				CWidget&	SetRed(bool value);
				CWidget&	SetRotatedCoord(bool value);
				CWidget&	SetReadOnly(bool value = true);

				void		ClearPopupItems();
				void		AddPopupItem(const TXString& idName, const TXString& text);
				const SWidgetDefinition* GetWidgetDefinition(){return fWidgetDef;}

			protected:
				friend class CWidgetsEditProvider;
							CWidget(CWidgetsEditProvider* provider, Sint32 widgetID);


			private:
				SWidgetDefinition*		fWidgetDef;
			};

		public:
			void		Clear();

			// String Widget ID
			CWidget		AddWidget(const char* widgetID, const TXString& paramName);
			CWidget		AddWidget(const char* widgetID, const TXString& paramName, const TXString& localizedName);
			CWidget		AddWidget(const char* widgetID, EWidgetType widgetType, const TXString& paramName, const TXString& localizedName);
			CWidget		AddWidget(const char* widgetID, EWidgetType widgetType, const TXString& localizedName);

			CWidget		AddWidget_BoundPopup(const char* widgetID, VectorWorks::TObjectBoundID boundID, bool isTopBound, const TXString& localizedName);
			CWidget		AddWidget_BoundOffset(const char* widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName);
			CWidget		AddWidget_BoundOffset(const char* widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName, const TXString& legacyOffsetParam);

			CWidget		GetWidget(const char* widgetID);

			// This funtion will read the choices from the popup parameter and update the widget, see VWParametricObj::PopupSetChoices
			// Typically, this function will be used during IProviderShapePane::Activate or when choices change via the OIP
			// If it must be used during IProviderShapePane::Update, you must take care for performance. Essentially, use another boolean parameter to denote when the list is dirty and needs to be updated
			// 'h' can be a parametric, a record, or a format
			CWidget		UpdatePopupWidgetChoices(const char* widgetID, MCObjectHandle h, const TXString& paramName);

			// Numeric Widget ID
			CWidget		AddWidget(Sint32 widgetID, const TXString& paramName);
			CWidget		AddWidget(Sint32 widgetID, const TXString& paramName, const TXString& localizedName);
			CWidget		AddWidget(Sint32 widgetID, EWidgetType widgetType, const TXString& paramName, const TXString& localizedName);
			CWidget		AddWidget(Sint32 widgetID, EWidgetType widgetType, const TXString& localizedName);

			CWidget		AddWidget_BoundPopup(Sint32 widgetID, VectorWorks::TObjectBoundID boundID, bool isTopBound, const TXString& localizedName);
			CWidget		AddWidget_BoundOffset(Sint32 widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName);
			CWidget		AddWidget_BoundOffset(Sint32 widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName, const TXString& legacyOffsetParam);

			CWidget		GetWidget(Sint32 widgetID);

			// see comment above for this function
			CWidget		UpdatePopupWidgetChoices(Sint32 widgetID, MCObjectHandle h, const TXString& paramName);

			IWidgetsProvider*	GetWidgetsProvider();

		protected:
			friend class	CWidget;

			VCOMPtr<VectorWorks::Extension::IExtendedProps>	fExtProps;
			VectorWorks::Extension::IWidgetsEditProvider*	fWidgetsProvider;
		};
	}
}
