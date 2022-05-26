//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//



namespace VWFC
{
	namespace VWUI
	{
		struct SChildControls {
			VWControl*		pControl;
			// if we created this control just to return a pointer to it
			// it should be deleted on way out (in the destructor)
			bool			bFake;
		};

		// DDX data
		enum EDDXType {
			kDDXTypeStaticText,
			kDDXTypeCheckButton,
			kDDXTypeCheckButtonBoolean,
			kDDXTypeCheckButtonTriState,
			kDDXTypeCheckGroupBox,
			kDDXTypeColorButton,
			kDDXTypeEditInteger,
			kDDXTypeEditReal,
			kDDXTypeEditText,
			kDDXTypeEditPassword,
			kDDXTypeEditColor,
			kDDXTypeSlider,
			kDDXTypeRadioButton,
			kDDXTypeRadioButtonBoolean,
			kDDXTypeRadioButtonEnum,
			kDDXTypeRadioGroupBox,
			kDDXTypePulldownMenuShort,
			kDDXTypePulldownMenuSizeT,
			kDDXTypePulldownMenuTXString,
			kDDXTypePulldownMenuMarker,
			kDDXTypeListBoxShort,
			kDDXTypeListBoxSizeT,
			kDDXTypeColorPopup,
			kDDXTypeColorPopupCustom,
			kDDXTypePatternPopup,
			kDDXTypeLineAttribPopup,
			kDDXTypeLineStylePopup,
			kDDXTypeLineWeightPopup,
			kDDXTypeMarkerPopup,
			kDDXTypeChooseClassPopupShort,
			kDDXTypeChooseClassPopupSizeT,
			kDDXTypeUnitEditText,
			kDDXTypeSearchEditBox,
			kDDXTypeChooseLayerPopupShort,
			kDDXTypeSearchablePulldownMenuTXString,
			kDDXTypeImagePopup,
			kDDXTypeResourceTextPopup,
			kDDXTypeListBrowser
		};

		struct SDDXData {
			EDDXType		type;
			TControlID		controlID;
			void*			pData;
			void*			pData1;
			void*			pData2;
			void*			pData3;
			Sint32			lData;
			TXString		strData;
			TXString		key;
			TValueFlags		flag;

			std::function<void(double value, TXString& out)>	fCallbackToTxt;
			std::function<double(const TXString& value)> 		fCallbackToValue;

			SDDXData() { flag = 0; fCallbackToTxt = nullptr; fCallbackToValue = nullptr; };
		};

		struct SSavedSettingsItem {
			TXString	name;
			TXString	value;
		};

		typedef std::vector<SChildControls>			TControlsArray;
		typedef std::vector<VWControlsContainer*>	TContainersArray;
		typedef std::vector<SDDXData>				TDDXDataArray;
		typedef std::vector<SSavedSettingsItem>		TSavedSettingsItemsArray;
	}
}
