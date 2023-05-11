# FFmpeg 基本命令

- 转换数据格式:ffmpeg -i in.mp4 -vcodec copy -acodec copy out.flv

> 参数含义 -vcodec 表示拷贝视频, -acodec表示拷贝音频; -an表示不要音频，-vn表示不要视频, -ar音频的采样率，-ac2 channel:音频的单声道，双声道，环绕立体声。
> -f 音频的数据存储格式,s16le, l: little end小头

- 滤镜命令:-vf滤镜，宽度高度200，视频编码器x264,不对音频做特殊处理。

```shell
ffmpeg -i in.mov -vf crop=in_w-200:in_h-200 -c:v libx264 -c:a copy out.mp4
```

- 视频裁剪与合并

```shell
#裁剪
ffmpeg -i in.mp4 -ss 00:00:00 -t 10 out.ts
#合并 onputs.txt是文件列表，所有文件格式: file filename
ffmpeg -f concat -i inputs.txt out.flv
# echo "file '1.ts'" > inputs.txt
# echo "file '2.ts'" > inputs.txt
从1分45秒开始剪切2分35秒
ffmpeg -i <input> -ss 00:01:45 -t 00:02:35 -vcodec copy -acodec copy <output>

从1分45秒开始剪切到第4分20秒，与上一行等效
ffmpeg -i <input> -ss 00:01:45 -to 00:04:20 -codec copy <output>
ffmpeg -ss 00:00:30 -i orginalfile.mpg -t 00:00:05 -vcodec copy -acodec copy newfile.mpg


从 4.5 秒开始的 5 秒长的视频
ffmpeg -i in.mp4 -ss 4.5 -t 5 out.mp4
```

> 原始数据的数据量越大，处理时间更长.

- 图片转视频，视频转图片

```shell
ffmpeg -i image-%3d.jpeg out.mp4
ffmpeg -i out.mp4 -r 1 -f image2 image-%3d.jpeg
```

- 视频帧率

```
ffmpeg -i input.avi -r 24 output.avi
将输出文件的帧速率强制为 24 fps

ffmpeg -r 1 -i input.m2v -r 24 output.avi
将输入文件的帧速率(仅对原始格式有效)强制为 1 fps，将输出文件的帧速率强制为 24 fps
```

- 视频比特率

```
ffmpeg -i input.avi -b:v 64k -bufsize 64k output.avi
将输出文件的视频比特率设置为 64 kbit/s
```

- 固定旋转

```
ffmpeg -i <input> -c copy -metadata:s:v:0 rotate=90 <output>
不要为旋转重新编码，而是简单地为旋转角度添加一个视频元数据字段
```

- 缩放到特定宽度

```
ffmpeg -i in.mp4 -filter:v scale="538:trunc(ow/a/2)*2" -c:a copy out.mp4'
给定所需的视频宽度，例如 538 像素，您可以使用以下方法将视频调整为该宽度，同时保持宽高比
```

- map命令

```
将第一个输入文件的第二个音频拷贝到 out.mp3
ffmpeg -i input.mp4 -map 0:a:1 -c copy out.mp3


将第一个输入文件的视频流和第二个输入文件的音频流拷贝到 out.mp4
ffmpeg -i i1.mp4 -i i2.mp4 -map 0:v -map 0:a -c copy out.mp4
```

- -map命令

```
反向的 map 命令（在 map 命令的参数前加负号）。
例如，-map -0:a:0，忽略第一个文件中的第一个音频流。
```

- 音视频同步

```
将音频延迟 3 秒
ffmpeg -i input.mov -itsoffset 3 -i input.mov -map 0:v -map 1:a -codec:a copy -codec:v copy output.mov


将视频延迟 3 秒(即将音频提前 3 秒)
    ffmpeg -i input.mov -itsoffset 3 -i input.mov -map 1:v -map 0:a -codec:a copy -codec:v copy output.mov
```

- 灰度转换

```
ffmpeg -y -i inFile -flags gray outFile
```

- 提取图像

```
ffmpeg -i foo.avi -r 1 -s WxH -f image2 outFil­e%0­3d.png
```

- 制造 1 分钟的音频噪音

```
ffmpeg -ar 48000 -t 60 -f s16le -acodec pcm_s16le -i /dev/u­random -ab 64K -f mp2 -acodec mp2 -y noise.mp2
```

- 直播推拉流

```shell
# -推流:re帧率保持同步
ffmpeg -re -i out.mp4 -c copy -f flv rtmp://server/live/streamName
# 拉流 保存的格式与拉流的格式一致
ffmpeg -i rtmp://server/live/streamName -c copy dump.flv

# 配置rtsp
ffmpeg -re -i 4k.mp4 -vcodec copy -codec copy -f rtsp rtsp://210.37..:554/live/rtsp
```

# FFmpeg代码结构

- libavcodec 提供了一系列编码器的实现
- libavformat 实现流协议，容器格式及其本IO访问
- libavutil 包括了hash器，解码器和各种工具函数
- libavfilter 提供了各种音视频过滤器
- libavdevice 提供了各种捕获设备和回放设备的接口
- libswresample 实现了混音和重采样
- libswscale 实现了色彩转换和缩放功能

# FFmpeg解码流程

![流程](./images/ffmpeg_decode.png)

# ffmpeg编译静态文件

- ![参考](https://www.freesion.com/article/35281423798/)

# ffmpeg录屏

```
# -i表示录屏的左上角位置
ffmpeg -video_size 1920x1080 -framerate 25 -f x11grab -i :0.0+1080 output.mp4
# 转换编码格式
ffmpeg -i xx.mp4 -vcodec h264 xx.mkv/avi
```

# 视频压缩

```
# 视频的原码率是 2.1Mb/s ，压缩为 1.5Mb/s
ffmpeg -i Desktop/1.mov -b:v 1.5M  Desktop/1.mp4
```

# 删除音轨

```
ffmpeg.exe -i videoWithAudio.mp4 -c:v copy -an videoWithoutAudio.mp4
```

# 常见用法

## 查看文件信息

```
ffmpge -i input.mp4
# 上面命令会输出很多冗余信息，加上-hide_banner参数，可以只显示元信息
ffmpeg -i input.mp4 -hide_banner
```

## 转换编码格式-transcoding

转换编码格式(transcoding)指的是，将视频文件从一种编码转成另一种编码。比如转成H.264编码，一般使用编码器libx264,所以只需要指定文件的视频编码器

```
ffmpeg -i [input.file] -c:v libx264 output.mp4
ffmpeg -i [input.file] -c:v libx265 output.mp4
```

## 转换容器格式-transmuxing

- 将视频文件从一种容器转换为另一种容器，mp4-webm
- 只是转换一下容器，内部的编码格式不变,所以使用-c copy 指定直接拷贝，不经过转码，这样比较快

```
ffmpeg -i input.mp4 -c copy outpub.webm
```

## 调整码率-transrating

- 调整码率指的是，改变编码的比特率，一般将用来视频文件的体机变小。下面的例子指定码率最小为964K,最大为3856K,缓冲区大小为2000K.

```
ffmpeg -i input.mp4 -minrate 964K -maxrate 3864K -bufsize 2000K output.mp4
```

## 改变分辨率-transsizing

- 改变视频分辨率的例子 1080P转为480P

```
ffmpeg -i input.mp4 -vf scale=480:-1 output.mp4
```

## 提取音频

- 视频里面提取音频(demuxing),可以像下面这样写

```
ffmpeg -i input.mp4 -vn -c:a copy output.aac
-vn表示去掉视频 -c:a copy表示不改变音频编码，直接拷贝
```

## 添加音频

- 添加音频(muxing)指的是，将外部音频加入视频，如何添加背景音乐或旁白。

```
ffmpeg -i input.aac -i input.mp4 output.mp4
# 上面例子中，有音频和视频两个输入文件，FFmpeg 会将它们合成为一个文件
```

## 截图

- 下面的例子是从指定时间开始，连续对1秒钟的视频进行截图

```
ffmpeg -y -i input.mp4 -ss 00:01:24 -t 00:00:01 output_%3d.jpg
```

- 如果只需要截一张图，可以指定只截取一帧

```
ffmpeg -ss 01:23:45 -i input -vframes 1 -q:v 2 output.jpg
# 上面例子中，-vframes 1指定只截取一帧，-q:v 2表示输出的图片质量，一般是1到5之间（1 为质量最高）。
```

## 裁剪

- 裁剪(cutting)指的是 截取原始视频里面的一个片段，输出为一个新视频，可以指定开始时间(start)和持续时间(duration),也可以指定结束时间(end)

```
ffmpeg -ss [start] -i [input] -t [duration] -c copy [output]
ffmpeg -ss [start] -i [input] -to [end] -c copy [output]
# 实际的例子
#$ ffmpeg -ss 00:01:50 -i [input] -t 10.5 -c copy [output]
#$ ffmpeg -ss 2.5 -i [input] -to 10 -c copy [output]
#上面例子中，-c copy表示不改变音频和视频的编码格式，直接拷贝，这样会快很多。

从左上角开始，复制 x=0px y=0px 的相应窗口来创建 1280x720 大小的输出视频
ffmpeg -i input.mp4 -vf "crop=w=1280:h=720:x=0:y=0" output.mp4
裁剪到宽度 360，高度 640，从坐标 (10, 20) 开始
ffmpeg -i input.mov -vf 'crop=360:640:10:20' output.mov
```

## 为音频添加封面

- 有些视频网站只允许上传视频文件。如果要上传音频文件，必须为音频添加封面，将其转为视频，然后上传。下面命令可以将音频文件，转为带封面的视频文件。

```
ffmpeg -loop 1 -i cover.jpg -i input.mp3 -c:v libx264 -c:a aac -b:a 192k -shortest output.mp4
# 上面命令中，有两个输入文件，一个是封面图片cover.jpg，另一个是音频文件input.mp3。-loop 1参数表示图片无限循环，-shortest参数表示音频文件结束，输出视频就结束。

-t 10 文件时长，单位为秒，建议取值原始视频总时长
ffmpeg -i 1.mp4 -i test.mp3 \
           -filter_complex "[1:a]aloop=loop=-1:size=2e+09[out];[out][0:a]amix" \
           -t 10 out.mp4
```

## 添加水印

```
在视频左上方 20## 0 的位置插入 logo.png 图片

-b:v 548k 可选参数，设置视频比特率，默认 200k 最好设置与原视频一致
ffmpeg -i 630.mp4 -acodec copy -b:v 548k -vf "movie=logo.png[watermark];[in][watermark]overlay=100:100" 630_logo.mp4
```

## 去除水印

```
设置一个矩形覆盖区域 x=100:y=100:w=50:h=50

show=1 为可选参数，设置显示边框，方便调试用的
ffmpeg -i 630_logo.mp4 -b:v 548k -vf delogo=x=100:y=100:w=50:h=50:show=1 630_logo_out.mp4
```

## 创造缩略图

```
在 10 秒时创建一个缩略图
ffmpeg -ss 10 -i <input file> -vframes 1 -vcodec png -an thumb.png
```

# FFmpeg基本参数

```
#基本参数
-codecs    列出可用编码
-formats列出支持的格式
-protocols列出支持的协议
-i input.mp4指定输入文件
-c:v libx264指定视频编码h264
-c:a aac    指定音频编码aac
-vcodec libx264旧写法
-acodec aac旧写法
-fs SIZE指定文件大小
#视频参数
-b bRate设置视频比特率(单位 kbit/s)
-fixaspect固定纵横比
-bt tolerance设置视频比特率容差(单位 kbit/s)
-maxrate bRate设置最大视频比特率容差(单位 kbit/s)
-minrate bRate设置最小视频比特率容差(单位 kbit/s)
-bufsize size设置速率控制缓冲区大小(以 kByte 为单位)
-sameq使用与源相同的视频质量(意味着 VBR)
-newvideo将新的视频流添加到当前输出流
-aspect RATIO纵横比(4:3、16:9 或 1.25)
-r RATE每秒帧率
-s WIDTHxHEIGHT帧大小
-vn去除视频
-an去除音频
#音频参数
-ab bRate设置音频比特率(单位 kbit/s)
-aframes N设置要录制的音频帧数 [-frames:a 的别名]
-aq q设置音频质量(特定于编解码器，VBR) [-q:a 的别名]
-an禁用录音
-acodec codec设置音频编解码器。[-codec:a 的别名] 使用 'copy' 复制流。
-vol以 256 的倍数更改音频音量，其中 256 = 100%(正常)音量。例如 512 = 200%
-newaudio将新的音频流添加到当前输出流
-alang code设置当前音频流的 ISO 639 语言代码(3 个字母)
#码率设置
-b:v 1M      视频比特率(1M = 1Mbit/s)
-b:a 1M      音频比特率(1M = 1Mbit/s)
#主要选项
-f fmt强制输入或输出文件格式
-i fName输入文件名，未指定显示内容流的摘要
-c codecName指定编解码器 [输入或输出]
-fs Nbytes以 Nbytes 指定最大输出文件大小
#全局选项
-y覆盖输出文件
-n不要覆盖输出文件
```

# ffmpeg常用录音+录屏+播放+推流等命令行

```
① 查看dshow支持的设备

ffmpeg -f dshow -list_devices true -i dummy
② 使用麦克风设备进行录音，生成一个wav音频文件

ffmpeg -f dshow -i audio="麦克风阵列 (Realtek(R) Audio)" out.wav
③ 查看麦克风设备支持的参数

ffmpeg -f dshow -list_options true -i audio="麦克风阵列 (Realtek(R) Audio)"
④ 使用麦克风设备进行录音，并指定参数

ffmpeg -f dshow -sample_rate 15000 -sample_size 16 -channels 1 -i audio="麦克风阵列 (Realtek(R) Audio)" out.wav
⑤ ffplay播放wav

ffplay -i out.wav
⑥ wav转pcm

ffmpeg -i out.wav -f s16le out.pcm
⑦ ffplay播放pcm

ffplay -ar 44100 -ac 2 -f s16le test.pcm
⑧ 从mp4文件提取pcm

ffmpeg -i test.mp4 -vn -acodec aac test.aac
ffmpeg -i test.aac -f s16le test.pcm
⑨ 音频重采样

ffmpeg -ar 44100 -ac 2 -f s16le -i test.pcm -ar 43100 -ac 1 s16le test_1_s32le.pcm
（2）录屏+播放

① ffplay实时播放屏幕

ffplay -f gdigrab -i desktop
② 录屏

ffmpeg -f gdigrab -i desktop -vcodec libx264 desktop.mp4
③ 录屏（调整编码参数）

ffmpeg -hide_banner -loglevel error -stats -f gdigrab -framerate 60 -offset_x 0 -offset_y 0 -video_size 1920x1080 -draw_mouse 1 -i desktop -c:v libx264 -r 60 -preset ultrafast -pix_fmt yuv420p -y desktop_full.mp4
④ 录屏+麦克风录音

ffmpeg -f gdigrab -i desktop -f dshow -i audio="麦克风阵列 (Realtek(R) Audio)" -vcodec libx264 -preset ultrafast -acodec libmp3lame -ar 44100 -ac 1 -r 25 desktop.mp4
⑤ 录屏+rtsp推流

ffmpeg -f gdigrab -i desktop -vcodec libx264 -preset ultrafast -r 25 -f rtsp rtsp://127.0.0.1/live/desktop
⑥ 录屏+rtmp推流

ffmpeg -f gdigrab -i desktop -vcodec libx264 -preset ultrafast -r 25 -s 1920*1080 -f flv rtmp://127.0.0.1/live/desktop
（3）摄像头+播放

① 查看dshow支持的设备

ffmpeg -f dshow -list_devices true -i dummy
② 播放摄像头

ffplay -f dshow -i video="USB webcam"
③ 查看摄像头的参数

ffmpeg -list_options true -f dshow -i video="USB webcam"
④ 录制摄像头

ffmpeg -f dshow -i video="USB webcam" -vcodec libx264 camera.mp4
⑤ 摄像头+rtsp推流

ffmpeg -f dshow -i video="USB webcam" -rtsp_transport tcp -vcodec libx264 -preset ultrafast -acodec libmp3lame -ar 44100 -ac 1 -r 25 -f rtsp rtsp://127.0.0.1/live/camera
⑥ 摄像头+rtmp推流

ffmpeg -f dshow -i video="USB webcam" -vcodec libx264 -acodec aac -ar 44100 -ac 1 -r 25 -s 1920*1080 -f flv rtmp://127.0.0.1/live/camera
```

# FFmpeg从mp4提取h264视频和aac文件

```
ffmpeg -i test.mp4 -an -vcodec copy -f h264 test.h264
ffmpeg -i test.mp4 -av -vcodec copy -f aac test.aac
```

<++>
