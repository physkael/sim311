//
// Simple lead-encased NaI detector geometry setup
//
// (C) 2012 Kael Hanson
//

#include <G4Material.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4LogicalVolume.hh>
#include <G4ThreeVector.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>
#include "globals.hh"

#include "ScintillatorDetectorConstruction.hh"
#include "MySteppingAction.hh"

using namespace CLHEP;

ScintillatorDetectorConstruction::ScintillatorDetectorConstruction() :
    world(NULL), leadCastle(NULL)
{
}

ScintillatorDetectorConstruction::~ScintillatorDetectorConstruction()
{
}

G4VPhysicalVolume* ScintillatorDetectorConstruction::Construct()
{
    G4Element* stikstof = new G4Element("Nitrogen", "N" , 7.0 ,  14.01*g/mole);
    G4Element* zuurstof = new G4Element("Oxygen"  , "O" , 8.0 ,  16.00*g/mole);
    G4Element* natrium  = new G4Element("Sodium"  , "Na", 11.0,  22.99*g/mole);
    G4Element* jodium   = new G4Element("Iodine"  , "I" , 53.0, 126.90*g/mole);
    
    G4Material* Air = new G4Material("Air", 1.29*mg/cm3, 2);
    Air->AddElement(stikstof, 0.70);
    Air->AddElement(zuurstof, 0.30);
    
    G4Material* NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(natrium, 1);
    NaI->AddElement(jodium, 1);
    
    G4Material* Al = new G4Material("Aluminum", 13.0, 26.98*g/mole, 2.70*g/cm3);
    G4Material* Pb = new G4Material("Lead", 82., 207.19*g/mole, 11.35*g/cm3);

    //////////////////////////////////////////////////
    //                                              //
    // \\  //                                       //
    //  \\//                                        //
    //   \/   O L U M E  D E F I N I T I O N S      //
    //                                              //
    //////////////////////////////////////////////////
    G4double worldX = 7.0 * cm;
    G4double worldY = 7.0 * cm;
    G4double worldZ = 50.0 * cm;
    G4LogicalVolume* theWorldLogVol = 
        new G4LogicalVolume(new G4Box("DeWereld", worldX, worldY, worldZ), 
                            Air, "TheLogicalWorld");
    theWorldLogVol->SetVisAttributes(G4VisAttributes(true));  // Can't see the world volume
	theWorldLogVol->SetVisAttributes(G4VisAttributes(G4Color(0.1, 0.1, 0.2, 0.05)));

    world = new G4PVPlacement(NULL, G4ThreeVector(), theWorldLogVol, 
                              "ThePhysicalWorld", NULL, false, 0, true);
    G4double leadX = 5.0 * cm;
    G4double leadY = 5.0 * cm;
    G4double leadZ = 10.0 * cm;
    G4LogicalVolume* theLeadCastle = 
        new G4LogicalVolume(new G4Box("LoodDoos", leadX, leadY, leadZ),
                            Pb, "LeadCastle");
    theLeadCastle->SetVisAttributes(G4VisAttributes(G4Color(0.65, 0.75, 0.55, 0.5)));
    leadCastle = new G4PVPlacement(0, G4ThreeVector(), theLeadCastle,
                                   "LeadCastle", theWorldLogVol, false, 0, true);

    // The NaI crystal scintillator assembly - hermetically sealed in Al case
    G4double scintRadius = 2.54 * cm;
    G4double scintLength = 2.50 * cm;
    G4double scintCaseR  = scintRadius + 0.1 * cm;
    G4double scintCaseL  = scintLength + 0.1 * cm;    
    G4LogicalVolume* NaICaseLogVol = 
        new G4LogicalVolume(new G4Tubs("NaIShield", 0, scintCaseR, scintCaseL, 0.0, 2*pi*radian), 
                            Al, "NaIHermetic");
    NaICaseLogVol->SetVisAttributes(G4VisAttributes(G4Color(0.75, 0.25, 0.65, 0.1)));
    G4LogicalVolume* theNaICrystalLogVol =
        new G4LogicalVolume(new G4Tubs("DeKristal", 0, scintRadius, scintLength, 0.0, 2*pi*radian), 
                            NaI, "TheNaICrystal");
    theNaICrystalLogVol->SetVisAttributes(G4VisAttributes(G4Color(0.1, 0.2, 0.25, 0.25)));
    scintCase = new G4PVPlacement(NULL, 
                            G4ThreeVector(0.0, 0.0, scintCaseL - leadZ),
                            NaICaseLogVol,
                            "NaIShieldPhysical",
                            theLeadCastle,
                            false, 0, true);
    scintCrystal = new G4PVPlacement(NULL, 
                            G4ThreeVector(0.0, 0.0, 0.0), 
                            theNaICrystalLogVol, 
                            "scintillatingCrystal",
                            NaICaseLogVol, false, 0, true);
    
    
    MySteppingAction* stepAction = MySteppingAction::GetInstance();
    stepAction->SetCrystalLogicalVolume(theNaICrystalLogVol);
    stepAction->SetLeadLogicalVolume(theLeadCastle);
    
    return world;
}

