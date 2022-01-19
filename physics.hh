#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option2.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList();
    void SetGammaCut(G4double);
    void SetElectronCut(G4double);
    
    void SetCuts();
    void SetRadiatorCuts();
    void SetDetectorCuts();
    //G4double fElectronCut, fGammaCut, fPositronCut;
    G4ProductionCuts* fRadiatorCuts;
    G4ProductionCuts* fDetectorCuts;
    G4double defaultCutValue = 1.*mm;
  //defaultCutValue = 0.001*mm;  // 1 um
  G4double cutForGamma     = defaultCutValue;
  G4double cutForElectron  = defaultCutValue;
  G4double cutForPositron  = defaultCutValue;

  G4double fGammaCut    = defaultCutValue;
  G4double fElectronCut = defaultCutValue;
  G4double fPositronCut = defaultCutValue;
    
};

#endif

