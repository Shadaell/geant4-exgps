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

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"
#include <ctime>
#include "anyoption.h"
#include <stdio.h>
#include <string.h>

#define MAX_HIST 100e03 //kev

/** 
    The function will fill the str_double_map with possible
    construction's options and their initial values.
    Then it will try to parse arguments and write option's values
    into the map(std::map<G4String, G4double> &str_double_map).
     Option/resource file has ':' separated options or flags,
     one per line.
     
     \param arguments count
     \param arguments 
     \param A reference of the empty map of pairs <G4String, G4double>
 */
void process_arguments(int _argc, char **_argv, 
		       std::map<G4String, G4double> &str_double_map)
{
  AnyOption *opt = new AnyOption();
  // str_double_map.insert( std::pair<G4String, G4double>
  // 			      ("tathick", 0.105*cm));
  // <-if TG height 0 then will be calculated from mass and diameter
  
  std::map<G4String, G4double>::iterator str_double_iterator;
  
  //add strings to the option's list:
  for( str_double_iterator = str_double_map.begin(); 
       str_double_iterator != str_double_map.end(); 
       str_double_iterator++)
    {
      //kind of opt->setOption("tathick"):
      opt->setOption(str_double_iterator->first.data());
    }
  
  if(_argc > 2)
    {
      G4String argument = _argv[1];
      std::string cfg_str = "config";
      //if first argument contains word config -- then parse it
      if(argument.contains(cfg_str))
	{
	  opt->processFile(_argv[1]);
	}
      else
	{//parse all arguments otherwise
	  opt->processCommandArgs( _argc, _argv );
	}
      
      char *value = 0x00;
      float scan_value = 0;
      for( str_double_iterator = str_double_map.begin();
	   str_double_iterator != str_double_map.end(); 
	   str_double_iterator++)
	{
	  //now search each a value for each option:
	  const char *the_string = str_double_iterator->first.data();
	  if( opt->getValue(the_string) != NULL )
	    {
	      value = opt->getValue( the_string );
	      //copy value given by option to the
	      //G4double pointer inside the mapt
	      sscanf(value, "%f", &scan_value);
	      str_double_iterator->second = (G4double)scan_value;
	    }
	}
    }
}

int main(int argc, char** argv)
{
  // выбор генератора случайных чисел
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  // и инициализация генератора текущим значением времени
  // благодаря этому результаты любых двух запусков моделирования не будут полностью одинаковы 
  CLHEP::HepRandom::setTheSeed(time(NULL));

  // создание класса для управления моделированием
  G4RunManager* runManager = new G4RunManager;

  // подключение обязательных классов: описание частиц, процессов, геометрии и источника
  runManager->SetUserInitialization(new PhysicsList);

  EventAction *userEventAction = new EventAction();
  runManager->SetUserAction(userEventAction);

  DetectorConstruction *construction_unit = new DetectorConstruction();

  // //Set initial options values and read some of them from argv:
  // std::map<G4String, G4double> str_double_map;
  // process_arguments(argc, argv, str_double_map);
  // //set construction's configuration from the map with params:
  // construction_unit->read_parameters(str_double_map);

  construction_unit->set_histo(0,MAX_HIST,12500,1);

  
  PrimaryGeneratorAction *gen_action = new PrimaryGeneratorAction();
  //set gen_action's configuration from the map with params:
  //gen_action->read_parameters(str_double_map);
  
  runManager->SetUserInitialization(construction_unit);
  runManager->SetUserAction(gen_action);
  
  /** Створюємо клас, який містить методи, які GEANT4 запускатиме на
      початку та в кінці симуляції,
      див. RunAction::BeginOfRunAction(G4Run*) та 
      RunAction::EndOfRunAction(G4Run*).
   */
  RunAction *userAction = new RunAction();
  /**
     assign pointer std::vector<DetectorSD*> *DSD_vector
     from RunAction class to make histograms from detector data:
  **/
  userAction->DSD_vector = &construction_unit->vector_DetectorSD;
  runManager->SetUserAction(userAction);
  
  SteppingAction *userSteppingAction = new SteppingAction();
  /** Assign vector of special detection counters which only
      track kinetic energy of incoming particles with no interaction:
  **/
  userSteppingAction->SetDetectorSD(&construction_unit->vector_DetectorSD);
  runManager->SetUserAction(userSteppingAction);
  


  
  // создание и настройка класса для управления визуализацией
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  //prepare to launch:
  runManager->Initialize();
  
  //lift off!
  if (argc!=1)   // batch mode  
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      // UI->ExecuteMacroFile(argv[1]);
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }  
  // освобождение памяти
  delete visManager;
  delete runManager;
  // и выход
  return 0;
}
