#!/bin/bash

cmake --build .

sudo cp ./rundir/Debug/obs-plugins/64bit/iklanlive-plugin.so /usr/lib/obs-plugins