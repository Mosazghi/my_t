# my_t

**my_t** is a highly configurable serial monitor that reads and writes data to/from serial ports. It also displays graphs for key-value variables, making it an valuable tool for debugging and testing embedded systems.

 

https://github.com/Mosazghi/my_t/assets/116307580/9f696b01-4fc4-47d3-8cb7-e7f8425e95b7


## Features

- **Serial communication**: read and write data to and from serial ports.
- **Data visualization**: display charts for key-value data in real-time.
- **Highly configurable**: customize settings to suit your specific needs.

## Installation Guide

**Note:** my_t has only been tested on Ubuntu 22.04 LTS or later.

A Windows deployment is planned for the future.

1. **Download the Installer**

   - Go to the [release page](https://github.com/Mosazghi/my_t/releases) of the repository.
   - Download the `installermy_t.run` file.

2. **Install my_t**

   - Open a terminal and navigate to the directory where the `installermy_t.run` file was downloaded.
   - Make the installer executable:

     ```sh
     chmod +x installermy_t.run
     ```

   - Run the installer:

     ```sh
     ./installermy_t.run
     ```

   - Follow the on-screen instructions to complete the installation.

3. **Run my_t from Anywhere**

   By default, to run the application, you need to navigate to the installation
   directory and run `my_t.sh` or alternatively search for `my_t` in the application menu.

   However, this can be inconvenient.

   To run `my_t` from any directory, you can either add the installation directory to your PATH or create a symbolic link:

   Fastest way is to create a symbolic link to `my_t.sh` in `/usr/local/bin`:

   ```sh
   sudo ln -s ~/my_t/my_t.sh /usr/local/bin/my_t
   ```

   Run `my_t` from anywhere by typing:

   ```sh
   my_t
   ```
