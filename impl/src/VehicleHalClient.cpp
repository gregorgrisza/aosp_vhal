// Based on hardware/interfaces/automotive/vehicle/2.0/default/impl/vhal_v2_0/VehicleHalClient.cpp

#define LOG_TAG __FILE_NAME__
#include <log/log_main.h>

#include "VehicleHalClient.h"

#include <android-base/logging.h>

namespace vendor {
namespace v {
namespace vehicle {
namespace V1_0 {

namespace impl {

void VehicleHalClient::onPropertyValue(const vhal_v2_0::VehiclePropValue& value, bool updateStatus)
{
    if (!mPropCallback)
    {
        ALOGE("%s(): PropertyCallBackType is not registered!", __func__);
        return;
    }
    return mPropCallback(value, updateStatus);
}

void VehicleHalClient::registerPropertyValueCallback(PropertyCallBackType&& callback)
{
    if (mPropCallback)
    {
        ALOGW("%s(): Cannot register multiple callbacks!", __func__);
        return;
    }
    mPropCallback = std::move(callback);
}

std::vector<vhal_v2_0::VehiclePropConfig> VehicleHalClient::getAllPropertyConfig() const
{
    return std::vector<vhal_v2_0::VehiclePropConfig>();
}

vhal_v2_0::StatusCode VehicleHalClient::setProperty(const vhal_v2_0::VehiclePropValue& value, bool updateStatus)
{
    ALOGD("%s(): prop: %d", __func__, value.prop);

    vhal_v2_0::StatusCode ret = vhal_v2_0::StatusCode::OK;

    ret = setIfSupportedProperty(value, updateStatus);

    if (ret == vhal_v2_0::StatusCode::OK)
    {
        onPropertyValue(value, updateStatus);
    }

    return ret;
}

vhal_v2_0::StatusCode VehicleHalClient::setIfSupportedProperty(const vhal_v2_0::VehiclePropValue& value, bool updateStatus)
{
    vhal_v2_0::StatusCode ret = vhal_v2_0::StatusCode::OK;

    switch (value.prop)
    {
    case static_cast<int32_t>(VehicleProperty::VENDOR_INTERIOR_LIGHTNING):
        {        
            const std::lock_guard<std::mutex> lock(mPropVendorInteriorLightning.second);
            mPropVendorInteriorLightning.first = value;
        }        
        break;
    default:
        break;
    }

    return ret;
}

} // namespace impl

} // namespace V1_0
} // namespace vehicle
} // namespace v
} // namespace vendor
