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
		// ---------------------------------------------------------------------------------------------------
		class CGenericLogger : public VectorWorks::Scripting::IPythonLogger
		{
		public:
						CGenericLogger(EFolderSpecifier folderSpec, const TXString& logFileName); 
						CGenericLogger(IFolderIdentifier* outputFolderID, const TXString& logFileName);
			virtual		~CGenericLogger();

			void		Flush();

			bool		HadScriptErrors() const;
			void		AddLogLine(const TXString& msg);
			void		AddLogLine(const std::exception& e);

			virtual void VCOM_CALLTYPE LogStdOut(const char* msg);
			virtual void VCOM_CALLTYPE LogStdErr(const char* msg);

		public:
			class CPrefixContext
			{
				friend class CGenericLogger;
			public:
				CPrefixContext(CGenericLogger& parent, const TXString& prefix) : fParent(parent) { fParent.farrPrefix.push_back( prefix ); }
				virtual ~CPrefixContext() { fParent.farrPrefix.pop_back(); }

			protected:
				CGenericLogger&	fParent;
			};

		private:
			IFileIdentifierPtr	fLogFileID;
			TXStringArray		fLogLines;
			TXString			fScriptPrefix;
			bool				fScriptHadErrors;
			TXStringSTLArray	farrPrefix;
		};
	}
}
