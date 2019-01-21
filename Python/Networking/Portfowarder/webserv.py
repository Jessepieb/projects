from flask import Flask, render_template
import sys
import random

app = Flask(__name__)
colourarray = ["Blue", "Red", "Green"]

def GetColour():

    return colourarray[int(servport-8000)-1]


@app.route('/')
def index():
    return render_template((GetColour()+"/index.html"), name=None)


def main():
    global servport
    servport = int(sys.argv[1])

    if (servport != None):
        app.run(debug=True, host='0.0.0.0', port=servport)
    else:
        app.run(debug=True, host='0.0.0.0', port=8001)
main()