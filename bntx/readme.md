
# BNTX Header

A BNTX file contains textures

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BNTX) |
| 0x4 | 8 | Version number |
| 0xC | 4 | BOM |
| 0xE | 2 | Alignment exponent |
| 0x10 | 2 | File name target address |
| 0x14 | 2 | Is relocated |
| 0x16 | 2 | _STR table offset |
| 0x18 | 4 | _RLT table offset |
| 0x1C | 4 | File size |

# NX Header

the texture container itself

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (NX) |
| 0x4 | 4 | Number of files |
| 0x8 | 8 | Texture table offset, points to table of 64 bit pointers into BRTI sections |
| 0x10 | 8 | Offset into BRTD section |
| 0x18 | 8 | Offset into _DIC section |

# _STR Header

String Table

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_STR) |
| 0x0 | 4 |  |

# _DIC Header

Dictionary

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_DIC) |
| 0x0 | 4 |  |

# BRTI header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BRTI) |
| 0x0 | 4 |  |

# BRTD Header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BRTD) |
| 0x0 | 4 |  |

# _RLT Header

Relocation Table

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_RLT) |
| 0x0 | 4 |  |
