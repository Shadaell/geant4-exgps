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
       
  cmd_AL_thickness =  new G4UIcmdWithADoubleAndUnit("/construction/AL_thickness",this);
  cmd_AL_thickness -> SetGuidance("Set the thickness of the AL bar."); 
  cmd_AL_thickness -> SetParameterName("Size",true);
  cmd_AL_thickness -> SetRange("Size>=0.");
  cmd_AL_thickness -> SetUnitCategory("Length");
  cmd_AL_thickness -> AvailableForStates(G4State_Idle); 
  
  cmd_AL_diameter =  new G4UIcmdWithADoubleAndUnit("/construction/AL_diameter",this);
  cmd_AL_diameter -> SetGuidance("Set the diameter of the AL bar."); 
  cmd_AL_diameter -> SetParameterName("Size",true);
  cmd_AL_diameter -> SetRange("Size>=0.");
  cmd_AL_diameter -> SetUnitCategory("Length");
  cmd_AL_diameter -> AvailableForStates(G4State_Idle); 

  cmd_TL_thickness =  new G4UIcmdWithADoubleAndUnit("/construction/TL_thickness",this);
  cmd_TL_thickness -> SetGuidance("Set the thickness of the TL cylinder."); 
  cmd_TL_thickness -> SetParameterName("Size",true);
  cmd_TL_thickness -> SetRange("Size>=0.");
  cmd_TL_thickness -> SetUnitCategory("Length");
  cmd_TL_thickness -> AvailableForStates(G4State_Idle); 
  
  cmd_TL_diameter =  new G4UIcmdWithADoubleAndUnit("/construction/TL_diameter",this);
  cmd_TL_diameter -> SetGuidance("Set the diameter of the TL cylinder."); 
  cmd_TL_diameter -> SetParameterName("Size",true);
  cmd_TL_diameter -> SetRange("Size>=0.");
  cmd_TL_diameter -> SetUnitCategory("Length");
  cmd_TL_diameter -> AvailableForStates(G4State_Idle); 

  cmd_GUN_TL_distance =  new G4UIcmdWithADoubleAndUnit("/construction/GUN_TL_distance",this);
  cmd_GUN_TL_distance -> SetGuidance("Distance from particle source to Tl-cylinder."); 
  cmd_GUN_TL_distance -> SetParameterName("Size",true);
  cmd_GUN_TL_distance -> SetRange("Size>=0.");
  cmd_GUN_TL_distance -> SetUnitCategory("Length");
  cmd_GUN_TL_distance -> AvailableForStates(G4State_Idle); 
  
  cmd_TL_AL_distance =  new G4UIcmdWithADoubleAndUnit("/construction/TL_AL_distance",this);
  cmd_TL_AL_distance -> SetGuidance("Distance from Tl-cylinder to AL bar."); 
  cmd_TL_AL_distance -> SetParameterName("Size",true);
  cmd_TL_AL_distance -> SetRange("Size>=0.");
  cmd_TL_AL_distance -> SetUnitCategory("Length");
  cmd_TL_AL_distance -> AvailableForStates(G4State_Idle); 

  
  cmd_TL_DETECTOR_distance =  new G4UIcmdWithADoubleAndUnit("/construction/TL_DETECTOR_distance",this);
  cmd_TL_DETECTOR_distance -> SetGuidance("Distance from Tl-cylinder to detector."); 
  cmd_TL_DETECTOR_distance -> SetParameterName("Size",true);
  cmd_TL_DETECTOR_distance -> SetRange("Size>=0.");
  cmd_TL_DETECTOR_distance -> SetUnitCategory("Length");
  cmd_TL_DETECTOR_distance -> AvailableForStates(G4State_Idle); 

  cmd_TG_DET_thickness =  new G4UIcmdWithADoubleAndUnit("/construction/TG_DET_thickness",this);
  cmd_TG_DET_thickness -> SetGuidance("Thickness of the real detector, if 0 -- the this det. is not used.."); 
  cmd_TG_DET_thickness -> SetParameterName("Size",true);
  cmd_TG_DET_thickness -> SetRange("Size>=0.");
  cmd_TG_DET_thickness -> SetUnitCategory("Length");
  cmd_TG_DET_thickness -> AvailableForStates(G4State_Idle); 
  
  cmd_TG_DET_diameter =  new G4UIcmdWithADoubleAndUnit("/construction/TG_DET_diameter",this);
  cmd_TG_DET_diameter -> SetGuidance("Diameter of the detector"); 
  cmd_TG_DET_diameter -> SetParameterName("Size",true);
  cmd_TG_DET_diameter -> SetRange("Size>=0.");
  cmd_TG_DET_diameter -> SetUnitCategory("Length");
  cmd_TG_DET_diameter -> AvailableForStates(G4State_Idle); 
  
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
  delete cmd_AL_thickness;
  delete cmd_AL_diameter;

  delete cmd_TL_thickness;
  delete cmd_TL_diameter;

  delete cmd_TG_DET_thickness;
  delete cmd_TG_DET_diameter;
  
  delete cmd_GUN_TL_distance;
  delete cmd_TL_AL_distance;
  delete cmd_TL_DETECTOR_distance;
  delete cmd_histo_bins;
  delete cmd_histo_min;
  delete cmd_histo_max;

  delete valueDir;
}

void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if(command == cmd_AL_thickness)
    detector -> set_AL_thickness
      (cmd_AL_thickness -> GetNewDoubleValue(newValue));
  if(command == cmd_AL_diameter)
    detector -> set_AL_diameter
      (cmd_AL_diameter -> GetNewDoubleValue(newValue));

  if(command == cmd_TL_thickness)
    detector -> set_TL_thickness
      (cmd_TL_thickness -> GetNewDoubleValue(newValue));
  if(command == cmd_TL_diameter)
    detector -> set_TL_diameter
      (cmd_TL_diameter -> GetNewDoubleValue(newValue));
  
  if(command == cmd_GUN_TL_distance)
    detector -> set_GUN_TL_distance
      (cmd_GUN_TL_distance -> GetNewDoubleValue(newValue));

  if(command == cmd_TL_AL_distance)
    detector -> set_TL_AL_distance
      (cmd_TL_AL_distance -> GetNewDoubleValue(newValue));

  if(command == cmd_TL_DETECTOR_distance)
    detector -> set_TL_DETECTOR_distance
      (cmd_TL_DETECTOR_distance -> GetNewDoubleValue(newValue));

  if(command == cmd_TG_DET_thickness)
    detector -> set_TG_DET_thickness
      (cmd_TG_DET_thickness -> GetNewDoubleValue(newValue));
  
  if(command == cmd_TG_DET_diameter)
    detector -> set_TG_DET_diameter
      (cmd_TG_DET_diameter -> GetNewDoubleValue(newValue));
  
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

