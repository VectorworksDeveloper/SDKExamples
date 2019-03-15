//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//

#pragma once

#include <map>

namespace MockUp
{
	// ------------------------------------------------------------------------------------------------------------
	class CMockVectorworksSDKEnvironment
	{
	protected:
					CMockVectorworksSDKEnvironment();
					CMockVectorworksSDKEnvironment(const CMockVectorworksSDKEnvironment& src);

	public:
		virtual		~CMockVectorworksSDKEnvironment();

		static CMockVectorworksSDKEnvironment&	Instance();

	public:
		typedef void		(*TCBPInstaller)(GenericFunctionPtr arrCallbacks[]);
		typedef bool		(*TVCOMInterfaceCreator)(const VWIID& iid, IVWUnknown*& outInterface);

		void		Install(TCBPInstaller installer = NULL, TVCOMInterfaceCreator vcomInterfaceCreator = NULL);
		void		Uninstall();

		void**		GetVCOMCallbackPtr();

		VCOMError	QueryInterface(const VWIID& iid, IVWUnknown** ppInterface);
		VCOMError	DeleteInterface(IVWUnknown* pInterface);
		CBBoolean	CB_Kludge(CBSignedShort selector, void* in, void* out, bool bUseLegacyZ);
		VoidPtr		CB_NewPtr(size_t size);
		void		CB_DisposePtr(void* p);
		GSHandle	CB_NewHandle(size_t size);
		void		CB_DisposeHandle(GSHandle handle);
		CBBoolean	CB_SetHandleSize(GSHandle handle, size_t size);
		void		CB_GetHandleSize(GSHandle handle, size_t& size);
		void		CB_ReduceHandleSize(GSHandle handle, size_t size);
		void		CB_GetHandleState(GSHandle handle, Boolean& isLocked);
		void		CB_SetHandleState(GSHandle handle, Boolean isLocked);

	protected:
		// CBP Support
		static inline GenericFunctionPtr	_FIDToPtr(Sint32 id)	{ return CMockVectorworksSDKEnvironment::Instance().farrCallbacks[ id ]; }

		// VCOM Support
		static inline Sint32				_RegisterInterface(void* pInLibFile, void* pInIID, bool cacheIt)	{ return kVCOMError_NotImplemented; }
		static inline Sint32				_QueryInterface(void* pInIID, void** pInInterface)					{ return CMockVectorworksSDKEnvironment::Instance().QueryInterface( *(VWIID*)pInIID, (IVWUnknown**) pInInterface ); }
		static inline void					_DeleteInterface(void* ppInInterface)								{ CMockVectorworksSDKEnvironment::Instance().DeleteInterface( (IVWUnknown*) ppInInterface ); }

		// Generic function support
		static inline CBBoolean				_CB_Kludge(CBSignedShort selector, void* in, void* out, bool bUseLegacyZ)	{ return CMockVectorworksSDKEnvironment::Instance().CB_Kludge( selector, in, out, bUseLegacyZ ); }
		static inline VoidPtr				_CB_NewPtr(size_t size)														{ return CMockVectorworksSDKEnvironment::Instance().CB_NewPtr( size ); }
		static inline void					_CB_DisposePtr(void* p)														{ CMockVectorworksSDKEnvironment::Instance().CB_DisposePtr( p ); }
		static inline GSHandle				_CB_NewHandle(size_t size)													{ return CMockVectorworksSDKEnvironment::Instance().CB_NewHandle( size ); }
		static inline void					_CB_DisposeHandle(GSHandle handle)											{ CMockVectorworksSDKEnvironment::Instance().CB_DisposeHandle( handle ); }
		static inline CBBoolean				_CB_SetHandleSize(GSHandle handle, size_t size)								{ return CMockVectorworksSDKEnvironment::Instance().CB_SetHandleSize( handle, size ); }
		static inline void					_CB_GetHandleSize(GSHandle handle, size_t& size)							{ CMockVectorworksSDKEnvironment::Instance().CB_GetHandleSize( handle, size ); }
		static inline void					_CB_ReduceHandleSize(GSHandle handle, size_t size)							{ CMockVectorworksSDKEnvironment::Instance().CB_ReduceHandleSize( handle, size ); }
		static inline void					_CB_GetHandleState(GSHandle handle, Boolean& isLocked)						{ CMockVectorworksSDKEnvironment::Instance().CB_GetHandleState( handle, isLocked ); }
		static inline void					_CB_SetHandleState(GSHandle handle, Boolean isLocked)						{ CMockVectorworksSDKEnvironment::Instance().CB_SetHandleState( handle, isLocked ); }

	private:
		IVWUnknown*		CreateStandardInterface(const VWIID& iid);

	private:
		CallBackBlock				fCallbackBlock;
		GenericFunctionPtr			farrCallbacks[ kcbMaximumCallbackDispatchID + 1 ];
		void*						fVCOMCallbackTable[15];
		GenericFunctionPtr			fCustomKludgeFunctionPtr;
		TVCOMInterfaceCreator		fVCOMInterfaceCreator;

		typedef std::map<VWIID, IVWSingletonUnknown*>	TSingletonInterfacesMap;
		TSingletonInterfacesMap		fmapSingletonInterfaces;
	};
}