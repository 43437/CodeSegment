#!/bin/sh

str='one:1~two:2~three:3~four:4'

keys='one~two 2~three~four~'
key='two '
var=$( echo "$keys"|awk -v key_find="$key" 'BEGIN{FS="~";}{i=1;while(i<NF){ if( $i==key_find) { print "T"; break} ++i}}' )
echo $var

echo "$LINENO"
