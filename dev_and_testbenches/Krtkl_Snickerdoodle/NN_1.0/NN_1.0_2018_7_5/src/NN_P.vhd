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
   
   -- Constants
   constant K_NEURON_ONE             : std_logic_vector(1 downto 0) := "01";
   constant K_NEURON_MINUS_ONE       : std_logic_vector(1 downto 0) := "11";
   
   constant K_W : T_WEIGHTS_INT_ARRAY(0 to 67) := (
      -7491 ,76898 ,5719 ,12972 ,
      2141 ,-10322 ,141 ,4862 ,
      -392 ,4536 ,5544 ,5785 ,
      2552 ,1938 ,4 ,1441 ,
      298 ,-3133 ,55 ,-454 ,
      -5868 ,637 ,-26 ,-363 ,
      8290 ,688 ,-9690 ,-17210 ,
      10586 ,-45846 ,-3942 ,-19326 ,
      -1182 ,-8708 ,-2201 ,317 ,
      10892 ,4515 ,4244 ,6321 ,
      -1712 ,-2351 ,-7263 ,-2280 ,
      1948 ,4522 ,-4654 ,3692 ,
      6479 ,-1341 ,-213 ,15079 ,
      1117 ,1913 ,5486 ,100 ,
      -879 ,3889 ,563 ,-538 ,
      -7595 ,-302 ,3676 ,-21036 ,
      3194 ,4343 ,3887 ,-1189 ,
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