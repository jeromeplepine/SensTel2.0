connect -url tcp:127.0.0.1:3121
source C:/Users/Chinook-ELE/ZynqWorkspace/SensTel2_emio/senstel_proto_emio/i2c_test/System_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
loadhw -hw C:/Users/Chinook-ELE/ZynqWorkspace/SensTel2_emio/senstel_proto_emio/i2c_test/System_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-HS3 210299A57A7D"} -index 0
dow C:/Users/Chinook-ELE/ZynqWorkspace/SensTel2_emio/senstel_proto_emio/i2c_test/i2c_senstel_proto_test/Debug/i2c_senstel_proto_test.elf
configparams force-mem-access 0
bpadd -addr &main
