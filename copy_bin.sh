#!/bin/bash

# Get target chipset
target=$(grep -Eo 'CONFIG_IDF_TARGET=".*?"' sdkconfig | sed 's/.*="\(.*\)".*/\1/g')
echo TARGET=$target

project_name=$(grep -Eo 'project\(.*?\)' CMakeLists.txt | sed 's/.*(\(.*\)).*/\1/g')
# echo PROJECT_NAME = $project_name

version=$(grep -Eo 'PROJECT_VER ".*?"' CMakeLists.txt | sed 's/.*"\(.*\)".*/\1/g')

# Make dir for copy bin
copy_dir="release_bin_"$project_name"_"$target"_"$version

echo copy_dir=$copy_dir 
if [ ! -d "$copy_dir" ]; then
    mkdir $copy_dir
fi

cd build

cp $(grep -v '^--' flash_args | awk '{print $2}') ../$copy_dir/

flash_args=$(cat flash_project_args | sed -E 's|([^/ ]+/)+([^/ ]+)|\2|g' | awk '{printf "%s ", $0}')

echo "python -m esptool --chip $target -b 460800 --before default_reset --after hard_reset write_flash $flash_args" > ../$copy_dir/flash.sh
chmod +x ../$copy_dir/flash.sh