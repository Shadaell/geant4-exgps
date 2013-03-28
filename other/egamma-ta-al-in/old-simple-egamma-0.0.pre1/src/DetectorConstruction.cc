/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
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

DetectorConstruction::DetectorConstruction()
{


  d_hist_min=0;
  d_hist_max=44000;
  d_hist_bins = 176000;
  d_energy_units=1;
  
  //деякі змінні, G4double -  те саме що і звичайний double
  // діаметр циліндра детектора:
  detector_diameter = 2*cm;
  // висота циліндра детектора
  detector_height = 1*cm;
  // відстань 0 координат Tl-пластини:
  gap1_distance = 20*cm;
  // відстань 0 координат до In-детектора
  gap2_distance = 20*cm;
  //деякі змінні:
  
  //діаметр пластини із Tl, де відбувається (e,gamma):
  cap_diameter = 2*15.0*cm;
  //товщина пластини із Tl, де відбувається (e,gamma):
  cap_thickness = 0.105*cm;

  target_distance = gap1_distance + gap2_distance;
  void_thickness = 1e-4*cm;
}

DetectorConstruction::~DetectorConstruction() {}

/**
   Create a new object of DetectorSD class and record it's
   pointer value to vector of pointers.
     
   \param name of the sensitive region
     
   \param If true -- then each SteppingAction will track any particle
   etting to this sensitive volume and book it's energy to the
   histograms.
*/
DetectorSD * DetectorConstruction::new_detector_sensitive
                                   (const G4String name,
				    const bool Ais_spec_counter)
{
  //add a new detector to the container
  if(!Ais_spec_counter)
    {
      vector_DetectorSD.push_back(new DetectorSD(name));
      //now pull out the pointer:
      std::vector<DetectorSD*>::iterator iter=vector_DetectorSD.end()-1;
      return (*iter);
    }
  else
    {
      vector_DetectorSD_COUNTERS.push_back(new DetectorSD(name));
      //now pull out the pointer:
      std::vector<DetectorSD*>::iterator iter=vector_DetectorSD_COUNTERS.end()-1;
      (*iter)->is_spec_counter=true;
      return (*iter);
  
    }
}

/** Set histogram properties.
    \param minimum value of range. 
    Anything lesser than this setpoint will be ignored.
      
    \param maximum value of range. 
    Anything greater than this setpoint will be ignored.
      
    \param Quantity of histogram bins.
*/
void DetectorConstruction::set_histo(const double min,
				     const double max,
				     const unsigned int n_bins, 
				     const unsigned int E_units)
{
  d_hist_min = min;
  d_hist_max = max;
  if(d_hist_max < d_hist_min)//if somehow on Earth..
    {
      d_hist_max = min;  d_hist_min = max;
    }
  d_hist_bins = n_bins;
  d_energy_units = E_units;

}
  

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
  
  G4Element *H = new G4Element("Hydrogen","H",1,1*g/mole);
  G4Material *void_dumb_material =  new G4Material("dumb_void", 1e-10*g/cm3, 1);
  void_dumb_material->AddElement(H,1);
  
  // второй способ: использует встроенную в Geant4 базу материалов
  // более простой, но иногда приходится прибегать к первому способу,
  // т.к. не все материалы содержатся в базе
  G4NistManager *nistMan = G4NistManager::Instance();
  
  G4Material *talium_material= nistMan->FindOrBuildMaterial("G4_Tl");
  G4Material *detector_material = nistMan->FindOrBuildMaterial("G4_In");
  // закінчили з матеріалами
  
  
  //---------------------------------------------------------------
  // --- volumes ---
  // создаем геометрию
  //---------------------------------------------------------------


  //-------- створюємо коробку "світовий об'єм"-------------------------
  // тут будуть розташовані всі об'єкти:
  G4Box *world_box = new G4Box("WORLD_BOX",
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
			"WORLD_LOG");
  
  // поставимо "світовий об'єм"  в початок координат:
  G4VPhysicalVolume *world_physical_volume = 
    new G4PVPlacement( 0, 
		       G4ThreeVector(),
		       world_logical_volume,
		       "WORLD_PHYS",
		       0, false, 0);
  //-----------------------------------------------------------------
  
  
  //-----------  робимо алюмінієву кришку корпуса детектора -------
  //геометрія:
  G4Tubs *Tl_plane =
    new G4Tubs("PLATE_TUBS",
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
			"PLATE_LOG");
  
  // вміщуємо його в "об'єм світу", коодинати (0, 0, gap1_distance)
  G4VPhysicalVolume *Tl_plane_physical_volume =
    new G4PVPlacement(0,
		      //3D-вектор розташування центра фігури в "світі":
		      G4ThreeVector(0, 0, gap1_distance), 
		      //логічний об'єм нашої кришки
		      Tl_plane_logical_volume,
		      "PLATE_PHYS",
		      //логічний об'єм "світу"
		      world_logical_volume,
		      false, 0);
  /**
     детектор-заглушка для отримання спектру просто без
     самопоглинання чи якихось реакції всередині матеріалу детектора
  **/
  G4Tubs *void_detector_tube = 
    new G4Tubs("VOID_DETECTOR_TUBE",
  	       0,
  	       detector_diameter/2,
  	       void_thickness,//void_thickness,
  	       0, 360*deg);
  
  G4LogicalVolume *void_detector_logical_volume =
    new G4LogicalVolume(
  			//фігура, що вміщує матеріал 
  			void_detector_tube,
  			//матеріал детектора
  			void_dumb_material,
  			"VOID_DETECTOR_LOGICAL");

  // вміщуємо його в "об'єм світу", коодинати
  G4VPhysicalVolume *void_det_phys =
    new G4PVPlacement(0,
  		      //3D-вектор розташування центра фігури в "світі":
  		      G4ThreeVector(0, 0,
  				    target_distance-
				    detector_height-2*void_thickness),
  		      //логічний об'єм сцинтилятора
  		      void_detector_logical_volume,
  		      "VOID_DETECTOR_PHYSICAL",
  		      //логічний об'єм "світу"
  		      world_logical_volume,
  		      false, 0);
  
  
  /**-------------------------------------------------------------
     опромінюваний зразок: In-мішень, як детектор
   **/
  // G4Tubs *detector_tube = 
  //   new G4Tubs("detector_tube",
  // 	       0,
  // 	       detector_diameter/2,
  // 	       detector_height,
  // 	       0, 360*deg);
  
  // G4LogicalVolume *detector_logical_volume =
  //   new G4LogicalVolume(
  // 			//фігура, що вміщує матеріал 
  // 			detector_tube,
  // 			//матеріал детектора
  // 			detector_material,
  // 			"INDIUM_DETECTOR_LOG");

  // // вміщуємо його в "об'єм світу", коодинати
  // G4VPhysicalVolume *det_phys =
  //   new G4PVPlacement(0,
  // 		      //3D-вектор розташування центра фігури в "світі":
  // 		      G4ThreeVector(0, 0,
  // 				    target_distance+detector_height/2),
  // 		      //логічний об'єм сцинтилятора
  // 		      detector_logical_volume,
  // 		      "INDIUM_DETECTOR_PHYS",
  // 		      //логічний об'єм "світу"
  // 		      world_logical_volume,
  // 		      false, 0);
  //---------------------------------------------------------------
  // --- ASSIGN RADIATION SENSITIVE DETECTORS ---
  // регистрируем detector_logical_volume как детектор
  // теперь при прохождении частиц через этот объем будет вызываться
  // метод DetectorSD::ProcessHits() в котором мы будем регистрировать
  // энергию оставленную в детекторе
  
  /** =================================================================
      Each use of DetectorConstruction::new_detector_sensitive(G4String)
      puts pointer to the vector_DetectorSD for futher operations on it.
      ================================================================
  **/
  // DetectorSD  *detector_sens_volume = new_detector_sensitive("DetectorSD");
  // detector_sens_volume->set_histo(d_hist_min,d_hist_max,
  // 				  d_hist_bins,d_energy_units);
  bool is_spec_counter=true;

  DetectorSD  *void_detector_sens_volume = new_detector_sensitive
               ("VoidDetectorSD", is_spec_counter);
  void_detector_sens_volume->set_histo(d_hist_min,d_hist_max,
				       d_hist_bins,d_energy_units);
  


  /** make this sensitive volume be a kinetic energy counter.**/
  
  G4SDManager *sens_det_manager = G4SDManager::GetSDMpointer();
  //додаємо до менеджера детекторів новий:
  // sens_det_manager->AddNewDetector(detector_sens_volume);
  // detector_logical_volume->SetSensitiveDetector(detector_sens_volume);

  sens_det_manager->AddNewDetector(void_detector_sens_volume);
  void_detector_logical_volume->SetSensitiveDetector(void_detector_sens_volume);
  
  

  // возвращаем указатель на мировой объем
  return world_physical_volume;
}

