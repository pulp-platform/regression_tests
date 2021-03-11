# Boot code

This folder contains the source of the bootcode that we compile and load in the ROM of Pulp. To compile it look at the README in the hello test's folder.


## How to compile the boot-code & build RTL with the updated boot_rom

```
git clone git@github.com:regression_tests.git -b boot_code_update

cd boot_code

export PULP_RISCV_GCC_TOOLCHAIN=*path to riscv gcc toolchain*/pulp-sdk-release/pkg/pulp_riscv_gcc/1.0.16

export PULP_CC=riscv32-unknown-elf-gcc

export PULP_LD=riscv32-unknown-elf-gcc

make clean all 

cp boot_code.cde ../../sim/boot/

cd ../../

./generate-scripts --rt-dpi --i2c-vip --flash-vip --i2s-vip --hyper-vip  --use-vip --verbose

cd sim

make clean all

```
Now we have our Pulp with the right boot_code loaded in the ROM. We can compile the code and run it.
