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