# Hello World!

This test could be a simple "hello world!" or a test to check whether we are able to boot Pulp loading the instructions to the L2 not from Jtag but from the flash memories (SPI and HYPER). 

## Boot test

To perform the boot test follow the procedure here from the pulp directory. First, in the rtl/tb/tb_pulp.sv file you have to:

 1. change the parameters LOAD_L2 and STIM_FROM respectively to "STANDALONE" and "HYPER_FLASH" (or "SPI_FLASH"),
 2. change UserPreload(0) to 1 for the SPI flash

Step number 1 will change the values in the register that Pulp reads to decide where to read the application instructions from. Step number 2 will allow the correct preload of the SPI Flash. As it is possible to see from tb_pulp.sv, SPI Flash and Hyper Flash can be loaded with desired values at compilation time by Questasim, by instantiating the desired files where needed.

Also, you will need the Verification IPs (VIPs). The READMEs in their folders (rtl/vip/*) contain the instructions to do it. Then, follow the instructions here above: 

### Compile the boot-code & build RTL

```
git clone git@github.com:regression_tests.git 

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

### Run the test

```
git clone git@github.com:pulp-platform/pulp-runtime.git -b boot_code_update

```

That branch of pulp-runtime has 2 key modifications to the rules/pulpos/default_rules.mk file: 

1. it does not overwrite the LOAD_L2 and STIM_FROM parameters 
2. when we execute the option 'run' in the test folder, pulp-runtime creates the .slm files to preload the flash.

Last operations to be done:

```

source pulp-runtime/configs/pulp.sh

cd regression_tests/hello/

export PULP_RISCV_GCC_TOOLCHAIN=*path to riscv gcc toolchain*/pulp-sdk-release/pkg/pulp_riscv_gcc/1.0.16

make clean all run gui=1

```


At this point you will be able to see that the selected memory contains the boot_code which is loaded in the L2 memory, where the instructions are stored.
