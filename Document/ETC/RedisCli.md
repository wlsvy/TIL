> 업무 할 때 개인적으로는 레디스 활용 시 우분투 환경에서 쓰고 있습니다. 관련해서 명령어들을 찾아봐야 하고 시간이 지나서 잊어버릴 수도 있는데, 참고할 만한 주요 문서들을 정리해봅니다.

# Redis CLI

> Overview of redis-cli, the Redis command line interface

The redis-cli (Redis command line interface) is a terminal program used to send commands to and read replies from the Redis server. <br/>
It has two main modes: an interactive REPL (Read Eval Print Loop) mode where the user types Redis commands and receives replies, and a command mode where `redis-cli` is executed with additional arguments and the reply is printed to the standard output.

In interactive mode, redis-cli has basic line editing capabilities to provide a familiar tyPING experience.

There are several options you can use to launch the program in special modes. You can simulate a replica and print the replication stream it receives from the primary, check the latency of a Redis server and display statistics, or request ASCII-art spectrogram of latency samples and frequencies, among many other things.

This guide will cover the different aspects of redis-cli, starting from the simplest and ending with the more advanced features.

출처 : [redis.io](https://redis.io/docs/manual/cli/)

## Info

The INFO command returns information and statistics about the server in a format that is simple to parse by computers and easy to read by humans.

The optional parameter can be used to select a specific section of information:

- server: General information about the Redis server
- clients: Client connections section
- memory: Memory consumption related information
- persistence: RDB and AOF related information
- stats: General statistics
- replication: Master/replica replication information
- cpu: CPU consumption statistics
- commandstats: Redis command statistics
- latencystats: Redis command latency percentile distribution statistics
- cluster: Redis Cluster section
- modules: Modules section
- keyspace: Database related statistics
- modules: Module related sections
- errorstats: Redis error statistics

It can also take the following values:

- all: Return all sections (excluding module generated ones)
- default: Return only the default set of sections
- everything: Includes all and modules

When no parameter is provided, the default option is assumed.

**Return** : Bulk string reply: as a collection of text lines.

출처 : [redis.io](https://redis.io/commands/info/)

## MONITOR

MONITOR is a debugging command that streams back every command processed by the Redis server. It can help in understanding what is happening to the database. This command can both be used via redis-cli and via telnet.

출처 : [redis.io](https://redis.io/commands/monitor/)
