#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		namespace InteractiveVGMObject
		{
			struct VertexRange
			{
				VertexRange(size_t begin, size_t end)
				{
					fBegin = begin;
					fEnd = end;
				}

				size_t fBegin;
				size_t fEnd;
			};

			struct EdgeGraphics
			{
				EdgeGraphics()
				{
					fColor = WorldPt3(-.3, -.3, -.3);
					fPixelFactor = 1;
				}

				WorldPt3 fColor;
				float fPixelFactor;
			};

			struct VertexGraphics
			{
				VertexGraphics()
				{
					fColor = WorldPt3(.1, .1, 0);
					fPixelFactor = 1;
				}

				WorldPt3 fColor;
				float fPixelFactor;
			};

			struct CageSelection
			{
				CageSelection()
				{
					fNumVertices = 0;
					fPt0 = WorldPt3(0, 0, 0);
					fPt1 = WorldPt3(0, 0, 0);
					fPt2 = WorldPt3(0, 0, 0);
					fColor = WorldPt3(1.0, 1.0, 1.0);
					fPixelFactor = 1.0;
					fDistance = 100.0;
				}
				int fNumVertices;
				WorldPt3 fPt0;
				WorldPt3 fPt1;
				WorldPt3 fPt2;
				WorldPt3 fColor;
				float fPixelFactor;
				float fDistance;
			};


			// client creates the implementation of this interface
			class IDeformMeshExternalData
			{
			public:
				virtual ~IDeformMeshExternalData() {}
				// feed the object id to VGM. Always called first after EndEdit() is called.
				virtual bool ObjectId(size_t*& objectId) = 0;

				virtual bool NumVertices(uint32_t& numVertices) = 0;
				virtual bool VertexPosition(uint32_t index, WorldPt3& position) = 0;
				virtual bool VertexNormal(uint32_t index, WorldPt3& normal) = 0;

				virtual bool NumTriangles(uint32_t& numTriangles) = 0;
				virtual bool VertexIndex(uint32_t index, uint32_t& vertexIndex) = 0;

				virtual bool Color(WorldPt3& color, float& opacity) { return false; }
			};

			// ---------------------------------------------------------------------------------------------------
			static const VWIID IID_DeformMesh = { 0x7cee8841, 0x9669, 0x436a, {0xb7, 0xd5, 0xcc, 0xd2, 0x49, 0x50, 0xd0, 0x0a} };

			class DYNAMIC_ATTRIBUTE IDeformMesh : public IEventSink
			{
			public:
				virtual void VCOM_CALLTYPE SetExternalDataCallback(IDeformMeshExternalData* data) = 0;

				virtual bool VCOM_CALLTYPE BeginEdit() = 0;
				virtual bool VCOM_CALLTYPE EndEdit() = 0;

				virtual bool VCOM_CALLTYPE EditVertices(const VertexRange& range) = 0;
				virtual bool VCOM_CALLTYPE EditEdgeGraphics(const EdgeGraphics& edge) = 0;
				virtual bool VCOM_CALLTYPE EditTransform(TransformMatrix& transform) = 0;
				virtual bool VCOM_CALLTYPE EditVertexGraphics(const VertexGraphics& vertGraphics) = 0;
				virtual bool VCOM_CALLTYPE EditCageAlpha(float alpha) = 0;
				virtual bool VCOM_CALLTYPE EditCageSelection(const CageSelection& cageSelection) = 0;
				virtual bool VCOM_CALLTYPE EditVertexWeightColors(const std::array<WorldPt3, 10>& colors) = 0;
				virtual bool VCOM_CALLTYPE EditVertexWeightPixelFactors(const std::array<float, 10>& factors) = 0;
			};
		}
	}
}
