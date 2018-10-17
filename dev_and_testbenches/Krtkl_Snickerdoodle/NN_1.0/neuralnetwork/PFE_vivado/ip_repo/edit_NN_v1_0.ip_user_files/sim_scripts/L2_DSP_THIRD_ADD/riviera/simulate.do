onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+L2_DSP_THIRD_ADD -L xbip_dsp48_wrapper_v3_0_4 -L xbip_utils_v3_0_8 -L xbip_pipe_v3_0_4 -L xbip_dsp48_macro_v3_0_15 -L xil_defaultlib -L secureip -O5 xil_defaultlib.L2_DSP_THIRD_ADD

do {wave.do}

view wave
view structure

do {L2_DSP_THIRD_ADD.udo}

run -all

endsim

quit -force
