//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include <memory>

namespace VectorWorks
{
	// ------------------------------------------------------------------------------------------------------------------------------------
	// 815CA1D5-1A2C-458E-80EE-8807650B6245
	static const VWIID IID_JSONParser = { 0x815ca1d5, 0x1a2c, 0x458e, { 0x80, 0xee, 0x88, 0x7, 0x65, 0xb, 0x62, 0x45 } };

	enum class EJSONType
	{
		  String
		, Double
		, Int
		, Bool
		, Array
		, Map
	};

	// Forward declaration for the following typedefs
	class IJSONType;

	typedef std::shared_ptr<IJSONType>		IJSONTypePtr;
	typedef std::map<TXString,IJSONTypePtr>	TJSONMap;
	typedef std::vector<IJSONTypePtr>		TJSONArray;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IJSONType
	{
	public:
		virtual					~IJSONType(){};

	public:
		virtual TXString		String( const TXString& defaultValue = "" ) const = 0;
		virtual double			Double( double defaultValue = 0.0 ) const = 0;
		virtual Sint32			Int( Sint32 defaultValue = 0 ) const = 0;
		virtual bool			Bool( bool defaultValue = false ) const = 0;
		virtual TJSONArray		Array( const TJSONArray& defaultValue = TJSONArray() ) const = 0;
		virtual TJSONMap		Map( const TJSONMap& defaultValue = TJSONMap() ) const = 0;

		virtual bool			IsType(EJSONType type) const = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
    class DYNAMIC_ATTRIBUTE IJSONParser : public IVWUnknown
	{
	public:
		virtual VCOMError			VCOM_CALLTYPE Extract( const TXString& inJSON, TJSONMap& outJSONMap ) = 0;
		virtual VCOMError			VCOM_CALLTYPE Compact( const TJSONMap& inJSONMap, TXString& outJSON ) = 0;

		virtual IJSONTypePtr		VCOM_CALLTYPE CompactString( const TXString& inString ) = 0;
		virtual IJSONTypePtr		VCOM_CALLTYPE CompactDouble( double inNumber ) = 0;
		virtual IJSONTypePtr		VCOM_CALLTYPE CompactInt( Sint32 inNumber ) = 0;
		virtual IJSONTypePtr		VCOM_CALLTYPE CompactBool( bool inBool ) = 0;
		virtual IJSONTypePtr		VCOM_CALLTYPE CompactArray( const TJSONArray& inJSONArray ) = 0;
		virtual IJSONTypePtr		VCOM_CALLTYPE CompactMap( const TJSONMap& inJSONMap ) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IJSONParser> IJSONParserPtr;
}
