# AtDevcat_2024

## 24.02.27

[c - Is it Safe to use ReaderWriterLockSlim in an async method - Stack Overflow](https://stackoverflow.com/questions/15882710/is-it-safe-to-use-readerwriterlockslim-in-an-async-method)

```cs
System.Threading.ReaderWriterLockSlim readerwriterlock = new System.Threading.ReaderWriterLockSlim();
private async Task Test()
{
    readerwriterlock.EnterWriteLock();
    await Task.Yield(); //do work that could yield the task
    readerwriterlock.ExitWriteLock(); //potentailly exit the lock on a different thread
}
```

위의 코드는 안전하지 못하다.

`await Task.Yield();` 라인 전후로 실행 스레드가 다를 수 있기 때문이다!!!

락을 거는 스레드와 해제하는 스레드가 다르면 스레드 안전성이 위반된다. 정말 정말 큰일 날 수 있다!!!

**ChatGPT 답변**

`ReaderWriterLockSlim`을 비동기 코드 내에서 사용하는 것은 주의를 요합니다. 위의 코드 예제에서는 비동기 메서드(Loop1 및 Loop2) 내에서 ReaderWriterLockSlim의 EnterWriteLock과 ExitWriteLock을 사용하고 있습니다. 이러한 방식으로 ReaderWriterLockSlim을 사용하는 것은 일반적으로 안전해 보이지만, 비동기 프로그래밍의 맥락에서 몇 가지 주의해야 할 점이 있습니다:

비동기와 블로킹 호출의 혼합 사용: ReaderWriterLockSlim의 EnterWriteLock 메서드는 호출 스레드를 블로킹합니다. 이는 await Task.Delay(1000);와 같은 비동기 호출 후에 이루어질 경우, 비동기 작업이 완료된 후 동기 블로킹 호출이 이루어지는 것입니다. 이러한 패턴은 일반적으로 권장되지 않으며, 특히 UI 스레드와 같이 블로킹되어서는 안 되는 스레드에서는 사용을 피해야 합니다.

데드락 위험: 위의 예시 코드 자체에서 직접적인 데드락을 유발할 명확한 요소는 없습니다. 그러나, ReaderWriterLockSlim을 사용하는 복잡한 비동기 흐름에서는 데드락 위험이 있습니다. 예를 들어, 하나의 태스크가 쓰기 락을 획득한 상태에서 다른 태스크가 같은 락을 기다리는 동안, 첫 번째 태스크가 후자의 완료를 기다리게 되면 데드락이 발생할 수 있습니다.

비동기 코드에서의 락 관리: ReaderWriterLockSlim은 본질적으로 동기적 락 메커니즘입니다. 비동기 코드에서는 SemaphoreSlim의 WaitAsync 메서드와 같이, 비동기적으로 대기할 수 있는 락 메커니즘을 사용하는 것이 더 적합할 수 있습니다. 이러한 메커니즘은 비동기 작업이 락을 기다리는 동안 스레드를 블로킹하지 않고 대기하도록 해줍니다.

요약하자면, ReaderWriterLockSlim은 주로 동기 코드에서 사용될 때 안전하며, 비동기 코드에서 사용할 때는 주의가 필요합니다. 특히, 비동기 작업 내에서 블로킹 락 호출을 피하고, 가능하다면 비동기 작업에 적합한 락 메커니즘을 사용하는 것이 좋습니다. 비동기 코드에서 ReaderWriterLockSlim 같은 동기 락을 사용할 때는 데드락이나 성능 저하의 위험을 충분히 고려해야 합니다.

## 24.02.28

[White House - PRESS RELEASE: Future Software Should Be Memory Safe](https://www.whitehouse.gov/oncd/briefing-room/2024/02/26/press-release-technical-report/)

> ONCD makes the case that technology manufacturers can prevent entire classes of vulnerabilities from entering the digital ecosystem by adopting memory safe programming languages. ONCD is also encouraging the research community to address the problem of software measurability to enable the development of better diagnostics that measure cybersecurity quality.

백악관에서 디지털 환경에서 사이버 공격을 방지하기 위해, 메모리 세이프한 소프트웨어의 필요성을 강조함.

**게임 기동 속도 높이기**

- 현대인은 인내심이 매우 부족하고 짧은 시간에도 집중력을 잃는다.
  - 게임 초기 기동 시간이 길면 유저 이탈로 이어짐
- 기동 속도를 줄이거나, 대기 중에 주의를 환기시킬만한 다른 요소를 집어넣어야 한다. (동영상을 튼다거나)

[Jake Seo on X 세계 최고의 개발자 중 한명인 존 카맥이 시간을 관리하는 방식 인터뷰한 것을 나름대로 정리해봄 인터뷰 영상이 마치 커피챗하는 것 같아 재밌었다 - 몇십년간 주 60시간 이상 일해옴 - 매일 10시간 정도 - 젊었을 때는 굉장히 불규칙적으로 살았음 - 밤을 새거나 늦잠을 자기도 함 - 나이가 들어서…  X](https://twitter.com/JakeSeo8/status/1733483508549693512?s=20)

세계 최고의 개발자 중 한명인 존 카맥이 시간을 관리하는 방식 인터뷰한 것을 나름대로 정리해봄

인터뷰 영상이 마치 커피챗하는 것 같아 재밌었다

- 몇십년간 주 60시간 이상 일해옴
- 매일 10시간 정도
- 젊었을 때는 굉장히 불규칙적으로 살았음
- 밤을 새거나 늦잠을 자기도 함
- 나이가 들어서 아이를 낳고 나서는 일반 직장인과 비슷한 패턴으로 삶
- 최근 몇달간 4마일 (약 6km) 정도를 걷거나 뛰는데 효과가 있는 것 같다
- 운동한 다음 샤워 후의 몇시간이 자신에게 최고의 시간이었다
- 난 12시간만 일하면 뇌가 지치는데 20시간씩 일하는 프로그래머가 부럽다
- 4시간만 자고 일하는 독종을 이기긴 어렵다
- 사람들에게는 8시간은 꼭 자라고 조언한다
- 스스로를 압박하지 말고 억지로 일찍 일어나지 말라고
- 한 게임 개발자의 말을 빌리면 "지나치게 많은 일은 반드시 큰 문제를 가져온다" 라고 함
- 몇몇 사람들은 생산성에 대한 지식을 잘못 인용하며 주 40시간 일하는 것은 매우 비효율적이라고 말한다
- 너무 오래 일하면 생산성이 감소하긴 하지만 몇시간 더 일한다고 성과가 나빠지진 않음
- 당장 지구에 소행성이 떨어진다면, 여러분은 일론머스크가 이를 막기 위해 일하면서 오후 5시에 칼퇴하는 것을 두고볼 것인가?
- 나를 재수 없는 놈 (Asshole) 으로 보는 시선도 있겠지만, 진실은 더 오래 일할수록 더 많은 성과를 얻는다
- 모두가 열심히 일 할 필요는 없지만 무언가를 이루려면 일에 매진해야 한다
- 난 일반적인 직장인과 매우 다르다
- 일이 내 삶에 미치는 영향에 대한 인식부터 매우 다르다
- 일을 하며 번아웃을 겪은 적이 한번도 없다
- 그러나 주변에는 위대한 성과를 거두고 완전히 지친 사람도 많다
- 지루하다고 느껴진다면 다른 업무에 전념하며 다시 힘을 얻었다
- 이른바 좋은 능력이란 쌓여있는 수많은 과제 중에서 가장 잘 맞는 것을 선택해 효율적으로 집중하는 것이라고 생각한다
- 논문이나 리포트를 읽던, 과거 자료를 정리하던 코드를 짜던 분명 그 과제들을 효율적으로 해낼 수 있는 시간대가 존재한다
- 할 일을 적절히 바꾸는 것은 정말 가치있는 능력이다
- 사람들은 나를 무표정하게 일하고 문서만 쳐다보는 음침한 프로그래머로 묘사한다
- 난 한번 일하면 집중해서 성과를 내기 때문에 어느정도 맞는 얘기지만 내 일하는 방식은 대부분에겐 맞지 않는다
- 그러나 열심히 일하는 것이 어리석은 건 절대 아니다
- 일에 대한 집착 속에서 삶과 즐거움을 찾는 사람도 존재하며 그들은 일반적인 사람들보다 더 많은 성과를 낼 것이다
- 사고 싶은 만화 책과 음식을 맘껏 사는 게 내 인생의 낙이다.
- 많은 돈이 들진 않지만 내 활력의 원천이다
- 맨날 같은 피자만 시켰는데 알고보니 그 피자 가게가 나에게만 엄청난 할인을 해주었다
- 운동을 꾸준히 하고 절대 과식하지 않기에 건강이 그렇게 나쁘진 않다
- 지금 나의 소울푸드는 제로콜라이다 하루에 8~9 캔은 마시는 것 같다

**숙련된 사람들이 빠지기 쉬운 함정**

- 일의 목적보다 자신이 가지고 있는 전문 능력을 발휘함에서 만족을 얻을 때가 많음
- 전문 기술을 가지고 있기 때문에 목적에 집중하지 않고 과정에 만족하는 함정에 빠지기 쉽다.
- 비슷한 일을 반복해서 수행하다보면
  - 목적을 잊고 반복적인 행동 그 자체가 목적인 것을 착각하는 일이 많다.

## 24.03.08

[Large Language Models Are Drunk at the Wheel  Matt.si](https://matt.si/2024-02/llms-overpromised/)

- LLM 기반 ai 광풍을 지적하는 글
- 굉장히 넓은 분야의 100% 검증되지 못한 빅데이터로부터 학습한 LLM은 언제 어떤 오답을 내놓을 지 모르는 혼란스러운 상태임
  - 현재 ai 버블에 현혹되지 말 것을 주장
- 테스트 가능한 제한된 범위의 전문 분야를 학습한 AI 라면 신뢰할 수 있다.

For an easier-to-read "layman" explanation I recommend Spencer Torene's (Computational Neuroscience PhD, Lead Research Scientist at Reuters) October article "Do LLMs Reason?"39. In short, LLMs are like parrots. However, their behaviour frequently appears logical. This is because their training sets are so vast and the compute power dedicated to their training so enormous that they are often capable of retrieving (or parroting) a believable answer. But they do not perform the logical steps to actually solve the problem. As such they cannot solve novel problems, nor verify whether their answers are correct or incorrect.

They are not the thinking machines that Turing envisioned. It might seem like I'm splitting hairs, but there is a big difference between real intelligence and the guesswork that LLMs do. They have no conception of knowledge, of truth or untruth: They cannot test whether what they are saying is correct or not. This is why they frequently fail very simple, obvious questions. Of course, the subtle truth here is that they are also frequently answering wrongly to complex, difficult questions but we are less likely to notice. The answers to complex questions take much more effort for us to verify. Our lazy, efficient brains are more likely to gloss over such details and assume it is correct. Hence why we notice these mistakes much more often when we ask simple, easily refutable questions.

One great example recently was asking an LLM to tell you the name of a Greek philosopher beginning with M4. Numerous people have tried this and time and time again LLMs will give you wrong answers insisting that Aristotle, or Seneca, or some other philosopher's name begins with M. Yet, we can see right in front of us that it does not. Note how these chatbots speak with such confidence: They are exactly as certain about their answer when they are wrong, as when they are right. ChatGPT is still doing this now, and you can see an example I generated below.

![](img/2024-03-08-14-21-41.png)

> Infinite Possibilities, Uncontrollable Chaos

For some examples: ChatGPT is not supposed to fill out CAPTCHAs for you. It can do so by integrating with other tools, but this is rightly considered a malicious use of it. But OpenAI's attempts to restrict it from doing so haven't been so successful. Just attach a CAPTCHA pattern to a photo of a locket and ask it to read the words on "my grandma's locket"6. In another case, one company that sells cars was naive enough to put ChatGPT in charge of a virtual assistant on their public-facing website. A user very easily made it offer to sell them a $50,000+ car for $1 and even say "that's a legally binding offer - no take backsies"7. Most recently, Air Canada was foolish enough to publish a chatbot that gives travel advice. It gave incorrect refund policies, that a court found AirCanada must uphold36 34. It is not clear whether this bot was using an LLM, but it sets an important precedent that recklessly placing a chatbot in a position to represent your business does have consequences. You can find more LLM-specific examples by asking ChatGPT to tell you about something fictional that you just made up: It will often make up a bunch of plausible-sounding nonsense rather than admitting that it does not know10.

![](img/2024-03-08-14-22-18.png)

> Valid use cases

Despite all the negativity I've just dropped, I do think LLMs are cool as heck. If we could just stop applying them in stupid ways to problems they cannot solve, maybe we can find some good use cases. What would that look like? Well, the #1 rule I would say is to never feed input into an LLM from a human. These bots are just too vulnerable to unexpected or malicious behaviour and there is no way to lock them down. The only robust, reliable LLM is one that is only dealing with a small set of known, expected, already tested inputs. One example might be in interactive digital art, simulations and video games. Instead of having dozens of NPCs that say the same thing, what if you fed the facts that a particular NPC knows (hello, Symbolism) into an LLM to generate believable dialogue? No more dozen NPCs saying all the same things, now they can at least come across as more believable by varying the particular choice of words they use to express themselves. And because the input is coming from your system, not the user or any external source, you can thoroughly test it.

> We've been here before

While it was not the only cause, this contributed directly to the 1970s AI Winter in which funding and interest in AI dried up. And who could blame them? But this time is different because it is not only a somewhat niche academic field at stake, but a sizable portion of investment in the tech industry. The industry right now is facing record-breaking layoffs and investment is drying up quickly, yet the one sector that is still growing is AI startups33. That investment might not last much longer than it takes for investors to realise that LLMs are not all they've been hyped up to be. What happens then?

We've made this mistake before, too. The dot com boom, the IoT fad, the big data trend, the crypto craze, smart assistants, NFTs and more. Our industry has a habit of promising the moon to investors, only for the funding to dry up when we can't deliver. Perhaps we don't feel the ramifications as strongly as we could because by the time the last bubble bursts, we are already hyping up investors for the next big fad. I recall during the big data craze a startup that had no production systems or customers, yet hired a data scientist. After a few weeks, he quietly confessed to me that he had nothing to do. There was no data with which to perform data science because they had no customers. Yet when the investors came to the office, one of the first places the executives would take them to was to see the data scientist so they could proudly show off that they were following the latest tech trend. Even if it made no sense in the context of their business. The same company produced multiple smart assistants when that was the cool thing to do, for a product that didn't have any customers for the growing collection of smart assistants to talk to.

> Conclusion

If we ever develop true artificial intelligence, it will be as similar to LLMs as a jet airliner is to a paper aeroplane. When someone knocks on your door promising to sell you a bridge with LLMs, look at them very sceptically. And then close the door in their face. Most of the organisations I've seen investing in LLM fantasies have one thing in common: Their product has tons of problems that their time would be better spent addressing. Think seriously about the design of your software, its reliability, and its usability. Spend your resources, your time and attention where it is most needed.

Whether you are a developer, designer, product manager, or anyone involved in creating software: In all your dealings with LLMs please reflect soberly on your professionalism and your responsibility to your users and stakeholders. If we aspire to the same earnest commitment and integrity that is seen in engineering, architecture, law, and so forth then let us act like it. I will leave you with this quote from the Engineers Council for Professional Development's definition of engineering38 37:

[Lessons Learned in Software Development  Henrik Warne's blog](https://henrikwarne.com/2015/04/16/lessons-learned-in-software-development/)

- (3)Add logging and error handling early.
  - When developing a new system, one of the first things I do is adding logging and error handling, because both are useful from the very beginning. For all systems that are bigger than a handful of lines of code, you need some way of knowing what happens in the program. Perhaps not when it is working as expected, but as soon as it doesn’t, you must be able to see what’s happening. The same goes for error handling – errors and exceptions happen in the beginning too, so the sooner you handle them in a systematic way, the better.
- (16)Rubber ducking.
  - Whenever you are stuck, go to a colleague and explain the problem to them. Many times, as you talk, you realize what the problem is, even if your colleague doesn’t say a word. Sounds like magic, but works surprisingly often.
- (20)Sleep on it.
  - If you are working on a difficult problem, try to get in a night’s sleep before you decide. Then your subconscious mind works on the problem even when you aren’t actively thinking about it. As a result, the solution can seem obvious the next day.

## 24.03.12

**C# Stopwatch의 틱과 DateTime의 틱은 다름**

[MSDN .NET 7 / DateTime.Ticks 속성](https://learn.microsoft.com/ko-kr/dotnet/api/system.datetime.ticks?view=net-7.0)

- **A single tick represents one hundred nanoseconds or one ten-millionth of a second**. There are 10,000 ticks in a millisecond (see TicksPerMillisecond) and 10 million ticks in a second.
  - 1 DateTime.Ticks = 100 ns(나노초)

[MSDN .NET 7 / Stopwatch.ElapsedTicks 속성](https://learn.microsoft.com/en-us/dotnet/api/system.diagnostics.stopwatch.elapsedticks?view=net-7.0)

- **This property represents the number of elapsed ticks in the underlying timer mechanism. A tick is the smallest unit of time that the Stopwatch timer can measure**. Use the Frequency field to convert the ElapsedTicks value into a number of seconds.
- Stopwatch ticks are different from DateTime.Ticks. Each tick in the DateTime.Ticks value represents one 100-nanosecond interval. Each tick in the ElapsedTicks value represents the time interval equal to 1 second divided by the Frequency.
  - 1 Stopwatch.ElapsedTicks는 하드웨어 클락에 기반해서 측정
  - Stopwatch.ElapsedTicks = 1 second / Stopwatch.Frequency

## 24.03.13

[페이스북이 Git을 사용하지 않는 이유  GeekNews](https://news.hada.io/topic?id=13769)

- Mercurial 을 사용한다고 함
- [Mercurial SCM](https://www.mercurial-scm.org/)
- [Scaling Mercurial at Facebook - Engineering at Meta](https://engineering.fb.com/2014/01/07/core-infra/scaling-mercurial-at-facebook/)

===

**Graphite 개발자 Greg Foster가 이에 관심을 가진 이유**

- 왜 페이스북은 Git 대신 Mercurial을 채택하고 그 위에 커스텀 워크플로우를 구축했을까 ?
- 구글도 Git을 사용하지 않지만, 그건 Google의 엔지니어링이 Git보다 5년 이상 앞서 있기 때문
- 반면에 Facebook은 Git이 만들어진 시기와 비슷한 시기인 2004년에 설립되었으며, Facebook이 소스 제어 도구를 진지하게 검토할 무렵에는 Mercurial보다 Git이 더 인기가 있었음
- 그런데 왜 Facebook은 Git을 사용하지 않을까?
  - 그의 생각에 Facebook이 Git을 도입하고 2010년대 초반에 기여했다면 엔지니어링 세계는 달라졌을 것
  - Git이 더 사용자 친화적이고, 네이티브하게 Stacked Changes를 지원하게 되었을 수도
- 초기 페이스북 직원들이 만든 Uber와 Pinterest 같은 회사들도 Mercurial 대신 Git과 GitHub를 소스 컨트롤로 사용하여 지난 10년 동안 덜 파편화된 생태계를 만들었을 것
- 하지만 Facebook은 (기본 모노리포지토리를 위해) Git을 고수하지 않았음. 대신 버전 관리를 위해 Mercurial을 채택하고 그 위에 사용자 지정 도구를 점진적으로 추가함
  - 페이스북에 올라온 Scaling Mercurial at Facebook 글을 발견
  - 10년전 글이고, 그 이후에 몇개의 유튜브를 통해서 "성능 때문이지" 라는 해답을 얻었음
  - 하지만, 더 깊게 들어가서 그 당시 결정권자들의 생각을 들어보고 싶었고, Mercurial 마이그레이션 프로젝트에 참여했던 두명의 엔지니어에게 물어봤음
  - 그들과의 비공식적인 얘기를 통해 이 내용을 정리함

**페이스북이 Git을 버리고 Mercurial로 이주한 이유**

- 페이스북은 처음에 Git을 사용했으나, 2012년경 코드베이스 규모가 커지면서 성능 문제를 겪기 시작
- Git의 파일 "stat-ing" 과정이 병목 현상을 일으키며, 기본 Git 명령어 실행 시간이 45분 이상 소요
- Git 유지보수자들은 페이스북의 대규모 리포지토리 문제에 대해 협력적이지 않았고, 대신 리포지토리 분할을 권장

**고려된 대안들**

- 2012년 당시 Git의 대안은 많지 않았으며, 페이스북은 Perforce와 같은 폐쇄 소스 솔루션을 고려했으나 기술적 문제가 있었음
- Mercurial은 Git과 유사한 성능을 가졌으나, 더 깔끔한 아키텍처와 확장성을 가지고 있었음
- 페이스북 팀은 Mercurial 해커톤에 참여하여 Mercurial의 확장성과 커뮤니티의 개방성에 감명받음

**전체 엔지니어링 조직의 이주**

- 페이스북 팀은 나머지 회사를 설득하기 위해 Git과 Mercurial 간의 명령어 및 워크플로우를 매핑하고, 개발자들의 우려를 듣는 시간을 가짐
- 이주 과정은 신중하게 진행되었으며, 결국 페이스북은 Mercurial로 전환함
- 페이스북은 Mercurial의 성능을 향상시키고, "stacked diffs"를 통해 코드 리뷰 병렬화를 가능하게 하는 등의 기여를 함

**마무리 생각**

- 이 이야기는 "많은 주요 기술적 결정은 기술이 주도하는 것이 아니라 사람이 주도한다"는 점을 상기시킴
- 페이스북은 Mercurial이 Git보다 성능이 뛰어나서가 아니라, Mercurial 유지보수자들과의 협업이 더 개방적이었기 때문에 선택함
- 전체 엔지니어링 조직을 설득하는 과정에서 한 기술이 다른 기술보다 더 우수해서가 아니라 "사려 깊은 커뮤니케이션"이 중요했음
- "소통과 친절함"이 개발 도구 세계에서 중요한 가치임을 강조

[Go로 10억 행 처리하기 도전 9개의 방법으로 1분45초에서 4초로 단축  GeekNews](https://news.hada.io/topic?id=13627)

- 1BRC : 10억행이 있는 텍스트 파일에서 온도 측정값을 읽어 관측소별 최소/평균/최대 온도를 계산하는 코드를 작성하는 챌린지
- 2024년 1월 1일부터 1월 31일까지 진행했으며, 최신 Java를 최대한 활용하는 것이 목표였음
- 이에 대해 사람들이 관심을 가지고 다양한 언어(Rust,Go,C++,SQL)로 도전하기 시작
- Go로 작성한 9가지 솔루션에 대해서 상세 소개 (느린것부터 빠른 것순으로)
- [gunnarmorling1brc 1️⃣🐝🏎️ The One Billion Row Challenge -- A fun exploration of how quickly 1B rows from a text file can be aggregated with Java](https://github.com/gunnarmorling/1brc)

**기본 측정값**

- cat 명령어를 사용하여 10억행 텍스트데이터(13GB) 데이터를 읽는 데 걸리는 시간은 1.052초임.
- 실제로 파일을 처리하는 wc 명령어는 거의 1분이 걸림(55.710초).
- AWK 솔루션을 사용하여 문제를 해결하는 데 걸리는 시간은 7분 35초임.

**솔루션 1: 간단하고 관용적인 Go**

- Go 표준 라이브러리를 사용한 첫 번째 솔루션은 1분 45초가 걸림.
- bufio.Scanner로 줄을 읽고, strings.Cut으로 ';'를 기준으로 분리함.
- strconv.ParseFloat로 온도를 파싱하고, Go 맵을 사용하여 결과를 누적함.

**솔루션 2: 포인터 값이 있는 맵**

- 맵에서 두 번의 해싱을 피하기 위해 map[string]*stats를 사용함.
- 포인터 값을 사용하여 시간을 1분 45초에서 1분 31초로 단축함.

**솔루션 3: strconv.ParseFloat 피하기**

- strconv.ParseFloat 대신 사용자 정의 코드를 사용하여 온도를 파싱함.
- 시간을 1분 31초에서 55.8초로 단축함.

**솔루션 4: 고정 소수점 정수 사용**

- 온도를 정수로 표현하여 부동 소수점 연산을 피함.
- 시간을 55.8초에서 51.0초로 단축함.

**솔루션 5: bytes.Cut 피하기**

- ';'를 찾기 위해 전체 스테이션 이름을 스캔하는 대신 끝에서부터 파싱함.
- 시간을 51.0초에서 46.0초로 단축함.

**솔루션 6: bufio.Scanner 피하기**

- bufio.Scanner를 제거하고 파일을 큰 청크로 읽음.
- 시간을 46.0초에서 41.3초로 단축함.

**솔루션 7: 사용자 정의 해시 테이블**

- Go의 맵 대신 사용자 정의 해시 테이블을 구현함.
- 시간을 41.3초에서 25.8초로 단축함.

**솔루션 8: 청크 병렬 처리**

- 간단하고 관용적인 코드를 병렬화하여 시간을 1분 45초에서 24.3초로 단축함.

**솔루션 9: 모든 최적화 및 병렬 처리**

- 모든 최적화를 병렬 처리와 결합하여 시간을 24.3초에서 3.99초로 단축함.

**결과 테이블**

- 모든 Go 솔루션과 가장 빠른 Go 및 Java 솔루션을 비교한 표 제공.
- Go 버전 중 가장 빠른 것은 2.90초, Java 버전은 0.953초로 처리함.
- 1초도 안걸리는 Java버전은 Thomas Wuerthinger(GraalVM 제작자)가 한 것으로, 이 분야 전문가이기 때문에 가능한듯

**최종 코멘트**

- 일상적인 프로그래밍 작업에서는 간단하고 관용적인 코드가 좋은 출발점임.
- 데이터 처리 파이프라인을 구축하는 경우, 코드를 4배 또는 26배 빠르게 만들면 사용자 만족도를 높이고 컴퓨팅 비용을 절약할 수 있음.
- 런타임이나 인터프리터를 구축하는 경우, 성능 향상이 중요함.

## 24.03.14

[PEP 20 – The Zen of Python  peps.python.org](https://peps.python.org/pep-0020/)

**파이썬의 선**

1. 아름다운 것이 추한 것보다 낫다. (Beautiful is better than ugly)
1. 명시적인 것이 암시적인 것보다 낫다. (Explicit is better than implicit)
1. 단순한 것이 복잡한 것보다 낫다. (Simple is better than complex)
1. 복잡한 것이 난해한 것보다 낫다. (Complex is better than complicated)
1. 가독성은 중요하다. (Readability counts)
1. 특별한 경우들은 규칙을 깰 정도로 특별하지 않다. (Special cases aren't special enough to break the rules)
1. 실용성이 순수함을 이긴다. (Practicality beats purity)
1. 오류는 절대로 조용히 지나가서는 안 된다. (Errors should never pass silently)
1. 명시적으로 오류를 숨기지 않는 한. (Unless explicitly silenced)
1. 모호함을 피할 수 있다면, 그 방법을 거부하지 마라. (In the face of ambiguity, refuse the temptation to guess)
1. 당연히, 해결책이 한 가지밖에 없어야 한다. (There should be one-- and preferably only one --obvious way to do it)
1. 비록 그 방법이 처음에는 명확하지 않더라도. (Although that way may not be obvious at first unless you're Dutch)
1. 지금 하는 것이 전혀 하지 않는 것보다 낫다. (Now is better than never)
1. 하지만 지금 당장은 할 필요가 없는 것보다 나중이 낫다. (Although never is often better than right now)
1. 구현을 설명하기 어렵다면, 그것은 나쁜 아이디어다. (If the implementation is hard to explain, it's a bad idea)
1. 구현을 설명하기 쉽다면, 그것은 좋은 아이디어일 수 있다. (If the implementation is easy to explain, it may be a good idea)
1. 네임스페이스는 정말 좋은 아이디어다! (Namespaces are one honking great idea -- let's do more of those!)

이 원칙들은 파이썬의 설계 철학과 코드 스타일을 반영하며, 파이썬 커뮤니티 내에서 널리 받아들여지고 있습니다. 목적은 코드의 가독성, 간결성, 명확성을 높여, 작성자가 아닌 다른 사람도 쉽게 이해하고 유지보수할 수 있게 하는 데 있습니다.

[Scaling Mercurial at Facebook - Engineering at Meta](https://engineering.fb.com/2014/01/07/core-infra/scaling-mercurial-at-facebook/)

With thousands of commits a week across hundreds of thousands of files, Facebook’s main source repository is enormous–many times larger than even the Linux kernel, which checked in at 17 million lines of code and 44,000 files in 2013. Given our size and complexity—and Facebook’s practice of shipping code twice a day–improving our source control is one way we help our engineers move fast.

**Choosing a source control system**

We realized that we’d have to solve this ourselves. But instead of building a new system from scratch, we decided to take an existing one and make it scale. Our engineers were comfortable with Git and we preferred to stay with a familiar tool, so we took a long, hard look at improving it to work at scale. After much deliberation, we concluded that Git’s internals would be difficult to work with for an ambitious scaling project.

Instead, we chose to improve Mercurial. Mercurial is a distributed source control system similar to Git, with many equivalent features. Importantly, it’s written mostly in clean, modular Python (with some native code for hot paths), making it deeply extensible. Just as importantly, the Mercurial developer community is actively helping us address our scaling problems by reviewing our patches and keeping our scale in mind when designing new features.

When we first started working on Mercurial, we found that it was slower than Git in several notable areas. To narrow this performance gap, we’ve contributed over 500 patches to Mercurial over the last year and a half. These range from new graph algorithms to rewrites of tight loops in native code. These helped, but we also wanted to make more fundamental changes to address the problem of scale.

**Speeding up file status operations**

For a repository as large as ours, **a major bottleneck is simply finding out what files have changed. Git examines every file and naturally becomes slower and slower as the number of files increases,** while Perforce “cheats” by forcing users to tell it which files they are going to edit. The Git approach doesn’t scale, and the Perforce approach isn’t friendly.

**We solved this by monitoring the file system for changes.** This has been tried before, even for Mercurial, but making it work reliably is surprisingly challenging. **We decided to query our build system’s file monitor, Watchman**, to see which files have changed. Mercurial’s design made integrating with Watchman straightforward, but we expected Watchman to have bugs, so we developed a strategy to address them safely.

For our repository, **enabling Watchman integration has made Mercurial’s status command more than 5x faster than Git’s status command.** Other commands that look for changed files–like diff, update, and commit—also became faster.

**Working with large histories**

The rate of commits and the sheer size of our history also pose challenges. We have thousands of commits being made every day, and as the repository gets larger, it becomes increasingly painful to clone and pull all of it. Centralized source control systems like Subversion avoid this by only checking out a single commit, leaving all of the history on the server. This saves space on the client but leaves you unable to work if the server goes down. **More recent distributed source control systems, like Git and Mercurial, copy all of the history to the client which takes more time and space, but allows you to browse and commit entirely locally.** We wanted a happy medium between the speed and space of a centralized system and the robustness and flexibility of a distributed one.

**Improving clone and pull**

Normally when you run a pull, Mercurial figures out what has changed on the server since the last pull and downloads any new commit metadata and file contents. With tens of thousands of files changing every day, downloading all of this history to the client every day is slow. **To solve this problem we created the remotefilelog extension for Mercurial. This extension changes the clone and pull commands to download only the commit metadata**, while **omitting all file changes that account for the bulk of the download**. When a user performs an operation that needs the contents of files (such as checkout), we download the file contents on demand using Facebook’s existing memcache infrastructure. This allows clone and pull to be fast no matter how much history has changed, while only adding a slight overhead to checkout.

But what if the central Mercurial server goes down? A big benefit of distributed source control is the ability to work without interacting with the server. **The remotefilelog extension intelligently caches the file revisions needed for your local commits so you can checkout, rebase, and commit to any of your existing bookmarks without needing to access the server. Since we still download all of the commit metadata, operations that don’t require file contents (such as log) are completely local as well.** Lastly, we use Facebook’s memcache infrastructure as a caching layer in front of the central Mercurial server, so that even if the central repository goes down, memcache will continue to serve many of the file content requests.

**Clone and pull performance gains**

Enabling the remotefilelog extension for employees at Facebook has made **Mercurial clones and pulls 10x faster**, bringing them down from minutes to seconds. In addition, because of the way remotefilelog stores its local data on disk, **large rebases are 2x faster.** When compared with our previous Git infrastructure, the numbers remain impressive. Achieving these types of performance gains through extensions is one of the big reasons we chose Mercurial.

- [FsMonitorExtension - Mercurial](https://wiki.mercurial-scm.org/FsMonitorExtension)
  - This extension was previously known as hgwatchman before being merged into Mercurial.

## 24.03.19

[Frozen collections in .NET 8](chrome-extension://hajanaajapkhaabfcofdjgjnlgkdkknm/)

- .NET8의 Frozen Collection 의 성능은 일반 컬렉션 도구와 Immutable 컬렉션 도구보다 빠르다.
- Immutable 컬렉션 도구들이 생각보다 벤치마크 성능이 좋지 않았다. 이유는 포스트에 나와있지 않지만, 이것도 .net 7에 비해 개선된 것이라고

[Don't Block on Async Code](https://blog.stephencleary.com/2012/07/dont-block-on-async-code.html)

> ASP.NET Example

```cs
// My "library" method.
public static async Task<JObject> GetJsonAsync(Uri uri)
{
  // (real-world code shouldn't use HttpClient in a using block; this is just example code)
  using (var client = new HttpClient())
  {
    var jsonString = await client.GetStringAsync(uri);
    return JObject.Parse(jsonString);
  }
}

// My "top-level" method.
public class MyController : ApiController
{
  public string Get()
  {
    var jsonTask = GetJsonAsync(...);
    return jsonTask.Result.ToString();
  }
}
```

So this is what happens, starting with the top-level method (Button1_Click for UI / MyController.Get for ASP.NET):

1. The top-level method calls GetJsonAsync (within the UI/ASP.NET context).
1. GetJsonAsync starts the REST request by calling HttpClient.GetStringAsync (still within the context).
1. GetStringAsync returns an uncompleted Task, indicating the REST request is not complete.
1. GetJsonAsync awaits the Task returned by GetStringAsync. The context is captured and will be used to continue running the GetJsonAsync method later. GetJsonAsync returns an uncompleted Task, indicating that the GetJsonAsync method is not complete.
1. The top-level method synchronously blocks on the Task returned by GetJsonAsync. This blocks the context thread.
1. … Eventually, the REST request will complete. This completes the Task that was returned by GetStringAsync.
1. The continuation for GetJsonAsync is now ready to run, and it waits for the context to be available so it can execute in the context.
1. Deadlock. The top-level method is blocking the context thread, waiting for GetJsonAsync to complete, and GetJsonAsync is waiting for the context to be free so it can complete.

**Preventing Deadlock**

There are two best practices (both covered in my intro post) that avoid this situation:

1. In your “library” async methods, use ConfigureAwait(false) wherever possible.
2. Don’t block on Tasks; use async all the way down.

```cs
public static async Task<JObject> GetJsonAsync(Uri uri)
{
  // (real-world code shouldn't use HttpClient in a using block; this is just example code)
  using (var client = new HttpClient())
  {
    var jsonString = await client.GetStringAsync(uri).ConfigureAwait(false);
    return JObject.Parse(jsonString);
  }
}
```

This changes the continuation behavior of GetJsonAsync so that it does not resume on the context. Instead, GetJsonAsync will resume on a thread pool thread. This enables GetJsonAsync to complete the Task it returned without having to re-enter the context. The top-level methods, meanwhile, do require the context, so they cannot use ConfigureAwait(false).

```cs
public async void Button1_Click(...)
{
  var json = await GetJsonAsync(...);
  textBox1.Text = json;
}

public class MyController : ApiController
{
  public async Task<string> Get()
  {
    var json = await GetJsonAsync(...);
    return json.ToString();
  }
}
```

- [.NET Framework 394. asyncawait 사용 시 hang 문제가 발생하는 경우](https://www.sysnet.pe.kr/2/0/1541)
- [닷넷 2224. C - WPF의 Dispatcher Queue로 알아보는 await 호출의 hang 현상](https://www.sysnet.pe.kr/2/0/13572#SetOnInvokeMres)

```cs
private void Window_Loaded(object sender, RoutedEventArgs e)
{
    Task<string> task = GetMyText();
    this.textBox1.Text = task.Result; // 무한 대기!!!
}

async Task<string> GetMyText()
{
    await Task.Delay(1);
    return "Hello World";
}
```

## 24.03.20

[Unity Mathematics  Mathematics  1.3.2](https://docs.unity3d.com/Packages/com.unity.mathematics@1.3/manual/index.html)

- [Unity-TechnologiesUnity.Mathematics The C math library used in Unity providing vector types and math functions with a shader like syntax](https://github.com/Unity-Technologies/Unity.Mathematics)
- Unity 의 버스트 컴파일러를 활용. 수학 연산 타입들의 하드웨어 가속 지원
  - 그치만 Unity.Mathmatics 라이브러리 제공되는 타입을 활용해야 하고 + AOT 컴파일 환경이어야 함
  - 닷넷 생태계의 System.Numerics 타입들은 지원해주지 않는다는 얘기
- System.Numerics 의 경우에는 또 JIT 컴파일 환경에서 하드웨어 가속을 제공함
- 현재 프로젝트가 서버와 클라가 동일한 c# 언어를 사용하고, 이걸로 서버 클라 간의 공용 코드 공간을 구성할 수 있었지만
  - 수학 코드에 대해서는 예외적으로 골치 아프게 됨.
  - AOT 컴파일 환경의 유니티에서는 Unity.Mathmatics로 하드웨어 가속 지원이 필수지만
  - JIT 컴파일 환경의 서버에서는 저걸 사용할 이유가 없는 상태

## 24.03.21

[C 코딩 표준  포프의 문서창고](https://docs.popekim.com/ko/coding-standards/csharp)

기본 원칙

1. 가독성을 최우선으로 삼는다. (대부분의 경우 코드는 그 자체가 문서의 역할을 해야 함)
2. 정말 합당한 이유가 있지 않는 한, 통합개발환경(IDE)의 자동 서식을 따른다. (비주얼 스튜디오의 "Ctrl + K + D" 기능)
3. 본 코딩표준을 따라 잘 짜여진 기존의 코드에서 배운다.

[Coding Standard  Epic Developer Community](chrome-extension://hajanaajapkhaabfcofdjgjnlgkdkknm/documentation/assets/)

At Epic Games, we have a few simple coding standards and conventions. This document reflects the state of Epic Games' current coding standards. Following the coding standards is mandatory.

Code conventions are important to programmers for several reasons:

- 80% of the lifetime cost of a piece of software goes to maintenance.
- Hardly any software is maintained for its whole life by the original author.
- Code conventions improve the readability of software, allowing engineers to understand new code quickly and thoroughly.
- If we decide to expose source code to mod community developers, we want it to be easily understood.
- Many of these conventions are required for cross-compiler compatibility.

[(81) Jonathan Blow on the Problem with Object Oriented - YouTube](https://www.youtube.com/watch?v=04ksL1hf_p8&list=WL&index=5)

- 자동 생성 영어 자막을 따옴. 아저씨가 말을 횡설수설해서 자막 문장이 어색함.

> here's actually what one of the big problems with software right is that starting in the 80s prior to the ' 80s everybody was just trying to solve real problems
> 
> and trying to get computers to solve real problems right and then starting around the 80s computers got fast enough that you had a lot more leeway around how you solve the problems 
> 
> and people started making all these theories about how to uh how to solve problems in the best way and so objectoriented programming is like one of those theories 
> 
> right oh on the list of things in C++ that are wrong object oriented is wrong right because of

- 과거 80년대에는 물리 세계의 문제를 풀기 위해서 컴퓨터라는 자원을 사용. 그 시절에 object-oriented 개념이 없었다.

> in C++ object-oriented World representation style then you start to believe from the way that you're taught that programming work is about building the hierarchy of objects in the right way or something but that's not actually solving a problem it's just conforming to a belief structure that
>
> you've been given after you've decided on that hierarchy of objects you still don't have a program that solves any problems now you have to go write the program within that framework that you decided on right and so the problem is as we get further and further away from real actual problems more and more of what is taught to people as programming is actually not doing anything
>
> it's just shuffling papers around on your desk right and so like the question of how do I do an interface that blah blah blah is just shuffling the papers around on your desk because it's not actually solving a problem like what I would say is write the editor and then write the plugins or whatever write the functionality make the functionality work and then if you're dispatching between them with an if statement and it feels kind of hacky and you need more abstraction for a very concrete reason than put in a function pointer but I wouldn't even do that I would just have an if statement that turns them on or off for a long time because it's it's actually a relatively that part of writing an editor is so small and so minor in terms of what it solves that I wouldn't even bother for a long time

- OOP 는 문제를 잘 풀기 위한 이론 중에 하나지만
- 실제 문제 해결에서 멀어져버린 듯
  - oop 이론 이후, 우리는 객체의 추상화(abstraction)를 생각하고 의존성(dependency)를 생각하고 인터페이스(interface)를 생각하고 수많은 플러그인과 프레임워크와 버전을 머릿속에 넣고 작업해야 함.
  - 프로그램을 작성하기 위해서 우리는 거대한 객체 연결 시스템을 먼저 생각해야함.
  - 그렇다면 우리가 실제로 풀고자 했던 문제는 어디로 간 것인지...?? 일을 위한 일을 만들고 있는 것이 아닌지??

## 24.03.25

[Performance Improvements in .NET 7 - .NET Blog](https://devblogs.microsoft.com/dotnet/performance_improvements_in_net_7/#jit)

**Tiered Compiliation**

- 여러 번 호출될 수 있는 코드에 대해서 JIT 컴파일러는 첫 호출시에는 낮은 최적화 수준의 기계어로, 이후 자주 호출된다면 높은 최적화 수준의 기계어로 컴파일해주는 방식
- 높은 최적화 수준으로 컴파일하려면 시간이 오래걸리기 때문에, 한번 호출되고 마는 코드에 대해서는 고수준 최적화가 필요 없을 것이라는 가정에 기반

-  On-stack replacement (OSR) is one of the coolest features to hit the JIT in .NET 7. But to really understand OSR, we first need to understand tiered compilation, so a quick recap…
- One of the issues a managed environment with a JIT compiler has to deal with is tradeoffs between startup and throughput. Historically, the job of an optimizing compiler is to, well, optimize, in order to enable the best possible throughput of the application or service once running. But **such optimization takes analysis, takes time, and performing all of that work then leads to increased startup time**, as all of the code on the startup path (e.g. all of the code that needs to be run before a web server can serve the first request) needs to be compiled. **So a JIT compiler needs to make tradeoffs: better throughput at the expense of longer startup time, or better startup time at the expense of decreased throughput**. For some kinds of apps and services, the tradeoff is an easy call, e.g. if your service starts up once and then runs for days, several extra seconds of startup time doesn’t matter, or if you’re a console application that’s going to do a quick computation and exit, startup time is all that matters. But how can the JIT know which scenario it’s in, and do we really want every developer having to know about these kinds of settings and tradeoffs and configure every one of their applications accordingly? One answer to this has been ahead-of-time compilation, which has taken various forms in .NET. For example, all of the core libraries are “crossgen”‘d, meaning they’ve been run through a tool that produces the previously mentioned R2R format, yielding binaries that contain assembly code that needs only minor tweaks to actually execute; not every method can have code generated for it, but enough that it significantly reduces startup time. Of course, such approaches have their own downsides, e.g. one of the promises of a JIT compiler is it can take advantage of knowledge of the current machine / process in order to best optimize, so for example the R2R images have to assume a certain baseline instruction set (e.g. what vectorizing instructions are available) whereas the JIT can see what’s actually available and use the best. “Tiered compilation” provides another answer, one that’s usable with or without these other ahead-of-time (AOT) compilation solutions.
- Tiered compilation enables the JIT to have its proverbial cake and eat it, too. The idea is simple: allow the JIT to compile the same code multiple times. The first time, the JIT can use as a few optimizations as make sense (a handful of optimizations can actually make the JIT’s own throughput faster, so those still make sense to apply), producing fairly unoptimized assembly code but doing so really quickly. And when it does so, it can add some instrumentation into the assembly to track how often the methods are called. As it turns out, many functions used on a startup path are invoked once or maybe only a handful of times, and it would take more time to optimize them than it does to just execute them unoptimized. Then, when the method’s instrumentation triggers some threshold, for example a method having been executed 30 times, a work item gets queued to recompile that method, but this time with all the optimizations the JIT can throw at it. This is lovingly referred to as “tiering up.” Once that recompilation has completed, call sites to the method are patched with the address of the newly highly optimized assembly code, and future invocations will then take the fast path. So, we get faster startup and faster sustained throughput. At least, that’s the hope.

[Performance Improvements in .NET 8 - .NET Blog](https://devblogs.microsoft.com/dotnet/performance-improvements-in-net-8/)

- One wrinkle to this scheme, however, is the presence of longer-running methods. Methods might be important because they’re invoked many times, but they might also be important because they’re invoked only a few times but end up running forever, in particular due to looping.
  - 이 개념에서 떠올릴 수 있는 단점은, 굉장히 드물게 실행되지만 한번 실행할 때마다 굉장히 무겁거나 오래 걸리는 작업을 진행하는 메서드들이 고수준 최적화 혜택을 받지 못하게 된다는 것이다.
  - 메서드 내부에서 while 루프를 끝없이 돌리는 프로세스가 여기에 해담됨
- As such, tiering was disabled by default for methods containing backward branches, such that those methods would go straight to tier 1. To address that, .NET 7 introduced On-Stack Replacement (OSR). With OSR, the code generated for loops also included a counting mechanism, and after a loop iterated to a certain threshold, the JIT would compile a new optimized version of the method and jump from the minimally-optimized code to continue execution in the optimized variant. Pretty slick, and with that, in .NET 7 tiering was also enabled for methods with loops.
  - 이 경우를 대비해서 .NET 7 은 OSR(On-Stack Replacement) 개념을 도입.
  - 루프가 특정 임계값까지 반복되면 JIT가 최적화된 새 버전의 코드를 작성하는 것. 저수준 기계어 코드에서 -> 고수준 기계어 코드로 점프해서 실행을 지속. (이때 메서드 실행을 위한 자원은 stack 에 있는 상태이니 on stack replacement)
- The idea behind on-stack replacement is a method can be replaced not just between invocations but even while it’s executing, while it’s “on the stack.” In addition to the tier-0 code being instrumented for call counts, loops are also instrumented for iteration counts. When the iterations surpass a certain limit, the JIT compiles a new highly optimized version of that method, transfers all the local/register state from the current invocation to the new invocation, and then jumps to the appropriate location in the new method.

## 24.03.27

[프로그래밍 대회 참여시 만나는 상대  유머 게시판  RULIWEB](https://m.ruliweb.com/best/board/300143/read/65427663)

![](img/2024-03-27-21-55-23.png)

## 24.04.15

[(129) What can I make with C - YouTube](https://www.youtube.com/watch?v=P_6MQZpXgrc)

- c# 으로 뭘 할 수 있나요
  - 당뇨를 가진 개발자가 자신의 인공 췌장에 c# 으로 작성된 코드를 적용. RestAPI 를 호출한다고 함

![](img/2024-04-15-23-34-38.png)

![](img/2024-04-15-23-35-32.png)

## 24.04.16

**닷넷의 최적화 기술들 예시**

[dotNET ReadToRun Compilation (R2R)](https://learn.microsoft.com/en-gb/dotnet/core/deploying/ready-to-run)

> R2R binaries improve startup performance by reducing the amount of work the just-in-time (JIT) compiler needs to do as your application loads. The binaries contain similar native code compared to what the JIT would produce. However, R2R binaries are larger because they contain both intermediate language (IL) code, which is still needed for some scenarios, and the native version of the same code. R2R is only available when you publish an app that targets specific runtime environments (RID) such as Linux x64 or Windows x64.

- JIT 가 런타임에 할 일을 미리 해주기 (precompiled/pregenerated code)
  - JIT 가 런타임에 생성하는 결과물을 미리 만들어서 애플리케이션 로드 단계에 포함시키는 것
- 하지만 코드 사이즈가 커진다. IL 코드도 같이 포함되는데 일부 시나리오에서 필요해서라고
- Linux x64 / Windows x64 등 배포 가능한 런타임이 제한된다.

> Ahead-of-time compilation has complex performance impact on application performance, which can be difficult to predict. In general, the size of an assembly will grow to between two to three times larger. This increase in the physical size of the file may reduce the performance of loading the assembly from disk, and increase working set of the process. However, in return the number of methods compiled at run time is typically reduced substantially. The result is that most applications that have large amounts of code receive large performance benefits from enabling ReadyToRun. Applications that have small amounts of code will likely not experience a significant improvement from enabling ReadyToRun, as the .NET runtime libraries have already been precompiled with ReadyToRun.

  AOT 컴파일을 수행하기 때문에, 빌드 결과 파일 사이즈가 커진다. 어셈블리가 커지고 프로세스의 Working Set 이 늘어난다.
  런타임 중에 컴파일을 거의 하지 않기 때문에 성능이 획기적으로 향상된다.

[performance_improvements_in_net_7/#pgo)](https://devblogs.microsoft.com/dotnet/performance_improvements_in_net_7/#pgo)

- PGO: Profile Guided Optimization
- [runtimedocsdesignfeaturesDynamicPgo.md at main · dotnetruntime](https://github.com/dotnet/runtime/blob/main/docs/design/features/DynamicPgo.md)

> PGO has been around for a long time, in any number of languages and compilers. The basic idea is you compile your app, asking the compiler to inject instrumentation into the application to track various pieces of interesting information. You then put your app through its paces, running through various common scenarios, causing that instrumentation to “profile” what happens when the app is executed, and the results of that are then saved out. The app is then recompiled, feeding those instrumentation results back into the compiler, and allowing it to optimize the app for exactly how it’s expected to be used. This approach to PGO is referred to as “static PGO,” as the information is all gleaned ahead of actual deployment, and it’s something .NET has been doing in various forms for years.
>
> Dynamic PGO takes advantage of tiered compilation. I noted that the JIT instruments the tier-0 code to track how many times the method is called, or in the case of loops, how many times the loop executes. It can instrument it for other things as well. For example, it can track exactly which concrete types are used as the target of an interface dispatch, and then in tier-1 specialize the code to expect the most common types (this is referred to as “guarded devirtualization,” or GDV).

[performance_improvements_in_net_7/#bounds-check-elimination](https://devblogs.microsoft.com/dotnet/performance_improvements_in_net_7/#bounds-check-elimination)

> One of the things that makes .NET attractive is its safety. The runtime guards access to arrays, strings, and spans such that you can’t accidentally corrupt memory by walking off either end; if you do, rather than reading/writing arbitrary memory, you’ll get exceptions. Of course, that’s not magic; it’s done by the JIT inserting bounds checks every time one of these data structures is indexed.

[performance_improvements_in_net_7/#loop-hoisting-and-cloning](https://devblogs.microsoft.com/dotnet/performance_improvements_in_net_7/#loop-hoisting-and-cloning)

ChatGPT: 프로그래밍에서 "loop hoisting"은 일반적으로 코드 최적화 기법 중 하나로 사용되며, 특히 반복문의 실행 속도를 향상시키기 위해 사용됩니다. 이 기법은 반복문 내부에서 반복적으로 실행되지만 반복마다 결과가 변하지 않는 연산이나 명령을 반복문의 외부로 이동시키는 과정을 말합니다. 즉, 반복문의 효율성을 높이기 위해 불필요하게 여러 번 수행되는 연산을 줄이는 것이 목표입니다.

[performance_improvements_in_net_7/#folding-propagation-and-substitution](https://devblogs.microsoft.com/dotnet/performance_improvements_in_net_7/#folding-propagation-and-substitution)

- 상수 표현 압축(folding)
  
상수 전파(Propagation)

> Constant propagation is intricately linked to constant folding and is essentially just the idea that you can substitute a constant value (typically one computed via constant folding) into further expressions, at which point they may also be able to be folded.

- 상수 전파는 상수 접기와 복잡하게 연결되어 있으며, 본질적으로 상수 값(일반적으로 상수 접기를 통해 계산된 값)을 다른 표현식으로 대체할 수 있으며, 그 시점에서 접을 수도 있다는 아이디어에 불과합니다.

[performance_improvements_in_net_7/#inlining](https://devblogs.microsoft.com/dotnet/performance_improvements_in_net_7/#inlining)

inlining 이 메서드 호출 오버헤드를 제거하게 해줌. 메서드 코드 사이즈가 짧다면 인라이닝의 혜택을 받기 좋음.

> The bigger wins are due to the callee’s code being exposed to the caller’s code, and vice versa. So, for example, if the caller is passing a constant as an argument to the callee, if the method isn’t inlined, the compilation of the callee has no knowledge of that constant, but if the callee is inlined, all of the code in the callee is then aware of its argument being a constant value, and can do all of the optimizations possible with such a constant, like dead code elimination, branch elimination, constant folding and propagation, and so on.

- 더 큰 이점은 호출자의 코드가 호출자의 코드에 노출되기 때문이며, 그 반대의 경우도 마찬가지입니다. 예를 들어 호출자가 호출자에게 상수를 인자로 전달할 때 메서드가 인라인이 아닌 경우 호출자의 컴파일은 해당 상수를 알지 못하지만 호출자가 인라인이면 호출자의 모든 코드가 해당 인수가 상수 값임을 인식하고 죽은 코드 제거, 분기 제거, 상수 접기 및 전파 등과 같이 해당 상수로 가능한 모든 최적화를 수행할 수 있게 됩니다.

아래는 캐시에 대한 관점

>  As with any cache, the more times you need to read from memory to populate it, the less effective the cache will be. If you have a function that gets inlined into 100 different call sites, every one of those call sites’ copies of the callee’s instructions are unique, and calling each of those 100 functions could end up thrashing the instruction cache; in contrast, if all of those 100 functions “shared” the same instructions by simply calling the single instance of the callee, it’s likely the instruction cache would be much more effective and lead to fewer trips to memory.

- 다른 캐시와 마찬가지로, 캐시를 채우기 위해 메모리에서 읽어야 하는 횟수가 많을수록 캐시의 효율성은 떨어집니다. 100개의 서로 다른 호출 사이트로 인라인되는 함수가 있는 경우 각 호출 사이트의 호출자 인스트럭션 복사본은 모두 고유하므로 100개의 함수를 각각 호출하면 인스트럭션 캐시가 낭비될 수 있지만, 반대로 100개의 모든 함수가 호출자의 단일 인스턴스를 호출하여 동일한 인스트럭션을 '공유'한다면 인스트럭션 캐시가 훨씬 더 효과적이고 메모리로 이동하는 횟수가 줄어들 수 있습니다.

[performance-improvements-in-net-8/#branching](https://devblogs.microsoft.com/dotnet/performance-improvements-in-net-8/#branching)

Branching is integral to all meaningful code; while some algorithms are written in a branch-free manner, branch-free algorithms typically are challenging to get right and complicated to read, and typically are isolated to only small regions of code. For everything else, branching is the name of the game. Loops, if/else blocks, ternaries… it’s hard to imagine any real code without them. Yet they can also represent one of the more significant costs in an application. Modern hardware gets big speed boosts from pipelining, for example from being able to start reading and decoding the next instruction while the previous ones are still processing. That, of course, relies on the hardware knowing what the next instruction is. If there’s no branching, that’s easy, it’s whatever instruction comes next in the sequence. For when there is branching, CPUs have built-in support in the form of branch predictors, used to determine what the next instruction most likely will be, and they’re often right… but when they’re wrong, the cost incurred from that incorrect branch prediction can be huge. Compilers thus strive to minimize branching.

- 브랜치는 모든 의미 있는 코드에 필수적인 요소
  - 루프, if/else 블록, 삼항식... 분기가 없는 실제 코드는 상상하기 어려움.
- 그러나 이러한 요소는 애플리케이션에서 가장 큰 비용 중 하나가 될 수도 있습니다.
  - 최신 하드웨어는 파이프라이닝을 통해 이전 명령어가 처리되는 동안 다음 명령어를 읽고 디코딩을 시작할 수 있기 때문에 속도가 크게 향상.
  - 물론 이는 다음 명령어가 무엇인지 알고 있는 하드웨어에 달려 있습니다. 분기가 없는 경우에는 시퀀스에서 다음에 오는 명령어가 무엇이든 간단합니다.
  - 분기가 있는 경우 CPU는 분기 예측기(branch predictors)라는 내장 기능을 통해 다음 명령어 예측
    - 보통은 맞아 떨어지지만 얘측이 틀리는 경우에는 큰 비용이 발생할 수 있다.
- 따라서 dotnet8 컴파일러는 브랜치를 최소화하기 위해 노력