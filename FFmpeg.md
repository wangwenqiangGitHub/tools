# FFmpeg 基本命令
- 转换数据格式:ffmpeg -i in.mp4 -vcodec copy -acodec copy out.flv
> 参数含义 -vcodec 表示拷贝视频, -acodec表示拷贝音频;
> -an表示不要音频，-vn表示不要视频, -ar音频的采样率，-ac2 channel:音频的单声道，双声道，环绕立体声。
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
```
> 原始数据的数据量越大，处理时间更长.

- 图片转视频，视频转图片
```shell
ffmpeg -i image-%3d.jpeg out.mp4
ffmpeg -i out.mp4 -r 1 -f image2 image-%3d.jpeg
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
```
## 为音频添加封面
- 有些视频网站只允许上传视频文件。如果要上传音频文件，必须为音频添加封面，将其转为视频，然后上传。下面命令可以将音频文件，转为带封面的视频文件。
```
ffmpeg -loop 1 -i cover.jpg -i input.mp3 -c:v libx264 -c:a aac -b:a 192k -shortest output.mp4
# 上面命令中，有两个输入文件，一个是封面图片cover.jpg，另一个是音频文件input.mp3。-loop 1参数表示图片无限循环，-shortest参数表示音频文件结束，输出视频就结束。
```

