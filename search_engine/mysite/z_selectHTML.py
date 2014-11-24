#-*- encoding: gb2312 -*-
import HTMLParser, urllib2, urllib, string


class readParser(HTMLParser.HTMLParser):
    def handle_data(self,data):
        global file1
        file1.write(data+" ")

if __name__ == '__main__':
    num = 0
    urllist = []
    namelist = []
    file1 = open("UrlList.txt","r")
    file1.close()
    file= open("UrlList.txt",'r')
    file2=open("NameList1.txt","w")
    line= file.readline()
    while line:
        try:
            usock = urllib.urlopen(line)
        except:
            line=file.readline()
            continue
        str1=usock.read()
        '''if (not ((str1.find(r'<div class="name">') ==-1)or(str1.find('Professor')==-1)or(str1.find('<div class="jobTitle">')==-1))):
            teacher_name=str1[str1.find(r'<div class="name">')+28 : 
                              str1.find('</div>' , str1.find(r'<div class="name">')+28 )-5 ]'''
        if (not str1.find('teacher-name')==-1):
            teacher_name=str1[str1.find(r'teacher-name')+22 : 
                              str1.find('</strong>' , str1.find(r'teacher-name')+22 ) ]

            teacher_name=teacher_name.lstrip(' ')
            teacher_name=teacher_name.rstrip('\n')
            teacher_name=teacher_name.rstrip(' ')
            teacher_name=teacher_name.rstrip('\n')
            namelist.append(teacher_name)
            file2.write(teacher_name)
            file2.write('\n')
            #print num
            #print teacher_name
            #print line
            file1=open("webs\\"+str(num)+".html","w")
            readparser = readParser()
            readparser.feed(str1)
            usock.close()
            readparser.close()
            urllist.append(line.rstrip('\n'))
            num=num+1
            file1.close()
        line=file.readline()
    print num
    file2.close()
    file.close()
    file = open("UrlList1.txt",'w')
    for str in urllist:
        file.write(str)
        file.write("\n")
    file.close()
    
