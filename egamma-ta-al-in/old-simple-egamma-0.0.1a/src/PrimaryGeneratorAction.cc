/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  // создаем источник частиц
  // источник испускает по одной частице
  particleGun = new G4ParticleGun(1);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* electron = particleTable->FindParticle("e-");
  // устанавливаем тип и энергию частиц, координаты положения источника
  particleGun->SetParticleDefinition(electron);
  particleGun->SetParticleEnergy(44000*keV);
  particleGun->SetParticlePosition(G4ThreeVector(0, 0,0));
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // задаем случайное направление излучения
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  // источник испускает одну частицу
  particleGun->GeneratePrimaryVertex(event);
}

