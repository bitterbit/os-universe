DEF_FILE_SIZE=5000 # 5000 mb = 5gb

if [ -z "$1" ]; then
    echo "forgot to supply an input folder?"
    exit 1
fi

if [ -z "$2" ]; then
    echo "forgot to supply an output file?"
    exit 1
fi

if [ ! -f $2 ]; then
    echo "output doesnt exist, creating with default size"    
    dd if=/dev/zero of=$2 bs=1m count=$DEF_FILE_SIZE
fi

docker run  --mount type=bind,source=$1,target=/root/folder \
            --mount type=bind,source=$2,target=/root/image.img \
    --cap-add=SYS_ADMIN \
    --privileged \
    -it folder2img /bin/bash -l
