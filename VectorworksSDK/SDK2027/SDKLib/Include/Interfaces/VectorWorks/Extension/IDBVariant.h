//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once


namespace VectorWorks
{
	namespace Extension
	{
		enum EVariantType
		{
											// SQL types
											// -------------------------------
			eVariantType_Unknown,			// Unsupported
			eVariantType_CHAR,				// CHAR, VARCHAR, DECIMAL, NUMERIC
			eVariantType_LONG,				// INTEGER
			eVariantType_SHORT,				// SMALLINT
			eVariantType_FLOAT,				// REAL
			eVariantType_DOUBLE,			// FLOAT, DOUBLE
			eVariantType_BINARY
		};

		// ---------------------------------------------------------------------------------------------------
		// {A643BA9A-9E2F-46ff-8E87-78330756FEE6}
		static const VWIID IID_DBVariant	= { 0xa643ba9a, 0x9e2f, 0x46ff, { 0x8e, 0x87, 0x78, 0x33, 0x7, 0x56, 0xfe, 0xe6 } };

		class DYNAMIC_ATTRIBUTE IDBVariant : public IVWUnknown
		{
		public:
			virtual EVariantType	VCOM_CALLTYPE GetType() = 0;
			virtual Uint32			VCOM_CALLTYPE GetSize() = 0;
			virtual bool			VCOM_CALLTYPE IsNullable() = 0;
			virtual void			VCOM_CALLTYPE Increase() = 0;

			virtual TXString		VCOM_CALLTYPE GetString() = 0;
			virtual void			VCOM_CALLTYPE SetString(const TXString& value) = 0;
			virtual Sint32			VCOM_CALLTYPE GetLong() = 0;
			virtual void			VCOM_CALLTYPE SetLong(Sint32 value) = 0;
			virtual Sint16			VCOM_CALLTYPE GetShort() = 0;
			virtual void			VCOM_CALLTYPE SetShort(Sint16 value) = 0;
			virtual float			VCOM_CALLTYPE GetFloat() = 0;
			virtual void			VCOM_CALLTYPE SetFloat(float value) = 0;
			virtual double			VCOM_CALLTYPE GetDouble() = 0;
			virtual void			VCOM_CALLTYPE SetDouble(double value) = 0;
				// Vectorworks 2012
			virtual void			VCOM_CALLTYPE GetBinary(void* value, size_t& size) = 0;
			virtual void			VCOM_CALLTYPE SetBinary(void* value, size_t size) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBVariant>		IDBVariantPtr;
	}
}
