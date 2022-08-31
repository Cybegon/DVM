| 1 Byte     | 1 Byte    | 1 Byte       | 1 Byte      | 4 Bytes |
|------------|-----------|--------------|-------------|---------|
| vm_control | vm_status | vm_privilege | vm_reserved | vm_user |



## vm_control

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| EF  | TF  | VF  | RES | RES | RES | RES | RES |

## vm_status

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| EQ  | LO  | LT  | RES | RES | RES | RES | RES |