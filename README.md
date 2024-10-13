# HyIOCP
- C++로 제작한 IOCP 서버 프로젝트입니다.
- IOCP 서버와 IOCP 서버의 Core lib (HyNetCore), Client로 구성되어 있습니다.
- Protobuf를 패킷 통신에 사용하였고, DB는 MySQL으로 연결했습니다.



### HyNetCore

- IOCP 서버가 include하여 사용하는 서버 코어 기능 libary입니다.
- 세션, 스레드, Job 등 코어 기능을 수행합니다.

### Server

- Core Lib을 사용하여 실제 게임 서버의 역할을 하는 콘솔 서버입니다.
- 유저세션, 서버 세션 등을 관리하고, 프로토버퍼로 생성한 패킷을 핸들링 합니다.
    
![image.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/dca5d1b3-ad21-44f0-b8d7-013810b61237/f65989f7-50eb-4ded-a5fe-36bd08a9337b/image.png)
    

### Client

- 패킷을 서버로부터(에) Recv(Send) 하는 역할을 하는 콘솔 클라이언트입니다.
  
![image.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/dca5d1b3-ad21-44f0-b8d7-013810b61237/ac47cf74-e8a8-45c0-ab96-39b92f3da234/image.png)
