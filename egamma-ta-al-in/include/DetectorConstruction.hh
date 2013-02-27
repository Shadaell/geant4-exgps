/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "DetectorSD2.hh"

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

#include <vector>
#include "G4VUserDetectorConstruction.hh"
#include "DetectorSD.hh"
#include "DetectorConstructionMessenger.hh"

#include <string>
#include "geom_objects.h"
#include <math.h>

#ifndef M_PI
        #define M_PI 3.141592653589793
#endif

class DetectorConstruction : public G4VUserDetectorConstruction
{                 
  public:
    DetectorConstruction();
    ~DetectorConstruction();
  
  G4VPhysicalVolume* Construct();
  
  /** Vector of pointers to DetectorSD objects.
      It will be filled on this->Construct() method call.
      Address of this object may be passed to other places.
   */
  std::vector<DetectorSD2*> vector_DetectorSD;

  /** Vector of pointers to DetectorSD objects.
      It will be filled on this->Construct() method call.
      Address of this object may be passed to other places.
   */
  std::vector<DetectorSD2*> vector_DetectorSD_COUNTERS;


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
  void read_parameters(const std::map<G4String, G4double> &str_double_map);
  
  /** Set histogram properties.
      \param minimum value of range. 
      Anything lesser than this setpoint will be ignored.
      
      \param maximum value of range. 
      Anything greater than this setpoint will be ignored.
      
      \param Quantity of histogram bins.
      
      \param energy units: 0 -- eV, 1 -- keV, 2 -- MeV
  */
  void set_histo(const double min, const double max,
		 const unsigned int n_bins, 
		 const unsigned int E_units=1);
  
  void use_Pb_shield(bool use)
  {
    with_Pb_shield = use;
  }
  /** Change distance from source to Tl-plane*/
  void set_GUN_TL_distance(const G4double dist)
  {
    gap1_distance = dist;
  }

  /** Change distance from Tl-plane to Al-bar.*/
  void set_TL_AL_distance(const G4double dist)
  {
    TL_AL_distance = dist;
  }

  /** Change distance from Tl-plane to the detector.*/
  void set_TL_DETECTOR_distance(const G4double dist)
  {
    gap2_distance = dist;
  }
    
  /** Change aluminum bar thickness*/
  void set_AL_thickness(const G4double thick)
  {
    aluminium_thick = thick;    
  }

  /** Change aluminum bar diameter*/
  void set_AL_diameter(const G4double diam)
  {
    if(diam>0) aluminium_diameter = diam;
  }

  /** Change Tallium-cylinder diameter*/
  void set_TL_thickness(const G4double thick)
  {
    if(thick>0) cap_thickness = thick;
  }
  /** Change Tallium-cylinder diameter*/
  void set_TL_diameter(const G4double diam)
  {
    cap_diameter = diam;
  }
  
  /** Change target detector thickness.
      \param a value with units, set to 0 if you want to disable
      real physical In-detector and use only "false" ones.
  */
  void set_TG_DET_thickness(const G4double thick)
  {
    detector_height = thick;
  }
  
  /** Change target detector thickness.
      \param a value with units
   */
  void set_TG_DET_diameter(const G4double diam)
  {
    detector_diameter=diam;
  }

  /** Change target mass. If zero mass -- then no target, 
      we will make only virtual detector there.
      \param a value with units of gramm. 
   */
  void set_TG_DET_mass(const G4double mass)
  {
    target_mass = mass;
  }
  
  /** Set number of histogram bins.
      \param quantity of bins.
   */
  void set_histo_bins(const G4int bins)
  {
    d_hist_bins = bins;
  }

  /** Set number of histogram min value.
      \param a value in units that are currently set, keV by default.
   */
  void set_histo_min(const G4double min)
  {
    d_hist_min = min;
  }

  /** Set number of histogram max value.
      \param a value in units that are currently set, keV by default.
   */
  void set_histo_max(const G4double max)
  {
    d_hist_max = max;
  }


  /**Return value of energy units used.
     \return energy units used: case 0: eV, case 1: keV, case 2: MeV.
   */
  unsigned hist_energy_units()
  {
    return d_energy_units;
  }
  
protected:
  /**
     Create a new object of DetectorSD class and record it's
     pointer value to vector of pointers.
     
     \param name of the sensitive region
     
  */
  DetectorSD2 * new_detector_sensitive(const G4String name);
  
private:

  bool with_Pb_shield;
  
  DetectorConstructionMessenger *messenger;
  
  double d_hist_min, d_hist_max;
  unsigned d_hist_bins;
  unsigned  d_energy_units;

  G4double target_mass;
  G4double aluminium_thick;
  G4double aluminium_diameter;
  
  /** діаметр циліндра детектора:*/
  G4double detector_diameter;
  
  /** висота циліндра детектора*/
  G4double detector_height;
  
  //** відстань 0 координат Tl-пластини:*/
  G4double gap1_distance;
  
  /** відстань 0 координат до In-детектора*/
  G4double gap2_distance;
  
  /**діаметр пластини із Tl, де відбувається (e,gamma):*/
  G4double cap_diameter;
  
  /**товщина пластини із Tl, де відбувається (e,gamma):*/
  G4double cap_thickness; //<- висота циліндра цеї штуки ^

  G4double void_thickness;
  
  G4double target_distance;
  
  /** target detector's diameter(real physical detector of given material),
      set it to 0 if you want to disable it.*/
  G4double TG_DET_thickness;
  
  G4double TL_AL_distance;
};

#endif

