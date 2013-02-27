/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef DetectorSD2_h
#define DetectorSD2_h 1
#include "G4VSensitiveDetector.hh"
#include <ios>
#include <iostream>
#include <fstream>
#include <map>
#include <utility>

#define MAX_BATCH_SIZE 200000

class G4Step;
class RunAction;


class DetectorSD2: public G4VSensitiveDetector 
{
  /**
     This sensitive detector class counts deposited particle's energy
     and it's initial kinetic enegy(without losses).
   */
public:

  DetectorSD2(G4String);
  ~DetectorSD2();

  /** disable deposited energy when detector used as virtual counter.
   * May speedup the simulation.*/
  void DisableDepositedEnergyCount();
  void EnableDepositedEnergyCount();

  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);

  /** Set this variable to tru if you want debug output.
   false by default.*/
  bool debug_output;
  
  /** Get known about particle type from given name
      and add it's energy to certain histogram
      \param Pointer to particle definition
      \param energy value
      \param energy unit, case 0: eV, case 1: keV, case 2: MeV.
      
  */
  void fill_hist(const G4String &pname, const double energy,
		 const unsigned EUNIT=1);

  
  /** Get known about particle type from given definition
      and add it's energy to certain histogram
      \param Pointer to particle definition
      \param Energy in keV units.
  */
  void fill_hist(const G4ParticleDefinition *pdef, const double energy);

  /** Get known about particle type from given name
      and add it's energy to certain histogram
      \param Pointer to particle definition
      \param energy value
      \param energy unit, case 0: eV, case 1: keV, case 2: MeV.
      
  */
  void fill_hist_deposited(const G4String &pname, const double energy,
			   const unsigned EUNIT=1);

  
  /** Get known about particle type from given definition
      and add it's energy to certain histogram
      \param Pointer to particle definition
      \param Energy in keV units.
  */
  void fill_hist_deposited(const G4ParticleDefinition *pdef, const double energy);
  
  /** Make the detector save tracked kinetic energies of certain particles to the files.
      \param iterator of map<G4String, std::vector<double>>
      \param optional : whether clear vector after saving[YES, by default]
  */
  void save_Ekinetic(std::map<G4String, std::vector<double> >::iterator &named_particle_iterator, bool noclear = false);

  /** Make the detector save deposited  energies of certain particles to the files.
      \param iterator of map<G4String, std::vector<double>>
      \param optional : whether clear vector after saving[YES, by default]
  */
  void save_Edeposited(std::map<G4String, std::vector <double> >::iterator &named_particle_iterator, bool noclear = false);

  /** Save all data vectors to files. Call this at the end of work.*/
  void save_all();
private:
  
  /** clear the vectors with raw spectra.*/
  void clear_raw_data();
  
  /** Dump the data from vector to file.*/
  void dump_vector(const char *filename,
		   std::vector<double> &vector,
		   bool append = true ) const;
private:
  bool d_deposited_count;
  unsigned  d_energy_units;
  
  std::map<G4String, std::vector <double> > named_vector_map_Ekin;
  std::map<G4String, std::vector <double> > named_vector_map_Edep;
  std::map<G4String, std::vector <double> >::iterator the_iterator;
  
  
private:
  unsigned long temp_count;
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
