//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"
#include "IObjectShapePaneProvider.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {83A43848-2DB6-491A-8FA8-B640D294F73F}
		static const TSinkIID IID_ProviderSpecialGroups = { 0x83a43848, 0x2db6, 0x491a, { 0x8f, 0xa8, 0xb6, 0x40, 0xd2, 0x94, 0xf7, 0x3f } };

		
		// ----------------------------------------------------------------------------------------------------
		enum class EPluginComponent
		{
			  Cancel
			, Path
			, Profile
			, SecondProfile
			, StyleProfile
			, StyleSecondProfile
			, Reshape
		};

		enum class EProviderType
		{
			  Unknown
			, Arc
			, Circle
			, Line
			, Oval
			, Polygon
			, Polyline
			, Rectangle
			, RoundedRectangle
			, Text
			, Locus3D
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderSpecialGroups : public IEventSink
		{
		public:
			//These returned strings are used for the orange "exit group" button and menu command 
			virtual TXString VCOM_CALLTYPE		GetPathGroupCustomTitleString0(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetProfileGroupCustomTitleString0(MCObjectHandle h = NULL) = 0;
            virtual TXString VCOM_CALLTYPE		GetManualEdgesGroupCustomTitleString0(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetPathGroupCustomTitleString1(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetProfileGroupCustomTitleString1(MCObjectHandle h = NULL) = 0;
            virtual TXString VCOM_CALLTYPE		GetManualEdgesGroupCustomTitleString1(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetPathGroupCustomTitleString2(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetProfileGroupCustomTitleString2(MCObjectHandle h = NULL) = 0;
            virtual TXString VCOM_CALLTYPE		GetManualEdgesGroupCustomTitleString2(MCObjectHandle h = NULL) = 0;

			//These returned strings are used in the right click context menu 
			virtual TXString VCOM_CALLTYPE		GetContextMenuEditPathString(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetContextMenuEditProfileString(MCObjectHandle h = NULL) = 0;
            virtual TXString VCOM_CALLTYPE		GetContextMenuEditManualEdgesString(MCObjectHandle h = NULL) = 0;

			//These are the strings for the "Choose Component" dialog radio buttons and help
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaTitleString(MCObjectHandle h = NULL) { return ""; }
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaWhichString(MCObjectHandle h = NULL) { return ""; }
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaPathString(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaProfileString(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE	 	GetChooseComponentDiaPathHelpString(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaProfileHelpString(MCObjectHandle h = NULL) = 0;
            virtual TXString VCOM_CALLTYPE      GetChooseComponentDiaManualEdgesString(MCObjectHandle h = NULL) { return ""; };
            virtual TXString VCOM_CALLTYPE      GetChooseComponentDiaManualEdgesHelpString(MCObjectHandle h = NULL) { return ""; };

			// Overloading this next element with a non-"" string adds a reshape option to the Choose Components dialog,
			// which is activated either by "Modify->Edit <item>" or the context menu "Edit" command. If this is overloaded,
			// GetChooseComponentDiaDblClkPDMenuReshapeString below should also be overloaded to add a Reshape option to the double-click menu.
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaReshapeString(MCObjectHandle h = NULL) { return ""; }
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaReshapeHelpString(MCObjectHandle h = NULL) { return ""; }

			// Overloading this next element with a non-"" string adds a reshape option to the Choose Components dialog,
			// which is activated either by "Modify->Edit <item>" or the context menu "Edit" command. If this is overloaded,
			// GetChooseComponentDiaDblClkPDMenuDrainageString below should also be overloaded to add a Drainage option to the double-click menu.
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDrainageString(MCObjectHandle h = NULL) { return ""; }
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDrainageHelpString(MCObjectHandle h = NULL) { return ""; }

			//These strings are used to populate the "Chose Component" dialog double-click behavior PD menu. 
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDblClkPDMenuHelpString(MCObjectHandle h = NULL) { return ""; }
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDblClkPDMenuPathString(MCObjectHandle h = NULL) = 0;
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDblClkPDMenuProfileString(MCObjectHandle h = NULL) = 0;

			//overload this with a non-null string if GetChooseComponentDiaReshapeString has been overloaded.
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDblClkPDMenuReshapeString(MCObjectHandle h = NULL) { return ""; }
            virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDblClkPDMenuManualEdgesString(MCObjectHandle h = NULL) { return ""; }

			//overload this with a non-null string if GetChooseComponentDiaDrainageString has been overloaded.
			virtual TXString VCOM_CALLTYPE		GetChooseComponentDiaDblClkPDMenuDrainageString(MCObjectHandle h = NULL) { return ""; }
			
			//Return false to disable reset while in group edit
			virtual bool VCOM_CALLTYPE			AllowInPlaceEditBehavior(MCObjectHandle h = NULL) = 0;

			//Called for edit object when kObjectEditGroupPropertyID is Sint8(kObjXPropEditGroupCustom)
			// return true if handled.
			virtual bool VCOM_CALLTYPE			ChoosePluginComponentToEdit(MCObjectHandle h, EPluginComponent& outResult, bool& outIsEdit3D) { return false; }

			//Called when user enters group edit modes. Return false to exit. Be carefull! Probably a lot of
			//opportunities to create problems here.
			virtual bool VCOM_CALLTYPE			OnEnterProfileGroup(MCObjectHandle h)		{ return false; }
			virtual bool VCOM_CALLTYPE			OnEnterSecondProfileGroup(MCObjectHandle h) { return false; }
			virtual bool VCOM_CALLTYPE			OnEnterPathGroup(MCObjectHandle h)			{ return false; }
            virtual bool VCOM_CALLTYPE			OnEnterManualEdgesGroup(MCObjectHandle h)	{ return false; }
			
			//Return true when need Fit to Objects command executed
			virtual bool VCOM_CALLTYPE			AllowFitToObject(MCObjectHandle h)			{ return false; }

			//VW2021
			//This returned strings are used for the orange "exit group" button and menu command
			virtual bool VCOM_CALLTYPE			GetSpecialGroupCustomTitleStrings(MCObjectHandle h, TXString& outString0, TXString& outString1, TXString& outString2) { return false; }

			// This will be called, if kObjXPropShowOthersEditGroup is ObjXPropEditGroupCustom.
			virtual bool VCOM_CALLTYPE			ShowOthersEditGroupForSpecialGroup(MCObjectHandle h) { return true; }

			virtual IObjectShapePaneProviderPtr	VCOM_CALLTYPE	GetObjectShapePaneProvider(MCObjectHandle h, const EProviderType& type) { return IObjectShapePaneProviderPtr(); }

			virtual bool VCOM_CALLTYPE			CheckExitGroupConditions(MCObjectHandle h, MCObjectHandle hGroup) { return true; /*true to allow exit*/ }

			//VW2022
			virtual bool VCOM_CALLTYPE			ShowParametricObjectForSpecialGroup(MCObjectHandle h) { return true; }
		};
	}
}
