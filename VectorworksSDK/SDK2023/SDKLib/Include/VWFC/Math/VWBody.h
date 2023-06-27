//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Math
	{
		class VWBody
		{
		public:
			// construction
						VWBody();
						VWBody(Sint32 bodyID);
						VWBody(const VWBody& src);
			virtual		~VWBody();

			VWBody&		operator=(const VWBody& src);

		public:
			size_t		GetFacesCount();
			VWBodyFace	GetFaceAt(size_t index);
			size_t		GetEdgesCount();
			VWBodyEdge	GetEdgeAt(size_t index);

			bool		RayShoot(const VWPoint3D& pt, const VWPoint3D& vector, VWBodyFace& outFace, VWBodyEdge& outEdge);

			Sint32		GetBodyID() const;

		private:
			IVWUnknown*	fp;
			Sint32			fBodyID;
		};
	}
}