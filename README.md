# Vectorworks SDK Examples

This folder contains an example for the Vectorworks 2021 SDK.

Developer information available at https://developer.vectorworks.net/

Please contact us [devsupport@vectorworks.net] to get included in the Partner Install if you have a user facing feature. See https://developer.vectorworks.net/index.php/Partner_Product_Install_Package

# Build instructions

### If you downloaded the repo directly on MacOS, you should de-quarantine the .zip before you unpack it. To do so, open the terminal and type:
```
xattr -d com.apple.quarantine FILE_LOCATION_HERE.
```

## Source requirements

This folder contains everything necessary to build the example.

If you use this code as a foundation for your work, make sure you change all required UUIDs in the code. All places where this needs to happen are marked with:
```
/*YOU MUST CHANGE THIS UUID if you copy this code*/
```
Failure to do so will result in plugin conflicts between source that have duplicate UUIDs ultimately resulting in one of the two features not working on the client machine.

**Note:** The Debug builds for win and mac are actually based on the release SDK with the difference that symbol generation is turned on and optimizations are turned off. The Debug SDK doesn't actually work with the release Vectorworks and I kept the mac version the same, as git doesn't allow the large debug library files to be added to the repository.

## Build tools requirements
- Windows - Visual Studio 2017, toolset version 14.12
- MacOS Big Sur  - Xcode 12.3

# Running & Debugging instructions

You need a copy of Vectorworks 2021 in order to run this example.

## Compile: you need to compile at least one example. This will create an output folder at:
```
Mac: <root folder>/Output/2021/_Output/
Windows: <root folder>\Output\2021\_Output\
```
Where `<root folder>` is the name of the cloned/downloaded reposity.

This location contains the debug and release (in separate folders) compiled dll of the plugin (actual file extension .vlb on win, and .vwlibrary on mac) and the resource file (.vwr) which is a file link under debug and a no-compression zip under release builds.

Additionally, once you compile an example, there will be an `IntermediateBuildFiles` folder that contains the intermediete compile files.

## Make Vectorworks find your built plugin

Find your Vectorworks installation's Plug-ins folder (Details on how to do this are in the included tutorial pdf). Create a shortcut/alias for:
```
Mac: <root folder>/Output/2021/_Output
Windows: <root folder>\Output\2021\_Output
```
Which will be moved into the user's plugin folder in Vectorworks:

* Mac: `/Users/<Username>/Library/Application Support/Vectorworks/2021/`
 * Windows: `C:\Users\<Username>\AppData\Roaming\Nemetschek\Vectorworks\2021\`

Note: this has the advantage that the plugin will be visible always to the specified Vectorworks version, regardless which Vectorworks copy you are running)
  
## This plugin works

If you run Vectorworks, your plugin should be found and the extensions it provices (menus, tools, objects, or functions) should be available.

## Debugging

You can setup VisualStuio and Xcode to execute Vectorworks and since it will load your compiled plugin from the place where it was compiled, VisualStudio and Xcode will be able to debug it. (release builds will act strangely when you debug as the code has been optimized and doesn't have direct relation to the source)

### VisualStudio

Right-click on the project, select 'Properties'. Then in the 'Debugging' tab, put the full path to Vectorworks.exe in the 'Command' field. You can use the popup to select 'Browse..'

This will instruct the VisualStudio to execute Vectorworks.exe for the debug settion. Then Vectorworks will load the dll (.vlb) of the plugin which it generated, and this will allow the debugger to respect breakpoints and debug the code.

## Xcode

From the Xcode menu, select Product -> Scheme -> Edit Scheme... menu command. Then on the 'Run' pane, open up the 'Executable' popup  and choose 'Other...' which will allow selection of an application that will be used for debugging.


## Debugging and Troubleshooting Tips

Some common issues which have been encountered are documented here.

### Common MacOS Issues
1. If you move any of the directories within the project directory around, keep in mind you will potentially have to edit those file paths within the project preferences pane. 

2. Outdated software/ Updated SDK/ Updated XCode – This project is tested to work on MacOS Big Sur with XCode Version 12.2.

3. Vectorworks doesn’t pick up the plugin.
	* Potential reasons:
		1) Incorrect alias folder: When making an alias, make sure that the folder contains the WebExample.vwlibrary file. For clarification, see steps 3, 4, and 10 in the included installation walkthrough. 
		2) Delete the .vwlibrary and .dSYM files present in the Debug/Alias folder and recompile the project so that it contains a brand new library file. An older version may potentially cause you issues.
		3) Incorrect version of the SDK or SDK Library. Please make sure you’re using the 2021 Version of the SDK included in the repo. Using older versions may result in missing or changed dependencies. 

4. NNA_Plugin_x files may not be found. 
	* How to fix: Press on the red-text missing file name so that the properties box on the right of XCode opens up.   Under the Location option, there should be the full path of the file. To the right of the full path, there is a little Folder icon. Click that, then navigate into the included Vectorworks SDK ->  /VectorworksSDK/SDK2021/SDKLib/Include/OnlyMac/. In here, you should find the correct file. Select it and the red text should go away, indicating that it is able to detect the file. 

5. Command CodeSign failed with nonzero exit 
	* Potential solutions:
		1) Make sure the project is stored locally. Storing it remotely may result in XCode needing the code to be signed. Storing it remotely allows for the target and project to be signed remotely. 
		2) Go to Project AND Target Build Settings, navigate to the Signing section, set Code Signing Identity to Don’t Code Sign, or to an empty box. (Source: https://stackoverflow.com/questions/31039513/how-can-i-skip-code-signing-for-development-builds-in-xcode)
	
6. File StdAfx.h not found after cleaning build files. 
	* Solution: Ignore it! When you build and run the project, this error will disappear.

### Common Windows 10 Issues
1. If you change any file paths around, please keep in mind that you may have to edit some of the file paths inside of the Properties pane. If you decide to edit file paths, ensure that if you make changes to the Debug configuration, make those same changes to the Release configuration. You can minimize the amount of individual changes you’ll have to make by making these changes under the All Configurations option in the Configuration drop-down menu by the top of the Properties pane. You may also have to manually edit the project file itself in a text editor.

2. Incorrect Windows SDK installed: The Windows SDK version being used for this project is 10.0.15063.0.

3. Visual Studio 17 (v141) was used for this project and tutorial. 
