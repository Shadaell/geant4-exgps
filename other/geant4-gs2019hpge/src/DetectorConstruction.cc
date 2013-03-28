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
#include "quick_geom.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

/** create a model of Canberra GC2019 HPGe detector
    \param parent logical volume pointer(world, usually)
    \param vector, pointers to created objects will be copied there
    \param pointer to sensitive detector, need it since we have sensitive parts.
    \param pointer to sensitive detector, need it since we have sensitive parts.
    \param position of the lower point of the cylinder. 
    \param rotational matrix.

 */
void CreateHPGE(G4LogicalVolume *parent,
	   std::vector< g4solid_object<G4Tubs>* > &result_objects_vector,
	   DetectorSD *sensitive_pointer1,
	   DetectorSD *sensitive_pointer2,
	   const G4ThreeVector &position,
	   G4RotationMatrix *rotMatrix = 0)
{
  #define D_LIT 1e-06*cm
  G4double ge_d/* crystal diamete*/,
    ge_h/*crystal height */,
    ge_front_dead,
    ge_side_dead,
    ge_back_dead,
    ge_hole_d,
    ge_hole_h,
    ge_hole_side_dead,
    ge_hole_bottom_dead,
    ge_side_cladding_thick,
    ge_cap_distance,
    ge_cap_diameter,
    ge_cap_front_thick,
    ge_cap_side_thick,
    ge_cap_back_thick,
    ge_mounting_thick;
  
  ge_d = 55.5*mm;
  ge_h = 41.5*mm;
  ge_hole_d = 11*mm;
  ge_hole_h = 31*mm;
  ge_front_dead = 1.35*mm;
  ge_side_dead = 1.35*mm;
  ge_back_dead = 1.35*mm;
  ge_hole_bottom_dead = 3e-3*mm;
  ge_hole_side_dead = 3e-3*mm;
  ge_side_cladding_thick = 0.76*mm;
  ge_cap_distance = 5*mm;
  ge_cap_diameter = 76.2*mm;
  ge_cap_front_thick = 1.5*mm;
  ge_cap_side_thick = 1.5*mm;
  ge_cap_back_thick = 12.3*mm;
  ge_mounting_thick =  3.2*mm;


  G4double endcap_gap = 5*mm;
  G4double endcap_thickness = 1.5*mm;
  
  G4Element *Fe = new G4Element("Iron", "Fe", 26, 55.845*g/mole);
  G4Element *Cr = new G4Element("Chromium"  , "Cr", 24, 51.996*g/mole);
  G4Element *Ni = new G4Element("Nickel"  , "Ni", 28, 58.69*g/mole);
  G4Element *C = new G4Element("Carbon"  , "C", 6, 12.0107*g/mole);
  G4Material *steel =  new G4Material("Steel", 7.8*g/cm3, 4);
  steel->AddElement(Fe, 73.85*perCent);
  steel->AddElement(C, 0.15*perCent);
  steel->AddElement(Cr, 18*perCent);
  steel->AddElement(Ni, 8*perCent);

  G4NistManager *nistMan = G4NistManager::Instance();

  G4Material *Ge_material = nistMan->FindOrBuildMaterial("G4_Ge");
  G4Material *Al_material = nistMan->FindOrBuildMaterial("G4_Al");
  
    //used for debug:
  bool cap_build = true,
    mounting_build = true,
    crystal_build = true,
    endcap_build = true,
    dead_ge_zone_build = true;
  
  //геометрія:
  G4ThreeVector placement;
  G4LogicalVolume *temp_logical_pointer;
  
  g4solid_object<G4Tubs> *ge_cylinder1, *ge_cylinder2,
    *mount_cylinder1, *mount_cylinder2,
    *cap_cylinder1, *cap_cylinder2, *cap_cylinder3,
    *endcap_al_top, *endcap_al_side, *endcap_steel_bottom,
    *ge_dead_bottom, *ge_dead_top, *ge_dead_side;

  G4VisAttributes *cap_attrib = new G4VisAttributes(G4Color(1, 1, 1));
  // cap parts:
  G4double cap_lower_plc = ge_cap_back_thick/2.0;
  G4double cap_upper_plc = ge_cap_back_thick + ge_mounting_thick
    + ge_h + ge_cap_distance + ge_cap_front_thick/2.0 + D_LIT;

  G4double cap_rout = (ge_cap_diameter)/2.0;
  G4double cap_side_rin = cap_rout - ge_cap_side_thick + D_LIT;
  // //hollow cylinder
  G4double cap_side_h = ge_mounting_thick + ge_cap_distance + ge_h;

  if(cap_build)
    {

      placement = G4ThreeVector(0,0, cap_lower_plc);
      placement += position;
      cap_cylinder1 = 
	make_cylinder(parent, "Cap_cyl1", Al_material,
		      placement,
		      cap_rout /* R, outer */,
		      ge_cap_back_thick/*h */,
		      0/* R, inner */,
		      rotMatrix);
      temp_logical_pointer = cap_cylinder1->get_logical();
      temp_logical_pointer->SetVisAttributes(cap_attrib);
  
      placement = G4ThreeVector(0, 0, ge_cap_back_thick + cap_side_h/2.0);
      placement += position;
      cap_cylinder2 = 
	make_cylinder(parent, "Cap_cyl2", Al_material,
		      placement,
		      cap_rout /* R, outer */,
		      cap_side_h/*h */,
		      cap_side_rin /* R, inner */,
		      rotMatrix);
      temp_logical_pointer = cap_cylinder2->get_logical();
      temp_logical_pointer->SetVisAttributes(cap_attrib);

      //----
      placement = G4ThreeVector(0,0, cap_upper_plc);
      placement += position;
      cap_cylinder3 = 
	make_cylinder(parent, "Cap_cyl3", Al_material,
		      placement,
		      cap_rout /* R, outer */,
		      ge_cap_front_thick/*h */,
		      0/* R, inner */,
		      rotMatrix);
      temp_logical_pointer = cap_cylinder3->get_logical();
      temp_logical_pointer->SetVisAttributes(cap_attrib);
      //finished aluminum cap.
      
      result_objects_vector.push_back(cap_cylinder1);
      result_objects_vector.push_back(cap_cylinder2);
      result_objects_vector.push_back(cap_cylinder3);

    }

  // endcap parts:
  G4double endcap_lower_plc = -1*endcap_gap;
  G4double endcap_upper_plc = 
    ge_cap_back_thick + ge_mounting_thick
    + ge_h + ge_cap_distance
    + ge_cap_front_thick/2.0 + endcap_gap + endcap_thickness/2.0 + D_LIT ;
  
  G4double endcap_rout = (ge_cap_diameter)/2.0 + endcap_gap;
  G4double endcap_side_rin = (ge_cap_diameter)/2.0 + endcap_gap - endcap_thickness;
  G4double endcap_side_plc = endcap_lower_plc  + .5*(endcap_upper_plc - endcap_lower_plc);
  G4double endcap_side_h = fabs(endcap_upper_plc) + fabs(endcap_lower_plc);
  
  if(endcap_build)
    {
      G4VisAttributes *endcap_attrib = new G4VisAttributes(G4Color(1, 1, 1));
  
      placement = G4ThreeVector(0,0, endcap_upper_plc);
      placement += position;
      endcap_al_top = 
  	make_cylinder(parent, "ENDCap_cyl1_top", Al_material,
  		      placement,
  		      endcap_rout /* R, outer */,
  		      endcap_thickness/*h */,
  		      0/* R, inner */, rotMatrix );
      temp_logical_pointer = endcap_al_top->get_logical();
      temp_logical_pointer->SetVisAttributes(endcap_attrib);
      
      // //hollow cylinder
      placement = G4ThreeVector(0, 0, endcap_side_plc);
      placement += position;
      endcap_al_side = 
  	make_cylinder(parent, "ENDCap_cyl2_side", Al_material,
  		      placement,
  		      endcap_rout /* R, outer */,
  		      endcap_side_h/*h */,
  		      endcap_side_rin
  		      /* R, inner */, rotMatrix );
      temp_logical_pointer = endcap_al_side->get_logical();
      temp_logical_pointer->SetVisAttributes(endcap_attrib);

      //----
      placement = G4ThreeVector(0,0, endcap_lower_plc);
      placement += position;
      endcap_steel_bottom = 
  	make_cylinder(parent, "ENDCap_cyl3_bottom", steel,
  		      placement,
  		      endcap_rout /* R, outer */,
  		      endcap_thickness/*h */,
  		      0/* R, inner */, rotMatrix );
      temp_logical_pointer = endcap_steel_bottom->get_logical();
      temp_logical_pointer->SetVisAttributes(endcap_attrib);
      //finished aluminum cap.
      
      result_objects_vector.push_back(endcap_al_top);
      result_objects_vector.push_back(endcap_al_side);
      result_objects_vector.push_back(endcap_steel_bottom);
    }
  
  //---
  G4VisAttributes *mounting_attrib_p1 = new G4VisAttributes(G4Color(.5, .5, .5));
  G4VisAttributes *mounting_attrib_p2 = new G4VisAttributes(G4Color(.7, .0, .0));
  //aluminium  mounting parts:
  //cylinder below
  if(mounting_build)
    {
      G4double mount1_plc = ge_cap_back_thick + ge_mounting_thick/2.0 + D_LIT;
      G4double mount2_plc = ge_cap_back_thick + ge_mounting_thick
				+ ge_h/2.0+ 2*D_LIT;
      G4double mount1_rout = ge_d/2.0;
      G4double mount2_rout = (ge_d)/2.0 + ge_side_cladding_thick;
      G4double mount2_rin = ge_d/2.0 + D_LIT;
      
      placement = G4ThreeVector(0,0, mount1_plc);
      placement += position;
      mount_cylinder1 = 
	make_cylinder(parent, "Mount_cyl1", Al_material,
		      placement,
		      mount1_rout /* R, outer */,
		      ge_mounting_thick/*h */,
		      0/* R, inner */,
		      rotMatrix);
      temp_logical_pointer = mount_cylinder1->get_logical();
      temp_logical_pointer->SetVisAttributes(mounting_attrib_p1);
  
      //hollow cylinder wrapping around the previous one and around the crystal.
      placement = G4ThreeVector(0, 0, mount2_plc);
      placement += position;
      mount_cylinder2 = 
	make_cylinder(parent, "Mount_cyl2", Al_material,
		      placement,
		      mount2_rout /* R, outer */,
		      ge_h/*h */,
		      mount2_rin
		      /* R, inner */,
		      rotMatrix);
  
      temp_logical_pointer = mount_cylinder2->get_logical();
      temp_logical_pointer->SetVisAttributes(mounting_attrib_p2);
      result_objects_vector.push_back(mount_cylinder1);
      result_objects_vector.push_back(mount_cylinder2);

    }
  
  //crystal active parts:
  G4VisAttributes *crystal_attrib = new G4VisAttributes(G4Color(1.0, .0, 1.0));
  G4double ge_cyl1_h = ge_hole_h - ge_back_dead + ge_hole_bottom_dead ;
  G4double ge_cyl2_h = ge_h - ge_hole_h - ge_hole_bottom_dead;	G4double ge_cyl1_rout = (ge_d - ge_side_dead)/2.0 -  D_LIT;
  G4double ge_cyl1_rin = (ge_hole_d + ge_hole_side_dead)/2.0;
  G4double ge_cyl1_plc = ge_cap_back_thick + ge_mounting_thick + ge_back_dead + ge_cyl1_h/2.0 + D_LIT;
  G4double ge_cyl2_plc = ge_cap_back_thick + ge_mounting_thick
    + ge_back_dead + ge_cyl1_h + ge_cyl2_h/2.0;
  std::cout << "\n\nBUILD" << "ge_cyl1(concentric): h, rout, rin, plc: "
	    << ge_cyl1_h << "\t"
	    << ge_cyl1_rout << "\t"
	    << ge_cyl1_rin << "\t"
	    << ge_cyl1_plc << "\n\n\n" ;
  std::cout << "\n\nBUILD" << "ge_cyl2(solid): h, rout, rin, plc: "
	    << ge_cyl2_h << "\t"
	    << ge_cyl1_rout << "\t"
	    << 0.0 << "\t"
	    << ge_cyl2_plc << "\n\n\n" ;
  if(crystal_build)
    {
            
      placement = G4ThreeVector(0, 0, ge_cyl1_plc);
      placement += position;

      ge_cylinder1 = 
	make_cylinder(parent, "Ge_cyl1", Ge_material,
		      placement,
		      ge_cyl1_rout /* R, outer */,
		      ge_cyl1_h/*h */,
		      ge_cyl1_rin/* R, inner */,
		      rotMatrix);
      
      placement = G4ThreeVector(0, 0, ge_cyl2_plc);
      placement += position;
      ge_cylinder2 = 
	make_cylinder(parent, "Ge_cyl2", Ge_material,
		      placement,
		      ge_cyl1_rout /* R, outer */,
		      ge_cyl2_h    /*h */,
		      0.0/* R, inner */,
		      rotMatrix
		      );
      temp_logical_pointer = ge_cylinder1->get_logical();
      temp_logical_pointer->SetVisAttributes(crystal_attrib);

      temp_logical_pointer = ge_cylinder2->get_logical();
      temp_logical_pointer->SetVisAttributes(crystal_attrib);
      result_objects_vector.push_back(ge_cylinder1);
      result_objects_vector.push_back(ge_cylinder2);

    }
  G4double ge_dead_lower_plc = ge_cap_back_thick + ge_mounting_thick + ge_back_dead/2.0 + .5*D_LIT;
  G4double ge_dead_upper_plc = ge_dead_lower_plc + ge_back_dead/2.0 + ge_h + ge_front_dead/2.0 + .5*D_LIT;
  G4double ge_dead_side_plc =  ge_dead_lower_plc + ge_back_dead/2.0 + ge_h/2.0 + .5*D_LIT;
  G4double ge_dead_rin = ge_d/2.0 + D_LIT;
  G4double ge_dead_rout = ge_d/2.0 + ge_side_dead;
  G4VisAttributes *ge_dead_attrib = new G4VisAttributes(G4Color(0, 1, 1));
  if(dead_ge_zone_build)
    {

      placement = G4ThreeVector(0, 0, ge_dead_lower_plc);
      placement += position;
      ge_dead_bottom = 
	make_cylinder(parent, "Ge_Dead_bottom", Ge_material,
		      placement,
		      ge_dead_rout,
		      ge_back_dead/* h*/,
		      ge_dead_rin,
		      rotMatrix);
      temp_logical_pointer = ge_dead_bottom->get_logical();
      temp_logical_pointer->SetVisAttributes(ge_dead_attrib);

      placement = G4ThreeVector(0, 0, ge_dead_upper_plc);
      placement += position;
      ge_dead_top = 
	make_cylinder(parent, "Ge_Dead_top", Ge_material,
		      placement,
		      ge_dead_rout,
		      ge_back_dead/* h*/,
		      0,
		      rotMatrix);
      temp_logical_pointer = ge_dead_top->get_logical();
      temp_logical_pointer->SetVisAttributes(ge_dead_attrib);

      placement = G4ThreeVector(0, 0, ge_dead_side_plc);
      placement += position;
      ge_dead_side = 
	make_cylinder(parent, "Ge_Dead_side", Ge_material,
		      placement,
		      ge_dead_rout,
		      ge_h/* h*/,
		      ge_dead_rin,
		      rotMatrix);
      temp_logical_pointer = ge_dead_side->get_logical();
      temp_logical_pointer->SetVisAttributes(ge_dead_attrib);
            
      
      result_objects_vector.push_back(ge_dead_bottom);
      result_objects_vector.push_back(ge_dead_top);
      result_objects_vector.push_back(ge_dead_side);
    }
  if(crystal_build)
    {
      if(ge_cylinder1 != NULL && sensitive_pointer1 != NULL)
	{
	  G4LogicalVolume *p = ge_cylinder1->get_logical();
	  p->SetSensitiveDetector(sensitive_pointer1);
	}
      if(ge_cylinder2 != NULL&& sensitive_pointer2 != NULL)
	{
	  G4LogicalVolume *p = ge_cylinder2->get_logical();
	  p->SetSensitiveDetector(sensitive_pointer2);
	}
    }

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // --- materials ---
  G4Element *N    = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
  G4Element *O    = new G4Element("Oxygen"  , "O", 8, 16.00*g/mole);
  G4Material *Air = new G4Material("Air", 1.29*mg/cm3, 2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);

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
  
  
  // g4solid_object<G4Tubs> * det_cylinder = make_cylinder(world_logical_volume, G4String("Ge_cyl"), Ge_material, G4ThreeVector(0,0,10*cm), 2*cm, 3*cm, 0*cm);
  
  // G4LogicalVolume *p = det_cylinder->get_logical();
  // DetectorSD  *detector_sens_volume = new DetectorSD("DetectorSD");

  // //додаємо до менеджера детекторів новий:
  // sens_det_manager->AddNewDetector(detector_sens_volume);
  // p->SetSensitiveDetector(detector_sens_volume);

  G4SDManager *det_manager = G4SDManager::GetSDMpointer();
  G4ThreeVector placement;
  G4LogicalVolume *temp_logical_pointer;
  
  DetectorSD  *ge_sensitive1 = new DetectorSD("ge_Sens1");
  
  det_manager->AddNewDetector(ge_sensitive1);
  
  std::vector< g4solid_object<G4Tubs>* > objects_vector;
  CreateHPGE(world_logical_volume, objects_vector,
	     ge_sensitive1, ge_sensitive1, G4ThreeVector(0,0,0));

  
  return world_physical_volume;
}

