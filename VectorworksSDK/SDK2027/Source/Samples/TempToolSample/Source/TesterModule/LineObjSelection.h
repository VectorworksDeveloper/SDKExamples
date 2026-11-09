//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// strings to create a record.
#define	kStr_TempTool_Record			"NNA_TempTool_Rec"
#define	kStrField_Param_TempTool		"TempToolParam"

namespace TesterModule
{
	// ------------------------------------------------------------------------------------------------------
	class CLineObjSelection
	{
	protected:
							CLineObjSelection();

	public:
		virtual				~CLineObjSelection();

		static CLineObjSelection& Instance();

	public:
		bool				InitializeFromSelection();
		void				Clear();
		
		MCObjectHandle		Get() const;

	private:
		MCObjectHandle		fLineObj;
	};
}