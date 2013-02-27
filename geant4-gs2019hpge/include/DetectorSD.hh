/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#ifndef DetectorSD_h
#define DetectorSD_h 1

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
    
  private:
    RunAction* runAction;
    G4double detEnergy;
};

#endif
