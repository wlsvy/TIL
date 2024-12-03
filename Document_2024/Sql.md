# Sql

## 24.10.22

**How to Rename a MySQL Database**

- Database 는 이름을 변경하는 직접적인 방법은 없고, dump 를 복구하는 우회법을 사용

- 1. Create a New Database
  - `CREATE DATABASE new_database_name;`
- 2. Export Data from the Old Database
  - `mysqldump -uroot -p old_database_name > backup.sql`
- 3. Import Data into the New Database
  - `mysql -uroot -p new_database_name < backup.sql`
- 4. Drop the Old Database (Optional)
  - `DROP DATABASE old_database_name;`

## 24.10.24

**라이브 상황에서 고려해볼 만한 내용(TIP)**

1. 실제 라이브라면 위와 같은(테이블 전체 Row를 수정하는)쿼리는 수행 속도를 측정할 필요가 있습니다.
  - 이런 경우는 실행하는 테이블을 `Count(*)`를 조사해서 MysqlClient를 Mysql 장비 CPU수만큼 실행해서 병렬로 분산 실행하면 좋습니다.
  - ( 특히 auroa, IOPS(Input/Output Operations Per Second)설정이 불가능하므로 최대한 CPU를 활용하는게 좋습니다. ) 
  - 예) (업적, 퀘스트, 아이템, 우편) 등이 보통 게임에서 모집단이 많을 법한 테이블이므로 실행 파일을 4개정도로 분산해서 준비 해 놓는게 좋습니다.

2. 로그 류의 정보를 담는 테이블은 실제로는 row수가 엄청날 겁니다.
  - '이런 테이블을 정말로 update를 해야하는가?' 에 대한 고민과 협의가 필요합니다.
  - 실제 라이브라면 점검때는 거의 (시간내에)불가능한 경우가 많습니다.
    - 그럼 안 하던가, 혹은 점검과 별개로 사이드로 진행합니다. 

3. 모집단이 많으면(약 천만 Row수 이상?) Update문 보다는 Insert문을 활용 하는게 더 효율적입니다.

**UPDATE 쿼리가 INSERT 쿼리보다 느린 이유**

1. **수정되는 행이 많은 경우**
   - `UPDATE`는 수정할 행을 찾는 과정에서 시간이 걸리며, 수정 작업 후 여러 추가 작업이 필요합니다.
   - 수정되는 행이 많을수록 처리 속도가 느려집니다.

2. **인덱스의 영향**
   - `UPDATE`는 관련된 인덱스를 다시 작성해야 할 수 있어 시간이 오래 걸릴 수 있습니다.
   - `INSERT`는 새로운 데이터를 추가하는 것이라 인덱스 처리 부담이 상대적으로 적습니다.

3. **트리거 및 제약 조건**
   - `UPDATE`는 트리거 및 제약 조건을 확인하고 실행해야 하기 때문에 성능 저하가 발생할 수 있습니다.
   - `INSERT`는 새로운 데이터에만 해당 조건을 적용하므로 더 빠르게 처리될 수 있습니다.

4. **데이터베이스의 복제 및 트랜잭션 로그**
   - `UPDATE`는 기존 데이터를 수정하므로 많은 트랜잭션 로그 기록이 필요합니다.
   - `INSERT`는 새로운 데이터만 추가하면 되기 때문에 로그 기록이 단순합니다.

5. **행 잠금(Locking)**
   - `UPDATE`는 수정할 행을 잠가야 하며, 여러 트랜잭션 간 락 경합이 발생할 수 있습니다.
   - `INSERT`는 새로운 행을 추가하는 것이므로 일반적으로 락 경합이 적습니다.

6. **스토리지 오버헤드**
   - `UPDATE`는 MVCC(Multi-Version Concurrency Control) 방식에서 원본 데이터를 유지하고 새로운 버전을 생성해야 하므로 스토리지 오버헤드가 발생합니다.
   - `INSERT`는 새로운 데이터만 추가하므로 스토리지 오버헤드가 적습니다.

**MVCC (Multi-Version Concurrency Control)**

1. MVCC란?: 데이터베이스에서 **동시성 제어**를 구현하는 방법
  - 쓰기 트랜잭션은 임시 데이터를 수정하고, 그 동안 읽기 트랜잭션은 원본 데이터를 참조하므로, 서로 충돌하지 않고 동시성을 유지할 수 있다. 이 방식은 데이터의 일관성을 유지하면서 동시 작업 가능

2. 동작 방식
  - **타임스탬프 또는 트랜잭션 ID**: 각 데이터 행에 트랜잭션 ID나 타임스탬프를 부여하여 여러 버전의 데이터를 유지.
  - **Snapshot Isolation**: 트랜잭션 시작 시 해당 시점의 데이터 스냅샷을 생성해 일관성 유지.

3. MVCC의 장점
  - **읽기-쓰기 충돌 방지**: 읽기와 쓰기가 동시에 발생 가능, 성능 향상.
  - **데드락 방지**: 트랜잭션 간 대기 없이 동시 작업 가능.
  - **일관된 읽기 제공**: 긴 트랜잭션에서도 일관된 데이터 제공.

4. MVCC의 단점
  - **스토리지 오버헤드**: 여러 버전을 유지하기 때문에 스토리지 공간을 더 많이 사용.
  - **Garbage Collection 필요**: 오래된 버전을 제거하는 가비지 컬렉션 필요.
  - **복잡한 구현**: 트랜잭션 간 동시성을 제어하는 시스템이 복잡.

5. MVCC를 사용하는 데이터베이스
  - **MySQL (InnoDB)**: InnoDB 스토리지 엔진에서 MVCC 사용.
  - **PostgreSQL**: 일관된 읽기를 제공하기 위해 MVCC 사용.
  - **Oracle**: Oracle Database에서 동시성 제어를 위해 MVCC 사용.

6. 예시
  - **A 트랜잭션**이 주문 정보를 읽는 동안, **B 트랜잭션**이 같은 데이터를 수정해도 A는 변경 전 버전의 데이터를 계속 참조.
  - B 트랜잭션은 새로운 데이터를 추가하거나 수정해도 다른 트랜잭션에 영향을 주지 않고 커밋 가능.

## 24.10.31

[MySQL  MySQL 8.0 Reference Manual  12 Character Sets, Collations, Unicode](https://dev.mysql.com/doc/refman/8.0/en/charset.html)

```
mysql> SHOW CHARACTER SET;
+----------+---------------------------------+---------------------+--------+
| Charset  | Description                     | Default collation   | Maxlen |
+----------+---------------------------------+---------------------+--------+
| big5     | Big5 Traditional Chinese        | big5_chinese_ci     |      2 |
| binary   | Binary pseudo charset           | binary              |      1 |
...
| latin1   | cp1252 West European            | latin1_swedish_ci   |      1 |
...
| ucs2     | UCS-2 Unicode                   | ucs2_general_ci     |      2 |
...
| utf8mb3  | UTF-8 Unicode                   | utf8mb3_general_ci  |      3 |
| utf8mb4  | UTF-8 Unicode                   | utf8mb4_0900_ai_ci  |      4 |
...
```
```
mysql> SHOW CHARACTER SET LIKE 'utf%';
+---------+------------------+--------------------+--------+
| Charset | Description      | Default collation  | Maxlen |
+---------+------------------+--------------------+--------+
| utf16   | UTF-16 Unicode   | utf16_general_ci   |      4 |
| utf16le | UTF-16LE Unicode | utf16le_general_ci |      4 |
| utf32   | UTF-32 Unicode   | utf32_general_ci   |      4 |
| utf8mb3 | UTF-8 Unicode    | utf8mb3_general_ci |      3 |
| utf8mb4 | UTF-8 Unicode    | utf8mb4_0900_ai_ci |      4 |
+---------+------------------+--------------------+--------+
```

```
mysql> SHOW COLLATION WHERE Charset = 'utf8mb4';
+----------------------------+---------+-----+---------+----------+---------+---------------+
| Collation                  | Charset | Id  | Default | Compiled | Sortlen | Pad_attribute |
+----------------------------+---------+-----+---------+----------+---------+---------------+
| utf8mb4_0900_ai_ci         | utf8mb4 | 255 | Yes     | Yes      |       0 | NO PAD        |
| utf8mb4_0900_bin           | utf8mb4 | 309 |         | Yes      |       1 | NO PAD        |
...
| utf8mb4_bin                | utf8mb4 |  46 |         | Yes      |       1 | PAD SPACE     |
...
| utf8mb4_general_ci         | utf8mb4 |  45 |         | Yes      |       1 | PAD SPACE     |
| utf8mb4_german2_ci         | utf8mb4 | 244 |         | Yes      |       8 | PAD SPACE     |
| utf8mb4_hr_0900_ai_ci      | utf8mb4 | 275 |         | Yes      |       0 | NO PAD        |
| utf8mb4_hr_0900_as_cs      | utf8mb4 | 298 |         | Yes      |       0 | NO PAD        |
| utf8mb4_hungarian_ci       | utf8mb4 | 242 |         | Yes      |       8 | PAD SPACE     |
...
| utf8mb4_vi_0900_as_cs      | utf8mb4 | 300 |         | Yes      |       0 | NO PAD        |
| utf8mb4_zh_0900_as_cs      | utf8mb4 | 308 |         | Yes      |       0 | NO PAD        |
+----------------------------+---------+-----+---------+----------+---------+---------------+
```

1. utf8mb4

> MySQL에서 사용하는 문자 집합(Character Set) 중 하나로, UTF-8 인코딩의 확장 버전
>
> 완전한 유니코드 지원: utf8mb4는 UTF-8의 모든 유니코드 문자를 지원하며, 특히 4바이트 문자를 포함. 이모지(emoji)나 특정 아시아 언어의 복잡한 문자 등등을 표현할 수 있음. 
>
> 호환성: 이전의 utf8 문자 집합은 최대 3바이트까지만 지원했기 때문에 일부 유니코드 문자를 저장할 수 없었습니다. utf8mb4는 이러한 제한을 극복합니다.

2. utf8mb4_general_ci

> utf8mb4 문자 집합에 대한 콜레이션(Collation) 중 하나

- utf8mb4: 문자 집합을 지정합니다.
- general: 일반적인(colloquial) 정렬 및 비교 규칙을 의미합니다.
- ci: 대소문자를 구분하지 않는(case-insensitive) 비교를 의미합니다.

3. COLLATE (콜레이션)

> 데이터베이스에서 문자열 데이터를 비교하고 정렬하는 방법을 정의하는 규칙. 문자 집합(Character Set)과 함께 사용

- 대소문자 구분: ci (case-insensitive, 대소문자 구분 없음) vs. cs (case-sensitive, 대소문자 구분)
- 일반 vs. 특정 언어: general vs. unicode 등

## 24.11.28

**MySql 에서 시스템 설정 확인**

- `SHOW VARIABLES;`: MySql 서버의 시스템 변수 확인
- `SHOW VARIABLES LIKE 'max_connections';` : 특정 변수만 확인
- `SELECT @@autocommit, @@sql_mode;` : 특정 변수 값을 확인
- `SHOW STATUS LIKE 'Threads_running';` : 특정 변수 값을 확인
- `SELECT * FROM INFORMATION_SCHEMA.GLOBAL_VARIABLES;`: 글로벌 변수와 값을 조회
- `SELECT * FROM INFORMATION_SCHEMA.GLOBAL_STATUS;` : MySQL 서버 상태 정보 확인
- `SHOW PROCESSLIST;` : 현재 실행 중인 쿼리와 스레드 확인
  - `SHOW FULL PROCESSLIST;` : 더 자세한 정보는 FULL 을 붙이기
- `SHOW GRANTS FOR CURRENT_USER;` : 현재 사용자 권한

## 24.12.03

[MySQL  MySQL 8.4 Reference Manual  17.8.2 Configuring InnoDB for Read-Only Operation](https://dev.mysql.com/doc/refman/8.4/en/innodb-read-only-instance.html)

- mysql 에서 Read Only 속성으로 권한 제한

```sql
CREATE USER 'readonly_user'@'%' IDENTIFIED BY 'password';

-- 특정 데이터베이스에 대한 SELECT 권한 부여
GRANT SELECT ON database_name.* TO 'readonly_user'@'%';

-- 모든 데이터베이스에 대해 읽기 전용 권한 부여 (필요한 경우)
GRANT SELECT ON *.* TO 'readonly_user'@'%';

-- 권한 확인
SHOW GRANTS FOR 'readonly_user'@'%';

-- 권한 적용
FLUSH PRIVILEGES;
```

- View 를 생성하는 경우

```sql
CREATE VIEW readonly_view AS SELECT * FROM database_name.table_name;

-- 권한 부여
GRANT SELECT ON database_name.readonly_view TO 'readonly_user'@'%';
```

