import os

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Define datetime for now
now = datetime.now()


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    # get list of dictionairs in portfolio
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = ?", session["user_id"])

    # update the price of each stock
    for row in portfolio:
        info = lookup(row["stock"])
        if info:
            db.execute("UPDATE portfolio SET price = ? WHERE user_id = ? AND stock = ?",
                       float(info["price"]), session["user_id"], row["stock"])
            total = row["shares"] * float(info["price"])
            db.execute("UPDATE portfolio SET total = ? WHERE user_id = ? AND stock = ?",
                       total, session["user_id"], row["stock"])

    # get updated list of dictionairs in portfolio
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = ?", session["user_id"])

    # get availible cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    return render_template("index.html", portfolio=portfolio, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Ensure symbol was submitted
        stock = request.form.get("symbol")
        if not stock:
            return apology("must provide a stock symbol")

        # Ensure symbol exists
        info = lookup(stock)
        if not info:
            return apology("symbol does not exist")

        # Ensure shares was submitted
        shares = request.form.get("shares")
        if not shares:
            return apology("must provide a number of stock shares")

        try:
            shares = int(shares)

        except ValueError:
            return apology("share's need to be an integer")

        # Ensure shares is a positive number
        if shares < 1:
            return apology("number of shares can't be 0 or negative")

        # Ensure user can affort the purchase
        total = shares * float(info["price"])
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if total > cash:
            return apology("insufficient funds")

        # Insert in stock_transaction table
        db.execute("INSERT INTO stock_transaction (stock, price, shares, type, total, date, user_id) VALUES(?, ?, ?, ?, ?, ?, ?)",
                   stock, float(info["price"]), shares, "buy", total, now, session["user_id"])

        # Update the portfolio table
        checkPortfolio = db.execute(
            "SELECT stock FROM portfolio WHERE stock = ? AND user_id = ?", stock, session["user_id"])
        if len(checkPortfolio) == 0:
            db.execute("INSERT INTO portfolio (stock, shares, price, total, user_id) VALUES(?, ?, ?, ?, ?)",
                       stock, shares, float(info["price"]), total, session["user_id"])
        else:
            db.execute("UPDATE portfolio SET shares = shares + ? WHERE stock = ? AND user_id = ?",
                       shares, stock, session["user_id"])

        # Update available cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total, session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM stock_transaction WHERE user_id = ?", session["user_id"])
    return render_template("history.html", history=history)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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

    else:
        stocks = lookup(request.form.get("symbol"))
        if not stocks:
            return apology("symbol does not exist")
        return render_template("quoted.html", stocks=stocks)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        uName = request.form.get("username")
        if not uName:
            return apology("must provide username")

        # Ensure password was submitted
        uPassword = request.form.get("password")
        if not uPassword:
            return apology("must provide password")

        # Ensure password was confirmed
        uConfirmation = request.form.get("confirmation")
        if not uConfirmation:
            return apology("must provide a password confirmation")

        # Ensure password matches with confirmation
        if uPassword != uConfirmation:
            return apology("password must match")

        rows = db.execute("SELECT * FROM users WHERE username = ?", uName)
        if len(rows) > 0:
            return apology("username already exists")

        # Generate hash
        uPassword = generate_password_hash(uPassword)

        # Insert info into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", uName, uPassword)

        session["user_id"] = db.execute("SELECT id FROM users WHERE username = ?", uName)[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        rows = db.execute("SELECT stock FROM portfolio WHERE user_id = ?", session["user_id"])
        SYMBOLS = [row["stock"] for row in rows]

        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol or symbol not in SYMBOLS:
            return apology("must provide a stock symbol")

        # Ensure symbol exists
        info = lookup(symbol)
        if not info:
            return apology("symbol does not exist")

        # Ensure shares was submitted
        shares = request.form.get("shares")
        if not shares:
            return apology("must provide a number of stock shares")

        try:
            shares = int(shares)

        except:
            return apology("share's need to be an integer")

        # Ensure shares is a positive number
        if shares < 1:
            return apology("number of shares can't be 0 or negative")

        # Ensure user have the stock and shares he/she want to sell
        row = db.execute("SELECT * FROM portfolio WHERE user_id = ? AND stock = ?",
                         session["user_id"], symbol)

        if len(row) != 1 or row[0]["shares"] < shares:
            return apology("You don't have enough shares to sell")

        else:
            total = shares * float(info["price"])

            # Update the portfolio table
            checkPortfolio = db.execute(
                "SELECT * FROM portfolio WHERE stock = ? AND user_id = ?", symbol, session["user_id"])
            if checkPortfolio[0]["shares"] == shares:
                db.execute("DELETE FROM portfolio WHERE stock = ? AND user_id = ?",
                           symbol, session["user_id"])
            else:
                db.execute("UPDATE portfolio SET shares = shares - ? WHERE stock = ? AND user_id = ?",
                           shares, symbol, session["user_id"])

            # Update available cash
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total, session["user_id"])

            # Insert in stock_transaction table
            db.execute("INSERT INTO stock_transaction (stock, price, shares, type, total, date, user_id) VALUES(?, ?, ?, ?, ?, ?, ?)", symbol, float(
                info["price"]), shares, "sell", total, now, session["user_id"])

            return redirect("/")

    else:
        SYMBOLS = [row["stock"] for row in db.execute("SELECT stock FROM portfolio WHERE user_id = ?", session["user_id"])]
        return render_template("sell.html", symbols=SYMBOLS)
