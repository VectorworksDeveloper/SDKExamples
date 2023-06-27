//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Tools;

	namespace VWObjects
	{
		enum EClassVisibility {
			kClassVisibilityInvisible			= -1,
			kClassVisibilityNormal				= 0,
			kClassVisibilityGrayed				= 2,
			kClassVisibilityDontCare			= 3,
		};

		class VWClass
		{
		public:
									VWClass(InternalIndex index);
									VWClass(const TXString& name);
			virtual					~VWClass();

			operator InternalIndex() const;

		public:
			void					SetThisClassAsDefault() const;
			bool					IsValidClass() const;
			TXString				GetName() const;
			// Objects that belong to that class are assigned to the None class.
			void					DeleteThisClass();

			EClassVisibility		IsClassVisible() const;
			// Does not reset the drawing visiblity automatically
			// VWObject::ResetAllObjectsVis should be called whenever class visibility is changed.
			void					SetClassVisible(EClassVisibility visibility);

			bool					GetUseGraphics() const;
			void					SetUseGraphics(bool use);
		
			VWClassAttr				GetClassAttribs() const;

			bool					EditWithUI() const;

			TXString				GetClassDescription();
			void					SetClassDescription(const TXString& description);

			// Tools
		public:
			static InternalIndex	GetDefaultClass();
			static InternalIndex	GetClassFromHandle(MCObjectHandle hClass);
			static bool				IsValidClassName(const TXString& name);
			static bool				IsValidClassIndex(InternalIndex index);
			static bool				IsValidClassHandle(MCObjectHandle h);
			static InternalIndex	GetClassIDByName(const TXString& name);
			// Returns the largest valid class ID number.
			// The smallest class ID is always the value obtained by calling GetNoneClassID,
			// the ID of the class 'None'.
			static InternalIndex	GetMaxClassIndex();
			// Returns the ID of the Guides class, first creating it and setting its attributes if it doesn't already exist.
			// Note that the name of the Guides class is localized and won't always be 'Guides'.
			static InternalIndex	AddGuidesClass();
			static InternalIndex	GetDimensionClassIndex();
			static InternalIndex	GetNoneClassIndex();

			// program variables for classes
			static EClassOptions	GetProgramVar_ClassOptions();

			static InternalIndex	CreateClassWithUI(TXString& inOutName);

			static void				ForEachClass(bool doGuestClasses, std::function<void(const VWClass& clas)> callback);

		protected:
			InternalIndex		fClassIndex;
		};
	}
}