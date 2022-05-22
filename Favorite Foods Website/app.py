from flask import Flask, redirect, render_template, request, session, url_for
import os
import sqlite3 as sl

app = Flask(__name__)
db = "favouriteFoods.db"


# root end point
# routes to login unless client has already logged in
@app.route("/")
def home():
    """
    Checks whether the user is logged in and returns appropriately.

    :return: renders login.html if not logged in,
                redirects to client otherwise.
    """
    # TODO: your code goes here and replaces 'pass' below
    # If, not logged in render the login page
    if not session.get("logged_in"):
        return render_template('login.html')
    # Otherwise, reroute to client page
    else:
        return redirect(url_for('client'))


# client endpoint
# renders appropriate template (admin or user)
@app.route("/client")
def client():
    """
    Renders appropriate template (admin or user)

    :return: redirects home if not logged in,
                renders admin.html if logged in as admin,
                user.html otherwise
    """
    # TODO: your code goes here and replaces 'pass' below
    # If not logged in, go back to home
    if not session.get("logged_in"):
        return redirect(url_for('home'))
    # If we are logged in as an admin, render the admin page with appropriate parameters
    elif session["username"] == "admin":
        return render_template("admin.html", username=session["username"], result=db_get_user_list())
    # If logged in as a user, render user page with appropriate parameters
    else:
        return render_template("user.html", username=session["username"], fav_food=db_get_food(session["username"]))


# create user endpoint (admin only)
# adds new user to db, then re-renders admin template
@app.route("/action/createuser", methods=["POST", "GET"])
def create_user():
    """
    Callable from admin.html only
    Adds a new user to db by calling db_create_user, then re-renders admin template

    :return: redirects to home if user not logged in,
                re-renders admin.html otherwise
    """
    # TODO: your code goes here and replaces 'pass' below
    # If we are not logged in, reroute to home
    if not session.get("logged_in"):
        return redirect(url_for('home'))
    # Create a new user in database with the submitted username and password
    if request.method == "POST":
        db_create_user(request.form["username"], request.form["password"])
    # Re-render admin.html
    return render_template("admin.html", username=session["username"], result=db_get_user_list())


# remove user endpoint (admin only)
# removes user from db, then re-renders admin template
@app.route("/action/removeuser", methods=["POST", "GET"])
def remove_user():
    """
    Callable from admin.html only
    Removes user from the db by calling db_remove_user, then re-renders admin template.

    :return: redirects to home if user not logged in,
                re-renders admin.html otherwise
    """
    # TODO: your code goes here and replaces 'pass' below
    # If not logged in, reroute to home
    if not session.get("logged_in"):
        return redirect(url_for('home'))
    # Remove the user from the database and re-render admin.html
    if request.method == "POST":
        db_remove_user(request.form["username"])
    return render_template("admin.html", username=session["username"], result=db_get_user_list())


# set food endpoint (user only)
# updates user food, then re-renders user template
@app.route("/action/setfood", methods=["POST", "GET"])
def set_food():
    """
    Callable from user.html only,
    Updates user food by calling db_set_food, then re-renders user template

    :return: redirects to home if user not logged in,
                re-renders user.html otherwise
    """
    # TODO: your code goes here and replaces 'pass' below
    # If not logged in, reroute to home
    if not session.get("logged_in"):
        return redirect(url_for('home'))
    # Set the users favorite food in the database and re-render user page
    if request.method == "POST":
        db_set_food(session["username"], request.form["set_fav_food"])
    return render_template("user.html", username=session["username"], fav_food=db_get_food(session["username"]))


# login endpoint
# allows client to log in (checks creds)
@app.route("/login", methods=["POST", "GET"])
def login():
    """
    Allows client to log in
    Calls db_check_creds to see if supplied username and password are correct

    :return: redirects to client if login correct,
                redirects back to home otherwise
    """
    # TODO: your code goes here and replaces 'pass' below
    if request.method == "POST":
        # If the information matches the admins login info, set login to true and reroute to client to handle rendering
        if request.form["username"] == "admin" and request.form["password"] == "passwords":
            session["username"] = request.form["username"]
            session["logged_in"] = True
            return redirect(url_for("client"))
        # If login info matches a database user, set login to true and reroute to client for page rendering
        elif db_check_creds(request.form["username"], request.form["password"]):
            session["username"] = request.form["username"]
            session["logged_in"] = True
            return redirect(url_for("client"))
        # If none works, ask for another login
        return redirect(url_for("home"))


# logout endpoint
@app.route("/logout", methods=["POST", "GET"])
def logout():
    """
    Logs client out, then routes to login
    Remove the user from the session
    :return: redirects back to home
    """
    # TODO: your code goes here and replaces 'pass' below
    # Set login to false and end session
    if request.method == "POST":
        session["logged_in"] = False
        session.pop("username",None)
    return redirect(url_for("home"))


def db_get_user_list() -> dict:
    """
    Queries the DB's userfoods table to get a list
    of all the user and their corresponding favorite food for display on admin.html.
    Called to render admin.html template.

    :return: a dictionary with username as key and their favorite food as value
                this is what populates the 'result' variable in the admin.html template
    """
    # TODO: your code goes here and replaces 'pass' below
    # Establish connection to database
    conn = sl.connect(db)
    curs = conn.cursor()
    # Select all users from the database
    cmd = 'SELECT * FROM credentials'
    # Execute command and store in users
    # 0th index is name and 1st is the password
    users = curs.execute(cmd)
    conn.commit()
    # Create a dictionary that will hold a username and favorite food
    d = {}
    for item in users:
        # First value in database is admin
        if item[0] != "admin":
            # Name is key and favorite food is value
            d[item[0]] = db_get_food(item[0])
    conn.close()
    return d


def db_create_user(un: str, pw: str) -> None:
    """
    Add provided user and password to the credentials table
    Add provided user to the userfoods table
    and sets their favorite food to "not set yet".
    Called from create_user() view function.

    :param un: username to create
    :param pw: password to create
    :return: None
    """
    # TODO: your code goes here and replaces 'pass' below
    # Establish connection to database
    conn = sl.connect(db)
    curs = conn.cursor()
    # Create a new user in the database
    sub = (un, pw,)
    cmd = 'INSERT INTO credentials (username, password) VALUES (?, ?)'
    curs.execute(cmd, sub)
    # Set favorite food
    food = (un, 'None')
    cmd = 'INSERT INTO userfoods VALUES (?, ?)'
    # Execute command and close the connection
    curs.execute(cmd, food)
    conn.commit()
    conn.close()


def db_remove_user(un: str) -> None:
    """
    Removes provided user from all DB tables.
    Called from remove_user() view function.

    :param un: username to remove from DB
    :return: None
    """
    # TODO: your code goes here and replaces 'pass' below
    # Establish connection
    conn = sl.connect(db)
    curs = conn.cursor()
    # Remove a user from the database
    sub = (un,)
    cmd = 'DELETE FROM credentials WHERE `username` = ?'
    curs.execute(cmd, sub)
    conn.commit()
    conn.close()


def db_get_food(un: str) -> str:
    """
    Gets the provided user's favorite food from the DB.
    Called to render user.html fav_food template variable.

    :param un: username to get favorite food of
    :return: the favorite food of the provided user as a string
    """
    # TODO: your code goes here and replaces 'pass' below
    # Establish connection to server
    conn = sl.connect(db)
    curs = conn.cursor()
    # Create commands
    sub = (un,)
    cmd = 'SELECT food FROM userfoods WHERE `username` = ?'
    # Obtain the users favorite food
    curs.execute(cmd, sub)
    # Store pairing in variable
    food = curs.fetchone()
    conn.commit()
    conn.close()
    return food[0]


def db_set_food(un: str, ff: str) -> None:
    """
    Sets the favorite food of user, un param, to new incoming ff (favorite food) param.
    Called from set_food() view function.

    :param un: username to update favorite food of
    :param ff: user's new favorite food
    :return: None
    """
    # TODO: your code goes here and replaces 'pass' below
    # Establish connections to database
    conn = sl.connect(db)
    curs = conn.cursor()
    # Create statements to set food
    sub = (ff, un,)
    cmd = 'UPDATE userfoods SET `food` = ? WHERE `username` = ?'
    curs.execute(cmd, sub)
    # Commit and close connection
    conn.commit()
    conn.close()


def db_check_creds(un: str, pw: str) -> bool:
    """
    Checks to see if supplied username and password are in the DB's credentials table.
    Called from login() view function.

    :param un: username to check
    :param pw: password to check
    :return: True if both username and password are correct, False otherwise.
    """
    # TODO: your code goes here and replaces 'pass' below
    # Establish connection to database
    conn = sl.connect(db)
    curs = conn.cursor()
    sub = (un, pw,)
    # Find the username and password in database
    cmd = 'SELECT * FROM credentials WHERE `username` = ? AND `password` = ?'
    curs.execute(cmd, sub)
    # Fetch the login info
    info = curs.fetchone()
    conn.commit()
    conn.close()
    # If null, return False and do not login
    if info is None:
        return False
    return True


if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    app.run(debug=True)
