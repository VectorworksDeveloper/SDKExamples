//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IXMLFile.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------
		struct DYNAMIC_ATTRIBUTE SXMLURI
		{
			TXString	fURI;
			TXString	fLocalName;
		};
		// ----------------------------------------------------------------------------------
		enum EXMLSAXAttrType
		{
			eXMLSAXAttrType_UNKNOWN,
			eXMLSAXAttrType_ATTRIBUTE,
			eXMLSAXAttrType_ID,
			eXMLSAXAttrType_IDREF,
			eXMLSAXAttrType_IDREFS,
			eXMLSAXAttrType_NMTOKEN,
			eXMLSAXAttrType_NMTOKENS,
			eXMLSAXAttrType_ENTITY,
			eXMLSAXAttrType_ENTITIES,
			eXMLSAXAttrType_NOTATION
		};

		// ----------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IXMLSAXAttributes
		{
		public:
			virtual									~IXMLSAXAttributes()		{ }
			virtual size_t          VCOM_CALLTYPE 	GetCount() = 0;
			virtual TXString        VCOM_CALLTYPE 	GetNameAt(size_t index) = 0;
			virtual SXMLURI         VCOM_CALLTYPE 	GetURIAt(size_t index) = 0;
			virtual TXString        VCOM_CALLTYPE 	GetValueAt(size_t index) = 0;
			virtual EXMLSAXAttrType VCOM_CALLTYPE 	GetTypeAt(size_t index) = 0;

			virtual size_t          VCOM_CALLTYPE 	GetIndex(const TXString& name) = 0;
			virtual size_t          VCOM_CALLTYPE 	GetIndex(const SXMLURI& uri) = 0;

			virtual EXMLSAXAttrType VCOM_CALLTYPE 	GetType(const TXString& name) = 0;
			virtual EXMLSAXAttrType VCOM_CALLTYPE 	GetType(const SXMLURI& uri) = 0;

			virtual TXString        VCOM_CALLTYPE 	GetValue(const TXString& name) = 0;
			virtual TXString        VCOM_CALLTYPE 	GetValue(const SXMLURI& uri) = 0;
		};

		// ----------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IXMLSAXListener
		{
		public:
			virtual						~IXMLSAXListener() { }
			virtual void VCOM_CALLTYPE 	OnDocument(const bool isStart) = 0;
			virtual void VCOM_CALLTYPE 	OnNode(const bool isStart, const SXMLURI& uri, const TXString& name, IXMLSAXAttributes* attributes) = 0;
			virtual void VCOM_CALLTYPE 	OnNodeValue(const TXString&  value) = 0;
			virtual void VCOM_CALLTYPE 	OnNodeCDATA(const TXString&  value) {}
		};

		// ----------------------------------------------------------------------------------
		// {2152700C-9800-47cd-A81D-0FDE431BA649}
		static const VWIID IID_XMLSAXFile = { 0x2152700c, 0x9800, 0x47cd, { 0xa8, 0x1d, 0xf, 0xde, 0x43, 0x1b, 0xa6, 0x49 } };

		class DYNAMIC_ATTRIBUTE IXMLSAXFile : public IVWUnknown
		{
		public:
			// Read Support
			virtual VCOMError VCOM_CALLTYPE	 ParseFile(IFileIdentifier* fileID, IXMLSAXListener* contentsListener) = 0;
			virtual VCOMError VCOM_CALLTYPE	 ParseBuffer(IXMLFileIOBuffer* inputBuffer, EXMLEncoding encoding, IXMLSAXListener* contentsListener) = 0;

			// Write Support
			virtual VCOMError VCOM_CALLTYPE  BeginDocument(IFileIdentifier* fileID, EXMLEncoding encoding) = 0;
			virtual VCOMError VCOM_CALLTYPE  BeginDocument(IXMLFileIOBuffer* outputBuffer, EXMLEncoding	encoding) = 0;
			virtual VCOMError VCOM_CALLTYPE  EndDocument() = 0;
			virtual VCOMError VCOM_CALLTYPE  BeginNode(const TXString& name) = 0;
			virtual VCOMError VCOM_CALLTYPE  BeginNode(const SXMLURI& uri) = 0;
			virtual VCOMError VCOM_CALLTYPE  EndNode() = 0;
			virtual VCOMError VCOM_CALLTYPE  AddValue(const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE  AddCDATA(const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE  AddComment(const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE  AddText(const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE  AddAttribute(const TXString& name, const TXString& value) = 0;

			virtual VCOMError		VCOM_CALLTYPE	SetFeature(EXMLFileFeature feature, bool bValue) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IXMLSAXFile>			IXMLSAXFilePtr;

		// ----------------------------------------------------------------------------------------------------
		const VCOMError		kVCOMError_XMLFile_SAXError		= 200;
	}
}

