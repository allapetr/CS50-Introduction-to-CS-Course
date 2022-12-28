import os
import datetime
#import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Declare global variables
SYMBOLS = {

}

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

    # Query database for symbol and shares the user currently has
    uid = session["user_id"]
    rows = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares)>0", uid)

    # Create new list of dictionary to store info needed for table
    result = []

    # Initialize variable which will caontain all totals
    total_stocks = 0

    # Loop through rows of database and create all needed info for table for each symbol
    for row in rows:

        # Put symbol and total_shares into variables
        symbol = row["symbol"]
        total_shares = row["total_shares"]

        # Look up price and name for currentsymbol
        symbol = lookup(symbol)

        # Calculate how much the stocks are currently worth (current price * total_shares)
        total = symbol["price"] * total_shares
        symbol["price"] = usd(symbol["price"])

        # Add up totals of all symbols
        total_stocks += total

        # Insert total(in uds) and total_shares into dictionary
        symbol["total"] = usd(total)
        symbol["shares"] = total_shares

        result.append(symbol)

    # Query database for cash
    current_cash = db.execute("SELECT cash FROM users WHERE id = ?", uid)

    # Access cash value
    cash = usd(current_cash[0]["cash"] + total_stocks)

    return render_template("index.html", rows=result, cash=cash, current_cash=usd(current_cash[0]["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # session["user_id"] = 3

    if request.method == "GET":
        return render_template("buy.html")

    else:

        # Access form data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if shares.isnumeric() == False:
            return render_template("apology.html", message="Enter a valid number of shares"), 400

        if shares.find(".") != -1:
            return render_template("apology.html", message="Enter a valid number of shares")

        # Ensure symbol was submitted
        if not symbol:

            if not shares:
                return render_template("apology.html", message="Enter a symbol and a number of shares"), 400

            else:
                return render_template("apology.html", message="Enter a symbol"), 400

        # Ensure shares was submitted
        if not shares:
            return render_template("apology.html", message="Enter a number of shares"), 400

        # Ensure shares is a positive integer
        if int(shares) <= 0:
            return render_template("apology.html", message="Enter a positive number of shares"), 400

        # Ensure symbol is valid
        symbol = request.form.get("symbol")
        symbol = lookup(symbol)

        if symbol is None:
            return render_template("apology.html", message="Unknown symbol"), 400

        # Query database for current cash the user currently has
        uid = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id = ?", uid)

        # Calculate total cost of shares user wants to buy
        total = symbol["price"] * int(shares)

        # Ensure user has enough money to buy the shares he/she wants
        if total > rows[0]["cash"]:
            return render_template("apology.html", message="Amount exceeds total"), 400

        shares = int(shares)
        price = symbol["price"]
        current_time = datetime.datetime.now()
        current_time = current_time.strftime('%Y-%m-%d %H:%M:%S')

        # Store purchase info in history.db
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transactioned) VALUES(?, ?, ?, ?, ?)",
                   uid, symbol["symbol"], shares, price, current_time)

        # Decrease cash amount
        new_cash = rows[0]["cash"] - total

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, uid)

        # Redirect user to home page
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # session["user_id"] = 3

    uid = session["user_id"]
    rows = db.execute("SELECT symbol, shares, price, transactioned FROM history WHERE user_id = ?", uid)

    for i in range(len(rows)):
        rows[i]["price"] = usd(rows[i]["price"])

    return render_template("history.html", rows=rows)


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
            # return render_template("apology.html", message="must provide password")

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


@app.route("/change_password", methods=["GET", "POST"])
def change_password():
    """Change password"""

    if request.method == "GET":
        return render_template("change_password.html")

    else:
        # Ensure username was submitted
        if not request.form.get("username"):
            return render_template("apology.html", massage="must provide username"), 400

        # Ensure old password was submitted
        elif not request.form.get("old_password"):
            return render_template("apology.html", message="must provide password"), 400

        # Ensure new password was submitted
        elif not request.form.get("new_password"):
            return render_template("apology.html", message="must provide new password"), 400

        # Ensure confirmation new password was submitted
        elif not request.form.get("confirm_new_password"):
            return render_template("apology.html", message="must provide password"), 400

        # Ensure new passoword and confirmation new password match
        if request.form.get("new_password") != request.form.get("confirm_new_password"):
            return render_template("apology.html", message="New passswords do not match"), 400

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("old_password")):
            return render_template("apology.html", message="invalid username and/or password"), 400

        # Hash password
        password_hash = generate_password_hash(request.form.get("new_password"))

        # Insert data into database
        db.execute("UPDATE users SET hash = ? WHERE username = ?", password_hash, request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")


@app.route("/extra_cash", methods=["GET", "POST"])
@login_required
def extra_cash():
    """Add extra cash"""

    if request.method == "GET":
        return render_template("extra_cash.html")

    else:
        amount = request.form.get("amount")

        if not amount:
            return render_template("apology.html", message="Please enter the amount you would like to add"), 400

        uid = session["user_id"]

        rows = db.execute("SELECT cash FROM users WHERE id = ?", uid)

        new_cash = rows[0]["cash"] + float(amount)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, uid)

        # Redirect user to home page
        return redirect("/")


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

    else:

        symbol = request.form.get("symbol")
        symbol = lookup(symbol)

        if symbol is None:
            return render_template("apology.html", message="Unknown symbol"), 400

        else:

            symbol["price"] = usd(symbol["price"])
            return render_template("quoted.html", message=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    """
    def check_password(password):
        if len(password) < 8:
            return False
        elif not re.search("[a-z]", password):
            return False
        elif not re.search("[A-Z]", password):
            return False
        elif not re.search("[0-9]", password):
            return False
        elif not re.search("[_@$]", password):
            return False
        elif re.search("\s", password):
            return False
        else:
            return True
    """
    if request.method == "GET":
        return render_template("register.html")

    else:

        # Access form data
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:

            if not password or not confirmation:
                return render_template("apology.html", message="Enter a name and a password", top=400), 400

            else:
                return render_template("apology.html", message="Enter a name", top=400), 400

        # Ensure password was submitted
        if not password:
            return render_template("apology.html", message="Enter a password", top=400), 400

        # Ensure password requirements are met
        # if check_password(password) == False:
            # return render_template("apology.html", message="Your password must be at least 8 characters long and must contain at least one lower case character, one upper case character, one digit and one symbol"), 400

        # Ensure confirmation password was submitted
        if not confirmation:
            return render_template("apology.html", message="Enter a password", top=400), 400

        # Ensure password and confirmation password match
        if password != confirmation:
            return render_template("apology.html", message="Passswords do not match"), 400

        # Ensure username doesn't already exist

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) == 1:
            return render_template("apology.html", message="Username already exists", top=400), 400

        # Hash password
        password_hash = generate_password_hash(password)

        # Insert data into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash)

        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        # Redirect to hompage
        return redirect("/")
        # return render_template("index.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    #session["user_id"] = 3

    uid = session["user_id"]

    if request.method == "GET":
        SYMBOLS = db.execute("SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", uid)
        return render_template("sell.html", rows=SYMBOLS)

    else:
        # Access form data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was submitted
        if not symbol:

            if not shares:
                return render_template("apology.html", message="Enter a symbol and the number of shares you want of sell"), 400

            else:
                return render_template("apology.html", message="Enter a symbol"), 400

        # Ensure shares was submitted
        if not shares:
            return render_template("apology.html", message="Enter the number of shares you want to sell"), 400

        # Ensure only listed symbols are sold
        SYMBOLS = db.execute("SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", uid)

        # Ensure shares is a positive integer
        if int(shares) <= 0:
            return render_template("apology.html", message="Enter a positive number of shares"), 400

        # if symbol not in SYMBOLS:
            # return render_template("apology.html", message="Selected symbol not available. Select a symbol from the list")

        # Ensure the user owns the amount of shares he wants to sell
        rows = db.execute(
            "SELECT SUM(shares) AS total_shares FROM history WHERE user_id = ? AND symbol = ? GROUP BY symbol HAVING SUM(shares)>0", uid, symbol)

        if int(shares) > rows[0]["total_shares"]:
            return render_template("apology.html", message="There are not enough shares available for this transaction"), 400

        # Get current time
        current_time = datetime.datetime.now()
        current_time = current_time.strftime('%Y-%m-%d %H:%M:%S')

        symbol = lookup(symbol)
        total = symbol["price"] * int(shares)

        # symbol["price"] = usd(symbol["price"])

        shares = -(int(shares))

        # Store purchase info in history.db
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transactioned) VALUES(?, ?, ?, ?, ?)",
                   uid, symbol["symbol"], shares, symbol["price"], current_time)

        # Query database for cash
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", uid)

        # Increase cash amount
        cash = current_cash[0]["cash"] + total

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, uid)

        # Redirect user to home page
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
