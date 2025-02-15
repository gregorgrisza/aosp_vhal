#define LOG_TAG __FILE_NAME__

#include <android-base/logging.h>
#include <android/log.h>
#include <android-base/macros.h>

#include "VendorVehicleHal.h"


namespace vendor {
namespace v {
namespace vehicle {
namespace V1_0 {

namespace impl {

    constexpr int VENDOR_INTERIOR_LIGHTNING = (int)VehicleProperty::VENDOR_INTERIOR_LIGHTNING;

    VendorVehicleHal::VendorVehicleHal(VehiclePropertyStore* propStore, VehicleHalClient* client,
                                           EmulatedUserHal* emulatedUserHal)
        : EmulatedVehicleHal(propStore, client, emulatedUserHal),
     {
    
     }
    
    static int _vendorWriteProp = -1;
    
    VehicleHal::VehiclePropValuePtr VendorVehicleHal::get(
            const VehiclePropValue& requestedPropValue, StatusCode* outStatus) {
        
     
     VehiclePropValuePtr v = nullptr;
     
     ALOGI("VendorVehicleHal::get  propId: 0x%x", requestedPropValue.prop);
     switch(requestedPropValue.prop)
     {
      case VENDOR_INTERIOR_LIGHTNING:{
      
       auto propValue = new VehiclePropValue();
       propValue->prop = VENDOR_INTERIOR_LIGHTNING;
       propValue->timestamp = elapsedRealtimeNano();
       propValue->value.int32Values.resize(1);
       propValue->value.int32Values[0] = _vendorWriteProp;
       
       v = getValuePool()->obtain(*propValue);
       
       ALOGI("VENDOR_WRITE_PROP calling ECU: to get its val to %d", _vendorWriteProp);
       return v;
      }
      
     }
       
      
     return EmulatedVehicleHal::get(requestedPropValue, outStatus);
    }
    
    StatusCode VendorVehicleHal::set(const VehiclePropValue& propValue) {
     
     ALOGI("VendorVehicleHal::set  propId: 0x%x", propValue.prop);
     
     switch(propValue.prop)
     {
      //
      // Do not return in order to keep prop store updated 
      //
      case VENDOR_INTERIOR_LIGHTNING:
       ALOGI("VENDOR_INTERIOR_LIGHTNING calling ECU: change val to %f", propValue.value.floatValues[0]);
       _vendorWriteProp = propValue.value.int32Values[0];
       break;
      
     }
     return EmulatedVehicleHal::set(propValue);
    }
    

} // namespace impl

} // namespace V1_0
} // namespace vehicle
} // namespace nlab
} // namespace vendor
