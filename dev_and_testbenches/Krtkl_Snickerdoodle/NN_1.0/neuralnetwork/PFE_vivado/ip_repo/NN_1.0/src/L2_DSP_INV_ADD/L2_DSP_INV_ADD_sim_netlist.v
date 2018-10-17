// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Tue Jun 12 17:39:56 2018
// Host        : DESKTOP-SUA8GT7 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               C:/Users/Vince/Desktop/PFE_vivado/PFE/PFE.srcs/sources_1/ip/L2_DSP_INV_ADD/L2_DSP_INV_ADD_sim_netlist.v
// Design      : L2_DSP_INV_ADD
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "L2_DSP_INV_ADD,xbip_dsp48_macro_v3_0_15,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "xbip_dsp48_macro_v3_0_15,Vivado 2017.4" *) 
(* NotValidForBitStream *)
module L2_DSP_INV_ADD
   (CLK,
    A,
    C,
    P);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF p_intf:pcout_intf:carrycascout_intf:carryout_intf:bcout_intf:acout_intf:concat_intf:d_intf:c_intf:b_intf:a_intf:bcin_intf:acin_intf:pcin_intf:carryin_intf:carrycascin_intf:sel_intf, ASSOCIATED_RESET SCLR:SCLRD:SCLRA:SCLRB:SCLRCONCAT:SCLRC:SCLRM:SCLRP:SCLRSEL, ASSOCIATED_CLKEN CE:CED:CED1:CED2:CED3:CEA:CEA1:CEA2:CEA3:CEA4:CEB:CEB1:CEB2:CEB3:CEB4:CECONCAT:CECONCAT3:CECONCAT4:CECONCAT5:CEC:CEC1:CEC2:CEC3:CEC4:CEC5:CEM:CEP:CESEL:CESEL1:CESEL2:CESEL3:CESEL4:CESEL5, FREQ_HZ 100000000, PHASE 0.000" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA undef" *) input [17:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 c_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME c_intf, LAYERED_METADATA undef" *) input [17:0]C;
  (* x_interface_info = "xilinx.com:signal:data:1.0 p_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME p_intf, LAYERED_METADATA undef" *) output [18:0]P;

  wire [17:0]A;
  wire [17:0]C;
  wire CLK;
  wire [18:0]P;
  wire NLW_U0_CARRYCASCOUT_UNCONNECTED;
  wire NLW_U0_CARRYOUT_UNCONNECTED;
  wire [29:0]NLW_U0_ACOUT_UNCONNECTED;
  wire [17:0]NLW_U0_BCOUT_UNCONNECTED;
  wire [47:0]NLW_U0_PCOUT_UNCONNECTED;

  (* C_A_WIDTH = "18" *) 
  (* C_B_WIDTH = "18" *) 
  (* C_CONCAT_WIDTH = "48" *) 
  (* C_CONSTANT_1 = "1" *) 
  (* C_C_WIDTH = "18" *) 
  (* C_D_WIDTH = "18" *) 
  (* C_HAS_A = "1" *) 
  (* C_HAS_ACIN = "0" *) 
  (* C_HAS_ACOUT = "0" *) 
  (* C_HAS_B = "0" *) 
  (* C_HAS_BCIN = "0" *) 
  (* C_HAS_BCOUT = "0" *) 
  (* C_HAS_C = "1" *) 
  (* C_HAS_CARRYCASCIN = "0" *) 
  (* C_HAS_CARRYCASCOUT = "0" *) 
  (* C_HAS_CARRYIN = "0" *) 
  (* C_HAS_CARRYOUT = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_CEA = "0" *) 
  (* C_HAS_CEB = "0" *) 
  (* C_HAS_CEC = "0" *) 
  (* C_HAS_CECONCAT = "0" *) 
  (* C_HAS_CED = "0" *) 
  (* C_HAS_CEM = "0" *) 
  (* C_HAS_CEP = "0" *) 
  (* C_HAS_CESEL = "0" *) 
  (* C_HAS_CONCAT = "0" *) 
  (* C_HAS_D = "0" *) 
  (* C_HAS_INDEP_CE = "0" *) 
  (* C_HAS_INDEP_SCLR = "0" *) 
  (* C_HAS_PCIN = "0" *) 
  (* C_HAS_PCOUT = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_SCLRA = "0" *) 
  (* C_HAS_SCLRB = "0" *) 
  (* C_HAS_SCLRC = "0" *) 
  (* C_HAS_SCLRCONCAT = "0" *) 
  (* C_HAS_SCLRD = "0" *) 
  (* C_HAS_SCLRM = "0" *) 
  (* C_HAS_SCLRP = "0" *) 
  (* C_HAS_SCLRSEL = "0" *) 
  (* C_LATENCY = "112" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_OPMODES = "000000000011010100000001" *) 
  (* C_P_LSB = "0" *) 
  (* C_P_MSB = "18" *) 
  (* C_REG_CONFIG = "00000000000000000000000011000100" *) 
  (* C_SEL_WIDTH = "0" *) 
  (* C_TEST_CORE = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  L2_DSP_INV_ADD_xbip_dsp48_macro_v3_0_15 U0
       (.A(A),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_U0_ACOUT_UNCONNECTED[29:0]),
        .B({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_U0_BCOUT_UNCONNECTED[17:0]),
        .C(C),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_U0_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYOUT(NLW_U0_CARRYOUT_UNCONNECTED),
        .CE(1'b1),
        .CEA(1'b1),
        .CEA1(1'b1),
        .CEA2(1'b1),
        .CEA3(1'b1),
        .CEA4(1'b1),
        .CEB(1'b1),
        .CEB1(1'b1),
        .CEB2(1'b1),
        .CEB3(1'b1),
        .CEB4(1'b1),
        .CEC(1'b1),
        .CEC1(1'b1),
        .CEC2(1'b1),
        .CEC3(1'b1),
        .CEC4(1'b1),
        .CEC5(1'b1),
        .CECONCAT(1'b1),
        .CECONCAT3(1'b1),
        .CECONCAT4(1'b1),
        .CECONCAT5(1'b1),
        .CED(1'b1),
        .CED1(1'b1),
        .CED2(1'b1),
        .CED3(1'b1),
        .CEM(1'b1),
        .CEP(1'b1),
        .CESEL(1'b1),
        .CESEL1(1'b1),
        .CESEL2(1'b1),
        .CESEL3(1'b1),
        .CESEL4(1'b1),
        .CESEL5(1'b1),
        .CLK(CLK),
        .CONCAT({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .P(P),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(NLW_U0_PCOUT_UNCONNECTED[47:0]),
        .SCLR(1'b0),
        .SCLRA(1'b0),
        .SCLRB(1'b0),
        .SCLRC(1'b0),
        .SCLRCONCAT(1'b0),
        .SCLRD(1'b0),
        .SCLRM(1'b0),
        .SCLRP(1'b0),
        .SCLRSEL(1'b0),
        .SEL(1'b0));
endmodule

(* C_A_WIDTH = "18" *) (* C_B_WIDTH = "18" *) (* C_CONCAT_WIDTH = "48" *) 
(* C_CONSTANT_1 = "1" *) (* C_C_WIDTH = "18" *) (* C_D_WIDTH = "18" *) 
(* C_HAS_A = "1" *) (* C_HAS_ACIN = "0" *) (* C_HAS_ACOUT = "0" *) 
(* C_HAS_B = "0" *) (* C_HAS_BCIN = "0" *) (* C_HAS_BCOUT = "0" *) 
(* C_HAS_C = "1" *) (* C_HAS_CARRYCASCIN = "0" *) (* C_HAS_CARRYCASCOUT = "0" *) 
(* C_HAS_CARRYIN = "0" *) (* C_HAS_CARRYOUT = "0" *) (* C_HAS_CE = "0" *) 
(* C_HAS_CEA = "0" *) (* C_HAS_CEB = "0" *) (* C_HAS_CEC = "0" *) 
(* C_HAS_CECONCAT = "0" *) (* C_HAS_CED = "0" *) (* C_HAS_CEM = "0" *) 
(* C_HAS_CEP = "0" *) (* C_HAS_CESEL = "0" *) (* C_HAS_CONCAT = "0" *) 
(* C_HAS_D = "0" *) (* C_HAS_INDEP_CE = "0" *) (* C_HAS_INDEP_SCLR = "0" *) 
(* C_HAS_PCIN = "0" *) (* C_HAS_PCOUT = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_SCLRA = "0" *) (* C_HAS_SCLRB = "0" *) (* C_HAS_SCLRC = "0" *) 
(* C_HAS_SCLRCONCAT = "0" *) (* C_HAS_SCLRD = "0" *) (* C_HAS_SCLRM = "0" *) 
(* C_HAS_SCLRP = "0" *) (* C_HAS_SCLRSEL = "0" *) (* C_LATENCY = "112" *) 
(* C_MODEL_TYPE = "0" *) (* C_OPMODES = "000000000011010100000001" *) (* C_P_LSB = "0" *) 
(* C_P_MSB = "18" *) (* C_REG_CONFIG = "00000000000000000000000011000100" *) (* C_SEL_WIDTH = "0" *) 
(* C_TEST_CORE = "0" *) (* C_VERBOSITY = "0" *) (* C_XDEVICEFAMILY = "zynq" *) 
(* ORIG_REF_NAME = "xbip_dsp48_macro_v3_0_15" *) (* downgradeipidentifiedwarnings = "yes" *) 
module L2_DSP_INV_ADD_xbip_dsp48_macro_v3_0_15
   (CLK,
    CE,
    SCLR,
    SEL,
    CARRYCASCIN,
    CARRYIN,
    PCIN,
    ACIN,
    BCIN,
    A,
    B,
    C,
    D,
    CONCAT,
    ACOUT,
    BCOUT,
    CARRYOUT,
    CARRYCASCOUT,
    PCOUT,
    P,
    CED,
    CED1,
    CED2,
    CED3,
    CEA,
    CEA1,
    CEA2,
    CEA3,
    CEA4,
    CEB,
    CEB1,
    CEB2,
    CEB3,
    CEB4,
    CECONCAT,
    CECONCAT3,
    CECONCAT4,
    CECONCAT5,
    CEC,
    CEC1,
    CEC2,
    CEC3,
    CEC4,
    CEC5,
    CEM,
    CEP,
    CESEL,
    CESEL1,
    CESEL2,
    CESEL3,
    CESEL4,
    CESEL5,
    SCLRD,
    SCLRA,
    SCLRB,
    SCLRCONCAT,
    SCLRC,
    SCLRM,
    SCLRP,
    SCLRSEL);
  input CLK;
  input CE;
  input SCLR;
  input [0:0]SEL;
  input CARRYCASCIN;
  input CARRYIN;
  input [47:0]PCIN;
  input [29:0]ACIN;
  input [17:0]BCIN;
  input [17:0]A;
  input [17:0]B;
  input [17:0]C;
  input [17:0]D;
  input [47:0]CONCAT;
  output [29:0]ACOUT;
  output [17:0]BCOUT;
  output CARRYOUT;
  output CARRYCASCOUT;
  output [47:0]PCOUT;
  output [18:0]P;
  input CED;
  input CED1;
  input CED2;
  input CED3;
  input CEA;
  input CEA1;
  input CEA2;
  input CEA3;
  input CEA4;
  input CEB;
  input CEB1;
  input CEB2;
  input CEB3;
  input CEB4;
  input CECONCAT;
  input CECONCAT3;
  input CECONCAT4;
  input CECONCAT5;
  input CEC;
  input CEC1;
  input CEC2;
  input CEC3;
  input CEC4;
  input CEC5;
  input CEM;
  input CEP;
  input CESEL;
  input CESEL1;
  input CESEL2;
  input CESEL3;
  input CESEL4;
  input CESEL5;
  input SCLRD;
  input SCLRA;
  input SCLRB;
  input SCLRCONCAT;
  input SCLRC;
  input SCLRM;
  input SCLRP;
  input SCLRSEL;

  wire [17:0]A;
  wire [29:0]ACIN;
  wire [29:0]ACOUT;
  wire [17:0]BCIN;
  wire [17:0]BCOUT;
  wire [17:0]C;
  wire CARRYCASCIN;
  wire CARRYCASCOUT;
  wire CARRYOUT;
  wire CLK;
  wire [18:0]P;
  wire [47:0]PCIN;
  wire [47:0]PCOUT;

  (* C_A_WIDTH = "18" *) 
  (* C_B_WIDTH = "18" *) 
  (* C_CONCAT_WIDTH = "48" *) 
  (* C_CONSTANT_1 = "1" *) 
  (* C_C_WIDTH = "18" *) 
  (* C_D_WIDTH = "18" *) 
  (* C_HAS_A = "1" *) 
  (* C_HAS_ACIN = "0" *) 
  (* C_HAS_ACOUT = "0" *) 
  (* C_HAS_B = "0" *) 
  (* C_HAS_BCIN = "0" *) 
  (* C_HAS_BCOUT = "0" *) 
  (* C_HAS_C = "1" *) 
  (* C_HAS_CARRYCASCIN = "0" *) 
  (* C_HAS_CARRYCASCOUT = "0" *) 
  (* C_HAS_CARRYIN = "0" *) 
  (* C_HAS_CARRYOUT = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_CEA = "0" *) 
  (* C_HAS_CEB = "0" *) 
  (* C_HAS_CEC = "0" *) 
  (* C_HAS_CECONCAT = "0" *) 
  (* C_HAS_CED = "0" *) 
  (* C_HAS_CEM = "0" *) 
  (* C_HAS_CEP = "0" *) 
  (* C_HAS_CESEL = "0" *) 
  (* C_HAS_CONCAT = "0" *) 
  (* C_HAS_D = "0" *) 
  (* C_HAS_INDEP_CE = "0" *) 
  (* C_HAS_INDEP_SCLR = "0" *) 
  (* C_HAS_PCIN = "0" *) 
  (* C_HAS_PCOUT = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_SCLRA = "0" *) 
  (* C_HAS_SCLRB = "0" *) 
  (* C_HAS_SCLRC = "0" *) 
  (* C_HAS_SCLRCONCAT = "0" *) 
  (* C_HAS_SCLRD = "0" *) 
  (* C_HAS_SCLRM = "0" *) 
  (* C_HAS_SCLRP = "0" *) 
  (* C_HAS_SCLRSEL = "0" *) 
  (* C_LATENCY = "112" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_OPMODES = "000000000011010100000001" *) 
  (* C_P_LSB = "0" *) 
  (* C_P_MSB = "18" *) 
  (* C_REG_CONFIG = "00000000000000000000000011000100" *) 
  (* C_SEL_WIDTH = "0" *) 
  (* C_TEST_CORE = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  L2_DSP_INV_ADD_xbip_dsp48_macro_v3_0_15_viv i_synth
       (.A(A),
        .ACIN(ACIN),
        .ACOUT(ACOUT),
        .B({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCIN(BCIN),
        .BCOUT(BCOUT),
        .C(C),
        .CARRYCASCIN(CARRYCASCIN),
        .CARRYCASCOUT(CARRYCASCOUT),
        .CARRYIN(1'b0),
        .CARRYOUT(CARRYOUT),
        .CE(1'b0),
        .CEA(1'b0),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEA3(1'b0),
        .CEA4(1'b0),
        .CEB(1'b0),
        .CEB1(1'b0),
        .CEB2(1'b0),
        .CEB3(1'b0),
        .CEB4(1'b0),
        .CEC(1'b0),
        .CEC1(1'b0),
        .CEC2(1'b0),
        .CEC3(1'b0),
        .CEC4(1'b0),
        .CEC5(1'b0),
        .CECONCAT(1'b0),
        .CECONCAT3(1'b0),
        .CECONCAT4(1'b0),
        .CECONCAT5(1'b0),
        .CED(1'b0),
        .CED1(1'b0),
        .CED2(1'b0),
        .CED3(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CESEL(1'b0),
        .CESEL1(1'b0),
        .CESEL2(1'b0),
        .CESEL3(1'b0),
        .CESEL4(1'b0),
        .CESEL5(1'b0),
        .CLK(CLK),
        .CONCAT({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .P(P),
        .PCIN(PCIN),
        .PCOUT(PCOUT),
        .SCLR(1'b0),
        .SCLRA(1'b0),
        .SCLRB(1'b0),
        .SCLRC(1'b0),
        .SCLRCONCAT(1'b0),
        .SCLRD(1'b0),
        .SCLRM(1'b0),
        .SCLRP(1'b0),
        .SCLRSEL(1'b0),
        .SEL(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2015"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
nBlnHi3Kp5ztG6vZNdMONLkWpVVpg2r7ZP2rdZEfioM4XUkRew1oDSrAozd60ivTx8PLiOPPRAJo
pOZd0llK5g==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
Kcs1MQe5BgqnN7tbrZMcEiZZSCl175bCFWu5jwqWj4RFDG/n9GjuiwAuZ9v2vQZcAxVE3h5w+TBc
Bk1lc9zc7T3tnbm4qpXepckPAqiTqMURQNO28XRRz5BSiTktDkY/dUGVSA0qxTdPGlkYZSpuFpl6
PjievZtLxEtp4cSEwJE=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
aG1w9h5Ae0N98iRQuCMUHQUwBA2KqP2Fbb/SCJOtosbKahOePVIWiIrkhbLMsr1/omYs/Q6fEj2G
uYHIEBLZLRANmjJt9kQu/jIzWAf0nK3OJkUCAMefyflw5y403PkpWIAHXqlArlaCVW2gWxzVxt9G
js0j3l7Y2dpahAMg2LgLgWyMj2rS0kjr+fbTwgci9As5Ndo6CDyXo7EcixOTvkWvqwxJaYFbtcFF
K1j0WC1jYCLSiEJ2ZB5/ODVnSmn3AWSksydgQ3iYMKpYPNlAwFN7t7HacZ95HxO8MGoNyjnDje35
EzrNZrAA4vUP8Y6En1JgkF6RLt8PJJfLc+wq+g==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
BYWKn+AL7Gth8aEXuzL+rpOrNP6Ug8Hc9TpmOLZLrPZ4boPFPd89qpRHOY6mfox3M09mZK4TuSx+
5DykxgtH7Gu2DHCqtg3Tg7eFTAzurR/EqXoPhuHQIzs5Y1T/5WlIb0c4l9CNWdc5TBVfbmKR+x4N
A259tw/6q69OtmAqFiB+p9GY8lyjNDWu07DJlxI2l6wSRYy8YqD7K1OrLRXxY6gaTqDWDXlcO+ia
T5/harPHjTiNAFO8U6YTfRQtNJUrOnNfSAnAtjrlegYGNcEl6u4sqYE/X/Pajk2n+1+KvJ6PR8L9
bdrCByV81f1z88nc1Twl6LUe54VQdfe5W+EOpQ==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2017_05", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
iJnLIMkUEl7Btn7IVUeqK6xbyk9c7fsISctkfj2c6osS1GvgHXWHkJPpNPHTeIth7zUvkUlYB/Jd
M5kNK3leJJj5TaqOLOh+cyWqEGY64EruHImVJasbLaVn3LUh67wEEMFoKhP9/KjqLsL3oFrKnU4i
JzYtVgZoCfaHBaIyRC6wms7z/YKP2Khya0dzmYHMmbdm9k2rL27fVLJcCEMSO1Dsz2D/qXnCFI8T
NHnM3Fv/xF2jOhtDIDqWGakvXk7l+ddg95MJ+5A578jqVX81M0WJwbHlaIJIG5uwIzTI46+pYw0Z
4sgDMkrl/aXSFYB5PU2L4hhVeq7e6c0dqUOVSw==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
sdiBszQspScY+UIwuaohSbs1PAZL6bemuOZlFLGklUXNsz7r1265PlclnSy9m0ilIWxY0HJkGEtl
Rs/zfRlF9Ag/CEiBQ4lStxiXa4cbOvNwkp9j1BXCYCAbMsw83x+ZvpyoQTXRfcBBvSAbtpFDJ7ar
qlJbO6erRjpDP373GIY=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
eUV1ae8Aw6l0UtyVDuKmrMQwdVI8vrJTYSKwNJ+/x3fs7qy5B2fVzNE8tFRcie7NykwBpJV9lQNN
iNNcReVBjS/oh7txKer0RVLuw2jQCeQBSixWXwdIra9CsrIF5V2GUuY3dDh9ofaqsgbKSlDNLzzm
0lHhjAw4Nbk9kwoo5NP9xZYaLPCNo4Qqi0A9Px++Zu3V7DcbPDDDQnNEzgQhcN8ilscDyGVOeiHu
/xJbo1lLkpyrDciztvHYqwj9O/kSyF1PikDg8xEaOx1QQVvaz7r51DlXlPCpqCUyFGEeiIrPCMHf
8rf7t9DpvBEVPF3eaofCDfiW9vWmbfgffwtMYg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
pIMSFENtMFj8e+tGiuDGuJNMlSTzC7+EsUTSCbjWz9z5psgM6E7ZmphGGKZhrZC0HATyMRoF+Ht5
BxCoGRadwum79XFsZI9Lw8aUygKXZ4b6RA503j6AYiPebeKQWeeedsZzXUd1DasPE2d+hAllkZEx
1mvZSeCY+EAtLZMT/VMEvci3zd/Kpt/PS0c7w6Dj2kn+XRRg1GGO5zs1qy8N5GefckhlXpDmyOYv
GRlwZ+K8qhlm6z+/z+PZZWwEwbQiVwKSY0UmvoGkGmHwCfvXLpyaHwWDwM/yWy1R4qC+Y4eJjmGV
UDynTzEV9vMkh/wMo1Vl0fMpyPWwQgHVexiT/A==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
0Dccn9NjWbP/7azBDZKJYedznYY1O5redXW4/JzitYeE89inmriThbWfK4ORdc4T/mmfJI6X0wbH
glp8wT3xbMGWuG3M/zwudUC+c5KImWERLpygVbPuWIXgjrMsANrg9ZyTkylR0PnRF8F5pC/tSIfa
kUDIedoLUCvxywLTq5j58SG+mNmJMMDBluSQDLROhcrOK0lGlIFacHhuf5fng8kuKmft9M2EVIMu
CDWPwekq+VMi501iXk7K06LAVurJy8EjJnTXd20PdvaheyJH/K1zQuDuFk1r2Ld4nPNAOTsC3pun
qECA2HkWjTfeOEhgL9CSHUNwanlEOwCh0hmmrQ==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 9792)
`pragma protect data_block
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
`pragma protect end_protected
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
