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
		typedef VWIID	TSinkIID;

		// ----------------------------------------------------------------------------------------------------
		// Base class for extension sink
		class DYNAMIC_ATTRIBUTE IEventSink : public IVWUnknown
		{
		public:
		};

		// ----------------------------------------------------------------------------------------------------
		// Base class for Vectorworks extensions implementation
		class DYNAMIC_ATTRIBUTE IExtension : public IVWUnknown
		{
		public:
			virtual const TXString& VCOM_CALLTYPE	GetUniversalName() = 0;
			virtual Sint32 VCOM_CALLTYPE			GetVersion() = 0;
			virtual IEventSink* VCOM_CALLTYPE		QueryEventSink(const TSinkIID& iid) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		template<class T> class VCOMSinkPtr : public VCOMPtr< T >
		{
		public:
			VCOMSinkPtr()					: VCOMPtr< T >()					{ }
			VCOMSinkPtr(T* ptr)				: VCOMPtr< T >( ptr )				{ }
			VCOMSinkPtr(const VWIID& iid)	: VCOMPtr< T >( iid )				{ }
			VCOMSinkPtr(IExtension* extension, const TSinkIID& iid)				{ this->Query( extension, iid ); }
			VCOMSinkPtr(MCObjectHandle hParametric, const TSinkIID& iid)		{ this->Query( hParametric, iid ); }
			VCOMSinkPtr(const TXString& universalName, const TSinkIID& iid)		{ this->Query( universalName, iid ); }
			VCOMSinkPtr(const VCOMSinkPtr& p)									{ T* ptr = p.Get(); this->Set( ptr ); if ( ptr ) { ptr->AddRef(); } }

		public:
			VCOMError	Query(IExtension* extension, const TSinkIID& iid)	{
															this->Release();

															VCOMError err = kVCOMError_Failed;
															if ( extension == NULL ) {
																err = kVCOMError_InvalidArg;
															}
															else {
																IEventSink*	pInterface	= extension->QueryEventSink( iid );
																// Vlado: Temporally removed 'dynamic_cast'
																// because on new Mac OS it is failing to cast properly
																//fPtr = dynamic_cast<T*>( pInterface );
																this->Set( (T*)( pInterface ) );
																if ( this->Get() == NULL ) {
																	if ( pInterface ) {
																		pInterface->Release();
																		pInterface	= NULL;
																	}
																	// the passed 'iid' is not from the extected type 'T'
																	err			= kVCOMError_InvalidArg;
																}
                                                                else
                                                                    err = kVCOMError_NoError;
															}
															return err;
														}

			VCOMError	Query( MCObjectHandle hParametric, const TSinkIID& iid )	{
															this->Release();

															VCOMError err = kVCOMError_Failed;
															if ( hParametric == nullptr )
															{
																err = kVCOMError_InvalidArg;
															}
															else
															{
																IVWUnknown*	pInterface	= NULL;

																void* kludgeParams[ 2 ];
																kludgeParams[ 0 ]	= (void*)&( hParametric );
																kludgeParams[ 1 ]	= (void*)&( iid );

																if ( gSDK->Kludge( 7010, kludgeParams, &pInterface ) )
																{
																	// Vlado: Temporally removed 'dynamic_cast'
																	// because on new Mac OS it is failing to cast properly
																	//fPtr = dynamic_cast<T*>( pInterface );
																	this->Set( (T*) ( pInterface ) );
																	if ( this->Get() == NULL )
																	{
																		if ( pInterface )
																		{
																			pInterface->Release();
																			pInterface	= NULL;
																		}
																		// the passed 'iid' is not from the extected type 'T'
																		err	= kVCOMError_InvalidArg;
																	}
																	else
																		err	= kVCOMError_NoError;
																}
															}
															return err;
														}

			VCOMError	Query( const TXString& universalName, const TSinkIID& iid )	{
															this->Release();

															VCOMError err = kVCOMError_Failed;
															if ( universalName == "" )
															{
																err = kVCOMError_InvalidArg;
															}
															else
															{
																IVWUnknown*	pInterface	= NULL;

																void* kludgeParams[ 2 ];
																kludgeParams[ 0 ]	= (void*)&( universalName );
																kludgeParams[ 1 ]	= (void*)&( iid );

																if ( gSDK->Kludge( 7106/*kKludgeQueryExtensionEventSinkByName*/, kludgeParams, &pInterface ) )
																{
																	// Vlado: Temporally removed 'dynamic_cast'
																	// because on new Mac OS it is failing to cast properly
																	//fPtr = dynamic_cast<T*>( pInterface );
																	this->Set( (T*) ( pInterface ) );
																	if ( this->Get() == NULL )
																	{
																		if ( pInterface )
																		{
																			pInterface->Release();
																			pInterface	= NULL;
																		}
																		// the passed 'iid' is not from the extected type 'T'
																		err	= kVCOMError_InvalidArg;
																	}
																	else
																		err	= kVCOMError_NoError;
																}
															}
															return err;
														}
		};

		typedef VCOMSinkPtr<IEventSink>					IEventSinkPtr;

		// ----------------------------------------------------------------------------------------------------
		// {07ECFCEE-F6FF-4B66-8834-9DEB295F3605}
		static const TSinkIID IID_MenuEventSink = { 0x7ecfcee, 0xf6ff, 0x4b66, { 0x88, 0x34, 0x9d, 0xeb, 0x29, 0x5f, 0x36, 0x5 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IMenuEventSink : public IEventSink
		{
		public:
			virtual Sint32 VCOM_CALLTYPE	Execute(MenuMessage* message) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {FACD1155-8A14-4349-AEDB-B1C2CC7D771D}
		static const TSinkIID IID_ParametricEventSink = { 0xfacd1155, 0x8a14, 0x4349, { 0xae, 0xdb, 0xb1, 0xc2, 0xcc, 0x7d, 0x77, 0x1d } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IParametricEventSink : public IEventSink
		{
		public:
			virtual Sint32 VCOM_CALLTYPE	Execute(ParametricMessage* message) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {55B1C992-D5E3-40A4-B280-D8D8CDB61488}
		static const TSinkIID IID_ToolEventSink = { 0x55b1c992, 0xd5e3, 0x40a4, { 0xb2, 0x80, 0xd8, 0xd8, 0xcd, 0xb6, 0x14, 0x88 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IToolEventSink : public IEventSink
		{
		public:
			virtual Sint32 VCOM_CALLTYPE	Execute(ToolMessage* message) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {C6038753-6AAD-4EE9-959F-41622C3B5AC7}
		static const TSinkIID IID_VSFunctionsEventSink = { 0xc6038753, 0x6aad, 0x4ee9, { 0x95, 0x9f, 0x41, 0x62, 0x2c, 0x3b, 0x5a, 0xc7 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IVSFunctionsEventSink : public IEventSink
		{
		public:
			virtual Sint32 VCOM_CALLTYPE	Execute(Sint32 action, PluginLibraryArgTable* argumentTable) = 0;
		};
	}
}
