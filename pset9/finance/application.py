import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_data = db.execute(
        "SELECT a.id, a.cash, b.symbol, b.shares FROM users a LEFT JOIN shares b ON a.id=b.id WHERE a.id=? and b.shares > 0", session["user_id"])

    for i, data in enumerate(user_data):
        response = lookup(data["symbol"])
        user_data[i]["price"] = response["price"]

        user_data[i]["value"] = user_data[i]["shares"] * user_data[i]["price"]

        user_data[i]["total"] = user_data[i]["cash"] + user_data[i]["value"]

    return render_template("index.html", user_data=user_data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        symbol = request.form.get("symbol")

       # Validate that the symbol is not empty.
        if len(symbol) == 0:
            return apology("Symbol can not be empty")

        # Validate the simbol exists
        response = lookup(symbol)

        if response == None:
            return apology("Symbol does not exists")

        # Validates that shares are greater than 0.
        shares = request.form.get("shares")

        try:
            shares = int(shares)
        except:
            return apology("Shares must be an integer")

        if shares <= 0:
            return apology("Shares must be greater than 0")

        shares = int(shares)

        # Checks for the cash the user has.
        user_data = db.execute("SELECT a.* FROM users a WHERE id = ?", session["user_id"])

        # Validate that the user has enough funds to buy the shares.
        buy_cash = shares * response["price"]
        if user_data[0]["cash"] < buy_cash:
            return apology("Not enough money on the account.")

        # Insert the transaction as a record.
        db.execute("INSERT INTO transactions (id, symbol, price, shares, type) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], symbol, response["price"], shares, "buy")

        # Insert or update the transaction in shares.
        check = db.execute("SELECT a.* FROM shares a WHERE a.id = ? and symbol= ?", session["user_id"], symbol)

        # The current share does not exist so we insert it
        if len(check) == 0:
            db.execute("INSERT INTO shares (id, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol, shares)

        # The current share already exist, so we updae it
        if len(check) == 1:
            new_shares = check[0]["shares"] + shares
            db.execute("UPDATE shares SET shares = ? where id = ?", new_shares, session["user_id"])

        # Update the current quantity of cash of the user.
        dif = user_data[0]["cash"] - buy_cash
        db.execute("UPDATE users SET cash = ? where id = ?", dif, session["user_id"])

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT a.* FROM transactions a WHERE a.id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions)
    

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":

        # Gets the symbol the user wants to find.
        symbol = request.form.get("symbol")

        response = lookup(symbol)

        if response == None:
            return apology("No stock symbol could be found")

        return render_template("quoted.html", response=response)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    # Validate the user data for registration.
    if request.method == "POST":

        # First, validates the username
        username = request.form.get("username")

        # Validate if the username is not empty.
        if len(username) == 0:
            return apology("Username can not be empty")

        # Validate if the username does not exist already.
        users = db.execute("SELECT a.username FROM users a WHERE a.username=?", username)
        if len(users) > 0:
            return apology("Username Already Used")

        # Validate that password and confirmation are not empty and do match.
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if len(password) == 0:
            return apology("Password can not be empty")

        if len(confirmation) == 0:
            return apology("Confirmation can not be empty")

        if password != confirmation:
            return apology("Password and Confirmation does not match")

        # If all validations are correct, insert the username and the password in the db.
        # Hash the password before inserting
        password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password)

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        symbols = db.execute("SELECT a.symbol FROM shares a WHERE a.id = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)

    if request.method == "POST":

        symbol = request.form.get("symbol")

        check = db.execute("SELECT a.* FROM shares a WHERE a.id = ? and a.symbol = ?", session["user_id"], symbol)

        shares = request.form.get("shares")

        try:
            shares = int(shares)
        except:
            return apology("Shares must be an integer", 400)

        if shares <= 0:
            return apology("Shares must be greater than 0", 400)

        if len(check) == 0 or check[0]["shares"] < shares:
            return apology("No symbol in your potfolio")

        # Insert the transaction as a record.
        response = lookup(check[0]["symbol"])
        db.execute("INSERT INTO transactions (id, symbol, price, shares, type) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], symbol, response["price"], shares, "sell")

        # Update the share with the sell value
        new_shares = check[0]["shares"] - shares
        db.execute("UPDATE shares SET shares = ? WHERE id = ? and symbol = ?",
                   new_shares, session["user_id"], symbol)

        # Update the current quantity of cash of the user.
        user_data = db.execute("SELECT a.* FROM users a WHERE a.id = ?", session["user_id"])

        sell_cash = shares * response["price"]

        dif = user_data[0]["cash"] + sell_cash
        db.execute("UPDATE users SET cash = ? where id = ?", dif, session["user_id"])

        return redirect("/")


@app.route("/password change", methods=["GET", "POST"])
@login_required
def password_change():

    if request.method == "GET":
        return render_template("password change.html")

    if request.method == "POST":
        password = request.form.get("password")

        if len(password) == 0:
            return apology("New password can not be empty")

        confirmation = request.form.get("confirmation")

        if len(confirmation) == 0:
            return apology("Confirmation can not be empty")

        if password != confirmation:
            return apology("Password and Confirmation do not match")

        password = generate_password_hash(password)
        db.execute("UPDATE users SET hash = ? where id = ?", password, session["user_id"])

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

