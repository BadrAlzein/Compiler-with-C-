open visualizer -display browser design data

set scan type mux_scan
analyze control signals -auto
setup scan identification full_scan
//add clocks 0 clk
//add clocks 0 reset
set test logic -clock on -reset on
//add mapping definition DFFR_X1 -scan_model SDFFR_X1
//add mapping definition DFFR_X2 -scan_model SDFFR_X2


set system mode dft
setup scan identification full_scan
run
report statistics

insert test logic 

write netlist _scan/mult_rtl_tech_mapped_scanable.v -replace
write atpg setup scanable -replace


