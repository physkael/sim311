//
// Simple lead-encased NaI detector geometry setup
//
// (C) 2012 Kael Hanson
//

#include <G4Material.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4SubtractionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4ThreeVector.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>
#include <G4RotationMatrix.hh>
#include "globals.hh"

#include "PropCtrDetectorConstruction.hh"
#include "MySteppingAction.hh"

using namespace CLHEP;

PropCtrDetectorConstruction::PropCtrDetectorConstruction() :
    world(NULL), propCtrPhysical(NULL), propGasPhysical(NULL)
{
}

PropCtrDetectorConstruction::~PropCtrDetectorConstruction()
{
}

G4VPhysicalVolume* PropCtrDetectorConstruction::Construct()
{
    G4Element* stikstof = new G4Element("Nitrogen", "N" , 7.0 ,  14.01*g/mole);
    G4Element* zuurstof = new G4Element("Oxygen"  , "O" , 8.0 ,  16.00*g/mole);

    G4Material* propGas = new G4Material("ArgonGas", 54.0, 131.30*g/mole,  5.88*mg/cm3);
    G4Material* Al      = new G4Material("Aluminum", 13.0,  26.98*g/mole,  2.70*g/cm3);
    G4Material* Pb		= new G4Material("Lead"    , 82.0, 207.19*g/mole, 11.35*g/cm3);
	G4Material* Cu		= new G4Material("Copper"  , 29.0,  63.54*g/mole,  8.94*g/cm3);
    
    G4Material* Air = new G4Material("Air", 1.29*mg/cm3, 2);
    Air->AddElement(stikstof, 0.70);
    Air->AddElement(zuurstof, 0.30);
        

    //////////////////////////////////////////////////
    //                                              //
    // \\  //                                       //
    //  \\//                                        //
    //   \/   O L U M E  D E F I N I T I O N S      //
    //                                              //
    //////////////////////////////////////////////////
    G4double worldX = 10.0 * cm;
    G4double worldY = 20.0 * cm;
    G4double worldZ = 10.0 * cm;
    G4LogicalVolume* theWorldLogVol = 
        new G4LogicalVolume(new G4Box("DeWereld", worldX, worldY, worldZ), 
                            Air, "TheLogicalWorld");
    theWorldLogVol->SetVisAttributes(G4VisAttributes(true));  // Can't see the world volume
	theWorldLogVol->SetVisAttributes(G4VisAttributes(G4Color(0.1, 0.1, 0.2, 0.05)));

    world = new G4PVPlacement(NULL, G4ThreeVector(), theWorldLogVol, 
                              "ThePhysicalWorld", NULL, false, 0, true);

    G4double copperPlateX = 4.5 * cm;
    G4double copperPlateY = 9.0 * cm;
    G4double copperPlateZ = 0.5 * cm;
	G4Box* plate = new G4Box("Plate", copperPlateX, copperPlateY, copperPlateZ);
    G4LogicalVolume* cupLV = new G4LogicalVolume(
		new G4SubtractionSolid(G4String("BafflePlate"), plate, 
		new G4Tubs("Porthole", 0, 1.0*cm, copperPlateZ, 0.0, 2*pi*radian)),
		Cu, "CopperPlate");

    cupLV->SetVisAttributes(G4VisAttributes(G4Color(0.75, 0.25, 0.35, 0.75)));
    foreShield = new G4PVPlacement(0, G4ThreeVector(0, 0, -4.5*cm), cupLV,
		"ForeShield", theWorldLogVol, false, 0, true);
	aftShield  = new G4PVPlacement(0, G4ThreeVector(0, 0, +4.5*cm), cupLV,
		"AftShield ", theWorldLogVol, false, 0, true);
	topShield  = new G4PVPlacement(
		new G4RotationMatrix(90.0*deg, 90.0*deg, 90.0*deg), 
		G4ThreeVector(+5.0*cm, 0, 0), cupLV,
		"ForeShield", theWorldLogVol, false, 0, true);

    // The NaI crystal scintillator assembly - hermetically sealed in Al case
    G4double propCtrR = 3.50 * cm;
    G4double propCtrL = 8.00 * cm;
    G4double propCasR  = propCtrR + 0.025*cm;
    G4double propCasL  = propCtrL + 0.05*cm;    
    G4LogicalVolume* propCtrAssemblyLV = new G4LogicalVolume(
		new G4Tubs("PCCylinder", 0, propCasR, propCasL, 0.0, 2*pi*radian), 
        Al, "ProportionalCounterAssembly");
    propCtrAssemblyLV->SetVisAttributes(G4VisAttributes(G4Color(0.75, 0.75, 0.85, 0.25)));
    G4LogicalVolume* propCtrGasLV = new G4LogicalVolume(
		new G4Tubs("GasCylinder", 0, propCtrR, propCtrL, 0.0, 2*pi*radian), 
		propGas, "ProportionalGasVolume");
    propCtrGasLV->SetVisAttributes(G4VisAttributes(G4Color(0.25, 0.1, 0.65, 0.25)));

    propCtrPhysical = new G4PVPlacement(
		new G4RotationMatrix(0.0*deg, 90.0*deg, 0.0*deg), 
		G4ThreeVector(), propCtrAssemblyLV, 
		"PropCtrPhysical", theWorldLogVol, false, 0, true);

    propGasPhysical = new G4PVPlacement(NULL, G4ThreeVector(), propCtrGasLV, 
        "PropGas", propCtrAssemblyLV, false, 0, true);
      
    MySteppingAction* stepAction = MySteppingAction::GetInstance();
    stepAction->SetCrystalLogicalVolume(propCtrGasLV);
    stepAction->SetLeadLogicalVolume(cupLV);
    
    return world;
}

