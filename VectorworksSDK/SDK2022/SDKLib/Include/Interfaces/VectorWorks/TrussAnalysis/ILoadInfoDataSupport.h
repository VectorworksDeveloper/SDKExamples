//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace TrussAnalysis
	{
		// ----------------------------------------------------------------------------------------------------
		struct SLoadInstData : public VectorWorks::Extension::SLoadData
		{
			struct	SLoadPoint
			{
				WorldPt3	fLoadPoint;
				bool		fDestributedLoadStartPoint;

				SLoadPoint()	{}
				SLoadPoint(WorldPt3 point, bool isStartPt = true)
					: fLoadPoint( point )
					, fDestributedLoadStartPoint( isStartPt )
				{ }
			};
			typedef	std::vector<SLoadPoint>	TLoadPointsArr;
			TLoadPointsArr	farrLoadPoints;
		};

		// ----------------------------------------------------------------------------------------------------
		// {0CE2CDC0-90B3-4ECA-9D0A-4B0E0A821536}
		static const VWIID IID_LoadInfoDataSupport	= { 0xce2cdc0, 0x90b3, 0x4eca, { 0x9d, 0xa, 0x4b, 0xe, 0xa, 0x82, 0x15, 0x36 } };


		class DYNAMIC_ATTRIBUTE ILoadInfoDataSupport : public IVWSingletonUnknown
		{
		
		public:
			virtual bool			VCOM_CALLTYPE HasLoadData(const TXString& univName) = 0;
			virtual bool			VCOM_CALLTYPE LoadObject(const TXString& univName) = 0;

			virtual bool			VCOM_CALLTYPE HasLoadData(MCObjectHandle object) = 0;
			virtual bool			VCOM_CALLTYPE LoadObject(MCObjectHandle object) = 0;

			virtual bool			VCOM_CALLTYPE SaveObject() = 0;
			
			virtual void			VCOM_CALLTYPE Clear() = 0;

			virtual void			VCOM_CALLTYPE CopyLoadDataFrom(MCObjectHandle object) = 0;

			virtual size_t			VCOM_CALLTYPE GetLoadsCount() const = 0;
			
			virtual size_t			VCOM_CALLTYPE AddLoadData(const VectorWorks::Extension::SLoadData& data) = 0; 
			virtual size_t			VCOM_CALLTYPE AddLoadData(const SLoadInstData& data) = 0; 
			virtual SLoadInstData	VCOM_CALLTYPE GetLoadData(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadData(const VectorWorks::Extension::SLoadData& data, size_t itemIndex = 0) = 0;
			virtual void			VCOM_CALLTYPE SetLoadData(const SLoadInstData& data, size_t itemIndex = 0) = 0;
			virtual	void			VCOM_CALLTYPE RemoveLoadData(size_t itemIndex = 0) = 0;

			virtual SLoadInstData::ELoadType	VCOM_CALLTYPE GetLoadType(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadType(SLoadInstData::ELoadType loadType, size_t itemIndex) = 0;
			virtual bool			VCOM_CALLTYPE IsIncludedInCalculations(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetIsIncludedInCalculations(bool include, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetGroupName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetGroupName(const TXString& name, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetLoadID(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadID(const TXString& loadID, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetLoadIDParamName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadIDParamName(const TXString& paramName, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetLoadName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadName(const TXString& loadName, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetLoadNameParamName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadNameParamName(const TXString& paramName, size_t itemIndex = 0) = 0;
			virtual double			VCOM_CALLTYPE GetWeigth(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetWeigth(double weight, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetWeightParamName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetWeightParamName(const TXString& paramName, size_t itemIndex = 0) = 0;
			virtual TXString		VCOM_CALLTYPE GetTotalDistWeightParamName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetTotalDistWeightParamName(const TXString& paramName, size_t itemIndex = 0) = 0;
			virtual void			VCOM_CALLTYPE GetLoadHangPoints(SLoadInstData::TLoadPointsArr& outHangPoints, size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE GetLoadHangPointsModel
										(SLoadInstData::TLoadPointsArr& outHangPoints, bool includeHangOffset, size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetLoadHangPoints(const SLoadInstData::TLoadPointsArr& localHangPoints, size_t itemIndex = 0) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE FindHangingPositionToAttach(size_t itemIndex = 0) = 0;

			// VW 2019
			virtual MCObjectHandle	VCOM_CALLTYPE GetHangingPosition(size_t itemIndex = 0) const = 0;
			virtual WorldPt3		VCOM_CALLTYPE GetHangOffsetModel(size_t itemIndex = 0) const = 0;
			virtual bool			VCOM_CALLTYPE DoHandlePositionTransform(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetDoHandlePositionTransform(bool handleTransform, size_t itemIndex = 0) = 0;
			virtual TransformMatrix	VCOM_CALLTYPE GetPositionTransform(size_t itemIndex = 0) const = 0;
			virtual size_t			VCOM_CALLTYPE FindLoadIndexClosestToPoint(const WorldPt3& inPoint, WorldPt3& outPointOnLoad) const = 0;

			// VW 2021
			virtual bool			VCOM_CALLTYPE IsWeightWidgetEnabled(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetWeightWidgetEnabled(bool isEnabled, size_t itemIndex = 0) = 0;

			// VW 2022
			virtual TXString		VCOM_CALLTYPE GetPositionParamName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetPositionParamName(const TXString& positionParamName, size_t itemIndex = 0) = 0;
			
			virtual TXString		VCOM_CALLTYPE GetPositionName(size_t itemIndex = 0) const = 0;
			virtual void			VCOM_CALLTYPE SetPositionName(const TXString& positionParamName, size_t itemIndex = 0) = 0;

		};
		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<ILoadInfoDataSupport>		ILoadInfoDataSupportPtr;
	}
}
