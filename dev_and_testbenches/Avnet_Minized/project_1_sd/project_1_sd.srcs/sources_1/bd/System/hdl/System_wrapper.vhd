--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
--Date        : Sun Apr 15 18:14:05 2018
--Host        : LAPTOP-GDRKMBCO running 64-bit major release  (build 9200)
--Command     : generate_target System_wrapper.bd
--Design      : System_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity System_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    SDIO_1_buspow : out STD_LOGIC;
    SDIO_1_busvolt : out STD_LOGIC_VECTOR ( 2 downto 0 );
    SDIO_1_cdn : in STD_LOGIC;
    SDIO_1_led : out STD_LOGIC;
    SDIO_1_wp : in STD_LOGIC;
    sdio_1_cmd_io : inout STD_LOGIC;
    sdio_1_data_io : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    sdio_clk : out STD_LOGIC
  );
end System_wrapper;

architecture STRUCTURE of System_wrapper is
  component System is
  port (
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    SDIO_1_cmd_o : out STD_LOGIC;
    SDIO_1_cmd_i : in STD_LOGIC;
    SDIO_1_cmd_t : out STD_LOGIC;
    SDIO_1_data_i : in STD_LOGIC_VECTOR ( 3 downto 0 );
    SDIO_1_data_o : out STD_LOGIC_VECTOR ( 3 downto 0 );
    SDIO_1_data_t : out STD_LOGIC_VECTOR ( 3 downto 0 );
    SDIO_1_led : out STD_LOGIC;
    SDIO_1_cdn : in STD_LOGIC;
    SDIO_1_wp : in STD_LOGIC;
    SDIO_1_buspow : out STD_LOGIC;
    SDIO_1_busvolt : out STD_LOGIC_VECTOR ( 2 downto 0 );
    sdio_clk : out STD_LOGIC
  );
  end component System;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal sdio_1_cmd_i : STD_LOGIC;
  signal sdio_1_cmd_o : STD_LOGIC;
  signal sdio_1_cmd_t : STD_LOGIC;
  signal sdio_1_data_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal sdio_1_data_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal sdio_1_data_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal sdio_1_data_i_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal sdio_1_data_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal sdio_1_data_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal sdio_1_data_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal sdio_1_data_io_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal sdio_1_data_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal sdio_1_data_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal sdio_1_data_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal sdio_1_data_o_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal sdio_1_data_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal sdio_1_data_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal sdio_1_data_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal sdio_1_data_t_3 : STD_LOGIC_VECTOR ( 3 to 3 );
begin
System_i: component System
     port map (
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(1 downto 0) => DDR_dm(1 downto 0),
      DDR_dq(15 downto 0) => DDR_dq(15 downto 0),
      DDR_dqs_n(1 downto 0) => DDR_dqs_n(1 downto 0),
      DDR_dqs_p(1 downto 0) => DDR_dqs_p(1 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(31 downto 0) => FIXED_IO_mio(31 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      SDIO_1_buspow => SDIO_1_buspow,
      SDIO_1_busvolt(2 downto 0) => SDIO_1_busvolt(2 downto 0),
      SDIO_1_cdn => SDIO_1_cdn,
      SDIO_1_cmd_i => sdio_1_cmd_i,
      SDIO_1_cmd_o => sdio_1_cmd_o,
      SDIO_1_cmd_t => sdio_1_cmd_t,
      SDIO_1_data_i(3) => sdio_1_data_i_3(3),
      SDIO_1_data_i(2) => sdio_1_data_i_2(2),
      SDIO_1_data_i(1) => sdio_1_data_i_1(1),
      SDIO_1_data_i(0) => sdio_1_data_i_0(0),
      SDIO_1_data_o(3) => sdio_1_data_o_3(3),
      SDIO_1_data_o(2) => sdio_1_data_o_2(2),
      SDIO_1_data_o(1) => sdio_1_data_o_1(1),
      SDIO_1_data_o(0) => sdio_1_data_o_0(0),
      SDIO_1_data_t(3) => sdio_1_data_t_3(3),
      SDIO_1_data_t(2) => sdio_1_data_t_2(2),
      SDIO_1_data_t(1) => sdio_1_data_t_1(1),
      SDIO_1_data_t(0) => sdio_1_data_t_0(0),
      SDIO_1_led => SDIO_1_led,
      SDIO_1_wp => SDIO_1_wp,
      sdio_clk => sdio_clk
    );
sdio_1_cmd_iobuf: component IOBUF
     port map (
      I => sdio_1_cmd_o,
      IO => sdio_1_cmd_io,
      O => sdio_1_cmd_i,
      T => sdio_1_cmd_t
    );
sdio_1_data_iobuf_0: component IOBUF
     port map (
      I => sdio_1_data_o_0(0),
      IO => sdio_1_data_io(0),
      O => sdio_1_data_i_0(0),
      T => sdio_1_data_t_0(0)
    );
sdio_1_data_iobuf_1: component IOBUF
     port map (
      I => sdio_1_data_o_1(1),
      IO => sdio_1_data_io(1),
      O => sdio_1_data_i_1(1),
      T => sdio_1_data_t_1(1)
    );
sdio_1_data_iobuf_2: component IOBUF
     port map (
      I => sdio_1_data_o_2(2),
      IO => sdio_1_data_io(2),
      O => sdio_1_data_i_2(2),
      T => sdio_1_data_t_2(2)
    );
sdio_1_data_iobuf_3: component IOBUF
     port map (
      I => sdio_1_data_o_3(3),
      IO => sdio_1_data_io(3),
      O => sdio_1_data_i_3(3),
      T => sdio_1_data_t_3(3)
    );
end STRUCTURE;
