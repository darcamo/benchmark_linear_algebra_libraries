
# Benchmark linear algebra libraries

In order to use this code, install the conan package manager and run the command 

```sh
conan remote add darcamo-bintray https://api.bintray.com/conan/darcamo/cppsim
```

After that, run the command below from the build folder (.. points to the parent fonder, which contains the conanfile.txt file).

```sh
conan install .. --build=missing -s build_type=Release
```

Now you can run cmake and compile the code as usual.
