#include<G4RunManager.hh> 
#include<G4UImanager.hh> 
#include<G4UIterminal.hh> 
#include<G4VisExecutive.hh> 
#include<G4Material.hh> 
#include<G4UserRunAction.hh> 
#include<G4Run.hh> 
#include<iostream> 
#include<string> 
#include<CLHEP/Random/Random.h> 
#include "DetectorConstruction.hh" 
#include "PrimaryGeneratorAction.hh" 
#include "EventAction.hh" 
#include "SteppingAction.hh" 
#include "SteppingVerbose.hh" 
#include "PhysicsList.hh" 
  using namespace std; 
   
   const char macros[]="vis.mac";
   class RunAction: public G4UserRunAction 
   { 
   public: 
     void BeginOfRunAction(const G4Run* aRun) 
     { 
       G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
     } 
   };
   int main(int argc,char** argv) 
   {
     class RunAction: public G4UserRunAction
   {
   public:
     void BeginOfRunAction(const G4Run* aRun)
     {
       G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
     }
   };
   int main(int argc,char** argv);
   {
    G4VSteppingVerbose::SetInstance(new SteppingVerbose);
    CLHEP::HepRandom::setTheSeed(time(0)+getpid());
      G4RunManager * runManager = new G4RunManager;
      DetectorConstruction* detector_c = new DetectorConstruction;
       runManager->SetUserInitialization(detector_c);
      G4VUserPhysicsList *p = new PhysicsList;
       runManager->SetUserInitialization(p);
      G4VisManager* visManager = new G4VisExecutive;
       visManager->Initialize();
       runManager->SetUserAction(new PrimaryGeneratorAction);
       runManager->SetUserAction(new RunAction);  
       runManager->SetUserAction(new EventAction);
       runManager->SetUserAction(new SteppingAction);
       runManager->Initialize();
      cout<<"===============================================================";
      cout<<endl;
      cout<< *(G4Material::GetMaterialTable()) << endl;
      cout<<"===============================================================";
      cout<<endl;
      G4UImanager * UI = G4UImanager::GetUIpointer();  
      G4UIsession * session = new G4UIterminal();      
       UI->ExecuteMacroFile(macros);
       delete session;
       delete visManager;
       delete runManager;
       return 0;
   }

    #ifndef DetectorConstruction_h 
   #define DetectorConstruction_h
  
  #include<globals.hh> 
  #include<G4VUserDetectorConstruction.hh> 
  #include<G4VSolid.hh>
  #include<G4LogicalVolume.hh> 
  #include<G4VPhysicalVolume.hh> 
  #include<G4Material.hh>
   class World {
   protected:
     G4VSolid *solid;
     G4LogicalVolume *logic;
     G4VPhysicalVolume *physic;
     G4Material *mater;
     double sizex, sizey, sizez;
   public:
     World(double size_x, double size_y, double size_z, G4Material *mater_=NULL);
     operator G4LogicalVolume*() {return logic;}
     G4LogicalVolume *getLogic() {return logic;}
     //    void setLogic(G4LogicalVolume *volA);
     G4VSolid *getSolid() {return solid;}
     G4VPhysicalVolume *getPhysic() {return physic;}
   };
   class DetectorConstruction : public G4VUserDetectorConstruction
   {
    public:
     DetectorConstruction();
     ~DetectorConstruction();
     G4VPhysicalVolume* Construct();
     
   protected:
   World *world;
   };
   
   #endif