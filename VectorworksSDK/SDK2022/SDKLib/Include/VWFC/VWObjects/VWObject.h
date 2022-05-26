//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_OBJECT__H
#define VECTORWORKS_OBJECT__H

#pragma once

namespace VWFC
{
	using namespace Tools;
	using namespace Math;
	
	namespace VWObjects
	{
		// --------------------------------------------------------------------------------------------------
		typedef std::vector<MCObjectHandle>					TMCObjectHandlesSTLArray;
		typedef std::vector<MCObjectHandle>::iterator		TMCObjectHandlesSTLIterator;
		typedef std::vector<InternalIndex>					TInternalIndexArray;

		// ---------------------------------------------------------------------------------------------
		class VWObject
		{
		public:
								VWObject();
								VWObject(MCObjectHandle hObj);
								VWObject(const VWObject&);
			VWObject&			operator=(const VWObject&);

			virtual				~VWObject();

			operator MCObjectHandle() const;

			// object manipulation
			void				DeleteObject(bool bUseUndo=true);
			void				ResetObject();

			// object class
			VWClass				GetObjectClass() const;
			void				SetObjectClass(const VWClass& clas);
			VWObjectAttr&		GetObjectAttribs();
			const VWObjectAttr&	GetObjectAttribs() const;

			// hierarchy
			void				InsertAfterObject(MCObjectHandle afterObj);
			void				InsertBeforeObject(MCObjectHandle beforeObj);

			// traversing
			MCObjectHandle		GetThisObject() const;
			MCObjectHandle		GetNextObject() const;
			MCObjectHandle		GetPrevObject() const;
			MCObjectHandle		GetParentObject() const;
			MCObjectHandle		GetParentLayer() const;
			MCObjectHandle		FindNextObject(short type) const;
			void				GetContainerInfo(MCObjectHandle* pOutContainerHandle, short* pOutContainerType, double* pOutContainerScale) const;

			// state&data
			short				GetType() const;
			bool				IsVisible() const;
			void				SetVisible(bool bVisible=true);
			bool				IsLocked() const;
			void				SetLock(bool bLock=true);
			bool				IsSelected() const;
			void				SetSelected(bool bSelect=true);
			virtual TXString	GetObjectName() const;
			virtual void		SetObjectName(const TXString& name);
			InternalIndex		GetInternalIndex() const;

			virtual void		GetObjectBounds(VWRectangle2D& bounds) const;
			virtual VWRectangle2D	GetObjectBounds() const;

			// object position & transformation
			virtual void		MoveObject(const VWPoint2D& offset);
			virtual void		MoveObject(double dx, double dy);
			virtual void		MoveObject3D(const VWPoint3D& offset);
			virtual void		MoveObject3D(double dx, double dy, double dz);
			virtual void		RotateObject(const VWPoint2D& pt, double dAngle);
			virtual void		ScaleObject(const VWPoint2D& cenPt, const VWPoint2D& scale);
			virtual void		ScaleObject(const VWPoint2D& cenPt, double scaleX, double scaleY);
			virtual bool		ScaleObject3D(const VWPoint3D& cenPt, const VWPoint3D& scale);
			virtual bool		ScaleObject3D(const VWPoint3D& cenPt, double scaleX, double scaleY, double scaleZ);
			virtual void		GetObjectMatrix(VWTransformMatrix& outMatrix) const;	// relative to the parent container
			virtual void		SetObjectMatrix(const VWTransformMatrix& matrix);		// relative to the parent container
			virtual VWTransformMatrix	GetObjectModelMatrix() const;					// relative to the model
			virtual void		SetObjectModelMatrix(const VWTransformMatrix& matrix);	// relative to the model
			virtual void		ApplyObjectMatrix(const VWTransformMatrix& matrix);
			virtual void		TransformObject(const VWTransformMatrix& matrix, bool applyTo3D=true, bool applyTo2D=false);	// type based trasforamtion, does not send events 
			virtual void		TransformObjectN(const VWTransformMatrix& matrix);	// emulates transforamtion via the user interface, similar to MoveObject - send states and events to parametric objects, resets them if Reset on Rotate is checked.
			virtual double		GetRotationAroundAxis(MajorAxisSpec aroundAxis);

			// Plane support
			virtual bool		IsPlanar() const;
			virtual bool		GetPlanarRef(TPlanarRefID& outPlanarRef) const;
			virtual void		SetPlanarRef(const TPlanarRefID& planarRef);
			virtual void		SetPlanarRefToGround();

			// aux list managment
			void				AttachAuxObject(MCObjectHandle hAuxObject);
			void				DeleteAuxObject(MCObjectHandle hAuxObject);
			MCObjectHandle		FindAuxObject(short type, MCObjectHandle hLastAuxObject=NULL) const;
			MCObjectHandle		GetFirstAuxObject() const;
			VWObjectIterator	GetFirstAuxObjectIterator() const;
			MCObjectHandle		GetParentAUX() const;

			// also see VWRecordObj::GetRecordObject for easier access to records
			MCObjectHandle		FindRecordObject(const TXString& recordName, MCObjectHandle hLastAuxObject=NULL) const;

			// Texturing
			void				SetTexture(InternalIndex textureRef, TexturePartSDK partID);
			void				SetTexture(MCObjectHandle hTexture, TexturePartSDK partID);
			void				SetDefaultTextureMapping(TexturePartSDK partID);
			void				GetTextureMappingInfo(TexturePartSDK partID, TextureMappingInfoSDK& outMappingInfo);
			void				GetTextureMappingInfo(TexturePartSDK partID, Sint32 decalLayerNum, TextureMappingInfoSDK& outMappingInfo);
			void				SetTextureMappingInfo(TexturePartSDK partID, const TextureMappingInfoSDK& mappingInfo);
			void				SetTextureMappingInfo(TexturePartSDK partID, Sint32 decalLayerNum, const TextureMappingInfoSDK& mappingInfo);
			Sint32				GetTextureMappingDecalLayerCount(TexturePartSDK partID);	// number of decal layers on a texture part

		// Tools
		public:
			static void				ResetObjectsVisibility();
			static bool				IsSelected(MCObjectHandle hObj);
			static void				DeselectAll();//XXX Vlado : this should be in the VWDocument
			static void				DeleteObject(MCObjectHandle hObj, bool bUseUndo=true);
			static void				ResetObject(MCObjectHandle hObj);
			static MCObjectHandle	GetNamedObject(const TXString& objName);
			static void				MakeUniqueObjectName(TXString& objName);

			static InternalIndex	Handle2InternalIndex(MCObjectHandle hObject);
			static MCObjectHandle	InternalIndex2Handle(InternalIndex internalIndex);

		protected:
			void		TransformObjectReq(MCObjectHandle hObject, const VWTransformMatrix& transf, bool applyTo3D, bool applyTo2D);

		protected:
			MCObjectHandle		fhObject;
			VWObjectAttr		fObjAttribs;
		};
	}
}

#endif // VECTORWORKS_OBJECT__H