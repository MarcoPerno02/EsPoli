import os
from flask import Flask, render_template, request
from flask_bootstrap import Bootstrap
from flask_wtf import FlaskForm
from flask_wtf.file import FileField
import wtforms

app = Flask(__name__)
app.config['SECRET_KEY'] = 'chiave-segreta'  # Chiave segreta necessaria per WTForms
bootstrap = Bootstrap(app)

users = [
    {"id": 1, "username": "Marcoo", "filenameUserImg": "img1.jpg"},
    {"id": 2, "username": "Luk", "filenameUserImg": "img1.jpg"},
    {"id": 3, "username": "Diego", "filenameUserImg": "img1.jpg"},
]

posts = [
    {"id": 1, "filenameImg": "img1.jpg", "date": "2 giorni fa", "user_id": 1,
        "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "},
    {"id": 2, "filenameImg": "img1.jpg", "date": "5 giorni fa", "user_id": 2,
        "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "},
    {"id": 3, "filenameImg": "img1.jpg", "date": "1 giorni fa", "user_id": 3,
        "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "},
]

chisiamo_info = [
    {
        "id": 1, "filenameUserImg": "img1.jpg", "username": "Marcoo", "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    },
    {
        "id": 2, "filenameUserImg": "img1.jpg", "username": "Luk", "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    },
    {
        "id": 3, "filenameUserImg": "img1.jpg", "username": "Pablo", "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    }
]


@app.route('/')
def index():
    upload_form = UploadForm()  # Crea un'istanza del tuo form
    tmp = []
    for post in posts:
        dict_tmp = post
        for user in users:
            if (user["id"] == post["user_id"]):
                dict_tmp["username"] = user["username"]
                dict_tmp["filenameUserImg"] = user["filenameUserImg"]
                break
        tmp.append(dict_tmp)
    return render_template('index.html', posts=tmp, form=upload_form)


@app.route('/post')
def post():
    id = int(request.args.get('id'))
    for post in posts:
        if (post["id"] == id):
            for user in users:
                if (user["id"] == post["user_id"]):
                    post["username"] = user["username"]
                    post["filenameUserImg"] = user["filenameUserImg"]
                    return render_template('post.html', post=post)


@app.route("/chisiamo")
def chisiamo():
    return render_template('chisiamo.html', posts=chisiamo_info)


class UploadForm(FlaskForm):
    fileToUpload = FileField('Seleziona un file')
    userIdToUpload = wtforms.IntegerField("Inserisci userId")
    descriptionToUpload = wtforms.StringField('Descrizione per il caricamento del file')

def get_unique_filename(upload_folder, filename):
    """Ritorna un nome di file unico nella cartella di upload."""
    base, ext = os.path.splitext(filename)
    counter = 1
    while os.path.exists(os.path.join(upload_folder, filename)):
        filename = f"{base}_{counter}{ext}"
        counter += 1
    return filename

@app.route('/upload', methods=['POST'])
def upload_file():
    form = UploadForm(request.form)

    if 'fileToUpload' not in request.files:
        return "Nessun file selezionato"
    
    file = request.files['fileToUpload']

    if file.filename == '':
        return "Nessun file selezionato"
    
    tmp = file.filename.split('.')
    if tmp[1] != "png" and tmp[1] != "jpg" and tmp[1] != "jpeg":
        return "Formato file non valido"

    descriptionToUpload = form.descriptionToUpload.data
    
    if descriptionToUpload == "":
        return "Descrizione vuota"

    userIdToUpload = int(form.userIdToUpload.data)
    
    if userIdToUpload == None:
        return "UserId vuoto"

    found = 0
    i = 0
    while found == 0 and i < users.__len__():
        if users[i]["id"] == userIdToUpload:
            found = 1
        else:
            i+=1
    
    if found == 0:
        return "UserId Non Esistente"

    unique_filename = get_unique_filename('static/', file.filename)
    file.save('static/' + unique_filename)

    tmp = {}
    tmp["id"] = posts[-1]["id"] + 1
    tmp["user_id"] = userIdToUpload
    tmp["description"] = descriptionToUpload
    tmp["filenameImg"] = unique_filename
    tmp["date"] = "Ora"
    posts.append(tmp)

    return "Caricamento completato con successo!"

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=3000, debug=True)
