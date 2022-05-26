//
//  VWMaterialObj.cpp
//  Import mtextur
//
//  Created by Samuel Kowalsky on 10.12.20.
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

// MARK: - Constructors, Destructors, Operators

VWMaterialObj::VWMaterialObj(const TXString& name, bool isSimpleMaterial)
{
    fhObject = gSDK->CreateMaterial(name, isSimpleMaterial);
}

VWMaterialObj::VWMaterialObj(MCObjectHandle hMaterial)
{
    if(VWMaterialObj::IsMaterialObject(hMaterial))
    {
        fhObject = hMaterial;
    }
}

VWMaterialObj::VWMaterialObj(const VWMaterialObj& source)
{
    fhObject = source.fhObject;
}

VWMaterialObj::~VWMaterialObj()
{
    fhObject = nullptr;
}

VWMaterialObj& VWMaterialObj::operator=(const VWMaterialObj& source)
{
    fhObject = source.fhObject;
    return *this;
}

// MARK: - Public Methods Basic

/// Returns the material reference assigned of the material
InternalIndex VWMaterialObj::GetMaterialRef() const
{
    InternalIndex materialRef = gSDK->GetObjectInternalIndex(fhObject);
    return materialRef;
}

/// Returns the name of the material
/// Alias of VWMaterialObj::GetObjectName
TXString VWMaterialObj::GetMaterialName()
{
    return VWMaterialObj::GetObjectName();
}

/// Sets the name of the material (Alias of VWMaterialObj::SetObjectName)
/// @param name The display name of the material
void VWMaterialObj::SetMaterialName(const TXString& name)
{
    VWMaterialObj::SetObjectName(name);
}

/// Returns true, if the material type was VWMaterialObj::Set to simple on creation
bool VWMaterialObj::IsSimpleMaterial()
{
    return gSDK->IsMaterialSimple(fhObject);
}

/// Returns the texture reference assigned to the material
InternalIndex VWMaterialObj::GetMaterialTexture()
{
    return gSDK->GetMaterialTexture(fhObject);
}

/// Assigns the given texture reference to the material
/// @param textureIndex Texture reference index
bool VWMaterialObj::SetMaterialTexture(InternalIndex textureIndex)
{
    return gSDK->SetMaterialTexture(fhObject, textureIndex);
}

/// Returns the fill style index assigned to the material
InternalIndex VWMaterialObj::GetMaterialFillStyle()
{
    return gSDK->GetMaterialFillStyle(fhObject);
}

/// Assigns the given fill style index to the material
/// @param fillStyle FIll style index
void VWMaterialObj::SetMaterialFillStyle(InternalIndex fillStyle)
{
    gSDK->SetMaterialFillStyle(fhObject, fillStyle);
}

/// Returns true, if the fill style property is VWMaterialObj::Set to inherit from the class
bool VWMaterialObj::IsMaterialFillStyleByClass()
{
    return gSDK->IsMaterialFillStyleByClass(fhObject);
}

/// VWMaterialObj::Sets the by class flag, defining whether or not the fill style property is VWMaterialObj::Set to inherit from the class
/// @param byClass Whether or not the fill style property should inherit form the class
void VWMaterialObj::SetMaterialFillStyleByClass(bool byClass)
{
    gSDK->SetMaterialFillStyle(fhObject, byClass);
}

/// Returns the fill color assigned to the material
ObjectColorType VWMaterialObj::GetMaterialFillColor()
{
    ObjectColorType fillColors;
    gSDK->GetMaterialFillColor(fhObject, fillColors);
    return fillColors;
}

/// Assigns the given fill color to the material
/// @param fillColors Fill color
void VWMaterialObj::SetMaterialFillColor(ObjectColorType& fillColors)
{
    gSDK->SetMaterialFillColor(fhObject, fillColors);
}

// MARK: - ObjectVariables

TXString VWMaterialObj::GetOvDescription()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialDescription, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvDescription(TXString description)
{
    TVariableBlock var(description);
    gSDK->SetObjectVariable(fhObject, ovMaterialDescription, var);
}

TXString VWMaterialObj::GetOvMark()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialMark, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvMark(TXString mark)
{
    TVariableBlock var(mark);
    gSDK->SetObjectVariable(fhObject, ovMaterialMark, var);
}

TXString VWMaterialObj::GetOvKeynote()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialKeynote, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvKeynote(TXString keynote)
{
    TVariableBlock var(keynote);
    gSDK->SetObjectVariable(fhObject, ovMaterialKeynote, var);
}


// MARK: - ObjectVariables: Construction

bool VWMaterialObj::GetOvIsVolumetric()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialIsVolumetric, var);
    
    bool data;
    return var.GetBoolean(data) ? data : true;  // default value: true
}

void VWMaterialObj::SetOvIsVolumetric(bool isVolumetric)
{
    TVariableBlock var((Boolean)isVolumetric);
    gSDK->SetObjectVariable(fhObject, ovMaterialIsVolumetric, var);
}

bool VWMaterialObj::GetOvIsSurfaceAreaMeasure()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialIsSurfaceAreaMeasure, var);
    
    bool data;
    return var.GetBoolean(data) ? data : true;  // default value: true
}

void VWMaterialObj::SetOvIsSurfaceAreaMeasure(bool isSurfaceAreaMeasure)
{
    TVariableBlock var((Boolean)isSurfaceAreaMeasure);
    gSDK->SetObjectVariable(fhObject, ovMaterialIsSurfaceAreaMeasure, var);
}

TXString VWMaterialObj::GetOvCategory()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialCategory, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvCategory(TXString category)
{
    TVariableBlock var(category);
    gSDK->SetObjectVariable(fhObject, ovMaterialCategory, var);
}

TXString VWMaterialObj::GetOvStandard()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialStandard, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvStandard(TXString standard)
{
    TVariableBlock var(standard);
    gSDK->SetObjectVariable(fhObject, ovMaterialStandard, var);
}

TXString VWMaterialObj::GetOvReferenceId()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialReferenceID, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvReferenceId(TXString referenceId)
{
    TVariableBlock var(referenceId);
    gSDK->SetObjectVariable(fhObject, ovMaterialReferenceID, var);
}

TXString VWMaterialObj::GetOvClassificationDescription()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialClassificationDescription, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvClassificationDescription(TXString description)
{
    TVariableBlock var(description);
    gSDK->SetObjectVariable(fhObject, ovMaterialClassificationDescription, var);
}

TXString VWMaterialObj::GetOvManufacturer()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialManufacturer, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvManufacturer(TXString manufacturer)
{
    TVariableBlock var(manufacturer);
    gSDK->SetObjectVariable(fhObject, ovMaterialManufacturer, var);
}

TXString VWMaterialObj::GetOvProductModel()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialProductModel, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvProductModel(TXString productModel)
{
    TVariableBlock var(productModel);
    gSDK->SetObjectVariable(fhObject, ovMaterialProductModel, var);
}

TXString VWMaterialObj::GetOvProductName()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialProductName, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvProductName(TXString productName)
{
    TVariableBlock var(productName);
    gSDK->SetObjectVariable(fhObject, ovMaterialProductName, var);
}

TXString VWMaterialObj::GetOvProductDescription()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialProductDescription, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvProductDescription(TXString productDescription)
{
    TVariableBlock var(productDescription);
    gSDK->SetObjectVariable(fhObject, ovMaterialProductDescription, var);
}

TXString VWMaterialObj::GetOvProductUrl()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialProductURL, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvProductUrl(TXString productUrl)
{
    TVariableBlock var(productUrl);
    gSDK->SetObjectVariable(fhObject, ovMaterialProductURL, var);
}

TXString VWMaterialObj::GetOvProductSource()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialSource, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvProductSource(TXString productSource)
{
    TVariableBlock var(productSource);
    gSDK->SetObjectVariable(fhObject, ovMaterialSource, var);
}

TXString VWMaterialObj::GetOvProductFinish()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialFinish, var);
    
    TXString data;
    return var.GetTXString(data) ? data : "";
}

void VWMaterialObj::SetOvProductFinish(TXString productFinish)
{
    TVariableBlock var(productFinish);
    gSDK->SetObjectVariable(fhObject, ovMaterialFinish, var);
}

double VWMaterialObj::GetOvProductCost()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialCost, var);
    
    double data;
    return var.GetReal64(data) ? data : 0;  // default value: 0
}

void VWMaterialObj::SetOvProductCost(double productCost)
{
    TVariableBlock var(productCost);
    gSDK->SetObjectVariable(fhObject, ovMaterialCost, var);
}

// MARK: - ObjectVariables: Physics Variables

double VWMaterialObj::GetOvSpecificGravity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialSpecificGravity, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvSpecificGravity(double specificGravity, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesSpecificGravity, TVariableBlock((Boolean)true));

    TVariableBlock var(specificGravity);
    gSDK->SetObjectVariable(fhObject, ovMaterialSpecificGravity, var);
}

double VWMaterialObj::GetOvModulusOfElasticity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialModulusOfElasticity, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvModulusOfElasticity(double modulusOfElasticity, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesModulusOfElasticity, TVariableBlock((Boolean)true));

    TVariableBlock var(modulusOfElasticity);
    gSDK->SetObjectVariable(fhObject, ovMaterialModulusOfElasticity, var);
}

double VWMaterialObj::GetOvYieldStrength()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialYieldStrength, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvYieldStrength(double yieldStrength, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesYieldStrength, TVariableBlock((Boolean)true));

    TVariableBlock var(yieldStrength);
    gSDK->SetObjectVariable(fhObject, ovMaterialYieldStrength, var);
}

double VWMaterialObj::GetOvTensileStrength()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialTensileStrength, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvTensileStrength(double tensileStrength, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesTensileStrength, TVariableBlock((Boolean)true));

    TVariableBlock var(tensileStrength);
    gSDK->SetObjectVariable(fhObject, ovMaterialTensileStrength, var);
}

double VWMaterialObj::GetOvSpecificHeat()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialSpecificHeat, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvSpecificHeat(double specificHeat, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesSpecificHeat, TVariableBlock((Boolean)true));

    TVariableBlock var(specificHeat);
    gSDK->SetObjectVariable(fhObject, ovMaterialSpecificHeat, var);
}

double VWMaterialObj::GetOvEmissivity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialEmissivity, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvEmissivity(double emissivity, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesEmissivity, TVariableBlock((Boolean)true));

    TVariableBlock var(emissivity);
    gSDK->SetObjectVariable(fhObject, ovMaterialEmissivity, var);
}

double VWMaterialObj::GetOvAlbedo()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialAlbedo, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvAlbedo(double albedo, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesAlbedo, TVariableBlock((Boolean)true));

    TVariableBlock var(albedo);
    gSDK->SetObjectVariable(fhObject, ovMaterialAlbedo, var);
}

double VWMaterialObj::GetOvThermalExpCoeff()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialThermalExpansionCoefficient, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvThermalExpCoeff(double thermalExpansionCoefficient, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesThermalExpansionCoefficient, TVariableBlock((Boolean)true));

    TVariableBlock var(thermalExpansionCoefficient);
    gSDK->SetObjectVariable(fhObject, ovMaterialThermalExpansionCoefficient, var);
}

double VWMaterialObj::GetOvLambda()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialLambda, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvLambda(double lambda, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesLambda, TVariableBlock((Boolean)true));

    TVariableBlock var(lambda);
    gSDK->SetObjectVariable(fhObject, ovMaterialLambda, var);
}

double VWMaterialObj::GetOvEmbodiedCarbon()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialEmbodiedCarbon, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvEmbodiedCarbon(double embodiedCarbon, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesEmbodiedCarbon, TVariableBlock((Boolean)true));

    TVariableBlock var(embodiedCarbon);
    gSDK->SetObjectVariable(fhObject, ovMaterialEmbodiedCarbon, var);
}

double VWMaterialObj::GetOvSoundVelocity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialSoundVelocity, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvSoundVelocity(double soundVelocity, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesSoundVelocity, TVariableBlock((Boolean)true));

    TVariableBlock var(soundVelocity);
    gSDK->SetObjectVariable(fhObject, ovMaterialSoundVelocity, var);
}

double VWMaterialObj::GetOvDensity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialDensity, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvDensity(double density, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesDensity, TVariableBlock((Boolean)true));

    TVariableBlock var(density);
    gSDK->SetObjectVariable(fhObject, ovMaterialDensity, var);
}

double VWMaterialObj::GetOvAcousticImpedance()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialAcousticImpedance, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvAcousticImpedance(double acousticImpedance, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesAcousticImpedance, TVariableBlock((Boolean)true));

    TVariableBlock var(acousticImpedance);
    gSDK->SetObjectVariable(fhObject, ovMaterialAcousticImpedance, var);
}

double VWMaterialObj::GetOvSlipResistance()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialSlipResistance, var);
    
    double data;
    var.GetReal64(data);
    
    return data;
}

void VWMaterialObj::SetOvSlipResistance(double slipResistance, bool updateUse)
{
    if(updateUse) gSDK->SetObjectVariable(fhObject, ovMaterialUsesSlipResistance, TVariableBlock((Boolean)true));

    TVariableBlock var(slipResistance);
    gSDK->SetObjectVariable(fhObject, ovMaterialSlipResistance, var);
}

// MARK: - ObjectVariables: Physics Use Values
bool VWMaterialObj::GetOvUsesSpecificGravity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesSpecificGravity, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesSpecificGravity(bool useSpecificGravity)
{
    TVariableBlock var((Boolean)useSpecificGravity);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesSpecificGravity, var);
}

bool VWMaterialObj::GetOvUsesModulusOfElasticity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesModulusOfElasticity, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesModulusOfElasticity(bool useModulusOfElasticity)
{
    TVariableBlock var((Boolean)useModulusOfElasticity);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesModulusOfElasticity, var);
}

bool VWMaterialObj::GetOvUsesYieldStrength()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesYieldStrength, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesYieldStrength(bool useYieldStrength)
{
    TVariableBlock var((Boolean)useYieldStrength);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesYieldStrength, var);
}

bool VWMaterialObj::GetOvUsesTensileStrength()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesTensileStrength, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesTensileStrength(bool useTensileStrength)
{
    TVariableBlock var((Boolean)useTensileStrength);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesTensileStrength, var);
}

bool VWMaterialObj::GetOvUsesSpecificHeat()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesSpecificHeat, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesSpecificHeat(bool useSpecificHeat)
{
    TVariableBlock var((Boolean)useSpecificHeat);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesSpecificHeat, var);
}

bool VWMaterialObj::GetOvUsesEmissivity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesEmissivity, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesEmissivity(bool useEmissivity)
{
    TVariableBlock var((Boolean)useEmissivity);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesEmissivity, var);
}

bool VWMaterialObj::GetOvUsesAlbedo()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesAlbedo, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesAlbedo(bool useAlbedo)
{
    TVariableBlock var((Boolean)useAlbedo);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesAlbedo, var);
}

bool VWMaterialObj::GetOvUsesThermalExpCoeff()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesThermalExpansionCoefficient, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesThermalExpCoeff(bool useThermalExpansionCoefficient)
{
    TVariableBlock var((Boolean)useThermalExpansionCoefficient);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesThermalExpansionCoefficient, var);
}

bool VWMaterialObj::GetOvUsesLambda()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesLambda, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesLambda(bool useLambda)
{
    TVariableBlock var((Boolean)useLambda);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesLambda, var);
}

bool VWMaterialObj::GetOvUsesEmbodiedCarbon()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesEmbodiedCarbon, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesEmbodiedCarbon(bool useEmbodiedCarbon)
{
    TVariableBlock var((Boolean)useEmbodiedCarbon);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesEmbodiedCarbon, var);
}

bool VWMaterialObj::GetOvUsesSoundVelocity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesSoundVelocity, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesSoundVelocity(bool useSoundVelocity)
{
    TVariableBlock var((Boolean)useSoundVelocity);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesSoundVelocity, var);
}

bool VWMaterialObj::GetOvUsesDensity()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesDensity, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesDensity(bool useDensity)
{
    TVariableBlock var((Boolean)useDensity);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesDensity, var);
}

bool VWMaterialObj::GetOvUsesAcousticImpedance()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesAcousticImpedance, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesAcousticImpedance(bool useAcousticImpedance)
{
    TVariableBlock var((Boolean)useAcousticImpedance);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesAcousticImpedance, var);
}

bool VWMaterialObj::GetOvUsesSlipResistance()
{
    TVariableBlock var;
    gSDK->GetObjectVariable(fhObject, ovMaterialUsesSlipResistance, var);
    
    bool data;
    var.GetBoolean(data);
    
    return data;
}

void VWMaterialObj::SetOvUsesSlipResistance(bool usesSlipResistance)
{
    TVariableBlock var((Boolean)usesSlipResistance);
    gSDK->SetObjectVariable(fhObject, ovMaterialUsesSlipResistance, var);
}

// MARK: - Static

/// Returns true, if the given object handle is a building material object
/// @param hObject Object handle to check
bool VWMaterialObj::IsMaterialObject(MCObjectHandle hObject)
{
    return gSDK->GetObjectTypeN(hObject) == kBuildingMaterialNode;
}

/// Returns true, if the given index refers to a building material
/// @param index Index to check
bool VWMaterialObj::IsMaterialObject(InternalIndex index)
{
    MCObjectHandle hObject = gSDK->InternalIndexToHandle(index);
    short type = hObject ? gSDK->GetObjectTypeN(hObject) : 0;
    return type == kBuildingMaterialNode;
}
