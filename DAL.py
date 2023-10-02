import os
import subprocess
import difflib
from zipfile import ZipFile, ZIP_DEFLATED


def getFileName():
    fileName = []
    for x in os.listdir('.'):
        fName = os.path.basename(x)
        if ".c" in fName:
            fileName.append(fName)
    return fileName


def compileFile(fileName: list[str]):
    '''
      This function is to compile the code into executable 
    '''
    # To do: extract student ID from fileName
    execFileNames = []
    
    
    for file in fileName:
        exe = file[0:file.rfind('.')]
        std = subprocess.run(["g++", file, "-o", exe], capture_output=True)
        if (os.path.exists(exe) == True):
            print("Compile status: ", exe, " success !!")
            execFileNames.append(exe)
        else:
            errLog = exe + "_errLog.txt"
            file = open(errLog, "w+")
            file.write(std.stderr.decode())
            file.close()
            print("Compile status: ", exe, " failed, error available at :", errLog)
    return execFileNames


def executeFile(execFileNames):
    '''
      This function take testing case number and exec file
    '''
    ansFileNames = []
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
        exePath = "./" + exe  # Exec command
        subprocess.run([exePath], stdin=commands, stdout=file)
        print("\nSuccessfully execute", exe)

        file.close()
        commands.close()
    return ansFileNames


def compareFile(ansFileNames: list[str], folder_name: str):
    ans_path = "ans.txt"
    
    report_list = []
    for file in ansFileNames:
        print("Checking student:", file)
        # Opening file for comparision
        student_ans = open(file, encoding="big5").readlines()
        correct_ans = open(ans_path).readlines()
        # Create html content
        # to display different
        diff = difflib.HtmlDiff().make_file(student_ans, correct_ans, ans_path, file)

        # Write html to file and save it
        report_name = file[0:file.rfind('_')] + '_compare.html'
        report_folder_path = "../../static/result/" + folder_name
        if not os.path.exists(report_folder_path):
            os.makedirs(report_folder_path)
        with open(os.path.join(report_folder_path, report_name), "w") as file:
            file.write(diff)
        report_list.append(report_name)
    return report_list


def run(folder_name: str):
  try:
    folder_path = os.path.join('uploads', folder_name)
    os.chdir(folder_path)

    fileName = getFileName()
    execFileNames = compileFile(fileName)
    ansFileNames = executeFile(execFileNames)
    result = compareFile(ansFileNames, folder_name)
    return zip(fileName, result)
  finally:
    os.chdir('../..')
