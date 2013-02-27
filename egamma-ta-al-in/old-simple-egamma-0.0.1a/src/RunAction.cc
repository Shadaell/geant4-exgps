/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#include "RunAction.hh"
#include "Hist1i.h"

#include "G4Run.hh"
#include "Randomize.hh"

RunAction::RunAction() {}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*)
{
  // создаем гистограмму
  // от 0 до 1000, с 1000 каналов
  hist = new Hist1i(0, 44000, 44000);
}

void RunAction::FillHist(G4double energy)
{
  if (energy > 0)
    // заполняем гистограмму величиной энергии в кэВ
    //hist->fill(energy/keV);
    hist->fill(energy/keV);
}

void RunAction::EndOfRunAction(const G4Run* )
{
  // сохраняем гистограмму в файл
  // второй параметр - первая строка файла
  hist->save("spectrum.csv", "\"energy, keV\", N");
}

