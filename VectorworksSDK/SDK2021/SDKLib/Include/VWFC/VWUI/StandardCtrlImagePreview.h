//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWUI
	{
		class CStandardCtrlImagePreview : public VWCustomCtrl
		{
		public:
						CStandardCtrlImagePreview(TControlID id);
						CStandardCtrlImagePreview(TControlID id, const TXString& previewDlgTitle, const TXString& closeBtn);
			virtual		~CStandardCtrlImagePreview();

			void		Clear();
			void		SetImage(VectorWorks::UI::IIconPtr image);
			bool		SetImageFile(VectorWorks::Filing::IFileIdentifierPtr fileID);
			void		SetDontUseOffset(bool value);

			enum class EMessageType
			{
				Normal,
				Grayed,
			};

			void		SetMessage(const TXString& msg, EMessageType type);

		// eventing
		protected:
			virtual void		OnPaint(VWCustomCtrlDC& dc);
			virtual void		OnMouseClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseDblClick(const SCustomCtrlMouseEvent& event);

		private:
			TXString					fPreviewDlgTitle;
			TXString					fPreviewDlgCloseBtn;

			VWCustomCtrlPen				fMessagePen;
			VWCustomCtrlPen				fMessagePenGray;
			VWCustomCtrlFont			fMessageFont;
			bool						fDontUseOffset;
			VectorWorks::UI::IIconPtr	fIcon;
			Sint16						fIconWidth;
			Sint16						fIconHeight;
			TXString					fMessage;
			EMessageType				fMessageType;

			struct SMessageLine
			{
				TXString	fLineTxt;
				Uint32		fLineWidth;
			};

			std::vector<SMessageLine>	farrMessageLines;
			Uint32						fLineHeight;
		};
	}
}