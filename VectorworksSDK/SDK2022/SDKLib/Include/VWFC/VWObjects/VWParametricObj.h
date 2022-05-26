//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VW_PARAMETRIC_OBJECT__H
#define VW_PARAMETRIC_OBJECT__H

#pragma once

#include <unordered_map>

namespace VWFC
{
	using namespace Tools;
	
	namespace VWObjects
	{
		class VWParametricObj : public VWGroupObj
		{
		public:
								VWParametricObj(MCObjectHandle hParametric);
								VWParametricObj(const TXString& parametricName, const VWPoint2D& location, double angle = 0);
								VWParametricObj(const TXString& parametricName, MCObjectHandle hPathObject);
								VWParametricObj(const VWParametricObj& src);
			virtual				~VWParametricObj();

			VWParametricObj&	operator=(const VWParametricObj& src);
	
		public:
			void				GetObjectToWorldTransform(VWTransformMatrix& out) const;
			TXString			GetParametricName() const;
			TXString			GetLocalizedParametricName() const;
			MCObjectHandle		GetObjectPath() const;
			void				SetObjectPath(MCObjectHandle hPathGroup);
			MCObjectHandle		GetObjectProfileGroup() const;
			void				SetObjectProfileGroup(MCObjectHandle hProfileGroup);
			VWRecordFormatObj	GetRecordFormat() const;
			VWRecordObj			GetRecord() const;

			VWPoint2D			GetPointObjectPos() const;
			void				SetPointObjectPos(const VWPoint2D& pt);
			VWPoint3D			GetObjectModelPos() const;
			void				SetObjectModelPos( const VWPoint3D& pt );
			void				GetLinearObjectPos(VWPoint2D& outA, VWPoint2D& outB) const;
			void				SetLinearObjectPos(const VWPoint2D& a, const VWPoint2D& b);

			TInternalID			GetInternalID() const;

			void				AnalyzeAndUpdateTransformMatrix( bool & paramNeedsFlipping );
	
			ESymbolDefType		GetSymType() const;

		// parameters
		public:
			size_t				GetParamsCount() const;
			TXString			GetParamName(size_t paramIndex) const;
			TXString			GetParamLocalizedName(size_t paramIndex) const;
			// returns ((size_t) -1) if not found
			size_t				GetParamIndex(const TXString& paramName) const;

			// universal param name based
			EFieldStyle			GetParamStyle(const TXString& univParamName) const;
			TXString			GetParamValue(const TXString& univParamName) const;
			void				SetParamValue(const TXString& univParamName, const TXString& value);
			Sint32				GetParamLong(const TXString& univParamName) const;
			void				SetParamLong(const TXString& univParamName, Sint32 value);
			bool				GetParamBool(const TXString& univParamName) const;
			void				SetParamBool(const TXString& univParamName, bool value);
			double				GetParamReal(const TXString& univParamName) const;
			void				SetParamReal(const TXString& univParamName, double value);
			TXString			GetParamString(const TXString& univParamName) const;
			void				SetParamString(const TXString& univParamName, const TXString& value);
			InternalIndex		GetParamClass(const TXString& univParamName) const;
			void				SetParamClass(const TXString& univParamName, InternalIndex resource);
			InternalIndex		GetParamBuildingMaterial(const TXString& univParamName) const;
			void				SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource);
			VWPattern			GetParamFill(const TXString& univParamName) const;
			void				SetParamFill(const TXString& univParamName, const VWPattern& attr);
			VWPattern			GetParamPenStyle(const TXString& univParamName) const;
			void				SetParamPenStyle(const TXString& univParamName, const VWPattern& attr);
			Uint8				GetParamPenWeight(const TXString& univParamName) const;
			void				SetParamPenWeight(const TXString& univParamName, Uint8 value);
			ColorRef			GetParamColor(const TXString& univParamName) const;
			void				SetParamColor(const TXString& univParamName, ColorRef value);
			InternalIndex		GetParamTexture(const TXString& univParamName) const;
			void				SetParamTexture(const TXString& univParamName, InternalIndex resource);
			InternalIndex		GetParamSymDef(const TXString& univParamName) const;
			void				SetParamSymDef(const TXString& univParamName, InternalIndex resource);

			TXString			GetParamAsString( const TXString& univParamName) const;
			void				SetParamAsString(const TXString& univParamName, const TXString& value);

			VWPoint2D			GetParamCtrlPt(const TXString& univParamNameX) const;
			void				SetParamCtrlPt(const TXString& univParamNameX, const VWPoint2D& pt);

			// record centered popup choices support
			// these can be used to store a dynamic choice list for popup parameters inside the parametric record
			// then, most likely, you would want to use CWidgetsEditProvider::UpdatePopupWidgetChoices
			size_t				PopupGetChoicesCount(const TXString& univParamName) const;
			void				PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue) const;
			void				PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs) const;
			void				PopupClearChoices(const TXString& univParamName);
			void				PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append);

			// index based
			// NOTE: Recomended use of universal parameter name based (above) functions because they are safer
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			EFieldStyle			/*Use univParamName function instead*/	GetParamStyle(size_t paramIndex) const;
			TXString			/*Use univParamName function instead*/	GetParamValue(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamValue(size_t paramIndex, const TXString& value);
			Sint32				/*Use univParamName function instead*/	GetParamLong(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamLong(size_t paramIndex, Sint32 value);
			bool				/*Use univParamName function instead*/	GetParamBool(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamBool(size_t paramIndex, bool value);
			double				/*Use univParamName function instead*/	GetParamReal(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamReal(size_t paramIndex, double value);
			TXString			/*Use univParamName function instead*/	GetParamString(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamString(size_t paramIndex, const TXString& value);
			InternalIndex		/*Use univParamName function instead*/	GetParamClass(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamClass(size_t paramIndex, InternalIndex resource);
			InternalIndex		/*Use univParamName function instead*/	GetParamBuildingMaterial(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource);
			VWPattern			/*Use univParamName function instead*/	GetParamFill(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamFill(size_t paramIndex, const VWPattern& attr);
			VWPattern			/*Use univParamName function instead*/	GetParamPenStyle(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamPenStyle(size_t paramIndex, const VWPattern& attr);
			Uint8				/*Use univParamName function instead*/	GetParamPenWeight(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamPenWeight(size_t paramIndex, Uint8 value);
			ColorRef			/*Use univParamName function instead*/	GetParamColor(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamColor(size_t paramIndex, ColorRef value);
			InternalIndex		/*Use univParamName function instead*/	GetParamTexture(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamTexture(size_t paramIndex, InternalIndex resource);
			InternalIndex		/*Use univParamName function instead*/	GetParamSymDef(size_t paramIndex) const;
			void				/*Use univParamName function instead*/	SetParamSymDef(size_t paramIndex, InternalIndex resource);

			TXString	/*Use univParamName function instead*/	GetParamAsString(size_t paramIndex) const;
			void		/*Use univParamName function instead*/	SetParamAsString(size_t paramIndex, const TXString& value);

			size_t		/*Use univParamName function instead*/	PopupGetChoicesCount(size_t paramIndex) const;
			void		/*Use univParamName function instead*/	PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue) const;
			void		/*Use univParamName function instead*/	PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs) const;
			void		/*Use univParamName function instead*/	PopupClearChoices(size_t paramIndex);
			void		/*Use univParamName function instead*/	PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append);


			// obsolete functions
			void				EnableParameter_OBSOLETE(size_t paramIndex, bool bEnabled);
			void				SetParameterVisibility_OBSOLETE(size_t paramIndex, bool bVisible);

		// parameter tols
		public:
			void				SetControlPtVisibility(size_t ctrlPtIndex, bool bVisible);
			bool				GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const;
			bool				GetParamLocalizedChoices(size_t paramIndex, TXStringSTLArray& outArray) const;
			bool				GetParamLocalizedChoiceFromString(const TXString& paramName, const TXString& universalName, TXString& outLocalizedName) const;
	
		// object math
		public:
			double				Get2DRotation180() const;
			double				Get2DRotation360() const;

		// styles
			
			MCObjectHandle		GetStyleHandle() const;
			RefNumber			GetStyleRefNumber() const;


		// Tools
		public:
			// Return true if the specified object handle is layer
			static bool				IsParametricObject(MCObjectHandle hObj);
			static bool				IsParametricObject(MCObjectHandle hObj, const TXString& name);
			static bool				IsParametricObject(MCObjectHandle hObj, TInternalID internalID);
			template<typename... TInternalIDs>
			static inline bool		IsParametricObject(MCObjectHandle hObj, TInternalID ID, TInternalIDs... IDs)
			{
				return IsParametricObject( hObj ) && setmember( GetInternalID( hObj ), ID, IDs... );
			}
			static MCObjectHandle	DefineCustomObject(const TXString& name, bool bShowPrefs);
			static MCObjectHandle	GetRecordFormat(MCObjectHandle hParametric, MCObjectHandle hDefault=NULL);
			static MCObjectHandle	GetRecord(MCObjectHandle hParametric, MCObjectHandle hDefault=NULL);
			static TInternalID		GetInternalID(MCObjectHandle hParametric);

		protected:
			// this is constructor for inheritant of this class
			// so this class will not create a new parametric but let the inheritant do that job
								VWParametricObj( Sint32 );

			void				SetParametricHandle(MCObjectHandle hParametric);

		public:
			size_t				GetParamIndexByUnivName(const TXString& univParamName) const;

		protected:
			MCObjectHandle		fhParamRecord;
			MCObjectHandle		fhParamFormat;

			typedef std::unordered_map<TXString, size_t>		TUnviNameKeyMap;
			TUnviNameKeyMap		fmapUnivNameKey;
		};
	}
}

#endif // VW_PARAMETRIC_OBJECT__H
