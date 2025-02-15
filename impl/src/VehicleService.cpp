#define LOG_TAG __FILE_NAME__
#include <log/log_main.h>

#include <chrono>
#include <thread>

#include <hidl/HidlTransportSupport.h>

#include <vhal_v2_0/EmulatedVehicleConnector.h>
#include <vhal_v2_0/EmulatedVehicleHal.h>
#include <vhal_v2_0/VehicleHalManager.h>
#include <vhal_v2_0/VehicleEmulator.h>

#include "VendorVehicleHal.h"

using namespace std::chrono_literals;

using namespace vendor::v::vehicle::V1_0;

using namespace android;
using namespace android::hardware;
using namespace android::hardware::automotive::vehicle::V2_0;

int main(int /* argc */, char* /* argv */ []) {
    auto store = std::make_unique<vhal_v2_0::VehiclePropertyStore>();
    auto connector = std::make_unique<vhal_v2_0::EmulatedVehicleConnector>();
    auto hal = std::make_unique<VendorVehicleHal>(store.get(), connector.get());
    auto emulator = std::make_unique<vhal_v2_0::VehicleEmulator>(hal.get());
    auto service = android::sp<vhal_v2_0::VehicleHalManager>::make(hal.get());
    connector->setValuePool(hal->getValuePool());


    android::hardware::configureRpcThreadpool(4, true /* callerWillJoin */);

    ALOGI("Registering as service...");
    android::status_t status = service->registerAsService();

    if (status != android::OK) {
        ALOGE("Unable to register vehicle service (%d)", status);
        return 1;
    }

    ALOGI("Ready");
    android::hardware::joinRpcThreadpool();

    return 0;
}
