from enum import Enum

import PySimpleGUI as sg

from real_time_plot import RealTimePlot
from uart import Uart


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

    layout = [[sg.Text('kp'), sg.Push(), sg.InputText()],
              [sg.Text('ki'), sg.Push(), sg.InputText()],
              [sg.Text('kd'), sg.Push(), sg.InputText()],
              [sg.Text('setpoint'), sg.Push(), sg.InputText()],
              [sg.Button('Connect'), sg.Button('Run')],
              [sg.Multiline(size=(60, 10), key='-STLINE-', autoscroll=True, write_only=True, reroute_stdout=True)]]

    window = sg.Window('Rwacs settings', layout)

    while True:

        event, values = window.read()

        if event == sg.WIN_CLOSED:
            break

        elif event == 'Connect':
            try:
                uart = Uart(BAUDRATE)
                plot = RealTimePlot(NROWS, NCOLS, X_LIM)
            except IndexError:
                print("Rwacs unable to connect")
                continue

        elif event == 'Run':
            try:
                for single_id in ControllerIDs:
                    uart.send(single_id.value, values[single_id.value])
                    print(single_id.name, "set to", values[single_id.value])

            except ValueError:
                print("Enter proper controller variables")
                continue

            except NameError:
                print("Rwacs not connected")
                continue
            
            uart.read()
            
            while True:
                message = uart.read()
                if message[0] == CSV_SYMBOL:
                    try:
                        csv_data = uart.decode_csv(message[1:])
                        csv_len = len(csv_data)
                        if csv_len != CSV_LEN:
                            print("Expected csv length: " + str(CSV_LEN) +
                                  ", received: " + str(csv_len))
                            continue
                        plot.update(csv_data)
                    except ValueError:
                        print("Corrupted csv line")
                else:
                    print(message.decode())

    window.close()
