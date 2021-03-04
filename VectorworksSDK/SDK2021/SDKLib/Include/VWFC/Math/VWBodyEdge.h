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
		class VWBodyEdge
		{
			friend class VWBody;
		public:
			// construction
							VWBodyEdge();
							VWBodyEdge(const VWBodyEdge& src);
			virtual			~VWBodyEdge();

			VWBodyEdge&		operator=(const VWBodyEdge& src);

			bool			IsValid() const;

		public:
			VWNURBSCurve	GetEdgeCurve();

		protected:
							VWBodyEdge(Sint32 edgeID);

			Sint32				GetBodyEdgeID() const;
			void			SetBodyEdgeID(Sint32 id);

		private:
			IVWUnknown*	fp;
			Sint32			fBodyEdgeID;
		};
	}
}