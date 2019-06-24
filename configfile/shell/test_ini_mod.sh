#!/bin/sh

. ./ini.sh

load_cfg "text.ini"

map_iter_begin "$map_ini_name"
k_iter="MAP_BEGIN"

while [ "x$k_iter" != "xMAP_END" -a "x$k_iter" != "x" ]
do
  k_iter=$(map_iter_get_key "$map_ini_name")
  v=$(map_get "$map_ini_name" "$k_iter")
  echo "k: $k_iter --> v: $v"
  map_iter_next "$map_ini_name"
done

map_set "$map_ini_name" "hello" "reset new"
map_set "$map_ini_name" "new_key" "new_added"

persist_cfg "text_mod.ini"
