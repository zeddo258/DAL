import os
from flask import Flask, render_template, request, session, jsonify
from configparser import ConfigParser
import uuid
import time
#from DAL import run


current_upload_information = {}


basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)


config = ConfigParser()
config.read('config.ini')

secret_key = config.get('Settings', 'SECRET_KEY')
app.secret_key = secret_key


def get_uid():
    if 'user_id' not in session:
        # 為新使用者生成一個唯一ID
        session['user_id'] = str(uuid.uuid4())
    user_id = session['user_id']
    return user_id



@app.route('/')
def index_page():
    get_uid()
    return render_template('index.html')


@app.route('/upload', methods=['POST'])
def upload():
    user_id = get_uid()        
    if user_id not in current_upload_information:
        unique_path = str(int(time.time())) + '-' + str(uuid.uuid4())
        current_upload_information[user_id] = {'path': unique_path}
    else:
        unique_path = current_upload_information[user_id]['path']
        
    file = request.files.get('file')
    if file is None:
        current_upload_information[user_id].update(request.json)
    else:
        save_path = os.path.join('uploads', unique_path)
        if not os.path.exists(save_path):
            os.makedirs(save_path)
        file.save(os.path.join(save_path, file.filename))
    return '', 200


@app.route('/hw_list', methods=['GET'])
def hw_list():
    all_options = os.listdir('command_scripts')
    return jsonify(all_options)


@app.route('/exec')
def exec():
    try:
        user_id = get_uid()
        folder_name = current_upload_information[user_id]
        del current_upload_information[user_id]
        print("Running...")
        result = run(folder_name)
        html_content = render_template('report_list_template.html', result=result)

        with open(f"./static/result/{folder_name}/test_report.html", "w") as f:
            f.write(html_content)
        return jsonify({'report_filename': folder_name})
    except Exception as e:
        return jsonify({'error': str(e)}), 500


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=11111)
