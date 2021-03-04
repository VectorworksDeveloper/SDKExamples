//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"
#include "../Math/IPolyDef.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IShapePaneWidgetAccess
		{
		public:
			enum ERealType {
				eRealType_Normal,
				eRealType_Coord,
				eRealType_Angle,
				eRealType_Area,
				eRealType_Volume,
			};

			enum ESubSelButton {
				eSubSelButton_Unknown,
				eSubSelButton_CurrentButtonUp,
				eSubSelButton_CurrentButtonDown,
				eSubSelButton_PrevButtonDown,
				eSubSelButton_PrevButtonUp,
				eSubSelButton_NextButtonDown,
				eSubSelButton_NextButtonUp,
			};

		public:
			virtual						~IShapePaneWidgetAccess()		{}
			virtual IWidgetsProvider*	GetWidgetProvider() = 0;
			// kWidgetLongInt
			virtual Sint32				GetValueInt(SintptrT viewWidget) = 0;
			virtual void				SetValueInt(SintptrT viewWidget, Sint32 value) = 0;
			// kWidgetBoolean
			virtual bool				GetValueBool(SintptrT viewWidget) = 0;
			virtual void				SetValueBool(SintptrT viewWidget, bool value) = 0;
			// kWidgetReal
			// kWidgetCoordDisp
			// kWidgetCoordLocX
			// kWidgetCoordLocY
			// kWidgetAngleDisp
			// kWidgetAreaDisp
			// kWidgetVolumeDisp
			virtual double				GetValueReal(SintptrT viewWidget, ERealType type = eRealType_Normal) = 0;
			virtual void				SetValueReal(SintptrT viewWidget, double value, ERealType type = eRealType_Normal) = 0;
			// kWidgetText
			// kWidgetPopUp
			// kWidgetRadio
			virtual TXString			GetValueString(SintptrT viewWidget) = 0;
			virtual void				SetValueString(SintptrT viewWidget, const TXString& value) = 0;
			// kWidgetDimStdPopUp
			// kWidgetPrecisionPopUp
			virtual Sint32				GetValueLong(SintptrT viewWidget) = 0;
			virtual void				SetValueLong(SintptrT viewWidget, Sint32 value) = 0;
			// kWidgetSubSelection
			virtual ESubSelButton		GetCurrentButton() = 0;
			virtual void				SetHighlightPoint(const WorldPt3& pt) = 0;
			virtual void				ClearHighlightPoint() = 0;
			virtual MCObjectHandle		AddHighlightObject(VectorWorks::Math::IPolyDef* polygon3D) = 0;
			virtual void				RemoveHighlightObject(MCObjectHandle hObject) = 0;

			// kWidgetSliderWithEdit
			virtual void				SetPromptString (SintptrT viewWidget, const TXString& str) = 0;
			virtual double				GetNumber(SintptrT viewWidget) = 0;
			virtual TXString			GetNumberAsString(SintptrT viewWidget) = 0;
			virtual void				SetNumber(SintptrT viewWidget, double value) = 0;
			virtual void				UpdateValueWithSliderPosition (SintptrT viewWidget) = 0;
			virtual void				UpdateSliderPositionWithValue (SintptrT viewWidget) = 0;
			virtual void				SetBoundsAndTickFrequency(SintptrT viewWidget, const Sint32 &minVal, const Sint32 &maxVal, const Sint32 &tickFreqVal) = 0;
			virtual void				SetEditNumber(SintptrT viewWidget, double value) = 0;
			virtual void				SetEditNumber(SintptrT viewWidget, const TXString& value) = 0;
			virtual void				SetSliderNumber(SintptrT viewWidget, double value) = 0;
			virtual void				SetSliderAngle(SintptrT viewWidget, double value) = 0;
			// Enables/Disabled the UI/data linkage between the edit control and the slider
			// If this is enabled then every time the slider moves
			// the UI will update the edit box and vice versa.  If disabled
			// then the core is responsible for updating the other UI
			// element when the shell notifies it that the other has changed.
			// Use IsEditChanged to determine which was modified.
			// Set bEnable True to enable autolink, false to disable.
			// See IsEditChanged
			virtual void				EnableAutoLink(SintptrT viewWidget, bool bEnable) = 0;
			virtual bool				IsEditChanged(SintptrT viewWidget) = 0;

			// kWidgetButtonResourcePopup
			virtual Sint32				ShowPullDownResourcePopup(SintptrT viewWidget, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize = kStandardSize) = 0;
			virtual bool				ShowPullDownResourcePopup(SintptrT viewWidget, VectorWorks::Extension::IResourceManagerContent* content) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		struct SSelectionContext
		{
			bool	fIsHomogMultiSelEdit;
			bool	fIsSingleObjectEdit;
			bool	fIsMultiSelEdit;
			bool	fIsLocked;
			bool	fIsMultipleSelection;
			bool	fIsDimsAndChainsSelection;
		};

		// ----------------------------------------------------------------------------------------------------
		// Constants for predefined fWidgetID when notifying.
		const static Sint32 kWidgetID_FlipButtonForParametricInWall = -100;

		// ----------------------------------------------------------------------------------------------------
		struct SShapePaneWidgetOnWidgetChange
		{
			IShapePaneWidgetAccess*		fWidgetAccess;
			Sint32						fWidgetID;
			SintptrT					fViewWidget;

			bool		fFirstSelObj;	// true when this is the first object in the selection
			bool		fLastSelObj;	// true when this is the last object in the selection
		};

		// ----------------------------------------------------------------------------------------------------
		struct SShapePaneWidgetTransferValue
		{
			bool						fTransferToView;
			MCObjectHandle				fhObject;
			MCObjectHandle				fhFormat;
			MCObjectHandle				fhRecord;
			IShapePaneWidgetAccess*		fWidgetAccess;
			Sint32						fWidgetID;
			SintptrT					fViewWidget;

			bool		fFirstSelObj;	// true when this is the first object in the selection
			bool		fLastSelObj;	// true when this is the last object in the selection
		};

		// ----------------------------------------------------------------------------------------------------
		// {452F49A5-AEC3-4ce7-BFAF-114C569BB4D0}
		static const TSinkIID IID_ProviderShapePane = { 0x452f49a5, 0xaec3, 0x4ce7, { 0xbf, 0xaf, 0x11, 0x4c, 0x56, 0x9b, 0xb4, 0xd0 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderShapePane : public IEventSink
		{
		public:
			virtual void		VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps)											= 0;
			virtual void		VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext)						= 0;
			virtual void		VCOM_CALLTYPE		Deactivate()																				= 0;
			virtual void		VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider)													= 0;
            
            virtual bool VCOM_CALLTYPE		OnPreWidgetChange(SShapePaneWidgetOnWidgetChange& data)												{ return false; }

			// return true if the message is handled. if not handled, the ParametricUIButtonHitMessage will be sent to the parametric
			// outNeedReset will cause the object to be reset by Vectorworks
			// when outChangeOk is false, the UndoAndRemove will be executed.
			//
			// NOTE! The outChangeOk parameter is the equivalent of the return value of the old function!
			//
			virtual bool		VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)	{ return false; }

			// return true if the message is handled and no default translation is to be done
			virtual bool		VCOM_CALLTYPE		TransferValue(SShapePaneWidgetTransferValue& data)											{ return false; }
			virtual bool		VCOM_CALLTYPE		ShouldRecreateWidgets()																		{ return false; }
            virtual void		VCOM_CALLTYPE		OnFullClean()																				{}
			virtual bool		VCOM_CALLTYPE		UpdateStyleWidgets(IWidgetsProvider* widgetProvider, bool hideStyleWidgets )				{ return false; }
			// returns user-defined OIP label. If the result is empty string , then the default OIP label is created.
			virtual TXString	VCOM_CALLTYPE		GetObjectLabel(MCObjectHandle hObject)														{ return TXString(); }

			// This function will be called after each call of OnWidgetChange
			// It will only be considered when the OIP is presented in a preferences, edit style or create dialogs for tools and objects
			// Return 'true' will close the dialog
			virtual bool		VCOM_CALLTYPE		ShouldCloseDialog(bool& outIsClosedWithOK)													{ return false; }

			// This function will be called in CExtendedPropsSupport::PostObjectUIButtonHit
			// It will determine whether the transaction controller should be suspended for layout editing
			// Return true to suspend
			virtual bool		VCOM_CALLTYPE		IsLayoutEditButton(Sint32 widgetID)															{ return false; }

			// This function will be called in CExtendedPropsSupport::PostObjectUIButtonHit
			// It will determine whether the selected object should be marked for selection change only or for modification
			// The viewport system will be suspended if this function returns true, as selection changes do not affect the viewports
			// Return true only when the selected object is not going to be modified to mark it for selection change only.
			virtual bool		VCOM_CALLTYPE		IsSelectionChangeButton(Sint32 widgetID)													{ return false; }

			bool	fFirstObjectInSelection;

		private:
			// Do not use this function, use the equivalent with the extra parameter outChangeOk
			// Also, note that the new function should return true if the event was handled.
			// The return value was changed so the compiler will report for the function change. this function will be removed in future versions
			virtual void		VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset)					{ }
		};
	}
}
