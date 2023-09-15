//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"
#include "../IConstraintsManager.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {8A4FD04E-6EC5-4EA0-BA3B-B40CCDCA742D}
		static const TSinkIID IID_ProviderConstraintsManager = { 0x8a4fd04e, 0x6ec5, 0x4ea0, { 0xba, 0x3b, 0xb4, 0xc, 0xcd, 0xca, 0x74, 0x2d } };

		// ----------------------------------------------------------------------------------------------------
		// Provides object specific data to the IConstraintsManager interface
		class DYNAMIC_ATTRIBUTE IProviderConstraintsManager : public IEventSink
		{
			public:
				virtual bool							VCOM_CALLTYPE SupportsConstraints(MCObjectHandle hObject, MCObjectHandle hGroup) { return false; }

				// GetBoundaryClassName is deprecated and not used anymore and does nothing
				virtual bool							VCOM_CALLTYPE /*deprecated*/GetBoundaryClassName(TXString& outClassName) { return false; }

				virtual TGetConstrintDataLambda			VCOM_CALLTYPE GetConstraintDataLambda() { return nullptr; }

				// Return true to display the boundary rect in the specified group
				virtual bool							VCOM_CALLTYPE ShowBoundaryRect(MCObjectHandle hObject, MCObjectHandle hGroup) { return false; }

				// Return false if you want the text object's text wrap to be set to false
				virtual bool							VCOM_CALLTYPE KeepTextWrapState() { return true; }

				// Return true if you want the unconstrained objects to get distributed, if the boundary gets resized.
				// An example for this is the Drawing Label and the ability to change its width.
				virtual bool							VCOM_CALLTYPE DistributeUnconstrainedObjects() { return false; }

				// Return false if you want this object to be EXCLUDED from the boundary rect and from the constraints calculations
				virtual bool							VCOM_CALLTYPE IsConstrainedObject(MCObjectHandle hObject) { return true; }

				// Return a lambda function that takes a resizing constrained PIO from the layout, such as Graphic Legend Image,
				// resizes the object and returns its SResizableObjectData as output parameter.
				// Return nullptr if you do not support such objects in your layout.
				virtual TUpdateConstrainedObjCallback	VCOM_CALLTYPE GetUpdateConstrainedObjCallback() { return nullptr; }

				// Return true if you want objects resizing top by y or left by x to get adjusted, so that they resize in the correct direction.
				// An example for that is a text with Center horizontal alignment, that we want to stay centered, instead of resize to the right only.
				virtual bool							VCOM_CALLTYPE AdjustTopLeftResizingObjects() { return false; }

				// Return true if you are setting outwrBounds to the bounds of the given object that should be used for constraints.
				// This allows you to provide something other than the actual object bounds.
				virtual bool							VCOM_CALLTYPE GetObjectAlternativeBoundsForConstraints(MCObjectHandle inhObj, WorldRect& outwrBounds) { return false; }

				// Set the text object's text.
				// Return false if you don't need to handle it. The newString argument will be set instead.
				virtual bool							VCOM_CALLTYPE SetTextObjectText(MCObjectHandle hTextObject, const TXString& newString) { return false; }

				// Return a callback function that takes two objects handles, such as Graphic Legend Image,
				// and checks if they are horizontally/vertically valid for automatic constraint.
				// Return nullptr if you want to use the default auto constraints checks.
				virtual TAutoConstraintCheckCallback	VCOM_CALLTYPE GetHorizAutoConstraintCheckCallback() { return nullptr; }
				virtual TAutoConstraintCheckCallback	VCOM_CALLTYPE GetVertAutoConstraintCheckCallback() { return nullptr; }

				// Return true if you want to use a customized behavior where frame boundaries are fixed depending on the objects constraints and alignments.
				// Return false if you want to use the standard behavior where top and left boundary are always fixed, resizing in bottom and right direction only.
				virtual bool							VCOM_CALLTYPE GetUseCustomFrameConstraints() { return false; }

				// Return true to allow dynamic objects that are vertically aligned but overlapping to still form a chain
				// Otherwise overlapping objects do not auto constrain and will not form a chain
				virtual bool							VCOM_CALLTYPE AllowVerticalChainOverlap(MCObjectHandle hPIO) { return false; }

				// Return true to allow locus objects to have constraints too in the layout
				virtual bool							VCOM_CALLTYPE IncludeLocusConstraints() { return false; }

		};
	}
}
