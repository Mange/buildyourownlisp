# buildyourownlisp #

Me teaching myself C by implementing a Lisp intepreter, loosly following the guide at [Build Your Own LISP](http://www.buildyourownlisp.com/).

## Dependencies ##

You need CMake to compile the project and [Check][check] to run tests.

The only supported platform right now is Mac OS X just beacuse I'm teaching myself on a OS X machine. When I understand more about the code, it should be possible to port to Linux trivially.

If you're a sadomasochist, you could help me port this to Windows. I might just read your pull request before I close it.

## Building ##

```
mkdir build
cd build
cmake ..
make
```

Binaries will be placed in `./build/bin`.

## Running tests ##

Build the project and run `ctest` from the `build` directory.

## License ##

Public domain. Do whatever you want. I claim no responsibility for the code.

[check]: http://check.sourceforge.net/web/install.html
