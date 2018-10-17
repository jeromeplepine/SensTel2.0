library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity NN_v1_0 is
   generic (
      -- Users to add parameters here
      
      -- User parameters ends
      -- Do not modify the parameters beyond this line


      -- Parameters of Axi Slave Bus Interface S0_AXI
      C_S0_AXI_DATA_WIDTH   : integer   := 32;
      C_S0_AXI_ADDR_WIDTH   : integer   := 5;

      -- Parameters of Axi Slave Bus Interface S_AXI_INTR
      C_S_AXI_INTR_DATA_WIDTH   : integer   := 32;
      C_S_AXI_INTR_ADDR_WIDTH   : integer   := 5;
      C_NUM_OF_INTR   : integer   := 1;
      C_INTR_SENSITIVITY   : std_logic_vector   := x"FFFFFFFF";
      C_INTR_ACTIVE_STATE   : std_logic_vector   := x"FFFFFFFF";
      C_IRQ_SENSITIVITY   : integer   := 1;
      C_IRQ_ACTIVE_STATE   : integer   := 1
   );
   port (
      -- Users to add ports here

      -- User ports ends
      -- Do not modify the ports beyond this line

      -- Ports of Axi Slave Bus Interface S0_AXI
      s0_axi_aclk    : in  std_logic;
      s0_axi_aresetn : in  std_logic;
      s0_axi_awaddr  : in  std_logic_vector(C_S0_AXI_ADDR_WIDTH-1 downto 0);
      s0_axi_awprot  : in  std_logic_vector(2 downto 0);
      s0_axi_awvalid : in  std_logic;
      s0_axi_awready : out std_logic;
      s0_axi_wdata   : in  std_logic_vector(C_S0_AXI_DATA_WIDTH-1 downto 0);
      s0_axi_wstrb   : in  std_logic_vector((C_S0_AXI_DATA_WIDTH/8)-1 downto 0);
      s0_axi_wvalid  : in  std_logic;
      s0_axi_wready  : out std_logic;
      s0_axi_bresp   : out std_logic_vector(1 downto 0);
      s0_axi_bvalid  : out std_logic;
      s0_axi_bready  : in  std_logic;
      s0_axi_araddr  : in  std_logic_vector(C_S0_AXI_ADDR_WIDTH-1 downto 0);
      s0_axi_arprot  : in  std_logic_vector(2 downto 0);
      s0_axi_arvalid : in  std_logic;
      s0_axi_arready : out std_logic;
      s0_axi_rdata   : out std_logic_vector(C_S0_AXI_DATA_WIDTH-1 downto 0);
      s0_axi_rresp   : out std_logic_vector(1 downto 0);
      s0_axi_rvalid  : out std_logic;
      s0_axi_rready  : in  std_logic;

      -- Ports of Axi Slave Bus Interface S_AXI_INTR
      s_axi_intr_aclk    : in  std_logic;
      s_axi_intr_aresetn : in  std_logic;
      s_axi_intr_awaddr  : in  std_logic_vector(C_S_AXI_INTR_ADDR_WIDTH-1 downto 0);
      s_axi_intr_awprot  : in  std_logic_vector(2 downto 0);
      s_axi_intr_awvalid : in  std_logic;
      s_axi_intr_awready : out std_logic;
      s_axi_intr_wdata   : in  std_logic_vector(C_S_AXI_INTR_DATA_WIDTH-1 downto 0);
      s_axi_intr_wstrb   : in  std_logic_vector((C_S_AXI_INTR_DATA_WIDTH/8)-1 downto 0);
      s_axi_intr_wvalid  : in  std_logic;
      s_axi_intr_wready  : out std_logic;
      s_axi_intr_bresp   : out std_logic_vector(1 downto 0);
      s_axi_intr_bvalid  : out std_logic;
      s_axi_intr_bready  : in  std_logic;
      s_axi_intr_araddr  : in  std_logic_vector(C_S_AXI_INTR_ADDR_WIDTH-1 downto 0);
      s_axi_intr_arprot  : in  std_logic_vector(2 downto 0);
      s_axi_intr_arvalid : in  std_logic;
      s_axi_intr_arready : out std_logic;
      s_axi_intr_rdata   : out std_logic_vector(C_S_AXI_INTR_DATA_WIDTH-1 downto 0);
      s_axi_intr_rresp   : out std_logic_vector(1 downto 0);
      s_axi_intr_rvalid  : out std_logic;
      s_axi_intr_rready  : in  std_logic;
      irq                : out std_logic
   );
end NN_v1_0;

architecture arch_imp of NN_v1_0 is

   -- component declaration
   component NN_v1_0_S0_AXI is
      generic (
         C_S_AXI_DATA_WIDTH   : integer   := 32;
         C_S_AXI_ADDR_WIDTH   : integer   := 5
      );
      port (
         o_PT       : out std_logic_vector(11 downto 0);
         o_WS       : out std_logic_vector(11 downto 0);
         o_RPM      : out std_logic_vector(11 downto 0);
         i_COM      : in  std_logic_vector(3 downto 0);
         o_DATA_RDY : out std_logic;
         
         S_AXI_ACLK   : in std_logic;
         S_AXI_ARESETN   : in std_logic;
         S_AXI_AWADDR   : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
         S_AXI_AWPROT   : in std_logic_vector(2 downto 0);
         S_AXI_AWVALID   : in std_logic;
         S_AXI_AWREADY   : out std_logic;
         S_AXI_WDATA   : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
         S_AXI_WSTRB   : in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
         S_AXI_WVALID   : in std_logic;
         S_AXI_WREADY   : out std_logic;
         S_AXI_BRESP   : out std_logic_vector(1 downto 0);
         S_AXI_BVALID   : out std_logic;
         S_AXI_BREADY   : in std_logic;
         S_AXI_ARADDR   : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
         S_AXI_ARPROT   : in std_logic_vector(2 downto 0);
         S_AXI_ARVALID   : in std_logic;
         S_AXI_ARREADY   : out std_logic;
         S_AXI_RDATA   : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
         S_AXI_RRESP   : out std_logic_vector(1 downto 0);
         S_AXI_RVALID   : out std_logic;
         S_AXI_RREADY   : in std_logic
      );
   end component NN_v1_0_S0_AXI;

   component NN_v1_0_S_AXI_INTR is
      generic (
         C_S_AXI_DATA_WIDTH   : integer   := 32;
         C_S_AXI_ADDR_WIDTH   : integer   := 5;
         C_NUM_OF_INTR   : integer   := 1;
         C_INTR_SENSITIVITY   : std_logic_vector   := x"FFFFFFFF";
         C_INTR_ACTIVE_STATE   : std_logic_vector   := x"FFFFFFFF";
         C_IRQ_SENSITIVITY   : integer   := 1;
         C_IRQ_ACTIVE_STATE   : integer   := 1
      );
      port (
         i_intr : in std_logic;
         S_AXI_ACLK   : in std_logic;
         S_AXI_ARESETN   : in std_logic;
         S_AXI_AWADDR   : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
         S_AXI_AWPROT   : in std_logic_vector(2 downto 0);
         S_AXI_AWVALID   : in std_logic;
         S_AXI_AWREADY   : out std_logic;
         S_AXI_WDATA   : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
         S_AXI_WSTRB   : in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
         S_AXI_WVALID   : in std_logic;
         S_AXI_WREADY   : out std_logic;
         S_AXI_BRESP   : out std_logic_vector(1 downto 0);
         S_AXI_BVALID   : out std_logic;
         S_AXI_BREADY   : in std_logic;
         S_AXI_ARADDR   : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
         S_AXI_ARPROT   : in std_logic_vector(2 downto 0);
         S_AXI_ARVALID   : in std_logic;
         S_AXI_ARREADY   : out std_logic;
         S_AXI_RDATA   : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
         S_AXI_RRESP   : out std_logic_vector(1 downto 0);
         S_AXI_RVALID   : out std_logic;
         S_AXI_RREADY   : in std_logic;
         irq   : out std_logic
      );
   end component NN_v1_0_S_AXI_INTR;
   
   component Neural_network is
      port(
         i_clk  : in  std_logic;
         
         i_pitch    : in  std_logic_vector(11 downto 0);
         i_ws       : in  std_logic_vector(11 downto 0);
         i_rpm      : in  std_logic_vector(11 downto 0);
         i_data_rdy : in  std_logic;
         
         o_intr     : out std_logic;
         output     : out std_logic_vector(3 downto 0)
      );
   end component Neural_network;

   signal PT       : std_logic_vector(11 downto 0);
   signal WS       : std_logic_vector(11 downto 0);
   signal RPM      : std_logic_vector(11 downto 0);
   signal COM      : std_logic_vector(3 downto 0);
   signal DATA_RDY : std_logic;
   signal intr     : std_logic;
   
begin

-- Instantiation of Axi Bus Interface S0_AXI
NN_v1_0_S0_AXI_inst : NN_v1_0_S0_AXI
   generic map (
      C_S_AXI_DATA_WIDTH   => C_S0_AXI_DATA_WIDTH,
      C_S_AXI_ADDR_WIDTH   => C_S0_AXI_ADDR_WIDTH
   )
   port map (
      o_PT       => PT,
      o_WS       => WS,
      o_RPM      => RPM,
      i_COM      => COM,
      o_DATA_RDY => DATA_RDY,
      
      S_AXI_ACLK    => s0_axi_aclk,
      S_AXI_ARESETN => s0_axi_aresetn,
      S_AXI_AWADDR  => s0_axi_awaddr,
      S_AXI_AWPROT  => s0_axi_awprot,
      S_AXI_AWVALID => s0_axi_awvalid,
      S_AXI_AWREADY => s0_axi_awready,
      S_AXI_WDATA   => s0_axi_wdata,
      S_AXI_WSTRB   => s0_axi_wstrb,
      S_AXI_WVALID  => s0_axi_wvalid,
      S_AXI_WREADY  => s0_axi_wready,
      S_AXI_BRESP   => s0_axi_bresp,
      S_AXI_BVALID  => s0_axi_bvalid,
      S_AXI_BREADY  => s0_axi_bready,
      S_AXI_ARADDR  => s0_axi_araddr,
      S_AXI_ARPROT  => s0_axi_arprot,
      S_AXI_ARVALID => s0_axi_arvalid,
      S_AXI_ARREADY => s0_axi_arready,
      S_AXI_RDATA   => s0_axi_rdata,
      S_AXI_RRESP   => s0_axi_rresp,
      S_AXI_RVALID  => s0_axi_rvalid,
      S_AXI_RREADY  => s0_axi_rready
   );

-- Instantiation of Axi Bus Interface S_AXI_INTR
NN_v1_0_S_AXI_INTR_inst : NN_v1_0_S_AXI_INTR
   generic map (
      C_S_AXI_DATA_WIDTH  => C_S_AXI_INTR_DATA_WIDTH,
      C_S_AXI_ADDR_WIDTH  => C_S_AXI_INTR_ADDR_WIDTH,
      C_NUM_OF_INTR       => C_NUM_OF_INTR,
      C_INTR_SENSITIVITY  => C_INTR_SENSITIVITY,
      C_INTR_ACTIVE_STATE => C_INTR_ACTIVE_STATE,
      C_IRQ_SENSITIVITY   => C_IRQ_SENSITIVITY,
      C_IRQ_ACTIVE_STATE  => C_IRQ_ACTIVE_STATE
   )
   port map (
      i_intr        => intr,
      S_AXI_ACLK    => s_axi_intr_aclk,
      S_AXI_ARESETN => s_axi_intr_aresetn,
      S_AXI_AWADDR  => s_axi_intr_awaddr,
      S_AXI_AWPROT  => s_axi_intr_awprot,
      S_AXI_AWVALID => s_axi_intr_awvalid,
      S_AXI_AWREADY => s_axi_intr_awready,
      S_AXI_WDATA   => s_axi_intr_wdata,
      S_AXI_WSTRB   => s_axi_intr_wstrb,
      S_AXI_WVALID  => s_axi_intr_wvalid,
      S_AXI_WREADY  => s_axi_intr_wready,
      S_AXI_BRESP   => s_axi_intr_bresp,
      S_AXI_BVALID  => s_axi_intr_bvalid,
      S_AXI_BREADY  => s_axi_intr_bready,
      S_AXI_ARADDR  => s_axi_intr_araddr,
      S_AXI_ARPROT  => s_axi_intr_arprot,
      S_AXI_ARVALID => s_axi_intr_arvalid,
      S_AXI_ARREADY => s_axi_intr_arready,
      S_AXI_RDATA   => s_axi_intr_rdata,
      S_AXI_RRESP   => s_axi_intr_rresp,
      S_AXI_RVALID  => s_axi_intr_rvalid,
      S_AXI_RREADY  => s_axi_intr_rready,
      irq           => irq
   );

   -- Add user logic here
   NN: Neural_network
      port map(
         i_clk      => s0_axi_aclk,
         i_pitch    => PT,
         i_ws       => WS,
         i_rpm      => RPM,
         i_data_rdy => DATA_RDY,
         
         o_intr     => intr,
         output     => COM
      );
   -- User logic ends

end arch_imp;
