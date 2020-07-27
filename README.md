# TIL
Today I Learned


## C++
- [Effective C++](https://github.com/wlsvy/TIL/tree/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B)
- [Effective STL](https://github.com/wlsvy/TIL/tree/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL)
- [Effective Modern C++](https://github.com/wlsvy/TIL/tree/master/Document/C%2B%2B/Effective%20Modern%20C%2B%2B/EffectiveModernCpp)
- [C++ Type Casting](https://github.com/wlsvy/TIL/blob/master/Document/C++/Cpp%20Type%20Casting.md)
- [C++ Value Category](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/C%2B%2B%20Value%20Category.md)
- [PrependidColon](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/PrependedColon.md)

## C#
- [Effective C#](https://github.com/wlsvy/TIL/tree/master/Document/C%23/Effective%20CSharp/EffectiveCSharp)

## Computer Science
- [컴퓨터 아키텍쳐](https://github.com/wlsvy/TIL/blob/master/Document/ComputerScience/ComputerArchitecture.md)
- [OS](https://github.com/wlsvy/TIL/blob/master/Document/ComputerScience/OperatingSystem.md)

## Graphics
- [2020 DirectX 개인 프로젝트 정리](https://github.com/wlsvy/TIL/blob/master/Document/Graphics/2020_DirectX_Project.md)
- [DirectX OpenGL 차이점](https://github.com/wlsvy/TIL/blob/master/Document/Graphics/DirectX_OpenGL_Difference.md)

# Coding Problem Solving

<details>
<summary>List</summary>


문제 | 분류 | 설명 | 해답 코드  
|---|---|---|---|
[KnightL on a Chessboard](https://www.hackerrank.com/challenges/knightl-on-chessboard/problem) | BFS, 중급 | 체스판 한쪽 끝에서 반대편 끝까지 체스말(나이트Knight)를 최소 몇 번 안에 이동시킬 수 있는지 찾기 | [KnightL on a Chessboard](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KnightL%20on%20a%20Chessboard.md)
[Friend Circle Queries](https://www.hackerrank.com/challenges/friend-circle-queries/problem) | UnionFind, 중급 | 여러 사람들 중 악수한 사람끼리 이어진 그룹의 크기 구하기 | [Friend Circle Queries](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Friend%20Circle%20Queries.cpp)
[Connected Cells in a Grid](https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem) | DFS, 그래프, 중급 | 조건을 만족하는 인접한 셀(cell) 연결된 총 갯수 구하기 | [Connected Cells in a Grid](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Connected%20Cells%20in%20a%20Grid.cpp)
[Cut the Tree](https://www.hackerrank.com/challenges/cut-the-tree/problem) | DFS, 그래프, 중급 | 노드로 이루어진 트리의 특정 선분을 잘랐을 때 분할된 트리 노드의 가중치 합 구하기, DFS 응용. 재귀 함수 호출 할때 깊이 들어가면서 가중치 합을 연산하는 것이 아닌, 함수 호출이 끝나고 빠져나오면서 연산하는 것이 포인트 | [Cut the Tree](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Cut%20the%20Tree.cpp)
[Count Luck](https://www.hackerrank.com/challenges/count-luck/problem) | DFS, 미로 | 미로의 목적지에 도달할 때 까지 마주친 갈림길의 수 구하기 | [Count Luck](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Count%20Luck.cpp)
[Minimum Loss](https://www.hackerrank.com/challenges/minimum-loss/problem) | 정렬 | 배열의 원소 중, A - B 가 음수이면서 그 절대값 차이가 제일 작을 때의 값 찾기 | [Minimum Loss](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Minimum%20Loss.cpp)
[Matrix Layer Rotation](https://www.hackerrank.com/challenges/matrix-rotation-algo/problem) | 이중 배열, 테두리 회정 | 이중 배열의 원소들을 반시계 방향으로 회전 | [Matrix Layer Rotation](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Matrix%20Layer%20Rotation.cpp)  + [이중 배열을 회전시키는 방법들](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/RotateMatrix.cpp)
[Snakes and Ladders](https://www.hackerrank.com/challenges/the-quickest-way-up/problem) | BFS | 뱀과 사다리 게임, 시작 지점에서 도착 지점에 도달하기 까지 주사위를 최소 몇 번 던져야 하는지 구하기, 주사위 면에 따른 BFS 분기를 활용하는 것이 포인트 | [Snakes and Ladders](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Snakes%20and%20Ladders_QuickWay.cpp)
[Red Knight's Shortest Path](https://www.hackerrank.com/challenges/red-knights-shortest-path/problem) | BFS 응용 <br>경로 기록 <br>중복 경로 처리 <br>체스 | 체스말 옮기기, 시작 지점에서 도착 지점 까지 도달하기 위한 최소 이동 횟수 및 목적지까지 이동한 방향 출력, 그리고 중복되는 경로가 존재하면 규칙에 따라 우선순위에 높은 경로를 선택. | [Red Knight's Shortest Path](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Red%20Knight's%20Shortest%20Path.cpp)
[Short Palindrome](https://www.hackerrank.com/challenges/short-palindrome/problem) | DP <br>문자열 | (난이도 어려움) 특정 문자열에서 조건을 만족하는 경우의 수 찾기.<br> (0 <= a < b < c < d < 문자열 길이, str[a] == str[d] && str[b] == str[c]) | [Short Palindrome](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Short%20Palindrome.cpp)
[Prim's (MST) : Special Subtree](https://www.hackerrank.com/challenges/primsmstsub/problem) | Prim <br>그래프 | 최소 신장 트리를 구하는 prim 알고리즘 작성 | [Prim_MST](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Prim_MST.cpp)
[Kruskal (MST): Really Special Subtree](https://www.hackerrank.com/challenges/kruskalmstrsub/problem) | Kruskal, <br>UnionFind, <br>그래프 | 최소 신장 트리를 구하는 kruskal 알고리즘 작성 | [Kruskal_MST](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Kruskal_MST.cpp)
[Dijkstra: Shortest Reach 2](https://www.hackerrank.com/challenges/dijkstrashortreach/problem?h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen) | 다익스트라, <br>최소길이, <br>그래프 | 시작 노드를 기준으로 다른 노드까지 최소 거리를 구하는 다익스트라 알고리즘 작성 | [Dijkstra](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Dijkstra.cpp)
[문자열 압축](https://programmers.co.kr/learn/courses/30/lessons/60057?language=cpp) | 문자열<br>카카오 | 문자열 압축 알고리즘 작성, 예외처리가 까다로운 문제<br>압축 숫자 자릿 수(0, 10 차이), 초기 위치 관련, 압축되지 않는 나머지 문자열 예외처리 | [StringCompression](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_StringCompression.cpp)
[괄호 변환](https://programmers.co.kr/learn/courses/30/lessons/60058) | 문자열,<br>괄호처리,<br>카카오 | 괄호 처리 알고리즘 작성 + 괄호 유효성 검사 | [ChangeParenthesis](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_ChangeParenthesis.cpp)
[자물쇠와 열쇠](https://programmers.co.kr/learn/courses/30/lessons/60059) | 이중배열 회전,<br>카카오 | key 와 lock 이중배열에 대해서, key를 이동시키거나 회전시켜서 lock 에 딱 맞출 수 있는지 구하기 | [Lock](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_Lock.cpp)
[가사 검색](https://programmers.co.kr/learn/courses/30/lessons/60060) | 트라이(Trie),<br> 문자열 검색,<br>카카오 | 쿼리(ex : st????)에 대해서 조건을 만족하는 문자열 갯수 찾기<br> - 쿼리와 동일한 길이 <br> - 쿼리의 ?를 제외한 문자는 전부 동일 | [StringSearch](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/KakaoBlind2020_StringSearch.cpp)
[Goodland Electricity](https://www.hackerrank.com/challenges/pylons/problem) | 그리디,<br> 배열 응용 | 특정 도시들의 정보가 배열로 주어졌을 때, 발전기를 설치하는 최소 횟수 구하기. 시간 효율성을 위해서 배열을 독특한 방식으로 사용해야 하는 것이 특징 | [Goodland Electricity](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Goodland%20Electricity.cpp)
[Candies](https://www.hackerrank.com/challenges/candies/problem) | 그리디,<br> 스택 | 배열내 인접한 원소의 값(학생 학년) 차이에 따라 사탕을 나눠주기. 최소로 필요한 사탕 갯수 구하기 | [Candies](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Candies.cpp)
[멀쩡한 사각형](https://programmers.co.kr/learn/courses/30/lessons/62048) | 최소공배수 | 격자로 나뉘어진 직사각형에서 대각선을 그었을 때, 대각선이 지나가는 격자 사각형 개수를 구하기 | [IntactRectangle](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/IntactRectangle.cpp)

### Helper Resources
- [TypeAliasing](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/TypeAliasing.cpp)  
- [GetArraySize](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/GetArraySize.cpp)  
- [ContainerOutstream](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/OutstreamHelper.cpp)  

</details>



