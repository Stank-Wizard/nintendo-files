# nintendo-files

Just a simple program that im working one as a part of something bigger, can decompress szs files, unpack sarc files, and view bflyt files.

## Decompressing szs

```
# clone repo
git clone https://github.com/Stank-Wizard/nintendo-files.git

# enter directory
cd nintendo-files/szs

# copy needed files
cp [path-to-your-systemData-files] .

# finally run the program
make
```

## Unpacking sarc

```
# clone repo
git clone https://github.com/Stank-Wizard/nintendo-files.git

# enter directory
cd nintendo-files/sarc

# copy needed files
cp [path-to-your-systemDataDecompressed-files] .

# finally run the program
make
```

## View bflyt

```
# clone repo
git clone https://github.com/Stank-Wizard/nintendo-files.git

# enter directory
cd nintendo-files/bflyt

# copy needed files
cp [path-to-your-systemDataUnpacked-files] .

# finally run the program
make
```

## View bntx

```
# clone repo
git clone https://github.com/Stank-Wizard/nintendo-files.git

# enter directory
cd nintendo-files/bntx

# copy needed files
cp [path-to-your-systemDataUnpacked-files] .

# finally run the program
make
```

## License

This software is licensed under the terms of the GPLv3, with exemptions for specific projects noted below.

You can find a copy of the license in the [LICENSE file](LICENSE).

## Credits

this repo is currently being developed and maintained by me but i'd like to give credit where credit is due as this couldn't be possible without the following sources:

* __thakis__ for the [szs file format decompression documentation](http://www.amnoid.de/gc/yaz0.txt)
* __kinnay__ for the [sarc and bflyt file format documentation](https://nintendo-formats.com/)
* __zeldamods wiki team__ for the [bntx file documentation](https://epd.zeldamods.org/wiki/Bntx)
