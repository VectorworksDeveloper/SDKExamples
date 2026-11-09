#pragma once

namespace UI
{
	class CMyControl : public VWCustomCtrl
	{
	public:
							CMyControl(TControlID id, bool bUseDefault=false);
		virtual				~CMyControl();

	// eventing
	protected:
		virtual void		OnControlAttached();
		virtual void		OnPaint(VWCustomCtrlDC& dc);
		virtual void		OnMouseMoved(const SCustomCtrlMouseEvent& event);
		virtual void		OnMouseDown(const SCustomCtrlMouseEvent& event);
		virtual void		OnMouseUp(const SCustomCtrlMouseEvent& event);
		virtual void		OnMouseDblClick(const SCustomCtrlMouseEvent& event);
		virtual void		OnMouseWheel(const SCustomCtrlMouseEvent& event, Sint16 deltaX, Sint16 deltaY);
		virtual void		OnKeyDown(const SCustomCtrlKeyEvent& event);
		virtual void		OnKeyUp(const SCustomCtrlKeyEvent& event);
		virtual void		OnChar(const SCustomCtrlKeyEvent& event);

	private:
		TXString			fstrText;
		ViewPt				fptText;

		typedef VCOMPtr<VectorWorks::UI::IIcon>		TIcon;

		TIcon				fIcon;
	};
}