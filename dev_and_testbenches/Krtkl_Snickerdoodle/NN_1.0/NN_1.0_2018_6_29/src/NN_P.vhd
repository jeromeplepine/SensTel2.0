-------------------------------------------------------------------------------
-- Title      : Neural_network package
-- Project    : PFE NN
-------------------------------------------------------------------------------
-- File       : NN_P.vhd
-- Author     : Vincent Cournoyer
-- Created    : 2018-04-03
-- Last update: 2018-04-03
-------------------------------------------------------------------------------
-- Description: Package pour le réseau de neurones
-------------------------------------------------------------------------------
-- Copyright (c) 2018 Vincent Cournoyer
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description

-------------------------------------------------------------------------------
library IEEE;
   use IEEE.std_logic_1164.all;
   use ieee.numeric_std.all;
   use ieee.std_logic_misc.all;
   
-------------------------------------------------------------------------------

package NN_P is
   constant K_NBR_INPUT   : integer := 3;
   constant K_NBR_NEURONS : integer := 8;
   constant K_NBR_OUTPUT  : integer := 4;
   
   -- Type declarations
   type T_ARRAY_SLV_18 is array (integer range <>) of std_logic_vector(17 downto 0);
   type T_ARRAY_SLV_19 is array (integer range <>) of std_logic_vector(18 downto 0);
   type T_ARRAY_SLV_20 is array (integer range <>) of std_logic_vector(19 downto 0);
   type T_ARRAY_SLV_21 is array (integer range <>) of std_logic_vector(20 downto 0);
   type T_ARRAY_SLV_22 is array (integer range <>) of std_logic_vector(21 downto 0);
   
   type T_ARRAY_SLV_30 is array (integer range <>) of std_logic_vector(29 downto 0);
   type T_ARRAY_SLV_31 is array (integer range <>) of std_logic_vector(30 downto 0);
   type T_ARRAY_SLV_32 is array (integer range <>) of std_logic_vector(31 downto 0);
   
   type T_WEIGHTS_INT_ARRAY is array (integer range <>) of integer;
   type T_WEIGHTS_SLV_ARRAY is array (integer range <>) of std_logic_vector(17 downto 0);
   
   type T_BIAS_ARRAY     is array (integer range <>) of integer;
   type T_BIAS_SLV_ARRAY is array (integer range <>) of std_logic_vector(29 downto 0);
   
   -- Function declarations
   function weight_to_slv(int_array : T_WEIGHTS_INT_ARRAY) return T_WEIGHTS_SLV_ARRAY;
   function bias_to_slv(int_array : T_BIAS_ARRAY) return T_BIAS_SLV_ARRAY;
   
   constant K_W : T_WEIGHTS_INT_ARRAY(0 to 67) := (
      --first layer
      1891, 7571, -100, -7859,
      707, -21727, 695, 368,
      33459, -41069, 564, -2,
      -13181, -56289, -2610, -4243,
      -3610, -14344, 258, 703,
      996, 5186, -1613, 83,
      -1546, -28835, 1018, 256,
      181, -2529, 46, -1884,
      
      --second layer
      851, -108, -3204, 3561, 3860, 1125, -131, 480, -2612,
      5506, 163, 1809, 4346, 1685, 1896, 208, 2203, -2522,
      -6484, 531, 1787, 2148, 914, 64, 646, 1133, -985,
      717, -628, -1536, 149, -4835, 1333, -1033, -868, 1481,
      OTHERS => 0);
   
   constant K_W_SLV  : T_WEIGHTS_SLV_ARRAY(67 downto 0);
   
   constant K_B : T_BIAS_ARRAY(0 to 11) := (
      K_W(3), K_W(7), K_W(11), K_W(15),
      K_W(19), K_W(23), K_W(27), K_W(31),
      K_W(40), K_W(49),  K_W(58), K_W(67),
      OTHERS => 0);
   
   constant K_B_SLV  : T_BIAS_SLV_ARRAY(11 downto 0);
end NN_P;

-------------------------------------------------------------------------------
package body NN_P is
   
   -- Convert weight array to std_logic_vector array
   function weight_to_slv(int_array : T_WEIGHTS_INT_ARRAY) return T_WEIGHTS_SLV_ARRAY is
      variable slv_array : T_WEIGHTS_SLV_ARRAY(int_array'length - 1 downto 0);
   begin
      for i in 0 to slv_array'length-1 loop
         slv_array(i) := std_logic_vector(to_signed(int_array(i), slv_array(i)'length));
      end loop;
      return slv_array;
   end function;
   
   -- Convert bias array to std_logic_vector array
   function bias_to_slv(int_array : T_BIAS_ARRAY) return T_BIAS_SLV_ARRAY is
      variable slv_array : T_BIAS_SLV_ARRAY(int_array'length - 1 downto 0);
   begin
      for i in 0 to slv_array'length-1 loop
         slv_array(i) := std_logic_vector(to_signed(int_array(i), slv_array(i)'length));
      end loop;
      return slv_array;
   end function;
   
   constant K_W_SLV  : T_WEIGHTS_SLV_ARRAY(0 to 67) := weight_to_slv(K_W);
   
   constant K_B_SLV  : T_BIAS_SLV_ARRAY(0 to 11) := bias_to_slv(K_B);
   
end NN_P;