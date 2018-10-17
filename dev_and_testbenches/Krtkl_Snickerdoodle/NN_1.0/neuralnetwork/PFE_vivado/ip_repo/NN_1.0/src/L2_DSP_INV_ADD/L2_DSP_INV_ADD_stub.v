// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Tue Jun 12 17:39:56 2018
// Host        : DESKTOP-SUA8GT7 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               C:/Users/Vince/Desktop/PFE_vivado/PFE/PFE.srcs/sources_1/ip/L2_DSP_INV_ADD/L2_DSP_INV_ADD_stub.v
// Design      : L2_DSP_INV_ADD
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "xbip_dsp48_macro_v3_0_15,Vivado 2017.4" *)
module L2_DSP_INV_ADD(CLK, A, C, P)
/* synthesis syn_black_box black_box_pad_pin="CLK,A[17:0],C[17:0],P[18:0]" */;
  input CLK;
  input [17:0]A;
  input [17:0]C;
  output [18:0]P;
endmodule
