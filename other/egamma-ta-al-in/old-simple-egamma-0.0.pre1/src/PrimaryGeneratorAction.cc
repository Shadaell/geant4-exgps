/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  particle_energy = 44000;
  source_position = G4ThreeVector(0,0,0);
  particle_momentum = G4ThreeVector(0,0,1);
  
  // создаем источник частиц
  // источник испускает по одной частице
  particleGun = new G4ParticleGun(1);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* electron = particleTable->FindParticle("e-");
  
  // устанавливаем тип и энергию частиц, координаты положения источника
  particleGun->SetParticleDefinition(electron);
  particleGun->SetParticleEnergy(particle_energy*keV);
  particleGun->SetParticlePosition(source_position);
  particleGun->SetParticleMomentumDirection(particle_momentum);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // задаем случайное направление излучения
  particleGun->SetParticleMomentumDirection(particle_momentum);
  // источник испускает одну частицу
  particleGun->GeneratePrimaryVertex(event);
}

