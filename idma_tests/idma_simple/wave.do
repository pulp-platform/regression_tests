onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -subitemconfig {/pulp_cluster_tb/cluster_i/s_dma_master_req.ar {-childformat {{size -radix unsigned}} -expand} /pulp_cluster_tb/cluster_i/s_dma_master_req.ar.size {-radix unsigned}} /pulp_cluster_tb/cluster_i/s_dma_master_req
add wave -noupdate -subitemconfig {/pulp_cluster_tb/cluster_i/s_dma_master_resp.r -expand} /pulp_cluster_tb/cluster_i/s_dma_master_resp
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/clk}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/req}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/gnt}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_valid}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_ready}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/add}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/wen}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/data}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/be}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/user}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/id}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_data}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_user}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_id}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_opc}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/ecc}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_ecc}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/ereq}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/egnt}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_evalid}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/r_eready}
add wave -noupdate -group {s_hci_dma[0]} {/pulp_cluster_tb/cluster_i/s_hci_dma[0]/clk_assert}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/clk}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/req}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/gnt}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_valid}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_ready}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/add}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/wen}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/data}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/be}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/user}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/id}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_data}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_user}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_id}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_opc}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/ecc}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_ecc}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/ereq}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/egnt}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_evalid}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/r_eready}
add wave -noupdate -expand -group {s_hci_dma[1]} {/pulp_cluster_tb/cluster_i/s_hci_dma[1]/clk_assert}
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {262653051593 ps} 1} {{Cursor 2} {262655244483 ps} 0}
quietly wave cursor active 2
configure wave -namecolwidth 150
configure wave -valuecolwidth 567
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
WaveRestoreZoom {262620992344 ps} {262771194315 ps}
