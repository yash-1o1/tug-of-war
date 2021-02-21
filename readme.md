# Tug Of War Application 

### Requirements 
This code requires the [Educational BoosterPack MKII (BOOSTXL-EDUMKII)](http://www.ti.com/tool/BOOSTXL-EDUMKII) paired with the MSP-EXP432P401R LaunchPad. The code has been written In C and could be flashed onto your board via the code composer studio

### Application Description

This is a simple tug of war game designed to run on the MSP 430 board. 

The configuration of the buttons is in such a way that they can control two predefined variables LEFT and RIGHT in the following manner:
 
* Holding L2 (the rightmost Launchpad button) increase LEFT.
* Holding L1 (the leftmost Launchpad button) should decrease LEFT.
* Holding B1 (the topmost Boosterpack button) should increase RIGHT.
* Holding B2 (the bottommost Boosterpack button) should decrease RIGHT

Working of the application:

* If the magnitude of the difference between LEFT and RIGHT is within [0, 10], LED1 is turned on.

* If LEFT surpasses RIGHT by at least 10, then BLED light lits up. BLED’s three individual LED components need to be lit according to the following logic:
    ○If LEFT surpasses RIGHT by [10, 20], BLED’s red LED lights up.
	○If LEFT surpasses RIGHT by [20, 30], BLED’s green LED lights up.
	○If LEFT surpasses RIGHT by [30, 40], BLED’s blue LED lights up.

* If RIGHT surpasses LEFT by at least 10, then LED2 needs to be lit. LED2’s three individual LED components need to be lit according to the following logic:
	○If RIGHT surpasses LEFT by [10, 20], LED2’s red LED lights up.
	○If RIGHT surpasses LEFT by [20, 30], LED2’s green LED lights up.
	○If RIGHT surpasses LEFT by [30, 40], LED2’s blue LED lights up.

##### This application was done under the help and guidance of Dr. Leyla Nazhandali
[ Visit the documentation created by Dr. Leyla Nazhandali for more information and guidance with MSP-EXP432P401R LaunchPad. ](https://sites.google.com/vt.edu/introduction-to-embeddedsystem/home) 