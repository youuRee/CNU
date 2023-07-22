USER=1
COMPUTER=2

def board_visualization(board):
    ### 틱택토 게임 출력 함수  
    for row in range(3):
        for col in range(3):
            
            if board[row][col] == 0: # not occupied
                print("▨", end='')
            elif board[row][col] == USER: # user
                print("○", end='')
            elif board[row][col] == COMPUTER: # computer
                print("×", end='')
            else:
                pass
        print()        
           
    
def board_turn(board, row, col, val):
    
    if 0 <= row < 3 and 0 <= col < 3:
        if board[row][col] == 0:
            board[row][col] = val
            return True
        else:
            print("그곳에 돌을 둘 수 없습니다. 다시 입력하세요.")
            return False
    else:
        print("그곳에 돌을 둘 수 없습니다. 다시 입력하세요.")
        return False
        
    
def win_condition(v1,v2,v3): # 사용자 승리 return 100, 컴퓨터 승리 return -100, 무승부 return 0
    if v1 == v2 == v3:  
        if v1 == 1: return 100
        elif v2 == 2: return -100
        else: return 0
    else:
        return 0
        
    
def game_result(board): # 사용자 승리 return 100, 컴퓨터 승리 return -100, 무승부 return 0
    result = 0
    # check rows
    for row in range(3):
        result = win_condition(board[row][0],board[row][1],board[row][2])      
        if result != 0: return result
      
    # check cols
    for col in range(3):
        result = win_condition(board[0][col],board[1][col],board[2][col])
        if result != 0: return result
        
    #check diagonals
    result = win_condition(board[0][0],board[1][1],board[2][2])      
    if result != 0: return result
    result = win_condition(board[0][2],board[1][1],board[2][0])      
    if result != 0: return result
        
    return result

def position():
    row = int(input("돌을 놓을 행을 입력하세요 (0~2):"))
    col = int(input("돌을 놓을 열을 입력하세요 (0~2):"))
    
    return row, col

def minimax(board, turn):
    # board : 현재 틱택토 보드
    # turn : user 또는 computer의 차례
    
    # hint
    # 1. minimax함수에서는 사람이 이기면 큰 수 (+100), 컴퓨터가 이기면 작은수 (-100), 비기면 중간값(0) 반환 - game_result() 함수 활용
    # 2. ① 사용자가 둔 수 이후에 대한 탐색과 ② 컴퓨터가 둔 수 이후에 대한 탐색을 재귀적’으로 수행
    #    단, 사용자는 값을 최대화 하는쪽으로 / 컴퓨터는 값을 최소화 하는 쪽으로 탐색 
    #    재귀적으로 탐색을 수행하다보면 승패가 결정된 값이 반환됨
    
    score = game_result(board) #현재 보드의 점수를 계산 
    
    if (score == 100 or score == -100) : # 게임을 끝까지 돌리고 score 리턴
        return score

    # 빈칸이 하나도 없다면 -> 즉, 승패 결정x
    count = 0
    for row in range(3):
        for col in range(3):
            if(board[row][col] != 0):
                count += 1
    if(count == 9): # 틱택토 board는 총 9개 이므로
        return 0   # 0 리턴 (무승부)
 
    
    if (turn == USER) :  # 사용자
        best_score = -10000 # 사용자는 최대값일수록 이길 가능성이 높기 때문에 초기값은 아주 작은값
        for row in range(3) :  #모든 셀을 돌면서 
            for col in range(3) :
                if (board[row][col]==0) : # 빈칸이면 
                    board[row][col] = USER # 채우고 
                    best_score = max(best_score, minimax(board,COMPUTER))  # 최대값을 찾기 위해 돌림 
                    board[row][col] = 0 # 둔것을 원상복구
        
    else : # 컴퓨터
        best_score = 10000 # 컴퓨터는 최소값일수록 이길 가능성이 높기 때문에 초기값은 아주 큰값
        for row in range(3):  
            for col in range(3):
                if (board[row][col] == 0):  # 빈칸이면 
                    board[row][col] = COMPUTER # 채우고 
                    best_score = min(best_score, minimax(board,USER))  # 최소값을 찾기 위해 돌림
                    board[row][col] = 0 # 둔것을 원상복구
    return best_score
    

def computer(board):
    ### 현재 computer()함수는 빈곳에 랜덤하게 돌을 두도록 프로그래밍 되어있음
    ### 무조건 user를 상대로 [비기거나/이기도록] 미니맥스 알고리즘을 이용하여 다시 프로그래밍 하시오  
    ### computer() 함수와 minimax() 함수만 새로 작성하여 문제를 해결하시오
    
    best_score = 10000 # 컴퓨터는 -100 이 이긴것이기 때문에 최소화를 찾아야함, 현재는 아주 큰 수를 지정
    row, col = -1, -1 # 초기치는 의미 없는 값
 
    for i_idx in range(3):
        for j_idx in range(3):
            if (board[i_idx][j_idx] == 0):  # 비어있으면 
                board[i_idx][j_idx] = COMPUTER # 일단 둠 
                score = minimax(board, USER) # 다음은 사용자가 두게하여 게임을 끝까지 진행
                board[i_idx][j_idx] = 0 # 둔것을 원상복구
                if (score < best_score):  # 점수가 가장 낮으면(100보다는 0, 0보다는 -100) 좌표를 보관
                    row, col = i_idx, j_idx
                    best_score = score
 
    return row, col # 가장 작은 score가 나온 좌표 리턴


### 게임 시작
print("게임 시작")
board = [[0,0,0],[0,0,0],[0,0,0]]
board_visualization(board)

for _ in range(5): # 플레이어는 최대 5번 돌을 둔다
    ###### User ######
    print("============= Your turn =============")
    row, col = position()
    while board_turn(board, row, col,USER) == 0:
        row, col = position()
        
    board_visualization(board)
    if game_result(board) == 100:
        print("사용자가 승리하였습니다.")
        break
    elif game_result(board) == -100:
        print("컴퓨터가 승리하였습니다.")
        break      
    ########################
    
    
    
    ###### Computer ######
    print("============= Computer =============")
    row, col = computer(board) # computer 함수를 다시 코딩 하시오
    board_turn(board, row, col, COMPUTER)
    board_visualization(board)   
    if game_result(board) == 100:
        print("사용자가 승리하였습니다.")
        break
    elif game_result(board) == -100:
        print("컴퓨터가 승리하였습니다.")
        break
    ########################

    
if game_result(board) == 0:
    print("비겼습니다.")