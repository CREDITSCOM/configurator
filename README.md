<img src="https://raw.githubusercontent.com/CREDITSCOM/Documentation/master/Src/Logo_Credits_horizontal_black.png" align="center">

[![Twitter](https://img.shields.io/twitter/follow/creditscom.svg?label=Follow&style=social)](https://twitter.com/intent/follow?screen_name=creditscom)
[![AGPL License](https://img.shields.io/github/license/CREDITSCOM/configurator.svg?color=green&label=License&style=plastic)](LICENSE)
![Version](https://img.shields.io/github/tag/CREDITSCOM/configurator.svg?label=Version&style=plastic)

# Credits Node Configurator

Cross-platform Credits Node config.ini setupper by Ui

<h3>About</h3>
Configurator helps easily setup Credits Node config.ini file by using flexible ui.<br/>
Credits Node parameters short infomation, possible values exists at square brackets:<br/>
<br/>
<strong><em>Boostrap</em></strong> [list, signal_server] - node startup type,<br/>
 - list used to connect network by user-defined node endpoint list<br/>
 - signal_server used to connect network by existing signal node<br/>
<strong><em>Node type</em></strong> [client, router] - transport node behaviour,<br/>
 - client used to normal node behaviour, also knows as "grey" network node<br/>
 - rounter used as "white" network node to transfer additional data to "grey" nodes<br/>
<strong><em>Server ip/port</em></strong> - ip/port to signal_server<br/>
<strong><em>Input port</em></strong> - node socket port to receive messages<br/>
<strong><em>Public ip/port</em></strong> - node ip/port (endpoint) to send messages from this socket<br/>
<strong><em>Api executor port</em></strong> - internal node port for executor<br/>
<strong><em>Executor port</em></strong> - public and internal executor port for node or clients<br/>
<strong><em>Api port</em></strong> - main public api port<br/>
<br/>
Possible ip format at "ip" edits:<br/>
- ipv4: 123.45.6.78<br/>
- ipv6: 2001:db8:85a3:8d3:1319:8a2e:370:7348<br/>
<br/>
Possible port format at "port" edits:<br/>
- 9000<br/>
<br/>
Possible format at [list] elements:<br/>
- ipv4: 123.45.6.78:9010<br/>
- ipv6: [2001:db8:85a3:8d3:1319:8a2e:370:7348]:9010<br/>

<h2>How to Build</h2>
Use QtCreator with Qt 5.12 or later with C++17 compiler support

<h3>Resources</h3>

<a href="https://credits.com//">CREDITS Website</a>

<a href="https://github.com/CREDITSCOM/DOCUMENTATION">Documentation</a>

<a href="https://credits.com/Content/Docs/TechnicalWhitePaperCREDITSEng.pdf">Whitepaper</a>

<a href="https://credits.com/Content/Docs/TechnicalPaperENG.pdf">Technical paper</a>

<a href="https://developers.credits.com/">Developers portal</a>

<a href="http://forum.credits.com/">Credits forum</a>
<h3>Community links</h3>
   <a href="https://t.me/creditscom"><img src ="https://simpleicons.org/icons/telegram.svg" height=40 widht=40 ></a>
   <a href="https://twitter.com/creditscom"><img src ="https://simpleicons.org/icons/twitter.svg" height=40 widht=40 ></a>
   <a href="https://www.reddit.com/r/CreditsOfficial/"><img src ="https://simpleicons.org/icons/reddit.svg" height=40 widht=40></a> 
   <a href="https://medium.com/@credits"><img src="https://simpleicons.org/icons/medium.svg" height=40 widht=40></a>
   <a href="https://www.instagram.com/credits_com/"><img src="https://simpleicons.org/icons/facebook.svg" height=40 widht=40></a>
   <a href="https://www.facebook.com/creditscom"><img src="https://simpleicons.org/icons/instagram.svg" height=40 widht=40></a>
   <a href="https://www.youtube.com/channel/UC7kjX_jgauCqmf_a4fqLGOQ"><img src="https://simpleicons.org/icons/youtube.svg" height=40 widht=40></a>
