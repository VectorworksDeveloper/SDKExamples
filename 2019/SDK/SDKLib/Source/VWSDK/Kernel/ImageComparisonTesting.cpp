#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Kernel/ImageComparisonTesting.h"

extern Boolean gVSHushErrorDialogs;

VCOMError VectorWorks::Debug::RunImageComparison(VectorWorks::Filing::IFolderIdentifierPtr settingsFolder, VectorWorks::Filing::IFileIdentifierPtr testImage, ImageTestResults& results)
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
				python->ScriptContext_AddVariable("testFilePath", testFile);				
				python->ScriptContext_AddVariable("dirPath", curDir);
				Boolean suppressVSErrors = true;
				gSDK->SetProgramVariable(9876, &suppressVSErrors);
				TState<Boolean> suppressErrors(gVSHushErrorDialogs, true);
				error = python->ScriptContext_Run();										
				if (VCOM_SUCCEEDED(error))													
				{																			
					VectorWorks::Filing::IFileIdentifierPtr resultsFile(VectorWorks::Filing::IID_FileIdentifier);
					resultsFile->Set(settingsFolder, "results.csv");							
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
									result.second.fMeanSqr = words[5].atof();				
									result.second.fHistDiff = words[6].atof();				
									result.second.fColor = words[7].atof();					
									result.second.fAngleTol = words[8].atoi();
									result.second.fBaseImage =  words[9];
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
