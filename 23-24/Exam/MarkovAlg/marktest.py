import sys

# loading program and test
# format to call tester
# python3 marktest.py <PROGRAM> <TESTCASE>
# program will print result of program
# in case program never stops, KILL IT <CTRL C>

if len(sys.argv) != 3:
    print("PROGRAM or TEST is missing")
    quit()

# loading program
# spaces are being ignored
comms = []
with open(sys.argv[1], "r") as prog:
    for com in prog:
        com = com.strip("\n")
        
        if "?" in com:
            # this is comment
            continue
        if com == "":
            # this is an empty string
            continue

        if "|->" in com:
            comms.append([1, *map(lambda x:x.strip(), com.split("|->"))])
        elif "->" in com:
            comms.append([0, *map(lambda x:x.strip(), com.split("->"))])
        else:
            print("SYNTAX ERROR in ", com)
            prog.close()
            quit()

# check how you program was loaded
print(*comms, sep='\n')

# executing program
with open(sys.argv[2], "r") as testcase:
    testc = testcase.readline().strip("\n")
    print("Staring state:", testc)
    run = True
    while run:
        for com in comms:
            if testc.count(com[1]):
                testc = testc.replace(com[1], com[2], 1)
                run = not com[0]
                break
        else: run = 0
        print(testc)
    print("Resuting state:", testc)