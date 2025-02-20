#define LOG_TAG __FILE_NAME__
#include <log/log_main.h>

#include <chrono>
#include <thread>

#include <hidl/HidlTransportSupport.h>

#include <vhal_v2_0/VehicleHalManager.h>

#include "VehicleHalClient.h"
#include "VendorVehicleHal.h"

using namespace std::chrono_literals;

using namespace android;
using namespace android::hardware;
using namespace android::hardware::automotive::vehicle::V2_0;


int main(int /* argc */, char* /* argv */ []) {
    auto store = std::make_unique<vhal_v2_0::VehiclePropertyStore>();
    auto client = std::make_unique<vvhal_v1_0::impl::VehicleHalClient>();
    auto hal = std::make_unique<vvhal_v1_0::impl::VendorVehicleHal>(store.get(), client.get());
    auto service = android::sp<vhal_v2_0::VehicleHalManager>::make(hal.get());

    configureRpcThreadpool(1, true); 

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
