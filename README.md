# node-libcpuid-neo
node-libcpuid-neo is a dead simple wrapper around [libcpuid](https://github.com/anrieff/libcpuid)

The main function is `.getCPUID()`, which returns a nice object of cpu capabilities (see Example)

This library is heavily inspired by [cpuid-node](https://github.com/terorie/cpuid-node), but attempts to fix some minor issue:
- There is a (hopefully correct) TypeScript typing for the returned object
- It uses `node-addon-api` (wrapper around `N-API` / `Node-API`) instead of `nan` to avoid nasty ABI issues, especially with electron

## Licensing
This library is MIT licensed, feel free to fork it or use it in commercial projects!

## Compatibility
The package is currently built for **Electron 14.1.1**

## Notes & Building
**This library is tailored to our needs and does not aim to be a universally compatible node package**, this repository is basically the public fork of our internal version. The main difference is that we DO NOT use `node-gyp` - You are responsible for building the package for your runtime!

The reason because we do not use `node-gyp` is that it doesn't nicely integrate with our workflow in other projects

Building the library for local development is easy:

`npm run dev-os-only` chooses the first configuration from `package.json` that matches the current OS and arch, builds it for the predefined runtime, currently **Electron 14.1.1**, and packs it

Building the library for acutal deployment is a bit tricker:

After much fiddling, we have decided to completely abandon crossbuilds and instead use native builds with Clang on all platforms. That works extremely well in practice, but requires you to have physical access to all device types / OSs for which you want to ship.
Internally we use a fleet of generic Linux machines which both build natively for Linux and run Windows VMs and a bunch of Intel and ARM MacMinis...

## Example
```
> addon = require('./build/linux/x64/electron/97/addon.node')
{ getCPUID: [Function (anonymous)] }
> addon.getCPUID()
{
  vendorName: 'AuthenticAMD',
  vendor: 'amd',
  vendorNumber: 1,
  brand: 'AMD Ryzen Threadripper 3960X 24-Core Processor ',
  codeName: 'Threadripper (Castle Peak)',
  physicalCores: 24,
  logicalCores: 48,
  totalCores: 48,
  clockSpeed: 2195,
  features: {
    fpu: true,
    vme: true,
    de: true,
    pse: true,
    tsc: true,
    msr: true,
    pae: true,
    mce: true,
    cx8: true,
    apic: true,
    mtrr: true,
    sep: true,
    pge: true,
    mca: true,
    cmov: true,
    pat: true,
    pse36: true,
    pn: false,
    clflush: true,
    dts: false,
    acpi: false,
    mmx: true,
    fxsr: true,
    sse: true,
    sse2: true,
    ss: false,
    ht: true,
    tm: false,
    ia64: false,
    pbe: false,
    pni: true,
    pclmul: true,
    dts64: false,
    monitor: true,
    ds_cpl: false,
    vmx: false,
    smx: false,
    est: false,
    tm2: false,
    ssse3: true,
    cid: false,
    cx16: true,
    xtpr: false,
    pdcm: false,
    dca: false,
    sse4_1: true,
    sse4_2: true,
    syscall: true,
    xd: false,
    x2apic: false,
    movbe: true,
    popcnt: true,
    aes: true,
    xsave: true,
    osxsave: true,
    avx: true,
    mmxext: true,
    '3dnow': false,
    '3dnowext': false,
    nx: true,
    fxsr_opt: true,
    rdtscp: true,
    lm: true,
    lahf_lm: true,
    cmp_legacy: true,
    svm: true,
    sse4a: true,
    misalignsse: true,
    abm: true,
    '3dnowprefetch': true,
    osvw: true,
    ibs: true,
    sse5: false,
    skinit: true,
    wdt: true,
    ts: true,
    fid: false,
    vid: false,
    ttp: true,
    tm_amd: true,
    stc: false,
    '100mhzsteps': false,
    hwpstate: true,
    constant_tsc: true,
    xop: false,
    fma3: true,
    fma4: false,
    tbm: false,
    f16c: true,
    rdrand: true,
    cpb: true,
    aperfmperf: true,
    pfi: false,
    pa: false,
    avx2: true,
    bmi1: true,
    bmi2: true,
    hle: false,
    rtm: false,
    avx512f: false,
    avx512dq: false,
    avx512pf: false,
    avx512er: false,
    avx512cd: false,
    sha_ni: true,
    avx512bw: false,
    avx512vl: false,
    sgx: false,
    rdseed: true,
    adx: true,
    avx512vnni: false,
    avx512vbmi: false,
    avx512vbmi2: false
  },
  cache: {
    L1I: { size: 32, associativity: 8, cacheLineSize: 64 },
    L1D: { size: 32, associativity: 8, cacheLineSize: 64 },
    L2: { size: 512, associativity: 8, cacheLineSize: 64 },
    L3: { size: 131072, associativity: 16, cacheLineSize: 64 },
    L4: { size: -1, associativity: -1, cacheLineSize: -1 }
  },
  id: { family: 15, model: 1, stepping: 0, extFamily: 23, extModel: 49 }
}
```