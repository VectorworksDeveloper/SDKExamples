//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Math;

	namespace VWObjects
	{
		class VWBodyObj : public VWObject
		{
		public:
							VWBodyObj();
							VWBodyObj(const VWBodyObj& src);
							VWBodyObj(MCObjectHandle hObj);
			virtual			~VWBodyObj();

			VWBodyObj&		operator=(const VWBodyObj& src);

		public:
			size_t			GetBodyCount();
			bool			GetBody(size_t index, VWBody& outBody);

			void			AddToolHighlighting(const VWBodyFace& face);
			void			AddToolHighlighting(const VWBodyEdge& edge);

		// tool
		public:
			// Return true if the specified object handle is suitable for body creation
			static bool		IsBodyObject(MCObjectHandle hObj);

		private:
			typedef TXGenericArray< Sint32 >	TBodiesArray;

			TBodiesArray		fBodies;
			IVWUnknown*			fpAPI;
			IVWUnknown*			fp;
		};
	}
}