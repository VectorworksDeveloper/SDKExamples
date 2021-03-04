//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_LOCUS_3D_OBJECT__H
#define VECTORWORKS_LOCUS_3D_OBJECT__H

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		class VWLocus3DObj : public VWObject
		{
		public:
							VWLocus3DObj(const VWPoint3D& pt);
							VWLocus3DObj(MCObjectHandle hLocus3D);
							VWLocus3DObj(const VWLocus3DObj& src);
			virtual			~VWLocus3DObj();

			VWLocus3DObj&	operator=(const VWLocus3DObj& src);

		public:
			void			SetPoint(const VWPoint3D& pt);
			VWPoint3D		GetPoint() const;

			virtual void	GetObjectMatrix(VWTransformMatrix& outMatrix) const;
			virtual void	SetObjectMatrix(const VWTransformMatrix& matrix);
		// tool
		public:
			// Return true if the specified object handle is 3D locus
			static bool		IsLocus3DObject(MCObjectHandle hObj);
		};
	}
}

#endif // VECTORWORKS_LOCUS_3D_OBJECT__H