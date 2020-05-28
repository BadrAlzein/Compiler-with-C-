library IEEE;
use IEEE.std_logic_1164.all; -- import std_logic types
--use IEEE.std_logic_arith.all; -- import add/sub of std_logic_vector
--use IEEE.std_logic_unsigned.all;
--use IEEE.std_logic_signed.all;
use IEEE.math_real.all; 
use IEEE.numeric_std.all; -- for type conversion to_unsigned

--library STD;
--use STD.textio.all;

--------------------------------------------------------------------------------
--!@file: TB_mult_algorithmic.vhd
--!@brief: testbench for the algorithmic multiplier description
--!...
--
--!@author: Tobias Koal(TK)
--!@revision info :
-- last modification by tkoal(TK)
-- Mon Apr 13 14:27:02 CEST 2015
--------------------------------------------------------------------------------

-- entity description

entity TB_mult_algorithmic is
end entity;

-- architecture description

architecture testbench of TB_mult_algorithmic is


	-- CONSTANTS (upper case only!)


	-- SIGNALS (lower case only!)

 component mult_algorithmic
  port(
  		a   : in   unsigned(19 downto 0);
  		b   : in   unsigned(19 downto 0);
  		z   : out  unsigned(39 downto 0)
  );
  end component;

--vhdl
	signal a: unsigned(19 downto 0);
	signal b: unsigned(19 downto 0);
	signal z: unsigned(39 downto 0) ;

--golden
	signal aGolden: unsigned(19 downto 0);
	signal bGolden: unsigned(19 downto 0);
	signal zGolden: unsigned(39 downto 0) ;

--constants
	constant MIN :  unsigned(19 downto 0) :=  "00000000000000000111" ;	
	constant LOOPLIMIT: integer := 10; -- testing limits
	constant SYNCTIME:TIME := 0.000 ps ; --small break to syncronise with golden device


begin
	-- this is your algorithmic multiplier description
	tb_component : entity work. mult_algorithmic(algorithmic_description)
	port map (
				  a => a,
                                   b => b,
                                   z => z
	);

--simulation 
 testBench: process
 begin
	for i in 0 to LOOPLIMIT loop
	for j in 0 to LOOPLIMIT loop
	wait for SYNCTIME; --sync with the golden device
	a <= MIN+i;
	b <=MIN+j; 
	wait for 12 ns;	
	end loop ; 
end loop ; 
end process;

--Golden Device
 goldendevice: process
 begin
	for i1 in 0 to LOOPLIMIT loop
	for j1 in 0 to LOOPLIMIT loop
	aGolden <= MIN+i1;
	bGolden <=MIN+j1; 
	wait for SYNCTIME; --sync with the golden device
	zGolden<=aGolden*bGolden;	
	wait for 12 ns;
	end loop ; 
end loop ; 
end process;

--Compare
 compare: process
 begin
	for i2 in 0 to LOOPLIMIT loop
	for j2 in 0 to LOOPLIMIT loop
	wait for  0.5 ps; --sync with the golden device
	if (z /= zGolden) then report "err" ;
	end if;
	
	wait for 12 ns;
	end loop ; 
end loop ; 
end process;


end testbench;

