//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace SpotlightInterfaces
	{
		// {A96E6859-6E6B-4863-87D8-226652B01CA5}
		static const VWIID IID_LightingDeviceData			= { 0xa96e6859, 0x6e6b, 0x4863, { 0x87, 0xd8, 0x22, 0x66, 0x52, 0xb0, 0x1c, 0xa5 } };
		
		static const size_t	kSetAll				= size_t( -1 );
		static const size_t	kIgnoreAccessories	= size_t( -2 );
		static const size_t	kSetAllClamps		= size_t( -3 );
		static const size_t	kSetAllAccessories	= size_t( -4 );

		/*	Never use a ILightingDeviceAccessoryData instances after its parent ILightingDeviceData is destroyed!
			This use case result is undefined and unsupported. */
		class DYNAMIC_ATTRIBUTE ILightingDeviceAccessoryData : public IVWUnknown
		{
		public:
			virtual void			VCOM_CALLTYPE DeleteAccessory() = 0;

			virtual size_t			VCOM_CALLTYPE GetParentCell() = 0;
			virtual void			VCOM_CALLTYPE SetParentCell( size_t newCellIndex ) = 0;

			virtual size_t			VCOM_CALLTYPE GetIndex() = 0;

			virtual TransformMatrix	VCOM_CALLTYPE GetAccessoryMatrix( bool get3D ) = 0;
			virtual void			VCOM_CALLTYPE SetAccessoryMatrix( const TransformMatrix& newMatrix, bool set3D ) = 0;

			virtual bool			VCOM_CALLTYPE GetUseDefaultPosition( bool get3D ) = 0;
			virtual void			VCOM_CALLTYPE SetUseDefaultPosition( bool useDefaultPosition, bool set3D ) = 0;
		};
		typedef VCOMPtr<ILightingDeviceAccessoryData>		ILightingDeviceAccessoryDataPtr;

		class DYNAMIC_ATTRIBUTE ILightingDeviceData : public IVWUnknown
		{
		 public:
			virtual bool			VCOM_CALLTYPE Load( MCObjectHandle hDevice ) = 0;
			virtual bool			VCOM_CALLTYPE Save() = 0;

			virtual ILightingDeviceAccessoryDataPtr VCOM_CALLTYPE GetAccessory( size_t cellIndex, size_t accessoryIndex ) = 0;
			virtual ILightingDeviceAccessoryDataPtr VCOM_CALLTYPE CreateAccessory( MCObjectHandle hSymDef, TransformMatrix transform2D, TransformMatrix transform3D, size_t parentCell, bool useUndo ) = 0;

			virtual TXString		VCOM_CALLTYPE GetParamString( const TXString& universalName, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;
			virtual void			VCOM_CALLTYPE SetParamString( const TXString& universalName, const TXString& value, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;

			virtual bool			VCOM_CALLTYPE GetParamBool( const TXString& universalName, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;
			virtual void			VCOM_CALLTYPE SetParamBool( const TXString& universalName, bool value, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;

			virtual double			VCOM_CALLTYPE GetParamDouble( const TXString& universalName, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;
			virtual void			VCOM_CALLTYPE SetParamDouble( const TXString& universalName, double value, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;

			virtual Sint32			VCOM_CALLTYPE GetParamSint32( const TXString& universalName, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;
			virtual void			VCOM_CALLTYPE SetParamSint32( const TXString& universalName, Sint32 value, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;

			virtual TXString		VCOM_CALLTYPE GetParamValue( const TXString& universalName, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;
			virtual void			VCOM_CALLTYPE SetParamValue( const TXString& universalName, const TXString& value, size_t cellIndex = 0, size_t accessoryIndex = kIgnoreAccessories ) = 0;

			virtual size_t			VCOM_CALLTYPE GetParamsCount() = 0;

			virtual TXString		VCOM_CALLTYPE GetParamUnivName( size_t paramIndex ) = 0;
			virtual TXString		VCOM_CALLTYPE GetParamLocalizedName( const TXString& universalName ) = 0;

			virtual bool			VCOM_CALLTYPE IsMulticellParam( const TXString& universalName ) = 0;
			virtual bool			VCOM_CALLTYPE IsAccessoryParam( const TXString& universalName ) = 0;

			virtual size_t			VCOM_CALLTYPE GetAccessoriesCount( size_t cellIndex = kSetAll ) = 0;
			virtual size_t			VCOM_CALLTYPE GetCellsCount() = 0;
			
			// These parameters interact with the lighting device and the light object that is inside the light, so we want to access them through these wrappers that will set 
			// the values properly on both
			virtual double			GetBrightness( size_t cellIndex ) const = 0;
			virtual void			SetBrightness( double value, size_t cellIndex ) = 0;

			virtual bool			GetUseEmitter( size_t cellIndex ) const = 0;
			virtual void			SetUseEmitter( bool value, size_t cellIndex ) = 0;

			virtual Sint32			GetEmitterBrightness( size_t cellIndex ) const = 0;
			virtual void			SetEmitterBrightness( Sint32 value, size_t cellIndex ) = 0;

			virtual Sint16			GetBrightnessUnit( size_t cellIndex ) const = 0;
			virtual void			SetBrightnessUnit( Sint16 value, size_t cellIndex ) = 0;
		};
		typedef VCOMPtr<ILightingDeviceData>		ILightingDeviceDataPtr;

		// -------------------------------------------------------------------------------------------
		// {4C984CE8-B5E9-4376-9F19-2B6D718E73C5}
		static const VWIID IID_LightingDeviceShutterImage
			= { 0x4c984ce8, 0xb5e9, 0x4376, {0x9f, 0x19, 0x2b, 0x6d, 0x71, 0x8e, 0x73, 0xc5}};
		class DYNAMIC_ATTRIBUTE ILightingDeviceShutterImage : public IVWSingletonUnknown
		{
		public:
			virtual Imaging::IRawImagePtr GetShutterImage(MCObjectHandle ld, const bool &hFlip, const bool &vFlip, const int &width = 0, const int &height = 0) = 0;
		};
		typedef VCOMPtr<ILightingDeviceShutterImage> ILightingDeviceShutterImagePtr;

		// -------------------------------------------------------------------------------------------
		// {5C984CE8-95E9-4376-9F19-2B6D718E73C5}
		static const VWIID IID_LightingDeviceGoboImage
			= { 0x5c984ce8, 0x95e9, 0x4376, {0x9f, 0x19, 0x2b, 0x6d, 0x71, 0x8e, 0x73, 0xc5}};
		class DYNAMIC_ATTRIBUTE ILightingDeviceGoboImage : public IVWSingletonUnknown
		{
		public:
			virtual MCObjectHandle GetFirstGobo(MCObjectHandle ld) = 0;
		};
		typedef VCOMPtr<ILightingDeviceGoboImage> ILightingDeviceGoboImagePtr;

		// -------------------------------------------------------------------------------------------
		// {4C984CE8-A5E9-4376-9F19-2B6D718E73C5}
		static const VWIID IID_GdtfFileUserDataNode
			= { 0x4c984ce8, 0xa5e9, 0x4376, {0x9f, 0x19, 0x2b, 0x6d, 0x71, 0x8e, 0x73, 0xc5}};
		class DYNAMIC_ATTRIBUTE IGdtfFileUserDataNode : public IVWSingletonUnknown
		{
		public:
			virtual void 		SetHandle(MCObjectHandle handle) = 0;
			virtual bool 		ValidGdtf() = 0;
			virtual UuidStorage GdtfUuid() = 0;
			virtual void 		SaveBuffer(char * buffer, size_t length, const UuidStorage& uuid) = 0;
			virtual size_t 		GetBufferLength() = 0;
			virtual void 		GetBuffer(char * buffer) = 0;
		};
		typedef VCOMPtr<IGdtfFileUserDataNode> IGdtfFileUserDataNodePtr;
	}
}
