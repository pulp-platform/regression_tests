# Regression tests
This repository contains a set of test, implemented in C, that are used as regression tests in our CI flow. Indeed, these tests are performed any time a push is done in the pulp-open's branches and are intended to verify that the basic functionalities of Pulp have not been compromised by the changes. Through time, this repo will be ppulated by more and more specific tests, granted that they work with the current pulp implementation.

## Tests
You can run tests either locally in a manual fashion or use your GitLab CI
instance. 

## Running software tests manually
Call the `./update-regression-tests` script in the pulp directory. This will populate this directory with all software tests.

To run the tests as they are the instructions are the following, from the pulp repo:
### To build Pulp
``
source setup/vsim.sh

./update-ips

./generate-scripts

cd sim

make all

``
### To run the tests
``
cd ..

source pulp-runtime/configs/pulp.sh

export PULP_RISCV_GCC_TOOLCHAIN= *path to riscv gcc toolchain*

make test-local-regressions
``

## Adding your own tests
You can add your own tests by putting them in a repository and adding them to
`update-tests` and `update-tests-gitlab` scripts in the top-level folder. Make
sure you define an appropriate `testset.cfg` that lists all the tests in your
repository and for each test provide another `testset.cfg` with instructions on
how to run it. Have a look at the already existing tests for an idea how such
files should look like.



