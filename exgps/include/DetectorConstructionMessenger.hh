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
// Based on code developed by  S.Guatelli
// Author:
// Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
// 

#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

class DetectorConstructionMessenger: public G4UImessenger
{
public:
  DetectorConstructionMessenger(DetectorConstruction* );
  ~DetectorConstructionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  
  /** pointer to detector*/
  DetectorConstruction*  detector;

  /** Name of the 'directory' in mac file, e.g. /construction/
   */
  G4UIdirectory*         valueDir;
  
  /** Set number of histogram bins. */
  G4UIcmdWithAnInteger* cmd_histo_bins;


  /** Set number of histogram min value. */
  G4UIcmdWithADoubleAndUnit* cmd_histo_min;


  /** Set number of histogram max value.  */
  G4UIcmdWithADoubleAndUnit* cmd_histo_max;
    

};
  
#endif

