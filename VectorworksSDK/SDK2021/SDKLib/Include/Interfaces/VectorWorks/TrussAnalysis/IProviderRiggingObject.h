//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace TrussAnalysis
	{
		enum class ERiggingObjectType
		{
			TrussLine	= 0,
			TrussCorner	= 1,
			TrussCircle	= 2,
			PipeElement	= 3,
		};

		struct SRiggingLine
		{
			WorldPt3	fStartPoint;
			WorldPt3	fEndPoint;
		};
		typedef	std::vector<SRiggingLine>	TRiggingLinesArr;

		// ----------------------------------------------------------------------------------------------------
		// {284BCDB4-942C-4E14-B8B0-EDD90A9BFC1A}
		static const Extension::TSinkIID	IID_ProviderRiggingObject	= { 0x284bcdb4, 0x942c, 0x4e14, { 0xb8, 0xb0, 0xed, 0xd9, 0xa, 0x9b, 0xfc, 0x1a } };

		class DYNAMIC_ATTRIBUTE IProviderRiggingObject : public Extension::IEventSink
		{
		public:
			virtual bool					VCOM_CALLTYPE Init(MCObjectHandle riggingObj) = 0;

			virtual	TXString				VCOM_CALLTYPE GetName() const = 0;
			virtual	void					VCOM_CALLTYPE SetName(const TXString& name) = 0;
			virtual	TXString				VCOM_CALLTYPE GetID() const = 0;
			virtual	void					VCOM_CALLTYPE SetID(const TXString& ID) = 0;

			virtual ERiggingObjectType		VCOM_CALLTYPE GetType() const = 0;

			virtual bool					VCOM_CALLTYPE GetLines(TRiggingLinesArr& outRiggingLines) const { return false; }
			virtual bool					VCOM_CALLTYPE GetCircle(double& outRadius, double& outArcAngle) const { return false; }

			virtual TXString				VCOM_CALLTYPE GetCrossSection() const = 0;
			virtual void					VCOM_CALLTYPE SetCrossSection(const TXString& crossSection) = 0;
			virtual double					VCOM_CALLTYPE GetDistributedWeight() const = 0;
			virtual void					VCOM_CALLTYPE SetDistributedWeight(double distributedWeight) = 0;
			virtual double					VCOM_CALLTYPE GetWidth() const = 0;
			virtual void					VCOM_CALLTYPE SetWidth(double width) = 0;
			virtual double					VCOM_CALLTYPE GetHeight() const = 0;
			virtual void					VCOM_CALLTYPE SetHeight(double height) = 0;

			virtual bool					VCOM_CALLTYPE DrawSchematicGeometry(EViewTypes view) = 0;
		};
		typedef Extension::VCOMSinkPtr<IProviderRiggingObject>		IProviderRiggingObjectPtr;

		// ----------------------------------------------------------------------------------------------------
		// {E61CC50F-DA74-4EF1-9C6E-AA890FEF71B3}
		static const VWIID	IID_RiggingObjectHangingSupport	= { 0xe61cc50f, 0xda74, 0x4ef1, { 0x9c, 0x6e, 0xaa, 0x89, 0xf, 0xef, 0x71, 0xb3 } };

		class DYNAMIC_ATTRIBUTE IRiggingObjectHangingSupport : public IVWSingletonUnknown
		{
		public:
			virtual bool			VCOM_CALLTYPE Init(MCObjectHandle riggingObj) = 0;

			virtual size_t			VCOM_CALLTYPE GetHangedLoadsCount() const = 0;

			virtual size_t			VCOM_CALLTYPE AddHangObject(MCObjectHandle hangObject, size_t loadIndex = 0) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE GetHangedObjectAt(size_t itemIndex, size_t& outLoadIndex) const = 0;
			virtual size_t			VCOM_CALLTYPE GetHangedObjectIndex(MCObjectHandle hangObject, size_t loadIndex = size_t(-1) ) const = 0;
			virtual bool			VCOM_CALLTYPE RemoveHangedObject(MCObjectHandle hangObject, size_t loadIndex ) = 0;
			virtual void			VCOM_CALLTYPE RemoveHangedObjectAt(size_t itemIndex) = 0;
		};
		typedef VCOMPtr<IRiggingObjectHangingSupport>		IRiggingObjectHangingSupportPtr;
	}
}
