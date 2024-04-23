# DVM - Dragon Virtual Machine

![](https://img.shields.io/github/actions/workflow/status/Cybegon/DVM/ci.yml?logo=GitHub&style=for-the-badge)
![](https://img.shields.io/github/license/Cybegon/DVM?color=0aa4ff&logo=GitHub&style=for-the-badge)

### Build

| Target      | Dependencies                        | Description                               |
|-------------|-------------------------------------|-------------------------------------------|
| dvm         | libdvm, libdvm-base, libcar         | Build an executable file                  |
| libdvm      |                                     | Build dvm as static library               |
| libdvm-base | libgeff, zip, libdvm-headers only   | Library that provides basic functionality |
| libgeff     |                                     | General executable file format            |
| libcar      | libdvm-headers only                 | CAR - Cybegon Architecture                |
| libcar-gen  | libdvm-headers, libcar-headers only | CAR Bytecode generator                    |

Update git submodules:
```
git submodule update --init --recursive
```


Build an executable file:
```
cmake -G "Ninja" -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --target dvm
```

## External libraries used by DVM

-   [minizip-ng](https://github.com/zlib-ng/minizip-ng) is under the [zlib](https://github.com/zlib-ng/minizip-ng/blob/master/LICENSE)
-   [hashmap.h](https://github.com/sheredom/hashmap.h) is under the [Unlicense](https://github.com/sheredom/hashmap.h/blob/master/LICENSE)