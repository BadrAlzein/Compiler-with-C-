# sdc version info
set sdc_version 1.4

# specify current design
current_design mult_rtl

# create clock constraint period is in defined as ns
create_clock [get_ports {clk}] -name vclk -period 1.0


