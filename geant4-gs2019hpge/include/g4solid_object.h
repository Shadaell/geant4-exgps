
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

#ifndef G4SOLID_OBJECT
#define G4SOLID_OBJECT

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include <string>

template<class G4SolidClass>
class g4solid_object
{
  /** A class template which contains 3 important pointers:
     (1) a pointer to derivative class of G4Solid (like G4Box, G4Tubs etc.);
     (2) a pointer to G4LogicalVolume;
     (3) a pointer to G4VPhysicalVolume;
     There are methods to get their values and to set their values.
     The class itself will only help to track whether those pointers have been set or not,
     whether those are usable. 
     
     Usage example:

     g4solid_object<G4Box> *object = new g4solid_object();
     object->set_name(std::string("some box"));
     
     object->set(solid, logical, physical);
     //where arguments are objects of classes:
     // G4Box* solid, G4LogicalVolume* logical, G4VPhysicalVolume* physical
     
     //gettings pointers:
     object->get(p_solid, p_logical, p_physical)
     
     //or.....
     G4Box *p_box = object->get_solid();
     G4LogicalVolume* logical = object->get_logical();
     G4VPhysicalVolume* physical = object->get_physical();
     //...
     std::string namestr = object->get_name();

     
   */
 public:
  /** ID number, assigned at creation*/
  int id;
  
 public:
  g4solid_object();
  
  ~g4solid_object();
  
  /** Name the object.*/
  void set_name(const std::string new_name);
  
  /** Get name of the object.*/
  std::string get_name();
  
  /** Return pointer to G4LogicalVolume of the object.*/
  G4LogicalVolume* get_logical();

  /** Return pointer to G4VPhysicalVolume of the object.*/
  G4VPhysicalVolume* get_physical();

  /** \brief  Assign inner pointers to given pointer to G4Solid derivative class,
              logical and physical volume pointers.
      \param pointer_shape :  pointer to object of G4Solid derivative class.
                              I will use this value don't delete pointer.
      \param pointer to G4Tubs, I will use this value don't delete pointer.
      \param pointer to G4LogicalVolume, I will use this value don't delete pointer.
      \param pointer to G4VPhysicalVolume, I will use this value don't delete pointer.
  */
  void set(   G4SolidClass *pointer_shape,
	      G4LogicalVolume *pointer_logical,
	      G4VPhysicalVolume *pointer_physical);

  /** \brief  Get object properties from this class, these are:
      pointer to G4Tubs, pointer to G4LogicalVolume, pointer to G4VPhysicalVolume.
      Method will assign given argument pointers to inner G4Tubs,
      logical and physical volume poitners.
      
      \param pointer_shape : target  pointer to object of G4Solid derivative class,
                             will be changed.
      \param pointer_logical : target G4LogicalVolume pointer, will be changed.
      \param pointer_physical : target G4VPhysicalVolume pointer, will be changed.
      \return 'true' if the object is valid, 'false' otherwise 
                     (if false then you should not use obtained pointers).
  */
  bool get(  G4SolidClass *pointer_shape,
	     G4LogicalVolume *pointer_logical,
	     G4VPhysicalVolume *pointer_physical);

  /** Return pointer to G4Tubs of the object.*/
  G4SolidClass* get_solid();

  /** Return bool value whether this class is good to use in geometry.
      If inner pointers to G4LogicalVolume and G4VPhysicalVolume objects
      are non NULL, then RETURN TRUE, FALSE OTHERWISE.
      \return true/false if object pointers have been/(not been) set.
  */
  bool is_good();

 protected:
  std::string name;
  bool logical_set;
  bool physical_set;
  bool shape_set;
  G4LogicalVolume *logical;
  G4VPhysicalVolume *physical;
  G4SolidClass *shape;
};

template<class G4SolidClass>
g4solid_object<G4SolidClass>::g4solid_object()
{
  id = rand();
  char number[16];
  for(int cnt = 0; cnt < 16; cnt++) number[cnt] = 0x00;
  sprintf(number, "%d", id);
  name = "geom_obj_";
  name.append(number);
      
  logical_set = false;
  physical_set = false;
  logical = NULL;
  physical = NULL;
}

template<class G4SolidClass>
g4solid_object<G4SolidClass>::~g4solid_object()
{
  if(logical_set && logical != NULL) delete logical;
  if(physical_set && physical != NULL) delete physical;
  if(shape_set && shape != NULL) delete shape;
}
  
/** Name the object.*/
template<class G4SolidClass>
void g4solid_object<G4SolidClass>::set_name(const std::string new_name)
{
  name = new_name;
}

/** Get name of the object.*/
template<class G4SolidClass>
std::string g4solid_object<G4SolidClass>::get_name()
{
  return name;
}
  
/** Return pointer to G4LogicalVolume of the object.*/
template<class G4SolidClass>
G4LogicalVolume* g4solid_object<G4SolidClass>::get_logical()
{
  return logical;
}

/** Return pointer to G4VPhysicalVolume of the object.*/
template<class G4SolidClass>
G4VPhysicalVolume* g4solid_object<G4SolidClass>::get_physical()
{
  return physical;
}

template<class G4SolidClass>
void g4solid_object<G4SolidClass>
     ::set( G4SolidClass *pointer_shape,
	    G4LogicalVolume *pointer_logical,
	    G4VPhysicalVolume *pointer_physical)
{
  shape_set = true;
  shape = (pointer_shape);
  logical_set = true;
  logical = (pointer_logical);
  physical_set = true;
  physical = (pointer_physical);
}

template<class G4SolidClass>
bool g4solid_object<G4SolidClass>
     ::get(  G4SolidClass *pointer_shape,
	     G4LogicalVolume *pointer_logical,
	     G4VPhysicalVolume *pointer_physical)
{
  pointer_shape = shape;
  pointer_logical = logical;
  pointer_physical= physical;
  return is_good();
}

/** Return pointer to G4Tubs of the object.*/
template<class G4SolidClass>
G4SolidClass* g4solid_object<G4SolidClass>::get_solid()
{
  return shape;
}

template<class G4SolidClass>  
bool g4solid_object<G4SolidClass>::is_good()
{
  return (logical_set && physical_set && shape_set &&
	  logical != NULL && physical != NULL && shape !=NULL)?
    true : false;
}



#endif
