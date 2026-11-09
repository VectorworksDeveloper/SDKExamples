//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		// {FF1BA83A-211E-4660-B3FC-35E84FDB58D2}
		static const VWIID IID_DBConnectionString	= { 0xff1ba83a, 0x211e, 0x4660, { 0xb3, 0xfc, 0x35, 0xe8, 0x4f, 0xdb, 0x58, 0xd2 } };

		class DYNAMIC_ATTRIBUTE IDBConnectionString : public IVWUnknown
		{
		public:
			virtual TXString		VCOM_CALLTYPE Get() = 0;
			virtual VCOMError		VCOM_CALLTYPE Set(const TXString& connectionString) = 0;
			virtual VCOMError		VCOM_CALLTYPE Set(IDBConnectionString* connectionString) = 0;
			virtual VCOMError		VCOM_CALLTYPE SetConnectionParams(const TXString& connectionParams) = 0;
			virtual TXString		VCOM_CALLTYPE GetConnectionParams() = 0;

			virtual Sint32			VCOM_CALLTYPE GetDriverID() = 0;
			virtual void			VCOM_CALLTYPE SetDriverID(const Sint32& id) = 0;
			virtual void			VCOM_CALLTYPE SetDriverID(const TXString & version, const TXString & driver = "") = 0;
			virtual	TXString		VCOM_CALLTYPE GetDriver() = 0;
			virtual void			VCOM_CALLTYPE SetDriver(const TXString & driver) = 0;
			virtual TXString		VCOM_CALLTYPE GetDSN() = 0;
			virtual	void			VCOM_CALLTYPE SetDSN(const TXString& dsn) = 0;
			virtual bool			VCOM_CALLTYPE IsDSNEmpty() = 0;
			virtual TXString		VCOM_CALLTYPE GetSDSN() = 0;
			virtual	void			VCOM_CALLTYPE SetSDSN(const TXString& sdsn) = 0;
			virtual TXString		VCOM_CALLTYPE GetDBQ() = 0;
			virtual	void			VCOM_CALLTYPE SetDBQ(const TXString& dbq) = 0;
			virtual TXString		VCOM_CALLTYPE GetDefaultDir() = 0;
			virtual void			VCOM_CALLTYPE SetDefaultDir(const TXString& dir) = 0;
			virtual	TXString		VCOM_CALLTYPE GetServer() = 0;
			virtual void			VCOM_CALLTYPE SetServer(const TXString& srv) = 0;
			virtual TXString		VCOM_CALLTYPE GetDataBase() = 0;
			virtual	void			VCOM_CALLTYPE SetDataBase(const TXString& db) = 0;
			virtual TXString		VCOM_CALLTYPE GetExtensions() = 0;
			virtual void			VCOM_CALLTYPE SetExtensions(const TXString& ext) = 0;
			virtual	TXString		VCOM_CALLTYPE GetProvider() = 0;
			virtual void			VCOM_CALLTYPE SetProvider(const TXString& prvd) = 0;
			virtual TXString		VCOM_CALLTYPE GetDataSource() = 0;
			virtual	void			VCOM_CALLTYPE SetDataSource(const TXString& ds) = 0;
			virtual TXString		VCOM_CALLTYPE GetExtProp() = 0;
			virtual void			VCOM_CALLTYPE SetExtProp(const TXString& extProp) = 0;
			virtual	TXString		VCOM_CALLTYPE GetUsername() = 0;
			virtual void			VCOM_CALLTYPE SetUsername(const TXString& usr) = 0;
			virtual TXString		VCOM_CALLTYPE GetFIL() = 0;
			virtual	void			VCOM_CALLTYPE SetFIL(const TXString& fil) = 0;
			virtual TXString		VCOM_CALLTYPE GetHost() = 0;
			virtual	void			VCOM_CALLTYPE SetHost(const TXString& host) = 0;
			virtual TXString		VCOM_CALLTYPE GetPort() = 0;
			virtual	void			VCOM_CALLTYPE SetPort(const TXString& port) = 0;
			virtual void			VCOM_CALLTYPE GetPassword(TXString& pass) = 0;
			virtual void			VCOM_CALLTYPE SetPassword(const TXString& pass) = 0;
			virtual	bool			VCOM_CALLTYPE HasPassword() = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBConnectionString>		IDBConnectionStringPtr;
	}
}
