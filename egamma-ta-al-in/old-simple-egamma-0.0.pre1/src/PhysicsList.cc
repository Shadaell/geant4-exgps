/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#include "PhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

PhysicsList::PhysicsList(): G4VUserPhysicsList()
{
  defaultCutValue = 1.0*mm;
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle()
{
  // регистрируем частицы
  // bosons
  G4Gamma::GammaDefinition();
  
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
}

void PhysicsList::ConstructProcess()
{
  // добавляем процессы:
  // движение частиц в пространстве и времени (уже реализовано в Geant4)
  AddTransportation();
  // электромагнитные взаимодействия (создаем сами)
  ConstructEM();
}

// standart EM
// gamma
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
// e+/e-
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4eMultipleScattering.hh"

#include "G4UrbanMscModel93.hh"

void PhysicsList::ConstructEM()
{
  // цикл по всем зарегистрированным частицам
  theParticleIterator->reset();
  while ( (*theParticleIterator)() ) {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    // подключаем соответствующие процессы для гамма, электронов и позитронов:
    if (particleName == "gamma") {
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      G4eMultipleScattering* msc = new G4eMultipleScattering();
      msc->AddEmModel(0, new G4UrbanMscModel93());
      //pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(msc,                     -1, 1, 1);      
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);      

    } else if (particleName == "e+") {
      G4eMultipleScattering* msc = new G4eMultipleScattering();
      msc->AddEmModel(0, new G4UrbanMscModel93());
      //pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(msc,                     -1, 1, 1);      
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);
    }
  }
}

void PhysicsList::SetCuts()
{
  // default cut value for all particle types 
  SetCutsWithDefault();
}

