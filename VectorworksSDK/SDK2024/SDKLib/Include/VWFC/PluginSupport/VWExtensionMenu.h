//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		using namespace VectorWorks::Extension;

		// ------------------------------------------------------------------------------------------------------
		class VWMenu_EventSink	: public VCOMImpl<IMenuEventSink>
		{
		public:
								VWMenu_EventSink(IVWUnknown* parent);
			virtual				~VWMenu_EventSink();

			void				SetUniversalName(const TXString& name);

		public:
			virtual void		DoInterface();
			virtual bool		GetItemEnabled();
			virtual void		OnDynamicVariableChunkUpdate();

		public:
			virtual SintptrT	GetUserData() const;
			virtual void		SetUserData(SintptrT userData);
			Sint32				GetResult() const;
			void				SetResult(Sint32 result);
			void				SetMenuChunkInfo(MenuChunkInfo* pMenuChunkInfo);

			// The default event notificaiotn
			// if no virutal is present for an event, this function is called to allow the user to catch everything
			virtual Sint32		OnDefaultEvent(MenuMessage* message);

		// IMenuEventSink
		public:
			virtual Sint32 VCOM_CALLTYPE			Execute(MenuMessage* message);

		protected:
			TXString			fUnivName;
			MenuChunkInfo*		fpMenuChunkInfo;
			Sint32				fResult;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SMenuDef
		{
			Uint16			fNeeds;
			Uint16			fNeedsNot;
			SResString		fTitle;
			SResString		fCategory;
			SResString		fHelpText;
			Sint16			fVersionCreated;
			Sint16			fVersoinModified;
			Sint16			fVersoinRetired;
			const char*		fOverrideHelpID;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SMenuChunkDef
		{
			SResString		fItemText;
			SResString		fHelpText;
			const char*		fOverrideHelpID;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SMenuDef_Legacy
		{
			Uint16			fNeeds;
			Uint16			fNeedsNot;
			SSTRResource	fTitle;
			SSTRResource	fCategory;
			STEXTResource	fHelpText;
			Sint16			fVersionCreated;
			Sint16			fVersoinModified;
			Sint16			fVersoinRetired;
			const char*		fOverrideHelpID;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SMenuChunkDef_Legacy
		{
			SSTRResource	fItemText;
			STEXTResource	fHelpText;
			const char*		fOverrideHelpID;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionMenu :	public VCOMImmediateImpl<IExtensionMenu>
		{
		public:
											VWExtensionMenu(	CallBackPtr cbp,
																const SMenuDef& menuDef,
																const SMenuChunkDef* arrMenuChunks=NULL,
																EMenuChunkType chunkType=eMenuChunkType_Regular);
											VWExtensionMenu(	CallBackPtr cbp,
																const SMenuDef_Legacy& menuDef,
																const SMenuChunkDef_Legacy* arrMenuChunks=NULL,
																EMenuChunkType chunkType=eMenuChunkType_Regular);
			virtual							~VWExtensionMenu();

		// IExtensionMenu
		public:
			virtual const TXString& VCOM_CALLTYPE	GetTitle();
			virtual const TXString& VCOM_CALLTYPE	GetCategory();
			virtual const TXString& VCOM_CALLTYPE	GetHelpText();
			virtual const TXString& VCOM_CALLTYPE	GetOverrideHelpID(size_t chunkIndex = size_t(-1));
			virtual	void VCOM_CALLTYPE				GetNeedsFlags(Uint16& outNeeds, Uint16& outNeedsNot);
			virtual	void VCOM_CALLTYPE				GetVersionInfo(Sint16& outCreated, Sint16& outModified, Sint16& outRetired);

		// IExtension
		public:
			virtual IEventSink* VCOM_CALLTYPE		QueryEventSink(const TSinkIID& iid);

		protected:
			virtual void						OnRefCountZero();
			virtual IMenuEventSink*				CreateMenuEventSink(IVWUnknown* parent) = 0;
			virtual bool						GetProtectionSinkIID(TSinkIID& outIID);
			virtual IProviderProtection*		CreateProtectionSink(IVWUnknown* parent);

		protected:
			struct SChunkInfo {
				TXString	fItem;
				TXString	fOverrideHelpID;
				TXString	fHelpText;
			};

			typedef std::vector<SChunkInfo>	TSubItemsVector;
			void						GetSubMenuItems(TSubItemsVector& outArrItems);
			void						SetSubMenuItems(const TSubItemsVector& arrItems);

			void						SetTitle(const TXString& value);

		private:
			CallBackPtr						fCBP;

			Uint16							fNeeds;
			Uint16							fNeedsNot;
			Sint16							fVersionCreated;
			Sint16							fVersoinModified;
			Sint16							fVersoinRetired;

			TXString						fstrTitle;
			TXString						fstrHelp;
			TXString						fstrCategory;
			TXString						fstrOverrideHelpID;
			EMenuChunkType					fMenuChunkType;
			bool							fMenuChunkIsDirty;

			TSubItemsVector					farrSubItems;

			class CMenuChunk;

			IMenuEventSink*					fLegacyEventSink;
			CMenuChunk*						fMenuChunkSink;
			bool							fProtectionObtained;
			bool							fHasProtection;
			TSinkIID						fProtectionSinkIID;
			IProviderProtection*			fProtectionSink;

		private:
			// -------------------------------------------------------------------
			class CMenuChunk : public VCOMImpl<IMenuChunk2Provider>
			{
			public:
						CMenuChunk(VWExtensionMenu* parent);
				virtual	~CMenuChunk();

			// IMenuChunk2Provider
			public:
				virtual EMenuChunkType VCOM_CALLTYPE	GetType();
				virtual const TXString& VCOM_CALLTYPE	GetItemHelp(size_t index);
				virtual bool VCOM_CALLTYPE				IsChunkDirty();
				virtual void VCOM_CALLTYPE				ClearChunkDirty();

			// IMenuChunkProvider
			public:
				virtual size_t VCOM_CALLTYPE			GetItemsCount();
				virtual const TXString& VCOM_CALLTYPE	GetItemTitle(size_t index);
				virtual const TXString& VCOM_CALLTYPE	GetOverrideHelpID(size_t index);
 
			private:
				VWExtensionMenu*		fParent;
			};
		};
	}
}
