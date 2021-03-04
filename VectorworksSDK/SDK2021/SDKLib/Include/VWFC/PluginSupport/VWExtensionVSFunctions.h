//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWPluginLibraryArgTable.h"
#include "VWPluginLibraryRoutine.h"

namespace VWFC
{
	namespace PluginSupport
	{
		using namespace VectorWorks::Extension;

		// ------------------------------------------------------------------------------------------------------
		class VWVSFunctions_EventSink	: public VCOMImpl<IVSFunctionsEventSink>
		{
		public:
								VWVSFunctions_EventSink(IVWUnknown* parent);
			virtual				~VWVSFunctions_EventSink();

			void				SetUniversalName(const TXString& name);

		public:
			// if 'isLocalMemory' is true then the routine memory will be deleted by the destructor
			// pass in 'false' if you are using custom routines (pointer to a local variable)
			void				AddRoutine(VWPluginLibraryRoutine* routine, bool isLocalMemory);

		// IVSFunctionsEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE		Execute(Sint32 action, PluginLibraryArgTable* argumentTable);

		protected:
			struct SRoutinesDef {
				VWPluginLibraryRoutine*	fRoutine;
				bool					fIsLocalMemory;
				SRoutinesDef*			fPrev;
			};

			SRoutinesDef*		fRoutines;
			TXString			fUnivName;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SFunctionParamDef
		{
			const char*				fName;
			EPluginLibraryArgType	fType;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SFunctionDef
		{
			const char*			fName;
			const char*			fCategory;
			const char*			fDescription;
			Sint32				fVersion;
			Sint8				fScope;
			bool				fHasReturnValue;
			SFunctionParamDef	fParams[11];
		};

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionVSFunctions : public VCOMImmediateImpl<IExtensionVSFunctions>
		{
		public:
											VWExtensionVSFunctions(	CallBackPtr cbp,
																	const SFunctionDef* arrFunctions);
			virtual							~VWExtensionVSFunctions();

		// IExtensionApp
		public:
			virtual IEventSink* VCOM_CALLTYPE			QueryEventSink(const TSinkIID& iid);

		// IExtensionVSFunctions
		public:
			virtual Uint32 VCOM_CALLTYPE				Initialize();
			virtual size_t VCOM_CALLTYPE				GetFunctionsCount();
			virtual const TXString& VCOM_CALLTYPE		GetFunctionName(size_t funcIndex);
			virtual const TXString& VCOM_CALLTYPE		GetFunctionCategory(size_t funcIndex);
			virtual const TXString& VCOM_CALLTYPE		GetFunctionDescription(size_t funcIndex);
			virtual Sint32 VCOM_CALLTYPE				GetFunctionVersion(size_t funcIndex);
			virtual Sint8 VCOM_CALLTYPE					GetFunctionScope(size_t funcIndex);
			virtual bool VCOM_CALLTYPE					GetFunctionHasReturnValue(size_t funcIndex);
			virtual size_t VCOM_CALLTYPE				GetFunctionParamsCount(size_t funcIndex);
			virtual const TXString& VCOM_CALLTYPE		GetFunctionParamName(size_t funcIndex, size_t paramIndex);
			virtual EPluginLibraryArgType VCOM_CALLTYPE	GetFunctionParamType(size_t funcIndex, size_t paramIndex);

		protected:
			virtual void					OnRefCountZero();
			virtual void					InitRoutines() = 0;
			virtual IVSFunctionsEventSink*	CreateVSFunctionsEventSink(IVWUnknown* parent) = 0;
			virtual bool					GetProtectionSinkIID(TSinkIID& outIID);
			virtual IProviderProtection*	CreateProtectionSink(IVWUnknown* parent);

		protected:
			IVSFunctionsEventSink*	fVSFunctionsEventSink;
			bool					fProtectionObtained;
			bool					fHasProtection;
			TSinkIID				fProtectionSinkIID;
			IProviderProtection*	fProtectionSink;

		private:
			CallBackPtr				fCBP;

			const SFunctionDef*		farrFunctions;
			typedef std::map<const char*, TXString>	TStringCache;
			TStringCache			fmapStringCache;

			typedef	std::pair<TStringCache::iterator, bool> TResultPair;
		};
	}
}

#define DEFINE_VWVSFunctions	DEFINE_VWVSFunctionsExtension;	\
								virtual void		InitRoutines();

#define BEGIN_VWVSFunctions( TClass, TName, TVer, TIID1, TIID2, TIID3, TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11) \
	IVSFunctionsEventSink*			TClass::CreateVSFunctionsEventSink(IVWUnknown* parent)	{ return SDK_NEW VWVSFunctions_EventSink( parent ); }		\
	const VWIID&					TClass::_GetIID()									{ static VWIID iid = { TIID1, TIID2, TIID3, {TIID4, TIID5, TIID6, TIID7, TIID8, TIID9, TIID10, TIID11} }; return iid; }	\
	Sint32 VCOM_CALLTYPE			TClass::GetVersion()								{ return TVer; }										\
	const TXString& VCOM_CALLTYPE	TClass::GetUniversalName()							{ fUniverslalName = TName; return fUniverslalName; }	\
	void							TClass::InitRoutines() {							\
										VWVSFunctions_EventSink* eventSink = dynamic_cast<VWVSFunctions_EventSink*> ( fVSFunctionsEventSink ); \
										VWFC_ASSERT( eventSink ); \
										if ( eventSink ) { 

#define ADD_VWVSFunctions_ROUTINE( TRoutine )		eventSink->AddRoutine( SDK_NEW TRoutine(), false );
#define ADD_VWVSFunctions_UserROUTINE( TRoutine )	eventSink->AddRoutine( TRoutine, true );
								

#define END_VWVSFunctions				} }
