

#ifndef PropCtrDetectorConstruction_H
#define PropCtrDetectorConstruction_H 1

#include "G4LogicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"

class PropCtrDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    PropCtrDetectorConstruction();
    ~PropCtrDetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
    
    // Physical volumes
    G4VPhysicalVolume* world;
    G4VPhysicalVolume* foreShield, *aftShield, *topShield;
    G4VPhysicalVolume* propCtrPhysical, *propGasPhysical;
};

#endif

