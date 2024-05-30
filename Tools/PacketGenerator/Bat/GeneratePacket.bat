@echo off
pushd %~dp0\Tools\PacketGenerator\Proto




set LogTag=[GenerateProto]

echo %LogTag% testzzzz

echo %LogTag% Start


echo %LogTag% Generate Start

protoc.exe --proto_path=./ --cpp_out=./ ./Struct.proto
protoc.exe --proto_path=./ --cpp_out=./ ./Enum.proto
protoc.exe --proto_path=./ --cpp_out=./ ./Protocol.proto

echo %LogTag% protoc Generate Result %ERRORLEVEL% 


pushd %~dp0\Tools\PacketGenerator
bin\PacketGenerator.exe --path=Proto/Protocol.proto --output=ServerPacketHandler --recv=C_ --send=S_
bin\PacketGenerator.exe --path=Proto/Protocol.proto --output=ClientPacketHandler --recv=S_ --send=C_

echo %LogTag% PacketGenerator Generate Result %ERRORLEVEL% 

IF ERRORLEVEL 1 PAUSE

echo %LogTag% Generate End

echo 현재 경로....

echo %LogTag% Copy Start
pushd %~dp0\Tools\PacketGenerator\Proto

echo 현재 경로는 다음과 같습니다:
echo %cd%

mkdir "..\..\..\Teset111"


XCOPY /Y /I *.pb.h "..\..\..\Server\Source\Protocol\"
XCOPY /Y /I *.pb.cc "..\..\..\Server\Source\Protocol\"
XCOPY /Y /I *.pb.h "..\..\..\Client\Source\Protocol\"
XCOPY /Y /I *.pb.cc "..\..\..\Client\Source\Protocol\"

pushd %~dp0\Tools\PacketGenerator\Output

XCOPY /Y /I "ClientPacketHandler.h" "..\..\..\Client\Source\"
XCOPY /Y /I "ServerPacketHandler.h" "..\..\..\Server\Source\"


echo %LogTag% Cleaning up origin files
pushd %~dp0\Tools\PacketGenerator\Proto
del *.pb.h
del *.pb.cc

pushd %~dp0\Tools\PacketGenerator\Output
del *.h


echo %LogTag% Copy End

echo %LogTag% End

PAUSE