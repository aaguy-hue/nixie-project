# Nixie Project
Hi! This is a collection of all the PCB designs and software I've written for an STM32-based
Nixie tube clock.

Nixie tubes are some really neat old displays from back during the 1960s, though they kept being
used in the USSR for quite a while, so you can find them on ebay being sold from various
post-soviet states. They have a pretty cool signature orange-ish glow that looks cool, so
I wanted to make a digital clock with them.

Note: Nixies operate at high voltage (albeit very low current), so make sure to exercise caution
when working with them!


## Project Structure
This is a bit unorganized and will likely soon be refactored, but at the moment this is the structure:
- 3D_Models: 3D models used in the PCBs (the NCH8200HV and my Micro USB connector)
- NixieProject.pretty: Footprint library
- nixies-us.pretty: A footprint library of various Nixie tubes
- nixies-us.mod: Schematic symbols for different Nixie tubes
- Single Tube Board: A PCB to power a single Nixie tube
- software: Software for the various projects
- symbols: Custom schematic symbols


## Part descriptions
- STM32F103C8T6: Microcontroller controlling the tubes
- NCH8200HV: Voltage booster, input 2.5-15V, output 170V
- AMS1117-3.3: 3.3V linear regulator
- K155ID1: BCD-to-decimal decoder

The rest of the parts should be pretty self-explanatory.