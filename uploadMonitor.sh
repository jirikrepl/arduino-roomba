#!/bin/bash

# upload and monitor
platformio -c clion run --target upload -e uno && platformio -c clion device monitor -e uno