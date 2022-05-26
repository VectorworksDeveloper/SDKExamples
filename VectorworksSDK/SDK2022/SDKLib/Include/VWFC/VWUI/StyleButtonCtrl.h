//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"
#include "VWFC/VWUI/ImageButtonCtrl.h"

namespace VWFC
{
	namespace VWUI
	{
				
		class VWStyleButtonCtrl : public VWImageButtonCtrl
		{
		public:
							VWStyleButtonCtrl(TControlID id);
			virtual			~VWStyleButtonCtrl();
		

		public:
			void	SetStyleType( EPluginStyleParameter type );
			EPluginStyleParameter GetStyleType();	
			                                                            
			void	SetParameterName( const TXString & parameterName );
			TXString GetParameterName();

			void	SetIconPushButtonImage(const TXString& imageSpec);
	
			void	AddAssociatedControl( TControlID id );
			void	UpdateAssociatedControls(bool allowEnabling = true);
			void	EnableAssociatedControls( bool enable = true );

			void	AddAssociatedParameter( const TXString& addedParameter );
			size_t	NumberofAssoicatedParameters();
			TXString	GetAssociatedParameter( size_t index );

			TControlID GetPrimaryAssoicatedControl();

			void	ClearAssoicatedParameters();
			void	ClearAssociatedControls();

		private:
			EPluginStyleParameter	fStyleType;
			TXString				fParameterName;

			std::vector<TControlID> fAssociatedControls;
			std::vector<TXString>	fAssociatedParameters;

		};

		class VWStyleGroupButtonCtrl : public VWControl
		{
		public:
							VWStyleGroupButtonCtrl( TControlID id );
			virtual			~VWStyleGroupButtonCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text);

		public:
			void	SetGroupID( Sint32 groupID );
			Sint32	GetGroupID();

			void	SetTextControlID( TControlID textContrlID );


			void	SetStyleGroupType( EPluginStyleGroup type );
			EPluginStyleGroup GetStyleGroupType();


		private:
			Sint32				fGroupID;
			EPluginStyleGroup	fStyleGroupType;
			TControlID			fTextControlID;


		};
	

	}
}