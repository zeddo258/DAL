import os
from flask import Flask, render_template, request, send_file
from flask_dropzone import Dropzone
from DAL import run
basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config.update(
    UPLOAD_PATH = os.path.join(basedir,'code'),
    DROPZONE_MAX_FILE_SIZE = 1024,
    DROPZONE_TIMEOUT = 5*60*1000,
    DROPZONE_ALLOWED_FILE_CUSTOM = True,
    DROPZONE_ALLOWED_FILE_TYPE = '.cpp, .c, .txt'
)

dropzone = Dropzone(app)
@app.route('/', methods=['GET','POST'])
def upload():
    if request.method == 'POST':
        file = request.files.get('file')
        file.save(os.path.join(app.config['UPLOAD_PATH'], file.filename) )
    return render_template('index.html')

@app.route('/exec')
def exec():
    res = run()
    #should return the list html compare
    return send_file('./ans.zip')



if __name__ == '__main__':
    app.run(debug=True)
