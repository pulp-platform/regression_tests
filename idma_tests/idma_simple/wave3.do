onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/AddrWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/axi_narrow_req_i
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/axi_narrow_rsp_o
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/axi_wide_req_i
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/axi_wide_rsp_o
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/AxiNarrowIdWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/AxiWideIdWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/clk_i
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/MemorySimInit
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_addr
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_gnt
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_rdata
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_req
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_rvalid
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_strb
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_wdata
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/narrow_we
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/NarrowDataWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/NarrowExtraBF
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/NarrowStrbWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/NumNarrowReq
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/NumWideBanks
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/NumWideReq
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/rst_ni
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillNarrowReqEntry
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillNarrowReqRouted
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillNarrowRspEntry
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillNarrowRspRouted
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillReqBank
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillRspBank
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillWideReqEntry
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillWideReqRouted
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillWideReqSplit
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillWideRspEntry
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillWideRspRouted
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/SpillWideRspSplit
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_addr
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_gnt
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_rdata
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_req
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_rvalid
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_strb
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_wdata
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/wide_we
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/WideDataWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/WidePriorityWait
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/WideStrbWidth
add wave -noupdate -expand -group i_memory_island /pulp_cluster_tb/i_memory_island/WordsPerBank
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/AddrWidth}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/axi_read_req}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/axi_read_resp}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/axi_req_i}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/axi_resp_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/axi_write_req}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/axi_write_resp}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/AxiDataWidth}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/BufDepth}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/busy_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/clk_i}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/HideStrb}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/IdWidth}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_addr_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_atop_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_gnt_i}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_rdata_i}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_req_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_rvalid_i}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_strb_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_wdata_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/mem_we_o}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/MemDataWidth}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/NumMemPorts}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/OutFifoDepth}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/read_busy}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/rst_ni}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/test_i}
add wave -noupdate -expand -group i_narrow_conv {/pulp_cluster_tb/i_memory_island/gen_narrow_conv[0]/i_narrow_conv/write_busy}
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {114866000000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 267
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {154929600 ns}
