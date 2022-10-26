/*
 * Copyright (C) 2020 The Android Open Source Project
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

#pragma once

#include <aidl/android/hardware/power/BnPower.h>

namespace aidl {
namespace android {
namespace hardware {
namespace power {
namespace impl {
namespace mediatek {

class Power : public BnPower {
public:
    Power();
    ~Power();
    ndk::ScopedAStatus setMode(Mode type, bool enabled) override;
    ndk::ScopedAStatus isModeSupported(Mode type, bool* _aidl_return) override;
    ndk::ScopedAStatus setBoost(Boost type, int32_t durationMs) override;
    ndk::ScopedAStatus isBoostSupported(Boost type, bool* _aidl_return) override;
    ndk::ScopedAStatus createHintSession(int32_t tgid, int32_t uid,
                                         const std::vector<int32_t>& threadIds,
                                         int64_t durationNanos,
                                         std::shared_ptr<IPowerHintSession>* _aidl_return) override;
    ndk::ScopedAStatus getHintSessionPreferredRate(int64_t* outNanoseconds) override;
private:
    typedef void (*libpowerhal_Init_t)(int);
    typedef void (*libpowerhal_LockRel_t)(int);
    typedef void (*libpowerhal_UserScnDisableAll_t)(void);
    typedef void (*libpowerhal_UserScnRestoreAll_t)(void);
    typedef int (*libpowerhal_CusLockHint_t)(int32_t, int32_t, __pid_t);

    libpowerhal_Init_t libpowerhal_Init;
    libpowerhal_CusLockHint_t libpowerhal_CusLockHint;
    libpowerhal_LockRel_t libpowerhal_LockRel;
    libpowerhal_UserScnDisableAll_t libpowerhal_UserScnDisableAll;
    libpowerhal_UserScnRestoreAll_t libpowerhal_UserScnRestoreAll;

    void *powerHandle;

    int mHandle;
    bool mLowPowerEnabled;
};

}  // namespace mediatek
}  // namespace impl
}  // namespace power
}  // namespace hardware
}  // namespace android
}  // namespace aidl
