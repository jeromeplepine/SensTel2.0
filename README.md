
## Chinook ÉTS SensTel2.0 Project

This SensTel version features the use of FreeRTOS, handles sensor data acquisition and processing, broadcasts most of it on CAN bus, logs it on-demand to an SD card, can implement wireless telemetry and manages the VHDL pitch control AI core. The development phase could be defined as beta and was developed up to the point where it is functional but not ressource efficient - it can and should be improved.

### Contents
* The project's latest files - those that were used during Racing Aeolus 2018
	* under "nn_ip_addition"
* Individual peripheral development projects (hardware system and C code) using Avnet's MiniZed devboard
	* under "dev_and_testbenches"
* Individual peripheral development projects (hardware system and C code) using Krtkl's Snickerdoodle devboard
	* under "dev_and_testbenches/Krtkl_Snickerdoodle/SensTel2_emio"
* The turbine pitch actuation testbench's code (which features the VNH5019-based shield currently used in the car)
	* under "dev_and_testbenches\Avnet_Minized\torque_testbench_w_ssi_vnh5019"
* A customized Snickerdoodle platform controller firmware project	
* The neural network's forward propagation VHDL implementation (under NN_1.0)
* A Texas Instrument Launchpad-based SSI testbench project

### Prerequisites
To work with the SensTel2.0 prototype, you'll need to have the Vivado design suite and the software development kit, SDK.
https://www.xilinx.com/products/design-tools/vivado/vivado-webpack.html
If you've never worked with Vivado, I highly recommend doing those tutorials from Avnet (find the link in the Documentation section)
	* Tutorial 01 Build a Zynq Hardware Platform
	* Tutorial 02 First Application - Hello World

To work with a Snickerdoodle developement board, you need a Digilent HS-3 programmer (or another Xilinx compatible JTAG programmer/debugger) and, ideally, a Krtkl BreakyBreaky expansion board.

To bring modifications to the platform controller's firmware, you'll need the Keil uVision MDK-Lite IDE.
http://www2.keil.com/mdk5/editions/lite

### Documentation and Tutorials

Avnet’s tutorials are very good primers to start using Xilinx’s development environment: Vivado, for editing the hardware system, and SDK, for editing the software.
[http://zedboard.org/support/design/18891/146](http://zedboard.org/support/design/18891/146) - Make yourself an account.
It is worth noting that any forum posts about any Zynq devboard or implementation can be considered when debugging.

[http://krtkl.com/documentation/](http://krtkl.com/documentation/) - Snickerdoodle book and schematics

## Notes
#### Project Status
While the project currently works as is, wireless telemetry is not currently implemented, the automatic pitch control needs to be trained using real data from the car (real torque meter readings are necessary) and the SD card can only handle one file at a time (once it  has a file on it, it needs to be formatted if you want to log something again). 
#### Development Boards
Two Zynq-based development boards have been bought and used to develop SensTel2.0.
Peripheral validation was started using a MiniZed devboard - I included the code I use to validate each peripheral’s functionalities. The prototype was built using a Snickerdoodle board. The MiniZed has an onboard debugger/programmer, while the Snickerdoodle doesn’t - this is why you need a Digilent HS-3 and, if possible, a Krtkl's BreakyBreaky prototyping adapter (which has the right connector for the HS-3).

Two MiniZed, two Snickerdoodle and one HS3 are in stock at Chinook.

[http://zedboard.org/product/minized](http://zedboard.org/product/minized)
[https://store.digilentinc.com/jtag-hs3-programming-cable/](https://store.digilentinc.com/jtag-hs3-programming-cable/)
[https://krtkl.com/snickerdoodle/](https://krtkl.com/snickerdoodle/)
***
#### Flashing - Snickerdoodle and MiniZed

Follow the guide at p22/116 of the Snickerdoodle book to learn about the boot possibilities of the snicker board. They refer to the boot select [pins at MIO4 and 5]. Something useful to know is that these MIO are not controlled directly by the buttons but rather by the platform controller of the snickerdoodle - it reads the [Re/set and Select] buttons and consequently toggles the right pins.
* Holding down Select at powerup sets the snickerdoodle in the JTAG mode.
* Holding down the Re/set button sets it into QSPI boot mode.

Not pressing anything puts the snickerdoodle in SD card boot mode. This is the default way of booting the Snickerdoodle.

JTAG mode allows (and is necessary for) you to program directly the Flash memory chip on board (Micron N25Q128A11ESE40F). QSPI mode allows the Snickerdoodle to pass a boot image to U-Boot, which handles loading the FPGA bit stream and the application C code .elf file.

  

To upload your hardware system’s bit stream and binary code, you have to power cycle the Snickerdoodle while making sure to press the Select button upon power up. All the LEDs will light up and shut off, signaling you can release the button. After programming the flash, if using the standard Platform Controller firmware, you have to power cycle it again but while holding down the Re/Set button. This will have you boot with your code without JTAG and SD card.

  

To know how to create the FSBL, follow: Tutorial 04 FSBL and Boot from QSPI (get it at
[http://zedboard.org/support/design/18891/146)](http://zedboard.org/support/design/18891/146)

The zip contains a tutorial pdf to instruct you how to build the FSBL for the Minized. The steps are pretty much identical than for the Snickerdoodle, except that you have to specifiy the FSBL even at the moment of flashing the image.
***
#### Flashing - Troubleshooting
**Vivado Hardware manager:**
If by accident you happen to lose power while programming the boot image to the Flash memory, you can erase the Flash’s contents. The functionality is in Vivado's Hardware Manager tool. Follow these instructions and make sure to choose the full erase: 
[https://forums.xilinx.com/t5/Configuration/Erase-dump-flash-memory-attached-to-Zynq-device-using-Vivado-IDE/td-p/821603](https://forums.xilinx.com/t5/Configuration/Erase-dump-flash-memory-attached-to-Zynq-device-using-Vivado-IDE/td-p/821603)

 
**“Problem in running uboot, Flash programming failed”:**
This happened to me after losing power while programming the flash. I got the message repeatedly when the Program Flash process was started. That and neverending progress bar waits. I found a solution in message 17 of the following forum post:[https://forums.xilinx.com/t5/Embedded-Boot-and-Configuration/Can-t-flash-QSPI/td-p/813536/page/2](https://forums.xilinx.com/t5/Embedded-Boot-and-Configuration/Can-t-flash-QSPI/td-p/813536/page/2)

It happened that the Digilent HS-3 JTAG programmer was effectively  still in a debugging session or was still at the same point that it was when I lost power and the process got compromised. What I did was:

-   In SDK and with the current project opened, I used the Program FPGA to manually program the Zynq’s PL
-   I launched a debug session, which went fine. That application ran as good as it did before.
    
-   I made sure the second core was in the Suspend state and paused the first. I disconnected and closed the debug session.
    
-   I made sure no breakpoints were enabled.
    
-   I power cycled the snickerdoodle while selecting JTAG boot mode
    
-   I power cycled the HS3 programmer
    
-   The flashing process was successful again after that.
***
#### Xilinx Development Tools - Troubleshooting & tips:
-   **Vivado and SDK:** Whenever you have the opportunity to specify a path, at least verify it - especially with Vivado, the project or output paths are usually the ones from the last opened project so that can mess your workspace pretty quickly if you don’t.
-  **Vivado:** Don’t forget that the last step before exporting hardware is bitstream generation
- **Vivado:** Adding and using a new IP Core can be problematic; the data sheets can be vague and pin names are possibly far from being self-explanatory. You’ll have to search forums and, sometimes, dig deep and carry out “sub-searches” for every possible leads you found.
- **SDK:**-   SDK: While stepping through your code when debugging, to be able to see the actual C drivers code and not its assembly, add the compiler flags “-g3 -O0” in the project’s bsp settings.
-   **SDK:** Eclipse has “perspectives”, which are IDE GUI tools layouts. The different layouts are organized to better suit a particular task like writing code or debugging. When going to Debug perspective, in SDK you’re stuck in this one even if the debug session is over. To go back to editing perspective, go to menu bar: Windows-> Perspective-> Open Perspective-> C/C++.
-   **SDK:** To end a debug session, press “Disconnect”. See picture below. A clean disconnection is always better - especially with the HS3 Xilinx JTAG Programmer.
-   **SDK:** I’ve ran into this annoying problem where the Fatfs library references become “undefined”. This is obviously not a problem if you haven’t chosen to include these files when you first setup the SDK project. I haven’t found the root of the problem but the workaround I used was to either “Re-generate the BSP sources” or to entirely delete it from the disk and creating another one.
***
#### Custom Platform Controller firmware:
Having the SD card boot as default instead of QSPI was annoying so I had to change the boot default in the platform controller’s firmware.

Their Platform Controller’s source code are now open and available here:
[https://github.com/krtkl/snickerdoodle-STM32F078-firmware](https://github.com/krtkl/snickerdoodle-STM32F078-firmware)

To be able to work with the project as-is, you have to install Keil uVision MDK-Lite. Page 60/116 of the Snickerdoodle book has the link you can get the Lite version at. I installed the IDE, had issues with unsupported device but didn’t care about it and left it at that. **UPDATE**: Do leave the error as is, get the STM32F078 pack at :[http://www.keil.com/dd2/stmicroelectronics/stm32f078vbhx/#/eula-container](http://www.keil.com/dd2/stmicroelectronics/stm32f078vbhx/#/eula-container)

I could then compile the code and complete page’s 60/116 guide. When a modification is made and you’re ready to program the controller, put it in DFU mode and follow the steps at page 61/116.

**DFU Mode:** Pressing down both buttons at the same time didnt prove useful for me; the board seems to enter the mode at first but like 500ms after leaving the buttons the board went back to another mode, preventing the DFuse app to see the hardware.

Power cycling while shorting the R55 pads worked though. You’ll know selecting DFU mode has worked when the green LED will have shut down and the Dfuse Demo app will list the mcu as a target.

The modifications I made changes the default boot mode as QSPI, and SD card boot is still accessible when power cycling with Re/Set held down.
***
**Hardware Prototype - Logging SD Card**
Pay attention to the micro SD card adapter permission switch: pushing it towards the adapter’s signal contacts clears the read-only signal; otherwise its in write-protection mode and you won’t even be able to initialize it. I personally taped the switch in the right position.
***

## Authors

* **Jérôme Paré-Lépine** SoC architecture, C FreeRTOS-based application code, firmware code, test code, prototype hardware bring up and documentation.
* **Vincent Cournoyer** Neural network IP Core and training implementation.

