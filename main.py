import os
from flask import Flask, render_template, request, session, jsonify, session, redirect, url_for
from configparser import ConfigParser
import uuid
import time
from DAL import Auto_Test
from datetime import timedelta

all_upload_information = {}


basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)

config = ConfigParser()
config.read('config.ini')

secret_key = config.get('Settings', 'SECRET_KEY')
app.secret_key = secret_key


@app.before_request
def make_session_permanent():
    session.permanent = True
    app.permanent_session_lifetime = timedelta(days=1)


def get_uid():
    if 'user_id' not in session:
        # 為新使用者生成一個唯一ID
        session['user_id'] = str(uuid.uuid4())
    user_id = session['user_id']
    return user_id


@app.route('/')
def home():
    if 'username' not in session:
        return redirect(url_for('login'))
    get_uid()
    return render_template('index.html')


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # 驗證用戶（這裡應使用更安全的方式）
        if username == 'lab214b' and password == 'LaB214b@2654737':
            session['username'] = username
            return redirect(url_for('home'))
        else:
            return '登入失敗，豪哥請手下留情QQ'
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.clear()  # 清空session
    return redirect(url_for('home'))


@app.route('/upload', methods=['POST'])
def upload():
    if 'username' not in session:
        return redirect(url_for('login'))
    user_id = get_uid()
    if user_id not in all_upload_information:
        unique_path = str(int(time.time())) + '-' + str(uuid.uuid4())
        all_upload_information[user_id] = {'upload_folder': unique_path}
    else:
        unique_path = all_upload_information[user_id]['upload_folder']

    file = request.files.get('file')
    if file is None:
        all_upload_information[user_id].update(request.json)
    else:
        save_path = os.path.join('uploads', unique_path)
        if not os.path.exists(save_path):
            os.makedirs(save_path)
        file.save(os.path.join(save_path, file.filename))
    return '', 200


@app.route('/upload_complete', methods=['POST'])
def upload_complete():
    if 'username' not in session:
        return redirect(url_for('login'))
    user_id = get_uid()
    if user_id in all_upload_information:
        current_information = all_upload_information[user_id]
        del all_upload_information[user_id]
        if not os.path.exists(os.path.join('uploads', current_information['upload_folder'])):
            return jsonify({'link': 'None'})
        auto_test = Auto_Test(**current_information)
        report_link = auto_test.run()
        return jsonify({'link': report_link})
    return jsonify({'link': 'None'})


@app.route('/hw_list', methods=['GET'])
def hw_list():
    if 'username' not in session:
        return redirect(url_for('login'))
    all_options = os.listdir('command_scripts')
    return jsonify(all_options)


if __name__ == '__main__':
    app.run()
