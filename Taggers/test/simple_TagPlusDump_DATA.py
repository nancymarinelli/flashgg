import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("FLASHggTagAndDump")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'POSTLS170_V5::All'
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 100 )

# Uncomment the following if you notice you have a memory leak
# This is a lightweight tool to digg further
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                        ignoreTotal = cms.untracked.int32(1),
#                                        monitorPssAndPrivate = cms.untracked.bool(True)
#                                       )

process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(

"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_1.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_2.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_3.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_4.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_5.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_6.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_7.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_8.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_9.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_10.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_11.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_12.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_13.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_14.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_15.root"

))

process.load("flashgg/Taggers/flashggTagSequence_cfi")
process.load("flashgg/Taggers/flashggTagTester_cfi")

# For debugging
switchToPreselected = True
switchToFinal = False
switchToPuppi = False
assert(not switchToPreselected or not switchToFinal)

if switchToPreselected:
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggDiPhotons"),cms.InputTag("flashggPreselectedDiPhotons"))

if switchToFinal:
    from flashgg.MicroAOD.flashggFinalEGamma_cfi import flashggFinalEGamma
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggDiPhotons"),cms.InputTag("flashggFinalEGamma",flashggFinalEGamma.DiPhotonCollectionName.value()))

if switchToPuppi:
    process.flashggUnpackedJets.JetsTag = cms.InputTag("flashggFinalPuppiJets")

from flashgg.Taggers.flashggTagOutputCommands_cff import tagDefaultOutputCommand

#process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('/tmp/nancy/vhEtTagOutputFile_Data.root'),
#                               outputCommands = tagDefaultOutputCommand			       
#                               )



process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("test.root"))

from flashgg.Taggers.tagsDumpers_cfi import createTagDumper
import flashgg.Taggers.dumperConfigTools as cfgTools
process.vhEtTagDumper = createTagDumper("VHEtTag")
process.vhEtTagDumper.dumpTrees =  True
process.vhEtTagDumper.dumpHistos = True



dipho_variables=["dipho_sumpt      := diPhoton.sumPt",
                 "dipho_cosphi     := abs(cos(diPhoton.leadingPhoton.phi - diPhoton.subLeadingPhoton.phi))",
                 "mass             := diPhoton.mass",
                 "leadPt           := diPhoton.leadingPhoton.pt",
                 "leadEt           := diPhoton.leadingPhoton.et",
                 "leadEta          := diPhoton.leadingPhoton.eta",
                 "leadPhi          := diPhoton.leadingPhoton.phi",
                 "lead_sieie       := diPhoton.leadingPhoton.sigmaIetaIeta",
                 "lead_hoe         := diPhoton.leadingPhoton.hadronicOverEm",
                 "lead_sigmaEoE    := diPhoton.leadingPhoton.sigEOverE",
                 "lead_ptoM        := diPhoton.leadingPhoton.pt/diPhoton.mass",
                 "leadR9           := diPhoton.leadingPhoton.r9",
                 "subleadPt        := diPhoton.subLeadingPhoton.pt",
                 "subleadEt        := diPhoton.subLeadingPhoton.et",
                 "subleadEta       := diPhoton.subLeadingPhoton.eta",
                 "subleadPhi       := diPhoton.subLeadingPhoton.phi",
                 "sublead_sieie    := diPhoton.subLeadingPhoton.sigmaIetaIeta",
                 "sublead_hoe      := diPhoton.subLeadingPhoton.hadronicOverEm",
                 "sublead_sigmaEoE := diPhoton.subLeadingPhoton.sigEOverE",
                 "sublead_ptoM     := diPhoton.subLeadingPhoton.pt/diPhoton.mass",
                 "subleadR9        := diPhoton.subLeadingPhoton.r9",
                 "leadIDMVA        := diPhoton.leadingView.phoIdMvaWrtChosenVtx",
                 "subleadIDMVA     := diPhoton.subLeadingView.phoIdMvaWrtChosenVtx",]

cfgTools.addCategories(process.vhEtTagDumper,
                       ## categories definition                                                                                                                                                                                  
                       [("all","1",0)
                    ],
                       ## variables to be dumped in trees/datasets. Same variables for all categories                                                                                                                            
                       variables=dipho_variables+
                       ["pfMET_rawPt        := met.uncorPt",
                        "pfMET_rawPhi       := met.uncorPhi",
                        "pfMET_rawSumEt     := met.uncorSumEt",
                        "pfMET_corPt        := met.corPt",
                        "pfMET_corPhi       := met.corPhi",
                        "pfMET_corSumEt     := met.corSumEt",
                        "caloMET_rawPt      := met.caloMETPt",
                        "caloMET_rawPhi     := met.caloMETPhi",
                        "caloMET_rawSumEt   := met.caloMETSumEt",
#                        "genMET_pt          := met.genMET.pt",
#                        "genMET_phi         := met.genMET.phi",
#                        "genMET_sumEt       := met.genMET.sumEt",
                        "pfNeutralEMFraction := met.NeutralEMFraction",
                        "pfNeutralHadEtFraction := met.NeutralHadEtFraction",
                        "pfChargedEMEtFraction := met.ChargedEMEtFraction",
                        "pfChargedHadEtFraction := met.ChargedHadEtFraction"
                        ],
                       histograms=["mass>>mass(160,100,180)",
                                   "subleadPt:leadPt>>ptLeadvsSub(180,20,200:180,20,200)",
                                   "leadIDMVA>>leadIDMVA(50,0,1)",
                                   "subleadIDMVA>>subleadIDMVA(50,0,1)",
                                   "pfMET_rawPt>>pfMET_rawPt(250,0,500)",
                                   "pfMET_corPt>>pfMET_corPt(250,0,500)",
                                   "pfMET_rawSumEt>>pfMET_rawSumEt(400,200,2000)",
                                   "pfMET_corSumEt>>pfMET_corSumEt(400,200,2000)",
                                   "caloMET_rawPt>>caloMET_rawPt(250,0,500)",
                                   "caloMET_rawSumEt>>caloMET_rawSumEt(400,200,2000)",
                                   "pfMET_rawPhi>>pfMET_rawPhi(100,-3.14,3.14)",
                                   "pfMET_corPhi>>pfMET_corPhi(100,-3.14,3.14)",
                                   "caloMET_rawPhi>>caloMET_rawPhi(100,-3.14,3.14)"
#                                   "genMET_pt>>genMET_pt(250,0,500)",
#                                   "genMET_phi>>genMET_phi(100,-3.14,3.14)",
#                                   "genMET_sumEt>>genMET_sumEt(400,200,2000)"
                                  ]
                       )




process.p = cms.Path(process.flashggTagSequence*process.flashggTagTester*process.vhEtTagDumper)

#process.e = cms.EndPath(process.out)

# import flashgg customization
from flashgg.MetaData.JobConfig import customize
# set default options if needed
customize.setDefault("maxEvents",100)
customize.setDefault("targetLumi",10e+3)
# call the customization
customize(process)
