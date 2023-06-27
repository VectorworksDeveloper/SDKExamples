//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#ifndef VECTORWORKS_FOUNDATION_CLASSES_LIBRARY__H
#define VECTORWORKS_FOUNDATION_CLASSES_LIBRARY__H


#pragma once

#if BUG
# define	VWFC_ASSERT(x)		ASSERTN( kVStanev, x )
# define	VWFC_VERIFY(x)		VERIFYN( kVStanev, x )
#else
# define	VWFC_ASSERT(x)		
# define	VWFC_VERIFY(x)		(x)
#endif


// exception managment
#ifdef _DEBUG
# ifdef _WINDOWS
#  define		THROW_VWFC_EXCEPTION(ex,err,desc)		/*throw ex(err, desc, __FILE__, __LINE__)*/
# else
#  define		THROW_VWFC_EXCEPTION(ex,err,desc)		/*throw ex(err, desc, "unknown", 0)*/
# endif
# define		VWFC_EXCEPTION_DEFINITION(exName)		exName(Sint32 err, const char* desc, const char* szFile, size_t line);
# define		VWFC_EXCEPTION_IMPLEMENTATION(exName)	exName::exName(Sint32 err, const char* desc, const char* szFile, size_t line) : VWException( err, desc, szFile, line )
#else
# define		THROW_VWFC_EXCEPTION(ex,err,desc)		/*throw ex(err, desc)*/
# define		VWFC_EXCEPTION_DEFINITION(exName)		exName(Sint32 err, const char* desc);
# define		VWFC_EXCEPTION_IMPLEMENTATION(exName)	exName::exName(Sint32 err, const char* desc) : VWException( err, desc )
#endif


namespace VWFC
{
	// --------------------------------------------------------------------------------
	// Expection base class
	class VWException
	{
	public:
#ifdef _DEBUG
				VWException(Sint32 err, const char* desc, const char* szFile, size_t line)	{ fszDescription = desc; fnErrorNum = err; fszFile = szFile; fLine = line; DMSG(( kEveryone, "%s (%d) : VWException : %d -> %s!\n", fszFile, fLine, fnErrorNum, fszDescription )); } 
#else
				VWException(Sint32 err, const char* desc)									{ fszDescription = desc; fnErrorNum = err; }
#endif
		virtual	~VWException()							{}

		Sint32				fnErrorNum;
		const char*		fszDescription;
#ifdef _DEBUG
		const char*		fszFile;
		size_t			fLine;
#endif
	};

	// --------------------------------------------------------------------------------
	enum EMarkerType {
		kMarkerFilledArrow			= 0,
		kMarkerEmptyArrow			= 1,
		kMarkerOpenArrow			= 2,
		kMarkerFilledBall			= 3,
		kMarkerEmptyBall			= 4,
		kMarkerSlash				= 5,
		kMarkerCross				= 6
	};

	enum EArrowType {
		kArrowNormal				= arArrow,
		kArrowTight					= arTightArrow,
		kArrowBall					= arBall,
		kArrowSlash					= arSlash,
		kArrowCross					= arCross
	};

	const size_t	kInvalidIndex	= size_t(-1);

}

// --------------------------------------------------------------------------------
// This file should be included in your precompiled header
// so you will gain access to everything in the VectorWorks Fondation Classes Library

/*#if _MINICAD_
// additional defined for the core
// see MiniCadCallBacks.h, they are not defined for the core, but only for the sdk
#include "XGraf3D.h"
#include "MObject.h"

const short cavalierOblique45		= kCavalierOblique45;
const short cavalierOblique30		= kCavalierOblique30;
const short cabinetOblique45		= kCabinetOblique45;
const short cabinetOblique30		= kCabinetOblique30;
const short plan					= kPlan;
const short perspective             = kPerspective;
const short renderWireFrame 		= kRenderWireFrame;
const short renderQuick 			= kRenderQuick;
const short renderSolid 			= kRenderSolid;
const short renderShadedSolid		= kRenderShadedSolid;
const short renderShadedNoLines 	= kRenderShadedNoLines;
const short renderFinalShaded 		= kRenderFinalShaded;
const short renderFinalHiddenLine	= kRenderFinalHiddenLine;
const short renderDashedHiddenLine	= kRenderDashedHiddenLine;
#endif*/

// Memroy manager
// The memory manager always goes in the library
#include "Memory/VWMManager.h"

// -------------------------------------------------------------------------------
// Include STL library
#include <vector>
#include <map>

typedef	std::vector<size_t>		TSizeTArray;


// -------------------------------------------------------------------------------
template <class T> class CEnumData
{
public:
	CEnumData(const char* values)
	{
		std::string str;
		size_t i = 0;
		for(const char* p = values; *p; p++)
		{
			if ( *p != ' ' )
			{
				if ( *p == ',' )
				{
					farrValues.push_back( str );
					fmapValues[str] = (T) i;
					str.clear();
					i++;
				}
				else
				{
					str += *p;
				}
			}
		}

		if ( str.size() > 0 )
		{
			farrValues.push_back( str );
			fmapValues[str] = (T) i;
		}
	}

	T Str2Enum(const char* str, T defValue) const
	{
		auto it = fmapValues.find( str );
		return it != fmapValues.end() ? it->second : defValue;
	}

	T Str2Enum(const std::string str, T defValue) const
	{
		auto it = fmapValues.find( str );
		return it != fmapValues.end() ? it->second : defValue;
	}

	const char* Enum2Str(T value) const
	{
		return farrValues[ size_t(value) ].c_str();
	}

// std iterator support
public:
	class const_iterator
	{
	public:
		typedef std::pair<T, const char*> value_type;
		typedef const std::pair<T, const char*> reference;

        const_iterator(const const_iterator& src) : fIterator(src.fIterator), fmapValues(src.fmapValues)	{ }
		~const_iterator()																					{ }

		const_iterator& operator=(const const_iterator& src)	{ fIterator = src.fIterator; return *this; }
        bool operator==(const const_iterator& b) const			{ return fIterator == b.fIterator; }
        bool operator!=(const const_iterator& b) const			{ return fIterator != b.fIterator; }
        bool operator< (const const_iterator& b) const			{ return fIterator < b.fIterator; }
        bool operator> (const const_iterator& b) const			{ return fIterator > b.fIterator; }
        bool operator<=(const const_iterator& b) const			{ return fIterator <= b.fIterator; }
        bool operator>=(const const_iterator& b) const			{ return fIterator >= b.fIterator; }

        const_iterator& operator++()							{ fIterator.operator++();	return *this; }
        const_iterator  operator++(int n)						{ fIterator.operator++(n);	return *this; }
        const_iterator& operator--()							{ fIterator.operator--();	return *this; }
        const_iterator  operator--(int n)						{ fIterator.operator--(n);	return *this; }
        const_iterator& operator+=(size_t n)					{ fIterator.operator+=(n);	return *this; }
        const_iterator  operator+(size_t n) const				{ fIterator.operator+(n) ;	return *this; }
        const_iterator& operator-=(size_t n)					{ fIterator.operator-=(n);	return *this; }
        const_iterator  operator-(size_t n) const				{ fIterator.operator-(n) ;	return *this; }

		reference operator*() const			{ return std::make_pair( this->value(), this->name() ); }

		const T&		value() const		{ return fmapValues.find(fIterator.operator*())->second; }
		const char*		name() const		{ return fIterator.operator*().c_str(); }

	protected:
		friend class CEnumData<T>;
		const_iterator(std::vector<std::string>::const_iterator it, const std::map<std::string,T>& map) : fIterator(it), fmapValues(map) { }

	private:
		std::vector<std::string>::const_iterator	fIterator;

		const std::map<std::string,T>&	fmapValues;
    };

    const_iterator begin() const { return const_iterator( farrValues.begin(), fmapValues ); }
    const_iterator end() const { return const_iterator(  farrValues.end(), fmapValues ); }

private:
	// no unicode support as these strings are fixed in the code universal names
	std::vector<std::string>	farrValues;
	std::map<std::string,T>		fmapValues;
};

// -------------------------------------------------------------------------------
// Support for enum define with the additional #Data class for mathing strings to the elements of the enumeration
// Example: enum_def( TMyEnum
//				, Option1
//				, Option1
//			);
#define enum_def(TEnum, ...) \
	enum class TEnum { __VA_ARGS__ };\
	typedef const CEnumData<TEnum>	TEnum##Type;\
	const CEnumData<TEnum>	TEnum##Data = #__VA_ARGS__;

// -------------------------------------------------------------------------------
// VCOM standard interfaces
#include "../Interfaces/VWInterfaces.h"

// Tools
#include "Tools/RGBColor.h"
#include "Tools/VWString.h"
#include "Tools/VWStringConv.h"
#include "Tools/ByteSwapper.h"
#include "Tools/StateRestore.h"
#include "Tools/UUID.h"
#include "Tools/VWTiming.h"
#include "Tools/DataSerializer.h"
#include "Tools/STRResLoader.h"
#include "Tools/AutoClassing.h"

// Math namespace
#include "Math/VWPoint2D.h"
#include "Math/VWPoint3D.h"
#include "Math/VWArc.h"
#include "Math/VWTransformMatrix.h"
#include "Math/VWLine2D.h"
#include "Math/VWCircle2D.h"
#include "Math/VWRectangle2D.h"
#include "Math/VWPolygon.h"
#include "Math/VWLine3D.h"
#include "Math/VWPolygon3D.h"
#include "Math/VWMathUtils.h"
#include "Math/VWCube.h"
#include "Math/VWPolygonOperation.h"
#include "Math/VWPolygon3DOperation.h"
#include "Math/VWCubicInterpolation.h"
#include "Math/VWPlane.h"
#include "Math/VWNURBSCurve.h"
#include "Math/VWNURBSSurface.h"
#include "Math/VWBody.h"
#include "Math/VWBodyFace.h"
#include "Math/VWBodyEdge.h"


// VWObjects namespace
#include "VWObjects/VWExceptions.h"
#include "VWObjects/VWObjectIterator.h"
#include "VWObjects/VWPattern.h"
#include "VWObjects/VWClassAttributes.h"
#include "VWObjects/VWObjectAttributes.h"
#include "VWObjects/VWClass.h"
#include "VWObjects/VWObject.h"
#include "VWObjects/VWDocument.h"
#include "VWObjects/VWGroupObj.h"
#include "VWObjects/VWLayerObj.h"
#include "VWObjects/VWLine2DObj.h"
#include "VWObjects/VWLocus2DObj.h"
#include "VWObjects/VWLocus3DObj.h"
#include "VWObjects/VWArcObj.h"
#include "VWObjects/VWPolygon2DObj.h"
#include "VWObjects/VWPolygon3DObj.h"
#include "VWObjects/VWExtrudeObj.h"
#include "VWObjects/VWSymbolDefObj.h"
#include "VWObjects/VWSymbolObj.h"
#include "VWObjects/VWWallObj.h"
#include "VWObjects/VWRoofFaceObj.h"
#include "VWObjects/VWRoofObj.h"
#include "VWObjects/VWRecordFormatObj.h"
#include "VWObjects/VWRecordObj.h"
#include "VWObjects/VWParametricObj.h"
#include "VWObjects/VWTextBlockObj.h"
#include "VWObjects/VWSolidObj.h"
#include "VWObjects/VWNURBSCurveObj.h"
#include "VWObjects/VWBodyObj.h"
#include "VWObjects/VWLightObj.h"
#include "VWObjects/VWViewportObj.h"
#include "VWObjects/VWWallObj.h"
#include "VWObjects/VWBitmapObj.h"
#include "VWObjects/VWTextureObj.h"
#include "VWObjects/VWMeshObj.h"
#include "VWObjects/VWViewObj.h"
#include "VWObjects/VWMaterialObj.h"

// VWUI
#include "VWUI/Control.h"
#include "VWUI/ControlsContainer.h"
#include "VWUI/GroupBoxCtrl.h"
#include "VWUI/ListBoxCtrl.h"
#include "VWUI/ListBrowserColumn.h"
#include "VWUI/ListBrowserItem.h"
#include "VWUI/ListBrowserCtrl.h"
#include "VWUI/PullDownMenuCtrl.h"
#include "VWUI/PushButtonCtrl.h"
#include "VWUI/RadioButtonCtrl.h"
#include "VWUI/RadioGroupBoxCtrl.h"
#include "VWUI/StaticTextCtrl.h"
#include "VWUI/TabPaneCtrl.h"
#include "VWUI/TabCtrl.h"
#include "VWUI/SwapPaneCtrl.h"
#include "VWUI/SwapCtrl.h"
#include "VWUI/ThumbnailPopupCtrl.h"
#include "VWUI/CheckButtonCtrl.h"
#include "VWUI/CheckGroupBoxCtrl.h"
#include "VWUI/ColorButtonCtrl.h"
#include "VWUI/EditIntegerCtrl.h"
#include "VWUI/EditRealCtrl.h"
#include "VWUI/EditTextCtrl.h"
#include "VWUI/EditPasswordCtrl.h"
#include "VWUI/EditTextColorCtrl.h"
#include "VWUI/StandardIconCtrl.h"
#include "VWUI/PictureCtrl.h"
#include "VWUI/MarkerPopupCtrl.h"
#include "VWUI/SliderCtrl.h"
#include "VWUI/ColorPopupCtrl.h"
#include "VWUI/ColorPopupCustomCtrl.h"
#include "VWUI/PatternPopupCtrl.h"
#include "VWUI/LineAttributePopupCtrl.h"
#include "VWUI/LineStylePopupCtrl.h"
#include "VWUI/LineWeightPopupCtrl.h"
#include "VWUI/Dialog.h"
#include "VWUI/ComplexDialog.h"
#include "VWUI/DialogEventArgs.h"
#include "VWUI/StandardEditTextDlg.h"
#include "VWUI/SavedSettingsManager.h"
#include "VWUI/CustomCtrl.h"
#include "VWUI/CustomCtrlAttrs.h"
#include "VWUI/CustomCtrlDrawing.h"
#include "VWUI/TreeCtrlItem.h"
#include "VWUI/TreeCtrl.h"
#include "VWUI/ChooseClassPopupCtrl.h"
#include "VWUI/ChooseLayerPopupCtrl.h"
#include "VWUI/SearchablePulldownCtrl.h"
#include "VWUI/ListCustomCtrl.h"
#include "VWUI/ImageButtonCtrl.h"
#include "VWUI/StaticTextCtrl.h"
#include "VWUI/SymbolDisplayCtrl.h"
#include "VWUI/SeparatorCtrl.h"
#include "VWUI/StyleButtonCtrl.h"
#include "VWUI/EditStyleDialog.h"
#include "VWUI/SelectCatalogDialog.h"
#include "VWUI/StandardCtrlImagePreview.h"

// more tools
#include "Tools/ParamProviders.h"
#include "Tools/TaggedData.h"
#include "Tools/VWTaggedObj.h"
#include "Tools/InfoBar.h"
#include "Tools/EncryptSupport.h"
#include "Tools/ClassPopupParam.h"
#include "Tools/VWSelectionSupport.h"
#include "Tools/VWResourceList.h"
#include "Tools/ProgressDlg.h"
#include "Tools/DocumentFreezer.h"
#include "Tools/DataSerializerSimple.h"
#include "Tools/FindObjAtPoint.h"
#include "Tools/VWStyleSupport.h"
#include "Tools/GenericLogger.h"
#include "Tools/WSCriteriaExpression.h"

// PluginSupport
#include "VWFC/PluginSupport/VWExtensions.h"

// more tools
#include "Tools/VWResourceListCategorized.h"

#include "Memory/VWMemoryLeakChecker.h"

// Special interfaces that depend on VWFC
#include "../Interfaces/VectorWorks/DataCatalog/ICatalog.h"

#endif // VECTORWORKS_FOUNDATION_CLASSES_LIBRARY__H
