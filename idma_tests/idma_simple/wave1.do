onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /pulp_cluster_tb/i_xbar/addr_map_i
add wave -noupdate -subitemconfig {{/pulp_cluster_tb/i_xbar/mst_reqs[1]} -expand {/pulp_cluster_tb/i_xbar/mst_reqs[1].aw} -expand} /pulp_cluster_tb/i_xbar/mst_reqs
add wave -noupdate /pulp_cluster_tb/i_xbar/mst_resps
add wave -noupdate /pulp_cluster_tb/i_xbar/slv_reqs
add wave -noupdate /pulp_cluster_tb/i_xbar/slv_resps
add wave -noupdate -expand /pulp_cluster_tb/axi_memreq
add wave -noupdate /pulp_cluster_tb/axi_memrsp
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {114866000000 ps} 0}
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
WaveRestoreZoom {114865949836 ps} {114866050164 ps}
