# Format-i - Immediate

#### Format-i32

| Mode  | Format | OP     | RegDst | Immediate |
|-------|--------|--------|--------|-----------|
| 1 bit | 3 bit  | 7 bit  | 5 bit  | 16 bit    |

#### Format-i64

| Mode  | Format | OP    | RegDst | Immediate |
|-------|--------|-------|--------|-----------|
| 2 bit | 6 bit  | 8 bit | 5 bit  | 32 bit    |

# Format-r - Register

| Mode  | Format | OP    | RegDst | RegSrc1 | RegSrc2  | OptRegSrc3 | Opt    |
|-------|--------|-------|--------|---------|----------|------------|--------|
| 1 bit | 3 bit  | 7 bit | 5 bit  | 5 bit   | 5 bit    | 5 bit      | 1 bit  |

# Format-j - Jump

| Mode  | Format | OP    | Immediate |
|-------|--------|-------|-----------|
| 2 bit | 6 bit  | 8 bit | 48 bit    |

# Format-c - Call

| Mode  | Format | OP    | Immediate |
|-------|--------|-------|-----------|
| 2 bit | 6 bit  | 8 bit | 48 bit    |

# !Format-f - Floating point!
    
### Coming soon...

# !Format-m - Matrix!

### Coming soon...
