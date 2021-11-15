import { CPUID, NATIVE } from "./native";

export function getCPUID(): CPUID {
    return NATIVE.getCPUID();
}