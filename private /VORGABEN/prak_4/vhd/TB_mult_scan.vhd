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
-- Mon Mar  4 09:49:47 CET 2013
--------------------------------------------------------------------------------

-- entity description

entity TB_mult_scan is
end entity;

-- architecture description

architecture testbench of TB_mult_scan is


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

