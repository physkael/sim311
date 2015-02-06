//
//  MySteppingAction.hh
//  N01
//
//  Created by Kael Hanson on 1/29/12.
//  Copyright (c) 2012 Université Libre de Bruxelles. All rights reserved.
//

#ifndef N01_MySteppingAction_hh
#define N01_MySteppingAction_hh

#include <G4UserSteppingAction.hh>

class MySteppingAction : public G4UserSteppingAction
{
private:
    const G4LogicalVolume* crystal;
    const G4LogicalVolume* lead;
    G4double dEdX;
    bool sawCrystal;
    bool sawLead;
    bool scatterIn;
    bool scatterOut;
    static MySteppingAction* singletonInstance;
    MySteppingAction();
    
public:
    virtual ~MySteppingAction();
    virtual void UserSteppingAction(const G4Step*);
    
    G4double GetdEdX() { return dEdX; }
    
    void Reset();
    
    static MySteppingAction* GetInstance();
    
    void SetCrystalLogicalVolume(const G4LogicalVolume* vol)
    {
        crystal = vol;
    }
    
    void SetLeadLogicalVolume(const G4LogicalVolume* vol)
    {
        lead = vol;
    }
    
    bool isOutScatter() { return scatterOut; }
    bool isInScatter() { return scatterIn; }
};

#endif
