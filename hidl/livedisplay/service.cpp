/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "vendor.lineage.livedisplay@2.1-service-nashc"

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <hidl/HidlTransportSupport.h>

#include "DisplayColorCalibration.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

using ::vendor::lineage::livedisplay::V2_1::IDisplayColorCalibration;
using ::vendor::lineage::livedisplay::V2_1::implementation::DisplayColorCalibration;

int main() {
    android::sp<IDisplayColorCalibration> dcc = new DisplayColorCalibration();

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (dcc->registerAsService() != android::OK) {
        LOG(ERROR) << "Cannot register display color calibration HAL service.";
        return 1;
    }

    LOG(INFO) << "LiveDisplay HAL service is ready.";

    joinRpcThreadpool();

    LOG(ERROR) << "LiveDisplay HAL service failed to join thread pool.";
    return 1;
}
