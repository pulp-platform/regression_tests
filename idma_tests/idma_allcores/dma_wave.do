onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/clk_i
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/rst_ni
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/test_mode_i
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/ext_master_req_o
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/ext_master_resp_i
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/term_event_o
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/term_irq_o
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/term_event_pe_o
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/term_irq_pe_o
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/busy_o
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_wdata
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_add
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_req
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_wen
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_be
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_id
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_gnt
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_r_rdata
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_r_valid
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_r_opc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/config_r_id
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_req_from_dma
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_req_from_rrc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_req_from_dma
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_req_from_rrc
add wave -noupdate -expand -group {iDMA wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_dma[0]} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_dma
add wave -noupdate -expand -group {iDMA wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_rrc[0]} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_rrc[0].a} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_rrc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_req_muxed
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_rsp_to_dma
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_rsp_to_rrc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_rsp_to_dma
add wave -noupdate -expand -group {iDMA wrap} -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_rsp_to_rrc[0]} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_rsp_to_rrc[0].r} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_rsp_to_rrc
add wave -noupdate -expand -group {iDMA wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_dma[0]} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_dma[0].r} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_dma
add wave -noupdate -expand -group {iDMA wrap} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_rrc[0]} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_rrc[0].r} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_rrc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_rsp_to_mux
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/soc_req
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/soc_rsp
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/dma_req
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/dma_rsp
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/dma_regs_req
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/dma_regs_rsp
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/stream_idx
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_req
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_req_queue
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_req
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_rsp
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/one_fe_valid
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/fe_valid
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_queue_valid
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/be_valid
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/be_rsp_valid
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/fe_ready
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_queue_ready
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/be_ready
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/be_rsp_ready
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/trans_complete
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/midend_busy
add wave -noupdate -expand -group {iDMA wrap} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_busy
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/done_id
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/next_id
add wave -noupdate -expand -group {init strm1} -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_write_rsp.rsp_chan} -expand} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_write_rsp}
add wave -noupdate -expand -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_write_req}
add wave -noupdate -expand -group {init strm1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_rsp}
add wave -noupdate -expand -group {init strm1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_req}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/clk_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/rst_ni}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/testmode_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_read_req_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_read_rsp_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_read_req_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_read_rsp_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_read_req_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_read_rsp_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_write_req_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_write_rsp_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_write_req_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_write_rsp_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_req_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_valid_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_ready_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_rsp_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_valid_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_ready_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_valid_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_ready_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_valid_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_ready_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_req_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_valid_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_ready_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_req_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_valid_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_ready_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/dp_poison_i}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_chan_ready_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_chan_valid_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_busy_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_busy_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_busy_o}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_buffer_in_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_in_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_in_valid}
add wave -noupdate -expand -group {to OBI transport layer} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_valid_shifted}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_out_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_out_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_ready_shifted}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_buffer_in}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_in}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_in}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_shifted}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_shifted}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_chan_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_chan_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_chan_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_chan_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_chan_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_chan_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_rsp}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_rsp}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_rsp}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_ar_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_ar_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_ar_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_aw_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_aw_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_in_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_in_ready}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_protocol}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_valid}
add wave -noupdate -expand -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_ready}
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {226792000000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 252
configure wave -valuecolwidth 120
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
WaveRestoreZoom {226663267749 ps} {227016368236 ps}
