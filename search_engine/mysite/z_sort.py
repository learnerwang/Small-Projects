file1=open('z_Wordlist.txt','r')
wordlist=file1.read()
wordlist1=wordlist.split('\n')
for t in wordlist1:
    list=[]
    for i in range(0,269):
        file=open("webs\\"+str(i)+".html","r")
        filestr=file.read().upper()
        if not filestr.find(t) ==-1:
            list.append(i)
        file.close()
    if len(list)>2:
        file=open("z_sort.txt","a")
        file.write(t+' ')
        for str1 in list:
            file.write(str(str1)+" ")
        file.write("\n")
        file.close()