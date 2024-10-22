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

