import os,sys,json
path_to_library =os.path.join(os.path.dirname(__file__),"httplib2/python3")
sys.path.append(path_to_library)
import httplib2
http = httplib2.Http()

if 0:
    url ="http://172.20.10.2/toggle"
    response,content  = http.request(url,"GET")
    print (response)

url_json="http://172.20.10.2/jblink"
headers={"Content-Type":"application/json;charset=UTF-8"}
data ={"times": "10","pause" : "200"}
response,content=http.request(url_json,"POST",headers=headers,body=json.dumps(data))
print (response)


