# Import The library flask
from flask import Flask, render_template, request

# __name__ refers to the name of the same file, in this case application.py
# Flask turn this same file into an application.
app = Flask(__name__)

# @ python decorator, apply one function to another
@app.route("/", methods=["GET", "POST"])
def index():
    # Function that searches for the name of the template and return its contents [First argument].
    # Function that let store in a variable an argument passed in the url.
    if request.method == "GET":
        return render_template("index.html")
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))