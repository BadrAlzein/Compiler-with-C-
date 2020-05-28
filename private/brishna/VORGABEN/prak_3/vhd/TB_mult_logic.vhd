library IEEE;
use IEEE.std_logic_1164.all; 
use IEEE.math_real.all; 
use IEEE.numeric_std.all; 

--------------------------------------------------------------------------------
--!@file: TB_mult_rtl.vhd
--!@brief: testbench for the rtl description of the multiplier
--!...
--
--!@author: Tobias Koal(TK)
--!@revision info :
-- last modification by tkoal(TK)
-- Mon Apr 13 14:29:16 CEST 2015
--------------------------------------------------------------------------------

-- entity description

entity TB_mult_logic is
end entity;

-- architecture description

architecture testbench of TB_mult_logic is


	-- CONSTANTS (upper case only!)

	-- SIGNALS (lower case only!)

begin

	-- put your code here!
	tb_component : entity work.mult_rtl(behave)
	port map (
		  );


	-- create a stimulus process here!

	-- create golden device

	-- observe functionality

	-- create a clk driver here!

	-- create a reset driver here!

end testbench;

