//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_LOCUS_2D_OBJECT__H
#define VECTORWORKS_LOCUS_2D_OBJECT__H

#pragma once

namespace VWFC
{
	using namespace Math;

	namespace VWObjects
	{
		class VWLocus2DObj : public VWObject
		{
		public:
							VWLocus2DObj(const VWPoint2D& pt);
							VWLocus2DObj(MCObjectHandle hLocus2D);
							VWLocus2DObj(const VWLocus2DObj& src);
			virtual			~VWLocus2DObj();

			VWLocus2DObj&	operator=(const VWLocus2DObj& src);

		public:
			void			SetPoint(const VWPoint2D& pt);
			VWPoint2D		GetPoint() const;

		// tool
		public:
			// Return true if the specified object handle is 2D locus
			static bool		IsLocus2DObject(MCObjectHandle hObj);
		};
	}
}

#endif // VECTORWORKS_LOCUS_2D_OBJECT__H