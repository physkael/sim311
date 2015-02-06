//
//  MyEventAction.cc
//  N01
//
//  Created by Kael Hanson on 1/29/12.
//  Copyright (c) 2012 Université Libre de Bruxelles. All rights reserved.
//

#include <iostream>
#include <G4Event.hh>
#include <G4VPhysicalVolume.hh>
#include "MyEventAction.hh"


MyEventAction::MyEventAction(MySteppingAction* _step) : step(_step)
{
    
}

MyEventAction::~MyEventAction()
{
    
}

void MyEventAction::BeginOfEventAction(const G4Event* event)
{
    step->Reset();
}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
    G4cout << "DE: " << step->GetdEdX() << " " <<
        step->isInScatter() << " " << step->isOutScatter() << std::endl;
}
