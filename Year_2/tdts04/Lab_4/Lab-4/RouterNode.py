#!/usr/bin/env python

#Student-id: hugho678, viles222

import GuiTextArea, RouterPacket, F
from copy import deepcopy

class RouterNode():
    myID = None
    myGUI = None
    sim = None
    costs = None

    neighbor_distance = None
    next_hop = None
    minimum_distance = None
    
    # Access simulator variables with:
    # self.sim.POISONREVERSE, self.sim.NUM_NODES, etc.

    # --------------------------------------------------
    def __init__(self, ID, sim, costs):
        self.myID = ID
        self.sim = sim
        self.myGUI = GuiTextArea.GuiTextArea("  Output window for Router #" + str(ID) + "  ")

        self.costs = deepcopy(costs)
        
        self.neighbor_distance = [[self.sim.INFINITY] * self.sim.NUM_NODES for _ in range(self.sim.NUM_NODES)]
        self.neighbor_distance[self.myID] = deepcopy(costs)

        self.next_hop = [-1] * self.sim.NUM_NODES
        self.minimum_distance = deepcopy(costs)
        
        self.next_hop[self.myID] = self.myID
        self.minimum_distance[self.myID] = 0
        
        for i in range(self.sim.NUM_NODES):
            if costs[i] != self.sim.INFINITY and i != self.myID:
                self.next_hop[i] = i
                

        self.propagate()
        
        
    # --------------------------------------------------
    def propagate(self):
        for neighbor in range(self.sim.NUM_NODES):
            if neighbor != self.myID and self.costs[neighbor] != self.sim.INFINITY:
                updated_costs = deepcopy(self.minimum_distance)

                if self.sim.POISONREVERSE:
                    for dest in range(self.sim.NUM_NODES):
                        if self.next_hop[dest] == neighbor and dest != neighbor:
                            updated_costs[dest] = self.sim.INFINITY

                packet = RouterPacket.RouterPacket(self.myID, neighbor, updated_costs)
                self.sendUpdate(packet)
    
    
    # --------------------------------------------------
    def recvUpdate(self, pkt):
        self.neighbor_distance[pkt.sourceid] = pkt.mincost
        
    # --------------------------------------------------
    def find_shortest(self):
        updated = False

        for dest in range(self.sim.NUM_NODES):
            if dest == self.myID:
                self.minimum_distance[dest] = 0
                self.next_hop[dest] = dest
                continue

            min_cost = self.costs[dest]
            best_hop = dest if min_cost != self.sim.INFINITY else -1

            for neighbor in range(self.sim.NUM_NODES):
                if neighbor != self.myID and self.costs[neighbor] != self.sim.INFINITY:
                    potential_cost = self.costs[neighbor] + self.neighbor_distance[neighbor][dest]

                    if potential_cost < min_cost:
                        min_cost = potential_cost
                        best_hop = neighbor

            if self.minimum_distance[dest] != min_cost or self.next_hop[dest] != best_hop:
                self.minimum_distance[dest] = min_cost
                self.next_hop[dest] = best_hop
                updated = True

        if updated:
            self.propagate()


    # --------------------------------------------------
    def sendUpdate(self, pkt):
        self.sim.toLayer2(pkt)

    # --------------------------------------------------
    def updateLinkCost(self, dest, newcost):
        self.costs[dest] = newcost
        self.find_shortest()


    # --------------------------------------------------
    def printDistanceTable(self):
        self.myGUI.println("Current state for router " + str(self.myID) +
                           " at time " + str(self.sim.getClocktime()))
        self.myGUI.println("")
        
        self.myGUI.println("Distancetable:")
        line = "    dst |"
        for i in range(self.sim.NUM_NODES):
            line += f"{i:>5}"
        self.myGUI.println(line)
        
        self.myGUI.println("---------" + "-----" * self.sim.NUM_NODES)
        
        for i in range(self.sim.NUM_NODES):
            if self.costs[i] == self.sim.INFINITY or i == self.myID: continue
        
            line = f" nbr  {i} |"
            for j in range(self.sim.NUM_NODES):
                line += f"{self.neighbor_distance[i][j]:>5}" 
            self.myGUI.println(line)
        self.myGUI.println("")
            
        
        self.myGUI.println("Our distance vector and routes:")
        line = "    dst |"
        for i in range(self.sim.NUM_NODES):
            line += f"{i:>5}"
        self.myGUI.println(line)
            
        self.myGUI.println("---------" + "-----" * self.sim.NUM_NODES)
        line = " cost   |"
        for i in range(self.sim.NUM_NODES):
            line += f"{self.minimum_distance[i]:>5}"
        self.myGUI.println(line)
        
        line = " Route  |"
        for i in range(self.sim.NUM_NODES):
            line += f"{self.next_hop[i]:>5}"
        self.myGUI.println(line)
        self.myGUI.println("")
        

  
                

