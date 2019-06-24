#!/bin/sh

. ./ini.sh

t_map_name="test"
save_file="text_save.cfg"

map_set "$t_map_name" "first" "1"
map_set "$t_map_name" "second" "2"
map_set "$t_map_name" "third" "3"
map_set "$t_map_name" "fourth" "4"
map_set "$t_map_name" "with_space" "this is contains space."

persist_cfg "$save_file" "$t_map_name"
