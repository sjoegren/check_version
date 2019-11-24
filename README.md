![](https://github.com/akselsjogren/check_version/workflows/Build/badge.svg)

# check_version
Check if a program version meets a simple requirement.

Usage:
```console
$ git --version | check_version -r 'version ([0-9]+\.[0-9]+\.[0-9]+)' -c 2.10.0
Result: 2.21.0 >= 2.10.0: true
$ echo $?
0

$ tmux -V | check_version -r '([0-9]+\.[0-9]+)' -c 2.4
Result: 2.1 >= 2.4: false
$ echo $?
1
```


## Build
Build:

    make

Test:

    make test
