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

#include "RunAction.hh"
#include "Hist1i.h"

#include "G4Run.hh"
#include "Randomize.hh"

RunAction::RunAction() 
{

}

RunAction::~RunAction()
{
  DSD_vector=NULL;
}

/** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::reset_histo() which will make all 
      DetectorSD objects ready to start capturing events.;
*/
void RunAction::BeginOfRunAction(const G4Run*)
{
  G4cout << "\n*********************************************\n";
  G4cout << "\n\n=======================\nBegin of RunAction:\n";
  
}

/** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::save_histo() which will write all 
      histograms created by DetectorSD objects to files.;
*/
void RunAction::EndOfRunAction(const G4Run* )
{
  if(this->DSD_vector!=NULL && (!DSD_vector->empty()) )
    {
      std::vector<DetectorSD2*>::iterator iter;
      for(iter = DSD_vector->begin(); iter < DSD_vector->end(); iter++)
	(*iter)->save_all();
    }
}

