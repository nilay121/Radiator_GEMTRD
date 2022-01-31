#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
    fPosZ=0;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
    fPosZ=0;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    //G4cout << "Energy deposition: " << fEdep << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(1, 0, fEdep/keV);
    man->FillNtupleDColumn(1,1,fPosZ/mm);
    man->AddNtupleRow(1);
    
    
}
