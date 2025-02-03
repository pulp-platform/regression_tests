onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/next_id
add wave -noupdate -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/done_id
add wave -noupdate -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/idma_busy
add wave -noupdate -expand -subitemconfig {/pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_req.burst_req -expand /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_req.d_req -expand} /pulp_cluster_tb/cluster_i/inst_idma/dmac_wrap_i/twod_req
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {228277275232 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 277
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
WaveRestoreZoom {228226132825 ps} {228311503056 ps}
