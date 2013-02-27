/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef DetectorSD_h
#define DetectorSD_h 1
#include "Hist1i.h"
#include "G4VSensitiveDetector.hh"
class G4Step;
class RunAction;

class DetectorSD: public G4VSensitiveDetector 
{
  public:
    DetectorSD(G4String);
    ~DetectorSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    void EndOfEvent(G4HCofThisEvent*);

  /** 
      if 'true' -- that indicates that this sensitive detector
      is used for other purposes than energy deposit calculation.
  */
  bool is_spec_counter;
  
  /** Set histogram properties.
      \param minimum value of range. 
      Anything lesser than this setpoint will be ignored.
      
      \param maximum value of range. 
      Anything greater than this setpoint will be ignored.
      
      \param Quantity of histogram bins.
  */
  void set_histo(const double min, const double max,
		 const unsigned int n_bins, 
		 const unsigned int E_units=1);

  /** Clear histogramms to start a new data collection.
   */
  void reset_histo();
  
  /** Write al histogramms to files. 
      It is recommended to call it simultaneously with 
      RunAction::EndOfRunAction(const G4Run* ).
  */
  void save_histo();

  /** Get known about particle type from given name
      and add it's energy to certain histogram
      \param Pointer to particle definition
      \param energy value
      \param energy unit, case 0: eV, case 1: keV, case 2: MeV.
      
  */
  void fill_hist(const G4String &pname, double energy, unsigned EUNIT=1);

  
  /** Get known about particle type from given definition
      and add it's energy to certain histogram
      \param Pointer to particle definition
      \param Energy in keV units.
  */
  void fill_hist(G4ParticleDefinition *pdef, double energy);
  
  /** Book particle's energy to the histogram.
      \param particle's energy, eV.
   */
  void fill_hist(double );
  
  /** Book electron's energy to the histogram.
      \param particle's energy, eV.
  */
  void fill_hist_electron(double );

  /** Book electron's energy to the histogram.
      \param particle's energy, eV.
  */
  void fill_hist_positron(double );
  
  /** Book proton's energy to the histogram.
      \param particle's energy, eV.
  */
  void fill_hist_proton(G4double);

  /** Book alpha particle's energy to the histogram.
      \param particle's energy, eV.
  */
  void fill_hist_alpha(G4double);
  
  /** Book neutron's energy to the histogram.
      \param particle's energy, eV.
  */
  void fill_hist_neutron(G4double);
  
  /** Book photon's energy to the histogram.
      \param particle's energy
  */
  void fill_hist_photon(G4double);
  
  /** Book photon's energy to the histogram.
      \param particle's energy
  */
  void fill_hist_other(G4double);

private:
  /** private method, it calls fill() method of pointer 
      (*hist_pointer) to object   of class Hist1i.*/
  void fill_hist_pointer(Hist1i *hist_pointer, const G4double energy);
  
private:
  
  long long e_count;
  long long gamma_count;
  
  double d_hist_min, d_hist_max;
  unsigned d_hist_bins;
  unsigned  d_energy_units;
  
  /** Histogram of energy deposit for all particles excep 'other'.*/
  Hist1i* hist;
  Hist1i* photon_hist;
  Hist1i* electron_hist;
  Hist1i* positron_hist;
  Hist1i* proton_hist;
  Hist1i* neutron_hist;
  Hist1i* alpha_hist;
  Hist1i* other_hist;   


  
  private:
  RunAction* runAction;
  
  /** On each event this pointer will be assigned to the currently
      processed track via 'G4Step* step->GetTrack()' method*/
  G4Track *track;
  
  /** Name of the currenlty processed track's particle,
      like "gamma","neutron" ... etc.*/
  G4String particle_name;
  G4double detEnergy;
};

#endif
