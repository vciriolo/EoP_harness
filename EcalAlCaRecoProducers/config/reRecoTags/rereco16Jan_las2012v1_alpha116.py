import FWCore.ParameterSet.Config as cms

from CondCore.DBCommon.CondDBSetup_cfi import *

RerecoGlobalTag = cms.ESSource("PoolDBESSource",
                               CondDBSetup,
                               connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'),
                               #     globaltag = cms.string('UNSPECIFIED::All'),
                               globaltag = cms.string('GR_R_42_V24::All'),
                               #toGet = cms.VPSet( ),   # hook to override or add single payloads
                               toGet = cms.VPSet(
    cms.PSet(record = cms.string("EcalLaserAPDPNRatiosRcd"),
             tag = cms.string("EcalLaserAPDPNRatios_data_20120131_158851_183320"),
             connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_ECAL")
             ),
    cms.PSet(record = cms.string('EcalLaserAlphasRcd'),
             tag = cms.string('EcalLaserAlphas_EB_sic1_btcp152_EE_sic1_btcp116'),
             connect = cms.untracked.string('frontier://FrontierInt/CMS_COND_ECAL')
             )
    ),
                               BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService')
                               )
