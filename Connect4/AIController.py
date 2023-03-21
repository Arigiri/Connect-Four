from Connect4 import *
import os

class AI:
    def __init__(self) -> None:
        self.game = Game()
        os.system("g++ AI.cpp")
        pass
    
    def AIMakeDecision(self):
        os.system("a.exe")
        f = open("decision.txt", "r")   
        decision = f.readline()
        posx = int(decision[0])
        posy = int(decision[-1])
        self.game.MakeDecision((posx, posy))
        print(decision)
        pass

    def Progress(self):
        self.game.Progress()
        if self.game.CheckIfAICanMakeDecision() and self.game.CanCheckResult() and self.game.CheckIfSomeOneWin() == 0:
            self.game.ExportMap()
            self.AIMakeDecision()
    
ai = AI()
while ai.game.running:
    ai.Progress()