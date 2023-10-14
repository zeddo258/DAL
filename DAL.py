import os
import subprocess
import difflib
import uuid
import shutil
from generate import make_report_html

class Program:
    def __init__(self, name: str) -> None:
        self.name = name
        self.state = None
        self.error_message = None
        self.output = None
        self.link = None


class Auto_Test:
    def __init__(self, upload_folder: str, topic: str, unit: str):
        self.upload_folder = os.path.join('uploads', upload_folder)
        self.topic = topic
        self.unit = unit
        self.standard_answer = None
        self.program_list:list[Program] = []
        self.__initialize_standard_answer()

    def __initialize_standard_answer(self):
        answer_path = os.path.join('command_scripts', self.topic, self.unit)
        answer_txt_path = os.path.join(answer_path, 'answer.txt')
        if not os.path.exists(answer_txt_path):
            result = subprocess.run(["g++", "-std=c++20", 'code.cpp', "-o", 'code'], cwd=answer_path, capture_output=True)
            if result.returncode != 0:
                raise Exception(result.stderr.decode('utf-8', errors='ignore'))
            program = Program('code')
            self.__execute_single_program(program, answer_path)
            with open(answer_txt_path, 'w') as file:
                file.write(program.output)
        with open(answer_txt_path) as file:
            self.standard_answer = file.read().strip()
        

    def __compile(self):
        all_program = [f for f in os.listdir(self.upload_folder) if f.endswith('.cpp')]
        for program_name in all_program:
            program_name_without_extension, extension = os.path.splitext(program_name)
            result = subprocess.run(["g++", "-std=c++20", program_name, "-o", program_name_without_extension], cwd=self.upload_folder, capture_output=True)
            current_program = Program(program_name_without_extension)
            if result.returncode != 0:
                current_program.state = 'Compile_Error'
                current_program.error_message = result.stderr.decode('utf-8', errors='ignore')
            self.program_list.append(current_program)
            os.remove(os.path.join(self.upload_folder, program_name))

    def __copy_all_files(self, src_dir: str, dest_dir: str):
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)
        for item in os.listdir(src_dir):
            s = os.path.join(src_dir, item)
            d = os.path.join(dest_dir, item)
            if os.path.isfile(s):
                shutil.copy2(s, d)
            elif os.path.isdir(s):
                shutil.copytree(s, d)

    def __execute_single_program(self, program: Program, program_folder: str):
        if program.state is not None:
            return
        execute_folder_name = str(uuid.uuid4())
        if os.path.exists(execute_folder_name):
            os.remove(execute_folder_name)
        os.mkdir(execute_folder_name)
        
        data_path = os.path.join('command_scripts', self.topic, 'source')
        self.__copy_all_files(data_path, execute_folder_name)
        
        program_path = os.path.join(program_folder, program.name)
        shutil.copy2(program_path, execute_folder_name)
        
        command_path = os.path.join('command_scripts', self.topic, self.unit, 'command.txt')
        shutil.copy2(command_path, execute_folder_name)
        
        os.remove(os.path.join(program_folder, program.name))
        
        result = subprocess.run(["timeout", "1s", 'expect', '/home/ds/DAL/exp_script.exp', f"./{program.name}", "command.txt"], cwd=execute_folder_name, capture_output=True)
        shutil.rmtree(execute_folder_name)
        if result.returncode != 0:
            program.state = 'Runtime_Error'
        else:
            program.state = 'Success'
            program.output = result.stdout.decode('utf-8', errors='ignore').replace('\r', '').strip()

    def __execute(self):
        for i in range(len(self.program_list)):
            self.__execute_single_program(self.program_list[i], self.upload_folder)
            
    def __compare(self):
        file_list = []
        if not os.path.exists(os.path.join('static', self.upload_folder)):
            os.mkdir(os.path.join('static', self.upload_folder))
        for program in sorted(self.program_list, key=lambda x: x.name):
            if program.state == 'Success':
                student_ans = program.output.split('\n')
                correct_ans = self.standard_answer.split('\n')
                diff = difflib.HtmlDiff().make_file(correct_ans, student_ans, 'Answer', program.name)
                program.link = os.path.join('static', self.upload_folder, f'{program.name}.html')
                with open(program.link, "w") as file:
                    file.write(diff)
            elif program.state == 'Compile_Error':
                formatted_errors = program.error_message.strip().split('\n')
                html_content = "<html><body><h1>編譯錯誤</h1><ul>"
                for err in formatted_errors:
                    html_content += f"<li>{err}</li>"
                html_content += "</ul></body></html>"
                program.link = os.path.join('static', self.upload_folder, f'{program.name}.html')
                with open(program.link, "w") as file:
                    file.write(html_content)
            file_list.append({'name': program.name, 'status': program.state, 'link': program.link})
        make_report_html(file_list, os.path.join('static', self.upload_folder, 'test_report.html'))
        shutil.rmtree(self.upload_folder)
        return os.path.join('static', self.upload_folder, 'test_report.html')
            
    def run(self):
        self.__compile()
        self.__execute()
        return self.__compare()


if __name__ == '__main__':
    auto_test = Auto_Test('test', '老鼠走迷宮', '作業')
    auto_test.run()