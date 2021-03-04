#import pydevd; pydevd.settrace(suspend=False)
import vs
import leaf

#--------------------------------------------------------------

class Frame:
    width = 0.0
    height = 0.0
    thickness = 0.0
    wingsNum = 0
    isGlass = False
    
    def __init__(self, width = 40.0, height = 120.0, thickness = 100.0, elevation = 0.0, leafType = 'None', openingAngle = 0):
        self.width = width
        self.height = height
        self.thickness = thickness
        self.elevation = elevation
        self.openingAngle = openingAngle
        self.leafType = leafType
        
        if(leafType == 'None'):
            self.wingsNum = 0
            self.isGlass = True
        elif(leafType == '1(no glass)'):
            self.wingsNum = 1
            self.isGlass = False
        elif(leafType == '1(glass)'):
            self.wingsNum = 1
            self.isGlass = True
        elif(leafType == '2(no glass)'):
            self.wingsNum = 2
            self.isGlass = False
        elif(leafType == '2(glass)'):
            self.wingsNum = 2
            self.isGlass = True

    def Draw(self):
        vs.BeginXtrd(0,self.thickness)
        vs.Rect(-self.width/2.0, self.height/2.0, self.width/2.0, self.height/2.0-self.thickness)
        r1 = vs.LNewObj()
        vs.Rect(-self.width/2.0, self.height/2.0-self.thickness, -self.width/2.0+self.thickness, -self.height/2.0+self.thickness)
        r2 = vs.LNewObj()
        r2 = vs.AddSurface(r1, r2)
        vs.Rect(self.width/2.0-self.thickness, self.height/2.0-self.thickness, self.width/2.0, -self.height/2.0+self.thickness)
        r3 = vs.LNewObj()
        r3 = vs.AddSurface(r2,r3)
        vs.Rect(-self.width/2.0, -self.height/2.0+self.thickness, self.width/2.0, -self.height/2.0)
        r4 = vs.LNewObj()
        r4 = vs.AddSurface(r3,r4)
        if (self.wingsNum == 2):
            vs.Rect(-self.thickness/2.0, self.height/2.0-self.thickness, self.thickness/2.0, -self.height/2.0+self.thickness)
            r5 = vs.LNewObj()
            r4 = vs.AddSurface(r4,r5)
        vs.EndXtrd()
        vs.SetRot3D(vs.LNewObj(), 90, 0, 0, 0, -self.height/2.0, 0)
        vs.Move3DObj(vs.LNewObj(), 0, self.height/2.0+self.thickness/2.0, 0)
        vs.Move3DObj(vs.LNewObj(), 0, 0, self.elevation)

        #instert leafs

        upi = vs.GetPrefReal(152) / 25.4

        leafPosOffsetY = self.thickness - leaf.Leaf.kFrameThicknessNotUPI*upi
        posFirstLeaf = (-self.width/2.0+self.thickness,
                        -self.thickness/2.0+leafPosOffsetY,
                         self.elevation+self.thickness  )

        if self.wingsNum == 0:

            wingsWidth  = self.width  - 2.0*self.thickness
            wingsHeight = self.height - 2.0*self.thickness

            firstLeaf = leaf.Leaf(wingsWidth, wingsHeight, posFirstLeaf)
            firstLeaf.SetType(leaf.kTypeNone, self.isGlass)
            firstLeaf.Draw()

        elif self.wingsNum == 1:

            wingsWidth  = self.width  - 2.0*self.thickness
            wingsHeight = self.height - 2.0*self.thickness

            firstLeaf = leaf.Leaf(wingsWidth, wingsHeight, posFirstLeaf)
            firstLeaf.SetType(leaf.kTypeLeft, self.isGlass)
            firstLeaf.Draw()
            firstLeaf.SetOpening(self.openingAngle)

        elif self.wingsNum == 2:

            wingsWidth  = (self.width  - 3.0*self.thickness)/2.0
            wingsHeight =  self.height - 2.0*self.thickness

            firstLeaf  = leaf.Leaf(wingsWidth, wingsHeight, posFirstLeaf)
            firstLeaf.SetType(leaf.kTypeLeft, self.isGlass)
            firstLeaf.Draw()
            firstLeaf.SetOpening(self.openingAngle)
            
            posSecondLeaf = (self.thickness/2.0, -self.thickness/2.0+leafPosOffsetY, self.elevation+self.thickness)
            
            secondLeaf = leaf.Leaf(wingsWidth, wingsHeight, posSecondLeaf)
            secondLeaf.SetType(leaf.kTypeRight, self.isGlass)
            secondLeaf.Draw()
            secondLeaf.SetOpening(self.openingAngle)
