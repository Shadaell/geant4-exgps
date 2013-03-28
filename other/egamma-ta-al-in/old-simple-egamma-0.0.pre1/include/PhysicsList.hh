/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsList: public G4VUserPhysicsList
{
  public:
    PhysicsList();
   ~PhysicsList();

  protected:
    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

    // these methods Construct physics processes and register them
    void ConstructEM();
};

#endif

