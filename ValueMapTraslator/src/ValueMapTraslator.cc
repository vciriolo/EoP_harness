// -*- C++ -*-
//
// Package:    ValueMapTraslator
// Class:      ValueMapTraslator
// 
/**\class ValueMapTraslator ValueMapTraslator.cc Calibration/ValueMapTraslator/src/ValueMapTraslator.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shervin Nourbakhsh,32 4-C03,+41227672087,
//         Created:  Sat Jul 13 15:40:56 CEST 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

//
// class declaration
//

class ValueMapTraslator : public edm::EDProducer {
  typedef double value_t;
  typedef edm::ValueMap<value_t> Map_t;

   public:
      explicit ValueMapTraslator(const edm::ParameterSet&);
      ~ValueMapTraslator();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
  edm::InputTag referenceCollectionTAG;
  edm::InputTag inputCollectionTAG;
  std::string outputCollectionName;
  edm::Handle<reco::GsfElectronCollection> referenceHandle;
  edm::Handle<Map_t> inputHandle;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
ValueMapTraslator::ValueMapTraslator(const edm::ParameterSet& iConfig):
  referenceCollectionTAG(iConfig.getParameter<edm::InputTag>("referenceCollection")),
  inputCollectionTAG(iConfig.getParameter<edm::InputTag>("inputCollection")),
  outputCollectionName(iConfig.getParameter<std::string>("outputCollection"))
{
   //now do what ever other initialization is needed
  /// \todo outputCollectionName = inputCollection+postfix
  produces< Map_t >(outputCollectionName);
  
}


ValueMapTraslator::~ValueMapTraslator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ValueMapTraslator::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   std::vector<value_t>  valueVector;
   std::auto_ptr<Map_t> valueVectorPtr(new Map_t());

   //------------------------------ 
   iEvent.getByLabel(referenceCollectionTAG, referenceHandle);
   iEvent.getByLabel(inputCollectionTAG, inputHandle);
   
   for(Map_t::const_iterator valueMap_itr = inputHandle->begin();
       valueMap_itr != inputHandle->end();
       valueMap_itr++){
   }
   Map_t::Filler filler(*valueVectorPtr);
   filler.insert(referenceHandle, valueVector.begin(), valueVector.end());
   filler.fill();

   iEvent.put(valueVectorPtr);
   
}

// ------------ method called once each job just before starting event loop  ------------
void 
ValueMapTraslator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ValueMapTraslator::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
ValueMapTraslator::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
ValueMapTraslator::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
ValueMapTraslator::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
ValueMapTraslator::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ValueMapTraslator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ValueMapTraslator);
