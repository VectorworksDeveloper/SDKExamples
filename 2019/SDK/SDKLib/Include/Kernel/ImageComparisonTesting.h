#pragma once

namespace VectorWorks
{
	namespace Debug
	{
		struct ImageTestSettings
		{
			TXString fImageName;
			Sint32 fSensitivity;
			bool fSolidSearch;
			bool fEntireImage;
			double fMeanSqr;
			double fHistDiff;
			Sint32 fNumMatches;
			double fColor;
			Sint32 fAngleTol;
			TXString fBaseImage;
		};

		struct ImageTestResults
		{
			bool fPassed;
			std::vector< std::pair<bool, ImageTestSettings> > fAreaPassed;
		};

		VCOMError RunImageComparison(VectorWorks::Filing::IFolderIdentifierPtr settingsFolder, VectorWorks::Filing::IFileIdentifierPtr testImage, ImageTestResults& results);
	}
}
