#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "VWFC/Tools/ImageComparisonTesting.h"
#include "../../ThirdPartySource/libcurl/include/curl/curl.h"
#include <iostream>

using namespace VectorWorks::Filing;

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool runCurl(const std::string& subUrl, curl_httppost* formpost)
{
	const std::string serverUrl = "http://gui-tests.vectorworks.net/api/";
	const std::string composedUrl = serverUrl + subUrl;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";
	CURL* curl = curl_easy_init();

	headerlist = curl_slist_append(headerlist, buf);
	bool result = true;
	if (curl) {
		std::string readBuffer;

		curl_easy_setopt(curl, CURLOPT_URL, composedUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		CURLcode res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
		{
			const char* err = curl_easy_strerror(res);
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				err);
			result = false;
		}
		else
		{
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			if (response_code)
			{

			}
		}


		curl_easy_cleanup(curl);

		curl_formfree(formpost);

		curl_slist_free_all(headerlist);
	}
	return result;
}

bool VectorWorks::Debug::CreateTestOnServer(const TXString& testName, const TXString& email)
{
	//curl_global_init has already been called during program startup
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "content-type:",
		CURLFORM_COPYCONTENTS, "multipart/form-data",
		CURLFORM_END);

	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "name",
		CURLFORM_COPYCONTENTS, testName.GetCharPtr(),
		CURLFORM_END);

	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "email",
		CURLFORM_COPYCONTENTS, email.GetCharPtr(),
		CURLFORM_END);

	return runCurl("tests/", formpost);
}

bool VectorWorks::Debug::UploadTestImageToServer(const TXString& testName, const TXString& stepName, IFileIdentifierPtr image, double fullImageSensitivity, double histDiff)
{
	//curl_global_init has already been called during program startup
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "content-type:",
		CURLFORM_COPYCONTENTS, "multipart/form-data",
		CURLFORM_END);

	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "test_name",
		CURLFORM_COPYCONTENTS, testName.GetCharPtr(),
		CURLFORM_END);

	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "name",
		CURLFORM_COPYCONTENTS, stepName.GetCharPtr(),
		CURLFORM_END);
	TXString threshold;
	threshold << fullImageSensitivity;
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "threshold",
		CURLFORM_COPYCONTENTS, threshold.GetCharPtr(),
		CURLFORM_END);
	TXString histogram_threshold;
	histogram_threshold << histDiff;
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "histogram_threshold",
		CURLFORM_COPYCONTENTS, histogram_threshold.GetCharPtr(),
		CURLFORM_END);

	TXString filePath;
	image->GetFileFullPath(filePath);
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "image",
		CURLFORM_FILE, filePath.GetCharPtr(),
		CURLFORM_END);
	return runCurl("test-steps/", formpost);
}

bool VectorWorks::Debug::UploadGeneratedImageToServer(const TXString& testName, const TXString& stepName, const TXString& runName, IFileIdentifierPtr image)
{
	//curl_global_init has already been called during program startup
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "content-type:",
		CURLFORM_COPYCONTENTS, "multipart/form-data",
		CURLFORM_END);
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "test_name",
		CURLFORM_COPYCONTENTS, testName.GetCharPtr(),
		CURLFORM_END);
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "step_name",
		CURLFORM_COPYCONTENTS, stepName.GetCharPtr(),
		CURLFORM_END);
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "run_name",
		CURLFORM_COPYCONTENTS, runName.GetCharPtr(),
		CURLFORM_END);
	TXString filePath;
	image->GetFileFullPath(filePath);
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "result_image",
		CURLFORM_FILE, filePath.GetCharPtr(),
		CURLFORM_END);
	return runCurl("test-run-steps/", formpost);
}

VCOMError VectorWorks::Debug::RunImageComparison(VectorWorks::Filing::IFolderIdentifierPtr settingsFolder, const TXString& settingsFileName, VectorWorks::Filing::IFileIdentifierPtr testImage, ImageTestResults& results)
{																							
	VectorWorks::Scripting::IPythonScriptEnginePtr python(VectorWorks::Scripting::IID_PythonScriptEngine);
	TXString script = TXResource("Vectorworks/Scripts/ImageCompareTests.py");				
	TXString curDir;																		
	results.fAreaPassed.clear();															
	results.fPassed = false;																
	VCOMError error = settingsFolder->GetFullPath(curDir);										
	if (VCOM_SUCCEEDED(error))																
	{																						
		TXString testFile;																	
		error = testImage->GetFileFullPath(testFile);										
		if (VCOM_SUCCEEDED(error))
		{		
			error = python->ScriptContext_Begin(script);
			if (VCOM_SUCCEEDED(error))
			{
				python->ScriptContext_AddVariable("settingsfile", settingsFileName);
				python->ScriptContext_AddVariable("testFilePath", testFile);
				python->ScriptContext_AddVariable("dirPath", curDir);
				Boolean suppressVSErrors = true;
				gSDK->SetProgramVariable(9876, &suppressVSErrors);
				error = python->ScriptContext_Run();
				if (VCOM_SUCCEEDED(error))
				{
					VectorWorks::Filing::IFileIdentifierPtr resultsFile(VectorWorks::Filing::IID_FileIdentifier);
					resultsFile->Set(settingsFolder, settingsFileName + "_results.csv");
					bool resultsExists;
					error = resultsFile->ExistsOnDisk(resultsExists);
					if (VCOM_SUCCEEDED(error) && resultsExists)
					{
						VectorWorks::Filing::IStdFilePtr file(VectorWorks::Filing::IID_StdFile);
						TXStringArray lines;
						error = file->ReadLines(resultsFile, lines);
						if (VCOM_SUCCEEDED(error))
						{
							bool overallFailed = false;
							for (size_t i = 1; i < lines.GetSize(); i++)
							{
								VWFC::Tools::TXStringSTLArray words;
								VWFC::Tools::TXStringExt::Tokenize(lines[i], words, ",");
								if (VERIFYN(kSWilcox, words.size() == 11))
								{
									std::pair<bool, ImageTestSettings> result;
									result.first = words[10].EqualNoCase("Pass");
									result.second.fImageName = words[0];
									result.second.fSensitivity = words[1].atoi();
									result.second.fSolidSearch = words[2].EqualNoCase("True");
									result.second.fNumMatches = words[3].atoi();
									result.second.fEntireImage = words[4].EqualNoCase("True");
									result.second.fSensitivityFullImage = words[5].atof();
									result.second.fHistDiff = words[6].atof();
									result.second.fColor = words[7].atof();
									result.second.fAngleTol = words[8].atoi();
									result.second.fBaseImage = words[9];
									if (!result.first)
										overallFailed = true;
									results.fAreaPassed.push_back(result);
								}
							}
							if (results.fAreaPassed.size() > 0 && !overallFailed)
								results.fPassed = true;
						}
					}
				}
				suppressVSErrors = false;
				gSDK->SetProgramVariable(9876, &suppressVSErrors);
			}
		}																					
	}																						
	return error;																			
}

void GenerateDefaultSettings(IFileIdentifierPtr baseImage)
{
	IFolderIdentifierPtr parentDir(IID_FolderIdentifier);
	baseImage->GetFolder(&parentDir);
	TXString filename;
	baseImage->GetFileNameWithoutExtension(filename);
	TXString filenameWithExt;
	baseImage->GetFileName(filenameWithExt);
	IFileIdentifierPtr settings(IID_FileIdentifier);
	settings->Set(parentDir, filename + ".csv");
	bool exists;
	settings->ExistsOnDisk(exists);
	if (!exists)
	{
		IStdFilePtr writeSettings(IID_StdFile);
		writeSettings->OpenNewWrite(settings);
		TXString header = "Template Image File,Sensitivity,Solid Search,Num000 Matches,Entire image,Mean Sqr,Hist diff,Color,Angle tol,Base Image\n";
		writeSettings->Write(header, false);
		TXString defaultSettings; 
		defaultSettings << filenameWithExt << ",700,FALSE,1,TRUE,700.000000,0.990000,0.000000,5," << filenameWithExt;
		writeSettings->Write(defaultSettings, false);
		writeSettings->Close();
	}
}

VCOMError NavigateSavedViews(VectorWorks::Filing::IFileIdentifierPtr testFile, bool saveBaseImages, std::function< bool(IFileIdentifierPtr) > callback)
{
	VCOMError result;
	if (gSDK->OpenDocumentPath(testFile, false))
	{
		IFolderIdentifierPtr parentDir(IID_FolderIdentifier);
		result = testFile->GetFolder(&parentDir);
		if (VCOM_SUCCEEDED(result))
		{
			IFolderIdentifierPtr settingsDir(IID_FolderIdentifier);
			TXString nameWithoutExt;
			result = testFile->GetFileNameWithoutExtension(nameWithoutExt);
			if (VCOM_SUCCEEDED(result))
			{
				result = settingsDir->Set(parentDir, nameWithoutExt);
				if (VCOM_SUCCEEDED(result))
				{
					bool exists;
					result = settingsDir->ExistsOnDisk(exists);
					if (VCOM_SUCCEEDED(result))
					{
						if (!exists)
						{
							settingsDir->CreateOnDisk();
						}
						short numViews = gSDK->GetNumSavedViews();
						for (short i = 1; i <= numViews; i++)
						{
							TXString viewName;
							gSDK->GetSavedView(i, viewName);
							TXString imageName = viewName;
							if (saveBaseImages)
							{
								imageName << "_base";
							}
							imageName << ".png";
							IFileIdentifierPtr destFilePtr(IID_FileIdentifier);
							destFilePtr->Set(settingsDir, imageName);
							if (saveBaseImages)
							{
								if (callback(destFilePtr))
									continue;
							}
							gSDK->RestoreSavedView(viewName);
							gSDK->DrawScreen();
							VectorWorks::SExportImageOptions info;
							info.fExportGeoreferencing = false;
							info.fResetAllPlugIns = false;
							info.fUpdateVewports = true;
							gSDK->ExportImage(destFilePtr, info);
							if (!saveBaseImages)
							{
								callback(destFilePtr);
							}
							else
							{
								GenerateDefaultSettings(destFilePtr);
							}
						}
					}
				}
			}
		}
		gSDK->CloseDocument();
	}
	else
	{
		result = kVCOMError_FileNotFound;
	}
	return result;
}

VCOMError VectorWorks::Debug::GenerateBaseImagesFromFile(VectorWorks::Filing::IFileIdentifierPtr testFile)
{
	return NavigateSavedViews(testFile, true, [&](IFileIdentifierPtr destFilePtr) {
		bool fileExists;
		if (VCOM_SUCCEEDED(destFilePtr->ExistsOnDisk(fileExists)) && fileExists)
		{
			return true;
		}
		return false;
	});
}

VCOMError VectorWorks::Debug::TestSavedViewsInFile(VectorWorks::Filing::IFileIdentifierPtr testFile, std::vector<ImageTestResults>& results)
{
	return NavigateSavedViews(testFile, false, [&](IFileIdentifierPtr destFilePtr) {
		ImageTestResults curResults;
		IFolderIdentifierPtr settingsDir(IID_FolderIdentifier);
		destFilePtr->GetFolder(&settingsDir);
		TXString settingsFileName;
		destFilePtr->GetFileNameWithoutExtension(settingsFileName);
		RunImageComparison(settingsDir, settingsFileName, destFilePtr, curResults);
		results.push_back(curResults);
		return false;
	});
}

VCOMError VectorWorks::Debug::AutogenerateSystemTest(const TXString& clientRoot, const TXString& testFilePath, const TXString& email)
{
	VectorWorks::Scripting::IPythonScriptEnginePtr python(VectorWorks::Scripting::IID_PythonScriptEngine);
	TXString script = TXResource("Vectorworks/Scripts/AutogenerateImageTests.py");
	VCOMError error = python->ScriptContext_Begin(script);
	if (VCOM_SUCCEEDED(error))
	{
		python->ScriptContext_AddVariable("clientRoot", clientRoot);
		python->ScriptContext_AddVariable("testFilePath", testFilePath);
		python->ScriptContext_AddVariable("email", email);
		error = python->ScriptContext_Run();
		VWVariant errors;
		VCOMError errorExists = python->Repository_GetValue("autoGenError", errors);
		if (VCOM_SUCCEEDED(errorExists))
		{
			TXString errorStr = errors.GetTXString();
			if (errorStr.IsEmpty())
			{
				gSDK->AlertCritical(errorStr);
			}

		}
	}
	return error;
}

#if GS_WIN
#define SEP "\\"
#else
#define SEP "/"
#endif

VCOMError PerforceSetup(const TXString& username, const TXString& password)
{
	VectorWorks::Scripting::IPythonScriptEnginePtr python(VectorWorks::Scripting::IID_PythonScriptEngine);
	TXString script = TXResource("Vectorworks/Scripts/PerforceAccess.py");

#if GS_WIN
	TXString clientName = TXString(_wgetenv(L"COMPUTERNAME"));
#else
    TXString clientName = "";//[[[NSHost currentHost] localizedName] toTXString];
#endif
	VCOMError error = python->ScriptContext_Begin(script);
	if (VCOM_SUCCEEDED(error))
	{
		python->ScriptContext_AddVariable("set", "True");
		python->ScriptContext_AddVariable("port", "perforce.nemetschek.net:1666");
		python->ScriptContext_AddVariable("user", username);
		python->ScriptContext_AddVariable("password", password);
		python->ScriptContext_AddVariable("client", "True");
		python->ScriptContext_AddVariable("clientSpec", "testAutoImageGen");
		python->ScriptContext_AddVariable("clientName", clientName);
		python->ScriptContext_AddVariable("open", "True");
		python->ScriptContext_AddVariable("openFiles", "//depot/Engineering/VectorWorks/Mainline/AppSource/Source/Include/UnitTests/AutoGeneratedImageTests.h");
		error = python->ScriptContext_Run();
	}
	return error;
}

VCOMError PerforceCleanup(IFileIdentifierPtr testFile)
{
	TXString fileName;
	testFile->GetFileName(fileName);
	TXString fullPath;
	testFile->GetFileFullPath(fullPath);
	TXString folderPath = fullPath.Left(fullPath.GetLength() - 4);
	folderPath = folderPath + SEP + "...";

	TXString allFilesToAdd = fullPath + ";" + folderPath;

	VectorWorks::Scripting::IPythonScriptEnginePtr python(VectorWorks::Scripting::IID_PythonScriptEngine);
	TXString script = TXResource("Vectorworks/Scripts/PerforceAccess.py");

#if GS_WIN
	TXString clientName = TXString(_wgetenv(L"COMPUTERNAME"));
#else
    TXString clientName = "";//[[[NSHost currentHost] localizedName] toTXString];
#endif

	VCOMError error = python->ScriptContext_Begin(script);
	if (VCOM_SUCCEEDED(error))
	{
		python->ScriptContext_AddVariable("add", "True");
		python->ScriptContext_AddVariable("addFiles", allFilesToAdd);
		python->ScriptContext_AddVariable("submit", "True");
		python->ScriptContext_AddVariable("description", "\"Generated image comparison test for " + fileName + "\"");
		python->ScriptContext_AddVariable("delete", "True");
		python->ScriptContext_AddVariable("clientName", clientName);
		error = python->ScriptContext_Run();
	}
	return error;
}

VCOMError VectorWorks::Debug::GenerateImageComparisonTest(const TXString& username, const TXString& password, VectorWorks::Filing::IFileIdentifierPtr testFile, const TXString& email)
{
	IApplicationFoldersPtr folders(IID_ApplicationFolders);
	IFolderIdentifierPtr tempFolder(IID_FolderIdentifier);
	VCOMError error = folders->GetOSSystemTemporaryFolder(&tempFolder);
	if (VCOM_SUCCEEDED(error))
	{
		TXString fileName;
		error = testFile->GetFileName(fileName);
		if (VCOM_SUCCEEDED(error))
		{
			TXString folderRoot;
			error = tempFolder->GetFullPath(folderRoot);
			if (VCOM_SUCCEEDED(error))
			{
				TXString clientRoot = folderRoot + "autoGenPerforce";
				TXString copyFileFolder = clientRoot + SEP + "depot" + SEP + "Engineering"+ SEP + "Documents" + SEP + "Tests" + SEP + "VW25" + SEP + "AutomatedSystemTests" + SEP + "ImageComparisonTests" + SEP;
				TXString copyFilePath = copyFileFolder + fileName;
				IFolderIdentifierPtr folder(IID_FolderIdentifier);
				error = folder->Set(copyFileFolder);
				if (VCOM_SUCCEEDED(error))
				{
					error = folder->CreateOnDisk();
					if (VCOM_SUCCEEDED(error))
					{
						IFileIdentifierPtr copyDest(IID_FileIdentifier);
						error = copyDest->Set(copyFilePath);
						if (VCOM_SUCCEEDED(error))
						{
							error = testFile->DuplicateOnDisk(copyDest, true);
							if (VCOM_SUCCEEDED(error))
							{
								error = GenerateBaseImagesFromFile(copyDest);
								if (VCOM_SUCCEEDED(error))
								{
									error = PerforceSetup(username, password);
									if (VCOM_SUCCEEDED(error))
									{
										error = AutogenerateSystemTest(clientRoot, copyFilePath, email);
										if (VCOM_SUCCEEDED(error))
										{
											PerforceCleanup(testFile);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return error;
}





