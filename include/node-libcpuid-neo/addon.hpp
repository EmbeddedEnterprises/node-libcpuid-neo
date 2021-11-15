#pragma once

#include <memory>
#include <napi.h>
#include <string_view>
#include <libcpuid.h>

#ifndef NAPI_CPP_EXCEPTIONS
#error Addon can only be compiled with NAPI exceptions enabled!
#endif

namespace NLN {

    Napi::String stringFromStringView(Napi::Env env, std::string_view sv);

    std::string_view mapVendor(cpu_vendor_t vendor);

    Napi::Object parseFeatures(Napi::Env env, const cpu_id_t& cpuData);

    Napi::Object parseCache(Napi::Env env, const cpu_id_t& cpuData);

    Napi::Object parseID(Napi::Env env, const cpu_id_t& cpuData);

    Napi::Object getCPUID(const Napi::CallbackInfo& info);
}