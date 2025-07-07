#!/bin/bash
set -e  # Exit immediately if a command fails

echo "[*] Compiling Assembly"
as sys.S -o bin/assm

echo "[*] Compiling C source files"
gcc -static -c src/init.c -I./include -o obj/init.o
gcc -static -c src/utils.c -I./include -o obj/utils.o

echo "[*] Building userland utilities"
gcc -static src/ls.c bin/assm -o bin/ls
gcc -static src/cd.c -o bin/cd
gcc -static src/pwd.c -o bin/pwd
gcc -static src/mkdir.c bin/assm -o bin/mkdir

echo "[*] Linking init (shell)"
gcc -static -o bin/init obj/init.o obj/utils.o bin/assm -z noexecstack

echo "[*] Creating initramfs"
cd bin
cat boot_files | cpio -H newc -o > init.cpio
mv init.cpio ../
cd ..

echo "[*] Building ISO image from kernel"

# # Ensure genisoimage or mkisofs is available
# command -v genisoimage >/dev/null 2>&1 || {
#     echo "genisoimage not found, trying mkisofs..."
#     command -v mkisofs >/dev/null 2>&1 || {
#         echo "Error: genisoimage or mkisofs is required but not found." >&2
#         exit 1
#     }
#     alias genisoimage=mkisofs
# }

cd ../linux
make isoimage FDARGS="initrd=/init.cpio" FDINITRD="$(pwd)/../react_unix/init.cpio"


echo "[*] Launching QEMU"
qemu-system-x86_64 -cdrom arch/x86/boot/image.iso -display gtk

