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
#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4ForwardXrayTR.hh"
#include "construction.hh"
#include "VtxStepCut.hh"
class MyDetectorConstruction;
class MyPhysicsList : public G4VUserPhysicsList
{
public:
    MyPhysicsList(MyDetectorConstruction*);
    ~MyPhysicsList();
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();
    
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBarions();
    
    void AddParameterisation();
    void ConstructGeneral();
    void ConstructEM();
    
    void SetGammaCut(G4double);
    void SetElectronCut(G4double);

    void SetRegGammaCut(G4double    cut){fGammaCut    = cut;};
    void SetRegElectronCut(G4double cut){fElectronCut = cut;};
    void SetRegPositronCut(G4double cut){fPositronCut = cut;};
   
    void SetRadiatorCuts();
    void SetDetectorCuts();
    
    void SetMaxStep(G4double);
    //void SetXTRModel(G4String m) {fXTRModel = m; G4cout<<fXTRModel<<G4endl;}; 

    G4double MaxChargedStep;

    G4ForwardXrayTR* fForwardXrayTR;
    
    VtxStepCut* theeminusStepCut ;
    VtxStepCut* theeplusStepCut ;

    G4double cutForGamma;
    G4double cutForElectron, cutForPositron;

    MyDetectorConstruction* pDet;
 
    G4ProductionCuts* fRadiatorCuts;
    G4ProductionCuts* fDetectorCuts;
    G4double fElectronCut, fGammaCut, fPositronCut;
    G4String fXTRModel;
    G4double step_cut=1*mm;
    G4double highEnergyLimit=100*keV;
};

#endif

