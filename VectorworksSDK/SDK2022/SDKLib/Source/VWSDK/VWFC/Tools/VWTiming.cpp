//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


#ifndef _WINDOWS
# include <time.h>	// timing for Mac
#endif


using namespace VWFC::Tools;
using namespace VWFC::VWUI;




// protect from reqursive timing environments
static Sint32 gEnvironmentRunningLevel	= 0;
static std::vector<const char*>	gArrCallstack;

static TXString _CollectCallstack()
{
	TXString	result;

	size_t		cnt	= gArrCallstack.size();
	for(size_t i=0; i<cnt; i++) {
		const char*	szFunction	= gArrCallstack[ i ];

		if ( i > 0 ) {
			result	+= " -> ";
		}

		if ( szFunction ) {
			result	+= szFunction;
		}
		else {
			result	+= "Unknown";
		}
	}

	return result;
}

// ------------------------------------------------------------------------------------------------------------------------------
CTimingEnvironment::CTimingEnvironment(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext)
	: fTiming( NULL )
	, fSettingsProvider( provider )
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		// first environment initializes the timing
		if ( gEnvironmentRunningLevel == 0 ) {
			VWFC::Tools::VWTiming::Initialize();
		}

		gEnvironmentRunningLevel++;

		fTiming		= SDK_NEW CTiming( provider, szFunction, szContext );
	}
	else {
		gEnvironmentRunningLevel++;
	}
}

CTimingEnvironment::~CTimingEnvironment()
{
	gEnvironmentRunningLevel--;

	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		if ( fTiming ) {
			delete fTiming;
			fTiming		= NULL;
		}

		// last environment shows the timing result dialog and deinitializes
		if ( gEnvironmentRunningLevel == 0 ) {
			TXStringArray		arrLines;
			VWFC::Tools::VWTiming::GetInstance()->GetTimingResult( "DTM", arrLines );

			fSettingsProvider->OnTimingFinished( arrLines );

			if ( fSettingsProvider->IsTimingShow() ) {
				VWFC::Tools::VWTiming::GetInstance()->ShowTimingResultDialog( "DTM" );
			}
			VWFC::Tools::VWTiming::Deinitilalize();
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------
CTiming::CTiming(ITimingSettingsProvider* provider, const char* szFunction)
	: fDataCnt( 0 )
	, fSettingsProvider( provider )
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		TXString	category	= this->Analyse( szFunction );

		gArrCallstack.push_back( szFunction );

		VWFC::Tools::VWTiming::GetInstance()->Start( category, "", ::_CollectCallstack() );
	}
}

CTiming::CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext)
	: fDataCnt( 0 )
	, fSettingsProvider( provider )
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		TXString	category	= this->Analyse( szFunction );

		gArrCallstack.push_back( szFunction );

		VWFC::Tools::VWTiming::GetInstance()->Start( category, szContext, ::_CollectCallstack() );
	}
}

CTiming::CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext, size_t data1, const char* str1)
	: fDataCnt( 0 )
	, fSettingsProvider( provider )
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		TXString	category	= this->Analyse( szFunction );

		gArrCallstack.push_back( szFunction );

		VWFC::Tools::VWTiming::GetInstance()->Start( category, szContext, ::_CollectCallstack() );
		fDataCnt		= 1;
		fData[0]		= data1;
		fDataStr[0]		= str1;
	}
}

CTiming::CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext, size_t data1, const char* str1, size_t data2, const char* str2)
	: fDataCnt( 0 )
	, fSettingsProvider( provider )
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		TXString	category	= this->Analyse( szFunction );

		gArrCallstack.push_back( szFunction );

		VWFC::Tools::VWTiming::GetInstance()->Start( category, szContext, ::_CollectCallstack() );
		fDataCnt		= 2;
		fData[0]		= data1;
		fDataStr[0]		= str1;
		fData[1]		= data2;
		fDataStr[1]		= str2;
	}
}

CTiming::CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext, size_t data1, const char* str1, size_t data2, const char* str2, size_t data3, const char* str3)
	: fDataCnt( 0 )
	, fSettingsProvider( provider )
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		TXString	category	= this->Analyse( szFunction );

		gArrCallstack.push_back( szFunction );

		VWFC::Tools::VWTiming::GetInstance()->Start( category, szContext, ::_CollectCallstack() );
		fDataCnt		= 3;
		fData[0]		= data1;
		fDataStr[0]		= str1;
		fData[1]		= data2;
		fDataStr[1]		= str2;
		fData[2]		= data3;
		fDataStr[2]		= str3;
	}
}

CTiming::~CTiming()
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		gArrCallstack.pop_back();

		switch ( fDataCnt ) {
			case 0:
			default:
				VWFC::Tools::VWTiming::GetInstance()->End( fTaskInfo );
				break;
			case 1:
				VWFC::Tools::VWTiming::GetInstance()->End( fTaskInfo, fData[0], fDataStr[0] );
				break;
			case 2:
				VWFC::Tools::VWTiming::GetInstance()->End( fTaskInfo, fData[0], fDataStr[0], fData[1], fDataStr[1] );
				break;
			case 3:
				VWFC::Tools::VWTiming::GetInstance()->End( fTaskInfo, fData[0], fDataStr[0], fData[1], fDataStr[1], fData[2], fDataStr[2] );
				break;
		}
	}
}

void CTiming::AddData(size_t data, const char* str)
{
	if ( fSettingsProvider && fSettingsProvider->IsTiming() ) {
		if ( fDataCnt < 3 ) {
			fData[ fDataCnt ]		= data;
			fDataStr[ fDataCnt ]	= str;
			fDataCnt++;
		}
	}
}

TXString CTiming::Analyse(const char* szFunction)
{
	TXString	str	= szFunction;
	ptrdiff_t	at	= str.Find( '(' );
	if ( at >= 0 ) {
		str	= str.Left( at );
	}

	TXStringSTLArray	arrTokens;
	TXStringExt::Tokenize( szFunction, arrTokens, ":" );

	size_t	tokensCnt	= arrTokens.size();
	if ( tokensCnt >= 1 ) {
		fTaskInfo	= arrTokens[ tokensCnt - 1 ];
	}

	TXString	category;
	if ( tokensCnt >= 3 ) {
		category	= arrTokens[ tokensCnt - 3 ];
	}

	return category;
}


// ------------------------------------------------------------------------------------------------

VWTiming::STimerStart::STimerStart()
{
	startTime = 0;
}

VWTiming::STimerStart::~STimerStart()
{
	startTime = 0;
}

// ------------------------------------------------------------------------------------------------

VWTiming::SData::SData()
{
	data = 0;
}

VWTiming::SData::SData(size_t dt, const TXString& txt)
{
	data = dt;
	desc = txt;
}

VWTiming::SData::~SData()
{
	data = 0;
}

// ------------------------------------------------------------------------------------------------

VWTiming::STimerCollected::STimerCollected()
{
	isValid			= true;
	timeEllapsed	= 0;
	count			= 1;
}

VWTiming::STimerCollected::~STimerCollected()
{
	timeEllapsed	= 0;
	count			= 0;
}

// ------------------------------------------------------------------------------------------------

VWTiming::STimerCategory::STimerCategory()
{
}

VWTiming::STimerCategory::~STimerCategory()
{
}

// ------------------------------------------------------------------------------------------------
VWTiming* VWTiming::spInstance	= NULL;

VWTiming::VWTiming()
{
}

VWTiming::~VWTiming()
{
}

VWTiming* VWTiming::GetInstance()
{
	// you should init the timer first
	VWFC_ASSERT( spInstance != NULL );
	return spInstance;
}

void VWTiming::Initialize()
{
	VWFC_ASSERT( spInstance == NULL );
	if ( spInstance == NULL )
		spInstance	= new VWTiming;
}

void VWTiming::Deinitilalize()
{
	VWFC_ASSERT( spInstance != NULL );
	if ( spInstance != NULL )
		delete spInstance;
	spInstance = nullptr;
}

Uint32 VWTiming::GetTimer()
{
	Uint32		time	= 0;
#ifdef _WINDOWS
	time		= (Uint32) ::GetTickCount();
#else
	time		= gSDK->TickCount() * 17;	// Mac returns 1 /60th of a second
#endif
	return time;
}

void VWTiming::Start(const TXString& category, const TXString& context, const TXString& callstack)
{
	STimerStart	start;
	start.category		= category;
	start.context		= context;
	start.startTime		= this->GetTimer();
	start.callstack		= callstack;

	fTimerStartQueue.push_back( start );
}

void VWTiming::End(const TXString& taskInfo, STimerCollected& collected)
{
	Uint32		thisTime	= this->GetTimer();

	STimerStart	started		= fTimerStartQueue.back();
	fTimerStartQueue.pop_back();

	collected.context		= started.context;
	collected.callstack		= started.callstack;
	collected.taskInfo		= taskInfo;
	collected.timeEllapsed	= thisTime - started.startTime;

	STimerCategory*	pFoundCategory		= NULL;
	// find if the category already exist
	size_t		len			= fTimerCategories.size();
	for(size_t i=0; i<len; i++) {
		STimerCategory&		category	= fTimerCategories[ i ];
		if ( category.category == started.category )  {
			pFoundCategory		= & category;
			break;
		}
	}

	// if found -- add to existring
	// otherwise create new category
	if ( pFoundCategory ) {
		pFoundCategory->arrTimerData.push_back( collected );
	}
	else {
		STimerCategory		newCategory;
		newCategory.category		= started.category;
		newCategory.arrTimerData.push_back( collected );

		fTimerCategories.insert( fTimerCategories.begin(), newCategory );
	}
}

void VWTiming::End(const TXString& taskInfo)
{
	STimerCollected	collected;
	this->End( taskInfo, collected );
}

void VWTiming::End(const TXString& taskInfo, size_t data1, const TXString& str1)
{
	STimerCollected	collected;
	collected.arrData.push_back( SData( data1, str1 ) );
	this->End( taskInfo, collected );
}

void VWTiming::End(const TXString& taskInfo, size_t data1, const TXString& str1, size_t data2, const TXString& str2)
{
	STimerCollected	collected;
	collected.arrData.push_back( SData( data1, str1 ) );
	collected.arrData.push_back( SData( data2, str2 ) );
	this->End( taskInfo, collected );
}

void VWTiming::End(const TXString& taskInfo, size_t data1, const TXString& str1, size_t data2, const TXString& str2, size_t data3, const TXString& str3)
{
	STimerCollected	collected;
	collected.arrData.push_back( SData( data1, str1 ) );
	collected.arrData.push_back( SData( data2, str2 ) );
	collected.arrData.push_back( SData( data3, str3 ) );
	this->End( taskInfo, collected );
}

void VWTiming::Compact()
{
	/*typedef std::map<TXString, size_t>	TStringToIndexMap;

	size_t	catCnt			= fTimerCategories.size();
	for(size_t iCat=0; iCat<catCnt; iCat++) {
		VWTiming::STimerCategory& cat	= fTimerCategories[ iCat ];

		TStringToIndexMap	mapTaskInfo;

		size_t	timerDataCnt	= cat.arrTimerData.size();
		for(size_t iTimerData=0; iTimerData<timerDataCnt; iTimerData++) {
			STimerCollected&	timerData	= cat.arrTimerData[ iTimerData ];

			TStringToIndexMap::iterator it = mapTaskInfo.find( timerData.taskInfo );
			if ( it == mapTaskInfo.end() ) {
				mapTaskInfo.insert( TStringToIndexMap::value_type( timerData.taskInfo, iTimerData ) );
			}
			else {
				STimerCollected&	originalTimerData	= cat.arrTimerData[ it->second ];
				originalTimerData.timeEllapsed			+= timerData.timeEllapsed;
				originalTimerData.count++;
				for(TDataArray::iterator itData = timerData.arrData.begin(); itData != timerData.arrData.end(); ++itData) {
					originalTimerData.arrData.push_back( *itData );
				}

				timerData.isValid			= false;
			}
		}
	}*/
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
// Timing dialog
namespace VWFC {
	namespace Tools {
		class CTimingResultsDialog : public VWDialog 
		{
			const VWTiming::TTimerCategoriesArray&	fArrCategories;
			TXString								fstrDescription;

			VWTabCtrl					fTabCtrl;
			VWPushButtonCtrl			fExportButton;
			struct SCategories {
				size_t						fTimerCatIndex;
				VWTabPaneCtrl*				fpTabPaneCtrl;
				VWListBrowserCtrl*			fpListBoxCtrl;
			};
			typedef std::vector<SCategories>		TDlgCategoriesArray;

			TDlgCategoriesArray					farrCategories;

		public:
			// -----------------------------------------------------------------------
			CTimingResultsDialog(const VWTiming::TTimerCategoriesArray& categories, const TXString& desc)
				: fArrCategories( categories ), fTabCtrl( 3 ), fExportButton( kLeftButtonID )
			{
				fstrDescription		= desc;
			}

			// -----------------------------------------------------------------------
			~CTimingResultsDialog()
			{
				size_t	len		= farrCategories.size();
				for(size_t i=0; i<len; i++) {
					SCategories& cat	= farrCategories[i];
					delete cat.fpTabPaneCtrl;
					delete cat.fpListBoxCtrl;
				}
			}

			// -----------------------------------------------------------------------
			virtual bool CreateDialogLayout()
			{
				TXString		dlgTitle	= "Timing Results : ";
				dlgTitle					+= fstrDescription;
				if ( ! this->CreateDialog( dlgTitle, "Close", "", false, true, true ) )			return false;

				if ( ! fTabCtrl.CreateControl( this ) )								return false;

				if ( ! fExportButton.CreateControl( this, "Export..." ) )			return false;

				size_t	ctrlID		= 4;
				// create controls
				size_t	len			= fArrCategories.size();
				for(size_t i=0; i<len; i++) {
					const VWTiming::STimerCategory& cat	= fArrCategories[ i ];

					SCategories		dlgCat;
					dlgCat.fTimerCatIndex		= i;
					dlgCat.fpTabPaneCtrl		= new VWTabPaneCtrl ((Sint32)  ctrlID++ ); 
					if ( dlgCat.fpTabPaneCtrl && ! dlgCat.fpTabPaneCtrl->CreateControl( this, cat.category ) )	return false;

					dlgCat.fpListBoxCtrl		= new VWListBrowserCtrl ((Sint32)  ctrlID++ ); 
					if ( dlgCat.fpListBoxCtrl && ! dlgCat.fpListBoxCtrl->CreateControl( this, 90, 15 ) )		return false;

					farrCategories.push_back( dlgCat );
				}

				// start arranging
				this->AddFirstGroupControl( & fTabCtrl );

				// arrange controls
				len					= farrCategories.size();
				for(size_t i=0; i<len; i++) {
					const SCategories& cat	= farrCategories[i];

					fTabCtrl.AddPane( cat.fpTabPaneCtrl );
					cat.fpTabPaneCtrl->AddFirstGroupControl( cat.fpListBoxCtrl );
					cat.fpTabPaneCtrl->SetEdgeBinding( true, true, true, true );
					cat.fpListBoxCtrl->SetEdgeBinding( true, true, true, true );
				}

				fTabCtrl.SetEdgeBinding( true, true, true, true );

				return true;
			}

			// -----------------------------------------------------------------------
			virtual	void OnDDXInitialize()
			{
			}

			// -----------------------------------------------------------------------
			virtual void OnSetUpEvent()
			{
				size_t	len			= farrCategories.size();
				for(size_t i=0; i<len; i++) {
					const SCategories&				cat		= farrCategories[i];
					const VWTiming::STimerCategory& timeCat	= fArrCategories[ cat.fTimerCatIndex ];

					cat.fpListBoxCtrl->InsertColumn( 0, "taskInfo", 200 );
					VWListBrowserColumn	timeCol	= cat.fpListBoxCtrl->InsertColumn( 1, "time", 75 );
					VWListBrowserColumn	cntCol	= cat.fpListBoxCtrl->InsertColumn( 2, "cnt", 37 );
					cat.fpListBoxCtrl->InsertColumn( 3, "context", 100 );
					cat.fpListBoxCtrl->InsertColumn( 4, "data", 150 );
					cat.fpListBoxCtrl->InsertColumn( 5, "callstack", 300 );
					timeCol.SetColumnHeaderJust( kColumnHeaderJustificationCenter );
					cntCol.SetColumnHeaderJust( kColumnHeaderJustificationCenter );
				
					size_t	len1			= timeCat.arrTimerData.size();
					// dont allow more than 100 time results
					// we dont want to overflow the lists max (32768)
					if ( len1 > 100 ) {
						// show first items only
						len1	= 100;
					}
					for(size_t j=0; j<len1; j++) {
						const VWTiming::STimerCollected&	timer	= timeCat.arrTimerData[ j ];
						if ( timer.isValid ) {
							double		time		= ((double) timer.timeEllapsed) / 1000;
							TXString	strTime;	strTime.Format( "%.5f sec", time );
							TXString	strCount;
							strCount.Format( "%d", timer.count );
							TXString	strData;
							size_t		dataLen		= timer.arrData.size();
							for(size_t j=0; j<dataLen; j++) {
								const VWTiming::SData&	data	= timer.arrData[j];

								TXString	str;
								str.Format( "(%d %s)", data.data, data.desc );
								strData		+= str;
							}

							TXString	strCallstack;
							if ( timer.callstack.GetLength() > 250 ) {
								strCallstack	= timer.callstack.Mid( timer.callstack.GetLength() - 250 );
							}
							else {
								strCallstack	= timer.callstack;
							}

							size_t					itemIndex	= cat.fpListBoxCtrl->AddRow( timer.taskInfo );

							cat.fpListBoxCtrl->GetItem( itemIndex, 1 ).SetItemText( strTime );
							cat.fpListBoxCtrl->GetItem( itemIndex, 2 ).SetItemText( strCount );
							cat.fpListBoxCtrl->GetItem( itemIndex, 3 ).SetItemText( timer.context );
							cat.fpListBoxCtrl->GetItem( itemIndex, 4 ).SetItemText( strData );
							cat.fpListBoxCtrl->GetItem( itemIndex, 5 ).SetItemText( strCallstack );

							//cat.fpListBoxCtrl->SetItemTextJustification( itemIndex, 1, kListBrowserTextJustificationRight );
						}
					}				
				}
			}
			// -----------------------------------------------------------------------
			virtual void OnBeforeDispatchEvent(TControlID controlID, VWDialogEventArgs& eventArg)
			{
				using namespace VectorWorks::Filing;
				if ( fExportButton.GetControlID() == controlID ) {
					IFileChooserDialogPtr	pFileChooser( IID_FileChooserDialog );
					if ( pFileChooser ) {
						pFileChooser->SetTitle( "Select file to export profile" );
						pFileChooser->SetDefaultFileName( "Profile.txt" );
						pFileChooser->AddFilter( "txt", "Text File" );
						pFileChooser->AddFilterAllFiles();
						if ( VCOM_SUCCEEDED( pFileChooser->RunSaveDialog() ) ) {
						   IFileIdentifierPtr	pFileID;
						   if ( VCOM_SUCCEEDED( pFileChooser->GetSelectedFileName( 0, & pFileID ) ) ) {
							   IStdFilePtr	  pFile( IID_StdFile );
							   if ( pFile && VCOM_SUCCEEDED( pFile->OpenNewWrite( pFileID ) ) ) {
									TXStringArray arrLines;
									this->ShowResults( pFile, arrLines );
									pFile->Close();
							   }
						   }
						}
					}
				}
			}

			// -----------------------------------------------------------------------
			void ShowResults(VectorWorks::Filing::IStdFilePtr pFile, TXStringArray& outArrLines)
			{
				TXString	line;

			    size_t	len			= fArrCategories.size();
				for(size_t i=0; i<len; i++) {
					//const SCategories&				cat		= farrCategories[i];
					//const VWTiming::STimerCategory& timeCat	= fArrCategories[ cat.fTimerCatIndex ];
					const VWTiming::STimerCategory& timeCat	= fArrCategories[ i ];

					if ( i > 0 ) {
						if ( pFile )	pFile->WriteNewLine();
						else			DMSG((kVStanev, ""));
					}

					line		= "Category: ";
					line		+= timeCat.category;
					if ( pFile ) {
						pFile->WriteStringLine( line );
						pFile->WriteStringLine( "----------------------" );
					}
					outArrLines.Append( line );
					outArrLines.Append( "----------------------" );

					line		= "taskInfo";
					line		+= "\t";
					line		+= "time";
					line		+= "\t";
					line		+= "count";
					line		+= "\t";
					line		+= "context";
					line		+= "\t";
					line		+= "data";
					line		+= "\t";
					line		+= "callstack";
					if ( pFile ) {
						pFile->WriteStringLine( line );
					}
					outArrLines.Append( line );

					size_t	len1			= timeCat.arrTimerData.size();
					for(size_t j=0; j<len1; j++) {
						const VWTiming::STimerCollected&	timer	= timeCat.arrTimerData[ j ];
						if ( timer.isValid ) {
							double		time		= ((double) timer.timeEllapsed) / 1000;
							TXString	strTime;	strTime.Format( "%.5f sec", time );
							TXString	strCount;
							strCount.Format( "%d", timer.count );
							TXString	strData;
							size_t		dataLen		= timer.arrData.size();
							for(size_t j=0; j<dataLen; j++) {
								const VWTiming::SData&	data	= timer.arrData[j];

								TXString	str;
								str.Format( "(%d %s)", data.data, data.desc );
								strData		+= str;
								if ( j + 1< dataLen ) {
									strData		+= "\t";
								}
							}

							line		= timer.taskInfo;
							line		+= "\t";
							line		+= strTime;
							line		+= "\t";
							line		+= strCount;
							line		+= "\t";
							line		+= timer.context;
							line		+= "\t";
							line		+= strData;
							line		+= "\t";
							line		+= timer.callstack;
							if ( pFile ) {
								pFile->WriteStringLine( line );
							}
							outArrLines.Append( line );
						}
					}
				}
			}
		};
	}
};


void VWTiming::ShowTimingResultDialog(const TXString& description)
{
	this->Compact();

	CTimingResultsDialog	dlg( fTimerCategories, description );
	dlg.RunDialogLayout("ShowTimingResult");
}

void VWTiming::GetTimingResult(const TXString& description, TXStringArray& outArrLines)
{
	this->Compact();

	CTimingResultsDialog	dlg( fTimerCategories, description );

	outArrLines.Append( "" );
	outArrLines.Append( "" );
	TXString	line;
	line.Format( "Timing results: %s", description );
	outArrLines.Append( line );
	outArrLines.Append( "------------------" );
	dlg.ShowResults( NULL, outArrLines );
}
