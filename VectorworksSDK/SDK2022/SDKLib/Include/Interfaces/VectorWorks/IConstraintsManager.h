//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	// ------------------------------------------------------------------------------------------------------------------------------------
	// {24CCA927-E577-446B-BDF0-23B90CE42EE8}
	static const VWIID IID_ConstraintsManager = { 0x24cca927, 0xe577, 0x446b, { 0xbd, 0xf0, 0x23, 0xb9, 0xc, 0xe4, 0x2e, 0xe8 } };

	// ------------------------------------------------------------------------------------------------------
	struct SConstraintData
	{
		bool		fLeft				= true;
		bool		fRight				= true;
		bool		fTop				= false;
		bool		fBottom				= false;
		bool		fHorizontalScale	= false;
		bool		fVerticalScale		= false;
		TXString	fText;
		bool		fIsLinkedText		= false;
	};
	using TGetConstrintDataLambda = std::function<bool(MCObjectHandle paramObject, MCObjectHandle hObject, SConstraintData& outData)>;

	// ------------------------------------------------------------------------------------------------------
	struct SDCMContextConstraintData
	{
		bool			fIsLeft				= false;
		bool			fIsRight			= false;
		bool			fIsTop				= false;
		bool			fIsBottom			= false;
		MCObjectHandle	fLeftObj			= nullptr;
		MCObjectHandle	fRightObj			= nullptr;
		MCObjectHandle	fTopObj				= nullptr;
		MCObjectHandle	fBottomObj			= nullptr;
		bool			fIsInsertPtHUsed	= false;
		bool			fIsInsertPtVUsed	= false;
	};
	using TDCMContextConstraintDataMap = std::unordered_map<MCObjectHandle,SDCMContextConstraintData>;

	// ------------------------------------------------------------------------------------------------------------------------------------
	struct SResizableObjectData
	{
		// The width and height of the resized object
		double			fWidth		= 0;
		double			fHeight		= 0;

		// Define the insertion point of the object and in what direction does it resize
		Sint16			fHorizAlign	= 0;
		Sint16			fVertAlign	= 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	using TUpdateConstrainedObjCallback = std::function<void(MCObjectHandle hObject, SResizableObjectData& outResizableObjectData)>;

	class DYNAMIC_ATTRIBUTE ILabelDCMSession
	{
		public:
			virtual					~ILabelDCMSession(){};

		public:
			using TOutputDuplicateCallback = std::function<MCObjectHandle(MCObjectHandle h)>;
			virtual void			SetOutputCallback(TOutputDuplicateCallback Callback) = 0;

			struct STextInfo
			{
				SConstraintData		fConstraintData;
				MCObjectHandle		fhObj = nullptr;
				MCObjectHandle		fhDup = nullptr;
			};

			using TTextFixedWidthCallback = std::function<void(const STextInfo& data, double& outWidth, double& outHeight)>;
			virtual void			SetTextFixedWidthCallback(TTextFixedWidthCallback callback) = 0;

			virtual void			SetUpdateConstrainedObjectCallback(TUpdateConstrainedObjCallback callback) = 0;

			virtual void			SetBoundary(const WorldRectVerts& boundaryRect, bool angle=true) = 0;

			virtual void			AddBasicShape(MCObjectHandle obj, const SConstraintData& constraintData) = 0;
			virtual void			AddText(MCObjectHandle obj, const SConstraintData& constraintData, bool isAlignmentForChanging = false) = 0;
			virtual void			AddParametricObject(MCObjectHandle obj, const VectorWorks::SConstraintData& constraintData) = 0;

			virtual void			Evaluate() = 0;
			virtual void			EvaluateWithBoundaryLength(double& inOutBoundaryLength) = 0;

			virtual WorldPt			GetOriginalBoundLineLeftStart() = 0;
			virtual WorldPt			GetOriginalBoundLineLeftEnd() = 0;
			virtual WorldPt			GetOriginalBoundLineRightStart() = 0;
			virtual WorldPt			GetOriginalBoundLineRightEnd() = 0;

			virtual WorldPt			GetResultBoundLineLeftStart() = 0;
			virtual WorldPt			GetResultBoundLineLeftEnd() = 0;
			virtual WorldPt			GetResultBoundLineRightStart() = 0;
			virtual WorldPt			GetResultBoundLineRightEnd() = 0;

			virtual void			ProcessSavedTexts() = 0;

			virtual const TDCMContextConstraintDataMap&	GetDCMContextConstraintDataMap() = 0;

			virtual void			SetDistributeUnconstrainedObjects(bool distributeUnconstrainedObjects) = 0;
			virtual void			SetAdjustTopLeftResizingObjects(bool adjustTopLeftResizingObjects) = 0;
	};
	typedef std::shared_ptr<ILabelDCMSession>		ILabelDCMSessionPtr;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IConstraintsManager : public IVWUnknown
	{
		public:
			virtual ILabelDCMSessionPtr	VCOM_CALLTYPE CreateDCMSession() = 0;

			virtual bool				VCOM_CALLTYPE AddConstraints(MCObjectHandle paramObject, MCObjectHandle hGroup, ILabelDCMSessionPtr inOutDcmSessionPtr, MCObjectHandle hSkippedObj = nullptr, bool doNotChangeText = false) = 0;

			virtual void				VCOM_CALLTYPE UpdateConstraints(MCObjectHandle hContainer) = 0;
			virtual void				VCOM_CALLTYPE UpdateConstraintsVisibility(MCObjectHandle hContainer, bool areNew = false, bool forceVisibility = false) = 0;

			virtual void				VCOM_CALLTYPE InitBoundaryRect(MCObjectHandle hContainer) = 0;
			virtual void				VCOM_CALLTYPE RemoveBoundaryRect(MCObjectHandle hContainer) = 0;
			virtual void				VCOM_CALLTYPE UpdateBoundaryRect(MCObjectHandle hContainer) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IConstraintsManager> IConstraintsManagerPtr;
}
