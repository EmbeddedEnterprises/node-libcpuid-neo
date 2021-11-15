#include "addon.hpp"
#include <iostream>

namespace NLN {

    Napi::String stringFromStringView(Napi::Env env, std::string_view sv) {
        return Napi::String::New(env, sv.data(), sv.size());
    }

    std::string_view mapVendor(cpu_vendor_t vendor) {
        using namespace std::literals;
    
        //Might consider an unordered_map, but probably slower and not worth it
        switch(vendor) {
            case VENDOR_INTEL: return "intel"sv;

            case VENDOR_AMD: return "amd"sv;

            case VENDOR_CYRIX: return "cyrix"sv;

            case VENDOR_NEXGEN: return "nexgen"sv;

            case VENDOR_TRANSMETA:return "transmeta"sv;

            case VENDOR_UMC: return "umc"sv;

            case VENDOR_CENTAUR: return "idt"sv;

            case VENDOR_RISE: return "rise"sv;

            case VENDOR_SIS: return "sis"sv;

            case VENDOR_NSC: return "nsc"sv;

            case VENDOR_HYGON: return "hygon"sv;

            default: return "unknown"sv;
        }
    }


    Napi::Object parseFeatures(Napi::Env env, const cpu_id_t& cpuData) {
        Napi::Object featureObj = Napi::Object::New(env);

        auto lol = cpuData.flags[CPU_FEATURE_3DNOW];

        featureObj.Set("fpu", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_FPU] > 0));
		featureObj.Set("vme", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_VME] > 0));
		featureObj.Set("de", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_DE] > 0));
		featureObj.Set("pse", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PSE] > 0));
		featureObj.Set("tsc", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TSC] > 0));
		featureObj.Set("msr", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MSR] > 0));
		featureObj.Set("pae", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PAE] > 0));
		featureObj.Set("mce", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MCE] > 0));
		featureObj.Set("cx8", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CX8] > 0));
		featureObj.Set("apic", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_APIC] > 0));
		featureObj.Set("mtrr", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MTRR] > 0));
		featureObj.Set("sep", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SEP] > 0));
		featureObj.Set("pge", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PGE] > 0));
		featureObj.Set("mca", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MCA] > 0));
		featureObj.Set("cmov", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CMOV] > 0));
		featureObj.Set("pat", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PAT] > 0));
		featureObj.Set("pse36", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PSE36] > 0));
		featureObj.Set("pn", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PN] > 0));
		featureObj.Set("clflush", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CLFLUSH] > 0));
		featureObj.Set("dts", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_DTS] > 0));
		featureObj.Set("acpi", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_ACPI] > 0));
		featureObj.Set("mmx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MMX] > 0));
		featureObj.Set("fxsr", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_FXSR] > 0));
		featureObj.Set("sse", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSE] > 0));
		featureObj.Set("sse2", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSE2] > 0));
		featureObj.Set("ss", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SS] > 0));
		featureObj.Set("ht", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_HT] > 0));
		featureObj.Set("tm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TM] > 0));
		featureObj.Set("ia64", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_IA64] > 0));
		featureObj.Set("pbe", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PBE] > 0));
		featureObj.Set("pni", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PNI] > 0));
		featureObj.Set("pclmul", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PCLMUL] > 0));
		featureObj.Set("dts64", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_DTS64] > 0));
		featureObj.Set("monitor", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MONITOR] > 0));
		featureObj.Set("ds_cpl", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_DS_CPL] > 0));
		featureObj.Set("vmx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_VMX] > 0));
		featureObj.Set("smx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SMX] > 0));
		featureObj.Set("est", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_EST] > 0));
		featureObj.Set("tm2", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TM2] > 0));
		featureObj.Set("ssse3", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSSE3] > 0));
		featureObj.Set("cid", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CID] > 0));
		featureObj.Set("cx16", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CX16] > 0));
		featureObj.Set("xtpr", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_XTPR] > 0));
		featureObj.Set("pdcm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PDCM] > 0));
		featureObj.Set("dca", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_DCA] > 0));
		featureObj.Set("sse4_1", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSE4_1] > 0));
		featureObj.Set("sse4_2", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSE4_2] > 0));
		featureObj.Set("syscall", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SYSCALL] > 0));
		featureObj.Set("xd", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_XD] > 0));
		featureObj.Set("x2apic", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_X2APIC] > 0));
		featureObj.Set("movbe", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MOVBE] > 0));
		featureObj.Set("popcnt", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_POPCNT] > 0));
		featureObj.Set("aes", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AES] > 0));
		featureObj.Set("xsave", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_XSAVE] > 0));
		featureObj.Set("osxsave", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_OSXSAVE] > 0));
		featureObj.Set("avx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX] > 0));
		featureObj.Set("mmxext", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MMXEXT] > 0));
		featureObj.Set("3dnow", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_3DNOW] > 0));
		featureObj.Set("3dnowext", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_3DNOWEXT] > 0));
		featureObj.Set("nx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_NX] > 0));
		featureObj.Set("fxsr_opt", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_FXSR_OPT] > 0));
		featureObj.Set("rdtscp", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_RDTSCP] > 0));
		featureObj.Set("lm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_LM] > 0));
		featureObj.Set("lahf_lm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_LAHF_LM] > 0));
		featureObj.Set("cmp_legacy", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CMP_LEGACY] > 0));
		featureObj.Set("svm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SVM] > 0));
		featureObj.Set("sse4a", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSE4A] > 0));
		featureObj.Set("misalignsse", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_MISALIGNSSE] > 0));
		featureObj.Set("abm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_ABM] > 0));
		featureObj.Set("3dnowprefetch", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_3DNOWPREFETCH] > 0));
		featureObj.Set("osvw", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_OSVW] > 0));
		featureObj.Set("ibs", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_IBS] > 0));
		featureObj.Set("sse5", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SSE5] > 0));
		featureObj.Set("skinit", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SKINIT] > 0));
		featureObj.Set("wdt", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_WDT] > 0));
		featureObj.Set("ts", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TS] > 0));
		featureObj.Set("fid", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_FID] > 0));
		featureObj.Set("vid", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_VID] > 0));
		featureObj.Set("ttp", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TTP] > 0));
		featureObj.Set("tm_amd", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TM_AMD] > 0));
		featureObj.Set("stc", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_STC] > 0));
		featureObj.Set("100mhzsteps", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_100MHZSTEPS] > 0));
		featureObj.Set("hwpstate", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_HWPSTATE] > 0));
		featureObj.Set("constant_tsc", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CONSTANT_TSC] > 0));
		featureObj.Set("xop", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_XOP] > 0));
		featureObj.Set("fma3", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_FMA3] > 0));
		featureObj.Set("fma4", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_FMA4] > 0));
		featureObj.Set("tbm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_TBM] > 0));
		featureObj.Set("f16c", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_F16C] > 0));
		featureObj.Set("rdrand", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_RDRAND] > 0));
		featureObj.Set("cpb", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_CPB] > 0));
		featureObj.Set("aperfmperf", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_APERFMPERF] > 0));
		featureObj.Set("pfi", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PFI] > 0));
		featureObj.Set("pa", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_PA] > 0));
		featureObj.Set("avx2", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX2] > 0));
		featureObj.Set("bmi1", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_BMI1] > 0));
		featureObj.Set("bmi2", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_BMI2] > 0));
		featureObj.Set("hle", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_HLE] > 0));
		featureObj.Set("rtm", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_RTM] > 0));
		featureObj.Set("avx512f", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512F] > 0));
		featureObj.Set("avx512dq", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512DQ] > 0));
		featureObj.Set("avx512pf", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512PF] > 0));
		featureObj.Set("avx512er", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512ER] > 0));
		featureObj.Set("avx512cd", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512CD] > 0));
		featureObj.Set("sha_ni", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SHA_NI] > 0));
		featureObj.Set("avx512bw", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512BW] > 0));
		featureObj.Set("avx512vl", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512VL] > 0));
		featureObj.Set("sgx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_SGX] > 0));
		featureObj.Set("rdseed", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_RDSEED] > 0));
		featureObj.Set("adx", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_ADX] > 0));
		featureObj.Set("avx512vnni", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512VNNI] > 0));
		featureObj.Set("avx512vbmi", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512VBMI] > 0));
		featureObj.Set("avx512vbmi2", Napi::Boolean::New(env, cpuData.flags[CPU_FEATURE_AVX512VBMI2] > 0));

        return featureObj;
    }

    Napi::Object parseCache(Napi::Env env, const cpu_id_t& cpuData) {
        Napi::Object cacheObj = Napi::Object::New(env);

        Napi::Object L1IObj = Napi::Object::New(env);
        L1IObj.Set("size", Napi::Number::New(env, cpuData.l1_instruction_cache));
        L1IObj.Set("associativity", Napi::Number::New(env, cpuData.l1_instruction_assoc));
        L1IObj.Set("cacheLineSize", Napi::Number::New(env, cpuData.l1_instruction_cacheline));

        cacheObj.Set("L1I", L1IObj);
        
        Napi::Object L1DObj = Napi::Object::New(env);
        L1DObj.Set("size", Napi::Number::New(env, cpuData.l1_data_cache));
        L1DObj.Set("associativity", Napi::Number::New(env, cpuData.l1_data_assoc));
        L1DObj.Set("cacheLineSize", Napi::Number::New(env, cpuData.l1_data_cacheline));

        cacheObj.Set("L1D", L1DObj);

        Napi::Object L2Obj = Napi::Object::New(env);
        L2Obj.Set("size", Napi::Number::New(env, cpuData.l2_cache));
        L2Obj.Set("associativity", Napi::Number::New(env, cpuData.l2_assoc));
        L2Obj.Set("cacheLineSize", Napi::Number::New(env, cpuData.l2_cacheline));

        cacheObj.Set("L2", L2Obj);

        Napi::Object L3Obj = Napi::Object::New(env);
        L3Obj.Set("size", Napi::Number::New(env, cpuData.l3_cache));
        L3Obj.Set("associativity", Napi::Number::New(env, cpuData.l3_assoc));
        L3Obj.Set("cacheLineSize", Napi::Number::New(env, cpuData.l3_cacheline));

        cacheObj.Set("L3", L3Obj);

        Napi::Object L4Obj = Napi::Object::New(env);
        L4Obj.Set("size", Napi::Number::New(env, cpuData.l4_cache));
        L4Obj.Set("associativity", Napi::Number::New(env, cpuData.l4_assoc));
        L4Obj.Set("cacheLineSize", Napi::Number::New(env, cpuData.l4_cacheline));

        cacheObj.Set("L4", L4Obj);

        return cacheObj;
    }

    Napi::Object parseID(Napi::Env env, const cpu_id_t& cpuData) {
        Napi::Object IDObj = Napi::Object::New(env);

        IDObj.Set("family", Napi::Number::New(env, cpuData.family));
        IDObj.Set("model", Napi::Number::New(env, cpuData.model));
        IDObj.Set("stepping", Napi::Number::New(env, cpuData.stepping));
        IDObj.Set("extFamily", Napi::Number::New(env, cpuData.ext_family));
        IDObj.Set("extModel", Napi::Number::New(env, cpuData.ext_model));

        return IDObj;
    }

    Napi::Object getCPUID(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();

        if(!cpuid_present()) {
            throw Napi::Error::New(env, "CPUID instruction is not available");
        }

        cpu_raw_data_t raw;
        if(cpuid_get_raw_data(&raw) < 0) {
            throw Napi::Error::New(env, "Could not execute CPUID");
        }

        cpu_id_t cpuData;
        if(cpu_identify(&raw, &cpuData) < 0) {
            throw Napi::Error::New(env, "Could not parse CPUID data");
        }

        Napi::Object parsedCPUData = Napi::Object::New(env);
        parsedCPUData.Set("vendorName", Napi::String::New(env, cpuData.vendor_str));
        parsedCPUData.Set("vendor", NLN::stringFromStringView(env, mapVendor(cpuData.vendor)));
        parsedCPUData.Set("vendorNumber", Napi::Number::New(env, int(cpuData.vendor)));
        parsedCPUData.Set("brand", Napi::String::New(env, cpuData.brand_str));
        parsedCPUData.Set("codeName", Napi::String::New(env, cpuData.cpu_codename));
        parsedCPUData.Set("physicalCores", Napi::Number::New(env, cpuData.num_cores));
        parsedCPUData.Set("logicalCores", Napi::Number::New(env, cpuData.num_logical_cpus));
        parsedCPUData.Set("totalCores", Napi::Number::New(env, cpuData.total_logical_cpus));
        parsedCPUData.Set("clockSpeed", Napi::Number::New(env, cpu_clock_by_os()));

        parsedCPUData.Set("features", parseFeatures(env, cpuData));

        parsedCPUData.Set("cache", parseCache(env, cpuData));

        parsedCPUData.Set("id", parseID(env, cpuData));

        return parsedCPUData;
    }

}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

    exports.Set("getCPUID", Napi::Function::New(env, NLN::getCPUID));

    return exports;
}

NODE_API_MODULE(addon, InitAll)