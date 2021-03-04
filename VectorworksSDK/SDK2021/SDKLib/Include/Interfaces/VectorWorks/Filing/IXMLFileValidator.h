//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IXMLFile.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// Errors from the validator
		const VCOMError		kVCOMError_FileValidator_InvalidSchema		= 110;
		const VCOMError		kVCOMError_FileValidator_XMLErrors			= 111;
		const VCOMError		kVCOMError_FileValidator_ValidateErrors		= 112;

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IXMLFileValidatorErrorListener
		{
		public:
			enum EErrorDomain
			{
				eErrorDomain_XMLError,
				eErrorDomain_Validation,
				eErrorDomain_XMLException,
			};

			struct SErrorInfo {
				EErrorDomain	fDomain;
				size_t			fLine;
				size_t			fCholumn;
				TXString		fDescription;
				Sint32				fCode;			// depends on the domain: VectorWorks::Filing::XMLErrors
				TXString		fText1;
				TXString		fText2;
				TXString		fText3;
				TXString		fText4;
			};

		public:
			virtual			~IXMLFileValidatorErrorListener()			{}
			virtual void	OnWarning(const SErrorInfo& errInfo) = 0;
			virtual void	OnError(const SErrorInfo& errInfo) = 0;
			virtual void	OnFatalError(const SErrorInfo& errInfo) = 0;
			virtual void	OnResetErrors() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IXMLFileValidatorNameErrorsListener
		{
		public:
			enum EIterateResult {
				kIterateResult_ContinueNotHandled,
				kIterateResult_ContinueHandled,
				kIterateResult_StopWithError
			};

		public:
			virtual					~IXMLFileValidatorNameErrorsListener()			{}
			virtual void			StartValidating(const TXString& name) = 0;
			virtual bool			EndValidating(const TXString& name, TXString& outXMLName) = 0;
			virtual void			OnErrorNameEmpty(const TXString& name, TXString& outXMLName) = 0;
			virtual EIterateResult	OnErrorSymbol(size_t pos, size_t cnt, TXString& badSymbol) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {384AE042-47F6-44a4-9980-622320B292F5}
		static const VWIID IID_XMLFileValidator = { 0x384ae042, 0x47f6, 0x44a4, { 0x99, 0x80, 0x62, 0x23, 0x20, 0xb2, 0x92, 0xf5 } };

		class DYNAMIC_ATTRIBUTE IXMLFileValidator : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	SetXML(IFileIdentifier* pXMLFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetXML(IXMLFileIOBuffer* pInputBuffer, EXMLEncoding encoding) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetSchema(IFileIdentifier* pSchemaFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetSchema(IXMLFileIOBuffer* pSchemaBuffer, EXMLEncoding encoding) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetErrorListener(IXMLFileValidatorErrorListener* pListener) = 0;

			virtual VCOMError VCOM_CALLTYPE	Validate() = 0;

			virtual VCOMError VCOM_CALLTYPE	ValidateXMLName(const TXString& name) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateXMLName(const TXString& name, TXString& outXMLName, IXMLFileValidatorNameErrorsListener* pErrListener = NULL) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IXMLFileValidator>		IXMLFileValidatorPtr;

		// ----------------------------------------------------------------------------------------------------
		// error namespaces domain
		namespace XMLErrors
		{
			namespace XMLErrorsDomain
			{
				enum Codes
				{
					  NoError                            = 0		// 
					// warnings --------------------------------------------------------------------------------------------------------
					, NotationAlreadyExists              = 2		// Notation '{0}' has already been declared
					, AttListAlreadyExists               = 3		// Attribute '{0}' has already been declared for element '{1}'
					, ContradictoryEncoding              = 4		// Encoding ({0}, from XMLDecl or manually set) contradicts the auto-sensed encoding, ignoring it
					, UndeclaredElemInCM                 = 5		// Element '{0}' was referenced in a content model but never declared
					, UndeclaredElemInAttList            = 6		// Element '{0}' was referenced in an attlist but never declared
					, XMLException_Warning               = 7		// An exception occurred! Type:{0}, Message:{1}
					// errors --------------------------------------------------------------------------------------------------------
					, FeatureUnsupported                 = 10		// {0} is unsupported
					, TopLevelNoNameComplexType          = 11		// Error: Top level complexType has no name - declaration ignored
					, TopLevelNoNameAttribute            = 12		// Globally-declared attribute must have a name - attribute declaration ignored
					, NoNameRefAttribute                 = 13		// Attribute must have a name or a ref - attribute declaration ignored
					, GlobalNoNameElement                = 14		// Globally-declared element must have a name - element declaration ignored
					, NoNameRefElement                   = 15		// Element must have a name or a ref attribute - element ignored
					, NoNameRefGroup                     = 16		// <group> must have a name or a ref attribute - declaration ignored
					, NoNameRefAttGroup                  = 17		// <attributeGroup> must have a name or a ref attribute - declaration ignored
					, AnonComplexTypeWithName            = 18		// Anonymous complexType in element {0} has a name attribute
					, AnonSimpleTypeWithName             = 19		// Anonymous simpleType in element {0} has a name attribute
					, InvalidElementContent              = 20		// The content of an element information item does not match (annotation?, (simpleType | complexType)?, (unique | key | keyref)*)
					, UntypedElement                     = 21		// Untyped element: {0}
					, SimpleTypeContentError             = 22		// Error in content of simpleType
					, ExpectedSimpleTypeInList           = 23		// Expected simpleType in 'list' declaration for {0}
					, ListUnionRestrictionError          = 24		// List | Union | Restriction content is invalid for type {0}
					, SimpleTypeDerivationByListError    = 25		// Error in content of derivation by list for {0}
					, ExpectedSimpleTypeInRestriction    = 26		// Expected simpleType in 'restriction' declaration for {0}
					, DuplicateFacet                     = 27		// Facet {0} already defined - ignoring
					, ExpectedSimpleTypeInUnion          = 28		// Expected simpleType in 'union' declaration for {0}
					, EmptySimpleTypeContent             = 29		// SimpleType content is empty
					, InvalidSimpleContent               = 30		// The content of the simpleContent element is invalid. The content must be RESTRICTION or EXTENSION
					, UnspecifiedBase                    = 31		// The BASE attribute must be specified for the RESTRICTION or EXTENSION element
					, InvalidComplexContent              = 32		// The content of the complexContent element is invalid. The content must be RESTRICTION or EXTENSION
					, SchemaElementContentError          = 33		// Error in content of <schema> element information item
					, ContentError                       = 34		// Content (annotation?,..) is incorrect for type {0}
					, UnknownSimpleType                  = 35		// Unknown simpleType: {0}
					, UnknownComplexType                 = 36		// Unknown complexType: {0}
					, UnresolvedPrefix                   = 37		// Prefix: '{0}' can not be resolved to a URI
					, RefElementNotFound                 = 38		// Ref element {0} not found in the Schema
					, TypeNotFound                       = 39		// Type not found in {0}:{1}
					, TopLevelAttributeNotFound          = 40		// Could not find top level attribute: {0}
					, InvalidChildInComplexType          = 41		// Invalid child '{0}' in the complex type
					, BaseTypeNotFound                   = 42		// Base type could not be found: {0}
					, NoAttributeInSchema                = 43		// No attribute '{0}' was defined in schema: {1}
					, DatatypeValidatorCreationError     = 44		// Error creating datatype validator: {0}
					, InvalidChildFollowingSimpleContent   = 45		// Invalid child following the simpleContent child in the complexType
					, InvalidChildFollowingConplexContent   = 46	// Invalid child following the complexContent child in the complexType
					, InvalidComplexTypeBlockValue       = 47		// The 'block' attribute values of a complexType must be #all | list(restriction,extension); {0} was found
					, InvalidComplexTypeFinalValue       = 48		// The 'final' attribute values of a complexType must be #all | list(restriction,extension); {0} was found
					, AttributeDefaultFixedValue         = 49		// An attribute cannot have both 'fixed' and 'default' present at the same time - default used
					, NotOptionalDefaultAttValue         = 50		// If default and use are both present, use must have the value 'optional'.
					, LocalAttributeWithNameRef          = 51		// Local attribute:{0} has also a ref defined - name ignored
					, GlobalAttributeWithNameRef         = 52		// Global attribute:'{0}' cannot have a ref defined
					, DuplicateAttribute                 = 53		// Error: Attribute '{0}' declared more than once in the same scope- ignoring
					, AttributeWithTypeAndSimpleType     = 54		// Attribute declarations may not contain both a type and a simpleType declaration
					, AttributeSimpleTypeNotFound        = 55		// SimpleType ({0}:{1}) for attribute: {2} not found
					, ElementWithFixedAndDefault         = 56		// An element cannot have both 'fixed' and 'default' present at the same time
					, DeclarationWithNameRef             = 57		// {0}:'{1}' has also a ref defined - name ignored
					, BadAttWithRef                      = 58		// ref cannot appear with any of type, abstract, block, final, nillable, default or fixed
					, InvalidDeclarationName             = 59		// Invalid {0} name:'{1}' - declaration ignored
					, GlobalElementWithRef               = 60		// Globally-declared element {0} cannot have a ref attribute - ref ignored
					, ElementWithTypeAndAnonType         = 61		// Element '{0}' cannot have both a type attribute and a simpleType/complexType type child
					, NotSimpleOrMixedElement            = 62		// Element {0} has a fixed or default value and must have a mixed simple or simple content model
					, DisallowedSimpleTypeExtension      = 63		// The simpleType {0} that {1} uses has a value of 'final' which does not permit extension
					, InvalidSimpleContentBase           = 64		// The type '{0}' specified as the base in the simpleContent element must not have complexContent
					, InvalidComplexTypeBase             = 65		// The type '{0}' is a simple type. It cannot be used in a derivation by RESTRICTION for a complexType
					, InvalidChildInSimpleContent        = 66		// Invalid child following the RESTRICTION or EXTENSION element in the simpleContent definition
					, InvalidChildInComplexContent       = 67		// Invalid child following the RESTRICTION or EXTENSION element in the complexContent definition
					, AnnotationError                    = 68		// Annotation can only appear once: type {0}
					, DisallowedBaseDerivation           = 69		// The base type {0} does not allow itself to be used as the base for a restriction and/or as a type in a list and/or union
					, SubstitutionRepeated               = 70		// The value 'substitution' already in the list
					, UnionRepeated                      = 71		// The value 'union' is already in the list
					, ExtensionRepeated                  = 72		// The value 'extension' is already in the list
					, ListRepeated                       = 73		// The value 'list' is already in the list
					, RestrictionRepeated                = 74		// The value 'restriction' is already in the list
					, InvalidBlockValue                  = 75		// Invalid block value: {0}
					, InvalidFinalValue                  = 76		// Invalid final value: {0}
					, InvalidSubstitutionGroupElement    = 77		// Element {0} cannot be part of the substitution group headed by {1}
					, SubstitutionGroupTypeMismatch      = 78		// Element {0} has a type which does not derive from the type of the element at the head of the substitution group
					, DuplicateElementDeclaration        = 79		// Duplicate element decl in the same scope: {0}
					, InvalidElementBlockValue           = 80		// The 'block' attribute values of an element must be #all | list(substitution,restriction,extension); {0} was found
					, InvalidElementFinalValue           = 81		// The 'final' attribute values of an element must be #all | list(restriction,extension); {0} was found
					, InvalidAttValue                    = 82		// Invalid value '{0}' for attribute: '{1}'.
					, AttributeRefContentError           = 83		// Ref is present, and simpleType/form/type found
					, DuplicateRefAttribute              = 84		// Duplicate reference attribute {0}:{1} in complexType
					, ForbiddenDerivationByRestriction   = 85		// Derivation by restriction is forbidden by either the base type '{0}' or the schema
					, ForbiddenDerivationByExtension     = 86		// Derivation by extension is forbidden by either the base type '{0}' or the schema
					, BaseNotComplexType                 = 87		// The base type specified in the complexContent element must be a complexType
					, ImportNamespaceDifference          = 88		// Imported schema '{0}' has a different targetNameSpace '{1}' from what's declared '{2}'
					, ImportRootError                    = 89		// Could not get the doc root for imported Schema: {0}
					, DeclarationNoSchemaLocation        = 90		// A schemaLocation attribute must be specified on '{0}' element.
					, IncludeNamespaceDifference         = 91		// Included schema '{0}' has a different targetNameSpace '{1}'
					, OnlyAnnotationExpected             = 92		// At most one <annotation> element is expected in the content.
					, InvalidAttributeContent            = 93		// The content must be (annotation?, simpleType?) for attribute '{0}={1}'
					, AttributeRequired                  = 94		// Attribute '{0}' must appear in {1} {2} declarations
					, AttributeDisallowed                = 95		// Attribute '{0}' cannot appear in {1} {2} declarations
					, InvalidMin2MaxOccurs               = 96		// Value of minOccurs '{0}' must not be greater than value of maxOccurs '{1}'
					, AnyAttributeContentError           = 97		// 'anyAttribute' elements can contain at most one 'annotation' element in their children
					, NoNameGlobalElement                = 98		// Global <{0}> must have a name - declaration ignored
					, NoCircularDefinition               = 99		// No circular definitions are allowed: '{0}'
					, DuplicateGlobalType                = 100		// Global {0}:'{1}' declared more than once or also declared as {2}
					, DuplicateGlobalDeclaration         = 101		// Global {0}:'{1}' declared more than once
					, WS_CollapseExpected                = 102		// Invalid value '{0}' for facet 'whiteSpace'. Value should be 'collapse'.
					, Import_1_1                         = 103		// The namespace of an <import> element must be different from the targetNamespace of the <import>ing schema
					, Import_1_2                         = 104		// If the namespace on an <import> element is not present, the <import>ing schema must have a targetNamespace
					, ElemIDValueConstraint              = 105		// Element '{0}' must not have a value constraint:'{1}' as its type is derived from ID
					, NoNotationType                     = 106		// It is an error for NOTATION to be used directly in a schema in element/attribute '{0}'
					, EmptiableMixedContent              = 107		// For element '{0}', the {content type} is mixed, then the {content type}'s particle must be emptiable
					, EmptyComplexRestrictionDerivation   = 108		// The content of complexType is EMPTY, but base is not empty or does not have emptiable particle.
					, MixedOrElementOnly                 = 109		// The content type of the base type:'{0}' and derived type:'{1}' must both be mixed or element-only.
					, InvalidContentRestriction          = 110		// The content type is not a valid restriction of the content type of the base.
					, ForbiddenDerivation                = 111		// Derivation by extension or restriction is forbidden by either the base type '{0}' or the schema
					, AtomicItemType                     = 112		// The {item type definition} must have {variety} of atomic or union (where all member types must be atomic)
					, MemberTypeNoUnion                  = 113		// The {member type definitions} must all have {variety} of atomic or list
					, GroupContentError                  = 114		// The group:'0' must contain (all | choice | sequence)
					, AttGroupContentError               = 115		// The attributeGroup:'0' must match (annotation?. ((attribute | attributeGroup)*, anyAttribute?))
					, MinMaxOnGroupChild                 = 116		// The child of a model group definition must not specify either the minOccurs or maxOccurs attribute.
					, DeclarationNotFound                = 117		// The {0} -'{1}:{2}'- not found in the schema
					, AllContentLimited                  = 118		// A group whose content is 'all' must only appear as the content type of a complex type definition.
					, BadMinMaxAllCT                     = 119		// When a model group has {compositor} 'all' which constitutes the {content type} of a complex type, minOccurs=maxOccurs=1
					, BadMinMaxAllElem                   = 120		// In an 'all' schema component, the value of minOccurs/maxOccurs of an element must be '0' or '1'.
					, NoCircularAttGroup                 = 121		// Circular attributeGroup reference -{0}- is disallowed outside <redefine>
					, DuplicateAttInDerivation           = 122		// Attribute '{0}' already defined in base and should not appear in derivation by extension.
					, NotExpressibleWildCardIntersection   = 123	// The intensional intersection of {attributes wildcard}s must be expressible
					, BadAttDerivation_1                 = 124		// Base type definition does not have any attributes
					, BadAttDerivation_2                 = 125		// Attribute '{0}' has an inconsistent REQUIRED setting with that of the base
					, BadAttDerivation_3                 = 126		// Type of attribute '{0}' must be validly derived from type of attribute in base
					, BadAttDerivation_4                 = 127		// Attribute '{0}' is either not fixed, or has a different value from that of the base
					, BadAttDerivation_5                 = 128		// Attribute '{0}' has invalid target namespace with respect to a base wildcard constraint or, base has no wildcard
					, BadAttDerivation_6                 = 129		// An attribute wildcard is present in the derived type, but not in the base
					, BadAttDerivation_7                 = 130		// The attribute wildcard in the derived type is not a valid subset of that in the base
					, BadAttDerivation_8                 = 131		// Attribute '{0}' cannot modify the 'use' attribute in a derived type, if base attribute use is prohibited
					, BadAttDerivation_9                 = 132		// The wildcard attribute in the derived type must be identical to or stronger than the one in the base.
					, AllContentError                    = 133		// Content of <all> is restricted to elements only. '{0}' encountered and ignored.
					, RedefineNamespaceDifference        = 134		// Redefined schema '{0}' has a different targetNameSpace '{1}'.
					, Redefine_InvalidSimpleType         = 135		// A simpleType child of a <redefine> must have a restriction element as a child
					, Redefine_InvalidSimpleTypeBase     = 136		// The base attribute of the restriction child of a simpleType, must be the same as the redefine simpleType's name attribute
					, Redefine_InvalidComplexType        = 137		// A complexType child of a <redefine> must have a restriction or extension element as a grandchild
					, Redefine_InvalidComplexTypeBase    = 138		// The base attribute of a restriction/extension must be the same as the complexType's name attribute in <redefine>
					, Redefine_InvalidGroupMinMax        = 139		// The group '{0}' which contains a reference to a group being redefined must have minOccurs = maxOccurs = 1
					, Redefine_DeclarationNotFound       = 140		// Could not find a declaration in the schema to be redefined corresponding to '{0}'
					, Redefine_GroupRefCount             = 141		// If a group child of a <redefine> element contains a group ref'ing itself, it must have exactly 1 reference.
					, Redefine_AttGroupRefCount          = 142		// If an attributeGroup of a <redefine> element contains a reference to itself, such reference must be exactly 1
					, Redefine_InvalidChild              = 143		// A <redefine> element cannot contain a child of type '{0}'
					, Notation_InvalidDecl               = 144		// The declaration for notation '{0}' is invalid
					, Notation_DeclNotFound              = 145		// The notation declaration '{0}:{1}' is not found
					, IC_DuplicateDecl                   = 146		// More than one identity constraint named '{0}'.
					, IC_BadContent                      = 147		// The content of an identity constraint must match (annotation?, selector, field+)
					, IC_KeyRefReferNotFound             = 148		// Key reference declaration '{0}' refers to unknown key with name '{1}'.
					, IC_KeyRefCardinality               = 149		// Cardinality of fields for keyref '{0}' and key '{1}' must match.
					, IC_XPathExprMissing                = 150		// Xpath expression is either missing or empty
					, AttUseCorrect                      = 151		// The {value constraint} of an attribute ref is not fixed or different from the fixed {value constraint} of '{0}'
					, AttDeclPropCorrect3                = 152		// The {type definition} for attribute '{0}={1}' is or is derived from ID, and must not have {value constraint}
					, AttDeclPropCorrect5                = 153		// More than one attribute derived from type ID cannot appear in the same complex type - '{0}' ignored
					, AttGrpPropCorrect3                 = 154		// More than one attribute derived from type ID cannot appear in the same attribute group - '{0}' ignored
					, InvalidTargetNSValue               = 155		// '' is not a legal value for the targetNamespace attribute; the attribute must be absent or contain a nonempty value
					, DisplayErrorMessage                = 156		// {0}
					, XMLException_Error                 = 157		// An exception occurred! Type:{0}, Message:{1}
					, InvalidRedefine                    = 158		// Invalid Redefine: '{0}' has already been included or redefined
					, InvalidNSReference                 = 159		// Schema Representation Constraint: Namespace '{0}' is referenced without <import> declaration
					, NotAllContent                      = 160		// An 'all' model group that's part of a complex type definition must constitute the entire content type of the definition
					, InvalidAnnotationContent           = 161		// An <annotation> can only contain <appinfo> and <documentation> elements
					, InvalidFacetName                   = 162		// Invalid facet name: {0}
					, InvalidXMLSchemaRoot               = 163		// The root element name of an XML Schema should be 'schema'.
					, CircularSubsGroup                  = 164		// Circular substitution groups are disallowed for element '{0}'.
					, SubsGroupMemberAbstract            = 165		// For '{0}' to be a member of the substitution group set of '{1}', its {abstract} must be false.
					, ELTSchemaNS                        = 166		// The namespace of element '{0}' must be from the schema namespace.
					, InvalidAttTNS                      = 167		// The {target namespace} of '{0}' must not match 'http://www.w3.org/2001/XMLSchema-instance'.
					, NSDeclInvalid                      = 168		// The namespace declaration is invalid.
					, DOMLevel1Node                      = 169		// Namespace fixup cannot be performed on a DOM Level 1 Node.
					// warnings --------------------------------------------------------------------------------------------------------
					, EntityExpansionLimitExceeded       = 172		// The parser has encountered more than '{0}' entity expansions in this document; this is the limit imposed by the application.
					, ExpectedCommentOrCDATA             = 173		// Expected comment or CDATA
					, ExpectedAttrName                   = 174		// Expected an attribute name
					, ExpectedNotationName               = 175		// Expected a notation name
					, NoRepInMixed                       = 176		// Repetition of individual elements is not legal for mixed content models
					, BadDefAttrDecl                     = 177		// Bad default attribute declaration
					, ExpectedDefAttrDecl                = 178		// Expected default attribute declaration, assuming #IMPLIED 
					, AttListSyntaxError                 = 179		// Attribute list syntax error
					, ExpectedEqSign                     = 180		// Expected equal sign
					, DupAttrName                        = 181		// Duplication attribute name
					, BadIdForXMLLangAttr                = 182		// Bad ID, '{0}', for xml:lang attribute
					, ExpectedElementName                = 183		// Expected an element name
					, MustStartWithXMLDecl               = 184		// Must start with an XMLDecl
					, CommentsMustStartWith              = 185		// Comments must start with <!--
					, InvalidDocumentStructure           = 186		// Invalid document structure
					, ExpectedDeclString                 = 187		// Expected a 'version=', 'encoding=', or 'standalone='
					, BadXMLVersion                      = 188		// Bad XML version string
					, UnsupportedXMLVersion              = 189		// Unsupported XML version, '{0}'
					, UnterminatedXMLDecl                = 190		// Unterminated XML decl
					, BadXMLEncoding                     = 191		// Bad XML encoding declaration, '{0}'
					, BadStandalone                      = 192		// Bad standalone declaration
					, UnterminatedComment                = 193		// Unterminated comment
					, PINameExpected                     = 194		// Processing instruction name expected
					, UnterminatedPI                     = 195		// Unterminated processing instruction
					, InvalidCharacter                   = 196		// Invalid character (Unicode: 0x{0})
					, UnexpectedTextBeforeRoot           = 197		// Unexpected text before root element
					, UnterminatedStartTag               = 198		// Unterminated start tag, '{0}'
					, ExpectedAttrValue                  = 199		// Expected an attribute value
					, UnterminatedEndTag                 = 200		// Unterminated end tag
					, ExpectedAttributeType              = 201		// Expected type (CDATA, ID, NMTOKEN, ..), for attribute '{0}' of element '{1}'
					, ExpectedEndOfTagX                  = 202		// Expected end of tag '{0}'
					, ExpectedMarkup                     = 203		// Expected tag name, comment, PI, or other markup
					, NotValidAfterContent               = 204		// Not valid after content
					, ExpectedComment                    = 205		// Expected comment
					, ExpectedCommentOrPI                = 206		// Expected comment or processing instruction
					, ExpectedWhitespace                 = 207		// Expected whitespace
					, NoRootElemInDOCTYPE                = 208		// No root element in DOCTYPE
					, ExpectedQuotedString               = 209		// Expected quoted string
					, ExpectedPublicId                   = 210		// Expected public id
					, InvalidPublicIdChar                = 211		// Invalid character in public id (Unicode: 0x{0})
					, UnterminatedDOCTYPE                = 212		// Unterminated DOCTYPE declaration
					, InvalidCharacterInIntSubset        = 213		// Invalid character in internal subset (Unicode: 0x{0})
					, ExpectedCDATA                      = 214		// Expected CDATA section
					, InvalidInitialNameChar             = 215		// Invalid initial name character
					, InvalidNameChar                    = 216		// Invalid name character
					, UnexpectedWhitespace               = 217		// Unexpected whitespace
					, InvalidCharacterInAttrValue        = 218		// Invalid character in attribute value {0} (Unicode: 0x{1})
					, ExpectedMarkupDecl                 = 219		// Expected a markup declaration
					, TextDeclNotLegalHere               = 220		// Text declaration not legal here
					, ConditionalSectInIntSubset         = 221		// Conditional section in internal subset
					, ExpectedPEName                     = 222		// Expected parameter entity name
					, UnterminatedEntityDecl             = 223		// Unterminated entity declaration, '{0}'
					, InvalidCharacterRef                = 224		// Invalid character reference
					, UnterminatedCharRef                = 225		// Unterminated character reference
					, ExpectedEntityRefName              = 226		// Expected entity name for reference
					, EntityNotFound                     = 227		// Entity '{0}' was not found
					, NoUnparsedEntityRefs               = 228		// Unparsed entity references, '{0}', not valid here
					, UnterminatedEntityRef              = 229		// Unterminated entity reference
					, RecursiveEntity                    = 230		// Recursive entity expansion
					, PartialMarkupInEntity              = 231		// Partial markup in entity value
					, UnterminatedElementDecl            = 232		// Unterminated element declaration, '{0}'
					, ExpectedContentSpecExpr            = 233		// Expected content specification expression for element '{0}'
					, ExpectedAsterisk                   = 234		// Expected asterisk
					, UnterminatedContentModel           = 235		// Unterminated Content model
					, ExpectedSystemId                   = 236		// Expected system id
					, ExpectedSystemOrPublicId           = 237		// Expected system or public id
					, UnterminatedNotationDecl           = 238		// Unterminated notation declaration
					, ExpectedSeqChoiceLeaf              = 239		// Expected ',', '|', or ')' characters
					, ExpectedChoiceOrCloseParen         = 240		// Expected '|' or ')' characters
					, ExpectedSeqOrCloseParen            = 241		// Expected ',' or ')' characters or close parenthesis in content model of element '{0}'
					, ExpectedEnumValue                  = 242		// Expected enumeration value for attribute '{0}'
					, ExpectedEnumSepOrParen             = 243		// Expected | enumeration separator, or closing paren
					, UnterminatedEntityLiteral          = 244		// Unterminated entity literal
					, MoreEndThanStartTags               = 245		// There are more end tags than start tags
					, ExpectedOpenParen                  = 246		// Expected an open parenthesis
					, AttrAlreadyUsedInSTag              = 247		// The attribute '{0}' is already used in element '{1}'
					, BracketInAttrValue                 = 248		// A '<' character cannot be used in attribute '{0}', except through &lt;
					, Expected2ndSurrogateChar           = 249		// A leading surrogate character was not followed by a legal second character
					, ExpectedEndOfConditional           = 250		// Expected ']]>' to end a conditional section
					, ExpectedIncOrIgn                   = 251		// Expected INCLUDE or IGNORE here
					, ExpectedINCLUDEBracket             = 252		// Expected [ to follow INCLUDE or IGNORE
					, ExpectedTextDecl                   = 253		// Expected a TextDecl here: <?xml ....
					, ExpectedXMLDecl                    = 254		// Expected a XMLDecl here: <?xml ....
					, UnexpectedEOE                      = 255		// Unexpected end of entity {0}
					, PEPropogated                       = 256		// A PE propagated out of the Sint32/ext subset, discarding extra text
					, ExtraCloseSquare                   = 257		// An extra ] character was found an ignored
					, PERefInMarkupInIntSubset           = 258		// PE refs are not allowed inside markup in the internal subset
					, EntityPropogated                   = 259		// An entity propagated out of the content section into Miscellaneous
					, ExpectedNumericalCharRef           = 260		// Expected &# to be followed by a numeric character value
					, ExpectedOpenSquareBracket          = 261		// Expected an open bracket ('[') here
					, BadSequenceInCharData              = 262		// The sequence ']]>' is not allowed in character data
					, IllegalSequenceInComment           = 263		// Illegal sequence '--' in comment
					, UnterminatedCDATASection           = 264		// Unterminated CDATA section
					, ExpectedNDATA                      = 265		// Expected NDATA
					, NDATANotValidForPE                 = 266		// NDATA is not legal for parameter entities
					, HexRadixMustBeLowerCase            = 267		// Hex radix character refs must use 'x', not 'X'
					, DeclStringRep                      = 268		// '{0}' has already been set. Ignoring redundant setting
					, DeclStringsInWrongOrder            = 269		// The XMLDecl strings must be in the order: version, encoding, standalone
					, NoExtRefsInAttValue                = 270		// External entities cannot be referred to from attribute values
					, XMLDeclMustBeLowerCase             = 271		// The XML or Text decl must start with '<?xml ', not '<?XML '
					, ExpectedEntityValue                = 272		// Expected a literal entity value or PUBLIC/SYSTEM id
					, BadDigitForRadix                   = 273		// '{0}' is not a valid digit for the indicated radix
					, EndedWithTagsOnStack               = 274		// The input ended before all started tags were ended. Last tag started was '{0}'
					, AmbiguousContentModel              = 275		// The content model for element '{0}' is ambiguous
					, NestedCDATA                        = 276		// Nested CDATA sections are not allowed
					, UnknownPrefix                      = 277		// The prefix '{0}' has not been mapped to any URI
					, PartialTagMarkupError              = 278		// The start and the end tag were in the different entities
					, EmptyMainEntity                    = 279		// The main XML document cannot be empty
					, CDATAOutsideOfContent              = 280		// CDATA is not allowed outside the root element
					, OnlyCharRefsAllowedHere            = 281		// Only numeric character entities or special character entities are legal here
					, Unexpected2ndSurrogateChar         = 282		// Got an unexpected trailing surrogate character
					, NoPIStartsWithXML                  = 283		// No processing instruction starts with 'xml'
					, XMLDeclMustBeFirst                 = 284		// The XML or Text declaration must start at line/column 1/1
					, XMLVersionRequired                 = 285		// The 'version=' string is required in an XMLDecl
					, StandaloneNotLegal                 = 286		// The 'standalone=' string is only allowed in the main XML entity
					, EncodingRequired                   = 287		// The 'encoding=' string is required in an Text Decl
					, TooManyColonsInName                = 288		// When namespaces are enabled, a name can have only one colon character
					, InvalidColonPos                    = 289		// When namespaces are enabled, the colon cannot be the first or last character
					, ColonNotLegalWithNS                = 290		// Colons are not allowed in this name when namespaces are enabled
					, SysException                       = 291		// A system exception occurred during processing
					, XMLException_Fatal                 = 292		// An exception occurred! Type:{0}, Message:{1}
					, UnexpectedEOF                      = 293		// Unexpected end of file exception. Message: {0}
					, UnexpectedError                    = 294		// UnexpectedError
					, BadSchemaLocation                  = 295		// The schemaLocation attribute does not contain pairs of values.
					, NoGrammarResolver                  = 296		// Internal error: don't have a GrammarResolver for TraverseSchema
					, SchemaScanFatalError               = 297		// Fatal error encountered during schema scan
					, IllegalRefInStandalone             = 298		// Reference to external entity declaration '{0}' is not allowed in a standalone document.
					, PEBetweenDecl                      = 299		// Partial markup in parameter entity replacement text in a complete declaration.
					, NoEmptyStrNamespace                = 300		// The value of the attribute '{0}' is invalid. Prefixed namespace bindings may not be empty.
					, NoUseOfxmlnsAsPrefix               = 301		// The prefix 'xmlns' cannot be bound to any namespace explicitly.
					, NoUseOfxmlnsURI                    = 302		// The namespace for 'xmlns' cannot be bound to any prefix explicitly.
					, PrefixXMLNotMatchXMLURI            = 303		// The prefix 'xml' cannot be bound to any namespace other than its usual namespace.
					, XMLURINotMatchXMLPrefix            = 304		// The namespace for 'xml' cannot be bound to any prefix other than 'xml'.
					, NoXMLNSAsElementPrefix             = 305		// Element '{0}' cannot have 'xmlns' as its prefix.
					, CT_SimpleTypeChildRequired         = 306		// Complex Type Definition Representation OK - 2.2: <restriction> must have a <simpleType> child.
				};
			}

			namespace ValidityDomain
			{
				enum Codes
				{
					  NoError                            = 0		// 
					// errors --------------------------------------------------------------------------------------------------------
					, ElementNotDefined                  = 2		// Unknown element '{0}'
					, AttNotDefined                      = 3		// Attribute '{0}' not defined
					, NotationNotDeclared                = 4		// Notation '{0}' was referenced but never declared
					, RootElemNotLikeDocType             = 5		// Root element different from DOCTYPE
					, RequiredAttrNotProvided            = 6		// Required attribute '{0}' was not provided
					, ElementNotValidForContent          = 7		// Element '{0}' is not valid for content model: '{1}'
					, BadIDAttrDefType                   = 8		// ID attributes must be #IMPLIED or #REQUIRED
					, InvalidEmptyAttValue               = 9		// This type of attribute cannot have an empty value
					, ElementAlreadyExists               = 10		// Element '{0}' has already been declared
					, MultipleIdAttrs                    = 11		// Element '{0}' has more than one ID attribute
					, ReusedIDValue                      = 12		// ID '{0}' has already been used
					, IDNotDeclared                      = 13		// ID attribute '{0}' was referenced but never declared
					, UnknownNotRefAttr                  = 14		// Attribute '{0}' refers to an unknown notation '{1}'
					, UndeclaredElemInDocType            = 15		// Element '{0}' was used in the DOCTYPE but never declared
					, EmptyNotValidForContent            = 16		// Empty content not valid for content model: '{0}'
					, AttNotDefinedForElement            = 17		// Attribute '{0}' is not declared for element '{1}'
					, BadEntityRefAttr                   = 18		// The value '{0}' for attribute '{1}' of type ENTITY/ENTITIES must refer to an external, unparsed entity
					, UnknownEntityRefAttr               = 19		// Attribute '{0}' refers to an unknown entity '{1}'
					, ColonNotValidWithNS                = 20		// If namespaces are enabled, it's invalid for an attribute of type ID/IDREF/IDREFS/ENTITY/ENTITIES/NOTATION to contain a colon.
					, NotEnoughElemsForCM                = 21		// Not enough elements to match content model : '{0}'
					, NoCharDataInCM                     = 22		// No character data is allowed by content model
					, DoesNotMatchEnumList               = 23		// The value '{0}' for attribute '{1}' does not match its defined enumeration or notation list
					, AttrValNotName                     = 24		// The value '{0}' for attribute '{1}' must be Name or Nmtoken
					, NoMultipleValues                   = 25		// Attribute '{0}' does not support multiple values
					, NotSameAsFixedValue                = 26		// Attribute '{0}' has a value, '{1}', that does not match its #FIXED value, '{2}'
					, RepElemInMixed                     = 27		// Element types cannot be duplicated in Mixed content models
					, NoValidatorFor                     = 28		// No validator for datatype {0}
					, IncorrectDatatype                  = 29		// Incorrect datatype: {0}
					, NotADatatype                       = 30		// {0} is not a datatype.
					, TextOnlyContentWithType            = 31		// The content attribute must be 'textOnly' if you specify a type attribute.
					, FeatureUnsupported                 = 32		// {0} is unsupported
					, NestedOnlyInElemOnly               = 33		// Nested Element decls only allowed in elementOnly content
					, EltRefOnlyInMixedElemOnly          = 34		// Element references only allowed in mixed or elementOnly content
					, OnlyInEltContent                   = 35		// {0} only allowed in elementOnly content.
					, OrderIsAll                         = 36		// {0} not allowed if the order is all.
					, DatatypeWithType                   = 37		// Datatype qualifiers can only be used if you specify a type attribute.
					, DatatypeQualUnsupported            = 38		// The datatype qualifier {0} is not supported.
					, GroupContentRestricted             = 39		// Error: {0} content must be one of element, group, modelGroupRef. Saw {1}
					, UnknownBaseDatatype                = 40		// Unknown base type {0} for type {1}.
					, OneOfTypeRefArchRef                = 41		// Can only have one of type and ref attributes.
					, NoContentForRef                    = 42		// A <{0}> declaration that has a ref attribute, cannot have child content.
					, IncorrectDefaultType               = 43		// Incorrect type for {0}'s default value: {1}
					, IllegalAttContent                  = 44		// Illegal content {0} in attribute group
					, ValueNotInteger                    = 45		// Value of {0} is not an integer.
					, DatatypeError                      = 46		// Datatype error: Type:{0}, Message:{1}.
					, SchemaError                        = 47		// Schema error: Type:{0}, Message:{1}
					, TypeAlreadySet                     = 48		// The type of the element has already been declared.
					, ProhibitedAttributePresent         = 49		// Prohibited Attribute is found.
					, IllegalXMLSpace                    = 50		// Illegal xml:space declaration.
					, NotBoolean                         = 51		// {0} is not a boolean.
					, NotDecimal                         = 52		// {0} is not a decimal.
					, FacetsInconsistent                 = 53		// Facets are inconsistent with base type.
					, IllegalFacetValue                  = 54		// Illegal value {0} for facet {1}.
					, IllegalDecimalFacet                = 55		// Illegal Facet for decimal type.
					, UnknownFacet                       = 56		// Unknown Facet: {0}.
					, InvalidEnumValue                   = 57		// Invalid value for Enum constant: {0}.
					, OutOfBounds                        = 58		// {0} is out of bounds:[ {1} {3} X  {4} {2} ].
					, NotAnEnumValue                     = 59		// {0} is not one of the specified enum values.
					, NotInteger                         = 60		// {0} is not an integer.
					, IllegalIntegerFacet                = 61		// Illegal Facet for Integer type.
					, NotReal                            = 62		// {0} is not a double.
					, IllegalRealFacet                   = 63		// Illegal Facet for Real type.
					, ScaleLargerThanPrecision           = 64		// Scale Facet must be less than or equal to Precision Facet
					, PrecisionExceeded                  = 65		// {0} has exceeded the precision Facet {1}
					, ScaleExceeded                      = 66		// {0} has exceeded the scale Facet {1}
					, NotFloat                           = 67		// {0} is not a float.
					, SchemaRootError                    = 68		// Can't get back Schema document's root element {0}.
					, WrongTargetNamespace               = 69		// Schema in {0} has a different target namespace from the one specified in the instance document {1}.
					, SimpleTypeHasChild                 = 70		// In element {0}: Can not have element children within a simple type content.
					, NoDatatypeValidatorForSimpleType   = 71		// This element {0} has a simpletype but no datatype validator was found.
					, GrammarNotFound                    = 72		// There is no Grammar for uri: {0}.
					, DisplayErrorMessage                = 73		// {0}
					, NillNotAllowed                     = 74		// xsi:nil must not be specified for the element {0} with nillable equals false
					, NilAttrNotEmpty                    = 75		// Element {0} with attribute xsi:nil=true must be empty
					, FixedDifferentFromActual           = 76		// Content of element '{0}' is different from the fixed attribute value in the element's schema declaration.
					, NoDatatypeValidatorForAttribute    = 77		// No datatype validator was found for this attribute {0}.
					, GenericError                       = 78		// Schema error during parsing
					, ElementNotQualified                = 79		// Element '{0}' should be qualified
					, ElementNotUnQualified              = 80		// Element '{0}' should be un-qualified
					, VC_IllegalRefInStandalone          = 81		// Reference to external entity declaration '{0}' is not allowed in a standalone document.
					, NoDefAttForStandalone              = 82		// Attribute '{0}' for element '{1}' has a default value and must be specified in a standalone document.
					, NoAttNormForStandalone             = 83		// Attribute '{0}' must not be changed by normalization in a standalone document.
					, NoWSForStandalone                  = 84		// White space must not occur between externally declared elements with element content in a standalone document.
					, VC_EntityNotFound                  = 85		// Entity '{0}' was not found
					, PartialMarkupInPE                  = 86		// Partial markup in parameter entity replacement text.
					, DatatypeValidationFailure          = 87		// Failed to validate '{0}'
					, UniqueParticleAttributionFail      = 88		// Complex type '{0}' violates the Unique Particle Attribution rule in its components '{1}' and '{2}'
					, NoAbstractInXsiType                = 89		// Abstract type '{0}' should not be used in xsi:type
					, NoDirectUseAbstractElement         = 90		// A member of abstract element {0} substitution group must be specified
					, NoUseAbstractType                  = 91		// Element {0} is declared with a type that is abstract.  Use xsi:type to specify a non-abstract type
					, BadXsiType                         = 92		// Unresolved type '{0}' found in xsi:type handling
					, NonDerivedXsiType                  = 93		// Type '{0}' that is used in xsi:type is not derived from the type of element '{1}'
					, NoSubforBlock                      = 94		// Element '{0}' has blocking constraint and does not permit substitution
					, AttributeNotQualified              = 95		// Attribute '{0}' should be qualified
					, AttributeNotUnQualified            = 96		// Attribute '{0}' should be un-qualified
					, IC_FieldMultipleMatch              = 97		// Field matches more than one value within the scope of its selector; fields must match unique values
					, IC_UnknownField                    = 98		// Internal identity constraint error; unknown field.
					, IC_AbsentKeyValue                  = 99		// Identity-constraint 4.2.1: element '{0}' has a key with no value.
					, IC_UniqueNotEnoughValues           = 100		// Not enough values specified for <unique> identity constraint for element '{0}'.
					, IC_KeyNotEnoughValues              = 101		// Not enough values specified for <key name={1}> identity constraint for element '{0}'.
					, IC_KeyRefNotEnoughValues           = 102		// Not enough values specified for <keyref name={1}> identity constraint for element '{0}'.
					, IC_KeyMatchesNillable              = 103		// Identity-constraint 4.2.3: element '{0}' has a key that matches an element that has nillable set to true.
					, IC_DuplicateUnique                 = 104		// Duplicate unique value declared for identity constraint of element '{0}'.
					, IC_DuplicateKey                    = 105		// Duplicate key value declared for identity constraint of element '{0}'.
					, IC_KeyRefOutOfScope                = 106		// The keyref '{0}' refers to a key/unique that is out of scope.
					, IC_KeyNotFound                     = 107		// The key for identity constraint of element '{0}' is not found.
					, NonWSContent                       = 108		// Non-whitespace characters are not allowed in schema elements other than 'appinfo' and 'documentation'.
					, EmptyElemNotationAttr              = 109		// EMPTY Element '{0}' has Attribute '{1}' of type NOTATION 
					, EmptyElemHasContent                = 110		// EMPTY Element '{0}' can't have content(not even entity references, comments, PIs or white space). 
					, ElemOneNotationAttr                = 111		// Element '{0}' has more than one Attribute of type NOTATION 
					, AttrDupToken                       = 112		// Attribute '{0}' has non distinct token '{1}' 
					, ElemChildrenHasInvalidWS           = 113		// Element '{0}' 's content model(children) does not allow escaped white space. 
				};
			}

			namespace XMLExceptionDomain
			{
				enum ECodes
				{
					  NoError                            = 0		// 
					// warnings --------------------------------------------------------------------------------------------------------
					, Scan_CouldNotOpenSource_Warning    = 2		// Warning: The primary document entity could not be opened. Id={0}
					, GC_ExistingGrammar                 = 3		// Warning: No caching of grammar set, a grammar with same key found in the cache pool.
					// errors --------------------------------------------------------------------------------------------------------
					, Array_BadIndex                     = 6		// The index is beyond the array bounds 
					, Array_BadNewSize                   = 7		// The new size is less than the old one
					, AttrList_BadIndex                  = 8		// The index given was beyond the max attribute index
					, AttDef_BadAttType                  = 9		// The passed AttTypes value is not known
					, AttDef_BadDefAttType               = 10		// The passed DefAttTypes value is not known
					, Bitset_BadIndex                    = 11		// The bit index was beyond the set size
					, Bitset_NotEqualSize                = 12		// The bit sets are not of the same size
					, BufMgr_NoMoreBuffers               = 13		// The buffer manager cannot provide any more buffers
					, BufMgr_BufferNotInPool             = 14		// The passed buffer was not found in this manager's pool
					, CPtr_PointerIsZero                 = 15		// The pointer has not been set
					, CM_BinOpHadUnaryType               = 16		// The binary operation node had a unary node type
					, CM_MustBeMixedOrChildren           = 17		// The content type must be mixed or children
					, CM_NoPCDATAHere                    = 18		// PCDATA nodes are not valid here
					, CM_NotValidForSpecType             = 19		// The {0} operation is invalid for the spec type
					, CM_UnaryOpHadBinType               = 20		// The unary operation node had a binary node type
					, CM_UnknownCMType                   = 21		// Unknown content model type
					, CM_UnknownCMSpecType               = 22		// Unknown content spec type
					, CM_NoParentCSN                     = 23		// The parent element has no content spec node
					, CM_NotValidSpecTypeForNode         = 24		// The spec type is not valid for {0}
					, DTD_UnknownCreateReason            = 25		// The creation reason enum has an unknown value
					, ElemStack_EmptyStack               = 26		// The element stack is empty
					, ElemStack_BadIndex                 = 27		// The element stack index given was beyond the stack top
					, ElemStack_StackUnderflow           = 28		// The element stack was already empty when a pop request occurred
					, ElemStack_NoParentPushed           = 29		// A parent operation was requested, but only one element is on the stack
					, Enum_NoMoreElements                = 30		// The enumerator contains no more elements
					, File_CouldNotOpenFile              = 31		// Could not open file: {0}
					, File_CouldNotGetCurPos             = 32		// Could not query the current file position
					, File_CouldNotCloseFile             = 33		// Could not close the file
					, File_CouldNotSeekToEnd             = 34		// Could not seek to end of file
					, File_CouldNotSeekToPos             = 35		// Could not seek to required position in file
					, File_CouldNotDupHandle             = 36		// Could not duplicate the handle
					, File_CouldNotReadFromFile          = 37		// Could not read data from file
					, File_CouldNotWriteToFile           = 38		// Could not write data to file
					, File_CouldNotResetFile             = 39		// Could not reset file to beginning
					, File_CouldNotGetSize               = 40		// Could not ascertain the file size
					, File_CouldNotGetBasePathName       = 41		// Could not determine base pathname of the file
					, File_BasePathUnderflow             = 42		// The base path had too few levels to weave in relative part
					, Gen_ParseInProgress                = 43		// Parse may not be called while parsing
					, Gen_NoDTDValidator                 = 44		// A DOCTYPE was seen but the installed validator does not understand DTDs
					, Gen_CouldNotOpenDTD                = 45		// Could not open DTD file '{0}'
					, Gen_CouldNotOpenExtEntity          = 46		// Could not open external entity '{0}'
					, Gen_UnexpectedEOF                  = 47		// The end of input was not expected
					, HshTbl_ZeroModulus                 = 48		// The hash modulus cannot be zero
					, HshTbl_BadHashFromKey              = 49		// Hashing the key returned an invalid bad hash value
					, HshTbl_NoSuchKeyExists             = 50		// The key '{0}' could not be found in the hash table
					, Mutex_CouldNotCreate               = 51		// Could not create mutex
					, Mutex_CouldNotClose                = 52		// Could not close mutex
					, Mutex_CouldNotLock                 = 53		// Could not lock mutex
					, Mutex_CouldNotUnlock               = 54		// Could not unlock mutex
					, Mutex_CouldNotDestroy              = 55		// Could not destroy mutex
					, NetAcc_InternalError               = 56		// Internal Error on NetAccessor
					, NetAcc_LengthError                 = 57		// Error on NetAccessor. Cannot determine length of remote file
					, NetAcc_InitFailed                  = 58		// The NetAccessor could not be initialized.
					, NetAcc_TargetResolution            = 59		// The host/address '{0}' could not be resolved
					, NetAcc_CreateSocket                = 60		// Could not create the socket for URL '{0}'
					, NetAcc_ConnSocket                  = 61		// Could not connect to the socket for URL '{0}'
					, NetAcc_WriteSocket                 = 62		// Could not write to the socket for URL '{0}'
					, NetAcc_ReadSocket                  = 63		// Could not read from the socket for URL '{0}'
					, NetAcc_UnsupportedMethod           = 64		// The specified HTTP method is not supported by this NetAccessor.
					, Pool_ElemAlreadyExists             = 65		// The element {0} already exists
					, Pool_BadHashFromKey                = 66		// Hashing the key returned an invalid bad hash value
					, Pool_InvalidId                     = 67		// The passed id is not valid for this pool
					, Pool_ZeroModulus                   = 68		// The modulus value cannot be zero
					, RdrMgr_ReaderIdNotFound            = 69		// The indicated reader id was never found
					, Reader_BadAutoEncoding             = 70		// The auto encoding enum has an unknown value
					, Reader_CouldNotDecodeFirstLine     = 71		// Could not decode first line of entity: {0}
					, Reader_NelLsepinDecl               = 72		// XMLDecl or TextDecl can not have NEL or lsep: {0}
					, Reader_EOIInMultiSeq               = 73		// End of input was hit in the middle of a multibyte sequence
					, Reader_SrcOfsNotSupported          = 74		// The current transcoding service does not support source offset information
					, Reader_EncodingStrRequired         = 75		// EBCDIC files must provide an encoding= string
					, Scan_CouldNotOpenSource            = 76		// The primary document entity could not be opened. Id={0}
					, Scan_UnbalancedStartEnd            = 77		// Unbalanced start/end tags found, cannot continue
					, Scan_BadPScanToken                 = 78		// The call to scanNext() is illegal at this time
					, Stack_BadIndex                     = 79		// The index is past the top of stack
					, Stack_EmptyStack                   = 80		// The stack is empty, cannot access members
					, Str_ZeroSizedTargetBuf             = 81		// The target buffer cannot have a max size of zero
					, Str_UnknownRadix                   = 82		// The given radix is not supported. Use 2, 8, 10, or 16
					, Str_TargetBufTooSmall              = 83		// The target buffer is too small to accept the results
					, Str_StartIndexPastEnd              = 84		// The start index is past the end of the string
					, Str_ConvertOverflow                = 85		// The represented value overflowed the output binary result
					, Strm_StdErrWriteFailure            = 86		// Could not write to standard err
					, Strm_StdOutWriteFailure            = 87		// Could not write to standard out
					, Strm_ConWriteFailure               = 88		// Could not write to console
					, StrPool_IllegalId                  = 89		// String pool id was not legal
					, Trans_CouldNotCreateDefCvtr        = 90		// Could not create a default transcoder
					, Trans_InvalidSizeReq               = 91		// The maximum size to xlat is larger than the declared block size
					, Trans_Unrepresentable              = 92		// Unicode char 0x{0} is not representable in encoding {1}
					, Trans_NotValidForEncoding          = 93		// Character {0} is not valid for encoding {1}
					, Trans_BadBlockSize                 = 94		// The requested block size is not equal to the size set during construction
					, Trans_BadSrcSeq                    = 95		// An invalid multi-byte source text sequence was encountered
					, Trans_BadSrcCP                     = 96		// {0} is not a valid value for encoding {1}
					, Trans_BadTrailingSurrogate         = 97		// Leading surrogate was not followed by trailing
					, Trans_CantCreateCvtrFor            = 98		// Could not create a converter for encoding: {0}
					, URL_MalformedURL                   = 99		// The URL was not correctly formed
					, URL_UnsupportedProto               = 100		// The URL used an unsupported protocol
					, URL_UnsupportedProto1              = 101		// Unsupported URL protocol: '{0}'
					, URL_OnlyLocalHost                  = 102		// Only localhost is supported at this time
					, URL_NoProtocolPresent              = 103		// No protocol prefix present
					, URL_ExpectingTwoSlashes            = 104		// Expected // after protocol
					, URL_IncorrectEscapedCharRef        = 105		// % must be followed by two hex digits
					, URL_UnterminatedHostComponent      = 106		// Unterminated host component
					, URL_RelativeBaseURL                = 107		// The base part of the URL cannot be relative
					, URL_BaseUnderflow                  = 108		// The base part has too few levels to weave in relative part
					, URL_BadPortField                   = 109		// The port field must be a 16 bit decimal number
					, UTF8_FormatError                   = 110		// invalid byte {0} ({1}) of a {2}-byte sequence.
					, UTF8_Invalid_2BytesSeq             = 111		// invalid byte {0} of 2-byte sequence.
					, UTF8_Invalid_3BytesSeq             = 112		// invalid bytes {0}, {1} of 3-byte sequence.
					, UTF8_Irregular_3BytesSeq           = 113		// irregular bytes {0}, {1} of 3-byte sequence.
					, UTF8_Invalid_4BytesSeq             = 114		// invalid bytes {0}, {1} of 4-byte sequence.
					, UTF8_Exceede_BytesLimit            = 115		// Exceede bytes limits {0}, {1}-byte sequence.
					, Vector_BadIndex                    = 116		// The passed index is past the end of the vector
					, Val_InvalidElemId                  = 117		// The element id was invalid
					, Val_CantHaveIntSS                  = 118		// When reusing the Grammar, no internal subset is allowed
					, XMLRec_UnknownEncoding             = 119		// The passed recognizer encoding was not known
					, Parser_Parse1                      = 120		// Wrong character
					, Parser_Parse2                      = 121		// Invalid reference number
					, Parser_Next1                       = 122		// A character is required after '\' 
					, Parser_Next2                       = 123		// '?' is not expected.  '(?:' or '(?=' or '(?!' or '(?<' or '(?#' or '(?>'?
					, Parser_Next3                       = 124		// '(?<=' or '(?<!' is expected
					, Parser_Next4                       = 125		// A comment is not terminated
					, Parser_Factor1                     = 126		// ')' is expected
					, Parser_Factor2                     = 127		// Unexpected end of the pattern in a modifier group
					, Parser_Factor3                     = 128		// ':' is expected
					, Parser_Factor4                     = 129		// Unexpected end of the pattern in a conditional group
					, Parser_Factor5                     = 130		// A back reference or an anchor or a lookahead or a lookbehind is expected in a conditional pattern
					, Parser_Factor6                     = 131		// There are more than three choices in a conditional group
					, Parser_Atom1                       = 132		// A character in U+0040-U+005f must follow \c
					, Parser_Atom2                       = 133		// A '{' is required before a category character.
					, Parser_Atom3                       = 134		// A property name is not closed by '}'
					, Parser_Atom4                       = 135		// Unexpected meta character
					, Parser_Atom5                       = 136		// Unknown property
					, Parser_CC1                         = 137		// A POSIX character class must be closed by ':]'
					, Parser_CC2                         = 138		// Unexpected end of the pattern in a character class
					, Parser_CC3                         = 139		// Unknown name for a POSIX character class
					, Parser_CC4                         = 140		// '-' is invalid here
					, Parser_CC5                         = 141		// ']' is expected
					, Parser_CC6                         = 142		// '{0}' is not a valid character range; use '\{1}' instead
					, Parser_Ope1                        = 143		// ='[' is expected
					, Parser_Ope2                        = 144		// ')' or '-[' or '+[' or '&[' is expected
					, Parser_Ope3                        = 145		// The range end code point '{0}' is less than the start code point '{1}'
					, Parser_Descape1                    = 146		// Invalid Unicode hex notation
					, Parser_Descape2                    = 147		// Overflow in a hex notation
					, Parser_Descape3                    = 148		// '\ x{' must be closed by '}'
					, Parser_Descape4                    = 149		// Invalid Unicode code point
					, Parser_Descape5                    = 150		// An anchor must not be here
					, Parser_Process1                    = 151		// This expression is not supported in the current option setting
					, Parser_Process2                    = 152		// '{0}' is not a valid character escape
					, Parser_Quantifier1                 = 153		// Invalid quantifier in '{0}'. A digit is expected
					, Parser_Quantifier2                 = 154		// Invalid quantifier in '{0}'. Invalid quantity or a '}' is missing
					, Parser_Quantifier3                 = 155		// Invalid quantifier in '{0}'. A digit or '}' is expexted
					, Parser_Quantifier4                 = 156		// Invalid quantifier in '{0}'. A min quantity must be <= a max quantity
					, Parser_Quantifier5                 = 157		// Invalid quantifier in '{0}'. A quantity value overflow
					, Gen_NoSchemaValidator              = 158		// A schema was seen but the installed validator does not understand schema
					, XUTIL_UnCopyableNodeType           = 159		// The {0} node type is not valid for copy
					, SubGrpComparator_NGR               = 160		// SubstitutionGroupComparator has no grammar resolver
					, FACET_Invalid_Len                  = 161		// Length Value '{0}' is invalid
					, FACET_Invalid_maxLen               = 162		// maxLength Value '{0}' is invalid
					, FACET_Invalid_minLen               = 163		// minLength Value '{0}' is invalid
					, FACET_NonNeg_Len                   = 164		// Length Value '{0}' must be a nonNegativeInteger
					, FACET_NonNeg_maxLen                = 165		// maxLength Value '{0}' must be a nonNegativeInteger
					, FACET_NonNeg_minLen                = 166		// minLength Value '{0}' must be a nonNegativeInteger
					, FACET_Len_maxLen                   = 167		// It is an error for both length and maxLength to be members of facets
					, FACET_Len_minLen                   = 168		// It is an error for both length and minLength to be members of facets
					, FACET_maxLen_minLen                = 169		// Value of maxLength '{0}' must be greater than the value of minLength '{1}'
					, FACET_bool_Pattern                 = 170		// Only constraining facet in boolean datatype is PATTERN
					, FACET_Invalid_Tag                  = 171		// Invalid Facet Tag '{0}'
					, FACET_Len_baseLen                  = 172		// Value of Length '{0}' must be equal to the base Length '{1}'
					, FACET_minLen_baseminLen            = 173		// Value of minLength '{0}' must be greater than or equal to the base minLength '{1}'
					, FACET_minLen_basemaxLen            = 174		// Value of minLength '{0}' must be less than or equal to the base maxLength '{1}'
					, FACET_maxLen_basemaxLen            = 175		// Value of maxLength '{0}' must be less than or equal to the base maxLength '{1}'
					, FACET_maxLen_baseminLen            = 176		// Value of maxLength '{0}' must be greater than or equal to the base minLength '{1}'
					, FACET_Len_baseMinLen               = 177		// Value of Length '{0}' must be greater than or equal to the base minLength '{1}'
					, FACET_Len_baseMaxLen               = 178		// Value of Length '{0}' must be less than or equal to the base maxLength '{1}'
					, FACET_minLen_baseLen               = 179		// Value of minLength '{0}' must be less than or equal to the base Length '{1}'
					, FACET_maxLen_baseLen               = 180		// Value of maxLength '{0}' must be greater than or equal to the base Length '{1}'
					, FACET_enum_base                    = 181		// Value of enumeration = '{0}' must be from the value space of base
					, FACET_Invalid_WS                   = 182		// Value of whitespace '{0}' must be one of 'preserve', 'replace', 'collapse'
					, FACET_WS_collapse                  = 183		// It is an error if whiteSpace = 'preserve' or 'replace' and base.whiteSpace = 'collapse'.
					, FACET_WS_replace                   = 184		// It is an error if whiteSpace = 'preserve' and base.whiteSpace = 'replace'.
					, FACET_Invalid_MaxIncl              = 185		// MaxInclusive '{0}' is invalid
					, FACET_Invalid_MaxExcl              = 186		// MaxExclusive '{0}' is invalid
					, FACET_Invalid_MinIncl              = 187		// MinInclusive '{0}' is invalid
					, FACET_Invalid_MinExcl              = 188		// MinExclusive '{0}' is invalid
					, FACET_Invalid_TotalDigit           = 189		// TotalDigit Value '{0}' is invalid
					, FACET_Invalid_FractDigit           = 190		// FractionDigit Value '{0}' is invalid
					, FACET_PosInt_TotalDigit            = 191		// TotalDigit Value '{0}' must be a PositiveInteger
					, FACET_NonNeg_FractDigit            = 192		// FractionDigit Value '{0}' must be a nonNegativeInteger
					, FACET_max_Incl_Excl                = 193		// It is an error for both maxInclusive and maxExclusive to be specified for the same datatype
					, FACET_min_Incl_Excl                = 194		// It is an error for both minInclusive and minExclusive to be specified for the same datatype
					, FACET_maxExcl_minExcl              = 195		// maxExclusive value '{0}' must be greater than minExclusive value '{1}'
					, FACET_maxExcl_minIncl              = 196		// maxExclusive value '{0}' must be greater than minInclusive value '{1}'
					, FACET_maxIncl_minExcl              = 197		// maxInclusive value '{0}' must be greater than minExclusive value '{1}'
					, FACET_maxIncl_minIncl              = 198		// maxInclusive value '{0}' must be greater than minInclusive value '{1}'
					, FACET_TotDigit_FractDigit          = 199		// TotalDigit value '{0}' must be greater than FractionDigit value '{1}'
					, FACET_maxIncl_base_maxExcl         = 200		// maxInclusive value '{0}' must be less than base's maxExclusive value '{1}'
					, FACET_maxIncl_base_maxIncl         = 201		// maxInclusive value '{0}' must be less than or equal to base's maxInclusive value '{1}'
					, FACET_maxIncl_base_minIncl         = 202		// maxInclusive value '{0}' must be greater than or equal to base's minInclusive value '{1}'
					, FACET_maxIncl_base_minExcl         = 203		// maxInclusive value '{0}' must be greater than base's minExclusive value '{1}'
					, FACET_maxExcl_base_maxExcl         = 204		// maxExclusive value '{0}' must be less than or equal to base's maxExclusive value '{1}'
					, FACET_maxExcl_base_maxIncl         = 205		// maxExclusive value '{0}' must be less than or equal to base's maxInclusive value '{1}'
					, FACET_maxExcl_base_minIncl         = 206		// maxExclusive value '{0}' must be greater than base's minInclusive value '{1}'
					, FACET_maxExcl_base_minExcl         = 207		// maxExclusive value '{0}' must be greater than base's minExclusive value '{1}'
					, FACET_minExcl_base_maxExcl         = 208		// minExclusive value '{0}' must be less than base's maxExclusive value '{1}'
					, FACET_minExcl_base_maxIncl         = 209		// minExclusive value '{0}' must be less than or equal to base's maxInclusive value '{1}'
					, FACET_minExcl_base_minIncl         = 210		// minExclusive value '{0}' must be greater than base's minInclusive value '{1}'
					, FACET_minExcl_base_minExcl         = 211		// minExclusive value '{0}' must be greater than base's minExclusive value '{1}'
					, FACET_minIncl_base_maxExcl         = 212		// minInclusive value '{0}' must be less than base's maxExclusive value '{1}'
					, FACET_minIncl_base_maxIncl         = 213		// minInclusive value '{0}' must be less than or equal to base's maxInclusive value '{1}'
					, FACET_minIncl_base_minIncl         = 214		// minInclusive value '{0}' must be greater than or equal to base's minInclusive value '{1}'
					, FACET_minIncl_base_minExcl         = 215		// minInclusive value '{0}' must be greater than base's minExclusive value '{1}'
					, FACET_maxIncl_notFromBase          = 216		// maxInclusive value '{0}' must be from the base's value space
					, FACET_maxExcl_notFromBase          = 217		// maxExclusive value '{0}' must be from the base's value space
					, FACET_minIncl_notFromBase          = 218		// minInclusive value '{0}' must be from the base's value space
					, FACET_minExcl_notFromBase          = 219		// minExclusive value '{0}' must be from the base's value space
					, FACET_totalDigit_base_totalDigit   = 220		// totalDigit value '{0}' must be less than or equal to base's totalDigit value '{1}'
					, FACET_fractDigit_base_totalDigit   = 221		// fractDigit value '{0}' must be less than or equal to base's totalDigit value '{1}'
					, FACET_fractDigit_base_fractDigit   = 222		// fractDigit value '{0}' must be less than or equal to base's fractDigit value '{1}'
					, FACET_maxIncl_base_fixed           = 223		// maxInclusive '{0}' must be equal to base's maxInclusive '{1}' , fixed
					, FACET_maxExcl_base_fixed           = 224		// maxExclusive '{0}' must be equal to base's maxExclusive '{1}' , fixed
					, FACET_minIncl_base_fixed           = 225		// minInclusive '{0}' must be equal to base's minInclusive '{1}' , fixed
					, FACET_minExcl_base_fixed           = 226		// minExclusive '{0}' must be equal to base's minExclusive '{1}' , fixed
					, FACET_totalDigit_base_fixed        = 227		// totalDigit '{0}' must be equal to base's totalDigit '{1}'  , fixed
					, FACET_fractDigit_base_fixed        = 228		// fractDigit '{0}' must be equal to base's fractDigit '{1}' , fixed
					, FACET_maxLen_base_fixed            = 229		// maxLen '{0}' must be equal to base's maxLen '{1}' , fixed
					, FACET_minLen_base_fixed            = 230		// minLen '{0}' must be equal to base's minLen '{1}' , fixed
					, FACET_len_base_fixed               = 231		// len '{0}' must be equal to base's len '{1}' , fixed
					, FACET_whitespace_base_fixed        = 232		// whitespace '{0}' must be equal to base's whitespace '{1}' , fixed
					, FACET_internalError_fixed          = 233		// internal Error: fixed
					, FACET_List_Null_baseValidator      = 234		// Null base validator in List 
					, FACET_Union_Null_memberTypeValidators   = 235	// Null member type validators in Union 
					, FACET_Union_Null_baseValidator     = 236		// Null base validator in Union
					, FACET_Union_invalid_baseValidatorType   = 237	// Union's base validator's type '{0}' must be union too 
					, VALUE_NotMatch_Pattern             = 238		// Value '{0}' does not match regular expression facet '{1}'
					, VALUE_Not_Base64                   = 239		// Value '{0}' is not encoded in Base64 
					, VALUE_Not_HexBin                   = 240		// Value '{0}' is not encoded in HexBin 
					, VALUE_GT_maxLen                    = 241		// Value '{0}' with length '{1}' exceeds maximum length facet of '{2}' 
					, VALUE_LT_minLen                    = 242		// Value '{0}' with length '{1}' is less than minimum length facet of '{2}' 
					, VALUE_NE_Len                       = 243		// Value '{0}' with length '{1}' is not equal to length facet of '{2}' 
					, VALUE_NotIn_Enumeration            = 244		// Value '{0}' is not in enumeration 
					, VALUE_exceed_totalDigit            = 245		// Value '{0}' with total digits '{1}' exceeds total digit facet of '{2}' 
					, VALUE_exceed_fractDigit            = 246		// Value '{0}' with fraction digits '{1}' exceeds fraction digit facet of '{2}' 
					, VALUE_exceed_maxIncl               = 247		// Value '{0}' must be less than or equal to MaxInclusive '{1}' 
					, VALUE_exceed_maxExcl               = 248		// Value '{0}' must be less than MaxExclusive '{1}' 
					, VALUE_exceed_minIncl               = 249		// Value '{0}' must be greater than or equal to MinInclusive '{1}' 
					, VALUE_exceed_minExcl               = 250		// Value '{0}' must be greater than MinExclusive '{1}' 
					, VALUE_WS_replaced                  = 251		// Value '{0}' is not whitespace replaced 
					, VALUE_WS_collapsed                 = 252		// Value '{0}' is not a whitespace collapsed 
					, VALUE_Invalid_NCName               = 253		// Value '{0}' is not valid NCName 
					, VALUE_Invalid_Name                 = 254		// Value '{0}' is not valid Name 
					, VALUE_ID_Not_Unique                = 255		// ID '{0}' is not unique 
					, VALUE_ENTITY_Invalid               = 256		// Value '{0}' is not valid ENTITY 
					, VALUE_QName_Invalid                = 257		// Value '{0}' is not valid QName 
					, VALUE_NOTATION_Invalid             = 258		// NOTATION '{0}' must be a valid QName 
					, VALUE_no_match_memberType          = 259		// Value '{0}' does not match any member types (of the union) 
					, VALUE_URI_Malformed                = 260		// Value '{0}' is NOT a valid URI 
					, XMLNUM_emptyString                 = 261		//  Empty string encountered.
					, XMLNUM_WSString                    = 262		//  String contains whitespaces only.
					, XMLNUM_2ManyDecPoint               = 263		//  More than one decimal points encountered.
					, XMLNUM_Inv_chars                   = 264		//  Invalid chars encountered.
					, XMLNUM_null_ptr                    = 265		//  Null pointer encountered.
					, XMLNUM_URI_Component_Empty         = 266		//  Cannot construct URI with null/empty '{0}' 
					, XMLNUM_URI_Component_for_GenURI_Only   = 267	//  '{0}', '{1}' can only be set for a generic URI! 
					, XMLNUM_URI_Component_Invalid_EscapeSequence   //  '{0}' contains invalid escape sequence '{1}'= 268
					, XMLNUM_URI_Component_Invalid_Char   = 269		//  '{0}' contains invalid char '{1}'
					, XMLNUM_URI_Component_Set_Null      = 270		//  '{0}' can not be set to null 
					, XMLNUM_URI_Component_Not_Conformant   = 271	//  '{0}' is NOT conformance '{1}' 
					, XMLNUM_URI_No_Scheme               = 272		//  No scheme found in URI
					, XMLNUM_URI_NullHost                = 273		//  '{0}', '{1}' may not be specified if host is not specified 
					, XMLNUM_URI_NullPath                = 274		//  '{0}', '{1}' may not be specified if path is not specified 
					, XMLNUM_URI_Component_inPath        = 275		//  '{0}', '{1}' cannot be specified in path
					, XMLNUM_URI_PortNo_Invalid          = 276		//  Port no '{0}' shall be in (0, 65535) 
					, XMLNUM_DBL_FLT_maxNeg              = 277		//  Value '{0}' shall be greater than the max Negative value '{1}' 
					, XMLNUM_DBL_FLT_maxPos              = 278		//  Value '{0}' shall be less than the max Negative value '{1}' 
					, XMLNUM_DBL_FLT_minNegPos           = 279		//  Value '{0}' shall be in the range of '{1}', '{2}' 
					, XMLNUM_DBL_FLT_InvalidType         = 280		//  Type '{0}' is invalid: internal error 
					, XMLNUM_DBL_FLT_No_Exponent         = 281		//  Value '{0}' shall have exponent. 
					, Regex_Result_Not_Set               = 282		// A result is not set.
					, Regex_CompactRangesError           = 283		// CompactRanges - Internal Error
					, Regex_MergeRangesTypeMismatch      = 284		// Merge Ranges - Mismatched type
					, Regex_SubtractRangesError          = 285		// SubtractRanges - Internal Error
					, Regex_IntersectRangesError         = 286		// IntersectRanges - Internal Error
					, Regex_ComplementRangesInvalidArg   = 287		// ComplementRanges - Argument must be a RangeToken
					, Regex_InvalidCategoryName          = 288		// Invalid category name: {0}
					, Regex_KeywordNotFound              = 289		// Keyword '{0}' not found
					, Regex_BadRefNo                     = 290		// Reference no must be more than zero
					, Regex_UnknownOption                = 291		// Unknown option: {0}
					, Regex_UnknownTokenType             = 292		// Unknown token type
					, Regex_RangeTokenGetError           = 293		// Failed to get RangeToken for: {0}
					, Regex_NotSupported                 = 294		// Not supported
					, Regex_InvalidChildIndex            = 295		// Invalid child index
					, Regex_RepPatMatchesZeroString      = 296		// Replace pattern cannot match zero length string
					, Regex_InvalidRepPattern            = 297		// Invalid replace pattern
					, NEL_RepeatedCalls                  = 298		// Enabling the NEL option can only be called once per process.
					, RethrowError                       = 299		// {0}
					, Out_Of_Memory                      = 300		// operator new fails.  Possibly running Of memory
					, DV_InvalidOperation                = 301		// Operation is not allowed
					, XPath_NoAttrSelector               = 302		// Selectors cannot select attributes
					, XPath_NoUnionAtStart               = 303		// Not allowed to have '|' at the beginning of an xpath value
					, XPath_NoMultipleUnion              = 304		// Not allowed to have '||' in an xpath value
					, XPath_MissingAttr                  = 305		// Missing attribute name in xpath
					, XPath_ExpectedToken1               = 306		// Expected xpath token 'NAMETEST_QNAME' or 'NAMETEST_ANY' or 'NAMETEST_NAMESPACE'
					, XPath_PrefixNoURI                  = 307		// Prefix '{0}' not bound to namespace URI in an xpath value
					, XPath_NoDoubleColon                = 308		// Not allowed to have double colon in the xpath expression
					, XPath_ExpectedStep1                = 309		// Expected step following token 'AXISNAME_CHILD::'
					, XPath_ExpectedStep2                = 310		// Expected step following '//' in xpath
					, XPath_ExpectedStep3                = 311		// Expected step following '/' in xpath
					, XPath_NoForwardSlash               = 312		// '/' not allowed after '//' in xpath
					, XPath_NoDoubleForwardSlash         = 313		// '//' only allowed after '.' at the beginning of an xpath
					, XPath_NoForwardSlashAtStart        = 314		// Not allowed to have '/' at the beginning of an xpath value
					, XPath_NoSelectionOfRoot            = 315		// Not allowed to select the root of an xpath
					, XPath_EmptyExpr                    = 316		// Empty xpath expression
					, XPath_NoUnionAtEnd                 = 317		// The xpath expression cannot end with '|'
					, XPath_InvalidChar                  = 318		// Invalid character following '.' in xpath
					, XPath_TokenNotSupported            = 319		// XPath token not supported
					, XPath_FindSolution                 = 320		// Find a solution!
					, DateTime_Assert_Buffer_Fail        = 321		// buffer not initialized yet!
					, DateTime_dt_missingT               = 322		// 'T' is missing! '{0}' 
					, DateTime_gDay_invalid              = 323		// invalid gDay! '{0}' 
					, DateTime_gMth_invalid              = 324		// invalid gMonth! '{0}' 
					, DateTime_gMthDay_invalid           = 325		// invalid gMonthDay! '{0}' 
					, DateTime_dur_Start_dashP           = 326		// Duration shall start with '-' or 'P'! '{0}' 
					, DateTime_dur_noP                   = 327		// Duration shall always have 'P'! '{0}' 
					, DateTime_dur_DashNotFirst          = 328		// '-' can only appear at first! '{0}' 
					, DateTime_dur_inv_b4T               = 329		// Duration has invalid stuff before 'T'! '{0}' 
					, DateTime_dur_NoTimeAfterT          = 330		// Duration has no time elements after 'T'! '{0}' 
					, DateTime_dur_NoElementAtAll        = 331		// Duration shall have at least element ! '{0}' 
					, DateTime_dur_inv_seconds           = 332		// Duration shall have at least one digit after the . ! '{0}' 
					, DateTime_date_incomplete           = 333		// Incomplete Date ! '{0}' 
					, DateTime_date_invalid              = 334		// Invalid Date ! '{0}' 
					, DateTime_time_incomplete           = 335		// Incomplete Time ! '{0}' 
					, DateTime_time_invalid              = 336		// Invalid Time ! '{0}' 
					, DateTime_ms_noDigit                = 337		// ms shall be present once '.' is present ! '{0}' 
					, DateTime_ym_incomplete             = 338		// Incomplete YearMonth! '{0}' 
					, DateTime_ym_invalid                = 339		// Year separator is missing or misplaced ! '{0}' 
					, DateTime_year_tooShort             = 340		// Year must have 'CCYY' format ! '{0}' 
					, DateTime_year_leadingZero          = 341		// Invalid leading zero in year! '{0}' 
					, DateTime_ym_noMonth                = 342		// no month in YearMonth ! '{0}' 
					, DateTime_tz_noUTCsign              = 343		// TimeZone is expected ! '{0}' 
					, DateTime_tz_stuffAfterZ            = 344		// Expecting nothing after 'Z'! '{0}' 
					, DateTime_tz_invalid                = 345		// Invalid TimeZone! '{0}' 
					, DateTime_year_zero                 = 346		// The year (0000) is an illegal year value! '{0}' 
					, DateTime_mth_invalid               = 347		// The month must have values 1 to 12! '{0}' 
					, DateTime_day_invalid               = 348		// The day must have values 1 to 31! '{0}' 
					, DateTime_hour_invalid              = 349		// Hour must have values 0-23! '{0}' 
					, DateTime_min_invalid               = 350		// Minute must have values 0-59! '{0}' 
					, DateTime_second_invalid            = 351		// Second must have values 0-60! '{0}' 
					, DateTime_tz_hh_invalid             = 352		// Minute must have values 0-59! '{0}' 
					, PD_EmptyBase                       = 353		// Particle Derivation Restriction: The derived complexType has content, while base is empty.
					, PD_NSCompat1                       = 354		// NSCompat: The namespace of '{0}' is not allowed by wildcard in base
					, PD_OccurRangeE                     = 355		// The occurrence range of '{0}' is not a valid restriction of base element's range
					, PD_NameTypeOK1                     = 356		// NameAndTypeOK: The Element name/uri in restriction does not match that of corresponding base element
					, PD_NameTypeOK2                     = 357		// NameAndTypeOK: Element '{0}' is nillable in the restriction, while it's not in the base
					, PD_NameTypeOK3                     = 358		// NameAndTypeOK: Element '{0}' is either not fixed, or is not fixed with the same value as in the base
					, PD_NameTypeOK4                     = 359		// NameAndTypeOK: The disallowed substitutions, for element '{0}', are not a superset of those of the base element
					, PD_NameTypeOK5                     = 360		// NameAndTypeOK: Element '{0}' has a type that does not derive from that of the base
					, PD_NameTypeOK6                     = 361		// NameAndTypeOK: Derived element '{0}' has fewer Identity Constraints than base element '{1}'
					, PD_NameTypeOK7                     = 362		// NameAndTypeOK: Derived element '{0}' has an Identity Constraint that does not appear on base element '{1}'
					, PD_RecurseAsIfGroup                = 363		// RecurseAsIfGroup: Element '{0}' belongs to a group of a variety different from that of the base
					, PD_Recurse1                        = 364		// Occurrence range of group is not a valid restriction of occurrence range of base group
					, PD_Recurse2                        = 365		// Recurse: There is not a complete functional mapping between the particles
					, PD_ForbiddenRes1                   = 366		// Forbidden restriction of 'any': Choice,Seq,All,Elt
					, PD_ForbiddenRes2                   = 367		// Forbidden restriction of 'all': Choice,Seq,Elt
					, PD_ForbiddenRes3                   = 368		// Forbidden restriction of 'choice': All,Seq,Leaf
					, PD_ForbiddenRes4                   = 369		// Forbidden restriction of 'sequence': Elt
					, PD_NSSubset1                       = 370		// Wildcard's occurrence range not a restriction of base wildcard's range
					, PD_NSSubset2                       = 371		// Wildcard is not a subset of corresponding wildcard in base
					, PD_NSRecurseCheckCardinality1      = 372		// Group's occurrence range not a restriction of base wildcard's range
					, PD_RecurseUnordered                = 373		// RecurseUnordered: There is not a complete functional mapping between the particles
					, PD_MapAndSum                       = 374		// MapAndSum: There is not a complete functional mapping between the particles
					, PD_InvalidContentType              = 375		// Particle derivation: Invalid content spec node type
					, NodeIDMap_GrowErr                  = 376		// NodeIDMap overflows and exceeds the largest available size
					, XSer_ProtoType_Null_ClassName      = 377		// ProtoType has null class name
					, XSer_ProtoType_NameLen_Dif         = 378		// ProtoType name length diff '{0}' vs '{1}'
					, XSer_ProtoType_Name_Dif            = 379		// ProtoType name diff '{0}' vs '{1}'
					, XSer_InStream_Read_LT_Req          = 380		// InputStream read '{0}' less than required '{1}'
					, XSer_InStream_Read_OverFlow        = 381		// InputStream read '{0}' beyond buffer available '{1}'
					, XSer_Storing_Violation             = 382		// Storing violation
					, XSer_StoreBuffer_Violation         = 383		// Store buffer violation '{0}', '{1}'
					, XSer_LoadPool_UppBnd_Exceed        = 384		// Object Tag '{0}' exceed load pool uppper Boundary '{1}'
					, XSer_LoadPool_NoTally_ObjCnt       = 385		// Load pool size '{0}' not tally with object count '{1}'
					, XSer_Loading_Violation             = 386		// Loading violation
					, XSer_LoadBuffer_Violation          = 387		// Load buffer violation '{0}', '{1}'
					, XSer_Inv_ClassIndex                = 388		// Invalid class index '{0}', '{1}'
					, XSer_Inv_FillBuffer_Size           = 389		// Invalid fillBuffer size '{0}', '{1}'
					, XSer_Inv_checkFillBuffer_Size      = 390		// Invalid checkFillBuffer size '{0}'
					, XSer_Inv_checkFlushBuffer_Size     = 391		// Invalid checkFlushBuffer size '{0}'
					, XSer_Inv_Null_Pointer              = 392		// Invalid null pointer encountered '{0}'
					, XSer_Inv_Buffer_Len                = 393		// Invalid buffer length '{0}'
					, XSer_CreateObject_Fail             = 394		// CreateObject fails 
					, XSer_ObjCount_UppBnd_Exceed        = 395		// Object count '{0}' exceed upper boundary '{1}'
					, XSer_GrammarPool_Locked            = 396		// Grammar Pool is locked by other party
					, XSer_GrammarPool_Empty             = 397		// Grammar Pool is empty
					, XSer_GrammarPool_NotEmpty          = 398		// Grammar Pool is NOT empty
					, XSer_StringPool_NotEmpty           = 399		// String Pool is NOT empty
					, XSer_BinaryData_Version_NotSupported   = 400	// Binary Data Version '{0}','{1}','{2}' not supported 
				};
			}
		};
	}
}


















































































































































































































































































































