# Copyright 2023 ETH Zurich and University of Bologna.
# Solderpad Hardware License, Version 0.51, see LICENSE for details.
# SPDX-License-Identifier: SHL-0.51
#
# Author: Michael Rogenmoser (michaero@iis.ee.ethz.ch)

transcript quietly

if {![info exists ::env(FI_CL_ROOT)]} { error "Define FI_CL_ROOT" }
set fi_cl_root $::env(FI_CL_ROOT)

if {![info exists ::env(FI_CLUSTER_INSTANCE)]} { error "Define FI_CLUSTER_INSTANCE" }
set fi_cluster_instance $::env(FI_CLUSTER_INSTANCE)

set fi_multi_bit_upset 0
if {[info exists ::env(FI_MULTI_BIT_UPSET)]} {
    set fi_multi_bit_upset $::env(FI_MULTI_BIT_UPSET)
}

echo "\[Fault Injection\] Info: FI_CL_ROOT set to $fi_cl_root"
echo "\[Fault Injection\] Info: FI_CLUSTER_INSTANCE set to $fi_cluster_instance"
echo "\[Fault Injection\] Info: FI_MULTI_BIT_UPSET set to $fi_multi_bit_upset"

set fi_cluster_dir [file join $fi_cl_root scripts fault_injection_utils]
set fi_common_dir  [file join $fi_cl_root fault_injection_sim scripts]

set verbosity            2
set log_injections       1
# Easy way to generate a variable seed
# set seed                 [clock seconds]
# Default value
set seed                 12345
set print_statistics     1

set inject_start_time 110584000000ps
set inject_stop_time 203880000000ps
set injection_clock "$fi_cluster_instance/clk_i"
set injection_clock_trigger 0
set fault_period 100
set rand_initial_injection_phase 0
# max_num set to 0 means until stop_time
set max_num_fault_inject 0
set signal_fault_duration 20ns
set register_fault_duration 0ns

set allow_multi_bit_upset $fi_multi_bit_upset
set use_bitwidth_as_weight 0
set check_core_output_modification 0
set check_core_next_state_modification 0
set reg_to_sig_ratio 1

source [file join $fi_cluster_dir pulp_extract_nets.tcl]

set inject_signals_netlist []
set inject_register_netlist []
set output_netlist []
set next_state_netlist []
set assertion_disable_list []

set inject_register_netlist [list {*}$inject_register_netlist {*}[get_memory_slice {0 16} {385 449}]]

set script_base_path $fi_common_dir
source [file join $fi_common_dir inject_fault.tcl]

