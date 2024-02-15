#include <config.h>

VM_IMAGE(baremetal_image, "../bao-baremetal-guest/build/spike/baremetal.bin");
VM_IMAGE(baremetal2_image, "../bao-baremetal-guest2/build/spike/baremetal.bin");

struct config config = {

    .vmlist_size = 2,
    .vmlist = {
        {
            .image = VM_IMAGE_BUILTIN(baremetal_image, 0x90000000),

            .entry = 0x90000000,

            .platform = {

                .cpu_num = 1,

                .region_num = 1,
                .regions = (struct vm_mem_region[]) {
                    {
                        .base = 0x90000000,
                        .size = 0x8000000,
                    },
                },

                .dev_num = 1,
                .devs = (struct vm_dev_region[]) {
                    {
                        .pa = 0x10000000,
                        .va = 0x10000000,
                        .size = 0x1000,
                    },
                },

                .arch = {
                    .irqc.plic = {
                        .base =0xc000000,
                    }
                }
            }
        },
        {
            .image = VM_IMAGE_BUILTIN(baremetal2_image, 0xa0000000),

            .entry = 0xa0000000,

            .platform = {

                .cpu_num = 1,

                .region_num = 1,
                .regions = (struct vm_mem_region[]) {
                    {
                        .base = 0xa0000000,
                        .size = 0x8000000,
                    },
                },

                .dev_num = 1,
                .devs = (struct vm_dev_region[]) {
                    {
                        .pa = 0x10000000,
                        .va = 0x10000000,
                        .size = 0x1000,
                    },
                },

                .arch = {
                    .irqc.plic = {
                        .base =0xc000000,
                    }
                }
            }
        }
    }
};
