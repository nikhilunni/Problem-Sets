import matplotlib.pyplot as plt
import numpy as np
from matplotlib.path import Path
import matplotlib.patches as patches
import math

### GLOBALS

SETTLEMENT = 0
CARD = 1
CITY = 2
MAX_POINTS = 10
MAX_RESOURCES = 4
LIMIT = 5

costs = np.array([[2, 3, 1],
                  [1, 1, 2],
                  [4, 2, 2]])

###

class CatanException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class Catan:
    def __init__(self, dice, resources, settlements, cities):
        self.width = dice.shape[1]
        self.height = dice.shape[0]
        self.dice = dice
        self.resources = resources
        self.settlements = settlements
        self.cities = cities

    def get_vertex_number(self, x, y):
        return (self.height + 1) * y + x
    
    def get_vertex_location(self, n):
        return (n % (self.height+1), n // (self.height+1))
    
    def is_tile(self, x, y):
        """returns whether x,y is a valid tile"""
        return x >= 0 and x < self.width and y >= 0 and y < self.width
    
    def build(self, x, y, building):
        """build either a city or a settlement"""
        if self.if_can_build(building, x, y):
            vertex = self.get_vertex_number(x, y)
            if building == "settlement":
                self.settlements.append(vertex)
            elif building == "city":
                if vertex not in self.settlements:
                    raise CatanException("A settlement must be built first.")
                self.cities.append(vertex)
                self.settlements.remove(vertex)
            else:
                raise CatanException("{0} is an unknown building. Please use 'city' or 'settlement'.".format(building))
        else:
            raise CatanException("Cannot build {0} here. Please check if_can_build before building".format(building))
            
    
    def if_can_build(self, building, x, y):
        """returns true if spot (x,y) is available, false otherwise"""
        if x< 0 or y<0 or x > self.width+1 or y > self.height + 1:
            raise CatanException("({0},{1}) is an invalid vertex".format(x,y))
        #first let's check that the spot is empty:
        if self.get_vertex_number(x,y) in self.cities:
            #spot not available
            return False
            #raise CatanException("City already exists at that vertex")
        for x1 in range(x-1,x+2):
            for y1 in range(y-1,y+2):
                if x1+y1 < x+y-1 or x1+y1 > x+y+1:
                    pass
                elif x1 < 0 or x1 > self.width or y1 < 0 or y1 > self.height:
                    pass
                elif building == "city" and x1 == x and y1 == y and self.get_vertex_number(x1,y1) in self.settlements:
                    pass
                elif self.get_vertex_number(x1,y1) in self.settlements or self.get_vertex_number(x1,y1) in self.cities:
                    return False
                    #raise CatanException("A settlement or a city is too close to the one you'd like to build.")
        return True

    def get_resources(self):
        """Returns array r where:
        r[i, :] = resources gained from throwing a (i+2)"""
        r = np.zeros((11, 3)) 
        for vertex in self.settlements:
            x, y = self.get_vertex_location(vertex)
            for dx in [-1, 0]:
                for dy in [-1, 0]:
                    xx = x + dx
                    yy = y + dy
                    if self.is_tile(xx, yy):
                        die = self.dice[yy, xx]
                        resource = self.resources[yy, xx]
                        r[die - 2, resource] += 1
        for vertex in self.cities:
            x, y = self.get_vertex_location(vertex)
            for dx in [-1, 0]:
                for dy in [-1, 0]:
                    xx = x + dx
                    yy = y + dy
                    if self.is_tile(xx, yy):
                        die = self.dice[yy, xx]
                        resource = self.resources[yy, xx]
                        r[die - 2, resource] += 2
        return r
    
    def draw(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, aspect='equal')
        ax.set_xlim(-0.02,self.width+0.02)
        ax.set_ylim(-0.02,self.height+0.02)
        ax.set_frame_on(False)
        ax.xaxis.set_visible(False)
        ax.yaxis.set_visible(False)
        for x in range(self.width):
            for y in range(self.height):
                color = ["brown", "red", "green"][self.resources[y, x]]
                ax.add_patch(patches.Rectangle((x, y),1,1, 
                                               facecolor=color))
                ax.text(x+0.5, y+0.5, str(self.dice[y, x]), fontsize=15)
        for vertex in self.settlements:
            x, y = self.get_vertex_location(vertex)
            ax.add_patch(patches.Rectangle((x-0.1, y-0.1),0.2,0.2, 
                                           facecolor="purple"))
            ax.text(x-0.05, y-0.09, "1", fontsize=15, color="white")
        for vertex in self.cities:
            x, y = self.get_vertex_location(vertex)
            ax.add_patch(patches.Rectangle((x-0.1, y-0.1),0.2,0.2, 
                                           facecolor="blue")) 
            ax.text(x-0.05, y-0.09, "2", fontsize=15, color="white")

class Player:    
    def __init__(self, action, board, resources, points = 0, turn_counter = 0):
        self.board = board
        self.action = action
        self.resources = resources
        self.points = points
        self.turn_counter = turn_counter
        
    def if_can_buy(self, item):
        if item == "card":
            return np.all(self.resources >= costs[CARD,:])
        elif item == "settlement":
            return np.all(self.resources >= costs[SETTLEMENT,:])
        elif item == "city":
            return np.all(self.resources >= costs[CITY,:])
        else:
            raise CatanException("Unknown item: {0}".format(item))
    
    def buy(self, item, x=-1,y=-1):
        if item == "card":
            self.points += 1
            self.resources = np.subtract(self.resources,costs[1])
        elif (item == "settlement" or item == "city") and self.board.if_can_build(item,x,y):
            self.board.build(x,y,item)
            if item == "settlement":
                self.points += 1
                self.resources = np.subtract(self.resources,costs[SETTLEMENT,:])
            else:
                self.points += 1
                self.resources = np.subtract(self.resources,costs[CITY,:])
            
    
    def play_round(self):
        dice_roll = np.random.randint(1,7)+np.random.randint(1,7)
        
        # collect resources
        collected_resources = self.board.get_resources()[dice_roll-2,:]
        self.resources = np.add(self.resources,collected_resources)
        self.resources = np.minimum(self.resources, MAX_RESOURCES) # LIMIT IS MAX # OF RESOURCES
        
        # perform action
        self.action(self, self.resources, costs)
        assert np.max(self.resources) < LIMIT
        
        # update the turn counter
        self.turn_counter += 1
        
        return dice_roll

def simulate_game(action, board, num_trials):
    """Simulates 'num_trials' games with policy 'action' and returns average length of games"""
    results = list()
    for _ in xrange(num_trials):
        resources = np.array([MAX_RESOURCES, MAX_RESOURCES, MAX_RESOURCES])
        live_board = Catan(board.dice, board.resources, [], [])
        player = Player(action, live_board, resources)
        
        while player.points < MAX_POINTS:
            if player.turn_counter > 10000:
                raise CatanException("possible infinite loop (over 10K turns)")
                break
            player.play_round()
        results.append(player.turn_counter)
    
    return np.sum(results)/float(num_trials)

def simulate_game_and_save(action, board):
    """Simulates 'num_trials' games with policy 'action' and returns average length of games"""
    results = list()
    
    resources = np.array([MAX_RESOURCES, MAX_RESOURCES, MAX_RESOURCES])
    live_board = Catan(board.dice, board.resources, [], [])
    player = Player(action, live_board, resources)
    
    settlements = []
    cities = []
    hands = []
    live_points = []
    dice_rolls = []

    while player.points < MAX_POINTS:
        if player.turn_counter > 100000:
            raise CatanException("possible infinite loop (over 10K turns)")
            break
        dice_roll = player.play_round()
        dice_rolls.append(dice_roll)
        settlements.append(live_board.settlements[:])
        cities.append(live_board.cities[:])
        hands.append(player.resources[:])
        live_points.append(player.points)
    
    return settlements, cities, hands, live_points, dice_rolls

def get_random_dice_arrangement(width, height):
    """returns a random field of dice"""
    ns = range(2, 13) * (width * height / 10 + 1)
    ns = ns[:width*height]
    np.random.shuffle(ns)
    ns = np.reshape(ns, (height, width))
    return ns