![](https://github.com/akselsjogren/check_version/workflows/Build/badge.svg)

# check_version
Check if a program version meets a simple requirement.

Usage:
```console
$ git --version | check_version -r 'version ([0-9]+\.[0-9]+\.[0-9]+)' -c 2.10.0
Result: 2.21.0 >= 2.10.0: true
$ echo $?
0

$ tmux -V | check_version --regex '([0-9]+\.[0-9]+)' --check-version 2.4
Result: 2.1 >= 2.4: false
$ echo $?
1

$ echo "hatch v4.8.15.16.23.42" | check_version -r 'v([0-9]+\.[0-9]+\.[0-9]+)' --mode=gt -c 4.8
Result: 4.8.15 > 4.8: true
$ echo "hatch v4.8.15.16.23.42" | check_version -r 'v([0-9]+\.[0-9]+\.[0-9]+)' --mode=le -c 4.8.20 --quiet
$ echo $?
0
```


## Build
Build:

    make

Test:

    make test
