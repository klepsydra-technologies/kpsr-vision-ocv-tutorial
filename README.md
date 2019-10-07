<p align="right">
  <img width="25%" height="25%"src="./images/klepsydra_logo.jpg">
</p>

# Vision OCV Tutorial

Tutorial for using the Vision OCV integration of Klepsydra.

# Installation Instructions
## System dependencies

* Ubuntu 14.04 or above
* Google Tests (https://github.com/klepsydra-technologies/googletest)
* ROS Indigo or above (optional)
* DDS (optional)
* Cmake 3.5.1 or above
* gcc for C++11 5.4.0 or above.
* Open CV (Version 3.4.x)

Note that Google Tests is pulled in automatically when installing this project and does not need separate installation.

## Klepsydra dependencies

* kpsr-core (installed with yaml support)
* kpsr-robotics
* kpsr-build (https://github.com/klepsydra-technologies/kpsr-build)

kpsr-build will be pulled in automatically by the install process of this project.

### Installation

## System installation

	sudo apt install build-essentials
	sudo apt install git
	sudo apt install cmake

## Installation

Given ```$KLEPSYDRA_HOME```, for example ```$HOME/klepsydra```:

```
cd $KLEPSYDRA_HOME
git clone https://github.com/kpsr-devs/kpsr-vision-ocv-tutorial.git
cd kpsr-vision-ocv-tutorial
git submodule update --init
mkdir build
cd build
cmake ..
make
make test
```

The cmake has the following options:
* -DKPSR_INSTALL_PATH for specifying the Klepsydra installation location (/opt/klepsydra by default)
* -DGTEST_PATH for the google test path (default is ../../googletest)
* -DKPSR_BUILD_PATH location of the ```kpsr-build``` repository

#  License

&copy; Copyright 2019-2020, Klepsydra Technologies, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are Copyright 2019-2020, Klepsydra Technologies
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

#  Contact

https://www.klepsydra.com
support@klepsydra.com
