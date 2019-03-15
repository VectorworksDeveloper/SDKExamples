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
			MCObjectHandle		GetObjectPath() const;
			void				SetObjectPath(MCObjectHandle hPathGroup);
			MCObjectHandle		GetObjectProfileGroup() const;
			void				SetObjectProfileGroup(MCObjectHandle hProfileGroup);
			VWRecordFormatObj	GetRecordFormat() const;
			VWRecordObj			GetRecord() const;

			VWPoint2D			GetPointObjectPos() const;
			void				SetPointObjectPos(const VWPoint2D& pt);
			void				GetLinearObjectPos(VWPoint2D& outA, VWPoint2D& outB) const;
			void				SetLinearObjectPos(const VWPoint2D& a, const VWPoint2D& b);

			TInternalID			GetInternalID() const;

			void				AnalyzeAndUpdateTransformMatrix( bool & paramNeedsFlipping );
	
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

			TXString			GetParamAsString( const TXString& univParamName) const;
			void				SetParamAsString(const TXString& univParamName, const TXString& value);

			VWPoint2D			GetParamCtrlPt(const TXString& univParamNameX);
			void				SetParamCtrlPt(const TXString& univParamNameX, const VWPoint2D& pt);

			// index based
			// NOTE: Recomended use of universal parameter name based (above) functions because they are safer
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			EFieldStyle	/*Use univParamName funcsion instead*/	GetParamStyle(size_t paramIndex) const;
			TXString	/*Use univParamName funcsion instead*/	GetParamValue(size_t paramIndex) const;
			void		/*Use univParamName funcsion instead*/	SetParamValue(size_t paramIndex, const TXString& value);
			Sint32		/*Use univParamName funcsion instead*/	GetParamLong(size_t paramIndex) const;
			void		/*Use univParamName funcsion instead*/	SetParamLong(size_t paramIndex, Sint32 value);
			bool		/*Use univParamName funcsion instead*/	GetParamBool(size_t paramIndex) const;
			void		/*Use univParamName funcsion instead*/	SetParamBool(size_t paramIndex, bool value);
			double		/*Use univParamName funcsion instead*/	GetParamReal(size_t paramIndex) const;
			void		/*Use univParamName funcsion instead*/	SetParamReal(size_t paramIndex, double value);
			TXString	/*Use univParamName funcsion instead*/	GetParamString(size_t paramIndex) const;
			void		/*Use univParamName funcsion instead*/	SetParamString(size_t paramIndex, const TXString& value);

			TXString	/*Use univParamName funcsion instead*/	GetParamAsString(size_t paramIndex) const;
			void		/*Use univParamName funcsion instead*/	SetParamAsString(size_t paramIndex, const TXString& value);


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
			
			MCObjectHandle		GetStyleHandle();
			RefNumber			GetStyleRefNumber();


		// Tools
		public:
			// Return true if the specified object handle is layer
			static bool				IsParametricObject(MCObjectHandle hObj);
			static bool				IsParametricObject(MCObjectHandle hObj, const TXString& name);
			static bool				IsParametricObject(MCObjectHandle hObj, TInternalID internalID);
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