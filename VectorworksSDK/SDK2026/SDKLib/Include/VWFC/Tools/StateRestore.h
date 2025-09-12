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
		// ---------------------------------------------------------------------------------------------------------------
		template<class TYPE> class ValueRestore
		{
		public:
					ValueRestore(TYPE* pVariable, TYPE newValue);
					~ValueRestore();

		private:
			TYPE*	fpVariable;
			TYPE	fOldValue;
		};

		// ---------------------------------------------------------------------------------------------------------------
		// Creating an instance of this class will disable screen refreshes
		// The destructor will restore the screen refresh
		class TDisableScreenRefreshState
		{
		public:
					TDisableScreenRefreshState();
			virtual	~TDisableScreenRefreshState();

		private:
			static size_t	sDisableState;
		};


		///////////////////////////////////////////////////////////////////////////////////
		// implementation
		template<class TYPE> ValueRestore<TYPE>::ValueRestore(TYPE* pVariable, TYPE newValue)
		{
			VWFC_ASSERT( pVariable );
			fpVariable		= pVariable;
			fOldValue		= * fpVariable;
			* fpVariable	= newValue;
		}

		template<class TYPE> ValueRestore<TYPE>::~ValueRestore()
		{
			* fpVariable	= fOldValue;
		}
	}
}