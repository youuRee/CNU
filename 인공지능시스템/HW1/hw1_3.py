from collections import deque

# 우주선이 이동할 수 있는 4가지 방향
# 좌상우하
dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

# 우주선이 회전할 수 있는 4가지 방향
# index : 0~3 -> 북동남서
rotate_dx = [[-1, -1, 1, 1], [0, 1, 1, 0], [1, 1, -1, -1], [0, -1, -1, 0]]
rotate_dy = [[0, 1, 0, -1], [1, 1, -1, -1], [0, -1, 0, 1], [-1, -1, 1, 1]]

# bfs 알고리즘을 이용하여 최단 거리 계산
def bfs(board):
    n, m = len(board), len(board[0])
    visited = [[[False]*4 for j in range(m)] for i in range(n)]  # 방문 여부 저장
    queue = deque()
    # queue : 우주선 앞쪽의 초기 위치 (0,1), 방향 (우주선 앞쪽이 가르키는 방향), 시간
    queue.append((0, 1, 1, 0))
    time_list = [] # 도착까지 걸린 시간을 담는 리스트 (최단시간 구하기 위해 필요!)

    visited[0][0][0] = True
    visited[0][0][1] = True
    
    '''
    Why visited 배열 3차원?
    visited[x][y][direction] : x, y 위치에서 direction 방향으로 회전하거나 이동한 적이 있는지를 나타내는 값
    -> 3차원이면 우주선이 이동하면서, 이전 상태와는 다른 방향으로 이동할 때와 회전할 때를 구분하여 방문 여부를 기록 가능
    +) direction : (0: 북쪽, 1: 동쪽, 2: 남쪽, 3: 서쪽)
    '''

    while queue:
        x, y, direction, time = queue.popleft() # direction : 0~3 -> 순서대로 북동남서
        if x == n-1 and y == m-1: # 도착점까지 갔을때
            time_list.append(time) # 걸린 시간을 time_list에 추가
        
        # 이동하기
        for d in range(4):
            nx, ny = x+dx[d], y+dy[d]
            # 이동 불가능한 위치 or 이미 방문한 위치면 continue!
            if nx<0 or nx>=n or ny<0 or ny>=m or board[nx][ny] == 1:
                continue
            if visited[nx][ny][direction]:
                continue
            # 처음 방문한 곳은 True로 방문 체크
            visited[nx][ny][direction] = True 
            # 큐에 추가
            queue.append((nx, ny, direction, time+1))
            
        # 회전하기
        for d in range(4):
            rx = x+rotate_dx[direction][d]
            ry = y+rotate_dy[direction][d]
            # 회전 하면 안되는 위치 or 이미 방문한 위치면 continue!
            if rx<0 or rx>=n or ry<0 or ry>=m or board[rx][ry] == 1:
                continue
            if visited[x][y][d]:
                continue
            # (x,y)에서 모든 방향 회전 함 -> True
            visited[x][y][d] = True
            queue.append((x, y, d, time+1))
            
    return time_list # time_list 안의 최소값이 결국 최단초

# 감시 공간 크기 입력
n, m = map(int, input('감시 공간 크기 입력: ').split())
board = []
for s in range(n): # 감시 공간 입력
    tmp = list(map(int, input(f'{s}행 입력: ').split()))
    board.append(tmp)

# 최단 거리 출력
answer = min(bfs(board)) 
print(f'감시 공간을 탈출할 수 있는 최단 시간은 {answer}초입니다.')
