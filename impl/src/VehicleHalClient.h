// Based on hardware/interfaces/automotive/vehicle/2.0/default/impl/vhal_v2_0/VehicleHalClient.h

#pragma once

#include <vhal_v2_0/VehicleClient.h>
#include "vendor/v/vehicle/1.0/types.h"

namespace vhal_v2_0 = android::hardware::automotive::vehicle::V2_0;

namespace vendor {
namespace v {
namespace vehicle {
namespace V1_0 {

namespace impl {

using SyncedVehiclePropValue = std::pair<vhal_v2_0::VehiclePropValue, std::mutex>;

// The common client operations that may be used by both native and
// virtualized VHAL clients.
class VehicleHalClient : public vhal_v2_0::IVehicleClient
{
public:
    // Type of callback function for handling the new property values
    using PropertyCallBackType =
        std::function<void(const vhal_v2_0::VehiclePropValue&, bool updateStatus)>;

    // Method from IVehicleClient
    void onPropertyValue(const vhal_v2_0::VehiclePropValue& value, bool updateStatus) override;

    void registerPropertyValueCallback(PropertyCallBackType&& callback);

    std::vector<vhal_v2_0::VehiclePropConfig> getAllPropertyConfig() const override;

    vhal_v2_0::StatusCode setProperty(const vhal_v2_0::VehiclePropValue& value, bool updateStatus) override;

private:
    vhal_v2_0::StatusCode setIfSupportedProperty(const vhal_v2_0::VehiclePropValue& value, bool updateStatus);

    PropertyCallBackType mPropCallback;
    SyncedVehiclePropValue mPropVendorInteriorLightning;
};

} // namespace impl

} // namespace V1_0
} // namespace vehicle
} // namespace v
} // namespace vendor
