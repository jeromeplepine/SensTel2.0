-- (c) Copyright 1995-2018 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:user:NN:1.0
-- IP Revision: 4

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY System_NN_1_0 IS
  PORT (
    irq : OUT STD_LOGIC;
    s_axi_intr_awaddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
    s_axi_intr_awprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
    s_axi_intr_awvalid : IN STD_LOGIC;
    s_axi_intr_awready : OUT STD_LOGIC;
    s_axi_intr_wdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axi_intr_wstrb : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    s_axi_intr_wvalid : IN STD_LOGIC;
    s_axi_intr_wready : OUT STD_LOGIC;
    s_axi_intr_bresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s_axi_intr_bvalid : OUT STD_LOGIC;
    s_axi_intr_bready : IN STD_LOGIC;
    s_axi_intr_araddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
    s_axi_intr_arprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
    s_axi_intr_arvalid : IN STD_LOGIC;
    s_axi_intr_arready : OUT STD_LOGIC;
    s_axi_intr_rdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axi_intr_rresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s_axi_intr_rvalid : OUT STD_LOGIC;
    s_axi_intr_rready : IN STD_LOGIC;
    s_axi_intr_aclk : IN STD_LOGIC;
    s_axi_intr_aresetn : IN STD_LOGIC;
    s0_axi_awaddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
    s0_axi_awprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
    s0_axi_awvalid : IN STD_LOGIC;
    s0_axi_awready : OUT STD_LOGIC;
    s0_axi_wdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    s0_axi_wstrb : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    s0_axi_wvalid : IN STD_LOGIC;
    s0_axi_wready : OUT STD_LOGIC;
    s0_axi_bresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s0_axi_bvalid : OUT STD_LOGIC;
    s0_axi_bready : IN STD_LOGIC;
    s0_axi_araddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
    s0_axi_arprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
    s0_axi_arvalid : IN STD_LOGIC;
    s0_axi_arready : OUT STD_LOGIC;
    s0_axi_rdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    s0_axi_rresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s0_axi_rvalid : OUT STD_LOGIC;
    s0_axi_rready : IN STD_LOGIC;
    s0_axi_aclk : IN STD_LOGIC;
    s0_axi_aresetn : IN STD_LOGIC
  );
END System_NN_1_0;

ARCHITECTURE System_NN_1_0_arch OF System_NN_1_0 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF System_NN_1_0_arch: ARCHITECTURE IS "yes";
  COMPONENT NN_v1_0 IS
    GENERIC (
      C_S_AXI_INTR_DATA_WIDTH : INTEGER; -- Width of S_AXI data bus
      C_S_AXI_INTR_ADDR_WIDTH : INTEGER; -- Width of S_AXI address bus
      C_NUM_OF_INTR : INTEGER; -- Number of Interrupts
      C_INTR_SENSITIVITY : STD_LOGIC_VECTOR; -- Each bit corresponds to Sensitivity of interrupt :  0 - EDGE, 1 - LEVEL
      C_INTR_ACTIVE_STATE : STD_LOGIC_VECTOR; -- Each bit corresponds to Sub-type of INTR: [0 - FALLING_EDGE, 1 - RISING_EDGE : if C_INTR_SENSITIVITY is EDGE(0)] and [ 0 - LEVEL_LOW, 1 - LEVEL_LOW : if C_INTR_SENSITIVITY is LEVEL(1) ]
      C_IRQ_SENSITIVITY : INTEGER; -- Sensitivity of IRQ: 0 - EDGE, 1 - LEVEL
      C_IRQ_ACTIVE_STATE : INTEGER; -- Sub-type of IRQ: [0 - FALLING_EDGE, 1 - RISING_EDGE : if C_IRQ_SENSITIVITY is EDGE(0)] and [ 0 - LEVEL_LOW, 1 - LEVEL_LOW : if C_IRQ_SENSITIVITY is LEVEL(1) ]
      C_S0_AXI_DATA_WIDTH : INTEGER; -- Width of S_AXI data bus
      C_S0_AXI_ADDR_WIDTH : INTEGER -- Width of S_AXI address bus
    );
    PORT (
      irq : OUT STD_LOGIC;
      s_axi_intr_awaddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
      s_axi_intr_awprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
      s_axi_intr_awvalid : IN STD_LOGIC;
      s_axi_intr_awready : OUT STD_LOGIC;
      s_axi_intr_wdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      s_axi_intr_wstrb : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      s_axi_intr_wvalid : IN STD_LOGIC;
      s_axi_intr_wready : OUT STD_LOGIC;
      s_axi_intr_bresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s_axi_intr_bvalid : OUT STD_LOGIC;
      s_axi_intr_bready : IN STD_LOGIC;
      s_axi_intr_araddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
      s_axi_intr_arprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
      s_axi_intr_arvalid : IN STD_LOGIC;
      s_axi_intr_arready : OUT STD_LOGIC;
      s_axi_intr_rdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      s_axi_intr_rresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s_axi_intr_rvalid : OUT STD_LOGIC;
      s_axi_intr_rready : IN STD_LOGIC;
      s_axi_intr_aclk : IN STD_LOGIC;
      s_axi_intr_aresetn : IN STD_LOGIC;
      s0_axi_awaddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
      s0_axi_awprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
      s0_axi_awvalid : IN STD_LOGIC;
      s0_axi_awready : OUT STD_LOGIC;
      s0_axi_wdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      s0_axi_wstrb : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      s0_axi_wvalid : IN STD_LOGIC;
      s0_axi_wready : OUT STD_LOGIC;
      s0_axi_bresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s0_axi_bvalid : OUT STD_LOGIC;
      s0_axi_bready : IN STD_LOGIC;
      s0_axi_araddr : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
      s0_axi_arprot : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
      s0_axi_arvalid : IN STD_LOGIC;
      s0_axi_arready : OUT STD_LOGIC;
      s0_axi_rdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      s0_axi_rresp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s0_axi_rvalid : OUT STD_LOGIC;
      s0_axi_rready : IN STD_LOGIC;
      s0_axi_aclk : IN STD_LOGIC;
      s0_axi_aresetn : IN STD_LOGIC
    );
  END COMPONENT NN_v1_0;
  ATTRIBUTE X_CORE_INFO : STRING;
  ATTRIBUTE X_CORE_INFO OF System_NN_1_0_arch: ARCHITECTURE IS "NN_v1_0,Vivado 2017.4";
  ATTRIBUTE CHECK_LICENSE_TYPE : STRING;
  ATTRIBUTE CHECK_LICENSE_TYPE OF System_NN_1_0_arch : ARCHITECTURE IS "System_NN_1_0,NN_v1_0,{}";
  ATTRIBUTE CORE_GENERATION_INFO : STRING;
  ATTRIBUTE CORE_GENERATION_INFO OF System_NN_1_0_arch: ARCHITECTURE IS "System_NN_1_0,NN_v1_0,{x_ipProduct=Vivado 2017.4,x_ipVendor=xilinx.com,x_ipLibrary=user,x_ipName=NN,x_ipVersion=1.0,x_ipCoreRevision=4,x_ipLanguage=VHDL,x_ipSimLanguage=MIXED,C_S_AXI_INTR_DATA_WIDTH=32,C_S_AXI_INTR_ADDR_WIDTH=5,C_NUM_OF_INTR=1,C_INTR_SENSITIVITY=0xFFFFFFFF,C_INTR_ACTIVE_STATE=0xFFFFFFFF,C_IRQ_SENSITIVITY=1,C_IRQ_ACTIVE_STATE=1,C_S0_AXI_DATA_WIDTH=32,C_S0_AXI_ADDR_WIDTH=5}";
  ATTRIBUTE X_INTERFACE_INFO : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER OF s0_axi_aresetn: SIGNAL IS "XIL_INTERFACENAME S0_AXI_RST, POLARITY ACTIVE_LOW";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_aresetn: SIGNAL IS "xilinx.com:signal:reset:1.0 S0_AXI_RST RST";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s0_axi_aclk: SIGNAL IS "XIL_INTERFACENAME S0_AXI_CLK, ASSOCIATED_BUSIF S0_AXI, ASSOCIATED_RESET s0_axi_aresetn, FREQ_HZ 49999950, PHASE 0.000, CLK_DOMAIN System_processing_system7_0_0_FCLK_CLK0";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_aclk: SIGNAL IS "xilinx.com:signal:clock:1.0 S0_AXI_CLK CLK";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_rready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_rvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_rresp: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_rdata: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_arready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_arvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI ARVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_arprot: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI ARPROT";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_araddr: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_bready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_bvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_bresp: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_wready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_wvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI WVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_wstrb: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_wdata: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_awready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_awvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI AWVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_awprot: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI AWPROT";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s0_axi_awaddr: SIGNAL IS "XIL_INTERFACENAME S0_AXI, WIZ_DATA_WIDTH 32, WIZ_NUM_REG 5, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 49999950, ID_WIDTH 0, ADDR_WIDTH 5, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN System_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0";
  ATTRIBUTE X_INTERFACE_INFO OF s0_axi_awaddr: SIGNAL IS "xilinx.com:interface:aximm:1.0 S0_AXI AWADDR";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s_axi_intr_aresetn: SIGNAL IS "XIL_INTERFACENAME S_AXI_INTR_RST, POLARITY ACTIVE_LOW";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_aresetn: SIGNAL IS "xilinx.com:signal:reset:1.0 S_AXI_INTR_RST RST";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s_axi_intr_aclk: SIGNAL IS "XIL_INTERFACENAME S_AXI_INTR_CLK, ASSOCIATED_BUSIF S_AXI_INTR, ASSOCIATED_RESET s_axi_intr_aresetn, FREQ_HZ 49999950, PHASE 0.000, CLK_DOMAIN System_processing_system7_0_0_FCLK_CLK0";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_aclk: SIGNAL IS "xilinx.com:signal:clock:1.0 S_AXI_INTR_CLK CLK";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_rready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_rvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_rresp: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_rdata: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_arready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_arvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR ARVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_arprot: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR ARPROT";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_araddr: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_bready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_bvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_bresp: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_wready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_wvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR WVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_wstrb: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_wdata: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_awready: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_awvalid: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR AWVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_awprot: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR AWPROT";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s_axi_intr_awaddr: SIGNAL IS "XIL_INTERFACENAME S_AXI_INTR, WIZ_DATA_WIDTH 32, WIZ_NUM_REG 5, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 49999950, ID_WIDTH 0, ADDR_WIDTH 5, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN System_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_intr_awaddr: SIGNAL IS "xilinx.com:interface:aximm:1.0 S_AXI_INTR AWADDR";
  ATTRIBUTE X_INTERFACE_PARAMETER OF irq: SIGNAL IS "XIL_INTERFACENAME IRQ, SENSITIVITY LEVEL_HIGH, PortWidth 1";
  ATTRIBUTE X_INTERFACE_INFO OF irq: SIGNAL IS "xilinx.com:signal:interrupt:1.0 IRQ INTERRUPT";
BEGIN
  U0 : NN_v1_0
    GENERIC MAP (
      C_S_AXI_INTR_DATA_WIDTH => 32,
      C_S_AXI_INTR_ADDR_WIDTH => 5,
      C_NUM_OF_INTR => 1,
      C_INTR_SENSITIVITY => X"FFFFFFFF",
      C_INTR_ACTIVE_STATE => X"FFFFFFFF",
      C_IRQ_SENSITIVITY => 1,
      C_IRQ_ACTIVE_STATE => 1,
      C_S0_AXI_DATA_WIDTH => 32,
      C_S0_AXI_ADDR_WIDTH => 5
    )
    PORT MAP (
      irq => irq,
      s_axi_intr_awaddr => s_axi_intr_awaddr,
      s_axi_intr_awprot => s_axi_intr_awprot,
      s_axi_intr_awvalid => s_axi_intr_awvalid,
      s_axi_intr_awready => s_axi_intr_awready,
      s_axi_intr_wdata => s_axi_intr_wdata,
      s_axi_intr_wstrb => s_axi_intr_wstrb,
      s_axi_intr_wvalid => s_axi_intr_wvalid,
      s_axi_intr_wready => s_axi_intr_wready,
      s_axi_intr_bresp => s_axi_intr_bresp,
      s_axi_intr_bvalid => s_axi_intr_bvalid,
      s_axi_intr_bready => s_axi_intr_bready,
      s_axi_intr_araddr => s_axi_intr_araddr,
      s_axi_intr_arprot => s_axi_intr_arprot,
      s_axi_intr_arvalid => s_axi_intr_arvalid,
      s_axi_intr_arready => s_axi_intr_arready,
      s_axi_intr_rdata => s_axi_intr_rdata,
      s_axi_intr_rresp => s_axi_intr_rresp,
      s_axi_intr_rvalid => s_axi_intr_rvalid,
      s_axi_intr_rready => s_axi_intr_rready,
      s_axi_intr_aclk => s_axi_intr_aclk,
      s_axi_intr_aresetn => s_axi_intr_aresetn,
      s0_axi_awaddr => s0_axi_awaddr,
      s0_axi_awprot => s0_axi_awprot,
      s0_axi_awvalid => s0_axi_awvalid,
      s0_axi_awready => s0_axi_awready,
      s0_axi_wdata => s0_axi_wdata,
      s0_axi_wstrb => s0_axi_wstrb,
      s0_axi_wvalid => s0_axi_wvalid,
      s0_axi_wready => s0_axi_wready,
      s0_axi_bresp => s0_axi_bresp,
      s0_axi_bvalid => s0_axi_bvalid,
      s0_axi_bready => s0_axi_bready,
      s0_axi_araddr => s0_axi_araddr,
      s0_axi_arprot => s0_axi_arprot,
      s0_axi_arvalid => s0_axi_arvalid,
      s0_axi_arready => s0_axi_arready,
      s0_axi_rdata => s0_axi_rdata,
      s0_axi_rresp => s0_axi_rresp,
      s0_axi_rvalid => s0_axi_rvalid,
      s0_axi_rready => s0_axi_rready,
      s0_axi_aclk => s0_axi_aclk,
      s0_axi_aresetn => s0_axi_aresetn
    );
END System_NN_1_0_arch;
