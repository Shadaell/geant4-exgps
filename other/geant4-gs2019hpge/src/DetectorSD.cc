/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#include "DetectorSD.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Step.hh"

DetectorSD::DetectorSD(G4String name): G4VSensitiveDetector(name)
{
  // получаем указатель на класс RunAction
  // мы будем вызывать его метод RunAction::FillHist
  // для заполнения гистограммы спектра поглощенной энергии
  runAction = (RunAction*) G4RunManager::GetRunManager()->GetUserRunAction();
}

DetectorSD::~DetectorSD() {}

void DetectorSD::Initialize(G4HCofThisEvent*)
{
  // в начале события сбрасываем энергию поглощенную детектором
  detEnergy = 0;
}

G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  // через детектор летит частица
  // добавляем энергию потерянную частицей
  // к счетчику энергии детектора
  G4double edep = step->GetTotalEnergyDeposit();
  detEnergy += edep;

//  G4Track* track = step->GetTrack();
//  G4String particleName = track->GetDefinition()->GetParticleName();
//  if (particleName == "gamma")
//    return false;

  return true;
}

void DetectorSD::EndOfEvent(G4HCofThisEvent*)
{
  // сохраняем энергию накопленную за событие в детекторе
  // в гистограмму
  runAction->FillHist(detEnergy);
}

