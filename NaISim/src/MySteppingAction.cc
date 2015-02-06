//
//  MySteppingAction.cc
//  N01
//
//  Created by Kael Hanson on 1/29/12.
//  Copyright (c) 2012 Université Libre de Bruxelles. All rights reserved.
//

#include <iostream>
#include <G4Step.hh>
#include <G4StepPoint.hh>
#include <G4TouchableHistory.hh>
#include "MySteppingAction.hh"

MySteppingAction* MySteppingAction::singletonInstance = NULL;

MySteppingAction::MySteppingAction() : crystal(NULL), lead(NULL)
{ 
    Reset();
}

MySteppingAction::~MySteppingAction() 
{
}

MySteppingAction* MySteppingAction::GetInstance() 
{
    if (singletonInstance == NULL) singletonInstance = new MySteppingAction;
    return singletonInstance;
}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    
    G4LogicalVolume* vol = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
    

    if (vol == lead) {
        sawLead = true;
        if (sawCrystal) scatterOut = true;
    }
    else if (vol == crystal) {
        sawCrystal = true;
        if (sawLead) scatterIn = true;
    }

    double dE = step->GetTotalEnergyDeposit();

//    G4cout << "CurVol: " << vol->GetName() << " " <<
//        sawCrystal << sawLead << step->IsFirstStepInVolume() <<
//        " dE " << dE << std::endl;
    
    if (vol != crystal) return;
    dEdX += dE; 
}

void MySteppingAction::Reset()
{
    scatterIn = scatterOut = false;
    sawLead   = sawCrystal = false;
    dEdX = 0.0;
}
