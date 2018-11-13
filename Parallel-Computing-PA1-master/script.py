with open("./in.txt") as file:
    with open("./out.csv", "w") as out:
        count = 1
        for line in file.readlines():
            line = line.replace("\n", "")
            for word in line.split(" "):
                if(word[0] >= "0" and word[0] <= "9" and len(word) > 3):
                    if(count == 3):
                        count = 1
                        out.write(word+"\n")
                    else:
                        count += 1
                        out.write(word+",")
                    
