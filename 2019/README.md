# Vectorworks 2019 SDK Examples

This folder contains examples for Vectorworks 2019.

# Build instructions

## Source requirements

The folder contains all required sources to build the examples.

If you use this code as a base of your work and copy it directly, make sure you change all required UUIDs in the duplicate code. All places that this needs to happen are marked with:
```
/*YOU MUST CHANGE THIS UUID if you copy this code*/
```
Failure to do so will result in plugin conflicts between source that have duplicate UUIDs ultimately resulting in one of the two features not working on the client machine.

**Note:** The Debug builds for win and mac are actually based on the release SDK with the difference that symbol generation is turned on and optimizations are turned off. The Debug SDK doesn't actually work with the release Vectorworks and I kept the mac version the same as git doesn't allow the large debug library files to be added to the repository.

## Build tools requirements
- Windows - Visual Studio 2017, toolset version 14.12
- Mac - Xcode 8.2

# Running & Debugging instructions

You need a copy of Vectorworks 2019 in order to run this example.

## Complile: you need to compile at least one example. This will create an output folder at:
```
<root folder>/SDKExamples/2019/_Output
```
Where `<root folder>` is the folder you have cloned this repository.

This location contains the debug and release (in separate folders) compiled dll of the plugin (actual file extension .vlb on win, and .vwlibrary on mac) and the resource file (.vwr) which is a file link under debug and a no-compression zip under release builds.

Additionally, there will be a `IntermediateBuildFiles' folder that contains the intermediete compile files on windows.

## Make Vectorworks find your built plugin

Find your Vectorworks instalation's Plug-ins folder and create a shortcut/alias to:
```
<root folder>//SDKExamples/2019/_Output
```

Alternatively, you can add this shortcut to the Vectorworks user's folder:
 * Mac: `/Users/<Username>/Library/Application Support/Vectorworks/2019/`
 * Windows: `C:\Users\<Username>\AppData\Roaming\Nemetschek\Vectorworks\2019\`
  
Note: this has the advantage that the plugin will be visible always to the specified Vectorworks version, regardless which Vectorworks copy you are running)
  
## The plugin works

If you run Vectorworks, your plugin should be found and the extensions it provices (menus, tools, objects, or functions) should be available.

## Debugging

You can setup VisualStuio and Xcode to execute Vectorworks and since it will load your compiled plugin from the place where it was compiled, VisualStudio and Xcode will be able to debug it. (release builds will act strangely when you debug as the code has been optimized and doesn't have direct relation to the source)

### VisualStudio

Right-click on the project, select 'Properties'. Then in the 'Debugging' tab, put the full path to Vectorworks.exe in the 'Command' field. You can use the popup to select 'Browse..'

This will instruct the VisualStudio to execute Vectorworks.exe for the debug settion. Then Vectorworks will load the dll (.vlb) of the plugin which it generated, and this will allow the debugger to respect breakpoints and debug the code.

## Xcode

From the Xcode menu, select Product -> Scheme -> Edit Scheme... menu command. Then on the 'Run' pane, open up the 'Executable' popup  and choose 'Other...' which will allow selection of an application that will be used for debugging.
