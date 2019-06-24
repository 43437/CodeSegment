#!/bin/sh

. ./ini.sh

load_cfg "text.ini"

echo "before copy, source: "
map_iter_begin "ini_map"

ini_iter="MAP_BEGIN"
while [ "x$ini_iter" != "xMAP_END" -a "x$ini_iter" != "x" ]
do
  ini_iter=$(map_iter_get_key "ini_map")
  v=$(map_get "ini_map" "$ini_iter")
  echo "k: $ini_iter ---> v: $v"
  map_iter_next "ini_map"
done

echo 
echo "after copy, source: "
map_copy "target" "ini_map"

map_iter_begin "ini_map"

ini_iter="MAP_BEGIN"
while [ "x$ini_iter" != "xMAP_END" -a "x$ini_iter" != "x" ]
do
  ini_iter=$(map_iter_get_key "ini_map")
  v=$(map_get "ini_map" "$ini_iter")
  echo "k: $ini_iter ---> v: $v"
  map_iter_next "ini_map"
done

echo "after copy, target: "
map_iter_begin "target"

ini_iter="MAP_BEGIN"
while [ "x$ini_iter" != "xMAP_END" -a "x$ini_iter" != "x" ]
do
  ini_iter=$(map_iter_get_key "target")
  v=$(map_get "target" "$ini_iter")
  echo "k: $ini_iter ---> v: $v"
  map_iter_next "target"
done

