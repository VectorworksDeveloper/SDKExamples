//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		class VWObjectIterator
		{
		public:
							VWObjectIterator(MCObjectHandle hObj);
			virtual			~VWObjectIterator();
		
			bool			operator==(const VWObjectIterator& src) const;
			bool			operator!=(const VWObjectIterator& src) const;

		public:
			MCObjectHandle		MoveNext();
			MCObjectHandle		MoveNextSelected();
			MCObjectHandle		MovePrev();
			MCObjectHandle		MovePrevSelected();
			MCObjectHandle		GetObject() const;
			MCObjectHandle		operator++();
			MCObjectHandle		operator++(Sint32);
			MCObjectHandle		operator--();
			MCObjectHandle		operator--(Sint32);
			MCObjectHandle		operator*() const;

								operator MCObjectHandle() const;

			short				GetType() const;

		// Tools
		public:
			static MCObjectHandle	NextObject(MCObjectHandle hObj);
			static MCObjectHandle	PrevObject(MCObjectHandle hObj);
			static MCObjectHandle	NextSelectedObject(MCObjectHandle hObj);
			static MCObjectHandle	PrevSelectedObject(MCObjectHandle hObj);
			

		protected:
			MCObjectHandle	fhObject;
		};
	}
}