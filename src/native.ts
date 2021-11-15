import { join } from 'path';

const isElectron = !!(process.versions as any)['electron'];

// Build a path, recursive to the current directory.
// Consists of platform, arch, runtime, runtimeABI, 'addon.node';
// e.g. ./windows/x64/electron/64/addon.node;
const path = './' + join(process.platform, process.arch, isElectron ? 'electron' : 'node', process.versions.modules, 'addon.node');

export const NATIVE = require(path) as NativeModule;

export type ECPUIDVendorStr =
    "intel" |
    "amd" |
    "cyrix" |
    "nexgen" |
    "transmeta" |
    "umc" |
    "idt" |
    "rise" |
    "sis" |
    "nsc" |
    "hygon" |
    "unknown";

//Supported instruction sets / extensions, true if supported, false if not
export type CPUIDFeatures = {
    fpu: boolean;
    vme: boolean;
    de: boolean;
    pse: boolean;
    tsc: boolean;
    msr: boolean;
    pae: boolean;
    mce: boolean;
    cx8: boolean;
    apic: boolean;
    mtrr: boolean;
    sep: boolean;
    pge: boolean;
    mca: boolean;
    cmov: boolean;
    pat: boolean;
    pse36: boolean;
    pn: boolean;
    clflush: boolean;
    dts: boolean;
    acpi: boolean;
    mmx: boolean;
    fxsr: boolean;
    sse: boolean;
    sse2: boolean;
    ss: boolean;
    ht: boolean;
    tm: boolean;
    ia64: boolean;
    pbe: boolean;
    pni: boolean;
    pclmul: boolean;
    dts64: boolean;
    monitor: boolean;
    ds_cpl: boolean;
    vmx: boolean;
    smx: boolean;
    est: boolean;
    tm2: boolean;
    ssse3: boolean;
    cid: boolean;
    cx16: boolean;
    xtpr: boolean;
    pdcm: boolean;
    dca: boolean;
    sse4_1: boolean;
    sse4_2: boolean;
    syscall: boolean;
    xd: boolean;
    x2apic: boolean;
    movbe: boolean;
    popcnt: boolean;
    aes: boolean;
    xsave: boolean;
    osxsave: boolean;
    avx: boolean;
    mmxext: boolean;
    "3dnow": boolean;
    "3dnowext": boolean;
    nx: boolean;
    fxsr_opt: boolean;
    rdtscp: boolean;
    lm: boolean;
    lahf_lm: boolean;
    cmp_legacy: boolean;
    svm: boolean;
    sse4a: boolean;
    misalignsse: boolean;
    abm: boolean;
    "3dnowprefetch": boolean;
    osvw: boolean;
    ibs: boolean;
    sse5: boolean;
    skinit: boolean;
    wdt: boolean;
    ts: boolean;
    fid: boolean;
    vid: boolean;
    ttp: boolean;
    tm_amd: boolean;
    stc: boolean;
    "100mhzsteps": boolean;
    hwpstate: boolean;
    constant_tsc: boolean;
    xop: boolean;
    fma3: boolean;
    fma4: boolean;
    tbm: boolean;
    f16c: boolean;
    rdrand: boolean;
    cpb: boolean;
    aperfmperf: boolean;
    pfi: boolean;
    pa: boolean;
    avx2: boolean;
    bmi1: boolean;
    bmi2: boolean;
    hle: boolean;
    rtm: boolean;
    avx512f: boolean;
    avx512dq: boolean;
    avx512pf: boolean;
    avx512er: boolean;
    avx512cd: boolean;
    sha_ni: boolean;
    avx512bw: boolean;
    avx512vl: boolean;
    sgx: boolean;
    rdseed: boolean;
    adx: boolean;
    avx512vnni: boolean;
    avx512vbmi: boolean;
    avx512vbmi2: boolean;
}

export type CPUIDSingleCache = {
    size: number; //size in KB, Could be zero, if the CPU lacks cache. If the size cannot be determined, it will be -1
    associativity: number;
    cacheLineSize: number;
}

export type CPUIDCache = {
    L1I: CPUIDSingleCache
    L1D: CPUIDSingleCache
    L2: CPUIDSingleCache
    L3: CPUIDSingleCache
    L4: CPUIDSingleCache
}

export type CPUIDID = {
    family: number;
    model: number;
    stepping: number;
    extFamily: number;
    extModel: number;
}

export type CPUID = {
    vendorName: string;
    vendor: ECPUIDVendorStr;
    vendorNumber: number;
    brand: string;
    codeName: string;
    physicalCores: number;
    logicalCores: number;
    totalCores: number;
    clockSpeed: number; //in MHz

    features: CPUIDFeatures;
}

export type NativeModule = {
    getCPUID(): CPUID;
}