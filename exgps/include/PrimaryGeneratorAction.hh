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

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include <map>

class G4ParticleGun;
class G4Event;


class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
  
    /** 
      Read parameters values from a map<G4String, G4double>;
      Possible G4Sting keys are:
      "shapedbeam"
      
      If map contains a pair of values like: "shapedbeam" and any value (1, etc.), then the electrons beam will be shaped.
      
      \param std::map reference(a container with G4String and G4double pairs).

  */
  void read_parameters(const std::map< G4String, G4double > &str_double_map);

  
  void GeneratePrimaries(G4Event* anEvent);
  /** particle energy, measured in keV 
      (use this way: particle_energy*keV )*/
  double get_particle_energy();
  
  /** Enables/disables the simulation of the real beam shape.
      Currently it's cross section has predefined shape -- a round
      with diameter -- 0.9*cm.
   **/
  void use_real_beam_shape(bool yesno)
  {real_electron_beam=yesno;}

private:
  G4double beam_diameter;
  bool real_electron_beam;
  G4ThreeVector source_position;
  G4ThreeVector particle_momentum;
  G4ParticleGun* particleGun;
};

#endif


