#!/bin/sh

#import other script
. ./ini.sh
. ./map.sh

load_cfg text.ini
map_name="ini_map"

map_init "$map_name" "$en"

keys=$(map_get_keys "$map_name")
echo "key set is $keys\n"

bHaskey="False"
bHaskey=$(map_has_key "$map_name" "hello")
echo "map has hello? $bHaskey"

bHaskey="False"
bHaskey=$(map_has_key "$map_name" "hell")
echo "map has hell? $bHaskey"
