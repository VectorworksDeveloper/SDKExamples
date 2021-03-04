//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// ------------------------------------------------------------------------------------------------------
		// Examples of using the encryption API
		//
		//	TXString	keyword = "5553ED6F135A4C589313CED27D5E95B2";	// max 32 bytes
		//	TXString	data	= "a chunk of private data to be hold encrypted";
		//	
		//	NNA_SCOPE // Example 1
		//	{
		//		// Holding encrypted data inside a context of a persistent class instance
		//		CEncryptedData	encrypter;
		//		encrypter.Set( data, keyword );
		//	
		//		CEncryptedData	decrypter = encrypter;
		//		TXString outData = decrypter.Get( keyword );
		//		outData = outData;
		//	}
		//	
		//	NNA_SCOPE // Example 2
		//	{
		//		// Holding encrypted data through a memory buffer (without persistent instance)
		//		std::vector<char> buffer;
		//		size_t bufferDataSize = 0; // this is needed in order to make sense of the data when decrypting
		//		
		//		NNA_SCOPE // Encrypt
		//		{
		//			CEncryptedData	encrypter;
		//			encrypter.Set( data, keyword );
		//			encrypter.GetMemory( buffer );
		//			bufferDataSize = encrypter.GetDataSize();
		//		}
		//		
		//		NNA_SCOPE // Decript
		//		{
		//			CEncryptedData	decrypter( buffer, bufferDataSize );
		//			TXString outData = decrypter.Get( keyword );
		//			outData = outData;
		//		}
		//	}
		//	
		//	NNA_SCOPE // Example 3
		//	{
		//		// Holding encrypted data through a memory buffer packaging the dataSize in the buffer
		//		std::vector<char> buffer;
		//	
		//		NNA_SCOPE
		//		{
		//			CEncryptedData	encrypter;
		//			encrypter.Set( data, keyword );
		//			encrypter.GetMemory( buffer );
		//			size_t bufferDataSize = encrypter.GetDataSize();
		//			// add the dataSize at the beginning of the buffer
		//			buffer.insert( buffer.begin(), (const char*)&bufferDataSize, ((const char*)&bufferDataSize) + sizeof(Uint64) );
		//		}
		//		
		//		NNA_SCOPE
		//		{
		//			if ( buffer.size() > sizeof(Uint64) )
		//			{
		//				// retrieve the data size from the end of the buffer, and prepare it for decoding
		//				size_t bufferDataSize = *((Uint64*)&buffer[0]);
		//				CEncryptedData	decrypter( &buffer[sizeof(Uint64)], buffer.size()-sizeof(Uint64), bufferDataSize );
		//				TXString outData = decrypter.Get( keyword );
		//				outData = outData;
		//			}
		//		}
		//	}


		// ------------------------------------------------------------------------------------------------------
		class CEncryptedData
		{
		public:
						CEncryptedData();
						CEncryptedData(const void* memory, size_t memorySize, size_t dataSize);
						CEncryptedData(const std::vector<char>& memory, size_t dataSize);
						CEncryptedData(const CEncryptedData& src);
			virtual		~CEncryptedData();

			CEncryptedData&	operator=(const CEncryptedData& src);

			// Encrypt/Decrypt the data with the provided 'keyword'
			// Note: keyword should not exceed 32 bytes in UTF8 encoding

			TXString	Get(const TXString& keyword);
			bool		Set(const TXString& data, const TXString& keyword);
			
			bool		Get(std::vector<char>& outData, const TXString& keyword);
			bool		Set(const std::vector<char>& data, const TXString& keyword);

			bool		IsEqualTo(const CEncryptedData& data, const TXString& keyword) const;
			bool		IsEqualTo(const TXString& data, const TXString& keyword) const;
			bool		IsEmpty() const;
		
			// Retrieve the encrypted buffer
			void			GetMemory(std::vector<char>& outMemory) const;	// as an array
			const void*		GetMemory() const;		// as memory block - start and size
			size_t			GetMemorySize() const;	// (const void*, size_t)
			size_t			GetDataSize() const;	// data size stored in the memory. this is needed to decrypt as it is not stored in the memory

		private:
			std::vector<char>	fMemory;
			size_t				fDataSize;
		};
	}
}
