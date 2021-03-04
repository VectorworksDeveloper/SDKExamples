//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VectorworksSDK.h"

#include "DocumentFreezer/PrimitivesGroup.h"

using namespace VectorWorks::Filing;
using namespace VWFC::Tools;
using namespace VWFC::Tools::DocumentFreezer;

CDocumentFreezer::CDocumentFreezer()
{
}

CDocumentFreezer::~CDocumentFreezer()
{
}

void CDocumentFreezer::Freeze(IFileIdentifier* outputFileID, EDocumentFreezerVersion version)
{
	if ( version == eDocumentFreezerVersion_MaxVersion )
		version = (EDocumentFreezerVersion)(version - 1);

	IStdFilePtr outputFile( IID_StdFile );
	if ( VCOM_SUCCEEDED( outputFile->OpenNewWrite( outputFileID ) ) )
	{
		outputFile->Write( (Uint32) version );

		MCObjectHandle hDocument = gSDK->GetDrawingHeader();

		// the AUX list
		for(MCObjectHandle hAUX = gSDK->FirstAuxObject( hDocument );
			hAUX;
			hAUX = gSDK->NextObject( hAUX ))
		{
			if ( version <= eDocumentFreezerVersion_1 )
			{
				short type = gSDK->GetObjectTypeN( hAUX );
				if ( type == symListNode )
				{
					CPrimitiveSymbolFolder	primitive( hAUX );
					primitive.Freeze( outputFile, version );
				}
				else if ( type == kDataNode )
				{
					CPrimitiveAUXData	primitive( hAUX );
					primitive.Freeze( outputFile, version );
				}
			}
		}

		// the child list
		for(MCObjectHandle hLayer = gSDK->FirstMemberObj( hDocument );
			hLayer;
			hLayer = gSDK->NextObject( hLayer ))
		{
			if ( version <= eDocumentFreezerVersion_1 )
			{
				if ( VWLayerObj::IsLayerObject( hLayer ) )
				{
					CPrimitiveLayer	primitive( hLayer );
					primitive.Freeze( outputFile, version );
				}
			}
		}

		outputFile->Close();
	}
}

bool CDocumentFreezer::AssertFrozen(IFileIdentifier* inputFileID, EDocumentFreezerVersion& outVersion, IDocumentFreezerAsserter* asserter)
{
	bool result = false;

	IStdFilePtr inputFile( IID_StdFile );
	if ( VCOM_SUCCEEDED( inputFile->OpenRead( inputFileID, false ) ) )
	{
		Uint32		version	= 0;
		inputFile->Read( version );
		if ( version < eDocumentFreezerVersion_MaxVersion )
		{
			outVersion = (EDocumentFreezerVersion) version;
			result = true;

			MCObjectHandle hDocument = gSDK->GetDrawingHeader();

			// the AUX list
			for(MCObjectHandle hAUX = gSDK->FirstAuxObject( hDocument );
				hAUX && result;
				hAUX = gSDK->NextObject( hAUX ))
			{
				if ( version <= eDocumentFreezerVersion_1 )
				{
					short type = gSDK->GetObjectTypeN( hAUX );
					if ( type == symListNode )
					{
						CPrimitiveSymbolFolder	primitive( hAUX );
						result = result && primitive.AssertFrozen( inputFile, outVersion, asserter );
					}
					else if ( type == kDataNode )
					{
						CPrimitiveAUXData	primitive( hAUX );
						result = result && primitive.AssertFrozen( inputFile, outVersion, asserter );
					}
				}
			}

			// the child list
			for(MCObjectHandle hLayer = gSDK->FirstMemberObj( hDocument );
				hLayer && result;
				hLayer = gSDK->NextObject( hLayer ))
			{
				if ( outVersion <= eDocumentFreezerVersion_1 )
				{
					if ( VWLayerObj::IsLayerObject( hLayer ) )
					{
						CPrimitiveLayer	primitive( hLayer );
						result = result && primitive.AssertFrozen( inputFile, outVersion, asserter );
					}
				}
			}
		}
		else if ( asserter )
		{
			asserter->AddFail( "Incorrect file version", __FILE__, __LINE__ );
		}
	}

	return result;
}
