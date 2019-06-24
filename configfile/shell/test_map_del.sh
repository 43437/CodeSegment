#!/bin/sh

#import other script
. ./ini.sh
. ./map.sh

load_cfg text.ini
map_name="ini_map"

map_init "$map_name" "$en"

map_iter_begin "$map_name"

i=0
while [ "x$key_it" != "xMAP_END" ]
do
  key_it=$(map_iter_get_key "$map_name")
  if [ $? -ne 0 ]
  then
    break
  fi
  echo "########## $i ##########"
  echo "key $key_it"
  value=$(map_get "$map_name" "$key_it")
  echo "value $value"
  i=`expr $i + 1`

  map_iter_next "$map_name"
  if [ $? -ne 0 ]
  then
    break
  fi
  
done

map_del "$map_name" "end"

echo "\n**********after del************\n"

map_iter_begin "$map_name"

i=0
key_it="MAP_BEGIN"
while [ "x$key_it" != "xMAP_END" ]
do
  key_it=$(map_iter_get_key "$map_name")
  if [ $? -ne 0 ]
  then
    break
  fi
  echo "########## $i ##########"
  echo "key $key_it"
  value=$(map_get "$map_name" "$key_it")
  echo "value $value"
  i=`expr $i + 1`

  map_iter_next "$map_name"
  if [ $? -ne 0 ]
  then
    break
  fi
  
done

echo "\nget del key's(end) value"
del_val=$(map_get "$map_name" "end")
echo "del_val is $del_val"
