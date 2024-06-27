onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/clk_i
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/rst_ni
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/test_mode_i
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/ext_master_req_o
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/ext_master_resp_i
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/term_event_o
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/term_irq_o
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/term_event_pe_o
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/term_irq_pe_o
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/busy_o
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_wdata
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_add
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_wen
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_be
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_id
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_gnt
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_r_rdata
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_r_valid
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_r_opc
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/config_r_id
add wave -noupdate -group {iDMA Wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_req_from_dma[0]} -expand} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_req_from_dma
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_reorg_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_write_req
add wave -noupdate -group {iDMA Wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_req_muxed[0]} -expand} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_req_muxed
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_rsp_to_dma
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_reorg_rsp
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_write_rsp
add wave -noupdate -group {iDMA Wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_rsp_to_mux[0]} -expand {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_rsp_to_mux[0].r} -expand} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/obi_read_rsp_to_mux
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/soc_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/soc_rsp
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/dma_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/dma_rsp
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/dma_regs_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/dma_regs_rsp
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/stream_idx
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/twod_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/twod_req_queue
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/idma_req
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/idma_rsp
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/one_fe_valid
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/fe_valid
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/twod_queue_valid
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/be_valid
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/be_rsp_valid
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/fe_ready
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/twod_queue_ready
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/be_ready
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/be_rsp_ready
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/trans_complete
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/midend_busy
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/idma_busy
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/done_id
add wave -noupdate -group {iDMA Wrap} /pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/next_id
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/clk_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/rst_ni}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/req_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/add_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/wen_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/wdata_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/be_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/id_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/gnt_o}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_rdata_o}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_opc_o}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_id_o}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_valid_o}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/reg_req_o}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/reg_rsp_i}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_id_d}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_id_q}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_opc_d}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_opc_q}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_valid_d}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_valid_q}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_rdata_d}
add wave -noupdate -expand -group {dma ctrl 0} {/pulp_cluster_tb/cluster_i/genblk2/dmac_wrap_i/gen_core_regs[0]/i_pe_translate/r_rdata_q}
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {254164744503 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 252
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
configure wave -timelineunits ns
update
WaveRestoreZoom {255222984954 ps} {255848503895 ps}
