Unicorn Engine port for UEFI firmware
=====================================

This fork of the [Unicorn Engine](https://github.com/unicorn-engine/unicorn) brings support
for building Unicorn-based applications and drivers in the UEFI firmware environment.
This was developed as part of [MultiArchUefiPkg](https://github.com/intel/MultiArchUefiPkg).

This repo is intended to be temporary, as part of upstreaming activities. Our intention
is to merge the UEFI support and assorted fixes into the main project repository.

See [README.md](README.md) for the original Unicorn Engine README.

Building
--------

Currently the supported targets are AARCH64 UEFI and RISCV64 UEFI.

You need the TianoCore UEFI EDK2 environment set up. Here's an example for
how the some of the Unicorn sample apps could be built in an EDK2 environment
targeting RISCV64:
```
. edksetup.sh
export GCC5_RISCV64_PREFIX=riscv64-linux-gnu-

build -a RISCV64 -t GCC5 -p unicorn/efi/UnicornPkg.dsc -b DEBUG
```

You get UnicornSampleX86, UnicornSampleArm64 and UnicornSampleRV.
The latter shows how it's possible to link against multiple target
emulation libraries.

[MultiArchUefiPkg](https://github.com/intel/MultiArchUefiPkg) itself is a great example
of how to use Unicorn with UEFI.

Note: There is an AArch64 issue where due to LTO the build of UnicornSampleArm64
takes forever and then bombs out complaining about missing __ashrti3.
This remains to be investigated, and a w/a is to modify the EDK2 Conf/tools_def.txt
to avoid LTO.
