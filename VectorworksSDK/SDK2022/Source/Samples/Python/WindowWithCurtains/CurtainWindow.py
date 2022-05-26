import vs
from Vector import Vector
#--------------------------------------------------------------

kMinimalPieceWidth = 10
kDistanceBetweenPieces = 5
kColorFamilyIndex = 1
kTransparencyFamilyIndex = 3
kPlainColorIndex = 40
kPlainTransparencyIndex = 10
kCurveStep = 2
kCurveHeight = 1

class Curtain:
    __fWidth = None
    __fHeight = None
    __fPieces = None
    __fOpacity = None
    __fColor = None
    __fPiecesHandles = []
    __fOriginPoint = Vector( 0, 0, 0 )
    __fCurveStep = None
    __fCurveHeight = None
    __fDistanceBetweenPieces = None
    
# curveStep, curveHeight and distanceBetweenPieces are not neccessary to add in the creation of the object
    def __init__( self, originPoint = Vector( 0, 0, 0 ), width = None, height = None, color = None, pieces = None, opacity = None, distanceBetweenPieces = kDistanceBetweenPieces, curveStep = kCurveStep, curveHeight = kCurveHeight ):
        self.__fWidth = width
        self.__fHeight = height
        self.__fPieces = pieces
        self.__fOpacity = opacity
        self.__fColor = color
        self.__fOriginPoint = originPoint
        self.__fPiecesHandles = []
        self.__fCurveStep = curveStep
        self.__fCurveHeight = curveHeight
        self.__fDistanceBetweenPieces = distanceBetweenPieces
          
    def __SetCurtainStyle( self ):
        isSuccessful, objName, objHand, recHand, wallHand = vs.GetCustomObjectInfo()
        if isSuccessful:
            if vs.IsNewCustomObject( objName ):
                refNum = -1
            else:
                refNum = vs.Name2Index( vs.GetRField( objHand, objName, "__CurtainTexture" ) )
            
            textureObj = Texture( vs.GetPluginString( 4020 ), refNum, self.__fColor, self.__fOpacity )
            textureIndex, textureName = textureObj.GetTexture()
                
            for pieceH in self.__fPiecesHandles:
                if pieceH:
                    vs.SetTextureRef( pieceH, textureIndex, 0 )
                    
            vs.SetRField( objHand, objName, "__CurtainTexture", textureName )
        
    def __DrawCurtainPoly( self, startPoint, endPoint, step ):
        vs.BeginPoly()
        vertexCnt = 1
        while startPoint <= endPoint:
            if vertexCnt % 2 == 0:
                vs.Add2DVertex( self.__fOriginPoint.x + startPoint, self.__fOriginPoint.y + self.__fCurveHeight, 3, 0 )
            else:
                vs.Add2DVertex( self.__fOriginPoint.x + startPoint, self.__fOriginPoint.y + 0, 3, 0 )
            vertexCnt += 1
            startPoint += step
        vs.EndPoly()
        vs.SetPolyClosed( vs.LNewObj(), False )
        
    def __DrawCurtainPiece( self, startPoint, endPoint, step ):
        vs.BeginXtrd( self.__fOriginPoint.z, self.__fHeight )
        self.__DrawCurtainPoly( startPoint, endPoint, step )
        vs.EndXtrd()
        
        return vs.LNewObj()
        
    def __DrawCurtain( self, step ):
        pieceWidth = ( self.__fWidth - ( ( self.__fPieces - 1 ) * self.__fDistanceBetweenPieces ) )/ self.__fPieces
        
        pieceStart = -self.__fWidth / 2
        for pieceNumber in range ( 0, self.__fPieces ):
            pieceHandle = self.__DrawCurtainPiece( pieceStart, pieceStart + pieceWidth, step )
            self.__fPiecesHandles.append( pieceHandle )
            pieceStart += pieceWidth + self.__fDistanceBetweenPieces
    
    def DrawCurtain( self ):
        self.__DrawCurtain( self.__fCurveStep )
        self.__SetCurtainStyle()
        
        return self.__fPiecesHandles
        
#This class is only for internal use  
class Texture:
    __fColor = None
    __fTransparency = None
    __fDefaultName = None
    __fRefNum = None
    __fTextureHand = vs.Handle()
    
    def __init__( self, defaultName = None, refNum = None, color = None, transparency = None ):
        self.__fColor = color
        self.__fTransparency = transparency / 100
        self.__fDefaultName = defaultName
        self.__fRefNum = refNum
        
    def __CreateTexture( self ):
        counter = 1
        textureName = self.__fDefaultName
        while vs.GetObject( textureName ) != vs.Handle():
            textureName = self.__fDefaultName + '-' + vs.Num2Str( 0, counter )
            counter += 1
        
        curtainTexture = vs.CreateTexture()
        vs.CreateShaderRecord( curtainTexture, kColorFamilyIndex, kPlainColorIndex )
        recHand = vs.CreateShaderRecord( curtainTexture, kTransparencyFamilyIndex, kPlainTransparencyIndex )
        vs.SetName( curtainTexture, textureName )
        self.__fTextureHand = curtainTexture
        self.__SetColor()
        self.__SetOpacity( recHand )
        self.__fRefNum = vs.Name2Index( textureName )
        
        return textureName
    
    def __SetColor( self ):
        red, green, blue = vs.ColorIndexToRGB( self.__fColor )          
        vs.SetRField( self.__fTextureHand, 'NNAMaxon Plain Color', 'Color', vs.Num2Str( 0, red ) )
        vs.SetRField( self.__fTextureHand, 'NNAMaxon Plain Color', 'Color G', vs.Num2Str( 0, green ) )
        vs.SetRField( self.__fTextureHand, 'NNAMaxon Plain Color', 'Color B', vs.Num2Str( 0, blue ) )
        
    def __SetOpacity( self, recHand ):
        vs.SetRField( self.__fTextureHand, 'NNAMaxon Plain Transparency', vs.GetFldName( recHand, 4 ), vs.Num2Str( 4, self.__fTransparency ) )
   
    def GetTexture( self ):
        if self.__fRefNum <= 0:
            textureName = self.__CreateTexture()
        else:
            textureName = vs.Index2Name( self.__fRefNum )
            self.__fTextureHand = vs.GetObject( textureName )
            self.__SetColor()
            self.__SetOpacity( vs.GetRecord( self.__fTextureHand, 1 ) )

        return self.__fRefNum, textureName  
            