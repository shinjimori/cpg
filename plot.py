#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import numpy as np
from scipy.signal import hilbert
import matplotlib.pyplot as plt
#from math import sin, cos

def read_data(filename):
    """read  file, and return data and heltz"""
    f = open(filename, 'r')
    params_header = f.readline() # header of parameter
    params = f.readline() # parameter value
    items = params.split(' ')
    heltz = str(items[0])      # Hzの値を取得
    l = f.readline()      # header of variables
    n = len(l.split(' ')) # ヘッダーの数をカウント

    rec = [[] for i in range(n)]

    while len(l) != 0:
        l = f.readline()
        a = l.split(' ')
        if len(a) != n:
            break
        for i in range(len(a)):
            try:
                rec[i].append(float(a[i]))
            except:
                break
    f.close()
    return [rec, heltz]


def data_plot(rec):
    """ Plot data
    -----------------------------------------------------------
    hopf:  0 1     2     3  4  5  6  7  8  9
    rec    t omega theta xe ve xf vf ye yf y
    -----------------------------------------------------------
    """

    fig, ax1 = plt.subplots()
    plt.title("Synchronous between pendulum and oscillator")
    ax1.plot(rec[0], rec[3], "b-", label='xe')
    ax1.set_xlabel("t[s]")
    ax1.set_ylabel("inner state")
    for tl in ax1.get_yticklabels():
        tl.set_color("b")
    ax2 = plt.twinx()
    ax2.plot(rec[0], rec[2], "r-", label='pendulum angular')
    ax2.set_ylabel("pendulum angular[rad]")
    for tl in ax2.get_yticklabels():
        tl.set_color("r")

    plt.figure()
    plt.plot(rec[0], rec[7], label='ye')
    plt.plot(rec[0], rec[8], label='yf')
    plt.plot(rec[0], rec[9], label='y')
    plt.ylabel('angular[rad], angular velocity[rad/s]')
    plt.xlabel('t[sec]')
    plt.legend()
    plt.show()

def main():
    """
    main function
    """
    rec, heltz = read_data(str(sys.argv[1]))
    print(heltz)
    fs=100
    t = np.array(rec[0])
    signal=np.array(rec[9])

    analytic_signal=hilbert(signal)
    instantaneous_phase = np.unwrap(np.angle(analytic_signal))
    instantaneous_frequency = (np.diff(instantaneous_phase)/(2.0*np.pi)*fs)
    print(len(t), len(signal), len(analytic_signal),len(instantaneous_frequency))

    plt.subplot(2,1,1)
    plt.plot(t, signal, label='angle[rad]')
    plt.xlabel('time[sec]')
    plt.legend()

    plt.subplot(2,1,2)
    plt.plot(t[1:],instantaneous_frequency,label='instantaneous frequency')
    plt.xlabel('time[sec]')
    plt.ylim(0,5)
    plt.legend()
    plt.show()

    #data_plot(rec)

if __name__ == "__main__":
    main()
