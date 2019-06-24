#!/bin/sh

. ./ini.sh

load_cfg "text_save.cfg"

map_iter_begin "$map_ini_name"

k_iter="MAP_BEGIN"
while [ "x$k_iter" != "xMAP_END" -a "x$k_iter" != "x" ]
do
  k_iter=$(map_iter_get_key "$map_ini_name")
  v=$(map_get "$map_ini_name" "$k_iter")
  echo "k: $k_iter ---> v: $v"
  map_iter_next "$map_ini_name"
done

persist_cfg "text_reload.cfg"
