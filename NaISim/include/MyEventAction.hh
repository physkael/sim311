//
//  MyEventAction.hh
//  N01
//
//  Created by Kael Hanson on 1/29/12.
//  Copyright (c) 2012 Université Libre de Bruxelles. All rights reserved.
//

#ifndef N01_MyEventAction_hh
#define N01_MyEventAction_hh

#include <G4UserEventAction.hh>
#include "MySteppingAction.hh"

class MyEventAction : public G4UserEventAction
{
private:
    MySteppingAction* step;
    
public:
    MyEventAction(MySteppingAction*);
    virtual ~MyEventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
};

#endif
