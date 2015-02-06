//
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
//
//
// $Id: exampleN01.cc,v 1.6 2006-06-29 17:47:10 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - exampleN01
// --------------------------------------------------------------

#include <Randomize.hh>
#include <G4RunManager.hh>
#include <QGSP_BERT.hh>
#include <QGSP.hh>
#include <G4VisExecutive.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UIExecutive.hh>

#include "PropCtrDetectorConstruction.hh"
#include "ExN01PrimaryGeneratorAction.hh"

#include "MySteppingAction.hh"
#include "MyEventAction.hh"

int main(int argc, char* argv[])
{
    long seed = 29181473;
	int optind = 1;

    CLHEP::HepRandom::setTheEngine(new CLHEP::Ranlux64Engine(seed, 5));
    
    // Construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    // set mandatory initialization classes
    G4VUserDetectorConstruction* detector = new PropCtrDetectorConstruction;
    runManager->SetUserInitialization(detector);
    G4VUserPhysicsList* physics = new QGSP;
    runManager->SetUserInitialization(physics);

    // set mandatory user action class
    G4VUserPrimaryGeneratorAction* gen_action = new ExN01PrimaryGeneratorAction;
    runManager->SetUserAction(gen_action);
    
    MySteppingAction* step = MySteppingAction::GetInstance();
    runManager->SetUserAction(step);
    runManager->SetUserAction(new MyEventAction(step));

    // Initialize G4 kernel
    runManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (optind < argc) {
		UImanager->ExecuteMacroFile(argv[optind++]);
    } else {
        G4VisManager* visualizationManager = new G4VisExecutive;
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        visualizationManager->Initialize();
		UImanager->ExecuteMacroFile("init.mac");
        ui->SessionStart();
        delete ui;        
        delete visualizationManager;
    }
    delete runManager;
    return 0;
}


