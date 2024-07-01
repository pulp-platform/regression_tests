onerror {resume}
quietly WaveActivateNextPane {} 0
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
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_dma
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_req_from_rrc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_req_muxed
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_rsp_to_dma
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_read_rsp_to_rrc
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_rsp_to_dma
add wave -noupdate -expand -group {iDMA wrap} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_reorg_rsp_to_rrc
add wave -noupdate -expand -group {iDMA wrap} -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_dma[0]} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_dma
add wave -noupdate -expand -group {iDMA wrap} -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_rrc[0]} -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/obi_write_rsp_to_rrc
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
add wave -noupdate -group {init strm1} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/clk_i
add wave -noupdate -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_write_rsp}
add wave -noupdate -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_write_req}
add wave -noupdate -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_req.req_valid}
add wave -noupdate -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_rsp.req_ready}
add wave -noupdate -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_rsp.rsp_valid}
add wave -noupdate -group {init strm1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_req.rsp_ready}
add wave -noupdate -group {init strm1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_rsp}
add wave -noupdate -group {init strm1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/init_read_req}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/clk_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/rst_ni}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/testmode_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_read_req_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_read_rsp_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_read_req_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_read_rsp_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_read_req_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_read_rsp_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_write_req_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_write_rsp_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_write_req_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_write_rsp_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_req_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_valid_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_ready_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_rsp_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_valid_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_ready_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_valid_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_ready_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_valid_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_ready_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_req_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_valid_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_ready_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_req_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_valid_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_ready_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/dp_poison_i}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_chan_ready_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_chan_valid_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_busy_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_busy_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_busy_o}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_buffer_in_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_in_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_in_valid}
add wave -noupdate -group {to OBI transport layer} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_valid_shifted}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_out_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_out_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_ready_shifted}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_buffer_in}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_in}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_in}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_shifted}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_shifted}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_chan_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_chan_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_chan_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_chan_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_chan_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_chan_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_rsp}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_rsp}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_rsp}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_ar_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_ar_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_ar_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_aw_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_aw_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_in_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_in_ready}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_protocol}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_valid}
add wave -noupdate -group {to OBI transport layer} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/rst_ni}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/testmode_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/idma_req_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/req_valid_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/req_ready_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/idma_rsp_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/rsp_valid_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/rsp_ready_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/idma_eh_req_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/eh_req_valid_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/eh_req_ready_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/axi_read_req_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/axi_read_rsp_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/init_read_req_o}
add wave -noupdate -group {backend 1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/init_read_rsp_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/obi_read_req_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/obi_read_rsp_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/init_write_req_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/init_write_rsp_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/obi_write_req_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/obi_write_rsp_i}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/busy_o}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/dp_busy}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/dp_poison}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_req}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_req}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_meta_req_tagged}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_meta_req_tagged}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_last_burst}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_last_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_super_last}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_req_in_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_req_in_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_req_out_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_req_out_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_req_out}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_req_out_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_req_out_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_req_out}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_rsp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_rsp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_rsp_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_rsp_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_dp_rsp_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/w_dp_rsp_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/ar_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/ar_ready_dp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/aw_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/aw_ready_dp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/aw_valid_dp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/ar_valid_dp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/aw_req_dp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/ar_req_dp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/legalizer_flush}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/legalizer_kill}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/is_length_zero}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/req_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/idma_rsp}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/rsp_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/rsp_ready}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_chan_valid}
add wave -noupdate -group {backend 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/r_chan_ready}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/clk_i}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/rst_ni}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/req_i}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/valid_i}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/ready_o}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_req_o}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_valid_o}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_ready_i}
add wave -noupdate -group {legalizer 1} -expand -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_req_o.w_dp_req} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_req_o.aw_req} -expand} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_req_o}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_valid_o}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_ready_i}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/flush_i}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/kill_i}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_busy_o}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_busy_o}
add wave -noupdate -group {legalizer 1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_tf_d}
add wave -noupdate -group {legalizer 1} -childformat {{{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_tf_q.length} -radix unsigned}} -subitemconfig {{/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_tf_q.length} {-height 16 -radix unsigned}} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_tf_q}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_tf_d}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_tf_q}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/opt_tf_d}
add wave -noupdate -group {legalizer 1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/opt_tf_q}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_tf_ena}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_tf_ena}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_page_num_bytes_to_pb}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_num_bytes_to_pb}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_page_num_bytes_to_pb}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_num_bytes_to_pb}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/c_num_bytes_to_pb}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_num_bytes_possible}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_num_bytes}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_addr_offset}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/r_done}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_num_bytes_possible}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_num_bytes}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_addr_offset}
add wave -noupdate -group {legalizer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/w_done}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/addr_i}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/not_bursting_i}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/reduce_len_i}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/max_llen_i}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/num_bytes_to_pb_o}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/page_addr_width}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/page_size}
add wave -noupdate -group {rd page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_read_page_splitter/page_offset}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/addr_i}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/not_bursting_i}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/reduce_len_i}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/max_llen_i}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/num_bytes_to_pb_o}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/page_addr_width}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/page_size}
add wave -noupdate -group {wr page splitter 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/gen_hw_legalizer/i_idma_legalizer/i_write_page_splitter/page_offset}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/clk_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/rst_ni}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/testmode_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_read_req_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_read_rsp_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_read_req_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_read_rsp_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_read_req_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_read_rsp_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_write_req_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_write_rsp_i}
add wave -noupdate -group {transport layer 1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_write_req_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_write_rsp_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_req_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_valid_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_ready_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_rsp_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_valid_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_ready_i}
add wave -noupdate -group {transport layer 1} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_valid_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_ready_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_valid_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_ready_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_req_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_valid_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/ar_ready_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_req_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_valid_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/aw_ready_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/dp_poison_i}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_chan_ready_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_chan_valid_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/r_dp_busy_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_busy_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_busy_o}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_buffer_in_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_in_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_in_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_valid_shifted}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_out_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_out_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_ready_shifted}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_buffer_in}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_buffer_in}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_buffer_in}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_in_shifted}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/buffer_out_shifted}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_chan_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_chan_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_chan_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_chan_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_chan_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_chan_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_r_dp_rsp}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_r_dp_rsp}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_r_dp_rsp}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/axi_ar_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_ar_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_ar_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_w_dp_rsp}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_w_dp_rsp}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/init_aw_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/obi_aw_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_req_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_dp_rsp_mux}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_in_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_in_ready}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_protocol}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_valid}
add wave -noupdate -group {transport layer 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/w_resp_fifo_out_ready}
add wave -noupdate -group {strm1 init read} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_dp_req_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_dp_valid_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_dp_ready_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_dp_rsp_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_dp_valid_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_dp_ready_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/read_meta_req_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/read_meta_valid_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/read_meta_ready_o}
add wave -noupdate -group {strm1 init read} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/read_req_o}
add wave -noupdate -group {strm1 init read} -expand {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/read_rsp_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_chan_ready_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/r_chan_valid_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/buffer_in_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/buffer_in_valid_o}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/buffer_in_ready_i}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/read_aligned_in_mask}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/mask_in}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/in_valid}
add wave -noupdate -group {strm1 init read} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/i_idma_transport_layer/i_idma_init_read/in_ready}
TreeUpdate [SetDefaultTree]
quietly WaveActivateNextPane
add wave -noupdate -color Gold {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/gen_streams[1]/gen_cpy_in/i_idma_backend_r_axi_rw_init_rw_obi/clk_i}
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {1574893420000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 252
configure wave -valuecolwidth 224
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
WaveRestoreZoom {248010100 ns} {3541692100 ns}
