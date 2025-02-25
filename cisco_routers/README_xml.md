# Fuzzing `RV215W`

`RV215W` is a small wireless router from `Cisco`, as described in there website 

[Cisco website]: https://www.cisco.com/c/en/us/products/collateral/routers/rv215w-wireless-n-vpn-router/data_sheet_c78-712088.html	"Cisco website"



### Examining the target

First thing first, let's look at one of the firmware located in our target directory.

We start with the binary blob `RV215W_FW_1.3.1.7.bin`, that we can examine with `binwalk` :

````bash
$ binwalk RV215W_FW_1.3.1.7.bin

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
32            0x20            TRX firmware header, little endian, image size: 11018240 bytes, CRC32: 0x7F23D367, flags: 0x0, version: 1, header size: 28 bytes, loader offset: 0x1C, linux kernel offset: 0x183C90, rootfs offset: 0x0
60            0x3C            LZMA compressed data, properties: 0x5D, dictionary size: 65536 bytes, uncompressed size: 4481156 bytes
1588400       0x183CB0        Squashfs filesystem, little endian, non-standard signature, version 3.0, size: 9425813 bytes, 1182 inodes, blocksize: 65536 bytes, created: 2020-05-15 00:48:58
```
````

Then we can extract the `squashfs` file system with `binwalk`and get the following :

````bash
$ binwalk -Mre RV215W_FW_1.3.1.7.bin
$ ls _RV215W_FW_1.3.1.7.bin.extracted/squashfs-root
bin  data  dev  etc  lib  mnt  proc  sbin  sys  tmp  usr  var  www

_RV215W_FW_1.3.1.7.bin.extracted/squashfs-root$ readelf -h bin/busybox
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           MIPS R3000
  Version:                           0x1
```

````

### Preparing our tools

Now we know we are targeting little endian MIPS binaries. Now let's try to execute a binary using `qemu user mode`. There is a `JSON` parsing binary there located in `/usr/sbin/jsonparse`.

```bash
$ sudo apt install qemu-user-static
$ cd _RV215_FW_1.3.1.7.bin.extracted/squashfs-root
$ qemu-mipsel-static -L . ./bin/busybox
squashfs-root$ qemu-mipsel-static -L . ./usr/sbin/xmlparser1 -h

/usr/sbin/xmlparser1: option requires an argument -- h
./usr/sbin/xmlparser1: -d -f filename -o output
```



Now that we have a pretty good target binary that takes a file as input, we can use our familiar `AFL` fuzzer in `QEMU` mode. Last thing we need to make sure of is to have the correct version of support for `afl-qemu-trace`, we can do it by recompiling the support as :



````bash
AFLPlusPlus$ cd qemu_mode
AFLPlusPlus/qemu_mode$ CPU_TARGET=mipsel ./build_qemu_support.sh
AFLPlusPlus$ sudo make install #not necessary, but more convenient not to have long paths in command

```
````

Now let's create both input and out directories for `AFL` , move a minimal json file into the input directory :



````bash
$ mkdir ./squashfs-root/in ./squashfs-root/out
$ wget https://raw.githubusercontent.com/strongcourage/fuzzing-corpus/master/xml/test.xml
$ cp test.xml
```
````

### Fuzzing our target

Time to fuzz, with `AFL` :

````bash
$ sudo bash -c 'echo "/data/app_crash/%t.%e.core.%p" > /proc/sys/kernel/core_pattern'
$ QEMU_LD_PREFIX=./squashfs-root/ afl-fuzz -Q -i ./squashfs-root/in/ -o ./squashfs-root/sync_dir/ -- ./squashfs-root/usr/sbin/xmlparser1 -d -f @@ -o /dev/null

```
````

- `QEMU_LD_PREFIX` is required to make sure our emulator knows which directory to use as a base to find the dynamic libraries
- `-Q` to use `QEMU` mode

The rest of the arguments are now familiar to you.
