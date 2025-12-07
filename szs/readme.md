# Yaz0 Header

| Offset | Size | Description |
| :--- | :--- | :--- | 
| 0x0 | 4 | Magic Number (Yaz0) |
| 0x4 | 4 | Decompressed size |
| 0x8 | 4 | Required memory alignment (either 0 or a power of 2) |
| 0xC | 4 | Reserved (always 0's) |
| 0x10 |  | Yaz0 compressed data |
