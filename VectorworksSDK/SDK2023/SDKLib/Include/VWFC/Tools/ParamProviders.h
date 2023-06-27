//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

namespace VWFC
{
	using namespace VWObjects;
	using namespace Math;

	namespace Tools
	{
		// ----------------------------------------------------------------------------------------------------------------------------------
		class CParamProviderAbstract
		{
		public:
									CParamProviderAbstract();
			virtual					~CParamProviderAbstract();

		public:
            virtual MCObjectHandle  GetObject() const = 0;
            
			virtual Sint32			GetParamLong(const TXString& szParamName) const = 0;
			virtual void			SetParamLong(const TXString& szParamName, Sint32 value) = 0;
			virtual bool			GetParamBool(const TXString& szParamName) const = 0;
			virtual void			SetParamBool(const TXString& szParamName, bool value) = 0;
			virtual double			GetParamReal(const TXString& szParamName) const = 0;
			virtual void			SetParamReal(const TXString& szParamName, double value) = 0;
			virtual TXString		GetParamString(const TXString& szParamName) const = 0;
			virtual void			SetParamString(const TXString& szParamName, const TXString& value) = 0;
			virtual VWPoint2D		GetParamCtrlPt(const TXString& szParamXCoord) const = 0;
			virtual void			SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value) = 0;

			virtual InternalIndex	GetParamClass(const TXString& univParamName) const = 0;
			virtual void			SetParamClass(const TXString& univParamName, InternalIndex resource) = 0;
			virtual InternalIndex	GetParamBuildingMaterial(const TXString& univParamName) const = 0;
			virtual void			SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource) = 0;
			virtual VWPattern		GetParamFill(const TXString& univParamName) const = 0;
			virtual void			SetParamFill(const TXString& univParamName, const VWPattern& attr) = 0;
			virtual	VWPattern		GetParamPenStyle(const TXString& univParamName) const = 0;
			virtual void			SetParamPenStyle(const TXString& univParamName, const VWPattern& attr) = 0;
			virtual Uint8			GetParamPenWeight(const TXString& univParamName) const = 0;
			virtual void			SetParamPenWeight(const TXString& univParamName, Uint8 value) = 0;
			virtual ColorRef		GetParamColor(const TXString& univParamName) const = 0;
			virtual void			SetParamColor(const TXString& univParamName, ColorRef value) = 0;
			virtual InternalIndex	GetParamTexture(const TXString& univParamName) const = 0;
			virtual void			SetParamTexture(const TXString& univParamName, InternalIndex resource) = 0;
			virtual InternalIndex	GetParamSymDef(const TXString& univParamName) const = 0;
			virtual void			SetParamSymDef(const TXString& univParamName, InternalIndex resource) = 0;

			virtual TXString		GetParamValue(const TXString& szParamName) const = 0;
			virtual void			SetParamValue(const TXString& szParamName, const TXString& value) = 0;

			virtual size_t			GetParamsCount() const = 0;
			virtual EFieldStyle		GetParamStyle(const TXString& szParamName) const = 0;
			virtual size_t			GetParamIndex(const TXString& szParamName) const = 0;

			virtual TXString		GetParamName(size_t index) const = 0;

			// see the equivalent functiosn in VWParametricObj, and VWFormatRecordObj, VWRecordObj
			virtual size_t			PopupGetChoicesCount(const TXString& univParamName) = 0;
			virtual void			PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue) = 0;
			virtual void			PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs) = 0;
			virtual void			PopupClearChoices(const TXString& univParamName) = 0;
			virtual void			PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append) = 0;

		public:
			void					ProcessParameter(bool bRead, bool& inOutValue, bool oldValue, const TXString& szParamName);
			void					ProcessParameter(bool bRead, Uint32& inOutValue, Uint32 oldValue, const TXString& szParamName);
			void					ProcessParameter(bool bRead, Sint32& inOutValue, Uint32 oldValue, const TXString& szParamName);
			void					ProcessParameter(bool bRead, double& inOutValue, double oldValue, const TXString& szParamName);
			void					ProcessParameter(bool bRead, TXString& inOutValue, const TXString& oldValue, const TXString& szParamName);
			void					ProcessParameter(bool bRead, VWPoint2D& inOutValue, const VWPoint2D& oldValue, const TXString& szParamNameXCoord, const TXString& szParamNameYCoord);
			void					ProcessParameterLineStyle(bool bRead, Sint32& inOutValue, Sint32 oldValue, size_t paramIndex, const TMultiplePseudoDashIndexConverter& converter);

			template<class T>
				void				ProcessParameter(bool bRead, T& inOutValue, T oldValue, const TXString& szParamName, T defIndex);
			template<class T>
				void				ProcessParameter(bool bRead, T& inOutValue, T oldValue, const TXString& szParamName, T defIndex, char** arrStrings);

			Uint32					DecodeEnumString(size_t paramIndex, const TXString& string, Uint32 def) const;
			TXString				EncodeEnumString(size_t paramIndex, Uint32 index, Uint32 def) const;
			Uint32					DecodeEnumString(char** arrStrings, const TXString& string, Uint32 def) const;
			TXString				EncodeEnumString(char** arrStrings, Uint32 index, Uint32 defIndex) const;

		// these are OBSOLETE ... do not use
		public:
			void					ProcessParameter(bool bRead, bool& inOutValue, bool oldValue, size_t paramIndex);
			void					ProcessParameter(bool bRead, Uint32& inOutValue, Uint32 oldValue, size_t paramIndex);
			void					ProcessParameter(bool bRead, Sint32& inOutValue, Uint32 oldValue, size_t paramIndex);
			void					ProcessParameter(bool bRead, double& inOutValue, double oldValue, size_t paramIndex);
			void					ProcessParameter(bool bRead, TXString& inOutValue, const TXString& oldValue, size_t paramIndex);
			void					ProcessParameter(bool bRead, VWPoint2D& inOutValue, const VWPoint2D& oldValue, size_t paramIndexXCoord, size_t paramIndexYCoord);
			template<class T>
				void				ProcessParameter(bool bRead, T& inOutValue, T oldValue, size_t paramIndex, T defIndex);
			template<class T>
				void				ProcessParameter(bool bRead, T& inOutValue, T oldValue, size_t paramIndex, T defIndex, char** arrStrings);

			virtual Sint32			GetParamLong(size_t paramIndex) const = 0;
			virtual void			SetParamLong(size_t paramIndex, Sint32 value) = 0;
			virtual bool			GetParamBool(size_t paramIndex) const = 0;
			virtual void			SetParamBool(size_t paramIndex, bool value) = 0;
			virtual double			GetParamReal(size_t paramIndex) const = 0;
			virtual void			SetParamReal(size_t paramIndex, double value) = 0;
			virtual TXString		GetParamString(size_t paramIndex) const = 0;
			virtual void			SetParamString(size_t paramIndex, const TXString& value) = 0;
			virtual VWPoint2D		GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const = 0;
			virtual void			SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value) = 0;
			virtual bool			GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const = 0;
			virtual EFieldStyle		GetParamStyle(size_t paramIndex) const = 0;

			virtual size_t			PopupGetChoicesCount(size_t paramIndex) = 0;
			virtual void			PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue) = 0;
			virtual void			PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs) = 0;
			virtual void			PopupClearChoices(size_t paramIndex) = 0;
			virtual void			PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append) = 0;

			virtual InternalIndex	GetParamClass(size_t paramIndex) const = 0;
			virtual void			SetParamClass(size_t paramIndex, InternalIndex resource) = 0;
			virtual InternalIndex	GetParamBuildingMaterial(size_t paramIndex) const = 0;
			virtual void			SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource) = 0;
			virtual VWPattern		GetParamFill(size_t paramIndex) const = 0;
			virtual void			SetParamFill(size_t paramIndex, const VWPattern& attr) = 0;
			virtual	VWPattern		GetParamPenStyle(size_t paramIndex) const = 0;
			virtual void			SetParamPenStyle(size_t paramIndex, const VWPattern& attr) = 0;
			virtual Uint8			GetParamPenWeight(size_t paramIndex) const = 0;
			virtual void			SetParamPenWeight(size_t paramIndex, Uint8 value) = 0;
			virtual ColorRef		GetParamColor(size_t paramIndex) const = 0;
			virtual void			SetParamColor(size_t paramIndex, ColorRef value) = 0;
			virtual InternalIndex	GetParamTexture(size_t paramIndex) const = 0;
			virtual void			SetParamTexture(size_t paramIndex, InternalIndex resource) = 0;
			virtual InternalIndex	GetParamSymDef(size_t paramIndex) const = 0;
			virtual void			SetParamSymDef(size_t paramIndex, InternalIndex resource) = 0;

		protected:
			bool					ResourceGetParamChoices(MCObjectHandle handle, size_t paramIndex, TXStringSTLArray& outArray) const;
		};

		// --------------------------------------------------------------------------------------------------------
		class CGenericParamProvider : public CParamProviderAbstract
		{
		public:
						CGenericParamProvider();
						CGenericParamProvider(MCObjectHandle hGenericObject);
						CGenericParamProvider(MCObjectHandle hParametricObject, const TXString& szFormatName);
						CGenericParamProvider(MCObjectHandle hParametricObject, MCObjectHandle hFormat);
			virtual		~CGenericParamProvider();

			void		Set(MCObjectHandle hGenericObject);
			void		Set(MCObjectHandle hParametricObject, const TXString& szFormatName);
			void		Set(MCObjectHandle hParametricObject, MCObjectHandle hFormat);

		public:
            virtual MCObjectHandle  GetObject() const;

			virtual Sint32			GetParamLong(const TXString& szParamName) const;
			virtual void			SetParamLong(const TXString& szParamName, Sint32 value);
			virtual bool			GetParamBool(const TXString& szParamName) const;
			virtual void			SetParamBool(const TXString& szParamName, bool value);
			virtual double			GetParamReal(const TXString& szParamName) const;
			virtual void			SetParamReal(const TXString& szParamName, double value);
			virtual TXString		GetParamString(const TXString& szParamName) const;
			virtual void			SetParamString(const TXString& szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const TXString& szParamXCoord) const;
			virtual void			SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value);

			virtual InternalIndex	GetParamClass(const TXString& univParamName) const;
			virtual void			SetParamClass(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(const TXString& univParamName) const;
			virtual void			SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource);
			virtual VWPattern		GetParamFill(const TXString& univParamName) const;
			virtual void			SetParamFill(const TXString& univParamName, const VWPattern& attr);
			virtual VWPattern		GetParamPenStyle(const TXString& univParamName) const;
			virtual void			SetParamPenStyle(const TXString& univParamName, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(const TXString& univParamName) const;
			virtual void			SetParamPenWeight(const TXString& univParamName, Uint8 value);
			virtual ColorRef		GetParamColor(const TXString& univParamName) const;
			virtual void			SetParamColor(const TXString& univParamName, ColorRef value);
			virtual InternalIndex	GetParamTexture(const TXString& univParamName) const;
			virtual void			SetParamTexture(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(const TXString& univParamName) const;
			virtual void			SetParamSymDef(const TXString& univParamName, InternalIndex resource);

			virtual TXString		GetParamValue(const TXString& szParamName) const;
			virtual void			SetParamValue(const TXString& szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const TXString& szParamName) const;
			virtual size_t			GetParamIndex(const TXString& szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

			// see the equivalent functiosn in VWParametricObj, and VWFormatRecordObj, VWRecordObj
			virtual size_t			PopupGetChoicesCount(const TXString& univParamName);
			virtual void			PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue);
			virtual void			PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void			PopupClearChoices(const TXString& univParamName);
			virtual void			PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append);

		public:
			static bool			IsGenericObject(MCObjectHandle h);

		// these are OBSOLETE ... do not use
		public:
			virtual Sint32				GetParamLong(size_t paramIndex) const;
			virtual void				SetParamLong(size_t paramIndex, Sint32 value);
			virtual bool				GetParamBool(size_t paramIndex) const;
			virtual void				SetParamBool(size_t paramIndex, bool value);
			virtual double				GetParamReal(size_t paramIndex) const;
			virtual void				SetParamReal(size_t paramIndex, double value);
			virtual TXString			GetParamString(size_t paramIndex) const;
			virtual void				SetParamString(size_t paramIndex, const TXString& value);
			virtual VWPoint2D			GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const;
			virtual void				SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value);
			virtual bool				GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const;
			virtual EFieldStyle			GetParamStyle(size_t paramIndex) const;

			virtual size_t				PopupGetChoicesCount(size_t paramIndex);
			virtual void				PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue);
			virtual void				PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void				PopupClearChoices(size_t paramIndex);
			virtual void				PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append);

			virtual InternalIndex	GetParamClass(size_t paramIndex) const;
			virtual void			SetParamClass(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(size_t paramIndex) const;
			virtual void			SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource);
			virtual VWPattern		GetParamFill(size_t paramIndex) const;
			virtual void			SetParamFill(size_t paramIndex, const VWPattern& attr);
			virtual	VWPattern		GetParamPenStyle(size_t paramIndex) const;
			virtual void			SetParamPenStyle(size_t paramIndex, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(size_t paramIndex) const;
			virtual void			SetParamPenWeight(size_t paramIndex, Uint8 value);
			virtual ColorRef		GetParamColor(size_t paramIndex) const;
			virtual void			SetParamColor(size_t paramIndex, ColorRef value);
			virtual InternalIndex	GetParamTexture(size_t paramIndex) const;
			virtual void			SetParamTexture(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(size_t paramIndex) const;
			virtual void			SetParamSymDef(size_t paramIndex, InternalIndex resource);

		private:
			CParamProviderAbstract*	fProvider;
		};

		// --------------------------------------------------------------------------------------------------------
		class CObjectParamProvider : public CParamProviderAbstract
		{
		public:
										CObjectParamProvider(MCObjectHandle hParametricObj);
										CObjectParamProvider(VWParametricObj& obj);
			virtual						~CObjectParamProvider();

		public:
            virtual MCObjectHandle  GetObject() const;

			virtual Sint32			GetParamLong(const TXString& szParamName) const;
			virtual void			SetParamLong(const TXString& szParamName, Sint32 value);
			virtual bool			GetParamBool(const TXString& szParamName) const;
			virtual void			SetParamBool(const TXString& szParamName, bool value);
			virtual double			GetParamReal(const TXString& szParamName) const;
			virtual void			SetParamReal(const TXString& szParamName, double value);
			virtual TXString		GetParamString(const TXString& szParamName) const;
			virtual void			SetParamString(const TXString& szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const TXString& szParamXCoord) const;
			virtual void			SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value);

			virtual InternalIndex	GetParamClass(const TXString& univParamName) const;
			virtual void			SetParamClass(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(const TXString& univParamName) const;
			virtual void			SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource);
			virtual VWPattern		GetParamFill(const TXString& univParamName) const;
			virtual void			SetParamFill(const TXString& univParamName, const VWPattern& attr);
			virtual VWPattern		GetParamPenStyle(const TXString& univParamName) const;
			virtual void			SetParamPenStyle(const TXString& univParamName, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(const TXString& univParamName) const;
			virtual void			SetParamPenWeight(const TXString& univParamName, Uint8 value);
			virtual ColorRef		GetParamColor(const TXString& univParamName) const;
			virtual void			SetParamColor(const TXString& univParamName, ColorRef value);
			virtual InternalIndex	GetParamTexture(const TXString& univParamName) const;
			virtual void			SetParamTexture(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(const TXString& univParamName) const;
			virtual void			SetParamSymDef(const TXString& univParamName, InternalIndex resource);

			virtual TXString		GetParamValue(const TXString& szParamName) const;
			virtual void			SetParamValue(const TXString& szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const TXString& szParamName) const;
			virtual size_t			GetParamIndex(const TXString& szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

			// see the equivalent functiosn in VWParametricObj, and VWFormatRecordObj, VWRecordObj
			virtual size_t			PopupGetChoicesCount(const TXString& univParamName);
			virtual void			PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue);
			virtual void			PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void			PopupClearChoices(const TXString& univParamName);
			virtual void			PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append);

		// these are OBSOLETE ... do not use
		public:
			virtual Sint32				GetParamLong(size_t paramIndex) const;
			virtual void				SetParamLong(size_t paramIndex, Sint32 value);
			virtual bool				GetParamBool(size_t paramIndex) const;
			virtual void				SetParamBool(size_t paramIndex, bool value);
			virtual double				GetParamReal(size_t paramIndex) const;
			virtual void				SetParamReal(size_t paramIndex, double value);
			virtual TXString			GetParamString(size_t paramIndex) const;
			virtual void				SetParamString(size_t paramIndex, const TXString& value);
			virtual VWPoint2D			GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const;
			virtual void				SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value);
			virtual bool				GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const;
			virtual EFieldStyle			GetParamStyle(size_t paramIndex) const;

			virtual size_t				PopupGetChoicesCount(size_t paramIndex);
			virtual void				PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue);
			virtual void				PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void				PopupClearChoices(size_t paramIndex);
			virtual void				PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append);

			virtual InternalIndex	GetParamClass(size_t paramIndex) const;
			virtual void			SetParamClass(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(size_t paramIndex) const;
			virtual void			SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource);
			virtual VWPattern		GetParamFill(size_t paramIndex) const;
			virtual void			SetParamFill(size_t paramIndex, const VWPattern& attr);
			virtual	VWPattern		GetParamPenStyle(size_t paramIndex) const;
			virtual void			SetParamPenStyle(size_t paramIndex, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(size_t paramIndex) const;
			virtual void			SetParamPenWeight(size_t paramIndex, Uint8 value);
			virtual ColorRef		GetParamColor(size_t paramIndex) const;
			virtual void			SetParamColor(size_t paramIndex, ColorRef value);
			virtual InternalIndex	GetParamTexture(size_t paramIndex) const;
			virtual void			SetParamTexture(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(size_t paramIndex) const;
			virtual void			SetParamSymDef(size_t paramIndex, InternalIndex resource);

		private:
			VWParametricObj				fObj;
		};

		// --------------------------------------------------------------------------------------------------------
		class CFormatParamProvider : public CParamProviderAbstract
		{
		public:
										CFormatParamProvider(MCObjectHandle hRecordFormatObj);
										CFormatParamProvider(VWRecordFormatObj& obj);
			virtual						~CFormatParamProvider();

		public:
            virtual MCObjectHandle  GetObject() const;

			virtual Sint32			GetParamLong(const TXString& szParamName) const;
			virtual void			SetParamLong(const TXString& szParamName, Sint32 value);
			virtual bool			GetParamBool(const TXString& szParamName) const;
			virtual void			SetParamBool(const TXString& szParamName, bool value);
			virtual double			GetParamReal(const TXString& szParamName) const;
			virtual void			SetParamReal(const TXString& szParamName, double value);
			virtual TXString		GetParamString(const TXString& szParamName) const;
			virtual void			SetParamString(const TXString& szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const TXString& szParamXCoord) const;
			virtual void			SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value);

			virtual InternalIndex	GetParamClass(const TXString& univParamName) const;
			virtual void			SetParamClass(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(const TXString& univParamName) const;
			virtual void			SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource);
			virtual VWPattern		GetParamFill(const TXString& univParamName) const;
			virtual void			SetParamFill(const TXString& univParamName, const VWPattern& attr);
			virtual VWPattern		GetParamPenStyle(const TXString& univParamName) const;
			virtual void			SetParamPenStyle(const TXString& univParamName, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(const TXString& univParamName) const;
			virtual void			SetParamPenWeight(const TXString& univParamName, Uint8 value);
			virtual ColorRef		GetParamColor(const TXString& univParamName) const;
			virtual void			SetParamColor(const TXString& univParamName, ColorRef value);
			virtual InternalIndex	GetParamTexture(const TXString& univParamName) const;
			virtual void			SetParamTexture(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(const TXString& univParamName) const;
			virtual void			SetParamSymDef(const TXString& univParamName, InternalIndex resource);

			virtual TXString		GetParamValue(const TXString& szParamName) const;
			virtual void			SetParamValue(const TXString& szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const TXString& szParamName) const;
			virtual size_t			GetParamIndex(const TXString& szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

			// see the equivalent functiosn in VWParametricObj, and VWFormatRecordObj, VWRecordObj
			virtual size_t			PopupGetChoicesCount(const TXString& univParamName);
			virtual void			PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue);
			virtual void			PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void			PopupClearChoices(const TXString& univParamName);
			virtual void			PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append);

		// these are OBSOLETE ... do not use
		public:
			virtual Sint32				GetParamLong(size_t paramIndex) const;
			virtual void				SetParamLong(size_t paramIndex, Sint32 value);
			virtual bool				GetParamBool(size_t paramIndex) const;
			virtual void				SetParamBool(size_t paramIndex, bool value);
			virtual double				GetParamReal(size_t paramIndex) const;
			virtual void				SetParamReal(size_t paramIndex, double value);
			virtual TXString			GetParamString(size_t paramIndex) const;
			virtual void				SetParamString(size_t paramIndex, const TXString& value);
			virtual VWPoint2D			GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const;
			virtual void				SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value);
			virtual bool				GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const;
			virtual EFieldStyle			GetParamStyle(size_t paramIndex) const;

			virtual size_t				PopupGetChoicesCount(size_t paramIndex);
			virtual void				PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue);
			virtual void				PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void				PopupClearChoices(size_t paramIndex);
			virtual void				PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append);

			virtual InternalIndex	GetParamClass(size_t paramIndex) const;
			virtual void			SetParamClass(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(size_t paramIndex) const;
			virtual void			SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource);
			virtual VWPattern		GetParamFill(size_t paramIndex) const;
			virtual void			SetParamFill(size_t paramIndex, const VWPattern& attr);
			virtual	VWPattern		GetParamPenStyle(size_t paramIndex) const;
			virtual void			SetParamPenStyle(size_t paramIndex, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(size_t paramIndex) const;
			virtual void			SetParamPenWeight(size_t paramIndex, Uint8 value);
			virtual ColorRef		GetParamColor(size_t paramIndex) const;
			virtual void			SetParamColor(size_t paramIndex, ColorRef value);
			virtual InternalIndex	GetParamTexture(size_t paramIndex) const;
			virtual void			SetParamTexture(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(size_t paramIndex) const;
			virtual void			SetParamSymDef(size_t paramIndex, InternalIndex resource);

		private:
			VWRecordFormatObj			fObj;
		};

		// --------------------------------------------------------------------------------------------------------
		class CRecordParamProvider : public CParamProviderAbstract
		{
		public:
										CRecordParamProvider(MCObjectHandle hRecordObj);
										CRecordParamProvider(VWRecordObj& obj);
			virtual						~CRecordParamProvider();

		public:
            virtual MCObjectHandle  GetObject() const;

			virtual Sint32			GetParamLong(const TXString& szParamName) const;
			virtual void			SetParamLong(const TXString& szParamName, Sint32 value);
			virtual bool			GetParamBool(const TXString& szParamName) const;
			virtual void			SetParamBool(const TXString& szParamName, bool value);
			virtual double			GetParamReal(const TXString& szParamName) const;
			virtual void			SetParamReal(const TXString& szParamName, double value);
			virtual TXString		GetParamString(const TXString& szParamName) const;
			virtual void			SetParamString(const TXString& szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const TXString& szParamXCoord) const;
			virtual void			SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value);

			virtual InternalIndex	GetParamClass(const TXString& univParamName) const;
			virtual void			SetParamClass(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(const TXString& univParamName) const;
			virtual void			SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource);
			virtual VWPattern		GetParamFill(const TXString& univParamName) const;
			virtual void			SetParamFill(const TXString& univParamName, const VWPattern& attr);
			virtual VWPattern		GetParamPenStyle(const TXString& univParamName) const;
			virtual void			SetParamPenStyle(const TXString& univParamName, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(const TXString& univParamName) const;
			virtual void			SetParamPenWeight(const TXString& univParamName, Uint8 value);
			virtual ColorRef		GetParamColor(const TXString& univParamName) const;
			virtual void			SetParamColor(const TXString& univParamName, ColorRef value);
			virtual InternalIndex	GetParamTexture(const TXString& univParamName) const;
			virtual void			SetParamTexture(const TXString& univParamName, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(const TXString& univParamName) const;
			virtual void			SetParamSymDef(const TXString& univParamName, InternalIndex resource);

			virtual TXString		GetParamValue(const TXString& szParamName) const;
			virtual void			SetParamValue(const TXString& szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const TXString& szParamName) const;
			virtual size_t			GetParamIndex(const TXString& szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

			// see the equivalent functiosn in VWParametricObj, and VWFormatRecordObj, VWRecordObj
			virtual size_t			PopupGetChoicesCount(const TXString& univParamName);
			virtual void			PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue);
			virtual void			PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void			PopupClearChoices(const TXString& univParamName);
			virtual void			PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append);

		// these are OBSOLETE ... do not use
		public:
			virtual Sint32				GetParamLong(size_t paramIndex) const;
			virtual void				SetParamLong(size_t paramIndex, Sint32 value);
			virtual bool				GetParamBool(size_t paramIndex) const;
			virtual void				SetParamBool(size_t paramIndex, bool value);
			virtual double				GetParamReal(size_t paramIndex) const;
			virtual void				SetParamReal(size_t paramIndex, double value);
			virtual TXString			GetParamString(size_t paramIndex) const;
			virtual void				SetParamString(size_t paramIndex, const TXString& value);
			virtual VWPoint2D			GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const;
			virtual void				SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value);
			virtual bool				GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const;
			virtual EFieldStyle			GetParamStyle(size_t paramIndex) const;

			virtual size_t				PopupGetChoicesCount(size_t paramIndex);
			virtual void				PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue);
			virtual void				PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs);
			virtual void				PopupClearChoices(size_t paramIndex);
			virtual void				PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append);

			virtual InternalIndex	GetParamClass(size_t paramIndex) const;
			virtual void			SetParamClass(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamBuildingMaterial(size_t paramIndex) const;
			virtual void			SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource);
			virtual VWPattern		GetParamFill(size_t paramIndex) const;
			virtual void			SetParamFill(size_t paramIndex, const VWPattern& attr);
			virtual	VWPattern		GetParamPenStyle(size_t paramIndex) const;
			virtual void			SetParamPenStyle(size_t paramIndex, const VWPattern& attr);
			virtual Uint8			GetParamPenWeight(size_t paramIndex) const;
			virtual void			SetParamPenWeight(size_t paramIndex, Uint8 value);
			virtual ColorRef		GetParamColor(size_t paramIndex) const;
			virtual void			SetParamColor(size_t paramIndex, ColorRef value);
			virtual InternalIndex	GetParamTexture(size_t paramIndex) const;
			virtual void			SetParamTexture(size_t paramIndex, InternalIndex resource);
			virtual InternalIndex	GetParamSymDef(size_t paramIndex) const;
			virtual void			SetParamSymDef(size_t paramIndex, InternalIndex resource);

		private:
			VWRecordObj			fObj;
		};

		// ==================================================================================================
		// template impelementation

		// ---------------------------------------------------------------------------------------------------
		// Process enumeration parameter from parameter enumeration values
		// ---------------------------------------------------------------------------------------------------
		template<class T>
		void CParamProviderAbstract::ProcessParameter(bool bRead, T& inOutValue, T oldValue, const TXString& szParamName, T defIndex)
		{
			this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex(szParamName), defIndex );
		}

		template<class T>
		void CParamProviderAbstract::ProcessParameter(bool bRead, T& inOutValue, T oldValue, const TXString& szParamName, T defIndex, char** arrStrings)
		{
			this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex(szParamName), defIndex, arrStrings );
		}

		template <class T>
		void CParamProviderAbstract::ProcessParameter(bool bRead, T& inOutValue, T oldValue, size_t paramIndex, T defIndex)
		{
			if ( bRead ) {
				TXString	strEncodedValue	= this->GetParamString( paramIndex );
				inOutValue					= (T) this->DecodeEnumString( paramIndex, strEncodedValue, defIndex );
			}
			else if ( oldValue != inOutValue ) {
				TXString	strEncodedValue	= this->EncodeEnumString( paramIndex, inOutValue, defIndex );
				this->SetParamString( paramIndex, strEncodedValue );
			}
		}

		// ---------------------------------------------------------------------------------------------------
		// Process enumeration parameter from specified array
		// ---------------------------------------------------------------------------------------------------
		template<class T>
		void CParamProviderAbstract::ProcessParameter(bool bRead, T& inOutValue, T oldValue, size_t paramIndex, T defIndex, char** arrStrings)
		{
			if ( bRead ) {
				TXString	strEncodedValue	= this->GetParamString( paramIndex );
				inOutValue					= (T) this->DecodeEnumString( arrStrings, strEncodedValue, defIndex );
			}
			else if ( oldValue != inOutValue ) {
				TXString	strEncodedValue	= this->EncodeEnumString( arrStrings, inOutValue, defIndex );
				this->SetParamString( paramIndex, strEncodedValue );
			}
		}

	}
}
