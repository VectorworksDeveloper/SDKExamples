//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

#include "CustomCtrl.h"

namespace VWFC
{
	namespace VWUI
	{
		template <class TItemArray> class VWListCustomCtrl : public VWCustomCtrl
		{
		public:
						VWListCustomCtrl(TControlID id, TItemArray& arrItems);
			virtual		~VWListCustomCtrl();
			
			const TItemArray&	GetArray() const;
			TItemArray&			GetArray();

			ViewCoord			GetLineHeight() const;

			size_t				GetVScrollPos();
			void				SetVScrollPos(size_t pos);

			size_t				GetHScrollPos();
			void				SetHScrollPos(size_t pos);

			void				EnsureVisible(typename TItemArray::const_reference item);

		// eventing
		protected:
			virtual void		OnPaint(VWCustomCtrlDC& dc);
			virtual void		OnMouseClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseDblClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseWheel(const SCustomCtrlMouseEvent& event, Sint16 deltaX, Sint16 deltaY);

		protected:
			bool				OnPaint(VWCustomCtrlDC& dc, Sint32 leftStart, Sint32 topStart, typename TItemArray::reference item, Sint32& ptLineX, Sint32& ptLineY, Sint32& maxLineWidth);
			bool				FindItem(typename TItemArray::pointer& outItem, Sint32 topStart, typename TItemArray::reference item, Sint32& ptLineX, Sint32& ptLineY, Uint16 atY);
			size_t				GetItemsCount(typename TItemArray::reference item, Sint32& linePtY, Sint32& ensureVisItemLinePtY);

		protected:
			VWCustomCtrlFont	fDefaultFont;
			VWCustomCtrlPen		fDefaultPen;

			ViewCoord			fLineHeight;
			ViewCoord			fCtrlWidth;
			ViewCoord			fCtrlHeight;

			TItemArray&			farrItems;

			typename TItemArray::const_pointer	fpEnsureVisibleItem;
			Sint32									fSetVScrollPosition;
			Sint32									fSetHScrollPosition;
		};
	}
}

namespace VWFC
{
	namespace VWUI
	{
		template <class TItemArray>
		VWListCustomCtrl<TItemArray>::VWListCustomCtrl(TControlID id, TItemArray& arrItems)
			: VWCustomCtrl( id )
			, fDefaultFont( "Arial", 12, false, false, false )
			, fDefaultPen( 0, 0, 0 )
			, fLineHeight( 0 )
			, farrItems( arrItems )
			, fpEnsureVisibleItem( NULL )
			, fSetVScrollPosition( -1 )
			, fSetHScrollPosition( -1 )
		{
		}

		template <class TItemArray>
		VWListCustomCtrl<TItemArray>::~VWListCustomCtrl()
		{
		}
		
		template <class TItemArray>
		const TItemArray&VWListCustomCtrl<TItemArray>::GetArray() const
		{
			return farrItems;
		}
		
		template <class TItemArray>
		TItemArray& VWListCustomCtrl<TItemArray>::GetArray()
		{
			return farrItems;
		}

		template <class TItemArray>
		ViewCoord VWListCustomCtrl<TItemArray>::GetLineHeight() const
		{
			return fLineHeight;
		}

		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::EnsureVisible(typename TItemArray::const_reference item)
		{
			fpEnsureVisibleItem = & item;
		}

		template <class TItemArray>
		size_t VWListCustomCtrl<TItemArray>::GetVScrollPos()
		{
			Sint32			leftStart	= 0;
			Sint32			topStart	= 0;
			this->GetScrollArea( leftStart, topStart );

			return DemoteTo<size_t>( kVStanev, topStart );
		}

		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::SetVScrollPos(size_t pos)
		{
			fSetVScrollPosition = (Sint32)pos; //-V202
		}
		
		template <class TItemArray>
		size_t VWListCustomCtrl<TItemArray>::GetHScrollPos()
		{
			Sint32			leftStart	= 0;
			Sint32			topStart	= 0;
			this->GetScrollArea( leftStart, topStart );

			return DemoteTo<size_t>( kVStanev, leftStart );
		}

		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::SetHScrollPos(size_t pos)
		{
			fSetHScrollPosition = pos; //-V103
		}

		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::OnMouseClick(const SCustomCtrlMouseEvent& event)
		{
			VWCustomCtrl::OnMouseClick( event );

			Sint32			leftStart	= 0;
			Sint32			topStart	= 0;
			this->GetScrollArea( leftStart, topStart );

			Sint32		ptLineX	= 0;
			Sint32		ptLineY	= 0;
			for(size_t i=0, cnt=farrItems.size(); i<cnt; ++i)
			{
				typename TItemArray::reference item = farrItems[ i ];

				typename TItemArray::pointer	foundItem	= NULL;
				if ( this->FindItem( foundItem, topStart, item, ptLineX, ptLineY, event.y ) && foundItem)
				{
					SCustomCtrlMouseEvent	localEvent	= event;
					foundItem->OnMouseClick( *this, localEvent, false );
					break;
				}
			}
		}
		
		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::OnMouseDblClick(const SCustomCtrlMouseEvent& event)
		{
			VWCustomCtrl::OnMouseDblClick( event );

			Sint32			leftStart	= 0;
			Sint32			topStart	= 0;
			this->GetScrollArea( leftStart, topStart );

			Sint32		ptLineX	= 0;
			Sint32		ptLineY	= 0;
			for(size_t i=0, cnt=farrItems.size(); i<cnt; ++i)
			{
				typename TItemArray::reference item = farrItems[ i ];

				typename TItemArray::pointer	foundItem	= NULL;
				if ( this->FindItem( foundItem, topStart, item, ptLineX, ptLineY, event.y ) && foundItem)
				{
					SCustomCtrlMouseEvent	localEvent	= event;
					foundItem->OnMouseClick( *this, localEvent, true );
					break;
				}
			}
		}

		template <class TItemArray>
		bool VWListCustomCtrl<TItemArray>::FindItem(typename TItemArray::pointer& outItem, Sint32 topStart, typename TItemArray::reference item, Sint32& ptLineX, Sint32& ptLineY, Uint16 atY)
		{
			bool result_Stop = false;
			if ( item.IsVisible() )
			{
				ptLineY	+= fLineHeight;
				if ( topStart <= ptLineY )
				{
					if ( ptLineY - topStart <= fCtrlHeight )
					{
						ViewCoord	localPt_y	= ptLineY - topStart;
						if ( localPt_y - fLineHeight <= atY && atY < localPt_y )
						{
							outItem	= & item;

							// we are not interested in traversing anymore
							result_Stop = true;
						}
					}
					else
					{
						// end of the visible area of the control
						result_Stop = true;
					}
				}

			
				if ( ! result_Stop )
				{
					for(size_t i=0, cnt=item.GetChildCount(); result_Stop == false && i<cnt; ++i)
					{
						typename TItemArray::pointer pChildItem = item.GetChildAt( i );
						if ( pChildItem )
						{
							result_Stop = this->FindItem( outItem, topStart, *pChildItem, ptLineX, ptLineY, atY );
						}
					}
				}
			}

			return result_Stop;
		}

		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::OnPaint(VWCustomCtrlDC& dc)
		{
			fCtrlWidth		= this->GetControlWidth();
			fCtrlHeight		= this->GetControlHeight();
			VWCustomCtrlDC	backbufferDC( fCtrlWidth, fCtrlHeight );
			backbufferDC.SelectFont( fDefaultFont );
			backbufferDC.SelectPen( fDefaultPen );

			if ( fLineHeight == 0 )
				fLineHeight		= 2 * DemoteTo<ViewCoord>( kVStanev, dc.GetStringWidth( "W" ) );
		
			Sint32			leftStart	= 0;
			Sint32			topStart	= 0;
			this->GetScrollArea( leftStart, topStart );

			// calculate scroll area size
			Sint32			scrollAreaLinePtY				= 0;
			Sint32			scrollAreaEnsureVisItemLinePtY	= 0;
			size_t		visibleItemsCnt					= 0;
			for(size_t i=0, cnt=farrItems.size(); i<cnt; ++i)
			{
				typename TItemArray::reference item = farrItems[ i ];
				visibleItemsCnt	+= this->GetItemsCount( item, scrollAreaLinePtY, scrollAreaEnsureVisItemLinePtY );
			}

			// apply the initial scroll first, and then ensure visible item
			if ( fSetVScrollPosition != -1 )
			{
				topStart	= fSetVScrollPosition;
			}
			
			// appy the initial scroll first, and then ensure visible item
			if ( fSetHScrollPosition != -1 )
			{
				leftStart	= fSetHScrollPosition;
			}
			// override the topStart so we have the item visible if needed
			// also check if we dont have it visible right now
			if ( fpEnsureVisibleItem )
			{
				if ( ! (topStart <= scrollAreaEnsureVisItemLinePtY && scrollAreaEnsureVisItemLinePtY <= topStart + fCtrlHeight ) )
				{
					topStart	= scrollAreaEnsureVisItemLinePtY - fCtrlHeight / 2;
				}
			}

			Sint32	overallHeight	= (Sint32)( fLineHeight * visibleItemsCnt ); //-V202
			if ( topStart > 0 )
			{
				if ( overallHeight < fCtrlHeight )
				{
					// we cannot overscroll in a custom control
					// it's just that the GetScrollArea doesn't return the correct value
					topStart		= 0;
				}
				else
				{
					Sint32	maxTopStart	= ( overallHeight - fCtrlHeight );
					if ( topStart > maxTopStart )
					{
						topStart	= maxTopStart;
					}
				}
			}

			// draw
			Sint32		ptLineX			= 0;
			Sint32		ptLineY			= 0;
			Sint32		maxLineWidth	= 0;
			for(size_t i=0, cnt=farrItems.size(); i<cnt; ++i)
			{
				typename TItemArray::reference item = farrItems[ i ];

				if ( this->OnPaint( backbufferDC, leftStart, topStart, item, ptLineX, ptLineY, maxLineWidth ) == false )
					break;
			}

			dc.BitBlt( ViewRect(0,0, fCtrlWidth, fCtrlHeight), backbufferDC, ViewPt(0,0) );

			maxLineWidth	+= fCtrlWidth / 4;
			this->UpdateScrollArea( maxLineWidth, overallHeight, leftStart, topStart, fLineHeight, true, false, true );

			// make sure we dont ensure visible item every draw
			fpEnsureVisibleItem		= NULL;
			fSetVScrollPosition		= -1;
			fSetHScrollPosition		= -1;
		}

		template <class TItemArray>
		bool VWListCustomCtrl<TItemArray>::OnPaint(VWCustomCtrlDC& dc, Sint32 leftStart, Sint32 topStart, typename TItemArray::reference item, Sint32& ptLineX, Sint32& ptLineY, Sint32& maxLineWidth)
		{
			bool resContinue = true;
			if ( item.IsVisible() )
			{
				ptLineY	+= fLineHeight;
				if ( topStart <= ptLineY )
				{
					if ( ptLineY - topStart <= fCtrlHeight )
					{
						ViewPt	localPt;
						localPt.x	= DemoteTo<ViewCoord>( kVStanev, ptLineX - leftStart );
						localPt.y	= DemoteTo<ViewCoord>( kVStanev, ptLineY - topStart );

						Sint32 thisLineWidth = item.OnPaint( *this, dc, localPt );
						if ( thisLineWidth > maxLineWidth )
							maxLineWidth	= thisLineWidth;
					}
					else
					{
						// end of the visible area of the control
						resContinue = false;
					}
				}

				if ( resContinue )
				{
					for(size_t i=0, cnt=item.GetChildCount(); i<cnt; ++i)
					{
						typename TItemArray::pointer pChildItem = item.GetChildAt( i );
						if ( pChildItem )
						{
							this->OnPaint( dc, leftStart, topStart, *pChildItem, ptLineX, ptLineY, maxLineWidth );
						}
					}
				}			
			}

			return resContinue;
		}

		template <class TItemArray>
		size_t VWListCustomCtrl<TItemArray>::GetItemsCount(typename TItemArray::reference item, Sint32& linePtY, Sint32& ensureVisItemLinePtY)
		{
			size_t	result	= 0;
			if ( item.IsVisible() )
			{
				result ++;
				linePtY	+= fLineHeight;
				if ( fpEnsureVisibleItem == & item )
				{
					ensureVisItemLinePtY	= linePtY;
				}

				for(size_t i=0, cnt=item.GetChildCount(); i<cnt; ++i)
				{
					typename TItemArray::pointer pChildItem = item.GetChildAt( i );
					if ( pChildItem )
					{
						result	+= this->GetItemsCount( *pChildItem, linePtY, ensureVisItemLinePtY );
					}
				}
			}

			return result;
		}

		template <class TItemArray>
		void VWListCustomCtrl<TItemArray>::OnMouseWheel(const SCustomCtrlMouseEvent& event, Sint16 deltaX, Sint16 deltaY)
		{
			VWCustomCtrl::OnMouseWheel( event, deltaX, deltaY );

			ptrdiff_t	top		= this->GetVScrollPos();
			top			-= deltaY * fLineHeight; //-V101
			if ( top < 0 )
			{
				top = 0;
			}

			this->SetVScrollPos( size_t(top) );
			this->Refresh();
		}
	}
}
