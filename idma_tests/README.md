## IDMA Tests

This folder contains basic tests for the iDMA IP. 
Currently, the following are supported:
- **1D transfers**
- **2D transfers**
- **3D transfers**

To launch each test:
1. Move into the related folder.
2. Launch the following:
    1. `make stimuli` : this will generate the randomized stimuli for the test. The randomized stimuli consist of transfer sizes, number of transfers to be executed, n-dimensional strides, etc ...
    2. `make all` : this will compile the C code. Few choices are available:
        - **Single Core mode**: no flags are needed. All transfers specified in the stimuli will be executed by Core 0 only.
        - **Sequential Multi-Core Mode**: specify **MULTI_CORE_S=1** in the command line when compiling the code. In this mode, all cores will execute the transfers specified in the stimuli in a sequential manner.
        - **Parallel Multi-Core Mode**: specify **MULTI_CORE_P=1** in the command line when compiling the code. In this mode, all cores will execute the transfers specified in the stimulin in a parallel manner.
    3. `make run` : this will launch the simulation in bash mode (use gui=1 for Modelsim gui).
4. All transfers will be executed in the three different directions that are currently supported: **L1->L2, L2->L1, L1->L1**.
