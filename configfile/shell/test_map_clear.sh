#!/bin/sh

#import other script
. ./ini.sh
. ./map.sh

load_cfg text.ini
map_name="ini_map"

echo "\n**********before clear************\n"
bf_keys=$(map_get_keys "$map_name" )
echo "keys before: $bf_keys"

nums=$(echo $bf_keys|awk 'BEGIN{FS="~"}{print NF}')

i=1
while [ $i -le $nums ]
do
  k=$(echo $bf_keys|awk -v iK="$i" 'BEGIN{FS="~"}{print $iK}')
  v=$(map_get "$map_name" "$k")
  echo "k:$k -----> v:$v"

  i=`expr $i + 1`
done

map_clear "$map_name"

echo "\n**********after clear************\n"

af_keys=$(map_get_keys "$map_name")
echo "keys after: $af_keys"

nums=$(echo $bf_keys|awk 'BEGIN{FS="~"}{print NF}')

i=1
while [ $i -le $nums ]
do
  k=$(echo $bf_keys|awk -v iK="$i" 'BEGIN{FS="~"}{print $iK}')
  v=$(map_get "$map_name" "$k")
  echo "k:$k -----> v:$v"

  i=`expr $i + 1`
done

