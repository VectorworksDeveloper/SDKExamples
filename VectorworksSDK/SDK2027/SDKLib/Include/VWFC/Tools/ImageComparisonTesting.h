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
			double fSensitivityFullImage;
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

		bool CreateTestOnServer(const TXString& testName, const TXString& email);
		bool UploadGeneratedImageToServer(const TXString& testName, const TXString& stepName, const TXString& runName, IFileIdentifierPtr image);
		bool UploadTestImageToServer(const TXString& testName, const TXString& stepName, IFileIdentifierPtr image, double fullImageSensitivity, double histDiff);

		VCOMError RunImageComparison(VectorWorks::Filing::IFolderIdentifierPtr settingsFolder, const TXString& settingsFileName, VectorWorks::Filing::IFileIdentifierPtr testImage, ImageTestResults& results);

		//This will open a .vwx file, navigate to every saved view and export to PNG.  The images will be saved in a directory with the same name 
		//as the file directly next to the file.  Images will be named the same as their saved view with a suffix of "_base", and any such images that already exist will not be overwritten.  
		VCOMError GenerateBaseImagesFromFile(VectorWorks::Filing::IFileIdentifierPtr testFile);

		//This will navigate to every saved view, export to PNG as above, and run the image comparison library on every exported image.
		VCOMError TestSavedViewsInFile(VectorWorks::Filing::IFileIdentifierPtr testFile, std::vector<ImageTestResults>& results);

		//Autogenerates a C++ Catch image comparison test and submits everything to Perforce
		VCOMError AutogenerateSystemTest(const TXString& clientRoot, const TXString& testFilePath, const TXString& email);

		//Does the whole suite.  This will copy the test file into a temporary Perforce workspace, generate all base images and settings from its saved views,
		//then generate a C++ test that will run this file, then submits the whole thing to Perforce.  
		VCOMError GenerateImageComparisonTest(const TXString& username, const TXString& password, VectorWorks::Filing::IFileIdentifierPtr testFile, const TXString& email);


	}
}
