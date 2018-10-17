connect -url tcp:127.0.0.1:3121
source C:/Users/Chinook-ELE/ZynqWorkspace/SensTel2_emio_NNip/nn_ip_addition/rtos_emio_port_NN_rev4_but_after_rev5/System_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
loadhw -hw C:/Users/Chinook-ELE/ZynqWorkspace/SensTel2_emio_NNip/nn_ip_addition/rtos_emio_port_NN_rev4_but_after_rev5/System_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
dow C:/Users/Chinook-ELE/ZynqWorkspace/SensTel2_emio_NNip/nn_ip_addition/rtos_emio_port_NN_rev4_but_after_rev5/rtos_nn_emio_app_rev4_after_rev6/Debug/rtos_nn_emio_app_rev4_after_rev6.elf
configparams force-mem-access 0
bpadd -addr &main
