#include <iostream>
#include <vector>
#include <TChain.h>
#include <TFile.h>
#include <cmath>
#include <cstdlib>
#include <TRandom3.h>
#include "svm.h"
#include "libsvm_container.h"
#include "csvc_interface.h"
#include "timer.h"
using namespace std;
void setBackground(TTree* background, svm_container & svm, svm_container & svm_eval, size_t & nbkg, size_t & nbkg_eval, std::vector<TH1D*>& bkg_hists){
  float_t  weight, leadJetPt, maxBTagVal, secondMaxBTagVal, subLeadJetPt, sumJetPt, pho1_ptoM, pho1_eta, pho1_idmva, pho2_ptoM, pho2_eta, pho2_idmva, nJets;
  background->SetBranchAddress( "weight", &weight );
  background->SetBranchAddress("leadJetPt", &leadJetPt); 
  background->SetBranchAddress("nJets", &nJets);  
  background->SetBranchAddress("maxBTagVal", &maxBTagVal);  
  background->SetBranchAddress("secondMaxBTagVal", &secondMaxBTagVal); 
  background->SetBranchAddress("subLeadJetPt", &subLeadJetPt);  
  background->SetBranchAddress("sumJetPt",&sumJetPt);
  background->SetBranchAddress("pho1_ptoM",&pho1_ptoM);
  background->SetBranchAddress("pho2_ptoM",&pho2_ptoM);
  background->SetBranchAddress("pho1_eta",&pho1_eta);
  background->SetBranchAddress("pho2_eta",&pho2_eta);
  background->SetBranchAddress("pho1_idmva",&pho1_idmva);
  background->SetBranchAddress("pho2_idmva",&pho2_idmva);
  for (UInt_t i=0; i<background->GetEntries(); i++) {
    background->GetEntry(i);
    bkg_hists.at(0)->Fill(leadJetPt,weight); 
    bkg_hists.at(1)->Fill(nJets,weight);  
    bkg_hists.at(2)->Fill(maxBTagVal,weight);  
    bkg_hists.at(3)->Fill(secondMaxBTagVal,weight); 
    bkg_hists.at(4)->Fill(subLeadJetPt,weight);  
    bkg_hists.at(5)->Fill(sumJetPt,weight);
    bkg_hists.at(6)->Fill(pho1_ptoM,weight);
    bkg_hists.at(7)->Fill(pho2_ptoM,weight);
    bkg_hists.at(8)->Fill(pho1_eta,weight);
    bkg_hists.at(9)->Fill(pho2_eta,weight);
    bkg_hists.at(10)->Fill(pho1_idmva,weight);
    bkg_hists.at(11)->Fill(pho2_idmva,weight);
    
    if(i%4 < 2) {
      svm.set_feature(leadJetPt); 
      svm.set_feature(nJets);  
      svm.set_feature(maxBTagVal);  
      svm.set_feature(secondMaxBTagVal); 
      svm.set_feature(subLeadJetPt);  
      svm.set_feature(sumJetPt);
      svm.set_feature(pho1_ptoM);
      svm.set_feature(pho2_ptoM);
      svm.set_feature(pho1_eta);
      svm.set_feature(pho2_eta);
      svm.set_feature(pho1_idmva);
      svm.set_feature(pho2_idmva);
      svm.set_event(4.*weight);
      nbkg++;
    } else {
      svm_eval.set_feature(leadJetPt); 
      svm_eval.set_feature(nJets);  
      svm_eval.set_feature(maxBTagVal);  
      svm_eval.set_feature(secondMaxBTagVal); 
      svm_eval.set_feature(subLeadJetPt);  
      svm_eval.set_feature(sumJetPt);
      svm_eval.set_feature(pho1_ptoM);
      svm_eval.set_feature(pho2_ptoM);
      svm_eval.set_feature(pho1_eta);
      svm_eval.set_feature(pho2_eta);
      svm_eval.set_feature(pho1_idmva);
      svm_eval.set_feature(pho2_idmva);
      svm_eval.set_event(4.*weight);
      nbkg_eval++;
    }    
  }
}
void setSignal(TTree* signal, svm_container & svm, svm_container & svm_eval, std::vector<TH1D*> sig_hists){
  float_t  weight, leadJetPt, maxBTagVal, secondMaxBTagVal, subLeadJetPt, sumJetPt, pho1_ptoM, pho1_eta, pho1_idmva, pho2_ptoM, pho2_eta, pho2_idmva, nJets;
  signal->SetBranchAddress( "weight", &weight );
  signal->SetBranchAddress("leadJetPt", &leadJetPt); 
  signal->SetBranchAddress("nJets", &nJets);  
  signal->SetBranchAddress("maxBTagVal", &maxBTagVal);  
  signal->SetBranchAddress("secondMaxBTagVal", &secondMaxBTagVal); 
  signal->SetBranchAddress("subLeadJetPt", &subLeadJetPt);  
  signal->SetBranchAddress("sumJetPt",&sumJetPt);
  signal->SetBranchAddress("pho1_ptoM",&pho1_ptoM);
  signal->SetBranchAddress("pho2_ptoM",&pho2_ptoM);
  signal->SetBranchAddress("pho1_eta",&pho1_eta);
  signal->SetBranchAddress("pho2_eta",&pho2_eta);
  signal->SetBranchAddress("pho1_idmva",&pho1_idmva);
  signal->SetBranchAddress("pho2_idmva",&pho2_idmva);
  for (UInt_t i=0; i<signal->GetEntries(); i++) {
    signal->GetEntry(i);
    sig_hists.at(0)->Fill(leadJetPt,weight); 
    sig_hists.at(1)->Fill(nJets,weight);  
    sig_hists.at(2)->Fill(maxBTagVal,weight);  
    sig_hists.at(3)->Fill(secondMaxBTagVal,weight); 
    sig_hists.at(4)->Fill(subLeadJetPt,weight);  
    sig_hists.at(5)->Fill(sumJetPt,weight);
    sig_hists.at(6)->Fill(pho1_ptoM,weight);
    sig_hists.at(7)->Fill(pho2_ptoM,weight);
    sig_hists.at(8)->Fill(pho1_eta,weight);
    sig_hists.at(9)->Fill(pho2_eta,weight);
    sig_hists.at(10)->Fill(pho1_idmva,weight);
    sig_hists.at(11)->Fill(pho2_idmva,weight);
    
    if(i%4 < 2) {
      svm.set_feature(leadJetPt); 
      svm.set_feature(nJets);  
      svm.set_feature(maxBTagVal);  
      svm.set_feature(secondMaxBTagVal); 
      svm.set_feature(subLeadJetPt);  
      svm.set_feature(sumJetPt);
      svm.set_feature(pho1_ptoM);
      svm.set_feature(pho2_ptoM);
      svm.set_feature(pho1_eta);
      svm.set_feature(pho2_eta);
      svm.set_feature(pho1_idmva);
      svm.set_feature(pho2_idmva);
      svm.set_event(4.*weight);
    } else {
      svm_eval.set_feature(leadJetPt); 
      svm_eval.set_feature(nJets);  
      svm_eval.set_feature(maxBTagVal);  
      svm_eval.set_feature(secondMaxBTagVal); 
      svm_eval.set_feature(subLeadJetPt);  
      svm_eval.set_feature(sumJetPt);
      svm_eval.set_feature(pho1_ptoM);
      svm_eval.set_feature(pho2_ptoM);
      svm_eval.set_feature(pho1_eta);
      svm_eval.set_feature(pho2_eta);
      svm_eval.set_feature(pho1_idmva);
      svm_eval.set_feature(pho2_idmva);
      svm_eval.set_event(4.*weight);
    }    
  }
}


int main(){
  srand(1);  
  int  nvar = 12;
  /* SVM containers: in this example we will use auto split functionality therefore we will not use seperate containers for training and test - giving the right numbers here will only affect performance / you can give an estimation as well */
  svm_container svm(nvar,40000);
  svm_container svm_eval(nvar,20000);
  /* debugging histograms */  
  std::vector<TH1D*> bkg_hist_dump(nvar);  
  std::vector<TH1D*> sig_hist_dump(nvar);  
  TString name1, name2;
  for(Long_t ind = 0; ind < nvar; ind++ ){
    name1="feature_" ; name2 = "Background distribution of feature ";
    bkg_hist_dump.at(ind) = new TH1D (name1+ind+"bkg" , name2+ind, 505 , -5., 500.);
    name1= TString("feature_") ; name2 = TString("Signal distribution of feature ");
    sig_hist_dump.at(ind) = new TH1D (name1+ind+"sig" , name2+ind, 505 , -5., 500.);
  } 
  vector<double> vars(nvar);
  double weight = 0.; 
  size_t nbkg_tot  = 0;
  size_t nbkg_eval = 0;
  int sep = 0; 

   TString fnamesignal = "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_TTHToGG_M125_13TeV_powheg_pythia8.root";
  TFile *inputsignal = TFile::Open( fnamesignal );
  TTree *signal     = (TTree*)inputsignal->Get("tagsDumper/trees/tth_125_13TeV_TTHHadronicTag");
  std::cout << signal->GetEntries() << std::endl;
  
  
  TFile *inputbackground1 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root" );
  TFile *inputbackground2 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_DiPhotonJetsBox_M40_80-Sherpa.root" );
  TFile *inputbackground3 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_Pythia8.root" );
  TFile *inputbackground4 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root" );
  TFile *inputbackground5 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root" );
  TFile *inputbackground6 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root" );
  TFile *inputbackground7 = TFile::Open( "/eos/user/s/saghosh/Shared/ttHgg_Saclay/For_ttHgg/RootFilesFggRunJobsOutput_20170206_3jets1BloosePtm3NoMVA_postPreAppFreeze/output_TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root" );
  
   
  // --- Register the training and test trees
  
  TTree *background1     = (TTree*)inputbackground1->Get("tagsDumper/trees/dipho_13TeV_TTHHadronicTag");
  std::cout << background1->GetEntries() << std::endl;
  TTree *background2     = (TTree*)inputbackground2->Get("tagsDumper/trees/dipho_13TeV_TTHHadronicTag");
  std::cout << background2->GetEntries() << std::endl;
  TTree *background3     = (TTree*)inputbackground3->Get("tagsDumper/trees/gjet_13TeV_TTHHadronicTag");
  std::cout << background3->GetEntries() << std::endl;
  TTree *background4     = (TTree*)inputbackground4->Get("tagsDumper/trees/gjet_13TeV_TTHHadronicTag");
  std::cout << background4->GetEntries() << std::endl;
  TTree *background5     = (TTree*)inputbackground5->Get("tagsDumper/trees/gjet_13TeV_TTHHadronicTag");
  std::cout << background5->GetEntries() << std::endl;
  TTree *background6     = (TTree*)inputbackground6->Get("tagsDumper/trees/ttgjets_13TeV_TTHHadronicTag");
  std::cout << background6->GetEntries() << std::endl;
  TTree *background7     = (TTree*)inputbackground7->Get("tagsDumper/trees/ttgg_13TeV_TTHHadronicTag");
  std::cout << background7->GetEntries() << std::endl;
   


  setBackground(background1, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setBackground(background2, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setBackground(background3, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setBackground(background4, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setBackground(background5, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setBackground(background6, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setBackground(background7, svm, svm_eval, nbkg_tot, nbkg_eval, bkg_hist_dump);
  setSignal(signal, svm, svm_eval, sig_hist_dump);


  TFile * tut = new TFile("tutorial_debug.root","RECREATE");
  for(Long_t ind = 0; ind < nvar; ind++ ){
    bkg_hist_dump.at(ind)->Write();
    sig_hist_dump.at(ind)->Write();
  } 
  tut->Close();
  /* The numbers should be given to the svm_interface */
  size_t nsamp_tot = svm.svm_cont->size();
  size_t nsig_tot  = nsamp_tot - nbkg_tot;
  size_t neval_tot = svm_eval.svm_cont->size();
  std::vector<int> * output = new vector<int>;
  std::cout << nbkg_tot << std::endl;
  std::cout << " Total event number in the svm container: " << svm.svm_cont->size()      << 
    " total event number in the svm evaluation container: " << svm_eval.svm_cont->size() << std::endl;
  svm_interface * csvc = new csvc_interface(nsamp_tot,nbkg_tot,nsig_tot);
  svm_analyze stop;
  stop.set_filename("tutorial.root");
  stop.set_svm_interface(csvc);
  stop.setup_svm(svm);
  stop.set_eval(svm_eval,nbkg_eval);

  //Enable probabilistic output
  stop.Do_probability_calc();
  //set the systematical unc
  stop.Set_systematical_unc(0.25);
  //set # of threads
  stop.Set_omp_threads(12);

  /*  timer prob;
  stop.Obtain_probabilities(1, 1000.,0.575, output);// c , gamma
  prob.stop("svm training and test takes: ");*/
  timer tmain; 
  tmain.start();
  stop.Scan_parameters(output);
  tmain.stop("scanning parameters takes: ");
  /*
    for(auto it =output->begin(); it!=output->end(); it++){
    std::cout << (*it) << " ";
    } 
  */
  return 0;
}
