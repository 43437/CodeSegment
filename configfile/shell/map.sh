#!/bin/sh

# $1 keyset
# $2 values
map_init()
{
  if [ $# -ge 2 ]
  then
    local loc_name="$1"
    local loc_pairs="$2"

    map_from_str "$loc_name" "$loc_pairs"
  else
    DEBUG_MAP_INI
  fi
}

map_from_str()
{
  if [ $# -lt 2 ]
  then 
    Err_FROM_STR
    return 1
  fi

  local loc_name="$1"
  local loc_pair=""
  local loc_str="$2"
  local loc_key=""
  local loc_value=""
  while [ "x$loc_str" != "x" -a "x$loc_str" != "x$loc_pair" ]
  do
    loc_pair=$(echo $loc_str|cut -d~ -f1)
    loc_str=$(echo $loc_str|cut -d~ -f2-)

    loc_key=$(echo "$loc_pair"|cut -d= -f1)
    loc_value=$(echo "$loc_pair"|cut -d= -f2-)
  
    map_set "$loc_name" "$loc_key" "$loc_value"
  done
}

map_copy()
{
  if [ $# -lt 2 ]
  then
    Err_COPY
    return 1
  fi

  local loc_target="$1"
  local loc_source="$2"

  eval "$loc_target"_key_set='$'"$loc_source"_key_set

  map_iter_begin "$loc_source"
  local iter_src="MAP_BEGIN"
 
  while [ "x$iter_src" != "xMAP_END" -a "x$iter_src" != "x" ] 
  do
    iter_src=$(map_iter_get_key "$loc_source")
    eval $loc_target'_'$iter_src='$'$loc_source'_'$iter_src
    map_iter_next "$loc_source"
  done
}

#$1 key
#return value
map_get()
{
  if [ $# -lt 2 ] 
  then
    Err_GET
    return 1
  fi

  local loc_name="$1"
  local loc_key="$2"
  eval local loc_value_var='$'"$loc_name"_"$loc_key"
  echo "$loc_value_var"|sed 's/=/ /g'
}

#$1 key
#$2 value
map_set()
{
  if [ $# -lt 3 ]
  then
    Err_SET
    return 1
  fi

  local loc_name="$1"
  local loc_key="$2"
  local loc_value="$3"
  local loc_s_value=$(echo "$loc_value"| sed 's/[[:blank:]]/=/g')
  eval "$loc_name"_"$loc_key"="$loc_s_value"

  bHasKey=$(map_has_key "$loc_name" "$loc_key")
  if [ "x$bHasKey" != "xTrue" ]
  then
    eval local loc_key_set='$'"$loc_name"_key_set
    loc_key_set="$loc_key_set""$loc_key""~"
    eval "$loc_name"_key_set="$loc_key_set"
  fi
}

map_del()
{
  if [ $# -lt 2 ]
  then
    Err_DEL
    return 1
  fi

  local loc_name="$1"
  local loc_key="$2"
  eval unset "$loc_name"_"$loc_key"
  
  eval local loc_key_set='$'"$loc_name"_key_set
  loc_key_set=$( echo "$loc_key_set"|awk -v key_del="$loc_key" 'BEGIN{FS="~";ORS="~"}{i=1;while(i<NF){ if( $i!=key_del) { print $i} ++i}}' )
  eval "$loc_name"_key_set="$loc_key_set"
}

map_clear()
{
  if [ $# -lt 1 ]
  then
    Err_CLEAR
    return 1
  fi

  loc_name="$1"
  loc_size=$(map_size "$loc_name")
  local loc_i=1
  local loc_keys=$(map_get_keys "$loc_name")
  while [ $loc_i -le $loc_size ]
  do
    local loc_key=$(echo "$loc_keys"|awk -v k_index="$loc_i" 'BEGIN{FS="~"}{print $k_index}')
    eval unset "$loc_name"_"$loc_key"
    loc_i=`expr $loc_i + 1`
  done

  eval unset "$loc_name"_key_set
}

map_size()
{
  if [ $# -lt 1 ]
  then 
    Err_SIZE
    return 1
  fi

  local loc_name="$1"
  eval local loc_key_set='$'"$loc_name"_key_set
  local loc_num=$(echo "$loc_key_set"|awk 'BEGIN{FS="~"}{print NF}')
  echo "$loc_num"
}

map_has_key()
{
  if [ $# -lt 2 ]
  then
    Err_HAS_KEY
    return 1
  fi

  local loc_name="$1"
  local loc_key="$2"
  eval local loc_key_set='$'"$loc_name"_key_set
  bFind=$( echo "$loc_key_set"|awk -v key_find="$loc_key" 'BEGIN{FS="~";}{i=1;while(i<=NF){ if( $i==key_find) { print "T"; break;}; ++i}}' )

  if [ "x$bFind" = "xT" ]
  then
    echo "True"
  else
    echo "False"
  fi
}

map_get_keys()
{
  if [ $# -lt 1 ]
  then
    Err_GET_KEYS
    return 1
  fi

  loc_name="$1"
  eval echo '$'"$loc_name"_key_set
}

map_iter_begin()
{
  if [ $# -lt 1 ]
  then
    Err_ITER_BEGIN
    return 1
  fi

  local loc_name="$1"
  eval "$loc_name"_map_index=1
}

map_iter_next()
{
  if [ $# -lt 1 ]
  then
    Err_ITER_NEXT_0
    return 1
  fi

  local loc_name="$1"
  eval local loc_index='$'"$loc_name"_map_index
  #not initialize
  if [ $loc_index -le 0 ]
  then
    Err_ITER_NEXT_1
    return 1
  fi

  eval local loc_key_set='$'"$loc_name"_key_set
  local loc_num=$(echo "$loc_key_set"|awk 'BEGIN{FS="~"}{print NF}')
  if [ $loc_index -le $loc_num ]
  then
    loc_index=`expr $loc_index + 1`
  else
    loc_index=0		#end of iterator
  fi
  eval "$loc_name"_map_index=$loc_index
}

map_iter_get_key()
{
  #error index, maybe not initialied
  if [ $# -lt 1 ]
  then
    Err_ITER_GET_KEY_0
    return 1
  fi

  local loc_name="$1"
  eval local loc_index='$'"$loc_name"_map_index
  if [ $loc_index -le 0 ]
  then
    Err_ITER_GET_KEY_1
    return 1
  fi

  eval local loc_key_set='$'"$loc_name"_key_set
  local loc_key=$(echo "$loc_key_set"|awk -v k_index="$loc_index" 'BEGIN{FS="~"}{if(k_index > NF){print "MAP_END"}else{print $k_index}}')
  
  echo "$loc_key"
}
