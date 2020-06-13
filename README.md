# TIL
Today I Learned


# Coding Problem Solving

#### 많은 풀이법을 보고 이해하는 것을 우선으로 합니다.

&nbsp;&nbsp; 코딩 문제풀이는 힘들고 많은 시간을 필요로 합니다. 문제 하나를 붙잡고 해결할 때까지 끈기있게 도전하는 태도는 분명 박수를 받아야 겠지만, 다른 필요한 공부가 급한 지금, 문제풀이에 오랫동안 몰두하기보다 그 시간을 좀 더 중요한 곳에 투자하려 합니다.

- 보통 중급 난이도의 문제 풀이. 한 문제를 1시간 동안 해결하지 못하면 다른 사람의 풀이 확인.
- 단, 스스로 풀지 못한 경우! 여기 풀이법을 정리하고 나중에 다시 풀어볼 것!!!


## List


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
[Prim's (MST) : Special Subtree](https://www.hackerrank.com/challenges/primsmstsub/problem) | Prim <br>그래프 | 최소 신장 트리를 구현하는 prim 알고리즘 작성 | [Prim_MST](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Prim_MST.cpp)


### Sub
- [TypeAliasing](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/TypeAliasing.cpp)  
- [GetArraySize](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/GetArraySize.cpp)  
- [ContainerOutstream](https://github.com/wlsvy/TIL/blob/master/Coding_Problem_Solving/Helper/OutstreamHelper.cpp)  
