// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
///*
// Part of simulation for use with GEANT4 code.
// Author  Bogdan Maslovskiy <blinkofnight(at,doggy,removeme)gmail(dot)>,
// Taras Schevchenko National University of Kyiv 2011
//****************


#include "DetectorSD2.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Step.hh"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

DetectorSD2::DetectorSD2(G4String name): G4VSensitiveDetector(name)
{
  // получаем указатель на класс RunAction
  // мы будем вызывать его метод RunAction::FillHist
  // для заполнения гистограммы спектра поглощенной энергии
  runAction = (RunAction*) G4RunManager::GetRunManager()->GetUserRunAction();
  d_energy_units=1;
  debug_output = false;
  temp_count = 0;
}

DetectorSD2::~DetectorSD2() 
{
  named_vector_map_Ekin.clear();
  named_vector_map_Edep.clear();
}

void DetectorSD2::Initialize(G4HCofThisEvent*)
{
  // в начале события сбрасываем энергию поглощенную детектором
  detEnergy = 0;
}

G4bool DetectorSD2::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  // через детектор летит частица
  // добавляем энергию потерянную частицей
  // к счетчику энергии детектора
  track = step->GetTrack();
  this->particle_name = track->GetDefinition()->GetParticleName();  
  G4double edep = step->GetTotalEnergyDeposit();
  detEnergy += edep;

  if(debug_output)
    {
      G4cout<< "\n---\n"
	    << G4VSensitiveDetector::SensitiveDetectorName
	    << particle_name
	    << " track Deposit energy: "<< edep/keV
	    <<" part. kinetic energy(kev):" << track->GetKineticEnergy()/keV
	    <<"\n";
    }
  return true;
}

void DetectorSD2::EndOfEvent(G4HCofThisEvent*)
{
  // сохраняем энергию накопленную за событие в детекторе
  // в гистограмму
  if(detEnergy > 0)
    fill_hist_deposited(particle_name, detEnergy);
}


/** Get known about particle type from given definition
    and add it's energy to certain histogram
    \param Pointer to particle definition
    \param Energy in keV units.
*/
void DetectorSD2::fill_hist(const G4ParticleDefinition *pdef, const double energy)
{
  if(!pdef || energy < 0) return;
  fill_hist(pdef->GetParticleName(), energy);
}

/** Get known about particle type from given definition
    and add it's energy to certain histogram
    \param Pointer to particle definition
    \param Energy in keV units.
*/
void DetectorSD2::fill_hist_deposited(const G4ParticleDefinition *pdef, const double energy)
{
  if(!pdef || energy < 0) return;
  fill_hist_deposited(pdef->GetParticleName(), energy);
}

/** Get known about particle type from given name
    and add it's energy to certain histogram
    \param Pointer to particle definition
    \param Energy in keV units.
*/
void DetectorSD2::fill_hist(const G4String &pname, const double energy, const unsigned EUNIT)
{
  if(EUNIT <= 2) d_energy_units = EUNIT;
  if(energy < 0) return;
  double value = -1;
  switch(d_energy_units)
    {
    case 0:  value = energy; break;
    case 1:  value = (energy/keV); break;
    case 2:  value = (energy/MeV); break;
    default:
      value = (energy/keV); break;
    }
  
  the_iterator = named_vector_map_Ekin.find(pname);
  if(the_iterator != named_vector_map_Ekin.end())
    {//if the given particle name has been found:
      if(debug_output)
	{
	
	  G4cout << G4VSensitiveDetector::SensitiveDetectorName.data() << "\t" << temp_count << "\t";
	  G4cout << "fill_hist: particle found [" << the_iterator->first << "]\t";
	  G4cout << "Ekin value: " << value << "\n";
	  G4cout << "vector size: "
		 << the_iterator->second.size() << "\n";
	}
      the_iterator->second.push_back(value);
      if(the_iterator->second.size() > MAX_BATCH_SIZE)
	{
	  save_Ekinetic(the_iterator);
	}
    }
  else
    {
      std::vector <double> new_vec;
      new_vec.push_back(value);
      named_vector_map_Ekin.insert(pair<G4String, std::vector <double> >(pname, new_vec));

      if(debug_output)
	{
	  G4cout << G4VSensitiveDetector::SensitiveDetectorName.data() << "\t" << temp_count << "\t";
	  G4cout << "fill_hist: particle NOT FOUND [" << pname << "]\n";
	  G4cout << "Adding new key: " << pname.data();
	  G4cout << "\tEkin  value: " << value << "\n";
	  the_iterator = named_vector_map_Ekin.find(pname);
	  if(the_iterator != named_vector_map_Ekin.end())
	    G4cout << "vector size: "
		   << the_iterator->second.size() << "\n";
	}
      //if this type of particle meets first time
      // -- then create a key and new vector for that
    }
  
  temp_count ++;
}

/** Get known about particle type from given name
    and add it's energy to certain histogram
    \param Pointer to particle definition
    \param Energy in keV units.
*/
void DetectorSD2::fill_hist_deposited(const G4String &pname,
				      const double energy,
				      const unsigned EUNIT)
{
  if(EUNIT <= 2) d_energy_units = EUNIT;
  if(energy < 0) return;
  double value;
  switch(d_energy_units)
    {
    case 0:  value = energy; break;
    case 1:  value = (energy/keV); break;
    case 2:  value = (energy/MeV); break;
    default:
      value = (energy/keV); break;
    }
  
  the_iterator = named_vector_map_Edep.find(pname);
  if(the_iterator != named_vector_map_Edep.end())
    {//if the given particle name has been found:
      the_iterator->second.push_back(value);
      if(the_iterator->second.size() > MAX_BATCH_SIZE)
	{
	  save_Edeposited(the_iterator);
	}
    }
  else
    {
      //if this type of particle meets first time
      // -- then create a key and new vector for that
      std::vector <double> new_vec;
      new_vec.push_back(value);
      named_vector_map_Edep.insert(pair<G4String, std::vector <double> >(pname, new_vec));
    }
			      
}
  
/** clear the vectors with raw spectra.*/
void DetectorSD2::clear_raw_data()
{
  named_vector_map_Ekin.clear();
  named_vector_map_Edep.clear();
}

/** Dump the data from vector to file.*/
void DetectorSD2::dump_vector(const char *filename,
			      std::vector<double> &vector, bool append ) const
{
  if(filename!=NULL && (!vector.empty()))
    {
      char mode[3]; mode[2] = 0x00;
      memmove((void*)mode, (void*)((append)? "a+" : "w+"), 2);
      FILE *fp = fopen(filename, "a+");
      if(fp!=NULL)
	{
	  for(unsigned i = 0; i < vector.size(); i++)
	    fprintf(fp,"%f\n", (float)vector.at(i));
	}
      fclose(fp);
    }
}

void DetectorSD2::save_Ekinetic(std::map<G4String, std::vector <double> >::iterator &named_particle_iterator, bool noclear)
{
  if(named_particle_iterator != (this->named_vector_map_Ekin.end())
     && !named_vector_map_Ekin.empty())
    {
      G4String filename;
      G4String sensDetName = G4VSensitiveDetector::SensitiveDetectorName;
      //make filename:
      filename += sensDetName + "_kinetic_" + named_particle_iterator->first;
      
      switch(d_energy_units)
	{
	case 0:  filename += "_eV_unit.raw"; break;
	case 1:  filename += "_keV_unit.raw"; break;
	case 2:  filename +=  "_MeV_unit.raw"; break;
	default:
	  filename += "_keV_unit.raw"; break;
	}
      if(debug_output)
	{
	  G4cout << "SAVING KINETIC ENERGY VEC:\n"
		 << sensDetName.data()
		 << "\tparticle category: " 
		 << named_particle_iterator->first.data()
		 << "\t N values: "
		 << named_particle_iterator->second.size() << "\n------\n";
	}
      //--write raw particle's energies
      dump_vector(filename, named_particle_iterator->second, true);
      //clear vector:
      if( !noclear)
	named_particle_iterator->second.clear();
    }

}

void DetectorSD2::save_Edeposited(std::map<G4String, std::vector <double> >::iterator &named_particle_iterator, bool noclear)
{
  if(named_particle_iterator != this->named_vector_map_Edep.end()
     && !named_vector_map_Edep.empty())
    {
      G4String filename;
      G4String sensDetName = G4VSensitiveDetector::SensitiveDetectorName;
      //make filename:
      filename += sensDetName + "_deposited_" + named_particle_iterator->first;
      
      switch(d_energy_units)
	{
	case 0:  filename += "_eV_unit.raw"; break;
	case 1:  filename += "_keV_unit.raw"; break;
	case 2:  filename +=  "_MeV_unit.raw"; break;
	default:
	  filename += "_keV_unit.raw"; break;
	}
      if(debug_output)
	{
	  G4cout << "SAVING DEPOSITED ENERGY VEC:\n"
		 << sensDetName.data()
		 << "\tparticle category: " 
		 << named_particle_iterator->first.data()
		 << "\t N values: "
		 << named_particle_iterator->second.size() << "\n------\n";
	}
      //--write raw particle's energies
      dump_vector(filename, named_particle_iterator->second, true);
      if( !noclear)
	named_particle_iterator->second.clear();
    }
}


void DetectorSD2::save_all()
{
  for(the_iterator = named_vector_map_Ekin.begin(); 
      the_iterator != named_vector_map_Ekin.end(); the_iterator++)
    {
      save_Ekinetic(the_iterator);
    }
  for(the_iterator = named_vector_map_Edep.begin(); 
      the_iterator != named_vector_map_Edep.end(); the_iterator++)
    {
      save_Edeposited(the_iterator);
    }
}
