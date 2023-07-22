from collections import deque

# 인공지능학부생 판별 함수
def is_ai_student(coord):
    
    x, y = abs(coord[0]), abs(coord[1])
    digit_sum = sum(map(int, str(x) + str(y)))
    # print(digit_sum)
    return digit_sum <= 16 or digit_sum % 2 == 0

def bfs(x, y):

    visited[x][y] = True

    queue = deque()
    queue.append((x,y))

    dx = [-1, 1, 0, 0] 
    dy = [0, 0, -1, 1]

    global count

    while queue:
        x, y = queue.popleft() # 인덱스
        value_x, value_y = x+distance_x, y+distance_y # 실제 좌표 값

        # 인공지능학부 인지 확인
        if is_ai_student((value_x, value_y)) == False:
            continue
        # 원 내부에 있는지 확인
        if (pow(value_x - cx, 2) + pow(value_y - cy, 2) < radius * radius) == False:
            continue
        # 상하좌우 중에 인공지능학부 한명이라도 있는지 확인 -> 있다면 count!
        if (is_ai_student((value_x-1, value_y)) or is_ai_student((value_x+1, value_y)) 
            or is_ai_student((value_x, value_y-1)) or is_ai_student((value_x, value_y+1))):
            # print(value_x, ',', value_y, " receive dessert")
            count += 1
        
        # 현재 위치에 상하좌우 이동해보고
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            # 이동 가능한 위치면 방문체크하고 queue에 추가
            if 0 <= nx < n and 0 <= ny < n and visited[nx][ny] == False:
                queue.append((nx, ny))
                visited[nx][ny] = True
                    

cx, cy = map(int, input('중심 좌표 입력: ').split())
radius = int(input('원의 반지름 입력: '))

#### 코드작성 ####

graph = []
visited = []

n = 2 * radius + 1
count = 0 # 디저트

# 인덱스와 실제 좌표 값의 차이
distance_x = cx - radius
distance_y = cy - radius

for i in range(n):
    visited.append([False] * n)

# 중심좌표인 첫 전달자 부터 bfs
bfs(radius, radius)

if count ==  0:
    answer = 0 # 처음 전달자 주변이 모두 타학과 학생이면 count = 0이 되므로
else:
    answer = count-1 # 처음 전달자(중심좌표) 제외

print(f'디저트를 받은 인공지능학부 학생은 총 {answer}명입니다.')

