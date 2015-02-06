

#ifndef ScintillatorDetectorConstruction_H
#define ScintillatorDetectorConstruction_H 1

#include "G4LogicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"

class ScintillatorDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    ScintillatorDetectorConstruction();
    ~ScintillatorDetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
    
    // Physical volumes
    G4VPhysicalVolume* world;
    G4VPhysicalVolume* leadCastle;
    G4VPhysicalVolume* scintCrystal;
    G4VPhysicalVolume* scintCase;
};

#endif

