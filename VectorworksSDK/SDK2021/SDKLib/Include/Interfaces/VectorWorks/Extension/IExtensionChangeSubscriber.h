//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum class EUndoChangeType
		{
			Create = 0,
			Modify,
			Delete,
			Rename,
			MoveVector,
			MoveList,
			DeleteUndoPlaceholder,
			MoveUndoPlaceholder
		};

		enum class EChangeTypeFlags
		{
			CreateFlag = 1 << (Uint32) EUndoChangeType::Create,
			ModifyFlag = 1 << (Uint32) EUndoChangeType::Modify,
			DeleteFlag = 1 << (Uint32) EUndoChangeType::Delete,
			RenameFlag = 1 << (Uint32) EUndoChangeType::Rename,
			MoveVectorFlag = 1 << (Uint32) EUndoChangeType::MoveVector,
			MoveListFlag = 1 << (Uint32) EUndoChangeType::MoveList,
			DeleteUndoPlaceholderFlag = 1 << (Uint32) EUndoChangeType::DeleteUndoPlaceholder,
			MoveUndoPlaceholderFlag = 1 << (Uint32) EUndoChangeType::MoveUndoPlaceholder,

			// The flags that results in a list modification (i.e. prev, next, parent etc. is changed)
			ListModificationFlag =	(Uint32) EChangeTypeFlags::CreateFlag |
									(Uint32) EChangeTypeFlags::DeleteFlag |
									(Uint32) EChangeTypeFlags::MoveListFlag |
									(Uint32) EChangeTypeFlags::MoveUndoPlaceholderFlag |
									(Uint32) EChangeTypeFlags::DeleteUndoPlaceholderFlag,

			// All the flags
			AnyFlag =	(Uint32) EChangeTypeFlags::CreateFlag |
						(Uint32) EChangeTypeFlags::ModifyFlag |
						(Uint32) EChangeTypeFlags::DeleteFlag |
						(Uint32) EChangeTypeFlags::RenameFlag |
						(Uint32) EChangeTypeFlags::MoveVectorFlag |
						(Uint32) EChangeTypeFlags::MoveListFlag |
						(Uint32) EChangeTypeFlags::DeleteUndoPlaceholderFlag |
						(Uint32) EChangeTypeFlags::MoveUndoPlaceholderFlag
		};

		// Define bitwise operators for the flags enum, as they are used often.
		inline Uint32 operator | (EChangeTypeFlags lhs, EChangeTypeFlags rhs)
		{
			return static_cast<Uint32>(static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs));
		}

		inline Uint32 operator & (EChangeTypeFlags lhs, EChangeTypeFlags rhs)
		{
			return static_cast<Uint32>(static_cast<Uint32>(lhs) & static_cast<Uint32>(rhs));
		}

		// ----------------------------------------------------------------------------------------------------
		class IChangeCollectionContext
		{
			public:
				class IChangeItem
				{
					public:
						virtual ~IChangeItem() {}

						virtual Uint32	GetChangeFlags() const = 0;
				};

			public:
				virtual		~IChangeCollectionContext() {}

				virtual bool IterateNonSuspendedObjects(std::function<bool (const MCObjectHandle&, const IChangeItem&)> callback) const = 0;
				virtual bool IterateAllObjects(std::function<bool (const MCObjectHandle&, const IChangeItem&)> callback) const = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {237FC113-8C84-46A3-9FF8-98674CEFE0CC}
		static const VWGroupID GROUPID_ExtensionChangeSubscriber = { 0x237fc113, 0x8c84, 0x46a3, { 0x9f, 0xf8, 0x98, 0x67, 0x4c, 0xef, 0xe0, 0xcc } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for an change subscriber
		class DYNAMIC_ATTRIBUTE IExtensionChangeSubscriber : public IExtension
		{
			public:
				virtual void		VCOM_CALLTYPE	Notify(IChangeCollectionContext* context) = 0;
				virtual IEventSink* VCOM_CALLTYPE	QueryEventSink(const TSinkIID& iid) { return nullptr; }
		};

		typedef VCOMPtr<IExtensionChangeSubscriber>	IExtensionChangeSubscriberPtr;
	}
}
