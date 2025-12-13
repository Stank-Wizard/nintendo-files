
# BNTX Header

A BNTX file contains textures

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BNTX) |
| 0x4 | 4 | UNKNOWN |
| 0x8 | 4 | UNKNOWN |
| 0xC | 4 | BOM |
| 0x10 | 2 | UNKNOWN |
| 0x12 | | |
| 0x | | |
| 0x | | |
| 0x | | |

# NX Header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (NX) |
| 0x4 | 4 | Number of files |
| 0x8 | 8 | UNKNOWN |
| 0x10 | 8 | Offset into BRTD section |
| 0x18 | 8 | Offset into _DIC section |

# _STR Header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_STR) |
| 0x0 | 4 |  |

# _DIC Header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_DIC) |
| 0x0 | 4 |  |

# BRTD Header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (BRTD) |
| 0x0 | 4 |  |

# _RLT Header

| Offset | Size | Description |
| :--- | :--- | :--- |
| 0x0 | 4 | Magic number (_RLT) |
| 0x0 | 4 |  |
