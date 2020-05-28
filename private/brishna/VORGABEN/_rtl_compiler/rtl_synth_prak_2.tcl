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

write_hdl > synth_prak_2/mult_rtl_synth.v
# synthesize it to mapped 
#synthesize -to_mapped -effort high

exit
