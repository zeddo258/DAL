import os
from flask import Flask, render_template, request
from flask_dropzone import Dropzone

basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config.update(
    UPLOAD_PATH = os.path.join(basedir,'files'),
    DROPZONE_MAX_FILE_SIZE = 1024,
    DROPZONE_TIMEOUT = 5*60*1000
)

dropzone = Dropzone(app)
@app.route('/', methods=['GET','POST'])

def upload():
    if request.method == 'POST':
        file = request.files.get('file')
        file.save(os.path.join(app.config['UPLOAD_PATH'], file.filename) )
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)