
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

# _DIC Entries

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Reference Bit |
| 0x4 | 2 | Left Node Index |
| 0x6 | 2 | Right Node Index |
| 0x8 | 8 | [_STR table entry](#_str-header) offset |

# BRTI header

Texture info

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BRTI) |
| 0x4 | 4 | Next Section Offest |
| 0x8 | 8 | Header Size |
| 0x10 | 1 | Flags |
| 0x11 | 1 | Dimensions |
| 0x12 | 2 | Tile Mode |
| 0x14 | 2 | Swizzle Size |
| 0x16 | 2 | Mip Map Count |
| 0x18 | 2 | Multi Sample Count |
| 0x1C | 2 | Reverse 1a |
| 0x20 | 4 | Format |
| 0x24 | 4 | Access Flags |
| 0x28 | 4 | Width |
| 0x2C | 4 | Height |
| 0x30 | 4 | Array Count |
| 0x34 | 4 | Block Height Log2 |
| 0x38 | 4 | Reserved |
| 0x3C | 4 | Reserved |
| 0x40 | 4 | Reserved |
| 0x44 | 4 | Reserved |
| 0x48 | 4 | Reserved |
| 0x4C | 4 | Reserved |
| 0x50 | 4 | Data Length |
| 0x54 | 4 | Alignment |
| 0x58 | 4 | Channel Type |
| 0x5C | 4 | Texture Type |
| 0x60 | 8 | Name Address |
| 0x68 | 8 | Parent Address |
| 0x70 | 8 | Ptrs Address |

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
| 0x4 | 4 | Offset of _RLT Table |
| 0x8 | 4 | Number of Sections |
| 0x0 | 4 |  |
| 0x0 | 4 |  |
| 0x0 | 4 |  |
| 0x0 | 4 |  |

# _RLT Entries

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Entry Offset |
| 0x0 | 4 | Array Count |
| 0x0 | 4 | Offset Count |
| 0x0 | 4 | Padding Size |
