from scipy import signal
import matplotlib.pyplot as plt
import numpy as np
from csnake import CodeWriter, Variable

#  generate test signal
fs = 200      # sampling time [Hz]
T = 0.5         # end time [s]
t = np.linspace(0, T, int(T*fs), dtype=np.float32)           # time array
sig = np.ones_like(t)
plt.plot(t, sig)

#  calculate filter coefficients
n = 41          # filter length
cutoff = 1       # low pass filter cutoff frequency [Hz]
b = signal.firwin(n, cutoff, fs=fs)     # fir coefficients
filtered = signal.lfilter(b, [1.0], sig)
plt.plot(t, filtered)
plt.grid()
plt.show()

# ----------------- .c/.h files generator ----------------- #

#  create c variable instance
FIR_b = Variable("FIR_b", "float", value=b)

#  Fir/fir.h header file
INCLUDE_GUARD = "INC_FIR_H_"
fir_h = CodeWriter()
fir_h.add_autogen_comment("fir.py")
fir_h.add_line()
fir_h.start_if_def(INCLUDE_GUARD, invert=True)
fir_h.add_define(INCLUDE_GUARD)
fir_h.add_line()
fir_h.add_define("FIR_LENGTH", n)
fir_h.add_line()
fir_h.add_variable_declaration(FIR_b, extern=True)
fir_h.add_line()
fir_h.end_if_def()
fir_h.write_to_file("../STM32_firmware/Components/Fir/Inc/fir_coeff.h")
print("Generated fir_coeff.h file")

#  Fir/fir.c source code file
fir_c = CodeWriter()
fir_c.add_autogen_comment("Fir_generator/fir.py")
fir_c.add_line()
fir_c.include("fir_coeff.h")
fir_c.add_line()
fir_c.add_variable_initialization(FIR_b)
fir_c.write_to_file("../STM32_firmware/Components/Fir/Src/fir_coeff.c")
print("Generated fir_coeff.c file")
