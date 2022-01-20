#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
   
    
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  //G4ParticleDefinition *particle = particleTable->FindParticle(particleName="e-");
  G4ParticleDefinition *particle = G4Electron::Definition();
  //G4ParticleDefinition *particle = G4Gamma::Definition();
  //G4ParticleDefinition *particle = G4PionMinus::Definition();

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(6.*GeV);
  //fParticleGun->SetParticleMomentum(6.*GeV);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  G4double envSizeXY = 10;
  G4double envSizeZ = 10;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }  
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }

  G4double size = 0.6; 
  G4double x0 = size * envSizeXY * (G4UniformRand()-0.5);
  G4double y0 = size * envSizeXY * (G4UniformRand()-0.5);
 // G4double z0 = -0.5 * envSizeZ;
  
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,-10*cm));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
