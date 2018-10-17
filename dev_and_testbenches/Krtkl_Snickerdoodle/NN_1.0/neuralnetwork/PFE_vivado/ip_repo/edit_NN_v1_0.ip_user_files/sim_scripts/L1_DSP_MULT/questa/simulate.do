onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib L1_DSP_MULT_opt

do {wave.do}

view wave
view structure
view signals

do {L1_DSP_MULT.udo}

run -all

quit -force
