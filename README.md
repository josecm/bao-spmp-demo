This tutorial guides you on how to run the Bao Hypervisor on the Spike simulator with support for sspmp hypervisor extension. It supports both 32-bit and 64-bit configurations.

To start, clone this repo and cd into it:

```
git clone git@github.com:josecm/bao-spmp-demo.git
cd bao-spmp-demo
```

For the RV64 target download the **riscv64-unknown-elf-** toolchain from [SiFive's Freedom Tools](https://github.com/sifive/freedom-tools/releases) github repository.

For the RV32 target download the **riscv32-unknown-elf-** toolchain from [RISC-V GNU tooolchain](https://github.com/riscv-collab/riscv-gnu-toolchain/releases/tag/2023.12.20) github repository.

Install the toolchain. Then, set the **CROSS_COMPILE** environment variable with the reference toolchain prefix path:

```
export CROSS_COMPILE=/path/to/toolchain/install/dir/bin/your-toolchain-prefix-
```

Clone the Bao repo with the experimental spmp branch and the OpenSBI firmware:

```
git clone https://github.com/josecm/bao-hypervisor.git --recursive --branch exp/spmp
git clone https://github.com/riscv-software-src/opensbi.git
```

Setup the `ARCH_SUB` enviroment variable according to your target:

- For RV32, `export ARCH_SUB=riscv32`
- For RV64, `export ARCH_SUB=riscv64`

Build the baremetal guests used for the demo:

```
make -C bao-baremetal-guest PLATFORM=spike ARCH_SUB=$ARCH_SUB MEM_BASE=0x90000000
make -C bao-baremetal-guest2 PLATFORM=spike ARCH_SUB=$ARCH_SUB MEM_BASE=0xa0000000
```

Set the CONFIG enviroment variable to the config you wish to try out. There 
are two configs available:

- **spike-spmp-single** runs a single dualcore guest
- **spike-spmp-dual** runs two singlecore guests

For example:

```
export CONFIG=spike-spmp-single
```

If you change the config, repeat the steps from this point onward.

Build Bao for the target config:

```
make -C bao-hypervisor PLATFORM=spike-spmp ARCH_SUB=$ARCH_SUB CONFIG_REPO=$(realpath configs) CONFIG=$CONFIG
```

Build OpenSBI firmware with the embedded Bao binary:

```
make -C opensbi PLATFORM=generic FW_PAYLOAD_PATH=$(realpath bao-hypervisor/bin/spike-spmp/$CONFIG/bao.bin) -j12
```

Before you build the spike simulator with the hypevisor spmp support, make sure you apply the provided patch (*0001-vSPMP-Use-guest-access-fault-causes.patch*). Finally, run spike with the following command:

Setup the `SPIKE_ISA_STRING` enviroment variable according to your target:

- For RV32, `export SPIKE_ISA_STRING=rv32imafdch_sstc_zicntr_zihpm`
- For RV64, `export SPIKE_ISA_STRING=rv64imafdch_sstc_zicntr_zihpm`


```
/path/riscv-isa-sim/build/spike -p2 -m4096 --isa=$SPIKE_ISA_STRING --spmpregions=64  opensbi/build/platform/generic/firmware/fw_payload.elf
```
