//
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
//
//
// $Id: RemSimSteppingAction.hh,v 1.4 2006/06/29 16:23:23 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
// 
// Author: Susanna Guatelli (guatelli@ge.infn.it)
//
// History:
// -----------
// 27 May  2003   S.Guatelli    first code review 
// 17 May  2003   S. Guatelli   1st implementation
//
// -------------------------------------------------------------------

#ifndef RemSimSteppingAction_h
#define RemSimSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "DetectorSD.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "globals.hh"

class G4Step;


class SteppingAction : public G4UserSteppingAction
{
public:

  SteppingAction();

  ~SteppingAction();

  void UserSteppingAction(const G4Step* aStep);
  
  /** assign pointer std::vector<DetectorSD*> *DSD_vector
      to make histograms from DUMB detector data.
  */
  void SetDetectorSD(std::vector <DetectorSD*> *vector);
  
private:
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
  std::vector <DetectorSD*> *DSD_vector;

};
#endif
