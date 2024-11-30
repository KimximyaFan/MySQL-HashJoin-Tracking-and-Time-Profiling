# MySQL-HashJoin-Tracking-and-Time-Profiling

참조 : https://nali.tistory.com/44

This codes are customized from 'MySQL-Server 8.0.36' for tracking and profiling hash join

all the customized codes can be found by 'Ctrl-F -> hong'

# 실행환경
우분투 운영체제를 사용하였습니다

저는 VMware 를 이용해서 가상으로 운영체제를 돌렸습니다

# MySQL 8.0.36 다운로드와 소스코드 파일 변경
깃허브 용량 제한 2GB 때문에 일단 일반 MySQL을 다운로드합니다

https://github.com/mysql/mysql-server/tree/mysql-8.0.36

위 링크에서 MySQL 8.0.36 버전을 다운로드 합니다

압축을 해제 한 후, 원본 소스코드의 일부를, 이 리포지토리에 있는 소스코드로 바꿉니다


# 설치

mysql-server 폴더를  '/usr/local' 경로로 이동시킵니다

그냥 하셔도 무방하지만 컨벤션 경로를 따릅니다

그 후, mysql-server 폴더에서 새로운 폴더를 만듭니다

'sudo mkdir mysqldir' 를 합니다

'cd /usr/local/mysql-server/mysqldir' 이 명령어를 통해 이동합니다

그 후 mysqldir 폴더 내에서 

sudo cmake .. \
-DCMAKE_INSTALL_PREFIX=/usr/local/mysql \
-DMYSQL_DATADIR=/usr/local/mysql/data \
-DMYSQL_UNIX_ADDR=/usr/local/mysql/mysql.sock \
-DMYSQL_TCP_PORT=3306 \
-DDEFAULT_CHARSET=utf8 \
-DDEFAULT_COLLATION=utf8_general_ci \
-DSYSCONFDIR=/etc \
-DWITH_EXTRA_CHARSETS=all \
-DWITH_INNOBASE_STORAGE_ENGINE=1 \
-DWITH_ARCHIVE_STORAGE_ENGINE=1 \
-DWITH_BLACKHOLE_STORAGE_ENGINE=1 \
-DDOWNLOAD_BOOST=1 \
-DWITH_BOOST=/usr/local/mysql/boost

위 명령어를 복사 붙여넣기 해서 실행합니다

CMake 가 끝나시면 이제 make를 합니다

'sudo make' 를 하시면 됩니다 

오래걸리므로 'sudo make -j2' 혹은 'sudo make -j4' 를 하셔도 무방합니다

make가 끝나시면

'sudo make install' 명령어를 실행합니다


# 실행

### 서버 실행
'cd /usr/local/mysql' 

위 명령어를 통해서 해당 폴더로 이동한 후

'sudo bin/mysqld --user=mysql' 

위 명령어를 실행하면 해당 터미널에서 mysql-server가 실행됩니다

### MySQL 인터페이스 실행


# TCP-H 설치와 실행

# 함수 추적 과정

# 시간 측정 과정

# 결론

using TCP-H Query 3

![1](https://github.com/user-attachments/assets/490db56b-0135-4f27-8a2e-ac89bdd890d1)

![2](https://github.com/user-attachments/assets/1d9aced6-728c-4056-81c7-125d8e980b5b)

![3](https://github.com/user-attachments/assets/f63c1a4d-4f36-4907-85f2-6aed101abf0f)

![4](https://github.com/user-attachments/assets/b1e1b21a-261d-4b48-9e32-8adc26e76da8)

![5](https://github.com/user-attachments/assets/8c410a74-a81c-4684-ab17-350116bb19b8)

![6](https://github.com/user-attachments/assets/931bfa8c-06ae-4d10-819f-20adf6c92f28)

![7](https://github.com/user-attachments/assets/9e82e487-ddde-40b0-990a-fc98a0dc140f)
