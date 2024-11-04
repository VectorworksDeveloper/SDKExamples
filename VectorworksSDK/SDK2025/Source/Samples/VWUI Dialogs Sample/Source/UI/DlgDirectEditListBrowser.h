#pragma once

namespace UI
{
	enum class EFirstGroupModes
	{
		eUserName			= 0,
		eWorkspace			= 1,
		eTool				= 2,
		eUse				= 3,
		eUnits				= 4,
		eHidePreviousField	= 5
	};


	struct SSelectedRowInfo
	{
		SSelectedRowInfo(	const TXString&	UserName,
			const TXString&	WorkSpace,
			const TXString&	ToolName,
			bool			Use,
			const TXString&	Units,
			bool			HidePreviousField
		)
		{
			fUserName			= UserName;
			fWorkSpace			= WorkSpace;
			fToolName			= ToolName;
			fUse				= Use;
			fUnits				= Units;
			fHidePreviousField	= HidePreviousField;
		}

		TXString	fUserName;
		TXString	fWorkSpace;
		TXString	fToolName;
		bool		fUse;
		TXString	fUnits;
		bool		fHidePreviousField;
	};

	class CDlgDirectEditListBrowser : public VWDialog
	{
	public:
		CDlgDirectEditListBrowser();
		virtual			~CDlgDirectEditListBrowser();

		// virtuals
	protected:
		virtual bool		CreateDialogLayout();
		virtual void		OnInitializeContent();
		virtual void		OnDDXInitialize();
		virtual void		OnUpdateUI();

		// events
	protected:
		//virtual void		OnDefaultButtonEvent();

		// dispatch map
	protected:
		DEFINE_EVENT_DISPATH_MAP;
		virtual void				OnListBrowserDirectEdit( TControlID controlID, VWListBrowserEventArgs& eventArgs );

		// DDX
	protected:

	private:
		void				UpdateLB();
		void				SetLBRow( size_t row );
		void				UpdateTextCel( const size_t& row, const size_t& column, const TXString& newValue );

		// Inner data
	private:

		std::vector< SSelectedRowInfo > fRowInfo;


		const StrVec fUserName	{ "Ivan", "Stoqn", "Georgi" };
		const StrVec fUnits		{ "mm", "inches" };
		std::unordered_map< TXString /*WorkSpaces*/, StrVec /*ToolName*/ > fWorkSpacesData {	{"Spotlight"	, {"Lighting Device"	, "Hanging Position"	, "Align and Distribute"	} },
																								{"Architect"	, {"Reference Marker"	, "Section Elevation"	, "Interior Elevation"		} },
																								{"Designer"		, {"Fastener"			, "Acorn Nut"			, "Eye bolt"				} },
																							};


	};
}
