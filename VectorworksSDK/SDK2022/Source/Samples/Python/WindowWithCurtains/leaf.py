import vs




kTypeLeft	= 1
kTypeRight	= 2
kTypeNone	= 3


class Leaf():


	kFrameThicknessNotUPI	= 50


	__frameOverlap 			= 0
	__frameWidth 			= 0
	__frameMainWidth		= __frameWidth - __frameOverlap
	__frameOverlapThickness	= 0
	__frameInsideThinckness 	= kFrameThicknessNotUPI - __frameOverlapThickness

	__glassThikness			= 0
	
	def __init__(self, width, height, position ):
		
		# #Validation
		# if width < 2*self.__frameWidth:
		# 	#return Leaf width is too small.
		# 	# vs.AlrtDialog("Leaf width is too small.")
		
		
		# if height < 2*self.__frameWidth:
		# 	#return Leaf hidth is too small.
		# 	# vs.AlrtDialog("Leaf height is too small.")
		
		upi = vs.GetPrefReal(152) / 25.4
		# self.upi = upi
		# vs.AlrtDialog(str(upi))
		
		#Frame instance parameters
		self.height 		= height
		self.width 			= width
		self.position 		= position
		
		self.hLeaf 			= vs.Handle()
		self.leafType 		= kTypeNone
		self.isGlassTrue 	= True
		self.openingAngle 	= 0
		
		
		self.__frameOverlap 			= 15*upi
		self.__frameThickness 			= self.kFrameThicknessNotUPI*upi
		self.__frameWidth 				= 50*upi
		self.__frameMainWidth			= self.__frameWidth - self.__frameOverlap
		self.__frameOverlapThickness	= 5*upi
		self.__frameInsideThinckness 	= self.__frameThickness - self.__frameOverlapThickness

		self.__glassThikness			= 2*upi



	
	def Draw(self):


		if self.leafType == kTypeNone:

			vs.BeginGroup()

			glassWidth 		= self.width  
			glassHeight 	= self.height
			glassThikness	= self.__glassThikness
			glassOrigin		= (0, 0)
			pathDirection	= (0, -1)

			vs.DSelectAll()
			vs.BeginXtrd( 0, glassThikness)
			vs.RectangleN( glassOrigin, pathDirection, glassWidth, glassHeight )
			hGlass = vs.LNewObj()
			vs.EndXtrd()

			vs.Set3DRot(hGlass, 0, 40, 0, 0, 0, 0)

			vs.EndGroup()
			hLeaf = vs.LNewObj()
			
			#position at origin with needed orientation
			vs.Set3DRot(hLeaf, 0, -90,   0, 0, 0, 0)
			vs.Move3DObj(hLeaf, self.__frameThickness/2, 0, 0)
			vs.Set3DRot(hLeaf, 0,   0, 90, 0, 0, 0)



		if self.leafType != kTypeNone:
				
			vs.BeginGroup()
			#Prepare Extrude Path
			pathWidth = self.width + self.__frameOverlap*2
			pathHeight = self.height + self.__frameOverlap*2
			pathOrigin = ( -self.__frameOverlap, self.__frameOverlap )
			pathDirection = (0, -1)

			vs.RectangleN( pathOrigin, pathDirection, pathWidth, pathHeight)
			hFramePath = vs.LNewObj()

			vs.SetPlanarRefIDToGround(hFramePath);
			hFramePath = vs.ConvertToNURBS(hFramePath, False)

			#Prepare Extrude Profile


			frameProfile = (
							self.__frameOverlap, 0,
							self.__frameWidth, 0, 										
							self.__frameWidth, self.__frameThickness,
							0, self.__frameThickness,
							0, self.__frameInsideThinckness,
							self.__frameOverlap, self.__frameInsideThinckness
							)



			vs.ClosePoly()
			vs.Poly(*frameProfile)
			hFrameProfile = vs.LNewObj()

			hFrameProfilePolyline = vs.MakePolyline(hFrameProfile)
			vs.DelObject(hFrameProfile)
			hFrameProfile = hFrameProfilePolyline

			
			hLeafFrame = vs.ExtrudeAlongPath(hFramePath, hFrameProfile)

			vs.DelObject(hFramePath)
			vs.DelObject(hFrameProfile)

			#insert glass
			glassWidth 		= self.width  - 2*self.__frameMainWidth
			glassHeight 	= self.height - 2*self.__frameMainWidth
			glassThikness	= self.__glassThikness
			glassOrigin		= (self.__frameMainWidth, -self.__frameMainWidth)

			vs.DSelectAll()
			vs.BeginXtrd(self.__frameThickness/2, self.__frameThickness/2 + glassThikness)
			vs.RectangleN( glassOrigin, pathDirection, glassWidth, glassHeight )
			hGlass = vs.LNewObj()
			vs.EndXtrd()

			vs.EndGroup()
			hLeaf = vs.LNewObj()


			#position at origin with needed orientation
			vs.Set3DRot(hLeaf, 0, -90,   0, 0, 0, 0)
			vs.Set3DRot(hLeaf, 0,   0, 180, 0, 0, 0)
			vs.Move3DObj(hLeaf, 0, -self.width, 0)
			vs.Set3DRot(hLeaf, 0,   0, 90, 0, 0, 0)
			



		#move to required position
		vs.Move3DObj(hLeaf, self.position[0], self.position[1], self.position[2], )


		if self.isGlassTrue == True:
			vs.SetFillBack(hGlass, 11)
			vs.SetOpacity(hGlass, 50)

		else:
			vs.SetFillBack(hGlass, 8)
			vs.SetOpacity(hGlass, 100)



		self.hLeaf = hLeaf





	def SetOpening(self, openingAngle):
		
		
		
		if openingAngle > 90 or openingAngle < 0:
			#return invalid opening angle
			return

		if self.hLeaf == vs.Handle:
			#return no leaf instance to rotate
			return


		openingAngle = openingAngle - self.openingAngle

		if self.leafType == kTypeLeft:

			xAxis = self.position[0] - self.__frameOverlap
			yAxis = self.position[1] + self.__frameInsideThinckness
			zAxis = self.position[2]

		if self.leafType == kTypeRight:

			xAxis = self.position[0] + self.__frameOverlap + self.width
			yAxis = self.position[1] + self.__frameInsideThinckness
			zAxis = self.position[2]
			openingAngle = -openingAngle

		if self.leafType == kTypeNone:
					return		

		self.openingAngle = openingAngle

		
		vs.Set3DRot(self.hLeaf, 0, 0, openingAngle, xAxis, yAxis, zAxis)


	def SetType(self, orientation, isGlassTrue):

		self.isGlassTrue = isGlassTrue
		
		if 	orientation == kTypeRight:
			self.leafType = kTypeRight

		elif orientation == kTypeLeft:
			self.leafType = kTypeLeft

		elif orientation == kTypeNone:
			self.leafType = kTypeNone

		else:
			#return invalid orientation
			pass


	# def getFrameThickness(self):
	# 	return self.kFrameThicknessNotUPI*self.upi

