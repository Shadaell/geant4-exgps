/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

// заголовочные файлы для классов которые мы реализовали сами
// эти файлы лежат в подкаталоге include/
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
// файл с фунциями для работы с системным временем
#include <ctime>


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
  construction_unit->set_histo(0,44000, 2000);
  runManager->SetUserInitialization(construction_unit);
  
  PrimaryGeneratorAction *gen_action = new PrimaryGeneratorAction();
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
  userAction->DSD_COUNTERS_vector = &construction_unit->vector_DetectorSD_COUNTERS;
  runManager->SetUserAction(userAction);
  
  SteppingAction *userSteppingAction = new SteppingAction();
  /** Assign vector of special detection coutners which only
      track kinetic energy of incoming particles with no interaction:
  **/
  userSteppingAction->SetDetectorSD(&construction_unit->vector_DetectorSD_COUNTERS);
  runManager->SetUserAction(userSteppingAction);
  
  // создание и настройка класса для управления визуализацией
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  //prepare to launch:
  runManager->Initialize();
  
  //lift off! 
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ExecuteMacroFile(argv[1]);
  
  // освобождение памяти
  delete visManager;
  delete runManager;
  // и выход
  return 0;
}
