//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace UI
	{
		// ------------------------------------------------------------------------------------------------------------------------------------
		// {3F812C72-5133-4A72-A45B-9AE8E62759EA}
		static const VWIID IID_WebContentFilter = { 0x3f812c72, 0x5133, 0x4a72, { 0xa4, 0x5b, 0x9a, 0xe8, 0xe6, 0x27, 0x59, 0xea } };

		class DYNAMIC_ATTRIBUTE IWebContentFilter : public IVWUnknown
		{
		public:
			virtual TXString	VCOM_CALLTYPE GetFilteredResult() = 0;

			virtual void		VCOM_CALLTYPE AddFilter_ByXMLFile(IXMLFile* xmlFile, const TXString& attributeName) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByTag(const TXString& tagName) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByText(bool found) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByAttrAndAttrValue(const TXString& attr, const TXString& attrVal)= 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByTagAndValue(const TXString& tagName, const TXString& valueRegex) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByTagAndNthChild(const TXString& tagName, const size_t nthChild) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByTagAttrAndAttrValue(const TXString& tagName, const TXString& attrName, const TXString& attrVal) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByTagAttrAndValue(const TXString& tagName, const TXString& attrName, const TXString& valueRegex) = 0;
			virtual void		VCOM_CALLTYPE AddFilter_ByNthChild(const size_t nthChild) = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IWebContentFilter>			IWebContentFilterPtr;
	}
}

