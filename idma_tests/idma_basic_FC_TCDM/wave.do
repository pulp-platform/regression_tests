onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -group {both streams} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/next_id
add wave -noupdate -group {both streams} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/done_id
add wave -noupdate -group {both streams} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_busy
add wave -noupdate -group {both streams} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/trans_complete
add wave -noupdate -group {both streams} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/midend_busy
add wave -noupdate -group {both streams} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/stream_idx[0]}
add wave -noupdate -group {both streams} -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/fe_valid
add wave -noupdate -group {both streams} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/one_fe_valid
add wave -noupdate -expand -group {Stream 0} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/next_id[0]}
add wave -noupdate -expand -group {Stream 0} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/done_id[0]}
add wave -noupdate -expand -group {Stream 0} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_busy[0]}
add wave -noupdate -expand -group {Stream 0} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/trans_complete[0]}
add wave -noupdate -expand -group {Stream 0} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/midend_busy[0]}
add wave -noupdate -expand -group {Stream 0} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/fe_valid[0]}
add wave -noupdate -expand -group {Stream 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/next_id[1]}
add wave -noupdate -expand -group {Stream 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/done_id[1]}
add wave -noupdate -expand -group {Stream 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_busy[1]}
add wave -noupdate -expand -group {Stream 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/trans_complete[1]}
add wave -noupdate -expand -group {Stream 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/midend_busy[1]}
add wave -noupdate -expand -group {Stream 1} {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/fe_valid[1]}
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {465052499193 ps} 0}
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
configure wave -timelineunits ps
update
WaveRestoreZoom {142806706479 ps} {489319307995 ps}
