# test data
#input = "125 17"
# actual input
input = "5 89749 6061 43 867 1965860 0 206250"

LUT = {}
MultipleOf2024 = [0, 2024, 4048, 6072, 8096, 10120, 12144, 14168, 16192, 18216, 20240
                #   26312,24288,28336,30360,32384,22264,34408,36432,38456,40480,42504,44528,46552,48576,50600,52624,
                #     54648,56672,58696,60720,62744,64768,66792,68816,70840,72864,74888,76912,78936,80960,82984,85008,
                #     87032,89056,91080,93104,95128,97152,99176,103224,105248,101200,107272,109296,111320,113344,115368,117392,
                #     119416,121440,123464,125488,127512,129536,131560,133584,135608,137632,139656,141680,143704,145728,147752,149776,
                #     151800,153824,155848,157872,159896,161920,163944,165968,167992,170016,172040,174064,176088,178112,180136,182160,
                #     184184,186208,188232,190256,192280,194304,196328,198352,200376
                  ]

def process(stone):
    temp = ""
    # 0
    if(int(stone) == 0):
        temp = "1"
    # odd length
    elif(len(stone)%2 and int(stone) != 0):
        if(int(stone) > 0 and int(stone) < 100):
            #print("MUL hit")
            temp = str(MultipleOf2024[int(stone)])
        else:
            temp = (str(int(stone)*2024))      
    # even
    elif(not len(stone)%2 and int(stone) != 0):
        first = int(stone[:len(stone)//2])
        second = int(stone[len(stone)//2:])
        temp = str(first) + " " + str(second)
    
    return temp

#part -1
def splitStone_part1(numbers):
    Lsum = 0
    data = numbers
    
    for i in range(0, 5):        
        for j in range(0, 5):
            #print(i, j)
            blinkedData = []
            for stone in data:
                temp = ""
                if stone in LUT.keys():                    
                    temp = LUT[stone]
                else:
                    temp = process(stone)
                
                LUT[stone] = temp
                if(" " in temp):
                    temp = temp.split()
                    for tmp in temp:
                        blinkedData.append(tmp)
                else:
                    blinkedData.append(temp)
            
            data = blinkedData
            #print(len(blinkedData), " : ", blinkedData)
        
    return len(data)
    #data = blinkedData

#part -2 - using recursive and Look up table
LUT1 = {}
def splitStone(stone, loopcount):
    if(stone, loopcount) in LUT1:
        return LUT1[(stone, loopcount)]
    # 0
    if(loopcount == 0):
        result = 1
    elif(stone == 0):
        result = splitStone(1, loopcount-1)    
    # even length
    elif(len(str(stone))%2 == 0):
        first = (str(stone)[:len(str(stone))//2])
        second = (str(stone)[len(str(stone))//2:])        
        result = splitStone(int(first), loopcount-1) + splitStone(int(second), loopcount-1)
    else: #odd length multiply by 2024
        result = splitStone(stone*2024, loopcount-1)

    # add computed result to lookup so we can skip if same combination 
    # occure again for another number
    LUT1[(stone, loopcount)] = result

    return result
    
    
sum = 0
for number in input.split():
    #sum += splitStone_part1([number])
    sum += splitStone(int(number), 75)
    
print(sum) 
 

    



    




