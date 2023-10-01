import os
import subprocess
import difflib
from zipfile import ZipFile, ZIP_DEFLATED


def getFileName(fileName, pathName):
  if (os.path.exists(pathName) == False):
    os.chdir("..")
  for x in os.listdir(pathName):
    fName = os.path.basename(x)
    if ".c" in fName:
      fileName.append(fName)

def getDir():
  return "code"


def zipFile():
  zip_path = './ans.zip'
  dir = './ans'
  
  with ZipFile(zip_path, 'w',ZIP_DEFLATED) as zip:
    for file in os.listdir(dir):
      fileDir = dir + '/' + file
      zip.write(fileDir, arcname=file)


def compileFile(fileName, pathName, execFileNames):
  '''
    This function is to compile the code into executable 
  '''
  wd = os.getcwd() # current working dir 
  os.chdir(wd + '/code' ) # Change to the dir in which contain student code 
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

def executeFile(execFileNames, ansFileNames):
  '''
    This function take testing case number and exec file
  '''
  # Get command
  for exe in execFileNames:
    # Student answer file
    ansFile = exe + "_ans.txt" 
    ansFileNames.append(ansFile)
    file = open(ansFile, "w+")
    # Get command
    commands = open("command.txt")
    # Start executing
    print("\nCurrently running :", exe)
    exePath = "./" + exe # Exec command
    subprocess.run([exePath], stdin=commands, stdout=file)
    print("\nSuccessfully execute", exe)

    file.close()
    commands.close()

  
def compareFile(ansFileNames):
  ans_path = "ans.txt"
  for file in ansFileNames:
    print("Checking student:", file)
    # Opening file for comparision
    student_ans = open(file, encoding="big5").readlines()
    correct_ans = open(ans_path).readlines()
    # Create html content 
    # to display different
    diff = difflib.HtmlDiff().make_file(student_ans, correct_ans, ans_path, file)

    # Write html to file and save it 
    report = file[0:file.find('_')] + '_res.html'
    dir = "../ans/" + report
    diff_report = open(dir, 'w+')
    diff_report.write(diff)
    diff_report.close()


def run():
  fileName = []
  pathName = getDir() 
  execFileNames = []
  ansFileNames = []
  
  getFileName(fileName, pathName)
  compileFile(fileName, pathName, execFileNames) 
  executeFile(execFileNames,ansFileNames)
  compareFile(ansFileNames)
  
  os.chdir('..')
  zipFile()
   
  

