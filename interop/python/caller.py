from subprocess import *
import threading
import time

def run():
    # p=Popen(['../c++/ConsoleEcho/build/consoleEcho', 'python'], stdin=PIPE, stdout=PIPE) #run like exec
    # p=Popen('../c++/ConsoleEcho/build/consoleEcho python', shell=True, stdin=PIPE, stdout=PIPE)   #run as terminal cmd
    # p=Popen(['java', '-jar', '../java/ConsoleEcho.jar', 'python'], stdin=PIPE, stdout=PIPE) #java call
    p=Popen(['nodejs', '../nodejs/consoleEcho.js', 'python'], stdin=PIPE, stdout=PIPE) #java call

    while True:
        line = p.stdout.readline()
        if not line:
            break
        print(line)

w = threading.Thread(target=run)

w.start()