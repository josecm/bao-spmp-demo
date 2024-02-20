Clone this repo and cd into it:

```
git clone git@github.com:josecm/bao-spmp-demo.git
cd bao-spmp-demo
```

Download the **riscv64-unknown-elf-** toolchain from [SiFive's Freedom Tools](https://github.com/sifive/freedom-tools/releases) github repository.

Install the toolchain. Then, set the **CROSS_COMPILE** environment variable with the reference toolchain prefix path:

```
export CROSS_COMPILE=/path/to/toolchain/install/dir/bin/your-toolchain-prefix-
```

Clone the Bao repo with the experimental spmp branch and the OpenSBI firmware:

```
git clone https://github.com/josecm/bao-hypervisor.git --recursive --branch exp/spmp
git clone https://github.com/riscv-software-src/opensbi.git
```

Build the baremetal guests used for the demo:

```
make -C bao-baremetal-guest PLATFORM=spike MEM_BASE=0x90000000
make -C bao-baremetal-guest2 PLATFORM=spike MEM_BASE=0xa0000000
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
make -C bao-hypervisor PLATFORM=spike-spmp CONFIG_REPO=$(realpath configs) CONFIG=$CONFIG
```

Build OpenSBI firmware with the embedded Bao binary:

```
make -C opensbi PLATFORM=generic FW_PAYLOAD_PATH=$(realpath bao-hypervisor/bin/spike-spmp/$CONFIG/bao.bin) -j12
```

Before you build the spike simulator with the hypevisor spmp support, make sure you apply the provided patch (*0001-vSPMP-Use-guest-access-fault-causes.patch*). Finally, run spike with the following command:

```
/path/riscv-isa-sim/build/spike -p2 -m4096 --isa=rv64imafdch_sstc_zicntr_zihpm --pmpregions=64  opensbi/build/platform/generic/firmware/fw_payload.elf
```
