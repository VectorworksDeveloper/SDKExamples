//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------------------------------------------
		// {95541C75-CDF6-43E8-8403-B80462D91B12}
		static const VWIID IID_MarkersPluginSupport = { 0x95541c75, 0xcdf6, 0x43e8, { 0x84, 0x3, 0xb8, 0x4, 0x62, 0xd9, 0x1b, 0x12 } };

		/**	Provides access to specific functionality implemented in Markers project (and not available in Core)
		*	Communication is achieved through Markers::Interfaces::CMarkersPluginSupport
		*/

		class DYNAMIC_ATTRIBUTE IMarkersPluginSupport : public IVWUnknown
		{
		public:
			// --------------------------------------------------------------------------------------------------------
			virtual MCObjectHandle	VCOM_CALLTYPE	ImportMarkerStyle(IResourceManagerContentPtr styleContent, const TXString& styleFolderName, const TXString& styleName)			= 0;
			virtual VCOMError		VCOM_CALLTYPE	ApplyMarkerStyle(MCObjectHandle hObject, MCObjectHandle hSymDef)																= 0;
			virtual void			VCOM_CALLTYPE	ApplyStyleParamsToObject(MCObjectHandle hSymDef, const TInternalID	internalID, MCObjectHandle hObject)							= 0;

			// --------------------------------------------------------------------------------------------------------
			virtual void			VCOM_CALLTYPE	UpdateDetailCalloutInstances(MCObjectHandle hMasterDetailCallout, MCObjectHandle hInstance)										= 0;
			virtual void			VCOM_CALLTYPE	UpdateSectionLineInstances(MCObjectHandle hSectionViewport, MCObjectHandle hSectionLineDefinition, MCObjectHandle hInstance)	= 0;
			virtual void			VCOM_CALLTYPE	SetFlagNeedsReset()																												= 0;
			virtual void			VCOM_CALLTYPE	DeleteFlagNeedsReset()																											= 0;
		};

		// ------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IMarkersPluginSupport> IMarkersPluginSupportPtr;
	}
}
