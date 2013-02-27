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

  //add strings to the option's list:
  for( str_double_iterator = str_double_map.begin();
       str_double_iterator != str_double_map.end(); 
       str_double_iterator++)  {
      G4double value = str_double_iterator->second;
      G4String key = str_double_iterator->first;
      // switch(key) {
      // case "some_key": {      }
      // default:
      // }
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

  G4Material *Fe_material= nistMan->FindOrBuildMaterial("G4_Fe");
  G4Material *Poly_material= nistMan->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material *concreteMaterial = nistMan->FindOrBuildMaterial("G4_CONCRETE");
  G4Material *detector_material = nistMan->FindOrBuildMaterial("G4_In");
  
  //---------------------------------------------------------------
  // создаем геометрию
  //---------------------------------------------------------------


  //-------- world box-------------------------
  // тут будуть розташовані всі об'єкти:
  G4Box *world_box = new G4Box("WORLD_BOX",
			       //3 параметри паралелепіпеда X,Y,Z
			       660*cm,
			       660*cm,
			       660*cm);

  // заполним воздухом лабораторию:
  G4LogicalVolume *world_logical_volume =
    new G4LogicalVolume(world_box, Air,	"WORLD_LOG");
  
  G4VPhysicalVolume *world_physical_volume = 
    new G4PVPlacement( 0, 
		       G4ThreeVector(),
		       world_logical_volume,
		       "WORLD_PHYS",
		       0, false, 0);
  //------------ Objects ---------------------------------------------------
  g4solid_object<G4Box> *plita = 
      make_box(world_logical_volume,
	       "plita",
	       concreteMaterial,
	       G4ThreeVector(0,0, -6.7*m), 3 * m, 3* m, 20 * cm);

  g4solid_object<G4Box> *febox = 
      make_box(world_logical_volume,
	       "febox",
	       Fe_material,
	       G4ThreeVector(0,0, -10.1*m), 2 * m, 2* m, 2 * m);
  

  g4solid_object<G4Box> *polybox = 
      make_box(world_logical_volume,
	       "polybox",
	       Poly_material,
	       G4ThreeVector(0,0, 0), 2 * m, 2* m, 2 * m);

  g4solid_object<G4Box> *airbox = 
      make_box(world_logical_volume,
	       "airbox",
	       Air,
	       G4ThreeVector(0,0, 0), 170*cm, 170*cm, 170*m);
  
  
  // --- ASSIGN RADIATION SENSITIVE DETECTORS ---
  /** =================================================================
      Each use of DetectorConstruction::new_detector_sensitive(G4String)
      puts pointer to the vector_DetectorSD for futher operations on it.
      ================================================================
  **/
  // DetectorSD2  *void0_sensitive =
  //   new_detector_sensitive("void0_DetectorSD2");
  
  // /** make this sensitive volume be a kinetic energy counter.**/
 
  // det_manager->AddNewDetector(void0_sensitive);
  // G4LogicalVolume *void0_det_log = void0_cylinder->get_logical();
  // void0_det_log->SetSensitiveDetector(void0_sensitive);
  
  // возвращаем указатель на мировой объем
  return world_physical_volume;
}

