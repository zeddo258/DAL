import os
from flask import Flask, render_template, request, send_file, url_for, redirect, session, jsonify
from flask_dropzone import Dropzone
from configparser import ConfigParser
import uuid
import time
from DAL import run


current_user_folder = {}


basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config.update(
    DROPZONE_MAX_FILE_SIZE = 1024,
    DROPZONE_TIMEOUT = 5*60*1000,
    DROPZONE_ALLOWED_FILE_CUSTOM = True,
    DROPZONE_ALLOWED_FILE_TYPE = '.cpp, .c, .txt'
)


config = ConfigParser()
config.read('config.ini')

secret_key = config.get('Settings', 'SECRET_KEY')
app.secret_key = secret_key

dropzone = Dropzone(app)




"""
@app.route('/', methods=['GET','POST'])
def home():
    if (request.method == 'POST'):
        hwork_name = request.form["nm"]
        if (os.path.exists(hwork_name) == False):
          os.mkdir(hwork_name)
        app.config.update(UPLOAD_PATH=os.path.join(basedir,hwork_name))
        return redirect(url_for("upload"))
    else:
        return render_template('index.html')
"""

def get_uid():
    if 'user_id' not in session:
        # 為新使用者生成一個唯一ID
        session['user_id'] = str(uuid.uuid4())
    user_id = session['user_id']
    return user_id


@app.route('/', methods=['GET','POST'])
def upload():
    user_id = get_uid()
    
    if request.method == 'POST':
        if user_id not in current_user_folder:
            unique_path = str(int(time.time())) + '-' + str(uuid.uuid4())
            current_user_folder[user_id] = unique_path
        else:
            unique_path = current_user_folder[user_id]
        file = request.files.get('file')
        save_path = os.path.join('uploads', unique_path)
        if not os.path.exists(save_path):
            os.makedirs(save_path)
        file.save(os.path.join(save_path, file.filename))
    return render_template('upload.html')

@app.route('/exec')
def exec():
    try:
        user_id = get_uid()
        folder_name = current_user_folder[user_id]
        del current_user_folder[user_id]
        result = run(folder_name)
        html_content = render_template('report_list_template.html', result=result)
        
        with open(f"./static/result/{folder_name}/test_report.html", "w") as f:
            f.write(html_content)
        return jsonify({'report_filename': folder_name})
    except Exception as e:
        return jsonify({'error': str(e)}), 500



if __name__ == '__main__':
    app.run(debug=True)
