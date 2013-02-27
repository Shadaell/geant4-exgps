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

#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* Det): detector(Det)
{ 
  // Fix the parameters of the shielding: material and thickness
  valueDir = new G4UIdirectory("/construction/");
  valueDir -> SetGuidance("Construction parameters");
       
  
  cmd_histo_bins =  new G4UIcmdWithAnInteger("/construction/hist_bins",this);
  cmd_histo_bins -> SetGuidance("number of histogramm bins."); 
  cmd_histo_bins -> SetParameterName("Number",true);
  cmd_histo_bins -> SetRange("Size>=0.");
  cmd_histo_bins -> AvailableForStates(G4State_Idle); 

  cmd_histo_min =  new G4UIcmdWithADoubleAndUnit("/construction/hist_min",this);
  cmd_histo_min -> SetGuidance("min value of energy histogramms"); 
  cmd_histo_min -> SetParameterName("Size",true);
  cmd_histo_min -> SetRange("Size>=0.");
  cmd_histo_min -> SetUnitCategory("Length");
  cmd_histo_min -> AvailableForStates(G4State_Idle); 

  cmd_histo_max =  new G4UIcmdWithADoubleAndUnit("/construction/hist_max",this);
  cmd_histo_max -> SetGuidance("max value of energy histogramms"); 
  cmd_histo_max -> SetParameterName("Size",true);
  cmd_histo_max -> SetRange("Size>=0.");
  cmd_histo_max -> SetUnitCategory("Length");
  cmd_histo_max -> AvailableForStates(G4State_Idle); 
    
  
}

DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
  delete cmd_histo_bins;
  delete cmd_histo_min;
  delete cmd_histo_max;

  delete valueDir;
}

void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  
  if(command == cmd_histo_bins)
    detector -> set_histo_bins
      (cmd_histo_bins -> GetNewIntValue(newValue));
  
  if(command == cmd_histo_min)
    detector -> set_histo_min
      (cmd_histo_min -> GetNewDoubleValue(newValue));
  if(command == cmd_histo_max)
    detector -> set_histo_max
      (cmd_histo_max -> GetNewDoubleValue(newValue));
  
}

