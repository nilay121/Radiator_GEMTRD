#include "stepping.hh"
#include <time.h>
MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *aStep)
{   
 /*   G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
    
   if(volume != fScoringVolume)
        return;
    
    G4double edep = step->GetTotalEnergyDeposit();
    edep=edep*1000;
    fEventAction->AddEdep(edep);*/
    
  // get volume of the current step
 // srand(time(0));
  auto volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // energy deposit
  auto edep = aStep->GetTotalEnergyDeposit();
  
    // step length
  G4double posz = 0.;
  if ( aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    posz = aStep->GetStepLength();
  }
      
  const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());    
  if ( volume == detectorConstruction->GetAbsorberPV() ) {
    fEventAction->AddEdep(edep,posz);
  }
    
  
  //--  gamma ENTER absorber ???

  //printf("----------- test ----------------- fGeomBoundary-%d(%d) \n",aStep->GetPostStepPoint()->GetStepStatus(),fGeomBoundary);

  if (aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary && aStep->GetPostStepPoint()->GetPhysicalVolume() )    
  {
    if (
	(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="Envelope") &&
	((aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="gem")) &&
	(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Transportation") &&
	(aStep->GetTrack()->GetMomentumDirection().z()>0.)                       &&
	(aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")
	)
      {
      	G4double temp = aStep->GetTrack()->GetKineticEnergy();
      	G4cout<<"The energy before entering GEM is :- "<<temp/keV<<" kev"<<G4endl;
        G4double randEne = rand()%30;
        aStep->GetTrack()->SetKineticEnergy((randEne+10)*keV); //10 giving good
       // aStep->GetTrack()->SetKineticEnergy(0*keV);
	Egamma = aStep->GetTrack()->GetKineticEnergy() ;
	G4cout<<"The energy after setting cut is :- "<<Egamma/keV<<" kev"<<G4endl;
	G4double ene_dep = aStep->GetTotalEnergyDeposit(); 
	
	G4cout<<"The energy deposited in GEM is :- "<<ene_dep/keV<<" kev"<<G4endl;
      }
  }  
  
  //--  gamma EXIT absorber forward
  if (aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary && aStep->GetPostStepPoint()->GetPhysicalVolume() )    {
  if (
      ((aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="gem") &&
       (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="World") &&
      (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Transportation") &&
      (aStep->GetTrack()->GetMomentumDirection().z()>0.) &&
      (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma"))
     )
     {
       Egamma2 = aStep->GetTrack()->GetKineticEnergy() ;
       G4cout<<"The energy after leaving GEM is :- "<<Egamma2/keV<<" kev"<<G4endl;
     }
  }
  
   G4AnalysisManager *man = G4AnalysisManager::Instance();
   
    man->FillNtupleDColumn(2, 0, Egamma/keV);
    man->FillNtupleDColumn(2, 1, Egamma2/keV);
    man->AddNtupleRow(2);
  
}
