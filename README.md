pico-bme688
===========

This project creates a _library_ for the BME688-sensor for the Raspberry Pi Pico. It mainly implements the
platform-specific functions needed by the official API of Bosch-Sensortec.

You usually don't use this project directly, but use it as git-submodule for an application
program. See [pico-bme688-forced](https://github.com/bablokb/pico-bme688-forced) for an
example.


Build
=====

After checkout, run

    git submodule update --init

This pulls in the git-repo from Bosch-Sensortec. Then run

    mkdir -p build
    cd build
    cmake ..
    make
    cd ..

The library is in `build/lib/libbme68x.a`. Headers are in `lib/include`.
