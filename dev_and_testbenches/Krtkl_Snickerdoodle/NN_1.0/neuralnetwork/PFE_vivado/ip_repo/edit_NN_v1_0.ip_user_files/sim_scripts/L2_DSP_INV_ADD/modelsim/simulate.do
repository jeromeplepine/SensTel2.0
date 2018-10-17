onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L xbip_dsp48_wrapper_v3_0_4 -L xbip_utils_v3_0_8 -L xbip_pipe_v3_0_4 -L xbip_dsp48_macro_v3_0_15 -L xil_defaultlib -L secureip -lib xil_defaultlib xil_defaultlib.L2_DSP_INV_ADD

do {wave.do}

view wave
view structure
view signals

do {L2_DSP_INV_ADD.udo}

run -all

quit -force
