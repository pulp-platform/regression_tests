#Hello World!
This test could be a simple "hello world!" or a test to check whether we are able to use the hyperbus to load the program's instruction from the hyperflash to the L2, or not. To perform the second test it is necessary to use the [pulp-sdk]{https://github.com/pulp-platform/pulp-sdk}. 
## Boot test
To perform the boot test follow the procedure here above from the pulp directory:
`
git clone git@github.com:pulp-platform/pulp-sdk.git

cd pulp-sdk

git clone git@github.com:pulp-platform/regression_tests.git -b boot_test

cp regression_tests/hello/boot_code.cde ../sim/boot/

cd ..

./generate-scripts --rt-dpi --i2c-vip --flash-vip --i2s-vip --hyper-vip  --use-vip --verbose

`
Modify the tb_pulp.sv to have LOAD_L2="STANDALONE" and STIM_FROM="HYPER_FLASH"

` 
cd sim

make clean all

cd ../pulp-sdk

` 
Follow the README of pulp-sdk to correctly build the sdk.

`
cd regression_tests/hello/

make conf boot=rom all CONFIG_OPT=vsim/boot-mode=rom

python slm_hyper.py > build/pulp/slm_files/flash_stim_hyper.slm

make conf boot=rom all CONFIG_OPT=vsim/boot-mode=rom run gui=1

`


