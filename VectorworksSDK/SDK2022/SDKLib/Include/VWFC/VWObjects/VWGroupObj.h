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
		class VWGroupObj : public VWObject
		{
		public:
								VWGroupObj();
								VWGroupObj(MCObjectHandle hGroup);
								VWGroupObj(const VWGroupObj& src);
			virtual				~VWGroupObj();

			VWGroupObj&			operator=(const VWGroupObj& src);

		public:
			// add specified object into this container
			void				AddObject(MCObjectHandle hObj);

			// delete objects inside the group
			void				DeleteAllInnerObjects(bool useUndo = false);
			
			// Return the first object in this container
			MCObjectHandle		GetFirstMemberObject() const;
			// Return iterator to the first object in this container
			VWObjectIterator	GetFirstMemberIterator() const;
			
			// Returns the last object in this container
			MCObjectHandle		GetLastMemberObject() const;
			// Return iterator to the last object in this container
			VWObjectIterator	GetLastMemberIterator() const;

			// C++11 style iteration
			//	for(MCObjectHandle h : VWGroupObj(hGroupLike))
			//	{
			//		...
			VWObjectIterator	begin() const;
			VWObjectIterator	end() const;

			// Find a handle in a list (searching children and aux lists).
			// Return true if the handle is found. 
			Boolean				FindHandleDeep(MCObjectHandle hObj) const;

			// searches for the first object of the specified type in the child list
			MCObjectHandle		FindObject(short type, MCObjectHandle hAfter = nullptr) const;

			// searches for the first object of one of the specified types in the child list
			MCObjectHandle		FindObjectFirstIn(const std::vector<short /*TDType*/>& types, MCObjectHandle hAfter = nullptr) const;

			// searches the child list for the first object of one of the specified types using DFS;
			// will descend into chosen group-like nodes if specified by TDType, empty vector descends into all group-like nodes
			MCObjectHandle		FindObjectFirstInDFS(const std::vector<short /*TDType*/>& types, MCObjectHandle hAfter = nullptr,
													 const std::vector<short /*TDType*/>& descendInto = {}) const;

			// searches the child list for the first object of one of the specified types using BFS;
			// always starts searching from this->fhObject and ignores all potential elements before hAfter;
			// will descend into chosen group-like nodes if specified by TDType, empty vector descends into all group-like nodes
			MCObjectHandle		FindObjectFirstInBFS(const std::vector<short /*TDType*/>& types, MCObjectHandle hAfter = nullptr,
													 const std::vector<short /*TDType*/>& descendInto = {}) const;

			// move all objects within the group
			void				MoveObjectDeep(const VWPoint2D& offset);
			void				Move3DObjectDeep(const VWPoint3D& offset);

			// set the specified transformation to all objects within this group
			// and to all other going reqursively down the groups
			void				ApplyTransformDeep(const VWTransformMatrix& matrix);

			// tool
		public:
			// Create group containing all selected objects
			static MCObjectHandle	GroupSelection();

			// Return true if the specified object handle is group
			static bool			IsGroupObject(MCObjectHandle hObj);
			static bool			IsGroupLikeObject(MCObjectHandle hObj);

		protected:
			// this is constructor for inheritant of this class
			// so this class will not create a new group but let the inheritant do that job
								VWGroupObj(Sint32);

		private:
			void			ApplyTransformDeepReq(MCObjectHandle hObject, const VWTransformMatrix& matrix);
			void			MoveDeepReq(MCObjectHandle hObject, const VWPoint2D& offset);
			void			MoveDeepReq(MCObjectHandle hObject, const VWPoint3D& offset);
		};
	}
}