//
//  VWMaterialObj.h
//  Import mtextur
//
//  Created by Samuel Kowalsky on 10.12.20.
//

#pragma once

namespace VWFC
{
    namespace VWObjects
    {
        enum class EMaterialPhysicalProperty
        {
            SpecificGravity,        // Unitless
            ModulusOfElasticity,    // kN/mm^2
            YieldStrength,          // kN/mm^2
            TensileStrength,        // kN/mm^2
            SpecificHeat,           // kJ/kg.K
            Emissivity,             // Unitless
            Albedo,                 // Unitless
            ThermalExpCoeff,        // 1/K
            Lambda,                 // W/m.K
            EmbodiedCarbon,         // ECO2
            SoundVelocity,          // m/s
            Density,                // kg/m^3
            AcousticImpedance,      // Pa.s/m^3
            SlipResistance,         // Unitless
        };

        class VWMaterialObj : public VWObject
        {
        // constructors, destructors, operators
        public:
            VWMaterialObj(const TXString& name, bool isSimpleMaterial = true);
            VWMaterialObj(MCObjectHandle hMaterial);
            VWMaterialObj(const VWMaterialObj& source);
            ~VWMaterialObj();
            
            VWMaterialObj& operator=(const VWMaterialObj& source);
            
        // public methods basic
        public:
            InternalIndex GetMaterialRef() const;
            
            TXString GetMaterialName();
            void SetMaterialName(const TXString& name);
            
            bool IsSimpleMaterial();
            
            InternalIndex GetMaterialTexture();
            bool SetMaterialTexture(InternalIndex textureIndex);
            
            InternalIndex GetMaterialFillStyle();
            void SetMaterialFillStyle(InternalIndex fillStyle);
            
            bool IsMaterialFillStyleByClass();
            void SetMaterialFillStyleByClass(bool byClass);
            
            ObjectColorType GetMaterialFillColor();
            void SetMaterialFillColor(ObjectColorType& fillColors);
            
        // public methods object variables
        public:
            TXString GetOvDescription();
            void SetOvDescription(TXString description);
            
            TXString GetOvMark();
            void SetOvMark(TXString mark);
            
            TXString GetOvKeynote();
            void SetOvKeynote(TXString keynote);
            
            // Construction
            bool GetOvIsVolumetric();
            void SetOvIsVolumetric(bool isVolumetric);
            
            bool GetOvIsSurfaceAreaMeasure();
            void SetOvIsSurfaceAreaMeasure(bool isSurfaceAreaMeasure);
            
            TXString GetOvCategory();
            void SetOvCategory(TXString category);
            
            TXString GetOvStandard();
            void SetOvStandard(TXString standard);
            
            TXString GetOvReferenceId();
            void SetOvReferenceId(TXString referenceId);
            
            TXString GetOvClassificationDescription();
            void SetOvClassificationDescription(TXString description);
            
            TXString GetOvManufacturer();
            void SetOvManufacturer(TXString manufacturer);
            
            TXString GetOvProductModel();
            void SetOvProductModel(TXString manufacturer);
            
            TXString GetOvProductName();
            void SetOvProductName(TXString productName);
            
            TXString GetOvProductDescription();
            void SetOvProductDescription(TXString productDescription);
            
            TXString GetOvProductUrl();
            void SetOvProductUrl(TXString productUrl);
            
            TXString GetOvProductSource();
            void SetOvProductSource(TXString productSource);
            
            TXString GetOvProductFinish();
            void SetOvProductFinish(TXString productFinish);
            
            double GetOvProductCost();
            void SetOvProductCost(double productCost);
            
            // Physical Variables

            // Sets outValue to the value of the passed physical property in base units.
            // See EMaterialPhysicalProperty for a list of the units used.
            // Returns false if the material does not have the passed property.
            bool GetPhysicalProperty(EMaterialPhysicalProperty property, double& outValue);

            // Sets outValue to the value of the passed physical property (for simple materials)
            // or the weighted average of the property of all submaterials (for compound materials) in base units.
            // See EMaterialPhysicalProperty for a list of the units used.
            // Returns false if the material or any of its submaterials do not have the passed property.
            bool GetAveragePhysicalProperty(EMaterialPhysicalProperty property, double& outValue);

            // Sets the value of the passed physical property in base units.
            // See EMaterialPhysicalProperty for a list of the units used.
            void SetPhysicalProperty(EMaterialPhysicalProperty property, double value, bool updateUse=true);
            
            // The getters for physical variables below return values in document units.

            double GetOvSpecificGravity();
            void SetOvSpecificGravity(double specificGravity, bool updateUse=true);
            
            double GetOvModulusOfElasticity();
            void SetOvModulusOfElasticity(double modulusOfElasticity, bool updateUse=true);
            
            double GetOvYieldStrength();
            void SetOvYieldStrength(double yieldStrength, bool updateUse=true);
            
            double GetOvTensileStrength();
            void SetOvTensileStrength(double tensileStrength, bool updateUse=true);
            
            double GetOvSpecificHeat();
            void SetOvSpecificHeat(double specificHeat, bool updateUse=true);
            
            double GetOvEmissivity();
            void SetOvEmissivity(double emissivity, bool updateUse=true);
            
            double GetOvAlbedo();
            void SetOvAlbedo(double albedo, bool updateUse=true);
            
            double GetOvThermalExpCoeff();
            void SetOvThermalExpCoeff(double thermalExpansionCoefficient, bool updateUse=true);
            
            double GetOvLambda();
            void SetOvLambda(double lambda, bool updateUse=true);
            
            double GetOvEmbodiedCarbon();
            void SetOvEmbodiedCarbon(double embodiedCarbon, bool updateUse=true);
            
            double GetOvSoundVelocity();
            void SetOvSoundVelocity(double soundVelocity, bool updateUse=true);
            
            // Returns the material density in the current document density units.
            // Result is valid only if GetOvUsesDensity() returns true.
            double GetOvDensity();

            // Sets the material density in metric units (kg/m^3).
            void SetOvDensity(double density, bool updateUse=true);
            
            double GetOvAcousticImpedance();
            void SetOvAcousticImpedance(double acousticImpedance, bool updateUse=true);
            
            double GetOvSlipResistance();
            void SetOvSlipResistance(double slipResistance, bool updateUse=true);
            
            // Physical Use Variables
            bool GetOvUsesSpecificGravity();
            void SetOvUsesSpecificGravity(bool usesSpecificGravity);
            
            bool GetOvUsesModulusOfElasticity();
            void SetOvUsesModulusOfElasticity(bool usesModulusOfElasticity);
            
            bool GetOvUsesYieldStrength();
            void SetOvUsesYieldStrength(bool usesYieldStrength);
            
            bool GetOvUsesTensileStrength();
            void SetOvUsesTensileStrength(bool usesTensileStrength);
            
            bool GetOvUsesSpecificHeat();
            void SetOvUsesSpecificHeat(bool usesSpecificHeat);
            
            bool GetOvUsesEmissivity();
            void SetOvUsesEmissivity(bool usesEmissivity);
            
            bool GetOvUsesAlbedo();
            void SetOvUsesAlbedo(bool usesAlbedo);
            
            bool GetOvUsesThermalExpCoeff();
            void SetOvUsesThermalExpCoeff(bool usesThermalExpansionCoefficient);
            
            bool GetOvUsesLambda();
            void SetOvUsesLambda(bool usesLambda);
            
            bool GetOvUsesEmbodiedCarbon();
            void SetOvUsesEmbodiedCarbon(bool usesEmbodiedCarbon);
            
            bool GetOvUsesSoundVelocity();
            void SetOvUsesSoundVelocity(bool usesSoundVelocity);
            
            bool GetOvUsesDensity();
            void SetOvUsesDensity(bool usesDensity);
            
            bool GetOvUsesAcousticImpedance();
            void SetOvUsesAcousticImpedance(bool usesAcousticImpedance);
            
            bool GetOvUsesSlipResistance();
            void SetOvUsesSlipResistance(bool usesSlipResistance);

			// Returns the material density for simple materials or average density of all submaterials for compound materials.
            // The result will be in the current document density units.
			bool GetAverageDensity(double& outDensity);
            
        // static
        public:
            static bool IsMaterialObject(MCObjectConstHandle hObject);
            static bool IsMaterialObject(InternalIndex index);
        };
    }
}
