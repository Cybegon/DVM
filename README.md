# DVM - Dragon Virtual Machine

![](https://img.shields.io/github/workflow/status/Cybegon/DVM/CI?logo=GitHub&style=for-the-badge)
![](https://img.shields.io/github/license/Cybegon/DVM?color=0aa4ff&logo=GitHub&style=for-the-badge)

### Build

| Target      | Dependencies                      | Description                               |
|-------------|-----------------------------------|-------------------------------------------|
| dvm         | libdvm, libdvm-base, libcar       | Build an executable file                  |
| libdvm      |                                   | Build dvm as static library               |
| libdvm-base | libgeff, zip, libdvm-headers only | Library that provides basic functionality |
| libgeff     |                                   | General executable file format            |
| libcar      | libdvm-headers only               | CAR - Cybegon Architecture                |

Build an executable file:
```
cmake -G "Ninja" -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --target dvm
```

## External libraries used by DVM

-   [ZIP](https://github.com/kuba--/zip) is under the [Unlicense](https://github.com/kuba--/zip/blob/master/UNLICENSE)