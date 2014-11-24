#-*- encoding: gb2312 -*-
import HTMLParser, urllib2, urllib, string

class MyParser(HTMLParser.HTMLParser):
    def __init__(self, url):
        HTMLParser.HTMLParser.__init__(self)  
        self.url = url
        self.list =[]
        
    def handle_starttag(self, tag, attrs):
        global urllist
        if tag == 'a':
            for name,value in attrs:
                if name == 'href':
                    if value.startswith('/'):
                        t = self.url.find('/',7)
                        url1=self.url[0:t]+value.rstrip('/')
                        if (url1 not in urllist)and("cs" in url1):
                            urllist.append(url1.rstrip('/'))
                            self.list.append(url1.rstrip('/'))
                    elif value.startswith('http://'):
                        url1=value.rstrip('/')
                        if (url1 not in urllist)and("cs" in url1):
                            urllist.append(value.rstrip('/'))
                            self.list.append(value.rstrip('/'))
    

class readParser(HTMLParser.HTMLParser):
    def handle_data(self,data):
        global file1
        file1.write(data+" ")

def getURL(url):
    global file1
    try:
        usock = urllib.urlopen(url)
    except:
        print 'get url excepton'
        print url
        return []
    if ("cs" not in url):
        return []
    else:
        parser = MyParser(url.rstrip('/'))
        parser.feed(usock.read())
        usock.close()
        parser.close()
        urls = parser.list
        return urls

def spider(startURL, depth):
    global file
    global file1
    i = 0
    global num
    if depth <= i:
        return 0
    else:
        
        urls = getURL(startURL)
        if len(urls) > 0:
            for url in urls:
                file.write(url)
                file.write("\n")
                num = num + 1
                spider(url,depth - 1)
        else:
            return 0
    return 1

if __name__ == '__main__':
    num = 0
    urllist = []
    #file= open("UrlList.txt",'r')
    #line= file.readline()
    #global file1
    '''while line:
        file1=open(str(num)+".html","w")
        usock = urllib.urlopen(line)
        readparser = readParser()
        readparser.feed(usock.read())
        usock.close()
        readparser.close()
        urllist.append(line.rstrip('\n'))
        num=num+1
        line=file.readline()
        file1.close()
    print num'''
    #file.close()
    file = open("UrlList.txt",'w')
    spider('http://www.cs.tsinghua.edu.cn/publish/csen/4922/index.html',3)
    print "over"
    print num
    file.close()
    