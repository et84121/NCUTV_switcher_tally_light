NCUTV switcher tally light
===
tally-light是一種指示燈置於攝影機上，用於告訴被攝人與攝影師說目前這台攝影機的畫面是播出中的。  

這個系統主要由一個發射器和三個接收機組成的。全部的供電採用行動電源進行供電。  

##發射器Part
其中發射器用到了

1. arduino Uno
2. Arduino Ethernet Shield
3. nRF24L01
4. 一塊液晶面板  

乙太網路主要是跟導播機溝通用的，藉由從中攔取ATEM導播機的UDP封包來知曉目前導播機播出哪台攝影機的畫面。  
而nRF24L01則是主從機間的溝通介面，藉由跳頻的方式來選擇不同的接收器。  
液晶面板則主要是用來指出目前的主機的工作狀態。  

##接收器Part
而接收器則是用到了

1. arduino Uno
2. nRF24L01
3. 紅綠LED
4. LED的驅動電路

主要就是藉由接收來自nRF24L01的訊號，並且轉換成LED訊號。

##架構圖
![Imgur](http://i.imgur.com/j6GSElV.png)

##目前的遇到的問題
1.	整套系統的體積過大，已經有縮小的計畫。
2.	沒有一個良好的case，等待經費實作。
3.	接收機的耗電流過小，容易被行動電源認為裝置已經充飽了而關掉電源。

##實體照片
![Imgur](http://i.imgur.com/mLyVMPw.jpg)
![Imgur](http://i.imgur.com/yQQZjxL.jpg)
