#ifndef QUICK_GEOM_H
#define QUICK_GEOM_H

#include "g4solid_object.h"

/**
   Make a cylinder. Function takes 6 important parametrs + 3 optional.
   @param Pointer to the worlds logical volume.
   @param name of object.
   @param material.
   @param vector of placement in world;
   @param Radius of the cylinder (1*cm by default)
   @param Height of the cylinder (1*cm by default)
     
   @param (Optional)Inner radius of the cylinder (0*cm by default, solid)
   @param (Optional)uncut matter of cylinder start -- 0*deg by default.
   It's needed when you make a sectorial cut of cylinder.
   This value means FROM what value of angle the cylinder matter is present.
     
   @param Pointer to G4RotationMatrix, if not 0, then the object will be rotated.
     
   @param (Optional)uncut matter of cylinder start -- 360*deg by default
   It's needed when you make a sectorial cut of cylinder.
   This value means TO what value of angle the cylinder matter is present.
	    
   \return A pointer to object of class 'g4solid_object<G4Tubs>'.
   See "g4solid_object.hh"!
   To use that object later you just call it's method:
   object->get(  G4Tubs *pointer_tubs,
   G4LogicalVolume *pointer_logical,
   G4VPhysicalVolume *pointer_physical).

*/
g4solid_object<G4Tubs> * make_cylinder
              ( G4LogicalVolume *WORLD_LOGICAL,
		const G4String name,
		G4Material *material,
		const G4ThreeVector placement,
		const G4double outer_radius = 1*cm,
		const G4double height = 1*cm,
		const G4double inner_radius = 0*cm,
		G4RotationMatrix *pRot = 0,
		const G4double uncut_angle_start = 0*deg,
		const G4double uncut_angle_end = 360*deg);

/**
   Make a box. Function takes 7 important parametrs.
   @param Pointer to the worlds logical volume.
   @param name of object.
   @param material.
   @param vector of placement in world;
     
   @param Pointer to G4RotationMatrix, if not 0, 
   then the object will be rotated.

   \return A pointer to object of class 'g4solid_object<G4Box>'.
   See "g4solid_object.hh"!
   To use that object later you just call it's method:
   object->get(  G4Box *pointer_tubs,
   G4LogicalVolume *pointer_logical,
   G4VPhysicalVolume *pointer_physical).
*/
g4solid_object<G4Box> * make_box( G4LogicalVolume *WORLD_LOGICAL,
				  const G4String name,
				  G4Material *material,
				  const G4ThreeVector placement,
				  const G4double x,
				  const G4double y,
				  const G4double z,
				  G4RotationMatrix *pRot = 0);

/**
   Make a cylinder. Function takes 6 important parametrs + 3 optional.
   @param Pointer to the worlds logical volume.
   @param name of object.
   @param material.
   @param Transformation via G4Transform3D class, example:
   G4RotationMatrix rot_matrix;
   rot_matrix.rotateZ(20*deg);
   G4Transform3D transform = G4Transform3D(rot_matrix,G4ThreeVector(x,y,z))

   @param Radius of the cylinder (1*cm by default)
   @param Height of the cylinder (1*cm by default)
     
   @param (Optional)Inner radius of the cylinder (0*cm by default, solid)
   @param (Optional)uncut matter of cylinder start -- 0*deg by default.
   It's needed when you make a sectorial cut of cylinder.
   This value means FROM what value of angle the cylinder matter is present.
     
   @param (Optional)uncut matter of cylinder start -- 360*deg by default
   It's needed when you make a sectorial cut of cylinder.
   This value means TO what value of angle the cylinder matter is present.

   \return A pointer to object of class 'g4solid_object<G4Tubs>'.
   See "g4solid_object.hh"!
   To use that object later you just call it's method:
   object->get(  G4Tubs *pointer_tubs,
   G4LogicalVolume *pointer_logical,
   G4VPhysicalVolume *pointer_physical).
*/
g4solid_object<G4Tubs> *make_cylinder
             ( G4LogicalVolume *WORLD_LOGICAL,
	       const G4String name,
	       G4Material *material,
	       const G4Transform3D transform,
	       const G4double outer_radius = 1*cm,
	       const G4double height = 1*cm,
	       const G4double inner_radius = 0*cm,
	       const G4double uncut_angle_start = 0*deg,
	       const G4double uncut_angle_end = 360*deg);

/**
   Make a box. Function takes 7 important parametrs.
   @param Pointer to the worlds logical volume.
   @param name of object.
   @param material.

   @param Transformation via G4Transform3D class, example:
   G4RotationMatrix rot_matrix;
   rot_matrix.rotateZ(20*deg);
   G4Transform3D transform = G4Transform3D(rot_matrix,G4ThreeVector(x,y,z))
     
   @param Pointer to G4RotationMatrix, if not 0, 
   then the object will be rotated.

   \return A pointer to object of class 'g4solid_object<G4Box>'.
   See "g4solid_object.hh"!
   To use that object later you just call it's method:
   object->get(  G4Box *pointer_tubs,
   G4LogicalVolume *pointer_logical,
   G4VPhysicalVolume *pointer_physical).
*/
g4solid_object<G4Box> * make_box
        ( G4LogicalVolume *WORLD_LOGICAL,
	  const G4String name,
	  G4Material *material,
	  const G4Transform3D transform,
	  const G4double x,
	  const G4double y,
	  const G4double z );

/** This funcion makes a box with a hole. Caller should provide box size, hole size,
    hole's center = box center.
   @param Pointer to the worlds logical volume.
   @param name of object.
   @param material.
   @param placement: placement of the box center.
   @param BoxDimensions: sizeof of the box (x,y,z)=(width, height, depth)
   @param HoleDimensions: sizeof hole inside the box (x,y,z)=(width, height, depth) (should be smaller than box).
   @param PVectorOfPointers: (optional, NULL by default) pointer to vector to which pointers of type (g4solid_object<G4Box>*)
   will be pushed(the parts of this box) if the pointer is not NULL.
   @param pRot: (optional, NULL by default) rotation matrix

 */
void make_box_with_hole( G4LogicalVolume *WORLD_LOGICAL,
			 const G4String name,
			 G4Material *material,
			 const G4ThreeVector placement,
			 G4ThreeVector BoxDimensions,
			 G4ThreeVector HoleDimensions,
			 std::vector< g4solid_object<G4Box>* > *PVectorOfPointers = NULL,
			 G4RotationMatrix *pRot = NULL);


#endif
