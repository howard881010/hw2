import matplotlib.pyplot as plt
import numpy as np
import serial
import time

serdev = '/dev/ttyACM0'

s = serial.Serial(serdev)

freq = int(s.readline())
Fs = 50 * freq;  
Ts = 1.0 / Fs; 
y = np.arange(0, 1.0 / freq * 2, Ts) 
n = len(y)
k = np.arange(n)
t = np.arange(0, 1.0 / freq * 2, Ts) 

T = n/Fs
frq = k/T 
frq = frq[range(int(n/2))] 

for x in range(0, int(100)):

    line=s.readline()
    y[x] = float(line)

Y = np.fft.fft(y)/n*2 

Y = Y[range(int(n/2))]
fig, ax = plt.subplots(2, 1)

ax[0].plot(t,y)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')
ax[1].plot(frq,abs(Y),'r')
ax[1].set_xlim([0, freq * 8]);
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')
plt.show()
s.close()
