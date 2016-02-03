from flask import Flask , render_template, request
from prettytable import PrettyTable
import pymysql
import os


def connectDB():
    global DB
    DB = pymysql.connect(host='localhost',
                        user='arduino',
                        password='arduino',
                        db='arduinodb')
    return

def disconnectDB():
    if DB:
        DB.close()
        return


def dbprint(DB_Name):
    try:
        connectDB()
        with DB.cursor() as cursor:
            sql = "select * from arduinodb." + DB_Name
            cursor.execute(sql)
            rows = cursor.fetchall()
            columns = cursor.description
            desc = []
            for item in columns:
                desc.append(item[0])
            T = PrettyTable(desc)
            for row in rows:
                T.add_row([item for item in row])
            disconnectDB()
            return T.get_html_string()
            # + ''' <meta http-equiv="refresh" content="1">'''
    finally:
        #DB.close()
        #return
        True

app = Flask(__name__)

extra_dirs = ['templates',]
extra_files = extra_dirs[:]
for extra_dir in extra_dirs:
    for dirname, dirs, files in os.walk(extra_dir):
        for filename in files:
            filename = os.path.join(dirname, filename)
            if os.path.isfile(filename):
                extra_files.append(filename)
@app.route('/')
def hello_world():
    return 'Hello World!'


@app.route('/home')
def index():
    return render_template("index.html")
    #return dbprint('bioterio_01')
    print("DONE")


@app.route('/dumb', methods= ['GET'])
def dumb():
    content = dbprint("bioterio_01")
    user = "Scolari"
    return render_template("dumb.html", **locals())


@app.route('/test', methods = ('GET', 'POST'))
def test():
    if request.method == 'GET':
        with open(os.path.join('templates', 'index.html'),'w') as f:
            f.write(dbprint('bioterio_01'))
            f.close()
            return render_template("index.html")


if __name__ == '__main__':
    app.run(host = "10.221.5.120", port = 80, debug = True, use_reloader = True)
            #extra_files=extra_files)
