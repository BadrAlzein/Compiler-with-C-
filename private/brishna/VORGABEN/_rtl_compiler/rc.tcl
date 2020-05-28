# Cadence RTL Compiler (RC)
#   version v05.20-s025_1 (32-bit) built Apr 13 2006
#
# Run with the following arguments:
#   -logfile rc.log
#   -cmdfile rtl.tcl

# set lib path
set_attribute lib_search_path ../lib/lib/ 
# set lib
set_attribute library {NangateOpenCellLibrary_typical_conditional_ccs.lib}

# read hdl file
read_hdl -vhdl vhd/mult_rtl.vhd

# elaborate it
elaborate mult_rtl

# synthesize it
synthesize -to_generic

# read design constraint file (only clk constraint here!)
#read_sdc ../lib/sdc/mult.sdc

write_hdl > synth_prak_3/mult_rtl_synth.v
# synthesize it to mapped 
synthesize -to_mapped -effort high

# flatten desing (should be obsolete here!)
ungroup -flatten -all
# write verilog file in synth dir
write_hdl > synth_prak_3/mult_synth_logic_flatten.v

# write timing information of synthesized design
write_sdf -timescale ns -precision 3 -celltiming all > synth_prak_3/mult_synth_logic_flatten.sdf

# execute perl script to modify sdf file 
shell perl synth_prak_3/modify_sdf.pl -f synth_prak_3/mult_synth_logic_flatten.sdf > synth_prak_3/mult_synth_logic_flatten_ms.sdf

# exit rtl compiler
#exit
