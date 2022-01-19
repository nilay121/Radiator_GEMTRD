#include "physics.hh"
#include "construction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4Material.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include <iomanip>

#include "G4Region.hh"
#include "G4RegionStore.hh"

#include "G4ProductionCuts.hh"
#include "G4EmProcessOptions.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4PAIModel.hh"
#include "G4PAIPhotModel.hh"

#include "G4SynchrotronRadiation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

#include "G4Decay.hh"

#include "G4VXTRenergyLoss.hh"
#include "G4RegularXTRadiator.hh"
#include "G4TransparentRegXTRadiator.hh"
#include "G4GammaXTRadiator.hh"
#include "G4StrawTubeXTRadiator.hh"

#include "G4XTRGammaRadModel.hh"
#include "G4XTRRegularRadModel.hh"
#include "G4XTRTransparentRegRadModel.hh"


#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"




MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics (new G4EmStandardPhysics_option2());	// Foe electromagnetic interaction> Modular 
}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::SetCuts()
{
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
 
  SetCutValue(cutForGamma, "gamma", "DefaultRegionForTheWorld");
  SetCutValue(cutForElectron, "e-", "DefaultRegionForTheWorld");
  SetCutValue(cutForPositron, "e+", "DefaultRegionForTheWorld");

  if (verboseLevel > 0)
  {
    G4cout << "VtxPhysicsList::SetCuts:";
  }
  G4Region* region;
  //* uncomment for FDC & depfet !!!!!!!!!!!!!!!!!!!!!!!!!!!
  if( !fRadiatorCuts ) SetRadiatorCuts();
  region = G4RegionStore::GetInstance()->GetRegion("XTRradiator");
  region->SetProductionCuts(fRadiatorCuts);
  G4cout << "Radiator cuts are set" << G4endl;
  
  if( !fDetectorCuts ) SetDetectorCuts();
  region = G4RegionStore::GetInstance()->GetRegion("XTRdEdxDetector");
  region->SetProductionCuts(fDetectorCuts);
  G4cout << "Detector cuts are set" << G4endl;
  
  if (verboseLevel > 1)     DumpCutValuesTable();
}
void MyPhysicsList::SetGammaCut(G4double val)
{
  cutForGamma = val;
}

///////////////////////////////////////////////////////////////////////////

void MyPhysicsList::SetElectronCut(G4double val)
{
  cutForElectron = val;
}
void MyPhysicsList::SetRadiatorCuts()
{
  if( !fRadiatorCuts ) fRadiatorCuts = new G4ProductionCuts();

  fRadiatorCuts->SetProductionCut(fGammaCut, idxG4GammaCut);
  fRadiatorCuts->SetProductionCut(fElectronCut, idxG4ElectronCut);
  fRadiatorCuts->SetProductionCut(fPositronCut, idxG4PositronCut);

  G4cout<<"Radiator gamma cut    = "<<fGammaCut/mm<<" mm"<<G4endl;
  G4cout<<"Radiator electron cut = "<<fElectronCut/mm<<" mm"<<G4endl;
  G4cout<<"Radiator positron cut = "<<fPositronCut/mm<<" mm"<<G4endl;
}

void MyPhysicsList::SetDetectorCuts()
{
  if( !fDetectorCuts ) fDetectorCuts = new G4ProductionCuts();

  fDetectorCuts->SetProductionCut(fGammaCut, idxG4GammaCut);
  fDetectorCuts->SetProductionCut(fElectronCut, idxG4ElectronCut);
  fDetectorCuts->SetProductionCut(fPositronCut, idxG4PositronCut);

  G4cout<<"Detector gamma cut    = "<<fGammaCut/mm<<" mm"<<G4endl;
  G4cout<<"Detector electron cut = "<<fElectronCut/mm<<" mm"<<G4endl;
  G4cout<<"Detector positron cut = "<<fPositronCut/mm<<" mm"<<G4endl;

}




