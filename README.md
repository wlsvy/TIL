# TIL
Today I Learned


## C++
- [Effective C++](https://github.com/wlsvy/TIL/tree/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B)
- [Effective STL](https://github.com/wlsvy/TIL/tree/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL)
- [Effective Modern C++](https://github.com/wlsvy/TIL/tree/master/Document/C%2B%2B/Effective%20Modern%20C%2B%2B/EffectiveModernCpp)
- [C++ Type Casting](https://github.com/wlsvy/TIL/blob/master/Document/C++/Cpp%20Type%20Casting.md)
- [C++ Value Category](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/C%2B%2B%20Value%20Category.md)
- [PrependidColon](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/PrependedColon.md)
- [C++ Ios api 정리](https://gist.github.com/wlsvy/329df8104a9b51bd65f6cda0dc2acde4#Category)
- [Cmake Study](https://github.com/wlsvy/CMake_Study)

## C#
- [Effective C#](https://github.com/wlsvy/TIL/tree/master/Document/C%23/Effective%20CSharp/EffectiveCSharp)

## Computer Science
- [컴퓨터 아키텍쳐](https://github.com/wlsvy/TIL/blob/master/Document/ComputerScience/ComputerArchitecture.md)
- [OS](https://github.com/wlsvy/TIL/blob/master/Document/ComputerScience/OperatingSystem.md)

## Graphics
- [2020 DirectX 개인 프로젝트 정리](https://github.com/wlsvy/TIL/blob/master/Document/Graphics/2020_DirectX_Project.md)
- [DirectX OpenGL 차이점](https://github.com/wlsvy/TIL/blob/master/Document/Graphics/DirectX_OpenGL_Difference.md)

## ETC
 - [기술면접 참고 자료](https://github.com/wlsvy/TIL/blob/master/Document/InterviewPreparation/tech-interview-Reference.md)

# Coding Problem Solving

<details>
<summary>List</summary>

문제 | 분류 | 설명 | 해답 코드  
|---|---|---|---|
[소수 만들기](https://programmers.co.kr/learn/courses/30/lessons/12977), [소수 찾기](https://programmers.co.kr/learn/courses/30/lessons/12921#) | 소수 | 앞으로 소수 관련 문제 풀때 참조합시다. | [MakePrime](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/MakePrime.cpp), [FindPrime](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/FindPrime.cpp)
[KnightL on a Chessboard](https://www.hackerrank.com/challenges/knightl-on-chessboard/problem) | BFS, 중급 | 체스판 한쪽 끝에서 반대편 끝까지 체스말(나이트Knight)를 최소 몇 번 안에 이동시킬 수 있는지 찾기 | [KnightL on a Chessboard](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KnightL%20on%20a%20Chessboard.md)
[Friend Circle Queries](https://www.hackerrank.com/challenges/friend-circle-queries/problem) | UnionFind, 중급 | 여러 사람들 중 악수한 사람끼리 이어진 그룹의 크기 구하기 | [Friend Circle Queries](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Friend%20Circle%20Queries.cpp)
[Connected Cells in a Grid](https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem) | DFS, 그래프, 중급 | 조건을 만족하는 인접한 셀(cell) 연결된 총 갯수 구하기 | [Connected Cells in a Grid](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Connected%20Cells%20in%20a%20Grid.cpp)
[Cut the Tree](https://www.hackerrank.com/challenges/cut-the-tree/problem) | DFS, 그래프, 중급 | 노드로 이루어진 트리의 특정 선분을 잘랐을 때 분할된 트리 노드의 가중치 합 구하기, DFS 응용. 재귀 함수 호출 할때 깊이 들어가면서 가중치 합을 연산하는 것이 아닌, 함수 호출이 끝나고 빠져나오면서 연산하는 것이 포인트 | [Cut the Tree](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Cut%20the%20Tree.cpp)
[Count Luck](https://www.hackerrank.com/challenges/count-luck/problem) | DFS, 미로 | 미로의 목적지에 도달할 때 까지 마주친 갈림길의 수 구하기 | [Count Luck](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Count%20Luck.cpp)
[Synchronous Shopping](https://www.hackerrank.com/challenges/synchronous-shopping/problem) | BFS, 다익스트라 | BFS 고난도 문제, 두 마리의 고양이가 상점가를 돌면서 종류별로 생선을 구한다. 두 마리 고양이가 목적지에서 만날 때까지 두 마리 고양이의 이동거리 중 최대값 구하기 | [Synchronous Shopping](https://gist.github.com/wlsvy/e0602509012c0d794f4164a3b4a13e4d)
[Minimum Loss](https://www.hackerrank.com/challenges/minimum-loss/problem) | 정렬 | 배열의 원소 중, A - B 가 음수이면서 그 절대값 차이가 제일 작을 때의 값 찾기 | [Minimum Loss](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Minimum%20Loss.cpp)
[Matrix Layer Rotation](https://www.hackerrank.com/challenges/matrix-rotation-algo/problem) | 이중 배열, 테두리 회정 | 이중 배열의 원소들을 반시계 방향으로 회전 | [Matrix Layer Rotation](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Matrix%20Layer%20Rotation.cpp)  + [이중 배열을 회전시키는 방법들](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/RotateMatrix.cpp)
[Snakes and Ladders](https://www.hackerrank.com/challenges/the-quickest-way-up/problem) | BFS | 뱀과 사다리 게임, 시작 지점에서 도착 지점에 도달하기 까지 주사위를 최소 몇 번 던져야 하는지 구하기, 주사위 면에 따른 BFS 분기를 활용하는 것이 포인트 | [Snakes and Ladders](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Snakes%20and%20Ladders_QuickWay.cpp)
[Red Knight's Shortest Path](https://www.hackerrank.com/challenges/red-knights-shortest-path/problem) | BFS 응용 <br>경로 기록 <br>중복 경로 처리 <br>체스 | 체스말 옮기기, 시작 지점에서 도착 지점 까지 도달하기 위한 최소 이동 횟수 및 목적지까지 이동한 방향 출력, 그리고 중복되는 경로가 존재하면 규칙에 따라 우선순위에 높은 경로를 선택. | [Red Knight's Shortest Path](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Red%20Knight's%20Shortest%20Path.cpp)
[Short Palindrome](https://www.hackerrank.com/challenges/short-palindrome/problem) | DP <br>문자열 | (난이도 어려움) 특정 문자열에서 조건을 만족하는 경우의 수 찾기.<br> (0 <= a < b < c < d < 문자열 길이, str[a] == str[d] && str[b] == str[c]) | [Short Palindrome](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Short%20Palindrome.cpp)
[Prim's (MST) : Special Subtree](https://www.hackerrank.com/challenges/primsmstsub/problem) | Prim <br>그래프 | 최소 신장 트리를 구하는 prim 알고리즘 작성 | [Prim_MST](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Prim_MST.cpp)
[Kruskal (MST): Really Special Subtree](https://www.hackerrank.com/challenges/kruskalmstrsub/problem) | Kruskal, <br>UnionFind, <br>그래프 | 최소 신장 트리를 구하는 kruskal 알고리즘 작성 | [Kruskal_MST](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Kruskal_MST.cpp)
[Dijkstra: Shortest Reach 2](https://www.hackerrank.com/challenges/dijkstrashortreach/problem?h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen) | 다익스트라, <br>최소길이, <br>그래프 | 시작 노드를 기준으로 다른 노드까지 최소 거리를 구하는 다익스트라 알고리즘 작성 | [Dijkstra](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Dijkstra.cpp)
[문자열 압축](https://programmers.co.kr/learn/courses/30/lessons/60057?language=cpp) | 문자열<br>카카오 | 문자열 압축 알고리즘 작성, 예외처리가 까다로운 문제<br>압축 숫자 자릿 수(0, 10 차이), 초기 위치 관련, 압축되지 않는 나머지 문자열 예외처리 | [StringCompression](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_StringCompression.cpp)
[후보키](https://programmers.co.kr/learn/courses/30/lessons/42890#) | 카카오, 비트연산 | 관계형 데이터 테이블에서 후보키 찾기 | [CandidateKey](https://gist.github.com/wlsvy/119e26a6d211f95188736f3021d45d94)
[무지의 먹방 라이브](https://programmers.co.kr/learn/courses/30/lessons/42891#) | 카카오 |  | [EatingShow](https://gist.github.com/wlsvy/05b6468833bca4a52852faf51803bee5)
[괄호 변환](https://programmers.co.kr/learn/courses/30/lessons/60058) | 문자열,<br>괄호처리,<br>카카오 | 괄호 처리 알고리즘 작성 + 괄호 유효성 검사 | [ChangeParenthesis](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_ChangeParenthesis.cpp)
[자물쇠와 열쇠](https://programmers.co.kr/learn/courses/30/lessons/60059) | 이중배열 회전,<br>카카오 | key 와 lock 이중배열에 대해서, key를 이동시키거나 회전시켜서 lock 에 딱 맞출 수 있는지 구하기 | [Lock](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_Lock.cpp)
[가사 검색](https://programmers.co.kr/learn/courses/30/lessons/60060) | 트라이(Trie),<br> 문자열 검색,<br>카카오 | 쿼리(ex : st????)에 대해서 조건을 만족하는 문자열 갯수 찾기<br> - 쿼리와 동일한 길이 <br> - 쿼리의 ?를 제외한 문자는 전부 동일 | [StringSearch](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_StringSearch.cpp)
[Goodland Electricity](https://www.hackerrank.com/challenges/pylons/problem) | 그리디,<br> 배열 응용 | 특정 도시들의 정보가 배열로 주어졌을 때, 발전기를 설치하는 최소 횟수 구하기. 시간 효율성을 위해서 배열을 독특한 방식으로 사용해야 하는 것이 특징 | [Goodland Electricity](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Goodland%20Electricity.cpp)
[Candies](https://www.hackerrank.com/challenges/candies/problem) | 그리디,<br> 스택 | 배열내 인접한 원소의 값(학생 학년) 차이에 따라 사탕을 나눠주기. 최소로 필요한 사탕 갯수 구하기 | [Candies](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Candies.cpp)
[멀쩡한 사각형](https://programmers.co.kr/learn/courses/30/lessons/62048) | 최소공배수 | 격자로 나뉘어진 직사각형에서 대각선을 그었을 때, 대각선이 지나가는 격자 사각형 개수를 구하기 | [IntactRectangle](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/IntactRectangle.cpp) [Lcm, Gcd](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/LCM_GCD.cpp)
[Gena Playing Hanoi](https://www.hackerrank.com/challenges/gena/problem) | 하노이,<br> BFS | 4개의 기둥을 활용하는 하노이의 탑, BFS를 활용하여 해결하는 방식이 참신했던 문제 | [Gena Playing Hanoi](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Gena%20Playing%20Hanoi.cpp)
[예산](https://programmers.co.kr/learn/courses/30/lessons/43237#) | 이분탐색 | 이분탐색을 활용하는 기본적인 문제입니다. | [BinarySearch_Budget](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/BinarySearch_Budget.cpp)
[입국심사](https://programmers.co.kr/learn/courses/30/lessons/43238) | 이분탐색 | 이분탐색을 활용하는 기본적인 문제입니다. | [Immigration](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Immigration.cpp)
[추석 트래픽](https://programmers.co.kr/learn/courses/30/lessons/17676) | 카카오, 문자열 | 어떤 작업의 시작/종료 시간이 주어졌을 때, 특정 1초 구간에서 처리되는 작업의 최대 개수 구하기 | [ThanksgivingDayTraffic](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/ThanksgivingDayTraffic.cpp)
[매칭 점수](https://programmers.co.kr/learn/courses/30/lessons/42893) | 카카오, 문자열 | 웹페이지 html을 분석하고 매칭점수 구하기 | [MatchingScore](https://gist.github.com/wlsvy/5f7fca5769759f008706da73bc83e85d)
[블록 게임](https://programmers.co.kr/learn/courses/30/lessons/42894) | 카카오, 테트리스 | 특정 테트리스 블록이 쌓인 상태에서, 추가적인 1x1 칸 블록을 임의로 삽입할 때 제거할 수 있는 블록의 최대 갯수 구하기 | [BlockGame](https://gist.github.com/wlsvy/bbb650588fef44c8aa663fd8e19cc262)
[기둥과 보 짓기](https://programmers.co.kr/learn/courses/30/lessons/60061#) | 카카오 | 격자 칸에 대해서, 가로/세로선을 차지하는 물체를 다루는 문제 | [ConstructPillarAndBeam](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/ConstructPillarAndBeam.cpp)
[외벽 점검](https://programmers.co.kr/learn/courses/30/lessons/60062) | 카카오, DFS | DFS 응용 문제 | [WallChecking](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/WallChecking.cpp)
[블록 이동하기](https://programmers.co.kr/learn/courses/30/lessons/60063) | 카카오, BFS, 미로 | BFS 응용 문제, 좌표 두 칸을 차지하는 로봇을 회전시켜가며, 목적지 까지 이동시킬 때 최소 이동 횟수를 구하자 | [MoveBlock](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/MoveBlock.cpp)
[호텔 방 배정](https://programmers.co.kr/learn/courses/30/lessons/64063) | 카카오, UnionFind | 연속된 순서의 숫자중 가장 마지막 값을 빠르게 찾는 법을 구현하는 것이 포인트  | [HotelReservation](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/HotelReservation.cpp)
[징검다리 건너기](https://programmers.co.kr/learn/courses/30/lessons/64062) | 카카오, 이분탐색 | 특정 횟수 만큼 밟으면 중간의 돌이 사라지는 징검다리 문제. | [SteppingStone](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/SteppingStone.cpp)
[튜플](https://programmers.co.kr/learn/courses/30/lessons/64065) | 카카오, 문자열 | 문제 풀이 로직보다 문자열 분석이 더 귀찮은 문제 | [Tuple](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Tuple.cpp)
[불량사용자](https://programmers.co.kr/learn/courses/30/lessons/64064) | 카카오, DFS | DFS 응용 문제, 제재 대상 아이디와 유저 아이디를 매칭 시키는 방법이 이전까지 풀어왔던 DFS 방식과는 다르다. | [IllegalUser](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/IllegalUser.cpp)
[수식 최대화](https://programmers.co.kr/learn/courses/30/lessons/67257) | 카카오, 문자열, 사칙연산 | 연산자 우선순위에 따라 수식 표현식 결과의 최댓값을 구하는 문제.  | [MaximizeExpression](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/MaximizeExpression.cpp)
[보석 쇼핑](https://programmers.co.kr/learn/courses/30/lessons/67258) | 카카오, 배열 | 조건을 만족하는 배열의 연속된 범위를 구하는 문제.  | [GemShopping](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/GemShopping.cpp)
[동굴 탐험](https://programmers.co.kr/learn/courses/30/lessons/67260) | 카카오, DFS/BFS | DFS/BFS 응용 문제, 특정 노드는 바로 접근할 수 없으며, 다른 임의의 노드에 방문한 뒤부터 잡근이 가능. 특정 노드를 방문하기 위해 선행되는 조건을 만족하는지 확인하는 과정에 주의하자. | [CaveAdventure](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/CaveAdventure.cpp)
[지형 이동](https://programmers.co.kr/learn/courses/30/lessons/62050) | BFS, 크루스컬 | BFS 응용 문제, 지형에 해당하는 칸마다 높이 값이 존재하며, 두 지역의 높이 차이가 특정 값보다 크다면 올라갈 때 사다리를 사용해야 한다. 최종적으로 필요한 사다리의 길이를 구하는 문제. 개인적으로 시간초과(set 데이터 비교 관련)으로 고생한 문제 **크루스컬을 활용하는 방법도 존재**  | [ExploreTerrain](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/ExploreTerrain.cpp)
[Max Array Sum](https://www.hackerrank.com/challenges/max-array-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming) | DP | 한칸 간격을 두고 인접한 배열 원소의 합을 구하기. 다수의 경우 중에서 최대값을 출력  | [Max Array Sum](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Max%20Array%20Sum.cpp)
[스티커 모으기(2)](https://programmers.co.kr/learn/courses/30/lessons/12971) | DP | 일차원 DP 응용 문제  | [CollectingSticker](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/CollectingSticker.cpp)
[땅따먹기](https://programmers.co.kr/learn/courses/30/lessons/12913) | DP | 이차원 DP  | [Hopscotch](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Hopscotch.cpp)
[가장 큰 정사각형 찾기](https://programmers.co.kr/learn/courses/30/lessons/12905#) | DP | 이차원 DP, 0과 1로 이루어진 2차원 배열에서 1이 차지하는 칸에 대해 가장 큰 정사각형 찾기 | [FindBiggestSquare](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/FindBiggestSquare.cpp)
[Lego Blocks](https://www.hackerrank.com/challenges/lego-blocks/problem) | DP, 블록쌓기 | 특정 칸을 완전히 채울 수 있게 레고블록을 사용하는 경우의 수 구하기. 접근법에 대한 배경지식이 없으면 코드 이해가 어려우니, 해설 페이지를 반드시 참조할 것. | [LegoBlocks](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/LegoBlocks.cpp)
[도둑질](https://programmers.co.kr/learn/courses/30/lessons/42897) | DP | 일차원 DP 응용문제, 스티커 모으기(2) 와 비슷한 유형 | [Theft](https://gist.github.com/wlsvy/dae136e5061a5ec276f179ae8e065856)
[3 x N 타일링](https://programmers.co.kr/learn/courses/30/lessons/12902) | DP, 블록쌓기 | 일차원 DP 응용문제, [접근법은 여기서 확인](https://wonillism.github.io/programmers/Programmers-3xn-tiling/) | [3xN_tiling](https://gist.github.com/wlsvy/768ec04cacdbd50dbbf2016925933495)
[Xor and Sum](https://www.hackerrank.com/challenges/xor-and-sum/problem) | 비트 연산 | 두 개의 2진수 값에 대해서, 한쪽 값을 1비트 씩 쉬프트 시킬 때 마다, 두 값의 xor 결과의 합을 구하기. (어려움)  | [xor-and-sum](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/xor-and-sum.cpp)
[지형 편집](https://programmers.co.kr/learn/courses/30/lessons/12984#) | 이분 탐색 | 블록을 쌓아 만든(마인크래프트 처럼) 지형에서 서로 다른 높낮이를 균일하게 만들 때 블록을 새로 만들거나 삭제할 때 들어가는 총 비용 구하기. 이분 탐색을 활용하지 않은 보다 간단한 해법이 존재한다.  | [EditTerrain](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/EditTerrain.cpp)


## 좀더 효율적인 문제풀이를 위해서
- #### 예외처리가 복잡해보인다 싶으면 일단 DFS/BFS를 먼저 생각하자
- #### 데이터 갯수가 많아 DFS/BFS 적용이 어렵다면 DP를 생각하자.
- #### map/unordered_map/set 등을 써야할 필요성을 느낀다면 그 전에 먼저 배열을 적용할 수 있는지 생각하자
- #### STL 컨테이너를 활용하는 경우, 더 빠른 코드 작성과, 가독성을 위해서 반복자(iterator) 사용은 자제하자.

### Helper Resources
- [TypeAliasing](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/TypeAliasing.cpp)  
- [GetArraySize](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/GetArraySize.cpp)  
- [ContainerOutstream](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/OutstreamHelper.cpp)  
- [Lcm, Gcd](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/LCM_GCD.cpp)

</details>



