# Nixie Project
This is a collection of all the PCB designs and software I've written for an STM32-based
Nixie tube clock.

Nixie tubes are some really neat old displays from back during the 1960s, though they kept being
used in the USSR for quite a while, so you can find them on ebay being sold from various
post-soviet states. They have a pretty cool signature orange-ish glow that looks cool, so
I wanted to make a digital clock with them.

Note: Nixies operate at high voltage (albeit very low current), so make sure to exercise caution
when working with them!

<br>

Online image of a Nixie clock (hopefully once mine is built I can replace this image with my own!)
<img width="500" src="https://github.com/user-attachments/assets/27458fbf-4d7b-4ec2-94c8-850ae7e4c9e9" />



## Project Structure
This is a bit unorganized and will likely soon be refactored, but at the moment this is the structure:
- 3D_Models: 3D models used in the PCBs (the NCH8200HV and my Micro USB connector)
- NixieProject.pretty: Footprint library
- nixies-us.pretty: A footprint library of various Nixie tubes
- nixies-us.mod: Schematic symbols for different Nixie tubes
- Single Tube Board: A PCB to power a single Nixie tube
- software: Software for the various projects
  - nixie_simple: Software for breadboard experiments
  - single_nixie: Software for single Nixie tube PCB
- symbols: Custom schematic symbols


## Part descriptions
- STM32F103C8T6: Microcontroller controlling the tubes
- NCH8200HV: Voltage booster, input 2.5-15V, output 170V
- AMS1117-3.3: 3.3V linear regulator
- K155ID1: BCD-to-decimal decoder

The rest of the parts should be pretty self-explanatory.
