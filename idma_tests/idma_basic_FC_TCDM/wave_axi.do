onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_addr
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_burst
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_cache
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_id
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_len
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_lock
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_prot
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_qos
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_ready
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_region
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_size
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_user
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/ar_valid
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_addr
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_atop
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_burst
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_cache
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_id
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_len
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_lock
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_prot
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_qos
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_ready
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_region
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_size
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_user
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/aw_valid
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/AXI_ADDR_WIDTH
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/AXI_DATA_WIDTH
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/AXI_ID_WIDTH
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/AXI_STRB_WIDTH
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/AXI_USER_WIDTH
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/b_id
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/b_ready
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/b_resp
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/b_user
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/b_valid
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_data
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_id
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_last
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_ready
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_resp
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_user
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/r_valid
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/w_data
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/w_last
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/w_ready
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/w_strb
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/w_user
add wave -noupdate -expand -group dma_slave /pulp_cluster_tb/dma_slave/w_valid
add wave -noupdate /pulp_cluster_tb/dma_demux_slv_req
add wave -noupdate -expand /pulp_cluster_tb/dma_demux_slv_resp
add wave -noupdate -expand -subitemconfig {/pulp_cluster_tb/dma_demux_wide2narrow_req.w -expand} /pulp_cluster_tb/dma_demux_wide2narrow_req
add wave -noupdate /pulp_cluster_tb/dma_demux_wide2narrow_resp
add wave -noupdate -expand /pulp_cluster_tb/dma_demux_memisl_req
add wave -noupdate /pulp_cluster_tb/dma_demux_memisl_resp
add wave -noupdate /pulp_cluster_tb/ar_wide_sel
add wave -noupdate /pulp_cluster_tb/aw_wide_sel
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {241927636364 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 237
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
WaveRestoreZoom {0 ps} {369947677273 ps}
