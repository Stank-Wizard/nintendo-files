
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
| 0x16 | 2 | [_STR table](#_str-header) offset |
| 0x18 | 4 | [_RLT table](#_rlt-header) offset |
| 0x1C | 4 | File size |

# NX Header

the texture container itself

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (NX) |
| 0x4 | 4 | Number of files |
| 0x8 | 8 | Texture table offset, points to table of 64 bit pointers into [BRTI tables](#brti-header) |
| 0x10 | 8 | [BRTD table](#brtd-header) offset |
| 0x18 | 8 | [_DIC table](#_dic-header) offset |

# _STR Header

String Table

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_STR) |
| 0x4 | 4 | Next section offset |
| 0x8 | 8 | Section size (including the following _DIC) |
| 0x10 | 8 | Number of strings in table |
| 0x18 | N | Null-terminated file names |

# _DIC Header

Dictionary

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_DIC) |
| 0x4 | 4 | Number of entries |
| 0x4 | 4 |  |

# BRTI header

Texture info

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BRTI) |
| 0x0 | 4 |  |

# BRTD Header

Texture data

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
