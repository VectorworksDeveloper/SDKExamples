#import pydevd; pydevd.settrace(suspend=False)
import vs
#import Common.Includes.vsoEventsConstants

kLedgeShaftWidth = 1/4
kLedgeShaftHeight = 1/2
kLedgeOffsetFromWindow = 12/10
kLedgeOffsetFromWall = 1.0
kLedgeOutWindow = 12/10
kColorIndexWood = vs.RGBToColorIndex(130*256, 60*256, 10*256)
kColorIndexMetal = vs.RGBToColorIndex(80*256, 75*256, 75*256)
kColorIndexPlastic = vs.RGBToColorIndex(224*256, 224*256, 224*256)

#We use this class like enum in C++
class LedgeType:
    AttachToWall = 1
    AttachToCeiling = 2

#We use this class like enum in C++
class LedgeMaterial:
    Wood = "Wood"
    Metal = "Metal"
    Plastic = "Plastic"

class LedgeObj:
    __fLedgeWidth = 0.0
    __fLedgeHeight = 0.0
    __fWindowWidth = 0.0
    __fWindowHeight = 0.0
    __fMaterial = ""
    __fType = LedgeType.AttachToWall
    __fFrameWidthOffset = 0.0
    
    def __init__(self, initLedgeWidth = 0.0, initLedgeHeight = 0.0,  initWindowWidth = 0.0, initWindowHeight = 0.0, initMaterial = LedgeMaterial.Wood, initType = LedgeType.AttachToWall, offset = 0.0):
        self.__fLedgeWidth = initLedgeWidth
        self.__fLedgeHeight = initLedgeHeight
        self.__fWindowWidth = initWindowWidth
        self.__fWindowHeight = initWindowHeight
        self.__fMaterial = initMaterial
        self.__fType = initType
        self.__fFrameWidthOffset = offset
    
    def setLedgeWidth(self, initLedgeWidth = 0.0):
        self.__fLedgeWidth = initLedgeWidth
    def setLedgeHeight(self, initLedgeHeight = 0.0):
        self.__fLedgeHeight = initLedgeHeight
    def setWindowWidth(self, initWindowWidth = 0.0):
        self.__fWindowWidth = initWindowWidth
    def setWindowHeight(self, initWindowHeight = 0.0):
        self.__fWindowHeight = initWindowHeight
    def setMaterial(self, initMaterial = LedgeMaterial.Wood):
        self.__fMaterial = initMaterial
    def setType(self, initType = LedgeType.AttachToWall):
        self.__fType = initType
    def setFrameWidthOffset(self, offset = 0.0):
        self.__fFrameWidthOffset = offset
    
    def getLedgeWidth(self):
        return self.__fLedgeWidth
    def getLedgeHeight(self):
        return self.__fLedgeHeight + ( self.__fWindowHeight * kLedgeOffsetFromWindow )
    def getWindowWidth(self):
        return self.__fWindowWidth
    def getWindowHeight(self):
        return self.__fWindowHeight
    def getMaterial(self):
        return self.__fMaterial
    def getType(self):
        return self.__fType
    def getFrameWidthOffset(self):
        return self.__fFrameWidthOffset
    def getLedgeShaftWidth(self):
        return self.__fLedgeWidth * kLedgeShaftWidth
    def getLedgeShaftHeight(self):
        return self.__fLedgeHeight * kLedgeShaftHeight
    
    
    def __DrawLedgePoly(self):
        vs.BeginPoly()
        vs.Add2DVertex(-self.__fLedgeWidth/2, 0, 0, 0)
        vs.Add2DVertex(-self.__fLedgeWidth/2, -self.__fLedgeHeight, 0, 0)
        vs.Add2DVertex(-self.__fLedgeWidth/2 * kLedgeShaftWidth, -self.__fLedgeHeight, 0, 0)
        vs.Add2DVertex(-self.__fLedgeWidth/2 * kLedgeShaftWidth, -self.__fLedgeHeight * kLedgeShaftHeight, 0, 0)
        vs.Add2DVertex(self.__fLedgeWidth/2 * kLedgeShaftWidth, -self.__fLedgeHeight * kLedgeShaftHeight, 0, 0)
        vs.Add2DVertex(self.__fLedgeWidth/2 * kLedgeShaftWidth, -self.__fLedgeHeight, 0, 0)
        vs.Add2DVertex(self.__fLedgeWidth/2, -self.__fLedgeHeight, 0, 0)
        vs.Add2DVertex(self.__fLedgeWidth/2, 0, 0, 0)
        vs.EndPoly()
        
        hPoly = vs.LNewObj()
        vs.SetPolyClosed( hPoly, True )
        
        return hPoly

    def __MoveLedge(self, hLedge):        
        if self.__fType == LedgeType.AttachToWall:
            # to Wall
            vs.Move3DObj( hLedge,
                           -(self.__fWindowWidth * kLedgeOutWindow)/2.0,
                           -self.__fLedgeWidth/2.0 - self.__fFrameWidthOffset/2.0,
                           self.__fLedgeHeight + ( self.__fWindowHeight * kLedgeOffsetFromWindow ) )
        else:
            isSuccessful, objName, objHand, recHand, wallHand = vs.GetCustomObjectInfo()            
            if isSuccessful and (vs.GetTypeN (wallHand) == 68 or vs.GetTypeN (wallHand) == 89):                                 # not sure if correct (need wall to test)
            # to Window
                startTopHeight, startBotHeight, endTopHeight, endBotHeight = vs.GetWallHeight( wallHand )
                vs.Move3DObj( hLedge,
                               -(self.__fWindowWidth * kLedgeOutWindow)/2.0,
                               -(kLedgeOffsetFromWall * self.__fLedgeWidth)/ -self.__fLedgeWidth/2.0 - self.__fFrameWidthOffset/2.0,
                               vs.Abs( endTopHeight - endBotHeight ) )
            else:
                self.__fType = LedgeType.AttachToWall
                vs.Move3DObj( hLedge,
                               -(self.__fWindowWidth * kLedgeOutWindow)/2.0,
                               -self.__fLedgeWidth/2.0 - self.__fFrameWidthOffset/2.0,
                               self.__fLedgeHeight + ( self.__fWindowHeight * kLedgeOffsetFromWindow ) )
        return hLedge       
    
    def __SetMaterial(self):
        hObject = vs.LNewObj()
        if self.__fMaterial == LedgeMaterial.Wood:
            #vs.SetTextureRef(hObject, -1, 1)
            vs.SetFillBack(hObject, kColorIndexWood)
        elif self.__fMaterial == LedgeMaterial.Metal:
            #vs.SetTextureRef(hObject, -1, 2)
            vs.SetFillBack(hObject, kColorIndexMetal)
        else:
            #vs.SetTextureRef(hObject, -1, 3)
            vs.SetFillBack(hObject, kColorIndexPlastic)

    def DrawLedge(self):
        vs.BeginXtrd( 0, self.__fWindowWidth * kLedgeOutWindow )
        hLedgePoly = self.__DrawLedgePoly()
        vs.EndXtrd()
        hLedgePoly = vs.LNewObj()           # without that line there is a bug : multiple insertion of the object leads to whole window (oall abojects) offset
        hLedgePoly = self.__MoveLedge( hLedgePoly )
        
        vs.Rotate3D( 0, 0, 90 )
        vs.Rotate3D( 0, 90, 0 )

        hLedgePoly = self.__SetMaterial()
        
#def execute():
    
#    theEvent, theEventData = vs.vsoGetEventInfo()
    
#    if theEvent == vs.kParametricRecalculate:
#        newObject = LedgeObj(10, 5, 80, 50, LedgeMaterial.Wood, LedgeType.AttachToWall)
#        newObject.DrawLedge()
    
