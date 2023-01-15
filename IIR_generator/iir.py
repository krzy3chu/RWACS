from scipy import signal
import matplotlib.pyplot as plt
import numpy as np
from csnake import CodeWriter, Variable

rank = 6        # continuous transfer function rank
zeroes = -100   # zeroes value
fs = 200        # sampling time [Hz]
T = 0.3         # step response end time [s]

z_c = []                      # continues transfer function zeroes
p_c = np.full(rank, zeroes)   # continues transfer function  poles
k_c = pow(-zeroes, rank)      # continues transfer function gain

[z, p, k, ts] = signal.cont2discrete((z_c, p_c, k_c), 1/fs, method="zoh")     # compute discrete form
sos = signal.zpk2sos(z, p, k, pairing='minimal', analog=False)                # convert to sos form

biquad = np.delete(sos, 3, axis=1)              # delete 3rd column, which should consist only ones, to obtain digital biquad form
biquad[:, 3:5] *= -1                            # change a0 a1 coefficients signs
biquad_num = len(biquad)                        # number of biquad stages
coeffs = np.concatenate(biquad)             # convert array into vector of coefficients

# ------------------ plot step response ------------------ #

t = np.arange(0, T, 1/fs)
t, y = signal.dstep((z, p, k, ts), t=t)
plt.plot(t, np.squeeze(y))
plt.grid()
plt.show()

# ----------------- .c/.h files generator ----------------- #

#  create c variable instances
IIR_coeffs = Variable("IIR_coeffs", "float", value=coeffs)

#  IIR/iir.h header file
INCLUDE_GUARD = "INC_IIR_H_"
fir_h = CodeWriter()
fir_h.add_autogen_comment("iir.py")
fir_h.add_line()
fir_h.start_if_def(INCLUDE_GUARD, invert=True)
fir_h.add_define(INCLUDE_GUARD)
fir_h.add_line()
fir_h.add_define("IIR_NUM_STAGES", biquad_num)
fir_h.add_line()
fir_h.add_variable_declaration(IIR_coeffs, extern=True)
fir_h.add_line()
fir_h.end_if_def()
fir_h.write_to_file("../STM32_firmware/Components/Iir/Inc/iir_coeff.h")
print("iir_coeff.h file generated")

#  IIR/iir.c source code file
fir_c = CodeWriter()
fir_c.add_autogen_comment("iir.py")
fir_c.add_line()
fir_c.include("iir.h")
fir_c.add_line()
fir_c.add_variable_initialization(IIR_coeffs)
fir_c.write_to_file("../STM32_firmware/Components/Iir/Src/iir_coeff.c")
print("iir_coeff.c file generated")
