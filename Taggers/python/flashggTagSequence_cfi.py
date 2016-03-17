import FWCore.ParameterSet.Config as cms
from flashgg.Taggers.flashggDiPhotonMVA_cfi import flashggDiPhotonMVA
from flashgg.Taggers.flashggVBFMVA_cff import flashggVBFMVA,flashggVBFDiPhoDiJetMVA
from flashgg.Taggers.flashggTags_cff import *
from flashgg.Taggers.flashggPreselectedDiPhotons_cfi import flashggPreselectedDiPhotons
from flashgg.Taggers.flashggTagSorter_cfi import flashggTagSorter
from flashgg.Taggers.flashggUpdatedIdMVADiPhotons_cfi import flashggUpdatedIdMVADiPhotons

flashggTagSequence = cms.Sequence(flashggUpdatedIdMVADiPhotons
                                  * flashggPreselectedDiPhotons
				  * flashggDiPhotonMVA
                                  * flashggUnpackedJets
                                  * flashggVBFMVA
                                  * flashggVBFDiPhoDiJetMVA
                                  * ( flashggUntagged
                                      + flashggVBFTag
#                                     + flashggTTHLeptonicTag
                                     + flashggVHEtTag
#                                     + flashggTTHHadronicTag
#                                     + flashggVHLooseTag
#                                     + flashggVHTightTag
                                     + flashggVHHadronicTag
					)
                                 * flashggTagSorter
                                  )

