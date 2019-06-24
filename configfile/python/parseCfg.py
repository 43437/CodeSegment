import configparser

cf=configparser.ConfigParser()

print("**********begin**********\n")

print("**********read**********")
''' read '''
cf.read("test.cfg")
val="default"
try:
    val=cf.get("default", "test1")
    print(cf.items("main"))
    print(cf.items("default"))
    print(val)
except Exception:
    pass
    

''' write '''
print("**********write**********")
cf1=configparser.ConfigParser()
cf1.add_section("section1")
cf1.set("section1", "key1", "1")
cf1.set("section1", "key2", "2")

cf1.add_section("section2")
#cf1.set("section2", "key2_1", 1)

with open("testw.cfg", "w") as f:
    cf1.write(f)

print("**********end**********")