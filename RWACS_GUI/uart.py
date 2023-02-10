import glob2 as glob
import serial


def decode_csv(data: bytes) -> list[float]:
    """Decode data that is in bytes and convert it into a list of floats

     Args:
        data (bytes): bytes to interpret and convert to a list

     Returns:
        list[float]: decoded csv data
    """
    return [float(idx) for idx in data.decode().split(', ')]


class Uart:
    """A class used to easily connect to uart with desired baudrate
    """

    def __init__(self, baudrate: int):
        rwacs_path = glob.glob("/dev/ttyACM*")
        self.__serial = serial.Serial(
            rwacs_path[0], baudrate)
        self.__serial.reset_input_buffer()

    def read(self) -> bytes:
        """Read uart until \n occurs

        Returns:
            bytes: a received message in bytes format
        """
        return self.__serial.readline()

    def send(self, receiver_id:int, data:int):
        """Send data to a desired receiver

        Args:
            receiver_id (int): where to send data
            data (int): data sent to the receiver
        """
        receiver_id = receiver_id.to_bytes(4, 'little', signed=True)
        data = data.to_bytes(4, 'little', signed=True)
        self.__serial.write(receiver_id + data)
        
    def reset(self):
        """Reset the buffer

        """
        self.__serial.reset_input_buffer()
