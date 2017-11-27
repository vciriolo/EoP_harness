#!   /usr/bin/env   python
import   os
import   glob
import   math
from   array   import   array
import   sys
import   time
import   subprocess

from   optparse   import   OptionParser

parser   =   OptionParser()

parser.add_option('--generateOnly',                  action='store_true',   dest='generateOnly',                  default=False,   help='generate   jobs   only,   without   submitting   them')

(options,   args)   =   parser.parse_args()

#ntupleName   =   "data-DoubleEG-Run2016BCD_ZSkim_12p9fb_multifit"
#ntupleName   =   "92X_dataRun2_Prompt_v9_SingleEle_harness_"
ntupleName   =   "Cal_Oct2017_cand_v5_runF"
#ntupleName   =   "Run2016BCDEFGH_WZSkim_Cal_Jan2017_ped_v1_multifit"
#ntupleName   =   "data-SingleElectron-Run2016BCD_WSkim_12p9fb_weights"
#options:   "data-Run2015D-25ns-multifit",   "data-Run2015D-25ns-multifit"   or   "data-Run2015D-25ns-stream".
folder   =   "/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/lbrianza/ntupleEoP/"
categories   =   ["EB"]#,"EB_0_1","EB_1_1479"]#,"EE","EE_1479_2","EE_2_25","EEp","EEp_1479_2","EEp_2_25","EEm","EEm_1479_2","EEm_2_25","EEp_2_225","EEp_225_25","EEm_2_225","EEm_225_25"]
#yMIN   =   ["0.85"]#,"0.85","0.85"]#,"0.65","0.65","0.40","0.65","0.65","0.40","0.65","0.65","0.40","0.40","0.40","0.40","0.40"]
yMIN   =   ["0.97"]
yMAX   =   ["1.02"]
#events   =   ["10000"]#,"10000","10000"]#,"10000","10000","10000","10000","10000","10000","10000","10000","10000","10000","10000","10000","10000"]
events = ["5000"]
#yMIN   =   ["0.95","0.95","0.95","0.95","0.95","0.95","0.95","0.95","0.95","0.95","0.95","0.95"]
#categories   =   ["EEp","EEp_1479_2","EEp_2_25","EEm","EEm_1479_2","EEm_2_25"]
#yMIN   =   ["0.65","0.65","0.40","0.65","0.65","0.40"]

'''
ntuplelist   =   [
"SingleElectron-Run2016B-WSkim-Prompt_v2-273150-275376",
"SingleElectron-Run2016C-WSkim-Prompt_v2-275420-276283",
"SingleElectron-Run2016D-WSkim-Prompt_v2-276315-276811",
"SingleElectron-Run2016E-WSkim-Prompt-v2-276830-277420",
"SingleElectron-Run2016F-WSkim-Prompt-v1-277820-278808",
"SingleElectron-Run2016G-WSkim-Prompt-v1-278817-280385",
"SingleElectron-Run2016H-WSkim-Prompt-v2-281207-284035",
"SingleElectron-Run2016H-WSkim-Prompt-v3-284036-284068"
]
'''
'''
folderlist=[
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016B-WSkim-Prompt_v2/273150-275376/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016C-WSkim-Prompt_v2/275420-276283/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016D-WSkim-Prompt_v2/276315-276811/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016E-WSkim-Prompt-v2/276830-277420/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016F-WSkim-Prompt-v1/277820-278808/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016G-WSkim-Prompt-v1/278817-280385/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016H-WSkim-Prompt-v2/281207-284035/271036_284044-23Sep2016/newNtuples/",
"/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Jan2017_ref/SingleElectron-Run2016H-WSkim-Prompt-v3/284036-284068/271036_284044-23Sep2016/newNtuples/"
]
'''
'''
folderlist = [
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Sep2017_ref/SingleElectron-Run2017B-WSkim-Prompt-v1/297046-297723/294927-302654_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Sep2017_ref/SingleElectron-Run2017B-WSkim-Prompt-v2/298678-299329/294927-302654_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Sep2017_ref/SingleElectron-Run2017C-WSkim-Prompt-v1/299368-299649/294927-302654_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Sep2017_ref/SingleElectron-Run2017C-WSkim-Prompt-v2/299929-300676/294927-302654_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Sep2017_ref/SingleElectron-Run2017C-WSkim-Prompt-v3/300742-302029/294927-302654_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Sep2017_ref/SingleElectron-Run2017D-WSkim-Prompt-v1/302030-302663/294927-302654_Prompt_v1/newNtuples/"
]
'''
'''
ntuplelist = [
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/92X_dataRun2_Prompt_v9/SingleElectron-Run2017B-WSkim-Prompt-v1/297046-297723/294927-302654_Prompt_v1/newNtuples/SingleElectron-Run2017B-WSkim-Prompt-v1-297046-297723.root",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/92X_dataRun2_Prompt_v9/SingleElectron-Run2017B-WSkim-Prompt-v2/298678-299329/294927-302654_Prompt_v1/newNtuples/SingleElectron-Run2017B-WSkim-Prompt-v2-298678-299329.root",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/92X_dataRun2_Prompt_v9/SingleElectron-Run2017C-WSkim-Prompt-v1/299368-299649/294927-302654_Prompt_v1/newNtuples/SingleElectron-Run2017C-WSkim-Prompt-v1-299368-299649.root",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/92X_dataRun2_Prompt_v9/SingleElectron-Run2017C-WSkim-Prompt-v2/299929-300676/294927-302654_Prompt_v1/newNtuples/splitNtuples4/SingleElectron-Run2017C-WSkim-Prompt-v2-299929-300676.root",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/92X_dataRun2_Prompt_v9/SingleElectron-Run2017C-WSkim-Prompt-v3/300742-302029/294927-302654_Prompt_v1/newNtuples/SingleElectron-Run2017C-WSkim-Prompt-v3-300742-302029.root",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/92X_dataRun2_Prompt_v9/SingleElectron-Run2017D-WSkim-Prompt-v1/302030-302663/294927-302654_Prompt_v1/newNtuples/SingleElectron-Run2017D-WSkim-Prompt-v1-302030-302663.root"
]
'''
'''
ntuplelist = [
"SingleElectron-Run2017B-WSkim-Prompt-v1-297046-297723.root",
"SingleElectron-Run2017B-WSkim-Prompt-v2-298678-299329.root",
"SingleElectron-Run2017C-WSkim-Prompt-v1-299368-299649.root",
"SingleElectron-Run2017C-WSkim-Prompt-v2-299929-300676.root",
"SingleElectron-Run2017C-WSkim-Prompt-v3-300742-302029.root",
"SingleElectron-Run2017D-WSkim-Prompt-v1-302030-302663.root"
]
'''
'''
ntuplelist = [
"SingleElectron-Run2017B-WSkim-Prompt-v1-297046-297723.root",
"SingleElectron-Run2017B-WSkim-Prompt-v2-298678-299329.root",
"SingleElectron-Run2017C-WSkim-Prompt-v1-299368-299649.root",
"SingleElectron-Run2017C-WSkim-Prompt-v3-300742-302029.root",
"SingleElectron-Run2017D-WSkim-Prompt-v1-302030-302663.root",
"SingleElectron-Run2017E-WSkim-Prompt-v1-303574-304797.root",
"DoubleEG-Run2017B-ZSkim-Prompt-v1-297046-297723.root", 
"DoubleEG-Run2017B-ZSkim-Prompt-v2-298678-299329.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v1-299368-299649.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v2-299929-300676.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v3-300742-302029.root", 
"DoubleEG-Run2017D-ZSkim-Prompt-v1-302030-302663.root", 
"DoubleEG-Run2017E-ZSkim-Prompt-v1-303574-304797.root"
]

folderlist=[
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/SingleElectron-Run2017B-WSkim-Prompt-v1/297046-297723/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/SingleElectron-Run2017B-WSkim-Prompt-v2/298678-299329/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/SingleElectron-Run2017C-WSkim-Prompt-v1/299368-299649/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/SingleElectron-Run2017C-WSkim-Prompt-v3/300742-302029/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/SingleElectron-Run2017D-WSkim-Prompt-v1/302030-302663/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/SingleElectron-Run2017E-WSkim-Prompt-v1/303574-304797/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017B-ZSkim-Prompt-v1/297046-297723/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017B-ZSkim-Prompt-v2/298678-299329/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017C-ZSkim-Prompt-v1/299368-299649/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017C-ZSkim-Prompt-v2/299929-300676/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017C-ZSkim-Prompt-v3/300742-302029/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017D-ZSkim-Prompt-v1/302030-302663/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_Ped_v2/DoubleEG-Run2017E-ZSkim-Prompt-v1/303574-304797/294927-304120_Prompt_v1/newNtuples/"
]
'''
'''
ntuplelist = [
"SingleElectron-Run2017B-WSkim-Prompt-v1-297046-297723.root",
"SingleElectron-Run2017B-WSkim-Prompt-v2-298678-299329.root",
"SingleElectron-Run2017C-WSkim-Prompt-v1-299368-299649.root",
"SingleElectron-Run2017C-WSkim-Prompt-v3-300742-302029.root",
"SingleElectron-Run2017D-WSkim-Prompt-v1-302030-302663.root",
"DoubleEG-Run2017B-ZSkim-Prompt-v1-297046-297723.root", 
"DoubleEG-Run2017B-ZSkim-Prompt-v2-298678-299329.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v1-299368-299649.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v2-299929-300676.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v3-300742-302029.root", 
"DoubleEG-Run2017D-ZSkim-Prompt-v1-302030-302663.root", 
"DoubleEG-Run2017E-ZSkim-Prompt-v1-303574-304797.root"
]

folderlist = [
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/SingleElectron-Run2017B-WSkim-Prompt-v1/297046-297723/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/SingleElectron-Run2017B-WSkim-Prompt-v2/298678-299329/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/SingleElectron-Run2017C-WSkim-Prompt-v1/299368-299649/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/SingleElectron-Run2017C-WSkim-Prompt-v3/300742-302029/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/SingleElectron-Run2017D-WSkim-Prompt-v1/302030-302663/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017B-ZSkim-Prompt-v1/297046-297723/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017B-ZSkim-Prompt-v2/298678-299329/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017C-ZSkim-Prompt-v1/299368-299649/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017C-ZSkim-Prompt-v2/299929-300676/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017C-ZSkim-Prompt-v3/300742-302029/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017D-ZSkim-Prompt-v1/302030-302663/294927-304120_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_PS_EoP_v1/DoubleEG-Run2017E-ZSkim-Prompt-v1/303574-304797/294927-304120_Prompt_v1/newNtuples/"
]
'''
'''
ntuplelist = [
"DoubleEG-Run2017B-ZSkim-Prompt-v1-297046-297723.root", 
"DoubleEG-Run2017B-ZSkim-Prompt-v2-298678-299329.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v1-299368-299649.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v2-299929-300676.root", 
"DoubleEG-Run2017C-ZSkim-Prompt-v3-300742-302029.root", 
"DoubleEG-Run2017D-ZSkim-Prompt-v1-302030-302663.root", 
"DoubleEG-Run2017E-ZSkim-Prompt-v1-303574-304797.root",
"DoubleEG-Run2017F-ZSkim-Prompt-v1-305040-305636.root"
]

folderlist = [
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017B-ZSkim-Prompt-v1/297046-297723/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017B-ZSkim-Prompt-v2/298678-299329/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017C-ZSkim-Prompt-v1/299368-299649/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017C-ZSkim-Prompt-v2/299929-300676/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017C-ZSkim-Prompt-v3/300742-302029/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017D-ZSkim-Prompt-v1/302030-302663/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017E-ZSkim-Prompt-v1/303574-304797/294927-305636_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_cand_v4/DoubleEG-Run2017F-ZSkim-Prompt-v1/305040-305636/294927-305636_Prompt_v1/newNtuples/"
]
'''

ntuplelist = [
"DoubleEG-Run2017F-ZSkim-Prompt-v1-305040-306460.root",
"SingleElectron-Run2017F-WSkim-Prompt-v1-305040-306460.root",
"DoubleEG-Run2017F-ZSkim-Prompt-v1-305040-306460.root",
"SingleElectron-Run2017F-WSkim-Prompt-v1-305040-306460.root"
]

folderlist=[
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_IC_v5/DoubleEG-Run2017F-ZSkim-Prompt-v1/305040-306460/294927-306126_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_IC_v5/SingleElectron-Run2017F-WSkim-Prompt-v1/305040-306460/294927-306126_Prompt_v1/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_IC_v5/DoubleEG-Run2017F-ZSkim-Prompt-v1/305040-306460/306134-306793_DCSonly/newNtuples/",
"/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/Cal_Oct2017_IC_v5/SingleElectron-Run2017F-WSkim-Prompt-v1/305040-306460/306134-306793_DCSonly/newNtuples/"
]


EBm   =   1

currentDir   =   os.getcwd();
CMSSWDir   =   currentDir+"/../";

os.system("mkdir   Job_monitoring_"+ntupleName)

ietamin   =   0
iphimax=   1
ietamax   =   0
iphimin   =   0

#run = ["runB_v1","runB_v2","runC_v1","runC_v2","runC_v3","runD_v1"]

for   i   in   range(len(categories)):
   ietamin   =   0
   ietamax   =   5
   for   k   in   range   (1,   6):
   #for   k   in   range   (1,   2):
      iphimin   =   0
      iphimax   =   10
      if   ietamin   ==   1:
         ietamin   =   k
         ietamax   =   k   +   9
      elif   k   !=   1:
         ietamin   =   ietamax   +1
         ietamax   =   ietamin   +   19   
      for   j   in   range   (0,   36):
      #for   j   in   range   (0,1):
       if      k   ==   1   and   j   ==   0:
            #iphimin   =   iphimax
            iphimax   =   iphimax   +   10
       if   k   ==   1   and   j   >   0:
         	iphimin   =   iphimax   
         	iphimax   =   iphimax   +   20
       if   k   !=   1   and   j   >   0:
            iphimin   =   iphimax   
            iphimax   =   iphimin   +   10
         #   iphimin   =   iphimax
         #   iphimax   =   iphimin   +   20
       if iphimin == 360:
        break  
       #for j in range(len(run)):
       #fn   =   "Job_monitoring_"+ntupleName+"/Job_"+categories[i]+"_ietamin_"+str(ietamin*(1))+"_ietamax_"+str(ietamax*(1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"_events_"+str(events[i]);
       #fn   =   "Job_monitoring_"+ntupleName+"/Job_"+categories[i]+"_ietamin_"+str(ietamax*(-1))+"_ietamax_"+str(ietamin*(-1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"_events_"+str(events[i]);
       #fn   =   "Job_monitoring_"+ntupleName+"/Job_"+categories[i]+"_ietamin_"+str(ietamin*(1))+"_ietamax_"+str(ietamax*(1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"_events_"+str(events[i])+"_1nw";
       fn   =   "Job_monitoring_"+ntupleName+"/Job_"+categories[i]+"_ietamin_"+str(ietamax*(-1))+"_ietamax_"+str(ietamin*(-1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"_events_"+str(events[i])+"_1nw";
         
       outScript   =   open(fn+".sh","w");
#            command   =   "ZFitter.exe   -f   EoverPmonitoring_batch_"+ntupleName+".dat   --evtsPerPoint   200000   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   0.95   --yMAX   1.05   --LUMI   24.1   --dayMin   15-03-2016   --dayMax   30-12-2016   --EoPvsPU   1   --noPU"   #use   this   if   you   want   to   run   vs   Nvtx
#            command   =   "ZFitter.exe   -f   EoverPmonitoring_batch_"+ntupleName+".dat   --evtsPerPoint   200000   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   0.8   --yMAX   1.20   --LUMI   24.1   --dayMin   15-03-2016   --dayMax   30-12-2016   --noPU"   #use   this   if   you   want   to   run   E/p   vs   LC
         #command   =   "ZFitter.exe   -f   EoverPmonitoring_batch_"+ntupleName+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   1.15   --LUMI   36.4   --dayMin   15-03-2016   --dayMax   30-12-2016   --noPU   --IetaMin   "+   str(ietamin*(1))   +   "   --IetaMax   "   +   str(ietamax*(1))   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time
         
         #command   =   "ZFitter.exe   -f   EoverPmonitoring_batch_"+ntupleName+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   1.15   --LUMI   36.4   --dayMin   15-03-2016   --dayMax   30-12-2016   --noPU   --IetaMax   "+   str(ietamin*(-1))   +   "   --IetaMin   "   +   str(ietamax*(-1))   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time
         
         #command   =   "ZFitter.exe   -f   /afs/cern.ch/user/v/vciriolo/work/private/EOverP/CMSSW_8_0_24_patch1/src/Calibration/ZFitter/data/validation/"+ntupleName+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   "+yMAX[i]+"   --LUMI   10   --dayMin   15-03-2016   --dayMax   30-12-2017   --noPU   --IetaMax   "+   str(ietamin*(-1))   +   "   --IetaMin   "   +   str(ietamax*(-1))   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time
         #command   =   "ZFitter.exe   -f   /afs/cern.ch/user/v/vciriolo/work/private/EOverP/CMSSW_8_0_24_patch1/src/Calibration/ZFitter/data/validation/"+ntupleName+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   "+yMAX[i]+"   --LUMI   10   --dayMin   15-03-2016   --dayMax   30-12-2017   --noPU   --IetaMax   "+   str(ietamax)   +   "   --IetaMin   "   +   str(ietamin)   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time
       #command   =   "ZFitter.exe   -f   /afs/cern.ch/user/v/vciriolo/work/private/EOverP/CMSSW_8_0_24_patch1/src/Calibration/ZFitter/data/validation/fast_test_"+run[j]+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   "+yMAX[i]+"   --LUMI   17.8   --dayMin   15-03-2016   --dayMax   30-12-2017   --noPU   --IetaMax   "+   str(ietamax)   +   "   --IetaMin   "   +   str(ietamin)   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time
       #command   =   "ZFitter.exe   -f   /afs/cern.ch/user/v/vciriolo/work/private/EOverP/CMSSW_8_0_24_patch1/src/Calibration/ZFitter/data/validation/fast_test_"+run[j]+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   "+yMAX[i]+"   --LUMI   17.8   --dayMin   15-03-2016   --dayMax   30-12-2017   --noPU   --IetaMax   "+   str(ietamin*(-1))   +   "   --IetaMin   "   +   str(ietamax*(-1))   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time
       command   =   "ZFitter.exe   -f   /afs/cern.ch/user/v/vciriolo/work/private/EOverP/CMSSW_8_0_24_patch1/src/Calibration/ZFitter/data/validation/"+ntupleName+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   "+yMAX[i]+"   --LUMI   17.8   --dayMin   15-03-2016   --dayMax   30-12-2017   --noPU   --IetaMax   "+   str(ietamin*(-1))   +   "   --IetaMin   "   +   str(ietamax*(-1))   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time  
       #command   =   "ZFitter.exe   -f   /afs/cern.ch/user/v/vciriolo/work/private/EOverP/CMSSW_8_0_24_patch1/src/Calibration/ZFitter/data/validation/"+ntupleName+".dat   --evtsPerPoint   "+events[i]+"   --laserMonitoringEP   --EBEE   "+categories[i]+"   --yMIN   "+yMIN[i]+"   --yMAX   "+yMAX[i]+"   --LUMI   17.8   --dayMin   15-03-2016   --dayMax   30-12-2017   --noPU   --IetaMax   "+   str(ietamax*(1))   +   "   --IetaMin   "   +   str(ietamin*(1))   +   "      --IphiMin   "   +   str(iphimin)   +   "   --IphiMax   "   +   str(iphimax)   #default,   to   be   run   for   E/p   vs   time  
       print   command;
         
       outScript.write('#!/bin/bash');
       outScript.write("\n"+'cd   '+CMSSWDir);
       outScript.write("\n"+'eval   `scram   runtime   -sh`');
       outScript.write("\n"+'cd   -');
       outScript.write("\necho   $PWD");
       outScript.write("\nmkdir   "+categories[i]+"__");
       outScript.write("\nll");

       for   j   in   range(len(ntuplelist)):
          outScript.write("\necho   \"copy   main   tree\"   ");
          #outScript.write("\ncp   "+folderlist[j]+""+ntuplelist[j]+".root   ./")
          #outScript.write("\ncp   "+folderlist[j]+""+ntuplelist[j]+"   ./")
          #outScript.write("\ncp   "+ntuplelist[j]+"   ./")
          outScript.write("\ncp   "+folderlist[j]+""+ntuplelist[j]+"   ./")
          
#          outScript.write("\necho   \"copy   extracalib   tree\"   ");
#          outScript.write("\ncmsStage   "+folderlist[j]+"extraCalibTree-"+ntuplelist[j]+".root   ./")

       outScript.write("\necho   \"copia13\"   ");
#                                                                        outScript.write("\ncp   -v   /afs/cern.ch/user/l/lbrianza/work/public/ntupleEoP/*   .")
         #outScript.write("\ncmsStage   "+folder+"momentumCalibration2015_EB_pTk.root   ./")
       outScript.write("\necho   \"copia14\"   ");
       #outScript.write("\ncmsStage   "+folder+"momentumCalibration2015_EB_scE.root   ./")
       outScript.write("\necho   \"copia15\"   ");
         #outScript.write("\ncmsStage   "+folder+"momentumCalibration2015_EE_pTk.root   ./")
       outScript.write("\necho   \"copia14\"   ");
       #outScript.write("\ncmsStage   "+folder+"momentumCalibration2015_EE_scE.root   ./")
       outScript.write("\necho   \"copia15\"   ");
       #outScript.write("\ncmsStage   "+folder+"EoverPmonitoring_batch_"+ntupleName+".dat   ./")
       outScript.write("\necho   \"fine   copia\"   ");
         
       outScript.write("\nls")
       outScript.write("\necho   \"eseguo:   "+command+"\"   ")
       outScript.write("\n"+command);
       outScript.write("\nls")
         #outScript.write("\ncp   -v   -r   "+categories[i]+"__/   "+currentDir+"/"+categories[i]+"_"+ntupleName+"_ietamin_"+str(ietamin*(1))+"_ietamax_"+str(ietamax*(1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"/")
         #outScript.write("\ncp   -v   -r   "+categories[i]+"__/   "+currentDir+"/"+categories[i]+"_"+ntupleName+"_ietamax_"+str(ietamin*(-1))+"_ietamin_"+str(ietamax*(-1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"/")
         #outScript.write("\ncp   -v   -r   "+categories[i]+"__/   "+currentDir+"/"+categories[i]+"_"+ntupleName+"_"+run[j]+"_ietamax_"+str(ietamax*(1))+"_ietamin_"+str(ietamin*(1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"/")
       outScript.write("\nexport EOS_MGM_URL=root://eosuser.cern.ch")
         #
       #outScript.write("\ncp   -v   -r   "+categories[i]+"__/   "+currentDir+"/"+categories[i]+"_"+ntupleName+"_"+run[j]+"_ietamax_"+str(ietamin*(-1))+"_ietamin_"+str(ietamax*(-1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"/")
         
       outScript.write("\ncp   -v   -r   "+categories[i]+"__/   /eos/user/v/vciriolo/EoP_monitoring/harness2017/Cal_Oct2017/SingleAndDouble/"+ntupleName+"/1nw/"+categories[i]+"_"+ntupleName+"_ietamax_"+str(ietamin*(-1))+"_ietamin_"+str(ietamax*(-1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"_events_"+str(events[i])+"/")
       #outScript.write("\ncp   -v   -r   "+categories[i]+"__/   /eos/user/v/vciriolo/EoP_monitoring/harness2017/Cal_Oct2017/SingleAndDouble/"+ntupleName+"/1nw/"+categories[i]+"_"+ntupleName+"_ietamax_"+str(ietamax*(1))+"_ietamin_"+str(ietamin*(1))+"_iphimin_"+str(iphimin)+"_iphimax_"+str(iphimax)+"_events_"+str(events[i])+"/")
       
       outScript.close();
       os.system("chmod   777   "+currentDir+"/"+fn+".sh");
       #command2   =   "bsub   -q   cmscaf1nd   -cwd   "+currentDir+"   "+currentDir+"/"+fn+".sh";
       command2   =   "bsub   -q   1nw   -cwd   "+currentDir+"   "+currentDir+"/"+fn+".sh";
       if   not   options.generateOnly:
                    os.system(command2);
       print   command2

            




'''
fn   =   "Job_monitoring_"+ntupleName+"/Job_"+"EE";
outScript   =   open(fn+".sh","w");
command   =   "ZFitter.exe   -f   EoverPcalibration_batch_"+ntupleName+".dat   --evtsPerPoint   50000   --laserMonitoringEPvsPU   --EBEE   EE   --yMIN   0.6   --yMAX   1.15   --LUMI   12.9   --dayMin   15-03-2016   --dayMax   01-08-2016"
print   command;
outScript.write('#!/bin/bash');
outScript.write("\n"+'cd   '+CMSSWDir);
outScript.write("\n"+'eval   `scram   runtime   -sh`');
outScript.write("\n"+'cd   -');
outScript.write("\necho   $PWD");
outScript.write("mkdir   EE__");
outScript.write("\nll");


outScript.write("\necho   \"copia1\"   ");
outScript.write("\ncmsStage   "+folder+ntupleName+".root   ./")
outScript.write("\necho   \"copia2\"   ");
outScript.write("\ncmsStage   "+folder+"extraCalibTree-"+ntupleName+".root   ./")

outScript.write("\necho   \"copia13\"   ");
#                                                                        outScript.write("\ncp   -v   /afs/cern.ch/user/l/lbrianza/work/public/ntupleEoP/*   .")
outScript.write("\ncmsStage   "+folder+"momentumCalibration2015_EE_pTk.root   ./")
outScript.write("\necho   \"copia14\"   ");
outScript.write("\ncmsStage   "+folder+"momentumCalibration2015_EE_scE.root   ./")
outScript.write("\necho   \"copia15\"   ");
outScript.write("\ncmsStage   "+folder+"EoverPcalibration_batch_"+ntupleName+".dat   ./")
outScript.write("\necho   \"fine   copia\"   ");

outScript.write("\nls")
outScript.write("\necho   \"eseguo:   "+command+"\"   ")
outScript.write("\n"+command);
outScript.write("\nls")
outScript.write("\ncp   -v   -r   EE__/   "+currentDir+"/EE_"+ntupleName+"/")
outScript.close();
os.system("chmod   777   "+currentDir+"/"+fn+".sh");
command2   =   "bsub   -q   cmscaf1nd   -cwd   "+currentDir+"   "+currentDir+"/"+fn+".sh";
if   not   options.generateOnly:
            os.system(command2);
print   command2
'''





