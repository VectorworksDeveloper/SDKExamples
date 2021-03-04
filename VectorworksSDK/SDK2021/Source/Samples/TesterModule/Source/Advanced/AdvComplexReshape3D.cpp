#include "StdAfx.h"

#include "AdvComplexReshape3D.h"

using namespace Advanced;
using namespace VectorWorks::Extension;

CAdvComplexReshape3D::CAdvComplexReshape3D(IVWUnknown* parent)
	: VCOMImpl<IProviderReshape3D>( parent )
{
}

CAdvComplexReshape3D::~CAdvComplexReshape3D()
{
}

void CAdvComplexReshape3D::	SelectionPrepare(bool bRestore, MCObjectHandle hObj)
{
}

void CAdvComplexReshape3D::SelectionUnPrepare(bool bRestore)
{
}

void CAdvComplexReshape3D::Cancel()
{
}

void CAdvComplexReshape3D::GetStatus(Sint32& outStatus)
{
}

Sint32 CAdvComplexReshape3D::GetCursorID()
{
	return 0;
}

void CAdvComplexReshape3D::UpdateHightlightStatus(Sint16 pickIndex)
{
}

void CAdvComplexReshape3D::SetupModeBar()
{
}

void CAdvComplexReshape3D::ModeEvent(Sint32 modeGroup, Sint16 newMode, Sint16 oldMode)
{
}

void CAdvComplexReshape3D::HandleCustomBarEvent(const CustomBarEventData& eventData)
{
}

void CAdvComplexReshape3D::MouseDown(Sint16 pickIndex)
{
}

void CAdvComplexReshape3D::MouseMove()
{
}

void CAdvComplexReshape3D::Draw()
{
}

void CAdvComplexReshape3D::Complete()
{
}
