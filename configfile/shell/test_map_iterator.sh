#!/bin/sh

#import other script
. ./ini.sh
. ./map.sh

load_cfg "text.ini"
map_name="ini_map"

#map_init "$map_name" "$en"

keys=$(map_get_keys "$map_name")
echo "keys is $keys"

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
