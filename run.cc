#include "run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Photons", "Photons");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleDColumn("fT");
    man->CreateNtupleDColumn("fEdep");
    man->CreateNtupleDColumn("fMomZ");
    man->CreateNtupleDColumn("detector_position");
    man->CreateNtupleDColumn("trackid");
    man->CreateNtupleDColumn("X_vetexPos");
    man->CreateNtupleDColumn("Y_vetexPos");
    man->CreateNtupleDColumn("Z_vetexPos");
    man->CreateNtupleDColumn("MomZ_vetexPos");
    man->FinishNtuple(0);
  
  
    man->CreateNtuple("GEMTRD", "GEMTRD");
    man->CreateNtupleDColumn("EnergyDepositPerEvent");
    man->CreateNtupleDColumn("StepLength");
    man->FinishNtuple(1);

}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output"+strRunID.str()+".root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
