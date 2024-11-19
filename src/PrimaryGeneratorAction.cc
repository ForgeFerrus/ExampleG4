#include "PrimaryGeneratorAction.hh"

#include<G4VEnergyLossProcess.hh>
#include<G4Event.hh>
#include<G4ParticleGun.hh>
#include<G4ParticleTable.hh>
#include<G4ParticleDefinition.hh>
#include<globals.hh>

    PrimaryGeneratorAction::PrimaryGeneratorAction()
   {
       G4int n_particle = 1;
       particleGun = new G4ParticleGun(n_particle);
   
       G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
       G4ParticleDefinition* particle = particleTable->FindParticle("e-");
     
       particleGun->SetParticleDefinition(particle);
       particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
       particleGun->SetParticlePosition(G4ThreeVector(0, 0, -10*CLHEP::cm));
       particleGun->SetParticleEnergy(50*CLHEP::MeV);
   }
    PrimaryGeneratorAction::~PrimaryGeneratorAction()
   {
       delete particleGun;
   }
    void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
   { 
       particleGun->GeneratePrimaryVertex(anEvent);
   }