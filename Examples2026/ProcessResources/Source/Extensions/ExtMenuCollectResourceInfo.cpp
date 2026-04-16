#include "StdAfx.h"
#include "ExtMenuCollectResourceInfo.h"

using namespace VectorWorks;
using namespace CollectResourceInfo;

namespace CollectResourceInfo
{

	static SMenuDef		gMenuDef = {
		/*Needs*/			EMenuEnableFlags::DocIsActive,
		/*NeedsNot*/		EMenuEnableFlags::None,
		/*Title*/			{"ExtMenuCollectResourceInfo", "title"},
		/*Category*/		{"ExtMenuCollectResourceInfo", "category"},
		/*HelpText*/		{"ExtMenuCollectResourceInfo", "help"},
		/*VersionCreated*/	31,
		/*VersoinModified*/	31,
		/*VersoinRetired*/	0,
		/*OverrideHelpID*/	""
	};
}


IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenuCollectResourceInfo,		
	/*Event sink*/		CExtMenuCollectResourceInfo_EventSink,
	/*Universal name*/	"Collect Resource Tags",		
	/*Version*/			1,				
	/*UUID*/			0xabd053cd, 0xb708, 0x4054, 0x9c, 0x29, 0xb7, 0x5, 0x78, 0xd3, 0xdb, 0xd9);


CExtMenuCollectResourceInfo::CExtMenuCollectResourceInfo(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef )
{
}

CExtMenuCollectResourceInfo::~CExtMenuCollectResourceInfo()
{
}


CExtMenuCollectResourceInfo_EventSink::CExtMenuCollectResourceInfo_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
{
}

CExtMenuCollectResourceInfo_EventSink::~CExtMenuCollectResourceInfo_EventSink()
{
}

static size_t _CalcObjectMemSizeReq(MCObjectHandle h, bool doHandleBody, bool doChild, bool doAux)
{
	size_t result = 0;
	if ( doHandleBody )
	{
		// adjust size for sub-handle, etc.
		const CBSignedShort kKludgeDebugListViewCalculateObjSize = 7314;
		gSDK->Kludge(kKludgeDebugListViewCalculateObjSize, h, &result);
	}

	if ( doChild )
	{
		for(MCObjectHandle hChild = gSDK->FirstMemberObj( h );
			hChild && *hChild;
			hChild = gSDK->NextObject( hChild ) )
		{
			result += ::_CalcObjectMemSizeReq( hChild, true, true, true );
		}
	}

	if ( doAux )
	{
		for(MCObjectHandle hChild = gSDK->FirstAuxObject( h );
			hChild && *hChild;
			hChild = gSDK->NextObject( hChild ) )
		{
			result += ::_CalcObjectMemSizeReq( hChild, true, true, true );
		}
	}

	return result;
}

// This function collects all symbol definitions in the selected library folder,
// imports them to the current document one by one, collects their tags and calculates their disk size (including all sub-handles and aux-handles)
// and outputs all this information to a tab-delimited text file.
void CExtMenuCollectResourceInfo_EventSink::DoInterface()
{
	IFileIdentifierPtr	_fileID( IID_FileIdentifier );
	bool				_saved = false;
	
	if ( gSDK->GetActiveDocument( &_fileID, _saved ) )
	{
		IFolderChooserDialogPtr folderChooser ( IID_FolderChooserDialog );
		folderChooser->SetTitle( TXResStr("ExtMenuCollectResourceInfo","SelFolder_Title") );
		folderChooser->SetDescription( TXResStr("ExtMenuCollectResourceInfo","SelFolder_Description") );
		if ( VCOM_SUCCEEDED( folderChooser->RunDialog() ) )
		{
			IFolderIdentifierPtr	folderIDPtr( IID_FolderIdentifier );
			folderChooser->GetSelectedPath( &folderIDPtr );

			TXStringSTLUnorderedSet setFilePaths;
			CProgressDlg			progressDlg;
			Sint32					loopCount	= 1; // +1 since we do a final loop/yield after EnumerateContents
			TXStringSTLArray		arrResults; // contains tabulated results, each index corresponds to a row in the output

			TXString				fullPath;
			folderIDPtr->GetFullPath( fullPath );
			size_t					rootSize	= fullPath.GetLength();

			progressDlg.Open( TXResStr("ExtMenuCollectResourceInfo","ProgressDlg_Open"), false /*canCancel*/ );
			progressDlg.SetTopText( TXResStr("ExtMenuCollectResourceInfo","ProgressDlg_TopText"), true );
			progressDlg.SetMeterText( TXResStr("ExtMenuCollectResourceInfo","ProgressDlg_MeterText"), true );

			std::chrono::steady_clock::time_point clockStart = std::chrono::high_resolution_clock::now();

			// Calculate the loop count necessary for the progress dialog (loop on each folder)
			folderIDPtr->EnumerateContents(
				[ &loopCount, &rootSize ] ( IFolderIdentifier* folderID )
				{
					loopCount++;
					
					return EFolderContentListenerResult::eFolderContentListenerResult_Continue;
				},
				[] ( IFileIdentifier* fileID )
				{
					return EFolderContentListenerResult::eFolderContentListenerResult_Continue;
				}
			, true /*recursive*/ );

			progressDlg.Start( 100, loopCount );

			// Index all files
			folderIDPtr->EnumerateContents(
				[ &progressDlg ] ( IFolderIdentifier* folderID )
				{
					progressDlg.DoYield();

					return EFolderContentListenerResult::eFolderContentListenerResult_Continue;
				},
				[ & ] ( IFileIdentifier* fileID )
				{
					VWResourceList symList;
					size_t cnt = symList.BuildList( kSymDefNode, fileID );

					if ( cnt > 0 )
					{
						TXString filePath;
						fileID->GetFileFullPath( filePath );

						filePath = filePath.Right( filePath.GetLength() - rootSize );

						progressDlg.SetBottomText( TXString(TXResStr("ExtMenuCollectResourceInfo","ProgressDlg_BottomText")).Replace( "%1", filePath ), true );

						gSDK->SetUndoMethod( kUndoSwapObjects );
						gSDK->SupportUndoAndRemove();
						for ( size_t i = 0; i < cnt; ++i )
						{
							MCObjectHandle resH = symList.ImportResourceToCurrentFile( i, VectorWorks::eImportResourceConflictResult_Replace );

							if ( resH ) 
							{
								TXString symName;
								symList.GetResourceName( i, symName );

								TXStringArray arrTags;
								gSDK->GetResourceTags( resH, arrTags );

								TXString tagsString;
								for ( const TXString& tag : arrTags )
								{
									tagsString += tag + ", ";
								}

								size_t nodeDiskSize = _CalcObjectMemSizeReq( resH, true, true, true );

								TXString finalString;
								finalString.Format( "%s\tSymbol Definition\t%s\t%s\t%d", filePath, symName, tagsString, nodeDiskSize );
								arrResults.push_back( finalString );
							}
						}

						gSDK->UndoAndRemove();
					}
					return EFolderContentListenerResult::eFolderContentListenerResult_Continue;
				}, true /*recursive*/ );

			progressDlg.DoYield();
			progressDlg.End();
			progressDlg.Close();
			std::chrono::steady_clock::time_point clockEnd = std::chrono::high_resolution_clock::now();

			auto timePassed	= std::chrono::duration_cast<std::chrono::seconds>( clockEnd - clockStart ).count(); // DF ~230s

			IFileIdentifierPtr	outFileIDPtr( IID_FileIdentifier );
			TXString			outFilePath;

			outFileIDPtr->Set( kLibrariesFolder, true /*userFolder*/, "ResourceReportOutputFile.txt" );
			outFileIDPtr->GetFileFullPath( outFilePath );

			std::ofstream outputFile( outFilePath.operator const char* ( ), std::ofstream::trunc );

			outputFile	<< "File Path" << "\t"
						<< "Resource Type" << "\t"
						<< "Resource Name" << "\t"
						<< "Resource Tags" << "\t"
						<< "Node Disk Size (bytes)" << "\t"
						<< std::endl << std::endl;

			for ( const auto & row : arrResults )
			{
				outputFile << row.operator const char* ( ) << std::endl;
			}

			outputFile.close();

			outFileIDPtr->RevealInOS();
		}
	}
	else
	{
		gSDK->AlertInform( TXResStr("ExtMenuCollectResourceInfo","Err_Msg"), TXResStr("ExtMenuCollectResourceInfo","Err_Advice") );
	}
}
