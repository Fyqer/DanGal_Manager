# DanGal Manager

This is project of small desktop application for managing password without using netowrk connection. 


### Available Functions
- Hashing master password in MD5 on local disk.
- Deleteing / editing / adding password and services names.
- Hashing passwords in AES encryption:
#### AES Levels
The class supports all AES key lenghts

* AES_128
* AES_192
* AES_256

#### Modes
The class supports the following operating modes

* ECB
* CBC
* CFB
* OFB

#### Padding
By default the padding method is `ISO`, however, the class supports:

* ZERO
* PKCS7
* ISO


#### LAUNCHING:
The program does not need to install additional libraries. To run the program, use an executable file (.exe).
- the program will ask us to enter the master password, if we have not used it before, a new masterPassword file with the master password hash will appear.
- run exe file again and start using it!
- 
Application using a third-party code for AES encryption, repository:( https://github.com/bricke/Qt-AES)

