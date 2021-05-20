# Raw Traffic


## What It Does
Raw Traffic is a app designed load a page as many times as possible as fast as possible, all routed through your personal proxies. This allows for you to eassily bot traffic to many websites. As of now it only supports loading pages once, however, in the soon future it should also work to bot media streams to any website. This only possible, however, if you buy or rent enough proxies.

## How It Does It
Raw Traffic aims to get the most possible traffic to a website in the least amount of time, while also not beeing too reasource heavy. To do this it is coded purly in c++17 and sends traffic to the target websites with libcurl. Raw Traffic also implements multi-threading with a user deffined number of threads. That way you can use however much or little of your computers resources to complete a task as you want.

## How To Use It
1) Download lastest Release Or Build Your Own
2) Extract compressed folder to location of choice
3) Navigate into the Assets folder
4) Open "settings.json" in a text editor
5) Set variables to what you want bassed on their descriptions (Video Streaming is untested)
6) Open "proxyList.txt" and paste a list of proxies seperated by new lines formmated like the example. The app runs down the list using the proxies then restarts at the top if it needs to. Because of this it would be benifsial to not choose a number too much higher than how many proxies you have or to reuse the same proxies every time (some proxies might get banned)
7) Run the executable

## Coming Soon
 - Bot Media Steams
 - Command Line Intergration
 - Integrate Proxy Rotating API (When I'm less broke)
