wordlist = []
for i in range(0,269):
    file = open('webs/'+str(i)+'.html','r')
    str4 = file.read()
    file.close()
    str4=str4.upper()
    str4=str4.replace('(',' ')
    str4=str4.replace(')',' ')
    str4=str4.replace(',',' ')
    str4=str4.replace('.',' ')
    list = str4.split()
    for str1 in list:
        str2=str1.lstrip(' ')
        str2=str2.rstrip(' ')
        if str2.isalpha() == False:
            continue
        if len(str2)<3:
            continue
        if not str2 in wordlist:
            wordlist.append(str2)
file = open("z_Wordlist.txt","w")
for str3 in wordlist:
    file.write(str3)
    file.write('\n')
file.close()