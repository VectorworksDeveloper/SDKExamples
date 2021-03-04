#ifndef _MISC_GRAPHICS_H_
#define _MISC_GRAPHICS_H_ 1

#pragma once



	enum class EViewTypes {
		NotSet,
		Top,
		Bottom,
		TopBottomCut,
		Front,
		Back,
		FrontBackCut,
		Left,
		Right,
		LeftRightCut,
		TopPlan,		// use this to add objects into the main drawing list of a symbol or plug-in and ensure 2D components synchronization
		ViewTypesNumber = TopPlan,

	};

    enum class ESetSpecialGroupErrors {
        NoError,
        CannotSet_BadData,
        CannotSet_UserSpecified,
    };

	enum class ETopPlanViewComponent {
		Top,
		TopBottomCut
	};

	enum class ELevelsOfDetail {
		NotSet = 0,
		Low = 1,
		Medium = 2,
		High = 4,
		All = 7
	};



#endif // _MISC_GRAPHICS_H_
