import sys

if (len(sys.argv) != 3):
    print("Wrong command format")
    quit()

coms = []
with open(sys.argv[1], "r") as prog:
    for line in prog:
        line = line.strip('\n')
        if "!" in line or line == "":
            # comment
            continue
        if '|->' in line:
            coms.append([1, *map(lambda x: x.strip(), line.split('|->'))])
        elif '->' in line:
            coms.append([0, *map(lambda x: x.strip(), line.split('->'))])
        else:
            print("SYNTAX ERROR near", line)
            exit(0)

with open(sys.argv[2], "r") as input:
    res = input.readline().strip('\n')
    print("starting state", res)
    run = 1
    while run:
        for i in coms:
            if i[1] in res:
                res = res.replace(i[1], i[2], 1)
                run = not i[0]
                break
        else:
            break
        print(res)
    print("RESULT state", res)