//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"
#include "DialogEventArgs.h"

namespace VWFC
{
	namespace VWUI
	{
		// -----------------------------------------------------------------------------
		enum EStandardImageID {
			kStandardImageID_None,
			kStandardImageID_Blank,
			kStandardImageID_DiamondBlack,
			kStandardImageID_DiamondHollow,
			kStandardImageID_DiamondGray,
			kStandardImageID_RedCrossedCircle,
			kStandardImageID_CheckMark,
			kStandardImageID_CheckMarkWhite,
			kStandardImageID_LeftBlackArrow,
			kStandardImageID_RightBlackArrow,
			kStandardImageID_LeftHollowArrow,
			kStandardImageID_RightHollowArraw,
			kStandardImageID_LeftThinArrow,
			kStandardImageID_RightThinkArrow,
			kStandardImageID_BallBlack,
			kStandardImageID_BallHollow,
			kStandardImageID_Slash,
			kStandardImageID_XMark,
		};

		// -----------------------------------------------------------------------------
		class VWListBrowserColumn;
		class VWListBrowserItem;

		// -----------------------------------------------------------------------------
		class VWDialog;
		class VWListBrowserCtrl : public VWControl
		{
		public:
									VWListBrowserCtrl(TControlID id);
			virtual					~VWListBrowserCtrl();

			virtual bool			CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines);

		public:
			void					EnableControl(bool enable);
			void					EnableClickAllDataChange(bool enable);
			void					EnableDragAndDrop(bool enable);
			void					EnableRadioToolTips();

			void					EnableSorting(bool enable);
			bool					IsSortingEnabled() const;

			void					EnableSingleLineSelection(bool enable);
			void					EnableUpdates(bool enable);
			void					EnableDropOnIndices(size_t startIndex, size_t endIndex, bool enable);
			
			void					EnableHierarchicalDisplay(bool enable);
			bool					IsHierarchicalDisplay() const;
			TXString				GetHierarchicalRowContainerPath(size_t rowIndex);

			void					EnableDirectEdit(bool enable);
			bool					IsDirectEditEnabled();

			void					SetFocusOnControl();

			void					RefreshControl();

			void					SetColumnWidth(size_t fromColumn, size_t toColumn, size_t width);
			void					GetColumnWidth(size_t column, short &width);

			size_t					GetSelectedItemsCount();

			void					EnableExternalSort(bool /*bEnable*/ = true);
			bool					IsExternalSortEnabled() const;

		// image list managment
		public:
			size_t					AddImage(size_t resourceID, size_t resourceIDSelected = 0);
			size_t					AddImage(const TXString& imageSpecifier, const TXString& selectedImageSpecifier = "");
			size_t					AddImageStandard(EStandardImageID image, EStandardImageID selImage = kStandardImageID_None);

		// columns
		public:
			VWListBrowserColumn		AddColumn(const TXString& text, const TXString& savedSettingsColumnName, size_t defaultWidth);
			VWListBrowserColumn		AddColumn(const TXString& text, size_t width);
			VWListBrowserColumn		InsertColumn(size_t columnIndex, const TXString& text, const TXString& savedSettingsColumnName, size_t defaultWidth);
			VWListBrowserColumn		InsertColumn(size_t columnIndex, const TXString& text, size_t width);
			void					DeleteColumn(size_t columnIndex);

			size_t					GetColumnsCount() const;
			VWListBrowserColumn		GetColumn(size_t columnIndex);

			void					EnableColumnLines(bool enable);
			bool					AreColumnLinesEnabled() const;

		// rows
		public:
			size_t					AddRow(const TXString& text, Sint32 marker = 0);
			size_t					InsertRow(size_t rowIndex, const TXString& text, Sint32 marker = 0);
			void					DeleteRow(size_t rowIndex);
			void					DeleteAllRows();

			size_t					GetRowsCount() const;

			bool					IsRowSelected(size_t rowIndex) const;
			void					SelectRow(size_t rowIndex, bool select) const;
			void					SelectRow(size_t firstRowIndex, size_t lastRowIndex, bool select) const;
			void					DeselectAll() const;

			Sint32					GetRowData(size_t rowIndex) const; // data stored with the row, preserved when sorting
			void					SetRowData(size_t rowIndex, Sint32 data);

			Sint32					GetRowMarker(size_t rowIndex) const;
			void					SetRowMarker(size_t rowIndex, Sint32 marker);
			size_t					GetRowWithMarker(Sint32 marker);
			// returns (size_t)-1 if nothing is selected
			size_t					GetFirstSelected() const;
			size_t					GetLastSelected() const;
			bool					GetNextSelected(size_t& row) const;
			bool					GetPrevSelected(size_t& row) const;

			// changes 'row' to next the selected row, starting from 'row' value
			// if 'row' is selected, nothing changes
			bool					GetNextRowSelected(size_t& row) const;
			bool					GetPrevRowSelected(size_t& row) const;

			bool					GetSelectedItemIndices(TSizeTArray& outArray) const;
			void					SetSelectedItemIndices(const TSizeTArray& arr, bool selected);

		// items
		public:
			VWListBrowserItem		GetItem(size_t rowIndex, size_t columnIndex);

		// auto item managment
		public:
			template <class TArr> 
			void					AutoItemsFill(	  const TArr&	arrItems						// array of items to be added
													, size_t		colsCnt							// number of columns to create
													, std::function<
															void(size_t rowIndex, size_t itemIndex)
														>
																	cellStrCallback					// callback to fill the data for a row from the specified item
													, size_t		selIndex = size_t(-1)			// index of the item to be selected (-1 to preserve selection)
													, std::function<
															bool(const TArr& arr, size_t itemIndex)
														>
																	shouldDisplayCallback = nullptr	// callback to determine if to display an item or not. visible by DEFAULT
													);

			template <class TArr> 
			void					AutoItemsFill_NoDelete(
													  const TArr&	arrItems						// array of items to be added
													, size_t		colsCnt							// number of columns to create
													, std::function<
															void(size_t rowIndex, size_t itemIndex)
														>
																	cellStrCallback					// callback to fill the data for a row from the specified item
													, size_t		selIndex = size_t(-1)			// index of the item to be selected (-1 to preserve selection)
													, std::function<
															bool(const TArr& arr, size_t itemIndex)
														>
																	shouldDisplayCallback = nullptr	// callback to determine if to display an item or not. visible by DEFAULT
													);

			template <class TArr> 
			void					AutoItemsUpdate(
													  const TArr&	arrItems						// array of items to be added
													, std::function<
															void(size_t rowIndex, size_t itemIndex)
														>
																	cellStrCallback					// callback to fill the data for a row from the specified item
													, size_t		selIndex = size_t(-1)			// index of the item to be selected (-1 to preserve selection)
													, std::function<
															bool(const TArr& arr, size_t itemIndex)
														>
																	shouldDisplayCallback = nullptr	// callback to determine if to display an item or not. visible by DEFAULT
													);

			template <class TArr> 
			bool					AutoItemsHandleDragNDrop(	  VWDialogEventArgs&	eventArgs	// the input event arguments
																, TArr&					arrItems	// array of items to be added
															);										// RETURNs true if the drop was handled

		// hierarchy support
		public:
			void					ExpandAllItems();
			bool					IsRowClosed(size_t rowIndex);
			void					ExpandItems(size_t rowIndex, bool recursive, size_t& outRedisplayedItemsCnt);
			void					CloseItems(size_t rowIndex, bool recursive, size_t& outClosedItemsCnt);
			bool					IsItemContainer(size_t rowIndex);
			void					CloseAllItems();
			TXString				GetItemOriginalName(size_t rowIndex, bool returnContainerName = true);

		private:
			typedef std::vector<Sint32>		TMarkersArray;

			bool				fIsHierarchical;
			TMarkersArray		farrIndexToMarker;
		};
	}
}




namespace VWFC
{
	namespace VWUI
	{
		// -----------------------------------------------------------------------------
		template <class TArr> 
		void VWListBrowserCtrl::AutoItemsFill(	  const TArr&	arrItems				// array of items to be added
												, size_t		colsCnt					// number of columns to create
												, std::function<
														void(size_t rowIndex, size_t itemIndex)
													>
																cellStrCallback			// callback to fill the data for a row from the specified item
												, size_t		selIndex				// index of the item to be selected (-1 to preserve selection)
												, std::function<
														bool(const TArr& arr, size_t itemIndex)
													>
																shouldDisplayCallback	// callback to determine if to display an item or not. visible by DEFAULT
												)
		{
			this->DeleteAllRows();
			this->AutoItemsFill_NoDelete( arrItems, colsCnt, cellStrCallback, selIndex, shouldDisplayCallback );
		}


		// -----------------------------------------------------------------------------
		template <class TArr> 
		void VWListBrowserCtrl::AutoItemsFill_NoDelete(
												  const TArr&	arrItems				// array of items to be added
												, size_t		colsCnt					// number of columns to create
												, std::function<
														void(size_t rowIndex, size_t itemIndex)
													>
																cellStrCallback			// callback to fill the data for a row from the specified item
												, size_t		selIndex				// index of the item to be selected (-1 to preserve selection)
												, std::function<
														bool(const TArr& arr, size_t itemIndex)
													>
																shouldDisplayCallback	// callback to determine if to display an item or not. visible by DEFAULT
												)
		{
			for(size_t itemIndex=0, cnt=arrItems.size(); itemIndex<cnt; ++itemIndex)
			{
				bool isVisible = true;
				if ( shouldDisplayCallback )
				{
					isVisible = shouldDisplayCallback( arrItems, itemIndex );
				}

				if ( isVisible )
				{
					size_t rowIndex = this->AddRow( "", Sint32(itemIndex) );
					cellStrCallback( rowIndex, itemIndex );
				}
			}

			if ( selIndex != size_t(-1) )
			{
				this->SelectRow( selIndex, true );
			}
		}

		// -----------------------------------------------------------------------------
		template <class TArr> 
		void VWListBrowserCtrl::AutoItemsUpdate(
												  const TArr&	arrItems				// array of items to be added
												, std::function<
														void(size_t rowIndex, size_t itemIndex)
													>
																cellStrCallback			// callback to fill the data for a row from the specified item
												, size_t		selIndex				// index of the item to be selected (-1 to preserve selection)
												, std::function<
														bool(const TArr& arr, size_t itemIndex)
													>
																shouldDisplayCallback	// callback to determine if to display an item or not. visible by DEFAULT
												)
		{
			size_t rowIndex = 0;
			for ( size_t itemIndex = 0, cnt = arrItems.size(); itemIndex < cnt; ++itemIndex )
			{
				bool isVisible = true;
				if ( shouldDisplayCallback )
				{
					isVisible = shouldDisplayCallback( arrItems, itemIndex );
				}

				if ( isVisible )
				{
					cellStrCallback( rowIndex, itemIndex );
					++rowIndex;
				}
			}

			if ( selIndex != size_t(-1) )
			{
				this->SelectRow( selIndex, true );
			}
		}

		// -----------------------------------------------------------------------------
		template <class TArr> 
		bool VWListBrowserCtrl::AutoItemsHandleDragNDrop(  VWDialogEventArgs&	eventArgs
														 , TArr&				arrItems				// array of items to be added
														)
		{
			// drag&drop specific data for the control
			typedef std::pair<bool, SListBrowserDragDropInfo>		TControlDropInfo;
			typedef std::map<TControlID, TControlDropInfo>			TControlDropContextMap;
			static TControlDropContextMap	sMapControlDropContext;
			auto dropContextIt = sMapControlDropContext.find( this->GetControlID() );
			if ( dropContextIt == sMapControlDropContext.end() )
			{
				auto insertRes = sMapControlDropContext.insert( TControlDropContextMap::value_type( this->GetControlID(), TControlDropInfo( false, SListBrowserDragDropInfo() ) ) );
				if ( insertRes.second )
				{
					dropContextIt = insertRes.first;
				}
			}

			bool result = false;
			if ( VERIFYN( kVStanev, dropContextIt != sMapControlDropContext.end() ) )
			{
				bool&						waitDropInfoMessage	= dropContextIt->second.first;
				SListBrowserDragDropInfo&	dropInfo			= dropContextIt->second.second;

				if ( waitDropInfoMessage )
				{
					SListBrowserDragDropInfo* thisDropInfo = eventArgs.GetListBrowserDropInfo();
					if ( thisDropInfo )
						dropInfo = *thisDropInfo;

					waitDropInfoMessage = false;
				}
				else if ( eventArgs.IsListBrowserNextMessageIsDropInfo() )
				{
					waitDropInfoMessage = true;
				}
				else if ( eventArgs.IsListBrowserDrawNDropEnd() )
				{
					size_t	dataCnt	= arrItems.size();
					size_t	dragCnt = dropInfo.farrIndicesDragged.GetSize();

					TArr	arrDragData;

					// extract drag data
					for(size_t iDrag=0; iDrag<dragCnt; ++iDrag)
					{
						Sint32	dragIndex		= dropInfo.farrIndicesDragged.GetAt( iDrag );
						size_t	dragDataIndex	= dragIndex >= 0 ? size_t( this->GetRowMarker( dragIndex ) ) : size_t(-1);
						if ( VERIFYN( kVStanev, dragDataIndex < dataCnt ) )
						{
							arrDragData.push_back( arrItems[ dragDataIndex ] );
						}
					}

					// delete the draged data backwards
					for(size_t iDrag=0; iDrag<dragCnt; ++iDrag)
					{
						Sint32	dragIndex		= dropInfo.farrIndicesDragged.GetAt( dragCnt - iDrag - 1 );
						size_t	dragDataIndex	= dragIndex >= 0 ? size_t( this->GetRowMarker( dragIndex ) ) : size_t(-1);
						if ( VERIFYN( kVStanev, dragDataIndex < dataCnt ) )
						{
							arrItems.erase( arrItems.begin() + dragDataIndex );
						}

						dataCnt			= arrItems.size();
					}

					// insert the drag data from copy after correcting the drop index
					size_t	dropDataIndex	= dropInfo.fDropIndex >= 0 ? size_t( this->GetRowMarker( dropInfo.fDropIndex ) ) : size_t(-1);
					for(size_t iDrag=0; iDrag<dragCnt; ++iDrag)
					{
						Sint32	dragIndex		= dropInfo.farrIndicesDragged.GetAt( dragCnt - iDrag - 1 );
						if ( dragIndex < dropInfo.fDropIndex && dropDataIndex > 0 )
						{
							dropDataIndex--;
						}
					}

					if ( dropInfo.fDropIndex > dropInfo.fDragIndex )
					{
						dropDataIndex++;
					}

					if ( VERIFYN( kVStanev, dropDataIndex <= dataCnt ) )
					{
						arrItems.insert( arrItems.begin() + dropDataIndex, arrDragData.begin(), arrDragData.end() );
					}

					result	= true;
				}
				else
				{
					// this is just a protection!
					waitDropInfoMessage = false;
				}
			}

			return result;
		}
	}
}
