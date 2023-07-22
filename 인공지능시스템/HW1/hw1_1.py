count = 0 # 집인지 창고인지 구별하기 위해 필요
storage = 0
home = 0

def dfs(r, c):
    # 좌표가 범위를 벗어난 경우 종료
    if r < 0 or r >= n_row or c < 0 or c >= n_col:
        return False
    # 해당 좌표가 집이 아니거나 이미 방문한 경우 종료
    if village[r][c] == 0 or visited[r][c] == True:
        return False
    # 해당 좌표가 집이면서 방문하지 않은 경우
    visited[r][c] = True
    global count
    count += 1

    # 해당 좌표의 주변 탐색
    dfs(r-1, c-1)
    dfs(r-1, c)
    dfs(r-1, c+1)
    dfs(r, c-1)
    dfs(r, c+1)
    dfs(r+1, c-1)
    dfs(r+1, c)
    dfs(r+1, c+1)

    return True
        
# 전대마을(행렬) 입력
n_row, n_col = map(int, input('마을의 행과 열 개수를 공백 기준으로 분리하여 입력: ').split())
village = []
for i in range(n_row):
    col = list(map(int, input(f'{i} 행 입력: ').split()))
    village.append(col)

# 마을에 있는 집 개수 출력
#### 코드 작성 ####
visited = []
for i in range(n_row):
    visited.append([False] * (n_col))

for i in range(n_row):
    for j in range(n_col):
        if dfs(i, j) == True:
            # dfs를 실행하였는데 count가 1 (즉, 주변에 자신만 1이라면) -> 창고
            if count == 1:
                storage += 1
            else:
                home += 1
            count = 0

print(f'전대마을에는 {home}개의 집, {storage}개의 창고가 있습니다.')