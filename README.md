# Automation1 Tango Driver



## Installation

The Automation1 Tango driver is distributed as source code and must therefore be built and configured before it can be used.


### Prerequisites

Building the driver requires:
* the usual build tools (e.g., a C++ compiler, etc),
* a working Tango installation,
* and the Automation1 C libraries and headers. 

Here we assume that the user has a working Tango distribution (we recommend
building and installing the Tango Source Distribution following the instructions here:
https://tango-controls.readthedocs.io/en/latest/How-To/installation/linux-debian.html#compilation-of-the-tangosourcedistribution).

Alternatively users new to Tango may want to perform a relatively quick binary installation of Tango to
work with the Automation1 Tango driver. This is straightforward to do using the conda
package manager (which we assume is already installed) and the conda-forge distribution
channel. 

1) Create a new conda environment for Tango XX (here we use v`9.5` but other versions may be used). The environment will be called `automation1`:

   ```
   conda create -n automation1 -c conda-forge python=3.10.12 cpptango=9.5 cppzmq omniorb pkg-config pogo make jive
   ```
 
2) This environment can then
be activated and the Tango database server can then be started using:

   ```
   conda activate automation1

   PyDatabaseds 2
   ```

Once Tango has been installed (either through the Tango Source Distribution or with `conda`) you will need to start the database:

```
sudo $TANGO_HOME/bin/tango start
```
where `TANGO_HOME` is the root path to where Tango is installed (typically this will be `/usr/local` or the conda environment prefix `$CONDA_PREFIX`)

### Version compatibility

This Automation1 driver is compatible with:
* Automation1 API v2.9 and onwards
* Tango v9.3 up to v10.3.3 (\*)

*\* Note, other versions have not been tested but may still work.*

### Building

The build environment expects several environment variables to be set. These include:
* `TANGO_HOME` - the root path to where Tango is installed (typically this will be `/usr/local` or the conda environment prefix `$CONDA_PREFIX`)
* `A1LIB_HOME` - the path to the Aerotech-provided Automation1 C library files
* `A1HEADER_HOME` - the path to the Aerotech-provide Automation1 C header files

Additionally, running the driver will require several environment variables to be set:
* `LD_LIBRARY_PATH` - this should include `$TANGO_HOME/lib`
* `TANGO_HOST` - most installations will use `localhost:10000;` consult the Tango
documentation for more details.

Once these variables are set, the driver source code can be obtained from git:

```
git clone
git@github.com:Observatory-Sciences/Automation1_Tango.git
```

and built by entering the created directory and invoking make:

```
cd Automation1_Tango
make
```

This will create the Automation1 driver executable as `bin/Automation1`.


## Setting up an Automation Controller as a Tango Device Server

Automation1 controllers must be registered as Tango devices inside of a Tango device server
to operate with the Tango driver. Users familiar with Tango will likely have created devices
using the `Jive Setup Wizard`, but we also provide a command line method for setting up
the required devices. This requires having PyTango installed, which can be done either
through conda or pip, e.g.
```
pip install pytango
```

A device server can quickly be created for an Automation1 controller using the provided
`register_device_server.py` script. This script registers a new device server with the
Tango database and creates a controller device and a (specified) number of axis devices. A
typical invocation of the script would be something like:

```
python register_device_server.py [device server instance name] [device name prefix] [controller IP address] [number of axis devices to create]
```

or more concretely:

```
python register_device_server.py Automation1Driver Automation1/TestDevices 192.168.1.100 2
```
where 
* `Automation1Driver` is the name of the device server instance,
* `Automation1/TestDevices` is the root name of each device,
* `192.168.1.100` is the IP
address of the controller,
* and `2` is the number of axis devices created.

This will result in one Tango `A1Controller` device being created called
`Automation1/TestDevices/controller` and two `A1Axis` devices being created
called `Automation1/TestDevices/axis0` and `Automation1/TestDevices/axis1`.
Additional help in using the script can be obtained by passing it a `--help` flag:
```
python register_device_server.py --help
```

## Running the Device Server
To use the Automation1 driver and device server created in the previous steps, we must
invoke the driver executable with the device server instance name:
```
bin/Automation1 Automation1Driver
```
where: `Automation1Driver` is the name of the device server instance used in the previous section.

The `Jive` application can be used to view properties of the Tango devices and to bring up
`ATKPanel`s for each device. These `ATKPanel`s allow attributes to be set and commands to
be issued to the controller and axes. Double-click the instance of a class (e.g.,
`Automation1/TestDevices/Axis0`) to launch the `ATKPanel`. Note that you will
receive an error if you haven’t started up the device server from the terminal before
attempting to open an `ATKPanel`.
