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
            
			virtual Sint32			GetParamLong(const char* szParamName) const = 0;
			virtual void			SetParamLong(const char* szParamName, Sint32 value) = 0;
			virtual bool			GetParamBool(const char* szParamName) const = 0;
			virtual void			SetParamBool(const char* szParamName, bool value) = 0;
			virtual double			GetParamReal(const char* szParamName) const = 0;
			virtual void			SetParamReal(const char* szParamName, double value) = 0;
			virtual TXString		GetParamString(const char* szParamName) const = 0;
			virtual void			SetParamString(const char* szParamName, const TXString& value) = 0;
			virtual VWPoint2D		GetParamCtrlPt(const char* szParamXCoord) const = 0;
			virtual void			SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value) = 0;

			virtual TXString		GetParamValue(const char* szParamName) const = 0;
			virtual void			SetParamValue(const char* szParamName, const TXString& value) = 0;

			virtual size_t			GetParamsCount() const = 0;
			virtual EFieldStyle		GetParamStyle(const char* szParamName) const = 0;
			virtual size_t			GetParamIndex(const char* szParamName) const = 0;

			virtual TXString		GetParamName(size_t index) const = 0;

		public:
			void					ProcessParameter(bool bRead, bool& inOutValue, bool oldValue, const char* szParamName);
			void					ProcessParameter(bool bRead, Uint32& inOutValue, Uint32 oldValue, const char* szParamName);
			void					ProcessParameter(bool bRead, Sint32& inOutValue, Uint32 oldValue, const char* szParamName);
			void					ProcessParameter(bool bRead, double& inOutValue, double oldValue, const char* szParamName);
			void					ProcessParameter(bool bRead, TXString& inOutValue, const TXString& oldValue, const char* szParamName);
			void					ProcessParameter(bool bRead, VWPoint2D& inOutValue, const VWPoint2D& oldValue, const char* szParamNameXCoord, const char* szParamNameYCoord);
			void					ProcessParameterLineStyle(bool bRead, Sint32& inOutValue, Sint32 oldValue, size_t paramIndex, const TMultiplePseudoDashIndexConverter& converter);

			template<class T>
				void				ProcessParameter(bool bRead, T& inOutValue, T oldValue, const char* szParamName, T defIndex);
			template<class T>
				void				ProcessParameter(bool bRead, T& inOutValue, T oldValue, const char* szParamName, T defIndex, char** arrStrings);

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

		protected:
			bool					ResourceGetParamChoices(MCObjectHandle handle, size_t paramIndex, TXStringSTLArray& outArray) const;
		};

		// --------------------------------------------------------------------------------------------------------
		class CGenericParamProvider : public CParamProviderAbstract
		{
		public:
						CGenericParamProvider();
						CGenericParamProvider(MCObjectHandle hGenericObject);
						CGenericParamProvider(MCObjectHandle hParametricObject, const char* szFormatName);
						CGenericParamProvider(MCObjectHandle hParametricObject, MCObjectHandle hFormat);
			virtual		~CGenericParamProvider();

			void		Set(MCObjectHandle hGenericObject);
			void		Set(MCObjectHandle hParametricObject, const char* szFormatName);
			void		Set(MCObjectHandle hParametricObject, MCObjectHandle hFormat);

		public:
            virtual MCObjectHandle  GetObject() const;

			virtual Sint32			GetParamLong(const char* szParamName) const;
			virtual void			SetParamLong(const char* szParamName, Sint32 value);
			virtual bool			GetParamBool(const char* szParamName) const;
			virtual void			SetParamBool(const char* szParamName, bool value);
			virtual double			GetParamReal(const char* szParamName) const;
			virtual void			SetParamReal(const char* szParamName, double value);
			virtual TXString		GetParamString(const char* szParamName) const;
			virtual void			SetParamString(const char* szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const char* szParamXCoord) const;
			virtual void			SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value);

			virtual TXString		GetParamValue(const char* szParamName) const;
			virtual void			SetParamValue(const char* szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const char* szParamName) const;
			virtual size_t			GetParamIndex(const char* szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

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

			virtual Sint32			GetParamLong(const char* szParamName) const;
			virtual void			SetParamLong(const char* szParamName, Sint32 value);
			virtual bool			GetParamBool(const char* szParamName) const;
			virtual void			SetParamBool(const char* szParamName, bool value);
			virtual double			GetParamReal(const char* szParamName) const;
			virtual void			SetParamReal(const char* szParamName, double value);
			virtual TXString		GetParamString(const char* szParamName) const;
			virtual void			SetParamString(const char* szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const char* szParamXCoord) const;
			virtual void			SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value);

			virtual TXString		GetParamValue(const char* szParamName) const;
			virtual void			SetParamValue(const char* szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const char* szParamName) const;
			virtual size_t			GetParamIndex(const char* szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

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

			virtual Sint32			GetParamLong(const char* szParamName) const;
			virtual void			SetParamLong(const char* szParamName, Sint32 value);
			virtual bool			GetParamBool(const char* szParamName) const;
			virtual void			SetParamBool(const char* szParamName, bool value);
			virtual double			GetParamReal(const char* szParamName) const;
			virtual void			SetParamReal(const char* szParamName, double value);
			virtual TXString		GetParamString(const char* szParamName) const;
			virtual void			SetParamString(const char* szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const char* szParamXCoord) const;
			virtual void			SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value);

			virtual TXString		GetParamValue(const char* szParamName) const;
			virtual void			SetParamValue(const char* szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const char* szParamName) const;
			virtual size_t			GetParamIndex(const char* szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

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

			virtual Sint32			GetParamLong(const char* szParamName) const;
			virtual void			SetParamLong(const char* szParamName, Sint32 value);
			virtual bool			GetParamBool(const char* szParamName) const;
			virtual void			SetParamBool(const char* szParamName, bool value);
			virtual double			GetParamReal(const char* szParamName) const;
			virtual void			SetParamReal(const char* szParamName, double value);
			virtual TXString		GetParamString(const char* szParamName) const;
			virtual void			SetParamString(const char* szParamName, const TXString& value);
			virtual VWPoint2D		GetParamCtrlPt(const char* szParamXCoord) const;
			virtual void			SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value);

			virtual TXString		GetParamValue(const char* szParamName) const;
			virtual void			SetParamValue(const char* szParamName, const TXString& value);

			virtual size_t			GetParamsCount() const;
			virtual EFieldStyle		GetParamStyle(const char* szParamName) const;
			virtual size_t			GetParamIndex(const char* szParamName) const;

			virtual TXString		GetParamName(size_t index) const;

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

		private:
			VWRecordObj			fObj;
		};

		// ==================================================================================================
		// template impelementation

		// ---------------------------------------------------------------------------------------------------
		// Process enumeration parameter from parameter enumeration values
		// ---------------------------------------------------------------------------------------------------
		template<class T>
		void CParamProviderAbstract::ProcessParameter(bool bRead, T& inOutValue, T oldValue, const char* szParamName, T defIndex)
		{
			this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex(szParamName), defIndex );
		}

		template<class T>
		void CParamProviderAbstract::ProcessParameter(bool bRead, T& inOutValue, T oldValue, const char* szParamName, T defIndex, char** arrStrings)
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
