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

#include "quick_geom.hh"


g4solid_object<G4Tubs> * make_cylinder(
	       G4LogicalVolume *WORLD_LOGICAL,
	       const G4String name,
	       G4Material *material,
	       const G4ThreeVector placement,
	       const G4double outer_radius,
	       const G4double height,
	       const G4double inner_radius,
	       G4RotationMatrix *pRot,
	       const G4double uncut_angle_start,
	       const G4double uncut_angle_end)
{
  G4String part_name;
  part_name = name + "_g4tubs";
  G4Tubs *tubs = new G4Tubs(part_name, inner_radius, outer_radius,
			    height/2.0, uncut_angle_start, uncut_angle_end);
  
  part_name = name + "_g4tubs_logicalVolume";
  G4LogicalVolume *logical =
    new G4LogicalVolume(tubs, material, part_name);
  
  part_name = name + "_g4tubs_physicalVolume";  
  G4VPhysicalVolume *physical =
    new G4PVPlacement(pRot, placement, logical, part_name, WORLD_LOGICAL,
		      false, 0);
  //create object and pack pointers to there:
  g4solid_object<G4Tubs> *truba = new g4solid_object<G4Tubs>();
  truba->set(tubs, logical, physical);
  return truba;
}  
//-------

g4solid_object<G4Tubs> * make_cylinder
( G4LogicalVolume *WORLD_LOGICAL,
  const G4String name,
  G4Material *material,
  const G4Transform3D transform,
  const G4double outer_radius,
  const G4double height,
  const G4double inner_radius,
  const G4double uncut_angle_start,
  const G4double uncut_angle_end)
{
  G4String part_name;
  part_name = name + "_g4tubs";
  G4Tubs *tubs = new G4Tubs(part_name, inner_radius, outer_radius,
			    height/2.0, uncut_angle_start, uncut_angle_end);
  
  part_name = name + "_g4tubs_logicalVolume";
  G4LogicalVolume *logical =
    new G4LogicalVolume(tubs, material, part_name);
  
  part_name = name + "_g4tubs_physicalVolume";  
  G4VPhysicalVolume *physical =
    new G4PVPlacement(transform, logical, part_name, WORLD_LOGICAL,
		      false, 0);
  //create object and pack pointers to there:
  g4solid_object<G4Tubs> *truba = new g4solid_object<G4Tubs>();
  truba->set(tubs, logical, physical);
  return truba;
}  
//-------

g4solid_object<G4Box> * make_box(G4LogicalVolume *WORLD_LOGICAL,
				 const G4String name,
				 G4Material *material,
				 const G4ThreeVector placement,
				 const G4double x,
				 const G4double y,
				 const G4double z,
				 G4RotationMatrix *pRot)
{
  G4String part_name;
  part_name = name + "_g4box";
  G4Box *pbox = new G4Box(part_name, x, y, z);
  
  part_name = name + "_g4box_logicalVolume";
  G4LogicalVolume *logical =
    new G4LogicalVolume(pbox, material, part_name);
  
  part_name = name + "_g4box_physicalVolume";  
  G4VPhysicalVolume *physical =
    new G4PVPlacement(pRot, placement, logical, part_name, WORLD_LOGICAL,
		      false, 0);
  //create object and pack pointers to there:
  g4solid_object<G4Box> *korobka = new g4solid_object<G4Box>();
  korobka->set(pbox, logical, physical);
  return korobka;
}
//-------

g4solid_object<G4Box> * make_box( G4LogicalVolume *WORLD_LOGICAL,
				  const G4String name,
				  G4Material *material,
				  const G4Transform3D transform,
				  const G4double x,
				  const G4double y,
				  const G4double z )
{
  G4String part_name;
  part_name = name + "_g4box";
  G4Box *pbox = new G4Box(part_name, x, y, z);
  
  part_name = name + "_g4box_logicalVolume";
  G4LogicalVolume *logical =
    new G4LogicalVolume(pbox, material, part_name);
  
  part_name = name + "_g4box_physicalVolume";  
  G4VPhysicalVolume *physical =
    new G4PVPlacement(transform, logical, part_name, WORLD_LOGICAL,
		      false, 0);
  //create object and pack pointers to there:
  g4solid_object<G4Box> *korobka = new g4solid_object<G4Box>();
  korobka->set(pbox, logical, physical);
  return korobka;
}
