# RP2040_XOC
Extreme Overclocking on Raspberry Pi's RP2040 chip
-

This repository has the tools needed for extreme overclocking on the Raspberry Pi RP2040. It assumes that the RP2040 is attached to a Raspberry Pi Pico.

Note - This will drastically degrade the lifetime of the chip and will perminantly damage it. It is also very likely that it will destroy the chip in question.

Software Overview
-
XOC provides the code to run the RP2040 off the Ring Oscillator, allowing for marginally higher clock speeds, but more importantly, a clock that changes dynamically with voltage.

XOC_dhry implements the XOC code into a version of Dhrystone, originally made by Reinhold P. Weicker, adapted for the Pico by Roy Longbottom (http://www.roylongbottom.org.uk/)

clock_stat is adapted from the pico-examples (https://github.com/raspberrypi/pico-examples/blob/master/clocks/), and is used to classify fast chips before beginning the overclocking process

Equipment Needed
-
- External Power Supply capable of outputting 1.1V to ~3.1V at upto 0.8A
- Soldering station
- Cooling solution (highly recommended)

Chip Selection
-
If you have a range of RP2040s to use, run clock_stat on each, taking note of the ring oscillator (ROSC) frequency. The higher the ROSC frequency, the faster the chip.

Core Voltage
-
In order to change the voltage above the RP2040's 1.3V maximum, the tracks between VSEL and DVDD have to be cut, and wires soldered to the DVDD side directly. Below is an image of the back of the Pico, showing where to make the cuts (red lines across the thick tracks), and where to remove the solder mask (red squares) so that wires can be added.

![](../pico_cuts.jpg)

Once complete, wire up the Pico as shown:

![](../pico_wires.jpg)

I'd recommend gluing the wires down to the Pico as they can rip off without much force.

Running the Test
-
To run the test, connect a power supply to the wires - this will control the core volts. Initially set it to 1.1V, and load the XOC_dhry.uf2 onto the Pico. Make sure your cooling solution is in place and at desired temperature (1000 MHz was reached when the chip was cooled to -40 Celcius), then slowly increase the voltage to overclock.