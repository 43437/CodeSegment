@echo off

set script_name=%~n0

set script_dir=%~dp0

set ffmpeg=%script_dir%ffmpeg.exe

set ffprobe=%script_dir%ffprobe.exe

set cut_time=%1

set cut_duration=%2

set src_file=%3

set out_folder=%script_dir%out

rem %ffmpeg% -version

set script_path=%~dp0

set C_DST_VIDEO_W=419

set C_FRAME_RATE=3





if not exist %out_folder% (

	echo mkdir %out_folder%

	md %out_folder%

)



set src_file_name=tmp

rem get src filename

for %%A in (%src_file%) do set src_file_name=%%~nA



set dst_folder_1=%out_folder%\%src_file_name%\

set dst_folder_2=%dst_folder_1%%src_file_name%-jpeg\



if exist %dst_folder_2% (

	rd /s /q %dst_folder_2%

)

md %dst_folder_2%



echo %C_FRAME_RATE% >%dst_folder_1%gif.info

%ffprobe% %src_file% 2> %dst_folder_1%video.info



for /f "tokens=3 delims=," %%a in ('find "Video" %dst_folder_1%video.info') do (

	set video_size=%%a & goto :break_find_vsize

)

:break_find_vsize



call :Strip %video_size%

echo %video_size%



for /f "tokens=1,2 delims=x" %%a in ("%video_size%") do (

	set video_w=%%a

	set video_h=%%b

)



echo w %video_w% h %video_h%



set divisor_a=%video_w%

set divisor_b=%video_h%

:calc_divisor_begin

if %divisor_a% EQU %divisor_b% (

	goto calc_divisor_end

) else (

	if %divisor_a% GTR %divisor_b% (

		set /a divisor_a=%divisor_a%-%divisor_b%

	) else (

		set /a divisor_b=%divisor_b%-%divisor_a%

	)

)

goto calc_divisor_begin

:calc_divisor_end

echo divisor %divisor_a%



set mul_size=1

set /a var_w_t=%video_w%/%divisor_a%

set /a var_h_t=%video_h%/%divisor_a%

:calc_dst_size_begin

set /a mul_size=%mul_size%+1

set /a ans_t=%var_w_t%*%mul_size%

rem echo mul_size %mul_size% ans_t %ans_t%



if %ans_t% GTR %C_DST_VIDEO_W% (

	echo out now mul_size ans_t %mul_size% %ans_t%

	goto calc_dst_size_end

) else (

	goto calc_dst_size_begin

)

:calc_dst_size_end



set /a dst_video_w=%mul_size%*%var_w_t%

set /a dst_video_h=%mul_size%*%var_h_t%



echo dst_video_w dst_video_h %dst_video_w% %dst_video_h%



:Strip

set var=%1



%ffmpeg% -ss %cut_time% -t %cut_duration% -i %src_file% -r 3 -s %dst_video_w%x%dst_video_h% -f image2 %dst_folder_2%\%src_file_name%-%%03d.jpeg



call %script_dir%gen_git_co.bat %dst_folder_2%