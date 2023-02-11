# :artificial_satellite: Reaction Wheel Attitude Control System :artificial_satellite:


**RWACS** is a platform that simulates a real spacecraft attitude control.


<p align="left">
  <img src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white">
  <img src="https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white"> 
</p>

## Goal :dart:
The objective of this project was to design a device that could alter and sustain its position through the utilization of a reaction wheel. The **RWACS** device is able to hold its position steady and move to a predetermined location. The desired position can be set through the use of an **encoder** or a **graphical user interface**. To achieve this, **custom hardware modules** were developed and can be accessed in the "Components" folder.
<p align="center">
  <img src="/README_FILES/POSITION_STAY.gif" alt="position stay"/>
</p>

<p align="center">
  <img src="/README_FILES/POSITION_CHANGE.gif" alt="position change"/>
</p>

## Core components 
* DRV8825 stepper motor driver
* NEMA 17 stepper motor
* Incremental encoder
* MPU6050 IMU
* NUCLEO-F746ZG
## Controller
The attitude control of this device is accomplished with high precision and efficiency through the utilization of a **PID controller**. This controller can be optimized through the alteration of its proportional, integral, and derivative gain parameters. Given the presence of an integral component in the plant model, it was decided to set the integral gain to zero. The implementation of the **PID controller** was carried out utilizing the functions provided by the **CMSIS library**.

<p align="center">
  <img src="/README_FILES/RWACS.png" alt="graph"/>
</p>

## GUI
A dedicated **graphical user interface** was created to enhance the interaction experience with the **RWACS**. The development utilized **Python** programming language and **PySimpleGUI library**. The app allows one to change setpoint and PID gains. In addition, it displays and saves data transmitted by the device in a "log.csv" file for further analysis and plotting by the user.
<p align="center">
  <img src="/README_FILES/GUI.gif" alt="GUI"/>
</p>


## 3D model
A custom **3D model** was created and 3D printed in the FDM technology. Files are provided in the repository under the "3D_model" folder.
## Doxygen documentation
A **doxygen documentation** was created for easy reference, and can be accessed in the "Doxygen" folder.
