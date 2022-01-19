#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{

}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    //track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4double posPhoton_z = aStep->GetTrack()->GetPosition().z();
    G4ThreeVector posPhoton = postStepPoint->GetPosition();
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();
    edep = aStep->GetTotalEnergyDeposit(); 
    
    //G4double Tsec = aStep->GetPreStepPoint()->GetKineticEnergy() ;

    G4double time = preStepPoint->GetGlobalTime();

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posPhoton[0]);
    man->FillNtupleDColumn(0, 2, posPhoton[1]);
    man->FillNtupleDColumn(0, 3, posPhoton_z);
    man->FillNtupleDColumn(0, 4, time);
    man->FillNtupleDColumn(0, 5, edep/keV);
    man->FillNtupleDColumn(0, 6, momPhoton[2]*GeV);
    man->FillNtupleDColumn(0, 7, posDetector[2]);
    man->AddNtupleRow(0);


    return true;
}
