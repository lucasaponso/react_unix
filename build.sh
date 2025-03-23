
as sys.S -o bin/assm # compile assembly

gcc -static -c src/init.c -I./include -lc -o ./obj/init.o ##compile shell
gcc -static -c src/utils.c -I./include -lc -o ./obj/utils.o ##compile util lib

gcc -static src/ls.c bin/assm  -o bin/ls ##compile ls
gcc -static src/cd.c -o bin/cd -lc ##compile ls
gcc -static src/pwd.c -o bin/pwd -lc ##compile ls

gcc -static src/mkdir.c bin/assm -o bin/mkdir -lc ##compile ls

gcc -static -o bin/init ./obj/init.o ./obj/utils.o bin/assm -lc -z noexecstack ##link shell, utils lib, assembly

cd bin
cat boot_files | cpio -H newc -o > init.cpio ##write ls, lua as exec in fs
rm -rf init ls ##do not remove lua
mv init.cpio ../

cd ../linux
make isoimage FDARGS="initrd=/init.cpio" FDINITRD=/home/aponso/to_backup/linux/react_unix/init.cpio
qemu-system-x86_64 -cdrom arch/x86/boot/image.iso
