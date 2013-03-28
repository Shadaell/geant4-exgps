/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#include "RunAction.hh"
#include "Hist1i.h"

#include "G4Run.hh"
#include "Randomize.hh"

RunAction::RunAction() 
{

}

// /** Create runaction with pointer to the vector with pointers to
//     sensitive detector objects.
//     \param address of the vector with DetectorSD* pointers;
// */
// RunAction::RunAction(std::vector<DetectorSD*> &vector) 
// {
//   this->DSD_vector = &vector;
// }

RunAction::~RunAction()
{
  DSD_vector=NULL;
}

/** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::reset_histo() which will make all 
      DetectorSD objects ready to start capturing events.;
*/
void RunAction::BeginOfRunAction(const G4Run*)
{
  G4cout << "\n*********************************************\n";
  G4cout << "\n\n=======================\nBegin of RunAction:\n";
  

  if(this->DSD_vector!=NULL)
    {
      
      if(!DSD_vector->empty())
	{
	  std::vector<DetectorSD*>::iterator iter;
	  for(iter=DSD_vector->begin(); iter<DSD_vector->end(); iter++)
	    (*iter)->reset_histo();
	  
	  for(iter=DSD_COUNTERS_vector->begin(); iter<DSD_COUNTERS_vector->end(); iter++)
	    (*iter)->reset_histo();

	}
    }
}

/** 
      Method RunAction::EndOfRunAction(G4Run*)
      will try to access the pointer
      std::vector<DetectorSD*> *DSD_vector;
      and call 
      DetectorSD::save_histo() which will write all 
      histograms created by DetectorSD objects to files.;
*/
void RunAction::EndOfRunAction(const G4Run* )
{
  if(this->DSD_vector!=NULL && (!DSD_vector->empty()) )
    {
      std::vector<DetectorSD*>::iterator iter;
      for(iter=DSD_vector->begin(); iter<DSD_vector->end(); iter++)
	(*iter)->save_histo();
    }

  if(this->DSD_COUNTERS_vector!=NULL && (!DSD_COUNTERS_vector->empty()) )
    {
      std::vector<DetectorSD*>::iterator iter;
      for(iter=DSD_COUNTERS_vector->begin(); iter<DSD_COUNTERS_vector->end(); iter++)
	(*iter)->save_histo();
    }
}

