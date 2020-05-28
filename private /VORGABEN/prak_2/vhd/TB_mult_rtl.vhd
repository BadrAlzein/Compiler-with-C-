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
-- Mon Apr 13 14:28:21 CEST 2015
--------------------------------------------------------------------------------

-- entity description

entity TB_mult_rtl is
end entity;

-- architecture description

architecture testbench of TB_mult_rtl is


	-- CONSTANTS (upper case only!)

	-- SIGNALS (lower case only!)
	
	component mult_algorithmic
  port(
  		a   : in   unsigned(19 downto 0);
  		
  		b   : in   unsigned(19 downto 0);
  		
  		z   : out  unsigned(39 downto 0);
  		
  		clk : in   STD_LOGIC;
  		
		reset  : in std_logic
  );
  end component;
  
  -- Constants to check for the Multilications
constant number :  unsigned(19 downto 0) :=  "00000000000000001111" ;
    -- the int range that i want to check the multiplication with it
constant rangeofLoop: integer := 20; 

--VHDL

signal a: unsigned(19 downto 0);
signal b: unsigned(19 downto 0);
signal clk,reset : std_logic:='0'; -- init values only in tb
signal z: unsigned(39 downto 0);


--GOLDEN DEVICE

 
	signal goldenDevice_z: unsigned(39 downto 0) ;
	--signal clk,reset : std_logic:='0'; -- init values only in tb
	
	
	-----------------------------not sure if needed---------------
	----------------------------------------------------------------------
		
-------------------------------------------------------------------------------
begin

	-- put your code here!
	tb_component : entity work.mult_rtl(behave)
	port map (
	   a, b,
	  clk , reset,z  );
--generate clock


	-- create a stimulus process here!
	 stimulus: process
 begin
	for input_a in 0 to rangeofLoop loop
	for input_b in 0 to rangeofLoop loop
  a <= number+input_a;
	b <= number+input_b; 
	wait for 16 ns;	
	end loop ; 
end loop ; 
wait;
end process;

	-- create golden device
goldendevice: process
 begin
	goldenDevice_z<=a*b;	
	wait for 0.5 ns;
	
end process;

	-- observe functionality
	compare: process
 begin
	
	
	if (z /= goldenDevice_z) then report "error" ;
	end if;
	
	wait for 12 ns;

end process;

	-- create a clk driver here!

  clk <= not clk after 1 ns; -- generate init value for clock

	-- create a reset driver here!
	reset<= '1' , '0' after 0.5 ns;

end testbench;
