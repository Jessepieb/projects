import flask

from infrastructure.view_modifiers import response

homepage = flask.Blueprint('home', __name__, url_prefix='/')


def get_latest_packages():
    return [
        {'name': 'flask', 'version': '1.2.3'},
        {'name': 'sqlalchemy', 'version': '2.2.0'},
        {'name': 'passlib', 'version': '3.0.0'},
    ]


@homepage.route('/')
@response(template_file='home/index.html')
def index():
    # return "Hello World!"
    test_packages = get_latest_packages()
    # return flask.render_template('home/index.html', packages=test_packages)
    return {'packages': test_packages}


@homepage.route('/about')
@response(template_file='home/about.html')
def about():
    return{}
