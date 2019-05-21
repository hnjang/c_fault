#!/bin/bash
export LD_PRELOAD=/usr/lib/libefence.so
export EF_ALIGNMENT=1
./overrun $1
