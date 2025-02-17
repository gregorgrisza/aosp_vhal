#pragma once

#include <vhal_v2_0/EmulatedVehicleHal.h>

namespace vhal_v2_0 = android::hardware::automotive::vehicle::V2_0;

namespace vendor {
namespace v {
namespace vehicle {
namespace V1_0 {

namespace impl {

/** Implementation of VehicleHal that connected to emulator instead of real vehicle network. */
class VendorVehicleHal : public EmulatedVehicleHal {
    public:
        VendorVehicleHal(VehiclePropertyStore* propStore, VehicleHalClient* client,
                           EmulatedUserHal* emulatedUserHal = nullptr);
    
        VehiclePropValuePtr get(const VehiclePropValue& requestedPropValue,
                                StatusCode* outStatus) override;
        StatusCode set(const VehiclePropValue& propValue) override;
    
    };

} // namespace impl

} // namespace V1_0
} // namespace vehicle
} // namespace v
} // namespace vendor