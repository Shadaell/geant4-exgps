/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef RunAction_h
#define RunAction_h 1

class Hist1i;

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "DetectorSD.hh"
#include <vector>

class G4Run;

class RunAction: public G4UserRunAction
{
public:
  RunAction();
  
  // /** Create runaction with pointer to the vector with pointers to
  //     sensitive detector objects.
  //     \param address of the vector with DetectorSD* pointers;
  // */
  // RunAction(std::vector<DetectorSD*> &vector_DetectorSD);
  
  ~RunAction();

  /** Vector of pointers to DetectorSD objects.
      The user may have to set this pointer manually
      e..g run_action->DSD_vector = &other_vector;
      
      Why do we need it? 
      Method RunAction::BeginOfRunAction(G4Run*)
      will try to access this pointer and call 
      DetectorSD::reset_histo();

      Method RunAction::EndOfRunAction(G4Run*)
      will try to access this pointer and call 
      DetectorSD::save_histo() which will write all 
      histograms created by DetectorSD objects to files.;

   */
  std::vector<DetectorSD*> *DSD_vector;

  std::vector<DetectorSD*> *DSD_COUNTERS_vector;
  
  /** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::reset_histo() which will make all 
      DetectorSD objects ready to start capturing events.;
  */
  void BeginOfRunAction(const G4Run*);

  /** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::save_histo() which will write all 
      histograms created by DetectorSD objects to files.;
  */
  void EndOfRunAction(const G4Run*);

  
  
};

#endif
