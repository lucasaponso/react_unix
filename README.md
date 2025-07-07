# React-Unix

Custom Linux OS built with the Linux kernel and user space
applicatiosn written in GNU C and x86 ASSM.


## How to Build?
Firstly, clone the Linux kernel.
```
git clone git@github.com:torvalds/linux.git --depth 1
```

Then move the react-unix-cfg into arch/x86/configs/react-unix-cfg
```
mv react-unix-cfg ../linux/arch/x86/configs/.
```

Then execute
```
make react-unix-cfg
```
Then run
```
make
```

Then to build the user-space
```
./build.sh
```