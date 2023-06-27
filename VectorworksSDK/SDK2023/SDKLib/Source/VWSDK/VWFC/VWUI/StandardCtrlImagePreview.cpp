//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/StandardCtrlImagePreview.h"

using namespace VWFC::VWUI;
using namespace VectorWorks::UI;
using namespace VectorWorks::Filing;

CStandardCtrlImagePreview::CStandardCtrlImagePreview(TControlID id)
	: VWCustomCtrl( id )
	, fMessagePen( 0, 0, 0 )
	, fMessagePenGray( 200, 200, 200 )
	, fMessageFont( "Arial", 10, false, false, false )
	, fLineHeight( 0 )
	, fDontUseOffset( false )
{
}

CStandardCtrlImagePreview::CStandardCtrlImagePreview(TControlID id, const TXString& previewDlgTitle, const TXString& closeBtn)
	: VWCustomCtrl( id )
	, fPreviewDlgTitle( previewDlgTitle )
	, fPreviewDlgCloseBtn( closeBtn )
	, fMessagePen( 0, 0, 0 )
	, fMessagePenGray( 200, 200, 200 )
	, fMessageFont( "Arial", 10, false, false, false )
	, fLineHeight( 0 )
	, fDontUseOffset( false )
{
}

CStandardCtrlImagePreview::~CStandardCtrlImagePreview()
{
}

void CStandardCtrlImagePreview::Clear()
{
	fIcon.Release();
	fIconWidth = fIconHeight = 0;
	fMessage.Clear();
	farrMessageLines.clear();
	this->Refresh();
}

void CStandardCtrlImagePreview::SetImage(IIconPtr image)
{
	fIconWidth = fIconHeight = 0;
	fIcon = image;
	if ( fIcon )
		fIcon->GetDimensions( fIconWidth, fIconHeight );
	fMessage.Clear();
	farrMessageLines.clear();
	this->Refresh();
}

bool CStandardCtrlImagePreview::SetImageFile(IFileIdentifierPtr fileID)
{
	fIconWidth = fIconHeight = 0;

	bool result = false;
	if ( fileID && VCOM_SUCCEEDED( fileID->ExistsOnDisk( result ) ) && result )
	{
		TXString	fullPath;
		fileID->GetFileFullPath( fullPath );

		TXString	ext;
		fileID->GetFileExtension( ext );

		TXString fullPathHiRez( fullPath );

		if ( fullPathHiRez.Find( "@2x" ) == -1 )
		{
			fullPathHiRez.Replace( "." + ext, "@2x." + ext );

			fileID->Set( fullPathHiRez );
			bool exists = false;
			fileID->ExistsOnDisk( exists );
			if ( exists )
			{
				fullPath = fullPathHiRez;
			}
			else
			{
				fileID->Set( fullPath );
			}
		}

		if ( fIcon == nullptr )
			fIcon.Query( VectorWorks::UI::IID_Icon );

		result = VCOM_SUCCEEDED( fIcon->SetFromAbsolutePath( fullPath ) );
		result = result && VCOM_SUCCEEDED( fIcon->GetDimensions( fIconWidth, fIconHeight ) );
	}
	else
	{
		fIcon.Release();
	}

	fMessage.Clear();
	farrMessageLines.clear();
	this->Refresh();

	return result;
}

void CStandardCtrlImagePreview::SetMessage(const TXString& msg, EMessageType type)
{
	fMessage = msg;
	fMessageType = type;
	farrMessageLines.clear();
	fIcon.Release();
	fIconWidth = fIconHeight = 0;
	this->Refresh();
}

void CStandardCtrlImagePreview::SetDontUseOffset(bool value)
{
	fDontUseOffset = value;
}

void CStandardCtrlImagePreview::OnPaint(VWCustomCtrlDC& dc)
{
	ViewCoord		ctrlWidth		= this->GetControlWidth();
	ViewCoord		ctrlHeight		= this->GetControlHeight();

	ViewRect	viewRect( 0, 0, ctrlWidth, ctrlHeight );

	dc.SelectBrush( VWCustomCtrlBrush( 255, 255, 255 ) );
	dc.FillRect( viewRect );

	if ( fIcon )
	{
		if ( ! fDontUseOffset )
			viewRect.Inset( 2, 2 ); // make a border

		double scale = std::min( viewRect.Width()/(double)fIconWidth, viewRect.Height()/(double)fIconHeight);
		ViewCoord viewWidth = ViewCoord(fIconWidth * scale);
		ViewCoord viewHeight = ViewCoord(fIconHeight * scale);
		ViewCoord viewX = ViewCoord(ctrlWidth / 2.0 - viewWidth / 2.0);
		ViewCoord viewY = ViewCoord(ctrlHeight / 2.0 - viewHeight / 2.0);

		dc.DrawIcon( ViewRect(viewX, viewY, viewX+viewWidth, viewY+viewHeight), fIcon );
	}
	else if ( ! fMessage.IsEmpty() )
	{
		switch ( fMessageType )
		{
		default:
		case EMessageType::Normal:
			dc.SelectPen( fMessagePen );
			break;
		case EMessageType::Grayed:
			dc.SelectPen( fMessagePenGray );
			break;
		}

		dc.SelectFont( fMessageFont );

		// regenerate the lines if the message have changed
		// otherwise just use them so we dont split the message always and we can have nice performance
		if ( farrMessageLines.size() == 0 )
		{
			Uint32 spaceWidth = dc.GetStringWidth( " " );

			TXStringSTLArray	arrPieces;
			TXStringExt::Tokenize( fMessage, arrPieces, " " );

			SMessageLine	line;
			for(const TXString& piece : arrPieces )
			{
				if ( line.fLineTxt.IsEmpty() )
				{
					line.fLineTxt = piece;
					line.fLineWidth = dc.GetStringWidth( piece );
				}
				else
				{
					Uint32 combinedWidth = line.fLineWidth + spaceWidth + dc.GetStringWidth( piece );
					if ( ViewCoord(combinedWidth + 2  * spaceWidth) < ctrlWidth )
					{
						line.fLineTxt += " ";
						line.fLineTxt += piece;
						line.fLineWidth = combinedWidth;
					}
					else
					{
						farrMessageLines.push_back( line );

						line.fLineTxt = piece;
						line.fLineWidth = dc.GetStringWidth( piece );
					}
				}
			}

			if ( ! line.fLineTxt.IsEmpty() )
				farrMessageLines.push_back( line );
		}

		if ( fLineHeight == 0 )
		{
			fLineHeight = dc.GetStringWidth( "W" );
			fLineHeight += (Uint32)(double(fLineHeight) * 1.0 / 3.0); // add a gap
		}

		ViewCoord linesTotalHeight = ViewCoord(farrMessageLines.size() * fLineHeight);

		ViewPt pt( 0, 0 );
		if ( linesTotalHeight < ctrlHeight )
			pt.y = ctrlHeight / 2 - linesTotalHeight / 2;

		for(const SMessageLine& line : farrMessageLines)
		{
			pt.x = 0;
			if ( ViewCoord(line.fLineWidth) < ctrlWidth )
				pt.x = ctrlWidth / 2 - line.fLineWidth / 2;
			dc.DrawString_TXString( pt, line.fLineTxt );
			pt.y += fLineHeight;
		}
	}
}

class CDlgImagePreview : public VWDialog
{
public:
	CDlgImagePreview(const TXString& title, const TXString& btn)
		: fImage( 4 )
	{
		// Assign settings tag to this dialog so it would save it's position and size automatically
		this->SetSavedSettingsTag( "Landscape", "DlgAddPlant" );

		fTitle = title;
		fButton = btn;
	}

	void		SetImage(IIconPtr image) { fImage.SetImage( image ); }

	virtual bool	CreateDialogLayout()
	{
		this->CreateDialog( fTitle, fButton, "", false, true, true );

		fImage.CreateControl( this, 800, 800 );

	    this->AddFirstGroupControl( & fImage );
		fImage.SetEdgeBinding( true, true, true, true );

		return true;
	}

	virtual	void	OnDDXInitialize()
	{
		this->AddDDX_Control( & fImage );
	}

private:
	TXString				fTitle;
	TXString				fButton;
	CStandardCtrlImagePreview	fImage;
};

void CStandardCtrlImagePreview::OnMouseClick(const SCustomCtrlMouseEvent& event)
{
	if ( fIcon && ! fPreviewDlgTitle.IsEmpty() )
	{
		CDlgImagePreview dlg( fPreviewDlgTitle, fPreviewDlgCloseBtn );
		dlg.SetImage( fIcon );
		dlg.RunDialogLayout( "" );
	}
}

void CStandardCtrlImagePreview::OnMouseDblClick(const SCustomCtrlMouseEvent& event)
{
	if ( fIcon && ! fPreviewDlgTitle.IsEmpty() )
	{
		CDlgImagePreview dlg( fPreviewDlgTitle, fPreviewDlgCloseBtn );
		dlg.SetImage( fIcon );
		dlg.RunDialogLayout( "" );
	}
}

