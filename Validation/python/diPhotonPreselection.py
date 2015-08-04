import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("preselTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'POSTLS170_V5::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 200 )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/n/nancy/private/HiggsRunII/CMSSW_7_4_0/src/flashgg/MicroAOD/test/microAOD_DiPhotonPreselection.root")
                            )

process.preselTest = cms.EDAnalyzer("DiphotonPreselectionValidation",
                                    outputFileName  = cms.string("output.root"),
                                    filterName      = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95"),
                                    lastfilterName      = cms.vstring("hltEG18R9Id85b90eHE10R9Id50b80eR9UnseededLastFilter","hltEG18Iso60CaloId15b35eHE10R9Id50b80eTrackIsoUnseededLastFilter"),
                                    objects         = cms.InputTag("selectedPatTrigger"),
                                    bits            = cms.InputTag("TriggerResults::HLT"),
                                    diPhotons  = cms.untracked.InputTag('flashggDiPhotons'),
                                    genPhotonTag = cms.InputTag("flashggGenPhotonsExtra"),
                                    rhoFixedGridCollection = cms.InputTag('fixedGridRhoAll'),
                                    rhoCorrection =  cms.bool(True),
                                    getHLTcandidates = cms.bool(True)       
                                 )


process.p = cms.Path(process.preselTest)

