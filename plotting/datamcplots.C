#include "setTDRStyle.h"
#include <sstream>
#include <fstream>
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include <vector>
#include "Rtypes.h"
#include "TColor.h"
#include "TVectorF.h"
#include <cstdlib>

void setTDRStyle();
TH1F *create1Dhisto(TString sample,TTree *tree,TString intLumi,TString cuts,TString branch,int bins,float xmin,float xmax,
		    bool useLog,int color, int style,TString name,bool norm,bool data);
TH2F *create2Dhisto(TString name,TTree *tree,TString intLumi,TString cuts,TString xbranch,int xbins,float xmin,float xmax,TString ybranch,int ybins,float ymin,float ymax,bool data);
void makePlotDataMC(TString name, TString dir, 
		    std::vector<TTree*> trees,  std::vector<TTree*> trees_syst_jes_up, std::vector<TTree*> trees_syst_jes_down, std::vector<TTree*> trees_syst_jer_up, std::vector<TTree*> trees_syst_jer_down, std::vector<TTree*> trees_syst_met_up, std::vector<TTree*> trees_syst_met_down, std::vector<TTree*> trees_syst_lhe, TString lumi,TString cut, TString addcut,
		    TString var,int nbins,float xmin,float xmax,TString xaxisname,
		    std::vector<TString> legends, std::vector<int> colors, bool logy, int norm=0);


void datamcplots(TString sample) {

  TH1::SetDefaultSumw2(kTRUE);
  setTDRStyle();
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  gStyle->SetPalette(1);

  float intLumi = 36.8;
  ostringstream tmpLumi;
  tmpLumi << intLumi;
  TString lumi = tmpLumi.str();

  std::vector<TTree*>   trees;   trees.clear();
  std::vector<TTree*>   trees_syst_jes_up;   trees_syst_jes_up.clear();
  std::vector<TTree*>   trees_syst_jes_down;   trees_syst_jes_down.clear();
  std::vector<TTree*>   trees_syst_jer_up;   trees_syst_jer_up.clear();
  std::vector<TTree*>   trees_syst_jer_down;   trees_syst_jer_down.clear();
  std::vector<TTree*>   trees_syst_met_up;   trees_syst_met_up.clear();
  std::vector<TTree*>   trees_syst_met_down;   trees_syst_met_down.clear();
  std::vector<TTree*>   trees_syst_lhe;   trees_syst_lhe.clear();
  std::vector<TString> legends; legends.clear();
  std::vector<int>     colors;  colors.clear();

  TString cut_ak8, cut_ca15, cut_hvr;

  if (sample == "photons") {
    TString path = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/photon/mc_nom/";
    TString datapath = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/photon/data/";
    TString systpath = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/photon/mc_sys/";

    //data: always read the data tree first 
    TFile *f_data = TFile::Open(datapath+"/singlephoton_tree.root" , "READONLY"); TTree *t_data = (TTree*)f_data->Get("Events"); 
    trees.push_back(t_data); legends.push_back("Data"); colors.push_back(1); 
    trees_syst_jes_up.push_back(NULL);
    trees_syst_jes_down.push_back(NULL);
    trees_syst_jer_up.push_back(NULL);
    trees_syst_jer_down.push_back(NULL);
    trees_syst_met_up.push_back(NULL);
    trees_syst_met_down.push_back(NULL);
    trees_syst_lhe.push_back(NULL);


    // mc
    TFile *f_topg   = TFile::Open(path+"/tgplusttg_tree.root" , "READONLY"); TTree *t_topg   = (TTree*)f_topg->Get("Events");
    TFile *f_vg     = TFile::Open(path+"/vg_tree.root"        , "READONLY"); TTree *t_vg     = (TTree*)f_vg->Get("Events");
    TFile *f_qcdmg  = TFile::Open(path+"/qcd-mg_tree.root"    , "READONLY"); TTree *t_qcdmg  = (TTree*)f_qcdmg->Get("Events");
    TFile *f_photon = TFile::Open(path+"/photon_tree.root"    , "READONLY"); TTree *t_photon = (TTree*)f_photon->Get("Events");
    trees.push_back(t_topg);   legends.push_back("t(t#bar{t})#gamma"); colors.push_back(627);     
    trees.push_back(t_vg);     legends.push_back("V#gamma");           colors.push_back(798); 
    trees.push_back(t_qcdmg);  legends.push_back("QCD");               colors.push_back(412);     
    trees.push_back(t_photon); legends.push_back("#gamma+jets");       colors.push_back(419);     


 //systs
    TFile *f_topg_syst_jes_up = TFile::Open(systpath+"jes_up/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_jes_up = (TTree*)f_topg_syst_jes_up->Get("Events");
    TFile *f_vg_syst_jes_up = TFile::Open(systpath+"jes_up/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_jes_up = (TTree*)f_vg_syst_jes_up->Get("Events");
    TFile *f_qcdmg_syst_jes_up = TFile::Open(systpath+"jes_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jes_up = (TTree*)f_qcdmg_syst_jes_up->Get("Events");
    TFile *f_photon_syst_jes_up = TFile::Open(systpath+"jes_up/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_jes_up = (TTree*)f_photon_syst_jes_up->Get("Events");
    TFile *f_topg_syst_jes_down = TFile::Open(systpath+"jes_down/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_jes_down = (TTree*)f_topg_syst_jes_down->Get("Events");
    TFile *f_vg_syst_jes_down = TFile::Open(systpath+"jes_down/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_jes_down = (TTree*)f_vg_syst_jes_down->Get("Events");
    TFile *f_qcdmg_syst_jes_down = TFile::Open(systpath+"jes_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jes_down = (TTree*)f_qcdmg_syst_jes_down->Get("Events");
    TFile *f_photon_syst_jes_down = TFile::Open(systpath+"jes_down/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_jes_down = (TTree*)f_photon_syst_jes_down->Get("Events");
    

    cout << "Loaded JES" << endl;
    trees_syst_jes_up.push_back(t_topg_syst_jes_up);
    trees_syst_jes_up.push_back(t_vg_syst_jes_up);
    trees_syst_jes_up.push_back(t_qcdmg_syst_jes_up);
    trees_syst_jes_up.push_back(t_photon_syst_jes_up);
    trees_syst_jes_down.push_back(t_topg_syst_jes_down);
    trees_syst_jes_down.push_back(t_vg_syst_jes_down);
    trees_syst_jes_down.push_back(t_qcdmg_syst_jes_down);
    trees_syst_jes_down.push_back(t_photon_syst_jes_down);


        TFile *f_topg_syst_jer_up = TFile::Open(systpath+"jer_up/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_jer_up = (TTree*)f_topg_syst_jer_up->Get("Events");
    TFile *f_vg_syst_jer_up = TFile::Open(systpath+"jer_up/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_jer_up = (TTree*)f_vg_syst_jer_up->Get("Events");
    TFile *f_qcdmg_syst_jer_up = TFile::Open(systpath+"jer_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jer_up = (TTree*)f_qcdmg_syst_jer_up->Get("Events");
    TFile *f_photon_syst_jer_up = TFile::Open(systpath+"jer_up/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_jer_up = (TTree*)f_photon_syst_jer_up->Get("Events");
    TFile *f_topg_syst_jer_down = TFile::Open(systpath+"jer_down/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_jer_down = (TTree*)f_topg_syst_jer_down->Get("Events");
    TFile *f_vg_syst_jer_down = TFile::Open(systpath+"jer_down/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_jer_down = (TTree*)f_vg_syst_jer_down->Get("Events");
    TFile *f_qcdmg_syst_jer_down = TFile::Open(systpath+"jer_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jer_down = (TTree*)f_qcdmg_syst_jer_down->Get("Events");
    TFile *f_photon_syst_jer_down = TFile::Open(systpath+"jer_down/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_jer_down = (TTree*)f_photon_syst_jer_down->Get("Events");
    

    trees_syst_jer_up.push_back(t_topg_syst_jer_up);
    trees_syst_jer_up.push_back(t_vg_syst_jer_up);
    trees_syst_jer_up.push_back(t_qcdmg_syst_jer_up);
    trees_syst_jer_up.push_back(t_photon_syst_jer_up);
    trees_syst_jer_down.push_back(t_topg_syst_jer_down);
    trees_syst_jer_down.push_back(t_vg_syst_jer_down);
    trees_syst_jer_down.push_back(t_qcdmg_syst_jer_down);
    trees_syst_jer_down.push_back(t_photon_syst_jer_down);
 

    
cout << "Loaded JER" << endl;


        TFile *f_topg_syst_met_up = TFile::Open(systpath+"met_up/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_met_up = (TTree*)f_topg_syst_met_up->Get("Events");
    TFile *f_vg_syst_met_up = TFile::Open(systpath+"met_up/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_met_up = (TTree*)f_vg_syst_met_up->Get("Events");
    TFile *f_qcdmg_syst_met_up = TFile::Open(systpath+"met_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_met_up = (TTree*)f_qcdmg_syst_met_up->Get("Events");
    TFile *f_photon_syst_met_up = TFile::Open(systpath+"met_up/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_met_up = (TTree*)f_photon_syst_met_up->Get("Events");
    TFile *f_topg_syst_met_down = TFile::Open(systpath+"met_down/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_met_down = (TTree*)f_topg_syst_met_down->Get("Events");
    TFile *f_vg_syst_met_down = TFile::Open(systpath+"met_down/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_met_down = (TTree*)f_vg_syst_met_down->Get("Events");
    TFile *f_qcdmg_syst_met_down = TFile::Open(systpath+"met_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_met_down = (TTree*)f_qcdmg_syst_met_down->Get("Events");
    TFile *f_photon_syst_met_down = TFile::Open(systpath+"met_down/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_met_down = (TTree*)f_photon_syst_met_down->Get("Events");
    

    trees_syst_met_up.push_back(t_topg_syst_met_up);
    trees_syst_met_up.push_back(t_vg_syst_met_up);
    trees_syst_met_up.push_back(t_qcdmg_syst_met_up);
    trees_syst_met_up.push_back(t_photon_syst_met_up);
    trees_syst_met_down.push_back(t_topg_syst_met_down);
    trees_syst_met_down.push_back(t_vg_syst_met_down);
    trees_syst_met_down.push_back(t_qcdmg_syst_met_down);
    trees_syst_met_down.push_back(t_photon_syst_met_down);
 

    
cout << "Loaded MET" << endl;


        TFile *f_topg_syst_lhe = TFile::Open(systpath+"LHEWeight/tgplusttg_tree.root"     , "READONLY"); TTree *t_topg_syst_lhe = (TTree*)f_topg_syst_lhe->Get("Events");
    TFile *f_vg_syst_lhe = TFile::Open(systpath+"LHEWeight/vg_tree.root"     , "READONLY"); TTree *t_vg_syst_lhe = (TTree*)f_vg_syst_lhe->Get("Events");
    TFile *f_qcdmg_syst_lhe = TFile::Open(systpath+"LHEWeight/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_lhe = (TTree*)f_qcdmg_syst_lhe->Get("Events");
    TFile *f_photon_syst_lhe = TFile::Open(systpath+"LHEWeight/photon_tree.root"     , "READONLY"); TTree *t_photon_syst_lhe = (TTree*)f_photon_syst_lhe->Get("Events");
    

    trees_syst_lhe.push_back(t_topg_syst_lhe);
    trees_syst_lhe.push_back(t_vg_syst_lhe);
    trees_syst_lhe.push_back(t_qcdmg_syst_lhe);
    trees_syst_lhe.push_back(t_photon_syst_lhe);
 

    
cout << "Loaded LHE" << endl;






    cut_ak8  = "ht>200 && ak8_1_pt>=500. ";
    cut_ca15 = "ht>200 && ca15_1_pt>=200.";
    cut_hvr  = "ht>200 && hotvr_1_pt>=200.";
 
  }

  if (sample == "qcd") {
    //TString path = "root://cmseos.fnal.gov//store//group/lpcjme/LGOutputs/hrt_qcd_20190225/";
    TString path = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/qcd/mc_nom/";
    TString datapath = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/qcd/data/";
    TString systpath = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/qcd/mc_sys/";

    //data: always read the data tree first 
    TFile *f_data = TFile::Open(datapath+"/jetht_tree.root" , "READONLY"); TTree *t_data = (TTree*)f_data->Get("Events"); 
    trees.push_back(t_data); legends.push_back("Data"); colors.push_back(1); 
    trees_syst_jes_up.push_back(NULL);
    trees_syst_jes_down.push_back(NULL);
    trees_syst_jer_up.push_back(NULL);
    trees_syst_jer_down.push_back(NULL);
    trees_syst_met_up.push_back(NULL);
    trees_syst_met_down.push_back(NULL);
    trees_syst_lhe.push_back(NULL);

    // mc
    TFile *f_qcdmg   = TFile::Open(path+"/qcd-mg_tree.root"  , "READONLY"); TTree *t_qcdmg   = (TTree*)f_qcdmg->Get("Events");
    TFile *f_diboson = TFile::Open(path+"/diboson_tree.root" , "READONLY"); TTree *t_diboson = (TTree*)f_diboson->Get("Events");
    TFile *f_top     = TFile::Open(path+"/top_tree.root"     , "READONLY"); TTree *t_top     = (TTree*)f_top->Get("Events");
    TFile *f_vqq     = TFile::Open(path+"/v-qq_tree.root"    , "READONLY"); TTree *t_vqq     = (TTree*)f_vqq->Get("Events");
    trees.push_back(t_qcdmg);   legends.push_back("QCD");        colors.push_back(412);     
    trees.push_back(t_diboson); legends.push_back("VV");         colors.push_back(419);
    trees.push_back(t_top);     legends.push_back("t/t#bar{t}"); colors.push_back(627);
    trees.push_back(t_vqq);     legends.push_back("V(qq)");      colors.push_back(600);


//systs
    TFile *f_qcdmg_syst_jes_up = TFile::Open(systpath+"jes_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jes_up = (TTree*)f_qcdmg_syst_jes_up->Get("Events");
    TFile *f_diboson_syst_jes_up = TFile::Open(systpath+"jes_up/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jes_up = (TTree*)f_diboson_syst_jes_up->Get("Events");
    TFile *f_top_syst_jes_up = TFile::Open(systpath+"jes_up/top_tree.root"     , "READONLY"); TTree *t_top_syst_jes_up = (TTree*)f_top_syst_jes_up->Get("Events");
    TFile *f_vqq_syst_jes_up = TFile::Open(systpath+"jes_up/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_jes_up = (TTree*)f_vqq_syst_jes_up->Get("Events");
    TFile *f_qcdmg_syst_jes_down = TFile::Open(systpath+"jes_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jes_down = (TTree*)f_qcdmg_syst_jes_down->Get("Events");
    TFile *f_diboson_syst_jes_down = TFile::Open(systpath+"jes_down/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jes_down = (TTree*)f_diboson_syst_jes_down->Get("Events");
    TFile *f_top_syst_jes_down = TFile::Open(systpath+"jes_down/top_tree.root"     , "READONLY"); TTree *t_top_syst_jes_down = (TTree*)f_top_syst_jes_down->Get("Events");
    TFile *f_vqq_syst_jes_down = TFile::Open(systpath+"jes_down/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_jes_down = (TTree*)f_vqq_syst_jes_down->Get("Events");
    
        cout << "Loaded JES" << endl;
    trees_syst_jes_up.push_back(t_qcdmg_syst_jes_up);
    trees_syst_jes_up.push_back(t_diboson_syst_jes_up);
    trees_syst_jes_up.push_back(t_top_syst_jes_up);
    trees_syst_jes_up.push_back(t_vqq_syst_jes_up);
    trees_syst_jes_down.push_back(t_qcdmg_syst_jes_down);
    trees_syst_jes_down.push_back(t_diboson_syst_jes_down);
    trees_syst_jes_down.push_back(t_top_syst_jes_down);
    trees_syst_jes_down.push_back(t_vqq_syst_jes_down);
    
TFile *f_qcdmg_syst_jer_up = TFile::Open(systpath+"jer_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jer_up = (TTree*)f_qcdmg_syst_jer_up->Get("Events");
    TFile *f_diboson_syst_jer_up = TFile::Open(systpath+"jer_up/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jer_up = (TTree*)f_diboson_syst_jer_up->Get("Events");
    TFile *f_top_syst_jer_up = TFile::Open(systpath+"jer_up/top_tree.root"     , "READONLY"); TTree *t_top_syst_jer_up = (TTree*)f_top_syst_jer_up->Get("Events");
    TFile *f_vqq_syst_jer_up = TFile::Open(systpath+"jer_up/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_jer_up = (TTree*)f_vqq_syst_jer_up->Get("Events");
    TFile *f_qcdmg_syst_jer_down = TFile::Open(systpath+"jer_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jer_down = (TTree*)f_qcdmg_syst_jer_down->Get("Events");
    TFile *f_diboson_syst_jer_down = TFile::Open(systpath+"jer_down/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jer_down = (TTree*)f_diboson_syst_jer_down->Get("Events");
    TFile *f_top_syst_jer_down = TFile::Open(systpath+"jer_down/top_tree.root"     , "READONLY"); TTree *t_top_syst_jer_down = (TTree*)f_top_syst_jer_down->Get("Events");
    TFile *f_vqq_syst_jer_down = TFile::Open(systpath+"jer_down/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_jer_down = (TTree*)f_vqq_syst_jer_down->Get("Events");
    
        cout << "Loaded JER" << endl;
    trees_syst_jer_up.push_back(t_qcdmg_syst_jer_up);
    trees_syst_jer_up.push_back(t_diboson_syst_jer_up);
    trees_syst_jer_up.push_back(t_top_syst_jer_up);
    trees_syst_jer_up.push_back(t_vqq_syst_jer_up);
    trees_syst_jer_down.push_back(t_qcdmg_syst_jer_down);
    trees_syst_jer_down.push_back(t_diboson_syst_jer_down);
    trees_syst_jer_down.push_back(t_top_syst_jer_down);
    trees_syst_jer_down.push_back(t_vqq_syst_jer_down);
    
TFile *f_qcdmg_syst_met_up = TFile::Open(systpath+"met_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_met_up = (TTree*)f_qcdmg_syst_met_up->Get("Events");
    TFile *f_diboson_syst_met_up = TFile::Open(systpath+"met_up/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_met_up = (TTree*)f_diboson_syst_met_up->Get("Events");
    TFile *f_top_syst_met_up = TFile::Open(systpath+"met_up/top_tree.root"     , "READONLY"); TTree *t_top_syst_met_up = (TTree*)f_top_syst_met_up->Get("Events");
    TFile *f_vqq_syst_met_up = TFile::Open(systpath+"met_up/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_met_up = (TTree*)f_vqq_syst_met_up->Get("Events");
    TFile *f_qcdmg_syst_met_down = TFile::Open(systpath+"met_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_met_down = (TTree*)f_qcdmg_syst_met_down->Get("Events");
    TFile *f_diboson_syst_met_down = TFile::Open(systpath+"met_down/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_met_down = (TTree*)f_diboson_syst_met_down->Get("Events");
    TFile *f_top_syst_met_down = TFile::Open(systpath+"met_down/top_tree.root"     , "READONLY"); TTree *t_top_syst_met_down = (TTree*)f_top_syst_met_down->Get("Events");
    TFile *f_vqq_syst_met_down = TFile::Open(systpath+"met_down/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_met_down = (TTree*)f_vqq_syst_met_down->Get("Events");
    
        cout << "Loaded MET" << endl;
    trees_syst_met_up.push_back(t_qcdmg_syst_met_up);
    trees_syst_met_up.push_back(t_diboson_syst_met_up);
    trees_syst_met_up.push_back(t_top_syst_met_up);
    trees_syst_met_up.push_back(t_vqq_syst_met_up);
    trees_syst_met_down.push_back(t_qcdmg_syst_met_down);
    trees_syst_met_down.push_back(t_diboson_syst_met_down);
    trees_syst_met_down.push_back(t_top_syst_met_down);
    trees_syst_met_down.push_back(t_vqq_syst_met_down);
    

TFile *f_qcdmg_syst_lhe = TFile::Open(systpath+"LHEWeight/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_lhe = (TTree*)f_qcdmg_syst_lhe->Get("Events");
    TFile *f_diboson_syst_lhe = TFile::Open(systpath+"LHEWeight/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_lhe = (TTree*)f_diboson_syst_lhe->Get("Events");
    TFile *f_top_syst_lhe = TFile::Open(systpath+"LHEWeight/top_tree.root"     , "READONLY"); TTree *t_top_syst_lhe = (TTree*)f_top_syst_lhe->Get("Events");
    TFile *f_vqq_syst_lhe = TFile::Open(systpath+"LHEWeight/v-qq_tree.root"     , "READONLY"); TTree *t_vqq_syst_lhe = (TTree*)f_vqq_syst_lhe->Get("Events");
    
        cout << "Loaded LHE" << endl;
    trees_syst_lhe.push_back(t_qcdmg_syst_lhe);
    trees_syst_lhe.push_back(t_diboson_syst_lhe);
    trees_syst_lhe.push_back(t_top_syst_lhe);
    trees_syst_lhe.push_back(t_vqq_syst_lhe);
    






    cut_ak8  = "ht>1000 && ak8_1_pt>=300. && n_ak8>=2";
    cut_ca15 = "ht>1000 && ca15_1_pt>=200. && n_ca15>=2";
    cut_hvr  = "ht>1000 && hotvr_1_pt>=200.";

  }

  if (sample == "muon") {

    cout << "Doing muons" << endl;
    TString path = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/muon/";
    TString systpath = "root://cmseos.fnal.gov//store/group/lpcjme/noreplica/NanoHRT/Trees/Apr08/muon/mc_sys/";

    //data: always read the data tree first 
    TFile *f_data = TFile::Open(path+"/data/singlemu_tree.root" , "READONLY"); TTree *t_data = (TTree*)f_data->Get("Events"); 
    trees.push_back(t_data); legends.push_back("Data"); colors.push_back(1); 
    trees_syst_jes_up.push_back(NULL);
    trees_syst_jes_down.push_back(NULL);
    trees_syst_jer_up.push_back(NULL);
    trees_syst_jer_down.push_back(NULL);
    trees_syst_met_up.push_back(NULL);
    trees_syst_met_down.push_back(NULL);
    trees_syst_lhe.push_back(NULL);

    cout << "Loaded data" << endl;

    // mc
    TFile *f_tt     = TFile::Open(path+"/mc_nom/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt     = (TTree*)f_tt->Get("Events");
    TFile *f_qcdmg   = TFile::Open(path+"/mc_nom/qcd-mg_tree.root"  , "READONLY"); TTree *t_qcdmg   = (TTree*)f_qcdmg->Get("Events");
    TFile *f_diboson = TFile::Open(path+"/mc_nom/diboson_tree.root" , "READONLY"); TTree *t_diboson = (TTree*)f_diboson->Get("Events");
    TFile *f_top     = TFile::Open(path+"/mc_nom/singletop_tree.root"     , "READONLY"); TTree *t_top     = (TTree*)f_top->Get("Events");
    TFile *f_ttv     = TFile::Open(path+"/mc_nom/ttv_tree.root"     , "READONLY"); TTree *t_ttv     = (TTree*)f_ttv->Get("Events");
    TFile *f_vqq     = TFile::Open(path+"/mc_nom/w_tree.root"    , "READONLY"); TTree *t_vqq     = (TTree*)f_vqq->Get("Events");
    trees.push_back(t_qcdmg);   legends.push_back("QCD");        colors.push_back(412);     
    trees.push_back(t_diboson); legends.push_back("VV");         colors.push_back(419);
    trees.push_back(t_tt);     legends.push_back("t#bar{t}"); colors.push_back(860);
    trees.push_back(t_top);     legends.push_back("single-t"); colors.push_back(627);
    trees.push_back(t_ttv);     legends.push_back("t#bar{t}V"); colors.push_back(890);
    trees.push_back(t_vqq);     legends.push_back("W+jets");      colors.push_back(400);

    cout << "Loaded nominals" << endl;

    //systs
    TFile *f_tt_syst_jes_up = TFile::Open(systpath+"jes_up/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_jes_up = (TTree*)f_tt_syst_jes_up->Get("Events");
    TFile *f_qcdmg_syst_jes_up = TFile::Open(systpath+"jes_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jes_up = (TTree*)f_qcdmg_syst_jes_up->Get("Events");
    TFile *f_diboson_syst_jes_up = TFile::Open(systpath+"jes_up/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jes_up = (TTree*)f_diboson_syst_jes_up->Get("Events");
    TFile *f_singletop_syst_jes_up = TFile::Open(systpath+"jes_up/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_jes_up = (TTree*)f_singletop_syst_jes_up->Get("Events");
    TFile *f_ttv_syst_jes_up = TFile::Open(systpath+"jes_up/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_jes_up = (TTree*)f_ttv_syst_jes_up->Get("Events");
    TFile *f_vqq_syst_jes_up = TFile::Open(systpath+"jes_up/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_jes_up = (TTree*)f_vqq_syst_jes_up->Get("Events");
    
    TFile *f_tt_syst_jes_down = TFile::Open(systpath+"jes_down/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_jes_down = (TTree*)f_tt_syst_jes_down->Get("Events");
    TFile *f_qcdmg_syst_jes_down = TFile::Open(systpath+"jes_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jes_down = (TTree*)f_qcdmg_syst_jes_down->Get("Events");
    TFile *f_diboson_syst_jes_down = TFile::Open(systpath+"jes_down/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jes_down = (TTree*)f_diboson_syst_jes_down->Get("Events");
    TFile *f_singletop_syst_jes_down = TFile::Open(systpath+"jes_down/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_jes_down = (TTree*)f_singletop_syst_jes_down->Get("Events");
    TFile *f_ttv_syst_jes_down = TFile::Open(systpath+"jes_down/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_jes_down = (TTree*)f_ttv_syst_jes_down->Get("Events");
    TFile *f_vqq_syst_jes_down = TFile::Open(systpath+"jes_down/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_jes_down = (TTree*)f_vqq_syst_jes_down->Get("Events");

    cout << "Loaded JES" << endl;
    trees_syst_jes_up.push_back(t_qcdmg_syst_jes_up);
    trees_syst_jes_up.push_back(t_diboson_syst_jes_up);
    trees_syst_jes_up.push_back(t_tt_syst_jes_up);
    trees_syst_jes_up.push_back(t_singletop_syst_jes_up);
    trees_syst_jes_up.push_back(t_ttv_syst_jes_up);
    trees_syst_jes_up.push_back(t_vqq_syst_jes_up);
    
    trees_syst_jes_down.push_back(t_qcdmg_syst_jes_down);
    trees_syst_jes_down.push_back(t_diboson_syst_jes_down);
    trees_syst_jes_down.push_back(t_tt_syst_jes_down);
    trees_syst_jes_down.push_back(t_singletop_syst_jes_down);
    trees_syst_jes_down.push_back(t_ttv_syst_jes_down);
    trees_syst_jes_down.push_back(t_vqq_syst_jes_down);

TFile *f_tt_syst_jer_up = TFile::Open(systpath+"jer_up/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_jer_up = (TTree*)f_tt_syst_jer_up->Get("Events");
    TFile *f_qcdmg_syst_jer_up = TFile::Open(systpath+"jer_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jer_up = (TTree*)f_qcdmg_syst_jer_up->Get("Events");
    TFile *f_diboson_syst_jer_up = TFile::Open(systpath+"jer_up/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jer_up = (TTree*)f_diboson_syst_jer_up->Get("Events");
    TFile *f_singletop_syst_jer_up = TFile::Open(systpath+"jer_up/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_jer_up = (TTree*)f_singletop_syst_jer_up->Get("Events");
    TFile *f_ttv_syst_jer_up = TFile::Open(systpath+"jer_up/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_jer_up = (TTree*)f_ttv_syst_jer_up->Get("Events");
    TFile *f_vqq_syst_jer_up = TFile::Open(systpath+"jer_up/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_jer_up = (TTree*)f_vqq_syst_jer_up->Get("Events");
    
    TFile *f_tt_syst_jer_down = TFile::Open(systpath+"jer_down/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_jer_down = (TTree*)f_tt_syst_jer_down->Get("Events");
    TFile *f_qcdmg_syst_jer_down = TFile::Open(systpath+"jer_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_jer_down = (TTree*)f_qcdmg_syst_jer_down->Get("Events");
    TFile *f_diboson_syst_jer_down = TFile::Open(systpath+"jer_down/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_jer_down = (TTree*)f_diboson_syst_jer_down->Get("Events");
    TFile *f_singletop_syst_jer_down = TFile::Open(systpath+"jer_down/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_jer_down = (TTree*)f_singletop_syst_jer_down->Get("Events");
    TFile *f_ttv_syst_jer_down = TFile::Open(systpath+"jer_down/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_jer_down = (TTree*)f_ttv_syst_jer_down->Get("Events");
    TFile *f_vqq_syst_jer_down = TFile::Open(systpath+"jer_down/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_jer_down = (TTree*)f_vqq_syst_jer_down->Get("Events");

    trees_syst_jer_up.push_back(t_qcdmg_syst_jer_up);
    trees_syst_jer_up.push_back(t_diboson_syst_jer_up);
    trees_syst_jer_up.push_back(t_tt_syst_jer_up);
    trees_syst_jer_up.push_back(t_singletop_syst_jer_up);
    trees_syst_jer_up.push_back(t_ttv_syst_jer_up);
    trees_syst_jer_up.push_back(t_vqq_syst_jer_up);
    
    trees_syst_jer_down.push_back(t_qcdmg_syst_jer_down);
    trees_syst_jer_down.push_back(t_diboson_syst_jer_down);
    trees_syst_jer_down.push_back(t_tt_syst_jer_down);
    trees_syst_jer_down.push_back(t_singletop_syst_jer_down);
    trees_syst_jer_down.push_back(t_ttv_syst_jer_down);
    trees_syst_jer_down.push_back(t_vqq_syst_jer_down);
	cout << "Loaded JER" << endl;

TFile *f_tt_syst_met_up = TFile::Open(systpath+"met_up/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_met_up = (TTree*)f_tt_syst_met_up->Get("Events");
    TFile *f_qcdmg_syst_met_up = TFile::Open(systpath+"met_up/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_met_up = (TTree*)f_qcdmg_syst_met_up->Get("Events");
    TFile *f_diboson_syst_met_up = TFile::Open(systpath+"met_up/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_met_up = (TTree*)f_diboson_syst_met_up->Get("Events");
    TFile *f_singletop_syst_met_up = TFile::Open(systpath+"met_up/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_met_up = (TTree*)f_singletop_syst_met_up->Get("Events");
    TFile *f_ttv_syst_met_up = TFile::Open(systpath+"met_up/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_met_up = (TTree*)f_ttv_syst_met_up->Get("Events");
    TFile *f_vqq_syst_met_up = TFile::Open(systpath+"met_up/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_met_up = (TTree*)f_vqq_syst_met_up->Get("Events");
    
    TFile *f_tt_syst_met_down = TFile::Open(systpath+"met_down/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_met_down = (TTree*)f_tt_syst_met_down->Get("Events");
    TFile *f_qcdmg_syst_met_down = TFile::Open(systpath+"met_down/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_met_down = (TTree*)f_qcdmg_syst_met_down->Get("Events");
    TFile *f_diboson_syst_met_down = TFile::Open(systpath+"met_down/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_met_down = (TTree*)f_diboson_syst_met_down->Get("Events");
    TFile *f_singletop_syst_met_down = TFile::Open(systpath+"met_down/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_met_down = (TTree*)f_singletop_syst_met_down->Get("Events");
    TFile *f_ttv_syst_met_down = TFile::Open(systpath+"met_down/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_met_down = (TTree*)f_ttv_syst_met_down->Get("Events");
    TFile *f_vqq_syst_met_down = TFile::Open(systpath+"met_down/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_met_down = (TTree*)f_vqq_syst_met_down->Get("Events");

    trees_syst_met_up.push_back(t_qcdmg_syst_met_up);
    trees_syst_met_up.push_back(t_diboson_syst_met_up);
    trees_syst_met_up.push_back(t_tt_syst_met_up);
    trees_syst_met_up.push_back(t_singletop_syst_met_up);
    trees_syst_met_up.push_back(t_ttv_syst_met_up);
    trees_syst_met_up.push_back(t_vqq_syst_met_up);
    
    trees_syst_met_down.push_back(t_qcdmg_syst_met_down);
    trees_syst_met_down.push_back(t_diboson_syst_met_down);
    trees_syst_met_down.push_back(t_tt_syst_met_down);
    trees_syst_met_down.push_back(t_singletop_syst_met_down);
    trees_syst_met_down.push_back(t_ttv_syst_met_down);
    trees_syst_met_down.push_back(t_vqq_syst_met_down);

	cout << "Loaded MET" << endl;

TFile *f_tt_syst_LHEWeight = TFile::Open(systpath+"LHEWeight/ttbar-powheg_tree.root"     , "READONLY"); TTree *t_tt_syst_LHEWeight = (TTree*)f_tt_syst_LHEWeight->Get("Events");
    TFile *f_qcdmg_syst_LHEWeight = TFile::Open(systpath+"LHEWeight/qcd-mg_tree.root"     , "READONLY"); TTree *t_qcdmg_syst_LHEWeight = (TTree*)f_qcdmg_syst_LHEWeight->Get("Events");
    TFile *f_diboson_syst_LHEWeight = TFile::Open(systpath+"LHEWeight/diboson_tree.root"     , "READONLY"); TTree *t_diboson_syst_LHEWeight = (TTree*)f_diboson_syst_LHEWeight->Get("Events");
    TFile *f_singletop_syst_LHEWeight = TFile::Open(systpath+"LHEWeight/singletop_tree.root"     , "READONLY"); TTree *t_singletop_syst_LHEWeight = (TTree*)f_singletop_syst_LHEWeight->Get("Events");
    TFile *f_ttv_syst_LHEWeight = TFile::Open(systpath+"LHEWeight/ttv_tree.root"     , "READONLY"); TTree *t_ttv_syst_LHEWeight = (TTree*)f_ttv_syst_LHEWeight->Get("Events");
    TFile *f_vqq_syst_LHEWeight = TFile::Open(systpath+"LHEWeight/w_tree.root"     , "READONLY"); TTree *t_vqq_syst_LHEWeight = (TTree*)f_vqq_syst_LHEWeight->Get("Events");
    trees_syst_lhe.push_back(t_qcdmg_syst_LHEWeight);
    trees_syst_lhe.push_back(t_diboson_syst_LHEWeight);
    trees_syst_lhe.push_back(t_tt_syst_LHEWeight);
    trees_syst_lhe.push_back(t_singletop_syst_LHEWeight);
    trees_syst_lhe.push_back(t_ttv_syst_LHEWeight);
    trees_syst_lhe.push_back(t_vqq_syst_LHEWeight);


	cout << "Loaded LHE" << endl;












    cut_ak8  = "ak8_1_pt>=500. && n_ak8>=1";
    cut_ca15 = "ca15_1_pt>=200. && n_ca15>=1";
    cut_hvr  = "hotvr_1_pt>=200.";

   cout << "Loaded files" << endl;

  }


  //makePlotDataMC(sample+"_jetpt","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe, lumi,cut_ak8,"0==0","ak8_1_pt",16,200.,1000.,"p_{T}(jet) [GeV]",legends,colors,true,1);
  //makePlotDataMC(sample+"_jetmsd","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_mass",20,0.,200.,"m_{SD}(jet) [GeV]",legends,colors,true,1);
  //makePlotDataMC(sample+"_jettau32","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_tau3/ak8_1_tau2",20,0.,1.,"#tau_{32}(jet)",legends,colors,true,1);
  //makePlotDataMC(sample+"_jettau21","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_tau2/ak8_1_tau1",20,0.,1.,"#tau_{21}(jet)",legends,colors,true,1);
  makePlotDataMC(sample+"_jetn2","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_n2b1",40,0.0,1.0,"N_{2}^{1}",legends,colors,true,1);
  makePlotDataMC(sample+"_jetn2ddt","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"(ak8_1_n2b1ddt < 0.4)","ak8_1_n2b1ddt",40,-0.25,0.4,"N_{2}^{1,DDT}",legends,colors,true,1);
  //makePlotDataMC(sample+"_ecftoptag","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ca15,"0==0","ca15_1_ecfTopTagBDT",20,0.,1.,"ECF BDT (t vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_hotvrmass","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_hvr,"0==0","hotvr_1_mass",20,50.,250.,"m (HOTVR) [GeV]",legends,colors,true,1);
  //makePlotDataMC(sample+"_bestwvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_best_WvsQCD",20,0.,1.,"BEST (W vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_besttvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_best_TvsQCD",20,0.,1.,"BEST (t vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_bestzvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_best_ZvsQCD",20,0.,1.,"BEST (Z vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_besthvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_best_HvsQCD",20,0.,1.,"BEST (H vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_imagetoptvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_image_top",20,0.,1.,"Image top (t vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_imagetopmdtvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_image_top_md",20,0.,1.,"Image top-MD (t vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8wvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8_WvsQCD",20,0.,1.,"DeepAK8 (W vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8tvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8_TvsQCD",20,0.,1.,"DeepAK8 (t vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8zvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8_ZvsQCD",20,0.,1.,"DeepAK8 (Z vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8hvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8_HvsQCD",20,0.,1.,"DeepAK8 (H vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8mdwvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8MD_WvsQCD",20,0.,1.,"Deepak8-MD (W vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8mdtvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8MD_TvsQCD",20,0.,1.,"Deepak8-MD (t vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8mdzvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8MD_ZvsQCD",20,0.,1.,"Deepak8-MD (Z vs. QCD)",legends,colors,true,1);
  //makePlotDataMC(sample+"_deepak8mdhvsqc","datamcplots_20190227_b",trees,trees_syst_jes_up, trees_syst_jes_down, trees_syst_jer_up, trees_syst_jer_down, trees_syst_met_up, trees_syst_met_down, trees_syst_lhe,lumi,cut_ak8,"0==0","ak8_1_DeepAK8MD_HvsQCD",20,0.,1.,"Deepak8-MD (H vs. QCD)",legends,colors,true,1);


}

void makePlotDataMC(TString name, TString dir, 
		    std::vector<TTree*> trees, std::vector<TTree*> trees_syst_jes_up, std::vector<TTree*> trees_syst_jes_down,std::vector<TTree*> trees_syst_jer_up, std::vector<TTree*> trees_syst_jer_down, std::vector<TTree*> trees_syst_met_up, std::vector<TTree*> trees_syst_met_down, std::vector<TTree*> trees_syst_lhe, TString lumi,TString cut, TString addcut,
		    TString var,int nbins,float xmin,float xmax,TString xaxisname,
		    std::vector<TString> legends, std::vector<int> colors, bool logy, int norm) {

  TH1::SetDefaultSumw2(kTRUE);
  std::cout << " working on " << name << " ...\n";

  TString sample; 
  if (name.Contains("qcd"))     { sample = "qcd"; }
  if (name.Contains("photons")) { sample = "photons"; }

  TH1F *h_sm; TH1F *h_data; TH1F *h_totErr; std::vector<TH1F*> mc_histos; mc_histos.clear();
  THStack *hs = new THStack("hs_"+name,"hs_"+name);

  TPaveText *pt_cms = new TPaveText(0.08,0.77,0.4,0.9,"NDC");
  pt_cms->SetFillStyle(0);
  pt_cms->SetFillColor(0);
  pt_cms->SetLineWidth(0);
  pt_cms->AddText("CMS");
  pt_cms->SetTextSize(0.08);

  TPaveText *pt_preliminary = new TPaveText(0.15,0.63,0.4,0.9,"NDC");
  pt_preliminary->SetFillStyle(0);
  pt_preliminary->SetFillColor(0);
  pt_preliminary->SetLineWidth(0);
  pt_preliminary->AddText("Preliminary");
  pt_preliminary->SetTextFont(52);
  pt_preliminary->SetTextSize(0.06);

  TLatex pt_lumi;
  const char *longstring = "35.9 fb^{-1} (13 TeV)";
  pt_lumi.SetTextSize(0.07);
  pt_lumi.SetTextFont(42);

  TLegend* leg = new TLegend(0.75,0.55,0.92,0.88);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetLineWidth(0);

  TString logstr = "lin"; if (logy) { logstr = "log"; }

  TCanvas *c_ = new TCanvas(name,name,600,600); c_->SetName("c_"+name);
  TPad *pMain  = new TPad("pMain_"+name,"pMain+"+name,0.,0.35,1.0,1.0);
  pMain->SetRightMargin(0.05);
  pMain->SetLeftMargin(0.15);
  pMain->SetBottomMargin(0.02);
  pMain->SetTopMargin(0.09);
  pMain->Draw();

  TPad *pRatio = new TPad("pRatio_"+name,"pRatio_"+name,0.0,0.0,1.0,0.35);
  pRatio->SetRightMargin(0.05);
  pRatio->SetLeftMargin(0.15);
  pRatio->SetTopMargin(0.02);
  pRatio->SetBottomMargin(0.3);
  pRatio->Draw();
 

  for (unsigned int i=0; i<trees.size(); ++i) {

    ostringstream tmpCount;
    tmpCount << i;
    TString count = tmpCount.str();
 
    bool data = false;  if (i==0) { data = true; }

    pMain->cd();
    TH1F *h = create1Dhisto(sample,trees[i],lumi,cut+" && ak8_1_pt > 500. && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_"+name+"_"+count,false,data); 
    if (i==0) { 
      h->SetMarkerSize(1.2); h->SetMarkerStyle(20); h->SetLineWidth(1); h->SetLineColor(colors[i]); h->SetFillColor(0);  
      leg->AddEntry(h,legends[i],"P");
      h->GetYaxis()->SetTitleSize(0.07);
      h->GetYaxis()->SetLabelSize(0.055);
      h->GetYaxis()->SetTitleOffset(1.1);
      h->GetXaxis()->SetLabelSize(0);
      h->GetXaxis()->SetTitle(xaxisname);
      if (norm == 0) { h->GetYaxis()->SetTitle("Events / bin"); } else { h->GetYaxis()->SetTitle("a. u."); }
      if (logy) { 
	gPad->SetLogy(); 
	h->GetYaxis()->SetRangeUser(1.,1000.*h->GetBinContent(h->GetMaximumBin())); 
	if (var.Contains("tau") || var.Contains("eta") || var.Contains("ecf")) { h->GetYaxis()->SetRangeUser(1.,100000.*h->GetBinContent(h->GetMaximumBin())); }
      } 
      else { h->GetYaxis()->SetRangeUser(0.,1.7*h->GetBinContent(h->GetMaximumBin())); }
      h->Draw("P E0");
      h_data = (TH1F*)h->Clone("h_"+name+"_data");
    } 
    else { 
      h->SetFillColor(colors[i]); h->SetMarkerSize(0); h->SetLineColor(colors[i]); 
      leg->AddEntry(h,legends[i],"FL"); 
      h->Draw("HIST E0 sames");
    }
    
    if (i==1) { h_sm = (TH1F*)h->Clone("h_sm"); h_totErr = (TH1F *) h->Clone("h_totErr"); hs->Add(h); 

	for (int b = 0; b <= h->GetNbinsX(); b++){
		h_totErr->SetBinContent(b,h->GetBinError(b) / h->GetBinContent(b));
		cout << "Bin Error " << b << " " << h->GetBinError(b) << endl;
		h_totErr->SetBinError(b, h->GetBinError(b));	
	}
    }
    if (i>1 ) { h_sm->Add(h); hs->Add(h); }


    //Evaluate systematics
    if (i >= 1){
	TH1F *jesUp = create1Dhisto(sample,trees_syst_jes_up[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_jesUp_"+name+"_"+count,false,data);  
	TH1F *jesDown = create1Dhisto(sample,trees_syst_jes_down[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_jesDn_"+name+"_"+count,false,data);  
	TH1F *jerUp = create1Dhisto(sample,trees_syst_jer_up[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_jerUp_"+name+"_"+count,false,data);  
	TH1F *jerDown = create1Dhisto(sample,trees_syst_jer_down[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_jerDn_"+name+"_"+count,false,data);  
	TH1F *metUp = create1Dhisto(sample,trees_syst_met_up[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_metUp_"+name+"_"+count,false,data);  
	TH1F *metDown = create1Dhisto(sample,trees_syst_met_down[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_metDn_"+name+"_"+count,false,data);  
	TH1F *lheSyst = create1Dhisto(sample,trees_syst_lhe[i],lumi,cut+" && "+addcut,var,nbins,xmin,xmax,false,1,1,"h_lhe_"+name+"_"+count,false,data);  
	
	for (int b = 0; b <= h->GetNbinsX(); b++){
		float jesBinUpErr = abs( jesUp->GetBinContent(b) - h->GetBinContent(b) ) / h->GetBinContent(b);
		float jesBinDnErr = abs( jesDown->GetBinContent(b) - h->GetBinContent(b)) / h->GetBinContent(b);
		float jerBinUpErr = abs( jerUp->GetBinContent(b) - h->GetBinContent(b) ) / h->GetBinContent(b);
		float jerBinDnErr = abs( jerDown->GetBinContent(b) - h->GetBinContent(b)) / h->GetBinContent(b);
		float metBinUpErr = abs( metUp->GetBinContent(b) - h->GetBinContent(b) ) / h->GetBinContent(b);
		float metBinDnErr = abs( metDown->GetBinContent(b) - h->GetBinContent(b)) / h->GetBinContent(b);
		float lheErr = abs( lheSyst->GetBinContent(b) - h->GetBinContent(b)) / h->GetBinContent(b);
		float prevErr = h_totErr->GetBinContent(b);
		cout << "Prev err = " << prevErr << endl;
		float newErr = sqrt(prevErr*prevErr + pow(max(jesBinUpErr, jesBinDnErr),2)  + pow(max(jerBinUpErr, jerBinDnErr),2) + pow(max(metBinUpErr, metBinDnErr),2) + lheErr*lheErr);
		h_totErr->SetBinContent(b, newErr ); 
	

    }

    }


  }

  // norm MC
  float normVal = h_data->Integral()/h_sm->Integral();
  if (norm !=0) { h_sm->Scale(normVal); }

  for (int b = 0; b <= h_sm->GetNbinsX(); b++){
	h_sm->SetBinError(b, h_totErr->GetBinContent(b)*h_sm->GetBinContent(b) );	 
	cout << "Setting Bin Error to h_sm " << h_totErr->GetBinContent(b)*h_sm->GetBinContent(b) << endl;
  }
  // data mc ratio 
  TH1F *h_sm_noerr = (TH1F *) h_sm->Clone("h_sm_noerr");
  for (int b = 0; b < h_sm_noerr->GetNbinsX()+1; b++) h_sm_noerr->SetBinError(b, 0.0); 
  TH1F *h_r = (TH1F*)h_data->Clone("h_"+name+"_r"); h_r->Divide(h_data,h_sm_noerr);

  TList *histos = hs->GetHists();
  TIter next(histos);
  TH1F *hist;
  while ((hist =(TH1F*)next())) { hist->Scale(normVal); }
 


  TH1F *h_ratioBand = (TH1F *) h_sm->Clone("h_ratioBand");
  h_ratioBand->Sumw2();
  h_ratioBand->Divide(h_ratioBand, h_sm, 1, 1);

  // continue drawing  
  pMain->cd();
  hs->Draw("HIST E0 sames");
  h_data->Draw("P E0 sames");
  h_sm->SetFillColor(16);
  h_sm->SetFillStyle(3244);
  h_sm->Draw("E2 same");
  h_data->Draw("P E0 sames");
  leg->Draw("sames");
  pt_cms->Draw("sames");
  pt_preliminary->Draw("sames");
  pt_lumi.DrawLatexNDC(0.64,0.93,longstring);
  c_->RedrawAxis();
  pMain->RedrawAxis();
  
  pRatio->cd();
  h_r->GetYaxis()->SetTitleOffset(0.6);
  h_r->GetYaxis()->SetTitleSize(0.12);
  h_r->GetYaxis()->SetLabelSize(0.1);
  h_r->GetYaxis()->SetNdivisions(4,9,0);
  h_r->GetYaxis()->SetRangeUser(0.01,1.99);
  h_r->GetYaxis()->SetTitle("N_{obs} / N_{exp}");
  h_r->GetXaxis()->SetTitleOffset(1.1);
  h_r->GetXaxis()->SetTitleSize(0.12);
  h_r->GetXaxis()->SetLabelSize(0.1);
  h_r->GetXaxis()->SetTitle(xaxisname);

  h_r->Draw("P E0");
  h_ratioBand->SetFillColor(16);
  h_ratioBand->SetFillStyle(1001);
  h_ratioBand->Draw("E2 same");
  h_r->Draw("P E0 same");
  

  const int dir_err = system("mkdir -p ./"+dir);
  if (-1 == dir_err) {
      printf("Error creating directory!n");
      exit(1);
  }
    c_->Print(dir+"/"+name+"_"+logstr+".png");
    c_->Print(dir+"/"+name+"_"+logstr+".pdf");
   
}



TH1F *create1Dhisto(TString sample,TTree *tree,TString intLumi,TString cuts,TString branch,int bins,float xmin,float xmax,
		    bool useLog,int color, int style,TString name,bool norm,bool data) {
  TH1::SetDefaultSumw2(kTRUE);

  TString cut;
  if (sample == "photons") {
    if (data) { cut ="(passPhoton165_HE10 && "+cuts+")"; } // photon
    else      { cut ="(xsecWeight*puWeight*"+intLumi+")*(passPhoton165_HE10 &&"+cuts+")"; }
  }
  if (sample == "qcd") {
    if (data) { cut ="(passHTTrig && "+cuts+")"; } // QCD
    else      { cut ="(xsecWeight*puWeight*"+intLumi+")*(passHTTrig &&"+cuts+")"; }
  }

  if (sample == "muon") {
    if (data) { cut ="("+cuts+")"; } // QCD
    else      { cut ="(xsecWeight*puWeight*"+intLumi+")*(1 &&"+cuts+")"; }
  }
  //else { std::cout << name << "\n"; cut ="(xsecWeight*puWeight*topptWeight*"+intLumi+")*("+cuts+")"; }

  TH1F *hTemp = new TH1F(name,name,bins,xmin,xmax); //hTemp->SetName(name);
  //cut = "ak8_1_pt > 500.";
  tree->Project(name,branch,cut);

  hTemp->SetLineWidth(3);
  hTemp->SetMarkerSize(0);
  hTemp->SetLineColor(color);
  hTemp->SetFillColor(color);
  hTemp->SetLineStyle(style);

  // ad overflow bin             
  double error =0.; double integral = hTemp->IntegralAndError(bins,bins+1,error);
  hTemp->SetBinContent(bins,integral);
  hTemp->SetBinError(bins,error);

  if (norm) { hTemp->Scale(1./(hTemp->Integral())); }

  return hTemp;
} //~ end of create1Dhisto



TH2F *create2Dhisto(TString name,TTree *tree,TString intLumi,TString cuts,TString xbranch,int xbins,float xmin,float xmax,TString ybranch,int ybins,float ymin,float ymax,bool data) {
  TH2::SetDefaultSumw2(kTRUE);
  TString cut;
  if (data) { cut ="(httrigprescalewgt)*("+cuts+")"; }
  else      { cut ="(xsecWeight*puWeight*topptWeight*"+intLumi+")*("+cuts+")"; }

  TH2F *hTemp = new TH2F(name,name,xbins,xmin,xmax,ybins,ymin,ymax); hTemp->SetName(name);
  tree->Project(name,ybranch+":"+xbranch,cut);

  return hTemp;
} //~ end of create1Dhisto

