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

이 리포지토리 코드들은 원본 소스코드의 경로에 맞춰놨으므로 해당 경로에 맞게 바꾸는걸 유의합니다


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

### MySQL DB 초기화

'groupadd mysql'

'useradd -r -g mysql -s /bin/false mysql'

'cd /usr/local/mysql'

'mkdir mysql-files'

'chown -R mysql:mysql /usr/local/mysql'

'chown mysql:mysql mysql-files' (해당위치: /usr/local/mysql)

'chmod 750 mysql-files'

위 명령어들을 모두 실행해 줍니다

'bin/mysqld --initialize --user=mysql \
--basedir=/usr/local/mysql \
--datadir=/usr/local/mysql/data'

위 명령어도 실행하는데, 임시 비밀번호가 나오니 잘 확인해두어야 합니다



### 서버 실행
'cd /usr/local/mysql' 

위 명령어를 통해서 해당 폴더로 이동한 후

'sudo bin/mysqld --user=mysql' 

위 명령어를 실행하면 해당 터미널에서 mysql-server가 실행됩니다

### MySQL 인터페이스 실행

서버를 실행 시켜놓은 채로, new terminal을 엽니다

'cd /usr/local/mysql'

'sudo bin/mysql -u root -p'

그리고 위 명령어를 실행하시면 MySQL 인터페이스를 실행할 수 있습니다

alter user 'root'@'localhost' identified by '원하는 비밀번호';

인터페이스 상에서 위 명령어를 실행을 통해 비밀번호를 설정할 수 있습니다

# TCP-H 설치와 실행

'sudo apt install gcc make'

TPC-H 데이터를 생성하기 위해서는 gcc 컴파일러와 make가 필요합니다. 이를 설치합니다.

'git clone https://github.com/electrum/tpch-dbgen.git'

GitHub에서 DBGen을 다운로드합니다.

'cd tpch-dbgen'

'make'

다운로드한 디렉토리로 이동하여 make 명령을 사용해 DBGen을 컴파일합니다.

'ls -l dbgen'

이제 dbgen 실행 파일이 생성되었는지 확인합니다.

'sudo mv tpch-dbgen /usr/local'

tpch-dbgen 폴더를 /usr/local 경로로 옮깁니다<br>
안옮겨도 무방하지만 저는 옮겼습니다

'./dbgen -s 1'

DBGen을 이용해 데이터를 생성할 수 있습니다. -s 옵션을 통해 데이터 크기를 지정할 수 있으며, -s 1은 1GB의 데이터를 생성합니다. <br>
위 명령어는 *.tbl 형식의 데이터 파일을 생성합니다. 각 테이블에 대한 데이터 파일이 포함됩니다. 생성된 파일은 다음과 같습니다:

nation.tbl <br>
region.tbl <br>
customer.tbl <br>
orders.tbl <br>
lineitem.tbl <br>
part.tbl <br>
supplier.tbl <br>
partsupp.tbl <br>


'sudo bin/mysql -u root -p --local-infile=1' <br>
MySQL에 접속합니다. 위 명령어를 이용해주세요

'CREATE DATABASE tpch;'
'USE tpch;'<br>
MySQL에 접속한 후 TPC-H 데이터를 위한 데이터베이스를 생성합니다.


'source /usr/local/tpch-dbgen/dss.ddl;' <br>
이 명령어는 /usr/local/tpch-dbgen/ 경로에 있는 dss.ddl 파일을 읽어, <br>
그 안에 있는 SQL 명령어를 MySQL에서 실행하게 됩니다. <br>
use tpch;가 이미 설정된 상태이므로, tpch 데이터베이스에 필요한 테이블들이 생성됩니다. <br>


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/customer.tbl' <br>
INTO TABLE CUSTOMER <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
CUSTOMER 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/lineitem.tbl' <br>
INTO TABLE LINEITEM <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
LINEITEM 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/nation.tbl' <br>
INTO TABLE NATION <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
NATION 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/orders.tbl' <br>
INTO TABLE ORDERS <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
ORDERS 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/part.tbl' <br>
INTO TABLE PART <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
PART 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/partsupp.tbl' <br>
INTO TABLE PARTSUPP <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
PARTSUPP 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/region.tbl' <br>
INTO TABLE REGION <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
REGION 테이블 데이터 로드


LOAD DATA LOCAL INFILE '/usr/local/tpch-dbgen/supplier.tbl' <br>
INTO TABLE SUPPLIER <br>
FIELDS TERMINATED BY '|' <br>
LINES TERMINATED BY '\n'; <br>
SUPPLIER 테이블 데이터 로드


select <br>
	l_orderkey, <br>
	sum(l_extendedprice * (1 - l_discount)) as revenue, <br>
	o_orderdate, <br>
	o_shippriority <br>
from <br>
	CUSTOMER, <br>
	ORDERS, <br>
	LINEITEM <br>
where <br>
	c_mktsegment = 'BUILDING' <br>
	and c_custkey = o_custkey <br>
	and l_orderkey = o_orderkey <br>
	and o_orderdate < date '1995-03-15' <br>
	and l_shipdate > date '1995-03-15' <br>
group  <br>
	l_orderkey, <br>
	o_orderdate, <br>
	o_shippriority <br>
order by <br>
	revenue desc, <br>
	o_orderdate; <br>
 <br>
쿼리 3번 파일을 위 코드와 같이 수정합니다


'time /usr/local/mysql/bin/mysql -u root -p tpch < /usr/local/tpch-dbgen/queries/3.sql' <br>
TPC-H 쿼리 3번 실행


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
