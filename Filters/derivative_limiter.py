import matplotlib.pyplot as plt
import numpy as np


dx1_lim = 20000        # first derivative signal limit
dx2_lim = 80000        # second derivative signal limit

fs = 50                    # sampling frequency [Hz]
T = 1                      # end time [s]
t = np.arange(0, T, 1/fs)   # time vector

# ---------- reference signal ---------- #
y = 2400*np.ones_like(t)
y[0] = 0
# y[5*fs:] = t[5*fs:] - 5
# y[8*fs:] = -0.2*t[8*fs:] + 5

y_out = np.zeros_like(y)        # output signal
# y_ctrl = np.zeros_like(y)       # auxiliary output control signal
y_ctrl = y.copy()

for i in range(1, T*fs):

    y_out[i] = y[i]
    dy = (y[i] - y[i-1]) * fs                   # reference signal first derivative
    dx1a = (y_out[i - 1] - y_out[i - 2]) * fs   # output signal older first derivative

    # ---------- protect from overshooting ---------- #
    dtr = pow((dx1a - dy), 2) / (2 * dx2_lim)  # distance on vertical axis to meet with reference signal
    if abs(y[i - 1] - y_out[i - 1]) <= dtr and y_out[i - 1] != y[i - 1]:     # if actual difference is lower than dtr
        pull = 0                                # pulls output signal up if positive, down if negative
        if y[i-1] > y_out[i-1]:                 # if reference signal is greater than output
            if dy < dx1a:
                pull = -0.1
            else:
                pull = 0.1
        else:
            if dy > dx1a:
                pull = 0.1
            else:
                pull = -0.1
        y_out[i] = y_out[i - 1] + pull
        y_ctrl[i] = y_out[i]                    # auxiliary

    dx1b = (y_out[i] - y_out[i - 1]) * fs       # output signal younger first derivative
    dx2 = (dx1b - dx1a) * fs                    # output signal second derivative

    # ---------- first derivative limiter ---------- #
    if dx1a > dx1_lim:
        y_out[i-1] = y_out[i - 2] + (dx1_lim / fs)
    if dx1a < -dx1_lim:
        y_out[i-1] = y_out[i - 2] - (dx1_lim / fs)

    # ---------- second derivative limiter ---------- #
    if dx2 > dx2_lim:
        y_out[i] = -y_out[i-2] + 2*y_out[i-1] + (dx2_lim / pow(fs, 2))
    if dx2 < -dx2_lim:
        y_out[i] = -y_out[i-2] + 2*y_out[i-1] - (dx2_lim / pow(fs, 2))

# ---------- auxiliary operations just for plotting purposes ---------- #
# y_ctrl = y_out.copy()
# y_ctrl[y > y_out] += 0.1
# y_ctrl[y < y_out] += - 0.1

# ---------- plot results ---------- #
plt.plot(t, y)
# plt.plot(t, y_ctrl)
plt.plot(t, y_out)
plt.grid()
plt.show()
