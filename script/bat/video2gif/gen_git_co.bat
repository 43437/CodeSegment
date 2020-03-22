@echo off

setlocal EnableDelayedExpansion



set script_dir=%~dp0

set ffmpeg=%script_dir%ffmpeg.exe

set src_jpegs=%1

set dst_gif=%1\out.gif

set tm_src_jpegs=%src_jpegs%tmp\

set begin_index=%2

set end_index=%3

set frame_rate=3



set gen_config_file=%src_jpegs%..\gif.info

if exist %gen_config_file% (

	echo gen config file is exist

	for /f %%a in (%gen_config_file%) do (

		set frame_rate=%%a

	)

)



set raw_file_prefix=%src_jpegs:~0,-5%

echo raw_file_prefix %raw_file_prefix%

for %%a in (%raw_file_prefix%) do set file_prefix=%%~na

echo src_jpegs %src_jpegs%

echo dst_gif %dst_gif%

echo file_prefix %file_prefix%

echo begin_index %begin_index%



setlocal EnableDelayedExpansion

if not [!begin_index!] == [] (

	

	echo begin index is not null

	if exist %tm_src_jpegs% (

		rd /s /q %tm_src_jpegs%

	)

	md %tm_src_jpegs%

	

	set loc_index_i=0

	for /f %%a in ('dir %src_jpegs% /b') do (

		set var=%%a

		set sub_index=!var:~-8,3!

		echo sub_index !sub_index!

		if !sub_index! GTR !begin_index! (

			if not [!end_index!] == [] (

				echo end index is not null

				if !sub_index! GTR !end_index! (

					goto end_index_for

				)

			)



			set /a loc_index_i=!loc_index_i!+1

			set loc_index_s_i=0000!loc_index_i!

			set loc_index_s_i=!loc_index_s_i:~-3!



			copy /y %src_jpegs%!var! %tm_src_jpegs%!file_prefix!!loc_index_s_i!.jpeg

		)

	)

	:end_index_for

	set src_jpegs=%tm_src_jpegs%

	set dst_gif=!src_jpegs!out.gif

)



%ffmpeg% -f image2 -framerate %frame_rate% -i %src_jpegs%%file_prefix%%%03d.jpeg -y %dst_gif%