import os
import subprocess

def getFileName(fileName, pathName):
  for x in os.listdir(pathName):
    fName = os.path.basename(x)
    if ".c" in fName:
      fileName.append(fName)

def getDir():
  pathName = input("Insert HOMEWORK name !!! ") 
  while ( os.path.exists(pathName) == False ):
    print("Homework directory doesn't exist!!!! ")
    pathName = input("Insert HOMEWORK name !!! ")
  return pathName


def compileFile(fileName, pathName, execFileNames):
  '''
    This function is to compile the code into executable 
  '''
  wd = os.getcwd() # current working dir 
  os.chdir(wd + '/' + pathName ) # Change to the dir in which contain student code 
  #To do: extract student ID from fileName
  for file in fileName:
    exe = file[0:file.find('_')]
    std = subprocess.run(["g++", file, "-o" ,exe], capture_output=True)
    if (os.path.exists(exe) == True ):
      print("Compile status: ", exe, " success !!")
      execFileNames.append(exe)
    else: 
      errLog = exe + "_errLog.txt" 
      file = open(errLog, "w+")
      file.write(std.stderr.decode())
      file.close()
      print("Compile status: ", exe, " failed, error available at :", errLog)   

def executeFile(execFileNames):
  '''
    This function take testing case number and exec file
  '''
  commands = open("command.txt")
  for exe in execFileNames:
    #To do: execute exe file with ./$filename
    ansFile = exe + "_ans.txt" 
    file = open(ansFile, "w+")
    commands = open("command.txt")
    print("\nCurrently running :", exe)
    exePath = "./" + exe 
    log = subprocess.run([exePath], stdin=commands, stdout=file)
    file.close()



def main():
  fileName = []
  pathName = getDir() 
  execFileNames = []
  getFileName(fileName, pathName)
  compileFile(fileName, pathName, execFileNames) 
  executeFile(execFileNames)

if __name__ == "__main__":
  main()
  

