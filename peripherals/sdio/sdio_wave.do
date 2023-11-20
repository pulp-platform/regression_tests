onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/sdClk
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/cmd
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/dat
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/oeCmd
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/oeDat
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/cmdOut
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/datOut
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/transf_cnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/lastCMD
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/cardIdentificationState
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/CardTransferActive
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/BusWidth
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/InbuffStatus
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/BlockAddr
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/inCmd
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/cmdRead
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/cmdWrite
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcIn
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcEn
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcRst
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/CardStatus
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/RCA
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/OCR
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/CID
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/CSD
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/Busy
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcOut
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crc_c
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/CurrentState
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/DataCurrentState
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/outDelayCnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/flash_write_cnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/flash_blockwrite_cnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/state
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/next_state
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/dataState
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/next_datastate
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/ValidCmd
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/inValidCmd
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/response_S
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/response_CMD
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/responseType
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/block_cnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/wptr
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crc_ok
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/last_din
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcDat_rst
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/mult_read
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/mult_write
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcDat_en
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcDat_in
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcDat_out
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/stop
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/appendCrc
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/startUppCnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/q_start_bit
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/k
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/qCmd
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/crcCnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/add_wrong_cmd_crc
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/add_wrong_cmd_indx
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/add_wrong_data_crc
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/outdly_cnt
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/data_send_index
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/write_out_index
add wave -noupdate -expand -group sdcard_model /tb_pulp/genblk9/sdModelTB0/sdModel_file_desc
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sys_clk_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/periph_clk_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/rstn_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_data_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_addr_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_valid_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rwn_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_data_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_ready_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_startaddr_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_size_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_continuous_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_en_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_clr_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_en_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_pending_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_curr_addr_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_rx_bytes_left_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_startaddr_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_size_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_continuous_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_en_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_clr_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_en_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_pending_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_curr_addr_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/cfg_tx_bytes_left_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_tx_req_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_tx_gnt_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_tx_datasize_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_tx_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_tx_valid_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_tx_ready_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_rx_datasize_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_rx_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_rx_valid_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/data_rx_ready_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/eot_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/err_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sdclk_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sdcmd_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sdcmd_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sdcmd_oen_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sddata_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sddata_i
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/sddata_oen_o
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_tx
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_tx_valid
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_tx_ready
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_tx_dc
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_tx_dc_valid
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_tx_dc_ready
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_rx_dc
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_rx_dc_valid
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_rx_dc_ready
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_cmd_op
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_cmd_arg
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_cmd_rsp_type
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_rsp_data
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_en
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_rwn
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_quad
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_block_size
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_data_block_num
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_status
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_start
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_start_sync
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_clkdiv_en
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_clkdiv_data
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_clkdiv_valid
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_clkdiv_ack
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_clk_sdio
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_eot
add wave -noupdate -expand -group sdio /tb_pulp/i_dut/soc_domain_i/pulp_soc_i/soc_peripherals_i/i_udma/i_sdio/s_err
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {11580335732 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
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
configure wave -timelineunits ms
update
WaveRestoreZoom {0 ps} {17833255871 ps}
