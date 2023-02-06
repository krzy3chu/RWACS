"""
    This file makes it easy to interact with the RWACS
    """

from enum import Enum
from threading import Thread
import numpy as np
import matplotlib.pyplot as plt
import PySimpleGUI as sg
from uart import Uart

BAUDRATE = 115200
CSV_FILE = "log.csv"
RECORDING = False


def record_logs():
    """
    Save uart data to the csv file
    """
    uart.read()
    try:
        with open(CSV_FILE, "w", encoding="utf-8") as csv_file:
            while RECORDING is True:
                csv_file.write(uart.read().decode())
    except NameError:
        print("Rwacs is not connected")


def plot_logs():
    """
    Plot received data
    """
    plt.plot(np.genfromtxt(CSV_FILE, delimiter=',')[:,0:2])
    plt.grid()
    plt.show()


class ControllerIDs(Enum):
    """Rwacs controller ids used to send data
    """
    KP = 0
    KI = 1
    KD = 2
    SETPOINT = 3


if __name__ == '__main__':

    sg.theme('DarkBlack')

    layout = [[sg.Text('kp:'), sg.Push(), sg.InputText(),
               sg.Button('set', key=ControllerIDs.KP.name)],

              [sg.Text('ki:'), sg.Push(), sg.InputText(),
               sg.Button('set', key=ControllerIDs.KI.name)],

              [sg.Text('kd:'), sg.Push(), sg.InputText(),
               sg.Button('set', key=ControllerIDs.KD.name)],

              [sg.Text('setpoint:'), sg.Push(), sg.InputText(),
               sg.Button('set', key=ControllerIDs.SETPOINT.name)],

              [sg.Button('Connect'), sg.Push(), sg.Button(
                  'Record logs'), sg.Button('Stop recording'), sg.Button('Plot')],
              [sg.Multiline(size=(60, 10), autoscroll=True, write_only=True, reroute_stdout=True)]]

    window = sg.Window('Rwacs settings', layout)

    while True:

        event, values = window.read()

        if event == sg.WIN_CLOSED:
            break

        elif event == 'Connect':
            try:
                uart = Uart(BAUDRATE)
                print("Rwacs is connected")
            except IndexError:
                print("Rwacs is unable to connect")

        elif event in [id.name for id in ControllerIDs]:
            current_id = ControllerIDs[event].value
            try:
                data = int(values[current_id])
            except ValueError:
                print("Enter data in the correct form")
                continue
            try:
                uart.send(current_id, data)
                print("Sent: " + str(data) + " to " + event)
            except NameError:
                print("Rwacs is not connected")

        elif event == 'Record logs':
            if RECORDING is False:
                RECORDING = True
                thread = Thread(target=record_logs)
                thread.start()
                print("Recording started")
            else:
                print("Logs are already being recorded")

        elif event == 'Stop recording':
            RECORDING = False
            print("Recording stopped")

        elif event == 'Plot':
            try:
                plot_logs()
            except ValueError:
                print("CSV file has to be repaired")

    window.close()
