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
		// ------------------------------------------------------------
		enum class EFindObjectOptions
		{
			AllObjs,
			VisibleOnly,
			SelectedOnly,
			UnlockedOnly
		};

		// ------------------------------------------------------------
		enum class EFindObjectTraversalOptions
		{
			Shallow,
			Groups
		};

		// ------------------------------------------------------------
		class CFindObjectAtPoint
		{
		public:
							CFindObjectAtPoint(MCObjectHandle hContainer);
			virtual			~CFindObjectAtPoint();

			void			Search(EFindObjectOptions objOpt, EFindObjectTraversalOptions travOpt, const VWFC::Math::VWPoint3D& pt, double dRadius);

			size_t			GetFoundObjectsCount() const;
			MCObjectHandle	GetFoundObjectAt(size_t index) const;

		protected:
			typedef std::vector<MCObjectHandle>		TObjectsArray;

			void			Search(MCObjectHandle hContainer, TObjectsArray& outArray, EFindObjectOptions objOpt, EFindObjectTraversalOptions travOpt, const VWFC::Math::VWPoint3D& pt, double dRadius);
			bool			CheckObject(MCObjectHandle hObject, const VWFC::Math::VWPoint3D& pt, double dRadius);
			VWPoint3D		UpdatePtWithPlanRotation(MCObjectHandle parentObj, const VWPoint3D& pt) const;

		private:

			MCObjectHandle		fhContainer;
			TObjectsArray		farrFoundObjects;
			bool				fIs3DSearch;
		};
	}
}