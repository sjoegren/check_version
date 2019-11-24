![](https://github.com/akselsjogren/check_version/workflows/Build/badge.svg)

# check_version
Check if a program version meets a simple requirement.

Usage:

    $ git --version | check_version -r 'version ([0-9]+\.[0-9]+\.[0-9]+)' -c 2.0
    Result: 2.21.0 >= 2.0: true

## Build
Build:

    make

Test:

    make test
