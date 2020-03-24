# 在ESP32上通过蓝牙与微信小程序连接实现的莫尔斯电码练习器
#### 全部功能需配合微信小程序使用。在微信中搜索“ZClubCola”即可找到对应的微信小程序，或者使用微信扫描下方的小程序码。

<div align=left> <img src = "https://tva1.sinaimg.cn/large/00831rSTgy1gcl8ate0vuj30by0bymz4.jpg" width="200px" />
</div>

## 物料清单
|名称|数量|说明|
|:---:|:---:|:---|
|ESP32开发板|1块||
|无源蜂鸣器|1只|3.3V供电，或根据自己实际情况选择|
|3.5毫米音频母座|1个|用于连接电键。若使用开关替代电键则不需要音频母座|
|开关|1个|用于替代电键，根据实际情况选择|
|螺杆及螺帽|2套|可选，用于引出触摸电键的引脚，可用其他物料替代。|
|杜邦线|若干||


## 使用方法
- ### 下载Arduino的IDE
	在 <a href = "https://arduino.cc" target = "__blank">官网（https://arduino.cc）</a>下载即可
- ### 在Arduino的IDE中安装esp32开发板支持包
	在Arduino的IDE中依次选择：首选项 - 设置 

	在“设置”标签卡中的“附加开发板管理器网址”添加如下链接：
	https://dl.espressif.com/dl/package_esp32_index.json

	添加完成后确定并关闭标签卡。再依次选择：工具 - 开发板 - 开发板管理器。

	在弹出的对话框的搜索输入栏中输入“ESP32”，并回车。选中检索出来的结果并安装。

- ### 下载源码并上传至开发板
	1. 将本项目源码下载后解压，并保持解压后的文件夹名称与主文件名称一致。
	1. 将ESP32通过USB数据线连接到电脑
	1. 使用Arduino IDE打开本项目源码
	1. 在Arduino IDE中依次选择： 工具 - 开发板 - ESP32 Dev Module
	1. 在Arduino IDE中的 “工具” 菜单中的 “端口” 选择ESP32所使用的端口
	1. 点击Arduino IDE界面中左上角的 “上传” 按钮，等待上传完成


- ### 接线
	电键
	|KEY|ESP32|
	|:---:|:---:|
	|PIN 1|GPIO 17|
	|PIN 2|GPIO 16|
	|GND| GND|

	蜂鸣器
	|BEE|ESP32|
	|:---:|:---:|
	|VCC|3.3V|
	|GND|GND|
	|IO|GPIO 23|

	触摸电键
	|TOUCH KEY|ESP32|
	|:---:|:---:|
	|PIN 1|GPIO 33 (T8)|
	|PIN 2|GPIO 32 (T9)|

	##### 说明：以上为默认情况下的接线方式，具体的设备可根据自己的实际情况连接，对应的引脚可以在pin.h中修改。

- ### 打开微信小程序
扫描小程序码或在微信中搜索小程序名称“ZClubCola”即可打开微信小程序

- ### 检查各项状态
微信小程序顶部有状态指示图标，分别为“莫尔斯电码练习器连接状态”，“MQTT服务器连接状态”， “手机蓝牙状态”。
灰色图标表示无效，蓝色表示有效。

注意：如果需要连接练习器，必须要先开启手机的蓝牙功能。

- ### 配对连接练习器
在手机开启蓝牙功能的状态下，点击“莫尔斯电码练习器”的状态指示图标。微信小程序会尝试使用蓝牙并搜索周边的已开机的莫尔斯电码练习器。如果搜索到相关设备，则会在底部弹出设备列表菜单，点击菜单中需要连接的设备即可配对连接。

- ### 设置参数
	在小程序首页点击右上方的齿轮按钮即可进入设置页面。其中：
1. ##### 呼号

	设置在MQTT上发送信息所显示的呼号。

1. ##### 电键类型

	切换当前使用的电键是手动电键或自动电键。

1. ##### 自动键左右按键交换

	当使用自动电键时切换点和划的按键。

1. ##### 使用触摸电键

	是否使用触摸电键。

1. ##### 触摸电键灵敏度

	设置触摸按键的灵敏度，数值越大灵敏度越高。

1. ##### 点与划的时长比例（标准为3） 

	设定“点”和“划”的时长比例。按照标准点为一个单位时长，划为三个单位时长。

1. ##### 地狱模式

	开启地狱模式后，使用手动电键必须严格按照所设定的时长进行电码的键入，否则不予以识别。

1. ##### 地狱模式容错率

	在开启地狱模式后，允许有一定的键入时长误差，这里按照正负百分比进行判断，最低为0%（即不能有一毫秒的误差），最高为100%。<br>
	例如：单位时长设定为100毫秒，容错率设定为0.1。则键入的时长在90毫秒和110毫秒范围内，均视为有效的键入点。如果设定容错率为0，则必须键入时长为准确的100毫秒才会被认为是有效的键入了点。（祝设定容错率为0的你玩的开心~）

1. ##### 是否转换电码

	是否将莫尔斯电码转换为对应字符并显示出来。

1. ##### 是否播放自己的电码

	当从MQTT上接收到自己刚刚发送的电码后，是否播放这条自己所发送的电码。

1. 发报时点的最大时长

	设置点的最大时间长度，使用手动电键时，小于此时长的视为点，大于此时长设为键入划。

1. ##### 播放电码时的最大时长

	在播放电码时，点的时长。

1. ##### 防抖时长

	电键消除抖动的时长。小于该时长的键入均视为无效键入。

1. ##### 是否自动发送电码到MQTT服务器

	开启后等待一定时间后自动将键入的电码发送至MQTT服务器。如果关闭该选项，则只有在点击“发送”按钮之后才会发送刚刚键入的电码。

1. ##### 自动发送等待时长

	开启自动发送之后空闲多久后将电码发送至MQTT服务器

1. ##### 字母间隔时长

	键入电码时，字母之间的间隔时间。

1. ##### 蜂鸣器频率

	设置蜂鸣器的鸣叫频率，可以更改蜂鸣器的鸣叫音调。


## 更新日志

#### 2020-03-22
- 增加“地狱模式”

#### 2020-03-20
- 增加设置参数在EEPROM中存储

#### 2020-03-04
- 增加支持触摸电键

## 特别鸣谢