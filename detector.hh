#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    G4double edep;
    G4double fdep=0;
    
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
