#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "g4root.hh"
#include "G4SystemOfUnits.hh"
#include "run.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    void AddEdep(G4double edep,G4double posz);
    
private:
    G4double fEdep;
    G4double fPosZ;
};

inline void MyEventAction::AddEdep(G4double edep,G4double posz) 
{ 
  fEdep += edep;
  fPosZ += posz;
} 



#endif
