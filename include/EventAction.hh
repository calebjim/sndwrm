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
/// \file EventAction.hh
/// \brief Definition of the EventAction class
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "Run.hh"
#include "PrimaryGeneratorAction.hh"
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
  public:
  EventAction();
  EventAction(PrimaryGeneratorAction* prim);
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
   
    void AddEdep (G4int iVol, G4double Edep, G4double time, G4double weight);
    void AddEdepTot(G4double);
    void AddEdepL(G4double );
    void AddEdepLhit(G4double  );
    void AddEdepQ(G4double );
    void AddEdepLhitInt(G4double);
    
    void AddArapuca(const G4String& key) {
    // check if eVname is already in the list
    if (std::find(fArapucaList.begin(), fArapucaList.end(), key) == fArapucaList.end()) {
        // not found → it's a new unique Arapuca
        fArapucaList.push_back(key);   // add to the list
        fNUniqueArapucas++;               // increment count
        }
    }
    G4int GetNUniqueArapucas() const { return fNUniqueArapucas; }
    void  ClearArapucas() { fArapucaList.clear(); fNUniqueArapucas = 0; }
    
    void SetInelProc(bool inel) { if (inel) fInel = true;};
    bool GetInelProc() { return fInel;};
    void SetFiducial(bool fid) {fFiducial = fid;};              
    bool GetFiducial() {return fFiducial;}; 
    void SetProcVtx(const G4ThreeVector &vtx) { procVtx[0] = vtx[0];   procVtx[1] = vtx[1];   procVtx[2] = vtx[2];}
    std::vector<G4int>& GetNucleiVec() {return fNucleiVec;};
    void SetNucleiVec(G4int pnucID);
    void CapEGam(G4double );
    
    PrimaryGeneratorAction* GetPrimGenAct() {return fPGA;};

    bool RegisterArapucaHit(G4int tid) {
        return fCountedArapucaHits.insert(tid).second;
    }
    void ClearArapucaHits() { fCountedArapucaHits.clear(); }

  private:
    PrimaryGeneratorAction* fPGA;
    G4double fEdep1,   fEdep2;
    G4double fEdepEvt, fEdepL, fEdepLhit, fEdepQ, fEdepLhitInt;
    G4double fWeight1, fWeight2;
    G4double fTime0;
    bool fInel;
    bool fFiducial;
    std::default_random_engine generator;
  
    G4double EnergyCalc(G4double, Run*, G4ThreeVector*  );
    G4ThreeVector GetProcVtx() {return procVtx;};
    G4ThreeVector procVtx;
    std::vector<G4int> fNucleiVec;
    std::vector<G4double> fEGamCap;
    G4double fEGamCapSum;

    std::vector<G4String> fArapucaList;
    G4int fNUniqueArapucas = 0;
    std::set<G4int> fCountedArapucaHits;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
