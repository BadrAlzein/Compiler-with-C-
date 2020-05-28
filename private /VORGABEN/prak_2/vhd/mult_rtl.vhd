library IEEE;
use IEEE.std_logic_1164.all; -- import std_logic types
use IEEE.numeric_std.all; -- for type conversion to_unsigned


-- import add/sub of std_logic_vector
--use IEEE.std_logic_arith.all; 
--use IEEE.std_logic_arith.unsigned;
--use IEEE.std_logic_unsigned.all;
--use ieee.std_logic_arith.all;
--library STD;
--use STD.textio.all;

--------------------------------------------------------------------------------
--!@file: mult_rtl.vhd
--!@brief: this is a simple multiplier description (generic) and iterativ
--!...
--
--!@author: Tobias Koal(TK)
--!@revision info :
-- last modification by tkoal(TK)
-- Mon Apr 13 14:27:49 CEST 2015
--------------------------------------------------------------------------------

-- entity description
-- generic (size:integer:=16; level:integer:=log(size));
entity mult_rtl is
port(
    a   : in   unsigned(19 downto 0);
		b   : in   unsigned(19 downto 0);
		clk : in STD_LOGIC;
		reset : in STD_LOGIC;
		z   : out  unsigned(39 downto 0)

);
end entity;

-- architecture description

architecture behave of mult_rtl is
  
  
--type levels_of_registers is array (4 downto 0) of unsigned (39 downto 0);
signal z_int :unsigned (39 downto 0);
signal a_int, b_int : unsigned (19 downto 0);
constant bit_number : unsigned := "00000000000000000000";
  
begin  
  
rtl: process(clk,reset) 
 begin

	if reset = '1' then 
		a_int<=bit_number;
		b_int<=bit_number;
		z_int <= bit_number * bit_number;
elsif rising_edge(clk)  then 
		a_int <= a;
		b_int <= b;
	z_int <= a_int * b_int;
	z<= z_int;
	
end if;
end process;
end behave;
