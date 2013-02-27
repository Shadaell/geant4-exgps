#ifndef GEOM_OBJECTS
#define GEOM_OBJECTS

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include <string>

class geom_object
{
 public:
  /** ID number, assigned at creation*/
  int id;
  
 public:
  geom_object()
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
  
  ~geom_object()
    {
      if(logical_set && logical != NULL) delete logical;
      if(physical_set && physical != NULL) delete physical;
    }
  
  /** Name the object.*/
  void set_name(const std::string new_name)
  {
    name = new_name;
  }
  /** Get name of the object.*/
  std::string get_name()
  {
    return name;
  }
  
  /** Return pointer to G4LogicalVolume of the object.*/
  G4LogicalVolume* get_logical()
  {
    return logical;
  }

  /** Return pointer to G4VPhysicalVolume of the object.*/
  G4VPhysicalVolume* get_physical()
  {
    return physical;
  }

  
  /** Return bool value whether this class is good to use in geometry.
      If inner pointers to G4LogicalVolume and G4VPhysicalVolume objects
      are non NULL, then RETURN TRUE, FALSE OTHERWISE.
      \return true/false if object pointers have been/(not been) set.
  */
  virtual bool is_good()
  {
    return (logical_set && physical_set && 
	    logical != NULL && physical!= NULL)?
      true : false;
  }
  
 protected:
  std::string name;
  bool logical_set;
  bool physical_set;
  G4LogicalVolume *logical;
  G4VPhysicalVolume *physical;
  
};

class cylinder : public geom_object
{
  /** helps to build a cylindrical object.
      A class that contains 3 important pointer for GGEANT4
      geometrical object:
      G4Tubs *, G4LogicalVolume*, G4VPhysicalVolume*
      From which one can build a geometry.
  **/  
public:

 cylinder(): geom_object()
  {
    tubs = NULL;
    tubs_set = false;
  }
  
  ~cylinder()
  {
    if(tubs_set) delete tubs;
  }
  /** Assign inner pointers to given G4Tubs,
      logical and physical volume pointers.
      \param pointer to G4Tubs, I will use this value don't delete pointer.
      \param pointer to G4LogicalVolume, I will use this value don't delete pointer.
      \param pointer to G4VPhysicalVolume, I will use this value don't delete pointer.
  */
  void set(  G4Tubs *pointer_tubs,
	     G4LogicalVolume *pointer_logical,
	     G4VPhysicalVolume *pointer_physical)
  {
    tubs_set = true;
    tubs = pointer_tubs;
    logical_set = true;
    logical = pointer_logical;
    physical_set = true;
    physical = pointer_physical;
  }

  /** Get object properties from this class, these are:
      pointer to G4Tubs, pointer to G4LogicalVolume, pointer to G4VPhysicalVolume.
      Method will assign given argument pointers to inner G4Tubs,
      logical and physical volume poitners.
      \param pointer_tubs : target G4Tubs pointer, will be changed.
      \param pointer_logical : target G4LogicalVolume pointer, will be changed.
      \param pointer_physical : target G4VPhysicalVolume pointer, will be changed.
      \return 'true' if the object is valid, 'false' otherwise (you should not use obtained pointers then).
  */
  bool get(  G4Tubs *pointer_tubs,
	     G4LogicalVolume *pointer_logical,
	     G4VPhysicalVolume *pointer_physical)
  {
    pointer_tubs = tubs;
    pointer_logical = logical;
    pointer_physical= physical;
    return is_good();
  }

  /** Return pointer to G4Tubs of the object.*/
  G4Tubs* get_tubs()
  {
    return tubs;
  }
  
  /** Return bool value whether this class is good to use in geometry.
      If inner pointers to G4Tubs, G4LogicalVolume and G4VPhysicalVolume objects are non NULL, then RETURN TRUE, FALSE OTHERWISE.
      \return true/false if object pointers have been/(not been) set.
  */
  bool is_good()
  {
    return (tubs_set && logical_set && physical_set && 
	    tubs != NULL && logical != NULL && physical!= NULL)?
      true : false;
  }
  
private:
  
  bool tubs_set;
  G4Tubs *tubs;
  
};

class box : public geom_object
{
  /** helps to build a box.
      A class that contains 3 important pointer for GGEANT4
      geometrical object:
      G4Box *, G4LogicalVolume*, G4VPhysicalVolume*
      From which one can build a geometry.
  **/
public:

 box(): geom_object()
  {
    p_box = NULL;
    box_set = false;
  }
  
  ~box()
  {
    if(box_set) delete p_box;
  }
  /** Assign inner pointers to given G4Tubs,
      logical and physical volume pointers.
      \param pointer to G4Tubs, I will use this value don't delete pointer.
      \param pointer to G4LogicalVolume, I will use this value don't delete pointer.
      \param pointer to G4VPhysicalVolume, I will use this value don't delete pointer.
  */
  void set(  G4Box *pointer_box,
	     G4LogicalVolume *pointer_logical,
	     G4VPhysicalVolume *pointer_physical)
  {
    box_set = true;
    p_box = pointer_box;
    logical_set = true;
    logical = pointer_logical;
    physical_set = true;
    physical = pointer_physical;
  }

  /** Get object properties from this class, these are:
      pointer to G4Box, pointer to G4LogicalVolume, pointer to G4VPhysicalVolume.
      Method will assign given argument pointers to inner G4Box,
      logical and physical volume poitners.
      \param pointer_box : target G4Box pointer, will be changed.
      \param pointer_logical : target G4LogicalVolume pointer, will be changed.
      \param pointer_physical : target G4VPhysicalVolume pointer, will be changed.
      \return 'true' if the object is valid, 'false' otherwise (you should not use obtained pointers then).
  */
  bool get(  G4Box *pointer_box,
	     G4LogicalVolume *pointer_logical,
	     G4VPhysicalVolume *pointer_physical)
  {
    pointer_box = p_box;
    pointer_logical = logical;
    pointer_physical= physical;
    return is_good();
  }

  /** Return pointer to G4Box of the object.*/
  G4Box* get_box()
  {
    return p_box;
  }
  
  /** Return bool value whether this class is good to use in geometry.
      If inner pointers to G4Box, G4LogicalVolume and G4VPhysicalVolume objects are non NULL, then RETURN TRUE, FALSE OTHERWISE.
      \return true/false if object pointers have been/(not been) set.
  */
  bool is_good()
  {
    return (box_set && logical_set && physical_set && 
	    p_box != NULL && logical != NULL && physical!= NULL)?
      true : false;
  }
  
private:
  
  bool box_set;
  G4Box *p_box;
  
};


#endif
