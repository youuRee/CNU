import math

class Game():
    def __init__(self, size, board, player, computer):
        self.size = size         # 구름게임 맵 크기 (정방행렬)
        self.board = board       # 구름게임 맵 
        self.player = player     # 플레이어 위치 
        self.computer = computer # 컴퓨터 위치 

    # 구름게임 출력 함수 
    def board_visualization(self):
        for idx in range(self.size):
            for jdx in range(self.size):
                if self.board[idx][jdx] == 0:   # 낭떠러지 
                    print("□ ", end='')
                elif self.board[idx][jdx] == 1: # 구름 
                    print('▨ ', end='')
                elif self.board[idx][jdx] == 2: # 플레이어
                    print('◆ ', end='')
                elif self.board[idx][jdx] == 3: # 컴퓨터 
                    print('● ', end='')
                else:
                    pass
            print()


    # 플레이어 이동 위치 함수 
    def position(self):
        player = list(map(int, input(f'플레이어가 이동할 위치 입력: ').split()))
        # 맵을 벗어나지 않도록 설정 
        if player[0] >= self.size or player[1] >= self.size:
            self.position()
        
        # 이동할 위치가 구름이고 상하좌우 방향이라면 플레이어 위치로 변환 / 기존 위치는 낭떠러지로 변환 
        if self.board[player[0]][player[1]] == 1 and (abs(self.player[0]-player[0]) + abs(self.player[1]-player[1])) == 1:
            self.board[self.player[0]][self.player[1]] = 0
            self.player = player
            self.board[player[0]][player[1]] = 2
        else:
            self.position()

    # 게임이 끝났는지 확인하는 함수 
    def win_condition(self, board, turn):
        # 리턴값 0: 컴퓨터 승리 / 1: 플레이어 승리 / 2: 승패 결정 X 
        
        #### 코드 작성 ####
        
        if turn:
            # 현재 플레이어에게 이동 가능한 위치가 없다면
            if self.ismove(self.board, self.player) == []:
                result = 0 # 컴퓨터 승
            else:
                result = 2 # 그렇지 않으면 승패x
        else:
            # 현재 컴퓨터에게 이동 가능한 위치가 없다면
            if self.ismove(self.board, self.computer) == []:
                result = 1 # 플레이어 승
            else:
                result = 2 # 그렇지 않으면 승패x
        return result


    # 게임 결과에 따른 minimax 알고리즘 점수를 리턴하는 함수 
    def evaluate(self, board, turn):

        result = self.win_condition(board, turn)

        #### 코드 작성 ####

        # retrun 값 : [score, move(position)]
        # result 값을 통해 누가 이겼는지 알 수 있기 때문에 이를 통해 score를 부여 
        # 컴퓨터 승 : -100, 플레이어 승: 100, 승패x: 0
        
        if result == 0:
            return [-100, None]
        elif result == 1:
            return [100, None]
        else:
            return [0, None]
        

    # 타겟이 이동할 수 있는 위치를 찾는 함수 
    def ismove(self, board, pos):
        moves = [] # 초기화 
        
        #### 코드 작성 ####
        # 상하좌우 리스트
        dx = [-1, 1, 0, 0] 
        dy = [0, 0, -1, 1]

        # 현재 위치(pos)에서 이동 가능한 좌표 moves 리스트에 추가
        for i in range(4):
            nx = pos[0] + dx[i]
            ny = pos[1] + dy[i]
            if 0 <= nx < size and 0 <= ny < size:
                if board[nx][ny] == 1:
                    moves.append([nx, ny])

        return moves


    # MiniMax 알고리즘 수행 함수 
    # 인자 : 현재 board 상태, 현재 위치에서 이동가능한 좌표들, 현재 게임 진행자, 알파값, 베타값
    def minimax(self, board, moves, turn, a, b):
        # 리턴값 : best_score, best_move (플레이어가 갈 수 있는 최적의 위치와 이에 따른 점수 리턴)

        #### 코드 작성 ####
        if moves == []: # 끝까지 탐색했으면
            return self.evaluate(self.board, turn) # 평가 함수 (휴리스틱 함수) 실행
        
        if turn: # 플레이어
            best_score = -10000 # 플레이어는 최대값일수록 이길 가능성이 높기 때문에 초기값은 아주 작은값
            for i in moves:
                self.board[i[0]][i[1]] = 0
                score = self.minimax(self.board, self.ismove(self.board, i), False, a, b)[0]
                # 새로 탐색한 값(score)가 현재 최소값(best_score) 보다 크다면
                if score > best_score:
                    best_score = score # best_score 변경
                    best_move = [i[0], i[1]]
                self.board[i[0]][i[1]] = 1

                # 알파베타 가지치기
                a = max(a, best_score)
                if a >= b: # 베타 컷
                    break

        else: # 컴퓨터
            best_score = 10000 # 컴퓨터는 최소값일수록 이길 가능성이 높기 때문에 초기값은 아주 큰값
            for i in moves:
                self.board[i[0]][i[1]] = 0 # 일단 두고
                score = self.minimax(self.board, self.ismove(self.board, i), True, a, b)[0]
                # 새로 탐색한 값(score)가 현재 최소값(best_score) 보다 작다면
                if score < best_score:
                    best_score = score # best_score 변경
                    best_move = [i[0], i[1]] # best_score의 현재 좌표
                self.board[i[0]][i[1]] = 1 # 둔 부분 원상복구

                # 알파베타 가지치기
                b = min(b, best_score)
                if a >= b: # 알파 컷
                    break

        return [best_score, best_move]

    # 컴퓨터가 이동할 최적의 위치를 받는 함수 
    def best_pos(self):
    	# 컴퓨터가 이동할 최적의 위치 
        position = self.minimax(self.board, self.ismove(self.board, self.computer), False, -10000, 10000)[1]

        # 위치를 받아와서 구름게임 맵과 컴퓨터 위치 변경 
        self.board[self.computer[0]][self.computer[1]] = 0
        self.computer = [position[0], position[1]]
        self.board[position[0]][position[1]] = 3

# 구름게임 맵 입력 
board = []
size = int(input('구름게임 맵 크기(정방행렬): '))
print('낭떠러지 : 0     구름 : 1')
for s in range(size):
    tmp = list(map(int, input(f'{s}행 입력: ').split()))
    board.append(tmp)

while True: # 플레이어 시작 위치 입력 
    player = list(map(int, input(f'플레이어 시작 위치 입력: ').split()))
    if player[0] >= 0 and player[0] < size and player[1] >= 0 and player[1] < size:
        if board[player[0]][player[1]] == 1:
            break
board[player[0]][player[1]] = 2

while True: # 컴퓨터 시작 위치 입력 
    computer = list(map(int, input(f'컴퓨터 시작 위치 입력: ').split()))
    if computer[0] >= 0 and computer[0] < size and computer[1] >= 0 and computer[1] < size:
        if board[computer[0]][computer[1]] == 1:
            break
board[computer[0]][computer[1]] = 3

# 구름게임 세팅 
game = Game(size, board, player, computer)

print("============= Initial State =============")
game.board_visualization()

# 구름게임 시작 
while True:
    print("=============== Computer ================")
    # 컴퓨터가 이동하기 전에 플레이어 상하좌우에 구름 있는지 확인 -> 없으면 컴퓨터 승!
    result = game.win_condition(game.board, False) # 컴퓨터가 진행하기 전 게임 상황 확인 
    if result == 0: # 컴퓨터가 이긴 경우 게임 종료 
        game.board_visualization()
        print('컴퓨터가 승리하였습니다.')
        break
    elif result == 1: # 플레이어가 이긴 경우 게임 종료 
        game.board_visualization()
        print('플레이어가 승리하였습니다.')
        break
    game.best_pos()
    game.board_visualization()

    print("=============== Your turn ===============")
    result = game.win_condition(game.board, True) # 플레이어가 진행하기 전 게임 상황 확인 
    if result == 0:
        game.board_visualization()
        print('컴퓨터가 승리하였습니다.')
        break
    elif result == 1:
        game.board_visualization()
        print('플레이어가 승리하였습니다.')
        break
    game.position()
    game.board_visualization()


