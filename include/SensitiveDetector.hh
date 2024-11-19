#ifndef SENSITIVEDETECTOR
   #define SENSITIVEDETECTOR
   
   #include<G4VSensitiveDetector.hh>
   
   class G4Step;
   class G4TouchableHistory;
   class SensitiveDetector: public G4VSensitiveDetector
   {
   private:
    static const int NOBINS = 1000;
    const double HIST_MAX;
    const double HIST_MIN;
    int histogram[NOBINS];
   public:
     SensitiveDetector(G4String name);
     ~SensitiveDetector();
     G4bool ProcessHits(G4Step *step, G4TouchableHistory *hist);
     void EndOfEvent(int nEvent);
   };
   
   #endif /* SENSITIVEDETECTOR */
