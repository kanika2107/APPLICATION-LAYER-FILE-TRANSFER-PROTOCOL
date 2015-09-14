import random
import copy

def SelectAction(state,move):
    array = []
    count = 0 
    temp = copy.deepcopy(state)
    for i in range(0,3):

        for j in range(0,3):
            temp = copy.deepcopy(state)
            if state[i][j]=='_':
                temp[i][j]=move
                array.append(temp)
                
    return array

def Min(a,b):
    if a < b :
        return a
    return b


def Max(a,b):
    if a > b :
        return a
    return b

def UTILITY(state):
    if((state[0][0]=='X' and state[0][1]=='X' and state[0][2]=='X') or (state[1][0]=='X' and state[1][1]=='X' and state[1][2]=='X') or (state[2][0]=='X' and state[2][1]=='X' and state[2][1]=='X') or (state[0][0]=='X' and state[1][0]=='X' and state[2][0]=='X') or (state[0][1]=='X' and state[1][1]=='X' and state[2][1]=='X') or (state[0][0]=='X' and state[1][1]=='X' and state[2][2]=='X') or (state[2][0]=='X' and state[1][1]=='X' and state[0][2]=='X')):
        return 1
    elif((state[0][0]=='O' and state[0][1]=='O' and state[0][2]=='O') or (state[1][0]=='O' and state[1][1]=='O' and state[1][2]=='O') or (state[2][0]=='O' and state[2][1]=='O' and state[2][1]=='O') or (state[0][0]=='O' and state[1][0]=='O' and state[2][0]=='O') or (state[0][1]=='O' and state[1][1]=='O' and state[2][1]=='O') or (state[0][0]=='O' and state[1][1]=='O' and state[2][2]=='O') or (state[2][0]=='O' and state[1][1]=='O' and state[0][2]=='O')):
        return -1
    else:
        return 0         

def TERMINAL_TEST(state):
    if((state[0][0]=='X' and state[0][1]=='X' and state[0][2]=='X') or (state[1][0]=='X' and state[1][1]=='X' and state[1][2]=='X') or (state[2][0]=='X' and state[2][1]=='X' and state[2][1]=='X') or (state[0][0]=='X' and state[1][0]=='X' and state[2][0]=='X') or (state[0][1]=='X' and state[1][1]=='X' and state[2][1]=='X') or (state[0][0]=='X' and state[1][1]=='X' and state[2][2]=='X') or (state[2][0]=='X' and state[1][1]=='X' and state[0][2]=='X')):
        return 1
    elif((state[0][0]=='O' and state[0][1]=='O' and state[0][2]=='O') or (state[1][0]=='O' and state[1][1]=='O' and state[1][2]=='O') or (state[2][0]=='O' and state[2][1]=='O' and state[2][1]=='O') or (state[0][0]=='O' and state[1][0]=='O' and state[2][0]=='O') or (state[0][1]=='O' and state[1][1]=='O' and state[2][1]=='O') or (state[0][0]=='O' and state[1][1]=='O' and state[2][2]=='O') or (state[2][0]=='O' and state[1][1]=='O' and state[0][2]=='O')):
        return 1
    for i in range(0,3):
        for j in range(0,3):
            if state[i][j]=='_':
                return 0

    return 1

def MINIMAX_DECISIONS(state):
    v = -213879879879879879879123213213123
    x=[]
    for a in SelectAction(state,'X'):
        p=MIN_VALUE(a,'O')
        if v < p:
            v = p
            x=a
    return x 

def MAXiMIN_DECISIONS(state):
    v = 21312321321312376575757657657657765
    x=[]
    for a in SelectAction(state,'O'):
        p=MAX_VALUE(a,'X')
        if v > p:
            v = p
            x=a
    return x   

def neg(move):
    if move=='X':
        return 'O'
    else:
        return 'X'

def MAX_VALUE(state,move):
    if TERMINAL_TEST(state)!=0 : 
        return UTILITY(state)
    v = -213123213213123
    for a in SelectAction(state,move):
   #     print a
        v=Max(v,MIN_VALUE(a,neg(move)))
    return v

def MIN_VALUE(state,move):
    if TERMINAL_TEST(state)!=0 :
        return UTILITY(state)
    v = 213123213213123
    for a in SelectAction(state,move):
        v=Min(v,MAX_VALUE(a,neg(move)))
    return v

def main(): 
    Game = [['_','_','_'],['_','_','_'],['_','_','_']]
    for i in Game :
        for j in i : 
            print j,
        print "\n"
    print " A coin is tossed .Choose Head or Tail.1 is for heads and 0 is for tails"

    #1 is for heads and 0 is for tails
    choice = int(input())
    toss = random.randint(0,1)
    flagmove=0 # for computers moves
    if choice == toss:
            flagmove=1
            print "You move first :D"
    else: 
            flagmove=0
            print "Computer moves :/"


    state=Game
    '''
        SINCE WE WANT TO COMPUTER TO WIN THEREFORE COMPUTER IS THE MAX PLAYER AND YOU ARE THE MIN PLAYER
    '''
    i=0
    for i  in range(0,9):
        if(i%2==0):
            state=MINIMAX_DECISIONS(state)
            print state
        else:
            state=MAXiMIN_DECISIONS(state)
            print state

    #state = Game
    #state = [['_','X','0'],['_','_','_'],['_','_','_']]
    # I am assuming computer plays first
    #action = SelectAction(Game,'X')

    #for i in action : 
     #   print i



main()
#!/usr/bin/env python
#Filename: tic-tac-toe.py
#Description: Tic-Tac-Toe two player game

class GAME:

    def __init__(self):
        '''Initialize parameters - the game board, moves stack and winner'''

        self.board = [ '-' for i in range(0,9) ]
        self.lastmoves = []
        self.winner = None

    def print_board(self):
        '''Print the current game board'''
       
        print "\nCurrent board:"

        for j in range(0,9,3):
            for i in range(3):
                if self.board[j+i] == '-':
                    print "%d |" %(j+i),
                else:
                    print "%s |" %self.board[j+i],
   
            print "\n",


    def get_free_positions(self):
        '''Get the list of available positions'''

        moves = []
        for i,v in enumerate(self.board):
            if v=='-':
                moves.append(i)
        return moves

    def mark(self,marker,pos):
        '''Mark a position with marker X or O'''
        self.board[pos] = marker
        self.lastmoves.append(pos)

    def revert_last_move(self):
        '''Reset the last move'''

        self.board[self.lastmoves.pop()] = '-'
        self.winner = None

    def is_gameover(self):
        '''Test whether game has ended'''

        win_positions = [(0,1,2), (3,4,5), (6,7,8), (0,3,6),(1,4,7),(2,5,8), (0,4,8), (2,4,6)]

        for i,j,k in win_positions:
            if self.board[i] == self.board[j] == self.board[k] and self.board[i] != '-':
                self.winner = self.board[i]
                return True

        if '-' not in self.board:
            self.winner = '-'
            return True

        return False

    def play(self,player1,player2):
        '''Execute the game play with players'''

        self.p1 = player1
        self.p2 = player2
   
        for i in range(9):

            self.print_board()
           
            if i%2==0:
                if self.p1.type == 'H':
                    print "\t\t[Human's Move]"
                else:
                    print "\t\t[Computer's Move]"

                self.p1.move(self)
            else:
                if self.p2.type == 'H':
                    print "\t\t[Human's Move]"
                else:
                    print "\t\t[Computer's Move]"

                self.p2.move(self)

            if self.is_gameover():
                self.print_board()
                if self.winner == '-':
                    print "\nGame over with Draw"
                else:
                    print "\nWinner : %s" %self.winner
                return

class Human:
    '''Class for Human player'''

    def __init__(self,marker):
        self.marker = marker
        self.type = 'H'
   
    def move(self, gameinstance):

        while True:
       
            m = raw_input("Input position:")

            try:
                m = int(m)
            except:
                m = -1
       
            if m not in gameinstance.get_free_positions():
                print "Invalid move. Retry"
            else:
                break
   
        gameinstance.mark(self.marker,m)
         
class AI:
    '''Class for Computer Player'''

    def __init__(self, marker):
        self.marker = marker
        self.type = 'C'

        if self.marker == 'X':
            self.opponentmarker = 'O'
        else:
            self.opponentmarker = 'X'

    def move(self,gameinstance):
        move_position,score = self.maximized_move(gameinstance)
        gameinstance.mark(self.marker,move_position)



    def maximized_move(self,gameinstance):
        ''' Find maximized move'''    
        bestscore = None
        bestmove = None

        for m in gameinstance.get_free_positions():
            gameinstance.mark(self.marker,m)
       
            if gameinstance.is_gameover():
                score = self.get_score(gameinstance)
            else:
                move_position,score = self.minimized_move(gameinstance)
       
            gameinstance.revert_last_move()
           
            if bestscore == None or score > bestscore:
                bestscore = score
                bestmove = m

        return bestmove, bestscore

    def minimized_move(self,gameinstance):
        ''' Find the minimized move'''

        bestscore = None
        bestmove = None

        for m in gameinstance.get_free_positions():
            gameinstance.mark(self.opponentmarker,m)
       
            if gameinstance.is_gameover():
                score = self.get_score(gameinstance)
            else:
                move_position,score = self.maximized_move(gameinstance)
       
            gameinstance.revert_last_move()
           
            if bestscore == None or score < bestscore:
                bestscore = score
                bestmove = m

        return bestmove, bestscore

    def get_score(self,gameinstance):
        if gameinstance.is_gameover():
            if gameinstance.winner  == self.marker:
                return 1 # Won
            elif gameinstance.winner == self.opponentmarker:
                return -1 # Opponent won
        return 0 # Draw
       

if __name__ == '__main__':
    game=GAME()    
    player1 = AI("X")
    player2 = AI("O")
    game.play( player1, player2)
