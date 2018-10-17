--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
--Date        : Sat May  5 21:15:17 2018
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
    CAN_0_rx : in STD_LOGIC;
    CAN_0_tx : out STD_LOGIC;
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    SDIO1_CLK : out STD_LOGIC;
    SDIO_1_buspow : out STD_LOGIC;
    SDIO_1_busvolt : out STD_LOGIC_VECTOR ( 2 downto 0 );
    SDIO_1_cdn : in STD_LOGIC;
    SDIO_1_led : out STD_LOGIC;
    SDIO_1_wp : in STD_LOGIC;
    UART_1_rxd : in STD_LOGIC;
    UART_1_txd : out STD_LOGIC;
    capturetrig0 : in STD_LOGIC;
    capturetrig0_1 : in STD_LOGIC;
    capturetrig1 : in STD_LOGIC;
    capturetrig1_1 : in STD_LOGIC;
    gpio_0_tri_io : inout STD_LOGIC_VECTOR ( 6 downto 0 );
    iic_0_scl_io : inout STD_LOGIC;
    iic_0_sda_io : inout STD_LOGIC;
    iic_1_scl_io : inout STD_LOGIC;
    iic_1_sda_io : inout STD_LOGIC;
    sdio_1_cmd_io : inout STD_LOGIC;
    sdio_1_data_io : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    spi_0_io0_io : inout STD_LOGIC;
    spi_0_io1_io : inout STD_LOGIC;
    spi_0_sck_io : inout STD_LOGIC;
    spi_0_ss1_o : out STD_LOGIC;
    spi_0_ss2_o : out STD_LOGIC;
    spi_0_ss_o : out STD_LOGIC;
    spi_0_ss_t : out STD_LOGIC
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
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    GPIO_0_tri_i : in STD_LOGIC_VECTOR ( 6 downto 0 );
    GPIO_0_tri_o : out STD_LOGIC_VECTOR ( 6 downto 0 );
    GPIO_0_tri_t : out STD_LOGIC_VECTOR ( 6 downto 0 );
    IIC_0_sda_i : in STD_LOGIC;
    IIC_0_sda_o : out STD_LOGIC;
    IIC_0_sda_t : out STD_LOGIC;
    IIC_0_scl_i : in STD_LOGIC;
    IIC_0_scl_o : out STD_LOGIC;
    IIC_0_scl_t : out STD_LOGIC;
    IIC_1_sda_i : in STD_LOGIC;
    IIC_1_sda_o : out STD_LOGIC;
    IIC_1_sda_t : out STD_LOGIC;
    IIC_1_scl_i : in STD_LOGIC;
    IIC_1_scl_o : out STD_LOGIC;
    IIC_1_scl_t : out STD_LOGIC;
    SPI_0_sck_i : in STD_LOGIC;
    SPI_0_sck_o : out STD_LOGIC;
    SPI_0_sck_t : out STD_LOGIC;
    SPI_0_io0_i : in STD_LOGIC;
    SPI_0_io0_o : out STD_LOGIC;
    SPI_0_io0_t : out STD_LOGIC;
    SPI_0_io1_i : in STD_LOGIC;
    SPI_0_io1_o : out STD_LOGIC;
    SPI_0_io1_t : out STD_LOGIC;
    SPI_0_ss_o : out STD_LOGIC;
    SPI_0_ss1_o : out STD_LOGIC;
    SPI_0_ss2_o : out STD_LOGIC;
    SPI_0_ss_t : out STD_LOGIC;
    CAN_0_tx : out STD_LOGIC;
    CAN_0_rx : in STD_LOGIC;
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
    UART_1_txd : out STD_LOGIC;
    UART_1_rxd : in STD_LOGIC;
    capturetrig0 : in STD_LOGIC;
    capturetrig1 : in STD_LOGIC;
    capturetrig0_1 : in STD_LOGIC;
    capturetrig1_1 : in STD_LOGIC;
    SDIO1_CLK : out STD_LOGIC
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
  signal gpio_0_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_0_tri_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_0_tri_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_0_tri_i_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_0_tri_i_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal gpio_0_tri_i_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal gpio_0_tri_i_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal gpio_0_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_0_tri_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_0_tri_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_0_tri_io_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_0_tri_io_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal gpio_0_tri_io_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal gpio_0_tri_io_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal gpio_0_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_0_tri_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_0_tri_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_0_tri_o_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_0_tri_o_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal gpio_0_tri_o_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal gpio_0_tri_o_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal gpio_0_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_0_tri_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_0_tri_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_0_tri_t_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_0_tri_t_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal gpio_0_tri_t_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal gpio_0_tri_t_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal iic_0_scl_i : STD_LOGIC;
  signal iic_0_scl_o : STD_LOGIC;
  signal iic_0_scl_t : STD_LOGIC;
  signal iic_0_sda_i : STD_LOGIC;
  signal iic_0_sda_o : STD_LOGIC;
  signal iic_0_sda_t : STD_LOGIC;
  signal iic_1_scl_i : STD_LOGIC;
  signal iic_1_scl_o : STD_LOGIC;
  signal iic_1_scl_t : STD_LOGIC;
  signal iic_1_sda_i : STD_LOGIC;
  signal iic_1_sda_o : STD_LOGIC;
  signal iic_1_sda_t : STD_LOGIC;
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
  signal spi_0_io0_i : STD_LOGIC;
  signal spi_0_io0_o : STD_LOGIC;
  signal spi_0_io0_t : STD_LOGIC;
  signal spi_0_io1_i : STD_LOGIC;
  signal spi_0_io1_o : STD_LOGIC;
  signal spi_0_io1_t : STD_LOGIC;
  signal spi_0_sck_i : STD_LOGIC;
  signal spi_0_sck_o : STD_LOGIC;
  signal spi_0_sck_t : STD_LOGIC;
begin
System_i: component System
     port map (
      CAN_0_rx => CAN_0_rx,
      CAN_0_tx => CAN_0_tx,
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      GPIO_0_tri_i(6) => gpio_0_tri_i_6(6),
      GPIO_0_tri_i(5) => gpio_0_tri_i_5(5),
      GPIO_0_tri_i(4) => gpio_0_tri_i_4(4),
      GPIO_0_tri_i(3) => gpio_0_tri_i_3(3),
      GPIO_0_tri_i(2) => gpio_0_tri_i_2(2),
      GPIO_0_tri_i(1) => gpio_0_tri_i_1(1),
      GPIO_0_tri_i(0) => gpio_0_tri_i_0(0),
      GPIO_0_tri_o(6) => gpio_0_tri_o_6(6),
      GPIO_0_tri_o(5) => gpio_0_tri_o_5(5),
      GPIO_0_tri_o(4) => gpio_0_tri_o_4(4),
      GPIO_0_tri_o(3) => gpio_0_tri_o_3(3),
      GPIO_0_tri_o(2) => gpio_0_tri_o_2(2),
      GPIO_0_tri_o(1) => gpio_0_tri_o_1(1),
      GPIO_0_tri_o(0) => gpio_0_tri_o_0(0),
      GPIO_0_tri_t(6) => gpio_0_tri_t_6(6),
      GPIO_0_tri_t(5) => gpio_0_tri_t_5(5),
      GPIO_0_tri_t(4) => gpio_0_tri_t_4(4),
      GPIO_0_tri_t(3) => gpio_0_tri_t_3(3),
      GPIO_0_tri_t(2) => gpio_0_tri_t_2(2),
      GPIO_0_tri_t(1) => gpio_0_tri_t_1(1),
      GPIO_0_tri_t(0) => gpio_0_tri_t_0(0),
      IIC_0_scl_i => iic_0_scl_i,
      IIC_0_scl_o => iic_0_scl_o,
      IIC_0_scl_t => iic_0_scl_t,
      IIC_0_sda_i => iic_0_sda_i,
      IIC_0_sda_o => iic_0_sda_o,
      IIC_0_sda_t => iic_0_sda_t,
      IIC_1_scl_i => iic_1_scl_i,
      IIC_1_scl_o => iic_1_scl_o,
      IIC_1_scl_t => iic_1_scl_t,
      IIC_1_sda_i => iic_1_sda_i,
      IIC_1_sda_o => iic_1_sda_o,
      IIC_1_sda_t => iic_1_sda_t,
      SDIO1_CLK => SDIO1_CLK,
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
      SPI_0_io0_i => spi_0_io0_i,
      SPI_0_io0_o => spi_0_io0_o,
      SPI_0_io0_t => spi_0_io0_t,
      SPI_0_io1_i => spi_0_io1_i,
      SPI_0_io1_o => spi_0_io1_o,
      SPI_0_io1_t => spi_0_io1_t,
      SPI_0_sck_i => spi_0_sck_i,
      SPI_0_sck_o => spi_0_sck_o,
      SPI_0_sck_t => spi_0_sck_t,
      SPI_0_ss1_o => spi_0_ss1_o,
      SPI_0_ss2_o => spi_0_ss2_o,
      SPI_0_ss_o => spi_0_ss_o,
      SPI_0_ss_t => spi_0_ss_t,
      UART_1_rxd => UART_1_rxd,
      UART_1_txd => UART_1_txd,
      capturetrig0 => capturetrig0,
      capturetrig0_1 => capturetrig0_1,
      capturetrig1 => capturetrig1,
      capturetrig1_1 => capturetrig1_1
    );
gpio_0_tri_iobuf_0: component IOBUF
     port map (
      I => gpio_0_tri_o_0(0),
      IO => gpio_0_tri_io(0),
      O => gpio_0_tri_i_0(0),
      T => gpio_0_tri_t_0(0)
    );
gpio_0_tri_iobuf_1: component IOBUF
     port map (
      I => gpio_0_tri_o_1(1),
      IO => gpio_0_tri_io(1),
      O => gpio_0_tri_i_1(1),
      T => gpio_0_tri_t_1(1)
    );
gpio_0_tri_iobuf_2: component IOBUF
     port map (
      I => gpio_0_tri_o_2(2),
      IO => gpio_0_tri_io(2),
      O => gpio_0_tri_i_2(2),
      T => gpio_0_tri_t_2(2)
    );
gpio_0_tri_iobuf_3: component IOBUF
     port map (
      I => gpio_0_tri_o_3(3),
      IO => gpio_0_tri_io(3),
      O => gpio_0_tri_i_3(3),
      T => gpio_0_tri_t_3(3)
    );
gpio_0_tri_iobuf_4: component IOBUF
     port map (
      I => gpio_0_tri_o_4(4),
      IO => gpio_0_tri_io(4),
      O => gpio_0_tri_i_4(4),
      T => gpio_0_tri_t_4(4)
    );
gpio_0_tri_iobuf_5: component IOBUF
     port map (
      I => gpio_0_tri_o_5(5),
      IO => gpio_0_tri_io(5),
      O => gpio_0_tri_i_5(5),
      T => gpio_0_tri_t_5(5)
    );
gpio_0_tri_iobuf_6: component IOBUF
     port map (
      I => gpio_0_tri_o_6(6),
      IO => gpio_0_tri_io(6),
      O => gpio_0_tri_i_6(6),
      T => gpio_0_tri_t_6(6)
    );
iic_0_scl_iobuf: component IOBUF
     port map (
      I => iic_0_scl_o,
      IO => iic_0_scl_io,
      O => iic_0_scl_i,
      T => iic_0_scl_t
    );
iic_0_sda_iobuf: component IOBUF
     port map (
      I => iic_0_sda_o,
      IO => iic_0_sda_io,
      O => iic_0_sda_i,
      T => iic_0_sda_t
    );
iic_1_scl_iobuf: component IOBUF
     port map (
      I => iic_1_scl_o,
      IO => iic_1_scl_io,
      O => iic_1_scl_i,
      T => iic_1_scl_t
    );
iic_1_sda_iobuf: component IOBUF
     port map (
      I => iic_1_sda_o,
      IO => iic_1_sda_io,
      O => iic_1_sda_i,
      T => iic_1_sda_t
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
spi_0_io0_iobuf: component IOBUF
     port map (
      I => spi_0_io0_o,
      IO => spi_0_io0_io,
      O => spi_0_io0_i,
      T => spi_0_io0_t
    );
spi_0_io1_iobuf: component IOBUF
     port map (
      I => spi_0_io1_o,
      IO => spi_0_io1_io,
      O => spi_0_io1_i,
      T => spi_0_io1_t
    );
spi_0_sck_iobuf: component IOBUF
     port map (
      I => spi_0_sck_o,
      IO => spi_0_sck_io,
      O => spi_0_sck_i,
      T => spi_0_sck_t
    );
end STRUCTURE;
