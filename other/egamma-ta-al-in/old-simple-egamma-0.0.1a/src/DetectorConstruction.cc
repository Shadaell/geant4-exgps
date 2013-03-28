/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#include "DetectorConstruction.hh"
#include "DetectorSD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "globals.hh"
#include "G4VisAttributes.hh" 
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
  // --- materials ---
  // создаем материалы
  // первый способ:
  G4Element *N    = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
  G4Element *O    = new G4Element("Oxygen"  , "O", 8, 16.00*g/mole);
  G4Material *Air = new G4Material("Air", 1.29*mg/cm3, 2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);
  
  // второй способ: использует встроенную в Geant4 базу материалов
  // более простой, но иногда приходится прибегать к первому способу,
  // т.к. не все материалы содержатся в базе
  G4NistManager *nistMan = G4NistManager::Instance();
  //G4Material* Air = nistMan->FindOrBuildMaterial("G4_AIR");
  G4Material *talium_material= nistMan->FindOrBuildMaterial("G4_Tl");
  G4Material *detector_material = nistMan->FindOrBuildMaterial("G4_In");
  // закінчили з матеріалами
  
  //деякі змінні, G4double - майже те саме що і звичайний double
   // діаметр циліндра детектора:
  G4double detector_diameter = 2*cm;
   // висота циліндра детектора
  G4double detector_height = 1*cm;
   // відстань від джерела до кришки ФЕП:
  G4double gap1_distance = 20*cm;
   // відстань від кришки ФЕП до ал. покриття кристала
  G4double gap2_distance = 25*cm;
  //деякі змінні:
  // діаметр алюмінієвої кришки ФЕП+алюмінієве покриття кристала:
  G4double cap_diameter = 2*15.0*cm;
  G4double cap_thickness = 0.90*cm; //<- висота циліндра цеї штуки ^
  
  //---------------------------------------------------------------
  // --- volumes ---
  // создаем геометрию
  //---------------------------------------------------------------


  //-------- створюємо коробку "світовий об'єм"-------------------------
  // тут будуть розташовані всі об'єкти:
  G4Box *world_box = new G4Box("world",
			       //3 параметри паралелепіпеда X,Y,Z
			       200*cm,
			       200*cm,
			       200*cm);

  // закачаємо у нього повітря, створивши логічний об'єм із матеріалом "Air":
  G4LogicalVolume *world_logical_volume =
    new G4LogicalVolume(////фігура, що вміщує матеріал 
			world_box,
			//речовина, щозаповнює цей "світ"
			Air,
			"world");
  
  // поставимо "світовий об'єм"  в початок координат:
  G4VPhysicalVolume *world_physical_volume = 
    new G4PVPlacement( 0, 
		       G4ThreeVector(),
		       world_logical_volume,
		       "world",
		       0, false, 0);
  //-----------------------------------------------------------------
  
  
  //-----------  робимо алюмінієву кришку корпуса детектора -------
  //геометрія:
  G4Tubs *Tl_plane =
    new G4Tubs("sodium_iodide",
	       //радіус внутрішнього циліндра:
	       0,
	       //радіус зовнішнього циліндра:
	       cap_diameter/2,
	       //висота
	       cap_thickness/2,
	       //розріз: повний
	       0,  360*deg
	       );
  //логічний об'єм кришки:
  G4LogicalVolume *Tl_plane_logical_volume =
    new G4LogicalVolume(Tl_plane,
			talium_material,
			"plate");
  
  // вміщуємо його в "об'єм світу", коодинати (0, 0, gap1_distance)
  G4VPhysicalVolume *Tl_plane_physical_volume =
    new G4PVPlacement(0,
		      //3D-вектор розташування центра фігури в "світі":
		      G4ThreeVector(0, 0, gap1_distance), 
		      //логічний об'єм нашої кришки
		      Tl_plane_logical_volume,
		      "plate",
		      //логічний об'єм "світу"
		      world_logical_volume,
		      false, 0);
  //--------робимо наш любий NaI кристал------------------------------
  // 
  G4Tubs *detector_tube = 
    new G4Tubs("detector",
	       0,
	       detector_diameter/2,
	       detector_height/2,
	       0, 360*deg);
  
  G4LogicalVolume *detector_logical_volume =
    new G4LogicalVolume(
			//фігура, що вміщує матеріал 
			detector_tube,
			//матеріал детектора
			detector_material,
			"detector");

  // вміщуємо його в "об'єм світу", коодинати (0, 0, gap1_distance+gap2_distance+товщина стінки алюмінієвої)
  G4VPhysicalVolume *det_phys =
    new G4PVPlacement(0,
		      //3D-вектор розташування центра фігури в "світі":
		      G4ThreeVector(0, 0, gap1_distance + gap2_distance+4*cap_thickness),
		      //логічний об'єм сцинтилятора
		      detector_logical_volume,
		      "detector",
		      //логічний об'єм "світу"
		      world_logical_volume,
		      false, 0);
  //---------------------------------------------------------------
  // --- ASSIGN RADIATION SENSITIVE DETECTORS ---
  // регистрируем detector_logical_volume как детектор
  // теперь при прохождении частиц через этот объем будет вызываться
  // метод DetectorSD::ProcessHits() в котором мы будем регистрировать
  // энергию оставленную в детекторе
  DetectorSD  *detector_sens_volume = new DetectorSD("DetectorSD");
  G4SDManager *sens_det_manager = G4SDManager::GetSDMpointer();
  //додаємо до менеджера детекторів новий:
  sens_det_manager->AddNewDetector(detector_sens_volume);
  detector_logical_volume->SetSensitiveDetector(detector_sens_volume);
  
  

  // возвращаем указатель на мировой объем
  return world_physical_volume;
}

