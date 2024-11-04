//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {75912CAB-2E60-4622-A027-15831A6FB2C3}
		static const TSinkIID IID_AssemblyUnitObject = { 0x75912cab, 0x2e60, 0x4622, { 0xa0, 0x27, 0x15, 0x83, 0x1a, 0x6f, 0xb2, 0xc3 } };
		
		// ----------------------------------------------------------------------------------------------------
		//
		class DYNAMIC_ATTRIBUTE IAssemblyUnitObject : public IEventSink
		{
		public:
			// Standalone Assembly Unit objects may generate geometry that is undesired when it is a member of an assembly,
			// because the Assembly object is responsible for generating it instead
			//
			// In the case of Doors and Windows, the most important example is the Jamb, which (when the "Use unit-provided
			// frames" option is false) is replaced with the Assembly Frame and Mullions, but the case is similar for
			// accessory objects like Sills, Lintels, Shutters, Trim, etc.
			//
			// The bAssemblyProvidesFrame argument indicates whether the Assembly is set to generate Mullion and Frame
			// geometry. If true, the Unit Object must disable creating all such geometry.
			//
			// Implementors must make all required changes to their parametric objects to achieve this goal.
			//
			// TODO T02293 - Consider adding a return code to this
			virtual void VCOM_CALLTYPE OnJoinAssembly(MCObjectHandle hUnitObject, bool bAssemblyProvidesFrame, WorldCoord zOffset, WorldCoord offsetOutOfAssemblyPlane ) = 0;
			
			// The Assembly will call this method to allow Units to sync a stored cut-plane value with the Assembly's
			//
			// Not all units will necessarily be able to do anything with the value, so a no-op is provided as a default
			// implementation
			//
			// Returning true here requests that the Assembly call CSDK::ResetObject on hUnitObject, so that unit objects
			// capable of updating only their 2-D geometry have the option of doing so.
			virtual bool VCOM_CALLTYPE OnAssemblyCutPlaneChange(MCObjectHandle hUnitObject, WorldCoord elevation) { return false; }
			
			// Requests that the Assembly automatically set the frame segment along this object's bottom edge to zero width.
			//
			// Obvious use-case is Doors. Default implementation provided to keep this opt-in.
			virtual bool VCOM_CALLTYPE BreakFrameOnBottomEdge(MCObjectHandle hUnitObject) const { return false; }
			
			// These two methods provide the Assembly with the information it needs to automatically create the Frame and
			// Mullions, and to construct the logical layout that supports the edit functionality.
			//
			// Implementor should return a polygon in the x-z plane bounding (ideally contacting) the unit object geometry
			// WITH any frame/jamb geometry still present.
			//
			// The second method should return the width of the frame.
			enum class UnitShapeType { Rectangular, Polygonal, Polyline };
			struct UnitCrossSection {
				UnitShapeType				shapeType;
				VWFC::Math::VWRectangle2D	rect;
				VWFC::Math::VWPolygon2D		poly;
			};
			enum class ShapeToPolyResultType { Success, Failure };
			enum class ShapeToPolyFailureType { Success, PolygonUnsupported, PolylineUnsupported, WidthReadOnly, HeightReadOnly, ElevationReadOnly, ObjectSpecificFailure };
			struct ShapeToPolyResult {
				ShapeToPolyResultType type;
				std::set< ShapeToPolyFailureType > failureSet = {};
				TXString customErrorMsg = "";
			};
			virtual UnitCrossSection	VCOM_CALLTYPE	AssemblyPlaneCrossSectionWithFrame	(MCObjectHandle hUnitObject) const = 0;
			virtual WorldCoord			VCOM_CALLTYPE	AssemblyPlaneUnitFrameWidth			(MCObjectHandle hUnitObject) const = 0;
			virtual void				VCOM_CALLTYPE	AddFrameWithWidth					(MCObjectHandle hUnitObject, WorldCoord width) = 0;
			virtual WorldCoord			VCOM_CALLTYPE	GetOffsetInAssembly					(MCObjectHandle hUnitObject) const = 0;
			virtual ShapeToPolyResult	VCOM_CALLTYPE	ShapeUnitToPoly						(MCObjectHandle hUnitObject, const UnitCrossSection& shape) = 0;
		};
		
		
		// ---------------------------------------------------------------------------------------------------
		
		struct ConstraintInfo {
			bool isWidthConstrained = false;
			bool isHeightConstrained = false;
			bool repeatHorizontal = false;
			double maxWidth = 0.0;
			bool repeatVertical = false;
			double maxHeight = 0.0;
		};
		
		static const VWIID IID_AssemblyUnitObjectConstraints = { 0x055dae92, 0x84d1, 0x4aa2, { 0xb2, 0x0e, 0x8d, 0xcc, 0x68, 0x4e, 0x7a, 0xe2 } };

		class DYNAMIC_ATTRIBUTE IAssemblyUnitObjectConstraints : public IVWSingletonUnknown
		{
		public:
			virtual ConstraintInfo VCOM_CALLTYPE GetConstraintInfo(MCObjectHandle hUnitObject) = 0;
			virtual void 	VCOM_CALLTYPE SetConstraintInfo(MCObjectHandle hUnitObject, const ConstraintInfo& ci) = 0;
			virtual bool 	VCOM_CALLTYPE GetWidthFixed(MCObjectHandle h) = 0;
			virtual void 	VCOM_CALLTYPE SetWidthFixed(MCObjectHandle h, bool val) = 0;
			virtual bool 	VCOM_CALLTYPE GetHeightFixed(MCObjectHandle h) = 0;
			virtual void 	VCOM_CALLTYPE SetHeightFixed(MCObjectHandle h, bool val) = 0;
			virtual bool	VCOM_CALLTYPE GetRepeatHorizontal(MCObjectHandle h) = 0;
			virtual void 	VCOM_CALLTYPE SetRepeatHorizontal(MCObjectHandle h, bool val) = 0;
			virtual double 	VCOM_CALLTYPE GetMaxWidth(MCObjectHandle h) = 0;
			virtual void 	VCOM_CALLTYPE SetMaxWidth(MCObjectHandle h, double val) = 0;
			virtual bool 	VCOM_CALLTYPE GetRepeatVertical(MCObjectHandle h) = 0;
			virtual void 	VCOM_CALLTYPE SetRepeatVertical(MCObjectHandle h, bool val) = 0;
			virtual double 	VCOM_CALLTYPE GetMaxHeight(MCObjectHandle h) = 0;
			virtual void 	VCOM_CALLTYPE SetMaxHeight(MCObjectHandle h, double val) = 0;
			
			virtual TXString VCOM_CALLTYPE GetAssemblyConstraintSeparatorPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyZPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyFixWidthPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyFixHeightPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyRepeatHorzPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyMaxWidthPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyRepeastVertPrompt() = 0;
			virtual TXString VCOM_CALLTYPE GetAssemblyMaxHeightPrompt() = 0;
		};

	// ----------------------------------------------------------------------------------------------------
	   typedef VCOMPtr<IAssemblyUnitObjectConstraints>			IAssemblyUnitObjectConstraintsPtr;
	}
}
