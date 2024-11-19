#include<G4Step.hh>
   #include<fstream>
   #include<iostream>
   #include"SensitiveDetector.hh"
using namespace CLHEP;
   
   using namespace std;
    SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name),
                                HIST_MAX(50*MeV),
                                HIST_MIN(5 *MeV)
   {
     for(int i = 0; i<NOBINS; i++)
       histogram[i] = 0;
   }
    G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
   {
      double energy = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
      double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
      int index = int(floor((energy-HIST_MIN)/bin_width));
      if(index >= 0 && index < NOBINS)
        histogram[index]++;
        step->GetTrack()->SetTrackStatus(fStopAndKill);
     return true;
   }
    SensitiveDetector::~SensitiveDetector()
   {
    std::ofstream file("spectrum.dat");
      double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
     for(int i = 0; i<NOBINS; i++)
     {
      double energy = i*bin_width + HIST_MIN;
      file << std::setw(15) << energy/MeV << " "
        << std::setw(15) << histogram[i] << std::endl;
     }
   }