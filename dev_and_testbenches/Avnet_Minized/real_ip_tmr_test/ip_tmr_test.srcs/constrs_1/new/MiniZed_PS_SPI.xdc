set_property IOSTANDARD LVCMOS33 [get_ports capturetrig0]
set_property IOSTANDARD LVCMOS33 [get_ports capturetrig1]

set_property IOSTANDARD LVCMOS33 [get_ports UART_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports UART_0_txd]
set_property PULLUP true [get_ports UART_0_rxd]
set_property PULLUP true [get_ports UART_0_txd]




set_property PACKAGE_PIN L15 [get_ports UART_0_rxd]
set_property PACKAGE_PIN M15 [get_ports UART_0_txd]
set_property PACKAGE_PIN L14 [get_ports capturetrig0]
set_property PACKAGE_PIN M14 [get_ports capturetrig1]
