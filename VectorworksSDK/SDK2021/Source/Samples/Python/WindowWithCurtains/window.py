#import pydevd; pydevd.settrace(suspend=False)
import vs
import frame
import Ledge
from CurtainWindow import Curtain
from Vector import Vector
from UI import CurtWindowDlg

#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class Constants:
	kObjXPropPreference					= 4
	kObjOnInitXProperties				= 5
	kObjXPropHasUIOverride				= 8
	kObjXHasCustomWidgetVisibilities	= 12
	kObjOnWidgetPrep					= 41
	kObjOnObjectUIButtonHit				= 35
	kObjectEventHandled					= -8
	kParametricRecalculate				= 3 
	kParametricPreference				= 4
	
	kSettingsButt						= 23
	kGeneralSeparator					= 24
	kOpeningSeparator					= 25
	kCurtainsSeparator					= 26
	
	kWidgetButton						= 12
	kWidgetSeparator					= 100
	
	kParamWidget_LabelID				= 1
	kParamWidget_Width					= 2
	kParamWidget_Height					= 3
	kParamWidget_ElvInWall				= 4
	kParamWidget_OpenTheWindow			= 5
	kParamWidget_OpeningAngle			= 6
	kParamWidget_Leaf					= 7
	kParamWidget_HasCurts				= 8
	kParamWidget_LedgeType 				= 9
	kParamWidget_LedgeMaterial			= 10
	kParamWidget_DrawTheCurts			= 11
	kParamWidget_CurtsColor				= 12
	kParamWidget_Pieces					= 13
	kParamWidget_Opacity				= 14
	
	kMaxWidthOfPieceInInches			= 4

	kColorIndexWood 					= vs.RGBToColorIndex(130*256, 60*256, 10*256)
	kColorIndexMetal 					= vs.RGBToColorIndex(80*256, 75*256, 75*256)
	kColorIndexPlastic 					= vs.RGBToColorIndex(224*256, 224*256, 224*256)
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
def Reset():
	width = vs.PWidth
	height = vs.PHeight
	elevation = vs.PElvInWall
	angle = vs.POpeningAngle
	leafType = vs.GetRField(gObjHandle, gObjName, 'Leaf')
	isOpened = vs.GetRField(gObjHandle, gObjName, 'OpenTheWindow')
	wallType = vs.GetTypeN(gWallHandle)

	if(wallType == 68 or wallType == 89):
		thickness = vs.WallWidth(gWallHandle)
	else:
		upi = vs.GetPrefReal(152) / 25.4
		thickness = 100*upi

	if isOpened == "False":
		angle = 0;

	frameObj = frame.Frame(width, height, thickness, elevation, leafType, angle)
	frameObj.Draw()

	
#draw curtain#######################

	if vs.PHasCurts:
		objLedge = Ledge.LedgeObj(height/20, height/40, width, height+elevation, vs.PLedgeMaterial, vs.PLedgeType, thickness)
		objLedge.DrawLedge()
		
		hObject = vs.LNewObj()
		if objLedge.getMaterial() == "Wood":
		#if self.__fMaterial == LedgeMaterial.Wood:
			vs.SetFillBack(hObject, Constants.kColorIndexWood)
		elif objLedge.getMaterial() == "Metal":
		#elif self.__fMaterial == LedgeMaterial.Metal:
			vs.SetFillBack(hObject, Constants.kColorIndexMetal)
		else:
			vs.SetFillBack(hObject, Constants.kColorIndexPlastic)
		
		curtainPieces = int( vs.Str2Num( vs.GetRField(gObjHandle, gObjName, "Pieces" ) ) )
		curtainStartZ = elevation + thickness / 2
		curtainStartY = thickness / 2 - objLedge.getLedgeShaftWidth() * 1.5 + objLedge.getLedgeWidth()
		curtainHeight = objLedge.getLedgeHeight() - objLedge.getLedgeShaftHeight()
		curtainWidth = width * Ledge.kLedgeOutWindow
		
		curtainCurvesWidth = 2
		if curtainCurvesWidth > objLedge.getLedgeShaftWidth():
			curtainCurvesWidth = objLedge.getLedgeShaftWidth()
			
		curtainOpacity = int ( vs.Str2Num( vs.GetRField( gObjHandle, gObjName, 'Opacity' ) ) )
		distanceBetweenCurtainPieces = 30
		curtainCurveStep = 30
		curtainColor = vs.Str2Num( vs.GetRField( gObjHandle, gObjName, '__CustomColor' ) )
		# distanceBetweenCurtainPieces, curtainCurveStep and curtainCurveWidth are not neccessary to add in the creation of the object
		curtain = Curtain( Vector( 0, -curtainStartY, curtainStartZ ), curtainWidth, curtainHeight, curtainColor, curtainPieces, 
						curtainOpacity, distanceBetweenCurtainPieces, curtainCurveStep, curtainCurvesWidth )
		if vs.PDrawTheCurts:
			curtain.DrawCurtain()
		
####################################

def CheckValues():
	#We check the values each time the user enters new data in the OIP
	 global winWidth
	 fraction, display, format, upi, name, squareName = vs.GetUnits()
	 
	 col = vs.GetRField(gObjHandle, gObjName, 'CurtsColor')
	 if col == 'White':
	 	vs.SetRField(gObjHandle, gObjName, '__CustomColor', 256)
	 elif col == 'Black':
	 	vs.SetRField(gObjHandle, gObjName, '__CustomColor', 257)
	 elif col == 'Custom Color' and vs.P__PrevCustomColor != 0:
	 	vs.SetRField(gObjHandle, gObjName, '__CustomColor', vs.P__PrevCustomColor)	
		
	####################################
	 val = vs.GetRField(gObjHandle, gObjName, 'IDLabel')
	 val = vs.Str2Num(val)
	 if val < 0:
	 	val = 0
	 	vs.SetRField(gObjHandle, gObjName, 'IDLabel', vs.Num2Str(0,val))
	 
	 ################################################
	 val = vs.GetRField(gObjHandle,gObjName,'Width')
	 
	 if(format == 2 or format == 3):
	 	inches = 0
	 	
	 	index = val.find("'")
	 	if index > -1:
	 		splitVal = val.split("'")
	 		inches += vs.Str2Num(splitVal[0])*12.0
	 		
	 		str = splitVal[1]
	 		index = str.find(name)
	 		if index > -1:
	 			str = str.replace(name, "")
	 			val = vs.Str2Num(str)
	 			inches += val
	 	
	 	else:
	 		index = val.find(name)
	 		if index > -1:
	 			val = val.replace(name,"")
	 			val = vs.Str2Num(val)
	 			inches += val
	 	
	 	if inches < 0:
	 		inches = 1
	 		
	 	val = vs.Num2Str(2, inches)
	 	val = val + name
	 else:
	 	val = CheckField(val,name)
	 	
	 vs.SetRField(gObjHandle, gObjName, 'Width', val)
	 
	 val = val.replace(name,"")
	 val = vs.Str2Num(val)
	 winWidth = val
	 
	 ################################################
	 val = vs.GetRField(gObjHandle,gObjName,'Height')
	 if(format == 2 or format == 3):
	 	inches = 0
	 	
	 	index = val.find("'")
	 	if index > -1:
	 		splitVal = val.split("'")
	 		inches += vs.Str2Num(splitVal[0])*12.0
	 		
	 		str = splitVal[1]
	 		index = str.find(name)
	 		if index > -1:
	 			str = str.replace(name, "")
	 			val = vs.Str2Num(str)
	 			inches += val
	 	
	 	else:
	 		index = val.find(name)
	 		if index > -1:
	 			val = val.replace(name,"")
	 			val = vs.Str2Num(val)
	 			inches += val
	 	
	 	if inches < 0:
	 		inches = 1
	 		
	 	val = vs.Num2Str(2, inches)
	 	val = val + name
	 else:
	 	val = CheckField(val,name)
	 	
	 vs.SetRField(gObjHandle, gObjName, 'Height', val)
	 
	 ################################################
	 val = vs.GetRField(gObjHandle,gObjName,'ElvInWall')
	 if(format == 2 or format == 3):
	 	inches = 0
	 	
	 	index = val.find("'")
	 	if index > -1:
	 		splitVal = val.split("'")
	 		inches += vs.Str2Num(splitVal[0])*12.0
	 		
	 		str = splitVal[1]
	 		index = str.find(name)
	 		if index > -1:
	 			str = str.replace(name, "")
	 			val = vs.Str2Num(str)
	 			inches += val
	 	
	 	else:
	 		index = val.find(name)
	 		if index > -1:
	 			val = val.replace(name,"")
	 			val = vs.Str2Num(val)
	 			inches += val
	 	
	 	if inches < 0:
	 		inches = 1
	 		
	 	val = vs.Num2Str(2, inches)
	 	val = val + name
	 else:
	 	val = CheckField(val,name)
	 	
	 vs.SetRField(gObjHandle, gObjName, 'ElvInWall', val)
	 
	 ##########################################################
	 val = vs.GetRField(gObjHandle, gObjName, 'OpeningAngle')
	 val = vs.Str2Num(val)
	 if val < 0:
	 	val = 0
	 elif val > 90:
	 	val = 90
	 
	 vs.SetRField(gObjHandle, gObjName, 'OpeningAngle', vs.Num2Str(2,val))
	 
	 ################################################
	 #In inches: maxPieces = winWidth(in inches) // (floor division) Max width of a pice
	 inchesPerUnit = 1/upi
	 winWidth = inchesPerUnit*winWidth
	 maxPieces = winWidth // Constants.kMaxWidthOfPieceInInches
	 
	 val = vs.GetRField(gObjHandle, gObjName, 'Pieces')
	 val = vs.Str2Num(val)
	 
	 if val > maxPieces:
	 	val = maxPieces
	 	vs.SetRField(gObjHandle, gObjName, 'Pieces', vs.Num2Str(0,val))
	 
	 ##############################################################
	 val = vs.GetRField(gObjHandle, gObjName, 'Opacity')
	 val = vs.Str2Num(val)
	 if val > 100:
	 	val = 100
	 elif val < 0:
	 	val = 0
	 	
	 vs.SetRField(gObjHandle, gObjName, 'Opacity', vs.Num2Str(0,val))

	 width = vs.PWidth
	 height = vs.PHeight
	 
	 upi = vs.GetPrefReal(152) / 25.4

	 wallType = vs.GetTypeN(gWallHandle)
	 if(wallType == 68 or wallType == 89):
		 thickness = vs.WallWidth(gWallHandle)
	 else:
		 thickness = 100 * upi
	
	 leafType = vs.GetRField(gObjHandle, gObjName, 'Leaf')
	 if(leafType == 'None'):
		 twoWings = False
	 elif(leafType == '1(no glass)'):
		 twoWings = False
	 elif(leafType == '1(glass)'):
		 twoWings = False
	 elif(leafType == '2(no glass)'):
		 twoWings = True
	 elif(leafType == '2(glass)'):
		 twoWings = True
	 
	 if (width/3 <= thickness and twoWings == True):
		 width = 3*thickness + 10*upi
		 vs.SetRField(gObjHandle, gObjName, 'Width', width)
	 if (thickness >= height/2):
		 height = 2*thickness + 10*upi
		 vs.SetRField(gObjHandle, gObjName, 'Height', height)
	 if (thickness >= width/2):
		 width = thickness*2 + 10*upi
		 vs.SetRField(gObjHandle, gObjName, 'Width', width)

def InitProps():
	#Add some widgets to the OIP
	vs.vsoAddWidget(Constants.kSettingsButt,Constants.kWidgetButton,vs.GetPluginString(4000))
			
	vs.vsoAddWidget(Constants.kGeneralSeparator,Constants.kWidgetSeparator,vs.GetPluginString(4011))		
			
	vs.vsoAddParamWidget(Constants.kParamWidget_LabelID, 'IDLabel', '')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_LabelID, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_Width, 'Width', '')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_Width, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_Height, 'Height', '')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_Height, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_ElvInWall, 'ElvInWall', '')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_ElvInWall, 1)
	####################################
	vs.vsoAddWidget(Constants.kOpeningSeparator,Constants.kWidgetSeparator,vs.GetPluginString(4012))
	####################################
	vs.vsoAddParamWidget(Constants.kParamWidget_OpenTheWindow,'OpenTheWindow','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_OpenTheWindow, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_OpeningAngle,'OpeningAngle','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_OpeningAngle, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_Leaf,'Leaf','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_Leaf, 1)
	#################################
	vs.vsoAddWidget(Constants.kCurtainsSeparator,Constants.kWidgetSeparator,vs.GetPluginString(4013))
	#################################
	vs.vsoAddParamWidget(Constants.kParamWidget_HasCurts,'HasCurts','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_HasCurts, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_LedgeType,'LedgeType','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_LedgeType, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_LedgeMaterial,'LedgeMaterial','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_LedgeMaterial, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_DrawTheCurts,'DrawTheCurts','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_DrawTheCurts, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_CurtsColor,'CurtsColor','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_CurtsColor, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_Pieces,'Pieces','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_Pieces, 1)
	
	vs.vsoAddParamWidget(Constants.kParamWidget_Opacity,'Opacity','')
	vs.vsoWidgetSetIndLvl(Constants.kParamWidget_Opacity, 1)
	
def UpdateParams():
	#Set the visibilities
	leafTypeField = vs.GetRField(gObjHandle, gObjName, 'Leaf')
	hasLeaf = not(leafTypeField == 'None')
	
	vs.vsoWidgetSetEnable(Constants.kParamWidget_OpenTheWindow, hasLeaf)
	
	wdwOpenEnable = vs.GetRField(gObjHandle, gObjName, 'OpenTheWindow')
	openTheWindow = (wdwOpenEnable == 'True')
	
	vs.vsoWidgetSetEnable(Constants.kParamWidget_OpeningAngle, openTheWindow and hasLeaf)
	
	wdwHasCurts = vs.GetRField(gObjHandle, gObjName, 'HasCurts')
	hasCurts = (wdwHasCurts == 'True')
	
	vs.vsoWidgetSetEnable(Constants.kParamWidget_LedgeType, hasCurts)
	vs.vsoWidgetSetEnable(Constants.kParamWidget_LedgeMaterial, hasCurts)
	vs.vsoWidgetSetEnable(Constants.kParamWidget_DrawTheCurts, hasCurts)
	
	drwTheCurts = vs.GetRField(gObjHandle, gObjName, 'DrawTheCurts')
	drawTheCurts = (drwTheCurts == 'True')
	
	vs.vsoWidgetSetEnable(Constants.kParamWidget_CurtsColor, hasCurts and drawTheCurts)
	vs.vsoWidgetSetEnable(Constants.kParamWidget_Pieces, hasCurts and drawTheCurts)
	vs.vsoWidgetSetEnable(Constants.kParamWidget_Opacity, hasCurts and drawTheCurts)

def OnButton(button):
	if(button == Constants.kSettingsButt):
		CurtWindowDlg.Dialog(gObjHandle)
		vs.ResetObject(gObjHandle)
		
def CheckField(val, name):
	index = val.find(name)
	if index > -1:
		val = val.replace(name, "")
	 	
	val = vs.Str2Num(val)
	if val <= 0:
		val = 1
	 	
	val = vs.Num2Str(2,val)
	if index > -1:
	 	val = val + name
		
	return val

#-------------------------------------------------------------------------------------
# This is the entry point from the plugin
#-------------------------------------------------------------------------------------
def main():
	# Define globals
	global gObjName, gObjHandle, gRecordHandle, gWallHandle
	ok, gObjName, gObjHandle, gRecordHandle, gWallHandle = vs.GetCustomObjectInfo()
	if gObjHandle == vs.Handle():
		gObjName = 'Window with Curtains'
		gObjHandle = vs.GetObject( gObjName ) # get the format
		
	# Get event
	theEvent, theEventData	= vs.vsoGetEventInfo()
	if theEvent == Constants.kObjOnInitXProperties:
		ok = vs.SetObjPropVS( Constants.kObjXPropPreference, True );
		ok	= vs.SetObjPropVS( Constants.kObjXPropHasUIOverride, True )
		ok	= vs.SetObjPropVS( Constants.kObjXHasCustomWidgetVisibilities, True )
		
		InitProps()
		
	elif theEvent == Constants.kObjOnWidgetPrep:
		UpdateParams()
		# to do: set visibilities
		# ...
		# this is very important! this is how the system knows we've handled this
		vs.vsoSetEventResult( Constants.kObjectEventHandled );

	elif theEvent == Constants.kParametricPreference:
		#Call the preferences window as the object is created or prefs button is clicked
		CurtWindowDlg.Dialog(gObjHandle)
		
	elif theEvent == Constants.kObjOnObjectUIButtonHit:
		OnButton(theEventData)
		
	elif theEvent == Constants.kParametricRecalculate:
		#Check the values, which the user enters in the OIP
		CheckValues()
		Reset()