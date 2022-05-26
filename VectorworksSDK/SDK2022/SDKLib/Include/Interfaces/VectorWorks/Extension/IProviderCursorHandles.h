//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"

// This provider allows a parametric object to supply reshape handles displayed by the cursor tool
// The handles are created using the following calls during object reset:
//		IISDK::CustomObjectControlPtsCreate
//		IISDK::CustomObjectControlPtsRemove
//		IISDK::CustomObjectControlPtSet
//
// Also it allows the plug-in to manage the mouse events for these handles as they are moved by the cursor tool
//
namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum ECursorHandleType
		{
			eCursorHandleType_Normal,
			eCursorHandleType_Image,
			eCursorHandleType_ImageWithPopup,
			eCursorHandleType_ImageWithPopupOnly,
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ICursorHandleGetContext
		{
		public:
			virtual			~ICursorHandleGetContext()		{}

			virtual	MCObjectHandle	GetObject() = 0;
			virtual	Sint32			GetCustomPtClientID() = 0;	// used by ISDK::CustomObjectControlPtSet set of functions
		}
		;

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ICursorHandleActionContext
		{
		public:
			virtual		~ICursorHandleActionContext()	{}

			virtual	MCObjectHandle	GetObject() = 0;
			virtual	Sint32			GetCustomPtClientID() = 0;	// used by ISDK::CustomObjectControlPtSet set of functions
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ICursorHandleDrawContext
		{
		public:
			virtual		~ICursorHandleDrawContext()	{}

			virtual	MCObjectHandle	GetObject() = 0;
			virtual	void			DrawDashedLine(const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID coordinatesInPlane = kPlanarRefID_ScreenPlane) = 0;
			// draw dashed object of the specified 'objectType'. The 'predrawSetupCallback' will be called before the draw for the user to setup the object which is of type 'objectType'
			virtual void			DrawDashedObject(short objectType, std::function<void(MCObjectHandle h)> predrawSetupCallback) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {88311AB9-9F69-4093-9AB1-6D9F00DAD543}
		static const TSinkIID IID_ProviderCursorHandles = { 0x88311ab9, 0x9f69, 0x4093, { 0x9a, 0xb1, 0x6d, 0x9f, 0x0, 0xda, 0xd5, 0x43 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderCursorHandles : public IEventSink
		{
		public:
			virtual ECursorHandleType	GetHandleType(ICursorHandleGetContext* context)									{ return eCursorHandleType_Normal; }
			virtual TXString			GetHandleCueText(ICursorHandleGetContext* context)								{ return ""; }
			virtual TXString			GetHandleCursorSpec(ICursorHandleGetContext* context)							{ return ""; }
			virtual TXString			GetHandleImageSpec(ICursorHandleGetContext* context, ViewPt& outImageOffset)	{ return ""; }
			virtual bool				GetHandleIsVisible(ICursorHandleGetContext* context)							{ return true; }

			virtual bool				OnCursorAction_MouseDown(ICursorHandleActionContext* context)	{ return false /*not handled*/; }
			virtual bool				OnCursorAction_Complete(ICursorHandleActionContext* context)	{ return false /*not handled*/; }
			virtual bool				OnCursorAction_MouseMove(ICursorHandleActionContext* context)	{ return false /*not handled*/; }
			virtual void				OnCursorAction_Draw(ICursorHandleActionContext* context)		{ }
			virtual void				OnCursorAction_Cancel(ICursorHandleActionContext* context)		{ }

		// VW2016
		public:
			virtual bool				IsDefaultCursorHandled()										{ return false; }
			virtual void				OnPrePkSelDraw(ICursorHandleDrawContext* context)				{ }

		// VW2017
		public:
			virtual bool				GetPopupBounds(ICursorHandleGetContext* context, ViewRect& outBounds)					{ return false; }
			virtual void				GetPopupChoices(ICursorHandleActionContext* context, IContextMenuProvider* menuProvider)	{ }
			virtual void				OnPopupChoice(ICursorHandleActionContext* context, size_t selIndex)							{ }
			virtual void				OnCustomBarEvent(ICursorHandleActionContext* context, const CustomBarEventData& data)		{ }
			virtual bool				Allow3DResize()													{ return false; }

		// VW2021
		public:
			virtual bool				SuppressDefaultLineLikeBoxLikeResizeGrips()						{ return false; }
		};
	}
}