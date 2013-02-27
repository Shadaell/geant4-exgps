/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "DetectorSD.hh"

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
  std::vector<DetectorSD*> vector_DetectorSD;

  /** Vector of pointers to DetectorSD objects.
      It will be filled on this->Construct() method call.
      Address of this object may be passed to other places.
   */
  std::vector<DetectorSD*> vector_DetectorSD_COUNTERS;


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
  
protected:
  /**
     Create a new object of DetectorSD class and record it's
     pointer value to vector of pointers.
     
     \param name of the sensitive region
     
     \param If true -- then each SteppingAction will track any particle
     etting to this sensitive volume and book it's energy to the
     histograms.
  */
  DetectorSD * new_detector_sensitive(const G4String name, 
				      bool Ais_spec_counter=false);


private:

  double d_hist_min, d_hist_max;
  unsigned d_hist_bins;
  unsigned  d_energy_units;
  
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
};

#endif

