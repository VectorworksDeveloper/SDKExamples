#pragma once

namespace DemoSystem
{
	namespace UI
	{
		struct SParamInfo
		{
			bool													fBoolValue;
			Sint32													fIntValue;
			double													fDoubleValue;
			TXString												fStrValue;
			VectorWorks::EnergyAnalysis::CSystemDataParam::EType	fParamType;
			TXString												fName;
		};

		class CDlgSysObjEditParam : public VWDialog
		{
		public:
								CDlgSysObjEditParam(const SParamInfo& paramInfo);
			virtual				~CDlgSysObjEditParam();

			bool				GetParamValueBool() const;
			Sint32				GetParamValueInt() const;
			double				GetParamValueDouble() const;
			TXString			GetParamValueString() const;

		// virtuals
		protected:
			virtual bool		CreateDialogLayout();
			virtual void		OnInitializeContent();
			virtual void		OnDDXInitialize();
			virtual void		OnUpdateUI();

		// events
		protected:
			void				InitParamNameWidth();

		// dispatch map
		protected:
			DEFINE_EVENT_DISPATH_MAP;

		// DDX
		protected:
			bool					fParamValueBool;
			Sint32					fParamValueInt;
			double					fParamValueReal;
			TXString				fParamValueTxt;

		// Inner data
		private:
			TXString				fParamName;
			size_t					fSwapPaneIndx;

		};
	}
}
