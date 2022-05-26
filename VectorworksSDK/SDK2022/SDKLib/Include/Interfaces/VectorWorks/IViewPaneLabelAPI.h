#pragma once

/**
* < How to use ViewPaneLabelAPI >
*    this component allows Vectorworks third party developers to have view-pane specific
*    information persistently shown in the top left of the view-pane.
*    The 'information' is a small icon followed by some text. This is called a pane label.
*    There can be one or more pane labels in a row.
*    Third party code can execute when a pane label is clicked on.

Examples)
// RowAdd() should be called when the item "MyRow" is added to the given view pane.
void HowToAdd()
{
    VCOMPtr<IViewPaneLabelAPI> viewPaneLabels(IID_ViewPaneLabels);
    viewPaneLabels->RowAdd(paneID, "MyRow", "", MyRowCallback);
}

// RowRemove() should be called when the item is removed from the view pane.
void HowToRemove()
{
    VCOMPtr<IViewPaneLabelAPI> viewPaneLabels(IID_ViewPaneLabels);
    viewPaneLbaels->RowRemove(paneID, "MyRow");
}

// If you want to update the icon with a new one, then you need to call RowRemove() and then RowAdd().

void MyRowCallback(Operation op, Args& args)
{
    switch( op ) {
        case GetLabels: {
            std::vector<Label>& labels = args.fGetLabelsArgs->fLabels;

            // add a single label to this row
			// The icon.png resolution should be 16 x 14. The developers should provide the large resolution icon 32 x 28 
			// Otherwise, the default icon will be used.
			// The text should be from the resource (vwr).
			labels.push_back( {"Localized Viewpane Label 1", "vwrFolderWithoutExtension/Images/Icon1.png" } );
			labels.push_back( {"Localized Viewpane Label 2", "vwrFolderWithoutExtension/Images/Icon2.png" } );
            labels.push_back( {"Localized Viewpane Label 3", "vwrFolderWithoutExtension/Images/Icon3.png" } );
			break;
		}
        case AdvanceState: {
            // user has clicked on this label!
			if (args.fAdvanceStateArgs->fLabelIndex == 0) // The 1st label in the row has been clicked
			else if (args.fAdvanceStateArgs->fLabelIndex == 1) // The 2nd label has been clicked
			else if (args.fAdvanceStateArgs->fLabelIndex == 2) // The 3rd label has been clicked
			...
           break;
        }
    }
}
*/

namespace VectorWorks
{
	namespace Extension
	{
		namespace ViewPaneLabelAPI
		{
			struct Args;

			enum Operation
			{
				Unknown,
				GetLabels,
				AdvanceState,
			};

			struct Label
			{
				TXString fIconSpec;	// An icon that is dispalyed on each view pane
				TXString fLabel;	// A label that is displayed on each view pane
			};

			struct GetLabelsArgs
			{
				std::vector<Label> fLabels;
			};

			struct AdvanceStateArgs
			{
				size_t fLabelIndex;
			};

			struct Args
			{
				Sint32 fPane = 0;
				TXString fRow;

				union
				{
					void* fUnknownArgs = nullptr;
					GetLabelsArgs* fGetLabelsArgs;
					AdvanceStateArgs* fAdvanceStateArgs;
				};
			};

			// ---------------------------------------------------------------------------------------------------
			// UUID = {afeb015d-ed4d-4953-806e-2c4ff1e1cfee}
			static const VWIID IID_ViewPaneLabels = { 0xafeb015d, 0xed4d, 0x4953,{ 0x80, 0x6e, 0x2c, 0x4f, 0xf1, 0xe1, 0xcf, 0xee } };

			class DYNAMIC_ATTRIBUTE IViewPaneLabelAPI : public IEventSink
			{
			public:
				virtual bool VCOM_CALLTYPE RowAdd(Sint32 paneID, const TXString& rowID, const TXString& parentRow, std::function<void(Operation, Args&)> callback) = 0;
				virtual bool VCOM_CALLTYPE RowRemove(Sint32 paneID, const TXString& rowID) = 0;
			};
		}
	}
}