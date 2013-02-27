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

#ifndef RunAction_h
#define RunAction_h 1

class Hist1i;

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "DetectorSD2.hh"
#include <vector>

class G4Run;

class RunAction: public G4UserRunAction
{
public:
  RunAction();
  
  // /** Create runaction with pointer to the vector with pointers to
  //     sensitive detector objects.
  //     \param address of the vector with DetectorSD* pointers;
  // */
  // RunAction(std::vector<DetectorSD*> &vector_DetectorSD);
  
  ~RunAction();

  /** Vector of pointers to DetectorSD objects.
      The user may have to set this pointer manually
      e..g run_action->DSD_vector = &other_vector;
      
      Why do we need it? 
      Method RunAction::BeginOfRunAction(G4Run*)
      will try to access this pointer and call 
      DetectorSD::reset_histo();

      Method RunAction::EndOfRunAction(G4Run*)
      will try to access this pointer and call 
      DetectorSD::save_histo() which will write all 
      histograms created by DetectorSD objects to files.;

   */
  std::vector<DetectorSD2*> *DSD_vector;
  
  /** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::reset_histo() which will make all 
      DetectorSD objects ready to start capturing events.;
  */
  void BeginOfRunAction(const G4Run*);

  /** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::save_histo() which will write all 
      histograms created by DetectorSD objects to files.;
  */
  void EndOfRunAction(const G4Run*);

  
  
};

#endif
