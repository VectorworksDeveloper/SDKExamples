//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_EXCEPTIONS__H
#define VECTORWORKS_EXCEPTIONS__H

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		class VWBadObjectTypeException : public VWException
		{
		public:
#ifdef _DEBUG
			VWBadObjectTypeException(Sint32 err, const char* desc, const char* szFile, size_t line) : VWException(err, desc, szFile, line)	{}
#else
			VWBadObjectTypeException(Sint32 err, const char* desc) : VWException(err, desc)	{}
#endif
			virtual	~VWBadObjectTypeException()							{}
		};


		class VWCannotCreateObjectException : public VWException
		{
		public:
#ifdef _DEBUG
			VWCannotCreateObjectException(Sint32 err, const char* desc, const char* szFile, size_t line) : VWException(err, desc, szFile, line)	{}
#else
			VWCannotCreateObjectException(Sint32 err, const char* desc) : VWException(err, desc)	{}
#endif
			virtual	~VWCannotCreateObjectException()		{}
		};
	}
}

#endif // VECTORWORKS_EXCEPTIONS__H