from enum import Enum

import PySimpleGUI as sg

from real_time_plot import RealTimePlot
from uart import Uart, decode_csv


class ControllerIDs(Enum):
    """Rwacs controller ids used to send data
    """
    KP = 0
    KI = 1
    KD = 2
    SETPOINT = 3


BAUDRATE = 112500

NROWS = 2
NCOLS = 2
X_LIM = 20

CSV_SYMBOL = 64
CSV_LEN = NROWS * NCOLS

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

              [sg.Button('Connect'), sg.Button('Run')],
              [sg.Multiline(size=(60, 10), autoscroll=True, write_only=True, reroute_stdout=True)]]

    window = sg.Window('Rwacs settings', layout)

    while True:

        event, values = window.read()

        if event == sg.WIN_CLOSED:
            break

        elif event == 'Connect':
            try:
                uart = Uart(BAUDRATE)
                plot = RealTimePlot(NROWS, NCOLS, X_LIM)
                print("Rwacs connected")
            except IndexError:
                print("Rwacs unable to connect")

        elif event in [id.name for id in ControllerIDs]:
            current_id = ControllerIDs[event].value
            try:
                data = int(values[current_id])
            except ValueError:
                print("Enter data in correct format")
                continue
            try:
                uart.send(current_id, data)
                print("Sent: " + str(data) + " to " + event)
            except NameError:
                print("Rwacs disconnected")

        elif event == 'Run':
            errors = 0
            try:
                uart.read()
                while True:
                    message = uart.read()
                    if message[0] == CSV_SYMBOL:
                        try:
                            csv_data = decode_csv(message[1:])
                            print(message.decode())
                            if len(csv_data) != CSV_LEN:
                                raise ValueError(
                                    "Data differs from what was declared")
                            plot.update(csv_data)
                        except ValueError:
                            errors += 1
                            if errors > 9:
                                errors = 0
                                print("Unable to decode and plot")
                                break
                    else:
                        print(message.decode())
            except NameError:
                print("Rwacs disconnected")

    window.close()
