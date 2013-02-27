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
// Author  Bogdan Maslovskiy <blinkofnight(at,doggy,removeme)gmail(dot)com>
// Taras Schevchenko National University of Kyiv 2012
//****************

#include "DetectorConstruction.hh"
#include "quick_geom.hh"

DetectorConstruction::DetectorConstruction()
{

  with_Pb_shield = false;
  
  messenger = new DetectorConstructionMessenger(this);
  
  d_hist_min=0;
  d_hist_max=100000;
  d_hist_bins = 200000;
  d_energy_units=1;

  aluminium_thick = 0.0*cm;
  aluminium_diameter = 9.0*cm;

  TG_DET_thickness = 0;
  target_mass = 0.0*g;
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
  cap_diameter = 10.0*cm;
  //товщина пластини із Tl, де відбувається (e,gamma):
  cap_thickness = 0.105*cm;

  TL_AL_distance=cap_thickness;
  
  target_distance = gap1_distance + cap_thickness + gap2_distance;
  void_thickness = 1e-4*cm;
}

DetectorConstruction::~DetectorConstruction() 
{
  delete messenger;
}

/**
   Create a new object of DetectorSD class and record it's
   pointer value to vector of pointers.
     
   \param name of the sensitive region
     

*/
DetectorSD2 * DetectorConstruction::new_detector_sensitive(const G4String name)
{
  //add a new detector to the container
  vector_DetectorSD.push_back(new DetectorSD2(name));
  //now pull out the pointer:
  std::vector<DetectorSD2*>::iterator iter = 
    vector_DetectorSD.end()-1;
  (*iter)->fill_hist("e-", 0);
  (*iter)->fill_hist("e+", 0);
  (*iter)->fill_hist("gamma", 0);
  (*iter)->fill_hist_deposited("e-", 0);
  (*iter)->fill_hist_deposited("e+", 0);
  (*iter)->fill_hist_deposited("gamma", 0);
  return (*iter);
}

/** 
    Read parameters values from a map<G4String, G4double>;
    Possible G4Sting keys are:
    "tathick", "tadiam", "tgthick", "tgdiam", "tgmass", "althick", "aldiam".
    example1:
    If map contains a pair of values like: "tgmass" and 0.200*g,
    then target detector mass will be set to 0.2g.
    
    //one may actually use this code :
    str_double_map.insert( std::pair<G4String, G4double>
    ("tgmass", 0.200*g));
    //to insert that values into map
    
    example2:    
    If map contains a pair of values: "tathick" and 0.100*cm,
    then Ta-plate thickness will be set to 0.1*cm.
    
    \param std::map reference(a container with G4String and G4double pairs).

*/
void DetectorConstruction::read_parameters(const std::map< G4String, G4double > &str_double_map)
{
  std::map< G4String, G4double >::const_iterator str_double_iterator;
  this->use_Pb_shield(false);  
  //add strings to the option's list:
  for( str_double_iterator = str_double_map.begin();
       str_double_iterator != str_double_map.end(); 
       str_double_iterator++)
    {
      G4double value = str_double_iterator->second;
      G4String key = str_double_iterator->first;
      if(key == "tathick")
	set_TL_thickness(value);
      else
      if(key == "tadiam")
	set_TL_diameter(value);
      else
      if(key == "althick")
	set_AL_thickness(value);
      else
      if(key == "aldiam")
	set_AL_diameter(value);
      else
      if(key == "tgthick")
	set_TG_DET_thickness(value);
      else
      if(key == "tgdiam")
	set_TG_DET_diameter(value);
      else
      if(key == "tgmass")
	set_TG_DET_mass(value);
      else
      if(key == "shield")
	this->use_Pb_shield(true);
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
  //lets build it up:
  
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
  target_distance = gap1_distance + cap_thickness + gap2_distance;
  
  //get pointer to sensitive detector manager:
  G4SDManager *det_manager = G4SDManager::GetSDMpointer();

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

  G4Material *Al_material= nistMan->FindOrBuildMaterial("G4_Al");
  G4Material *Pb_material= nistMan->FindOrBuildMaterial("G4_Pb");
  G4Material *talium_material= nistMan->FindOrBuildMaterial("G4_Ta");

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
  
  
  //-----------  Talium plate which is bombarded by e- -------
  //геометрія:
  G4ThreeVector placement = G4ThreeVector(0, 0, gap1_distance);
  g4solid_object<G4Box> *tl_plane_box = 
    make_box(world_logical_volume, 
	     "TL_PLATE",
	     talium_material,
	     placement,
	     cap_diameter/2,
	     cap_diameter/2,
	     cap_thickness/2  );
  /**
     детектор-заглушка для отримання спектру просто без
     самопоглинання чи якихось реакції всередині матеріалу детектора.
     Розташований після Tl-пластинки, але перед Al-бруском
  **/
  placement = G4ThreeVector(0, 0,
			    gap1_distance + cap_thickness
			    +2*void_thickness);
  g4solid_object<G4Tubs> *void0_cylinder = 
    make_cylinder(world_logical_volume, "VOID0", void_dumb_material,
		  placement,
		  detector_diameter/2,
		  void_thickness);

  //-----------  Aluminum e- filter  -------
  //геометрія:
  if(aluminium_thick>1e-06)
    {
      placement = G4ThreeVector(0, 0,
				gap1_distance + cap_thickness +
				TL_AL_distance + aluminium_thick);
      g4solid_object<G4Tubs> *aluminium_cylinder = 
	make_cylinder(world_logical_volume, "ALUM_BULK", Al_material,
		      placement,
		      aluminium_diameter/2,
		      aluminium_thick);
    }
  
  if(with_Pb_shield)
    {
      placement = G4ThreeVector(0, 0, gap1_distance+
				cap_thickness+
				TL_AL_distance+
				aluminium_thick);
      g4solid_object<G4Tubs> *plumbum_cylinder = 
	make_cylinder(world_logical_volume, "PLUMBUM_BULK", Pb_material,
		      placement,
		      aluminium_diameter/2+5*cm /** outer radius**/,
		      aluminium_thick,
		      aluminium_diameter/2 /** inner radius**/);

    }

  /**
     детектор-заглушка для отримання спектру просто без
     самопоглинання чи якихось реакції всередині матеріалу детектора.
     Розташований після Al-бруска.
  **/
  placement = G4ThreeVector(0, 0, target_distance - 0.1*cm);
  g4solid_object<G4Tubs> *void1_cylinder = 
    make_cylinder(world_logical_volume, "VOID1", void_dumb_material,
		  placement,
		  detector_diameter/2,
		  void_thickness);
  
  
  /**-------------------------------------------------------------
     опромінюваний зразок: In-мішень, як детектор
  **/
  if(target_mass > (1e-20*g))
    {
      if(detector_height <= (1e-16*cm) && target_mass > (0*g))
	{//then calculate from it's mass and diameter
	  
	  detector_height = target_mass/detector_material->GetDensity()/(M_PI*detector_diameter);
	}

      placement = G4ThreeVector(0, 0, target_distance + detector_height/2);
      g4solid_object<G4Tubs> *target_cylinder = 
	make_cylinder(world_logical_volume, "TARGET_BULK",
		      detector_material,
		      placement,
		      detector_diameter/2.0,
		      detector_height);
      DetectorSD2 *sensitive = new_detector_sensitive("target_DetectorSD2");
      
      det_manager->AddNewDetector(sensitive);
      G4LogicalVolume *det_log = target_cylinder->get_logical();
      det_log->SetSensitiveDetector(sensitive);
    } 
  
  
  // --- ASSIGN RADIATION SENSITIVE DETECTORS ---
  /** =================================================================
      Each use of DetectorConstruction::new_detector_sensitive(G4String)
      puts pointer to the vector_DetectorSD for futher operations on it.
      ================================================================
  **/
  DetectorSD2  *void0_sensitive =
    new_detector_sensitive("void0_DetectorSD2");
  DetectorSD2  *void_sensitive = 
    new_detector_sensitive("void1_DetectorSD2");
  
  /** make this sensitive volume be a kinetic energy counter.**/
  
  det_manager->AddNewDetector(void0_sensitive);
  G4LogicalVolume *void0_det_log = void0_cylinder->get_logical();
  void0_det_log->SetSensitiveDetector(void0_sensitive);
  
  det_manager->AddNewDetector(void_sensitive);
  G4LogicalVolume *void_det_log = void1_cylinder->get_logical();
  void_det_log->SetSensitiveDetector(void_sensitive);
  
  // возвращаем указатель на мировой объем
  return world_physical_volume;
}

