# Badgerloop Firmware Repository
*Authors: Eric Udlis, Ben Everson, Marco Kurzynski*

The staging ground for a complete pod-embedded refactor (not rewrite!)

## Setup

To download all necessary packages run
```bash
$ ./bloop-dev setup
```
This will
- Install build dependecies
- Setup pre-commit

## Setup Instructions
Run `./bloop-dev setup` to set up the build environment

### Local Build Instructions
Run `./bloop-dev build` to build the application using the local toolchain

### Cross Compilation
Run `./bloop-dev cross` to build the application for executtion on the Beaglebone Black

### Pre-Commit and Linting

Pre-commit is build into this repositoy. This automatically lints and formats your code on commit.

If your code fails a pre-commit check, you may need to re-run `git add` to add the changes.

To manually run the linter run `./bloop-dev lint`

## Repository Structure
Our driver and device source code is located in [embedded](embedded).

[Drivers](embedded/drivers) contains code that manages communication like i2c and CAN.

[Devices](embedded/devices) contains device specific code to manage devices like the motor controller and IO expanders.

## Contributing
Check out our [CONTRIBUTING](CONTRIBUTING.md) document to see how you can start getting involved!

## Testing
TODO...
