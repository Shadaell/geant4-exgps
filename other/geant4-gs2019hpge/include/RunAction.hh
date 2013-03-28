/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#ifndef RunAction_h
#define RunAction_h 1

class Hist1i;

#include "G4UserRunAction.hh"
#include "globals.hh"
class G4Run;

class RunAction: public G4UserRunAction
{
  public:
    RunAction();
   ~RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    
    void FillHist(G4double);

  private:
    Hist1i* hist;
};

#endif
