library IEEE;
use IEEE.std_logic_1164.all; -- import std_logic types
--use IEEE.std_logic_arith.all; -- import add/sub of std_logic_vector
--use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all; -- for type conversion to_unsigned

--library STD;
--use STD.textio.all;

--------------------------------------------------------------------------------
--!@file: mult_algorithmic.vhd
--!@brief: this file contains an algorithmic description of a multiplier 
--!...
--
--!@author: Tobias Koal(TK)
--!@revision info :
-- last modification by tkoal(TK)
-- Mon Apr 13 14:26:25 CEST 2015
--------------------------------------------------------------------------------

-- entity description

entity mult_algorithmic is
port(
		a   : in   unsigned(19 downto 0);
		b   : in   unsigned(19 downto 0);
		z   : out  unsigned(39 downto 0)
);
end entity;

-- architecture description

architecture algorithmic_description of mult_algorithmic is


begin

	z<=a*b;

end algorithmic_description;

