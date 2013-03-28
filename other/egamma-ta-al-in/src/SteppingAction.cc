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

#include "SteppingAction.hh"
#include "G4ios.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4ParticleDefinition.hh"
#include "G4VPhysicalVolume.hh"


SteppingAction::SteppingAction()
{ 

}

SteppingAction::~SteppingAction()
{ 

}

/** assign pointer std::vector<DetectorSD*> *DSD_vector
    to make histograms from DUMB detector data.
    \param pointer to std::vector of pointers DetectorSD* .
*/
void SteppingAction::SetDetectorSD(std::vector <DetectorSD2*> *vector)
{
  DSD_vector = vector;
}
  
void SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
  G4VPhysicalVolume* volume = aStep->GetPostStepPoint()->GetPhysicalVolume();
  G4VSensitiveDetector* sens_detector = aStep->GetPostStepPoint()->GetSensitiveDetector();
  
  G4String volumeName= (volume)? volume->GetName(): G4String("null");
  G4String sensName= (sens_detector)? sens_detector->GetName(): G4String("null");
  G4Track *track = aStep->GetTrack();
  
  G4String particleName = (track->GetDynamicParticle()
			        ->GetDefinition()
			        ->GetParticleName());
  if(sens_detector!=NULL && DSD_vector!=NULL)
    {
      std::vector<DetectorSD2*>::iterator iter;
      for(iter = DSD_vector->begin(); iter < DSD_vector->end(); iter++)
	{
	  if( (*iter)->GetName() == sensName)
	    {
	      (*iter)->fill_hist(particleName, track->GetKineticEnergy());
	      // G4cout << "stepping: DetectorSD name: " << sensName
	      //  	     << " track ID: "<< track->GetTrackID()
	      //  	     << " p.name: "  << particleName
	      //  	     << " p.energy :"<< (track->GetKineticEnergy())/keV <<
	      // 	"\n";
	    }
	}
    }

}

