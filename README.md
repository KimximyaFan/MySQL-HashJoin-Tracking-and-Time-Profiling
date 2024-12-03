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

![image](https://github.com/user-attachments/assets/f3c6bc62-2055-463c-9bc8-900d3333a1a2)

'git clone https://github.com/electrum/tpch-dbgen.git'

GitHub에서 DBGen을 다운로드합니다.

'cd tpch-dbgen'

'make'

다운로드한 디렉토리로 이동하여 make 명령을 사용해 DBGen을 컴파일합니다.

'ls -l dbgen'
이제 dbgen 실행 파일이 생성되었는지 확인합니다.

![image](https://github.com/user-attachments/assets/127b2959-01d8-45cc-840a-240d7998fd7e)

'sudo mv tpch-dbgen /usr/local'

tpch-dbgen 폴더를 /usr/local 경로로 옮깁니다<br>
안옮겨도 무방하지만 저는 옮겼습니다

![image](https://github.com/user-attachments/assets/771676a2-19da-4965-bd47-9e9abb90dc26)

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

![image](https://github.com/user-attachments/assets/f839a1f7-4654-46e4-b177-12ee0d5553bf)


'CREATE DATABASE tpch;'
'USE tpch;'<br>
MySQL에 접속한 후 TPC-H 데이터를 위한 데이터베이스를 생성합니다.

![image](https://github.com/user-attachments/assets/c079d41b-d966-4190-a66b-822b7e07f0ad)

![image](https://github.com/user-attachments/assets/c90be4d1-f704-4dcf-99bd-b77d77ccc689)

'source /usr/local/tpch-dbgen/dss.ddl;' <br>
이 명령어는 /usr/local/tpch-dbgen/ 경로에 있는 dss.ddl 파일을 읽어, <br>
그 안에 있는 SQL 명령어를 MySQL에서 실행하게 됩니다. <br>
use tpch;가 이미 설정된 상태이므로, tpch 데이터베이스에 필요한 테이블들이 생성됩니다. <br>

![image](https://github.com/user-attachments/assets/5c23d3ea-05fd-4bc3-bdce-7118add0333d)

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

![image](https://github.com/user-attachments/assets/8722586c-c46d-4876-8c54-be82f5f5f9df)

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

![image](https://github.com/user-attachments/assets/d29dbb2e-be1d-4100-b92d-98a5153e9afe)

'time /usr/local/mysql/bin/mysql -u root -p tpch < /usr/local/tpch-dbgen/queries/3.sql' <br>
TPC-H 쿼리 3번 실행


# 함수 추적 과정

![1](https://github.com/user-attachments/assets/7713ac47-044a-4881-8b38-2c16f5c7d779)

일단 hash join 키워드가 들어있는 소스코드 파일을 찾아 들어갔습니다

![2](https://github.com/user-attachments/assets/17ed23be-b426-4b7e-9aad-b79c6c726642)

해당 파일들의 모든 함수에 printf 를 찍어보고 추적해본 결과

![3](https://github.com/user-attachments/assets/8593455e-3fe2-4ea2-9e27-deaebb178302)

위 그림과 같은 구조임을 알아냈습니다

![4](https://github.com/user-attachments/assets/cbbd0e78-72d6-41c4-b051-370edf89d3a7)

해쉬조인이 실행되는 쿼리를 수행했더니 mysqld 터미널상에서 printf 가 찍힙니다

![image](https://github.com/user-attachments/assets/5341be20-d9a7-4ddd-b824-c6e3274e3b1d)

수많은 일련의 과정들을 거쳐서 확인해본 결과, 해쉬조인 기능 자체의 응집도가 높게 설계되어 있어서<br>
외부에서 해쉬조인을 호출하는건, accesspath에서 해쉬조인 이터레이터를 만들고<br>
sql_union 쪽에서 이터레이터를 실행합니다 

![image](https://github.com/user-attachments/assets/0c5d1e80-0fb7-493d-b267-fbab093e18ce)

사실상 해쉬조인 모듈 호출은 위 코드에서 한 곳밖에 없다고 봐도 무방합니다<br>
sql_union 에서 이터레이터 실행은 다형성으로 작동하기 때문입니다

![image](https://github.com/user-attachments/assets/8302f1ef-2b8c-4707-8a15-c2d91a0cba12)

그래서 해당 기점을 중심으로 상위 방향으로 함수추적을 쭉 진행하였습니다<br>
일단 나이브하게 추적해본 결과 sql_union 쪽에서 optimize 함수를 수행하였습니다

![image](https://github.com/user-attachments/assets/0565809b-b531-4a23-bb56-6ce6cdf651cd)

![image](https://github.com/user-attachments/assets/2a697150-7c44-4315-aab3-6e57dfbbf2e1)

![image](https://github.com/user-attachments/assets/54a7682e-e923-44d9-bbfb-44053445b3fb)

똑같은 추적방식으로 계속해서 상위방향으로 함수를 추적해 나갔습니다

![image](https://github.com/user-attachments/assets/b2fda8b5-3b9d-45cb-aae8-3b0aca2f4864)

최종적으로 sql_parse.cc 에서 do_command() 함수라는 곳에 도달하였고, 해당 함수는

![image](https://github.com/user-attachments/assets/ceec1cb5-a1fe-4b72-a1e9-7467cb7e1bdc)

그림과 같이 mysql 인터페이스 상에서 쿼리를 입력 받는 부분임을 알아냈습니다

![image](https://github.com/user-attachments/assets/99280145-6a90-434f-a6b9-1dd18cd2c0f8)

좀 더 디테일하게 추적해본 결과, CreateIteratorFromAccessPath() 에서 해쉬조인 이터레이터를 만들고<br>
일련의 과정을 거쳐서 sql_union 에서 ExecuteIteratorQuery() 실행 이후 본격적인 해쉬조인이 실행됨을 알 수 있습니다 

![image](https://github.com/user-attachments/assets/6b972f5f-4db2-430d-8afc-561e236b070e)

최종적인 상위에서 해쉬조인 시작까지의 과정인 위 그림과 같습니다

# 시간 측정 과정

![image](https://github.com/user-attachments/assets/d475453f-0a53-4e0f-b9f4-bb7830254ccb)
![image](https://github.com/user-attachments/assets/ce9beb81-0393-493a-98a8-e74b688b0a4c)

일단 첫번째로 해볼 것은 <br>
전체 시간 중 해쉬조인이 시간을 얼마나 차지하는지, 다른 기능은 시간이 얼마나 걸리는지 <br>
전체 시간을 측정하는 것입니다 <br>
TCP-H 쿼리3 번을 실행하면 위 그림과 같이 <br>
do_command() 가 두 번 찍힙니다 <br>
첫 번째 do_command()는 모르는 쿼리이고 두 번째 쿼리가 해쉬조인을 수행하므로 <br>
일단 저 두 쿼리를 나눠서 시간을 측정합니다

![image](https://github.com/user-attachments/assets/2afee973-90b6-4736-bf45-7ccd9e9ad4fa)

시간 측정에 쓰는 define으로 만든 함수입니다

![image](https://github.com/user-attachments/assets/c06a2270-4457-4d4b-919a-91dff6eef972)

위 두 구간 시간 측정을 위한 변수들입니다

![image](https://github.com/user-attachments/assets/cfd319e1-48fc-451f-8188-34c69fd5d726)

![image](https://github.com/user-attachments/assets/3af99c32-347d-4c31-a176-c1bc9c4764d3)

do_command() 함수를 래퍼로 감싸서 시작시간을 측정하고 <br>
쿼리가 끝날 때 Check_secondary_engine_statement() 도 항상 실행하므로 <br> 
해당 함수도 래퍼를 이용해서 종료 시간을 측정합니다 

![image](https://github.com/user-attachments/assets/3f90bcb9-5eac-4742-881b-1d7c31589753)

![image](https://github.com/user-attachments/assets/595e0ef9-a1fa-4a70-b884-b7659f21b26a)

![image](https://github.com/user-attachments/assets/5c5c851e-e0f1-4689-a40c-3fb1998f7564)

![image](https://github.com/user-attachments/assets/80bc98be-a2d0-4049-91c3-e920fdcaa99a)

TCP-H 쿼리 3번은 해쉬조인 관련 쿼리가 92%의 시간을 차지하므로<br>
해쉬조인쪽으로 시간 분석을 들어가는게 타당함을 알 수 있습니다

![image](https://github.com/user-attachments/assets/11c9d4cb-2d85-483d-9f6c-3065c9a5e82c)

![image](https://github.com/user-attachments/assets/60efc5a9-baf2-46fc-a86f-e0c332611d0c)

![image](https://github.com/user-attachments/assets/e24ba489-c354-4f03-889c-edb34cf73237)

위 그림은 의도적으로 해쉬조인을 유도한 쿼리를 실행 했을 때 함수의 추적입니다 <br>
하얗게 박스친 부분이 높은 반복으로 나타난 구간을 의미합니다 <br>
직관적으로 보면, 반복되는 함수들이 실행시간 총합이 높을 것이므로<br>
저기에 있는 함수들을 골라서 시간을 측정해보는게 타당합니다

![image](https://github.com/user-attachments/assets/27266ef7-719b-45b5-8495-7818552f0e19)

![image](https://github.com/user-attachments/assets/32bfd947-91ea-49b3-9e4d-fd3e63f06ba7)

![image](https://github.com/user-attachments/assets/47936d95-ba70-49c3-a266-eb4f1a923dfc)

정리 해보면 위 그림과 같은 함수들이 나오는데 <br>
chunk 생성자 소멸자는 추적이 까다로워서 스킵했습니다 <br>
그리고 StoreRow(),  ReadRowFromProbeIterator() 관련 함수 시간을 측정 했습니다 <br>

![image](https://github.com/user-attachments/assets/089e7401-368c-445a-8e87-44e221a01aaf)

![image](https://github.com/user-attachments/assets/d91e7bdd-c4c1-48ba-8d94-c819368f7f38)

![image](https://github.com/user-attachments/assets/945ef834-fd55-4c54-b842-8272eb4b8ac3)

StoreRow() 관련 시간 측정입니다

![image](https://github.com/user-attachments/assets/9169cb8d-dcc8-442c-9fbd-c0596a03dd24)

![image](https://github.com/user-attachments/assets/a6bb535f-d09a-4e36-9b38-26cd982c9b3c)

![image](https://github.com/user-attachments/assets/dff8590c-9382-4a96-bcc7-a170264ad761)

위 그림처럼 시간을 구했었고

![image](https://github.com/user-attachments/assets/6c4c9a43-58c5-4018-9bc4-df3b9e759459)

![image](https://github.com/user-attachments/assets/58f76fc9-742b-44e0-a06b-1d98b18d091e)

![image](https://github.com/user-attachments/assets/e97d7eac-fde6-49cc-9627-c4b4a0930ff0)

StoreRow() 관련 함수들은 해쉬조인 관련 시간중에서 극히 낮은 비중을 차지함을 알아냈습니다

![image](https://github.com/user-attachments/assets/9ba506e9-85b4-4846-9ed2-1f774dff0f46)

![image](https://github.com/user-attachments/assets/4d52cc38-9477-4c6a-a59f-4b3d59ec3edc)

![image](https://github.com/user-attachments/assets/b50e6300-91ff-45ec-9967-3b802b26f548)

Read Row From Probe Iterator 관련 시간측정 변수들입니다

![image](https://github.com/user-attachments/assets/447606df-4a82-4086-9b14-0431ff59b280)

![image](https://github.com/user-attachments/assets/f632ec52-a692-435f-87b0-81d076ad5cc6)

![image](https://github.com/user-attachments/assets/2ee5e3b1-79e4-4438-9681-f85e3c05a4a6)

![image](https://github.com/user-attachments/assets/56ab2f95-1b0d-47f3-a498-8b77c4283699)

![image](https://github.com/user-attachments/assets/b5475857-f6d8-4795-947c-e24aa00b79b8)

![image](https://github.com/user-attachments/assets/72521acb-8815-4c88-b7f4-f14ef73cbcbc)

![image](https://github.com/user-attachments/assets/924f784e-78b2-4dc6-adda-19df72af7fe7)

![image](https://github.com/user-attachments/assets/84c6e8a1-9372-4067-ab34-001863c8bb6a)

![image](https://github.com/user-attachments/assets/6a0c2087-15e9-4dde-921c-4726b27ed3c1)

![image](https://github.com/user-attachments/assets/b3e03678-e761-44a3-8567-01c4fa78f45c)

결과를 보면 <br>
ReadRowFromProbeIterator() <br>
ReadNextJoinedRowFromHashTable() <br>
위 두 함수의 실행시간 총합이 굉장히 높은 비율을 차지함을 알 수 있습니다 <br>
그렇다면 해당 함수를 파고드는게 타당합니다


# 결론

using TCP-H Query 3

![1](https://github.com/user-attachments/assets/490db56b-0135-4f27-8a2e-ac89bdd890d1)

![2](https://github.com/user-attachments/assets/1d9aced6-728c-4056-81c7-125d8e980b5b)

![3](https://github.com/user-attachments/assets/f63c1a4d-4f36-4907-85f2-6aed101abf0f)

![4](https://github.com/user-attachments/assets/b1e1b21a-261d-4b48-9e32-8adc26e76da8)

![5](https://github.com/user-attachments/assets/8c410a74-a81c-4684-ab17-350116bb19b8)

![6](https://github.com/user-attachments/assets/931bfa8c-06ae-4d10-819f-20adf6c92f28)

![7](https://github.com/user-attachments/assets/9e82e487-ddde-40b0-990a-fc98a0dc140f)
