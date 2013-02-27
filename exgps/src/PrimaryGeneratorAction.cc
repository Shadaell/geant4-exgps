// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
///*
// Part of simulation for use with GEANT4 code.
// Author  Bogdan Maslovskiy <blinkofnight(at,doggy,removeme)gmail(dot)>,
// Taras Schevchenko National University of Kyiv 2011
//****************

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"
#include <stdlib.h>

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  source_position = G4ThreeVector(0,0,0);
  particle_momentum = G4ThreeVector(0,0,1);
  beam_diameter = 0.9*cm;
  real_electron_beam=true;
  // создаем источник частиц
  // источник испускает по одной частице
  particleGun = new G4ParticleGun(1);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* electron = particleTable->FindParticle("e-");
  
  // устанавливаем тип и энергию частиц, координаты положения источника
  particleGun->SetParticleDefinition(electron);
  //  particleGun->SetParticleEnergy(particle_energy*keV);
  particleGun->SetParticlePosition(source_position);
  particleGun->SetParticleMomentumDirection(particle_momentum);
}

/** particle energy, measured in keV 
    (use this way: particle_energy*keV )*/
double PrimaryGeneratorAction::get_particle_energy()
{
  if(particleGun!=NULL)
    return particleGun->GetParticleEnergy();
  return 0;
}
  
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // задаем случайное направление излучения
  if(real_electron_beam)
    {
      source_position = G4ThreeVector(beam_diameter*drand48(),beam_diameter*drand48(),0);
    }
  
  particleGun->SetParticlePosition(source_position);
  particleGun->SetParticleMomentumDirection(particle_momentum);
  // источник испускает одну частицу
  particleGun->GeneratePrimaryVertex(event);
}

/** 
    Read parameters values from a map<G4String, G4double>;
    Possible G4Sting keys are:
    "shapedbeam"
      
    If map contains a pair of values like: "shapedbeam" and any value (1, etc.), then the electrons beam will be shaped.
      
    \param std::map reference(a container with G4String and G4double pairs).

*/
void PrimaryGeneratorAction::read_parameters(const std::map< G4String, G4double > &str_double_map)
{
  this->use_real_beam_shape(false);
  std::string the_string = "shapedbeam";
  std::map<G4String, G4double>::const_iterator str_double_iterator;
  
  for( str_double_iterator = str_double_map.begin();
       str_double_iterator != str_double_map.end(); 
       str_double_iterator++)
    {
      G4String key = str_double_iterator->first;
      if(key.contains(the_string))
	this->use_real_beam_shape(true);
    }
}
