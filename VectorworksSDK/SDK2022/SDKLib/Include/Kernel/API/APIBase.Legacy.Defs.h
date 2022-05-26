//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//




///////////////////////////////////////////
//  Attributes (Class)
///////////////////////////////////////////


	extern "C" CBBoolean GS_CALLBACK GS_GetClassBeginningMarker(CallBackPtr, InternalIndex index, SMarkerStyle& mstyle);
		/*
			Gets the beginning marker information for the class with internal index 'index'
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetClassEndMarker(CallBackPtr, InternalIndex index, SMarkerStyle& mstyle);
		/*
			Gets the end marker information for the class with internal index 'index'
		*/

	extern "C" void GS_CALLBACK GS_GetClColor(CallBackPtr, InternalIndex index, ObjectColorType& color);
		/*
			Returns the colors defined for the class with the specified index.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetClFillPat(CallBackPtr, InternalIndex index);
		/*
			Returns the fill style for the class with the specified index.
		*/

	extern "C" short GS_CALLBACK GS_GetClLineWeight(CallBackPtr, InternalIndex index);
		/*
			Returns the line weight for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_GetClMarker(CallBackPtr, InternalIndex index, MarkerType& style, short& size, short& angle);
		/*
			Returns the marker style for the specified class.
		*/


	extern "C" Boolean GS_CALLBACK GS_GetClUseGraphic(CallBackPtr, InternalIndex index);
		/*
			Returns whether the graphic attributes are used in object creation for the specified class.
		*/

	extern "C" short GS_CALLBACK GS_GetClVisibility(CallBackPtr, InternalIndex index);
		/*
			Returns the visibility of the class specified by the index argument.  The return values are: -1 for
			invisible, 0 for visible, and 2 for gray.  
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetVPClassFillStyle(CallBackPtr, MCObjectHandle viewport, InternalIndex classIndex);
		/*
			Returns the fill style for the specified class for the specified viewport.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetClassBeginningMarker(CallBackPtr, InternalIndex index, SMarkerStyle mstyle);
		/*
			Sets the beginning marker information for the class with internal index 'index'
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetClassEndMarker(CallBackPtr, InternalIndex index, SMarkerStyle mstyle);
		/*
			Sets the end marker information for the class with internal index 'index'
		*/

	extern "C" void GS_CALLBACK GS_SetClColor(CallBackPtr, InternalIndex index, ObjectColorType color);
		/*
			Sets the colors for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClFillPat(CallBackPtr, InternalIndex index, InternalIndex fill);
		/*
			Sets the fill style for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClLineWeight(CallBackPtr, InternalIndex index, short mils);
		/*
			Sets the line weight for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClMarker(CallBackPtr, InternalIndex index, MarkerType style, short size, short angle);
		/*
			Sets the marker style for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClUseGraphic(CallBackPtr, InternalIndex index, Boolean use);
		/*
			Sets whether graphic attributes are used at object creation for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClVisibility(CallBackPtr, InternalIndex index, short vis);
		/*
			Set the visibility of the specified class.  The visibility options are: -1 for invisible, 0 for
			visible, and 2 for gray. 
		*/

	extern "C" Boolean GS_CALLBACK GS_VPClassHasOverride(CallBackPtr, MCObjectHandle viewport, InternalIndex classIndex);
		/*
			Indicates whether the specified viewport has an override of the class attributes for the specified
			class.
		*/



///////////////////////////////////////////
//  Attributes (Default)
///////////////////////////////////////////


	extern "C" CBBoolean GS_CALLBACK GS_DeleteAllDLComponents(CallBackPtr);
		/*
			Deletes all components in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_DeleteDLComponent(CallBackPtr, CBSignedShort index);
		/*
			Deletes the component at index in the Double Line Preferences.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDefaultArrowByClass(CallBackPtr);
		/*
			Returns whether the default arrow style is set to use the class attribute.
		*/

	extern "C" void GS_CALLBACK GS_GetDefaultArrowHeads(CallBackPtr, Boolean& starting, Boolean& ending, ArrowType& style, short& size);
		/*
			Returns the default arrow heads setting.  The size is in 1/16384 inches.  This function is being
			obsoleted.  Use GetDefaultArrowHeadsN instead.

		*/

	extern "C" void GS_CALLBACK GS_GetDefaultArrowHeadsN(CallBackPtr, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
		/*
			Returns the default arrow heads setting.  The size is in inches.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDefaultBeginningMarker(CallBackPtr, SMarkerStyle& mstyle, CBBoolean& visibility);
		/*
			Gets the current default marker type information
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetDefaultClass(CallBackPtr);
		/*
			Returns the default class.
		*/

	extern "C" void GS_CALLBACK GS_GetDefaultColors(CallBackPtr, ObjectColorType& colors);
		/*
			Returns the current default ObjectColorType record.  The default values are used for all newly
			created objects.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDefaultEndMarker(CallBackPtr, SMarkerStyle& mstyle, CBBoolean& visibility);
		/*
			Gets the current default end marker information
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDefaultFColorsByClass(CallBackPtr);
		/*
			Returns whether the default fill colors are set to use the class attributes.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetDefaultFillPat(CallBackPtr);
		/*
			Retruns the default fill pattern.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDefaultFPatByClass(CallBackPtr);
		/*
			Returns whether the default fill style is set to use the class attribute.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetDefaultHatch(CallBackPtr);
		/*
			Returns the handle of the default hatch, or nil if there is no default hatch. 
		*/

	extern "C" short GS_CALLBACK GS_GetDefaultLineWeight(CallBackPtr);
		/*
			Returns the default line weight (in mils).
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDefaultLWByClass(CallBackPtr);
		/*
			Returns whether the default line weight is set to use the class attribute.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDefaultPColorsByClass(CallBackPtr);
		/*
			Returns whether the default pen colors are set to use the class attributes.
		*/


	extern "C" Boolean GS_CALLBACK GS_GetDefaultPPatByClass(CallBackPtr);
		/*
			Returns whether the default pen pattern is set to use the class attribute.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentClass(CallBackPtr, CBSignedShort index, Sint32 &componentClass);
		/*
			Gets the class of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentFill(CallBackPtr, CBSignedShort index, Sint32 &fill);
		/*
			Gets the fill style of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentFillColors(CallBackPtr, CBSignedShort index, ColorRef &fillForeColor, ColorRef &fillBackColor);
		/*
			Gets the fore and back fill colors of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentName(CallBackPtr, CBSignedShort index, InternalName &componentName);
		/*
			Gets the name of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentPenColors(CallBackPtr, CBSignedShort index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor);
		/*
			Gets the fore and back colors of the left and right side pens of component at index in the Double
			Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentPenWeights(CallBackPtr, CBSignedShort index, CBUnsignedByte &penWeightLeft, CBUnsignedByte &penWeightRight);
		/*
			Gets the left and right side pen weights of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentUseFillClassAttr(CallBackPtr, CBSignedShort index, CBBoolean &useClassAttr);
		/*
			Gets the use fill class attributes flag of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentUsePenClassAttr(CallBackPtr, CBSignedShort index, CBBoolean &leftPenUseClassAttr, CBBoolean &rightPenUseClassAttr);
		/*
			Gets the use class attributes flags of the left and right side pens of the component at index in the
			Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDLComponentWidth(CallBackPtr, CBSignedShort index, WorldCoord &width);
		/*
			Gets the width of the component at index in the Double Line Preferences.
		*/

	extern "C" WorldCoord GS_CALLBACK GS_GetDLControlOffset(CallBackPtr);
		/*
			Gets the Double Line Preferences control offset.
		*/

	extern "C" CBSignedShort GS_CALLBACK GS_GetDLOptions(CallBackPtr);
		/*
			Gets the Double Line Preferences options.

			0 - Create Lines
			1 - Create Polygons
			2 - Create Lines and Polygons
		*/

	extern "C" WorldCoord GS_CALLBACK GS_GetDLSeparation(CallBackPtr);
		/*
			Gets the Double Line Preferences separation.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetDocumentDefaultSketchStyle(CallBackPtr);
		/*
			Returns the document default sketch style.  Returns -2 if the document default sketch style is set
			to not sketch.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetNumberOfDLComponents(CallBackPtr, short& numComponents);
		/*
			Gets the number of components in the Double Line Preferences.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetObjectInternalIndex(CallBackPtr, MCObjectHandle h);
		/*


		*/

	extern "C" Boolean GS_CALLBACK GS_GetProgramVariable(CallBackPtr, short variableSelector, void* result);
		/*
			GetProgramVariable returns general program information based on the selector passed.  For example,
			the var2DConvertRes selector would set the short pointed to by result to the 2D conversion
			resolution.  If the selector is not recognized, result is unchanged and false is returned.  A list
			of recognized selectors is found in MiniCadCallBacks.h.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetWallPrefStyle(CallBackPtr, InternalIndex& wallStyleNum);
		/*
			Gets the Internal Index of the current document default Wall Style
		*/

	extern "C" Boolean GS_CALLBACK GS_GetWallStyle(CallBackPtr, MCObjectHandle theWall, InternalIndex& wallStyle);
		/*
			Gets the Internal Index of the Wall Style for theWall
		*/


	extern "C" void GS_CALLBACK GS_SetDefaultArrowByClass(CallBackPtr);
		/*
			Sets the default arrow style to use the current class attribute.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultArrowHeads(CallBackPtr, Boolean starting, Boolean ending, ArrowType style, short size);
		/*
			Sets the default for arrow heads.  The size is in 1/16384 inches.  This function is being obsoleted. 
			Use SetDefaultArrowHeadsN instead.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultArrowHeadsN(CallBackPtr, Boolean starting, Boolean ending, ArrowType style, double_param size);
		/*
			Sets the default for arrow heads.  The size is in inches.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDefaultBeginningMarker(CallBackPtr, SMarkerStyle mstyle, CBBoolean visibility);
		/*
			Sets the current default beginning marker information
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultClass(CallBackPtr, InternalIndex classID);
		/*
			Sets the default class.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultColors(CallBackPtr, ObjectColorType colors);
		/*
			Sets the Default ObjectColorType record to colors.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDefaultEndMarker(CallBackPtr, SMarkerStyle mstyle, CBBoolean visibility);
		/*
			Sets the current default end marker information
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultFColorsByClass(CallBackPtr);
		/*
			Sets the default fill colors to use the current class attributes.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultFillPat(CallBackPtr, InternalIndex theFill);
		/*
			Sets the default fill pattern.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultFPatByClass(CallBackPtr);
		/*
			Sets the default fill pattern to use the current class attribute.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDefaultHatch(CallBackPtr, MCObjectHandle inHatchDef);
		/*
			Sets the document's default hatch to inHatchDef.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultLineWeight(CallBackPtr, short mils);
		/*
			Sets the default line weight (in mils).
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultLWByClass(CallBackPtr);
		/*
			Sets the default line weight to use the current class attribute.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultPColorsByClass(CallBackPtr);
		/*
			Sets the default pen colors to use the current class attributes.
		*/


	extern "C" void GS_CALLBACK GS_SetDefaultPPatByClass(CallBackPtr);
		/*
			Sets the default pen style to use the current class attribute.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultWallThickness(CallBackPtr, WorldCoord thickness);
		/*
			Sets the default wall and double line thickness.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentClass(CallBackPtr, CBSignedShort index, Sint32 componentClass);
		/*
			Sets the class of the component at index in the Double Line Preferences.  Does nothing if Architect
			is not enabled.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentFill(CallBackPtr, CBSignedShort index, Sint32 fill);
		/*
			Sets the fill of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentFillColors(CallBackPtr, CBSignedShort index, ColorRef fillForeColor, ColorRef fillBackColor);
		/*
			Sets the fore and back fill colors of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentName(CallBackPtr, CBSignedShort index, const InternalName& componentName);
		/*
			Sets the name of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentPenColors(CallBackPtr, CBSignedShort index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor);
		/*
			Gets the fore and back colors of the left and right side pens of component at index in the Double
			Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentPenWeights(CallBackPtr, CBSignedShort index, CBUnsignedByte penWeightLeft, CBUnsignedByte penWeightRight);
		/*
			Sets the left and right side pen weights of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentUseFillClassAttr(CallBackPtr, CBSignedShort index, CBBoolean useClassAttr);
		/*
			Sets the use fill class attributes flag of the component at index in the Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentUsePenClassAttr(CallBackPtr, CBSignedShort index, CBBoolean leftPenUseClassAttr, CBBoolean rightPenUseClassAttr);
		/*
			Sets the use class attributes flags of the left and right side pens of the component at index in the
			Double Line Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetDLComponentWidth(CallBackPtr, CBSignedShort index, WorldCoord width);
		/*
			Sets the width of the component at index in the Double Line Preferences.
		*/

	extern "C" void GS_CALLBACK GS_SetDLControlOffset(CallBackPtr, WorldCoord controlOffset);
		/*
			Sets the Double Line Preferences control offset.
		*/

	extern "C" void GS_CALLBACK GS_SetDLOptions(CallBackPtr, CBSignedShort options);
		/*
			Sets the Double Line Preferences options.

			0 - Create Lines
			1 - Create Polygons
			2 - Create Lines and Polygons
		*/

	extern "C" void GS_CALLBACK GS_SetDLSeparation(CallBackPtr, WorldCoord separation);
		/*
			Sets the Double Line Preferences separation.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetDocumentDefaultSketchStyle(CallBackPtr, InternalIndex sketchIndex);
		/*
			Sets the document default sketch style.  Set sketchIndex to -2 to never sketch objects using the
			document default sketch style.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetProgramVariable(CallBackPtr, short variableSelector, const void* value);
		/*
			SetProgramVariable sets general program information based on the selector passed.  If the selector
			is not recognized, nothing is unchanged and false is returned.  value should be a pointer to a
			variable of the correct size for the passed selector (for example, a pointer to a boolean when using
			the varBlackBackground selector).  A list of recognized selectors is found in MiniCadCallBacks.h.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetWallPrefStyle(CallBackPtr, InternalIndex wallStyleNum);
		/*
			Sets the document wall preferences to match the traits of the style referred to by wallStyleNum
		*/

	extern "C" void GS_CALLBACK GS_WrapGetDefaultWallThickness(CallBackPtr, double_gs& outCoordLen);
		/*
			TEMPORARY wrapper procedure around PageLengthToCoordLengthN function to avoid illegal return type of
			Coord. See Jeff Koppi.
		*/



///////////////////////////////////////////
//  Attributes (Geometric)
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_Add3DVertex(CallBackPtr, MCObjectHandle h, const WorldPt3& v, Boolean recalcBounds = true);
		/*
			Adds a vertex to a 3D polygon.
		*/

	extern "C" void GS_CALLBACK GS_AddVertex(CallBackPtr, MCObjectHandle h, const WorldPt& p, VertexType t = vtCorner, WorldCoord arcRadius = 0, Boolean recalcBounds = true);
		/*
			Adds p as the new last vertex in the polyline or polygon h.  The vertex will be of type t.  h will
			be transformed into a polyline if necessary.  If t is vtArc, the radius of the corner is specified
			by arcRadius; if arcRadius is zero, the arc will be made as large as will fit.  If recalcBounds is
			false, the bounding box of the poly is not recalculated to reflect the changed coordinate values. 
			This is useful when you are changing many points of a polygon (call ResetObject when you have
			finished).
		*/

	extern "C" void GS_CALLBACK GS_CalcAreaN(CallBackPtr, MCObjectHandle h, double_gs& area);
		/*
			Calculates the area of 2D objects which can be filled.  If the object is not one of these objects
			then 0.0 is returned.  This function is being obsoleted.  Use ObjArea instead.
		*/

	extern "C" void GS_CALLBACK GS_CalcPerimN(CallBackPtr, MCObjectHandle h, double_gs& perim);
		/*
			Calculates the perimeter of 2D objects which can be filled.  If the object is not one of these
			objects then 0.0 is returned.
		*/

	extern "C" double_gs GS_CALLBACK GS_CalcSurfaceArea(CallBackPtr, MCObjectHandle h);
		/*
			Calculates the surface area of a solid or object that can be a solid.  If there is a problem or the
			object is not a valid solid, it returns 0.0.  This function is being obsoleted.  Use ObjSurfaceArea
			instead.
		*/

	extern "C" double_gs GS_CALLBACK GS_CalcVolume(CallBackPtr, MCObjectHandle h);
		/*
			Calculates the volume of a solid or object that can be a solid.  If there is a problem or the object
			is not a valid solid, it returns 0.0.  This function is being obsoleted.  Use ObjVolume instead.
		*/

	extern "C" Boolean GS_CALLBACK GS_Centroid3D(CallBackPtr, MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG);
		/*
			Returns the center of gravity of a 3D object. The function returns TRUE if
			the values were found.
		*/

	extern "C" short GS_CALLBACK GS_CountVertices(CallBackPtr, MCObjectHandle h);
		/*
			Returns the number of vertices in h if h is a polygon, polyline, 3D polygon, or roof.  For all other
			object types, CountVertices returns 0.
		*/

	extern "C" short GS_CALLBACK GS_CreateSkylight(CallBackPtr, MCObjectHandle object);
		/*
			Creates a skylight on the face of the roof indicated by index.  Only 3D symbols are permitted, 2D
			and Hybrid symbols are not acceptable.
		*/

	extern "C" void GS_CALLBACK GS_DeleteVertex(CallBackPtr, MCObjectHandle h, short vertexNum);
		/*
			Deletes the vertexNum'th vertex from h.  h may be a polygon, polyline, or 3D polygon.  If h has only
			3 vertices, then DeleteVertex has no effect'i.e., DeleteVertex will not allow you to make a
			degenerate polygon.
		*/

	extern "C" void GS_CALLBACK GS_ForEach3DPointInObject(CallBackPtr, MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env);
		/*
			Iterates each point on a 3D object. Warning, this function has a very specific  low level function.
			Future use or general purpose use of this function may not be supported.
		*/

	extern "C" void GS_CALLBACK GS_ForEachPolyEdge(CallBackPtr cbp, MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv);
		/*
			This iterates through each edge of a polyline and returns information about it - defining points,
			edge type, and visibility. Each edge type will be one of: kSegment, kArc, or kBezier. Cubic vertices
			are converted to bezier, and arc vertices may be converted into separate kSegment and kArc. Arcs are
			always counterclockwise. Some edges may be degenerate (have all defining points equal to each
			other). Warning: there may be more edges than vertices. See GS_ForEachPolyEdgeProcPtr in
			MiniCadCallBacks.h for more info.
		*/

	extern "C" void GS_CALLBACK GS_Get3DVertex(CallBackPtr, MCObjectHandle h, short vertexNum, WorldPt3& vertex);
		/*
			Sets vertex to the vertexNum'th vertex of the 3D polygon.  Vertices are numbered starting from 1 up
			to CountVertices(h).  If vertexNum is outside the defined range or if h is not a 3D polygon,
			Get3DVertex will return the point {0, 0, 0}.
		*/

	extern "C" void GS_CALLBACK GS_GetArcInfoN(CallBackPtr, MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY);
		/*
			Returns the startAngle, sweepAngle, and center of the specified arc.  The center is especially
			useful because the CoordRect returned from GetBoundingBox is the union of each quadrant box that the
			arc includes, so the center of that box is not always the center of the arc.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetBatAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint);
		/*
			Get the settings of a bat style dormer.  This will fail if the dormerID identifies a dormer of a
			different style, or the dormerID is not valid.

			dormerID: Identifies the dormer for which to retrieve the information.

			useHeight: Set to true if the next value is the height of the dormer, if false, next value is the
			depth (front to back) of the dormer.
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.
			baseHeight: Dimension of the bottom half of the dormer.
			topWidth: Dimension of the roof of the dormer.

			topSlope: Angle of the dormer roof.

			controlPoint: The distance from the side to where the curve starts.  Must be less than (bottomWidth
			- topWidth) / 2.
		*/

	extern "C" void GS_CALLBACK GS_GetControlVertex(CallBackPtr, MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius);
		/*
			Identical to GetVertex except that it returns the Bezier control point for cubic spline sections.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDormerAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset);
		/*
			Get the common settings for all dormers.  This will fail if the dormerID identifies a skylight, or
			dormerID is not valid.

			dormerID: Identifies the dormer for which to retrieve the information.
			edgeIndex: Index to which roof face this skylight is placed.  Value is one based.

			cornerOffset: Distance from the vertex to the center of the dormer.
			isPerpOffset: Determines the meaning of the next parameter.  Set to true for the value to be the
			plan distance from the outline to the front of the dormer.  Set to false for offsetValue to set the
			distance from the top of the dormer to the bearing height.
			perpOrHeightOffset: Either the distance from the outline to the front of the dormer, or from the
			dormer roof to the floor.

			symName: Symbol to place in the dormer, this is the window.
			centerSymbol: Set to true to vertically center the symbol in the dormer.  Doing so causes the next
			parameter to be ignored.
			Set to false to offset the symbol from the top of the dormer using the next parameter.
			symOffset: Distance from top of the dormer to symbol insertion point.

		*/

	extern "C" void GS_CALLBACK GS_GetEndPoints(CallBackPtr, MCObjectHandle h, WorldPt& startPt, WorldPt& endPt);
		/*
			Gets the endpoints of a line or wall object.
		*/

	extern "C" void GS_CALLBACK GS_GetEntityMatrix(CallBackPtr, MCObjectHandle h, TransformMatrix& theMat);
		/*
			Given a handle to an extrude, multiple extrude, sweep, or symbol, this function sets theMat to that
			drawing entity's matrix.
		*/

	extern "C" void GS_CALLBACK GS_GetExtrudeValues(CallBackPtr, MCObjectHandle h, WorldCoord& bottom, WorldCoord& top);
		/*
			Given a handle to and extrude or a multiple extrude, returns the top and bottom surfaces in entity
			space.  To convert a 2D defining point to it's 3D world space equivalent on the bottom of the
			extrude, add the bottom value as the z-value of the point and then multiply this 3D point by the
			entity matrix.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetGableAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang);
		/*
			Get the settings of a gable style dormer.  This will fail if the dormerID identifies a dormer of a
			different style, or the dormerID is not valid.

			dormerID: Identifies the dormer for which to retrieve the information.

			useHeight: Set to true if the next value is the height of the dormer, if false, next value is the
			depth (front to back) of the dormer.
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			leftSlope: Angle of left dormer roof.
			rightSlope: Angle of right dormer roof.

			overhang: Distance roof projects past dormer walls.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetHipAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang);
		/*
			Get the settings of a hip style dormer.  This will fail if the dormerID identifies a dormer of a
			different style, or the dormerID is not valid.

			dormerID: Identifies the dormer for which to retrieve the information.

			useHeight: true if the next value is the height of the dormer, if false, next value is the depth
			(front to back) of the dormer
			heightDepthValue: size of the dormer, either by height or depth; determined by previous parameter

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			leftSlope: Angle of left dormer roof.
			rightSlope: Angle of right dormer roof.
			frontSlope: Angle of the front dormer roof face.

			overhang: Distance roof projects past dormer walls.
		*/

	extern "C" void GS_CALLBACK GS_GetLocus3DPosition(CallBackPtr, MCObjectHandle h, WorldPt3& locPos);
		/*
			Returns in locPos, the position of the 3D locus.
		*/

	extern "C" void GS_CALLBACK GS_GetLocusPosition(CallBackPtr, MCObjectHandle h, WorldPt& locPos);
		/*
			Returns in locPos, the position of the locus.
		*/

	extern "C" void GS_CALLBACK GS_GetMarkerPolys(CallBackPtr, MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly);
		/*
			Returns two polylines that define the geometry of the start and end markers for the specified
			object.

			Note: The cross marker polyline has a hidden edge at the second vertex.

		*/

	extern "C" short GS_CALLBACK GS_GetNumRoofElements(CallBackPtr, MCObjectHandle object);
		/*
			Get number of dormers & skylights on this roof object.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetObjectBoundingBoxVerts(CallBackPtr, MCObjectHandle h, WorldRectVerts &outBoxVerts);
		/*
			Gets the rotated vertices for  a text object.  For other objects it returns the WorldRectVerts to
			match the object's bounds.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetObjectBounds(CallBackPtr, MCObjectHandle h, WorldRect& bounds);
		/*
			Returns in bounds the smallest CoordRect that completely surrounds h.
		*/

	extern "C" void GS_CALLBACK GS_GetObjectCube(CallBackPtr, MCObjectHandle h, WorldCube& boundsCube);
		/*
			Returns in boundsCube the smallest cube that completely surrounds h.
		*/

	extern "C" short GS_CALLBACK GS_GetPolyDirection(CallBackPtr, MCObjectHandle polyToCheck);
		/*
			Returns kPolyDirectionClockwise, kPolyDirectionCounterClockwise, or  kPolyDirectionError.  A
			clockwise poly has vertices defined that loop around in the clockwise direction.  All polygons are
			treated as loops that connect the first and last vertex  reguardless of open status.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetPolyShapeClose(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether or not the polyshape has been marked as 'closed'.  A closed shape automatically
			draws a line connecting the last segment to the first.
		*/

	extern "C" short GS_CALLBACK GS_GetQArcQuadrant(CallBackPtr, MCObjectHandle h);
		/*
			Given a handle to a quarter arc, function returns the quadrant in which the quarter arc lies.  -1 is
			returned if h is not a quarter arc.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetRoofAttributes(CallBackPtr, MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter);
		/*
			Get the properties of the roof.

			genGableWall: Set to true to have a wall created at gable ends of the roof.  Otherwise no object
			will be inserted.
			bearingInset  is where the weight of the roof rests on the wall.  This is an inset from the defining
			edge of the roof plan.
			miterType: Specify 1 for a vertical miter, 2 for horizontal miter, 3 for a double miter cut, and 4
			for a square end miter cut.
			vertMiter: This is used only with the double miter type; it specifies the vertical length of the
			miter cut.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetRoofElementType(CallBackPtr, MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType);
		/*
			Get the type of roof object from id.

			Identifies the dormer for which to retrieve the information.
			edgeIndex: Index to which roof face this skylight or dormer is placed.  Value is one based.

			isDormer: true if this object is a dormer, false if skylight
			dormerType: if it is a dormer then:

			1 for Trapezium Dormer
			2 for Saddle Dormer
			3 for Shed Dormer
			4 for Slope Dormer
			5 for Bat Dormer
		*/

	extern "C" void GS_CALLBACK GS_GetRRectDiameters(CallBackPtr, MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam);
		/*
			Given a handle to a rounded rectangle object, function sets xDiam and yDiam to the diameters of the
			corner ellipse.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetShedAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang);
		/*
			Get the settings of a shed style dormer.  This will fail if the dormerID identifies a dormer of a
			different style, or the dormerID is not valid.

			dormerID: Identifies the dormer for which to retrieve the information.

			useHeight: Set to true if the next value is the height of the dormer, if false, next value is the
			depth (front to back) of the dormer
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			topSlope: Angle of dormer roof.

			overhang: Distance roof projects past dormer walls.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetSkylight(CallBackPtr, MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName);
		/*
			Get skylight attributes.

			skylightID: Identifier for this skylight.  Value is returned by CreateSkylight().
			edgeIndex: Index to which roof face this skylight is placed.  Value is one based.
			cornerOffset: Top/Plan distance from vertex referenced by 'edgeIndex' to center of skylight.  This
			distance is parallel to the roof outline as defined by: vertex[edgeindex+1] - vertex[edgeIndex].
			perpOffset: Top/Plan distance from roof outline to center of skylight.
			symName: Skylight symbol to place in the roof.
		*/

	extern "C" void GS_CALLBACK GS_GetSweepAnglesN(CallBackPtr, MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle);
		/*
			Gets the angles that define a sweep.  startAngle is the angle that the sweep begins, with 0' lying
			along the x-axis in entity space.  arcAngle is how many degrees from the startAngle the sweep
			revolves.  incrAngle is how many degrees between facets of the sweep.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetTrapeziumAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope);
		/*
			Get the settings of a trapezium style dormer.  This will fail if the dormerID identifies a dormer of
			a different style, or the dormerID is not valid.

			dormerID: Identifies the dormer for which to retrieve the information.

			useHeight: true if the next value is the height of the dormer, if false, next value is the depth
			(front to back) of the dormer.
			heightDepthValue: size of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: dimension of bottom front edge of the dormer, left to right.

			useTopWidth: true if using a dimension to set the width of the dormer roof.  False if the top width
			of the dormer is determined by the left and right slope.  The topWidth is exclusive of leftSlope &
			rightSlope.
			topWidth: dimension of the roof of the dormer.
			leftSlope: angle of left dormer wall.
			rightSlope: angle of right dormer wall.
			topSlope: angle of the roof of the dormer.
		*/

	extern "C" void GS_CALLBACK GS_GetVertex(CallBackPtr, MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius);
		/*
			Sets vertex to the vertexNum'th vertex of h and vType to the corner type.  vType always equals
			vtCorner for a polygon.  Vertices are numbered starting from 1 up to CountVertices(h).  If vertexNum
			is outside the defined range, GetVertex will return the point {0, 0} and vtCorner.
		*/

	extern "C" void GS_CALLBACK GS_Insert3DVertex(CallBackPtr, MCObjectHandle h, const WorldPt3& p, short beforeVertex, Boolean recalcBounds = true);
		/*
			Inserts a new vertex of type t into the specified 3D polygon.  Existing vertices are numbered
			starting from 1; set beforeVertex to 1 to insert the new vertex before the first vertex, set it to
			one greater than the last vertex (i.e. CountVertices(cbp, h) + 1) to insert the new point as the
			last vertex.  If recalcBounds is false, the bounding box of the poly is not recalculated to reflect
			the changed coordinate values.  This is useful when you are changing many points of a polygon (call
			ResetObject when you have finished).
		*/

	extern "C" void GS_CALLBACK GS_InsertVertex(CallBackPtr, MCObjectHandle h, const WorldPt& p, short beforeVertex, VertexType t = vtCorner, WorldCoord arcRadius = 0, Boolean recalcBounds = true);
		/*
			Inserts a new vertex of type t into the specified polygon or polyline.  The shape h will be
			transformed into a polyline if necessary.  Existing vertices are numbered starting from 1; set
			beforeVertex to 1 to insert the new vertex before the first vertex, set it to CountVertices(cbp,
			h)+1 to insert the new point as the last vertex.  If recalcBounds is false, the bounding box of the
			poly is not recalculated to reflect the changed coordinate values.  This is useful when you are
			changing many points of a polygon (call ResetObject when you have finished).
		*/

	extern "C" Boolean GS_CALLBACK GS_Moments3D(CallBackPtr, MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz);
		/*
			Returns the moments of inertia of a 3D object about the x, y, and z axes of
			a point at the center of gravity of the object. The function returns TRUE if
			the values were found.
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsCurveEvaluatePoint(CallBackPtr, MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt);
		/*
			This function determines the point on the nurbs curve at the given U value in the indexed piece.
		*/

	extern "C" Sint32 GS_CALLBACK GS_NurbsCurveGetNumPieces(CallBackPtr, MCObjectHandle nHandle);
		/*
			returns the number of pieces that compose the given piecewise nurbs curve.
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsCurveType(CallBackPtr, MCObjectHandle nHandle, Sint32 index, bool& isByWeight);
		/*
			return true if the index piece is created by fit point, false otherwise	
		*/

	extern "C" short GS_CALLBACK GS_NurbsDegree(CallBackPtr, MCObjectHandle nHandle, Sint32 index);
		/*
			returns the degree of the indexed piece of the given nurbs curve or the degree of the surface in
			U(index =1) or V(index = 0)
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsDelVertex(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2);
		/*
			It deletes the index2 point of the index1 piece for nurbs curve with deletion of points shared
			by two pieces resulting in the curves being combined. or It deletes an entire index2 row (index1 =
			1) or column (index1 = 0)of points
		*/

	extern "C" Sint32 GS_CALLBACK GS_NurbsGetNumPts(CallBackPtr, MCObjectHandle nHandle, Sint32 index);
		/*
			eturns either the number of control or fit points for the index piece of the given curve, or the
			number of control points of the given surface in u(index=1) (or v(index=0)) direction.
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsGetPt3D(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt);
		/*
			Gets the index2 vertex of the indexe1 piece of the given NURBS curve or the index1 U and index2 V
			control point of the surfaces 
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsGetWeight(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight);
		/*
			returns the weight for the  index2 control point of the index1 piece of nurbs curve or  for the
			indexU row and the indexV column control point of nurbs surface
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsKnot(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot);
		/*
			returns the index2 knot of the index1 piece of the given nurbs curve or the index2 knot of  U
			knot(index =1) or V knot(index=0) of the given nurbs surface
		*/

	extern "C" Sint32 GS_CALLBACK GS_NurbsNumKnots(CallBackPtr, MCObjectHandle nHandle, Sint32 index);
		/*
			returns the number of knots for the indexed piece of the given nurbs curve.  or number of U knot
			vector (index=1) or
			V knot vector (index=0) of the given nurbs surface
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsSetKnot(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot);
		/*
			sets the index2 knot of the index1 piece of the given nurbs curve or the index2 knot of  U
			knot(index =1) or V knot(index=0) of the given nurbs surface
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsSetPt3D(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt);
		/*
			sets the indexed vertex of the indexed point of the given nurbs curve or the indexed (index2)control
			point of the surfaces in either the U (index 1= 1)or V(index1 =0) direction.
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsSetWeight(CallBackPtr, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight);
		/*
			sets the weight for the  index2 control point of the index1 piece of nurbs curve or  for the indexU
			row and the indexV column control point of nurbs surface
		*/

	extern "C" Boolean GS_CALLBACK GS_NurbsSurfaceEvaluatePoint(CallBackPtr, MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt);
		/*
			This function determines the point on the nurbs surface at the given U,V values.
		*/

	extern "C" double_gs GS_CALLBACK GS_ObjArea(CallBackPtr, MCObjectHandle h);
		/*
			Calculates the area of 2D objects which can be filled.  The value will be in the current Area Units. 
			If the object cannot be filled, then 0.0 is returned.
		*/

	extern "C" double_gs GS_CALLBACK GS_ObjSurfaceArea(CallBackPtr, MCObjectHandle h);
		/*
			Calculates the surface area of a solid or object that can be a solid. The value will be in the
			current Area Units.  If there is a problem or the object is not a valid solid, it returns 0.0.
		*/

	extern "C" double_gs GS_CALLBACK GS_ObjVolume(CallBackPtr, MCObjectHandle h);
		/*
			Calculates the volume of a solid or object that can be a solid. The value will be in the current
			Volume Units.  If there is a problem or the object is not a valid solid, it returns 0.0.
		*/

	extern "C" Boolean GS_CALLBACK GS_Products3D(CallBackPtr, MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx);
		/*
			Returns the products of inertia of a 3D object for the xy, yz, and zx planes
			passing through a point at the center of gravity of the object. The function
			returns TRUE if the values were found.
		*/

	extern "C" void GS_CALLBACK GS_RemoveRoofElement(CallBackPtr, MCObjectHandle object, short id);
		/*
			Remove a dormer or skylight from the roof object.

			id is the value returned from Create...Dormer() or CreateSkylight() routine.
		*/

	extern "C" void GS_CALLBACK GS_Set3DVertex(CallBackPtr, MCObjectHandle h, short vertexNum, const WorldPt3& vertex, Boolean recalcBounds = true);
		/*
			Sets the vertex number vertexNum to have the value ofof h vertex.  If recalcBounds is false, the
			bounding box of the poly is not recalculated to reflect the changed coordinate values.  This is
			useful when you are changing many points of a polygon (call ResetObject when you have finished).
		*/

	extern "C" void GS_CALLBACK GS_SetArcAnglesN(CallBackPtr, MCObjectHandle h, double_param startAngle, double_param sweepAngle);
		/*
			Sets the specified arc to have the startAngle and sweepAngle passed.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetBatAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, WorldCoord topWidth, WorldCoord baseHeight, double_param topSlope, WorldCoord controlPoint);
		/*
			Set the settings of a hip style dormer.

			dormerID: Identifies the dormer for which to set the information.

			useHeight: Set to true if the next value is the height of the dormer, if false, next value is the
			depth (front to back) of the dormer.
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right..
			topWidth: Dimension of the roof of the dormer.
			baseHeight: Dimension of the bottom half of the dormer.

			topSlope: Angle of the dormer roof.

			controlPoint: The distance from the side to where the curve starts.  Must be less than (bottomWidth
			- topWidth) / 2.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetDormerAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, short edgeIndex, WorldCoord cornerOffset, Boolean isPerpOffset, WorldCoord perpOrHeightOffset, InternalIndex symName, Boolean centerSymbol, WorldCoord symOffset);
		/*
			Get the common settings for all dormers.  This will fail if the dormerID identifies a skylight, or
			dormerID is not valid.

			dormerID: Identifies the dormer for which to set the information.
			edgeIndex: Index to which roof face this dormer is placed.  Value is one based.

			cornerOffset: Distance from the vertex to the center of the dormer.
			isPerpOffset: Determines the meaning of the next parameter.  Set to true for the value to be the
			plan distance from the outline to the front of the dormer.  Set to false for offsetValue to set the
			distance from the top of the dormer to the bearing height.
			perpOrHeightOffset: Either the distance from the outline to the front of the dormer, or from the
			dormer roof to the floor.

			symName: Symbol to place in the dormer, this is the window.
			centerSymbol: Set to true to vertically center the symbol in the dormer.  Doing so causes the next
			parameter to be ignored.
			Set to false to offset the symbol from the top of the dormer using the next parameter.
			symOffset: Distance from top of the dormer to symbol insertion point.
		*/

	extern "C" void GS_CALLBACK GS_SetDormerThick(CallBackPtr, MCObjectHandle object, WorldCoord wallThick, WorldCoord roofThick);
		/*
			Set thickness values for dormers.
		*/

	extern "C" void GS_CALLBACK GS_SetEndPoints(CallBackPtr, MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt);
		/*
			Sets the endpoints of a line or wall object.
		*/

	extern "C" void GS_CALLBACK GS_SetEntityMatrix(CallBackPtr, MCObjectHandle h, const TransformMatrix& theMat);
		/*
			Sets the matrix of an extrude, multiple extrude, sweep, or symbol to theMat.
		*/

	extern "C" void GS_CALLBACK GS_SetExtrudeValues(CallBackPtr, MCObjectHandle h, WorldCoord bottom, WorldCoord top);
		/*
			Given a handle to and extrude or a multiple extrude, sets the top and bottom surfaces in entity
			space.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetGableAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, WorldCoord overhang);
		/*
			Set the settings of a gable style dormer.

			dormerID: Identifies the dormer for which to set the information.

			useHeight: Set to true if the next value is the height of the dormer, if false, next value is the
			depth (front to back) of the dormer.
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			leftSlope: Angle of left dormer roof.
			rightSlope: Angle of right dormer roof.

			overhang: Distance roof projects past dormer walls.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetHipAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, double_param frontSlope, WorldCoord overhang);
		/*
			Set the settings of a hip style dormer.

			dormerID: Identifies the dormer for which to set the information.

			useHeight: Set to true if the next value is the height of the dormer, if false, next value is the
			depth (front to back) of the dormer.
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			leftSlope: Angle of left dormer roof.
			rightSlope: Angle of right dormer roof.
			frontSlope: Angle of the front dormer roof face.

			overhang: Distance roof projects past dormer walls.
		*/

	extern "C" void GS_CALLBACK GS_SetLocus3DPosition(CallBackPtr, MCObjectHandle h, const WorldPt3& locPos);
		/*
			Sets the 3D locus to the position specified by locPos.
		*/

	extern "C" void GS_CALLBACK GS_SetLocusPosition(CallBackPtr, MCObjectHandle h, const WorldPt& locPos);
		/*
			Sets the locus to the position specified by locPos.
		*/

	extern "C" void GS_CALLBACK GS_SetObjectBounds(CallBackPtr, MCObjectHandle h, const WorldRect& bounds);
		/*
			Sets the bounding box for the object h.  If an object is a simple object (a rectangle or an oval)
			then its bounding box is a defining attribute and changes to it will have the expected effect.  If
			the object is a more complex object (a wall or dimension) then the bounding box is a derived
			attribute and changes to it will not affect the definition of the object.  However, since MiniCad
			uses the bounding box in drawing the object, changing the bounding box of a complex object will have
			a noticable affect manifested as a drawing error.  This error is only temporary as the bounding box
			will be correctly reset after certain operations.  A general technique for achieving the same end is
			to use MoveObject() and ScaleObject().

		*/

	extern "C" void GS_CALLBACK GS_SetPolyShapeClose(CallBackPtr, MCObjectHandle h, Boolean closed);
		/*
			Sets the polyshape's closed flag to the one specified.  A closed shape automatically draws a line
			connecting the last segment to the first.
		*/

	extern "C" void GS_CALLBACK GS_SetQArcQuadrant(CallBackPtr, MCObjectHandle h, short quadrant);
		/*
			Given a handle to a quarter arc and a quadrant number, function sets the quarter arc to the
			specified quadrant.
		*/

	extern "C" void GS_CALLBACK GS_SetRoofAccessoriesParameters(CallBackPtr, MCObjectHandle roof, Boolean insertAttic, Boolean insertSoffit, Boolean insertFascia, WorldCoord fasciaWidth, WorldCoord fasciaHeight, WorldCoord atticHeight, WorldCoord recess, WorldCoord rakeThick, WorldCoord trimDepth);
		/*
			Allows to set roof accessories parameters
		*/

	extern "C" void GS_CALLBACK GS_SetRoofAttributes(CallBackPtr, MCObjectHandle object, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter);
		/*
			Set the properties of the roof.

			genGableWall: Set to true to have a wall created at gable ends of the roof.  Otherwise no object
			will be inserted.
			bearingInset  is where the weight of the roof rests on the wall.  This is an inset from the defining
			edge of the roof plan.
			miterType:  Specify 1 for a vertical miter, 2 for horizontal miter, 3 for a double miter cut, and 4
			for a square end miter cut.  vertMiter: This is used only with the double miter type; it specifies
			the vertical length of the miter cut.
		*/

	extern "C" void GS_CALLBACK GS_SetRRectDiameters(CallBackPtr, MCObjectHandle h, WorldCoord xDiam, WorldCoord yDiam);
		/*
			Given a handle to a rounded rectangle object, function sets the diameters of the corner ellipse to
			xDiam and yDiam.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetShedAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param topSlope, WorldCoord overhang);
		/*
			Set the settings of a shed style dormer. 

			dormerID: Identifies the dormer for which to set the information.

			useHeight: true if the next value is the height of the dormer, if false, next value is the depth
			(front to back) of the dormer
			heightDepthValue: size of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			topSlope: Angle of dormer roof.

			overhang: Distance roof projects past dormer walls.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetSkylight(CallBackPtr, MCObjectHandle object, const short skylightID, short edgeIndex, WorldCoord cornerOffset, WorldCoord perpOffset, InternalIndex symName);
		/*
			Set skylight attributes.

			skylightID: Identifier for this skylight.  Value is returned by CreateSkylight().
			edgeIndex: Index to which roof face this skylight is placed.  Value is one based.
			cornerOffset: Top/Plan distance from vertex referenced by 'edgeIndex' to center of skylight.  This
			distance is parallel to the roof outline as defined by: vertex[edgeindex+1] - vertex[edgeIndex].
			perpOffset: Top/Plan distance from roof outline to center of skylight.
			symName: Skylight symbol to place in the roof.
		*/

	extern "C" void GS_CALLBACK GS_SetSweepAnglesN(CallBackPtr, MCObjectHandle theSweep, double_param startAngle, double_param arcAngle, double_param incrAngle);
		/*
			Sets the angles that define a sweep.  startAngle is the angle that the sweep begins, with 0' lying
			along the x-axis in entity space.  arcAngle is how many degrees from the startAngle the sweep
			revolves.  incrAngle is how many degrees between facets of the sweep.
		*/

	extern "C" void GS_CALLBACK GS_SetSweepScrew(CallBackPtr, MCObjectHandle theSweep, WorldCoord dist);
		/*
			Sets the distance that the sweep advances along its rotation axis for each complete revolution.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetTrapeziumAttributes(CallBackPtr, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, Boolean useTopWidth, WorldCoord topWidth, double_param leftSlope, double_param rightSlope, double_param topSlope);
		/*
			Set trapezium dormer attributes.

			dormerID: Identifies the which dormer for which to set the values.

			useHeight: Set to true if the next value is the height of the dormer, otherwise set to false if the
			next value is the depth (front to back) of the dormer.
			heightDepthValue: GSSize of the dormer, either by height or depth; determined by previous parameter.

			bottomWidth: Dimension of bottom front edge of the dormer, left to right.

			useTopWidth: True if using a dimension to set the width of the dormer roof.  False if the top width
			of the dormer is determined by the left and right slope.  The topWidth is exclusive of leftSlope &
			rightSlope.
			topWidth: Dimension of the roof of the dormer.
			leftSlope: Angle of left dormer wall.
			rightSlope: Angle of right dormer wall.

			topSlope: Angle of the roof of the dormer.
		*/

	extern "C" void GS_CALLBACK GS_SetVertex(CallBackPtr, MCObjectHandle h, short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius, Boolean recalcBounds = true);
		/*
			Sets the vertex number vertexNum (1->numVerts) to have the value of vertex.  vType can be one of
			vtCorner, vtBezier, vtCubic, vtArc  and Coord arcRadius sets the radius of the vetex if it of
			VertexType == vtArc.  If recalcBounds is false, the bounding box of the poly is not recalculated to
			reflect the changed coordinate values.  This is useful when you are changing many points of a
			polygon (call ResetObject when you have finished).
		*/

	extern "C" void GS_CALLBACK GS_WrapGetSweepScrew(CallBackPtr, MCObjectHandle theSweep, double_gs& outCoordLen);
		/*
			TEMPORARY wrapper procedure around PageLengthToCoordLengthN function to avoid illegal return type of
			Coord. See Jeff Koppi.
		*/



///////////////////////////////////////////
//  Attributes (Graphic)
///////////////////////////////////////////


	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCircularDimension(CallBackPtr, const WorldPt& center, const WorldPt& end, WorldCoord startOffset, WorldCoord textOffset, const WorldRect& box, Boolean isRadius);


	extern "C" Boolean GS_CALLBACK GS_GetArrowByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the specified object is using the class arrow style.
		*/

	extern "C" void GS_CALLBACK GS_GetArrowHeads(CallBackPtr, MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size);
		/*
			starting is true if start has arrowHead, ending is true if endpt has arrowHead, and ArrowType is one
			of arArrow, arTightArrow, arBall, arSlash, arCross which correspond to MiniCAD's arrowHeads as
			displayed in the attribute pop-up. GSSize is in points.  This function is being obsoleted.  Use
			GetArrowHeadsN instead.
		*/

	extern "C" void GS_CALLBACK GS_GetArrowHeadsN(CallBackPtr, MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
		/*
			Gets the arrow head settings for  the object h.  starting is true if its startpt has an arrowHead,
			ending is true if its endpt has an arrowHead, and ArrowType is one of arArrow, arTightArrow, arBall,
			arSlash, arCross which correspond to MiniCAD's arrowHeads as displayed in the attribute pop-up. GSSize
			is in inches. 
		*/

	extern "C" Boolean GS_CALLBACK GS_GetColor(CallBackPtr, MCObjectHandle h, ObjectColorType& colors);
		/*
			Returns the ObjectColorType record of the object h. Returns false if the object cannot have a color.
		*/

	extern "C" OpacityRef GS_CALLBACK GS_GetDefaultOpacity(CallBackPtr);
		/*
			Returns the default opacity
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetDefaultOpacityByClass(CallBackPtr);
		/*
			Gets the default opacity of class
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFColorsByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the specified object is using the class fill colors.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFillIAxisEndPoint(CallBackPtr, MCObjectHandle objectHandle, WorldPt& iAxisEndPoint);
		/*
			Gets the i-axis end point of the fill.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFillJAxisEndPoint(CallBackPtr, MCObjectHandle objectHandle, WorldPt& jAxisEndPoint);
		/*
			Gets the j-axis end point of the fill.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFillOriginPoint(CallBackPtr, MCObjectHandle objectHandle, WorldPt& originPoint);
		/*
			Gets the origin point of the fill.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetFillPat(CallBackPtr, MCObjectHandle h);
		/*
			Returns the fill pattern ID or hatch number of h, or 0 if h is an object with no fill pattern (e.g.
			line, group, etc.).  [The fill pattern IDs are the same as in MiniPascal: none is 0, white is 1,
			black is 2, and so on.  If the object is hatched, the number is negative, and valid values are not
			consecutive.]
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFillPoints(CallBackPtr, MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint);
		/*
			Gets start and axis end points of the fill.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFPatByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the specified object is using the class fill style.
		*/

	extern "C" short GS_CALLBACK GS_GetLineWeight(CallBackPtr, MCObjectHandle h);
		/*
			Returns line weight of h in mils (thousandths of an inch) or zero if h is a non-drawing- or
			meta-object (e.g. a symbol definition or group).
		*/

	extern "C" short GS_CALLBACK GS_GetLineWeightDisplayMM(CallBackPtr, short mils);
		/*
			Returns the value to display in hundredths-of-a-mm for a lineweight in mils.  If the mils value
			passed in is invalid, it returns 0.  (Note that the return value is of type short, but its units are
			1/100 mm.)
		*/

	extern "C" short GS_CALLBACK GS_GetLineWeightDisplayPt(CallBackPtr, short mils);
		/*
			Returns the value to display in sixteenths-of-a-Point for a lineweight in mils.  If the mils value
			passed in is invalid, it returns 0.  (Note that the return value is of type short, but its units are
			1/16 Point.)
		*/

	extern "C" Boolean GS_CALLBACK GS_GetLWByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the object is using the class line weight.
		*/

	extern "C" void GS_CALLBACK GS_GetMarker(CallBackPtr, MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end);
		/*
			Returns the markers of a passed segment or arc.  This function supercedes GetArrowHeads. Each size
			unit is equal to 1/16384 of an inch on the printed page.  If you have a segment or arc with a one
			inch marker, size will return with 16384. If you pass NIL for the obj parameter, this call will get
			the marker defaults for this document.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetObjBeginningMarker(CallBackPtr, MCObjectHandle h, SMarkerStyle& mstyle, CBBoolean& visibility);
		/*
			Gets the beginning marker information for an object
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetObjEndMarker(CallBackPtr, MCObjectHandle h, SMarkerStyle& mstyle, CBBoolean& visibility);
		/*
			Gets the end marker information for an object
		*/

	extern "C" OpacityRef GS_CALLBACK GS_GetOpacity(CallBackPtr, MCObjectHandle h);
		/*
			Returns the object opacity of h
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetOpacityByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns weather the object is using the class opacity
		*/

	extern "C" Boolean GS_CALLBACK GS_GetPColorsByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the object is using the class pen colors.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetPPatByClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the object is using the class pen style.
		*/

	extern "C" void GS_CALLBACK GS_GetVertexVis(CallBackPtr, MCObjectHandle h, short vertNum, Boolean& vis);
		/*
			Gets the visibility of the segment passing through (for curves) or the segment following the
			specified vertex.  See SetVertexVis for more explanation.
		*/

	extern "C" void GS_CALLBACK GS_SetArrowByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified object to use the class arrow style.
		*/

	extern "C" void GS_CALLBACK GS_SetArrowHeads(CallBackPtr, MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, short size);
		/*
			Sets object h to have arrowHeads of type  style,  with size size.  place arrowhead on start if
			starting is true, and on endpoint if ending is true.  GSSize is in points.  This function is being
			obsoleted.  Use SetArrowHeadsN instead.
		*/

	extern "C" void GS_CALLBACK GS_SetArrowHeadsN(CallBackPtr, MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, double_param size);
		/*
			Sets object h to have arrowHeads of type  style,  with size size.  place arrowhead on start if
			starting is true, and on endpoint if ending is true.  GSSize is in inches.
		*/

	extern "C" void GS_CALLBACK GS_SetColor(CallBackPtr, MCObjectHandle h, ObjectColorType colors);
		/*
			Sets the ObjectColorType record for h.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultOpacity(CallBackPtr, OpacityRef inOpacity);
		/*
			Sets the default opacity
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultOpacityByClass(CallBackPtr);
		/*
			Sets the default opacity to use the current class opacity 
		*/

	extern "C" void GS_CALLBACK GS_SetFColorsByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified object to use the class fill colors.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetFillIAxisEndPoint(CallBackPtr, MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint);
		/*
			Sets the i-axis end point of the fill.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetFillJAxisEndPoint(CallBackPtr, MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint);
		/*
			Sets the j-axis end point of the fill.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetFillOriginPoint(CallBackPtr, MCObjectHandle objectHandle, const WorldPt& originPoint);
		/*
			Sets the origin point of the fill.
		*/

	extern "C" void GS_CALLBACK GS_SetFillPat(CallBackPtr, MCObjectHandle h, InternalIndex theFill);
		/*
			Sets the fill pattern or hatch of h to the pattern ID or hatch number specified by theFill.  [The
			fill pattern IDs are the same as in MiniPascal: none is 0, white is 1, black is 2, and so on.  Hatch
			numbers are negative, but valid numbers are not sequential.  You must obtain a hatch number from
			another call such as GetFillPat or NameToInternalIndex, and they are not valid across documents.]
		*/

	extern "C" void GS_CALLBACK GS_SetFPatByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified object to use the class fill pattern.
		*/

	extern "C" void GS_CALLBACK GS_SetLineWeight(CallBackPtr, MCObjectHandle h, short mils);
		/*
			Sets the line weight of h to the specified number of mils.  If h is a group, SetLineWeight will
			change all of its members.  If h is neither a drawing object nor a group, SetLineWeight does nothing.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetLineWeightDisplayMM(CallBackPtr, short hundredths);
		/*
			Sets the mm value to display for an internal mil lineweight value.  Receives a value in hundredths
			of mm and converts it to a mil value.  If the mil value is valid (between 0 and 255), it sets the
			value to display in mm for that mil value and returns true.  If the mil value is invalid, it returns
			false.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetLineWeightDisplayPt(CallBackPtr, short sixteenths);
		/*
			Sets the Pt value to display for an internal mil lineweight value.  Receives a value in sixteenths
			of points and converts it to a mil value.  If the mil value is valid (between 0 and 255), it sets
			the value to display in points for that mil value and returns true.  If the mil value is invalid, it
			returns false.
		*/

	extern "C" void GS_CALLBACK GS_SetLWByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified object to use the class line weight.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetObjBeginningMarker(CallBackPtr, MCObjectHandle h, SMarkerStyle mstyle, CBBoolean visibility);
		/*
			Sets the beginning marker information for an object
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetObjEndMarker(CallBackPtr, MCObjectHandle h, SMarkerStyle mstyle, CBBoolean visibility);
		/*
			Sets the end marker information for an object
		*/

	extern "C" void GS_CALLBACK GS_SetOpacity(CallBackPtr, MCObjectHandle h, OpacityRef  inNewOpacity);
		/*
			Sets the opacity of h
		*/

	extern "C" void GS_CALLBACK GS_SetOpacityByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified class to use the class opacity
		*/

	extern "C" void GS_CALLBACK GS_SetPColorsByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified object to use the class pen colors.
		*/

	extern "C" void GS_CALLBACK GS_SetPPatByClass(CallBackPtr, MCObjectHandle h);
		/*
			Sets the specified class to use the class pen style.
		*/

	extern "C" void GS_CALLBACK GS_SetVertexVis(CallBackPtr, MCObjectHandle h, short vertNum, Boolean vis);
		/*
			Sets the visibility of the segment passing through (for curves) or the segment following the
			specified vertex.  When a curved segment's visibility is changed, it affects the entire curve from
			corner point to corner point.  Multiple bezier segements in sequence, for example, will be made
			visible or invisible as a group.
		*/



///////////////////////////////////////////
//  Attributes (System)
///////////////////////////////////////////


	extern "C" MCObjectHandle GS_CALLBACK GS_GetDefinition(CallBackPtr, MCObjectHandle h);
		/*
			Returns the definition of an instance.  h may be a symbol instance, record instance, layer link, or
			on-drawing worksheet.
		*/

	extern "C" short GS_CALLBACK GS_GetDXFColorToLineWeight(CallBackPtr, const short inDXFColorIndex);
		/*
			Given a valid DXF color index from 0 to 255 (0 = kDXFColorByBlock), the lineweight in mils that the
			color maps to is returned. This map is used to initialize the mapping dialog on import, and to
			control mapping when doing a silent import with GS_ImportDXFMac() or GS_ImportDXFWin(). If that
			color index is not currently being mapped to a lineweight, kUnmappedLineWeight is returned. During
			DXF import, any unmapped values will be set to a default value. To set the mapping, use
			GS_SetDXFColorToLineWeight(). Constants for standard colors (kDXFCyan, etc) are defined in
			MiniCadCallBacks.h.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetNamedObject(CallBackPtr, const InternalName& objName);
		/*
			Returns the object with the specified name or nil if no such object exists.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetObjectClass(CallBackPtr, MCObjectHandle h);
		/*
			Returns the internal index of the class h belongs to.  You can translate the class ID number to its
			name by using ClassIDToName.
		*/

	extern "C" void GS_CALLBACK GS_GetObjectName(CallBackPtr, MCObjectHandle h, InternalName& name);
		/*
			Gets the name of the object passed.  If h has no name, name is set to the empty string.
		*/

	extern "C" short GS_CALLBACK GS_GetObjectType(CallBackPtr, MCObjectHandle h);
		/*
			Returns the object type code of h, or 0 if h is nil.  Object type codes are listed in
			MiniCadCallBacks.h.
		*/

	extern "C" void GS_CALLBACK GS_GetSymbolDefinitionIcon(CallBackPtr, MCObjectHandle theSymDef, Sint32 icon[32] );
		/*
			OBSOLETE.  
		*/

	extern "C" short GS_CALLBACK GS_GetSymbolDefinitionType(CallBackPtr, MCObjectHandle theSymDef);
		/*
			Returns whether the current symbols is 2D, 3D or both (k2DSym, k3DSym, kHybridSym).
		*/

	extern "C" Boolean GS_CALLBACK GS_IsLocked(CallBackPtr, MCObjectHandle h);
		/*
			Returns the Lock state of h.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsSelected(CallBackPtr, MCObjectHandle h);
		/*
			Returns the selection state of h.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsVisible(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether or not the object is currently visible.  (Note: visibility is not affected by
			whether or not the object currently intersects the screen).  Passed a layer, this routine takes into
			account the layer visibility flags and the current layer options.
		*/

	extern "C" void GS_CALLBACK GS_LockObject(CallBackPtr, MCObjectHandle h, Boolean lock = true);
		/*
			Locks or unlocks the specified object according to the value of lock (true indicates lock, false
			indicates unlock).
		*/

	extern "C" void GS_CALLBACK GS_SelectObject(CallBackPtr, MCObjectHandle h, Boolean select = true);
		/*
			Sets the selection flag of h.  
		*/

	extern "C" void GS_CALLBACK GS_SetDXFColorToLineWeight(CallBackPtr, const short inDXFColorIndex, const short inLineWeight);
		/*
			This sets DXF import system to map the given DXF color index  to the given lineweight in mils.  A
			valid DXF color index is from 0 to 255 (0 = kDXFColorByBlock) and a valid lineweight in mils is 0 to
			255 (0 is invisible and should normally not be used). This map is used to initialize the mapping
			dialog on import, and to control mapping when doing a silent import with GS_ImportDXFMac() or
			GS_ImportDXFWin(). During DXF import, any unmapped values will be set to a default value. To view
			the current mapping, use GS_GetDXFColorToLineWeight(). Constants for standard colors (kDXFCyan, etc)
			are defined in MiniCadCallBacks.h.
		*/

	extern "C" void GS_CALLBACK GS_SetObjectClass(CallBackPtr, MCObjectHandle h, InternalIndex classID);
		/*
			Changes h to the specified class.  If classID does not map to a defined class, h is left unchanged. 
			If h's visibility changes, it will be redrawn.
		*/

	extern "C" GSError GS_CALLBACK GS_SetObjectName(CallBackPtr, MCObjectHandle h, const InternalName& name);
		/*
			Sets h's name to the specified string.  To un-name an object, set its name to the empty string, i.e.
			'SetObjectName(h, "\p");'.  SetObjectName may return one of three error codes: noErr (there was no
			error), nameNotUniqueErr (some other object already has the same name), or nameTableFullErr (no new
			names can be added; you must un-name some objects first.)  You are limited to approximately 16,000
			named objects in a single file, though you may run out of memory before reaching this limit.
		*/

	extern "C" void GS_CALLBACK GS_SetSymbolDefinitionIcon(CallBackPtr, MCObjectHandle theSymDef, const Sint32 icon[32] );
		/*
			Sets the icon of the passed symbol definition to the one pointed to by icon.
		*/

	extern "C" void GS_CALLBACK GS_SetVisibility(CallBackPtr, MCObjectHandle h, Boolean visible);
		/*
			Turns h visible if visible is true; invisible if false.
		*/



///////////////////////////////////////////
//  Auxiliary and Data Objects
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AttachAuxObject(CallBackPtr, MCObjectHandle h, MCObjectHandle newOwner);
		/*
			Puts h in the aux list of newOwner.  h may not be in any list when AttachAuxObject is called.
		*/

	extern "C" void GS_CALLBACK GS_DeleteAuxObject(CallBackPtr, MCObjectHandle h, MCObjectHandle owner);
		/*
			Deletes h from the aux list of owner.  If h is not actually in owner's aux list, DeleteAuxObject
			does nothing.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_FindAuxObject(CallBackPtr, MCObjectHandle owner, short objectType);
		/*
			FindAuxObject returns the first object in owner's aux list with the specified object type, or nil if
			it can't find any.  See FindDataObject for sample code.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_FindDataObject(CallBackPtr, MCObjectHandle owner, OSType tag);
		/*
			FindDataObject will return the first data object attached to owner that has the specified tag.  A
			tag of '****' will match any data object.  If you only need to find one instance of a data object
			(if, for example, you know that only one should exist), use this:
					
						Handle ao;
						if ((ao = FindDataObject(cbp, owner, myTag)) != nil) ...
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_FirstAuxObject(CallBackPtr, MCObjectHandle h);
		/*
			Returns the first object in h's aux list, or nil if h's aux list is empty.  From this first object,
			you may reach successive objects by calling NextObject.  A loop to iterate over all the objects in
			an aux list looks something like this:
					
			   for (Handle h = FirstAuxObject(owner); h != nil; h = NextObject(h)) {
			        Do your thing here. 
						}
						
			This routine is supplied for advanced users'normally you should use FindDataObject and
			NextDataObject.
		*/

	extern "C" OSType GS_CALLBACK GS_GetDataTag(CallBackPtr, MCObjectHandle h);
		/*
			Returns the tag of a data object.  If h is not a data object, GetDataTag returns '    ' (four
			spaces).  This routine is useful when searching aux lists by hand using FirstAuxObject or the 'find
			any' tag for FindDataObject.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetPluginType(CallBackPtr, const InternalName& name, EVSPluginType& type);
		/*
			Returns what type the indicated plug-in is in the type parameter.  The types are defined in
			MiniCadCallBacks.h.  Returns false if it fails to determine the type.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsPluginFormat(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the indicated format node is used for a plug-in.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_NewDataObject(CallBackPtr, MCObjectHandle attachTo, OSType tag, size_t objectSize);
		/*
			Creates a new data object of size objectSize with the specified tag and attaches it to the object
			attachTo.  If attachTo is nil, the data object is still created, but is not attached to anything;
			you must then use AttachAuxObject to attach it to another object.  Calling GetObjectType on a data
			object will return userDataNode.  Graphsoft reserves all tags consisting entirely of lowercase
			letters.  [Note: While data objects are intended to only appear as auxiliary objects, you may insert
			them into the normal drawing list with no ill effects.  However, using excessive numbers of them
			this way will slow down basic operations such as picking, snapping, and redrawing.]
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_NextAuxObject(CallBackPtr, MCObjectHandle start, short objectType);
		/*
			Similar to FindAuxObject, but begins searching at the specified object.  See NextDataObject for
			sample code.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_NextDataObject(CallBackPtr, MCObjectHandle start, OSType tag);
		/*
			Similar to FindDataObject, but begins searching at the specified object.  If you need to find all of
			several instances attached to a single object, use this loop:
					
			   for (Handle ao = FindDataObject(cbp, owner, myTag), nextAux = NextObject(cbp, ao);
			        ao != nil;
			        ao = NextDataObject(cbp, nextAux, myTag), nextAux = ao ? NextObject(cbp, ao) : nil)
						...
					
			You may perform any operation you need on ao inside the loop, including deleting it.
					
			Note that careless use of NextDataObject may send you into an infinite loop.  Consider the
			following:
					
						for (Handle ao = FindDataObject(cbp, owner, 'BLAH'); ao != nil; ao = NextDataObject(cbp,
			ao, 'BLAH'))
			       ...
					
			If the initialization step (ao = FindDataObject(cbp, owner, 'BLAH')) returns an object, this loop
			will never terminate.  Because the NextDataObject call starts searching at an object already known
			to match, it will keep returning the object ao forever.
		*/

	extern "C" void GS_CALLBACK GS_RemoveAuxObject(CallBackPtr, MCObjectHandle h, MCObjectHandle owner);
		/*
			Removes h from the aux list of owner.  If h is not actually in owner's aux list, RemoveAuxObject
			does nothing.  h is not deleted, merely detached.  You may then use AttachAuxObject to attach it to
			a different owner.
		*/

	extern "C" Boolean GS_CALLBACK GS_TaggedDataCreate(CallBackPtr, MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,size_t numDataElements);
		/*
			Creates an Aux list data container node attached to inOwner. 'dataContainer' is a unique four char
			ID .  An array of 'numDataElements'  of type 'dataType' is created.  The array is then accessable in
			inOwner's at <dataContainer, dataType, dataTag> 
		*/

	extern "C" Boolean GS_CALLBACK GS_TaggedDataGet(CallBackPtr, MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,size_t dataIndex, void* getData);
		/*
			Gets 'data' of type 'dataType'  mapped to 'dataTag'  into array created by GS_TaggedDataCreate. Gets
			the data in inOwner's aux list at <dataContainer, dataType, dataTag> 

		*/

	extern "C" Boolean GS_CALLBACK GS_TaggedDataGetNumElements(CallBackPtr, MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,Sint32* getData);
		/*
			Gets the number of elements in the array specified by <inOwner, dataContainer, dataType, dataTag>
		*/

	extern "C" Boolean GS_CALLBACK GS_TaggedDataRemoveContainer(CallBackPtr, MCObjectHandle inOwnerObj,OSType dataContainer);
		/*
			Removes the data container node from the aux list of owner.
		*/

	extern "C" Boolean GS_CALLBACK GS_TaggedDataRemoveTag(CallBackPtr, MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag);
		/*
			Removes the data of type 'dataType' stored in 'dataContainer' that is mapped to 'dataTag'.  Removes
			the data in inOwner's aux list at <dataContainer, dataType, dataTag> 
		*/

	extern "C" Boolean GS_CALLBACK GS_TaggedDataSet(CallBackPtr, MCObjectHandle inOwnerObj,OSType dataContainer,Sint32 dataType,Sint32 dataTag,size_t dataIndex, const void* data);
		/*
			Sets 'data' of type 'dataType'  mapped to 'dataTag'  into array created by GS_TaggedDataCreate. Sets
			the data in inOwner's aux list at <dataContainer, dataType, dataTag> 

		*/



///////////////////////////////////////////
//  Coordinate Transformation
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_CoordLengthToPageLengthN(CallBackPtr, WorldCoord len, double_gs& pageLength);
		/*
			Returns in pageLength the value in page-inches that corresponds to the Coord len.
		*/

	/* *** Implemented as a library call *** */
	double_gs GS_LIBRARY GS_CoordLengthToPageLengthN(CallBackPtr, WorldCoord len);
		/*
			Function version of the same call which returns void.
		*/

	extern "C" double_gs GS_CALLBACK GS_CoordLengthToPagePoints(CallBackPtr, WorldCoord len);
		/*
			Converts Coord values to typographical point sizes relative to the current page. NOTE that at
			different layer scale factors, the same Coord dimension will convert to different point sizes. This
			function is typically used to interpret the values returned from text size calls.
		*/

	extern "C" Boolean GS_CALLBACK GS_CoordLengthToPixelLength(CallBackPtr, WorldCoord numCoords, short& numPixels);
		/*
			Converts a number of Coords into pixels.  Returns false if numCoords is too large to fit into a
			two-byte integer.
		*/

	extern "C" void GS_CALLBACK GS_CoordLengthToUnitsLengthN(CallBackPtr, WorldCoord len,  double_gs& unitsLength);
		/*
			Transforms a length in system coordinates to the equivalent number of real-world units.  The units
			are the base units of the drawing, e.g. millimeters, inches, &c.  (The base unit for feet and inches
			is feet, not inches.)
		*/

	/* *** Implemented as a library call *** */
	double_gs GS_LIBRARY GS_CoordLengthToUnitsLengthN(CallBackPtr, WorldCoord len);
		/*
			Function version of the same call which returns void.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateOvalN(CallBackPtr, const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height);
		/*
			creates oval with specified properties
		*/

	extern "C" Boolean GS_CALLBACK GS_DimStringToCoord(CallBackPtr, const TXString& s, WorldCoord& c);
		/*
			Transforms the dimension string s into a MiniCad+ coordinate.  Returns false if s could not be
			interpreted as a dimension, true if it could.
		*/

	extern "C" void GS_CALLBACK GS_FPCoordLengthToPageLength(CallBackPtr, double_param coordLen, double_gs& pageLen);
		/*
			Convert floating point Coord length to page-inch length.
		*/

	extern "C" void GS_CALLBACK GS_FPCoordLengthToUnitsLength(CallBackPtr, double_param coordLen, double_gs& unitsLen);
		/*
			Convert floating point Coord length to drawing units length.
		*/

	extern "C" void GS_CALLBACK GS_ModelPt2DToScreenPt(CallBackPtr, WorldPt& vertex);
		/*
			It transform a given vertex from model definition to VCS definition.
		*/

	extern "C" void GS_CALLBACK GS_ModelVecToScreenVec(CallBackPtr, WorldPt& vertex);
		/*
			It transform a given vertex from model definition to VCS definition.
		*/

	extern "C" void GS_CALLBACK GS_PageLengthToFPCoordLength(CallBackPtr, double_param pageLen, double_gs& coordLen);
		/*
			Convert page-inch length to floating point Coord length.
		*/

	extern "C" WorldCoord GS_CALLBACK GS_PagePointsToCoordLength(CallBackPtr, double_gs& points);
		/*
			Converts typographical point sizes to Coord values relative to the current page. NOTE that at
			different layer scale factors, the same point size will convert to different Coord values. This
			function is typically used to pass point values to text size calls.
		*/

	extern "C" void GS_CALLBACK GS_PixelLengthToCoordLength(CallBackPtr, short numPixels, WorldCoord& numCoords);
		/*
			Converts a number of screen pixels into Coords.
		*/

	extern "C" void GS_CALLBACK GS_ScreenPtToModelPt2D(CallBackPtr, WorldPt& vertex);
		/*
			It transform a given vertex from VCS definition to model definition.
		*/

	extern "C" void GS_CALLBACK GS_ScreenVecToModelVec(CallBackPtr, WorldPt& vertex);
		/*
			It transform a given vertex from VCS definition to model definition.
		*/

	extern "C" void GS_CALLBACK GS_UnitsLengthToFPCoordLength(CallBackPtr, double_param unitsLen, double_gs& coordLen);
		/*
			Convert drawing units length to floating point Coord length.
		*/

	extern "C" WorldCoord GS_CALLBACK GS_WorldCoordsPerDrawingUnit(CallBackPtr);
		/*
			Returns the number of world space coordinates that represent 1 of the currently selected drawing
			units. For example, if the current document's units were millimeters, this function would return the
			number of WorldCoords that are in 1 millimeter.
		*/

	extern "C" void GS_CALLBACK GS_WrapPageLengthToCoordLengthN(CallBackPtr, double_param len, double_gs& outCoordLen);
		/*
			TEMPORARY wrapper procedure around PageLengthToCoordLengthN function to avoid illegal return type of
			Coord. See Jeff Koppi.
		*/

	extern "C" void GS_CALLBACK GS_WrapUnitsLengthToCoordLengthN(CallBackPtr, double_param len, double_gs& outCoordLen);
		/*
			TEMPORARY wrapper procedure around PageLengthToCoordLengthN function to avoid illegal return type of
			Coord. See Jeff Koppi.
		*/



///////////////////////////////////////////
//  Creation
///////////////////////////////////////////


	extern "C" short GS_CALLBACK GS_AddSolid(CallBackPtr, MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);


	extern "C" Boolean GS_CALLBACK GS_AppendRoofEdge(CallBackPtr, MCObjectHandle object, const WorldPt& edgePt, double_param slope, WorldCoord projection, WorldCoord eaveHeight);
		/*
			Create a vertex of the roof.  Vertex is appended to the end of the list of vertices.  Vertices
			define the outline of the roof.  Vertices must progress in a counter clock wise direction, when
			viewed from a top view, otherwise the roof cannot be built.

			edgePt: Coordinate point for this edge
			slope: pitch of this roof edge
			projection: eave overhang
			eaveHeight: eave height
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_Create3DPoly(CallBackPtr);
		/*
			Creates and returns a handle to a new 3D polygon with no vertices.  Use Add3DVertex or
			Insert3DVertex to build the polygon.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateAngleDimension(CallBackPtr, const WorldPt& center, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset);


	extern "C" MCObjectHandle GS_CALLBACK GS_CreateArcN(CallBackPtr, const WorldRect& bounds, double_param startAngle, double_param sweepAngle);
		/*
			Creates a new arc object as the topmost object in the current layer.  The arc is a portion of the
			oval defined by the rectangle bounds.  startAngle and endAngle are in degrees, with 0' being east
			and moving counterclockwise.  Returns a handle to the new arc object.
		*/

	extern "C" short GS_CALLBACK GS_CreateBatDormer(CallBackPtr, MCObjectHandle object);
		/*
			Create a bat style dormer.

			This only creates the object, SetDormerAttributes() & SetBatAttributes() must still be called to
			define the attributes of the dormer.

			object: is the roof object into which to add the dormer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateChainDimension(CallBackPtr, MCObjectHandle h1, MCObjectHandle h2);
		/*
			Creates and returns a new chain dimension object when the two dimensions or chains that are passed
			in meet the requirements for being in a single chain dimension object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCombineIntoSurface(CallBackPtr, const WorldPt& inPoint);
		/*
			Creates a polyline from the bounded selection surrounding inPoint.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCone(CallBackPtr, const WorldPt3& center, const WorldPt3 &tip, WorldCoord radius);
		/*
			Creates a solid cone at the specified location, and adds it to the top of the active layer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateContourCurves(CallBackPtr, MCObjectHandle h, double_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal);


	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCustomDimensionStandard(CallBackPtr, const TXString& name);
		/*
			Creates a new custom dimension standard with the name specified and default values of the  active
			dimension standard.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCustomObject(CallBackPtr, const InternalName& name, const WorldPt& location, double_param angle = 0.0);
		/*
			Creates an instance of the custom object specified by the name argument using  location and angle. 
			Custom Object tools typically call this function with the current cursor location.  Calls
			DefineCustomObject() first to either find the defining FormatNode or create it.  If it is created,
			the user will be presented with an initialization dialog.  Returns handle to Object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCustomObjectByMatrix(CallBackPtr, const InternalName& name, const TransformMatrix& matrix);
		/*
			Creates an instance of the CustomObject specified by the name argument.  Location and orientation
			are defined by the matrix argument.  Calls DefineCustomObject() first to either find the defining
			FormatNode or create it.  If it is created, the user will be presented with an initialization
			dialog.  Returns handle to Object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCustomObjectDoubleClick(CallBackPtr, const InternalName& name);
		/*
			Displays an object creation dialog which enables the creation of an instance of the CustomObject
			specified by the name argument.  Location and orientation are defined by  the dialog.  Calls
			DefineCustomObject() first to either find the defining FormatNode or create it.  Returns handle to
			Object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateCustomObjectPath(CallBackPtr, const InternalName& name, MCObjectHandle pathHand = NULL, MCObjectHandle profileGroupHand = NULL);
		/*
			Creates an instance of the path custom object specified by the name argument using location and
			angle.  Calls DefineCustomObject() first to either find the defining FormatNode or create it.  If it
			is created, the user will be presented with an initialization dialog.  Returns handle to Object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateExtrude(CallBackPtr, WorldCoord bottom, WorldCoord top);
		/*
			Creates and returns a handle to a new extrude entity.  You may add objects to the definition either
			by using AddObjectToContainer, InsertObjectBefore, or InsertObjectAfter or by calling EnterContainer
			on the returned handle.  [See the manual entries for these functions for more details.].  The
			extrude matrix defaults to the identity matrix (top view, no rotation).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateExtrudeAlongPath(CallBackPtr, MCObjectHandle pathHandle, MCObjectHandle profileHandle);
		/*
			returns the surface handle if it succeeds, returns NULL if it fails
		*/

	extern "C" short GS_CALLBACK GS_CreateGableDormer(CallBackPtr, MCObjectHandle object);
		/*
			Create a gable style dormer.

			This only creates the object, SetDormerAttributes() & SetGableAttributes() must still be called to
			define the attributes of the dormer.

			object: is the roof object into which to add the dormer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateGroup(CallBackPtr);
		/*
			Creates and returns a handle to a new group object.  You may add objects to the group either by
			using AddObjectToContainer, InsertObjectBefore, or InsertObjectAfter or by calling EnterContainer on
			the returned handle.  [See the manual entries for these functions for more details.]
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateHemisphere(CallBackPtr, const WorldPt3& center, const WorldPt3 &topPoint);
		/*
			Creates a solid hemisphere at the specified location, and adds it to the top of the active layer. 
			The topPoint is the point on the hemisphere furthest from the base; the center is the center of the
			sphere that the hemisphere is a half of.
		*/

	extern "C" short GS_CALLBACK GS_CreateHipDormer(CallBackPtr, MCObjectHandle object);
		/*
			Create a hip style dormer.

			This only creates the object, SetDormerAttributes() & SetHipAttributes() must still be called to
			define the attributes of the dormer.

			object: is the roof object into which to add the dormer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateImageProp(CallBackPtr, TXString& propName, InternalIndex textureRef, WorldCoord height, WorldCoord width, Boolean enforceImageAspectRatio, Boolean crossedPlanes, Boolean createPlugin, Boolean autoRotate, Boolean createSymbol);
		/*
			Create an image prop from the options specified.  The texture resource and optional symbol created
			will use names derived from the propName parameter.  If those names are being used then unique names
			will be assigned.  If enforceImageAspectRatio is true, the prop width will be derived from the prop
			height and the texture's image aspect ratio. Otherwise the height and width can be set independently
			of the texture's image aspect ratio.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateInterpolatedSurface(CallBackPtr, MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree);
		/*
			Creates an interpolated surface with the specified degrees and number of points. If a handle to a
			NURBS surface is provided,the interpolated surface will approximate that surface;if the handle is
			NULL, it creates a rectangular surface.numUPts(numVPts) must be greater than uDegree(vDegree).

		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLayer(CallBackPtr, const InternalName& layerName, short layerType);
		/*
			Creates a layer of the specified type.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLayerN(CallBackPtr, const InternalName& name, double_param scale);
		/*
			Creates a layer with the specified name and scale, and adds it to the end of the layer list (it will
			draw on top).  The layer is made active.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLightN(CallBackPtr, const WorldPt3& pos, short kind, Boolean isOn, double_param brightness, const WorldPt3& color, Boolean castShadows);
		/*
			Creates and returns a new light with the specified position, kind (kDirectionalLight | kPointLight |
			kSpotLight), and basic light data.  The light is created as the topmost object in the current layer. 
			This routine returns nil if the creation fails.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLine(CallBackPtr, const WorldPt& startPt, const WorldPt& endPt);
		/*
			Creates a line from startPt to endPt.  Will not create a line if both points are the same.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLinearDimension(CallBackPtr, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset, WorldCoord textOffset, const Vector2& dir, short dimType);
		/*
			Creates a linear dimension object.  p1 and p2 are the two endpoints of the distance to be measured. 
			startOffset is the distance from p1 to the dimension line.  textOffset is CURRENTLY UNUSED. dir is
			the normalized difference between p2 and p1. If dir is passed in as (0,0), this value is calculated
			automatically. dimType indicates whether to allow only horizontal and vertical dimension lines,
			whether to rotate the dimension line to have the same direction as the vector between p1 and p2, or
			whether to create an ordinate dimension.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLocus(CallBackPtr, const WorldPt& location);
		/*
			Creates a locus point at the specified location.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLocus3D(CallBackPtr, const WorldPt3& location);
		/*
			Creates a 3D locus point at the specified location.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateLoftSurfaces(CallBackPtr, MCObjectHandle groupCurvesH, Boolean bRule, Boolean  bClose, Boolean bSolid);
		/*
			CreateLoftSurfaces creates NURBS surfaces by interpolating a group of cross-section curves.  The
			sequence of the curves being added into the group is the sequence of the curves being lofted.

		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateNurbsCurve(CallBackPtr, WorldPt3 firstPt, bool byCtrlPts, short degree);


	extern "C" MCObjectHandle GS_CALLBACK GS_CreateNurbsSurface(CallBackPtr, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree);
		/*
			Creates a NURBS surface with the number of control points and degrees as specified. Call
			NurbsSetPt3D() to set
			the control net

		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateOval(CallBackPtr, const WorldRect& bounds);
		/*
			create oval with specified specified bounds
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreatePolyshape(CallBackPtr);
		/*
			Creates a new polygon object with no vertices.  This routine is used to create both polygons and
			polylines: CreatePolyshape creates a polygon, then AddVertex and InsertVertex will turn it into a
			polyline if asked to add a non-corner vertex.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateQArc(CallBackPtr, const WorldRect& bounds, short quadrant);
		/*
			Creates a quarterArc 
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateRectangle(CallBackPtr, const WorldRect& bounds);
		/*
			Creates an rectangle with the specified bounds.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateRectangleN(CallBackPtr, const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height);
		/*
			Creates rectangle with specified properties
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateRoof(CallBackPtr, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter);
		/*
			Create a roof object.  The outline of the roof must still be defined.  Use AppendRoofVertex() to
			define the roof plan.

			genGableWall: Set to true to have a wall created at gable ends of the roof.  Otherwise no object
			will be inserted.
			bearingInset is where the weight of the roof rests on the wall.  This is an inset from the defining
			edge of the roof plan.
			miterType:  Specify 1 for a vertical miter, 2 for horizontal miter, 3 for a double miter cut, and 4
			for a square end miter cut.
			vertMiter: This is used only with the double miter type; it specifies the vertical length of the
			miter cut.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateRoundWall(CallBackPtr, const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, WorldCoord wallThickness = 0);
		/*
			Creates a round wall whose arc spans from startPt to endPt  and contains ptOnArc with the specified
			thickeness.  If the thickness is zero, the default wall thickness will be used.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateRRectangle(CallBackPtr, const WorldRect& bounds, WorldCoord xDiam, WorldCoord yDiam);
		/*
			created rotated rectanle with specified bounding properties
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateRRectangleN(CallBackPtr, const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, CBBoolean isProportional);
		/*
			creates rotated rectangle specified properities
		*/

	extern "C" short GS_CALLBACK GS_CreateShedDormer(CallBackPtr, MCObjectHandle object);
		/*
			Create a shed style dormer.
			This only creates the object, SetDormerAttributes() & SetShedAttributes() must still be called to
			define the attributes of the dormer.

			object: is the roof object into which to add the dormer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateBasicSlab(CallBackPtr, short slabKind);
		/*
			Creates a slab of the specified slab kind (1 = roof, 2 = floor, 3 = column).  Call SetObjectVariable
			to fill in the properties for the slab object (all constants start with ovSlab...).  Slabs are
			container objects, after creating the slab add objects to the container to give it shape.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateSphere(CallBackPtr, const WorldPt3& center, WorldCoord radius);
		/*
			Creates a solid sphere at the specified location, and adds it to the top of the active layer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateStaticHatch(CallBackPtr, const InternalName& name, const WorldPt& inOriginPoint, double_param inRotationAngle);
		/*
			Creates a static hatch using inHatchName inside the bounded selection surrounding inOriginPoint. 
			inRotationAngle determines the rotation of the result. 
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateStaticHatchFromObject(CallBackPtr, MCObjectHandle inObj, const InternalName& name, const WorldPt& inOriginPoint, double_param inRotationAngle);
		/*
			Creates a static hatch using inHatchName inside the object inObject.  inOriginPoint and
			inRotationAngle determine the origin and rotation of the resultin hatch pattern. 
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateSurfacefromCurvesNetwork(CallBackPtr);
		/*
			This function will create a NURBS surface from a network of selected intersecting curves in the
			document.


		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateSweepN(CallBackPtr, double_param startAngle, double_param arcAngle, double_param incrAngle, WorldCoord screwDist);
		/*
			Creates and returns a handle to a new sweep entity.  You may add objects to the definition either by
			using AddObjectToContainer, InsertObjectBefore, or InsertObjectAfter or by calling EnterContainer on
			the returned handle.  [See the manual entries for these functions for more details.].  The sweep
			matrix defaults to the identity matrix (top view, no rotation).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateSymbolDefinition(CallBackPtr, const InternalName& name);
		/*
			Creates and returns a handle to a new symbol definition object.  You may add objects to the
			definition either by using AddObjectToContainer, InsertObjectBefore, or InsertObjectAfter or by
			calling EnterContainer on the returned handle.  [See the manual entries for these functions for more
			details.]  Function returns nil if the name is already in use.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateSymbolFolder(CallBackPtr, const InternalName& name);
		/*
			Creates a new symbol folder with the specified name if it doesn't already exist.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateTaperedExtrude(CallBackPtr, MCObjectHandle profileH, const double_param angle = 0.0, const double_param height = 1.0 );
		/*
			Creates tapered extrude objects from a selected object profileH. The tapered angle is in degree. The
			Tapered height is in inch.
		*/

	extern "C" short GS_CALLBACK GS_CreateTrapeziumDormer(CallBackPtr, MCObjectHandle object);
		/*
			Create a trapezium style dormer.

			This only creates the object, SetDormerAttributes() & SetTrapeziumAttributes() must still be called
			to define the attributes of the dormer.

			object: is the roof object into which to add the dormer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateViewport(CallBackPtr, MCObjectHandle parentHandle);
		/*
			Creates a viewport object. The specified parent handle may only be a layer or a group contained
			within a layer, nested or otherwise.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateWall(CallBackPtr, const WorldPt& startPt, const WorldPt& endPt, WorldCoord thickness = 0);
		/*
			Creates a wall from startPt to endPt with the specified thickness.  If thickness is zero, the Wall
			Preferences will be used.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_DefineCustomObject(CallBackPtr, const InternalName& name, Byte prefWhen = kCustomObjectPrefAlways);
		/*
			Look for a FormatNode which defines the custom object specified by the name argument.  If it does
			not exist, create a FormatNode based on definition in resource file.  Also create a RecordNode with
			default parameter values.  The prefWhen argument determines if a dialog is presented: 0 means never,
			1 means always, and 2 means only if we just created a new FormatNode.  The dialog allows the user to
			set the default parameter values. Returns handle to CustomObject FormatNode.
		*/

	extern "C" void GS_CALLBACK GS_DuplicateSelection(CallBackPtr, WorldCoord dx, WorldCoord dy);
		/*
			Duplicate the selection and move it <dx, dy> from the original.  The new duplicates will be
			selected, and the originals deselected.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ExtendNurbsCurve(CallBackPtr, MCObjectHandle curveHandle, double_param distance, Boolean bStart, Boolean bLinear);
		/*
			Extends a curve by a given distance at the start or the end.  The extension can either be linear or
			can match the curvature of the existing end.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ExtendNurbsSurface(CallBackPtr, MCObjectHandle surfaceHandle, double_param distance, Boolean bStart, Boolean bLinear, Boolean bUDir);
		/*
			Extends a surface by a given distance at the start or the end of the U direction or V direction. 
			The extension can either be linear or can continue the curvature of the edge of the surface.

		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GenerateBezierApproximationFromPolygon(CallBackPtr, MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic);
		/*
			Generates a quadratic B'zier curve approximation of the path represented by the constituent vertices
			of the referenced polygon object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GroupSelection(CallBackPtr);
		/*
			Groups all currently selected objects.  If there are less than two objects selected, it will not
			create a group and will return nil.
		*/

	extern "C" short GS_CALLBACK GS_IntersectSolid(CallBackPtr, MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		/*


		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_PlaceSymbolByNameN(CallBackPtr, const InternalName& symName, const WorldPt& location, double_param rotation = 0.0);
		/*
			Places an instance of the the symbol with the given name at the specified location, rotated by
			<rotation> degrees.  If there is no symbol with the specified name, PlaceSymbolByName does nothing.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_PlaceSymbolN(CallBackPtr, MCObjectHandle definition, const WorldPt& location, double_param rotation = 0.0);
		/*
			Places an instance of the symbol <definition> at the specified location, rotated by <rotation>
			degrees.  If definition is nil, PlaceSymbol does nothing.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_RevolveWithRail(CallBackPtr, MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH);
		/*
			Creates a NURBS surface or a group of surfaces by revolving a profile about an axis and following a
			rail guide curve on a plane perpendicular to the plane containing the axis and the profile.

		*/

	extern "C" void GS_CALLBACK GS_Split2DObjectByLine(CallBackPtr, MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles);
		/*
			Split a  2d object by a line defined by two points p1 and p2.
		*/

	extern "C" short GS_CALLBACK GS_SubtractSolid(CallBackPtr, MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);




///////////////////////////////////////////
//  Dialogs
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AddChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short nItemIndex);
		/*
			Add strItemText to a layout manager list box or pull down menu. The text item is added at position
			nItemIdex. This is a zero based index for the list of items. 

			This call should only be used inside of an event handler callback function.

			For the multicolumn list box, items in different columns must be separated by tab characters.  I.e.,
			use this function to set a whole line at a time, with columns separated by tab characters.  All tab
			stops must have been set before calling this function.
		*/

	extern "C" void GS_CALLBACK GS_AddListBoxTabStop(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 tabStop);
		/*
			Adds a tab stop to a Layout Manager list box.
			The last parameter is the tab stop, in characters.  This function should be called in the dialog
			handler, as opposed to the
			dialog definition procedure.  This function will clear all data in the list control.
		*/

	extern "C" short GS_CALLBACK GS_AddListBrowserImage(CallBackPtr, Sint32 dialogID, Sint32 componentID, short resourceType, short resourceID, short resourceIDSelected = 0);
		/*
			Adds specified image resource to image list.

		*/

	extern "C" Boolean GS_CALLBACK GS_AdjustComponentPixelPos(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nHorizontalPixels, Sint32 nVerticalPixels);
		/*
			Adjust the pixel width and height of the specified Layout Manager component.  Can be used before or
			after SetBelowComponent or SetRightComponent.  Alignment calls override pixel adjustments.
		*/

	extern "C" void GS_CALLBACK GS_AlertCritical(CallBackPtr, const TXString& text, const TXString& advice = "");
		/*
			Displays an alert dialog that informs the user of a serious problem that requires intervention or
			correction before work can continue.
		*/

	extern "C" void GS_CALLBACK GS_AlertInform(CallBackPtr, const TXString& text, 
			const TXString& advice = "", 
			CBBoolean minorAlert = false, 
			const TXString& category = "",
			const TXString& item = "",
			const TXString& checkboxOverideText = "");
		/*
			Displays a dialog which informs the user about the result of a command.  Offers no user choices; the
			user acknowledges the message by clicking the OK button. Specify a category and item to show an
			optional "Do not show this dialog again" checkbox.
		*/

	extern "C" short GS_CALLBACK GS_AlertQuestion(CallBackPtr, const TXString& question, const TXString& advice = "", short defaultButton = 0,
			const TXString& OKOverrideText = "", const TXString& cancelOverrideText = "", const TXString& customButtonAText = "", 
			const TXString& customButtonBText = "",
			const TXString& category = "", 
			const TXString& item = "", 
			const TXString& checkboxOverideText = "");
		/*
			Displays a dialog that alerts the user to a condition or situation that requires the user's decision
			and input before preceeding, such as an impending action with potentially destructive or
			irreversible consequencies.   Specify a category and an item to show an optional 'Always do the
			selected action' checkbox.
		*/

	extern "C" bool GS_CALLBACK GS_AlignBottomEdge(CallBackPtr, Sint32 dialogID, Sint32 srcItemID, short bottomID, short alignMode = 1);
		/*
			Sets the bottomID for the srcItem. The bottomID can be any number. All items with the same bottomID
			will be aligned along their bottom edge. 

			alignMode = eResize = 0 resize the item to align the edge
			alignMode = eShift = 1 shift the item to align the edge
		*/

	extern "C" bool GS_CALLBACK GS_AlignLeftEdge(CallBackPtr, Sint32 dialogID, Sint32 srcItemID, short leftID, short alignMode = 1);
		/*
			Sets the leftID for the srcItem. The leftID can be any number. All items with the same leftID will
			be aligned along their left edge. 

			alignMode = eResize = 0 resize the item to align the edge
			alignMode = eShift = 1 shift the item to align the edge
		*/

	extern "C" bool GS_CALLBACK GS_AlignRightEdge(CallBackPtr, Sint32 dialogID, Sint32 srcItemID, short rightID, short alignMode = 1);
		/*
			Sets the rightID for the srcItem. RightID can be any number. All items with the same rightID will be
			aligned along their right edge. 

			alignMode = eResize = 0 resize the item to align the edge
			alignMode = eShift = 1 shift the item to align the edge
		*/

	extern "C" Boolean GS_CALLBACK GS_AreListBrowserColumnLinesEnabled(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Determines if column lines are drawn.
		*/

	extern "C" Boolean GS_CALLBACK GS_AreListBrowserRadioColumnLinesEnabled(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Determines if "column" lines are drawn between radio control items.
		*/

	extern "C" Boolean GS_CALLBACK GS_ClearGradientSliderSegments(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Removes all segments greater than 2 from the gradient slider.
		*/

	extern "C" Boolean GS_CALLBACK GS_Confirm(CallBackPtr, const TXString& strNode, Boolean yesOrNo);
		/*
			Posts a confirmation dialog with the specified message and two buttons.  If yesOrNo is false, the
			buttons are labeled OK and Cancel, if it is true, they read Yes and No instead.  Returns 1 if the
			user clicks OK (or Yes) and 0 if they click Cancel (or No).
		*/

	extern "C" void GS_CALLBACK GS_CreateCenteredStaticText(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar);
		/*
			Similar to CreateStaticText, but creates static text that is centered in its control field on the
			dialog.
		*/

	extern "C" void GS_CALLBACK GS_CreateCheckBox(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& name);
		/*
			Creates a layout manager check box. 
			Event handling:
			data field is set to the state of the control (true or false) for check box events
		*/

	extern "C" void GS_CALLBACK GS_CreateCheckBoxGroupBox(CallBackPtr, Sint32 dialogID, short itemID, const TXString& name, bool hasFrame);
		/*
			Creates a checkbox group box.  The checkbox will have name as its label.  If hasFrame is true, the
			group will have a box drawn around it like a regular group box.
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateClassPullDownMenu(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar);
		/*
			Creates a Layout Manager class pull down menu control.
		*/

	extern "C" void GS_CALLBACK GS_CreateCMYKColorSwatch(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			CreateCMYKColorSwatch creates a control that allows the user to select a color using the standard OS
			color picker and obtain the results as a CMYK color.
		*/

	extern "C" void GS_CALLBACK GS_CreateColorPopup(CallBackPtr, Sint32 dialogID, Sint32 itemID, short widthInStdChar = -1);
		/*
			Create a color popup dialog control that displays the 256 color palette associated with the active
			document.  
		*/

	extern "C" void GS_CALLBACK GS_CreateControl(CallBackPtr, Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data);
		/*
			Creates the control specified by controlKind.  The name and data parameter are general input
			parameters for the different control types. See MiniCadCallBacks.X.h for the complete list of
			indexed controls. 
		*/

	extern "C" void GS_CALLBACK GS_CreateCustomControl(CallBackPtr, Sint32 dlogID, Sint32 controlID, short width, short length);
		/*
			Creates an empty layout manager control
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateDesignLayerPullDownMenu(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar);
		/*
			Creates a Layout Manager design layer pull down menu control.
		*/

	extern "C" void GS_CALLBACK GS_CreateEditInteger(CallBackPtr, Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, short widthInStdChar);
		/*
			Edits Sint32 integers. Allows math calculations in control. 
		*/

	extern "C" void GS_CALLBACK GS_CreateEditReal(CallBackPtr, Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, short widthInStdChar);
		/*
			Edits real values. Allows usits and math calculations to be entered in edit field.  There are 5 edit
			real types: 1 - Real, regular old real type; 2 - Angle, SDK input and output is always in degrees
			but display and user input is based on documents Unit settings; 3 - Dimension, usually an offset
			this is a distance that is not tied to the origin; 4 -  CoordinateX, this is an exact x location on
			the drawing; 5- CoordinateY, this is an exact y location on the drawing. There are separate x and y
			controls to account for changes the user may make to the origin.  Z coordinates should use the
			offset mode.
		*/

	extern "C" void GS_CALLBACK GS_CreateEditText(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& defaultText, short widthInStdChar, short heightInLines = 1);
		/*
			Creates a layout manager edit box with the given itemID. The widthInStdChar specifies the
			aproximate number of characters that will be visible in the edit box. The edit text is limited to
			255 characters
			Event handling:
			an event is generated everytime a key is hit in the edit text, the value of the data field is
			undefined
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateEnhancedPullDownMenu(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, Boolean bShowIconInMainWindow);


	extern "C" void GS_CALLBACK GS_CreateGroupBox(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& name, Boolean hasFrame);
		/*
			Creates a layout manager group box with the given itemID.  
			name - leave blank to create box with no name
			hasFrame - set to false to create a logical grouping. 
			For dialogs with more than one radio button group, each radio button group must have its own group
			box, but the group box does not have to have a frame. 

			Event handling:
			Group boxes do not generate events.

		*/

	extern "C" Boolean GS_CALLBACK GS_CreateIconPushButton(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nIconID, Sint32 widthInStdChar);
		/*
			Creates an icon push button with the specified icon ID and width in characters.
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateImageControl(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 iWidthPixels, Sint32 iHeightPixels, MCObjectHandle hImage);
		/*
			Creates a Layout Manager image control.
		*/

	extern "C" Sint32 GS_CALLBACK GS_CreateLayout(CallBackPtr, const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName);
		/*
			creates a layout manager dialog and returns a dialog ID
			hasHelp - pass true to create a dialog help box along the bottom of the dialog
			defaultButtonName & cancelButtonName - if the string is non nil, creates a  button with ID equal to
			1 or 2 respectively. These buttons always appear in the bottom right corner of the dialog, and they
			are always placed in the order that is appropriate for a particular platform. For custom placement
			of the default and cancel buttons, pass nil in this routine and use the standard routines to create
			and place buttons with ID's equal to 1 or 2. 
		*/

	extern "C" void GS_CALLBACK GS_CreateLineAttributePopup(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Create a dialog control that displays both line style and line weight choices available in the
			current document.  
		*/

	extern "C" void GS_CALLBACK GS_CreateLineStylePopup(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Create a dialog control that displays the line style choices available in the active document.  
		*/

	extern "C" void GS_CALLBACK GS_CreateLineWeightPopup(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Create a line weight popup dialog control to display list of line weights available in current
			document.  
		*/

	extern "C" void GS_CALLBACK GS_CreateListBox(CallBackPtr, Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines);
		/*
			Creates a layout manager list box with the given itemID.  

			Event handling:
			When an item is selected the itemID equals list boxes ID and the data field contains the index of
			the selected item.
			When an item is double clicked the itemID equals the negative of the list box ID and the data field
			contains the index of the selected item.
		*/

	extern "C" void GS_CALLBACK GS_CreateListBoxN(CallBackPtr, Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines, Boolean isMultiSel);
		/*
			Creates a layout manager list box with the given itemID.  


		*/

	extern "C" void GS_CALLBACK GS_CreateListBrowser(CallBackPtr, Sint32 dialogID, Sint32 componentID, CBSignedShort widthInStdChar, CBSignedShort heightInLines);
		/*
			Creates a layout manager list browser control.
		*/

	extern "C" void GS_CALLBACK GS_CreateMarkerPopup(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Create a Marker popup dialog control.
		*/

	extern "C" void GS_CALLBACK GS_CreatePatternPopup(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Create a pattern popup dialog control that displays all fill patterns available in current document.
		*/

	extern "C" void GS_CALLBACK GS_CreatePullDownMenu(CallBackPtr, Sint32 dialogID, Sint32 itemID, short widthInStdChar);
		/*
			Creates a layout manager pull down menu with the given itemID.  

			Event handling:
			data equals the index of the selected item
		*/

	extern "C" Boolean GS_CALLBACK GS_CreatePullDownMenuGroupBox(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, const TXString& strLabel, Boolean bHasFrame);


	extern "C" void GS_CALLBACK GS_CreatePushButton(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& buttonName);
		/*
			Creates a layout manager push button menu with the given itemID.  

			Event handling:
			data is undefined for push button events
		*/

	extern "C" void GS_CALLBACK GS_CreateRadioButton(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& buttonName);
		/*
			Creates a layout manager radio button menu with the given itemID. 

			Event handling:
			Event is generated when the radio button state is changed to true, data parameter is undefined.
		*/

	extern "C" void GS_CALLBACK GS_CreateRadioButtonGroupBox(CallBackPtr, Sint32 dialogID, short itemID, const TXString& name, bool hasFrame);
		/*
			Creates a radio button group box.  The radio button will have name as its label.  If hasFrame is
			true, the group will have a box drawn around it like a regular group box.
		*/

	extern "C" Sint32 GS_CALLBACK GS_CreateResizableLayout(CallBackPtr, const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, CBBoolean widthResizable, CBBoolean heightResizable);
		/*
			Similar to CreateLayout, but creates a resizable dialog.  The parameters are the same as
			CreateLayout except for widthResizable, and heightResizable, which specify whether the width and
			height, respectively, will be resizable in the resulting dialog.  A dialog ID is returned by the
			function.
		*/

	extern "C" void GS_CALLBACK GS_CreateRightStaticText(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar);
		/*
			Similar to CreateStaticText, but creates static text that is right-justified in its control field on
			the dialog.
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateSeparator(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 iLength);
		/*
			Creates a Layout Manager image separator.
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateSheetLayerPullDownMenu(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar);
		/*
			Creates a Layout Manager sheet layer pull down menu control.
		*/

	extern "C" void GS_CALLBACK GS_CreateStandardIconControl(CallBackPtr, Sint32 dialogID, Sint32 iconControlID, Sint32 iconNumber);
		/*
			Creates a standard icon control, which is used to display either the application icon or an alert
			icon.
		*/

	extern "C" void GS_CALLBACK GS_CreateStaticText(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar);
		/*
			Creates a layout manager static text menu with the given itemID.  
			widthInStdChar is only used for multiline static texts. For single line static text set this
			field to -1 and the appropriate width will be calculated. 

			Event handling:
			no event handling for static text.
		*/

	extern "C" void GS_CALLBACK GS_CreateSwapControl(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Creates a swap control.  dialogID is the ID of the dialog, and itemID is the ID of the control.
		*/

	extern "C" void GS_CALLBACK GS_CreateSwapPane(CallBackPtr, Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID);
		/*
			Creates a swap pane within the specified swap control.  dialogID is the ID of the dialog,
			swapControlID is the ID of the swap control, and newGroupID is the ID of the group which is to be
			inserted into the swap control.
		*/

	extern "C" void GS_CALLBACK GS_CreateTabControl(CallBackPtr, Sint32 dialogID, short itemID);
		/*
			Creates a tab control.
		*/

	extern "C" void GS_CALLBACK GS_CreateTabPane(CallBackPtr, Sint32 dialogID, short itemID, short groupID);
		/*
			Creates a tab pane within a tab control.  groupID is the ID of the group that contains the controls
			which will appear on this tab pane.
		*/

	extern "C" Boolean GS_CALLBACK GS_CreateThreeStateCheckBox(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, const TXString& strName);


	extern "C" Boolean GS_CALLBACK GS_CreateTreeControl(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar, Sint32 heightInLines);
		/*
			Creates a Layout Manager tree control.
		*/

	extern "C" void GS_CALLBACK GS_DeleteAllItems(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Deletes all items in the specified list box.
		*/

	extern "C" Boolean GS_CALLBACK GS_DeleteAllListBrowserItems(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Deletes all list browser items.
		*/

	extern "C" Boolean GS_CALLBACK GS_DeleteListBrowserColumn(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Deletes a column from the specified list browser control.
		*/

	extern "C" Boolean GS_CALLBACK GS_DeleteListBrowserItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex);
		/*
			Deletes an item from the specified list browser control.
		*/

	extern "C" void GS_CALLBACK GS_DeselectEditText(CallBackPtr, Sint32 dialogID, Sint32 controlID);
		/*
			Deselects all text in the specified edit control.
		*/

	extern "C" Boolean GS_CALLBACK GS_DisplayColorPopup(CallBackPtr, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right, Boolean inDisplayByClassOption, ColorRef& ioColorRef, Boolean& ioIsByClass);
		/*
			Displays standard application color picking menu at the location specified by the box
			(top,left,bottom,tight).  Retruns false if user cancels.
		*/

	extern "C" void GS_CALLBACK GS_DisplaySwapPane(CallBackPtr, Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber);
		/*
			Causes the specified swap pane to be displayed within the specified swap control.  dialogID is the
			ID of the dialog, swapControlID is the ID of the swap control, and groupNumber is the 0-based index
			of the swap pane to be displayed.  Swap panes are numbered sequentially in the order that they were
			inserted into the control.
		*/

	extern "C" void GS_CALLBACK GS_DisplayTabPane(CallBackPtr, Sint32 dialogID, Sint32 controlID, Sint32 groupNumber);
		/*
			Causes the specified tab pane to be displayed within the specified tab control.  dialogID is the ID
			of the dialog, controlID is the ID of the tab control, and groupNumber is the 0-based index of the
			tab pane to be displayed.  Tab panes are numbered sequentially in the order that they were inserted
			into the control.
		*/

	extern "C" void GS_CALLBACK GS_EnableItem(CallBackPtr, Sint32 dialogID, Sint32 itemID, Boolean bEnable);
		/*
			Enable or disable (gray) a layout manager item. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" Boolean GS_CALLBACK GS_EnableListBrowser(CallBackPtr, Sint32 dialogID, Sint32 componentID, Boolean enable);
		/*
			Enables or disables the specified list browser.

		*/

	extern "C" Boolean GS_CALLBACK GS_EnableListBrowserClickAllDataChange(CallBackPtr, Sint32 dialogID, Sint32 componentID, Boolean enable);
		/*
			Enables all radio and multi state column data items to be changed with a single click if the alt key
			or option key is pressed during the click.
		*/

	extern "C" void GS_CALLBACK GS_EnableListBrowserColumnLines(CallBackPtr, Sint32 dialogID, Sint32 componentID, Boolean enableColumnLines);
		/*
			Enables/disables column lines.
		*/

	extern "C" void GS_CALLBACK GS_EnableListBrowserColumnTracking(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableColumnTracking);
		/*
			Enables/disables column tracking.
		*/

	extern "C" Boolean GS_CALLBACK GS_EnableListBrowserDragAndDrop(CallBackPtr, Sint32 dialogID, Sint32 componentID, Boolean bEnable);
		/*
			Enables or disables drag and drop on the specified list browser control.  Use
			SetListBrowserDragAndDropColumn to set the drag and drop column.
		*/

	extern "C" Boolean GS_CALLBACK GS_EnableListBrowserDropOnIndices(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartIndex, Sint32 iEndIndex, Boolean bEnable);


	extern "C" void GS_CALLBACK GS_EnableListBrowserRadioColumnLines(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableRadioColumnLines);
		/*
			Enables/disables radio item "column" lines.
		*/

	extern "C" Boolean GS_CALLBACK GS_EnableListBrowserSingleLineSelection(CallBackPtr, Sint32 dialogID, Sint32 componentID, Boolean enable);
		/*
			Enables or disables single line only selection.
			Multiple selections will not be allowed if this feature is on.
		*/

	extern "C" void GS_CALLBACK GS_EnableListBrowserSorting(CallBackPtr, Sint32 dialogID, Sint32 componentID, Boolean enableSorting);
		/*
			Enables/disables sorting.
		*/

	extern "C" Boolean GS_CALLBACK GS_EnableListBrowserUpdates(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Boolean bEnableUpdates);
		/*
			Determines if updates should be enabled for the specified list browser.
		*/

	extern "C" Boolean GS_CALLBACK GS_EnsureListBrowserItemIsVisible(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iIndex);
		/*
			Ensures the element at iIndex is visible in the specified list browser.
		*/

	extern "C" Boolean GS_CALLBACK GS_ExpandTreeControlItem(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, Boolean bExpand);
		/*
			Expands or collapses the specified tree control item.
		*/

	extern "C" Boolean GS_CALLBACK GS_FindListBrowserColumnDataItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& columnDataItemIndex);
		/*
			Finds the column data item with the specified text.
		*/

	extern "C" Boolean GS_CALLBACK GS_FindListBrowserColumnItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& itemIndex);
		/*
			Finds the column item with the specified text.
		*/

	extern "C" void GS_CALLBACK GS_FormatTextDialog(CallBackPtr, FormatTextType& formatTextRec);
		/*
			Opens the Format Text Dialog. The formatTextRec is an input and output parameter block.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetActiveEditItem(CallBackPtr, Sint32 dialogID);
		/*
			Returns the active edit control in the specified dialog.  If no edit control has the focus, -1 is
			returned.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetActivePane(CallBackPtr, Sint32 dialogID, Sint32 controlID);
		/*
			Retunrs the active pane within the specified tab or swap control.  dialogID is the ID of the dialog,
			controlID is the ID of the tab or swap control.  This function works with both tab and swap controls.
		*/

	extern "C" void GS_CALLBACK GS_GetBooleanItem(CallBackPtr, Sint32 dialogID, Sint32 itemID, Boolean& state);
		/*
			Get the boolean state of a layout manager radio button or check box. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_GetChoiceCount(CallBackPtr, Sint32 dialogID, Sint32 itemID, short& numItems);
		/*
			Gets the number of text items in a layout manager list box or pull down menu. The count is one
			based. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_GetChoiceIndex(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex);
		/*
			Finds the index of the given string in a layout manager list box or pull down menu. The index is
			zero based and is set to -1 if the item is not found. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_GetChoiceText(CallBackPtr, Sint32 dialogID, Sint32 itemID, short nItemIndex, TXString& strItemText);
		/*
			Gets the text for the given index in a layout manager list box or pull down menu. The index is zero
			based. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_GetCMYKColor(CallBackPtr, Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor);
		/*
			GetCMYKColor allows the user to get the CMYK color selected in a CMYK Color Swatch control.
		*/

	extern "C" void GS_CALLBACK GS_GetColorButton(CallBackPtr, Sint32 dialogID, Sint32 itemID, RGBColor& rgb);
		/*
			Gets the color of a layout manager color button.
		*/

	extern "C" void GS_CALLBACK GS_GetColorChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, short& colorIndex);
		/*
			Get current choice for color popup dialog control. 
		*/

	extern "C" Boolean GS_CALLBACK GS_GetComponentRect(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32& nLeft, Sint32& nTop, Sint32& nRight, Sint32& nBottom);
		/*
			Retrieves the bounding rect coordinates of the specified Layout Manager component.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetComponentTextWidth(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32& nWidthInLMUnits);
		/*
			Retrieves the static text's width in Layout Manager Units.
		*/

	struct SControlDataBase;
	extern "C" void GS_CALLBACK GS_GetControlData(CallBackPtr, Sint32 dialogID, Sint32 itemID, SControlDataBase& data);
		/*
			Get the control data for itemID.

			See MiniCadCallBack.X.h for a description of how this call is used with each indexed control. 
		*/

	extern "C" void GS_CALLBACK GS_GetCustomControlScrollArea(CallBackPtr, Sint32 dialogID, Sint32 component, Sint32 *leftStart, Sint32 *topStart);
		/*
			Gets the scrollbar data on a Custom control
		*/

	extern "C" bool GS_CALLBACK GS_GetEditInteger(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32& value);
		/*
			Gets the user entered integer from the specified field. Calculates any math expressions the user may
			have entered. Returns false if there is an error.
		*/

	extern "C" bool GS_CALLBACK GS_GetEditReal(CallBackPtr, Sint32 dialogID, Sint32 componentID, short editRealType, double& value);
		/*
			Gets the user entered real from the specified field. Calculates any math expressions the user may
			have entered. Returns false if there is an error. See CreateEditReal for a description of
			editRealType.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetGradientSliderData(CallBackPtr, Sint32 dialogID, Sint32 componentID, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color);
		/*
			Gets the spot position, midpoint position and color of the specified gradient slider segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetGradientSliderSelectedMarker(CallBackPtr, Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType);
		/*
			Gets the selected marker for the specified gradient slider. Use the EGradientSliderMarkerType
			constants to identify the marker type; kGradientSliderMarkerSpot = 1, kGradientSliderMarkerMidpoint
			= 2.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetIconPushButtonState(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed);
		/*
			Retrieves the state of the specified Layout Manager icon push button (pressed or not pressed).
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetImagePopupObject(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex);
		/*
			Returns the object index for the specified image popup item.
		*/

	extern "C" short GS_CALLBACK GS_GetImagePopupObjectItemIndex(CallBackPtr, Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		/*
			Returns item index for the specified object.
		*/

	extern "C" short GS_CALLBACK GS_GetImagePopupSelectedItem(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Gets the selected item.
		*/

	extern "C" void GS_CALLBACK GS_GetItemText(CallBackPtr, Sint32 dialogID, Sint32 itemID, TXString& strCurrentText);
		/*
			Get the text of a layout manager item.   This call should only be used inside of an event handler
			callback function.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetLayoutDialogPosition(CallBackPtr, Sint32 dialogID, short& left, short& top, short& right, short& bottom);
		/*
			Get the screen location of the dialog window, in pixels.
			This function will return false if the dialog window does not exist.  The dialog window will exist
			anytime between the Setup message and OK/Cancel message.
		*/

	extern "C" void GS_CALLBACK GS_GetLayoutDialogSize(CallBackPtr, Sint32 dialogID, short& width, short& height);
		/*
			Retrieves a Layout Manager dialog's size, in pixels.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetLayoutFromRsrc(CallBackPtr, short textRsrcID);
		/*
			Creates a layout dialog and returns a dailog ID.
			textRsrcID is the ID number of a Macintosh text resorce that contains a VectorScript specification
			of the layout manager dialog.
			If there is an error then the fuction returns zero.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetLBHeaderTextWidth(CallBackPtr, const TXString& str, bool allowForSortingTriangle = false);
		/*
			Gives the width in pixels that is required to display the given string without truncation in a
			ListBrowser -- can be used a parameter to GS_InsertListBrowserColumn()
		*/


	extern "C" void GS_CALLBACK GS_GetLineWeightChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, short& lineWeight);
		/*
			Get current choice for a line weight dialog control.  The value is in mils.  
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserColumnWidth(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, short& width);
		/*
			Gets the width of the specified column in the specified list browser control.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserColumnDataItemInfo(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex, TXString& itemString, short &imageOn, short &imageOff, Sint32 &itemData);
		/*
			Gets the specified column data item's text, image and user data.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetListBrowserColumnSortState(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 columnIndex);
		/*
			Gets the column sort state.

			Returns:
			the column sort state:
				-1 Descending sort
				1  Ascending sort
				0  No sort
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserColumnOwnerDrawnType(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 &iOwnerDrawnType);
		/*
			Gets the list browser column's owner drawn type.

			iOwnerDrawnType - input - the list browser item's owner drawn type.
			NOTE: for valid constants see enum EListBrowserOwnerDrawnType in MiniCadCallBacks.h
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserColumnHeaderToolTip(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText);
		/*
			Sets the list browser column header's tooltip text.

			strToolTipPrimaryText - determines the text displayed when the user hovers the mouse over the
			header.
			strToolTipSubText - determines the text displayed when the user hovers the mouse over the header
			then expands the tooltip text by pressing alt on Windows or Command on Mac

		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserColumnHeaderJust(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 &iJustification);
		/*
			Gets the list browser header's column justification.

			iJustification:
				left	1
				center	2
				right	3
				invalid	4
		*/

	extern "C" short GS_CALLBACK GS_GetListBrowserControlType(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Gets control type for column.
		*/

	extern "C" short GS_CALLBACK GS_GetListBrowserEditDisplayType(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Gets edit display type for list items in specified column.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserEventInfo(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32& iEventType, Sint32& iRowIndex, Sint32& iColumnIndex);
		/*
			Retrieves the list browser event info
		*/


	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemData(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32& nUserData);
		/*
			Retrieves the user data associated with the list browser item.
		*/

	extern "C" short GS_CALLBACK GS_GetListBrowserItemDisplayType(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Gets item display type for list items in specified column.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemFillForeColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		/*
			Gets the specified list browser item's fill foreground color.

			iRedIndex	- output - the item's red index		[0-255].
			iBlueIndex	- output - the item's blue index		[0-255].
			iGreenIndex	- output - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemFillBackColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		/*
			Gets the specified list browser item's fill background color.

			iRedIndex	- output - the item's red index		[0-255].
			iBlueIndex	- output - the item's blue index		[0-255].
			iGreenIndex	- output - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemGradientOrImageRefNumber(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &liRefNumber);
		/*
			Gets the specified list browser item's gradient or image.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemInfo(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, short& imageIndex);
		/*
			Gets data from item.
		*/

#if _WINDOWS
	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemPatternIndex(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iPatternIndex);
		/*
			Gets the specified list browser item's pattern index.

			iPatternIndex - output  - the item's pattern index

			Windows-only.
		*/
#endif

#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemPattern(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* &pPattern);
		/*
			Gets the specified list browser item's pattern.

			pPattern - input  - the item's pattern.

			Mac-only.
		*/
#endif

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemPenForeColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		/*
			Gets the specified list browser item's pen foreground color.

			iRedIndex	- output - the item's red index		[0-255].
			iBlueIndex	- output - the item's blue index		[0-255].
			iGreenIndex	- output - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemPenBackColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		/*
			Gets the specified list browser item's pen background color.

			iRedIndex	- output - the item's red index		[0-255].
			iBlueIndex	- output - the item's blue index		[0-255].
			iGreenIndex	- output - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemTextJust(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &justification);
		/*
			Gets the text alignment for the specified list browser item.

			justification - output - the item's justification.
						- left		1
						- center		2
						- right		3
						- invalid		4
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemTextStyle(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, unsigned char &textStyle);
		/*
			Gets the text style for the specified list browser item.

			textStyle - input - the item's text style.
						- plain		0000 (0)
						- bold		0001 (1)
						- italic		0010 (2)
						- underline	0100 (4)
						- invalid		1000 (8)
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserItemTextColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &redIndex, Sint32 &greenIndex, Sint32 &blueIndex);
		/*
			Gets the text color for the specified list browser item.

			redIndex	- output - the item's red index		[0-255].
			blueIndex	- output - the item's blue index		[0-255].
			greenIndex	- output - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_GetListBrowserMultImageIndexes(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32& iImageIndex0, Sint32& iImageIndex1, Sint32& iImageIndex2);
		/*
			Gets the index of the images within the list browser multi image display.

			iImageIndex0	- ouput - the icons.rsrc icon family ID for the first image.
			iImageIndex1	- ouput - the icons.rsrc icon family ID for the second image.
			iImageIndex2	- ouput - the icons.rsrc icon family ID for the third image.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetListBrowserSortColumn(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Gets the index of the sort column in the specified list browser control.
		*/

	extern "C" void GS_CALLBACK GS_GetMarkerChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, MarkerType& style, CBSignedByte& angle, double& size, double& width, CBUnsignedByte& thicknessBasis, double& thickness);
		/*
			Get current choice for Marker popup dialog control. 

		*/

	extern "C" short GS_CALLBACK GS_GetMarkerPopupSelectedItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size);
		/*
			*** Note:  This function is obsolete; please use 'Set/GetMarkerChoice()'

			Returns the 1-based index number of the selected item in the specified marker popup menu item.  If
			the return value equals 8, a custom marker is selected, and the style angle, and size parameters
			will describe the marker.
		*/

	extern "C" GSHandle GS_CALLBACK GS_GetMultilineText(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Returns a handle to the text of a multiline edit control in a Layout Manager dialog.  This function
			can handle strings longer than 254 characters.  The calling function is responsible for freeing this
			handle.

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" short GS_CALLBACK GS_GetNumGradientSliderSegments(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Gets the number of segments in the gradient slider. Note: a gradient slider must always have at
			least 2 segments.
		*/

	extern "C" short GS_CALLBACK GS_GetNumImagePopupItems(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Returns the number of items in the image popup.
		*/

	extern "C" short GS_CALLBACK GS_GetNumListBrowserColumns(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Gets the number of columns in the specified list browser control.
		*/

	extern "C" short GS_CALLBACK GS_GetNumListBrowserColumnDataItems(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Get the number of columnDataItems.
		*/

	extern "C" short GS_CALLBACK GS_GetNumListBrowserItems(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Gets the number of items in the specified list browser control.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetNumSelectedListBrowserItems(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Returns the number of selected list browser items.

		*/

	extern "C" void GS_CALLBACK GS_GetPatternData(CallBackPtr, Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor);
		/*
			Get current choice for pattern popup dialog control, and the displayed foreground and background
			color indexes.
		*/

	extern "C" void GS_CALLBACK GS_GetSelChoiceIndex(CallBackPtr, Sint32 dialogID, Sint32 itemID, short inStartIndex, short& outSelectedIndex);
		/*
			Returns the selected value in a choice item. inStartIndex is where to start looking.  It will return
			the value index (choiceNumber) or -1 if no selection is found.

			[jag 2-8-99]  GetSelChoice now works with list boxes.  Since list boxes can support multiple
			selections, GetSelChoice can be called repeatedly to retrieve all selections.  Pass 0 for atChoice
			to retrieve the first one, and choiceNumber will contain the index of that item.  To retrieve the
			next one, pass choiceNumber + 1 for atChoice.  Repeat this process until -1 is returned for
			choiceNumber.  Also, if no items are selected in the list box, -1 will be returned for choiceNumber.
		*/

	extern "C" void GS_CALLBACK GS_GetSelectedChoiceIndex(CallBackPtr, Sint32 dialogID, Sint32 itemID, short& nItemIndex);
		/*
			Gets the index of the selected item in a layout manager list box or pull down menu. The index is
			zero based. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_GetSelectionRange(CallBackPtr, Sint32 dialogID, Sint32 controlID, Sint32& startPos, Sint32& endPos);
		/*
			Returns the range of the current selection for the specified control.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetThreeStateCheckBoxState(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32& iState);


	extern "C" Boolean GS_CALLBACK GS_GetTreeControlItemData(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData);
		/*
			Retrieves the user data of the specified item from a tree control.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetTreeControlSelectedItem(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32& nItemID);
		/*
			Retrieves the itemID of the selected item from a Layout Manager tree control.
		*/

	extern "C" Sint32 GS_CALLBACK Deprecated545(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, const TXString& strName, Sint32 iIconID);

	extern "C" short GS_CALLBACK GS_InsertGradientSliderSegment(CallBackPtr, Sint32 dialogID, Sint32 componentID, double_param spotPosition, const WorldPt3& color);
		/*
			 Inserts a new segment into the gradient slider and initializes its data to the specified values.
		*/

	extern "C" short GS_CALLBACK GS_InsertImagePopupObjectItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		/*
			Inserts the specified object into the image popup.
		*/

	extern "C" Sint32 GS_CALLBACK GS_InsertImagePopupResource(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index);
		/*
			Inserts the indicated item in the specified resource list into the indicated image popup and returns
			the image popup index of the inserted item.
		*/

	extern "C" Sint32 GS_CALLBACK GS_InsertImagePopupSeparator(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel);


	extern "C" short GS_CALLBACK GS_InsertListBrowserColumn(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& headerString, short width);
		/*
			Inserts a column into the specified list browser control.
		*/

	extern "C" short GS_CALLBACK GS_InsertListBrowserColumnDataItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short imageOn, short imageOff, Sint32 itemData);
		/*
			Inserts column data item with specified data.
		*/

	extern "C" short GS_CALLBACK GS_InsertListBrowserItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex, const TXString& itemString);
		/*
			Insert an item into the specified list browser control.
		*/

	extern "C" Boolean GS_CALLBACK GS_InsertProposedClassOrLayerItem(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, Sint32 nIconIndex);

		/*
			Inserts a class or layer item in the proposed section of a Class, Design Layer, or Sheet Layer
			Layout Manager Pull Down.

		*/

	extern "C" Sint32 GS_CALLBACK GS_InsertTreeControlItem(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, Sint32 nParentID, Sint32 nAfterID);
		/*
			Inserts an item into a Layout Manager tree control.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsItemEnabled(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID);
		/*
			Determines if the specified item is currently enabled.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsItemVisible(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID);
		/*
			Determines if the specified item is currently visible.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsListBrowserColumnTrackingEnabled(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Determines if column tracking is enabled for the specified column.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsListBrowserItemSelected(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex);
		/*
			Determines if the specified item is currently selected.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsListBrowserSortingEnabled(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Determines if sorting is enabled or disabled.
		*/

	extern "C" Boolean GS_CALLBACK GS_NotifyPullDownClicked(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID);
		/*
			Sends an item hit notification when the pull down menu is clicked, allowing developers to
			dynamically populate the menu.
		*/

	extern "C" VoidPtr GS_CALLBACK GS_OverrideControl(CallBackPtr, Sint32 dlogID, Sint32 controlID, VoidPtr vp);
		/*
			Overrides a Layout Manager Control
		*/

	extern "C" void GS_CALLBACK GS_PostMinorNoteAlert(CallBackPtr, const TXString& strNode);
		/*
			Posts a minor note alert with the specified message.  (A note alert has the exclamation point icon,
			your message, and an OK button. If the "route minor alerts to databar" preference is set, this alert
			is displayed only on the databar.
		*/

	extern "C" void GS_CALLBACK GS_PostMinorStopAlert(CallBackPtr, const TXString& strNode);
		/*
			Posts a stop alert with the specified message.  (A stop alert has the stop icon, your message, and
			an OK button.  If the "route minor alerts to databar" preference is set, this alert is displayed
			only on the databar.
		*/

	extern "C" void GS_CALLBACK GS_PostNoteAlert(CallBackPtr,  const TXString& strNode);
		/*
			Posts a note alert with the specified message.  (A note alert has the exclamation point icon, your
			message, and an OK button.
		*/

	extern "C" void GS_CALLBACK GS_PostStopAlert(CallBackPtr, const  TXString& strNode);
		/*
			Posts a stop alert with the specified message.  (A stop alert has the stop icon, your message, and
			an OK button.
		*/

	extern "C" Boolean GS_CALLBACK GS_RefreshItem(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID);
		/*
			Refreshes the specified item.
		*/

	extern "C" Boolean GS_CALLBACK GS_RefreshListBrowser(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Refreshes the contents of the specified list browser.
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveAllImagePopupItems(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Removes all items from the image popup.
		*/

	extern "C" void GS_CALLBACK GS_RemoveAllListBrowserColumnDataItems(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex);
		/*
			Removes all column data items.
		*/

	extern "C" void GS_CALLBACK GS_RemoveChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, short itemIndexToRemove);
		/*
			Remove the string located at the given index  in a layout manager list box or pull down menu. The
			index is zero based. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveEnhancedPullDownMenuItemRange(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartItemIndexToRemove, Sint32 iEndItemIndexToRemove);


	extern "C" Boolean GS_CALLBACK GS_RemoveGradientSliderSegment(CallBackPtr, Sint32 dialogID, Sint32 componentID, short segmentIndex);
		/*
			Removes the specified segment from the gradient slider.
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveImagePopupItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex);
		/*
			Removes the specified item from the image popup.
		*/

	extern "C" void GS_CALLBACK GS_RemoveListBoxTabStop(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Removes the last tab stop from a Layout Manager list box.
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveListBrowserColumnDataItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex);
		/*
			Removes the specified column data item.
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveTreeControlItem(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID);
		/*
			Removes an item from a Layout Manager tree control.
		*/
	
	extern "C" Sint32 GS_CALLBACK GS_RunLayoutDialog(CallBackPtr, Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& universalName);
		/*
			Run the platform specific dialog. Returns the id of the button used to close the dialog.  (1 =
			defualt button, 2 = cancel button)

			handEvent is a pointer to a function with the following parameters (Sint32 dlogID, Sint32& itemHit,
			void* data, void* env)
			itemHit is the itemID of the control that recieved an event, data contains information specific to
			that  control, and env is a pointer that can be use to pass in additional data. The documentation
			for the control creation routines contains an Event handling section which describes how individual
			controls use itemHit and data fields. 

			In addition to the control events there are two special events: 
			For dialog set up itemHit = kSetupMessage. This event occurs after the dialog is created but before
			it is displayed. Use this event to initialize control values.
			For dialog set down itemHit = kSetdownMessage. This event can be used for storing control data. 

			To error check dialog data add a case for the default button (itemHit = 1) and check the data, to
			prevent the dialog from closing set itemHit = 0. 
		*/

	extern "C" void GS_CALLBACK GS_SelectChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, short nItemIndex, Boolean bSelect = true);
		/*
			Selects the item with the given index in a layout manager list box or pull down menu. The index is
			zero based. 

			This call should only be used inside of an event handler callback function.

			9/9/04, JAG: Added the bSelect parameter.  If false, the list item is deselected.  True by default.
		*/

	extern "C" void GS_CALLBACK GS_SelectEditText(CallBackPtr, Sint32 dialogID, Sint32 itemID);
		/*
			Selects the text in an edit text item. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" Boolean GS_CALLBACK GS_SelectTreeControlItem(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID);
		/*
			Selects the specified tree control item.
		*/

	extern "C" bool GS_CALLBACK GS_SetBelowItem(CallBackPtr, Sint32 dialogID, Sint32 srcItemID, Sint32  belowItemID, short indent = 0, short lineSpacing = 0);
		/*
			Used to place a item below the srcItem. Indent shifts the rightItem horizontally and lineSpacing
			shifts the rightItem vertically.
		*/

	extern "C" void GS_CALLBACK GS_SetBooleanItem(CallBackPtr, Sint32 dialogID, Sint32 itemID, Boolean bSelect);
		/*
			Set or clear a layout manager radio button or check box. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_SetCMYKColor(CallBackPtr, Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor);
		/*
			SetCMYKColor allows the user to set the CMYK color selected in a CMYK Color Swatch control.

		*/

	extern "C" void GS_CALLBACK GS_SetColorButton(CallBackPtr, Sint32 dialogID, Sint32 itemID, const RGBColor& rgb);
		/*
			Sets the color of a layout manager color button.
		*/

	extern "C" void GS_CALLBACK GS_SetColorChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, short colorIndex);
		/*
			Sets the choice for the color popup dialog control to the specified color index.  
		*/

	extern "C" Boolean GS_CALLBACK GS_SetComponentIndeterminate(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Boolean bIndeterminateState);
		/*
			Determines if the specified Layout Manager attribute control (line, weight, color, etc) should be
			set to the third, indeterminate state.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetComponentSize(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nWidthPixels, Sint32 nHeightPixels);
		/*
			Sets the width and height of the specified Layout Manager component.
		*/

	extern "C" void GS_CALLBACK GS_SetControlData(CallBackPtr, Sint32 dialogID, Sint32 itemID, const SControlDataBase& data);
		/*
			Sets the data field for the control specified by itemID.

			See MiniCadCallBack.X.h for a description of how this call is used with each indexed control. 
		*/

	extern "C" void GS_CALLBACK GS_SetEdgeBinding(CallBackPtr, Sint32 dialogID, Sint32 itemID, CBBoolean boundToLeft, CBBoolean boundToRight, CBBoolean boundToTop, CBBoolean boundToBottom);
		/*
			Binds edges of a control to its parent.  Binding to an edge indicates that the control will maintain
			a predictable distance from one of its sides to the corresponding side of its parent.  Bindings can
			be either fixed or proportional.  Fixed bindings maintain a constant distance from their parent. 
			Proportional bindings maintain a distance that is a ratio of the initial position to the width (or
			height, as appropriate) of the parent.

			This function sets bindings to be fixed.  To change any of them to be proportional, use
			SetProportionalBinding.
		*/

	extern "C" void GS_CALLBACK GS_SetEditInteger(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 value);
		/*
			Sets the edit integer control to value.
		*/

	extern "C" void GS_CALLBACK GS_SetEditReal(CallBackPtr, Sint32 dialogID, Sint32 componentID, short editRealType, double value);
		/*
			Sets the edit real control to value. See CreateEditReal for a description of editRealType.
		*/

	extern "C" bool GS_CALLBACK GS_SetFirstGroupItem(CallBackPtr, Sint32 dialogID, Sint32 groupID, Sint32 firstItemID);
		/*
			Places firstItemID in the top left corner of the group
		*/

	extern "C" bool GS_CALLBACK GS_SetFirstLayoutItem(CallBackPtr, Sint32 dialogID, Sint32 firstItemID);
		/*
			Places firstItemID in the top left corner of the dialog.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetFocusOnItem(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID);
		/*
			Sets the keyboard input focus on the specified item.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetFocusOnListBrowser(CallBackPtr, Sint32 dialogID, Sint32 componentID);
		/*
			Sets the keyboard/input focus on the specified list browser.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetGradientSliderData(CallBackPtr, Sint32 dialogID, Sint32 componentID, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color);
		/*
			Sets the spot position, midpoint position and color of the specified gradient slider segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetGradientSliderSelectedMarker(CallBackPtr, Sint32 dialogID, Sint32 componentID, short segmentIndex, short markerType);
		/*
			Sets the selected marker for the specified gradient slider. Use the EGradientSliderMarkerType
			constants to specify marker type; kGradientSliderMarkerSpot = 1, kGradientSliderMarkerMidpoint = 2.
		*/

	extern "C" void GS_CALLBACK GS_SetHelpText(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& helpText);
		/*
			Set the help text for itemID. 
		*/

	extern "C" Boolean GS_CALLBACK GS_SetIconPushButtonState(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Boolean bPressed);
		/*
			Sets the state of the specified Layout Manager icon push button to either pressed or not pressed.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetImageControlHandle(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage);
		/*
			Sets the image definition node handle for the specified Layout Manager image control.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetImageControlPath(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath);
		/*
			Sets the image control path for the specified layout manager image control.  Use
			GS_CreateImageControl to first set up the image control then use GS_SetImageControlPath in your
			kSetupMessage case to set the image file path (ie C:\\File.JPG).
		*/

	extern "C" Boolean GS_CALLBACK GS_SetImagePopupSelectedItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex);
		/*
			Sets the selected item.
		*/

	extern "C" void GS_CALLBACK GS_SetItemText(CallBackPtr, Sint32 dialogID, Sint32 itemID, const TXString& strNewText);
		/*
			Set the text for a layout manager item.  To change the dialog title, set itemID to the dialog's ID.

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetItemToolTipText(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, Sint32 nIndex, Sint32 nSubIndex);
		/*
			Sets the tooltip text for list browsers items -- specify row (nIndex) and column (nSubIndex).
			Values are 1-based. 

		*/

	extern "C" Boolean GS_CALLBACK GS_SetLayoutDialogPosition(CallBackPtr, Sint32 dialogID, short left, short top);
		/*
			Set the screen location of the top left corner of the dialog window, in pixels.
			This function will return false if the dialog window does not exist.  The dialog window will exist
			anytime between the Setup message and OK/Cancel message.
		*/

	extern "C" void GS_CALLBACK GS_SetLayoutDialogSize(CallBackPtr, Sint32 dialogID, short width, short height);
		/*
			Sets the size of a Layout Manager dialog, in pixels.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetLayoutOption(CallBackPtr, Sint32 dialogID, short option, Sint32 value);
		/*
			Set various options for specified layout manager dialog.  
			For VW 12, the only option is kLMDialogIsAlert = 1 which ignores the value argument.  It affects the
			OK button position on Windows platform for Alert dialogs.  
		*/


	extern "C" void GS_CALLBACK GS_SetLineWeightChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, short lineWeight);
		/*
			Set the current choice of the line weight dialog control to the value specified in mils.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserColumnWidth(CallBackPtr, Sint32 dialogID, Sint32 componentID, short fromColumn, short toColumn, short width);
		/*
			Sets the width of the specified range of columns of the specified list browser control.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserColumnOwnerDrawnType(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 iOwnerDrawnType);
		/*
			Sets the list browser column's owner drawn type.

			iOwnerDrawnType - input - the list browser item's owner drawn type.
			NOTE: for valid constants see enum EListBrowserOwnerDrawnType in MiniCadCallBacks.h
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserColumnHeaderToolTip(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText);
		/*
			Sets the list browser column header's tooltip text.

			strToolTipPrimaryText - determines the text displayed when the user hovers the mouse over the
			header.
			strToolTipSubText - determines the text displayed when the user hovers the mouse over the header
			then expands the tooltip text by pressing alt on Windows or Command on Mac
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserColumnHeaderJust(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 iJustification);
		/*
			Sets the list browser header's column justification.

			iJustification:
				left	1
				center	2
				right	3
				invalid	4
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserColumnImage(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nColumnIndex, Sint32 nImageIndex);
		/*
			Draws an icon instead of text on a list browser header column.  Use GS_AddListBrowserImage to add
			the image first then use the index of the added image as the nImageIndex parameter in this function.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserControlType(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, short controlType);
		/*
			Sets control type for column.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserDragAndDropColumn(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex);
		/*
			Sets the drag and drop column.  The drag and drop column must be of control type 6:Number.
			When the mouse cursor is over this column, the cursor will change to the drag and drop cursor and
			drag and drop will be enabled.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserEditDisplayType(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType);
		/*
			Sets edit display type for list items in specified column.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemData(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32 nUserData);
		/*
			Sets the user data associated with the list browser item.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemDisplayType(CallBackPtr, Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType);
		/*
			Sets item display type for list items in specified column.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemFillForeColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		/*
			Sets the specified list browser item's fill foreground color.

			iRedIndex	- input - the item's red index		[0-255].
			iBlueIndex	- input - the item's blue index		[0-255].
			iGreenIndex	- input - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemFillBackColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		/*
			Sets the specified list browser item's fill background color.

			iRedIndex	- input - the item's red index		[0-255].
			iBlueIndex	- input - the item's blue index		[0-255].
			iGreenIndex	- input - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemGradientOrImageRefNumber(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, Sint32 liRefNumber);
		/*
			Sets the specified list browser item's gradient or image to display.  Pass in the ref number of the
			gradient or image.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemInfo(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, short imageIndex);
		/*
			Sets data for item.
		*/

#if _WINDOWS
	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemPatternIndex(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iPatternIndex);
		/*
			Sets the specified list browser item's pattern index.

			iPatternIndex - input  - the item's pattern index

			Windows-only.
		*/
#endif

#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemPattern(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* pPattern);
		/*
			Sets the specified list browser item's pattern.

			pPattern - input  - the item's pattern.

			Mac-only.
		*/
#endif

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemPenForeColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		/*
			Sets the specified list browser item's pen foreground color.

			iRedIndex	- input - the item's red index		[0-255].
			iBlueIndex	- input - the item's blue index		[0-255].
			iGreenIndex	- input - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemPenBackColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		/*
			Sets the specified list browser item's pen background color.

			iRedIndex	- input - the item's red index		[0-255].
			iBlueIndex	- input - the item's blue index		[0-255].
			iGreenIndex	- input - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemTextJust(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 justification);
		/*
			Sets the text alignment for the specified list browser item.

			justification - input - the item's justification.
						- left		1
						- center		2
						- right		3
						- invalid		4
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemTextStyle(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, unsigned char textStyle);
		/*
			Sets the text style for the specified list browser item.

			textStyle - input - the item's text style.
						- plain		0000 (0)
						- bold		0001 (1)
						- italic		0010 (2)
						- underline	0100 (4)
						- invalid		1000 (8)
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemTextColor(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 redIndex, Sint32 greenIndex, Sint32 blueIndex);
		/*
			Sets the text color for the specified list browser item.

			redIndex	- input - the item's red index		[0-255].
			blueIndex	- input - the item's blue index		[0-255].
			greenIndex	- input - the item's green index		[0-255].
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserItemUsingColumnDataItem(CallBackPtr, Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short columnDataItemIndex);
		/*
			Sets list item data with specified column data item.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserMultImageIndexes(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iImageIndex0, Sint32 iImageIndex1, Sint32 iImageIndex2);
		/*
			Sets the index of the images within the list browser multi image display.

			iImageIndex0	- input - the icons.rsrc icon family ID for the first image.
			iImageIndex1	- input - the icons.rsrc icon family ID for the second image.
			iImageIndex2	- input - the icons.rsrc icon family ID for the third image.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetListBrowserSelection(CallBackPtr, Sint32 dialogID, Sint32 componentID, short firstItemIndex, short lastItemIndex, Boolean select);
		/*
			Selects the specified range of items.
		*/

	extern "C" void GS_CALLBACK GS_SetListBrowserSortColumn(CallBackPtr, Sint32 dialogID, Sint32 componentID, Sint32 columnIndex, Boolean isAscending);
		/*
			Sets the specified column as the sort column in the specified list browser control.
		*/

	extern "C" void GS_CALLBACK GS_SetMarkerChoice(CallBackPtr, Sint32 dialogID, Sint32 itemID, MarkerType style, CBSignedByte angle, double size, double width, CBUnsignedByte thicknessBasis, double thickness);
		/*
			Set current choice for Marker popup dialog control.  
		*/

	extern "C" void GS_CALLBACK GS_SetMultilineText(CallBackPtr, Sint32 dialogID, Sint32 itemID, GSHandle text);
		/*
			Sets the text of a multiline edit control in a Layout Manager dialog.  This function can handle
			strings longer than 254 characters.

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_SetPatternData(CallBackPtr, Sint32 dialogID, Sint32 itemID, short patternIndex, short foreColor, short backColor);
		/*
			Set current choice and colors for the pattern popup dialog control.  
		*/

	extern "C" void GS_CALLBACK GS_SetProportionalBinding(CallBackPtr, Sint32 dialogID, Sint32 itemID, CBBoolean leftProportional, CBBoolean rightProportional, CBBoolean topProportional, CBBoolean bottomProportional);
		/*
			Sets a control's bindings to be proportional.  Proportional bindings maintain a distance that is a
			ratio of the initial position to the width (or height, as appropriate) of the parent.

			To change a control's bindings to be fixed, use SetEdgeBinding.
		*/

	extern "C" bool GS_CALLBACK GS_SetRightItem(CallBackPtr, Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, short indent = 0, short lineSpacing = 0);
		/*
			Used to place a item to the right of the srcItem. Indent shifts the rightItem horizontally and
			lineSpacing shifts the rightItem vertically.
		*/

	extern "C" void GS_CALLBACK GS_SetSelectionRange(CallBackPtr, Sint32 dialogID, Sint32 controlID, Sint32 startPos, Sint32 endPos);
		/*
			Sets the range of the current selection for the specified control.
		*/

	extern "C" void GS_CALLBACK GS_SetTextEditable(CallBackPtr, Sint32 dialogID, Sint32 itemID, Boolean editable);
		/*
			Sets the editable state of a text field or of the text field contained by an object (if there is
			just one)
		*/

	extern "C" Boolean GS_CALLBACK GS_SetThreeStateCheckBoxState(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Sint32 iState);


	extern "C" Boolean GS_CALLBACK GS_SetTreeControlItemData(CallBackPtr, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, Sint32 nItemData);
		/*
			Sets the user data of the specified item from a tree control.
		*/

	extern "C" Boolean GS_CALLBACK GS_ShowEnhancedPullDownMenuGroupIcon(CallBackPtr, Sint32 liDialogID, Sint32 liComponentID, Boolean bShowGroupIcon);
		/*
			Determines if the group icon should be shown in the specified enhanced pull down menu.
		*/

	extern "C" void GS_CALLBACK GS_ShowItem(CallBackPtr, Sint32 dialogID, Sint32 itemID, Boolean bShow);
		/*
			Show or hide a layout manager item. 

			This call should only be used inside of an event handler callback function.
		*/

	extern "C" void GS_CALLBACK GS_UpdateCustomControlScrollArea(CallBackPtr, Sint32 dialogID, Sint32 component, Sint32 width, Sint32 height, Sint32 leftStart, Sint32 topStart, Sint32 stepSize, bool liveUpdate, bool alwaysShowHoriz = false, bool alwaysShowVert = false );
		/*
			Updates the definition of the scrollbars on a custom control.
		*/


	extern "C" bool GS_CALLBACK GS_VerifyLayout(CallBackPtr, Sint32 dialogID);
		/*
			verifies that all items were created.
		*/



///////////////////////////////////////////
//  Document
///////////////////////////////////////////


	extern "C" InternalIndex GS_CALLBACK GS_AddClass(CallBackPtr, const InternalName& className);
		/*
			Adds a new class with the name specified and returns its classID index.  If a class of that name
			already exists, the function does nothing and returns the existing class index.
		*/


	extern "C" InternalIndex GS_CALLBACK GS_AddGuidesClass(CallBackPtr);
		/*
			Returns the ID of the Guides class, first creating it and setting its attributes if it doesn't
			already exist. Note that the name of the Guides class is localized and won't always be 'Guides'.
		*/

	extern "C" void GS_CALLBACK GS_ColorIndexToName(CallBackPtr, const ColorRef& inColorRef, TXString& outColorName);
		/*
			Returns the name of the color referenced by inColorRef.
		*/

	extern "C" void GS_CALLBACK GS_ColorIndexToRGB(CallBackPtr, ColorRef colorIndex, RGBColor& rgb);
		/*
			Converts a color index from the current document to its component RGB values.
		*/

	extern "C" Boolean GS_CALLBACK GS_CopySymbol(CallBackPtr, const TXString& inFilePath, const InternalName& symName);
		/*
			Copies the specified symbol from the specified document into the active document. File path is
			relative to the application folder and should use colon directory separators.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateGradient(CallBackPtr, const InternalName& name);
		/*
			Creates a new gradient resource.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateHatch(CallBackPtr, const InternalName& inName, CBBoolean inUsePageUnits, CBBoolean inRotateInWalls, CBBoolean inRotateInSymbols, CBBoolean inTransparent,  ColorRef inFillColorIndex);
		/*
			Creates a hatch definition with the given name, appending a nubmer if the name already exists. The
			hatch has one level (line), which can be changed with GS_SetHatchLevel(0, ...). Additional levels
			can be created with GS_SetHatchLevel(n, ...) where n is one more than the existing number of levels
			(which you can get with GS_GetObjectVariable(...ovHatchNumLevels...)). See MiniCadCallBacks.h for
			other hatch object variable selectors.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateImageFromPaint(CallBackPtr, MCObjectHandle paint, const InternalName& imageName);
		/*
			Creates an image resource from a paint node.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreatePaintFromImage(CallBackPtr, MCObjectHandle image);
		/*
			Creates a paint node from an image resource.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateWallStyle(CallBackPtr, const InternalName& wallStyleName);
		/*
			Creates a Wall Style of the given name.  If the given name is in use, the next available name will
			be used.
		*/

	extern "C" void GS_CALLBACK GS_DeleteClass(CallBackPtr, const InternalName& className);
		/*
			Deletes the class specified or does nothing if the class does not exist.  Objects that belong to
			that class are assigned to the None class.
		*/


	extern "C" void GS_CALLBACK GS_DeselectAll(CallBackPtr);
		/*
			Deselects all currently editable objects.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetActiveSymbolDef(CallBackPtr);
		/*
			Returns a handle to the currently selected symbol definition, if one has been selected.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetClassVisibility(CallBackPtr, InternalIndex index);
		/*
			Returns the visibility of the class with the specified index.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetCurrentLayer(CallBackPtr);
		/*
			Returns a handle to the current list group.  If you are not entered into a group, it is the active
			layer, otherwise it is a handle to the object that you have entered.
		*/

	extern "C" short GS_CALLBACK GS_GetCurrentView(CallBackPtr);
		/*
			Gets the current selected view index
		*/


	extern "C" InternalIndex GS_CALLBACK GS_GetDimensionClassID(CallBackPtr);
		/*
			Returns the Internal Index for the Dimension class in the active document.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetGradientData(CallBackPtr, MCObjectHandle gradient, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color);
		/*
			Gets the spot position, midpoint position and color of the specified gradient segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetGradientMidpointPosition(CallBackPtr, MCObjectHandle gradient, short segmentIndex, double& position);
		/*
			Gets the midpoint position of the specified gradient segment.
		*/

	extern "C" void GS_CALLBACK GS_GetGradientSpotColor(CallBackPtr, MCObjectHandle gradient, short segmentIndex, WorldPt3& color);
		/*
			Gets the spot color of the specified gradient segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetGradientSpotPosition(CallBackPtr, MCObjectHandle gradient, short segmentIndex, double& position);
		/*
			Gets the spot position of the specified gradient segment.
		*/

	extern "C" void GS_CALLBACK GS_GetGridUnits(CallBackPtr, WorldCoord& x, WorldCoord& y);
		/*
			Returns the current document's x and y pen grid setting.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetHatchLevel(CallBackPtr, MCObjectHandle inHatchDef, short inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight);
		/*
			Gets the indicated level of the hatch definition to the parameters specified: startPt and repeatVec
			define a line, dashFactor indicates what fraction of the line is drawn (0.0 to 1.0), offsetVec is an
			offset from startPt to the next parallel line. The index starts at 0. The number of hatch levels is
			found with GS_GetObjectVariable(...ovHatchNumLevels...).
		*/

	extern "C" void GS_CALLBACK GS_GetLayerScaleN(CallBackPtr, MCObjectHandle h, double_gs& scale);
		/*
			If h is a handle to a layer, scale is set to its scale; otherwise scale is set to 0.0.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetNamedLayer(CallBackPtr, const InternalName& layerName);
		/*
			Return a handle to the layer specified by the layerName argument.   
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetNoneClassID(CallBackPtr);
		/*
			This returns the InternalIndex for the None class in the active document.
		*/


	extern "C" short GS_CALLBACK GS_GetNumGradientSegments(CallBackPtr, MCObjectHandle gradient);
		/*
			Gets the number of segments in the gradient. Note: a gradient must always have at least 2 segments.
		*/

	extern "C" void GS_CALLBACK GS_GetPageBounds(CallBackPtr, WorldRect& bounds);
		/*
			Sets bounds to the smallest rectangle surrounding all of the pages.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetPatternBits(CallBackPtr, short inIndex, CBUnsignedByte outPattern[8]);
		/*
			Returns the document's bitmap pattern for the given index. inIndex must be in the range 1 to 71.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetSheetLayerUserOrigin(CallBackPtr, MCObjectHandle layerHandle, WorldPt& origin);
		/*
			Gets the user origin of the specified sheet layer.
		*/

	extern "C" void GS_CALLBACK GS_GetUnits(CallBackPtr, UnitsType& currentUnits);
		/*
			Returns the current drawing units in a UnitsType structure.
		*/

	extern "C" void GS_CALLBACK GS_GetUserOrigin(CallBackPtr, WorldPt& origin);
		/*
			Gets the current origin of the drawing as an offset from the center of the page. Obsolete - Use
			GetUserOriginFP.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetUserOriginFP(CallBackPtr, WorldPt& outOrigin);
		/*
			Gets the current origin of the drawing as an offset from the center of the page. Returns a floating
			point value. If the origin could not be gotten, outOrigin is set to (0,0)  and false is returned.
		*/

	extern "C" short GS_CALLBACK GS_InsertGradientSegment(CallBackPtr, MCObjectHandle gradient, double_param spotPosition, double_param midpointPosition, const WorldPt3& color);
		/*
			Inserts a new segment into the gradient and initializes its data to the specified values.
		*/

	extern "C" void GS_CALLBACK GS_MarkCurrentDocChanged(CallBackPtr);
		/*
			Mark the current document as having been changed.  This will enable the save command and prompt the
			user to save if the document is closed before saving.
		*/

	extern "C" Sint32 GS_CALLBACK GS_NumSelectedObjects(CallBackPtr);
		/*
			Returns the number of currently selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveGradientSegment(CallBackPtr, MCObjectHandle gradient, short segmentIndex);
		/*
			Removes the specified segment from the specified gradient.
		*/

	extern "C" void GS_CALLBACK GS_ResetAllObjectsVisibility(CallBackPtr);
		/*
			Resets the visibility of all drawing objects.
		*/

	extern "C" void GS_CALLBACK GS_RGBToColorIndex(CallBackPtr, const RGBColor& rgb, ColorRef& colorIndex);
		/*
			Converts an RGB color to the closest matching color in the MiniCad color palette.
		*/

	extern "C" void GS_CALLBACK GS_SelectAll(CallBackPtr);
		/*
			Selects all currently editable objects.
		*/

	extern "C" void GS_CALLBACK GS_SetActiveSymbolDef(CallBackPtr, MCObjectHandle aSymDef);
		/*
			Sets the current symbol to the symbol definition passed.
		*/

	extern "C" void GS_CALLBACK GS_SetClassVisibility(CallBackPtr, InternalIndex index, Boolean visible);
		/*
			Sets the visibility of the class with the specified index.  Does not reset the drawing visiblity
			automatically, ResetAllObjectsVis should be called whenever class visibility is changed.
		*/

	extern "C" void GS_CALLBACK GS_SetCurrentLayer(CallBackPtr, MCObjectHandle theLayer);
		/*
			Sets the active layer of the document to theLayer.
		*/


	extern "C" Boolean GS_CALLBACK GS_SetGradientData(CallBackPtr, MCObjectHandle gradient, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color);
		/*
			Sets the spot position, midpoint position and color of the specified gradient segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetGradientMidpointPosition(CallBackPtr, MCObjectHandle gradient, short segmentIndex, double_param position);
		/*
			Sets the midpoint position of the specified gradient segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetGradientSpotColor(CallBackPtr, MCObjectHandle gradient, short segmentIndex, const WorldPt3& color);
		/*
			Sets the spot color of the specified gradient segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetGradientSpotPosition(CallBackPtr, MCObjectHandle gradient, short& segmentIndex, double_param position);
		/*
			Sets the spot position of the specified gradient segment.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetHatchLevel(CallBackPtr, MCObjectHandle inHatchDef, short inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, double_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, short inMilsLineWeight);
		/*
			Sets the indicated level of the hatch definition to the parameters specified: startPt and repeatVec
			define a line, dashFactor indicates what fraction of the line is drawn (0.0 to 1.0), offsetVec is an
			offset from startPt to the next parallel line. If the indicated level doesn't exist but level-1 does
			exist, then the level is created, else if the level exists it is modified, else the function returns
			false. The index starts at 0. 
		*/

	extern "C" void GS_CALLBACK GS_SetLayerScaleN(CallBackPtr, MCObjectHandle theLayer, double_param newScale);
		/*
			Sets theLayer's scale to new scale.
		*/

	extern "C" void GS_CALLBACK GS_SetMarker(CallBackPtr, MCObjectHandle obj, MarkerType style, short size, short angle, Boolean start, Boolean end);
		/*
			Sets the markers of a segment or arc.  This function supercedes SetArrowHeads.  The size parameter
			is the number of 1/16384 ths of an inch that you desire the marker to be.  For a one inch marker
			pass in a size value equal to 16384. If you pass NIL for the obj parameter, this call will set the
			marker defaults for this document.  The angle parameter must be in range 0 to 90 degrees.
		*/

	extern "C" void GS_CALLBACK GS_SetProjection(CallBackPtr, MCObjectHandle theLayer, short newProj, Boolean confirmWithUser, Boolean doProgress);
		/*
			Changes the projection of the specified layer to newProj.  If confirmWithUser is true, then the user
			will be asked if they want to continue if a Sint32 re-render is invoked as a result of the projection
			change. Otherwise, the re-render will proceed without a dialog.  When doProgress is set, any
			re-rendering necessary displays the normal series of rendering progress indicators in the mode bar.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetRenderMode(CallBackPtr, MCObjectHandle theLayer, short newRenderMode, Boolean immediate, Boolean doProgress);
		/*
			This sets the render mode of the specified layer and takes care of regenerating the rendering. If
			immediate is true, then all rendering will take place before the call returns. Otherwise, any
			rendering that can take place in the background will be postponed until program execution re-enters
			the main event loop. doProgress controls whether progress information is displayed during the
			operation.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetSheetLayerUserOrigin(CallBackPtr, MCObjectHandle layerHandle, const WorldPt& origin);
		/*
			Sets the user origin of the specified sheet layer.
		*/

	extern "C" void GS_CALLBACK GS_SetUserOrigin(CallBackPtr, const WorldPt& origin);
		/*
			Sets the current origin of the drawing as an offset from the center of the page. Obsolete - Use
			SetUserOriginFP.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetUserOriginFP(CallBackPtr, const WorldPt& inOrigin);
		/*
			Sets the current origin of the drawing as an offset from the center of the page. Uses Floating point
			parameter. If the origin could not be set as specified, false is returned and the origin is set to
			(0,0).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ShowCreateImageDialog(CallBackPtr);
		/*
			Displays a dialog that allows the user to select an image file from which a new image resource is
			created.
		*/

	extern "C" Boolean GS_CALLBACK GS_ShowGradientEditorDialog(CallBackPtr, MCObjectHandle& gradient);
		/*
			Displays the gradient editor dialog for the specified gradient. If a handle variable that is
			initialized to 'NULL' is passed to the function, a new default gradient resource should be created
			and displayed in the editor dialog.
		*/

	extern "C" Boolean GS_CALLBACK GS_ValidClass(CallBackPtr, InternalIndex classID);
		/*
			Returns true if the classID is currently valid in the document.
		*/



///////////////////////////////////////////
//  Files and Directories
///////////////////////////////////////////


	extern "C" TTesselator GS_CALLBACK GS_CreateTessellator(CallBackPtr, short convertRes3D);
		/*
			Creates a tessellator object for use in exporting 3DS.  Pass 'convertRes3D' = -1 if you want to use
			document's 3D conversion res.
		*/

	extern "C" void GS_CALLBACK GS_DeleteTessellator(CallBackPtr, TTesselator pTess);
		/*
			Deletes a tessellator created with GS_CreateTessellator.
		*/

	extern "C" Boolean GS_CALLBACK GS_EncryptVSPluginFilePath(CallBackPtr, const TXString & inFullPath, Boolean doObfuscation = true, const TXString & testOutputFolder = "");
		/*
			Encrypt the specified VectorScript Plug-in file.  For use by a batch-encryption plug-in. 
		*/

	extern "C" Boolean GS_CALLBACK GS_FindFileInPluginFolderN(CallBackPtr, const TXString& fileName, TXString& outFullPath);
		/*
			Searches for a file in all plug-in folders.  fileName is the name of the file to search; if fileName
			has no file extension, it is assumed to be the base name of a plug-in, and the function will search
			for files with that base name and extensions of 'vsm', 'vst', 'vso', 'vlb', 'dll', 'sdo', and 'qtr'. 
			The path of the file is returned in outFilePath.  The function returns true if the file is found,
			false otherwise.
		*/

#if 0
	extern "C" CBBoolean GS_CALLBACK GS_FindFilePathInPluginFolder(CallBackPtr, char fileName[260], char filePath[260]);
		/*
			Searches for a file in all plug-in folders.  fileName is the name of the file to search; if fileName
			has no file extension, it is assumed to be the base name of a plug-in, and the function will search
			for files with that base name and extensions of 'vsm', 'vst', 'vso', 'vlb', 'dll', 'sdo', and 'qtr'. 
			The path of the file is returned in filePath.  The function returns true if the file is found, false
			otherwise.
			NOTE: This function is obsolete.  Use FindFileInPluginFolderN instead.
		*/
#endif

	extern "C" EForEachFileResult GS_CALLBACK GS_ForEachFileInStandardFolder(CallBackPtr cbp, GS_ForEachFilePathProcPtr processFile, Sint32 folderSpec, void* env);
		/*
			For each file in the folder class, calls a given function 'processFile'.  The files are given in
			alphabetical order, regardless of their physical location on the filesystem.  If a file with the
			same name occurs more than once in the search path, only the first occurrence will be returned. 
			Each file passed into the callback is guaranteed to exist at that moment, so its existence may not
			need to be rechecked.

			The interface for this function is designed to closely match ForEachFileInFolder.

			'folderSpec' is one of the folder constants defined in FolderSpecifiers.h
		*/

#if 0
	extern "C" GSError GS_CALLBACK GS_ForEachFilePathInFolder(CallBackPtr cbp, GS_ForEachFilePathProcPtr processFile, char* inStartDirectory, Boolean doRecursive, void* env);
		/*
			Calls processFile for each file in inStartDirectory. It passes the path, file name, & file extension
			to that routine. If doRecursive is set, then each file in subfolders is also passed. NOTE: this
			routine only passes files, It does not pass folder names regardless of the setting of doRecursive.
			NOTE: This function is being obsoleted.  Use ForEachFilePathInFolderN instead.
		*/
#endif

	extern "C" EForEachFileResult GS_CALLBACK GS_ForEachFilePathInFolderN(CallBackPtr cbp, GS_ForEachFilePathNProcPtr processFile, const TXString& inStartDirectory, Boolean doRecursive, void* env);
		/*
			Calls processFile for each file in inStartDirectory. It passes the path, file name, & file extension
			to that routine. If doRecursive is set, then each file in subfolders is also passed. NOTE: this
			routine only passes files, It does not pass folder names regardless of the setting of doRecursive.
			ForEachFilePathInFolderN replaces ForEachFileInFolder. It differs only in return type (of this
			function and of the proc ptr), which is now  the enum EForEachFileResult, defined in
			MiniCadCallBacks.h.
		*/

	extern "C" EForEachFileResult GS_CALLBACK GS_ForEachFilePathInPluginFolder(CallBackPtr cbp, GS_ForEachFilePathNProcPtr processFile, void* env);
		/*
			Calls processFile for each file in every plug-in directory. It passes the path, file name, & file
			extension to that routine.  NOTE: this routine only passes files; it does not pass folder names.
		*/

	extern "C" EForEachFileResult GS_CALLBACK GS_ForEachFilePathInStandardFolder(CallBackPtr cbp, GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env);
		/*
			For each file in the folder class, calls a given function 'processFile'.  The files are given in
			alphabetical order, regardless of their physical location on the filesystem.  If a file with the
			same name occurs more than once in the search path, only the first occurrence will be returned. 
			Each file passed into the callback is guaranteed to exist at that moment, so its existence may not
			need to be rechecked.

			The interface for this function is designed to closely match ForEachFileInFolder.

			'folderSpec' is one of the folder constants defined in FolderSpecifiers.h
		*/

	extern "C" Boolean GS_CALLBACK GS_GetActiveDocumentN(CallBackPtr, TXString& activeDocumentPath, Boolean& saved);
		/*
			Returns the path of the active VectorWorks document. The return value is false if there is no open
			document. The saved parameter indicates whether the document has been saved to disk. If it has not,
			then activeDocumentPath is only a file name.
		*/

#if 0
	extern "C" Boolean GS_CALLBACK GS_GetActiveDocumentPath(CallBackPtr, char activeDocumentPath[255], Boolean& saved);
		/*
			Returns the full path of the active MiniCAD document. The return value is false if there is no open
			document. The saved parameter indicates whether the document has been saved to disk. If it has not,
			then activeDocumentPath will contain the name of the file, but no path information.
			NOTE: This function is being obsoleted.  Use GetActiveDocumentN instead.
		*/
#endif


	extern "C" Boolean GS_CALLBACK GS_GetFilePathInStandardFolder(CallBackPtr, Sint32 folderClass, const TXString& fileName, TXString& outFilePath, Boolean& exists);
		/*
			Gets the first file in the search path with the given name.  If the file is not found, the path will
			be under the User Data folder, ready to be created.
			folderClass: One of the folderSpecifier constants defined in FolderSpecifiers.h
			fileName: the name of the file to search for.
			outFilePath: The path of the file that was found.
			NOTE: This function is obsolete.  Use GetFilePathInStandardFolderN instead.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFilePathInStandardFolderN(CallBackPtr, Sint32 folderClass, const TXString& fileName, TXString& outFilePath, Boolean& exists);
		/*
			Gets the first file in the search path with the given name.  If the file is not found, the path will
			be under the User Data folder, ready to be created.
			folderClass: One of the folderSpecifier constants defined in FolderSpecifiers.h
			fileName: the name of the file to search for.
			outFilePath: The path of the file that was found.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFilePathInUserRoot(CallBackPtr, FolderSpecifier folderClass, const TXString& fileName, TXString& outFilePath);
		/*
			Get the filename in the given folder class under the User Data root.  This function is useful for
			obtaining the paths of files to save out to.
			folderClass: One of the folder type constants defined in FolderSpecifiers.h
			fileName: The name of the file
			outFilePath: The path to the file under the User Data root.
			NOTE: This function is obsolete.  Use GetFilePathInUserRootN instead.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetFilePathInUserRootN(CallBackPtr, FolderSpecifier folderClass, const TXString& fileName, TXString& outFilePath);
		/*
			Get the filename in the given folder class under the User Data root.  This function is useful for
			obtaining the paths of files to save out to.
			folderClass: One of the folder type constants defined in FolderSpecifiers.h
			fileName: The name of the file
			outFilePath: The path to the file under the User Data root.
		*/


	extern "C" Boolean GS_CALLBACK GS_GetFolderN(CallBackPtr, FolderSpecifier inWhichFolder, TXString& outPath, Boolean inCreateIfMissing = false);
		/*
			Returns the full path of the folder requested by inWhichFolder. outPath must be a pointer to a
			buffer of at least 1024 characters. If the requested folder does not exist and inCreateIfMissing is
			true, then it will be created. Otherwise, it returns false if the folder does not exist.
		*/

#if _WINDOWS
	extern "C" GSError GS_CALLBACK GS_GetFolderPath(CallBackPtr, FolderSpecifier inWhichFolder, TXString& outPath, Boolean inCreateIfMissing = false);
		/*
			Returns the full path of the folder requested by whichFolder. outPath must be a pointer to a buffer
			of at least 255 characters. If the requested folder does not exist and inCreateIfMissing is true,
			then it will be created. Otherwise, it returns dirNotFoundErr if the folder does not exist.
			NOTE: This function is being obsoleted.  Use GetFolderN instead.
		*/
#endif

	extern "C" Boolean GS_CALLBACK GS_GetNamedSubFolderN(CallBackPtr, const TXString& parentPath, const TXString& partialPath, TXString& outFolderPath);
		/*
			Given a parent volume reference, directory ID, & partial pathname, GetNamedSubFolder returns the
			"Hard" volume reference & directory ID of the specified folder. It accepts the standard dirID of 2
			for the root directory of a volume.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetNumFilesInStandardFolder(CallBackPtr, FolderSpecifier folderClass, Uint32& numFiles);
		/*
			Returns the number of unique files in the given folder class.
		*/

	extern "C" short GS_CALLBACK GS_ImportDXF(CallBackPtr, const TXString& inFilePath);
		/*
			The DXF or DWG file specified by the path inFilePath is imported into the currently active document.
			No dialogs come up except for the progress dialog, which allows the user to cancel.
			GetProgramVariable() and SetProgramVariable() can be used to control the settings that would
			normally be set in the import dialog or to get info about the import after it has completed.
			GS_SetDXFColorToLineWeight() and GS_GetDXFColorToLineWeight() can be used to set and view the
			current color to lineweight mapping for import.
		*/

#if 0
	extern "C" short GS_CALLBACK GS_ImportDXFWin(CallBackPtr, const TXString& inFile, Sint32& outOpenDWGError, DWORD& outWinError);
		/*
			The DXF or DWG file specified by the path inFile is imported into the currently active document. No
			dialogs come up except for the progress dialog, which allows the user to cancel.
			GetProgramVariable() and SetProgramVariable() can be used to control the settings that would
			normally be set in the import dialog or to get info about the import after it has completed.
			GS_SetDXFColorToLineWeight() and GS_GetDXFColorToLineWeight() can be used to set and view the
			current color to lineweight mapping for import.  The equivalent Macintosh call is GS_ImportDXFMac().
			See the definition of enum EDXFError for an explanation of the returned error codes.
			NOTE: This function is being obsoleted.  Use ImportDXF instead.
		*/
#endif

	extern "C" Boolean GS_CALLBACK GS_IsInStandardFolder(CallBackPtr, FolderSpecifier folderClass, const TXString& filePath, TXString& outFolderPath);
		/*
			Returns true if the given file path is under the given standard folder class.   'outFolderPath' will
			be set to the standard folder that the file is under if successful.
			folderClass is one of the folder constants in FolderSpecifiers.h
			NOTE: This function is obsolete.  Use IsInStandardFolderN instead.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsInStandardFolderN(CallBackPtr, FolderSpecifier folderClass, const TXString& filePath, TXString& outFolderPath);
		/*
			Returns true if the given file path is under the given standard folder class.   'outFolderPath' will
			be set to the standard folder that the file is under if successful.
			folderClass is one of the folder constants in FolderSpecifiers.h
		*/

	extern "C" CBBoolean GS_CALLBACK GS_OpenDocumentPath(CallBackPtr, const TXString& inPath, CBBoolean inShowErrorMessages);
		/*
			Opens the document specified by inPath. Set inShowErrorMessages to false if you want to make sure no
			dialogs come up.
		*/

	extern "C" Boolean GS_CALLBACK GS_ReadVSExternalFilePath(CallBackPtr, const TXString& inFilePath, TMPExternalDataForWorkspace& outData);
		/*
			Private callback for use by Diehl Graphsoft's Workspace external only.
			Given a full pathname, this callback will open the file and determine if it is a MiniPascal External
			file.  If so, it will read in a portion of its contents and return the data in the argument outData.

		*/

	extern "C" GSError GS_CALLBACK GS_SaveActiveDocumentPath(CallBackPtr, const TXString& activeDocumentPath);
		/*
			Saves the active document to the specified file without presenting any dialogs to the user (other
			than possible error alerts). You can save over  the currently active document by passing in its
			path, but otherwise this call will not overwrite existing disk documents.
		*/

	extern "C" bool GS_CALLBACK GS_TesselateObject(CallBackPtr, TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv);
		/*
			Tessellates over an object.  Requires a Tessellator object created with GS_CreateTessellator.
		*/

	extern "C" bool GS_CALLBACK GS_WriteMaterialImageFile(CallBackPtr, const TXString& szFullPathName, MCObjectHandle hMaterial, Sint32 type);
		/*
			Writes a material containing an image into an image file.  'type' should be 'JPEG' or 'PNGf'. 
			Returns true if the call was successful.
		*/



///////////////////////////////////////////
//  Image Manipulation
///////////////////////////////////////////


	extern "C" Boolean GS_CALLBACK GS_UpdateThumbnailPreview(CallBackPtr, InternalIndex inIndex);
		/*
			For a given VectorWorks resource (i.e. Hatch, Texture, Symbol/PIO, etc...), this function will
			update it's thumbnail preview. If there does not exist a preview for this resource, one will be
			created for it. 

			This function returns true if the operation was successful, false otherwise.
		*/

#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" HBITMAP GS_CALLBACK GS_CreateDIBFromPaintNode(CallBackPtr, MCObjectHandle h);
		/*
			Creates a new Windows device-independent bitmap (DIB) and initializes its attributes and bit values
			using the paint node object passed in.  IMPORTANT: This bitmap should be deallocated only by calling
			the SDK function GS_DisposeDIB.
		*/
#endif

#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" HBITMAP GS_CALLBACK GS_CreateDIBFromPreview(CallBackPtr, InternalIndex &inIndex, short pixelWidth, short pixelHeight);
		/*
			Creates a new Windows device-independent bitmap (DIB) and inserts a copy of a preview image from a
			VectorWorks Resource  (i.e. Hatch, Texture, Symbol/PIO, etc...).  IMPORTANT: This bitmap should be
			deallocated only by calling the SDK function GS_DIsposeDIB.
		*/
#endif

#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" MCObjectHandle GS_CALLBACK GS_CreatePaintNodeFromDIB(CallBackPtr, HBITMAP hBitmap);
		/*
			Creates a handle to a paint node object and initializes the object's attributes and bit values using
			the device independent bitmap (DIB) provided.  This DIB should be a Windows HBITMAP created by a
			call to the Win32 function CreateDIBSection.
		*/
#endif

#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" void GS_CALLBACK GS_DisposeDIB(CallBackPtr, HBITMAP hBitmap);
		/*
			Deallocates a device-independent bitmap created by the SDK function GS_CreateDIBFromPaintNode.  This
			call should be used instead of the conventional Win32 function DeleteObject.
		*/
#endif


#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	extern "C" BitMapPtr GS_CALLBACK GS_GetBitmapPtr(CallBackPtr, MCObjectHandle h);
		/*
			Given a handle to a bitmap object, returns a pointer to the actual bitmap stored inside.  You are
			free to alter the bits in any way, but do not change the rowBytes or bounds fields of the bitmap. 
			Changing the baseAddr field will have no effect.  WARNING: Because this routine returns a pointer to
			a piece of a relocatable block, you must lock h before using GetBitmapPtr.  In other words, your
			code should look something like this:

			gVWMM->HLock(h);
			myBitmapPtr = GetBitmapPtr(h);
			   do stuff here...   
			gVWMM->HUnlock(h);
		*/
#endif



///////////////////////////////////////////
//  Internal use
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_CloseXCode(CallBackPtr, Sint32 extCodeInfoID);
		/*
			Closes an external code resource file. This should not be in MiniCadCallBacks. It is strictly for
			internal use.
		*/

	extern "C" GenericFunctionPtr GS_CALLBACK GS_OpenXCode(CallBackPtr, Sint32 extCodeInfoID, Boolean needsResourceFileOpen);
		/*
			Opens an external code resource file. This should not be in MiniCadCallBacks. It is strictly for
			internal use.
		*/



///////////////////////////////////////////
//  Memory Allocation
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_DisposeHandle(CallBackPtr, GSHandle handle);
		/*
			Disposes of all memory associated with "handle".
		*/

	extern "C" void GS_CALLBACK GS_DisposePtr(CallBackPtr, void* p);
		/*
			Disposes pointer p. VWMM::DisposePtr must only be used to dispose pointers allocated by the NewPtr SDK
			call.
		*/

	extern "C" void GS_CALLBACK GS_GetHandleSize(CallBackPtr, GSHandle handle, size_t& size);
		/*
			Retrieves the size in bytes of the data area of "handle".
		*/

	extern "C" void GS_CALLBACK GS_GetHandleState(CallBackPtr, GSHandle handle, Boolean& isLocked);
		/*
			Retrieves the lock state of the handle.
		*/

	/* *** Implemented as a library call *** */
	void GS_LIBRARY GS_HLock(CallBackPtr, GSHandle handle);
		/*
			Locks "handle". The effect of locking and unlocking a GSHandle is identical to locking and unlocking
			a Mac Handle. Specifically, you can reduce, but not increase the size of a locked handle, and the
			data of an unlocked handle may be moved as a result of memory allocation calls. Handles are always
			created in an unlocked state.
		*/

	/* *** Implemented as a library call *** */
	void GS_LIBRARY GS_HUnlock(CallBackPtr, GSHandle handle);
		/*
			Unlocks "handle".
		*/

	extern "C" GSHandle GS_CALLBACK GS_NewHandle(CallBackPtr, size_t size);
		/*
			Allocates a memory handle of the requested size or returns nil if the request cannot be fulfilled.
			GSHandle data structures are double-dereferenced like Macintosh Handle data structures to access
			their data. GSHandle will always be allocated like MiniCAD list objects, but should not be assumed
			to be implemented as a Macintosh Handle.
		*/

	extern "C" VoidPtr GS_CALLBACK GS_NewPtr(CallBackPtr, size_t size);
		/*
			Allocates a pointer block of size bytes. Returns NULL if the allocation fails. This is a relatively
			low performace allocator intended for data which must be persistent across calls to the external.
		*/

	extern "C" void GS_CALLBACK GS_ReduceHandleSize(CallBackPtr, GSHandle handle, size_t size);
		/*
			This performs a similar task to VWMM::SetHandleSize except that it is illegal to increase the size of a
			handle with this call and it is impossible for this call to fail, so error checking is not necessary.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetHandleSize(CallBackPtr, GSHandle handle, size_t size);
		/*
			Sets the size of "handle" to "size" bytes. If the size of the handle increases, then the new space
			at the end is filled with random data. If the size decreases, then the data in the handle is
			truncated. If the allocation fails, then the function result is false.
		*/

	extern "C" void GS_CALLBACK GS_SetHandleState(CallBackPtr, GSHandle handle, Boolean isLocked);
		/*
			Sets the handle lock state.
		*/

	extern "C" VoidPtr GS_CALLBACK GS_SetPtrSize(CallBackPtr, void* p, size_t size);
		/*
			Sets the size of pointer p to size and returns the new pointer. If p can be resized without being
			moved, then the result will be the same address as p. If p has be moved to be successfully resized
			then the result is the new address of the pointer and the original address is no longer valid. If
			the resize is not successful, then the result is nil and p is untouched.
		*/



///////////////////////////////////////////
//  Menus
///////////////////////////////////////////


	extern "C" Sint32 GS_CALLBACK GS_AddResourceToList(CallBackPtr, Sint32 listID, MCObjectHandle resource);
		/*
			Adds the indicated resource to the specified resource list, if the resource is of the same type as
			the items already in the list.  Returns the index of the resource in the list or 0.
		*/

	extern "C" Sint32 GS_CALLBACK GS_BuildResourceList(CallBackPtr, short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems);
		/*
			Creates a list of information of all the resources of the specified type in the current document. 
			If the Display Default Content preference is on and folderIndex is not 0, it will also include all
			the resources of the specified type in all the files in the specified folder.  The folderIndex
			indicates a standard VW folder.  subFolderName is the name of a folder in the standard folder, and
			it can also be a partial path.  If subFolderName is empty, it will use the standard folder indicated
			by folderIndex.  It returns an ID for the list and sets the numItems parameter.
		*/

	extern "C" void GS_CALLBACK GS_DeleteResourceFromList(CallBackPtr, Sint32 listID, Sint32 index);
		/*
			Deletes the indicated item from the specified resource list.
		*/

	extern "C" void GS_CALLBACK GS_DisposeResourceList(CallBackPtr, Sint32 listID);
		/*
			Frees memory for the indicated resource list.
		*/

	extern "C" void GS_CALLBACK GS_GetActualNameFromResourceList(CallBackPtr, Sint32 listID, Sint32 index, TXString& name);
		/*
			Returns the actual name of the indicated item in the specified resource list. This call will strip
			off the filename that is appended for resources with the same name from different files. To get the
			display name use GS_GetNameFromResource.
		*/

	extern "C" short GS_CALLBACK GS_GetMyMenuCommandIndex(CallBackPtr);
		/*
			This returns to an executing external menu handler an index representing itself to be used with
			other menu calls.
		*/

	extern "C" void GS_CALLBACK GS_GetNameFromResourceList(CallBackPtr, Sint32 listID, Sint32 index, TXString& name);
		/*
			Returns the display name of the indicated item in the specified resource list which includes the
			appended file name for resources with the same name. To get the actual name use
			GS_GetActualNameFromResourceList.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetResourceFromList(CallBackPtr, Sint32 listID, Sint32 index);
		/*
			Returns the resource from the indicated item in the specified resource list, if that item is in the
			current document.  Otherwise it returns 0.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ImportResourceToCurrentFile(CallBackPtr, Sint32 listID, Sint32 index);
		/*
			This imports the indicated resource in the specified list to the current file, if it is not already
			in the current file.  It returns the resource.
		*/

	extern "C" Boolean GS_CALLBACK GS_RegisterMenuForCallback(CallBackPtr, short menuIndex, OSType whichChange);
		/*
			This registers a menu definition function to receive a callback when the specified internal MiniCad
			condition change takes place. The available condition changes are documented in the developer's kit.
			After the specified condition change takes place, the menu will receive a MenuNotifyMessage::kAction event with the
			specified change identifier in the message1 field.
		*/

	extern "C" Sint32 GS_CALLBACK GS_ResourceListSize(CallBackPtr, Sint32 listID);
		/*
			Returns the number of items in the specified resource list.
		*/

	extern "C" void GS_CALLBACK GS_UnregisterMenuForCallback(CallBackPtr, short menuIndex, OSType whichChange);
		/*
			This unregisters the specified menu so that it will no longer receive notification of the specified
			condition change. If the menu is not in the active overlay, it should not be receiving notification
			of events.
		*/



///////////////////////////////////////////
//  Mode Bar
///////////////////////////////////////////

	extern "C" void GS_CALLBACK GS_Deprecated35L(CallBackPtr, short iconID);
	/*
			Places a pushButton in the modeBar.  PushButtons are used in MiniCad for preferences buttons. 
			Response to Button events when tool definition function  receives the ToolModeMessage::kAction action with
			message1 equal to the GroupNumber of the button.
		*/

	extern "C" void GS_CALLBACK GS_Deprecated36L(CallBackPtr, short initialSetting, short iconID);
	/*
			Adds a check box to the mode bar.  iconID is the resource ID of a ICN#  icon.  initialSetting > 0
			sets the checkbox to true.  Use GetModeValue to find the current value (state) of the check box. 
		*/

	extern "C" void GS_CALLBACK GS_AddPullDownMenuItem(CallBackPtr, short group, const TXString& item);
		/*
			Adds an item to a pull-down menu in the mode bar.

			Parameters:

			group - The group of the pull-down menu
			item - The item to add to the pull-down menu
		*/

	extern "C" void GS_CALLBACK GS_AddPullDownMenuMode(CallBackPtr, const TXString& label);
		/*
			Adds a pull-down menu to the mode bar.

			Parameters:

			label - The text label for the pull-down menu
		*/
	extern "C" void GS_CALLBACK GS_Deprecated37L(CallBackPtr, short initialSetting, short numButtons, short id1, short id2, short id3 = 0, short id4 = 0, short id5 = 0, short id6 = 0);
	/*
			Adds a group of radio buttons to the mode bar.  numButtons is the number of buttons <= 6 and id# is
			the 'ICN#' resource ID of the button's icon.  initialSetting is the number , left to right , of the
			button originally highlighted.
		*/

	extern "C" void GS_CALLBACK GS_AddTxtBtnMode(CallBackPtr, const TXString& theText);
		/*
			Same as AddButtonMode except the button is button with text.
		*/

	extern "C" void GS_CALLBACK GS_EnableMode(CallBackPtr, short modeNum, Boolean enable);
		/*
			Enables or disables the specified mode.  Modes are numbered starting from 1 in the order they were
			added into the mode bar.  Passing enable as false disables the mode; true enables it.
		*/

	extern "C" short GS_CALLBACK GS_GetModeValue(CallBackPtr, short modeNum);
		/*
			Returns the value of the specified mode.  Different mode types return values as follows:
			   radio button:  Returns the number of the currently selected radio button (numbered left to right
			starting at 1.)
			   checkbox: Returns 1 if the checkbox is checked, 0 if it is not.
			   button:  Always returns 0.
		*/

	extern "C" void GS_CALLBACK GS_SetHelpString(CallBackPtr, const TXString& helpMessage);
		/*
			Places helpMessage in the mode bar to the right of any other mode objects.
		*/

	extern "C" void GS_CALLBACK GS_SetModeValue(CallBackPtr, short modeNum, short theValue);
		/*
			Sets the value of the specified mode.  The meaning of theValue depends on the type of the mode, as
			follows:
			   radio button:  theValue is the number of the radio button in the group to set (numbered left to
			right, starting at 1).
			   checkbox:  check the box if theValue is not 0, uncheck it if theValue is 0.
			   button:  SetModeValue has no effect.
		*/

	extern "C" void GS_CALLBACK GS_SetPullDownMenuSelection(CallBackPtr, short group, short selectedItem);
		/*
			Sets the selection for a pull-down menu in the mode bar.

			Parameters:

			group - The group of the pull-down menu
			selectedItem - The zero-based index of the item to select
		*/



///////////////////////////////////////////
//  Name Translation
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_ClassIDToName(CallBackPtr, InternalIndex classID, InternalName& className);
		/*
			Sets className to the name of the class with the specified ID number.  Valid class ID numbers range
			from one up to MaxClassID(), though not necessarily all numbers in that range will be defined
			classes.  If classID does not map to a defined class, class name is set to the empty string.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_ClassNameToID(CallBackPtr, const InternalName& className);
		/*
			Returns the ID number of the class with the specified name, or -1 if there is no class with that
			name.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_InternalIndexToHandle(CallBackPtr, InternalIndex index);
		/*
			Returns the object with the specified internal index.
		*/

	extern "C" void GS_CALLBACK GS_InternalIndexToNameN(CallBackPtr, InternalIndex index, InternalName& name);
		/*
			Translates the specified internal index to its corresponding object name.  This call supersedes
			GS_InternalIndexToName.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_MaxClassID(CallBackPtr);
		/*
			Returns the largest valid class ID number.  The smallest class ID is always the value obtained by
			calling GetNoneClassID, the ID of the class 'None'.
		*/

	extern "C" Boolean GS_CALLBACK GS_NameToInternalIndexN(CallBackPtr, const TXString& name, InternalIndex& index);
		/*
			Translates the specified object name to its corresponding internal index.  This call supersedes
			GS_NameToInternalIndex.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetPolyVertexLoopDirection(CallBackPtr, MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec);
		/*
			Sets the vertex loop direction of ioPolyToSet to be that specified by inPolyDirectionSpec. 
			inPolyDirectionSpec may be one of kPolyDirectionClockwise, kPolyDirectionCounterClockwise. True is
			returned if direction is set.
		*/



///////////////////////////////////////////
//  Object Manipulation
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AddToConstraintModel(CallBackPtr, MCObjectHandle obj);
		/*
			Adds the specified object to the constraint model that is being built, along with its constraints
			and any other objects constrained to this object and their constraints.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddViewportAnnotationObject(CallBackPtr, MCObjectHandle viewportHandle, MCObjectHandle annotationHandle);
		/*
			Adds the specified annotation object to the specified viewport.
		*/

	extern "C" Boolean GS_CALLBACK GS_AppendParameterWidget(CallBackPtr, Sint32 ObjectID, Sint32 parameterID, const TXString& text, Sint32 data);
		/*
			Appends an existing parameter onto the Object Info Palette for an event-enabled plug-in object. 
			ParameterID is the 1-based index of the parameter to add; text is the text that will appear on the
			Object Info Palette for this parameter.  data is unused.
		*/

	extern "C" Boolean GS_CALLBACK GS_AppendWidget(CallBackPtr, Sint32 ObjectID, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data);
		/*
			Appends a widget onto the Object Info Palette for an event-enabled plug-in object.  Possible
			widgetType values are 12 (button), and 13 (static text).  EventID is the data value included in an
			event generated by this widget.  data is unused.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ConvertTo3DPolygons(CallBackPtr, MCObjectHandle h, Boolean preserveOriginal = false);
		/*
			Creates and returns a handle to a new 3D polygon object which is h converted to a group of 3D
			polygons.  By default, the new polygonized object replaces the original, but if preserveOriginal is
			true, the polygonized object is created as the frontmost object in the current layer.  Note that not
			all objects can be converted to a polygon, so the type of the objects returned may not be qPolyNode. 
			In particular, loci, text, bitmaps, picts, and on-drawing worksheets are not converted.
		*/

	extern "C" MCObjectHandle  GS_CALLBACK GS_ConvertToNURBS(CallBackPtr, MCObjectHandle h, Boolean keepOrig = false);
		/*
			This function converts the input object h into a new NURBS object or a group of NURBS objects in the
			document.
			By default, the original object h is deleted.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ConvertToPolygon(CallBackPtr, MCObjectHandle h, Boolean preserveOriginal = false);
		/*
			Creates and returns a handle to a new polygon object which is h converted to a polygon.  By default,
			the new polygonized object replaces the original, but if preserveOriginal is true, the polygonized
			object is created as the frontmost object.  Note that not all objects can be converted to a polygon,
			so the type of the object returned may not be polyNode.  In particular, lines, loci, text, bitmaps,
			picts, and on-drawing worksheets are not converted.  Symbols and groups are converted to groups of
			polygonized objects.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ConvertToPolygonN(CallBackPtr, MCObjectHandle h, Boolean preserveOriginal , short conversionResolution);
		/*
			Like ConvertToPolygon but takes a conversion resolution kLowConvertRes, kMedConvertRes,
			kHighConvertRes,  and kVeryHighConvertRes.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ConvertToPolyline(CallBackPtr, MCObjectHandle h, Boolean preserveOriginal = false);
		/*
			Just like ConvertToPolygon, but makes a polyline object instead.  Polylines yield smoother results
			for curved objects (ellipses, arcs, &c.) but are more difficult to manipulate in certain ways than
			polygons.
		*/

	extern "C" Boolean GS_CALLBACK GS_ConvertToUnstyledWall(CallBackPtr, MCObjectHandle theWall);
		/*
			Converts a wall to be unstyled
		*/

	extern "C" void GS_CALLBACK GS_CreateConstraintModel(CallBackPtr, MCObjectHandle obj, Boolean useSelection);
		/*
			This creates a parametric constraint model.  It should be called efore objects which could have
			parametric constraints have their geometry or location modified.  If all of the selected objects in
			the drawing will be modified, useSelection should be true.  Then all selected objects will be added
			to the model, along with any other objects constrained to them and the involved constraints.  The
			identified object will also be added to the model, along with any objects constrained to it.  If
			only selected objects will be modified, obj should be nil and useSelection true.  Additional objects
			can be added to the model with the AddToConstraintModel function.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateOffsetNurbsObjectHandle(CallBackPtr, MCObjectHandle h,   double offset);
		/*
			This function will return a handle to a NURBS object that is offset from the given NURBS object h by
			the offset distance. 
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomObjectControlPtsCreate(CallBackPtr cbp, MCObjectHandle inOwnerObj, Sint32 numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc,void* env);
		/*
			Creates data storage for Custom Control Points for custom object.  If initProc is non-nil then it
			will be called for each of the controlPt elements. CustomObjects that provide custom Control Points
			must set the kObjXPropCustomCursorResize Property.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomObjectControlPtsRemove(CallBackPtr, MCObjectHandle inOwnerObj);
		/*
			Removes the control points attached to inOwnerObj. CustomObjects that provide custom Control Points
			must set the kObjXPropCustomCursorResize Property.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomObjectControlPtSet(CallBackPtr, MCObjectHandle inOwnerObj,Sint32 dataIndex, const WorldPt3& pt,Boolean is2DOnly,Boolean isHidden,Sint32 inClientID);
		/*
			Sets the specified Control Point properties.  Must follow a succssfull call to
			GS_CustomObjectControlPtsCreate.  dataIndex  is a zero based index specifying the Control Point to
			be set.  False is returned if index  is out of range or if called on an object type other than a
			kParametricNode.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CustomObjectGetSurfaceProxy(CallBackPtr, MCObjectHandle inPathObject);
		/*
			2D path Objects that participate in surface operations like Add, Intersect and clip return a proxy
			object for the path.  The proxy is in NOT in the object's local coordinate space- it is in the same
			space as  inPathObject. To participate, objects must set the kObjXIs2DSurfaceEligable.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomObjectReplacePath(CallBackPtr, MCObjectHandle inPathObject, MCObjectHandle pathPolyline);
		/*
			Inserts pathPolyline as the path of inPathObject by after first translating it to the objects
			coordinate space.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_DeleteAllComponents(CallBackPtr, MCObjectHandle wall);
		/*
			Deletes all components in wall.  wall can be a wall or Wall Style.  If wall is nil, this function
			operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_DeleteComponent(CallBackPtr, MCObjectHandle wall, CBSignedShort index);
		/*
			Deletes the component at index in wall.  wall can be a wall or Wall Style.  If wall is nil, this
			function operates on the Wall Preferences.
		*/

	extern "C" void GS_CALLBACK GS_DeleteConstraint(CallBackPtr, MCObjectHandle obj, MCObjectHandle constraint);
		/*
			The indicated constraint node is deleted from the indicated drawing object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_DuplicateObject(CallBackPtr, MCObjectHandle h);
		/*
			Duplicates an object and places the copy at the same location as the original. The copy is NOT added
			to the list.  NOTE: not all flags of original object is copied such as the LOCK flag
		*/

	extern "C" void GS_CALLBACK GS_EnableParameter(CallBackPtr, MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetEnabled);
		/*
			Sets the user interface enable state of the control for the specified custom object parameter.
		*/

	extern "C" Boolean GS_CALLBACK GS_EvaluateNurbsSurfacePointAndNormal(CallBackPtr, MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point,  WorldPt3& normal);
		/*
			Determines the point and normal on the NURBS surface at the given u,v value
		*/

	extern "C" void GS_CALLBACK GS_ForEachLayer(CallBackPtr cbp, GS_ForEachObjectProcPtr action, void *actionEnv);
		/*
			typedef void (*ForEachLayerProcPtr)(Handle h, CallBackPtr cbp, void *env);

			Calls action on each layer header in the current drawing.
		*/

	extern "C" void GS_CALLBACK GS_ForEachObject(CallBackPtr cbp, short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv);
		/*
			typedef void (*ForEachObjectProcPtr)(Handle h, CallBackPtr cbp, void *env);

			Calls action with env equal to actionEnv and h equal in turn to each object that matches the
			criteria specified by traverseWhat.  TraverseWhat must be equal to exactly one of allSelected (all
			visible, selected objects), allEditable (all visible, unlocked objects on currently editable
			layers), allSelectedAndEditable (all selected and unlocked objects), allDrawing (all objects in the
			drawing on all layers, regardless of visibility, selection, or locked state), allSymbolDefs (all
			symbol definitions), or allObjects (all objects in the drawing and all symbol definitions), plus at
			most one of descendIntoGroups (also process objects inside of qualifying groups) or descendIntoAll
			(also process objects inside of qualifying groups and group-like objects (walls, sweeps, extrudes,
			etc.))
		*/

	extern "C" void GS_CALLBACK GS_Get2DPt(CallBackPtr, MCObjectHandle obj, short index, WorldPt& loc);
		/*
			Returns the coords for the x and y position of the specified vertex of the specified object.  This
			only works for 2D objects.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetBinaryConstraint(CallBackPtr, short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2);
		/*
			Returns a handle to a constraint involving two objects of the specified type on the specified
			vertices of the specified objects.  If the constraint does not exist, it returns 0.
		*/

	extern "C" void GS_CALLBACK GS_GetClosestPt(CallBackPtr, MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj);
		/*
			Returns the vertex index of the object or a subobject closest to the location in index.  Index is
			set to 0 if no vertex is close or to -1 if the type of the object is unsupported.  If the object is
			a wall, and a vertex of a subobject is close to the location, it will set obj to that subobject.  If
			the object is a symbol or PIO, and a vertex of a subobject is close to the location, it will return
			an index into the objects list to indicate which subobject in containedObj.    This only supports 2D
			objects.
		*/

	extern "C" void GS_CALLBACK GS_GetClosestSide(CallBackPtr, MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB);
		/*
			Returns the indices of the vertices of the specified object that define the side of the object that
			is closest to the specified location.  This function only supports 2D objects.  If the object is not
			supported, it will return -1 and -1.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentClass(CallBackPtr, MCObjectHandle wall, CBSignedShort index, Sint32 &componentClass);
		/*
			Gets the class of the component at index in wall.  wall can be a wall or Wall Style.  If wall is
			nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentFill(CallBackPtr, MCObjectHandle wall, CBSignedShort index, Sint32 &fill);
		/*
			Gets the fill style of the component at index in wall.  wall can be a wall or Wall Style.  If wall
			is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentFillColors(CallBackPtr, MCObjectHandle wall, CBSignedShort index, ColorRef &fillForeColor, ColorRef &fillBackColor);
		/*
			Gets the fore and back fill colors of the component at index in wall.  wall can be a wall or Wall
			Style.  If wall is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentName(CallBackPtr, MCObjectHandle wall, CBSignedShort index, InternalName &componentName);
		/*
			Gets the name of the component at index in wall.  wall can be a wall or Wall Style.  If wall is nil,
			this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentPenColors(CallBackPtr, MCObjectHandle wall, CBSignedShort index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor);
		/*
			Gets the fore and back colors of the left and right side pens of the component at index in wall. 
			wall can be a wall or Wall Style.  If wall is nil, this function operates on the Wall Preferences.
		*/


	extern "C" CBBoolean GS_CALLBACK GS_GetComponentPenWeights(CallBackPtr, MCObjectHandle wall, CBSignedShort index, CBUnsignedByte &penWeightLeft, CBUnsignedByte &penWeightRight);
		/*
			Gets the left and right side pen weights of the component at index in wall.  wall can be a wall or
			Wall Style.  If wall is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentUseFillClassAttr(CallBackPtr, MCObjectHandle wall, CBSignedShort index, CBBoolean &useClassAttr);
		/*
			Gets the use fill class attributes flag of the component at index in wall.  wall can be a wall or
			Wall Style.  If wall is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentUsePenClassAttr(CallBackPtr, MCObjectHandle wall, CBSignedShort index, CBBoolean &leftPenUseClassAttr, CBBoolean &rightPenUseClassAttr);
		/*
			Gets the use class attributes flags of the left and right side pens of the component at index in
			wall.  wall can be a wall or Wall Style.  If wall is nil, this function operates on the Wall
			Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetComponentWidth(CallBackPtr, MCObjectHandle wall, CBSignedShort index, WorldCoord &width);
		/*
			Gets the width of the component at index in wall.  wall can be a wall or Wall Style.  If wall is
			nil, this function operates on the Wall Preferences.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetCustomObjectColor(CallBackPtr, MCObjectHandle objectHand, Sint32 iTagID, ColorRef& ioColorRef);
		/*
			Get an auxilary ColorRef stored in'objectHand' previously  with SetCustomObjectColor .  Aplication
			will preserve the color mapped to inTagID accross  document transfer and and during PurgeUnused
			Colors.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetCustomObjectPath(CallBackPtr, MCObjectHandle objectHand);
		/*
			Returns a handle to the path object for a path custom object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetCustomObjectProfileGroup(CallBackPtr, MCObjectHandle objectHand);
		/*
			Returns a handle to the profile group of a path custom object.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDimensionStandardVariable(CallBackPtr, short dimensionIndex, short fieldSelector, TVariableBlock& value);
		/*
			Returns a property of a dimension standard.  The index specifies which dimension to examine. The
			nine built-in dimension standards use indexes 1 thru 9. Custom dimensions use indexes 0 thru -8. The
			selector chooses which property will be returned, and the value contains the actual value of that
			property. This function returns false if an invalid dimension index or field selector is specified.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetDistanceAlongNurbsCurve(CallBackPtr, MCObjectHandle inNurbsCurve, double_param inParameter1, Sint32 inParameter1CurveIndex,  double_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance);
		/*
			Gets distance between a point at parameter1 on the curve piece index1 and another point at
			parameter2 on the curve piece with index2
		*/

	extern "C" Boolean GS_CALLBACK GS_GetLocalizedPluginChoice(CallBackPtr, const InternalName& pluginName, const TXString& parameterName, Sint32 choiceIndex, TXString& localizedChoice);
		/*
			Returns true with outChoice as specified by inPluginName, nParameterName and inChoiceIndex.  Each of
			the input names are universal names.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetLocalizedPluginName(CallBackPtr, const InternalName& pluginName, InternalName& localizedName);
		/*
			Get the localized name of a plug-in given its universal name.  

			When VectorWorks plug-ins are localized by distributors in other countries, their names are
			translated to the appropriate language.  The plug-in file stores both the original universal name
			and this translated localized name.  The translated name is displayed by the VectorWorks user
			interface instead of the original name.  If a script needs to display the name of a plug-in in a
			dialog or message then it should call this function to determine the localized name.  (Note that
			scripts will use the universal name to specify a plug-in when the name is not being displayed to the
			user.) 
		*/

	extern "C" Boolean GS_CALLBACK GS_GetLocalizedPluginParameter(CallBackPtr, const InternalName& pluginName, const TXString& parameterName, TXString& localizedParameterName);
		/*
			Get the localized name of a plug-in parameter given the universal name of plug-in and universal name
			of parameter.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetNumberOfComponents(CallBackPtr, MCObjectHandle wall, short& numComponents);
		/*
			Gets the number of components in wall.  wall can be a wall or Wall Style.  If wall is nil, this
			function operates on the Wall Preferences.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetNurbsObjectDistanceFromPoint(CallBackPtr, MCObjectHandle h, const WorldPt&  point,  double& distance);
		/*
			This function will return the distance from the input point  to the input NURBS Object h.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetObjectProperty(CallBackPtr, MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue);
		/*
			Gets the specified object property.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetObjectPropertyChar(CallBackPtr, MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue);
		/*
			Gets the specified object property.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetObjectVariable(CallBackPtr, MCObjectHandle theObject, short setSelector, TVariableBlock& value);
		/*
			Retrieves the property of an object.  The selector chooses which property will be retrived, and the
			value contains the property value upon return.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetParameterOnNurbsCurve(CallBackPtr, MCObjectHandle h, const WorldPt3&  point,  double& parameter, Sint32& index);
		/*
			Given a NURBS curve handle and a point(in world space), this function returns the parameter of the
			point obtained by projecting the input point. The function also returns the index of the piece in
			the piecewise NURRBS curve on which the projected point lies.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetPointAndParameterOnNurbsCurveAtGivenLength(CallBackPtr, MCObjectHandle inNurbCurve, double_param inPercentOfLength, WorldPt3& outPointOnCurve,  double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex);
		/*
			Gets point, parametric parameter, and curve index of the inNurbCurve provided.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetRoofEdge(CallBackPtr, MCObjectHandle object, short index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight);
		/*
			Get a vertex of the roof.  Vertices define the outline of the roof and its characteristics. 
			Vertices must progress in a counter clock wise direction, when viewed from a top view, otherwise the
			roof cannot be built.

			index: Indexs have values between 1 and NVertices (See GetRoofVertices())
			edgePt: Coordinate point for this edge
			slope: pitch of this roof edge
			projection: eave overhang
			eaveHeight: eave height
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetSingularConstraint(CallBackPtr, short type, MCObjectHandle obj, short vertexA, short vertexB);
		/*
			Returns a handle to a constraint node involving a single object of the indicated type on the
			specified vertices of the specified object.  If the constraint does not exist, it returns 0.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetViewportClassVisibility(CallBackPtr, MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType);
		/*
			Gets the visibility for the specified class in the specified viewport.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetViewportCropObject(CallBackPtr, MCObjectHandle viewportHandle);
		/*
			Gets the specified viewport's crop object, if any.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetViewportGroup(CallBackPtr, MCObjectHandle viewportHandle, short groupType);
		/*
			Gets the specified viewport group.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetViewportGroupParent(CallBackPtr, MCObjectHandle groupHandle);
		/*
			Gets viewport parent of specified viewport group.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetViewportLayerVisibility(CallBackPtr, MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType);
		/*
			Gets the visibility for the specified layer in the specified viewport.
		*/

	extern "C" MeshErrorType GS_CALLBACK GS_GroupToMesh(CallBackPtr, MCObjectHandle theMesh);
		/*
			Converts a group of 3D polygons into a mesh network.  0 is returned if the operation is successful,
			otherwise an error code is returned.
		*/

	extern "C" Boolean GS_CALLBACK GS_HasConstraint(CallBackPtr, MCObjectHandle obj);
		/*
			Returns whether the indicated object has a constraint node.
		*/

	extern "C" Boolean GS_CALLBACK GS_InsertAllParametersAsWidgets(CallBackPtr, Sint32 inObjectID);
		/*
			Inserts all parameters of a plug-in object as widgets on the Object Info Palette.   inObjectID is
			passed to the Object's ParametricInitXPropsMessage::kAction event handler in the message parameter .
		*/


	extern "C" Boolean GS_CALLBACK GS_InsertParameterWidget(CallBackPtr, Sint32 ObjectID, Sint32 position, Sint32 parameterID, const TXString& text, Sint32 data);
		/*
			Inserts an existing parameter into the Object Info Palette for event-enabled plug-in objects. 
			position is the 0-based position for this new parameter (subsequent parameters are shifted down);
			parameterID is the 1-based index of the parameter to insert.
		*/

	extern "C" Boolean GS_CALLBACK GS_InsertWidget(CallBackPtr, Sint32 ObjectID, Sint32 position, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data);
		/*
			Inserts an existing parameter into the Object Info Palette for event-enabled plug-in objects. 
			position is the 0-based position for this new widget.  WidgetType values: 12 (button), 13 (static
			text).  EventID is data included in widget-generated event.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsObjectFromReferencedFile(CallBackPtr, MCObjectHandle h);
		/*
			Returns whether the object came from a subscription and is therefore succeptible to being updated.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsViewportGroupContainedObject(CallBackPtr, MCObjectHandle objectHandle,  short groupType);
		/*
			Determines if specified object is a viewport group-contained object.
		*/

	extern "C" void GS_CALLBACK GS_MakePolyshapeValid(CallBackPtr, MCObjectHandle thePoly);
		/*
			Checks the polyshape for internal consistency, making changes as necessary.  This should be called
			when manipulating polyshapes that have holes.
		*/

	extern "C" MeshErrorType GS_CALLBACK GS_MeshToGroup(CallBackPtr, MCObjectHandle theMesh);
		/*
			Converts a mesh to a group of 3D polygons.  0 is returned if the operation is successful, otherwise
			an error code is returned.
		*/

	extern "C" void GS_CALLBACK GS_MoveObject(CallBackPtr, MCObjectHandle h, WorldCoord dx, WorldCoord dy);
		/*
			Move the object by the offsets specified.
		*/

	extern "C" void GS_CALLBACK GS_MoveObject3D(CallBackPtr, MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz, bool inMoveScreenObjectsWith3D = false);
		/*
			Move the objects in 3D-space by the offsets specified.  The offsets are specified along the world
			axes, unlike the MoveObject call which takes offsets in the screen plane.
		*/

	extern "C" void GS_CALLBACK GS_NotifyLayerChange(CallBackPtr, StatusData liAdditionalData = 0);
		/*
			Sends out a kNotifyLayerChange
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveCustomObjectColor(CallBackPtr, MCObjectHandle objectHand, Sint32 iTagID);
		/*
			Deletes  an auxilary ColorRef stored in'objectHand' previously  with SetCustomObjectColor
		*/

	extern "C" Boolean GS_CALLBACK GS_RemoveRoofEdge(CallBackPtr, MCObjectHandle object, short index);
		/*
			Remove a vertex and associated attributes from a roof object.  Indices are one based.
		*/

	extern "C" void GS_CALLBACK GS_ResetObject(CallBackPtr, MCObjectHandle h);
		/*
			Updates the object for any changes in parameters (e.g. resetting bounding box, rebuilding wall
			groups, etc.)

			Note: as of version 9.0, ResetObect can be used to force the redraw of a worksheet or worksheet
			image. UseSetCallBackInval to turn worksheet and worksheet image updating on and off.
		*/

	extern "C" void GS_CALLBACK GS_RotateObjectN(CallBackPtr, MCObjectHandle& h, const WorldPt& rotCenter, double_param angle);
		/*
			Rotates h about a line parallel to the zaxis that passes through rotCenter through angle degrees
		*/

	extern "C" Boolean GS_CALLBACK GS_ScaleObject3D(CallBackPtr, MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector);
		/*
			Scales Objects that support 3D scaling. False is returned for unsupported object types. Supported
			object types include kNurbsSurfaceNodes.
		*/

	extern "C" void GS_CALLBACK GS_ScaleObjectN(CallBackPtr, MCObjectHandle h, const WorldPt& scaleCen, double_param scaleX, double_param scaleY);
		/*
			Scales 2d objects h just as scale dialog does in minicad.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetBinaryConstraint(CallBackPtr, short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2);
		/*
			Sets a constraint between two objects or two parts of a single object.  Valid values for type are 1
			(coincident), 2 (colinear), 3 (parallel), 6 (tangent), 7 (concentric), 8 (distance), 9 (horizontal
			distance), 10 (vertical distance), 12 (angle) and 13 (perpendicular).  obj1VertexA and obj1VertexB
			indicate which vertices of the first object to use in the constraint, and obj2VertexA and
			obj2VertexB indicate which vertices of the second object to use.  A value of -1 indicates that a
			vertex parameter is not applicable.  The containedObj fields are for an index into the list of a
			container object such as a symbol.  This can be obtained from the GetClosestPt function.  If the
			constraint cannot be set, it returns false.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentClass(CallBackPtr, MCObjectHandle wall, CBSignedShort index, Sint32 componentClass);
		/*
			Sets the class of the component at index in wall.  wall can be a wall or Wall Style.  If wall is
			nil, this function operates on the Wall Preferences.  Does nothing if Architect is not enabled.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentFill(CallBackPtr, MCObjectHandle wall, CBSignedShort index, Sint32 fill);
		/*
			Sets the fill of the component at index in wall.  wall can be a wall or Wall Style.  If wall is nil,
			this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentFillColors(CallBackPtr, MCObjectHandle wall, CBSignedShort index, ColorRef fillForeColor, ColorRef fillBackColor);
		/*
			Sets the fore and back fill colors of the component at index in wall.  wall can be a wall or Wall
			Style.  If wall is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentName(CallBackPtr, MCObjectHandle wall, CBSignedShort index, const InternalName& componentName);
		/*
			Sets the name of the component at index in wall.  wall can be a wall or Wall Style.  If wall is nil,
			this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentPenColors(CallBackPtr, MCObjectHandle wall, CBSignedShort index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor);
		/*
			Sets the fore and back colors of the left and right side pens of the component at index in wall. 
			wall can be a wall or Wall Style.  If wall is nil, this function operates on the Wall Preferences.
		*/


	extern "C" CBBoolean GS_CALLBACK GS_SetComponentPenWeights(CallBackPtr, MCObjectHandle wall, CBSignedShort index, CBUnsignedByte penWeightLeft, CBUnsignedByte penWeightRight);
		/*
			Sets the left and right side pen weights of the component at index in wall.  wall can be a wall or
			Wall Style.  If wall is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentUseFillClassAttr(CallBackPtr, MCObjectHandle wall, CBSignedShort index, CBBoolean useClassAttr);
		/*
			Sets the use fill class attributes flag of the component at index in wall.  wall can be a wall or
			Wall Style.  If wall is nil, this function operates on the Wall Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentUsePenClassAttr(CallBackPtr, MCObjectHandle wall, CBSignedShort index, CBBoolean leftPenUseClassAttr, CBBoolean rightPenUseClassAttr);
		/*
			Sets the use class attributes flags of the left and right side pens of the component at index in
			wall.  wall can be a wall or Wall Style.  If wall is nil, this function operates on the Wall
			Preferences.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetComponentWidth(CallBackPtr, MCObjectHandle wall, CBSignedShort index, WorldCoord width);
		/*
			Sets the width of the component at index in wall.  wall can be a wall or Wall Style.  If wall is
			nil, this function operates on the Wall Preferences.
		*/

	extern "C" void GS_CALLBACK GS_SetConstraintValue(CallBackPtr, MCObjectHandle constraint, double_param value);
		/*
			Sets the indicated dimensional constraint object to the indicated value.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetCustomDimensionStandardVariable(CallBackPtr, short dimensionIndex, short fieldSelector, const TVariableBlock& value);
		/*
			Changes a property of a custom dimension standard.  The index specifies which custom dimension to
			change. The nine built-in dimension standards use indexes 1 thru 9 and cannot be changed with this
			function. Custom dimensions use indexes 0 thru -8, and those are the dimension index values that
			should be used with this function. The selector chooses which property will be changed, and the
			value specifies what that property should be changed to. This function returns false if an invalid
			dimension index or field selector is specified.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetCustomObjectColor(CallBackPtr, MCObjectHandle objectHand, Sint32 iTagID, ColorRef inColorRef);
		/*
			Store/Set an auxilary ColorRef in 'objectHand' so GetCustomObjectColor  can access it later. 
			Application will preserve the color mapped to inTagID accross document transfer and and during
			PurgeUnused Colors.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetCustomObjectControlPointVisibility(CallBackPtr, MCObjectHandle objectHand, short controlPtIndex, Boolean setVisible);
		/*
			Sets the control point of objectHand specified by the one-based index controlPtIndex to the
			visibility specified by setVisible.  The control points are the control points defined  by prameters
			of the objectHand type.  These control points are NOT the same as the custom contol points provided
			by  CustomObjectControlPtsCreate.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetCustomObjectPath(CallBackPtr, MCObjectHandle objectHand, MCObjectHandle pathHand);
		/*
			Sets the path object of a path custom object.  Returns true if the object was set correctly.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetCustomObjectProfileGroup(CallBackPtr, MCObjectHandle objectHand, MCObjectHandle profileGroupHand);
		/*
			Sets the profile group for a path custom object.  profileGroupHand may be the handle of a group or a
			single object.
		*/

	extern "C" void GS_CALLBACK GS_SetDefinition(CallBackPtr, MCObjectHandle h, MCObjectHandle newDef);
		/*
			Changes h's defining object to the new one specified by newDef.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetObjectProperty(CallBackPtr, Sint32 inCodeRefID, Sint32 inPropID, Boolean inValue);
		/*
			Sets the specified object property.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetObjectPropertyChar(CallBackPtr, Sint32 inCodeRefID, Sint32 inPropID, unsigned char inValue);
		/*
			Sets the Specified object property
		*/

	extern "C" Boolean GS_CALLBACK GS_SetObjectVariable(CallBackPtr, MCObjectHandle theObject, short setSelector, const TVariableBlock& value);
		/*
			Changes the property of an object.  The selector chooses which property will be changed, and the
			value specifies what it should be changed to have.
		*/

	extern "C" void GS_CALLBACK GS_SetParameterVisibility(CallBackPtr, MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetVisible);
		/*
			Sets the user interface visibility of the control for the specified custom object parameter.
		*/

	extern "C" void GS_CALLBACK GS_SetRoofEdge(CallBackPtr, MCObjectHandle object, short index, const WorldPt& vertexPt, double_param slope, WorldCoord projection, WorldCoord eaveHeight);
		/*
			Set a vertex of the roof.  Vertices define the outline of the roof and its characteristics. 
			Vertices must progress in a counter clock wise direction, when viewed from a top view, otherwise the
			roof cannot be built.

			index: Indexs have values between 1 and NVertices (See GetRoofVertices())
			edgePt: Coordinate point for this edge
			slope: pitch of this roof edge
			projection: eave overhang
			eaveHeight: eave height
		*/

	extern "C" Boolean GS_CALLBACK GS_SetSingularConstraint(CallBackPtr, short type, MCObjectHandle obj, short vertexA, short vertexB);
		/*
			Sets a constraint on a single object.  The valid values for type are  4 (vertical), 5 (horizontal),
			8 (distance), 9 (vertical distance), 10 (horizontal distance) and 11 (radius).  vertexA and vertexB
			indicate which vertices of the object define the geometry to be constrained.  A value of -1
			indicates that a vertex parameter is not applicable.  It returns false if the constraint cannot be
			set.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetViewportClassVisibility(CallBackPtr, MCObjectHandle viewportHandle, InternalIndex classIndex, short visibilityType);
		/*
			Sets the visibility for the specified class in the specified viewport.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetViewportCropObject(CallBackPtr, MCObjectHandle viewportHandle, MCObjectHandle cropHandle);
		/*
			Sets the specified crop object in the specified viewport. If a crop object already exists, it will
			be replaced by the new object, so Sint32 as the new object is a valid crop.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetViewportLayerVisibility(CallBackPtr, MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short visibilityType);
		/*
			Sets the visibility for the specified layer in the specified viewport.
		*/

	extern "C" Boolean GS_CALLBACK GS_TrimToSelectedObjects(CallBackPtr, MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2);


	extern "C" Boolean GS_CALLBACK GS_UpdateConstraintModel(CallBackPtr);
		/*
			This updates the geometry of the constraint model for all the objects that were explicitly added to
			the model (through the useSelection flag or by being passed into CreateConstraintModel or
			AddToConstraintModel) to their current location and geometry in the drawing.  Then it attempts to
			resolve all the parametric constraints in the model, setting any node that was modified by user
			action to be unmovable.  If a constraint could not be resolved, this function returns false, and an
			Undo call should be made.
		*/

	extern "C" void GS_CALLBACK GS_UpdateViewport(CallBackPtr, MCObjectHandle viewportHandle);
		/*
			Updates the specified viewport: a dirty viewport, whose render type is other than wireframe or
			sketch, will be re-rendered.
		*/

	extern "C" Boolean GS_CALLBACK GS_ViewportHasCropObject(CallBackPtr, MCObjectHandle viewportHandle);
		/*
			Indicates if specified viewport has a crop object.
		*/



///////////////////////////////////////////
//  Resources
///////////////////////////////////////////
	extern "C" void GS_CALLBACK GS_GetResourceString(CallBackPtr, short id, short index, TXString& theString, Boolean lookOnlyInCurrentFile = true, EEmptyStringResourceHandling debugWarning = eWarnAboutEmptyStringResult);




///////////////////////////////////////////
//  Selection Manipulation
///////////////////////////////////////////


	extern "C" MCObjectHandle GS_CALLBACK GS_FirstSelectedObject(CallBackPtr);
		/*
			Returns handle to the first selected editable object in the drawing.
		*/

	extern "C" void GS_CALLBACK GS_GetSelectionBounds(CallBackPtr, WorldRect& bounds, BoundsType type = kRefreshBounds);
		/*
			Returns in bounds the smallest CoordRect that completely surrounds the selection.  For an object
			like a locus, the value depends on the type: kGeometricBounds will just give the point the locus is
			at, while kRefreshBounds will give the rectangle that encloses what is drawn on screen to represent
			the locus.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetSelectionBoundsCube(CallBackPtr, WorldCube &theCube);
		/*
			Gets the bounding cube of 3D objects currently selected. It returns the number of 3D objects it
			found. If it returns 0, then theCube is undefined.
		*/

	extern "C" void GS_CALLBACK GS_MoveSelection(CallBackPtr, WorldCoord dx, WorldCoord dy);
		/*
			Moves the selected objects 
		*/

	extern "C" void GS_CALLBACK GS_MoveSelection3D(CallBackPtr, WorldCoord dx, WorldCoord dy, WorldCoord dz);
		/*
			Analogous to MoveSelection
		*/

	extern "C" void GS_CALLBACK GS_RotateSelectionN(CallBackPtr, const WorldPt& rotCen, double_param rotAngle);
		/*
			Rotates selection  about rotCen through rotAngle degrees.
		*/

	extern "C" void GS_CALLBACK GS_ScaleSelectionN(CallBackPtr, const WorldPt& scaleCen, double_param scaleX, double_param scaleY);
		/*
			Scales the each 2D object of the selection as ScaleObject does.
		*/



///////////////////////////////////////////
//  Text Block Objects
///////////////////////////////////////////


	extern "C" Boolean GS_CALLBACK GS_AddText(CallBackPtr, MCObjectHandle textBlock, Sint32 beforeChar, Handle newText);
		/*
			Adds the characters in newText to the text in textBlock, starting before the character beforeChar.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddTextFromBuffer(CallBackPtr, MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize);
		/*
			This is identical to GS_AddText except it takes the text to be added from a pointer rather than a
			Mac-specific Handle. This function provides the only way to add text to a text block from a native
			Windows external. A result of true indicates success. A result of false indicates failure due to low
			memory or invalid parameters.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateTextBlock(CallBackPtr, const TXString& textStr, const WorldPt& textOrigin, Boolean fixedSize, WorldCoord width);
		/*
			Creates a text block at location textOrigin with the string textStr using the current defaults for
			font, size, style, and color.  If fixedSize is true, width determines the static width of the text
			box and text is dynamically wrapped to that width; otherwise lines break only on carraige returns in
			the text.
		*/

	extern "C" void GS_CALLBACK GS_DeleteText(CallBackPtr, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars);
		/*
			Deletes numChars from the text in textBlock beginning at firstChar.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetCharNumFromPoint(CallBackPtr, MCObjectHandle textBlock, const WorldPt& pt);
		/*
			This function will give the number of the character in the given text object that is closest to the
			given world point.
		*/

	extern "C" void GS_CALLBACK GS_GetTextColor(CallBackPtr, MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor);
		/*
			Sets charColor to the color of character number charNum.
		*/

	extern "C" void GS_CALLBACK GS_GetTextFontIndex(CallBackPtr, MCObjectHandle textBlock, Sint32 charNum, short& fontIndex);
		/*
			Gets the font of character number charNum.

			See FontNameFromIndex & FontIndexFromName for information about font index values.
		*/

	extern "C" void GS_CALLBACK GS_GetTextJustification(CallBackPtr, MCObjectHandle textBlock, short& justification);
		/*
			Gets the justification from the text object.  See SetTextJustification for the meaning of
			justification values.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetTextLength(CallBackPtr, MCObjectHandle textBlock);
		/*
			Returns the number of characters in the text block.
		*/

	extern "C" void GS_CALLBACK GS_GetTextLineHeight(CallBackPtr, MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height);
		/*
			Gets the actual spacing of the line containing character charNum.
		*/

	extern "C" void GS_CALLBACK GS_GetTextOrientationN(CallBackPtr, MCObjectHandle h, double_gs& angle, short& flipState);
		/*
			Gets the orientation of a text block.  angle is the angle of rotation.  flipState indicates along
			which axis the text is flipped, 0 = none, 1 = horizontal, 2 = vertical.  When drawing the text, the
			text is first flipped about the center point and then rotated around the same point.
		*/

	extern "C" void GS_CALLBACK GS_GetTextSize(CallBackPtr, MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize);
		/*
			Sets charSize to the size of character number charNum.
		*/

	extern "C" void GS_CALLBACK GS_GetTextStyle(CallBackPtr, MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle);
		/*
			Sets charStyle to the style of character number charNum.
		*/

	extern "C" void GS_CALLBACK GS_GetTextVerticalAlignment(CallBackPtr, MCObjectHandle textBlock, short& verticalAlignment);
		/*
			Gets the vertical alignment of the text block.  See SetTextVerticalAlignment for the meaning of the
			alignment constants.
		*/

	extern "C" void GS_CALLBACK GS_GetTextVerticalSpacing(CallBackPtr, MCObjectHandle textBlock, short& spacing, WorldCoord& height);
		/*
			Gets the spacing of the entire text block. which can be:

				kTextCustomLeading = 0,
				kTextSingle = 2,
				kTextThreeHalves = 3,
				kTextDouble = 4

			If spacing is kTextCustomLeading, then height is set to the custom leading value. Otherwise height
			is unchanged.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetTextWidth(CallBackPtr, MCObjectHandle textBlock, WorldCoord& width);
		/*
			Returns the width between left and right margin of the text block.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetTextWrap(CallBackPtr, MCObjectHandle textBlock, Boolean& wrapped);
		/*
			Returns whether the text block wraps its text.
		*/

	extern "C" void GS_CALLBACK GS_SetTextColor(CallBackPtr, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor);
		/*
			Sets the range of characters from firstChar to firstChar+numChars to have the color specified in
			charColor.
		*/

	extern "C" void GS_CALLBACK GS_SetTextFontIndex(CallBackPtr, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, short fontIndex);
		/*
			Sets the range of characters from firstChar to firstChar+numChars to have the font specified in
			fontIndex.

			See FontNameFromIndex & FontIndexFromName for information about font index values.
		*/

	extern "C" void GS_CALLBACK GS_SetTextJustification(CallBackPtr, MCObjectHandle textBlock, short justification);
		/*
			Sets the text object textBlock to have the justification specified, using the following table:

			justification        meaning
			1                       left
			2                       center
			3                       right
			4						justify
		*/

	extern "C" void GS_CALLBACK GS_SetTextOrientationN(CallBackPtr, MCObjectHandle h, double_param angle, short flipState);
		/*
			Sets the orientation of a text block.  angle is the angle of rotation.  flipState indicates along
			which axis the text is flipped, 0 = none, 1 = horizontal, 2 = vertical.  When drawing the text, the
			text is first flipped about the center point and then rotated around the same point.
		*/

	extern "C" void GS_CALLBACK GS_SetTextSize(CallBackPtr, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, WorldCoord charSize);
		/*
			Sets the range of characters from firstChar to firstChar+numChars to have the size specified in
			charSize.
		*/

	extern "C" void GS_CALLBACK GS_SetTextStyle(CallBackPtr, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char charStyle);
		/*
			Sets the range of characters from firstChar to firstChar+numChars to have the style specified in
			charStyle.
		*/

	extern "C" void GS_CALLBACK GS_SetTextVerticalAlignment(CallBackPtr, MCObjectHandle textBlock, short verticalAlignment);
		/*
			Sets the vertical alignment of the text block.

			kTopBox = 1,
			kTopBaseline = 2,
			kCenterBox = 3,
			kBottomBaseline = 4,
			kBottomBox = 5

		*/

	extern "C" void GS_CALLBACK GS_SetTextVerticalSpacing(CallBackPtr, MCObjectHandle textBlock, short spacing, WorldCoord height);
		/*
			Sets the spacing of the entire text block to the value specified by spacing, which can be:

				kTextCustomLeading = 0,
				kTextSingle = 2,
				kTextThreeHalves = 3,
				kTextDouble = 4

			If kTextCustomLeading is specified, then the line height is set to the value in height. Otherwise
			height is ignored.
		*/

	extern "C" void GS_CALLBACK GS_SetTextWidth(CallBackPtr, MCObjectHandle textBlock, WorldCoord width);
		/*
			Turns on wrapping for the text block and sets the margin with to newWidth.
		*/

	extern "C" void GS_CALLBACK GS_SetTextWrap(CallBackPtr, MCObjectHandle textBlock, Boolean wrapped);
		/*
			Turns on wrapping for the text block and leaves the margins unchanged.
		*/

	extern "C" void GS_CALLBACK GS_SpellCheckTextBuffer(CallBackPtr, GSHandle charsHandle, Boolean textChanged);
		/*
			Performs a spell check on the text in charsHandle. The textChanged parameter is true when
			corrections are made and the corrected text is returned in charsHandle.
		*/



///////////////////////////////////////////
//  Textures
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AttachDefaultTextureSpace(CallBackPtr, MCObjectHandle object, short multiPartID);
		/*
			Deletes any pre-existing space attached to the object (with the specified part ID), creates a new
			one with the default value for this type of object, and attaches the texture space to the object.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateShaderRecord(CallBackPtr, MCObjectHandle texture, Sint32 family, Sint32 prototype);
		/*
			Creates a shader record of the desired family (1 = color, 2 = reflectivity, 3 = transparency, 4 =
			bump) and prototype (constants depend on family value).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateTexture(CallBackPtr);
		/*
			Creates a new texture object handle with default values
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateTextureBitmap(CallBackPtr);
		/*
			Creates a new default texture bitmap, with no paint node attached.  Texture bitmap's paint node
			should be attached before this texture bitmap is used by MiniCAD (ovTextureBitmapPaintNode).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateTextureBitmapFromPaintNode(CallBackPtr, MCObjectHandle paintNodeObject);
		/*
			Creates a new texture bitmap, with the specified paint node attached.
		*/

	extern "C" void GS_CALLBACK GS_DeleteTextureSpace(CallBackPtr, MCObjectHandle object, short multiPartID);
		/*
			Removes the texture space from this object.  To render textures correctly, an object must have both
			a non-zero texture ref and a texture space attached.  The reverse of this means that the texture ref
			for the object should be set to zero when this function is called.
		*/

	extern "C" Boolean GS_CALLBACK GS_EditShaderRecord(CallBackPtr, MCObjectHandle shaderRecord);
		/*
			Brings up the edit shader dialog for this shader.  Returns true if the user pressed the OK button to
			dismiss the dialog.
		*/

	extern "C" Boolean GS_CALLBACK GS_EditTexture(CallBackPtr, MCObjectHandle texture);
		/*
			Brings up the "Edit Texture" dialog for this texture
		*/

	extern "C" Boolean GS_CALLBACK GS_EditTextureSpace(CallBackPtr, MCObjectHandle texturedObject, short multiPartID);
		/*
			Brings up the "Edit Mapping" dialog for the space attached to the object.

		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetClGenTexture(CallBackPtr, InternalIndex index);
		/*
			Returns the sysname of the generic texture for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_GetClRoofTextures(CallBackPtr, InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer);
		/*
			Returns the roof textures for the specified class.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetClUseTexture(CallBackPtr, InternalIndex index);
		/*
			Returns whether textures will be used at object creation for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_GetClWallTextures(CallBackPtr, InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center);
		/*
			Returns the wall textures for the specified class.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetShaderRecord(CallBackPtr, MCObjectHandle parentNode, Sint32 family);
		/*
			Returns the shader record of the specified family (1 = color, 2 = reflectivity, 3 = transparency, 4
			= bump), if one is attached to the texture.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetTextureRef(CallBackPtr, MCObjectHandle object, short multiPartID, Boolean resolveByClass);
		/*
			Returns the texture ref for this object, which is the internal index, or name, of the texture node
			used by this object.  The texture is specific to the multiPartID part of the object (kPrimary,
			kSecondary, or kTertiary).  Walls can have three different textures and roofs can have two if they
			are "expanded" through ovExpandedTexture.  Textures may be applied by class.  If an object's texture
			is -1, then the object will be rendered with the texture of its class.  If an object's texture ref
			is -1 and resolveByClass is kNoResolveByClass, this routine will return -1.  If the object's texture
			ref is -1 and resolveByClass is kResolveByClass, then this routine will look up the object's class
			and return the class' texture ref.
			Objects can be more specific about which of the class' textures to use by having a texture ref of -2, -3, etc.
			-2: Class "Other" texture, -3: wall right, -4: wall left, -5: wall center, -6: roof top, -7: roof dormer texture.
		*/

	extern "C" void GS_CALLBACK GS_GetTextures(CallBackPtr, MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture);
		/*
			Returns the textures for the specified object.  A value of 0 in a texture parameter means the object
			has no texture of that kind.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetTextureSpace(CallBackPtr, MCObjectHandle object, short multiPartID);
		/*
			Returns the texture space attached to this object, with the same part ID as multiPartID.  Walls may
			have three texture spaces attached to them if they have expanded textures, for example.
		*/

	extern "C" InternalIndex GS_CALLBACK GS_GetVPClassGenTexture(CallBackPtr, MCObjectHandle viewport, InternalIndex classIndex);
		/*
			Returns the InternalIndex of the generic texture for the specified class for the specified viewport.
		*/

	extern "C" void GS_CALLBACK GS_GetVPClassRoofTextures(CallBackPtr, MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer);
		/*
			Returns the InternalIndex's of the roof textures for the specified class for the specified viewport.
		*/

	extern "C" void GS_CALLBACK GS_GetVPClassWallTextures(CallBackPtr, MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center);
		/*
			Returns the InternalIndex's of the wall textures for the specified class for the specified viewport.
		*/

	extern "C" void GS_CALLBACK GS_SetClGenTexture(CallBackPtr, InternalIndex index, InternalIndex texture);
		/*
			Sets the generic texture for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClRoofTextures(CallBackPtr, InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer);
		/*
			Sets the roof textures for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClUseTexture(CallBackPtr, InternalIndex index, Boolean use);
		/*
			Sets whether texture attributes are used at object creation for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetClWallTextures(CallBackPtr, InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center);
		/*
			Sets the wall textures for the specified class.
		*/

	extern "C" void GS_CALLBACK GS_SetDefaultTextureSpace(CallBackPtr, MCObjectHandle object, MCObjectHandle space, short multiPartID);
		/*
			Sets the space to the default values for this type of object.

		*/

	extern "C" void GS_CALLBACK GS_SetTextureRef(CallBackPtr, MCObjectHandle object, InternalIndex textureRef, short multiPartID);
		/*
			See GetTextureRef
		*/



///////////////////////////////////////////
//  Tool Utilities
///////////////////////////////////////////


	extern "C" MCObjectHandleID GS_CALLBACK GS_AddToolPersistentDraw(CallBackPtr, GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv);
		/*
			Application calls drawProcPtr to maintain persistent screen drawing.  Return value is ID used in
			GS_RemoveToolPersistentDraw.
		*/

	extern "C" MCObjectHandleID GS_CALLBACK GS_AddToolSnapGeometry(CallBackPtr, MCObjectHandle inSnapGeometry);
		/*
			Adds a copy of inSnapGeometry to an application list of snapable geometry.  The return ID is used to
			remove the the snap geometry from this list using GS_RemoveToolSnapGeometry.
		*/

	extern "C" void GS_CALLBACK GS_BoxToolDraw(CallBackPtr);
		/*
			Draws a  box using the first two Tool points of the tool points.   Call this from the ToolMessage::kAction_Draw
			action handler of the tool definition procedure
		*/

	extern "C" Boolean GS_CALLBACK GS_ClearAllToolPts(CallBackPtr);
		/*
			Removes all tool points. 
		*/

	extern "C" void GS_CALLBACK GS_ClearDataDisplayBar(CallBackPtr);
		/*
			Clears the data display bar so that it has no values displaying in any of the boxes.
		*/

	extern "C" Sint32 GS_CALLBACK GS_ClickDragToolStatus(CallBackPtr);
		/*
			Return a status constat for a tool that requires two distinct points and click drag.  Call this from
			the ToolMessage::kAction_GetStatus action handler of the tool definition procedure
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarCreate(CallBackPtr, short inNumFields, CustomBarRefID& outCustomBarRefID);
		/*
			Creates an instance of a custom editable dataBar.  outCustomBarRefID is returned as reference for
			other CustomBar APIs.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarGetFieldInfo(CallBackPtr, CustomBarRefID inCustomBarID, short inFieldIndex, CustomBarFieldInfo& inFieldInfo);
		/*
			Gets the specifed field info of the specified CustomBar.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarInstall(CallBackPtr, CustomBarRefID inCustomBarID);
		/*
			Installs the CustomBar allocated with  CustomBarCreate.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarRelease(CallBackPtr, CustomBarRefID inCustomBarRefID);
		/*
			Frees the CustomBar allocated with  CustomBarCreate.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarSetFieldAngle(CallBackPtr, CustomBarRefID inCustomBarID, short inFieldIndex, const double& inDegrees);
		/*
			Places the string equivalent of inDegrees in the specified field. 
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarSetFieldInfo(CallBackPtr, CustomBarRefID inCustomBarID, short inFieldIndex, const CustomBarFieldInfo& inFieldInfo);
		/*
			Sets the specifed field info of the specified CustomBar.
		*/

	extern "C" Boolean GS_CALLBACK GS_CustomBarSetFieldWorldCoord(CallBackPtr, CustomBarRefID inCustomBarID, short inFieldIndex, const WorldCoord& inCoordVal);
		/*
			Places the string equivalent of inCoordVal in the specified field. 
		*/

	extern "C" void GS_CALLBACK GS_Default2DToolDraw(CallBackPtr);
		/*
			Draws a 2D line segment between each of the tool points.   Call this from the ToolMessage::kAction_Draw action
			handler of the tool definition procedure
		*/

	extern "C" void GS_CALLBACK GS_Default3DToolDraw(CallBackPtr);
		/*
			Draws a 3D line segment between each of the tool points.   Call this from the ToolMessage::kAction_Draw action
			handler of the tool definition procedure
		*/

	extern "C" void GS_CALLBACK GS_DrawCoordArcN(CallBackPtr, const WorldRect& theBox, double_param startAngle, double_param sweepAngle);
		/*
			Draws a portion of the ellipse bounded by theBox.  startAngle and sweepAngle are in degrees, with 0'
			being east and increasing values moving counter-clockwise.
		*/

	extern "C" void GS_CALLBACK GS_DrawCoordEllipse(CallBackPtr, WorldRect& theBox);
		/*
			Draws the ellipse bounded by theBox.
		*/

	extern "C" void GS_CALLBACK GS_DrawCoordLine(CallBackPtr, const WorldPt& p1, const WorldPt& p2);
		/*
			Draws and image of a line with given world coordinates.  DrawCoord.... callbacks are often used in
			interactive2DDraw draw procedures.
		*/

	extern "C" void GS_CALLBACK GS_DrawCoordLine3D(CallBackPtr, const WorldPt3& p1, const WorldPt3& p2);
		/*
			Draws and image of a line with given world coordinates.  DrawCoord.... callbacks are often used in
			ToolMessage::kAction_Draw action handlers.
		*/

	extern "C" void GS_CALLBACK GS_DrawCoordRect(CallBackPtr, const WorldRect& theBox);
		/*
			Draws the rectangle bounded by theBox.
		*/

	extern "C" void GS_CALLBACK GS_DrawDataDisplayBar(CallBackPtr, Boolean drawFramesFirst = false);
		/*
			Draws the data display bar.
		*/

	extern "C" void GS_CALLBACK GS_DrawNurbsObject(CallBackPtr, MCObjectHandle h);
		/*
			Draws the NURBS object h on the screen.
		*/

	extern "C" void GS_CALLBACK GS_DrawObject(CallBackPtr, MCObjectHandle h, Boolean doSelect);
		/*
			Draws the object h on the screen.  If doSelect is true, the handles will also be drawn.
		*/

	extern "C" void GS_CALLBACK GS_GetCoords(CallBackPtr, WorldPt& p, ViewPt& m);
		/*
			Returns the final mouse position after an Interactive2DDraw call, both in world and view coordinates.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetNumToolPts(CallBackPtr);


	extern "C" const ICoreToolAccess* GS_CALLBACK GS_GetToolCoreInterface(CallBackPtr);
		/*
			Returns a private Graphsoft interface pointer.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPt2D(CallBackPtr, Sint32 inIndex, WorldPt& outToolPoint);


	extern "C" Boolean GS_CALLBACK GS_GetToolPt3D(CallBackPtr, Sint32 inIndex, WorldPt3& outToolPoint);
		/*
			Gets  the specified 3D ToolPoint .  The index  is a zero based index .  False is returned if the
			index is out of range 0 <= index< GS_GetNumToolPoints.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPtCurrent2D(CallBackPtr, WorldPt& outToolPoint);
		/*
			Gets the 2D Current Smart Cursor  value. 
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPtCurrent3D(CallBackPtr, WorldPt3& outToolPt);
		/*
			Returns in outToolPt the current 3D point.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPtCurrentViewPt(CallBackPtr, ViewPt& outToolPt);
		/*
			Returns in outToolPt the current view space point. 
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPtCurrentWorkingPlane(CallBackPtr, WorldPt3& outToolPt);
		/*
			Returns in outToolPt the current 3D working plane point. 
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPtViewPoint(CallBackPtr, Sint32 inIndex, ViewPt& outToolPoint);
		/*
			Gets  the specified view space ToolPoint .  The index  is a zero based index .  False is returned if
			the index is out of range 0 <= index< GS_GetNumToolPoints.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetToolPtWorkingPlane(CallBackPtr, Sint32 inIndex, WorldPt3& outToolPoint);
		/*
			Gets  the specified 3D working plane ToolPoint .  The index  is a zero based index .  False is
			returned if the index is out of range 0 <= index< GS_GetNumToolPoints.
		*/

	extern "C" void GS_CALLBACK GS_InstallConstraintAlong3DLine(CallBackPtr, const Ray& inConstraintDescription);
		/*
			Constrains the GS_GetToolPtCurrent3D result to a point along the line defined by
			inConstraintDescription. This constraint is removed with every tool point added or removed.
		*/

	extern "C" void GS_CALLBACK GS_Interactive2DDraw(CallBackPtr cbp, short options, short shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env);
		/*
			Interactive2DDraw is called when drawing interactively.  To use it, you must define all drawing to
			be done as a function of the worldspace start and endpoints of a drag operation.
			the prototype for Interactive2DDraw is :
					
			Interactive2DDraw(CallBackPtr cbp, short options, short shiftConsMode, I2DDrawProcPtr drawProc, void
			*env);
					
			where drawProc is the function that does the drawing.  Interactive2DDraw takes care of 
			the draw and undraw for you as well as respond to any constraints set with shiftConsMode 
			or the constaint set in the TDef.

		*/

	extern "C" Sint32 GS_CALLBACK GS_OnePointToolStatus(CallBackPtr);
		/*
			Return a value representing the current status of the tool. 
		*/

	extern "C" Sint32 GS_CALLBACK GS_PolyToolStatus(CallBackPtr);
		/*
			Return a status constat for a tool that requires user a defined  number of points.  The tool is
			completed with a double click or a click on the first point entered.   Call this from the
			ToolMessage::kAction_GetStatus action handler of the tool definition procedure
		*/

	extern "C" Boolean GS_CALLBACK GS_PopLastToolPt(CallBackPtr);
		/*
			Removes the last tool point.  If the user has cllicked three times and PopLastToolPt is called the
			number of tool points will be reduced from three to two. 
		*/

	extern "C" void GS_CALLBACK GS_RemoveHotSpot(CallBackPtr, HotSpotRefID inHotSpotID);
		/*
			Removes the HotSpot specified by inHotSpotID.
		*/

	extern "C" void GS_CALLBACK GS_RemoveToolPersistentDraw(CallBackPtr, MCObjectHandleID persistentDrawRefID);
		/*
			Removes the persistent draw installed by AddToolPersistentDraw.
		*/

	extern "C" void GS_CALLBACK GS_RemoveToolSnapGeometry(CallBackPtr, MCObjectHandleID inSnapGeometryID);
		/*
			Removes the snap geometry added with GS_AddToolSnapGeometry.
		*/

	extern "C" void GS_CALLBACK GS_SetCursorMode(CallBackPtr);
		/*
			Makes the cursor tool the active tool.  This cannot be called from Tool externals.
		*/

	extern "C" void GS_CALLBACK GS_SetDataDisplayBarField(CallBackPtr, short fieldNum, BarNumberType barType, const TXString& barLabel);
		/*
			Sets one field of the data display bar to display a particular type of information.  fieldNum
			specifies which field and must be in the range 1-6.
		*/

	extern "C" void GS_CALLBACK GS_SetDimUserBarValue(CallBackPtr, short fieldNum, WorldCoord dimVal);
		/*
			Sets the value for a userBarStr field to a dimension value.  The dimVal will be displayed in the
			current units setting.
		*/

	extern "C" void GS_CALLBACK GS_SetFloatUserBarValueN(CallBackPtr, short fieldNum, double_param floatVal, short numPlaces);
		/*
			Sets the value for a userBarStr field from a floating point value.  numPlaces specifies the number
			of decimal places to use in the conversion.  Passing -1 for numPlaces specifies a general format
			similar to that found in the worksheet, -2 converts the number as an angle using the current units
			setting.
		*/

	extern "C" void GS_CALLBACK GS_SetTextUserBarValue(CallBackPtr, short fieldNum, const TXString& textVal);
		/*
			Sets the value for a userBarStr field to the passed string.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetToolProperty(CallBackPtr, Sint32 inCodeRefID, Sint32 inToolPropID, Boolean inValue);
		/*
			Uses the inCodeRefID passed to the tool 's ToolInitXPropsMessage::kAction action handler to set the property
			specified by inToolPropID.
		*/

	extern "C" Boolean GS_CALLBACK GS_SetToolPropertyChar(CallBackPtr, Sint32 inCodeRefID, Sint32 inToolPropID, char inValue);
		/*
			Uses the inCodeRefID passed to the tool 's ToolInitXPropsMessage::kAction action handler to set the property
			specified by inToolPropID.
		*/

	extern "C" Sint32 GS_CALLBACK GS_ThreePointToolStatus(CallBackPtr);
		/*
			Return a status constat for a tool that requires three distinct points   Call this from the
			ToolMessage::kAction_GetStatus action handler of the tool definition procedure
		*/

	extern "C" HotSpotRefID GS_CALLBACK GS_TrackHotSpot(CallBackPtr, Boolean& outIs3d, WorldPt3& outLocation);
		/*
			Returns the ID of the HotSpot at the current mouse posistion.
		*/

	extern "C" void GS_CALLBACK GS_TrackTool(CallBackPtr, MCObjectHandle& overObject, short& overPart, SintptrT& code);
		/*
			Used during the kToolDoPick case of a tool definition.  Returns in overObject the object the cursor
			is currently over (or nil if the cursor is not over any object) and in overPart one of cursOnNothing
			(object is not over any snappable object), cursOnObject (cursor is over an object), or cursOnHandle
			(object is over a selected object's handle).  TrackTool only responds to 'snappable' objects, i.e.
			objects that are on a currently editable or snappable layer. code returns a RefNumber or BlankHandle
			that is specific to each overPart message.
		*/

	extern "C" Sint32 GS_CALLBACK GS_TwoPointToolStatus(CallBackPtr);
		/*
			Return a value representing the current status of the tool.
		*/



///////////////////////////////////////////
//  Tree Walking & Manipulation
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AddObjectToContainer(CallBackPtr, MCObjectHandle h, MCObjectHandle container);
		/*
			Moves h inside the specified container object and makes it the last item in the container.  This
			routine is supplied for convenience; 'AddObjectToContainer(cbp, h, c)' is equivalent to
			'InsertObjectAfter(cbp, h, LastMemberObject(cbp, c))'
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_AuxOwner(CallBackPtr, MCObjectHandle h);
		/*
			For object h, returns the object that contains h in its auxList. Nil is returned if object h is not
			part of an aux list.
		*/

	extern "C" void GS_CALLBACK GS_DeleteObject(CallBackPtr, MCObjectHandle h, Boolean useUndo = true);
		/*
			Deletes h and all of its sub-objects, if it has any. If undo is active and an undo swap primitive
			has been created using the AddBeforeSwapObject call, then the useUndo flag must be set to true so
			that object will not be freed from memory (since the undo table is pointing to it). On the other
			hand, if h is a temporary object and AddAfterSwapObject was not called after it was created and
			AddBeforeSwapObject was not called before this delete call, then the useUndo flag should be set to
			false so that h will actually be deleted. Note that this function does not add anything to or
			directly affect the undo table.
		*/

	extern "C" Boolean GS_CALLBACK GS_FindHandleDeep(CallBackPtr, MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused);
		/*
			Find a handle in a list (searching children and aux lists). Return true if the handle is found. 
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_FirstMemberObj(CallBackPtr, MCObjectHandle h);
		/*
			Returns the first object in any container.  A container is a 'group-like' object, that is, an object
			which is composed of other objects. Groups, layers, symbol definitions (but not symbol instances!),
			extrudes, multiple extrudes, sweeps, slabs (meshes? walls? dimensions?) are all containers.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetDefaultContainer(CallBackPtr);
		/*
			Returns the container which all new objects are added.  Usually this is a layer, but can also be an
			object that has been 'entered' using the Enter Group menu command.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetDrawingHeader(CallBackPtr);
		/*
			Returns the header node of the currently active drawing.  From the header node, you can reach any
			object in the drawing.  FirstMemberObj(GetDrawingHeader()) is the first (i.e. bottom-most) layer.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetHatchListHeader(CallBackPtr);
		/*
			Returns a handle to the container holding the hatch definitions. You can iterate through the list of
			hatches by searching for objects of kHatchDefNode type starting at GS_FirstMemberObj(...,
			GS_GetHatchListHeader()).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetSymbolLibraryHeader(CallBackPtr);
		/*
			Returns the symbol library header of the current document.
		*/

	extern "C" void GS_CALLBACK GS_InsertObjectAfter(CallBackPtr, MCObjectHandle h, MCObjectHandle afterObject);
		/*
			Unlinks h from wherever it currently is in the drawing and inserts it immediately after afterObject. 
			Any changes in drawing order can be accomplished using this routine or its companion
			InsertObjectBefore.  For example, to implement the 'Move Foward' command, you would use
			'InsertObjectAfter(cbp, h, NextObject(cbp, h))'.  You can also use InsertObjectAfter to move objects
			in to and out of containers'see InsertObjectBefore for an example of this.
		*/

	extern "C" void GS_CALLBACK GS_InsertObjectBefore(CallBackPtr, MCObjectHandle h, MCObjectHandle beforeObject);
		/*
			Unlinks h from wherever it currently is in the drawing and inserts it immediately before
			beforeObject.  Note that you can use this routine to move object in to and out of containers.  For
			example, to make an object the first object in a group, use 'InsertObjectBefore(cbp, h,
			FirstMemberObj(cbp, aGroup))'.  The same caveats about what types of objects may be inserted where
			that apply to InsertObjectAfter also apply to InsertObjectBefore.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_LastMemberObj(CallBackPtr, MCObjectHandle h);
		/*
			Just like FirstMemberObj, but returns the last object instead.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_NextObject(CallBackPtr, MCObjectHandle h);
		/*
			Returns the object immediately following h, or nil 
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ParentObject(CallBackPtr, MCObjectHandle h);
		/*
			Returns the 'parent' of h, that is, h's immediate owner.  For most objects, this is the layer they
			are in; for an object in a container, it is its enclosing container; for a layer, it is the drawing
			header.  The drawing header and any symbol definitions which are not in any folder have no parent;
			calling ParentObject on them will return nil.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_PrevObject(CallBackPtr, MCObjectHandle h);
		/*
			Returns a handle to the object imediately before h in the drawing list.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_SearchForAncestorType(CallBackPtr, CBSignedShort objectType, MCObjectHandle h);
		/*
			For object h, returns the first ancestor object of type tdType, or nil if no (eventual) parent of
			that type exists. For example, CB_SearchForAncestorType(16, h) will return the symDef that contains
			h, or nil if h is not a child of a symDef. Aux lists are not considered in this function (if h is in
			an aux list, this function will always return nil). 
		*/

	extern "C" void GS_CALLBACK GS_SetPageBounds(CallBackPtr, const WorldRect& bounds);
		/*
			Sets bounds to the smallest rectangle surrounding all of the pages.
		*/



///////////////////////////////////////////
//  <Unclassified>
///////////////////////////////////////////


	extern "C" Boolean GS_CALLBACK GS_AcquireExportPDFSettingsAndLocation(CallBackPtr, Boolean inbSeparateDocuments);
		/*
			This will querry the user for the Export PDF settings  and then ask for the PDF file name, or folder
			name if the SeparateDocuments parameter is true.  When the SeparateDocuments parameter is true, it
			means you want to export a series of sheet layers or saved views in separate PDF documents instead
			of all together in a single document.  This is intended to support Batch PDF Export.
		*/

	extern "C" void GS_CALLBACK GS_ClosePDFDocument(CallBackPtr);
		/*
			This will finish creating the PDF document that you started with GS_OpenPDFDocument.  This is
			intended to suppor t Batch Export to PDF.
		*/

	extern "C" short GS_CALLBACK GS_ExportPDFPages(CallBackPtr, const TXString& inSavedViewNameStr);
		/*
			This will export the current document to PDF.  You must call GS_OpenPDFDocument before calling this
			function.  This is intended to support Batch Export to PDF.
		*/

	extern "C" Boolean GS_CALLBACK GS_OpenPDFDocument(CallBackPtr, const TXString& inFileNameStr);
		/*
			This will begin the export to  a PDF document.  You must call GS_AcquireExportPDFSettingsAndLocation
			before calling this function.  The filename parameter can be blank if you indicate that you are not
			generating separate documents in GS_AcquireExportPDFSettingsAndLocation.  This is intended to
			support Batch PDF Export.
		*/



///////////////////////////////////////////
//  Undo
///////////////////////////////////////////


	extern "C" Boolean GS_CALLBACK GS_AddAfterMoveObject(CallBackPtr, MCObjectHandle h);
		/*
			Use this callback after you move an object in your routine.  "Move" here does not mean moving an
			object across the page (like a drag), it means moving an object within the internal MiniCad main
			drawing list (like when an object changes layers or is "sent to back"). Only applicable after a
			SetUndoMethod(cbp, kUndoSwapObjects) or a SetUndoMethod(cbp, kUndoReplaceSelection) call has been
			made.  An AddBeforeMoveObject(h) must have been called before AddAfterMoveObject(h) is called.
			Passing a nil handle creates undo primitives for all selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddAfterSwapObject(CallBackPtr, MCObjectHandle h);
		/*
			Use this callback after you add an object in your routine.  A reference to h is stored in the undo
			table, and that is object is deleted when Undo is selected.  Only applicable after a
			SetUndoMethod(cbp, kUndoSwapObjects) or a SetUndoMethod(cbp, kUndoReplaceSelection) call has been
			made. Passing a nil handle creates undo primitives for all selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddBeforeMoveObject(CallBackPtr, MCObjectHandle h);
		/*
			Use this callback before you move an object in your routine.  "Move" here does not mean moving an
			object across the page (like a drag), it means moving an object within the internal MiniCad main
			drawing list (like when an object changes layers or is "sent to back"). Only applicable after a
			SetUndoMethod(cbp, kUndoSwapObjects) or a SetUndoMethod(cbp, kUndoReplaceSelection) call has been
			made.  An AddAfterMoveObject(h) must be called after an AddBeforeMoveObject(h) call.  Passing a nil
			handle creates undo primitives for all selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddBeforeSwapObject(CallBackPtr, MCObjectHandle h);
		/*
			Use this callback before you delete an object in your routine.  The object is stored in the undo
			table and is re-inserted into the drawing when undo is selected.  Only applicable after a
			SetUndoMethod(cbp, kUndoSwapObjects) or a SetUndoMethod(cbp, kUndoReplaceSelection) call has been
			made.  After this call is issued, the object should be deleted using the call GS_DeleteObject(h,
			true), with the true indicating that undo is in effect for this object. Passing a nil handle creates
			undo primitives for all selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddBothSwapObject(CallBackPtr, MCObjectHandle h);
		/*
			Use this callback before you modify an object in your routine.  A copy and a reference to h is
			stored in the undo table.  When Undo is selected, h is deleted and the copy from the undo record is
			inserted.  Only applicable after a SetUndoMethod(cbp, kUndoSwapObjects) or a SetUndoMethod(cbp,
			kUndoReplaceSelection) call has been made. Passing a nil handle creates undo primitives for all
			selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddCoordMoveObject2D(CallBackPtr, MCObjectHandle h, WorldCoord dx, WorldCoord dy);
		/*
			Use this callback before you apply a 2D move to an object. Internally, this undo technique uses less
			memory than an AddBothSwapObjs call because it only saves the delta, not a copy of the entire
			object. Passing a nil handle creates undo primitives for all selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_AddCoordMoveObject3D(CallBackPtr, MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz);
		/*
			Use this callback before you apply a 3D move to an object. Internally, this undo technique uses less
			memory than an AddBothSwapObjs call because it only saves the delta, not a copy of the entire
			object. Passing a nil handle creates undo primitives for all selected objects.
		*/

	extern "C" Boolean GS_CALLBACK GS_EndUndoEvent(CallBackPtr);
		/*
			Ends the creation of an undo event. A new event must have been initiated (with the SetUndoEvent()
			callback) before EndUndoEvent() can be called. EndUndoEvent() saves the view at the end of the user
			action and performs general undo cleanup. The use of this procedure is not required; VectorWorks
			will automatically end the event when an external is completed.

		*/

	extern "C" void GS_CALLBACK GS_NameUndoEvent(CallBackPtr, const TXString& name);
		/*
			Attaches a name to the current undo event. A new event must be in the process of being built
			(created with the SetUndoEvent() callback) before NameUndoEvent() can be called.
		*/

	extern "C" Boolean GS_CALLBACK GS_NonUndoableActionOK(CallBackPtr);
		/*
			Posts a dialog informing the user that the action that is about to be performed is not undo-able. If
			the user clicks OK, this function returns true. If the user clicks NOT OK, this function returns
			false. If the "Show Undo Warnings" preference is turned off, NO dialog is presented, a user response
			of OK is assumed, and this function returns true. If this function returns true, you MUST call
			GS_SetUndoMethod(kUndoNone) before proceeding to change objects.
		*/

	extern "C" void GS_CALLBACK GS_SetUndoMethod(CallBackPtr, short undoType);
		/*
			Sets the method of undo to one of the kUndo' types listed below:
			  - kUndoNone (0) disables undo for the duration of the plug-in and clears the undo table. (It is
			sometimes advisable to precede this type of call with a NonUndoableActionOK call to allow the user a
			chance to back out of the operation.)
			  - kUndoSwapObjects (21) allows customization of the objects to be replaced using
			AddBeforeSwapObject, AddAfterSwapObject, and AddBothSwapObjects.
			  - kUndoReplaceSelection (17) saves the objects currently selected.  When undo is selected, the
			selection at that time is replaced with the saved selection.


		*/

	extern "C" void GS_CALLBACK GS_SupportUndoAndRemove(CallBackPtr);
		/*
			Notifies the undo system that an UndoAndRemove() call might be issued for the next undo event, and
			to therefore always build the next undo event (at least temporarily) regardless of whether the user
			has disabled the undo system or not. This call must be issued before the SetUndoMethod() call of an
			undo event that might be undone and removed using the UndoAndRemove() call.

		*/

	extern "C" void GS_CALLBACK GS_UndoAndRemove(CallBackPtr);
		/*
			Undo a partially built (unended) undo event and remove it from the undo table. The SetUndoMethod()
			call of the event that is being undone and removed must have been preceded with a
			SupportUndoAndRemove() call.
		*/



///////////////////////////////////////////
//  Utility
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AngleToStringN(CallBackPtr, double_param angle, TXString& s);
		/*
			Convert a number of degrees to its string representation, using the current drawing's angle format.
		*/

	extern "C" void GS_CALLBACK GS_AssociateLinearDimension(CallBackPtr, MCObjectHandle h, CBBoolean selectedObjectsMode);
		/*
			Associates a linear dimension with an object when the dimension's endpoints are coincident with
			objects in the drawing.  When selectedObjectsMode is true, only selected objects will be checked to
			see if they should be associated with the linear dimension.
		*/

	extern "C" Boolean GS_CALLBACK GS_CallPluginLibrary(CallBackPtr, const TXString& routineName, PluginLibraryArgTable* argumentTable, Sint32 status);
		/*
			Call an SDK Plug-in Library Routine. 
		*/

	extern "C" void GS_CALLBACK GS_ClipSurface(CallBackPtr, MCObjectHandle h1, MCObjectHandle h2);
		/*
			Creates a new surface object by subtracting the intersection of surfaces h1 and h2 from h1.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CombineIntoSurface(CallBackPtr, const WorldPt& insidePt);
		/*
			Given a point, CombineIntoSurface calls the menu function of the same name and passes it insidePt as
			the click point.
		*/

	extern "C" void GS_CALLBACK GS_CoordToDimString(CallBackPtr, WorldCoord c, TXString& s);
		/*
			Transforms the coordinate c into a dimension string in the current drawing's units.
		*/

	extern "C" CBSignedShort GS_CALLBACK GS_CStringCompare(CallBackPtr, ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags);
		/*
			Compares the C strings cStr1 and cStr2, returning one of the following values from
			EStringCompareResult: kEqualStrings, kFirstStringSmaller, kFirstStringBigger. The compare uses the
			flags from EStringCompare, which currently has: kDefaultCompare, kIncludeCase, kIgnoreCase.
			(kDefaultCompare is what VW uses internally to compare names - currently it is equal to kIgnoreCase.)
		*/

	extern "C" CBBoolean GS_CALLBACK GS_CStringEqual(CallBackPtr, ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags);
		/*
			Returns true if the C strings cStr1 and cStr2 are equal, false if they are not. The bit-flags
			compareFlags must be from EStringCompare, which currently has: kDefaultCompare, kIncludeCase,
			kIgnoreCase. (kDefaultCompare is what VW uses internally to compare names - currently it is equal to
			kIgnoreCase.)
		*/

	extern "C" void GS_CALLBACK GS_DisableModules(CallBackPtr, Sint32 modules);
		/*
			Disables modules.  The modules parameter is a bitfield indicating which modules to disable.
		*/

	extern "C" void GS_CALLBACK GS_DisplayContextHelpOfCurrentPlugin(CallBackPtr);
		/*
			This function will display the context help of the plug-in that is considered 'current'. This could
			be a command plug-in that has a dialog open, or a tool plug-in that is active.

		*/

	extern "C" Boolean GS_CALLBACK GS_DisplayContextualHelp(CallBackPtr, const char* inIdentifier);
		/*
			Using the identifier string for a GUI element (tool, menu item, dialog) given by the Contextual Help
			Manager displays the associated contextual help. This could be a WebWorks webpage, a Internet
			webpage or even a local file.
		*/

	extern "C" void GS_CALLBACK GS_DisplayOrganizationDialog(CallBackPtr, short tabToSelect);
		/*
			Display the Organization dialog with the specified integer as the initially selected tab.
			0: The most recently displayed tab is selected
			1: The Classes tab is selected .
			2: The Design Layers tab is selected.
			3: The Sheet Layers tab is selected.
			4: The Viewports tab is selected.
			5: The Saved Views tab is selected.
		*/

	extern "C" short GS_CALLBACK GS_DoMenuName(CallBackPtr, const TXString& name, short chunkIndex);
		/*
			Executes the menu specified by name.  Calls menu items by the name of the external menu file or the
			name of the internal MITM resource. Using the file and resource names allows externals to work on
			any localized version of MiniCad.  If the name is a chunk, then the chunkIndex should be the number
			of the item in the chunk to execute.  If the item is not a chunk then 0 must be passed in
			chunkIndex.  DoMenuName can be called recursively.
		*/

	extern "C" Sint32 GS_CALLBACK GS_DoProgramAction(CallBackPtr, short actionSelector, void* actionEnv);
		/*
			Does program action.
		*/

	extern "C" void GS_CALLBACK GS_DoubleToString(CallBackPtr, TNumStyleClass inNumStyle,  Byte inAccuracy, Byte inFormat, double_param inDouble, TXString& outString);
		/*
			Converts a floating point number to a string that matches the current document's number formatting
			(fractional, decimal, etc.).
		*/

#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	extern "C" void GS_CALLBACK GS_DoUpdateOrActivate(CallBackPtr, EventRecord& theEvent);
		/*
			Allows an external to pass back update events to the main MiniCad event loop. It currently does not
			handle activate events correctly, but will in the future. It is intended to support movable modal
			dialogs in externals.
		*/
#endif

	extern "C" void GS_CALLBACK GS_DrawScreen(CallBackPtr, const ViewRect& clipRect, Boolean isLastFrame = true);
		/*
			Draws the entire database of objects visible on the screen.  This routine is used internally with
			the QuickTime external .  THis routine should not be used externally.
		*/

	extern "C" void GS_CALLBACK GS_EllipseEllipseIntersect(CallBackPtr, const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects);
		/*
			Returns the intersections between two ellipses in sects, which also contains information about which
			intersections are actually valid.
		*/

	extern "C" Sint32 GS_CALLBACK GS_ExternalNameToID(CallBackPtr, const TXString& fnName);
		/*
			This returns the ID of an external library file, allowing it to be called by the XCALL interface
			which takes an ID. It is faster than calling an external by file name.
		*/

	extern "C" short GS_CALLBACK GS_FontIndexFromName(CallBackPtr, const TXString& fontName);
		/*
			FontIndexFromName allows a file-specific font index to be looked up or assigned based on a font
			name. If the specified font has been used in the current document, then its index will be returned.
			If the font has never been used, then a new index will be returned. Once a font index has been
			assigned, it is guaranteed to remain fixed until the document is closed. The specified font must be
			present on the current system or the error index (-1) will be returned. If -1 is specified when
			assigning a font to an object in MiniCAD, the default system font will be used, so it's always legal
			to pass the result of this function to another SDK call to specify a font index.
		*/

	extern "C" void GS_CALLBACK GS_FontNameFromIndex(CallBackPtr, short fontIndex, TXString& fontName, Boolean useMappingTable);
		/*
			MiniCAD specifies fonts by an internal index which is specific to the active MiniCAD file.
			FontNameFromIndex allows the name of the font to be retrieved given an index. If useMappingTable is
			true, then the name of the font actually used to draw text on this system is returned. This takes
			the user's font mapping into account, and the font name returned will be present on your system, but
			may not correspond to the font originally specified for this object. If useMappingTable is false,
			then the name of the font originally assigned will be returned and there is a significant chance
			that the font will not be present on your system.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetActiveClassicSerialNumber(CallBackPtr, short inSerialNumberStyle, char* serialNumber);
		/*
			Gets the currently active serial number.  The inSerialNumberStyle parameter must be one of two
			numbers:
			  0 for VectorWorks
			  1 for RenderWorks

			The serial number buffer is supplied by the calling function, which must be large enough to hold the
			resulting serial number.
		*/

	extern "C" void GS_CALLBACK GS_GetActiveSerialNumber(CallBackPtr, char* serialNumber);
		/*
			Gets the currently active serial number.  The serial number buffer is supplied by the calling
			function, which must be large enough to hold the resulting serial number.
		*/

	extern "C" Boolean GS_CALLBACK GS_GetCallBackInval(CallBackPtr);
		/*
			Returns whether callbacks are invalidating portions of the screen that are being changed.
		*/

	extern "C" short GS_CALLBACK GS_GetCurrentMode(CallBackPtr);
		/*
			Returns the current mode.
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetDataBarCursorVisState(CallBackPtr);
		/*
			Returns the visibility states of the data bar cursors: -1 undefined, 0 primary, 1 primary &
			secondary, 2 show all
		*/

	extern "C" Sint32 GS_CALLBACK GS_GetEnabledModules(CallBackPtr);
		/*
			Returns a bitfield indicating which modules are enabled.
		*/

	extern "C" void GS_CALLBACK GS_GetHostInfo(CallBackPtr, short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& productName, TXString& productVersion);
		/*
			This returns info about the application hosting the external. hostID is set to a constant
			identifying kMiniCad or kBlueprint defined in MiniCadHookIntf.h. version, majorRev, & minorRev
			correspond to 5, 0, & 1 in MiniCad 5.0.1. 
		*/

	extern "C" void GS_CALLBACK GS_GetModifierFlags(CallBackPtr, Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag);
		/*
			Returns the current state of the modifier keys.
		*/

	extern "C" void GS_CALLBACK GS_GetProduct(CallBackPtr, short& product, Sint32& modules);
		/*
			Retrieves information that identifies what vertical market product (if any) is currently running,
			and which add-ons (modules) are currently available (if any).
		*/

	extern "C" Boolean GS_CALLBACK GS_GetSavedSetting(CallBackPtr, const TXString& category, const TXString& setting, TXString& value);
		/*
			Read a value from the saved settings file. 
		*/

	extern "C" void GS_CALLBACK GS_HandlePendingUpdatesAndActivates(CallBackPtr);
		/*
			HandlePendingUpdatesAndActivates searches the event queue and processes any update or activate
			events intended for MiniCad windows. This can be called after a dialog obscures the screen in order
			to avoid a temporary 'white hole' in the middle of the screen.
		*/

	extern "C" void GS_CALLBACK GS_HilitePalettesAndTopDocument(CallBackPtr, Boolean doHilite);
		/*
			This makes sure windows are deactivated behind dialogs - DO NOT USE THIS: It is currently broken and
			it may be deleted if we find it too difficult to fix properly.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_IntersectObjects(CallBackPtr, MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs);
		/*
			Returns a handle of CoordPts which indicate all of the intersections between the two objects.  If
			onlyOnObjs is true, then only intersections that actually lie on both objects are returned.  The
			returned intersection handle must be disposed after using.
		*/

	extern "C" Boolean GS_CALLBACK GS_Kludge(CallBackPtr, short selector, void* in, void* out);
		/*
			Internal use only
		*/

	extern "C" void GS_CALLBACK GS_LineEllipseIntersect(CallBackPtr, const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects);
		/*
			Calculates the intersection between the two lines specified.  Parallel is set if no intersection
			could be found because the lines are parallel.  intOnLine is set if the intersection is between the
			endpoints of both lines.
		*/

	extern "C" void GS_CALLBACK GS_LineLineIntersect(CallBackPtr, const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect);
		/*
			Calculates the intersection between the two lines specified.  Parallel is set if no intersection
			could be found because the lines are parallel.  intOnLine is set if the intersection is between the
			endpoints of both lines.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_ObjectNearCoordPt(CallBackPtr, const WorldPt& p);
		/*
			Returns the object that the point p is currently over.  If no objects are near the point then nil is
			returned.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_PlaySoundResource(CallBackPtr, Handle soundResource, CBBoolean async, CBBoolean forcePlay);
		/*
			Plays a sound resource. Set async true to play the sound asynchronously, or false to play the sound
			synchronously. Set forcePlay true to ignore the Use Sound preference. Set forcePlay false to observe
			the Use Sound preference.
		*/

	extern "C" Boolean GS_CALLBACK GS_PointInsidePoly(CallBackPtr, const WorldPt& checkPt, MCObjectHandle h);
		/*
			Returns true if theObject is a polyNode or curveNode and checkpt is inside of the polygon object. 
			Polyline objects are converted to polygons.

		*/

	extern "C" Boolean GS_CALLBACK GS_PointOnPolyEdge(CallBackPtr, const WorldPt& checkPt, MCObjectHandle h, WorldCoord checkRadius);
		/*
			Returns true if h is a polyNode, curveNode or polylineNode and checkpt is within checkRadius of the
			edge of the polygon object.  Polyline objects are converted to polygons.
		*/

	extern "C" Sint32 GS_CALLBACK GS_RegisterExternal(CallBackPtr, const TXString& fileName, short codeResID, OSType codeResType);
		/*
			This registers an external code resource so that it can be called from another external. The
			codeResID & codeResType fields specify which resource contains the main code segment. It returns the
			ID by which the code segment can be called. NOTE: do not register files with a file type of 'XCOD'
			as they are registered automatically at startup. they will always use XCOD 50 resources as the main
			code segment.
		*/

	extern "C" Boolean GS_CALLBACK GS_RegisterNotificationProcedure(CallBackPtr, StatusProcPtr proc, OSType whichChange);
		/*
			Registers the procedure passed in the first parameter with the VectorWorks gNotification object.
			When an internal event matching that specified by the whichChange parameter occurs, the registered
			procedure will be called and can take appropriate action. See MCNotify.h for notification constants
			which can be used with this system.
		*/

	extern "C" void GS_CALLBACK GS_SetCallBackInval(CallBackPtr, Boolean turnInvalOn);
		/*
			Sets whether or not callbacks should be invalidating portions of the screen that are being changed.
			This should be used if you need to create temporary objects for calculation purposes and do not want
			the screen to be redrawn as a result.

			Note: as of version 9.0, SetCallBackInval now also turns worksheet and worksheet image updating on
			and off. Use ResetObject to force a redraw of a worksheet or worksheet image.
		*/

	extern "C" void GS_CALLBACK GS_SetPersistentHighlight(CallBackPtr, MCObjectHandle theObject, Boolean highlightState);
		/*
			SetPersistentHighlight is the interface for a global persistent object highlighting system which
			allows a single object to be highlighted in a manner similar to, but more transient than object
			selection. When highlighted by calling this function with a true value in hilightState, the object
			will be drawn in or surrounded by a bold pen stroke. If an object is highlighted using this call and
			the drawing is refreshed for any reason, the highlight state will be properly maintained until it is
			eventually removed by calling this function again with a false value passed in hilightState. A
			plug-in must remove any hilight state it applies to an object before it returns control to
			VectorWorks.
		*/

	extern "C" void GS_CALLBACK GS_SetSavedSetting(CallBackPtr, const TXString& category, const TXString& setting, const TXString& value);
		/*
			Writes a value to the saved settings file.  
		*/

	extern "C" Boolean GS_CALLBACK GS_StringToAngleN(CallBackPtr, const TXString& s, double_gs& angle);
		/*
			Convert between an angle string and a number of degrees.  StringToAngle will accept degrees,
			minutes, and seconds or decimal degrees (or no explicit angle units; this is presumed to be degrees).
		*/

	extern "C" Boolean GS_CALLBACK GS_StringToDouble(CallBackPtr, TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble);
		/*
			Parses the inString based on inNumStyle, performs any math operations, and returns a real value in
			outDouble. Returns false if there is an error in parsing the string.
		*/

	extern "C" Boolean GS_CALLBACK GS_SymbolContainsLight(CallBackPtr, MCObjectHandle symbol);
		/*
			Returns true if definition of symbol contains at least one light node.
		*/

	extern "C" void GS_CALLBACK GS_ToggleObjectHighlight(CallBackPtr, MCObjectHandle theObject);
		/*
			Similar to SetPersistentHighlight, but this call simply draws or removes the highlight from the
			specified object. Exclusive Or drawing is used, so each call will toggle the highlight state to its
			opposite.
		*/

	extern "C" void GS_CALLBACK GS_UnregisterNotificationProcedure(CallBackPtr, StatusProcPtr proc, OSType whichChange);
		/*
			Unregisters a notification procedure previously registered by RegisterProcedureForCallback. This
			MUST be done before the setDown message or the application will crash when the next notification is
			sent to your plug-in.
		*/

	extern "C" Boolean GS_CALLBACK GS_VerifyPluginLibrary(CallBackPtr, const TXString& routineName);
		/*
			Verify that a particular SDK Plug-in Library Routine is currently installed and available.  
		*/



///////////////////////////////////////////
//  View Manipulation
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_GetPerspectiveInfo(CallBackPtr, MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect);
		/*
			Returns info from the specified layer regarding perspective projection parameters.
		*/

	extern "C" short GS_CALLBACK GS_GetProjection(CallBackPtr, MCObjectHandle theLayer);
		/*
			Returns the projection index from the specified layer.
		*/

	extern "C" short GS_CALLBACK GS_GetRenderMode(CallBackPtr, MCObjectHandle theLayer);
		/*
			Returns the render mode index from the specified layer.
		*/

	extern "C" short GS_CALLBACK GS_GetScreenDPI(CallBackPtr);
		/*
			Returns the screen resolution used by MiniCAD to map page inches to the pixels on the screen. This
			value represents both horizontal and vertical resolution, as MiniCAD does not support systems
			without rectangular pixels.
		*/

	extern "C" void GS_CALLBACK GS_GetViewCenter(CallBackPtr, WorldPt& center);
		/*
			Returns the CoordPt which is in the center of the current view.
		*/

	extern "C" void GS_CALLBACK GS_GetViewMatrix(CallBackPtr, MCObjectHandle theLayer, TransformMatrix& theMat);
		/*
			Returns the view matrix from the specified layer.
		*/

	extern "C" void GS_CALLBACK GS_GetWorkingPlane(CallBackPtr, Axis &theAxis);
		/*
			Gets the current working plane.
		*/

	extern "C" void GS_CALLBACK GS_NewCurrentViewMatrix(CallBackPtr, const TransformMatrix& theMat, Boolean interactive);
		/*
			Fully handles a change in the current view matrix, including updating the active layer's
			information, asking the user to re-render, and invalidating the screen.
		*/

	extern "C" void GS_CALLBACK GS_NewWorkingPlane(CallBackPtr, const Axis &theAxis);
		/*
			Sets a new working plane.
		*/

	extern "C" void GS_CALLBACK GS_PreviewDrawFrame(CallBackPtr, Handle thisPreview, Boolean selectedOnly = false);
		/*
			This is a call for interactive rotation of 3D objects.  This call is used to produce behavior the
			user sees when using 3D view specification tools like walkthrough and flyover.  To use this service,
			first get the current view matrix with GetViewMatrix. Then create a preview with PreviewSetup. You
			can then repeatedly modify the matrix, call SetViewMatrix and call PreviewDrawFrame in a loop until
			the desired view is chosen. The view change would typically respond to input from the user, but
			QuickTime export uses the same calls to display animation previews. You must then call
			PreviewFinish, and if you want to permanently alter the view, you must call NewCurrentViewMatrix to
			set the new view. 
		*/

	extern "C" void GS_CALLBACK GS_PreviewFinish(CallBackPtr, Handle& thisPreview);
		/*
			completes the preview
		*/

	extern "C" Handle GS_CALLBACK GS_PreviewSetup(CallBackPtr, Boolean doDynamicSpeedups = true, double_param targetFPS = 0.0, Boolean drawGroundPlane = true, Boolean drawPage = true, Boolean drawCropRect = true);
		/*
			This is the setup call for a set of routines supporting interactive rotation of 3D objects.  This is
			the behavior the user sees when using 3D view specification tools like walkthrough and flyover.  To
			use this service, first get the current view matrix with GetViewMatrix. Then create a preview with
			PreviewSetup. You can then repeatedly modify the matrix, call SetViewMatrix and call
			PreviewDrawFrame in a loop until the desired view is chosen. The view change would typically respond
			to input from the user, but QuickTime export uses the same calls to display animation previews. You
			must then call PreviewFinish, and if you want to permanently alter the view, you must call
			NewCurrentViewMatrix to set the new view. 

		*/

	extern "C" void GS_CALLBACK GS_RedrawRect(CallBackPtr, const WorldRect& redrawR);
		/*
			Immediately redraws the rectangle specified by redrawR.
		*/

	extern "C" void GS_CALLBACK GS_SetViewCenter(CallBackPtr, const WorldPt& center);
		/*
			Centers the view on the specified point.
		*/

	extern "C" void GS_CALLBACK GS_SetViewMatrix(CallBackPtr, MCObjectHandle theLayer, const TransformMatrix& theMatrix);
		/*
			A low-level routin that sets the view matrix of the specified layer to theMatrix.  This does not
			handle other factors involved with changing the view such as redrawing, re-rendering, etc.
		*/

	extern "C" void GS_CALLBACK GS_SetWorkingPlaneAxis(CallBackPtr, const Vector &si, const Vector &sj, const Vector &sk);
		/*
			Sets the working plane orientation, leaving its origin at the same point.
		*/

	extern "C" void GS_CALLBACK GS_SetWorkingPlaneVertex(CallBackPtr, const WorldPt3 &v);
		/*
			Sets the working plane origin, leaving its orientation as it was.
		*/

	extern "C" void GS_CALLBACK GS_SetZoomFactorN(CallBackPtr, double_param zoomFac);
		/*
			Sets the view to be a factor of normal scale.  SetZoomFactor(2.0) corresponds to 200% in the readout
			in the data display bar. SetZoomFactor(0.5) corresponds to 50%.
		*/

	extern "C" void GS_CALLBACK GS_ViewRotWorldZN(CallBackPtr, double_param angle, Boolean interactive);


	extern "C" Boolean GS_CALLBACK GS_WorldRect2ViewRect(CallBackPtr, const WorldRect& wRect, ViewRect& vRect);
		/*
			Convert a rect from world space to view space. 
		*/



///////////////////////////////////////////
//  Walls
///////////////////////////////////////////


	extern "C" short GS_CALLBACK GS_AddBreak(CallBackPtr, MCObjectHandle theWall, WorldCoord off, short breakType, void* breakData);
		/*
			Adds a break with the specified parameters to theWall.  The index of the new break is returned by
			the function.
		*/

	extern "C" void GS_CALLBACK GS_DeleteBreak(CallBackPtr, MCObjectHandle theWall, short index);
		/*
			Deletes the break specified.
		*/

	extern "C" void GS_CALLBACK GS_ForEachBreak(CallBackPtr cbp, MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv);
		/*
			typedef Boolean (*ForEachBreakProcPtr)(Handle h, Sint32 index, Coord off, Sint32 breakType, void*
			breakData, CallBackPtr cbp, void* env);

			Steps through each break in a wall and calls the action procedure until all breaks have been passed
			or true is returned from the action procedure.  off is the distance along the Wall, starting at the
			first point, that the break lies.  Depending upon the breakType, breakData can point to one of the
			following records: SymbolBreakType, HalfBreakType, CapBreakType, or PeakBreakType.
		*/

	extern "C" WorldCoord GS_CALLBACK GS_GetLayerDeltaZOffset(CallBackPtr, MCObjectHandle theWall);
		/*
			Gets theWall's layer delta Z offset.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_GetLinkHeightToLayerDeltaZ(CallBackPtr, MCObjectHandle theWall);
		/*
			Gets whether or not the height of theWall is linked to the layer delta Z.
		*/

	extern "C" void GS_CALLBACK GS_GetPolyBreakGeometry(CallBackPtr, MCObjectHandle theWall, short breakIndex, MCObjectHandle& polyline);
		/*
			If the break, in theWall at the specified break index,  references a polyBreak object then a copy of
			the polybreak is converted into a polyline object. The Caller is responsible for deleting the
			returned polyline (use GS_DeleteObject w/ undo = false)

		*/

	extern "C" void GS_CALLBACK GS_GetWallCaps(CallBackPtr, MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round);
		/*
			Gets whether or not theWall has a left cap and right cap, as well as whether or not the caps are
			round.
		*/

	extern "C" void GS_CALLBACK GS_GetWallCapsOffsets(CallBackPtr, MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset);
		/*
			Gets theWall's cap offsets.
		*/

	extern "C" void GS_CALLBACK GS_GetWallHeights(CallBackPtr, MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom);
		/*
			Gets the heights of the start and end of the specified wall.  The distances are measured from the
			ground plane on the layer in which the wall exists.
		*/

	extern "C" Boolean GS_CALLBACK GS_JoinWalls(CallBackPtr, MCObjectHandle firstWall, MCObjectHandle secondWall,  const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, Boolean capped, Boolean showAlerts);
		/*
			This function provides an interface to the wall join tool. Input two walls and a point on each wall,
			specify a join type, and set the capped flag. 

			Join Modifier Types:  kTWallJoin, kLWallJoin, kXWallJoin, kAutoWallJoin, kAutoLWallJoin

		*/

	extern "C" void GS_CALLBACK GS_MoveWallByOffset(CallBackPtr, MCObjectHandle theWall, WorldCoord& offset);
		/*
			Available in VW Architect only. Moves the wall perpendiclar to its definition line by the specified
			offset, and maintains all wall connections Offsets to the left hand side of the wall are positive,
			and to the right hand side are negative. 
		*/

	extern "C" void GS_CALLBACK GS_ReverseWallSides(CallBackPtr, MCObjectHandle theWall);
		/*
			Switch the left and right side of a wall by reversing the direction of the wall.  This is an
			interface to the button with the same name on the Object Info palette.
		*/

	extern "C" void GS_CALLBACK GS_SetAsPolyBreak(CallBackPtr, MCObjectHandle& thePolyline, MCObjectHandle theWall, short breakIndex);
		/*
			Available in VW Architect only. Takes the given polyline and uses it to set a polybreak at the given
			breakIndex. The polyline object is converted to a polyBreak object and placed in the wall aux list. 
			The input polyline must be a stand alone object (not in the drawing or any other list)

		*/

	extern "C" void GS_CALLBACK GS_SetBreak(CallBackPtr, MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData);
		/*
			Sets the break, specified by index, to the break information specified.  When  breakType ==
			kSymbolBreak, a duplicate of the symbol handle contained in the breakData paramater is inserted and
			the handle pointed to by breakData is updated with the handle to the new symbol. If the original
			symbol was already in the wall, you should NOT dereference any handles to that symbol because it
			will be deleted by the next call to ResetWall. 

			To change the break of an existing symbol without duplicating that symbol, set the symbol handle in
			breakData to nil prior to calling SetBreak. This will copy all of the passed in break data,
			including the offset, into the break but will not create a new symbol instance. 


		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetLayerDeltaZOffset(CallBackPtr, MCObjectHandle theWall, WorldCoord layerDeltaZOffset);
		/*
			Sets theWall's layer delta Z offset.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetLinkHeightToLayerDeltaZ(CallBackPtr, MCObjectHandle theWall, CBBoolean linkToLayerDeltaZ);
		/*
			Sets whether or not the height of theWall is linked to the layer delta Z.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetWallCaps(CallBackPtr, MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round);
		/*
			Sets whether or not theWall has a left cap and right cap, as well as whether or not the caps are
			round.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetWallCapsOffsets(CallBackPtr, MCObjectHandle theWall, WorldCoord leftCapLeftOffset, WorldCoord leftCapRightOffset, WorldCoord rightCapLeftOffset, WorldCoord rightCapRightOffset);
		/*
			Sets theWall's cap offsets.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetWallHeights(CallBackPtr, MCObjectHandle theWall, WorldCoord startHeightTop, WorldCoord startHeightBottom, WorldCoord endHeightTop, WorldCoord endHeightBottom);
		/*
			Sets the heights of the start and end of the specified wall.  The distances are measured from the
			ground plane on the layer in which the wall exists.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetWallStyle(CallBackPtr, MCObjectHandle theWall, InternalIndex wallStyle, WorldCoord selectedOffset, WorldCoord replacingOffset);
		/*
			Sets the Wall Style of theWall based on the given offsets.
		*/

	extern "C" CBBoolean GS_CALLBACK GS_SetWallWidth(CallBackPtr, MCObjectHandle theWall, WorldCoord newWidth);
		/*
			Sets theWall to the width specified.  Must be followed by a call to ResetObject to reconstruct the
			wall with the new width.
		*/

	extern "C" void GS_CALLBACK GS_WrapGetWallWidth(CallBackPtr, MCObjectHandle theWall, double_gs& outCoordLen);
		/*
			TEMPORARY wrapper procedure around PageLengthToCoordLengthN function to avoid illegal return type of
			Coord. See Jeff Koppi.
		*/



///////////////////////////////////////////
//  Windows
///////////////////////////////////////////


	extern "C" Boolean GS_CALLBACK GS_GetScreenSize(CallBackPtr, ViewRect& screenRect);
		/*
			screenRect returns with the QuickDraw ViewRect corresponding to the active document's visible drawing,
			that to the right of and below the rulers, and to the left of and above the scroll bars.
		*/


#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" void GS_CALLBACK GS_EnterMoveableWindow(CallBackPtr, HWND hDialog);
		/*
			Ensure MiniCad windows and palettes are properly updated when a Windows dialog box is displayed. For
			backwards compatibility, passing NULL is allowed but not recommended. This call must have a matching
			call to ExitMoveableWindow. Pass the handle to the dialog being dispalyed. Usually called from the
			dialog's WM_CREATE or WM_INITDIALOG message handler. You can avoid having to call this function by
			deriving your MFC dialog from TGSDialog instead of CDialog.
			(For Windows based builds only)
		*/
#endif

#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" void GS_CALLBACK GS_ExitMoveableWindow(CallBackPtr, HWND hDialog);
		/*
			Ensure VectorWorks windows and palettes are properly updated when a Windows dialog box is displayed.
			Pass the handle to the dialog being destroyed. For backwards compatibility, passing NULL is allowed
			but not recommended. This call must have a matching call to EnterMoveableWindow. Usually called from
			the dialog's WM_DESTROY message handler. You can avoid having to call this function by deriving your
			MFC dialog from TGSDialog instead of CDialog.
			(For Windows based builds only)
		*/
#endif


#if _WINDOWS && defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
	extern "C" HWND GS_CALLBACK GS_GetMainHWND(CallBackPtr);
		/*
			Gets the Windows HWND (window handle) associated with the MiniCad application.
			(For Windows MFC-based builds only)

		*/
#endif


///////////////////////////////////////////
//  Worksheets
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_AutoFitWorksheetRowHeights(CallBackPtr, MCObjectHandle worksheet, short fromRow, short toRow);
		/*
			Auto fit the height for the specified worksheet rows to the content of the cells.
		*/

	extern "C" void GS_CALLBACK GS_ClearWorksheetCells(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		/*
			Clears contents and attributes from specified worksheet cells.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateWorksheet(CallBackPtr, const InternalName& name, short rows, short columns);
		/*
			Creates a new worksheet object with the specified name and number of rows and columns.
			If the name is in use, a legal available name based on the specified name will be used instead.
			The number of rows must be >= 1 and <= 4094.
			The number of columns must be >= 1 and <= 256.
			NOTE: To create an on-drawing worksheet object, pass a worksheet handle to CreateWorksheetImage.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_CreateWorksheetImage(CallBackPtr, MCObjectHandle worksheet, const WorldPt& topLeftCorner);
		/*
			Creates an on_drawing object (image) of the specified worksheet with the created worksheet image's
			top left corner located at the specified point.
		*/

	extern "C" void GS_CALLBACK GS_DeleteWorksheetColumns(CallBackPtr, MCObjectHandle worksheet, short startColumn, short numColumns);
		/*
			Deletes the specified number of worksheet columns starting with the specified start column.
		*/

	extern "C" void GS_CALLBACK GS_DeleteWorksheetRows(CallBackPtr, MCObjectHandle worksheet, short startRow, short numRows);
		/*
			Deletes the specified number of worksheet rows starting with the specified start row.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetTopVisibleWorksheet(CallBackPtr);
		/*
			Returns handle to topmost visible worksheet.
		*/

	extern "C" void GS_CALLBACK GS_GetWkSheetSubrowCellActualString(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow, TXString& cellString);
		/*
			Gets the specified worksheet subrow cell's actual string.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellAlignment(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment);
		/*
			Gets the specified worksheet cell's horizontal alignment.

			Horizontal alignment constants:
			kTextGeneralJustify  = 0
			kTextLeftJustify           = 1
			kTextCenterJustify    = 2
			kTextRightJustify       = 3

		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellBorder(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right);
		/*
			Gets the specified worksheet cell's border.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellFill(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern);
		/*
			Gets the specified cell's fill style and color

			Fill style constants:
			0 for NO FILL, 1 for SOLID FILL , 2 for PATTERN FILL


		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellFormula(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, TXString& formula);
		/*
			Gets the specified worksheet cell's formula.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellNumberFormat(CallBackPtr, 
		MCObjectHandle worksheet, const ViewPt& cell, short& style, short& accuracy, 
		TXString & leaderString, TXString & trailerString);
		/*
			Gets the specified worksheet cell's number format.

			Number Format constants:
			name                          value                meaning of accuracy
			nsGeneral                   = 0
			nsFixDecimal            = 1                       number of decimal places
			nsDecwCommas    = 2                      number of decimal places
			nsScientific               = 3                       number of decimal places
			nsFractional              = 4                       largest displayed denominator
			nsDimension            = 5                       
			nsAngle                      = 6                       corresponds to angular accuracy in units
			dialog
			nsDate                         = 7                       
			nsConditonal           = 8
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellString(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, TXString& cellString);
		/*
			Gets the specified worksheet cell's displayed string.
			If the cell contains a string, the displayed string IS that string.
			If the cell contains a number, the displayed string is that number PLUS any formatting applied to
			that number.
			Use IsWorksheetCellString and/or MP_IsWSCellNumber to determine what type of value the cell actually
			contains. 
			Use GetWorksheetCellValue to retrieve actual numerical value without  formatting from a cell that
			contains a number.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellTextFormat(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style);
		/*
			Gets the specified worksheet cell's text format.

			Text Format (style) constants:
			kTextStylePlain               = 0
			kTextStyleBold               = 1
			kTextStyleItalic                = 2
			kTextStyleUnderline    = 4
			kTextStyleOutline         = 8
			kTextStyleShadow       = 16

			Note: Outline and Shadow only display on the Mac
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellTextAngle(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short& angle);
		/*
			Gets the specified worksheet cell's text angle.


		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellTextColor(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color);
		/*
			Gets the specified cell's text color.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellValue(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, double& cellValue);
		/*
			Gets the specified worksheet cell's numerical value.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellVertAlignment(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment);
		/*
			Gets the specified worksheet cell's vertical alignment.

			Vertical alignment constants:
			kTextTopBox = 1
			kTextCenterBox = 3
			kTextBottomBox = 5

		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetCellWrapTextFlag(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag);
		/*
			Gets the specified worksheet cell's wrap text state.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetColumnOperators(CallBackPtr, MCObjectHandle worksheet, short databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3);
		/*
			Gets the specified worksheet database row's column operators.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetColumnWidth(CallBackPtr, MCObjectHandle worksheet, short column, short& width);
		/*
			Gets the specified worksheet column's width.
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetWorksheetFromImage(CallBackPtr, MCObjectHandle worksheetImage);
		/*
			Returns the worksheet associated with the specified worksheet on-drawing object (image).
		*/

	extern "C" MCObjectHandle GS_CALLBACK GS_GetWorksheetImage(CallBackPtr, MCObjectHandle worksheet);
		/*
			Gets the handle to the specified worksheet's on-drawing object (image).
		*/

	extern "C" Boolean GS_CALLBACK GS_GetWorksheetMergedCellRange(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell);
		/*
			Gets the range of cell covered by the specified cell and return true if the specified cell is a
			merged cell.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetPlacement(CallBackPtr, MCObjectHandle worksheet, ViewRect& windowPosition);
		/*
			Retrieves the specified worksheet's window position.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetRowColumnCount(CallBackPtr, MCObjectHandle worksheet, short& numRows, short& numColumns);
		/*
			Gets number of rows and columns in specified worksheet.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetRowHeight(CallBackPtr, MCObjectHandle worksheet, short row, short& height);
		/*
			Gets the specified worksheet row's height.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetRowHLockState(CallBackPtr, MCObjectHandle worksheet, short row, Boolean& lockState);
		/*
			Gets the specified worksheet row's height lock state
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetSelection(CallBackPtr, MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow);
		/*
			Gets the specified worksheet's selection.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetSubrowCellString(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short subrow, TXString& cellString);
		/*
			Gets the specified worksheet subrow cell's displayed string.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetSubrowCellValue(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short subrow, double& cellValue);
		/*
			Gets the specified worksheet subrow cell's numerical value.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" void GS_CALLBACK GS_GetWorksheetSubrowCount(CallBackPtr, MCObjectHandle worksheet, short databaseRow, short& numSubrows);
		/*
			Gets the number of subrows associated with the specified worksheet database row.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" void GS_CALLBACK GS_InsertWorksheetColumns(CallBackPtr, MCObjectHandle worksheet, short beforeColumn, short numColumns);
		/*
			Inserts the specified number of worksheet columsn before the specified column.
		*/

	extern "C" void GS_CALLBACK GS_InsertWorksheetRows(CallBackPtr, MCObjectHandle worksheet, short beforeRow, short numRows);
		/*
			Inserts the specified number of worksheet rows before the specified row.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsValidWorksheetCell(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell);
		/*
			Determines if specified cell is valid for the specified worksheet.
			NOTE: A determination that a cell is valid only means that the specified cell falls within a range
			of 0 to the current number of worksheet rows and 0 to the current number of worksheet columns. A
			valid cell does not imply that every worksheet SDK function will accept that cell. The user should
			always  note any specific cell and cell range restrictions of a call they may use.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsValidWorksheetRange(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		/*
			Determines if specified range is valid for the specified worksheet.
			NOTE: A determination that a range is valid only means that the specified range falls within a range
			of 0 to the current number of worksheet rows and 0 to the current number of worksheet columns. A
			valid range does not imply that every worksheet SDK function will accept that range. The user should
			always  note any specific cell and cell range restrictions of a call they may use.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsValidWorksheetSubrowCell(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short subrow);
		/*
			Determines if specified worksheet subrow cell is valid.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsWorksheetCellNumber(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell);
		/*
			Determines if the specified worksheet cell's contents is a numerical value.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsWorksheetCellString(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell);
		/*
			Determines if the specified worksheet cell's contents is a string value.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsWorksheetDatabaseRow(CallBackPtr, MCObjectHandle worksheet, short databaseRow);
		/*
			Determines if specified worksheet row is a database row.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsWorksheetSubrowCellNumber(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short subrow);
		/*
			Determines if the specified worksheet subrow cell's contents is a numerical value.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsWorksheetSubrowCellString(CallBackPtr, MCObjectHandle worksheet, const ViewPt& cell, short subrow);
		/*
			Determines if the specified worksheet subrow cell's contents is a string value.
			WARNING: Because database subrow cells and their contents are dynamically created based on the
			current database of objects and the current critieria string any return values from this function
			are not guaranteed to be correct beyond this function call. Use this function carefully and at your
			own risk.
		*/

	extern "C" Boolean GS_CALLBACK GS_IsWorksheetVisible(CallBackPtr, MCObjectHandle worksheet);
		/*
			Determines if specified worksheet is currently visible (being shown).
		*/

	extern "C" void GS_CALLBACK GS_RecalculateWorksheet(CallBackPtr, MCObjectHandle worksheet);
		/*
			Recalculates all formulas for the specified worksheet.
		*/

	extern "C" void GS_CALLBACK GS_SetTopVisibleWorksheet(CallBackPtr, MCObjectHandle worksheet);
		/*
			Sets specified visible worksheet to be topmost.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellAlignment(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short cellAlignment);
		/*
			Sets specified horizontal alignment in specifed worksheet cells.

			Horizontal alignment constants:
			kTextGeneralJustify  = 0
			kTextLeftJustify           = 1
			kTextCenterJustify    = 2
			kTextRightJustify       = 3
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellBorder(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline);
		/*
			Sets the specified border for the specified worksheet cells.

			OBSOLETE for Version 12: see new SetWorksheetCellBorders. [HOT 07/12/05]
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellBorders(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline, Boolean insideHorz, Boolean insideVert);
		/*
			Sets the specified border for the specified worksheet cells.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellFill(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, ColorRef bgcolor, ColorRef fgcolor, short fillpattern);
		/*
			Sets specified fill style and color in specifed worksheet cells.

			Fill style constants:
			0 for NO FILL, 1 for SOLID FILL , 2 for PATTERN FILL
			bgcolor - cell background color  (0 if none)
			fgcolor	- cell foreground color   (0 if none)
			fillpattern - cell fill pattern index  (-1 if none)
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellFormula(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula);
		/*
			Sets specified formula string in specified worksheet cell(s).
			If the 0 column is specified, a database row is created and the formula set as the database row
			criteria.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellNumberFormat(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, short accuracy, const TXString& leaderString, const TXString& trailerString);
		/*
			Sets the specified number format for the specified worksheet cells.

			Number Format constants:
			name                          value                meaning of accuracy
			nsGeneral                   = 0
			nsFixDecimal            = 1                       number of decimal places
			nsDecwCommas    = 2                      number of decimal places
			nsScientific               = 3                       number of decimal places
			nsFractional              = 4                       largest displayed denominator
			nsDimension            = 5                       
			nsAngle                      = 6                       corresponds to angular accuracy in units
			dialog
			nsDate                         = 7                       
			nsConditonal           = 8
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellTextFormat(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short fontIndex, short size, short style);
		/*
			Sets the specified text format for the specified worksheet cells.

			Text Format (style) constants:
			kTextStylePlain               = 0
			kTextStyleBold               = 1
			kTextStyleItalic                = 2
			kTextStyleUnderline    = 4
			kTextStyleOutline         = 8
			kTextStyleShadow       = 16

			Note: Outline and Shadow only display on the Mac
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellTextAngle(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short angle);
		/*
			Sets specified text angle in specifed worksheet cells.

			Note:
			VW12 supports only horizontal text (0 degree) and vertical text (90 degrees). So, the input of any
			angle different from 0 will be handled as 90 degrees in VW12.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellTextColor(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color);
		/*
			Sets specified text color in specifed worksheet cells
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellVertAlignment(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short vAlignment);
		/*
			Sets specified vertical alignment in specifed worksheet cells.

			Vertical alignment constants:
			kTextTopBox = 1
			kTextCenterBox = 3
			kTextBottomBox = 5
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCellWrapTextFlag(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean wrapTextFlag);
		/*
			Sets specified wrap text state in specifed worksheet cells
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetColumnOperators(CallBackPtr, MCObjectHandle worksheet, short databaseRow, short sort1, short sort2, short sort3, short sum1, short sum2, short sum3);
		/*
			Sets the specified sort and summarize operators for the specified worksheet database row.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetColumnWidth(CallBackPtr, MCObjectHandle worksheet, short fromColumn, short toColumn, short width);
		/*
			Sets the specifed width for the specified worksheet columns.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetCurrentCell(CallBackPtr, MCObjectHandle worksheet, const ViewPt& currentCell);
		/*
			Sets the specified cell to be the worksheet's current cell. If specified cell is not contained
			within currently specified worksheet range, current selection is changed to single cell selection.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetPlacement(CallBackPtr, MCObjectHandle worksheet, const ViewRect& windowPosition);
		/*
			Sets the specified worksheet's window position.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetRowsHeight(CallBackPtr, MCObjectHandle worksheet, short fromRow, short toRow, short height, Boolean updatePalette, Boolean lockHeight);
		/*
			Sets the specifed height for the specified worksheet rows.

			Note:
			updatePalette - input - specifies whether or not to update the worksheet palette
			lockHeight	- input - specifies whether or not to lock the height for the specified rows.
					  If 'true' the height will be locked and the row will not automatically be resized when
			text is entered in a cell.
		*/

	extern "C" void GS_CALLBACK GS_SetWorksheetSelection(CallBackPtr, MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, short topRangeSubrow, const ViewPt& bottomRightRangeCell, short bottomRangeSubrow);
		/*
			Sets the selection for the specified visible worksheet.
		*/

	extern "C" void GS_CALLBACK GS_ShowWorksheet(CallBackPtr, MCObjectHandle worksheet, Boolean show);
		/*
			Shows/hides the specified worksheet.
		*/

	extern "C" void GS_CALLBACK GS_ShowWorksheetDialog(CallBackPtr, short dialogType);
		/*
			Displays the specified worksheet dialog for the topmost visible worksheet (if any). Worksheet
			dialogs that set attributes act on the worksheet's current selection.

			Dialogs constants:
			kWSColumnWidthDialog		= 0
			kWSCellBorderDialog			= 1
			kWSCellNumberFormatDialog		= 2
			kWSPreferencesDialog			= 3
			kWSPageSetupDialog			= 4
			kWSPrintDialog				= 5
			kWSFunctionDialog			= 6
			kWSCriteriaDialog			= 7
			kWSTextFormatDialog			= 8
			kWSSetRowCriteriaDialog		= 9
			kWSEditRowCriteriaDialog		= 10
		*/

	extern "C" Boolean GS_CALLBACK GS_WorksheetMergeCells(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		/*
			Merges the specifed worksheet cells into a single cell
		*/

	extern "C" Boolean GS_CALLBACK GS_WorksheetSplitCells(CallBackPtr, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		/*
			Splits the specifed worksheet cells back into individual cells.
		*/



///////////////////////////////////////////
//  Workspaces
///////////////////////////////////////////


	extern "C" void GS_CALLBACK GS_CloseResFile(CallBackPtr, short inFileID);
		/*
			This shall only be used to close files opened with OpenWorkspaceResFile and OpenExternalResFile.
		*/

	extern "C" void GS_CALLBACK GS_GetCurrentWorkspaceFile(CallBackPtr, TXString& outFileName);


	extern "C" short GS_CALLBACK GS_OpenExternalResFile(CallBackPtr, const TXString& inFileName, Byte fileAccessPerm = kFileReadWrite);


	extern "C" short GS_CALLBACK GS_OpenWorkspaceResFile(CallBackPtr, const TXString& inFileName, Boolean createNewFile = false, Byte fileAccessPerm = kFileReadWrite);


	extern "C" void GS_CALLBACK GS_SetWorkspaceFileToReload(CallBackPtr, const TXString& inFileName);


	extern "C" Boolean GS_CALLBACK GS_WSAddMenu(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName);
		/*
			Adds a new workspace to the referenced workspace file.
			@param inWorkspaceReference is a reference to the XML Workspace file..
			@param inMenuIdentifier the menu that we are adding to the workspace.
			@param inMenuName the name of the menu that we are adding.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSAddMenuItem(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, char inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier);
		/*
			Adds a new menu item definition to the master list of menu items in the referrenced workspace.

			@param inWorkspaceReference is a reference to the XML Workspace file..
			@param inMenuItemIdentifier the menu item that we are adding to the workspace.
			@param inMenuItemsUniversalName the name of the menu item that we are adding to the workspace.
			@param inShortcutKey the shortcut key to activate this menu item.
			@param inShortcutKeyModifiers the modifier keys that are used in combination with the shortcut key
			to activate this menu item.
			@param inSubMenuIdentifier the submenu that hangs off of this menu item.
			@return true if the operation was successful.

		*/

	extern "C" Boolean GS_CALLBACK GS_WSAddTool(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolIdentifier, char inShortcutKey, Uint32 inKeyModifiers);
		/*
			Adds a tool definition to the master list of tools within a workspace.

			@param inToolIdentifier the tool we are adding to the workspace.
			@param inShortcutKey the shortcut key to activate the tool.
			@param inKeyModifiers the shortcut key modifiers that are used in combination with the shortcut key
			to active this tool.
			@return true if the operation was successful.

		*/

	extern "C" Boolean GS_CALLBACK GS_WSAddToolPalette(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier);
		/*
			Add a tool palette definition to the referenced workspace.

			@param inToolPaletteIdentifier is the palette identifier to add to the workspace.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSAddToolSet(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize);
		/*
			@param inToolSetIdentifier the tool set we are adding to the workspace.
			@param inIconData the memory containing the icon data.
			@param inIconDataSize the size of the memory in inIconData.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSGetVersion(CallBackPtr, Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion);
		/*
			Gets the version of the referenced workspace.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSMenuAddMenuItem(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName);
		/*
			Adds a menu item reference to a menu in the referrenced workspace.

			@param inWorkspaceReference is a reference to the XML Workspace file..
			@param inMenuIdentifier the menu that we are adding a new menu item to.
			@param inMenuItemsUniversalName the universal name for this menu item.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSMenuBarAddMenu(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier);
		/*
			Adds a menu reference to the menu bar in the given workspace.

			@param inWorkspaceReference is a reference to the XML Workspace file..
			@param inMenuIdentifier the menu that we are adding to this workspace.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSOpen(CallBackPtr, const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference);
		/*
			Open a workspace file for reading or writing.
			@param inWorkspaceFileToWrite is a reference to the file that VectorWorks will create to store and
			or provide Workspace data.
			@param outWorkspaceReference will be a reference to an open Workspace file if the operation was
			successful.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSPaletteGetHomeCorner(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner);


	extern "C" Boolean GS_CALLBACK GS_WSPaletteSetHomeCorner(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, short inWindowHomeCorner);
		/*
			Sets the home corner for the given palette in the referenced workspace.

			@param inWorkspaceReference is a reference to the XML Workspace file..
			@param inPaletteIdentifier the palette's home corner (top-left, bottom-right, etc).
			@param inWindowHomeCorner this is actually the enumeration, EWindowHomeCorner.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSSetVersion(CallBackPtr, Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion);
		/*
			Sets the version number for the given workspace reference.

		*/

	extern "C" Boolean GS_CALLBACK GS_WSToolPaletteAddToolSet(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier);
		/*
			@param inWorkspaceReference is a reference to the XML Workspace file..
			@param inToolPaletteIdentifier the tool palette that we are adding a new tool set to.
			@param inToolSetIdentifier the new tool set we are adding to the tool palette.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSToolSetAddTool(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize);
		/*
			This function adds a tool reference to the tool set in the referenced workspace.

			@param inToolSetIdentifier the tool set we are adding to the workspace.
			@param inIconData the memory containing the icon data.
			@param inIconDataSize the size of the memory in inIconData.
			@return true if the operation was successful.
		*/

	extern "C" Boolean GS_CALLBACK GS_WSToolSetAddToolChildToTool(CallBackPtr, Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier);
		/*
			This function adds a sub-tool to a tool hierarchy in a tool set.

			@param inWorkspaceReference is a reference to the XML Workspace file.
			@param inToolSetIdentifier is the tool set we are interested in.
			@param inParentToolIdentifier is the parent tool that we are going to add a sub-tool to.
			@param inChildToolIdentifier is the new child tool we are adding to the list of tools in this
			collection.
			@return true if the operation was successful.
		*/

