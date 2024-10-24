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
  - ( 특히 auroa, iops설정이 불가능하므로 최대한 CPU를 활용하는게 좋습니다. ) 
  - 예) (업적, 퀘스트, 아이템, 우편) 등이 보통 게임에서 모집단이 많을 법한 테이블이므로 실행 파일을 4개정도로 분산해서 준비 해 놓는게 좋습니다.
2. 로그 류의 정보를 담는 테이블은 실제로는 row수가 엄청날 겁니다.
  - '이런 테이블을 정말로 update를 해야하는가?' 에 대한 고민과 협의가 필요합니다.
  - 실제 라이브라면 점검때는 거의 (시간내에)불가능한 경우가 많습니다.
    - 그럼 안 하던가, 혹은 점검과 별개로 사이드로 진행합니다. 
3. 모집단이 많으면(약 천만 Row수 이상?) Update문 보다는 Insert문을 활용 하는게 더 효율적입니다.
