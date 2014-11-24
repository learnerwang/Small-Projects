file1=open('z_Namelist.txt','r')
for i in range(0,269):
    name=file1.readline()
    name=name.rstrip('\n')
    print name
    file = open('webs\\'+str(i)+'.html','r')
    str1=file.read()
    file.close()
    print str1.find(name)
    str1=str1[str1.find(name):]
    print str1
    file = open('webs\\'+str(i)+'.html','w')
    file.write(str1)
    file.close()