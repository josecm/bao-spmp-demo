CROSS_COMPILE ?= arm-none-eabi-
ARCH_GENERIC_FLAGS+=-DAARCH32

ARM_PROFILE?=armv8-a+simd
ARCH_SUB_GENERIC_FLAGS:=-mfpu=auto -mfloat-abi=hard
