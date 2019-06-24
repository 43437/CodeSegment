#!/bin/sh

. ./map.sh

map_ini_name="ini_map"

load_cfg()
{
  if [ $# -lt 1 ]
  then
    Err_LOAD_CFG_0
    return 1
  fi

  local f_name="$1"
  local var=""
  if [ ! -f "$f_name" ]
  then
    Err_LOAD_CFG_1
    return 1
  else
    sed -i 's/^[ \t]*//g' "$f_name"
    sed -i 's/[ \t]*$//g' "$f_name"
    var=$(awk 'BEGIN{ORS="~";FS="[[:blank:]]*=[[:blank:]]*"} /^[^#].*$/{print $1"="$2}' "$f_name")
    map_init "$map_ini_name" "$var"
  fi
}

persist_cfg()
{
  if [ $# -lt 1 ]
  then
    Err_PERSIST_CFG
    return 1
  fi

  local cfg_file="$1"
  local map_name="ini_map"

  if [ $# -ge 2 ]
  then
    map_name="$2"
  fi

  : > "$cfg_file"

  local k=""
  local v=""
  local key_it="MAP_BEGIN"
  map_iter_begin "$map_name"
  while [ "x$key_it" != "xMAP_END" -a "x$key_it" != "x" ]
  do
    key_it=$(map_iter_get_key "$map_name")
    k="$key_it"
    v=$(map_get "$map_name" "$k")
    map_iter_next "$map_name"
    if [ "x$k" != "x" ]
    then
      echo "$k"="$v" >> "$cfg_file"
    fi
  done
}
