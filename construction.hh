#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SDManager.hh"
#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();

private:
    G4Box *solidWorld, *solidRadiator, *solidDetector, *solidScintillator;
    G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector, *logicScintillator, *logicGem;
    G4VPhysicalVolume *physWorld, *physDetector, *physRadiator, *physScintillator;

    G4OpticalSurface *mirrorSurface;

    G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI;
    G4Element *C, *Na, *I;
      G4Box*             fSolidRadSlice;   // pointer to the solid  z-slice 
  G4LogicalVolume*   fLogicRadSlice;   // pointer to the logical z-slide
  G4VPhysicalVolume* fPhysicRadSlice;  // pointer to the physical z-slide

  G4Box*             fSolidRadRing;    // pointer to the solid  R-slice 
  G4LogicalVolume*   fLogicRadRing;    // pointer to the logical R-slide
  G4VPhysicalVolume* fPhysicRadRing;   // pointer to the physical R-slide

  G4Box*             fSolidRadiator;
  G4LogicalVolume*   fLogicRadiator; 
  G4VPhysicalVolume* fPhysicsRadiator;

  G4Material* fRadiatorMat;        // pointer to the mixed TR radiator material
  G4Material* fFoilMat;            // pointer to the TR foil radiator material
  G4Material* fGasMat;             // pointer to the TR gas radiator material

  G4double fRadThickness;
  G4double fGasGap;
  G4double foilGasRatio;

  G4int fFoilNumber;

  G4double fDetThickness;
  G4double fDetLength;
  G4double fDetGap;

  G4double fStartR;
  G4double fStartZ;

//G4double fRadThick;
  G4double fMylarThick;

 
  

  // G4double fElectronCut, fGammaCut, fPositronCut;
       

  G4Region*             fRegGasDet;
  G4Region*             fRadRegion;
  G4Material*        fMat;  
  G4Material*        fAbsorberMaterial;

    void DefineMaterials();
    virtual void ConstructSDandField();

    G4GenericMessenger *fMessenger;

    G4LogicalVolume *fScoringVolume;

};

#endif
