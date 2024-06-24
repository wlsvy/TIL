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

- 상수 폴딩(Constant Folding): 이 최적화 기법은 실행 시간이 아닌 컴파일 시간에 상수 표현식을 평가하는 것을 포함합니다. 예를 들어, 2 + 2와 같은 표현을 컴파일 중에 4로 대체하면 프로그램 실행 시 필요한 계산이 줄어듭니다.
- 상수 전파(Constant Propagation): 이 기법은 알려진 상수의 값을 표현식에 대체하는 것을 포함합니다. 변수가 상수 값에 할당되면 이 값은 변수가 사용되는 곳마다 직접 대체됩니다. 예를 들어, x = 3이라면 y = x + 2 표현식은 컴파일 중에 y = 5로 대체됩니다.

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

> Branching is integral to all meaningful code; while some algorithms are written in a branch-free manner, branch-free algorithms typically are challenging to get right and complicated to read, and typically are isolated to only small regions of code. For everything else, branching is the name of the game. Loops, if/else blocks, ternaries… it’s hard to imagine any real code without them. Yet they can also represent one of the more significant costs in an application. Modern hardware gets big speed boosts from pipelining, for example from being able to start reading and decoding the next instruction while the previous ones are still processing. That, of course, relies on the hardware knowing what the next instruction is. If there’s no branching, that’s easy, it’s whatever instruction comes next in the sequence. For when there is branching, CPUs have built-in support in the form of branch predictors, used to determine what the next instruction most likely will be, and they’re often right… but when they’re wrong, the cost incurred from that incorrect branch prediction can be huge. Compilers thus strive to minimize branching.

- 브랜치는 모든 의미 있는 코드에 필수적인 요소
  - 루프, if/else 블록, 삼항식... 분기가 없는 실제 코드는 상상하기 어려움.
- 그러나 이러한 요소는 애플리케이션에서 가장 큰 비용 중 하나가 될 수도 있습니다.
  - 최신 하드웨어는 파이프라이닝을 통해 이전 명령어가 처리되는 동안 다음 명령어를 읽고 디코딩을 시작할 수 있기 때문에 속도가 크게 향상.
  - 물론 이는 다음 명령어가 무엇인지 알고 있는 하드웨어에 달려 있습니다. 분기가 없는 경우에는 시퀀스에서 다음에 오는 명령어가 무엇이든 간단합니다.
  - 분기가 있는 경우 CPU는 분기 예측기(branch predictors)라는 내장 기능을 통해 다음 명령어 예측
    - 보통은 맞아 떨어지지만 얘측이 틀리는 경우에는 큰 비용이 발생할 수 있다.
- 따라서 dotnet8 컴파일러는 브랜치를 최소화하기 위해 노력

[performance-improvements-in-net-8/#non-gc-heap](https://devblogs.microsoft.com/dotnet/performance-improvements-in-net-8/#non-gc-heap)

> What if we could ensure that the string object for this literal is created some place where it would never move, for example on the Pinned Object Heap (POH)? Then the JIT could avoid the indirection and instead just hardcode the address of the string, knowing that it would never move. Of course, the POH guarantees objects on it will never move, but it doesn’t guarantee addresses to them will always be valid; after all, it doesn’t root the objects, so objects on the POH are still collectible by the GC, and if they were collected, their addresses would be pointing at garbage or other data that ended up reusing the space.
>
> To address that, .NET 8 introduces a new mechanism used by the JIT for these kinds of situations: the Non-GC Heap (an evolution of the older “Frozen Segments” concept used by Native AOT). The JIT can ensure relevant objects are allocated on the Non-GC Heap, which is, as the name suggests, not managed by the GC and is intended to store objects where the JIT can prove the object has no references the GC needs to be aware of and will be rooted for the lifetime of the process, which in turn implies it can’t be part of an unloadable context.

- Non-GC 힙(네이티브 AOT에서 사용하던 "Frozen Segments” 개념의 발전된 형태인)
- JIT는 이름에서 알 수 있듯이 GC가 관리하지 않는 비 GC 힙에 관련 객체가 할당되도록 할 수 있으며, JIT가 객체에 GC가 알아야 할 참조가 없고 프로세스 수명 동안 루팅될 것임을 증명할 수 있는 객체를 저장하기 위한 것으로, 이는 다시 말해 언로드할 수 없는 컨텍스트의 일부가 될 수 없음을 뜻합니다.

![](img/2024-04-16-21-11-31.png)

[performance-improvements-in-net-8/#constant-folding#zeroing](https://devblogs.microsoft.com/dotnet/performance-improvements-in-net-8/#constant-folding#zeroing)

> The JIT frequently needs to generate code that zeroes out memory. Unless you’ve used **[SkipLocalsInit]**, for example, any stack space allocated with **stackalloc** needs to be zeroed, and it’s the JIT’s responsibility to generate the code that does so. Consider this benchmark:

- zeroing 수행 시 벡터 연산(SIMD) 활용

[performance-improvements-in-net-8/#constant-folding#peephole-optimizations](https://devblogs.microsoft.com/dotnet/performance-improvements-in-net-8/#constant-folding#peephole-optimizations)

- 엿보기 구멍 최적화

> A “peephole optimization” is one in which a small sequence of instructions is replaced by a different sequence that is expected to perform better. This could include getting rid of instructions deemed unnecessary or replacing two instructions with one instruction that can accomplish the same task. Every release of .NET features a multitude of new peephole optimizations, often inspired by real-world examples where some overhead could be trimmed by slightly increasing code quality, and .NET 8 is no exception.

- 광범위하게 발견되는 사례들을 (그러나 카테고리를 만들고 분류하기에는 너무 사소한) 최적화하는 기법들
- 작은 크기의 명령어 집합이 더 나은 성능이 기대되는 다른 명령어로 대체하는 것
- 불필요한 명령어를 제거하거나 두 개의 명령어를 동일한 작업을 수행할 수 있는 하나의 명령어로 대체 등등

> - dotnet/runtime#73120 from @dubiousconst282 and dotnet/runtime#74806 from @En3Tho improved the handling of the common bit-test patterns like (x & 1) != 0.
> - dotnet/runtime#77874 gets rid of some unnecessary casts in a method like short Add(short x, short y) => (short)(x + y).
> - dotnet/runtime#76981 improves the performance of multiplying by a number that’s one away from a power of two, by replacing an imul instruction with a three-instruction mov/shl/add sequence, and dotnet/runtime#77137 improves other multiplications by a constant via replacing a mov/shl sequence with a single lea.
> - dotnet/runtime#78786 from @pedrobsaila fuses together separate conditions like value < 0 || value == 0 into the equivalent of value <= 0.
> - dotnet/runtime#82750 eliminates some redundant cmp instructions.
> - dotnet/runtime#79630 avoids an unnecessary and in a method like static byte Mod(uint i) => (byte)(i % 256).
> - dotnet/runtime#77540 from @AndyJGraham, dotnet/runtime#84399, and dotnet/runtime#85032 optimize pairs of load and store instructions and replace them with a single ldp or stp instruction on Arm.
> - dotnet/runtime#84350 similarly optimizes pairs of str wzr instructions to be str xzr instructions.
> - dotnet/runtime#83458 from @SwapnilGaikwad optimizes some redundant memory loads on Arm by replacing some ldr instructions with mov instructions.
> - dotnet/runtime#83176 optimizes an x < 0 expression from emitting a cmp/cset sequence on Arm to instead emitting an lsr instruction.
> - dotnet/runtime#82924 removes a redundant overflow check on Arm for some division operations.
> - dotnet/runtime#84605 combines an lsl/cmp sequence on Arm into a single cmp.
> - dotnet/runtime#84667 combines neg and cmp sequences into use of cmn on Arm.
> - dotnet/runtime#79550 replaces mul/neg sequences on Arm with mneg.

- 기타 등등...

## 24.04.17

[The Single Language Productivity Myth](https://www.breakneck.dev/blog/single-language-myth)

프로젝트를 단일 언어로 구성할 시 기대할 수 있는 장점

    You only have to learn a single language
    You can share code between frontend and backend
    You get type safety between backend and frontend
    Easier deployment

그래서 정말 그럴지...?? 파고들어보는데

1. 단 하나의 언어만 공부하면 된다.

In any real project, you already use so many languages and tool.

    Html
    Css
    Javascript
    Typescript
    Tailwind
    SQL
    Prisma
    Vite
    Yaml
    Docker
    Vercel
    Serverless vs Server
    8 .config.js files

> You switch between so many languages, tools and systems constantly. One more is not gonna kill your productivity.

- 이미 많은 언어와 도구를 알고 있거나 사용하고 있을 것이고 여기서 하나를 더 추가한다고 생산성이 비극적으로 감소하진 않을 것

> Knowing "frontend" javascript gives you almost no advantage once want to create a server that takes in requests and responds back with json.

- "프론트 엔드" 자바스크립트에 익숙하다는 점이 당신이 서버를 새로 만들 때 큰 도움이 되진 않을 것이다.

If you want to learn that you have to learn

    SQL
    How to model your tables / entities
    Prisma (ORM)
    How to authenticate on the server
    How to run long running, expensive stuff in the background
    How do you even route incoming requests?
    How do you respond back with json?
    How do you respond with a 404? When do you respond with a 404?
    How do you do middleware?
    How do you accept a file upload and store it somewhere?
    How do you generate an openAPI definition? What even is that?
    Wtf is this cors thing?
    Where do you host it?
    How do you set up your pipelines to deploy automatically?

> Imagine having to figure all these out for the first time in a node app vs a c# app.
> 
> No matter how experienced you are in frontend javascript, you gain basically nothing by choosing node over c# over go over django.
> 
> Knowing react does not significantly improve your speed in learning or implementing any of these.

2. 백엔드와 프론트엔드 간의 공유되는 코드를 사용할 수 있다.

It's amazing in theory, it just doesn't really work out in reality. What happens most of the time is that one class tries to do too much.

This is especially appearant in the case of entity classes that also describe the shape of the database tables.

  This goes out of control every single time.  
  Most people have caught onto different dto or model classes by now.

Especially validation trips people up, because they think about "the" validation.  
But there are actually 3 different types of validation here. Client side, api level, database level.

These 3 levels of the system just don't map 1:1 and if you try to make it work (which sadly you can) you will find yourself drowning in complexity.

- 공유 코드의 단점은 분명히 있음. 서버와 클라에서 둘 다 쓰이는 코드라면 하는 일이 너무 많아질 수 있다.
  - ORM 에 대응하는 dto 역할의 클래스가 클라에서도 사용되는 경우
  - 서버 <-> 클라 간 인터페이스에서 이 dto 객체에 대해 추가 검증 요구 사항이 새로 생기고 + 데이터베이스 레이어에서 마찬가지로 dto 에 대해 추가 검증을 요구하는 경우
  - 하나의 dto 타입에 대해 DB 레이어 검증/ 통신 레이어 검증 코드가 자라나게 된다.
- 이 부분은 주장이 좀 빈약하지 싶다

1. 백엔드와 프론트엔드 간 타입 세이프를 보장 가능

This is just not really a big deal with modern tools like openAPI / swagger.

I have type safety between my AspNetCore backend and my NextJs frontend too.
I just have to generate a client from my automatically generated openAPI contract with one command.
npx swagger-typescript-api -p ./../backend/Schema.yaml -o ./src/api -n api.ts --axios

and now I call my typesafe endpoints like this
let launches = await api.getTodaysLaunchesEndpoint();

- 상호 언어간 이런 사례들에 대비하는 도구들은 얼마든지 있다.

4. 쉬운 배포

Honestly, yea.
It definitely is easier to deploy a singular nextjs app than a nextjs app + a backend server in c#, go or even javascript.

However figuring it out shouldnt cost you any more than a day. That's if you never done it before.

- 맞는 말이지만, 그럼 둘 이상의 언어를 사용할 때 배포가 어려워지는가? 
  - 그렇게 하기 위한 방법을 배우는 것은 하루 정도 밖에 시간이 들지 않을 것이다. 배포가 크게 어렵지 않다.

## 24.04.17

[Performance Improvements in .NET 8 - .NET Blog](https://devblogs.microsoft.com/dotnet/performance-improvements-in-net-8/)

**JIT 역가상화(Devirtualize) 최적화**

> Beyond the mechanisms used to enable tiering and dynamic PGO getting better (and, did I mention, being on by default?!) in .NET 8, the optimizations it performs also get better. One of the main optimizations dynamic PGO feeds is the ability to devirtualize virtual and interface calls per call site. As noted, the JIT tracks what concrete types are used, and then can generate a fast path for the most common type; this is known as guarded devirtualization (GDV). Consider this benchmark:

- 동적 PGO 의 주요 최적화 기능 중 하나는 call site별로 가상 및 인터페이스 호출을 가상화하는 능입니다. 앞서 언급했듯이 JIT는 어떤 콘크리트 타입이 사용되는지 파악한 다음 가장 일반적인 타입에 대한 패스트 패스를 생성할 수 있으며, 이를 guarded devirtualization(GDV)라고 합니다.

[5 Rules for DTOs  Blog](https://ardalis.com/5-rules-dtos/?ref=dailydev)

- [(132) 5 Rules For DTOs - YouTube](https://www.youtube.com/watch?v=W4n9x_qGpT4)
- C# 기반 코드를 예시로 들어서 설명

![](img/2024-04-17-20-17-21.png)

![](img/2024-04-17-20-18-04.png)

![](img/2024-04-17-20-18-19.png)

> Now, even though DTOs don't need encapsulation, it's still generally preferred to use C# properties rather than fields. By default, serializers and other language features work on properties but not fields (though you can configure this). Rule 3:

![](img/2024-04-17-20-18-30.png)

> Here are some of the things that should be DTOs, and should be named according to their particular use, rather than naming them "FooDTO"

![](img/2024-04-17-20-18-40.png)

[(132) .NET Configuration In Depth  .NET Conf 2023 - YouTube](https://www.youtube.com/watch?v=aOXaBZFB0-0)

![](img/2024-04-17-20-47-35.png)

![](img/2024-04-17-20-47-51.png)

![](img/2024-04-17-20-48-15.png)

![](img/2024-04-17-20-49-16.png)

dotnet 의 configuration 기능에 대한 강연 세션

- 애플리케이션의 구성 및 옵션 정보에 대한 분류를 설명
- 다양한 사례를 수집해 일반화된 기능을 제공함.
  - config 정보를 정적 혹은 동적으로 제공할 수 있음
  - config 의 소스는 파일 형태(Json) / Azure 등 외부 서비스의 데이터 / 프로세스 실행 인자(args)
    - config 의 소스가 어느 곳이라도 맞춤 솔루션을 가지고 있음
  - config 의 사용처가, 범주에 따라 필요한 option 을 전달받도록 제한

[Fearless Security Memory Safety - Mozilla Hacks - the Web developer blog](https://hacks.mozilla.org/2019/01/fearless-security-memory-safety/)

**What Is Memory Safety**

> When we talk about building secure applications, we often focus on memory safety. Informally, this means that in all possible executions of a program, there is no access to invalid memory. Violations include:

- use after free / 이미 반환된 메모리를 사용
- double free / 중복 반환
  - 스마트 포인터 / GC / 혹은 ownership (Rust) 로 방지
- null pointer dereference / Null 포인터 참조
  - Rust prevents null pointer dereferencing two ways:
    - Avoiding nullable pointers (with special OptionType)
    - Avoiding raw pointer dereferencing
- using uninitialized memory / 초기화되지 않은 메모리 사용
- buffer overflow / 버퍼 오버플로우
  - - bound checks 로 방지

## 24.04.18

[LRitzdorfTheJeffDeanFacts A consolidated list of the Jeff Dean Facts!](https://github.com/LRitzdorf/TheJeffDeanFacts)

- [구글 천재 프로그래머 - YouTube](https://www.youtube.com/watch?v=VfBOPOwc1UI&list=WL&index=16)
- 구글 천재 프로그래머 제프 딘(Jeff Dean) 에 관한 밈

> Compilers don't warn Jeff Dean. Jeff Dean warns compilers.

- 컴파일러는 Jeff Dean 에게 경고를 하지 않는다. Jeff Dean 은 컴파일러에게 경고를 한다.

[Latency Numbers Every Programmer Should Know](https://gist.github.com/jboner/2841832)

### Latency numbers every programmer should know
    L1 cache reference ......................... 0.5 ns
    Branch mispredict ............................ 5 ns
    L2 cache reference ........................... 7 ns
    Mutex lock/unlock ........................... 25 ns
    Main memory reference ...................... 100 ns             
    Compress 1K bytes with Zippy ............. 3,000 ns  =   3 µs
    Send 2K bytes over 1 Gbps network ....... 20,000 ns  =  20 µs
    SSD random read ........................ 150,000 ns  = 150 µs
    Read 1 MB sequentially from memory ..... 250,000 ns  = 250 µs
    Round trip within same datacenter ...... 500,000 ns  = 0.5 ms
    Read 1 MB sequentially from SSD* ..... 1,000,000 ns  =   1 ms
    Disk seek ........................... 10,000,000 ns  =  10 ms
    Read 1 MB sequentially from disk .... 20,000,000 ns  =  20 ms
    Send packet CA->Netherlands->CA .... 150,000,000 ns  = 150 ms

Assuming ~1GB/sec SSD

![](img/2024-04-18-16-33-36.png)

Visual chart provided by [ayshen](https://gist.github.com/ayshen)

Data by [Jeff Dean](http://research.google.com/people/jeff/)

Originally by [Peter Norvig](http://norvig.com/21-days.html#answers)

Compiled by [github.com/hellerbarde](https://gist.github.com/hellerbarde/2843375)

## 24.04.19

[Introducing .NET Core - .NET Blog](https://devblogs.microsoft.com/dotnet/introducing-net-core/)

- 과거의 닷넷은 Set of Verticals, 수직 구조의 집합

> When we originally shipped the .NET Framework in 2002 there was only a single framework. Shortly after, we released the .NET Compact Framework which was a subset of the .NET Framework that fit within the footprint of smaller devices, specifically Windows Mobile. The compact framework was a separate code base from the .NET Framework. It included the entire vertical: a runtime, a framework, and an application model on top.
> 
> Since then, we’ve repeated this subsetting exercise many times: Silverlight, Windows Phone and most recently for Windows Store. This yields to fragmentation because the .NET Platform isn’t a single entity but a set of platforms, owned by different teams, and maintained independently.
> 
> Of course, there is nothing wrong with offering specialized features in order to cater to a particular need. But it becomes a problem if there is no systematic approach and specialization happens at every layer with little to no regards for corresponding layers in other verticals. The outcome is a set of platforms that only share APIs by the fact that they started off from a common code base. Over time this causes more divergence unless explicit (and expensive) measures are taken to converge APIs.

![](img/2024-04-19-15-36-59.png)

불행히도 이 수직 구조 간에 공유 코드가 지원되지 않았음

- 닷넷의 버전 업데이트, 그리고 호환성과의 사투

> Unfortunately, we’ve also learned that even compatible changes can break applications. Let me provide a few examples

    Adding an interface to an existing type can break applications because it might interfere with how the type is being serialized.
    Adding an overload to a method that previously didn’t had any overloads can break reflection consumers that never handled finding more than one method.
    Renaming an internal type can break applications if the type name was surfaced via a ToString() method.

> .NET Core is a modular implementation that can be used in a wide variety of verticals, scaling from the data center to touch based devices, is available as open source, and is supported by Microsoft on Windows, Linux and Mac OSX.
>
> Let me go into a bit more detail of how .NET Core looks like and how it addresses the issues I discussed earlier.

버전 업데이트를 진행해도 대부분 문제없는 것은 사실. 하지만 99.9%가 멀쩡해도 0.1%의 사용사례에서 호환성 문제가 있다면

.NET 기반 프로세스가 돌아가는 18억개의 장비 중 180만개의 장비가 장애를 겪게 됨

그것도 런타임 중에 그러니까 고객 대응 중에 문제가 발생한다면 경우에 따라 치명적일 수 있음

- Birth of portable class libraries(PCL) / 해결책으로 PCL 도입

> Originally, there was no concept of code sharing across verticals. No portable class libraries, no shared projects. You were essentially stuck with creating multiple projects, linked files, and #if. This made targeting multiple verticals a daunting task.
> 
> In the Windows 8 timeframe we came up with a plan to deal with this problem. When we designed the Windows Store profile we introduced a new concept to model the subsetting in a better way: contracts.
> 
> Originally, the .NET Framework was designed around the assumption that it’s always deployed as a single unit, so factoring was not a concern. The very core assembly that everything else depends on is mscorlib. The mscorlib provided by the .NET Framework contains many features that that can’t be supported everywhere (for example, remoting and AppDomains). This forces each vertical to subset even the very core of the platform. This made it very complicated to tool a class library experience that lets you target multiple verticals.
> 
> The idea of contracts is to provide a well factored API surface area. Contracts are simply assemblies that you compile against. In contrast to regular assemblies contract assemblies are designed around proper factoring. We deeply care about the dependencies between contracts and that they only have a single responsibility instead of being a grab bag of APIs. Contracts version independently and follow proper versioning rules, such as adding APIs results in a newer version of the assembly.
> 
> We’re using contracts to model API sets across all verticals. The verticals can then simply pick and choose which contracts they want to support. The important aspect is that verticals must support a contract either wholesale or not at all. In other words, they can’t subset the contents of a contract.
> 
> This allows reasoning about the API differences between verticals at the assembly level, as opposed to the individual API level that we had before. This aspect enabled us to provide a class library experience that can target multiple verticals, also known as portable class libraries.

> Two years ago, we’ve started to ship libraries on NuGet. Since we didn’t add those libraries to the .NET Framework we refer to them as “out-of-band”. Out-of- band libraries don’t suffer from the problem we just discussed because they are application-local. In other words, the libraries are deployed as if they were part of your application.
> 
> This pretty much solves all the problems that prevent you from upgrading to a later version. Your ability to take a newer version is only limited by your ability to release a newer version of your application. It also means you’re in control which version of the library is being used by a specific application. Upgrades are done in the context of a single application without impacting any other application running on the same machine.
> 
> This enables us to release updates in a much more agile fashion. NuGet also provides the notion of preview versions which allow us to release bits without yet committing on a specific API or behavior. This supports a workflow where we can provide you with our latest design and – if you don’t like it – simply change it. A good example of this is immutable collections. It had a beta period of about nine months. We spend a lot of time trying to get the design right before we shipped the very first version. Needless to say that the final design – thanks to the extensive feedback you provided – is way better than the initial version.

- 닷넷 코어 -> Nuget Package 의 집합으로 구성시켜버리기

![](img/2024-04-19-15-41-41.png)

![](img/2024-04-19-15-41-51.png)

> NuGet allows us to deliver .NET Core in an agile fashion. So if we provide an upgrade to any of the NuGet packages, you can simply upgrade the corresponding NuGet reference.
> 
> Delivering the framework itself on NuGet also removes the difference between expressing 1st party .NET dependencies and 3rd party dependencies – they are all NuGet dependencies. This enables a 3rd party package to express, for instance, that they need a higher version of the System.Collections library. Installing this 3rd party package can now prompt you to upgrade your reference to System.Collections. You don’t have to understand the dependency graph – you only need to consent making changes to it.
> 
> The NuGet based delivery also turns the .NET Core platform into an app-local framework. The modular design of .NET Core ensures that each application only needs to deploy what it needs. We’re also working on enabling smart sharing if multiple applications use the same framework bits. However, the goal is to ensure that each application is logically having its own framework so that upgrading doesn’t interfere with other applications running on the same machine.
> 
> Our decision to use NuGet as a delivery mechanism doesn’t change our commitment to compatibility. We continue to take compatibility extremely seriously and will not perform API or behavioral breaking changes once a package is marked as stable. However, the app-local deployment ensures that the rare case where a change that is considered additive breaks an application is isolated to development time only. In other words, for .NET Core these breaks can only occur after you upgraded a package reference. In that very moment, you have two options: addressing the compat glitch in your application or rolling back to the previous version of the NuGet package. But in contrast to the .NET Framework those breaks will not occur after you deployed the application to a customer or the production server.

## 24.04.20

[Dynamic PGO in .NET 6.0.md](https://gist.github.com/EgorBo/dc181796683da3d905a5295bfd3dd95b)

## What exactly PGO can optimize for us?
1) **Profile-driving inlining** - inliner relies on PGO data and can be very aggressive for hot paths and care less about cold ones, see [dotnet/runtime#52708](https://github.com/dotnet/runtime/pull/52708) and [dotnet/runtime#55478](https://github.com/dotnet/runtime/pull/55478). A good example where it has visible effects is [this](https://twitter.com/EgorBo/status/1451149444183990273) StringBuilder benchmark:


2) **Guarded devirtualization** - most monomorphic virtual/interface calls can be devirtualized using PGO data, e.g.:
```csharp
void DisposeMe(IDisposable d)
{
    d.Dispose();
}
```
It looks like nothing can be optimized here, right? Just an ordinary virtual (interface) call on top of an unknown object that will go through several indirects to call the actual Dispose() implementation and its body will never be inlined here. Now let's see what PGO can do here.  
With Dynamic PGO on, this method will be compiled to something like this in tier0 (in machine code):
```diff
void DisposeMe(IDisposable d)
{
+   call CORINFO_HELP_CLASSPROFILE32(d, offset);
    d.Dispose();
}
```
We now poll that `d` for its underlying type every call of that method. Yes, it makes it slightly slower, but eventually it will be re-compiled to tier1 to something like this:

```diff
void DisposeMe(IDisposable d)
{
+   if (d is MyType)           // E.g. Profile states that Dispose here is 'mostly' called on MyType.
+       ((MyType)d).Dispose(); // Direct call - can be inlined now!
+   else
        d.Dispose();           // a cold fallback, just in case
}
```
![image](https://user-images.githubusercontent.com/523221/126960839-6bc3b110-014a-4680-abd8-44c9e7e01765.png)
&nbsp;&nbsp;&nbsp;&nbsp;*^ codegen diff for a case where MyType::Dispose is empty*

  
3) **Hot-cold block reordering** - JIT re-orders blocks to keep hot ones closer to each other and pushes cold ones to the end of the method. The following code:
```csharp
void DoWork(int a)
{
    if (a > 0)
        DoWork1();
    else
        DoWork2();
}
```
Is compiled like this in tier0:
```diff
void DoWork(int a)
{
    if (a > 0)
+       __block_0_counter++;
        DoWork1();
    else
+       __block_1_counter++;
        DoWork2();
}
```
And again: once it's recompiled to tier1 it is optimized into:
```diff
void DoWork(int a)
{
    // E.g. __block_0_counter is smaller or even zero => DoWork1 is rarely (never) taken
    // and JIT re-orders DoWork2 with DoWork1:
-   if (a > 0)
+   if (a <= 0)
-       DoWork2();
+       DoWork1();
    else
-       DoWork1();
+       DoWork2();
}
```
4) **Register allocation** - realistic block weights allow JIT to pick a better strategy on what to keep in registers and what to spill
5) **Misc** - some optimizations such as Loop Clonning, Inlined Casts, etc. aren't applied in cold blocks.

[Java의 미래, Virtual Thread  우아한형제들 기술블로그](https://techblog.woowahan.com/15398/)

![](img/2024-04-20-01-36-55.png)

Virtual Thread는 기존 Java의 스레드 모델과 달리, 플랫폼 스레드와 가상 스레드로 나뉩니다. 플랫폼 스레드 위에서 여러 Virtual Thread가 번갈아 가며 실행되는 형태로 동작합니다. 마치 커널 스레드와 유저 스레드가 매핑되는 형태랑 비슷합니다.

여기서 가장 큰 특징은 Virtual Thread는 컨텍스트 스위칭 비용이 저렴하다는 것입니다.

|Thread | Virtual | Thread |
| ------- | ----------- | ----- |
|Stack 사이즈 |	~2MB |	~10KB|
|생성시간 |	~1ms |	~1µs| 
컨텍스트 스위칭 |	~100µs |	~10µs

Thread는 기본적으로 최대 2MB의 스택 메모리 사이즈를 가지기 때문에, 컨텍스트 스위칭 시 메모리 이동량이 큽니다. 또한 생성을 위해선 커널과 통신하여 스케줄링해야 하므로, 시스템 콜을 이용하기 때문에 생성 비용도 적지 않습니다.

하지만 Virtual Thread는 JVM에 의해 생성되기 때문에 시스템 콜과 같은 커널 영역의 호출이 적고, 메모리 크기가 일반 스레드의 1%에 불과합니다. 따라서 Thread에 비해 컨텍스트 스위칭 비용이 적습니다.

## 24.04.22

[Introducing .NET Standard - .NET Blog](https://devblogs.microsoft.com/dotnet/introducing-net-standard/)

..NET Standard : 닷넷 생태계에서 지원하는 API 집합

    .NET Standard is a set of APIs that all .NET platforms have to implement. This unifies the .NET platforms and prevents future fragmentation.
    .NET Standard 2.0 will be implemented by .NET Framework, .NET Core, and Xamarin. For .NET Core, this will add many of the existing APIs that have been requested.
    .NET Standard 2.0 includes a compatibility shim for .NET Framework binaries, significantly increasing the set of libraries that you can reference from your .NET Standard libraries.
    .NET Standard will replace Portable Class Libraries (PCLs) as the tooling story for building multi-platform .NET libraries.

![](img/2024-04-22-13-41-38.png)

    But on the other hand, this forking poses a massive problem for developers writing code for multiple .NET platforms because there isn’t a unified class library to target:
    There are currently three major flavors of .NET, which means you have to master three different base class libraries in order to write code that works across all of them. Since the industry is much more diverse now than when .NET was originally created it’s safe to assume that we’re not done with creating new .NET platforms. Either Microsoft or someone else will build new flavors of .NET in order to support new operating systems or to tailor it for specific device capabilities.

![](img/2024-04-22-13-41-55.png)

    This is where the .NET Standard comes in:
    For developers, this means they only have to master one base class library. Libraries targeting .NET Standard will be able to run on all .NET platforms. And platform providers don’t have to guess which APIs they need to offer in order to consume the libraries available on NuGet.

**What does this mean for .NET Core?**

- .NET Core 와 .NET Standard 는 엄연히 분리되어 있는 상태
- .NET Standard는 모든 플랫폼에서 검증된 API 이기 때문에, 기존 API 집합에서 새로운 것을 추가하기 위해 검증 절차가 복잡할 것임
- .NET Core는 out-of-band 들 그러니까 닷넷 전체 생태계에서 검증되지는 않았지만 닷넷 팀이 실험 운용하기 위한 도구들을 .NET Core에 실을 수 있다.
  - 개발자 피드백들을 미리 받아보고 그 후에 .NET Standard에 태우기도 한다고 함.

## 24.04.23

**C# float / decimal**

C#에서 float과 decimal은 둘 다 부동 소수점 숫자를 표현하는 데 사용되는 데이터 유형입니다. 그러나 그들 간에는 몇 가지 중요한 차이점이 있습니다.

- 정밀도와 범위:
  - float: IEEE 754 표준에 따라 32 비트 부동 소수점을 나타냅니다. 이는 대략 7자리의 유효 숫자를 가지며 대략적으로 ±1.5 x 10^(-45)에서 ±3.4 x 10^(38) 범위를 가집니다.
  - decimal: 128 비트 고정 소수점을 사용하며, 보다 높은 정밀도를 제공합니다. 약 ±1 x 10^(-28) 에서 ±7.9 x 10^(28) 범위를 가지며, 최대 28자리의 유효 숫자를 표현할 수 있습니다.
- 소수점 고정 및 부동:
  - float: 이진 부동 소수점으로 표현되어 있어서, 0이 아닌 숫자를 정확하게 표현하는 데 어려움이 있을 수 있습니다. 예를 들어, 0.1과 같은 십진수를 정확히 표현할 수 없을 수 있습니다.
  - decimal: 십진 고정 소수점으로 표현되어 있어서, 금융 및 금전 계산과 같은 정확한 값이 필요한 분야에서 유용합니다. 이로 인해 소수점 이하 숫자를 정확하게 다룰 수 있습니다.
- 메모리 사용:
  - float: 각 값이 32 비트이므로 메모리 사용량이 상대적으로 작습니다.
  - decimal: 128 비트로 각 값이 표현되므로, 메모리 사용량이 더 큽니다. 이는 대량의 숫자를 다루는 경우에는 중요한 고려 요소가 될 수 있습니다.
- 성능:
  - float은 하드웨어에서 원시적으로 지원되는 타입이므로 일반적으로 연산이 더 빠릅니다.
  - decimal은 소프트웨어로 구현되어 있으며 정밀도를 위해 더 많은 작업을 수행해야 하므로 연산 속도가 더 느릴 수 있습니다.

**해킹 관련해서**

[xz 오픈소스 공격의 전체 타임라인 정리  GeekNews](https://news.hada.io/topic?id=14122)

- 2년 넘게 "Jia Tan"이라는 이름을 사용하는 공격자가 xz 압축 라이브러리에 성실하고 효과적인 기여자로 활동하여 최종적으로 커밋 권한과 관리자 권한을 부여받음.
- 그 권한을 사용하여 Debian, Ubuntu, Fedora 및 기타 systemd 기반 Linux 시스템에서 OpenSSH sshd의 종속성이기도 한 xz의 일부인 liblzma에 매우 미묘하고 주의 깊게 숨겨진 백도어를 설치함.
- 이 백도어는 SSH 세션 시작 시 공격자가 숨겨진 명령을 보내는 것을 감시하여, 로그인하지 않고도 대상 시스템에서 임의의 명령을 실행할 수 있는 기능을 공격자에게 제공함. 인증되지 않은 대상 원격 코드 실행임.
- 이 공격은 2024년 3월 29일 공개적으로 공개되었으며, 널리 사용되는 오픈소스 소프트웨어에 대한 최초의 심각한 공급망 공격으로 보임.
- 오픈소스 공급망 보안에 있어 분수령이 될 사건임.
- 이 게시물은 2021년 말로 거슬러 올라가는 것으로 보이는 이 공격의 사회공학적 측면에 대해 구성한 자세한 타임라인임.

[XZ Utils 백도어 사건으로 돌아보는 오픈소스 생태계](https://blog.outsider.ne.kr/1714)

이번 공격 자체도 충격적이지만 비슷한 일이 반복적으로 발생하는데 상황이 나아지진 않는다고 느끼고 있다. 이전에도 비슷한 사건이 있었다.

- 2018년에는 Node.js의 [event-stream](https://github.com/dominictarr/event-stream)를 이용한 [공급망 공격이 있었다](https://snyk.io/blog/a-post-mortem-of-the-malicious-event-stream-backdoor). 2011년에 `event-stream`을 만든 Dominic Tarr는 당시 npm에만 400여 개의 모듈을 가지고 있었고 더 이상 관리되지 않던 `event-stream`에 자신이 기여하겠다고 접근해서 저장소 권한과 모듈 배포 권한을 획득한 뒤 이 안에 악성코드를 심어서 배포했다.
- 2024년에는 브라우저 간 동작 차이를 메꿔주는 `polyfill.js`를 편하게 사용하도록 `polyfill.io`라는 서비스가 Funnull이라는 회사에 넘어가게 되면서 최초에 `polyfill.io`를 만들었던 사람이 공급망 공격이 우려되니 [즉시 사용을 중단하라고 경고](https://x.com/triblondon/status/1761852117579427975?s=20)했다.

`polyfill.io`는 약간 다른 부분이 있긴 하지만 `event-stream`을 포함해서 이번 사건도 오픈소스 메인테이너 부족이 근본적인 원인이 아닌가 하는 생각이 든다. 메인테이너가 10명, 20명이었다면 Jia Tan이 저렇게 메인테이너로 쉽게 들어오지도 못했을 것이고 들어왔어도 악성코드를 맘대로 커밋하지 못했을 것이다. 그렇게 보면 이런 문제 혹은 품질의 문제도 포함해서 **근본적인 원인은 오픈소스 생태계의 메인테이너들이 처한 환경이 그리 좋지 않다는 데 있다고 생각한다**.

xkcd에 [Dependency](https://xkcd.com/2347/)라는 다음과 같은 만화가 있다.

![](img/2024-04-23-19-26-26.png)

수많은 의존성을 가진 오픈소스를 사용하고 있지만 일반적으로 개발자가 직접 사용하는 유명한 프로젝트나 모던한 프로젝트에만 관심을 두지, 그 뒤에 있는 많은 프로젝트에는 관심을 가지지 않는다. 이번 XZ Utils와 마찬가지로 xkcd에서는 그중 어떤 의존성은 한 명의 메인테이너에게 완전히 의존하고 있어서 그 사람이 지치거나 더는 작업을 할 수 없게 되었을 때 전체 의존성이 깨질 수 있음을 지적한 것이다.

공급망 공격은 아니었지만 2014년 4월 OpenSSL에서 메모리에 저장된 정보를 빼갈 수 있는 [Heartbleed](https://heartbleed.com/)라는 취약점이 발견되었다. 이때 취약점과 별개로 오픈소스 생태계는 이래서 믿을 수 없다거나 어떻게 이런 버그를 모를 수 있냐 하는 얘기도 있었지만, 전 세계에서 OpenSSL에 의존하지 않는 곳이 없다시피 하지만 실패로 펀딩을 제대로 받지 못하고 [풀타임 직원이 1명뿐](http://veridicalsystems.com/blog/of-money-responsibility-and-pride/)임이 밝혀졌다. 그리고 OpenSSL에 십여 년 동안 기여하던 사람들이 [이때 펀딩이 들어오면서 처음 뒤셀도르프에서 오프라인으로 만날 수 있게 되었다](https://coolspeed.wordpress.com/2015/02/16/unseeable_comrade_in_arms/)는 얘기에 놀라기도 했다.(이때 이분들은 온라인으로만 서로 작업하다가 15년 만에 처음 만나게 되었다.)

이런 사건들을 보면 **우리 생태계가 소수의 선의에 얼마나 기대어 있는가를 다시한번 생각하게 했다**. 여기서 **우리 생태계라고 한 것은 오픈소스 생태계뿐만 아니라 그 위에 쌓아 올린 수많은 IT 시스템도 마찬가지이기 때문이다**

## 24.04.24

[Quora 는 어떻게 죽었나  GeekNews](https://news.hada.io/topic?id=13191)

    Quora는 한때 특정 질문에 대한 답변을 찾는 데 있어 전문가의 정보를 제공하는 번성하는 커뮤니티였음
    사용자들이 이탈하면서 사이트는 의미 없고 반복적인 내용, 이상한 질문, 증오스러운 글, AI 생성 글들로 가득 차게 됨
    과거에는 구글 검색 결과 상단에서 Quora의 신중한 답변을 볼 수 있었지만, 이제는 터무니없는 질문과 답변이 검색 결과에 나타남

## Quora의 초기 장점과 커뮤니티

    Quora는 소셜 네트워킹을 염두에 두고 설계되었으며, 전문가들이 지식을 공유하고 커뮤니티를 구축할 수 있는 플랫폼이었음
    초기 멤버들은 Quora의 질 높은 답변과 질문, 활발한 모더레이션, 사용자 중심의 사이트 구조를 높이 평가함
    Quora는 전문가들에게 다양한 혜택을 제공하고, 긍정적인 공간을 유지하기 위해 노력했으며, 이로 인해 많은 페이지 뷰와 투자를 유치함

## Quora의 문제점과 쇠락

    Quora는 질문의 길이를 줄이고, 피드 최적화를 통해 질 낮은 콘텐츠를 홍수처럼 쏟아내기 시작함
    광고와 봇 문제, 수익 창출의 지연, 예산 삭감 등으로 인해 커뮤니티 관리와 품질 유지에 어려움을 겪음
    AI의 등장과 자동화된 모더레이션은 사이트의 질을 더욱 악
    화시킴

## AI 시대의 Quora

    Quora는 AI를 통해 질문과 답변을 생성하고, 사용자의 답변을 AI 모델 훈련에 사용할 수 있도록 서비스 약관을 변경함
    많은 사용자들이 새로운 약관에 동의하지 않고 자신의 작업을 삭제하거나 사이트를 떠남
    AI로 인해 커뮤니티의 정체성이 훼손되고, Quora가 과거의 커뮤니티와 전문성을 자동화 시스템으로 대체하려는 시도는 실패로 끝날 것으로 예상됨

## 24.04.30

[Variable-length quantity - Wikipedia](https://en.wikipedia.org/wiki/Variable-length_quantity)

- VLQ

> A variable-length quantity (VLQ) was defined for use in the standard MIDI file format[2] to save additional space for a resource-constrained system, and is also used in the later Extensible Music Format (XMF).

![](img/2024-04-30-16-03-45.png)

- 패킷 전송 시에 정수형 타입 바이트 사이즈를 압축하기 위해 적용
- 깃허브 코드 예시: [kstenerudgo-vlq Go implementation of the Variable Length Quantity (VLQ) type](https://github.com/kstenerud/go-vlq)

## 24.05.09

**mstsc**

- [Microsoft Learn: mstsc](https://learn.microsoft.com/ko-kr/windows-server/administration/windows-commands/mstsc)

> Creates connections to Remote Desktop Session Host servers or other remote computers and edits an existing Remote Desktop Connection (.rdp) configuration file.
>
> `mstsc.exe [<connectionfile>] [/v:<server>[:<port>]] [/g:<gateway>] [/admin] [/f <fullscreen>] [/w:<width> /h:<height>] [/public] [/multimon] [/l] [/restrictedadmin] [/remoteguard] [/prompt] [/shadow:<sessionid>] [/control] [/noconsentprompt]
mstsc.exe /edit <connectionfile>`

ChatGPT: MSTSC는 Microsoft Terminal Services Client의 약자로, Microsoft Windows 운영 체제에서 사용되는 원격 데스크톱 프로토콜의 클라이언트 응용 프로그램입니다. 이 프로그램은 원격 데스크톱 서비스를 사용하여 원격 컴퓨터에 연결하고 그 컴퓨터를 제어할 수 있도록 해줍니다. MSTSC를 사용하면 지리적으로 떨어진 컴퓨터에 원격으로 액세스하여 파일을 전송하거나 작업을 수행할 수 있습니다.

[The Decorator Pattern is sometimes helpful – The Shade Tree Developer](https://jeremydmiller.com/2024/04/29/the-decorator-pattern-is-sometimes-helpful/)

    The most common usage of a decorator for me has been to separate out some kind of infrastructural concern like logging, error handling, or security from the core behavior. Just think on this. Instrumentation, security, and error handling are all very important elements of successful production code, but how many times in your career have you struggled to comprehend, modify, or debug code that is almost completely obfuscated by technical concerns.
    
    According to the original Gang of Four book, the “Decorator Pattern”:
    
    …dynamically adds/overrides behavior in an existing method of an object.

- decorator 패턴을 wrapper 형태로 사용하는 사례
- DB로부터 데이터를 조회해 .NET object 로 바꿔주는 LoadAsync() 메서드가 있다고 하면
  - LoadAsync() 메서드를 정의하는 인터페이스 (A 인터페이스)
  - LoadAsync 메서드의 코어 역할을 수행하는 버전 (B 클래스)
  - A 인터페이스 객체를 필드로 쥐고 있으며(Nested 객체 활용), LoadAsync 호출 시 해당 객체의 LoadAsync를 호출되 에러 핸들링을 책임지는 버전 (C 클래스)
- B 클래스는 이제 코어 역할에만 집중하고, C 클래스는 Resilient 하게 역할을 수행하는 것에 초점을 맞추기 -> 역할에 분리를 달성할 수 있다.

## 24.05.10

[Don't write clean code, write CRISP code — Bitfield Consulting](https://bitfieldconsulting.com/posts/crisp-code)

- Correct
- Readable
- Idiomatic

    An obvious example of a universal convention is err: Go programmers always use this name to refer to an arbitrary error value. While we wouldn’t usually re-use variable names within the same function, we do re-use err for all the various errors that there can be throughout the function. It’s a mistake to try to avoid this by creating variant names like err2, err3, and so on.
    
    Why? Because it requires a tiny bit more cognitive effort from the reader. If you see err, your mind glides right over it with perfect understanding. If you see some other name, your mind has to stop to resolve the puzzle.
    
    I call these tiny roadblocks “cognitive microaggressions”. Each is so tiny that its individual effect is almost unnoticeable, yet they soon pile up, and if you encounter them all day and every day, they have a significant effect on your quality of life.
    
    As you write each line of code, you should be thinking “How much effort does it take to understand this? Could I reduce that somehow?” The secret of great software engineering is doing a lot of little things well.

- Simple

    One attribute that simple code tends to have is directness: it does just what it says on the tin. It doesn’t have weird and unexpected side effects, or conflate several unrelated things. Directness is inversely related to concision: if there are three similar tasks to do, a simple program will do it with three similar functions.
    
    This is one reason people find it hard to write simple code: we’re all terrified of repeating ourselves. The DRY principle is so ingrained that we even use it as a verb: “we need to DRY up this function” (as Calvin noted, verbing weirds language).
    
    But there’s nothing wrong with repetition in itself. I say again, there’s nothing wrong with repetition in itself (see?) It can be a valuable way of conveying emphasis. And if we find ourselves creating new abstractions to no purpose other than avoiding repetition, then we’ve gone wrong somewhere: that makes the program more complex, not more simple.

- Performant

    The idea of “mechanical sympathy” is helpful to bear in mind when you’re programming. It means that you have some understanding of how the machine works, fundamentally, and you take care not to abuse it or get in its way. For example, if you don’t know what memory is, how can you write efficient programs?
    
    I often see code that blithely slurps in entire data files into a single structure, then proceeds to actually process them just a few bytes at a time. I learned to program on a machine with 1K of memory, or about a thousand words, and that will teach you the value of a byte, believe me.
    
    I’m writing this, some years later, on a machine with about 16 million words of memory, and don’t run out of them quite so frequently, but nonetheless, memory matters.

    ## 24.05.13

[(167) Cognitive Prompting(인지적 프롬프팅) 공유회 full ver.](https://www.youtube.com/watch?v=CkCL8dV_mPk&list=WL&index=5)

![](img/2024-05-13-02-26-42.png)

![](img/2024-05-13-02-27-40.png)

[MSDN: DeflateStream](https://learn.microsoft.com/ko-kr/dotnet/api/system.io.compression.deflatestream?view=net-8.0)

- 무손실 파일 압축 및 파일 해제. 업계 표준인 Deflate 알고리즘
- [Deflate - Wikipedia](https://en.wikipedia.org/wiki/Deflate)

**Go 문법 비판하는 내용**

[GitHub - ksimkago-is-not-good A curated list of articles complaining that go (golang) isn't good enough](https://github.com/ksimka/go-is-not-good)

> - stuck in 70's
> - no oop
> - c style
> - poor error handling

## 24.05.14

[당신이 바로, 당신이 찾던 기술 코파운더에요  GeekNews](https://news.hada.io/topic?id=14609)

- [You Are the Technical Cofounder You Need](https://every.to/p/you-are-the-technical-cofounder-you-need)

- Exit한 창업자로서, 세상을 바꿀 다음 아이디어를 가지고 있다고 믿는 야심찬 기업가들이 종종 찾아옴
    - 그들은 아이디어를 단순한 개념 이상으로 만들어 시작하고 싶어함
- 일반적으로 그들이 해결하고자 하는 문제에 대해 이야기하는 것으로 시작함
    - 초기 창업자들에게 주는 조언: 대부분의 가정이 틀릴 것이므로, 빠르게 반복하고 확장되지 않는 일을 하는 것이 중요함
- 대화는 보통 다음과 같이 진행됨:
    
    > 기업가: ...그래서 제 스타트업이 혁신적일 거예요.  
    > 나: 좋아요, 지금까지 어디까지 왔나요?  
    > 기업가: 와이어프레임을 만들었어요. MVP를 만들기 위해 계약자를 고용했는데, 비용이 많이 들었어요. 그래서 자금 조달이 필요할 것 같아요.  
    > 나: 하지만 계속 외주 개발자에게 의존하고 싶진 않죠? 당신처럼 이 일에 전념할 사람이 필요해요. 소프트웨어 스타트업은 창업팀에 소프트웨어 엔지니어가 필요해요.  
    > 기업가: 맞아요. 기술 공동창업자를 찾는 게 답일 수 있다고 생각했어요. 어떻게 해야 할까요?
    
- 이 때 나는 보통 **안 좋은 소식**을 전해야 함
    - 아이디어를 가지고 기술 공동창업자를 찾는 사람이, 아이디어를 찾는 기술 공동창업자보다 훨씬 많음
    - **아이디어만 가진 사람이 엔지니어 파트너를 성공적으로 찾는 경우는 거의 없음**
    - 기술 공동창업자를 기다리는 대부분의 사업은 시작조차 못하거나, 내부 역량 부족으로 실패함
- 하지만 희망이 없는 건 아님
    - 이 시점에서 나는 도움이 되는 조언을 해주는데, 창업자로서 성공하는데 필수적인 태도에 뿌리를 두고 있음
    - 열정적인 초기 창업자들에게 기술 공동창업자 찾기를 그만두고, 그 에너지를 **기술 공동창업자가 되려고** 노력하는 데 쏟으라고 조언함

**야심찬 목표는 배움의 이유임**

- 야심 찬 창업자는 어느 날 아침 꿈에 그리던 아이디어를 떠올리며 이를 만들고 싶어하지만, 정식 기술 교육을 받은 적이 없어 막막하기만 함
    - 그들은 혼자선 할 수 없다고 믿음
    - 어떻게 시작해야 할지, 누가 안내해 줄지, 배우고 만들 시간을 어떻게 찾을지 모름
    - 이런 딜레마는 판매, 마케팅, 성장 등 많은 분야에서 발생하지만, 특히 프로그래밍에서 그러함
- 그러나 달성하고자 하는 야심찬 흥미로운 목표보다 새로운 것을 배울 동기가 더 큰 것은 없음
    - 큰 아이디어를 가진 창업자들에게: "**축하합니다. 가장 어려운 부분을 해냈습니다. 배울 이유를 찾은거에요.**"
- 야심찬 기업가와의 대화로 돌아가면:
    
    > 나: 당신처럼 이 일에 전념할 사람이 필요해요. 소프트웨어 스타트업은 창업팀에 소프트웨어 엔지니어가 필요해요.  
    > 기업가: 맞아요. 기술 공동창업자를 찾는 게 답일 수 있다고 생각했어요. 어떻게 해야 할까요?  
    > 나: 기술 공동창업자 찾기를 그만두세요. **당신이 기술 공동창업자가 되어야 합니다.**
    
- 14년 전 프로그래밍을 시작했을 때는 서점에서 산 물리적 책이나 도서관에서 빌린 커피 얼룩진 입문서에 의존해야 했음
    
    - 반면 오늘날은 인공지능의 황금기로, 기술적 질문에 대한 모든 답변이 손끝에 있음
    - "어떻게 하면 X 또는 Y를 할 수 있을까요?"와 같은 질문뿐만 아니라 "어떻게 시작하죠?"와 같은 높은 수준의 질문도 가능함
    
    > "\[아이디어\]를 만들고 출시하기 위해 어떤 기술을 이해해야 하나요?"  
    > 관계형 데이터베이스요?  
    > "관계형 데이터베이스가 뭐예요?"  
    > 아, 자세히 설명하는 좋은 유튜브 영상이 있네요. "제 아이디어에 맞는 데이터베이스를 설계해주세요."  
    > 그렇게 진행하다 보면...
    
- 누구나 어떤 주제든 배울 수 있고, 그렇게 하기에 결코 늦지 않다고 믿음
    - 중요한 것은 배울 필요가 있다는 것임
    - 내 인생에서 배운 것의 대부분은 정식 교육이나 전문 학위가 필요하지 않았고 전적으로 제 열망에 의해 이루어졌기 때문에 그렇게 믿음
    - 10년 전에는 멘토와 자원에 접근할 수 있었지만, 오늘날 여러분에게 제공되는 멘토와 자원의 일부에 불과함
    - 내가 할 수 있었다면, 당신도 할 수 있음
- 할 수 없다고 생각한다면 자문해 볼 것: **무엇이 두려운가요?**
    - 노력인가요, 시간 투자인가요, 실패 가능성인가요?
    - 그런 것들 중 하나라도 해당 된다면, 기업가 정신은 당신에게 너무 벅찬 여정일 수 있음
    - 스타트업에 온 마음을 쏟고, 밤낮으로 일하고, 많은 실수를 하는 데 기술적일 필요는 없음
    - 단순히 **배우는 것에 개방적**이기만 하면 됨

[LogLog Games](https://loglog.games/blog/leaving-rust-gamedev/#gui-situation-in-rust-is-terrible)

**Leaving Rust gamedev after 3 years**

내용이 굉장히 길다...

- Rust being great at big refactorings solves a largely self-inflicted issues with the borrow checker
- Indirection only solves some problems, and always at the cost of dev ergonomics
- ECS solves the wrong kind problem

    Because of the way Rust's type system and borrow checker works, ECS comes up as a naturally occurring solution to the problem of "how do we have stuff reference other stuff". Unfortunately, I think there's quite a bit of terminology mixup, and not only do different people mean different things, but also that the large part of the community attributes some things to ECS that aren't actually ECS. Let's try to separate things out.

  - 캐릭터 A 가 캐릭터 B를 따라다니던 중 캐릭터 B가 갑자기 사라져버리면 어떻게 할 것인가?
  - borrowcheck 가 필수인 러스트에서는 이런 경우 포인터를 처리하는게 고달프다.
  - 무엇인가를 참고하는 물건들에 대해서 코드를 작성할 때 애를 많이 먹는 듯

- Generalized systems don't lead to fun gameplay
- Making a fun & interesting games is about rapid prototyping and iteration, Rust's values are everything but that
- Procedural macros are not even "we have reflection at home"
- Hot reloading is more important for iteration speed than people give it credit for
- Abstraction isn't a choice
- GUI situation in Rust is terrible
- Reactive UI is not the answer to making highly visual, unique and interactive game UI
- Orphan rule should be optional
- Compile times have improved, but not with proc macros
- Rust gamedev ecosystem lives on hype
- Global state is annoying/inconvenient for the wrong reasons, games are single threaded.
- Dynamic borrow checking causes unexpected crashes after refactorings
- Context objects aren't flexible enough

## 24.05.22

**작업 이슈**

- 닷넷의 ConcurrentQueue<T>
  - Clear 할 때마다 가비지 생성
  - ring 버퍼 형태의 구조
  - 버퍼는 하나의 배열이 아니라 배열 크기가 32인 Segment 가 여러개 붙어 있는 형태
    - false sharing 을 최소화 하기 위인
    - 큰 배열 하나를 다수의 스레드에서 접근하면 당연히 캐시 미스가 많이 생기겠지
  - Clear 구현의 경우, head/tail 에 해당하는 segment를 얼려 놓고(freeze) 새로운 Segment를 생성해서 할당, 기존 segment는 gc 되도록
    - 무턱대고 Clear를 호출하면 가비지가 엄청 발생한다는 것

[c - Linking Cancellation Tokens - Stack Overflow](https://stackoverflow.com/questions/29623178/linking-cancellation-tokens?newreg=d7d85e7f86f34ed69a90c020738c8625)

I use a cancellation token that is passed around so that my service can be shut down cleanly. The service has logic that keeps trying to connect to other services, so the token is a good way to break out of these retry loops running in separate threads. My problem is that I need to make a call to a service which has internal retry logic but to return after a set period if a retry fails. I would like to create a new cancellation token with a timeout which will do this for me. The problem with this is that my new token isn't linked to the “master” token so when the master token is cancelled, my new token will still be alive until it times-out or the connection is made and it returns.

- cascading cancelling

이렇게 풀라네요

```cs
var parentCts = new CancellationTokenSource();
var childCts = CancellationTokenSource.CreateLinkedTokenSource(parentCts.Token);
        
childCts.CancelAfter(1000);
Console.WriteLine("Cancel child CTS");
Thread.Sleep(2000);
Console.WriteLine("Child CTS: {0}", childCts.IsCancellationRequested);
Console.WriteLine("Parent CTS: {0}", parentCts.IsCancellationRequested);
Console.WriteLine();
        
parentCts.Cancel();
Console.WriteLine("Cancel parent CTS");
Console.WriteLine("Child CTS: {0}", childCts.IsCancellationRequested);
Console.WriteLine("Parent CTS: {0}", parentCts.IsCancellationRequested);
```

Output as expected:

    Cancel child CTS
    Child CTS: True
    Parent CTS: False
    
    Cancel parent CTS
    Child CTS: True
    Parent CTS: True

**False Sharing(with ChatGPT4)**

False sharing은 멀티스레딩 환경에서 개별 스레드가 공유 데이터를 수정할 때 CPU 캐시 라인의 비효율적인 사용으로 발생하는 성능 저하 현상입니다. 각 CPU 코어는 데이터를 캐시 라인(대개 64바이트) 단위로 캐싱하는데, 서로 다른 스레드가 같은 캐시 라인에 위치한 데이터를 동시에 수정하려고 하면, 캐시 라인이 스레드 간에 불필요하게 전송되어 성능이 저하될 수 있습니다.

> 각 스레드가 배열의 인접한 위치를 수정하는 경우 false sharing이 발생할 수 있습니다.

```cs
public class FalseSharingDemo
{
    private static int[] array = new int[8];

    public static void Main()
    {
        Thread t1 = new Thread(() => UpdateArrayIndex(0));
        Thread t2 = new Thread(() => UpdateArrayIndex(1));

        t1.Start();
        t2.Start();

        t1.Join();
        t2.Join();
    }

    private static void UpdateArrayIndex(int index)
    {
        for (int i = 0; i < 100000000; i++)
        {
            array[index]++;
        }
    }
}
```

캐시 라인이 64바이트라고 가정하고,
만약에 `int[128]` 처럼 크기가 큰 배열이 있다고 하자

배열의 첫 번째 원소와 마지막 원소는 인접해 있지 않으니까, 이 둘을 각각 접근할 때는 false sharing 을 걱정하지 않아도 돼음

>> OK

이번에는 `int[4]` 배열이 여럿 있다고 해보자.
서로 다른 배열 객체에 접근한다고 할때 false sharing 이 발생할 가능성이 있을까?

>> 발생할 수 있음

## 24.05.27

**dotnet System.IO.Pipeline**

[C 고성능 서버 - System.IO.Pipeline 도입 후기  leafbirddevnote](https://leafbird.github.io/devnote/2020/12/27/C-%EA%B3%A0%EC%84%B1%EB%8A%A5-%EC%84%9C%EB%B2%84-System-IO-Pipeline-%EB%8F%84%EC%9E%85-%ED%9B%84%EA%B8%B0/#%EB%8B%A8%EC%A0%90-%EB%84%88%EB%AC%B4-%EB%A7%8E%EC%9D%80-Task%EB%A5%BC-%EC%83%9D%EC%84%B1%ED%95%9C%EB%8B%A4)

> System.IO.Pipeline은 ASP.NET Core의 성능을 크게 끌어올린 네트워크 버퍼 운용 라이브러리다. 이를 적용하면 네트워크 버퍼구현의 여러가지 문제점들과 boilerplate한 구현들을 손쉽게 해결할 수 있으나, 최소 2 tasks/peer를 소켓의 수명만큼 열어두어야 하기 때문에 소켓을 긴 시간 유지하는 타입의 TCP서버라면 도입 전에 신중한 성능 테스트를 거쳐야 한다.

- 장점 : 불필요한 메모리 복사를 없앤다.
- 장점 : 네트워크 버퍼의 고정길이 제약을 없애준다.
- 단점 : 너무 많은 Task를 생성한다.

    위의 두가지 장점만으로 Pipeline의 도입을 시도해볼 가치는 충분했다. 그래서 우리는 게임서버의 수신 버퍼를 Pipeline으로 대체하고, MS Azure 에서 F8s 급 인스턴스 수십대를 동원해 10만 동접 스트레스 테스트를 진행해 보았다.

    결과는 기대와 완전히 달랐는데.. Pipeline 도입 전보다 영 더 못한 성능을 보여줬다. 이건 뭐… cpu 사용량이 높고 낮아지는 것이 문제가 아니라, 동접이 일정수치 이상 오르면 서버가 아무 일도 처리하지 않고 멈춰버렸다. 반응없는 프로세스에서 덤프를 떠서 디버거로 살펴보면… 대기상태인 스레드가 잔뜩 생겨있고, 일해야 할 스레드가 부족해서 추가 스레드를 계속해서 만들어내고 있는 것처럼 보였다.

    원인은 Pipeline과 함께 사용하는 task (System.Threading.Tasks.Task) 들이었다. class Pipe 인스턴스 하나를 쓸 때마다 파이프라인에 ‘읽기’와 ‘쓰기’를 담당하는 class Task 객체 두 개를 사용하게 된다. 수신버퍼에만 Pipe를 달면 소켓의 2배, 송수신 버퍼에 모두 달면 소켓의 4배수 만큼의 task가 생성 되어야 하기 때문이다. 게임서버 프로세스당 5,000 명의 동접을 받는다고 하면 최대 20,000개의 task가 생성되고, 이 중 상당수는 waiting 상태로 IO 이벤트를 기다리게 된다.

    task가 아무리 가볍다고 해도 네트워크 레이어에만 몇 만개의 task를 만드는 것은 그리 효율적이지 않다. TPL에 대한 이야기를 시작하면 해야 할 말이 아주 많기 때문에 별도의 포스팅으로 분리해야 할 것이다. 과감히 한 줄로 정리해보면, task는 상대적으로 OS의 커널오브젝트인 스레드보다 가볍다는 것이지 수천 수만개를 만들만큼 깃털같은 물건은 아닌 것이다.


[https://devblogs.microsoft.com/dotnet/system-io-pipelines-high-performance-io-in-net/](https://devblogs.microsoft.com/dotnet/system-io-pipelines-high-performance-io-in-net/)

이런 저런 데모 코드를 보여주는데,

- ArrayPool을 활용하는 코드에서 주의 사항
  - The byte[] we’re using from the ArrayPool<byte> are just regular managed arrays. This means whenever we do a ReadAsync or WriteAsync, those buffers get pinned for the lifetime of the asynchronous operation (in order to interop with the native IO APIs on the operating system). This has performance implications on the garbage collector since pinned memory cannot be moved which can lead to heap fragmentation. Depending on how long the async operations are pending, the pool implementation may need to change.
- Back Pressure 와 Flow Control
  - '소켓에서 받은 데이터를 버퍼에서 읽을 때 부하 < 읽은 데이터를 파싱할 때 부하'
  - read 동작을 수행하는 스레드가 가져오는 데이터를, parsing 스레드가 따라잡지를 못한다.
  - In a perfect world, reading & parsing work as a team: the reading thread consumes the data from the network and puts it in buffers while the parsing thread is responsible for constructing the appropriate data structures. Normally, parsing will take more time than just copying blocks of data from the network. As a result, the reading thread can easily overwhelm the parsing thread. The result is that the reading thread will have to either slow down or allocate more memory to store the data for the parsing thread. For optimal performance, there is a balance between frequent pauses and allocating more memory.
  - To solve this problem, the pipe has two settings to control the flow of data, the PauseWriterThreshold and the ResumeWriterThreshold. The PauseWriterThreshold determines how much data should be buffered before calls to PipeWriter.FlushAsync pauses. The ResumeWriterThreshold controls how much the reader has to consume before writing can resume.

**DecoratorPattern**

[The Decorator Pattern in Modern C 2024](https://blog.postsharp.net/decorator-pattern)

- metalama
- [Metalama A Framework for Clean & Concise Code in C](https://www.postsharp.net/metalama#concept)
- 인터페이스 의존성 없이 method 로만 decorator 패턴을 구성하는 솔루션

![](img/2024-05-27-18-43-05.png)

[microsoftMicrosoft.IO.RecyclableMemoryStream A library to provide pooling for .NET MemoryStream objects to improve application performance.](https://github.com/microsoft/Microsoft.IO.RecyclableMemoryStream)

> Microsoft.IO.RecyclableMemoryStream is a MemoryStream replacement that offers superior behavior for performance-critical systems. In particular it is optimized to do the following:

    Eliminate Large Object Heap allocations by using pooled buffers
    Incur far fewer gen 2 GCs, and spend far less time paused due to GC
    Avoid memory leaks by having a bounded pool size
    Avoid memory fragmentation
    Allow for multiple ways to read and write data that will avoid extraneous allocations
    Provide excellent debuggability and logging
    Provide metrics for performance tracking

```cs
class Program
{
    private static readonly RecyclableMemoryStreamManager manager = new RecyclableMemoryStreamManager();

    static void Main(string[] args)
    {
        var sourceBuffer = new byte[] { 0, 1, 2, 3, 4, 5, 6, 7 };
        
        using (var stream = manager.GetStream())
        {
            stream.Write(sourceBuffer, 0, sourceBuffer.Length);
        }
    }
}
```

## 24.05.31

**캡슐 AmbientOcclusion**

![](img/2024-05-31-11-23-44.png)

- [CS2's Magic Menu](https://youtu.be/sAfC3wHmIeE)
- [Last of Us2's Indirect Shadows](https://youtu.be/9XSWmaXfCJo)
- [Sphere - occlusion](https://www.shadertoy.com/view/4djSDy)

그림자를 드리울 때, 삼각형이 많은 캐릭터 메시를 그대로 사용한다면 무겁다.

캐릭터와 비슷한 크기의 캡슐을 몸에 달게 하고, 캡슐로 간접광 그림자를 표현하는 최적화 기법

## 24.06.03

[YOLO Software Architecture  DevIQ](https://deviq.com/practices/yolo-architecture)

> YOLO Architecture describes a development style characterized by minimal planning, lack of organization, and an absence of clear architectural principles. 

- 욜로 아키텍쳐
- 막 사는 아키텍쳐

## 24.06.04

**UTF8Encoding**

> UTF8Encoding 에서 encoderShouldEmitUTF8Identifier 가 true 일 때와 아닐 때 인코딩 후 어떤 차이가 있어?

UTF8Encoding 클래스에서 EncoderShouldEmitUTF8Identifier 속성의 값에 따라 인코딩 결과에 차이가 있습니다.

- EncoderShouldEmitUTF8Identifier = true
  - 인코딩된 바이트 스트림의 시작 부분에 **BOM(Byte Order Mark)** 문자가 포함됩니다.
  - BOM은 **U+FEFF 코드 포인트**를 가지는 **3바이트 시퀀스(EF BB BF)**입니다.
  - BOM을 사용하면 인코딩 방식을 쉽게 식별할 수 있습니다.
  - 일부 프로그램에서는 BOM을 필요로 하기 때문에 이 경우에 유용합니다.
- EncoderShouldEmitUTF8Identifier = false
  - 인코딩된 바이트 스트림에 BOM 문자가 포함되지 않습니다.
  - 순수한 UTF-8 인코딩된 데이터만 포함됩니다.
  - 파일 크기가 약간 작아질 수 있습니다.
  - 일부 프로그램에서는 BOM이 필요 없기 때문에 이 경우에 선호될 수 있습니다.

예를 들어, 문자열 "Hello, 世界!"를 인코딩한다고 가정하면:

- EncoderShouldEmitUTF8Identifier = true인 경우 EF BB BF 48 65 6C 6C 6F 2C 20 E4 B8 96 E7 95 8C 21 와 같은 바이트 시퀀스가 생성됩니다.
- EncoderShouldEmitUTF8Identifier = false인 경우 48 65 6C 6C 6F 2C 20 E4 B8 96 E7 95 8C 21 와 같은 바이트 시퀀스가 생성됩니다.
- 대부분의 경우 EncoderShouldEmitUTF8Identifier = false가 더 적절할 것 같지만, 특정 프로그램에서 BOM이 필요한 경우에는 true로 설정하는 것이 좋습니다.

## 24.06.06

**완전 랜덤 커스터마이징**

게임 커스커 마이징 절차 중에서 '헤어스타일', '문신', '체형' 의 데이터 목록이 있다면, 

- 이 중에서 완전 랜덤으로 선택하는 것
- 최초 프리셋을 일부 선별하고 이 중에서 랜덤 선택하는 것

> 어쩌다가 굉장히 독특한 개성의 프리셋이 커스터마이징 화면에서 처음부터 나오면, 평범한 외형을 선호하는 대부분의 유저들은 당혹스러워 할 것이고, 독특한 외형을 선호하는 유저들의 경우 처음부터 이런 모습을 보여주면 기대치가 떨어지게 될 수 있음.(이런 유저의 경우에는 직접 커스터마이징 툴을 만져보면서 발견해나가게 해야 함. 랜덤 선택으로부터 극단적인 예시 & 강렬한 인상을 줘버리면 부작용이 생긴다.)
>
> 문신같은 후천적인 요소도 초기 프리셋에서는 “없음”이 선택되어 있으면 좋겠습니다. 커스터마이징은 게임 내에서 새롭게 태어나는 사람을 고르는 기분이 드는데, 문신을 처음부터 가지고 태어나는 사람은 없으니 기본적으로는 선택적 요소가 되어야 할 것 같습니다.
>
> 미리 선택된 프리셋은 대부분의 사람들이 생성할 것 같은 외형을 모조리 합친 다음 평균낸 듯한 “최대한 아무런 특징이 없는 것 같은 외모”면 좋겠습니다. (우리 게임은 커스터마이징이 그렇게 어렵진 않지만) 평균값에서 조금씩 깍아서 내가 원하는 외모를 만드는 것이 극단적 형태에서부터 시작하는 것보다 쉽기 때문입니다.

[C#/.NET Method Call Performance - Facts](https://www.aloneguid.uk/posts/2021/05/csharp-method-call-performance/)

```cs
#LINQPad optimize+

Util.AutoScrollResults = true;
	BenchmarkRunner.Run<MethodCalls>();

[ShortRunJob]
[MinColumn, MaxColumn, MeanColumn, MedianColumn]
[MemoryDiagnoser]
[MarkdownExporter]
public class MethodCalls
{
	private MethodsContainer _c = new MethodsContainer();
	private static Func<int, int> _staticLambda = MethodsContainer.StaticMethod;
	
	[Benchmark]
	public int Static() => MethodsContainer.StaticMethod(1);
	[Benchmark]
	public int StaticViaLambda() =>  _staticLambda(1);
	[Benchmark]
	public async Task<int> StaticAsync()=> await MethodsContainer.StaticAsyncMethod(1);
	[Benchmark]
	public int Dynamic() => _c.DynamicMethod(1);
	[Benchmark]
	public async Task<int> DynamicAsync() => await _c.DynamicAsyncMethod(1);
	[Benchmark]
	public int Virtual() => _c.VirtualMethod(1);
	[Benchmark]
	public async Task<int> VirtualAsync() => await _c.VirtualAsyncMethod(1);
}

public class MethodsContainer
{
	public static int StaticMethod(int arg) { return arg * 2; }
	public static Task<int> StaticAsyncMethod(int arg) { return Task.FromResult<int>(arg * 2); }
	public int DynamicMethod(int arg) { return arg * 2; }
	public Task<int> DynamicAsyncMethod(int arg) { return Task.FromResult<int>(arg * 2); }
	public virtual int VirtualMethod(int arg) { return arg * 2; }
	public virtual Task<int> VirtualAsyncMethod(int arg) { return Task.FromResult<int>(arg * 2); }
}
```

| Method          | Mean      | Error     | StdDev    | Min       | Max       | Median    | Gen 0     | Gen 1 | Gen 2 | Allocated |
|-----------------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|-------|-----------|
| Static          | 0.1086 ns | 0.6070 ns | 0.0333 ns | 0.0835 ns | 0.1464 ns | 0.0960 ns | -         | -     | -     | -         |
| StaticViaLambda | 4.1860 ns | 1.1548 ns | 0.0633 ns | 4.1383 ns | 4.2578 ns | 4.1619 ns | -         | -     | -     | -         |
| StaticAsync     | 20.0131 ns| 31.6018 ns| 1.7322 ns | 18.0743 ns| 21.4084 ns| 20.5566 ns| 0.0172    | -     | -     | 72 B      |
| Dynamic         | 0.4950 ns | 0.6165 ns | 0.0338 ns | 0.4564 ns | 0.5189 ns | 0.5098 ns | -         | -     | -     | -         |
| DynamicAsync    | 17.9998 ns| 16.0884 ns| 0.8819 ns | 17.4451 ns| 19.0167 ns| 17.5376 ns| 0.0172    | -     | -     | 72 B      |
| Virtual         | 0.6042 ns | 0.3357 ns | 0.0184 ns | 0.5860 ns | 0.6228 ns | 0.6038 ns | -         | -     | -     | -         |
| VirtualAsync    | 20.8322 ns| 5.6442 ns | 0.3094 ns | 20.4769 ns| 21.0419 ns| 20.9778 ns| 0.0172    | -     | -     | 72 B      |


1. Static methods are 6 times faster than normal instance methods.
2. Static lambda call is 38 times slower than static method call.

Why? This is really odd, but not when you look at generated IL. Here’s one for static method call:
```
MethodCalls.Static:
IL_0000:  ldc.i4.1    
IL_0001:  call        UserQuery+MethodsContainer.StaticMethod
IL_0006:  ret   
```
and for static lambda:
```
MethodCalls.StaticViaLambda:
IL_0000:  ldsfld      UserQuery+MethodCalls._staticLambda
IL_0005:  ldc.i4.1    
IL_0006:  callvirt    System.Func<System.Int32,System.Int32>.Invoke
IL_000B:  ret  
```

As you can see call is replaced with callvirt - so static lambda is actually treated as virtual method call. Thus we have an overhead of ldsfld loading wrapper instance as well.

3. Static methods are 68 times faster than virtual methods.
4. Virtual methods are 10.5 times slower than instance methods. Makes you think to carefully choose which methods should be virtual.
5. Async calls allocate 72 bytes of memory, regardless of method signature. Normal methods have no impact on memory allocations.
6. Regardless of method signature, all of the async method calls are really slow.

## 24.06.12

[StringBuilders magic for very large strings](chrome-extension://hajanaajapkhaabfcofdjgjnlgkdkknm/)

```cs
[MemoryDiagnoser]
public class StringBenchmark
{
    private readonly StringBuilder stringBuilder = new();
    private readonly List<string> list = new();
    private const int IterationCount = 1000;
    private const string TenCharacters = "0123456789";
    
    [Benchmark]
    public string StringBuilder()
    {
        for (var i = 0; i < IterationCount; i++)
        {
            stringBuilder.Append(TenCharacters);
        }

        return stringBuilder.ToString();
    }
    
    [Benchmark]
    public string List()
    {
        for (var i = 0; i < IterationCount; i++)
        {
            list.Add(TenCharacters);
        }

        return string.Concat(list);
    }
}
```

- 열글자 (tenCharacters) 1,000 개를 이어붙일 때

| Method        | Mean     | Error     | StdDev    | Gen0   | Gen1   | Gen2   | Allocated |
|-------------- |---------:|----------:|----------:|-------:|-------:|-------:|----------:|
| StringBuilder | 2.613 us | 0.0142 us | 0.0126 us | 6.3477 | 0.3967 |      - |  51.95 KB |
| List          | 6.969 us | 0.0320 us | 0.0283 us | 4.3716 | 0.0229 | 0.0076 |  35.81 KB |

- 백글자 (oneHundredCharacters) 10,000 개를 이어붙일 때

| Method        | Mean     | Error    | StdDev   | Gen0      | Gen1      | Gen2     | Allocated |
|-------------- |---------:|---------:|---------:|----------:|----------:|---------:|----------:|
| StringBuilder | 553.3 us | 17.36 us | 51.20 us |  696.2891 |  696.2891 | 210.9375 |   3.83 MB |
| List          | 652.8 us | 16.35 us | 48.22 us | 1030.2734 | 1018.5547 | 998.0469 |   6.15 MB |

- string 이 짧은 경우 List가 메모리 효율적이지만, 특정 수치 이상으로 길어진다면 어느 순간부터 stringBuilder가 더 효율적이다.
- 이유는 List는 하나의 배열이기 때문에 덩치가 커지면서 버퍼 사이즈를 넘어서면 재할당 발생.
- 그렇지만 StringBuilder는 내부적으로 LinkedList 구조이다. 하나의 버퍼 사이즈가 충분히 커지면 또 다른 StringBuilder를 만드는 것
- Gen2 GC 의 경우도 마찬가지, List는 일체형 배열이기 때문에, 8byte * 10,000 = 대략 80Kbyte => LOH(Large Object Heap) 으로 이동할 정도로 충분히 커진다. stringBuilder 보다 Gen2 GC를 더 차지하는 셈

[Multitasking, parallel processing, and concurrency in Swift – The Eclectic Light Company](https://eclecticlight.co/2024/06/10/multitasking-parallel-processing-and-concurrency-in-swift/)

    In computers with a single processor core, multitasking was a way of cheating to give the impression that the processor was doing several things at once, when in fact all it was doing was switching rapidly between two or more different programs. There are two fundamental models for doing that:
    
    - cooperative multitasking, in which individual tasks yield to give others processing time;
    - preemptive multitasking, in which a scheduler switches between tasks at regular intervals.
    
    When a processor switches from one task to the next, the current task state must be saved so that it can be resumed later. Once that’s complete, the next task is loaded to complete what’s known as a context switch. That incurs overhead, both in terms of processing and in memory storage. Inevitably, switching between lightweight tasks has less overhead. There have been different strategies adopted to determine the optimum size of tasks and overhead imposed by context switching, and terminology differs between them, variously using words such as processes, threads and even fibres, which can prove thoroughly confusing.

## 24.06.16

ChatGPT 만담

**URL Tempering에 대해**

URL tempering은 웹 애플리케이션 보안 위협 중 하나로, 사용자가 URL을 조작하여 서버가 의도하지 않은 동작을 하게 만드는 것을 말합니다. 이는 주로 인증되지 않은 액세스, 데이터 노출, 무단 변경 등을 초래할 수 있습니다. URL tempering의 주요 유형과 방지 방법에 대해 설명하겠습니다.

#### 주요 유형

1. **매개변수 조작 (Parameter Tampering)**: URL의 쿼리 매개변수를 변경하여 서버에 잘못된 데이터를 전송합니다. 예를 들어, 사용자가 자신의 계정 정보에 접근하기 위해 `user_id=123`을 `user_id=456`으로 변경할 수 있습니다.

2. **디렉토리 트래버설 (Directory Traversal)**: URL의 경로를 조작하여 웹 루트 디렉토리 외부의 파일에 접근하려고 시도합니다. 예를 들어, `/app/docs/../etc/passwd`와 같은 URL을 사용하여 서버의 중요한 파일에 접근할 수 있습니다.

3. **IDOR (Insecure Direct Object Reference)**: 사용자가 직접 객체를 참조할 수 있는 URL을 조작하여 권한이 없는 데이터를 액세스합니다. 예를 들어, `/profile/123`을 `/profile/456`으로 변경하여 다른 사용자의 프로필에 접근할 수 있습니다.

## 24.06.17

[C Array and List Fastest Loop in 2024 - NDepend Blog](https://blog.ndepend.com/c-array-and-list-fastest-loop/)

> We listed the key findings in the introduction. Let’s conclude that future versions of .NET and C# might change these results. For example, in the future, the C# compiler might assert that a list doesn’t get modified and use the Span<T> based optimization. We will update this post regularly to find out.

```cs
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;
 
BenchmarkRunner.Run<Benchmarks>();
 
public class Benchmarks {
 
   [Params(100, 1_000, 10_000)]
   public int Length { get; set; }
   private void AssertResult(int result) {
      if (result != (Length * (Length - 1)) / 2) {
         Environment.FailFast("");
      }
   }
 
   private int[] m_Items;
 
   [GlobalSetup]
   public void Setup() {
      m_Items = Enumerable.Range(0, Length).ToArray();
   }
 
   [Benchmark]
   public void ForLoop() {
      int result = 0;
      for (int i = 0; i < m_Items.Length; i++) {
         result += m_Items[i];
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForLoop_LengthAsVariable() {
      int result = 0;
      int length = m_Items.Length;
      for (int i = 0; i < length; i++) {
         result += m_Items[i];
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForeachLoop() {
      int result = 0;
      foreach (int item in m_Items) {
         result += item;
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ArrayForEach() {
      int result = 0;
      Array.ForEach(m_Items, item => {
         result += item;
      });
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForSpanLoop() {
      int result = 0;
      Span<int> span = m_Items;
      for (int i = 0; i < span.Length; i++) {
         result += span[i];
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForSpanLoop_LengthAsVariable() {
      int result = 0;
      Span<int> span = m_Items;
      int length = span.Length;
      for (int i = 0; i < length; i++) {
         result += span[i];
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForSpanRefLoop() {
      int result = 0;
      Span<int> span = m_Items;
      ref int ptr = ref MemoryMarshal.GetReference(span);
      for (int i = 0; i < span.Length; i++) {
         int item = Unsafe.Add(ref ptr, i);
         result += item;
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForSpanRefLoop_LengthAsVariable() {
      int result = 0;
      Span<int> span = m_Items;
      ref int ptr = ref MemoryMarshal.GetReference(span);
      int length = span.Length;
      for (int i = 0; i < length; i++) {
         int item = Unsafe.Add(ref ptr, i);
         result += item;
      }
      AssertResult(result);
   }
 
   [Benchmark]
   public void ForSpanRefLoop2() {
      int result = 0;
      Span<int> span = m_Items;
      ref int start = ref MemoryMarshal.GetReference(span);
      ref int end = ref Unsafe.Add(ref start, m_Items.Length);
 
      while (Unsafe.IsAddressLessThan(ref start, ref end)) {
         result += start;
         start = ref Unsafe.Add(ref start, 1);
      }
      AssertResult(result);
   }
}
```

- foreach 가 for 보다 빠르다.
  - foreach 의 경우 jit 컴파일러가 불필요한 검증을 패싱하도록 최적화 되어 있음
- List<T> 의 경우 for 루프가 foreach 보다 빠르다.
  - foreach loop 는 List<T> 가 중간에 수정될 수 있음을 고려했기 때문
  - Enumerator 가 사용된다.
- Span<T> 를 사용하는 경우. T[] 와는 동일하지만, List<T> 보다는 빠르다.

![](img/2024-06-17-01-47-18.png)

## 24.06.20

[Why Your SSD (Probably) Sucks and What Your Database Can Do About It  CedarDB - The All-In-One-Database](https://cedardb.com/blog/ssd_latency/)

- 대충 운영체제가 디스크에 쓰기 명령을 할 때, 쓰기 큐를 먼저 거친다는 것
- 쓰기 큐에 입력되는 시간만 두고 볼 때 딜레이는 짧은 편이지만, 실제 디스크에 저장될 때까지의 시간을 보면 마이크로(micro) -> 밀리(milli) 초 단위를 왔다갔다 하는 정도

**ChatGPT 만담 SSD 쓰기 큐**

**쓰기 큐의 역할**

1. **쓰기 병합**:
   - SSD는 쓰기 작업을 병합하여 성능을 최적화합니다. 여러 개의 작은 쓰기 작업을 모아서 한 번에 큰 쓰기 작업으로 처리하면 쓰기 성능이 향상되고, SSD의 수명도 연장됩니다.

2. **쓰기 순서 최적화**:
   - SSD는 플래시 메모리 셀의 특성상 랜덤 쓰기보다 순차 쓰기에 더 적합합니다. 쓰기 큐를 통해 쓰기 명령을 재정렬하여 순차적으로 처리함으로써 성능을 최적화할 수 있습니다.

3. **내구성 향상**:
   - SSD는 쓰기 작업을 고르게 분배하여 특정 셀에 과도한 쓰기 작업이 집중되지 않도록 합니다. 이를 통해 플래시 메모리의 수명을 연장할 수 있습니다.

4. **플래시 변환 계층(FTL)**:
   - SSD의 플래시 변환 계층은 논리적 주소를 물리적 주소로 매핑하는 작업을 수행합니다. 이 과정에서 쓰기 큐를 사용하여 쓰기 명령을 최적화하고, 가비지 컬렉션 등의 내부 관리 작업을 효율적으로 처리합니다.

**데이터 내구성 보장**

운영 체제나 파일 시스템이 `write()` 명령을 실행하면, SSD 내부의 쓰기 큐에 의해 실제 쓰기 작업이 지연될 수 있습니다. 이 때문에 시스템이 충돌하면 데이터가 물리적 저장 매체에 아직 기록되지 않았을 수 있습니다. 이러한 이유로 데이터베이스 시스템은 다음과 같은 추가적인 메커니즘을 사용하여 데이터의 내구성을 보장합니다.

1. **플러시 명령**:
   - `fsync()`나 `fdatasync()` 같은 명령을 사용하여 운영 체제 버퍼와 SSD의 쓰기 큐를 비워 실제로 데이터를 디스크에 기록하도록 합니다.

2. **저널링**:
   - 데이터베이스는 쓰기 작업 전에 로그(저널)에 기록하여, 시스템 충돌 시 복구할 수 있도록 합니다. 이 로그는 커밋된 데이터가 실제로 저장되었는지 확인하는 데 사용됩니다.

3. **배터리 백업 캐시**:
   - 일부 고급 SSD는 전원 손실 시에도 데이터를 보호하기 위해 배터리 백업 DRAM 캐시를 사용합니다. 이 캐시는 전원 복구 후 데이터를 플래시 메모리에 기록할 수 있습니다.

결론적으로, SSD에도 쓰기 큐가 있으며, 이를 통해 성능과 내구성을 최적화합니다. 그러나 데이터의 내구성을 보장하기 위해서는 추가적인 메커니즘이 필요합니다. 데이터베이스 시스템은 이러한 메커니즘을 통해 ACID 속성의 "D"를 보장합니다.

[(239) 지금! 🚨 개발자라면 무조건 알아야하는 NPM 해킹](https://www.youtube.com/watch?v=DjfpcmK62ew&list=WL&index=5)

- [npm left-pad incident](https://en.wikipedia.org/wiki/Npm_left-pad_incident)
- [Supply chain attack](https://en.wikipedia.org/wiki/Supply_chain_attack)
  - 복잡하게 얽혀있는 패키지 디펜던시 그래프 중에서, 가장 보안이 약한 마이너한 패키지를 공략. 여기서 보안 이슈가 발생하면 해당 패키지에 의존하는 다른 모든 패키지에 악영향이 가게 됨

**`left-pad` 이슈 설명**

`left-pad`는 JavaScript 개발자들 사이에서 널리 사용되는 npm 패키지였습니다. 이 패키지는 문자열의 왼쪽에 특정 문자를 추가하여 원하는 길이로 문자열을 확장하는 간단한 기능을 제공했습니다. 예를 들어, 문자열을 일정 길이로 만들기 위해 공백이나 '0' 같은 문자를 추가하는 데 사용될 수 있습니다.

> 굉장히 간단한 코드 였다.

![](img/ma2024-06-20-22-53-38.png)

**`left-pad` 이슈의 발생**
2016년, `left-pad` 패키지의 개발자 Azer Koçulu는 npm과 이름 충돌 문제로 분쟁을 겪었습니다. 이로 인해 Koçulu는 자신이 관리하는 모든 npm 패키지를 npm 레지스트리에서 삭제하기로 결정했습니다. 이 중 하나가 `left-pad`였고, 당시 `left-pad`는 많은 인기 있는 라이브러리와 프로젝트에서 사용되고 있었습니다.

**영향**
`left-pad`의 삭제는 즉각적인 영향을 미쳤습니다. `left-pad`를 의존성으로 가진 수천 개의 프로젝트가 빌드 실패를 경험했으며, 이는 전 세계 개발자 커뮤니티에서 큰 혼란을 야기했습니다. 이 사건은 단일 패키지가 전체 생태계에 미치는 영향의 규모와 소프트웨어 의존성 관리의 중요성을 강조했습니다.

**결과 및 교훈**
이 사건 이후 npm은 패키지의 무단 삭제가 다른 사용자에게 미치는 영향을 방지하기 위해 정책을 강화했습니다. 또한, 많은 개발자들이 패키지 의존성을 더 신중하게 관리할 필요성을 인식하게 되었습니다.

`left-pad` 이슈는 소프트웨어 개발에 있어 오픈 소스 프로젝트의 의존성 관리와 커뮤니티 내 의사소통의 중요성을 잘 보여주는 사례로 남아 있습니다.

- [Expert grabs expired domain for NPM package to make a point • The Register](https://www.theregister.com/2022/05/10/security_npm_email/)
- 다운로드 수 6백만 회에 달하는 패키지. 보안 스캔들
  - NPM foreach 라이브러리의 관리자 이메일이 커스텀 도메인의 계정 -> 그런데 대상 커스텀 도메인이 만료 날짜가 되고 해당 도메인이 매물로 나왔는데 한 보안 전문가가 이 도메인을 사버리고 자칫하면 악성 해커가 관리자 계정을 훔칠 수 도 있었다며 경고함

- [Typosquatting](https://en.wikipedia.org/wiki/Typosquatting)
- > Typosquatting, also called URL hijacking, a sting site, a cousin domain, or a fake URL, is a form of cybersquatting, and possibly brandjacking which relies on mistakes such as typos made by Internet users when inputting a website address into a web browser. A user accidentally entering an incorrect website address may be led to any URL, including an alternative website owned by a cybersquatter.
- 유명한 사이트 도메인과 한 글자 차이나는 url 을 수도 없이 준비. 재수 없는 사람이 실수로 오타를 입력해서 엉뚱한 사이트로 들어갔다가 실제 사이트와 똑같은 모습에 속고 로그인 계정 /비밀번호를 입력했다가 개인정보가 노출되는 수법. or 악성 프로그램 다운로드

[(239) 애플도 당했다! 최악의 보안사태 "Log4J" 설명해드림. 10분컷.](https://www.youtube.com/watch?v=kwS3twdVsko)

- [Log4j](https://en.wikipedia.org/wiki/Log4j)

> Log4j 취약점, 공식적으로는 CVE-2021-44228로 알려져 있으며, "Log4Shell"이라고도 불립니다. 이 취약점은 Apache Log4j 2 라이브러리에서 발견되었으며, 원격 코드 실행을 허용하는 매우 심각한 보안 결함입니다. 공격자는 로깅 작업 중에 사용자 제어가 가능한 데이터를 이용해 원격 코드 실행을 시도할 수 있습니다.

![](img/2024-06-20-22-41-45.png)
- [Java Naming and Directory Interface](https://en.wikipedia.org/wiki/Java_Naming_and_Directory_Interface)
  - log4j 가 JNDI (Java Naming and Directory Interface) 를 활용. 원격 url 에 연결할 수 있고, 악성 코드를 내부로 가져와서 실행시킬 수 있다.
  - 테슬라 애플도 뚫림
  - 아이폰 이름에 / 와이파이 이름에 위의 이미지 키워드를 입력 시, 해당 애플 쪽 백엔드 시스템이 url 에 접속 시도함
- 마인크래트의 채팅에 입력하면 실행 가능

![](img/2024-06-20-22-44-03.png)

- 제로 데이 취약점
- > A zero-day (also known as a 0-day) is a vulnerability in software or hardware that is typically unknown to the vendor and for which no patch or other fix is available.
- > Despite developers' goal of delivering a product that works entirely as intended, virtually all software and hardware contain bugs. Many of these impair the security of the system and are thus vulnerabilities. Although the basis of only a minority of cyberattacks, zero-days are considered more dangerous than known vulnerabilities because there are fewer countermeasures possible.

## 24.06.24

[Pooling large arrays with ArrayPool – Adam Sitnik – .NET Performance and Reliability](https://adamsitnik.com/Array-Pool/)

- How to use it?

First of all you need to obtain an instance of the pool. You can do in at least three ways:

- Recommended: use the ArrayPool<T>.Shared property, which returns a shared pool instance. It’s thread safe and all you need to remember is that it has a default max array length, equal to 2^20 (1024*1024 = 1 048 576).
- Call the static ArrayPool<T>.Create method, which creates a thread safe pool with custom maxArrayLength and maxArraysPerBucket. You might need it if the default max array length is not enough for you. Please be warned, that once you create it, you are responsible for keeping it alive.
- Derive a custom class from abstract ArrayPool<T> and handle everything on your own.
- Next thing is to call the Rent method which requires you to specify minimum length of the buffer. Keep in mind, that what Rent returns might be bigger than what you have asked for.

```cs
byte[] webRequest = request.Bytes;
byte[] buffer = ArrayPool<byte>.Shared.Rent(webRequest.Length);

Array.Copy(
    sourceArray: webRequest, 
    destinationArray: buffer, 
    length: webRequest.Length); // webRequest.Length != buffer.Length!!
```

**대기큐**

게임 인원 대기

- 특정 서버 접속 인원 수가 한도를 초과하지 못하도록 막는 효과
- 혹은 특정 시간 내에 동작을 수행하는 인원 수를 일정하게 유지하는 효과 (수율: throughput)

[Exploring the generated code ListT and fallback cases](https://andrewlock.net/behind-the-scenes-of-collection-expressions-part-2-exploring-the-generated-code-list-and-fallback-cases/)

```cs
using System.Collections.Generic;

List<int> list = [1, 2, 3, 4, 5];
```

- collection expression 사용 시 `CollectionMarshal` 을 사용한 코드를 자동 생성
  - SharpLab 에서 쉽게 체크해볼 수 있다.
  - https://sharplab.io/#v2:D4AQDABCCMAsDcBYAUCgMgSwM4BcA8GAdjgHwQA22OEAvBANrQA0EATCwMwuwsCsAuvCA===
- List.Add(); 를 다섯 번 호출하는 것보다 빠름

```cs
List<int> list = new List<int>();
CollectionsMarshal.SetCount(list, 3);
Span<int> span = CollectionsMarshal.AsSpan(list);
int num = 0;
span[num] = 1;
num++;
span[num] = 2;
num++;
span[num] = 3;
num++;
```

In this post, I showed how collection expressions can always fallback to collection initializers for types that support them. I also showed how to create your own types to support collection initializers and expressions by implementing IEnumerable and adding an Add() method. Finally I showed how List<T> is optimized for collection expressions by using the .NET 8 API CollectionsMarshal.SetCount(), and how this falls back to collection expressions if you're targeting earlier framework versions.