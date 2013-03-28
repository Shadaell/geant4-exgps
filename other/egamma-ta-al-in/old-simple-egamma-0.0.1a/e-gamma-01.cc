/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

// заголовочные файлы для классов которые мы реализовали сами
// эти файлы лежат в подкаталоге include/
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

// заголовочные файлы для классов из библиотеки Geant4
#include "G4RunManager.hh"
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
  runManager->SetUserInitialization(new DetectorConstruction);
  runManager->SetUserAction(new PrimaryGeneratorAction);

  // подключение дополнительных классов: набор/сохранение гистограмм
  runManager->SetUserAction(new RunAction);

  // создание и настройка класса для управления визуализацией
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  // настройка ядра моделироавния:
  // непосредственное конструирование частиц, процессов и геометрии
  // расчет сечений, оптимизация геометрии, ...
  runManager->Initialize();
  
  // запуск конфигурационного файла
  G4UImanager* UI = G4UImanager::GetUIpointer();
	// в argv[1] содержится первый параметр командной строки (имя конфигурационного файла)
  UI->ExecuteMacroFile(argv[1]);
  
  // освобождение памяти
  delete visManager;
  delete runManager;
  // и выход
  return 0;
}
