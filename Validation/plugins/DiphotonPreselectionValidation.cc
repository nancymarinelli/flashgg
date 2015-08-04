#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ptr.h"
//#include "DataFormats/Common/interface/PtrVector.h"
#include "flashgg/DataFormats/interface/GenPhotonExtra.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "flashgg/MicroAOD/interface/VertexSelectorBase.h"
#include "DataFormats/EgammaCandidates/interface/PhotonCore.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "flashgg/DataFormats/interface/Photon.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"

#include "flashgg/MicroAOD/interface/PhotonIdUtils.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "flashgg/DataFormats/interface/VertexCandidateMap.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"


// **********************************************************************

// define the structures used to create tree branches and fill the trees

// per-event tree:
struct eventInfo {

    int ndiphoton;

};

// per-photon tree:
struct diphotonInfo {

// leading photon
    int pho1_isEB;
    int pho1_isEE;
    float pho1_pt;
    float pho1_eta;
    float pho1_phi;
    float pho1_energy;
    float pho1_r9;
    float pho1_hoe;
    float pho1_sieie;
    float pho1_full5x5_r9;
    float pho1_full5x5_hoe;
    float pho1_full5x5_sieie;
    float pho1_hcalTowerSumEtConeDR03;
    float pho1_trkSumPtHollowConeDR03;
    float pho1_pfChgIsoWrtChosenVtx02;
// subleading photon
    int pho2_isEB;
    int pho2_isEE;
    float pho2_pt;
    float pho2_eta;
    float pho2_phi;
    float pho2_energy;
    float pho2_r9;
    float pho2_hoe;
    float pho2_sieie;
    float pho2_full5x5_r9;
    float pho2_full5x5_hoe;
    float pho2_full5x5_sieie;
    float pho2_hcalTowerSumEtConeDR03;
    float pho2_trkSumPtHollowConeDR03;
    float pho2_pfChgIsoWrtChosenVtx02;
// diphoton info
    float pt;
    float eta;
    float phi;
    float energy;
    float mass;

};
// **********************************************************************

using namespace std;
using namespace edm;
using namespace flashgg;

// **********************************************************************

class DiphotonPreselectionValidation : public edm::EDAnalyzer
{
public:
    explicit DiphotonPreselectionValidation( const edm::ParameterSet & );
    ~DiphotonPreselectionValidation();



private:


    void initTrig( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames );
    bool hltPass( edm::Handle<edm::TriggerResults> triggerBits );
    std::vector<math::XYZTLorentzVector> hltP4( const edm::TriggerNames &triggerNames,
            edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
            std::vector<std::string> filterLabels );
    std::pair<bool, math::XYZTLorentzVector>  onlineOfflineMatching( const edm::TriggerNames &triggerNames,
            edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
            math::XYZTLorentzVector p4, std::string filterLabel, float dRmin );


    virtual void beginJob() override;
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;
    virtual void endJob() override;

    std::string outputFileName_;
    EDGetTokenT<View<flashgg::Photon> > photonToken_;
    edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate> > diphotonToken_;
    edm::EDGetTokenT<edm::View<reco::Vertex> >               vertexToken_;
    EDGetTokenT<vector<flashgg::GenPhotonExtra> > genPhotonToken_;
    edm::ParameterSetID triggerNamesID_;
    std::map<std::string, unsigned int> trigger_indices;
    edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
    std::vector<std::string> filterName_;
    std::vector<std::string> lastfilterName_;
    edm::InputTag rhoFixedGrid_;
    bool rhoCorrectedIso_;
    bool getHLTcandidates_;
    //
    bool debug_;
    //
    TH1F *h_sim_pt_;
    TH1F *h_reco_pt_;
    //
    TH1F *h_nVtx_tot_;
    TH1F *h_nVtx_offl_;
    TH1F *h_nVtx_hlt_;

    //
    TH1F *h_r9_lead_tot_eb_;
    TH1F *h_full5x5r9_lead_tot_eb_;
    TH1F *h_full5x5r9_lead_tot_ee_;

    TH1F *h_r9_sublead_tot_eb_;
    TH1F *h_r9_lead_tot_ee_;
    TH1F *h_r9_sublead_tot_ee_;
    //
    TH1F *h_phoIso_lead_tot_eb_;
    TH1F *h_phoIso_sublead_tot_eb_;
    TH1F *h_phoIso_lead_tot_ee_;
    TH1F *h_phoIso_sublead_tot_ee_;
    //
    TH1F *h_chIso_lead_tot_eb_;
    TH1F *h_chIso_sublead_tot_eb_;
    TH1F *h_chIso_lead_tot_ee_;
    TH1F *h_chIso_sublead_tot_ee_;


    //
    TH1F *h_pt_lead_tot_[4];
    TH1F *h_pt_sublead_tot_[4];
    TH1F *h_r9_lead_tot_[4];
    TH1F *h_r9_sublead_tot_[4];
    TH1F *h_eta_lead_tot_[4];
    TH1F *h_eta_sublead_tot_[4];
    TH1F *h_mass_tot_[4];
    //
    TH1F *h_pt_lead_offl_[4];
    TH1F *h_pt_sublead_offl_[4];
    TH1F *h_eta_lead_offl_[4];
    TH1F *h_eta_sublead_offl_[4];
    TH1F *h_mass_offl_[4];
    //
    TH1F *h_pt_lead_hlt_[4];
    TH1F *h_pt_sublead_hlt_[4];
    TH1F *h_eta_lead_hlt_[4];
    TH1F *h_eta_sublead_hlt_[4];
    TH1F *h_mass_hlt_[4];
    //
    int nEvents_ = 0;
    int nEventsWithTwoGenPhotons_ = 0;
    int nEventsWithTwoRecoPhotons_ = 0;
    int nGenPhotons_ = 0;
    int nMatched = 0;
    int nSinglePhoPassingAODSel_ = 0;
    int nSinglePhoPassingAODSelPlusPt20_ = 0;
    int nDiphoAfterHlt_ = 0;
    int nDiphoAfterHltAndPresel_ = 0;
    int nDiphoMatched_ = 0;
    int nDiphoPassingEtaCut_ = 0;
    int nDiPhoPrompt_ = 0;
    int lDiPhoPrompt_ = 0;
    int nDiphoPassing_ = 0;
    int nMissing_;
    int nLowMassPair_ = 0;
    int nLowMassPairAfterPresel_ = 0;
    int nLowMassPairAfterPreselAndHLT_ = 0;
    //// N-1 histos
    TH1F *h_nMin1_hoe_offl_[4];
    TH1F *h_nMin1_hoe_hlt_[4];
    TH1F *h_nMin1_pt_offl_[4];
    TH1F *h_nMin1_pt_hlt_[4];
    TH2F *h2_nMin1_r9_offl_[4];
    TH1F *h_nMin1_r9_offl_[4];
    TH1F *h_nMin1_r9_low_offl_[4];
    TH1F *h_nMin1_r9_high_offl_[4];
    TH1F *h_nMin1_r9_hlt_[4];
    TH1F *h_nMin1_r9_low_hlt_[4];
    TH1F *h_nMin1_r9_high_hlt_[4];
    TH1F *h_nMin1_sieie_offl_[4];
    TH1F *h_nMin1_sieie_hlt_[4];
    TH1F *h_nMin1_phoIso_offl_[4];
    TH1F *h_nMin1_phoIso_hlt_[4];
    TH1F *h_nMin1_chIso_offl_[4];
    TH1F *h_nMin1_chIso_hlt_[4];
    TH1F *h_nMin1_mass_offl_[4];
    TH1F *h_nMin1_mass_hlt_[4];
    ///////
    TH1F *h_pt_tot_[4];
    TH1F *h_hoe_tot_[4];
    TH1F *h_newhoe_tot_[4];
    TH1F *h_r9_tot_[4] ;
    TH1F *h_sieie_tot_[4];
    TH1F *h_phoIso_tot_[4];
    TH1F *h_chIso_tot_[4];
    //// low mass crap
    TH2F *h2_lowMass_eta_offl_;
    TH2F *h2_lowMass_pt_offl_;
    TH2F *h2_lowMass_mass_offl_;
    TH2F *h2_lowMass_mass_hlt_;
    TH2F *h2_lowMass_massFromSC_hlt_;
    TH2F *h2_lowMass_massSCvsPho_offl_;

    //// test of the miniAOD photon content
    TH1F *h_pt_aod_;
    TH1F *h_eta_gen_;
    TH1F *h_eta_aod_;
    TH1F *h_hoe_aod_;


};


// ******************************************************************************************
// ******************************************************************************************

//
// constants, enums and typedefs
//

//
// static data member definitions
//



//
// constructors and destructor
//
DiphotonPreselectionValidation::DiphotonPreselectionValidation( const edm::ParameterSet &iConfig ):
    outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
    photonToken_( consumes<View<flashgg::Photon> >( iConfig.getUntrackedParameter<InputTag> ( "PhotonTag", InputTag( "flashggPhotons" ) ) ) ),
    diphotonToken_( consumes<View<flashgg::DiPhotonCandidate> >( iConfig.getUntrackedParameter<InputTag> ( "diPhotons", InputTag( "flashggDiPhotons" ) ) ) ),
    vertexToken_( consumes<View<reco::Vertex> >( iConfig.getUntrackedParameter<InputTag> ( "VertexTag", InputTag( "offlineSlimmedPrimaryVertices" ) ) ) ),
    genPhotonToken_( mayConsume<vector<flashgg::GenPhotonExtra> >( iConfig.getParameter<InputTag>( "genPhotonTag" ) ) ),
    triggerBits_( consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>( "bits" ) ) ),
    triggerObjects_( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>( "objects" ) ) ),
    filterName_( iConfig.getParameter<std::vector<std::string> >( "filterName" ) ),
    lastfilterName_( iConfig.getParameter<std::vector<std::string> >( "lastfilterName" ) )

{

    rhoFixedGrid_  = iConfig.getParameter<edm::InputTag>( "rhoFixedGridCollection" );
    rhoCorrectedIso_ = iConfig.getParameter<bool>( "rhoCorrection" );
    getHLTcandidates_ = iConfig.getParameter<bool>( "getHLTcandidates" );

    h_sim_pt_     = new TH1F( "h_sim_pt", "Gen photon Pt;Pt (GeV);Counts", 100, 0., 150. );
    h_reco_pt_     = new TH1F( "h_reco_pt", "Reco photon Pt;Pt (GeV);Counts", 100, 0., 150. );


    h_nVtx_tot_           = new TH1F( "h_nVtx_tot", "Offline Vertices; nVtx; Counts", 100, 0., 100. );
    h_nVtx_offl_          = new TH1F( "h_nVtx_offl", "Offline Vertices; nVtx; Counts", 100, 0., 100. );
    h_nVtx_hlt_           = new TH1F( "h_nVtx_hlt", "Offline Vertices; nVtx; Counts", 100, 0., 100. );


    h_pt_lead_tot_[0]     = new TH1F( "h_pt_lead_tot_cat0", "Lead photon Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_tot_[1]     = new TH1F( "h_pt_lead_tot_cat1", "Lead photon Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_tot_[2]     = new TH1F( "h_pt_lead_tot_cat2", "Lead photon Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_tot_[3]     = new TH1F( "h_pt_lead_tot_cat3", "Lead photon Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_pt_sublead_tot_[0]  = new TH1F( "h_pt_sublead_tot_cat0", "SubLead photon Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_tot_[1]  = new TH1F( "h_pt_sublead_tot_cat1", "SubLead photon Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_tot_[2]  = new TH1F( "h_pt_sublead_tot_cat2", "SubLead photon Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_tot_[3]  = new TH1F( "h_pt_sublead_tot_cat3", "SubLead photon Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_eta_lead_tot_[0]    = new TH1F( "h_eta_lead_tot_cat0", "Lead photon Cat 0;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_tot_[1]    = new TH1F( "h_eta_lead_tot_cat1", "Lead photon Cat 1;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_tot_[2]    = new TH1F( "h_eta_lead_tot_cat2", "Lead photon Cat 2;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_tot_[3]    = new TH1F( "h_eta_lead_tot_cat3", "Lead photon Cat 3;#eta;Counts", 68, -3.4, 3.4 );
    //
    h_eta_sublead_tot_[0] = new TH1F( "h_eta_sublead_tot_cat0", "SubLead photon Cat 0;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_tot_[1] = new TH1F( "h_eta_sublead_tot_cat1", "SubLead photon Cat 1;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_tot_[2] = new TH1F( "h_eta_sublead_tot_cat2", "SubLead photon Cat 2;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_tot_[3] = new TH1F( "h_eta_sublead_tot_cat3", "SubLead photon Cat 3;#eta;Counts", 68, -3.4, 3.4 );
    //
    h_mass_tot_[0]        = new TH1F( "h_mass_tot_cat0", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_tot_[1]        = new TH1F( "h_mass_tot_cat1", "diPhoton Mass Cat 1;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_tot_[2]        = new TH1F( "h_mass_tot_cat2", "diPhoton Mass Cat 2;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_tot_[3]        = new TH1F( "h_mass_tot_cat3", "diPhoton Mass Cat 3;m_{#gg}(GeV);Count", 80, 80., 160. );
    //
    h_r9_lead_tot_eb_     = new TH1F( "h_r9_lead_tot_eb", "Lead photon EB; R9;Counts", 100, 0., 1.1 );
    h_r9_lead_tot_ee_     = new TH1F( "h_r9_lead_tot_ee", "Lead photon EE; R9;Counts", 100, 0., 1.1 );
    h_full5x5r9_lead_tot_eb_     = new TH1F( "h_full5x5r9_lead_tot_eb", "Lead photon EB; R9;Counts", 100, 0., 1.1 );
    h_full5x5r9_lead_tot_ee_     = new TH1F( "h_full5x5r9_lead_tot_ee", "Lead photon EE; R9;Counts", 100, 0., 1.1 );

    h_phoIso_lead_tot_eb_     = new TH1F( "h_phoIso_lead_tot_eb", "Lead photon EB; phoIso (GeV);Counts", 100, 0., 30. );
    h_phoIso_lead_tot_ee_     = new TH1F( "h_phoIso_lead_tot_ee", "Lead photon EE; phoIso (GeV);Counts", 100, 0., 30. );
    h_chIso_lead_tot_eb_     = new TH1F( "h_chIso_lead_tot_eb", "Lead photon EB; chIso (GeV);Counts", 100, 0., 30. );
    h_chIso_lead_tot_ee_     = new TH1F( "h_chIso_lead_tot_ee", "Lead photon EE; chIso (GeV);Counts", 100, 0., 30. );
    h_r9_lead_tot_[0]     = new TH1F( "h_r9_lead_tot_cat0", "Lead photon Cat 0; R9;Counts", 100, 0., 1.1 );
    h_r9_lead_tot_[1]     = new TH1F( "h_r9_lead_tot_cat1", "Lead photon Cat 1; R9;Counts", 100, 0., 1.1 );
    h_r9_lead_tot_[2]     = new TH1F( "h_r9_lead_tot_cat2", "Lead photon Cat 2; R9;Counts", 100, 0., 1.1 );
    h_r9_lead_tot_[3]     = new TH1F( "h_r9_lead_tot_cat3", "Lead photon Cat 3; R9;Counts", 100, 0., 1.1 );
    //
    h_r9_sublead_tot_eb_     = new TH1F( "h_r9_sublead_tot_eb", "SubLead photon EB; R9;Counts", 100, 0., 1.1 );
    h_r9_sublead_tot_ee_     = new TH1F( "h_r9_sublead_tot_ee", "SubLead photon EE; R9;Counts", 100, 0., 1.1 );
    h_phoIso_sublead_tot_eb_ = new TH1F( "h_phoIso_sublead_tot_eb", "SubLead photon EB;phoIso (GeV);Counts", 100, 0., 30. );
    h_phoIso_sublead_tot_ee_ = new TH1F( "h_phoIso_sublead_tot_ee", "SubLead photon EE;phoIso (GeV);Counts", 100, 0., 30. );
    h_chIso_sublead_tot_eb_ = new TH1F( "h_chIso_sublead_tot_eb", "SubLead photon EB;chIso (GeV);Counts", 100, 0., 30. );
    h_chIso_sublead_tot_ee_ = new TH1F( "h_chIso_sublead_tot_ee", "SubLead photon EE;chIso (GeV);Counts", 100, 0., 30. );
    h_r9_sublead_tot_[0]  = new TH1F( "h_r9_sublead_tot_cat0", "SubLead photon Cat 0;R9;Counts", 100, 0., 1.1 );
    h_r9_sublead_tot_[1]  = new TH1F( "h_r9_sublead_tot_cat1", "SubLead photon Cat 1;R9;Counts", 100, 0., 1.1 );
    h_r9_sublead_tot_[2]  = new TH1F( "h_r9_sublead_tot_cat2", "SubLead photon Cat 2;R9;Counts", 100, 0., 1.1 );
    h_r9_sublead_tot_[3]  = new TH1F( "h_r9_sublead_tot_cat3", "SubLead photon Cat 3;R9;Counts", 100, 0., 1.1 );
    //
    h_pt_lead_offl_[0]     = new TH1F( "h_pt_lead_offl_cat0", "Lead photon Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_offl_[1]     = new TH1F( "h_pt_lead_offl_cat1", "Lead photon Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_offl_[2]     = new TH1F( "h_pt_lead_offl_cat2", "Lead photon Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_offl_[3]     = new TH1F( "h_pt_lead_offl_cat3", "Lead photon Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_pt_sublead_offl_[0]  = new TH1F( "h_pt_sublead_offl_cat0", "SubLead photon Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_offl_[1]  = new TH1F( "h_pt_sublead_offl_cat1", "SubLead photon Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_offl_[2]  = new TH1F( "h_pt_sublead_offl_cat2", "SubLead photon Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_offl_[3]  = new TH1F( "h_pt_sublead_offl_cat3", "SubLead photon Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_eta_lead_offl_[0]    = new TH1F( "h_eta_lead_offl_cat0", "Lead photon Cat 0;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_offl_[1]    = new TH1F( "h_eta_lead_offl_cat1", "Lead photon Cat 1;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_offl_[2]    = new TH1F( "h_eta_lead_offl_cat2", "Lead photon Cat 2;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_offl_[3]    = new TH1F( "h_eta_lead_offl_cat3", "Lead photon Cat 3;#eta;Counts", 68, -3.4, 3.4 );
    //
    h_eta_sublead_offl_[0] = new TH1F( "h_eta_sublead_offl_cat0", "SubLead photon Cat 0;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_offl_[1] = new TH1F( "h_eta_sublead_offl_cat1", "SubLead photon Cat 1;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_offl_[2] = new TH1F( "h_eta_sublead_offl_cat2", "SubLead photon Cat 2;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_offl_[3] = new TH1F( "h_eta_sublead_offl_cat3", "SubLead photon Cat 3;#eta;Counts", 68, -3.4, 3.4 );
    //
    h_mass_offl_[0]        = new TH1F( "h_mass_offl_cat0", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_offl_[1]        = new TH1F( "h_mass_offl_cat1", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_offl_[2]        = new TH1F( "h_mass_offl_cat2", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_offl_[3]        = new TH1F( "h_mass_offl_cat3", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    //
    h_pt_lead_hlt_[0]     = new TH1F( "h_pt_lead_hlt_cat0", "Lead photon Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_hlt_[1]     = new TH1F( "h_pt_lead_hlt_cat1", "Lead photon Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_hlt_[2]     = new TH1F( "h_pt_lead_hlt_cat2", "Lead photon Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_lead_hlt_[3]     = new TH1F( "h_pt_lead_hlt_cat3", "Lead photon Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_pt_sublead_hlt_[0]  = new TH1F( "h_pt_sublead_hlt_cat0", "SubLead photon Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_hlt_[1]  = new TH1F( "h_pt_sublead_hlt_cat1", "SubLead photon Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_hlt_[2]  = new TH1F( "h_pt_sublead_hlt_cat2", "SubLead photon Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_sublead_hlt_[3]  = new TH1F( "h_pt_sublead_hlt_cat3", "SubLead photon Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_eta_lead_hlt_[0]    = new TH1F( "h_eta_lead_hlt_cat0", "Lead photon Cat 0;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_hlt_[1]    = new TH1F( "h_eta_lead_hlt_cat1", "Lead photon Cat 1;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_hlt_[2]    = new TH1F( "h_eta_lead_hlt_cat2", "Lead photon Cat 2;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_lead_hlt_[3]    = new TH1F( "h_eta_lead_hlt_cat3", "Lead photon Cat 3;#eta;Counts", 68, -3.4, 3.4 );
    //
    h_eta_sublead_hlt_[0] = new TH1F( "h_eta_sublead_hlt_cat0", "SubLead photon Cat 0;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_hlt_[1] = new TH1F( "h_eta_sublead_hlt_cat1", "SubLead photon Cat 1;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_hlt_[2] = new TH1F( "h_eta_sublead_hlt_cat2", "SubLead photon Cat 2;#eta;Counts", 68, -3.4, 3.4 );
    h_eta_sublead_hlt_[3] = new TH1F( "h_eta_sublead_hlt_cat3", "SubLead photon Cat 3;#eta;Counts", 68, -3.4, 3.4 );
    //
    h_mass_hlt_[0]        = new TH1F( "h_mass_hlt_cat0", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_hlt_[1]        = new TH1F( "h_mass_hlt_cat1", "diPhoton Mass Cat 1;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_hlt_[2]        = new TH1F( "h_mass_hlt_cat2", "diPhoton Mass Cat 2;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_mass_hlt_[3]        = new TH1F( "h_mass_hlt_cat3", "diPhoton Mass Cat 3;m_{#gg}(GeV);Count", 80, 80., 160. );
    //
    nEvents_ = 0;
    nEventsWithTwoGenPhotons_ = 0;
    nEventsWithTwoRecoPhotons_ = 0;
    nGenPhotons_ = 0;
    nMatched = 0;
    nSinglePhoPassingAODSel_ = 0;
    nSinglePhoPassingAODSelPlusPt20_ = 0;
    nDiphoAfterHlt_ = 0;
    nDiphoAfterHltAndPresel_ = 0;
    nDiphoPassingEtaCut_ = 0;
    nDiphoMatched_ = 0;
    nDiPhoPrompt_ = 0;
    nDiphoPassing_ = 0;
    nMissing_ = 0;


    /// all variables before pre-selection
    h_pt_tot_[0]     = new TH1F( "h_pt_tot_cat0", "Pt Cat 0;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_tot_[1]     = new TH1F( "h_pt_tot_cat1", "Pt Cat 1;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_tot_[2]     = new TH1F( "h_pt_tot_cat2", "Pt Cat 2;Pt (GeV);Counts", 100, 0., 150. );
    h_pt_tot_[3]     = new TH1F( "h_pt_tot_cat3", "Pt Cat 3;Pt (GeV);Counts", 100, 0., 150. );
    //
    h_hoe_tot_[0]        = new TH1F( "h_hoe_tot_cat0", "H/E Cat 0; H/E;Count", 50, 0., 0.5 );
    h_hoe_tot_[1]        = new TH1F( "h_hoe_tot_cat1", "H/E Cat 1; H/E;Count", 50, 0., 0.5 );
    h_hoe_tot_[2]        = new TH1F( "h_hoe_tot_cat2", "H/E Cat 2; H/E;Count", 50, 0., 0.5 );
    h_hoe_tot_[3]        = new TH1F( "h_hoe_tot_cat3", "H/E Cat 3; H/E;Count", 50, 0., 0.5 );
    //
    h_newhoe_tot_[0]        = new TH1F( "h_newhoe_tot_cat0", "H/E Cat 0; H/E;Count", 50, 0., 0.5 );
    h_newhoe_tot_[1]        = new TH1F( "h_newhoe_tot_cat1", "H/E Cat 1; H/E;Count", 50, 0., 0.5 );
    h_newhoe_tot_[2]        = new TH1F( "h_newhoe_tot_cat2", "H/E Cat 2; H/E;Count", 50, 0., 0.5 );
    h_newhoe_tot_[3]        = new TH1F( "h_newhoe_tot_cat3", "H/E Cat 3; H/E;Count", 50, 0., 0.5 );
    //
    h_r9_tot_[0]        = new TH1F( "h_r9_tot_cat0", "R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_r9_tot_[1]        = new TH1F( "h_r9_tot_cat1", "R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_r9_tot_[2]        = new TH1F( "h_r9_tot_cat2", "R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_r9_tot_[3]        = new TH1F( "h_r9_tot_cat3", "R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h_sieie_tot_[0]        = new TH1F( "h_sieie_tot_cat0", "#sigma_{i#etai#eta} Cat 0; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_sieie_tot_[1]        = new TH1F( "h_sieie_tot_cat1", "#sigma_{i#etai#eta} Cat 1; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_sieie_tot_[2]        = new TH1F( "h_sieie_tot_cat2", "#sigma_{i#etai#eta} Cat 2; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_sieie_tot_[3]        = new TH1F( "h_sieie_tot_cat3", "#sigma_{i#etai#eta} Cat 3; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    //
    h_phoIso_tot_[0]        = new TH1F( "h_phoIso_tot_cat0", "phoIso Cat 0; phoIso(GeV);Count", 100, 0., 10. );
    h_phoIso_tot_[1]        = new TH1F( "h_phoIso_tot_cat1", "phoIso Cat 1; phoIso(Gev);Count", 100, 0., 10. );
    h_phoIso_tot_[2]        = new TH1F( "h_phoIso_tot_cat2", "phoIso Cat 2; phoIso(GeV);Count", 100, 0., 10. );
    h_phoIso_tot_[3]        = new TH1F( "h_phoIso_tot_cat3", "phoIso Cat 3; phoIso(GeV);Count", 100, 0., 10. );
    //
    h_chIso_tot_[0]        = new TH1F( "h_chIso_tot_cat0", "chIso Cat 0; chIso(GeV);Count", 100, 0., 10. );
    h_chIso_tot_[1]        = new TH1F( "h_chIso_tot_cat1", "chIso Cat 1; chIso(Gev);Count", 100, 0., 10. );
    h_chIso_tot_[2]        = new TH1F( "h_chIso_tot_cat2", "chIso Cat 2; chIso(GeV);Count", 100, 0., 10. );
    h_chIso_tot_[3]        = new TH1F( "h_chIso_tot_cat3", "chIso Cat 3; chIso(GeV);Count", 100, 0., 10. );


    // N-1 plots
    h_nMin1_hoe_offl_[0]        = new TH1F( "h_nMin1_hoe_offl_cat0", "N-1 plot: H/E Cat 0; H/E;Count", 50, 0., 0.5 );
    h_nMin1_hoe_offl_[1]        = new TH1F( "h_nMin1_hoe_offl_cat1", "N-1 plot: H/E Cat 1; H/E;Count", 50, 0., 0.5 );
    h_nMin1_hoe_offl_[2]        = new TH1F( "h_nMin1_hoe_offl_cat2", "N-1 plot: H/E Cat 2; H/E;Count", 50, 0., 0.5 );
    h_nMin1_hoe_offl_[3]        = new TH1F( "h_nMin1_hoe_offl_cat3", "N-1 plot: H/E Cat 3; H/E;Count", 50, 0., 0.5 );
    //
    h_nMin1_hoe_hlt_[0]        = new TH1F( "h_nMin1_hoe_hlt_cat0", "N-1 plot: H/E Cat 0; H/E;Count", 50, 0., 0.5 );
    h_nMin1_hoe_hlt_[1]        = new TH1F( "h_nMin1_hoe_hlt_cat1", "N-1 plot: H/E Cat 1; H/E;Count", 50, 0., 0.5 );
    h_nMin1_hoe_hlt_[2]        = new TH1F( "h_nMin1_hoe_hlt_cat2", "N-1 plot: H/E Cat 2; H/E;Count", 50, 0., 0.5 );
    h_nMin1_hoe_hlt_[3]        = new TH1F( "h_nMin1_hoe_hlt_cat3", "N-1 plot: H/E Cat 3; H/E;Count", 50, 0., 0.5 );
    //
    h_nMin1_pt_offl_[0]        = new TH1F( "h_nMin1_pt_offl_cat0", "N-1 plot: Pt Cat 0; Pt(GeV);Count", 100, 0., 200. );
    h_nMin1_pt_offl_[1]        = new TH1F( "h_nMin1_pt_offl_cat1", "N-1 plot: Pt Cat 1; Pt(Gev);Count", 100, 0., 200. );
    h_nMin1_pt_offl_[2]        = new TH1F( "h_nMin1_pt_offl_cat2", "N-1 plot: Pt Cat 2; Pt(GeV);Count", 100, 0., 200. );
    h_nMin1_pt_offl_[3]        = new TH1F( "h_nMin1_pt_offl_cat3", "N-1 plot: Pt Cat 3; Pt(GeV);Count", 100, 0., 200. );
    //
    h_nMin1_pt_hlt_[0]        = new TH1F( "h_nMin1_pt_hlt_cat0", "N-1 plot: Pt Cat 0; Pt(GeV);Count", 100, 0., 200. );
    h_nMin1_pt_hlt_[1]        = new TH1F( "h_nMin1_pt_hlt_cat1", "N-1 plot: Pt Cat 1; Pt(Gev);Count", 100, 0., 200. );
    h_nMin1_pt_hlt_[2]        = new TH1F( "h_nMin1_pt_hlt_cat2", "N-1 plot: Pt Cat 2; Pt(GeV);Count", 100, 0., 200. );
    h_nMin1_pt_hlt_[3]        = new TH1F( "h_nMin1_pt_hlt_cat3", "N-1 plot: Pt Cat 3; Pt(GeV);Count", 100, 0., 200. );
    //
    h_nMin1_r9_offl_[0]        = new TH1F( "h_nMin1_r9_offl_cat0", "N-1 plot: R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_offl_[1]        = new TH1F( "h_nMin1_r9_offl_cat1", "N-1 plot: R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_offl_[2]        = new TH1F( "h_nMin1_r9_offl_cat2", "N-1 plot: R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_offl_[3]        = new TH1F( "h_nMin1_r9_offl_cat3", "N-1 plot: R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h_nMin1_r9_low_offl_[0]        = new TH1F( "h_nMin1_r9_low_offl_cat0", "N-1 plot: R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_low_offl_[1]        = new TH1F( "h_nMin1_r9_low_offl_cat1", "N-1 plot: R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_low_offl_[2]        = new TH1F( "h_nMin1_r9_low_offl_cat2", "N-1 plot: R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_low_offl_[3]        = new TH1F( "h_nMin1_r9_low_offl_cat3", "N-1 plot: R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h_nMin1_r9_high_offl_[0]        = new TH1F( "h_nMin1_r9_high_offl_cat0", "N-1 plot: R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_high_offl_[1]        = new TH1F( "h_nMin1_r9_high_offl_cat1", "N-1 plot: R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_high_offl_[2]        = new TH1F( "h_nMin1_r9_high_offl_cat2", "N-1 plot: R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_high_offl_[3]        = new TH1F( "h_nMin1_r9_high_offl_cat3", "N-1 plot: R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h2_nMin1_r9_offl_[0]        = new TH2F( "h2_nMin1_r9_offl_cat0", "N-1 plot: R9 Cat 0; low R9 ; high R9", 80, 0.3, 1.1, 80, 0.3, 1.1 );
    h2_nMin1_r9_offl_[1]        = new TH2F( "h2_nMin1_r9_offl_cat1", "N-1 plot: R9 Cat 1; low R9 ; high R9", 80, 0.3, 1.1, 80, 0.3, 1.1 );
    h2_nMin1_r9_offl_[2]        = new TH2F( "h2_nMin1_r9_offl_cat2", "N-1 plot: R9 Cat 2; low R9 ; high R9", 80, 0.3, 1.1, 80, 0.3, 1.1 );
    h2_nMin1_r9_offl_[3]        = new TH2F( "h2_nMin1_r9_offl_cat3", "N-1 plot: R9 Cat 3; low R9 ; high R9", 80, 0.3, 1.1, 80, 0.3, 1.1 );
    //
    h_nMin1_r9_hlt_[0]        = new TH1F( "h_nMin1_r9_hlt_cat0", "N-1 plot: R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_hlt_[1]        = new TH1F( "h_nMin1_r9_hlt_cat1", "N-1 plot: R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_hlt_[2]        = new TH1F( "h_nMin1_r9_hlt_cat2", "N-1 plot: R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_hlt_[3]        = new TH1F( "h_nMin1_r9_hlt_cat3", "N-1 plot: R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h_nMin1_r9_low_hlt_[0]        = new TH1F( "h_nMin1_r9_low_hlt_cat0", "N-1 plot: R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_low_hlt_[1]        = new TH1F( "h_nMin1_r9_low_hlt_cat1", "N-1 plot: R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_low_hlt_[2]        = new TH1F( "h_nMin1_r9_low_hlt_cat2", "N-1 plot: R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_low_hlt_[3]        = new TH1F( "h_nMin1_r9_low_hlt_cat3", "N-1 plot: R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h_nMin1_r9_high_hlt_[0]        = new TH1F( "h_nMin1_r9_high_hlt_cat0", "N-1 plot: R9 Cat 0; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_high_hlt_[1]        = new TH1F( "h_nMin1_r9_high_hlt_cat1", "N-1 plot: R9 Cat 1; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_high_hlt_[2]        = new TH1F( "h_nMin1_r9_high_hlt_cat2", "N-1 plot: R9 Cat 2; R9 ;Count", 100, 0., 1.1 );
    h_nMin1_r9_high_hlt_[3]        = new TH1F( "h_nMin1_r9_high_hlt_cat3", "N-1 plot: R9 Cat 3; R9 ;Count", 100, 0., 1.1 );
    //
    h_nMin1_sieie_offl_[0]        = new TH1F( "h_nMin1_sieie_offl_cat0", "N-1 plot: #sigma_{i#etai#eta} Cat 0; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_nMin1_sieie_offl_[1]        = new TH1F( "h_nMin1_sieie_offl_cat1", "N-1 plot: #sigma_{i#etai#eta} Cat 1; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_nMin1_sieie_offl_[2]        = new TH1F( "h_nMin1_sieie_offl_cat2", "N-1 plot: #sigma_{i#etai#eta} Cat 2; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_nMin1_sieie_offl_[3]        = new TH1F( "h_nMin1_sieie_offl_cat3", "N-1 plot: #sigma_{i#etai#eta} Cat 3; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    //
    h_nMin1_sieie_hlt_[0]        = new TH1F( "h_nMin1_sieie_hlt_cat0", "N-1 plot: #sigma_{i#etai#eta} Cat 0; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_nMin1_sieie_hlt_[1]        = new TH1F( "h_nMin1_sieie_hlt_cat1", "N-1 plot: #sigma_{i#etai#eta} Cat 1; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_nMin1_sieie_hlt_[2]        = new TH1F( "h_nMin1_sieie_hlt_cat2", "N-1 plot: #sigma_{i#etai#eta} Cat 2; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    h_nMin1_sieie_hlt_[3]        = new TH1F( "h_nMin1_sieie_hlt_cat3", "N-1 plot: #sigma_{i#etai#eta} Cat 3; #sigma_{i#etai#eta};Count", 100, 0., 0.05 );
    //
    h_nMin1_phoIso_offl_[0]        = new TH1F( "h_nMin1_phoIso_offl_cat0", "N-1 plot: phoIso Cat 0; phoIso(GeV);Count", 100, 0., 10. );
    h_nMin1_phoIso_offl_[1]        = new TH1F( "h_nMin1_phoIso_offl_cat1", "N-1 plot: phoIso Cat 1; phoIso(Gev);Count", 100, 0., 10. );
    h_nMin1_phoIso_offl_[2]        = new TH1F( "h_nMin1_phoIso_offl_cat2", "N-1 plot: phoIso Cat 2; phoIso(GeV);Count", 100, 0., 10. );
    h_nMin1_phoIso_offl_[3]        = new TH1F( "h_nMin1_phoIso_offl_cat3", "N-1 plot: phoIso Cat 3; phoIso(GeV);Count", 100, 0., 10. );
    //
    h_nMin1_phoIso_hlt_[0]        = new TH1F( "h_nMin1_phoIso_hlt_cat0", "N-1 plot: phoIso Cat 0; phoIso(GeV);Count", 100, 0., 10. );
    h_nMin1_phoIso_hlt_[1]        = new TH1F( "h_nMin1_phoIso_hlt_cat1", "N-1 plot: phoIso Cat 1; phoIso(Gev);Count", 100, 0., 10. );
    h_nMin1_phoIso_hlt_[2]        = new TH1F( "h_nMin1_phoIso_hlt_cat2", "N-1 plot: phoIso Cat 2; phoIso(GeV);Count", 100, 0., 10. );
    h_nMin1_phoIso_hlt_[3]        = new TH1F( "h_nMin1_phoIso_hlt_cat3", "N-1 plot: phoIso Cat 3; phoIso(GeV);Count", 100, 0., 10. );
    //
    h_nMin1_chIso_offl_[0]        = new TH1F( "h_nMin1_chIso_offl_cat0", "N-1 plot: chIso Cat 0; chIso(GeV);Count", 100, 0., 10. );
    h_nMin1_chIso_offl_[1]        = new TH1F( "h_nMin1_chIso_offl_cat1", "N-1 plot: chIso Cat 1; chIso(Gev);Count", 100, 0., 10. );
    h_nMin1_chIso_offl_[2]        = new TH1F( "h_nMin1_chIso_offl_cat2", "N-1 plot: chIso Cat 2; chIso(GeV);Count", 100, 0., 10. );
    h_nMin1_chIso_offl_[3]        = new TH1F( "h_nMin1_chIso_offl_cat3", "N-1 plot: chIso Cat 3; chIso(GeV);Count", 100, 0., 10. );
    //
    h_nMin1_chIso_hlt_[0]        = new TH1F( "h_nMin1_chIso_hlt_cat0", "N-1 plot: chIso Cat 0; chIso(GeV);Count", 100, 0., 10. );
    h_nMin1_chIso_hlt_[1]        = new TH1F( "h_nMin1_chIso_hlt_cat1", "N-1 plot: chIso Cat 1; chIso(Gev);Count", 100, 0., 10. );
    h_nMin1_chIso_hlt_[2]        = new TH1F( "h_nMin1_chIso_hlt_cat2", "N-1 plot: chIso Cat 2; chIso(GeV);Count", 100, 0., 10. );
    h_nMin1_chIso_hlt_[3]        = new TH1F( "h_nMin1_chIso_hlt_cat3", "N-1 plot: chIso Cat 3; chIso(GeV);Count", 100, 0., 10. );
    //
    h_nMin1_mass_offl_[0]        = new TH1F( "h_nMin1_mass_offl_cat0", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_nMin1_mass_offl_[1]        = new TH1F( "h_nMin1_mass_offl_cat1", "diPhoton Mass Cat 1;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_nMin1_mass_offl_[2]        = new TH1F( "h_nMin1_mass_offl_cat2", "diPhoton Mass Cat 2;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_nMin1_mass_offl_[3]        = new TH1F( "h_nMin1_mass_offl_cat3", "diPhoton Mass Cat 3;m_{#gg}(GeV);Count", 80, 80., 160. );
    //
    h_nMin1_mass_hlt_[0]        = new TH1F( "h_nMin1_mass_hlt_cat0", "diPhoton Mass Cat 0;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_nMin1_mass_hlt_[1]        = new TH1F( "h_nMin1_mass_hlt_cat1", "diPhoton Mass Cat 1;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_nMin1_mass_hlt_[2]        = new TH1F( "h_nMin1_mass_hlt_cat2", "diPhoton Mass Cat 2;m_{#gg}(GeV);Count", 80, 80., 160. );
    h_nMin1_mass_hlt_[3]        = new TH1F( "h_nMin1_mass_hlt_cat3", "diPhoton Mass Cat 3;m_{#gg}(GeV);Count", 80, 80., 160. );

    //// low mass crap
    h2_lowMass_eta_offl_        = new TH2F( "h2_lowMass_eta_offl",  "Low mass: GEN vs RECO #eta;#eta_{RECO} ;#eta_{GEN}",  68, -3.4, 3.4,  68, -3.4, 3.4 );
    h2_lowMass_pt_offl_         = new TH2F( "h2_lowMass_pt_offl",   "Low mass: GEN vs RECO Pt ;Pt_{RECO} (GeV) ;Pt_{GEN} (GeV)", 100, 0., 200., 100, 0., 200. );
    h2_lowMass_mass_offl_       = new TH2F( "h2_lowMass_mass_offl", "Low mass: GEN vs RECO mass ;m_{RECO} (GeV) ;m_{GEN} (GeV)",   200, 60., 160., 200, 60., 160. );
    h2_lowMass_mass_hlt_       = new TH2F( "h2_lowMass_mass_hlt", "Low mass: HLT vs OFFL pho mass ;m_{RECO} (GeV) ;m_{HLT} (GeV)", 200, 60., 160., 200, 60., 160. );
    h2_lowMass_massFromSC_hlt_       = new TH2F( "h2_lowMass_massFromSC_hlt", "Low mass: HLT vs OFFL SC mass ;m_{RECO} (GeV) ;m_{HLT} (GeV)", 200, 60., 160., 200,
            60., 160. );
    h2_lowMass_massSCvsPho_offl_       = new TH2F( "h2_lowMass_massSCvsPho_offl", "Low mass: SC vs Pho mass ;m_{Pho} (GeV) ;m_{SC} (GeV)",    200, 60., 160., 200,
            60., 160. );

    //// Test of the miniAOD photon content
    h_eta_gen_    = new TH1F( "h_eta_gen", "Photon #eta Gen;Counts", 68, -3.4, 3.4 );
    h_pt_aod_     = new TH1F( "h_pt_aod", "Photon pt spectrum from miniAOD;Pt (GeV);Counts", 100, 0., 150. );
    h_hoe_aod_    = new TH1F( "h_hoe_aod", "Photon H/E from AOD; H/E;Count", 50, 0., 0.5 );
    h_eta_aod_    = new TH1F( "h_eta_aod", "Photon #eta from AOD;Counts", 68, -3.4, 3.4 );
    debug_ = true;


}


DiphotonPreselectionValidation::~DiphotonPreselectionValidation()
{
    TFile *file = new TFile( outputFileName_.c_str(), "recreate" );

    h_sim_pt_->Write();
    h_reco_pt_->Write();

    h_nVtx_tot_ ->Write();
    h_nVtx_offl_ ->Write();
    h_nVtx_hlt_ ->Write();

//
    h_r9_lead_tot_eb_     ->Write();
    h_full5x5r9_lead_tot_eb_ ->Write();
    h_full5x5r9_lead_tot_ee_ ->Write();
    h_r9_lead_tot_ee_     ->Write();
    h_r9_sublead_tot_eb_     ->Write();
    h_r9_sublead_tot_ee_     ->Write();
//
    h_phoIso_lead_tot_eb_     ->Write();
    h_phoIso_lead_tot_ee_     ->Write();
    h_phoIso_sublead_tot_eb_     ->Write();
    h_phoIso_sublead_tot_ee_     ->Write();
//
    h_chIso_lead_tot_eb_     ->Write();
    h_chIso_lead_tot_ee_     ->Write();
    h_chIso_sublead_tot_eb_     ->Write();
    h_chIso_sublead_tot_ee_     ->Write();


    for( int iCat = 0; iCat < 4; iCat++ ) {

        h_pt_lead_tot_[iCat]     ->Write();
        h_pt_sublead_tot_[iCat]  ->Write();
        h_r9_lead_tot_[iCat]     ->Write();
        h_r9_sublead_tot_[iCat]     ->Write();
        h_eta_lead_tot_[iCat]    ->Write();
        h_eta_sublead_tot_[iCat] ->Write();
        h_mass_tot_[iCat]        ->Write();
        //
        h_pt_lead_offl_[iCat]     ->Write();
        h_pt_sublead_offl_[iCat]  ->Write();
        h_eta_lead_offl_[iCat]    ->Write();
        h_eta_sublead_offl_[iCat] ->Write();
        h_mass_offl_[iCat]        ->Write();
        //
        h_pt_lead_hlt_[iCat]     ->Write();
        h_pt_sublead_hlt_[iCat]  ->Write();
        h_eta_lead_hlt_[iCat]    ->Write();
        h_eta_sublead_hlt_[iCat] ->Write();
        h_mass_hlt_[iCat]        ->Write();

        /// variable before pre-selection

        h_pt_tot_[iCat] ->Write();
        h_hoe_tot_[iCat] ->Write();
        h_newhoe_tot_[iCat] ->Write();
        h_r9_tot_[iCat] ->Write();
        h_sieie_tot_[iCat] ->Write();
        h_phoIso_tot_[iCat] ->Write();
        h_chIso_tot_[iCat] ->Write();


        // N-1 stuff
        h_nMin1_pt_offl_[iCat] ->Write();
        h_nMin1_hoe_offl_[iCat] ->Write();
        h2_nMin1_r9_offl_[iCat] ->Write();
        h_nMin1_r9_offl_[iCat] ->Write();
        h_nMin1_r9_low_offl_[iCat] ->Write();
        h_nMin1_r9_high_offl_[iCat] ->Write();
        h_nMin1_sieie_offl_[iCat] ->Write();
        h_nMin1_phoIso_offl_[iCat] ->Write();
        h_nMin1_chIso_offl_[iCat] ->Write();
        h_nMin1_mass_offl_[iCat] ->Write();
        //
        h_nMin1_pt_hlt_[iCat] ->Write();
        h_nMin1_hoe_hlt_[iCat] ->Write();
        h_nMin1_r9_hlt_[iCat] ->Write();
        h_nMin1_r9_low_hlt_[iCat] ->Write();
        h_nMin1_r9_high_hlt_[iCat] ->Write();
        h_nMin1_sieie_hlt_[iCat] ->Write();
        h_nMin1_phoIso_hlt_[iCat] ->Write();
        h_nMin1_chIso_hlt_[iCat] ->Write();
        h_nMin1_mass_hlt_[iCat] ->Write();

    }
    // low mass crap
    h2_lowMass_eta_offl_ ->Write();
    h2_lowMass_pt_offl_ ->Write();
    h2_lowMass_mass_offl_ ->Write();
    h2_lowMass_massSCvsPho_offl_ ->Write();
    h2_lowMass_mass_hlt_ ->Write();
    h2_lowMass_massFromSC_hlt_ ->Write();

    ////
    h_eta_gen_->Write();
    h_eta_aod_->Write();
    h_pt_aod_->Write();
    h_hoe_aod_->Write();



    file->Close();
}


void DiphotonPreselectionValidation::initTrig( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames )
{

    trigger_indices.clear();
    for( unsigned int i = 0; i < triggerNames.triggerNames().size(); i++ ) {
        std::string trimmedName = HLTConfigProvider::removeVersion( triggerNames.triggerName( i ) );
        //std::cout << "trimmedName " << trimmedName << std::endl;
        trigger_indices[trimmedName] = triggerNames.triggerIndex( triggerNames.triggerName( i ) );
    }
}



bool DiphotonPreselectionValidation::hltPass( edm::Handle<edm::TriggerResults> triggerBits )
{

    for( std::map<std::string, unsigned int>::const_iterator cit = trigger_indices.begin(); cit != trigger_indices.end(); cit++ ) {
        if( triggerBits->accept( cit->second ) ) {
            //cout << " accept " << " " << cit->first << " " << cit->second << endl;
            std::vector<std::string>::const_iterator it = find( filterName_.begin(), filterName_.end(), cit->first );

            if( it != filterName_.end() )
            { return true; }
        }
    }

    return false;
}

std::pair<bool, math::XYZTLorentzVector>  DiphotonPreselectionValidation::onlineOfflineMatching( const edm::TriggerNames &triggerNames,
        edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
        math::XYZTLorentzVector p4, std::string filterLabel, float dRmin = 0.15 )
{



    std::pair<bool, math::XYZTLorentzVector> result;
    result.first = false;
    result.second = math::XYZTLorentzVector( 0, 0, 0, 0 );
    float minDr = 9999.;
    float dR = 9999.;
    math::XYZTLorentzVector bestP4;
    for( pat::TriggerObjectStandAlone obj : *triggerObjects ) {
        obj.unpackPathNames( triggerNames );
        if( obj.hasFilterLabel( filterLabel ) ) {
            dR = deltaR( p4, obj.p4() );
            std::cout << "onlineOfflineMatching hlt eta " << obj.eta() << " dR: " << dR << std::endl;
            //math::XYZTLorentzVector temp;
            if( dR < minDr ) {
                minDr = dR;
                bestP4 = obj.p4();
            }
        }
        if( dR > dRmin ) { continue; }

        result.first = true;
        result.second = bestP4;

    }

    //        temp.SetPxPyPzE(obj.px(),obj.py(), obj.pz(),obj.p());
    std::cout << result.second.Eta() << "==" << p4.Eta() << std::endl;
    cout << " ismatched " <<  result.first << " P4 " << result.second << endl;






    return result;
}




std::vector<math::XYZTLorentzVector> DiphotonPreselectionValidation::hltP4( const edm::TriggerNames &triggerNames,
        edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects, std::vector<std::string> filterLabels )
{

    std::vector< math::XYZTLorentzVector> triggerCandidates;

    for( pat::TriggerObjectStandAlone obj : *triggerObjects ) {
        obj.unpackPathNames( triggerNames );
        for( std::string filter : filterLabels ) {
            if( obj.hasFilterLabel( filter ) )
            { triggerCandidates.push_back( obj.p4() ); }
        }
    }


    return triggerCandidates;
}






void
DiphotonPreselectionValidation::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{

    // ********************************************************************************

    // access edm objects
    Handle<View<flashgg::Photon> > photonsHandle;
    iEvent.getByToken( photonToken_, photonsHandle );
    //
    Handle<View<flashgg::DiPhotonCandidate> > diphotons;
    iEvent.getByToken( diphotonToken_, diphotons );
    //
    edm::Handle<edm::TriggerResults> triggerBits;
    iEvent.getByToken( triggerBits_, triggerBits );
    //
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    if( getHLTcandidates_ ) {
        iEvent.getByToken( triggerObjects_, triggerObjects );
    }
    //
    Handle<View<reco::Vertex> > primaryVertices;
    iEvent.getByToken( vertexToken_, primaryVertices );
    //
    Handle<vector<flashgg::GenPhotonExtra> > genPhotonsHandle;
    if( ! iEvent.isRealData() ) {
        iEvent.getByToken( genPhotonToken_, genPhotonsHandle );
    }
    //
    Handle<double> rhoHandle;
    iEvent.getByLabel( rhoFixedGrid_, rhoHandle );
    const double rhoFixedGrd = *( rhoHandle.product() );
    double effectiveAreaEB = 0.16544;
    double effectiveAreaEE = 0.13212;



    if( !triggerBits.isValid() ) {
        LogDebug( "" ) << "TriggerResults product not found - returning result=false!";
        return;
    }


    // Apply event selection
    const edm::TriggerNames &triggerNames = iEvent.triggerNames( *triggerBits );
    initTrig( *triggerBits, triggerNames );


    //*************************************
    nEvents_++;

    // ********************************************************************************

    const auto &genPhotons = *genPhotonsHandle;
    const auto &photons = *photonsHandle;
    //int nGenPhoFromHiggs=0;


    if( genPhotons.size() < 2 ) { return; }
    nEventsWithTwoGenPhotons_++;
    cout << " Gen photon size " <<  genPhotons.size() << endl;
    if( photons.size() < 2 ) { return; }
    nEventsWithTwoRecoPhotons_++;
    cout << " Reco photon size " <<  photons.size() << endl;


    // int lMatched=0;
    for( unsigned int i1 = 0; i1 < genPhotons.size();  i1++ ) {
        auto gen1 = genPhotons[i1].ptr();
        for( unsigned int i2 = i1 + 1; i2 < genPhotons.size();  i2++ ) {
            auto gen2 = genPhotons[i2].ptr();
            if( !( gen1->pdgId() == 22 && gen2->pdgId() == 22 ) ) { continue; }
            if( !( gen1->motherRef()->pdgId() == 25 && gen2->motherRef()->pdgId() == 25 ) ) { continue; }
            if( !( abs( gen1->eta() ) < 2.5 &&  abs( gen2->eta() ) < 2.5 ) ) { continue; }
            h_sim_pt_ ->Fill( gen1->pt() );
            h_sim_pt_ ->Fill( gen2->pt() );

            nGenPhotons_++;
            cout << " selected gen photons  pt1 " << gen1->pt() << " pt2 " <<  gen2->pt() << " eta1 " << gen1->eta() << " eta2 " << gen2->eta() << endl;


            for( size_t idipho = 0; idipho < diphotons->size(); idipho++ ) {
                Ptr<flashgg::DiPhotonCandidate> diphoPtr = diphotons->ptrAt( idipho );
                if( !( diphoPtr->leadingPhoton()->hasMatchedGenPhoton() ) || !( diphoPtr->subLeadingPhoton()->hasMatchedGenPhoton() ) ) { continue; }

                if( !( ( diphoPtr->leadingPhoton()->matchedGenPhoton()->pt() == gen1->pt() &&
                         diphoPtr->subLeadingPhoton()->matchedGenPhoton()->pt() == gen2->pt() )  ||
                        ( diphoPtr->leadingPhoton()->matchedGenPhoton()->pt() == gen2->pt() &&
                          diphoPtr->subLeadingPhoton()->matchedGenPhoton()->pt() == gen1->pt() ) ) )   { continue; }
                nDiphoMatched_++;
                cout << " Has matched gen photon lead  " << diphoPtr->leadingPhoton()->hasMatchedGenPhoton() << " sub " << diphoPtr->subLeadingPhoton()->hasMatchedGenPhoton()
                     << endl;
                cout << " Has matched gen photon type lead  " << diphoPtr->leadingPhoton()->genMatchType() << " sub " << diphoPtr->subLeadingPhoton()->genMatchType() << endl;


                h_reco_pt_ ->Fill( diphoPtr->leadingPhoton()->pt() );
                h_reco_pt_ ->Fill( diphoPtr->subLeadingPhoton()->pt() );


                // leading photon
                float pho1_isEB = diphoPtr->leadingPhoton()->isEB();
                float pho1_isEE = diphoPtr->leadingPhoton()->isEE();
                float pho1_isGAP = diphoPtr->leadingPhoton()->isEBEEGap();
                float pho1_pt = diphoPtr->leadingPhoton()->pt();
                float pho1_eta = diphoPtr->leadingPhoton()->eta();
                //float pho1_r9 = diphoPtr->leadingPhoton()->r9();
                float pho1_r9 = diphoPtr->leadingPhoton()->full5x5_r9();
                float pho1_full5x5r9 =  diphoPtr->leadingPhoton()->full5x5_r9();
                float pho1_hoe = diphoPtr->leadingPhoton()->hadronicOverEm();
                float pho1_newhoe = diphoPtr->leadingPhoton()->hadTowOverEm();
                float pho1_full5x5_sieie = diphoPtr->leadingPhoton()->full5x5_sigmaIetaIeta();
                float pho1_pfChgIsoWrtChosenVtx03 = diphoPtr->leadingPhoton()->pfChgIsoWrtChosenVtx03();
                float pho1_pfPhoIso03 = diphoPtr->leadingPhoton()->pfPhoIso03();

                if( rhoCorrectedIso_ ) {
                    double effectiveArea = 0.;
                    if( diphoPtr->leadingPhoton()->isEB() )
                    { effectiveArea = effectiveAreaEB; }
                    else
                    { effectiveArea = effectiveAreaEE; }
                    pho1_pfPhoIso03 = pho1_pfPhoIso03 -  rhoFixedGrd * effectiveArea;
                }



                float pho1_trkSumPtHollowConeDR03 = diphoPtr->leadingPhoton()->trkSumPtHollowConeDR03();

                /*

                  float pho1_phi = diphoPtr->leadingPhoton()->phi();
                  float pho1_energy = diphoPtr->leadingPhoton()->energy();
                  float pho1_sieie = diphoPtr->leadingPhoton()->sigmaIetaIeta();
                  float pho1_full5x5_r9 = diphoPtr->leadingPhoton()->full5x5_r9();
                  float pho1_full5x5_hoe = diphoPtr->leadingPhoton()->hadronicOverEm();

                  float pho1_hcalTowerSumEtConeDR03 = diphoPtr->leadingPhoton()->hcalTowerSumEtConeDR03();

                  float pho1_pfChgIsoWrtChosenVtx02 = diphoPtr->leadingPhoton()->pfChgIsoWrtChosenVtx02();
                */
                // subleading photon
                float pho2_isEB = diphoPtr->subLeadingPhoton()->isEB();
                float pho2_isEE = diphoPtr->subLeadingPhoton()->isEE();
                float pho2_isGAP = diphoPtr->subLeadingPhoton()->isEBEEGap();
                float pho2_pt = diphoPtr->subLeadingPhoton()->pt();
                float pho2_eta = diphoPtr->subLeadingPhoton()->eta();
                //float pho2_r9 = diphoPtr->subLeadingPhoton()->r9();
                float pho2_r9 = diphoPtr->subLeadingPhoton()->full5x5_r9();
                float pho2_full5x5r9 = diphoPtr->subLeadingPhoton()->full5x5_r9();
                float pho2_hoe = diphoPtr->subLeadingPhoton()->hadronicOverEm();
                float pho2_newhoe = diphoPtr->subLeadingPhoton()->hadTowOverEm();
                float pho2_full5x5_sieie = diphoPtr->subLeadingPhoton()->full5x5_sigmaIetaIeta();
                float pho2_pfChgIsoWrtChosenVtx03 = diphoPtr->subLeadingPhoton()->pfChgIsoWrtChosenVtx03();
                float pho2_pfPhoIso03 = diphoPtr->subLeadingPhoton()->pfPhoIso03();

                if( rhoCorrectedIso_ ) {
                    double effectiveArea = 0.;
                    if( diphoPtr->subLeadingPhoton()->isEB() )
                    { effectiveArea = effectiveAreaEB; }
                    else
                    { effectiveArea = effectiveAreaEE; }
                    pho2_pfPhoIso03 = pho2_pfPhoIso03 -  rhoFixedGrd * effectiveArea;
                }


                float pho2_trkSumPtHollowConeDR03 = diphoPtr->subLeadingPhoton()->trkSumPtHollowConeDR03();

                /*

                  float pho2_phi = diphoPtr->subLeadingPhoton()->phi();
                  float pho2_energy = diphoPtr->subLeadingPhoton()->energy();
                  float pho2_sieie = diphoPtr->subLeadingPhoton()->sigmaIetaIeta();
                  float pho2_full5x5_r9 = diphoPtr->subLeadingPhoton()->full5x5_r9();
                  float pho2_full5x5_hoe = diphoPtr->subLeadingPhoton()->hadronicOverEm();

                  float pho2_hcalTowerSumEtConeDR03 = diphoPtr->subLeadingPhoton()->hcalTowerSumEtConeDR03();

                  float pho2_pfChgIsoWrtChosenVtx02 = diphoPtr->subLeadingPhoton()->pfChgIsoWrtChosenVtx02();
                */
                // diphoton info

                //       float pt = diphoPtr->pt();
                //float eta = diphoPtr->eta();
                float mass = diphoPtr->mass();


                //   float phi = diphoPtr->phi();
                // float energy = diphoPtr->energy();


                cout << " matching lead " << pho1_pt <<  " sublead " << pho2_pt << endl;
                nSinglePhoPassingAODSel_++;

                if( pho1_isGAP ||  pho2_isGAP ) { continue; }
                nDiphoPassingEtaCut_++;

                if( !( pho1_pt > 20  && pho2_pt > 20 ) ) { continue; }
                nSinglePhoPassingAODSelPlusPt20_++;

                // generated mass
                math::XYZTLorentzVector  genP4 =  diphoPtr->leadingPhoton()->matchedGenPhoton()->p4() +  diphoPtr->subLeadingPhoton()->matchedGenPhoton()->p4();
                float genMass = sqrt( genP4.Dot( genP4 ) );
                // calculate invariant mass using the SC and Vtx(0,0,0)
                math::XYZPoint vtx( 0., 0., 0. );
                math::XYZPoint caloPosition1 = diphoPtr->leadingPhoton()->superCluster()->position();
                math::XYZPoint caloPosition2 = diphoPtr->subLeadingPhoton()->superCluster()->position();
                math::XYZVector direction1 = caloPosition1 - vtx;
                math::XYZVector direction2 = caloPosition2 - vtx;
                math::XYZVector momentum1 = direction1.unit() * diphoPtr->leadingPhoton()->superCluster()->rawEnergy() ;
                math::XYZVector momentum2 = direction2.unit() * diphoPtr->subLeadingPhoton()->superCluster()->rawEnergy() ;
                math::XYZTLorentzVectorD p4_1( momentum1.x(), momentum1.y(), momentum1.z(), diphoPtr->leadingPhoton()->superCluster()->rawEnergy() );
                math::XYZTLorentzVectorD p4_2( momentum2.x(), momentum2.y(), momentum2.z(), diphoPtr->subLeadingPhoton()->superCluster()->rawEnergy() );
                math::XYZTLorentzVector  scP4 =  p4_1 + p4_2;
                float massFromSC = sqrt( scP4.Dot( scP4 ) );
                //mass=massFromSC;
                if( mass <= 80 ) { mass = 80.001; }
                if( mass >= 160 ) { mass = 159.001; }
                if( massFromSC <= 80 ) { massFromSC = 80.001; }
                if( massFromSC >= 160 ) { massFromSC = 159.001; }
                //

                // ***** *****
                // Define categories
                // ***** *****
                float r9_cut_value_eb = 0.85;
                float r9_cut_value_ee = 0.90;

                //        float r9_cut_value_eb=0.85;
                //float r9_cut_value_ee=0.85;

                bool diphoton_category[4];
                bool CIC[4] = {false, false, false, false};
                bool CIC_minusPt[4] = {false, false, false, false};
                bool CIC_minusHoe[4] = {false, false, false, false};
                bool CIC_minusR9[4] = {false, false, false, false};
                bool CIC_minusSieie[4] = {false, false, false, false};
                bool CIC_minusPhoIso[4] = {false, false, false, false};
                bool CIC_minusChIso[4] = {false, false, false, false};
                bool CIC_minusMass[4] = {false, false, false, false};

                // EB EB - high R9
                diphoton_category[0] = ( pho1_isEB && pho1_r9 >  r9_cut_value_eb && pho2_isEB && pho2_r9 >  r9_cut_value_eb );


                // EB EB - high R9 - low R9
                diphoton_category[1] = ( ( pho1_isEB && pho1_r9 >   r9_cut_value_eb && pho2_isEB  && pho2_r9  <= r9_cut_value_eb ) ||
                                         ( pho1_isEB && pho1_r9 <=  r9_cut_value_eb && pho2_isEB  && pho2_r9 >  r9_cut_value_eb )  ||
                                         ( pho1_isEB && pho1_r9 <=  r9_cut_value_eb && pho2_isEB  && pho2_r9 <= r9_cut_value_eb )
                                       );
                //  not EBEB - high R9
                diphoton_category[2] = ( ( pho1_isEE && pho1_r9 >  r9_cut_value_ee && pho2_isEE && pho2_r9 > r9_cut_value_ee ) ||
                                         ( pho1_isEE && pho1_r9 >  r9_cut_value_ee && pho2_isEB && pho2_r9 > r9_cut_value_eb ) ||
                                         ( pho1_isEB && pho1_r9 >  r9_cut_value_eb && pho2_isEE && pho2_r9 > r9_cut_value_ee )
                                       );



                // not EB EB - high R9 - low R9
                diphoton_category[3] = ( ( pho1_isEE && pho1_r9  > r9_cut_value_ee && pho2_isEE && pho2_r9 <= r9_cut_value_ee ) ||
                                         ( pho1_isEE && pho1_r9 <= r9_cut_value_ee && pho2_isEE && pho2_r9 >  r9_cut_value_ee ) ||
                                         ( pho1_isEE && pho1_r9 <= r9_cut_value_ee && pho2_isEE && pho2_r9 <= r9_cut_value_ee ) ||
                                         ( pho1_isEE && pho1_r9 >  r9_cut_value_ee && pho2_isEB && pho2_r9 <= r9_cut_value_eb ) ||
                                         ( pho1_isEB && pho1_r9 >  r9_cut_value_eb && pho2_isEE && pho2_r9 <= r9_cut_value_ee ) ||
                                         ( pho1_isEE && pho1_r9 <= r9_cut_value_ee && pho2_isEB && pho2_r9 >  r9_cut_value_eb ) ||
                                         ( pho1_isEB && pho1_r9 <= r9_cut_value_eb && pho2_isEE && pho2_r9 >  r9_cut_value_ee ) ||
                                         ( pho1_isEB && pho1_r9 <= r9_cut_value_eb && pho2_isEE &&  pho2_r9 <= r9_cut_value_ee ) ||
                                         ( pho1_isEE && pho1_r9 <= r9_cut_value_ee && pho2_isEB && pho2_r9 <= r9_cut_value_eb )
                                       );


                if( !( diphoton_category[0] || diphoton_category[1] ||  diphoton_category[2] ||  diphoton_category[3] ) ) {
                    nMissing_++;
                    cout << " Lead    in EB " <<   pho1_isEB << " eta " << pho1_eta << " R9 " <<  pho1_r9 << endl;
                    cout << " SubLead in EB " <<   pho2_isEB << " eta " << pho2_eta << " R9 " <<  pho2_r9 << endl;
                }


                h_nVtx_tot_ ->Fill( primaryVertices->size() );

                /////////////////////////////  Get the HLT candidates
                float massHLT = -999.;
                math::XYZTLorentzVector  hltP4;
                if( hltPass( triggerBits ) )  {

                    if( getHLTcandidates_ ) {
                        for( size_t f = 0; f < lastfilterName_.size(); f++ ) {
                            std::pair<bool, math::XYZTLorentzVector> leadHLT = onlineOfflineMatching( triggerNames, triggerObjects, diphoPtr->leadingPhoton()->p4(), lastfilterName_[f] );
                            std::pair<bool, math::XYZTLorentzVector> subLeadHLT = onlineOfflineMatching( triggerNames, triggerObjects, diphoPtr->subLeadingPhoton()->p4(),
                                    lastfilterName_[f] );
                            cout << "    " << endl;
                            if( leadHLT.first == true &&  subLeadHLT.first == true ) {
                                hltP4 =  leadHLT.second + subLeadHLT.second;
                                massHLT = sqrt( hltP4.Dot( hltP4 ) );
                            }
                        }
                        if( massHLT > 0 ) {
                            if( massHLT <= 80 )  {
                                // massHLT = 80.001;
                                cout << " massHLT " << massHLT << " hltP4 " << hltP4 << endl;
                            }
                            if( massHLT >= 160 ) { massHLT = 159.001; }
                        }
                        // h2_lowMass_mass_hlt_ -> Fill ( mass, massHLT);
                        // h2_lowMass_massFromSC_hlt_ -> Fill ( massFromSC, massHLT);

                    }

                }



                if( mass < 95 ) {
                    nLowMassPair_++;
                    if( debug_ ) {
                        std::cout << " ----------- " << std::endl;
                        std::cout << " I have found an odd low RECO mass pair " <<  diphoPtr->mass() << " Gen Mass " <<  genMass << std::endl;
                        std::cout << " Checking invariant mass calculated from SC and nominal vertex " << massFromSC << std::endl;
                        std::cout << " gen eta 1 " <<  diphoPtr->leadingPhoton()->matchedGenPhoton()->eta() <<  " gen pt 1 " <<  diphoPtr->leadingPhoton()->matchedGenPhoton()->pt()
                                  << " pdg Id " << diphoPtr->leadingPhoton()->matchedGenPhoton()->pdgId() << " mother ID " <<  diphoPtr->leadingPhoton()->matchedGenPhoton()->motherRef()->pdgId()
                                  << std::endl;

                        std::cout << " gen eta 2 " <<  diphoPtr->subLeadingPhoton()->matchedGenPhoton()->eta() <<  " gen pt 2 " <<
                                  diphoPtr->subLeadingPhoton()->matchedGenPhoton()->pt()
                                  << " pdg Id " << diphoPtr->subLeadingPhoton()->matchedGenPhoton()->pdgId() << " mother ID " <<
                                  diphoPtr->subLeadingPhoton()->matchedGenPhoton()->motherRef()->pdgId() << std::endl;
                        cout << " eta 1 " <<  diphoPtr->leadingPhoton()->eta() << " eta 2 " << diphoPtr->subLeadingPhoton()->eta() << endl;
                        cout << " pt 1 " <<  diphoPtr->leadingPhoton()->pt() << " pt 2 " << diphoPtr->subLeadingPhoton()->pt() << endl;
                        std::cout << " ----------- " << std::endl;
                    }
                }





                /////////  fill histos for the denominator
                for( int iCat = 0; iCat < 4; iCat++ ) {
                    if( diphoton_category[iCat] ) {
                        h_pt_lead_tot_[iCat] -> Fill( pho1_pt ) ;
                        h_pt_sublead_tot_[iCat] -> Fill( pho2_pt ) ;
                        h_r9_lead_tot_[iCat] -> Fill( pho1_r9 ) ;
                        h_r9_sublead_tot_[iCat] -> Fill( pho2_r9 ) ;
                        h_eta_lead_tot_[iCat] -> Fill( pho1_eta ) ;
                        h_eta_sublead_tot_[iCat] -> Fill( pho2_eta ) ;
                        h_mass_tot_[iCat] -> Fill( mass ) ;
                        //
                        h_pt_tot_[iCat]  -> Fill( pho1_pt ) ;
                        h_pt_tot_[iCat]  -> Fill( pho2_pt ) ;
                        h_hoe_tot_[iCat]  -> Fill( pho1_hoe ) ;
                        h_hoe_tot_[iCat]  -> Fill( pho2_hoe ) ;
                        h_newhoe_tot_[iCat]  -> Fill( pho1_newhoe ) ;
                        h_newhoe_tot_[iCat]  -> Fill( pho2_newhoe ) ;
                        h_r9_tot_[iCat] -> Fill( pho1_r9 ) ;
                        h_r9_tot_[iCat] -> Fill( pho2_r9 ) ;
                        h_sieie_tot_[iCat] -> Fill( pho1_full5x5_sieie ) ;
                        h_sieie_tot_[iCat] -> Fill( pho2_full5x5_sieie ) ;
                        h_phoIso_tot_[iCat] -> Fill( pho1_pfPhoIso03 );
                        h_phoIso_tot_[iCat] -> Fill( pho2_pfPhoIso03 );
                        h_chIso_tot_[iCat] -> Fill( pho1_trkSumPtHollowConeDR03 );
                        h_chIso_tot_[iCat] -> Fill( pho2_trkSumPtHollowConeDR03 );

                    }
                }


                // pt cut
                bool pt_cut = false;
                pt_cut =  pho1_pt > 30  &&  pho2_pt > 20;

                // HoE cut
                bool hoe_cut = false;
                hoe_cut = ( pho1_hoe < 0.08 &&   pho2_hoe < 0.08 );

                // diPhoton mass cut
                bool mass_cut = mass > 95.;
                ////
                float phoIsoCutValue = 6;
                //        float chIsoCutValue=6;
                float trkIsoCutValue = 6;
                float sieie_cut_value_eb = 0.015;
                float sieie_cut_value_ee = 0.035;
                float low_r9_cutValue_eb = 0.50;
                float low_r9_cutValue_ee = 0.85;

                /// debug
                if( debug_ ) {
                    if( pho1_isEE && pho2_isEE ) {
                        cout << " Both photons in EE " << endl;
                    } else if( pho1_isEE &&  pho2_isEB ) {
                        cout << " Pho1 in EE " << endl;
                    } else if( pho2_isEE &&  pho1_isEB ) {
                        cout << " Pho2 in EE " << endl;
                    } else if( pho1_isEB && pho2_isEB ) {
                        cout << " Both photons in EB " << endl;
                    }
                    std::cout << " Pho1 r9 " << pho1_r9 << " " <<  diphoPtr->leadingPhoton()->r9() << " Pho2 r9 " << pho2_r9 << " " <<  diphoPtr->subLeadingPhoton()->r9() << endl;
                    std::cout << " Pho1 pt " << pho1_pt << " Pho2 pt " << pho2_pt << endl;
                    std::cout << " Pho1 h/e " << pho1_hoe << " Pho2 h/e " << pho2_hoe << endl;
                    std::cout << " Pho1 sieie " << pho1_full5x5_sieie << " " << diphoPtr->leadingPhoton()->sigmaIetaIeta() << " Pho2 sieie " << pho2_full5x5_sieie << " " <<
                              diphoPtr->subLeadingPhoton()->sigmaIetaIeta() << endl;
                    std::cout << " Pho1 phoIso " << pho1_pfPhoIso03 << " Pho2 phoIso " << pho2_pfPhoIso03 << endl;
                    std::cout << " Pho1 trkIso " << pho1_trkSumPtHollowConeDR03 << " Pho2 trkIso " << pho2_trkSumPtHollowConeDR03 << endl;
                    std::cout << " Diphoton mass " << mass  << endl;
                    cout << " diphoton_category[0] is " << diphoton_category[0] << endl;
                    cout << " diphoton_category[1] is " << diphoton_category[1] << endl;
                    cout << " diphoton_category[2] is " << diphoton_category[2] << endl;
                    cout << " diphoton_category[3] is " << diphoton_category[3] << endl;

                    if( pho1_full5x5_sieie >= 31 || pho2_full5x5_sieie >= 31 ) {
                        cout << " pho1 r9 " << diphoPtr->leadingPhoton()->r9() << " pho2 r9 " << diphoPtr->subLeadingPhoton()->r9() << endl;
                        cout << " pho1 chIso " << diphoPtr->leadingPhoton()->chargedHadronIso() << " pho2 chIso " << diphoPtr->subLeadingPhoton()->chargedHadronIso() << endl;
                        cout << " pho1 chIso/pt " << diphoPtr->leadingPhoton()->chargedHadronIso() / diphoPtr->leadingPhoton()->pt() << " pho2 chIso/pt " <<
                             diphoPtr->subLeadingPhoton()->chargedHadronIso() / diphoPtr->subLeadingPhoton()->pt() << endl;
                    }

                    //// end debug
                }

                ///////////////////////////////////////////////////////////////////////////// CIC
                CIC[0] =
                    pt_cut &&
                    pho1_r9 >  low_r9_cutValue_eb && pho2_r9 >  low_r9_cutValue_eb &&
                    hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    // No pho iso cut for high-r9   pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue &&
                    //            pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut ;
                if( debug_ )  { cout << " diphoton_category[0]&&CIC[0] is " << ( diphoton_category[0] && CIC[0] ) << endl; }


                CIC[1] =
                    pt_cut &&
                    hoe_cut &&

                    ( (
                          //   EB low R9 - EB high r9
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          //   EB low R9 - EB low r9
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;

                if( debug_ ) { std::cout << " diphoton_category[1]&&CIC[1] is " << ( diphoton_category[1] && CIC[1] ) << endl; }



                CIC[2] =
                    pt_cut &&
                    hoe_cut &&
                    /// ! EBEB high R9
                    ( ( pho1_isEB  && pho1_r9 > low_r9_cutValue_eb &&
                        pho2_isEE  && pho2_r9 > low_r9_cutValue_ee )
                      ||
                      ( pho1_isEE  && pho1_r9 > low_r9_cutValue_ee &&
                        pho2_isEB  && pho2_r9 > low_r9_cutValue_eb )
                      ||
                      ( pho1_isEE  && pho1_r9 > low_r9_cutValue_ee &&
                        pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&

                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ) &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    // pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;
                if( debug_ ) { std::cout << " diphoton_category[2]&&CIC[2] is " << ( diphoton_category[2] && CIC[2] ) << std::endl; }



                CIC[3] =
                    pt_cut &&
                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE high R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 >  r9_cut_value_ee )
                      //
                      ||
                      //
                      (
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho1_isEE &&
                          pho1_r9 >  r9_cut_value_ee )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;



                if( debug_ ) {
                    std::cout << " diphoton_category[3]&&CIC[3] is " << ( diphoton_category[3] && CIC[3] ) << std::endl;

                    cout << " 1 is " << ( pho1_isEB && pho1_r9 <= r9_cut_value_eb && pho1_r9 > low_r9_cutValue_eb && pho1_full5x5_sieie < sieie_cut_value_eb &&
                                          pho1_pfPhoIso03 < phoIsoCutValue && pho1_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;

                    cout << " 2 is " << ( pho1_isEE && pho1_r9 <= r9_cut_value_ee && pho1_r9 > low_r9_cutValue_ee && pho1_full5x5_sieie < sieie_cut_value_ee &&
                                          pho1_pfPhoIso03 < phoIsoCutValue && pho1_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;

                    cout << " 3 is " << ( pho2_isEB && pho2_r9 <= r9_cut_value_eb && pho2_r9 > low_r9_cutValue_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                                          pho2_pfPhoIso03 < phoIsoCutValue && pho2_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;

                    cout << " 4 is " << ( pho2_isEE && pho2_r9 <= r9_cut_value_ee && pho2_r9 > low_r9_cutValue_ee  && pho2_full5x5_sieie < sieie_cut_value_ee &&
                                          pho2_pfPhoIso03 < phoIsoCutValue && pho2_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;



                    cout << " 1' is " << ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho1_full5x5_sieie < sieie_cut_value_eb &&  pho1_pfPhoIso03 < phoIsoCutValue &&
                                           pho1_trkSumPtHollowConeDR03 < trkIsoCutValue && pho2_isEE && pho2_r9 > low_r9_cutValue_ee && pho2_full5x5_sieie < sieie_cut_value_ee &&
                                           pho2_pfPhoIso03 < phoIsoCutValue && pho2_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;

                    cout << " 2' is " << ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho1_full5x5_sieie < sieie_cut_value_ee &&  pho1_pfPhoIso03 < phoIsoCutValue &&
                                           pho1_trkSumPtHollowConeDR03 < trkIsoCutValue && pho2_isEB && pho2_r9 > low_r9_cutValue_eb && pho2_full5x5_sieie < sieie_cut_value_ee &&
                                           pho2_pfPhoIso03 < phoIsoCutValue && pho2_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;

                    cout << " 3' is " << ( pho2_isEE && pho2_r9 > low_r9_cutValue_ee && pho2_full5x5_sieie < sieie_cut_value_ee &&  pho2_pfPhoIso03 < phoIsoCutValue &&
                                           pho2_trkSumPtHollowConeDR03 < trkIsoCutValue && pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho1_full5x5_sieie < sieie_cut_value_ee &&
                                           pho1_pfPhoIso03 < phoIsoCutValue && pho1_trkSumPtHollowConeDR03 < trkIsoCutValue ) << endl;


                }



                //   Minus Pt
                CIC_minusPt[0] =
                    pho1_r9 > low_r9_cutValue_eb && pho2_r9 > low_r9_cutValue_eb &&
                    hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    // No pho iso  cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    // pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso  cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusPt[1] =

                    hoe_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;






                CIC_minusPt[2] =
                    ( ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEB  && pho2_r9 > low_r9_cutValue_eb ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&
                    hoe_cut &&
                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ) &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusPt[3] =

                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;





                //  Minus R9
                CIC_minusR9[0] =
                    pt_cut &&
                    hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusR9[1] =
                    pt_cut &&
                    hoe_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          //pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          //pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          //pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          //pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;










                CIC_minusR9[2] =
                    pt_cut &&
                    hoe_cut &&
                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee ) ) &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusR9[3] =
                    pt_cut &&
                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          //	     pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          // pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          //pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          // pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          //pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          // pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          //pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        // pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        // pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        //pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;


                //  Minus Hoe
                CIC_minusHoe[0] =
                    pt_cut &&
                    pho1_r9 > low_r9_cutValue_eb && pho2_r9 > low_r9_cutValue_eb &&
                    //     hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    // No pho iso  cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    // pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;



                CIC_minusHoe[1] =
                    pt_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;





                CIC_minusHoe[2] =
                    pt_cut &&
                    // No sieie cut for high-r9
                    ( ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEB  && pho2_r9 > low_r9_cutValue_eb ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&
                    //hoe_cut &&
                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee ) ) &&
                    // No pho iso cut for high-r9  pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    // pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;



                CIC_minusHoe[3] =
                    pt_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;





                //   Minus Sieie
                CIC_minusSieie[0] =
                    pt_cut &&
                    pho1_r9 > low_r9_cutValue_eb && pho2_r9 > low_r9_cutValue_eb &&
                    hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusSieie[1] =
                    pt_cut &&
                    hoe_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          //pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          // pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          //pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          //pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;


                CIC_minusSieie[2] =
                    pt_cut &&
                    ( ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEB  && pho2_r9 > low_r9_cutValue_eb ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&
                    hoe_cut &&
                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ) &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9  pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;



                CIC_minusSieie[3] =
                    pt_cut &&
                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          //pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          //pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          //pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          //pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          //pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          //pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          //pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        //pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        //pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        // pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;





                //   Minus phoIso
                CIC_minusPhoIso[0] =
                    pt_cut &&
                    pho1_r9 > low_r9_cutValue_eb && pho2_r9 > low_r9_cutValue_eb &&
                    hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    //pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusPhoIso[1] =
                    pt_cut &&
                    hoe_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          //pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          // pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          // pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          //pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;




                CIC_minusPhoIso[2] =
                    pt_cut &&
                    ( ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEB  && pho2_r9 > low_r9_cutValue_eb ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&
                    hoe_cut &&
                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ) &&
                    // No pho iso cut for high-r9  pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;



                CIC_minusPhoIso[3] =
                    pt_cut &&
                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          //pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          //pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          //pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          //pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          // pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          //pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          //pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        //pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        //pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        //pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;





                //   Minus chIso
                CIC_minusChIso[0] =
                    pt_cut &&
                    pho1_r9 > low_r9_cutValue_eb && pho2_r9 > low_r9_cutValue_eb &&
                    hoe_cut &&
                    // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;



                CIC_minusChIso[1] =
                    pt_cut &&
                    hoe_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          //pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          //pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          //pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue ) )  &&
                    //  pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) )     &&
                    mass_cut ;






                CIC_minusChIso[2] =
                    pt_cut &&
                    ( ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEB  && pho2_r9 > low_r9_cutValue_eb ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&
                    hoe_cut &&
                    // No sieie cut for high-r9
                    //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                    // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ) &&
                    // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                    //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&
                    // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                    mass_cut;


                CIC_minusChIso[3] =
                    pt_cut &&
                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          //pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue )
                      //pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          //pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue )
                      //pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          //pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue )
                      //pho2_trkSumPtHollowConeDR03 < trkIsoCutValue)
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue )
                      //pho2_trkSumPtHollowConeDR03 < trkIsoCutValue)
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue )
                      //pho1_trkSumPtHollowConeDR03 < trkIsoCutValue)
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        //pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        //pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) ) &&
                    mass_cut;




                //   Minus Mass
                CIC_minusMass[0] =
                    pt_cut &&
                    pho1_r9 > low_r9_cutValue_eb && pho2_r9 > low_r9_cutValue_eb &&
                    hoe_cut ;
                // No sieie cut for high-r9 pho1_full5x5_sieie < sieie_cut_value_eb && pho2_full5x5_sieie < sieie_cut_value_eb &&
                // No pho iso cut for high-r9 pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue;
                // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue;
                //mass_cut;


                CIC_minusMass[1] =
                    pt_cut &&
                    hoe_cut &&

                    ( (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          pho1_r9 > r9_cut_value_eb )
                      ||
                      (
                          pho1_r9 <= r9_cut_value_eb  &&
                          pho1_r9 >  low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue &&
                          //
                          pho2_r9  <= r9_cut_value_eb  &&
                          pho2_r9 >  low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue ) );


                CIC_minusMass[2] =
                    pt_cut &&
                    ( ( pho1_isEB && pho1_r9 > low_r9_cutValue_eb && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEB  && pho2_r9 > low_r9_cutValue_eb ) ||
                      ( pho1_isEE && pho1_r9 > low_r9_cutValue_ee && pho2_isEE  && pho2_r9 > low_r9_cutValue_ee ) ) &&
                    hoe_cut;
                // No sieie cut for high-r9
                //((pho1_isEB && pho1_full5x5_sieie < sieie_cut_value_eb && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ||
                // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEB  &&  pho2_full5x5_sieie < sieie_cut_value_eb ) ||
                // (pho1_isEE && pho1_full5x5_sieie < sieie_cut_value_ee && pho2_isEE  &&  pho2_full5x5_sieie < sieie_cut_value_ee) ) &&
                // No pho iso cut for high-r9  pho1_pfPhoIso03 < phoIsoCutValue  &&  pho2_pfPhoIso03 < phoIsoCutValue  &&
                //pho1_pfChgIsoWrtChosenVtx03 < chIsoCutValue &&  pho2_pfChgIsoWrtChosenVtx03 < chIsoCutValue;
                // No trk iso cut for high-r9 pho1_trkSumPtHollowConeDR03 <  trkIsoCutValue && pho2_trkSumPtHollowConeDR03 <  trkIsoCutValue;
                //mass_cut;


                CIC_minusMass[3] =
                    pt_cut &&
                    hoe_cut &&
                    ( (
                          //  EB lowR9 - EE loWR9
                          pho1_isEB &&
                          pho1_r9 <= r9_cut_value_eb &&
                          pho1_r9 > low_r9_cutValue_eb &&
                          pho1_full5x5_sieie < sieie_cut_value_eb &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEB &&
                          pho2_r9 <= r9_cut_value_eb &&
                          pho2_r9 > low_r9_cutValue_eb &&
                          pho2_full5x5_sieie < sieie_cut_value_eb &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EE low R9 - EE low R9
                      (
                          pho1_isEE &&
                          pho1_r9 <= r9_cut_value_ee &&
                          pho1_r9 > low_r9_cutValue_ee &&
                          pho1_full5x5_sieie < sieie_cut_value_ee &&
                          pho1_pfPhoIso03 < phoIsoCutValue &&
                          pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB high R9 - EE low R9
                      (
                          pho1_isEB &&
                          pho1_r9 >  r9_cut_value_eb &&
                          //
                          pho2_isEE &&
                          pho2_r9 <= r9_cut_value_ee &&
                          pho2_r9 > low_r9_cutValue_ee  &&
                          pho2_full5x5_sieie < sieie_cut_value_ee &&
                          pho2_pfPhoIso03 < phoIsoCutValue &&
                          pho2_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 >  r9_cut_value_eb &&
                        //
                        pho1_isEE &&
                        pho1_r9 <= r9_cut_value_ee &&
                        pho1_r9 > low_r9_cutValue_ee  &&
                        pho1_full5x5_sieie < sieie_cut_value_ee &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue )
                      ||
                      // EB low R9 - EE high R9
                      ( pho1_isEB &&
                        pho1_r9 <= r9_cut_value_eb &&
                        pho1_r9 > low_r9_cutValue_eb  &&
                        pho1_full5x5_sieie < sieie_cut_value_eb &&
                        pho1_pfPhoIso03 < phoIsoCutValue &&
                        pho1_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho2_isEE &&
                        pho2_r9 >  r9_cut_value_ee )
                      ||
                      ( pho2_isEB &&
                        pho2_r9 <= r9_cut_value_eb &&
                        pho2_r9 > low_r9_cutValue_eb  &&
                        pho2_full5x5_sieie < sieie_cut_value_eb &&
                        pho2_pfPhoIso03 < phoIsoCutValue &&
                        pho2_trkSumPtHollowConeDR03 < trkIsoCutValue &&
                        //
                        pho1_isEE &&
                        pho1_r9 >  r9_cut_value_ee ) );



                if( ( diphoton_category[0] && CIC[0] ) || ( diphoton_category[1] && CIC[1] ) || ( diphoton_category[2] && CIC[2] ) || ( diphoton_category[3] && CIC[3] ) ) {

                    nDiphoPassing_++;
                    h_nVtx_offl_ ->Fill( primaryVertices->size() );
                    if( hltPass( triggerBits ) )  {

                        h_nVtx_hlt_ ->Fill( primaryVertices->size() );
                    }
                }


                if( hltPass( triggerBits ) )  {
                    nDiphoAfterHlt_++;

                    if( ( diphoton_category[0] && CIC[0] ) || ( diphoton_category[1] && CIC[1] ) || ( diphoton_category[2] && CIC[2] ) || ( diphoton_category[3] && CIC[3] ) ) {
                        nDiphoAfterHltAndPresel_++;

                    }
                }




                ///// debug r9
                if( pt_cut &&  pho1_isEB && pho2_isEB ) {
                    h_full5x5r9_lead_tot_eb_ -> Fill( pho1_full5x5r9 ) ;
                    h_full5x5r9_lead_tot_eb_ -> Fill( pho2_full5x5r9 ) ;
                    h_r9_lead_tot_eb_ -> Fill( pho1_r9 ) ;
                    h_r9_lead_tot_eb_ -> Fill( pho2_r9 ) ;
                }

                if( pt_cut &&  pho1_isEE && pho2_isEE ) {
                    h_full5x5r9_lead_tot_ee_ -> Fill( pho1_full5x5r9 ) ;
                    h_full5x5r9_lead_tot_ee_ -> Fill( pho2_full5x5r9 ) ;
                    h_r9_lead_tot_ee_ -> Fill( pho1_r9 ) ;
                    h_r9_lead_tot_ee_ -> Fill( pho2_r9 ) ;
                }





                for( int iCat = 0; iCat < 4; iCat++ ) {
                    if( diphoton_category[iCat] && CIC [iCat] ) {
                        //nDiphoPassing_++;
                        h_pt_lead_offl_[iCat] -> Fill( pho1_pt ) ;
                        h_pt_sublead_offl_[iCat] -> Fill( pho2_pt ) ;
                        h_eta_lead_offl_[iCat] -> Fill( pho1_eta ) ;
                        h_eta_sublead_offl_[iCat] -> Fill( pho2_eta ) ;
                        h_mass_offl_[iCat] -> Fill( mass ) ;

                        if( hltPass( triggerBits ) ) {
                            h_pt_lead_hlt_[iCat] -> Fill( pho1_pt ) ;
                            h_pt_sublead_hlt_[iCat] -> Fill( pho2_pt ) ;
                            h_eta_lead_hlt_[iCat] -> Fill( pho1_eta ) ;
                            h_eta_sublead_hlt_[iCat] -> Fill( pho2_eta ) ;
                            h_mass_hlt_[iCat] -> Fill( mass ) ;



                            ////////////// temporary
                            if( pho1_isEB ) {
                                //h_r9_lead_tot_eb_ -> Fill ( pho1_r9 ) ;

                                h_phoIso_lead_tot_eb_ -> Fill( pho1_pfPhoIso03 ) ;
                                h_chIso_lead_tot_eb_ -> Fill( pho1_pfChgIsoWrtChosenVtx03 ) ;
                            } else {
                                //h_r9_lead_tot_ee_ -> Fill ( pho1_r9 ) ;
                                h_phoIso_lead_tot_ee_ -> Fill( pho1_pfPhoIso03 ) ;
                                h_chIso_lead_tot_ee_ -> Fill( pho1_pfChgIsoWrtChosenVtx03 ) ;
                            }

                            if( pho2_isEB ) {
                                // h_r9_sublead_tot_eb_ -> Fill ( pho2_r9 ) ;
                                h_phoIso_sublead_tot_eb_ -> Fill( pho2_pfPhoIso03 ) ;
                                h_chIso_sublead_tot_eb_ -> Fill( pho2_pfChgIsoWrtChosenVtx03 ) ;

                            } else {
                                //                          h_r9_sublead_tot_ee_ -> Fill ( pho2_r9 ) ;
                                h_phoIso_sublead_tot_ee_ -> Fill( pho2_pfPhoIso03 ) ;
                                h_chIso_sublead_tot_ee_ -> Fill( pho2_pfChgIsoWrtChosenVtx03 ) ;

                            }
                        }
                    }
                }


                /////////   N-1 plots
                for( int iCat = 0; iCat < 4; iCat++ ) {
                    if( diphoton_category[iCat] ) {

                        if( CIC_minusPt[iCat] ) {
                            h_nMin1_pt_offl_[iCat]->Fill( pho1_pt ) ;
                            h_nMin1_pt_offl_[iCat]->Fill( pho2_pt ) ;
                            if( hltPass( triggerBits ) )  {
                                h_nMin1_pt_hlt_[iCat]->Fill( pho1_pt ) ;
                                h_nMin1_pt_hlt_[iCat]->Fill( pho2_pt ) ;
                            }
                        }



                        if( CIC_minusHoe[iCat] ) {
                            h_nMin1_hoe_offl_[iCat]->Fill( pho1_hoe ) ;
                            h_nMin1_hoe_offl_[iCat]->Fill( pho2_hoe ) ;
                            if( hltPass( triggerBits ) )  {
                                h_nMin1_hoe_hlt_[iCat]->Fill( pho1_hoe ) ;
                                h_nMin1_hoe_hlt_[iCat]->Fill( pho2_hoe ) ;
                            }
                        }



                        if( CIC_minusR9[iCat] ) {
                            h_nMin1_r9_offl_[iCat]->Fill( pho1_r9 ) ;
                            h_nMin1_r9_offl_[iCat]->Fill( pho2_r9 ) ;
                            if( hltPass( triggerBits ) )  {
                                h_nMin1_r9_hlt_[iCat]->Fill( pho1_r9 ) ;
                                h_nMin1_r9_hlt_[iCat]->Fill( pho2_r9 ) ;
                            }
                        }
                        /////////////// special N-1 plots for R9
                        float r9_low = -1, r9_high = -1;
                        bool lowIsEB = false;
                        if( CIC_minusR9[iCat] ) {

                            if( pho1_r9 < pho2_r9 ) {
                                r9_low = pho1_r9;
                                r9_high = pho2_r9;
                                if( pho1_isEB ) { lowIsEB = true; }
                            } else {
                                r9_low = pho2_r9;
                                r9_high = pho1_r9;
                                if( pho2_isEB ) { lowIsEB = true; }
                            }
                            h2_nMin1_r9_offl_[iCat]->Fill( r9_low, r9_high ) ;
                            //

                            ///////////  min R9
                            if( iCat == 0 || iCat == 2 )
                            { h_nMin1_r9_low_offl_[iCat]->Fill( r9_low ) ; }

                            if( iCat == 1 &&  r9_high > 0.5 )
                            { h_nMin1_r9_low_offl_[iCat]->Fill( r9_low ) ; }

                            if( iCat == 3 ) {
                                if( lowIsEB ) {
                                    if( r9_high > 0.5 ) { h_nMin1_r9_low_offl_[iCat]->Fill( r9_low ) ; }
                                } else {
                                    if( r9_high > 0.8 ) { h_nMin1_r9_low_offl_[iCat]->Fill( r9_low ) ; }
                                }

                            }
                            ////////////// Max r9
                            if( iCat == 0 || iCat == 2 )
                            { h_nMin1_r9_high_offl_[iCat]->Fill( r9_high ) ; }

                            if( iCat == 1 &&  r9_low > 0.5 )
                            { h_nMin1_r9_high_offl_[iCat]->Fill( r9_high ) ; }

                            if( iCat == 3 ) {
                                if( lowIsEB ) {
                                    if( r9_low > 0.5 ) { h_nMin1_r9_high_offl_[iCat]->Fill( r9_high ) ; }
                                } else {
                                    if( r9_low > 0.8 ) { h_nMin1_r9_high_offl_[iCat]->Fill( r9_high ) ; }
                                }

                            }

                            if( hltPass( triggerBits ) )  {

                                //////// min R9
                                if( iCat == 0 || iCat == 2 )
                                { h_nMin1_r9_low_hlt_[iCat]->Fill( r9_low ) ; }


                                if( iCat == 1 &&  r9_high > 0.5 )
                                { h_nMin1_r9_low_hlt_[iCat]->Fill( r9_low ) ; }

                                if( iCat == 3 ) {
                                    if( lowIsEB ) {
                                        if( r9_high > 0.5 ) { h_nMin1_r9_low_hlt_[iCat]->Fill( r9_low ) ; }
                                    } else {
                                        if( r9_high > 0.8 ) { h_nMin1_r9_low_hlt_[iCat]->Fill( r9_low ) ; }
                                    }

                                }



                                ////////////////// max R9
                                if( iCat == 0 || iCat == 2 )
                                { h_nMin1_r9_high_hlt_[iCat]->Fill( r9_high ) ; }


                                if( iCat == 1 &&  r9_low > 0.5 )
                                { h_nMin1_r9_high_hlt_[iCat]->Fill( r9_high ) ; }

                                if( iCat == 3 ) {
                                    if( lowIsEB ) {
                                        if( r9_low > 0.5 ) { h_nMin1_r9_high_hlt_[iCat]->Fill( r9_high ) ; }
                                    } else {
                                        if( r9_low > 0.8 ) { h_nMin1_r9_high_hlt_[iCat]->Fill( r9_high ) ; }
                                    }
                                }
                            }
                        }




                        //////////////

                        if( CIC_minusSieie[iCat] ) {
                            h_nMin1_sieie_offl_[iCat]->Fill( pho1_full5x5_sieie ) ;
                            h_nMin1_sieie_offl_[iCat]->Fill( pho2_full5x5_sieie ) ;
                            if( hltPass( triggerBits ) )  {
                                h_nMin1_sieie_hlt_[iCat]->Fill( pho1_full5x5_sieie ) ;
                                h_nMin1_sieie_hlt_[iCat]->Fill( pho2_full5x5_sieie ) ;


                            }
                        }


                        if( CIC_minusPhoIso[iCat] ) {
                            h_nMin1_phoIso_offl_[iCat]->Fill( pho1_pfPhoIso03 ) ;
                            h_nMin1_phoIso_offl_[iCat]->Fill( pho2_pfPhoIso03 ) ;
                            if( hltPass( triggerBits ) )  {
                                h_nMin1_phoIso_hlt_[iCat]->Fill( pho1_pfPhoIso03 ) ;
                                h_nMin1_phoIso_hlt_[iCat]->Fill( pho2_pfPhoIso03 ) ;


                            }
                        }


                        if( CIC_minusChIso[iCat] ) {
                            //h_nMin1_chIso_offl_[iCat]->Fill ( pho1_pfChgIsoWrtChosenVtx03 ) ;
                            // h_nMin1_chIso_offl_[iCat]->Fill ( pho2_pfChgIsoWrtChosenVtx03 ) ;
                            h_nMin1_chIso_offl_[iCat]->Fill( pho1_trkSumPtHollowConeDR03 ) ;
                            h_nMin1_chIso_offl_[iCat]->Fill( pho2_trkSumPtHollowConeDR03 ) ;
                            if( hltPass( triggerBits ) )  {
                                //h_nMin1_chIso_hlt_[iCat]->Fill ( pho1_pfChgIsoWrtChosenVtx03) ;
                                //h_nMin1_chIso_hlt_[iCat]->Fill ( pho2_pfChgIsoWrtChosenVtx03) ;
                                h_nMin1_chIso_hlt_[iCat]->Fill( pho1_trkSumPtHollowConeDR03 ) ;
                                h_nMin1_chIso_hlt_[iCat]->Fill( pho2_trkSumPtHollowConeDR03 ) ;


                            }
                        }



                        if( CIC_minusMass[iCat] ) {

                            if( hltPass( triggerBits ) &&  massHLT > 0 )  {
                                h2_lowMass_mass_hlt_ -> Fill( mass, massHLT );
                                h2_lowMass_massFromSC_hlt_ -> Fill( massFromSC, massHLT );
                            }


                            h2_lowMass_mass_offl_ -> Fill( mass, genMass );
                            h2_lowMass_massSCvsPho_offl_ -> Fill( mass, massFromSC );


                            if( mass < 95 ) {
                                nLowMassPairAfterPresel_++;
                                h2_lowMass_eta_offl_ -> Fill( pho1_eta, diphoPtr->leadingPhoton()->matchedGenPhoton()->eta() );
                                h2_lowMass_eta_offl_ -> Fill( pho2_eta, diphoPtr->subLeadingPhoton()->matchedGenPhoton()->eta() );
                                h2_lowMass_pt_offl_ -> Fill( pho1_pt, diphoPtr->leadingPhoton()->matchedGenPhoton()->pt() );
                                h2_lowMass_pt_offl_ -> Fill( pho2_pt, diphoPtr->subLeadingPhoton()->matchedGenPhoton()->pt() );
                                if( debug_ ) { cout << " Mass passing presel " << mass << endl; }

                            }



                            h_nMin1_mass_offl_[iCat]->Fill( mass ) ;
                            if( debug_ ) { std::cout << " Offl Minus mass " << mass << " gen mass " << genMass << std::endl; }
                            if( hltPass( triggerBits ) )  {
                                if( mass < 95 ) { nLowMassPairAfterPreselAndHLT_++; }
                                if( debug_ ) { std::cout << " HLT Minus mass " << mass << " gen mass " << genMass << std::endl; }
                                h_nMin1_mass_hlt_[iCat]->Fill( mass ) ;
                            }

                        }





                    }
                } // N-1 selection

                /////////
            }   //end loop over reco diphotons
        }
    }



    // ********************************************************************************

}

void
DiphotonPreselectionValidation::beginJob()
{

}

void
DiphotonPreselectionValidation::endJob()
{
    cout << " Number of events being processed " << nEvents_ << endl;
    cout << " Number of events with two gen photons " << nEventsWithTwoGenPhotons_ << endl;
    cout << " Number of events with two Reco photons " << nEventsWithTwoRecoPhotons_ << endl;
    cout << "                    " << endl;
    cout << " number of gen diphotons from Higgs in the eta fiducial volume " << nGenPhotons_ << " events " << nGenPhotons_ << endl;
    cout << " number of reco diphotons matching the gen photons " <<  nDiphoMatched_ << endl;
    cout << " number of reco diphotons passing the miniAOD cuts " << nSinglePhoPassingAODSel_ << " events " << nSinglePhoPassingAODSel_ <<  endl;
    cout << " Efficiency of those cuts "  << float( nSinglePhoPassingAODSel_ ) / nGenPhotons_ << endl;
    cout << " DiPho in fiducial eta " <<  nDiphoPassingEtaCut_ << endl;
    cout << " Number of events with both photons with Pt 20 " << nSinglePhoPassingAODSelPlusPt20_ << " eff " << float(
             nSinglePhoPassingAODSelPlusPt20_ ) / nGenPhotons_ << endl;
    cout << "                    " << endl;


    cout << " DiPho passing presel " << nDiphoPassing_ << endl;
    cout << " Low mass pairs " <<  nLowMassPair_ << endl;
    cout << " Low mass pairs passing preselection " <<  nLowMassPairAfterPresel_ << endl;
    cout << " Low mass pairs passing preselection and HLT " <<  nLowMassPairAfterPreselAndHLT_ << endl;
    cout << " DiPho after HLT " << nDiphoAfterHlt_ << endl;
    cout << " DiPho after HLT and Preselection " << nDiphoAfterHltAndPresel_ << endl;
    cout << " missing from categories " << nMissing_ << endl;


} // end of endJob




typedef DiphotonPreselectionValidation FlashggDiphotonPreselectionValidation;
DEFINE_FWK_MODULE( DiphotonPreselectionValidation );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

