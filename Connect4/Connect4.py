import pygame
import time 

class Point:
    def __init__(self, position : tuple, positionInTable : tuple, Player : int, color, size : int) -> None:
        self.position = position
        self.color = color
        self.r = size
        self.positionInTable = positionInTable
        self.Player = Player
        # print(self.positionInTable)
        pass
    
    def draw(self, surface : pygame.surface):
        pygame.draw.circle(surface, self.color, self.position, self.r)
    

class Game:
    def __init__(self) -> None:
        self.width, self.height = 800, 600
        self.running = True
        self.CurrPlayer = 1
        self.GameEnded = False
        pygame.init()
        self.Surface = pygame.display.set_mode((self.width, self.height))
        self.size = 50
        self.col = 6
        self.row = 7
        self.mat = []
        self.points = []
        self.O = (100, 100) #Start table at
        for i in range(self.col):
            self.mat.append([])
            for j in range(self.row):
                self.mat[i].append(0)
                
        #Colors
        self.White = (255, 255, 255)
        self.Black = (0, 0, 0)
        self.Red = (255, 0, 0)
        self.Blue = (0, 0, 255)
        
    def Show(self):
        self.Surface.fill(self.White)
        for i in range(self.col):
            for j in range(self.row):
                position = (j * self.size + self.O[0], i * self.size + self.O[1])
                pygame.draw.rect(self.Surface, self.Black, pygame.Rect(position[0], position[1], self.size, self.size), 1)
        
        for point in self.points:
            point.draw(self.Surface)
       
        
        pygame.display.flip()
    
    def Input(self):
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                self.running = False
            if event.type == pygame.MOUSEBUTTONDOWN:
               if self.CurrPlayer == 1 and self.Drop(pygame.mouse.get_pos()):
                    position = self.Drop(pygame.mouse.get_pos())
                    self.MakeDecision(position)
    
    def Drop(self, position : tuple):
        posx = (position[0] - self.O[0]) // self.size
        posy = 0
        try:
            if(self.mat[posy][posx] != 0 or posx < 0 or posy < 0):
                return False
            return (posx, posy)
        except:
            print("Outside the box")
            return False
    
    def Update(self):
        offset = 5
        #Update Input

        self.points = []
        for i in range(self.col):
            for j in range(self.row):
                val = self.mat[i][j]
                if val == -1:
                    self.points.append(Point((j * self.size + self.O[0] + self.size // 2, i * self.size + self.O[1] + self.size // 2), 
                                           (j, i), self.mat[i][j], self.Blue, self.size // 2 - offset))
                if val == 1:
                    self.points.append(Point((j * self.size + self.O[0] + self.size // 2, i * self.size + self.O[1] + self.size // 2), 
                                           (j, i), self.mat[i][j], self.Red, self.size // 2 - offset))
        if len(self.points) > 0:
            pass
        #Update Points
        for point in self.points:
            if self.CanGoDown(point):
                point.positionInTable = point.positionInTable[0], point.positionInTable[1] + 1
        #reset Mat
        self.mat = []
        for i in range(self.col):
            self.mat.append([])
            for j in range(self.row):
                self.mat[i].append(0)
        #applyPoint
        for point in self.points:
            self.mat[point.positionInTable[1]][point.positionInTable[0]] = point.Player

        if len(self.points) > 0:
            if self.CanCheckResult():
                Player = self.CheckIfSomeOneWin()
                if Player != 0:
                    print(Player)
                    self.ShowVictoryText(Player)
                    pass

    def CheckIfSomeOneWin(self):
        Matdir = [(-1, -1), (1, 1), (-1, 1), (1, -1), (1, 0), (-1, 0), (0, 1), (0, -1)]
        for col in range(self.col):
            for row in range(self.row):
                Player = self.mat[col][row]
                if Player == 0:
                    continue
                for direction in Matdir:
                    temprow = row
                    tempcol = col
                    count = 0
                    while self.CheckInsideTheBox(tempcol, temprow) and self.mat[tempcol][temprow] == Player:
                        # print(self.mat[tempcol][temprow], Player)
                        # print(tempcol, temprow)
                        temprow += direction[0]
                        tempcol += direction[1]
                        count += 1
                        if count == 4:
                            return Player
        return 0
    
    def CheckInsideTheBox(self, col, row):
        return col >= 0 and row >= 0 and col <= self.col - 1 and row <= self.row - 1
    
    def CanCheckResult(self):
        for point in self.points:
            if self.CanGoDown(point):
                return False
        return True
        pass
    
    def ShowVictoryText(self, Player):
        self.GameEnded = True
        self.Update()
        self.Show()
        font = pygame.font.Font('freesansbold.ttf', 100)
        
        if Player == 1:
            text = font.render('Player 1 Win', True, self.Red, self.White)
        else:
            text = font.render('Player 2 Win', True, self.Red, self.White)
        text_rect = text.get_rect()
        text_rect.center = self.width // 2, self.height // 2
        self.Surface.blit(text, text_rect)
    
    def CanGoDown(self, point):
        MaxHeight = len(self.mat) - 1
        if point.positionInTable[1] + 1 <= MaxHeight:
                if self.mat[point.positionInTable[1] + 1][point.positionInTable[0]] == 0:
                    return True
        return False
        
    def Progress(self):
        self.Input()
        if not self.GameEnded:
            self.Update()
            self.Show()
        time.sleep(0.1)
        
    def MakeDecision(self, position):
        self.mat[0][position[0]] = self.CurrPlayer
        if self.CurrPlayer == 1:
            self.CurrPlayer = -1
        else: self.CurrPlayer = 1
    
    def CheckIfAICanMakeDecision(self):
        return self.CurrPlayer == -1 and self.CanCheckResult()
    
    def ExportMap(self):
        f = open("map.txt", "w")
        for col in range(self.col):
            for row in range(self.row):
                f.write(str(self.mat[col][row]) + " ")
            f.write('\n')
        f.close()
               