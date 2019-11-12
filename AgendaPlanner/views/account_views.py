import  flask

from infrastructure.view_modifiers import  response

account = flask.Blueprint('account', __name__, url_prefix='/account')


@account.route('/register', methods=['GET'])
@response(template_file='account/register.html')
def register_get():
    return {}


@account.route('/register', methods=['POST'])
@response(template_file='account/register.html')
def register_post():
    return {}


@account.route('/login', methods=['GET'])
@response(template_file='account/login.html')
def login_get():
    return {}


@account.route('/login', methods=['POST'])
@response(template_file='account/login.html')
def login_post():
    return {}


@account.route('/logout')
def logout():
    return flask.abort(404)