import sys

if __name__=="__main__":
    if len(sys.argv)>1:
        print("python: Hello "+sys.argv[1])
    else:
        print("python: Hello world")
