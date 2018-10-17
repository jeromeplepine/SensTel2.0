-------------------------------------------------------------------------------
-- Title      : Neural_network
-- Project    : PFE NN
-------------------------------------------------------------------------------
-- File       : Neural_network.vhd
-- Author     : Vincent Cournoyer
-- Created    : 2018-04-03
-- Last update: 2018-04-03
-------------------------------------------------------------------------------
-- Description: Réseau de neurones artificiels à 3 entrée et 4 sorties
--              Contrôle le pitch ainsi que la vitesse (gear) du véhicule.
-------------------------------------------------------------------------------
-- Copyright (c) 2018 Vincent Cournoyer
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description

-------------------------------------------------------------------------------
library IEEE;
   use IEEE.STD_LOGIC_1164.ALL;
   use ieee.numeric_std.all;

library work;
   use work.NN_P.all;
   use work.ALL;
   
-------------------------------------------------------------------------------
entity Neural_network is
   port(
      i_clk      : in  std_logic;
      
      i_pitch    : in  std_logic_vector(11 downto 0);
      i_ws       : in  std_logic_vector(11 downto 0);
      i_rpm      : in  std_logic_vector(11 downto 0);
      i_data_rdy : in  std_logic;
      
      o_intr     : out std_logic;
      output     : out std_logic_vector(3 downto 0)
   );
end Neural_network;

-------------------------------------------------------------------------------
architecture Neural_network_A of Neural_network is
   component L1_DSP_MULT is
		port(
			CLK : in  std_logic;
			A   : in  std_logic_vector(11 downto 0);
			B   : in  std_logic_vector(17 downto 0);
			P   : out std_logic_vector(29 downto 0)
		);
	end component L1_DSP_MULT;
   
	component L1_DSP_MULT_ADD is
		port(
			CLK : in  std_logic;
			A   : in  std_logic_vector(11 downto 0);
			B   : in  std_logic_vector(17 downto 0);
			C   : in  std_logic_vector(29 downto 0);
			P   : out std_logic_vector(30 downto 0)
		);
	end component L1_DSP_MULT_ADD;
	
	component L1_DSP_MULT_ADD_BIAS is
		port(
			CLK : in  std_logic;
			A   : in  std_logic_vector(11 downto 0);
			B   : in  std_logic_vector(17 downto 0);
			C   : in  std_logic_vector(29 downto 0);
			P   : out std_logic_vector(30 downto 0)
		);
	end component L1_DSP_MULT_ADD_BIAS;
	
	component L1_DSP_ADD is
		port(
			CLK    : in  std_logic;
			C      : in  std_logic_vector(30 downto 0);
			CONCAT : in  std_logic_vector(30 downto 0);
			P      : out std_logic_vector(31 downto 0)
		);
	end component L1_DSP_ADD;
	
   component L2_DSP_INV_ADD is
      port(
         CLK : in  std_logic;
         A   : in  std_logic_vector(17 downto 0);
         C   : in  std_logic_vector(17 downto 0);
         P   : out std_logic_vector(18 downto 0)
      );
   end component L2_DSP_INV_ADD;
	
	component L2_DSP_FIRST_ADD is
		port(
			CLK : in  std_logic;
			A   : in  std_logic_vector(18 downto 0);
			C   : in  std_logic_vector(18 downto 0);
			P   : out std_logic_vector(19 downto 0)
		);
	end component L2_DSP_FIRST_ADD;
	
	component L2_DSP_SECOND_ADD is
		port(
			CLK : in  std_logic;
			A   : in  std_logic_vector(19 downto 0);
			C   : in  std_logic_vector(19 downto 0);
			P   : out std_logic_vector(20 downto 0)
		);
	end component L2_DSP_SECOND_ADD;
	
	component L2_DSP_THIRD_ADD is
		port(
			CLK : in  std_logic;
			A   : in  std_logic_vector(20 downto 0);
			C   : in  std_logic_vector(17 downto 0);
			P   : out std_logic_vector(21 downto 0)
		);
	end component L2_DSP_THIRD_ADD;
	
   signal intr_prop_reg1      : std_logic;
   signal intr_prop_reg2      : std_logic;
   signal intr_prop_reg3      : std_logic;
   signal intr_prop_reg4      : std_logic;
   signal intr_prop_reg5      : std_logic;
   signal intr_prop_reg6      : std_logic;
   signal intr_prop_reg7      : std_logic;
   signal intr_prop_reg8      : std_logic;
   signal intr_prop_reg9      : std_logic;
   signal intr_prop_reg10     : std_logic;
   signal intr_prop_reg11     : std_logic;
   signal intr_prop_reg12     : std_logic;
   signal intr_prop_reg13     : std_logic;
   signal intr_prop_reg14     : std_logic;
   signal intr_prop_reg15     : std_logic;
   signal intr_prop_reg16     : std_logic;
   signal intr_prop_reg17     : std_logic;
   
   signal lay1_reg_mult       : T_ARRAY_SLV_30(0 to K_NBR_NEURONS - 1);
   signal lay1_reg_first_add  : T_ARRAY_SLV_31(0 to K_NBR_NEURONS * 2 - 1);
   signal lay1_reg_second_add : T_ARRAY_SLV_32(0 to K_NBR_NEURONS - 1);
   
   signal lay2_reg_first_add  : T_ARRAY_SLV_19(0 to K_NBR_OUTPUT * 4 - 1);
   signal lay2_reg_second_add : T_ARRAY_SLV_20(0 to K_NBR_OUTPUT * 2 - 1);
   signal lay2_reg_third_add  : T_ARRAY_SLV_21(0 to K_NBR_OUTPUT - 1);
   signal lay2_reg_fourth_add : T_ARRAY_SLV_22(0 to K_NBR_OUTPUT - 1);
   
   signal neuron_mult_result  : T_ARRAY_SLV_18(0 to K_NBR_NEURONS * K_NBR_OUTPUT - 1);
   
   signal inv_output : std_logic_vector(3 downto 0);
begin
   PROC_INTR_PROP : process (i_clk)
   begin
      if (rising_edge(i_clk)) then
         intr_prop_reg1  <= i_data_rdy;
         intr_prop_reg2  <= intr_prop_reg1;
         intr_prop_reg3  <= intr_prop_reg2;
         intr_prop_reg4  <= intr_prop_reg3;
         intr_prop_reg5  <= intr_prop_reg4;
         intr_prop_reg6  <= intr_prop_reg5;
         intr_prop_reg7  <= intr_prop_reg6;
         intr_prop_reg8  <= intr_prop_reg7;
         intr_prop_reg9  <= intr_prop_reg8;
         intr_prop_reg10 <= intr_prop_reg9;
         intr_prop_reg11 <= intr_prop_reg10;
         intr_prop_reg12 <= intr_prop_reg11;
         intr_prop_reg13 <= intr_prop_reg12;
         intr_prop_reg14 <= intr_prop_reg13;
         intr_prop_reg15 <= intr_prop_reg14;
         intr_prop_reg16 <= intr_prop_reg15;
         intr_prop_reg17 <= intr_prop_reg16;
         o_intr          <= intr_prop_reg17;
      end if;
   end process;
   
   GEN_FIRST_LAYER: for i in 0 to K_NBR_NEURONS-1 generate
      INST_MULT: L1_DSP_MULT
      port map( 
         CLK => i_clk,
         A   => i_pitch,
         B   => K_W_SLV(i*4),
         P   => lay1_reg_mult(i)
      );
      
      INST_MULT_ADD: L1_DSP_MULT_ADD
      port map( 
         CLK => i_clk,
         A   => i_ws,
         B   => K_W_SLV(i*4+1),
         C   => lay1_reg_mult(i)(29) & lay1_reg_mult(i)(29 downto 1),
         P   => lay1_reg_first_add(i*2)
      );
      
      INST_MULT_ADD_BIAS: L1_DSP_MULT_ADD_BIAS
      port map( 
         CLK => i_clk,
         A   => i_rpm,
         B   => K_W_SLV(i*4+2),
         C   => K_B_SLV(i),
         P   => lay1_reg_first_add(i*2+1)
      );
      
      INST_ADD: L1_DSP_ADD
      port map( 
         CLK    => i_clk,
         C      => lay1_reg_first_add(i*2),
         CONCAT => lay1_reg_first_add(i*2+1),
         P      => lay1_reg_second_add(i)
      );
   end generate GEN_FIRST_LAYER;
   
   
   
   GEN_SECOND_LAYER: for i in 0 to K_NBR_OUTPUT-1 generate
      GEN_MULT_ADD: for j in 0 to K_NBR_NEURONS/2-1 generate
         PROC_FIRST_SIGN_INVERSION_j: process(i_clk)
            begin
               if(rising_edge(i_clk)) then
                  if(lay1_reg_second_add(2*j)(31) = '1') then
                     neuron_mult_result(8*i+2*j) <= std_logic_vector((not signed(K_W_SLV(32+9*i+2*j))) + 1);
                  else
                     neuron_mult_result(8*i+2*j) <= K_W_SLV(32+9*i+2*j);
                  end if;
                  
                  if(lay1_reg_second_add(2*j+1)(31) = '1') then
                     neuron_mult_result(8*i+2*j+1) <= std_logic_vector((not signed(K_W_SLV(32+9*i+2*j+1))) + 1);
                  else
                     neuron_mult_result(8*i+2*j+1) <= K_W_SLV(32+9*i+2*j+1);
                  end if;
               end if;
            end process;
      
         INST_INVERSION_ADD_j: L2_DSP_INV_ADD
         port map(
            CLK => i_clk,
            A   => neuron_mult_result(8*i+2*j),
            C   => neuron_mult_result(8*i+2*j+1),
            P   => lay2_reg_first_add(4*i+j)
         );
      end generate GEN_MULT_ADD;
      
      INST_FIRST_ADD_BOTTOM_NEURONS_i: L2_DSP_FIRST_ADD
      port map(
         CLK => i_clk,
         A   => lay2_reg_first_add(4*i),
         C   => lay2_reg_first_add(4*i+1),
         P   => lay2_reg_second_add(2*i)
      );
      
      INST_FIRST_ADD_TOP_NEURONS_i: L2_DSP_FIRST_ADD
      port map(
         CLK => i_clk,
         A   => lay2_reg_first_add(4*i+2),
         C   => lay2_reg_first_add(4*i+3),
         P   => lay2_reg_second_add(2*i+1)
      );
      
      INST_SECOND_ADD_i: L2_DSP_SECOND_ADD
      port map(
         CLK => i_clk,
         A   => lay2_reg_second_add(2*i),
         C   => lay2_reg_second_add(2*i+1),
         P   => lay2_reg_third_add(i)
      );
      
      INST_THIRD_ADD_i: L2_DSP_THIRD_ADD
      port map(
         CLK => i_clk,
         A   => lay2_reg_third_add(i),
         C   => K_B_SLV(8+i)(17 downto 0),
         P   => lay2_reg_fourth_add(i)
      );
      
      PROC_OUTPUT_ACTIVATION_i: process(i_clk)
      begin
         if(rising_edge(i_clk)) then
            if(lay2_reg_fourth_add(i)(21) = '0') then
               inv_output(i) <= '1';
            else
               inv_output(i) <= '0';
            end if;
         end if;
      end process;
   end generate GEN_SECOND_LAYER;
   
   output(0) <= inv_output(3);
   output(1) <= inv_output(2);
   output(2) <= inv_output(1);
   output(3) <= inv_output(0);
   
end;