#!/bin/sh

#import other script
. ./ini.sh
. ./map.sh

load_cfg text.ini
map_name="ini_map"

map_init "$map_name" "$en"

keys=$(map_get_keys "$map_name")
echo "map keys is $keys"
iSize=$(map_size "$map_name")
echo "map size is $iSize"

map_set "$map_name" "new" "add"

keys=$(map_get_keys "$map_name")
echo "map keys is $keys"
iSize=$(map_size "$map_name")
echo "map size is $iSize"
