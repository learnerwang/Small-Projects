from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponseRedirect
from django.template import Context,Template

searchtext ='''<title>Supervisor Search Engine_By Fanzy</title>
<form method="GET" action="/search">
<img src="logo.jpg" width="193" height="116" />
<input type="text" name="q" size = 70>
<input type="submit" value="click me-____-"/>
</from>
'''

class my_list(object):
	def __init__(self,num,url,name,post):
		self.num=(int)(num)
		self.url=url
		self.name=name
		self.post=post

def buildindex():
	file=open("mysite\z_sort.txt","r")
	invertedlist={}
	global namelist
	global urllist
	line= file.readline()
	while line:
		line1=line[line.find(" ")+1:]
		name=line[0:line.find(" ")]
		list1=line1.split()
		list2=[]
		for str1 in list1:
			i=(int)(str1)
			#file1=open("mysite\webs\\"+str1+".html")
			#filestr1=file1.read()
			#filestr=filestr1.upper()
			t=my_list(i,urllist[i],namelist[i],"")
			'''if (filestr.upper().find(name)<50):
				str2=filestr1[0:filestr.find(name)+len(name)+200]+"..."
				str3=str2.replace(name,"<FONT color=#FF0000>"+name+"</FONT>")
				name=name.lower()
				str3=str3.replace(name,"<FONT color=#FF0000>"+name+"</FONT>")
				name=name[0:1].upper()+name[1:].lower()
				str3=str3.replace(name,"<FONT color=#FF0000>"+name+"</FONT>")
				t=my_list(i,urllist[i],namelist[i],str3)
			else:
				str2="..."+filestr1[filestr.find(name)-49:filestr.find(name)+len(name)+200]+"..."
				str3=str2.replace(name,"<FONT color=#FF0000>"+name+"</FONT>")
				name=name.lower()
				str3=str3.replace(name,"<FONT color=#FF0000>"+name+"</FONT>")
				name=name[0:1].upper()+name[1:].lower()
				str3=str3.replace(name,"<FONT color=#FF0000>"+name+"</FONT>")
				t=my_list(i,urllist[i],namelist[i],str3)'''
			name=name.upper()
			list2.append(t)
		invertedlist[name.upper()]=list2
		line= file.readline()
	file.close()
	return invertedlist

def buildnameindex():
	namelist=[]
	file=open("mysite\z_NameList.txt","r")
	line= file.readline()
	while line:
		namelist.append((line.rstrip('\n')).upper())
		line=file.readline()
	file.close()
	return namelist

def buildurlindex():
	urllist=[]
	file=open("mysite\z_UrlList.txt","r")
	line= file.readline()
	while line:
		urllist.append(line.rstrip('\n'))
		line=file.readline()
	file.close()
	return urllist



urllist = buildurlindex()
namelist = buildnameindex()

text = Template("""<title>Supervisor Search Engine_By Fanzy</title>
<form method="GET" action="/search">
<img src="logo.jpg" width="193" height="116" />
<input type="text" name="q" size = 70 value = "{{search|safe}}">
<input type="submit" value="click me-____-"/>
</from>
<br> Keywords are : {{search}}
<br> Results are : <br>
{% for list in result_list %}
	<li><a href={{list.url}}><FONT font-size=24>{{list.name}}</FONT></a><br>
	{% autoescape off %} 
	<FONT color=#000000 font-size=14>{{list.post}}</FONT><br>
	{% endautoescape %}
	<FONT font-size=12px color=#009900>{{list.url}}</FONT>
	</li>
{% endfor %}
<br>
<br>Click <a href="/search">here</a> to return.""")

text_no = Template("""<title>Supervisor Search Engine_By Fanzy</title>
<form method="GET" action="/search">
<img src="logo.jpg" width="193" height="116" />
<input type="text" name="q" size = 70 value = "{{search|safe}}">
<input type="submit" value="click me-____-"/>
</from>
<br> Keywords are : {{search}}
 <br> No results! <br>
<br>Click <a href="/search">here</a> to return.""")



@csrf_exempt
def index(request):
	invertedlist = buildindex()
	if not request.GET.has_key('q'):
		return HttpResponse(searchtext)
	else:
		para = request.GET['q']
		para = (str(para).rstrip(' '))
		anslist=[]
		anslist1=[]
		if (para.upper() in namelist):
			return HttpResponseRedirect(urllist[namelist.index(para.upper())])
		else:
			paralist = para.split()
			if not invertedlist.has_key(paralist[0].upper()):
				c=Context( { 'search' :request.GET['q'] } )
				text_no.render(c)
				return HttpResponse(text_no.render(c))
			anslist=invertedlist[paralist[0].upper()]
			for parai in paralist:
				if parai==paralist[0]:
					continue
				if not invertedlist.has_key(parai.upper()):
					c=Context( { 'search' :request.GET['q'] } )
					text_no.render(c)
					return HttpResponse(text_no.render(c))
				anslist1=invertedlist[parai.upper()]
				deletelist=[]
				for ans1 in anslist:
					flag=False
					for ans2 in anslist1:
						if ans1.num==ans2.num:
							flag=True
							break
					if not flag:
						deletelist.append(ans1)
				for ans3 in deletelist:
					anslist.remove(ans3)
			if len(anslist)==0:
				c=Context( { 'search' :request.GET['q'] } )
				text_no.render(c)
				return HttpResponse(text_no.render(c))
			for i in anslist:
				i.post=""
				file1=open("mysite\webs\\"+str(i.num)+".html",'r')
				filestr1=file1.read().decode('utf-8')
				filestr=filestr1.upper()
				for j in request.GET['q'].split():
					j=j.upper()
					if (filestr.upper().find(j)<50):
						str2=filestr1[0:filestr.find(j)+len(j)+200]+"..."
						str3=str2.replace(j,"<FONT color=#FF0000>"+j+"</FONT>")
						j=j.lower()
						str3=str3.replace(j,"<FONT color=#FF0000>"+j+"</FONT>")
						j=j[0:1].upper()+j[1:].lower()
						str3=str3.replace(j,"<FONT color=#FF0000>"+j+"</FONT>")
						i.post=i.post+str3+"<br>"
					else:
						str2="..."+filestr1[filestr.find(j)-49:filestr.find(j)+len(j)+200]+"..."
						str3=str2.replace(j,"<FONT color=#FF0000>"+j+"</FONT>")
						j=j.lower()
						str3=str3.replace(j,"<FONT color=#FF0000>"+j+"</FONT>")
						j=j[0:1].upper()+j[1:].lower()
						str3=str3.replace(j,"<FONT color=#FF0000>"+j+"</FONT>")
						i.post=i.post+str3+"<br>"
			c = Context( {  'search' :request.GET['q'],
							'result_list' : anslist ,
						   'namelist' : namelist, 'urllist' : urllist} )
			return HttpResponse(text.render(c))

