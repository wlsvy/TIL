# Snowflake Id

참고

- [announcing snowflake](https://blog.twitter.com/engineering/en_us/a/2010/announcing-snowflake)
- [github : twitter snowflake](https://github.com/twitter-archive/snowflake/tree/b3f6a3c6ca8e1b6847baa6ff42bf72201e2c2231)
  - [IDWorker Code](https://github.com/twitter-archive/snowflake/blob/b3f6a3c6ca8e1b6847baa6ff42bf72201e2c2231/src/main/scala/com/twitter/service/snowflake/IdWorker.scala)
- c# 코드 예시. [github : snowflake-net](https://github.com/stulzq/snowflake-net/blob/master/Snowflake/IdWorker.cs)

```scala
/** Copyright 2010-2012 Twitter, Inc.*/
package com.twitter.service.snowflake

import com.twitter.ostrich.stats.Stats
import com.twitter.service.snowflake.gen._
import java.util.Random
import com.twitter.logging.Logger

/**
 * An object that generates IDs.
 * This is broken into a separate class in case
 * we ever want to support multiple worker threads
 * per process
 */
class IdWorker(val workerId: Long, val datacenterId: Long, private val reporter: Reporter, var sequence: Long = 0L)
extends Snowflake.Iface {
  private[this] def genCounter(agent: String) = {
    Stats.incr("ids_generated")
    Stats.incr("ids_generated_%s".format(agent))
  }
  private[this] val exceptionCounter = Stats.getCounter("exceptions")
  private[this] val log = Logger.get
  private[this] val rand = new Random

  val twepoch = 1288834974657L

  private[this] val workerIdBits = 5L
  private[this] val datacenterIdBits = 5L
  private[this] val maxWorkerId = -1L ^ (-1L << workerIdBits)
  private[this] val maxDatacenterId = -1L ^ (-1L << datacenterIdBits)
  private[this] val sequenceBits = 12L

  private[this] val workerIdShift = sequenceBits
  private[this] val datacenterIdShift = sequenceBits + workerIdBits
  private[this] val timestampLeftShift = sequenceBits + workerIdBits + datacenterIdBits
  private[this] val sequenceMask = -1L ^ (-1L << sequenceBits)

  private[this] var lastTimestamp = -1L

  // sanity check for workerId
  if (workerId > maxWorkerId || workerId < 0) {
    exceptionCounter.incr(1)
    throw new IllegalArgumentException("worker Id can't be greater than %d or less than 0".format(maxWorkerId))
  }

  if (datacenterId > maxDatacenterId || datacenterId < 0) {
    exceptionCounter.incr(1)
    throw new IllegalArgumentException("datacenter Id can't be greater than %d or less than 0".format(maxDatacenterId))
  }

  log.info("worker starting. timestamp left shift %d, datacenter id bits %d, worker id bits %d, sequence bits %d, workerid %d",
    timestampLeftShift, datacenterIdBits, workerIdBits, sequenceBits, workerId)

  def get_id(useragent: String): Long = {
    if (!validUseragent(useragent)) {
      exceptionCounter.incr(1)
      throw new InvalidUserAgentError
    }

    val id = nextId()
    genCounter(useragent)

    reporter.report(new AuditLogEntry(id, useragent, rand.nextLong))
    id
  }

  def get_worker_id(): Long = workerId
  def get_datacenter_id(): Long = datacenterId
  def get_timestamp() = System.currentTimeMillis

  protected[snowflake] def nextId(): Long = synchronized {
    var timestamp = timeGen()

    if (timestamp < lastTimestamp) {
      exceptionCounter.incr(1)
      log.error("clock is moving backwards.  Rejecting requests until %d.", lastTimestamp);
      throw new InvalidSystemClock("Clock moved backwards.  Refusing to generate id for %d milliseconds".format(
        lastTimestamp - timestamp))
    }

    if (lastTimestamp == timestamp) {
      sequence = (sequence + 1) & sequenceMask
      if (sequence == 0) {
        timestamp = tilNextMillis(lastTimestamp)
      }
    } else {
      sequence = 0
    }

    lastTimestamp = timestamp
    ((timestamp - twepoch) << timestampLeftShift) |
      (datacenterId << datacenterIdShift) |
      (workerId << workerIdShift) | 
      sequence
  }

  protected def tilNextMillis(lastTimestamp: Long): Long = {
    var timestamp = timeGen()
    while (timestamp <= lastTimestamp) {
      timestamp = timeGen()
    }
    timestamp
  }

  protected def timeGen(): Long = System.currentTimeMillis()

  val AgentParser = """([a-zA-Z][a-zA-Z\-0-9]*)""".r

  def validUseragent(useragent: String): Boolean = useragent match {
    case AgentParser(_) => true
    case _ => false
  }
}
```

위 코드에서는 timestamp와 sequence를 갱신하는 동작이 얽히게 되서 스레드 세이프한 동작은 아닙니다. 그래서 동기적(synchronized)으로 실행되게끔 장치를 걸어두고 있습니다.

그렇지만 스레드 세이프하게 코드를 수정할 방법이 있습니다. (CLR via C# 에서 morph 패턴으로 소개된 방식과 비슷 => 원자적으로 수정되는 값을 검증하면서 멀티스레드 환경에서 오염된 값을 읽는 다면 동작을 처음부터 다시 반복하는 것)

- 출처 : [godruoyi/go-snowflake](https://github.com/godruoyi/go-snowflake/blob/master/atomic_resolver.go)

```go
package snowflake

import "sync/atomic"

var lastTime int64
var lastSeq uint32

// AtomicResolver define as atomic sequence resolver, base on standard sync/atomic.
func AtomicResolver(ms int64) (uint16, error) {
	var last int64
	var seq, localSeq uint32

	for {
		last = atomic.LoadInt64(&lastTime)
		localSeq = atomic.LoadUint32(&lastSeq)
		if last > ms {
			return MaxSequence, nil
		}

		if last == ms {
			seq = MaxSequence & (localSeq + 1)
			if seq == 0 {
				return MaxSequence, nil
			}
		}

		if atomic.CompareAndSwapInt64(&lastTime, last, ms) && atomic.CompareAndSwapUint32(&lastSeq, localSeq, seq) {
			return uint16(seq), nil
		}
	}
}
```


We currently use MySQL to store most of our online data. In the beginning, the data was in one small database instance which in turn became one large database instance and eventually many large database clusters. For various reasons, the details of which merit a whole blog post, we’re working to replace many of these systems with the Cassandra distributed database or horizontally sharded MySQL (using gizzard).

Unlike MySQL, Cassandra has no built-in way of generating unique ids – nor should it, since at the scale where Cassandra becomes interesting, it would be difficult to provide a one-size-fits-all solution for ids. Same goes for sharded MySQL.

트위터 팀은 대규모 데이터를 처리하기 위해 카산드라 분산 데이터베이스를 도입했는데, 수평 확장 시스템인 카산드라에서는 MySQL과 다르게 unique Id를 자체 발급하는 기능을 지원하지 않습니다. -> uniqueId 를 지원하기 위한 해결책이 반드시 필요했습니다.

UUID 사용을 고려했지만 이 경우에는 데이터 크기가 128 비트이기 때문에 필요 이상으로 컸습니다. 다른 해결책의 경우에는 상당한 성능 비용을 지불해야 하는 단점이 있었고요.

트위터 팀이 고안한 방법은 timestamp, workerId, sequece Number를 64비트 데이터에 포함시키는 새로운 형식의 포맷을 만드는 겁니다.

![](https://upload.wikimedia.org/wikipedia/commons/5/5a/Snowflake-identifier.png)

snowflake 방식을 통해 시간에 따라 정렬되는 Unique Id를 발급할 수 있게 됩니다. 64비트로 구성되기 때문에 효율적으로 정보 압축이 가능합니다. 그렇지만 기기마다 측정하는 시간에 차이가 있다면 문제가 발생할 지 모릅니다.